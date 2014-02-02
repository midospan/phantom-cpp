/* ******************* Includes ****************** */
#include "phantom/jit.h"
#include "JitLocalVariable.h"
#include "JitLocalVariable.hxx"
#include "JitInstanceMemberFunction.h"
#include "JitStaticMemberFunction.h"
#include "phantom/def_jit_internal.h"
/* *********************************************** */
o_registerN((phantom, reflection, jit), JitLocalVariable);

o_namespace_begin(phantom, reflection, jit) 

JitLocalVariable::JitLocalVariable( Block* a_pBlock, Type* a_pType, const string& a_strName, const CodeLocation& a_Location, jit_value value, bitfield a_bfModifiers /*= 0*/)
    : LocalVariable( a_pBlock, a_pType, a_strName, a_Location, a_bfModifiers )
{
    o_assert(value.type == a_pType);
    m_Value = value;
    m_Value.setLocal();
    m_Value.type = a_pType;
}

JitLocalVariable::JitLocalVariable( Block* a_pBlock, Type* a_pType, const string& a_strName, const CodeLocation& a_Location, bitfield a_bfModifiers /*= 0*/ ) 
    : LocalVariable( a_pBlock, a_pType, a_strName, a_Location, a_bfModifiers )
{
    m_Value = getJitSubroutine()->createValue(a_pType);
    m_Value.setLocal(); // ensure value is addressable to debug it
}

JitSubroutine* JitLocalVariable::getJitSubroutine() const
{
    return as<JitSubroutine*>(getBlock()->getSubroutine());
}

int JitLocalVariable::store(jit_value value) const
{
    o_assert(toJitType(value.type) == toJitType(m_Value.type));
    return getJitSubroutine()->store(m_Value.value, value.value);
}

jit_value JitLocalVariable::address() const
{
    return getJitSubroutine()->addressOf(m_Value);
}

void JitLocalVariable::setupFrame()
{
    setFrameOffset(m_Value.getFrameOffset());
}

jit_value JitLocalVariable::load() const
{
    return m_Value;
}


o_namespace_end(phantom, reflection, jit)