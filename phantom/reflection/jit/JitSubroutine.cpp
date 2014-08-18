/* ******************* Includes ****************** */
#include "phantom/jit.h"
#include "JitSubroutine.h"
#include "JitSubroutine.hxx"
#include "JitClass.h"
#include "JitSignal.h"
#include "JitLocalVariable.h"
#include "phantom/def_jit_internal.h"
/* *********************************************** */
o_registerN((phantom, reflection, jit), JitSubroutine);

o_namespace_begin(phantom, reflection, jit)

JitSubroutine::JitSubroutine(Subroutine* a_pSubroutine, EJitAbi a_eAbi) 
    : m_pSubroutine(a_pSubroutine)
    , m_eAbi(a_eAbi)
{
    if(m_jit_context.context)
    {
        unregisterJitFunction(m_jit_function);
        jit_context_destroy((jit_context_t)m_jit_context.context);
    }
    m_jit_context.context = jit_context_create();
    m_jit_function = jit_function_create((jit_context_t)m_jit_context.context, toJitSignature(m_eAbi, getSignature()));
    
    jit_function_set_optimization_level((jit_function_t)m_jit_function.function, 0);
    registerJitFunction(m_jit_function, this);
}

JitSubroutine::~JitSubroutine( void )
{
    jit_context_destroy((jit_context_t)m_jit_context.context);
}

void JitSubroutine::compileDebugPrint( const char* to_print )
{
    startCompilation();
    static std::set<string> s_print_text;
    s_print_text.insert(to_print);
    auto it = s_print_text.find(to_print);
    std::set<string>::const_reference text = *it;


    size_t argCount = m_pSubroutine->getSignature()->getParameterCount()+1; // parameters+this
    jit_value_t* args = o_allocate_n(argCount, jit_value_t); 

    jit_function func = getJitFunction();

    // call printf

    jit_type_t printf_param0 = jit_type_void_ptr;
    jit_type_t printf_signature = jit_type_create_signature(jit_abi_vararg, jit_type_void, &printf_param0, 1, 0);
    jit_value_t text_ptr_value = jit_value_create_nint_constant((jit_function_t)func.function, jit_type_void_ptr, (jit_nint)text.c_str());
    jit_insn_call_native((jit_function_t)func.function, "printf", (void*)printf, printf_signature, &text_ptr_value, 1, 0);
    
    endCompilation();

    o_deallocate_n(args, argCount, jit_value_t);
}

jit_context JitSubroutine::getContext() const
{
    return m_jit_context;
}

void JitSubroutine::instructionCompilationCallback( void* insn, byte* start, byte* end )
{   
    if(start == end) return; // empty instruction => skip
    jit_function func;
    jit_value_t value1 = jit_insn_get_value1((jit_insn_t)insn);
    jit_value_t value2 = jit_insn_get_value2((jit_insn_t)insn);
    if(value1)
        func = jit_value_get_function(value1);
    if(value2)
        func = jit_value_get_function(value2);

    if(func.function == nullptr)
    {
        func = jitFunctionFromMemoryAddressEnd(start); 
    }
    if(func.function)
    {
        JitSubroutine* pCompiledInstanceMemberFunction = jitSubroutine(func);
        Subroutine* pSubroutine = pCompiledInstanceMemberFunction->getSubroutine();
        o_assert(pCompiledInstanceMemberFunction);
        if(pSubroutine->getMemoryStart() == 0) 
            pSubroutine->setMemoryStart(start);
        pSubroutine->setMemoryEnd(end);
        unsigned short start_line;
        unsigned short start_column;
        unsigned short end_line;
        unsigned short end_column;
        jit_insn_get_code_location((jit_insn_t)insn, &start_line, &start_column, &end_line, &end_column);
        SourceFile* pSourceFile = pSubroutine->getCodeLocation().getSourceFile();
        CodeLocation codeLocation(CodePosition(pSourceFile, start_line, start_column)
            , CodePosition(pSourceFile, end_line, end_column));
        pSubroutine->addInstruction(new Instruction(jit_insn_get_opcode((jit_insn_t)insn), codeLocation, MemoryLocation(start, end)));
    }
    else 
    {
        o_warning(false, "func not found");
    }
}

void JitSubroutine::compilationSuccessCallback(void* func)
{
    JitSubroutine* pCompiledInstanceMemberFunction = jitSubroutine(func);
    o_assert(pCompiledInstanceMemberFunction);
    Subroutine* pSubroutine = pCompiledInstanceMemberFunction->getSubroutine();
    o_assert(pSubroutine);
    if(pSubroutine->getBlock() == nullptr) 
        return ;
    vector<LocalVariable*> localVariables;
    pSubroutine->getBlock()->getLocalVariablesCascade(localVariables);
    size_t count = pSubroutine->getInstructionCount();
    vector<Instruction*> undefinedInstructions;
    CodeLocation replacementCodeLocation;
    for(size_t i = 0; i<count; ++i)
    {
        Instruction* pInstruction = pSubroutine->getInstruction(i);
        if(pInstruction->getCodeLocation() == CodeLocation())
        {
            if(replacementCodeLocation != CodeLocation())
            {
                // worst hack ever because i forgot to define setCodeLocation...
                *(CodeLocation*)((byte*)pInstruction+8) = replacementCodeLocation;
            }
            undefinedInstructions.push_back(pInstruction);
        }
        else 
        {
            replacementCodeLocation = pInstruction->getCodeLocation();
            for(auto it = undefinedInstructions.begin(); it != undefinedInstructions.end(); ++it)
            {
                *(CodeLocation*)((byte*)(*it)+8) = replacementCodeLocation;
            }
            undefinedInstructions.clear();
        }
    }
    for(auto it = localVariables.begin(); it != localVariables.end(); ++it)
    {
        JitLocalVariable* pLocalVariable = static_cast<JitLocalVariable*>(*it);
        pLocalVariable->setupFrame();
    }
}

inline void JitSubroutine::startCompilation()
{
    o_assert(!jit_function_is_compiled((jit_function_t)m_jit_function.function));
    jit_function_set_insn_compilation_callback((jit_function_t)m_jit_function.function, (jit_function_insn_compilation_callback_t) &JitSubroutine::instructionCompilationCallback);
    jit_function_set_compilation_success_callback((jit_function_t)m_jit_function.function, (jit_function_compilation_success_callback)&JitSubroutine::compilationSuccessCallback);
    jit_context_build_start((jit_context_t)m_jit_context.context);
}

inline void JitSubroutine::endCompilation()
{
    jit_function_compile((jit_function_t)m_jit_function.function);
    jit_function_set_insn_compilation_callback((jit_function_t)m_jit_function.function, nullptr);
    jit_context_build_end((jit_context_t)m_jit_context.context);
    installClosures();
}

inline void JitSubroutine::abortCompilation()
{
    jit_function_abandon((jit_function_t)m_jit_function.function);
    jit_function_set_insn_compilation_callback((jit_function_t)m_jit_function.function, nullptr);
    jit_context_build_end((jit_context_t)m_jit_context.context);
    unregisterJitFunction(m_jit_function);
    jit_context_destroy((jit_context_t)m_jit_context.context);
}

inline inline jit_value   JitSubroutine::load (jit_value value) 
{
    return jit_value(jit_insn_load((jit_function_t)m_jit_function.function, (jit_value_t)value.value), value.type);
}

inline inline jit_value   JitSubroutine::dup (jit_value value) 
{
    return jit_value(jit_insn_dup((jit_function_t)m_jit_function.function, (jit_value_t)value.value), value.type);
}

inline inline jit_value   JitSubroutine::loadSmall (jit_value value) 
{
    return jit_value(jit_insn_load_small((jit_function_t)m_jit_function.function, (jit_value_t)value.value), value.type);
}

inline int         JitSubroutine::store (jit_value dest, jit_value value) 
{
    return jit_insn_store((jit_function_t)m_jit_function.function, (jit_value_t)dest.value, (jit_value_t)value.value);
}

inline inline jit_value   JitSubroutine::loadRelative (jit_value value, int offset, Type* type) 
{
    return jit_value(jit_insn_load_relative((jit_function_t)m_jit_function.function, (jit_value_t)value.value, offset, toJitType(type)), type);
}

inline int         JitSubroutine::storeRelative (jit_value dest, int offset, jit_value value) 
{
    return jit_insn_store_relative((jit_function_t)m_jit_function.function, (jit_value_t)dest.value, offset, (jit_value_t)value.value);
}

inline inline jit_value   JitSubroutine::addRelative (jit_value value, int offset) 
{
    return jit_insn_add_relative((jit_function_t)m_jit_function.function, (jit_value_t)value.value, offset);
}

inline inline jit_value   JitSubroutine::loadElem (jit_value base_addr, jit_value index, Type* elem_type) 
{
    return jit_value(jit_insn_load_elem((jit_function_t)m_jit_function.function, (jit_value_t)base_addr.value, (jit_value_t)index.value, toJitType(elem_type)), elem_type);
}

inline inline jit_value   JitSubroutine::loadElemAddress (jit_value base_addr, jit_value index, Type* elem_type) 
{
    return jit_value(jit_insn_load_elem_address((jit_function_t)m_jit_function.function, (jit_value_t)base_addr.value, (jit_value_t)index.value, toJitType(elem_type)), elem_type->pointerType());
}

inline int         JitSubroutine::storeElem (jit_value base_addr, jit_value index, jit_value value) 
{
    return jit_insn_store_elem((jit_function_t)m_jit_function.function, (jit_value_t)base_addr.value, (jit_value_t)index.value, (jit_value_t)value.value);
}

inline int         JitSubroutine::checkNull (jit_value value) 
{
    return jit_insn_check_null((jit_function_t)m_jit_function.function, (jit_value_t)value.value);
}

inline inline jit_value   JitSubroutine::add (jit_value value1, jit_value value2) 
{
    return jit_insn_add((jit_function_t)m_jit_function.function, (jit_value_t)value1.value, (jit_value_t)value2.value);
}

inline inline jit_value   JitSubroutine::addOVF (jit_value value1, jit_value value2) 
{
    return jit_insn_add_ovf((jit_function_t)m_jit_function.function, (jit_value_t)value1.value, (jit_value_t)value2.value);
}

inline inline jit_value   JitSubroutine::sub (jit_value value1, jit_value value2) 
{
    return jit_insn_add_ovf((jit_function_t)m_jit_function.function, (jit_value_t)value1.value, (jit_value_t)value2.value);
}

inline inline jit_value   JitSubroutine::subOVF (jit_value value1, jit_value value2) 
{
    return jit_insn_sub_ovf((jit_function_t)m_jit_function.function, (jit_value_t)value1.value, (jit_value_t)value2.value);
}

inline inline jit_value   JitSubroutine::mul (jit_value value1, jit_value value2) 
{
    return jit_insn_mul((jit_function_t)m_jit_function.function, (jit_value_t)value1.value, (jit_value_t)value2.value);
}

inline inline jit_value   JitSubroutine::mulOVF (jit_value value1, jit_value value2) 
{
    return jit_insn_mul_ovf((jit_function_t)m_jit_function.function, (jit_value_t)value1.value, (jit_value_t)value2.value);
}

inline inline jit_value   JitSubroutine::div (jit_value value1, jit_value value2) 
{
    return jit_insn_div((jit_function_t)m_jit_function.function, (jit_value_t)value1.value, (jit_value_t)value2.value);
}

inline inline jit_value   JitSubroutine::rem (jit_value value1, jit_value value2) 
{
    return jit_insn_rem((jit_function_t)m_jit_function.function, (jit_value_t)value1.value, (jit_value_t)value2.value);
}

inline inline jit_value   JitSubroutine::remIEEE (jit_value value1, jit_value value2) 
{
    return jit_insn_rem_ieee((jit_function_t)m_jit_function.function, (jit_value_t)value1.value, (jit_value_t)value2.value);
}

inline jit_value   JitSubroutine::neg (jit_value value1) 
{
    return jit_insn_neg((jit_function_t)m_jit_function.function, (jit_value_t)value1.value);
}

inline jit_value   JitSubroutine::and (jit_value value1, jit_value value2) 
{
    return jit_insn_and((jit_function_t)m_jit_function.function, (jit_value_t)value1.value, (jit_value_t)value2.value);
}

inline jit_value   JitSubroutine::or (jit_value value1, jit_value value2) 
{
    return jit_insn_or((jit_function_t)m_jit_function.function, (jit_value_t)value1.value, (jit_value_t)value2.value);
}

inline jit_value   JitSubroutine::xor (jit_value value1, jit_value value2) 
{
    return jit_insn_xor((jit_function_t)m_jit_function.function, (jit_value_t)value1.value, (jit_value_t)value2.value);
}

inline jit_value   JitSubroutine::not (jit_value value1) 
{
    return jit_insn_not((jit_function_t)m_jit_function.function, (jit_value_t)value1.value);
}

inline jit_value   JitSubroutine::shl (jit_value value1, jit_value value2) 
{
    return jit_insn_shl((jit_function_t)m_jit_function.function, (jit_value_t)value1.value, (jit_value_t)value2.value);
}

inline jit_value   JitSubroutine::shr (jit_value value1, jit_value value2) 
{
    return jit_insn_shr((jit_function_t)m_jit_function.function, (jit_value_t)value1.value, (jit_value_t)value2.value);
}

inline jit_value   JitSubroutine::ushr (jit_value value1, jit_value value2) 
{
    return jit_insn_ushr((jit_function_t)m_jit_function.function, (jit_value_t)value1.value, (jit_value_t)value2.value);
}

inline jit_value   JitSubroutine::sshr (jit_value value1, jit_value value2) 
{
    return jit_insn_sshr((jit_function_t)m_jit_function.function, (jit_value_t)value1.value, (jit_value_t)value2.value);
}

inline jit_value   JitSubroutine::eq (jit_value value1, jit_value value2) 
{
    return jit_insn_eq((jit_function_t)m_jit_function.function, (jit_value_t)value1.value, (jit_value_t)value2.value);
}

inline jit_value   JitSubroutine::ne (jit_value value1, jit_value value2) 
{
    return jit_insn_ne((jit_function_t)m_jit_function.function, (jit_value_t)value1.value, (jit_value_t)value2.value);
}

inline jit_value   JitSubroutine::lt (jit_value value1, jit_value value2) 
{
    return jit_insn_lt((jit_function_t)m_jit_function.function, (jit_value_t)value1.value, (jit_value_t)value2.value);
}

inline jit_value   JitSubroutine::le (jit_value value1, jit_value value2) 
{
    return jit_insn_le((jit_function_t)m_jit_function.function, (jit_value_t)value1.value, (jit_value_t)value2.value);
}

inline jit_value   JitSubroutine::gt (jit_value value1, jit_value value2) 
{
    return jit_insn_gt((jit_function_t)m_jit_function.function, (jit_value_t)value1.value, (jit_value_t)value2.value);
}

inline jit_value   JitSubroutine::ge (jit_value value1, jit_value value2) 
{
    return jit_insn_ge((jit_function_t)m_jit_function.function, (jit_value_t)value1.value, (jit_value_t)value2.value);
}

inline jit_value   JitSubroutine::cmpl (jit_value value1, jit_value value2) 
{
    return jit_insn_cmpl((jit_function_t)m_jit_function.function, (jit_value_t)value1.value, (jit_value_t)value2.value);
}

inline jit_value   JitSubroutine::cmpg (jit_value value1, jit_value value2) 
{
    return jit_insn_cmpg((jit_function_t)m_jit_function.function, (jit_value_t)value1.value, (jit_value_t)value2.value);
}

inline jit_value   JitSubroutine::toBool (jit_value value1) 
{
    return jit_insn_to_bool((jit_function_t)m_jit_function.function, (jit_value_t)value1.value);
}

inline jit_value   JitSubroutine::toNotBool (jit_value value1) 
{
    return jit_insn_to_not_bool((jit_function_t)m_jit_function.function, (jit_value_t)value1.value);
}

inline jit_value JitSubroutine::callIntrinsic( const string& a_strInstrinsicName, jit_value* a_pValues, size_t a_uiValueCount )
{
    switch(a_uiValueCount)
    {
    case 1:
        return callIntrinsic(a_strInstrinsicName, a_pValues[0] );
    case 2:                
        return callIntrinsic(a_strInstrinsicName, a_pValues[0], a_pValues[1] );
    case 3:                  
        return callIntrinsic(a_strInstrinsicName, a_pValues[0], a_pValues[1], a_pValues[2] );
    case 4:                  
        return callIntrinsic(a_strInstrinsicName, a_pValues[0], a_pValues[1], a_pValues[2], a_pValues[3] );
    }
    return jit_value();
}

inline jit_value   JitSubroutine::acos BOOST_PREVENT_MACRO_SUBSTITUTION (jit_value value1) 
{
    return jit_insn_acos((jit_function_t)m_jit_function.function, (jit_value_t)value1.value);
}

inline jit_value   JitSubroutine::asin BOOST_PREVENT_MACRO_SUBSTITUTION (jit_value value1) 
{
    return jit_insn_asin((jit_function_t)m_jit_function.function, (jit_value_t)value1.value);
}

inline jit_value   JitSubroutine::atan BOOST_PREVENT_MACRO_SUBSTITUTION (jit_value value1) 
{
    return jit_insn_atan((jit_function_t)m_jit_function.function, (jit_value_t)value1.value);
}

inline jit_value   JitSubroutine::atan2 BOOST_PREVENT_MACRO_SUBSTITUTION (jit_value value1, jit_value value2) 
{
    return jit_insn_atan2((jit_function_t)m_jit_function.function, (jit_value_t)value1.value, (jit_value_t)value2.value);
}

inline jit_value   JitSubroutine::cos BOOST_PREVENT_MACRO_SUBSTITUTION (jit_value value1) 
{
    return jit_insn_cos((jit_function_t)m_jit_function.function, (jit_value_t)value1.value);
}

inline jit_value   JitSubroutine::cosh BOOST_PREVENT_MACRO_SUBSTITUTION (jit_value value1) 
{
    return jit_insn_cosh((jit_function_t)m_jit_function.function, (jit_value_t)value1.value);
}

inline jit_value   JitSubroutine::exp BOOST_PREVENT_MACRO_SUBSTITUTION (jit_value value1) 
{
    return jit_insn_exp((jit_function_t)m_jit_function.function, (jit_value_t)value1.value);
}

inline jit_value   JitSubroutine::log BOOST_PREVENT_MACRO_SUBSTITUTION (jit_value value1) 
{
    return jit_insn_log((jit_function_t)m_jit_function.function, (jit_value_t)value1.value);
}

inline jit_value   JitSubroutine::log10 BOOST_PREVENT_MACRO_SUBSTITUTION (jit_value value1) 
{
    return jit_insn_log10((jit_function_t)m_jit_function.function, (jit_value_t)value1.value);
}

inline jit_value   JitSubroutine::pow BOOST_PREVENT_MACRO_SUBSTITUTION (jit_value value1, jit_value value2) 
{
    return jit_insn_pow((jit_function_t)m_jit_function.function, (jit_value_t)value1.value, (jit_value_t)value2.value);
}

inline jit_value   JitSubroutine::sin BOOST_PREVENT_MACRO_SUBSTITUTION (jit_value value1) 
{
    return jit_insn_sin((jit_function_t)m_jit_function.function, (jit_value_t)value1.value);
}

inline jit_value   JitSubroutine::sinh BOOST_PREVENT_MACRO_SUBSTITUTION (jit_value value1) 
{
    return jit_insn_sinh((jit_function_t)m_jit_function.function, (jit_value_t)value1.value);
}

inline jit_value   JitSubroutine::sqrt BOOST_PREVENT_MACRO_SUBSTITUTION (jit_value value1) 
{
    return jit_insn_sqrt((jit_function_t)m_jit_function.function, (jit_value_t)value1.value);
}

inline jit_value   JitSubroutine::tan BOOST_PREVENT_MACRO_SUBSTITUTION (jit_value value1) 
{
    return jit_insn_tan((jit_function_t)m_jit_function.function, (jit_value_t)value1.value);
}

inline jit_value   JitSubroutine::tanh BOOST_PREVENT_MACRO_SUBSTITUTION (jit_value value1) 
{
    return jit_insn_tanh((jit_function_t)m_jit_function.function, (jit_value_t)value1.value);
}

inline jit_value   JitSubroutine::ceil BOOST_PREVENT_MACRO_SUBSTITUTION (jit_value value1) 
{
    return jit_insn_ceil((jit_function_t)m_jit_function.function, (jit_value_t)value1.value);
}

inline jit_value   JitSubroutine::floor BOOST_PREVENT_MACRO_SUBSTITUTION (jit_value value1) 
{
    return jit_insn_floor((jit_function_t)m_jit_function.function, (jit_value_t)value1.value);
}

inline jit_value   JitSubroutine::rint BOOST_PREVENT_MACRO_SUBSTITUTION (jit_value value1) 
{
    return jit_insn_rint((jit_function_t)m_jit_function.function, (jit_value_t)value1.value);
}

inline jit_value   JitSubroutine::round BOOST_PREVENT_MACRO_SUBSTITUTION (jit_value value1) 
{
    return jit_insn_round((jit_function_t)m_jit_function.function, (jit_value_t)value1.value);
}

inline jit_value   JitSubroutine::trunc BOOST_PREVENT_MACRO_SUBSTITUTION (jit_value value1) 
{
    return jit_insn_trunc((jit_function_t)m_jit_function.function, (jit_value_t)value1.value);
}

inline jit_value   JitSubroutine::isNAN (jit_value value1) 
{
    return jit_insn_is_nan((jit_function_t)m_jit_function.function, (jit_value_t)value1.value);
}

inline jit_value   JitSubroutine::isFinite (jit_value value1) 
{
    return jit_insn_is_finite((jit_function_t)m_jit_function.function, (jit_value_t)value1.value);
}

inline jit_value   JitSubroutine::isInf (jit_value value1) 
{
    return jit_insn_is_inf((jit_function_t)m_jit_function.function, (jit_value_t)value1.value);
}

inline jit_value   JitSubroutine::abs BOOST_PREVENT_MACRO_SUBSTITUTION (jit_value value1) 
{
    return jit_insn_abs((jit_function_t)m_jit_function.function, (jit_value_t)value1.value);
}

inline jit_value   JitSubroutine::min BOOST_PREVENT_MACRO_SUBSTITUTION (jit_value value1, jit_value value2) 
{
    return jit_insn_min((jit_function_t)m_jit_function.function, (jit_value_t)value1.value, (jit_value_t)value2.value);
}

inline jit_value   JitSubroutine::max BOOST_PREVENT_MACRO_SUBSTITUTION (jit_value value1, jit_value value2) 
{
    return jit_insn_max((jit_function_t)m_jit_function.function, (jit_value_t)value1.value, (jit_value_t)value2.value);
}

inline jit_value   JitSubroutine::sign BOOST_PREVENT_MACRO_SUBSTITUTION (jit_value value1) 
{
    return jit_insn_sign((jit_function_t)m_jit_function.function, (jit_value_t)value1.value);
}

inline int         JitSubroutine::branch (jit_label *label) 
{
    return jit_insn_branch((jit_function_t)m_jit_function.function, (jit_label_t*)label);
}

inline int         JitSubroutine::branchIf (jit_value value, jit_label *label) 
{
    return jit_insn_branch_if((jit_function_t)m_jit_function.function, (jit_value_t)value.value, (jit_label_t*)label);
}

inline int         JitSubroutine::branchIfNot (jit_value value, jit_label *label) 
{
    return jit_insn_branch_if_not((jit_function_t)m_jit_function.function, (jit_value_t)value.value, (jit_label_t*)label);
}

inline int         JitSubroutine::jumpTable (jit_value value, jit_label *labels, unsigned int num_labels) 
{
    return jit_insn_jump_table((jit_function_t)m_jit_function.function, (jit_value_t)value.value, (jit_label_t*)labels, num_labels);
}

inline jit_value   JitSubroutine::addressOf (jit_value value1) 
{
    return jit_value(jit_insn_address_of((jit_function_t)m_jit_function.function, (jit_value_t)value1.value), value1.type->pointerType());
}

inline jit_value   JitSubroutine::referenceOf (jit_value value1) 
{
    return jit_value(jit_insn_address_of((jit_function_t)m_jit_function.function, (jit_value_t)value1.value), value1.type->referenceType());
}

inline jit_value   JitSubroutine::addressOfLabel (jit_label *label) 
{
    return jit_insn_address_of_label((jit_function_t)m_jit_function.function, (jit_label_t*)label);
}

inline jit_value JitSubroutine::cast( jit_value value, Type* dest )
{
    jit_value implicit_cast_result = implicitCast(value, dest);
    if(NOT(implicit_cast_result.isNull()))
    {
        return implicit_cast_result;
    }

    if(value.type->asDataPointerType() != nullptr AND (dest->asDataPointerType() == nullptr))
        return jit_value();

    if(dest->asDataPointerType())
    {
        o_assert(value.type->asDataPointerType());
        phantom::reflection::Type* pDestPointedType = dest->asDataPointerType()->getPointedType();
        phantom::reflection::Type* pSrcPointedType = value.type->asDataPointerType()->getPointedType();
        if((pDestPointedType->asClass() != nullptr) AND (pSrcPointedType->asClass() != nullptr))
        {
            // Down cast
            size_t offset = pDestPointedType->asClass()->getSuperClassOffsetCascade(pSrcPointedType->asClass());
            if(offset == 0xffffffff) return jit_value();
            return jit_value(addRelative(value, -(int)offset).value, dest);
        }
        else 
        {
            return jit_value();
        }
    }
    // Other cases should have be done in implicit cast
    return jit_value();
}

inline jit_value   JitSubroutine::implicitCast(jit_value value, Type* a_pDestType ) 
{
    if(a_pDestType == value.type) return value;

    // Remove const which don't acts in terms of convertion (only if addressed types are const, see below for this case)
    value.type = value.type->removeConst();
    a_pDestType = a_pDestType->removeConst();

    if(value.type->asReferenceType() AND a_pDestType->asReferenceType())
    {
        // If both reference => same treatment is they were pointers, recall with pointer types
        jit_value pointer;
        pointer.value = value.value;
        pointer.type = value.type->removeReference()->pointerType();
        jit_value casted = implicitCast(pointer, a_pDestType->removeReference()->pointerType());
        casted.type = casted.type->removePointer()->referenceType(); // restore reference type
        return casted;
    }

    // If source is reference and not destination, dereference the source and cast
    if(value.type->asReferenceType())
    {
        implicitCast(loadRelative(value, 0, value.type->removeReference()), a_pDestType);
    }

    if(!value.type->isImplicitlyConvertibleTo(a_pDestType)) 
        return jit_value();

    o_assert((value.type->asDataPointerType() == nullptr) || (a_pDestType->asDataPointerType() != nullptr), " src is ptr => dest is ptr, or something is wrong in isConvertibleTo");
    if(a_pDestType->asDataPointerType())
    {
        o_assert(value.type->asDataPointerType());

        phantom::reflection::Type* pDestPointedType = a_pDestType->asDataPointerType()->getPointedType();
        phantom::reflection::Type* pSrcPointedType = value.type->asDataPointerType()->getPointedType();

        if(pSrcPointedType->asConstType() AND NOT(pDestPointedType->asConstType()))
        {
            return jit_value();
        }

        pDestPointedType = pDestPointedType->removeConst();
        pSrcPointedType = pSrcPointedType->removeConst();

        if((pDestPointedType->asClass() == nullptr) == (pSrcPointedType->asClass() == nullptr))
        {
            if(pDestPointedType->asClass())
            {
                size_t offset = pSrcPointedType->asClass()->getSuperClassOffsetCascade(pDestPointedType->asClass());
                if(offset == 0xffffffff) return jit_value();
                if(offset == 0) return jit_value((jit_value_t)value.value, a_pDestType);
                return jit_value(jit_insn_add_relative(func, (jit_value_t)value.value, offset), a_pDestType);
            }
            else
            {
                return jit_value();
            }
        }
        else 
        {
            return jit_value();
        }
    }
    // TODO fix that shitty triple test
    else if(a_pDestType->asArithmeticType() AND value.type->asArithmeticType())
    {
        return jit_value(jit_insn_convert(func, (jit_value_t)value.value, toJitType(a_pDestType), 0), a_pDestType);
    }
    else if(a_pDestType->asIntegralType() AND value.type->asArithmeticType())
    {
        return jit_value(jit_insn_convert(func, (jit_value_t)value.value, toJitType(a_pDestType), 0), a_pDestType);
    }
    else if(a_pDestType->asArithmeticType() AND value.type->asIntegralType())
    {
        return jit_value(jit_insn_convert(func, (jit_value_t)value.value, toJitType(a_pDestType), 0), a_pDestType);
    }
    else if((a_pDestType->asReferenceType() != nullptr) AND (value.type->asReferenceType() == nullptr))
    {
        /// Convert from value to reference => address value
        if(value.isAddressable()) 
        {
            return jit_value(jit_insn_address_of(func, (jit_value_t)value.value), a_pDestType);
        }
        else if(a_pDestType->asReferenceType()->getReferencedType()->asConstType())
        {
            jit_value_t temp_value = jit_value_create(func, toJitType(a_pDestType->asReferenceType()->getReferencedType())) ;
            jit_value_set_addressable(temp_value);
            int result = jit_insn_store(func, temp_value, (jit_value_t)value.value);
            o_assert(result);
            return jit_value(jit_insn_address_of(func, temp_value), a_pDestType);
        }
    }
    else if((a_pDestType->asReferenceType() == nullptr) AND (value.type->asReferenceType() != nullptr))
    {
        /// Convert from reference to value (dereference) => get value content
        return jit_insn_load_relative(func, (jit_value_t)value.value, 0, toJitType(a_pDestType));
    }
    return jit_value();
}

inline jit_value   JitSubroutine::convert(jit_value value, phantom::reflection::Type* a_pDestType) 
{
    return jit_value(jit_insn_convert((jit_function_t)m_jit_function.function, (jit_value_t)value.value, toJitType(a_pDestType), 0), a_pDestType);
}

inline jit_value   JitSubroutine::callSubroutine (Subroutine* a_pSubroutine, jit_value *args, uint a_uiArgCount, int flags) 
{
    Subroutine* pCalledSubroutine = a_pSubroutine;
    Type* pReturnType =  pCalledSubroutine->getSignature()->getReturnType();

    jit_value_t * vargs = (jit_value_t*)o_malloc(a_uiArgCount*sizeof(jit_value_t));
    for(uint i = 0; i<a_uiArgCount; ++i)
    {
        vargs[i] = (jit_value_t)args[i].value;
    }

    JitSubroutine* pJitSubroutine = as<JitSubroutine*>(a_pSubroutine->getExtension());

    jit_value returnedValue;
    if(pJitSubroutine)
    {
        returnedValue = jit_value(jit_insn_call((jit_function_t)m_jit_function.function
            , pCalledSubroutine->getQualifiedDecoratedName().c_str()
            , (jit_function_t)pJitSubroutine->getGenericCallFunction().function
            , toJitSignature(pJitSubroutine->getAbi(), pCalledSubroutine->getSignature())
            , vargs, a_uiArgCount, flags), pReturnType);
    }
    else 
    {
        returnedValue = jit_value(jit_insn_call((jit_function_t)m_jit_function.function
            , pCalledSubroutine->getQualifiedDecoratedName().c_str()
            , (jit_function_t)a_pJitSubroutine->getJitFunction().function
            , toJitSignature(a_pJitSubroutine->getAbi(), pCalledSubroutine->getSignature())
            , vargs, a_uiArgCount, flags), pReturnType);
    }

    o_free(vargs);

    return returnedValue;
}

void JitSubroutine::callSignal( Signal* a_pSignal, jit_value *args, uint a_uiArgCount, int flags )
{    
    jit_value_t * vargs = (jit_value_t*)o_malloc(a_uiArgCount*sizeof(jit_value_t));
    for(uint i = 0; i<a_uiArgCount; ++i)
    {
        vargs[i] = (jit_value_t)args[i].value;
    }

    jit_insn_call_native((jit_function_t)m_jit_function.function
        , a_pSignal->getQualifiedDecoratedName().c_str()
        , a_pSignal->getCallClosure()
        , toJitSignature(e_JitAbi_thiscall, a_pSignal->getSignature())
        , vargs, a_uiArgCount, flags);

    o_free(vargs);
}

inline jit_value   JitSubroutine::callIndirect (jit_value value, Signature* a_pSignature, jit_value *args, unsigned int a_uiArgCount, int flags) 
{
    jit_value_t * vargs = (jit_value_t*)o_malloc(a_uiArgCount*sizeof(jit_value_t));
    for(uint i = 0; i<a_uiArgCount; ++i)
    {
        vargs[i] = (jit_value_t)args[i].value;
    }
    jit_value returnedValue = jit_value(jit_insn_call_indirect((jit_function_t)m_jit_function.function, (jit_value_t)value.value, toJitSignature(e_JitAbi_thiscall, a_pSignature), vargs, a_uiArgCount, flags), a_pSignature->getReturnType());
    o_free(vargs);

    return returnedValue;
}

inline jit_value   JitSubroutine::callIndirectVtable (jit_value value, Signature* a_pSignature, jit_value *args, unsigned int a_uiArgCount, int flags) 
{
    jit_value_t * vargs = (jit_value_t*)o_malloc(a_uiArgCount*sizeof(jit_value_t));
    for(uint i = 0; i<a_uiArgCount; ++i)
    {
        vargs[i] = (jit_value_t)args[i].value;
    }
    jit_value returnedValue = jit_value(jit_insn_call_indirect_vtable((jit_function_t)m_jit_function.function, (jit_value_t)value.value, toJitSignature(e_JitAbi_thiscall, a_pSignature), vargs, a_uiArgCount, flags), a_pSignature->getReturnType());
    o_free(vargs);

    return returnedValue;
}

inline jit_value   JitSubroutine::callNative (const char *name, void *native_func, EJitAbi abi, Signature* a_pSignature, jit_value* args, unsigned int a_uiArgCount, int exception_return, int flags) 
{
    jit_value_t * vargs = (jit_value_t*)o_malloc(a_uiArgCount*sizeof(jit_value_t));
    for(uint i = 0; i<a_uiArgCount; ++i)
    {
        vargs[i] = (jit_value_t)args[i].value;
    }
    jit_value returnedValue =  jit_value(jit_insn_call_native((jit_function_t)m_jit_function.function, name, native_func, toJitSignature(abi, a_pSignature), vargs, a_uiArgCount, flags), a_pSignature->getReturnType());
    o_free(vargs);
    return returnedValue;
}

inline jit_value   JitSubroutine::callIntrinsic (const char *name, void *intrinsic_func, const void* descriptor, jit_value arg1, jit_value arg2) 
{
    return jit_value(jit_insn_call_intrinsic((jit_function_t)m_jit_function.function, name, intrinsic_func, (const jit_intrinsic_descr_t*)descriptor, (jit_value_t)arg1.value, (jit_value_t)arg2.value));
}

inline jit_value JitSubroutine::callIntrinsic( const string& a_strInstrinsicName, jit_value v0 )
{
    return jit_phantom_math_func((jit_function_t)m_jit_function.function, convertIntrinsicName(a_strInstrinsicName).c_str(), (jit_value_t)v0.value);
}

inline jit_value JitSubroutine::callIntrinsic( const string& a_strInstrinsicName, jit_value v0, jit_value v1 )
{
    return jit_phantom_math_func((jit_function_t)m_jit_function.function, convertIntrinsicName(a_strInstrinsicName).c_str(), (jit_value_t)v0.value, (jit_value_t)v1.value);
}

inline jit_value JitSubroutine::callIntrinsic( const string& a_strInstrinsicName, jit_value v0, jit_value v1, jit_value v2 )
{
    return jit_phantom_math_func((jit_function_t)m_jit_function.function, convertIntrinsicName(a_strInstrinsicName).c_str(), (jit_value_t)v0.value, (jit_value_t)v1.value, (jit_value_t)v2.value);
}

inline jit_value JitSubroutine::callIntrinsic( const string& a_strInstrinsicName, jit_value v0, jit_value v1, jit_value v2, jit_value v3 )
{
    return jit_phantom_math_func((jit_function_t)m_jit_function.function, convertIntrinsicName(a_strInstrinsicName).c_str(), (jit_value_t)v0.value, (jit_value_t)v1.value, (jit_value_t)v2.value, (jit_value_t)v3.value);
}

inline int         JitSubroutine::incomingReg (jit_value value, int reg) 
{
    return jit_insn_incoming_reg((jit_function_t)m_jit_function.function, (jit_value_t)value.value, reg);
}

inline int         JitSubroutine::incomingFramePosn (jit_value value, int frame_offset) 
{
    return jit_insn_incoming_frame_posn((jit_function_t)m_jit_function.function, (jit_value_t)value.value, frame_offset);
}

inline int         JitSubroutine::outgoingReg (jit_value value, int reg) 
{
    return jit_insn_outgoing_reg((jit_function_t)m_jit_function.function, (jit_value_t)value.value, reg);
}

inline int         JitSubroutine::outgoingFramePosn (jit_value value, int frame_offset) 
{
    return jit_insn_outgoing_frame_posn((jit_function_t)m_jit_function.function, (jit_value_t)value.value, frame_offset);
}

inline int         JitSubroutine::returnReg (jit_value value, int reg) 
{
    return jit_insn_return_reg((jit_function_t)m_jit_function.function, (jit_value_t)value.value, reg);
}

inline int         JitSubroutine::setupForNested (int nested_level, int reg) 
{
    return jit_insn_setup_for_nested((jit_function_t)m_jit_function.function, nested_level, reg);
}

inline int         JitSubroutine::flushStruct (jit_value value) 
{
    return jit_insn_flush_struct((jit_function_t)m_jit_function.function, (jit_value_t)value.value);
}

inline jit_value   JitSubroutine::import (jit_value value) 
{
    return jit_value(jit_insn_import((jit_function_t)m_jit_function.function, (jit_value_t)value.value), value.type);
}

inline int         JitSubroutine::push (jit_value value) 
{
    return jit_insn_push((jit_function_t)m_jit_function.function, (jit_value_t)value.value);
}

inline int         JitSubroutine::pushPtr (jit_value value, Type* type) 
{
    return jit_insn_push_ptr((jit_function_t)m_jit_function.function, (jit_value_t)value.value, toJitType(type));
}

inline int         JitSubroutine::setParam (jit_value value, int offset) 
{
    return jit_insn_set_param((jit_function_t)m_jit_function.function, (jit_value_t)value.value, offset);
}

inline int         JitSubroutine::setParamPtr (jit_value value, Type* type, int offset) 
{
    return jit_insn_set_param_ptr((jit_function_t)m_jit_function.function, (jit_value_t)value.value, toJitType(type), offset);
}

inline int         JitSubroutine::pushReturnAreaPtr () 
{
    return jit_insn_push_return_area_ptr((jit_function_t)m_jit_function.function);
}

inline int         JitSubroutine::popStack (int num_items) 
{
    return jit_insn_pop_stack((jit_function_t)m_jit_function.function, num_items);
}

inline int         JitSubroutine::deferPopStack (int num_items) 
{
    return jit_insn_defer_pop_stack((jit_function_t)m_jit_function.function, num_items);
}

inline int         JitSubroutine::flushDeferPop (int num_items) 
{
    return jit_insn_flush_defer_pop((jit_function_t)m_jit_function.function, num_items);
}

inline int         JitSubroutine::returnValue (jit_value value) 
{
    return jit_insn_return((jit_function_t)m_jit_function.function, (jit_value_t)value.value);
}

inline int         JitSubroutine::returnPtr (jit_value value, Type* type) 
{
    return jit_insn_return_ptr((jit_function_t)m_jit_function.function, (jit_value_t)value.value, toJitType(type));
}

inline int         JitSubroutine::defaultReturn () 
{
    return jit_insn_default_return((jit_function_t)m_jit_function.function);
}

inline int         JitSubroutine::throwValue(jit_value value) 
{
    return jit_insn_throw((jit_function_t)m_jit_function.function, (jit_value_t)value.value);
}

inline jit_value   JitSubroutine::getCallStack () 
{
    return jit_insn_get_call_stack((jit_function_t)m_jit_function.function);
}

inline jit_value   JitSubroutine::thrownException () 
{
    return jit_insn_thrown_exception((jit_function_t)m_jit_function.function);
}

inline int         JitSubroutine::usesCatcher () 
{
    return jit_insn_uses_catcher((jit_function_t)m_jit_function.function);
}

inline jit_value   JitSubroutine::startCatcher () 
{
    return jit_insn_start_catcher((jit_function_t)m_jit_function.function);
}

inline int         JitSubroutine::branchIfPCNotInRange (jit_label start_label, jit_label end_label, jit_label *label) 
{
    return jit_insn_branch_if_pc_not_in_range((jit_function_t)m_jit_function.function, start_label.label, end_label.label, (jit_label_t*)label);
}

inline int         JitSubroutine::rethrowUnhandled () 
{
    return jit_insn_rethrow_unhandled((jit_function_t)m_jit_function.function);
}

inline int         JitSubroutine::startFinally (jit_label *finally_label) 
{
    return jit_insn_start_finally((jit_function_t)m_jit_function.function, (jit_label_t*)finally_label);
}

inline int         JitSubroutine::returnFromFinally () 
{
    return jit_insn_return_from_finally((jit_function_t)m_jit_function.function);
}

inline int         JitSubroutine::callFinally (jit_label *finally_label) 
{
    return jit_insn_call_finally((jit_function_t)m_jit_function.function, (jit_label_t*)finally_label);
}

inline jit_value   JitSubroutine::startFilter (jit_label *label, Type* type) 
{
    return jit_insn_start_filter((jit_function_t)m_jit_function.function, (jit_label_t*)label, toJitType(type));
}

inline int         JitSubroutine::returnFromFilter (jit_value value) 
{
    return jit_insn_return_from_filter((jit_function_t)m_jit_function.function, (jit_value_t)value.value);
}

inline jit_value   JitSubroutine::callFilter (jit_label *label, jit_value value, Type* type) 
{
    return jit_insn_call_filter((jit_function_t)m_jit_function.function, (jit_label_t*)label, (jit_value_t)value.value, toJitType(type));
}

inline int         JitSubroutine::memcpy BOOST_PREVENT_MACRO_SUBSTITUTION (jit_value dest, jit_value src, jit_value size) 
{
    return jit_insn_memcpy((jit_function_t)m_jit_function.function, (jit_value_t)dest.value, (jit_value_t)src.value, (jit_value_t)size.value);
}

inline int         JitSubroutine::memmove BOOST_PREVENT_MACRO_SUBSTITUTION (jit_value dest, jit_value src, jit_value size) 
{
    return jit_insn_memmove((jit_function_t)m_jit_function.function, (jit_value_t)dest.value, (jit_value_t)src.value, (jit_value_t)size.value);
}

inline int         JitSubroutine::memset BOOST_PREVENT_MACRO_SUBSTITUTION (jit_value dest, jit_value value, jit_value size) 
{
    return jit_insn_memset((jit_function_t)m_jit_function.function, (jit_value_t)dest.value, (jit_value_t)value.value, (jit_value_t)size.value);
}

inline jit_value   JitSubroutine::alloca BOOST_PREVENT_MACRO_SUBSTITUTION (jit_value size) 
{
    return jit_insn_alloca((jit_function_t)m_jit_function.function, (jit_value_t)size.value);
}

inline int         JitSubroutine::moveBlocksToEnd (jit_label from_label, jit_label to_label) 
{
    return jit_insn_move_blocks_to_end((jit_function_t)m_jit_function.function, from_label.label, to_label.label);
}

inline int         JitSubroutine::moveBlocksToStart (jit_label from_label, jit_label to_label) 
{
    return jit_insn_move_blocks_to_start((jit_function_t)m_jit_function.function, from_label.label, to_label.label);
}

inline int         JitSubroutine::markOffset (int offset) 
{
    return jit_insn_mark_offset((jit_function_t)m_jit_function.function, offset);
}
/*

void        JitSubroutine::iterInit (iter_t *iter, jit_block block) 
{
    o_assert(false);
}

void        JitSubroutine::iterInitLast (iter_t *iter, jit_block block) 
{
    o_assert(false);
}

jit_insn    JitSubroutine::iterNext (iter_t *iter) 
{
    o_assert(false);
}

jit_insn    JitSubroutine::iterPrevious (iter_t *iter) 
{
    o_assert(false);
}*/


inline jit_value JitSubroutine::getStructPointer() const
{
    return jit_value_get_struct_pointer((jit_function_t)m_jit_function.function);
}

inline void JitSubroutine::ref( jit_value value )
{
    return jit_value_ref((jit_function_t)m_jit_function.function, (jit_value_t)value.value);
}

inline jit_value JitSubroutine::createValue( Type* type )
{
    return jit_value_create((jit_function_t)m_jit_function.function, toJitType(type));
}

inline jit_value   JitSubroutine::createCharConstant (char const_value)
{
    return jit_value_create_nint_constant((jit_function_t)m_jit_function.function, toJitType(typeOf<char>()), const_value);
}

inline jit_value   JitSubroutine::createUCharConstant (uchar const_value)
{
    return jit_value_create_nint_constant((jit_function_t)m_jit_function.function, toJitType(typeOf<uchar>()), const_value);
}

inline jit_value   JitSubroutine::createShortConstant (short const_value)
{
    return jit_value_create_nint_constant((jit_function_t)m_jit_function.function, toJitType(typeOf<short>()), const_value);
}

inline jit_value   JitSubroutine::createUShortConstant (ushort const_value)
{
    return jit_value_create_nint_constant((jit_function_t)m_jit_function.function, toJitType(typeOf<ushort>()), const_value);
}

inline jit_value JitSubroutine::createIntConstant( int const_value )
{
    return jit_value_create_nint_constant((jit_function_t)m_jit_function.function, toJitType(typeOf<int>()), const_value);
}

inline jit_value JitSubroutine::createUIntConstant (uint const_value)
{
    return jit_value_create_nint_constant((jit_function_t)m_jit_function.function, toJitType(typeOf<uint>()), const_value);
}

inline jit_value JitSubroutine::createSizeTConstant (size_t const_value)
{
    return jit_value_create_nint_constant((jit_function_t)m_jit_function.function, toJitType(typeOf<size_t>()), const_value);
}

inline jit_value JitSubroutine::createVoidPtrConstant (void* const_value)
{
    return jit_value_create_nint_constant((jit_function_t)m_jit_function.function, toJitType(typeOf<void*>()), (jit_nint)const_value);
}

inline jit_value JitSubroutine::createLongLongConstant( long long const_value )
{
    return jit_value_create_long_constant((jit_function_t)m_jit_function.function, toJitType(typeOf<long long>()), const_value);
}

inline jit_value JitSubroutine::createFloatConstant( float const_value )
{
    return jit_value_create_float32_constant((jit_function_t)m_jit_function.function, toJitType(typeOf<float>()), const_value);
}

inline jit_value JitSubroutine::createDoubleConstant( double const_value )
{
    return jit_value_create_float64_constant((jit_function_t)m_jit_function.function, toJitType(typeOf<double>()), const_value);
}

inline jit_value JitSubroutine::createConstant( const jit_constant *const_value )
{
    return jit_value_create_constant((jit_function_t)m_jit_function.function, (const jit_constant_t*)const_value);
}

inline jit_value JitSubroutine::getParameter( uint param ) const
{
    uint jitParamIndex = (getAbi() == e_JitAbi_thiscall) ? param+1 : param;
    return jit_value(jit_value_get_param((jit_function_t)m_jit_function.function, jitParamIndex), m_pSubroutine->getParameterType(param));
}

inline jit_value JitSubroutine::getThis() const
{
    o_assert(m_pSubroutine->getOwner());
    return (getAbi() == e_JitAbi_thiscall) 
        ? jit_value(jit_value_get_param((jit_function_t)m_jit_function.function, 0), m_pSubroutine->getOwner()->asClass()->pointerType())
        : jit_value();
}

inline void JitSubroutine::pushCodeLocation( const CodeLocation& codeLocation )
{
    sm_CodeLocationStack.push_back(codeLocation);
    jit_function_set_current_code_location((jit_function_t)m_jit_function.function, codeLocation.getStart().line, codeLocation.getStart().column, codeLocation.getEnd().line, codeLocation.getEnd().column);
}

inline void JitSubroutine::popCodeLocation()
{
    sm_CodeLocationStack.pop_back();
    CodeLocation codeLocation;
    if(sm_CodeLocationStack.size())
    {
        codeLocation = sm_CodeLocationStack.back();
    }
    jit_function_set_current_code_location((jit_function_t)m_jit_function.function, codeLocation.getStart().line, codeLocation.getStart().column, codeLocation.getEnd().line, codeLocation.getEnd().column);
}

inline int JitSubroutine::label( jit_label *l )
{
    return jit_insn_label((jit_function_t)m_jit_function.function, (jit_label_t*)l);
}

inline int JitSubroutine::new_block()
{
    return jit_insn_new_block((jit_function_t)m_jit_function.function);
}

inline bool JitSubroutine::isCompiled() const
{
    return jit_function_is_compiled((jit_function_t)m_jit_function.function) != 0;
}

inline string JitSubroutine::convertIntrinsicName( const string& a_strInstrinsicName )
{
    if(a_strInstrinsicName.size() == 1)
    {
        switch(a_strInstrinsicName[0])
        {
        case '+':
            return "add";
        case '-':
            return "sub";
        case '/':
            return "div";
        case '*':
            return "mul";
        }
    }
    return a_strInstrinsicName;
}

void JitSubroutine::setClosures()
{
    m_pSubroutine->setClosure(jit_function_to_closure((jit_function_t)m_jit_function.function));
}

o_namespace_end(phantom, reflection, jit)
