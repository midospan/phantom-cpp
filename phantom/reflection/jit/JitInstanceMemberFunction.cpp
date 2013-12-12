/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include "phantom/def_jit_internal.h"
#include "JitInstanceMemberFunction.h"
#include "JitClass.h"
#include "JitLocalVariable.h"
/* *********************************************** */
o_registerN((phantom, reflection, jit), JitInstanceMemberFunction);

o_namespace_begin(phantom, reflection, jit)

JitInstanceMemberFunction::JitInstanceMemberFunction( const string& a_strName, Signature* a_pSignature, bitfield a_Modifiers ) 
    : InstanceMemberFunction(a_strName, a_pSignature, a_Modifiers) 
    , m_jit_virtual_indirection_function(nullptr)
    , m_jit_placeholder_function(nullptr)
{
}

JitInstanceMemberFunction::~JitInstanceMemberFunction( void )
{
}

jit_function JitInstanceMemberFunction::getVTableJitFunction( size_t a_uiThisOffset ) const
{
    o_assert(m_jit_function.function, "Closure not yet created, you must add this JitInstanceMemberFunction to a JitClass"); 
    if(a_uiThisOffset == 0) return m_jit_function;
    auto found = m_VTableOffsetFixFunctions.find(a_uiThisOffset);
    if(found != m_VTableOffsetFixFunctions.end())
    {
        return found->second;
    }
    jit_function func = compileThisOffsetShiftFunction(a_uiThisOffset);
    // UNCOMMENT TO TEST APPLY
    /*void* nul = 0;
    void* null[] = { &nul };
    jit_function_apply(func, null, nullptr);*/
    m_VTableOffsetFixFunctions[a_uiThisOffset] = func;
    return func;
}

phantom::generic_member_func_ptr JitInstanceMemberFunction::getGenericMemberFunctionPointer() const
{
    generic_member_func_ptr ptr;
    if(isVirtual())
    {
        ptr.setClosurePointer(jit_function_to_closure((jit_function_t)m_jit_virtual_indirection_function.function));
    }
    else
    {
        ptr.setClosurePointer(jit_function_to_closure((jit_function_t)m_jit_function.function));
    }
    return ptr;
}

void JitInstanceMemberFunction::setVirtual()
{
    if(isVirtual()) return;
    m_Modifiers.setMask(o_virtual);
    o_assert(m_jit_virtual_indirection_function.function == nullptr);
    m_jit_virtual_indirection_function = jit_function_create((jit_context_t)m_jit_context.context, toJitSignature(e_JitAbi_thiscall, getSignature()));
    o_assert(m_jit_virtual_indirection_function.function);
    m_jit_placeholder_function = m_jit_virtual_indirection_function;
}

jit_function JitInstanceMemberFunction::createJitFunction( jit_context context )
{
    jit_function func = jit_function_create((jit_context_t)context.context, toJitSignature(e_JitAbi_thiscall, getSignature()));
    if(isVirtual())
    {
        m_jit_virtual_indirection_function = jit_function_create((jit_context_t)context.context, toJitSignature(e_JitAbi_thiscall, getSignature()));
        o_assert(m_jit_virtual_indirection_function.function);
        m_jit_placeholder_function = m_jit_virtual_indirection_function;
    }
    else
    {
        m_jit_placeholder_function = func;
    }
    return func;
}

void JitInstanceMemberFunction::compileVTableIndirectionFunction()
{
    o_assert(m_jit_virtual_indirection_function.function);
    jit_context_build_start((jit_context_t)m_jit_context.context);
    size_t argCount = getSignature()->getParameterCount()+1; // parameters+this
    jit_value_t* args = o_allocate_n(argCount, jit_value_t); 

    // The indirection has the same signature as the indirected one
    jit_value_t this_pointer = jit_value_get_param((jit_function_t)m_jit_virtual_indirection_function.function, 0);
    jit_value_t vtable_index = jit_value_create_nint_constant((jit_function_t)m_jit_virtual_indirection_function.function, jit_type_nuint, getVirtualTableIndex());
    jit_value_t vtable_array = jit_insn_load_relative ((jit_function_t)m_jit_virtual_indirection_function.function, this_pointer, 0, jit_type_void_ptr);
    jit_value_t vtable_pointer = jit_insn_load_elem((jit_function_t)m_jit_virtual_indirection_function.function, vtable_array, vtable_index, jit_type_void_ptr);

    size_t i = 0;
    for(;i<argCount;++i)
    {
        args[i] = jit_value_get_param((jit_function_t)m_jit_virtual_indirection_function.function, i);
    }

    jit_insn_call_indirect_vtable ((jit_function_t)m_jit_virtual_indirection_function.function, vtable_pointer, jit_function_get_signature((jit_function_t)m_jit_function.function), args, argCount, 0);

    int result = jit_function_compile((jit_function_t)m_jit_virtual_indirection_function.function);
    o_assert(result != 0);
    
    jit_context_build_end((jit_context_t)m_jit_context.context);

    o_deallocate_n(args, argCount, jit_value_t);
}

jit_function JitInstanceMemberFunction::compileThisOffsetShiftFunction( size_t a_uiThisOffset ) const
{
    size_t argCount = getSignature()->getParameterCount()+1; // parameters+this
    jit_value_t* args = o_allocate_n(argCount, jit_value_t); 

    // The fixing function has the same signature as the indirected one
    jit_function_t func = jit_function_create((jit_context_t)m_jit_context.context, jit_function_get_signature((jit_function_t)m_jit_function.function));

    jit_value_t new_this = jit_insn_add(func, jit_value_get_param(func, 0), jit_value_create_nint_constant(func, jit_type_nint, -((int)a_uiThisOffset)));

    args[0] = new_this;

    size_t i = 1;
    for(;i<argCount;++i)
    {
        args[i] = jit_value_get_param(func, i);
    }

    jit_insn_call(func, "vtable-indirection", (jit_function_t)m_jit_function.function, jit_function_get_signature((jit_function_t)m_jit_function.function), args, argCount, 0);

    int result = jit_function_compile(func);
    o_assert(result != 0);

    o_deallocate_n(args, argCount, jit_value_t);

    return func;
}

void* JitInstanceMemberFunction::getClosurePointer() const
{
    if(isVirtual())
    {
        return jit_function_to_closure((jit_function_t)m_jit_virtual_indirection_function.function);
    }
    else
    {
        return jit_function_to_closure((jit_function_t)m_jit_function.function);
    }
}

jit_function JitInstanceMemberFunction::getJitGenericCallFunction() const
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

void JitInstanceMemberFunction::call( void* a_pThis, void** a_ppArgs ) const
{
    size_t paramCount = getSignature()->getParameterCount();
    void** shiftedArgs = o_allocate_n(paramCount + 1, void*);
    if(a_ppArgs)
    {
        ::memcpy(shiftedArgs+1, a_ppArgs, paramCount*sizeof(void*));
    }
    shiftedArgs[0] = &a_pThis;
    jit_function_apply((jit_function_t)m_jit_placeholder_function.function, shiftedArgs, nullptr);
    o_deallocate_n(shiftedArgs, paramCount + 1, void*);
}

void JitInstanceMemberFunction::call( void* a_pThis, void** a_ppArgs, void* a_pReturnArea ) const
{
    size_t paramCount = getSignature()->getParameterCount();
    void** shiftedArgs = o_allocate_n(paramCount + 1, void*);
    if(a_ppArgs)
    {
        ::memcpy(shiftedArgs+1, a_ppArgs, paramCount*sizeof(void*));
    }
    shiftedArgs[0] = &a_pThis;
    jit_function_apply((jit_function_t)m_jit_placeholder_function.function, shiftedArgs, a_pReturnArea);
    o_deallocate_n(shiftedArgs, paramCount + 1, void*);
}

void JitInstanceMemberFunction::call( void** args, void* a_pReturnArea ) const
{
    jit_function_apply((jit_function_t)m_jit_placeholder_function.function, args, a_pReturnArea);
}

void JitInstanceMemberFunction::call( void** args ) const
{
    jit_function_apply((jit_function_t)m_jit_placeholder_function.function, args, nullptr);
}

void* JitInstanceMemberFunction::getVTablePointer( size_t a_uiThisOffset ) const
{
    return jit_function_to_vtable_pointer((jit_function_t)getVTableJitFunction(a_uiThisOffset).function);
}

o_namespace_end(phantom, reflection, jit)
