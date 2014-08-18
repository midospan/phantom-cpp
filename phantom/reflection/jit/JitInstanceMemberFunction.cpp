/* ******************* Includes ****************** */
#include "phantom/jit.h"
#include "JitInstanceMemberFunction.h"
#include "JitInstanceMemberFunction.hxx"
#include "phantom/def_jit_internal.h"
#include "JitClass.h"
#include "JitLocalVariable.h"
/* *********************************************** */
o_registerN((phantom, reflection, jit), JitInstanceMemberFunction);

o_namespace_begin(phantom, reflection, jit)

JitInstanceMemberFunction::JitInstanceMemberFunction( InstanceMemberFunction* a_pInstanceMemberFunction ) 
    : JitSubroutine(a_pInstanceMemberFunction, e_JitAbi_thiscall) 
    , m_jit_virtual_indirection_function(nullptr)
{
    if(a_pInstanceMemberFunction->isVirtual())
    {
        compileVTableIndirectionFunction(); 
    }
}

JitInstanceMemberFunction::~JitInstanceMemberFunction( void )
{
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

void JitInstanceMemberFunction::compileVTableIndirectionFunction()
{
    m_jit_virtual_indirection_function = jit_function_create((jit_context_t)m_jit_context.context, toJitSignature(m_eAbi, getSignature()));
    o_assert(m_jit_virtual_indirection_function.function);
    jit_context_build_start((jit_context_t)m_jit_context.context);
    size_t argCount = getSignature()->getParameterCount()+1; // parameters+this
    jit_value_t* args = o_allocate_n(argCount, jit_value_t); 

    // The indirection has the same signature as the indirected one
    jit_value_t this_pointer = jit_value_get_param((jit_function_t)m_jit_virtual_indirection_function.function, 0);
    jit_value_t vtable_index = jit_value_create_nint_constant((jit_function_t)m_jit_virtual_indirection_function.function, jit_type_nuint, getInstanceMemberFunction()->getVirtualTableIndex());
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

void JitInstanceMemberFunction::compileThisAdjustementThunk( size_t a_uiThisOffset ) const
{
    o_assert(m_ThisAdjustmentThunks.find(a_uiThisOffset) == m_ThisAdjustmentThunks.end());

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
    string name = "[thunk]:"+m_pSubroutine->getQualifiedDecoratedName()+":adjustor{"+boost::lexical_cast<string>(a_uiThisOffset)+"}";
    jit_insn_call(func
                , name.c_str()
                , (jit_function_t)m_jit_function.function
                , jit_function_get_signature((jit_function_t)m_jit_function.function)
                , args
                , argCount
                , 0);

    int result = jit_function_compile(func);
    o_assert(result != 0);

    o_deallocate_n(args, argCount, jit_value_t);

    m_ThisAdjustmentThunks[a_uiThisOffset] = func;
}

InstanceMemberFunction* JitInstanceMemberFunction::getInstanceMemberFunction() const
{
    return static_cast<InstanceMemberFunction*>(m_pSubroutine);
}

void JitInstanceMemberFunction::setClosures()
{
    if(isVirtual())
    {
        m_pSubroutine->setClosure(jit_function_to_closure((jit_function_t)m_jit_virtual_indirection_function.function));
        Class* pClass = getInstanceMemberFunction()->getOwnerClass();
        for(auto it = pClass->beginVirtualMemberFunctionTables(); it != pClass->endVirtualMemberFunctionTables(); ++it)
        {
            size_t uiOffset = (*it)->getOffset();
            auto it = m_ThisAdjustmentThunks.find(uiOffset);
            if(it == m_ThisAdjustmentThunks.end())
            {
                // No thunk needed, use directly the function as the vtable pointer
                getInstanceMemberFunction()->setVTableClosure(uiOffset, jit_function_to_vtable_pointer((jit_function_t)m_jit_function.function));
            }
            else 
            {
                // Thunk needed
                getInstanceMemberFunction()->setVTableClosure(uiOffset, jit_function_to_vtable_pointer((jit_function_t)it->second.function));
            }
        }
    }
    else
    {
        m_pSubroutine->setClosure(jit_function_to_closure((jit_function_t)m_jit_function.function));
    }
}

jit_function JitInstanceMemberFunction::getJitCallFunction() const
{
    return m_pSubroutine->isVirtual() ? m_jit_virtual_indirection_function : m_jit_function;
}

o_namespace_end(phantom, reflection, jit)
