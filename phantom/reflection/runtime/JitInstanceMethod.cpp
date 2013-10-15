/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include "JitInstanceMethod.h"
#include "JitClass.h"
#include "JitLocalVariable.h"
/* *********************************************** */
o_registerN((phantom, reflection, runtime), JitInstanceMethod);

o_namespace_begin(phantom, reflection, runtime)

JitInstanceMethod::JitInstanceMethod( const string& a_strName, Signature* a_pSignature, bitfield a_Modifiers ) 
    : InstanceMethod(a_strName, a_pSignature, a_Modifiers) 
    , m_jit_function(nullptr)
    , m_jit_virtual_indirection_function(nullptr)
    , m_jit_placeholder_function(nullptr)
    , m_jit_context(nullptr)
{
    reset();
}

JitInstanceMethod::~JitInstanceMethod( void )
{
    jit_context_destroy(m_jit_context);
}

void JitInstanceMethod::CompileDebugMethod( JitInstanceMethod* pMethod, const char* to_print )
{
    pMethod->startCompilation();
    static std::set<string> s_print_text;
    s_print_text.insert(to_print);
    auto it = s_print_text.find(to_print);
    std::set<string>::const_reference text = *it;


    size_t argCount = pMethod->getSignature()->getParameterCount()+1; // parameters+this
    jit_value_t* args = o_allocate_n(argCount, jit_value_t); 

    jit_function_t func = pMethod->getJitFunction();

    // call printf

    jit_type_t printf_param0 = jit_type_void_ptr;
    jit_type_t printf_signature = jit_type_create_signature(jit_abi_vararg, jit_type_void, &printf_param0, 1, 0);
    jit_value_t text_ptr_value = jit_value_create_nint_constant(func, jit_type_void_ptr, (jit_nint)text.c_str());
    jit_insn_call_native(func, "printf", (void*)printf, printf_signature, &text_ptr_value, 1, 0);

    pMethod->endCompilation();

    o_deallocate_n(args, argCount, jit_value_t);
}

jit_context_t JitInstanceMethod::getContext() const
{
    return m_jit_context;
}

void JitInstanceMethod::reset()
{
    if(m_jit_context)
    {
        jit_context_destroy(m_jit_context);
    }
    m_jit_context = jit_context_create();
    m_jit_function = jit_function_create(m_jit_context, jit_type_from_phantom_signature(jit_abi_thiscall, getSignature()));
    jit_function_set_optimization_level(m_jit_function, 0);
    o_assert(m_jit_function);
    if(isVirtual())
    {
        m_jit_virtual_indirection_function = jit_function_create(m_jit_context, jit_type_from_phantom_signature(jit_abi_thiscall, getSignature()));
        o_assert(m_jit_virtual_indirection_function);
        m_jit_placeholder_function = m_jit_virtual_indirection_function;
    }
    else
    {
        m_jit_placeholder_function = m_jit_function;
    }
}

jit_function_t JitInstanceMethod::getVTableJitFunction( size_t a_uiThisOffset ) const
{
    o_assert(m_jit_function, "Closure not yet created, you must add this JitInstanceMethod to a JitClass"); 
    if(a_uiThisOffset == 0) return m_jit_function;
    auto found = m_VTableOffsetFixFunctions.find(a_uiThisOffset);
    if(found != m_VTableOffsetFixFunctions.end())
    {
        return found->second;
    }
    jit_function_t func = compile_this_offset_fix_function(a_uiThisOffset);
    // UNCOMMENT TO TEST APPLY
    /*void* nul = 0;
    void* null[] = { &nul };
    jit_function_apply(func, null, nullptr);*/
    m_VTableOffsetFixFunctions[a_uiThisOffset] = func;
    return func;
}

phantom::generic_member_func_ptr JitInstanceMethod::getGenericMemberFunctionPointer() const
{
    generic_member_func_ptr ptr;
    if(isVirtual())
    {
        ptr.setClosurePointer(jit_function_to_closure(m_jit_virtual_indirection_function));
    }
    else
    {
        ptr.setClosurePointer(jit_function_to_closure(m_jit_function));
    }
    return ptr;
}

void JitInstanceMethod::setVirtual()
{
    if(isVirtual()) return;
    m_bfModifiers.setMask(o_virtual);
    o_assert(m_jit_virtual_indirection_function == nullptr);
    m_jit_virtual_indirection_function = jit_function_create(m_jit_context, jit_type_from_phantom_signature(jit_abi_thiscall, getSignature()));
    o_assert(m_jit_virtual_indirection_function);
    m_jit_placeholder_function = m_jit_virtual_indirection_function;
}

void JitInstanceMethod::compile_vtable_indirection_function()
{
    o_assert(m_jit_virtual_indirection_function);
    jit_context_build_start(m_jit_context);
    size_t argCount = getSignature()->getParameterCount()+1; // parameters+this
    jit_value_t* args = o_allocate_n(argCount, jit_value_t); 

    // The indirection has the same signature as the indirected one
    jit_value_t this_pointer = jit_value_get_param(m_jit_virtual_indirection_function, 0);
    jit_value_t vtable_index = jit_value_create_nint_constant(m_jit_virtual_indirection_function, jit_type_nuint, getVirtualTableIndex());
    jit_value_t vtable_array = jit_insn_load_relative (m_jit_virtual_indirection_function, this_pointer, 0, jit_type_void_ptr);
    jit_value_t vtable_pointer = jit_insn_load_elem(m_jit_virtual_indirection_function, vtable_array, vtable_index, jit_type_void_ptr);

    size_t i = 0;
    for(;i<argCount;++i)
    {
        args[i] = jit_value_get_param(m_jit_virtual_indirection_function, i);
    }

    jit_insn_call_indirect_vtable (m_jit_virtual_indirection_function, vtable_pointer, jit_function_get_signature(m_jit_function), args, argCount, 0);

    int result = jit_function_compile(m_jit_virtual_indirection_function);
    o_assert(result != 0);
    
    jit_context_build_end(m_jit_context);

    o_deallocate_n(args, argCount, jit_value_t);
}

jit_function_t JitInstanceMethod::compile_this_offset_fix_function( size_t a_uiThisOffset ) const
{
    size_t argCount = getSignature()->getParameterCount()+1; // parameters+this
    jit_value_t* args = o_allocate_n(argCount, jit_value_t); 

    // The fixing function has the same signature as the indirected one
    jit_function_t func = jit_function_create(getContext(), jit_function_get_signature(m_jit_function));

    jit_value_t new_this = jit_insn_add(func, jit_value_get_param(func, 0), jit_value_create_nint_constant(func, jit_type_nint, -((int)a_uiThisOffset)));

    args[0] = new_this;

    size_t i = 1;
    for(;i<argCount;++i)
    {
        args[i] = jit_value_get_param(func, i);
    }

    jit_insn_call(func, "vtable-indirection", m_jit_function, jit_function_get_signature(m_jit_function), args, argCount, 0);

    int result = jit_function_compile(func);
    o_assert(result != 0);

    o_deallocate_n(args, argCount, jit_value_t);

    return func;
}

void* JitInstanceMethod::getClosurePointer() const
{
    if(isVirtual())
    {
        return jit_function_to_closure(m_jit_virtual_indirection_function);
    }
    else
    {
        return jit_function_to_closure(m_jit_function);
    }
}

jit_function_t JitInstanceMethod::getJitGenericCallFunction() const
{
    if(isVirtual())
    {
        return m_jit_virtual_indirection_function;
    }
    else
    {
        return m_jit_function;
    }
}

void JitInstanceMethod::invoke( void* a_pThis, void** a_ppArgs ) const
{
    size_t paramCount = getSignature()->getParameterCount();
    void** shiftedArgs = o_allocate_n(paramCount + 1, void*);
    if(a_ppArgs)
    {
        memcpy(shiftedArgs+1, a_ppArgs, paramCount*sizeof(void*));
    }
    shiftedArgs[0] = &a_pThis;
    jit_function_apply(m_jit_placeholder_function, shiftedArgs, nullptr);
    o_deallocate_n(shiftedArgs, paramCount + 1, void*);
}

void JitInstanceMethod::invoke( void* a_pThis, void** a_ppArgs, void* a_pReturnArea ) const
{
    size_t paramCount = getSignature()->getParameterCount();
    void** shiftedArgs = o_allocate_n(paramCount + 1, void*);
    if(a_ppArgs)
    {
        memcpy(shiftedArgs+1, a_ppArgs, paramCount*sizeof(void*));
    }
    shiftedArgs[0] = &a_pThis;
    jit_function_apply(m_jit_placeholder_function, shiftedArgs, a_pReturnArea);
    o_deallocate_n(shiftedArgs, paramCount + 1, void*);
}

void JitInstanceMethod::call( void** args, void* a_pReturnArea ) const
{
    jit_function_apply(m_jit_placeholder_function, args, a_pReturnArea);
}

void JitInstanceMethod::call( void** args ) const
{
    jit_function_apply(m_jit_placeholder_function, args, nullptr);
}

void JitInstanceMethod::instructionCompilationCallback( jit_insn_t insn, byte* start, byte* end )
{   
    if(start == end) return; // empty instruction => skip
    jit_function_t func = 0;
    jit_value_t value1 = jit_insn_get_value1(insn);
    jit_value_t value2 = jit_insn_get_value2(insn);
    if(value1)
        func = jit_value_get_function(value1);
    if(value2)
        func = jit_value_get_function(value2);

    if(func == nullptr)
    {
        for(auto it = sm_Compiled.begin(); it != sm_Compiled.end(); ++it)
        {
             JitInstanceMethod* pCompiled = it->second;
             if(pCompiled->getMemoryEnd() == start)
             {
                 func = it->first;
                 break;
             }
        }
    }
    if(func)
    {
        JitInstanceMethod* pCompiledInstanceMethod = sm_Compiled[func];
        o_assert(pCompiledInstanceMethod);
        if(pCompiledInstanceMethod->getMemoryStart() == 0) 
            pCompiledInstanceMethod->setMemoryStart(start);
        pCompiledInstanceMethod->setMemoryEnd(end);
        unsigned short start_line;
        unsigned short start_column;
        unsigned short end_line;
        unsigned short end_column;
        jit_insn_get_code_location(insn, &start_line, &start_column, &end_line, &end_column);
        SourceFile* pSourceFile = pCompiledInstanceMethod->getCodeLocation().getSourceFile();
        CodeLocation codeLocation(CodePosition(pSourceFile, start_line, start_column)
            , CodePosition(pSourceFile, end_line, end_column));
        pCompiledInstanceMethod->addInstruction(new Instruction(jit_insn_get_opcode(insn), codeLocation, MemoryLocation(start, end)));
    }
    else 
    {
        o_warning(false, "func not found");
    }
}

void JitInstanceMethod::compilationSuccessCallback(jit_function_t func)
{
    JitInstanceMethod* pCompiledInstanceMethod = sm_Compiled[func];
    o_assert(pCompiledInstanceMethod);
    vector<LocalVariable*> localVariables;
    pCompiledInstanceMethod->getBlock()->getLocalVariablesCascade(localVariables);
    size_t count = pCompiledInstanceMethod->getInstructionCount();
    vector<Instruction*> undefinedInstructions;
    CodeLocation replacementCodeLocation;
    for(size_t i = 0; i<count; ++i)
    {
        Instruction* pInstruction = pCompiledInstanceMethod->getInstruction(i);
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

void JitInstanceMethod::startCompilation()
{
    o_assert(!jit_function_is_compiled(m_jit_function));
    o_assert(sm_Compiled[m_jit_function] == nullptr);
    sm_Compiled[m_jit_function] = this;
    jit_function_set_insn_compilation_callback(m_jit_function, &JitInstanceMethod::instructionCompilationCallback);
    jit_function_set_compilation_success_callback(m_jit_function, &JitInstanceMethod::compilationSuccessCallback);
    jit_context_build_start(m_jit_context);
}

void JitInstanceMethod::endCompilation()
{
    jit_function_set_insn_compilation_callback(m_jit_function, nullptr);
    jit_context_build_end(m_jit_context);
    sm_Compiled.erase(m_jit_function);
}

void JitInstanceMethod::abortCompilation()
{
    jit_function_set_insn_compilation_callback(m_jit_function, nullptr);
    jit_context_build_end(m_jit_context);
    jit_function_abandon(m_jit_function);
    sm_Compiled.erase(m_jit_function);
    reset();
}

map<jit_function_t, JitInstanceMethod*> JitInstanceMethod::sm_Compiled;

o_namespace_end(phantom, reflection, runtime)
