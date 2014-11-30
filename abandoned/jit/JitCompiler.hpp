#ifndef o_reflection_jit_JitSubroutine_h__
#define o_reflection_jit_JitSubroutine_h__

/* ******************* Includes ****************** */
#include "def_jit_internal.h"
/* *********************************************** */
o_namespace_begin(phantom, reflection, jit)

struct JitAddressable : public CompilerData
{
    JitAddressable(LanguageElement* a_pElement) : CompilerData(a_pElement) {}
    virtual int store(jit_value value) const = 0;
    virtual jit_value load() const = 0;
    virtual JitSubroutine* getJitSubroutine() const = 0;
    virtual reflection::Type* getValueType() const = 0;
    virtual jit_value address() const = 0;
    jit_value loadAs(reflection::Type* a_pType) const;
};

struct JitLocalVariable : public JitAddressable
{
    JitLocalVariable(JitSubroutine* a_pJitSubroutine, LocalVariable* a_pLocalVariable, jit_value a_Value);
    jit_value           getJitValue() const { return m_Value.value; }

    virtual int store(jit_value value) const
    {
        o_assert(toJitType(value.type) == toJitType(m_Value.type));
        return m_pJitSubroutine->store(m_Value.value, value.value);
    }
    virtual jit_value load() const;
    virtual jit_value address() const { return m_pJitSubroutine->addressOf(m_Value); }

    LocalVariable* getLocalVariable() const {return static_cast<LocalVariable*>(m_pElement); }

    void setupFrame() { getLocalVariable()->setFrameOffset(m_Value.getFrameOffset()); }

    JitSubroutine* m_pJitSubroutine;
    jit_value m_Value;
};

struct JitCaseLabel : public CompilerData
{
    JitCaseLabel(jit_label* a_p_jit_label, LabelStatement* a_pStatement)
        : CompilerData(a_pStatement) {}
    jit_label  m_jit_Label;
};

o_namespace_end(phantom, reflection, jit)

#endif // JitSubroutine_h__
