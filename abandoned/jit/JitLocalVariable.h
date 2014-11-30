

#ifndef o_moon_script_JitLocalVariable_h__
#define o_moon_script_JitLocalVariable_h__
// #pragma __PragmaPrintFile__


/* ****************** Includes ******************* */
#include <phantom/jit.h>
#include <phantom/reflection/jit/JitAddressable.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, reflection, jit), JitLocalVariable);
/* *********************************************** */

o_namespace_begin(phantom, reflection, jit)

class o_jit_export JitLocalVariable : public LocalVariable, public JitAddressable
{

public:
    JitLocalVariable(Block* a_pBlock, Type* a_pType, const string& a_strName, const CodeLocation& a_Location, bitfield modifiers = 0);
    JitLocalVariable(Block* a_pBlock, Type* a_pType, const string& a_strName, const CodeLocation& a_Location, jit_value value, bitfield modifiers = 0);
    ~JitLocalVariable(void) 	{}

    JitSubroutine*      getJitSubroutine() const;
    jit_value           getJitValue() const { return m_Value.value; }

    jit_value getValue() const 
    {
        return m_Value;
    }

    virtual reflection::Type*   getValueType() const { return LocalVariable::getValueType(); }

    virtual int store(jit_value value) const;
    virtual jit_value load() const;
    virtual jit_value address() const;

    void setupFrame();

protected:
    jit_value m_Value;
};

o_namespace_end(phantom, reflection, jit)

#endif