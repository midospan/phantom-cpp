/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include "JitLocalVariable.h"
#include "JitInstanceMethod.h"
#include "JitStaticMethod.h"
/* *********************************************** */
o_registerN((phantom, reflection, runtime), JitLocalVariable);

o_namespace_begin(phantom, reflection, runtime) 

JitLocalVariable::JitLocalVariable( Block* a_pBlock, Type* a_pType, const string& a_strName, const CodeLocation& a_Location, jit_value_t value, bitfield a_bfModifiers /*= 0*/)
    : LocalVariable( a_pBlock, a_pType, a_strName, a_Location, a_bfModifiers )
{
    m_Value.value = value;
    jit_value_set_local(value);
    m_Value.type = a_pType;
}

JitLocalVariable::JitLocalVariable( Block* a_pBlock, Type* a_pType, const string& a_strName, const CodeLocation& a_Location, bitfield a_bfModifiers /*= 0*/ ) 
    : LocalVariable( a_pBlock, a_pType, a_strName, a_Location, a_bfModifiers )
{
    m_Value.value = jit_value_create(getJitFunction(), jit_type_from_phantom_type(a_pType));
    jit_value_set_local(m_Value.value); // ensure value is addressable to debug it
    m_Value.type = a_pType;
}

jit_function_t JitLocalVariable::getJitFunction() const
{
    Subroutine* pSubroutine = getBlock()->getSubroutine();
    JitInstanceMethod* pInstanceMethod = static_cast<JitInstanceMethod*>(pSubroutine->asInstanceMethod());
    if(pInstanceMethod) return pInstanceMethod->getJitFunction();
    return static_cast<JitStaticMethod*>(pSubroutine->asStaticMethod())->getJitFunction();
}

int JitLocalVariable::store(jit_phantom_value_t value) const
{
    o_assert(value.type == m_Value.type);
    return jit_insn_store(getJitFunction(), m_Value.value, value.value);
}

jit_phantom_value_t JitLocalVariable::address() const
{
    return jit_phantom_value_t(
        jit_insn_address_of(getJitFunction(), m_Value.value)
        , pointerTypeOf(m_Value.type));
}

void JitLocalVariable::setupFrame()
{
    setFrameOffset(jit_value_get_frame_offset(m_Value.value));
}



o_namespace_end(phantom, reflection, runtime)