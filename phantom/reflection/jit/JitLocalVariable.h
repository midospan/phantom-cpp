

#ifndef o_moon_script_JitLocalVariable_h__
#define o_moon_script_JitLocalVariable_h__
// #pragma __PragmaPrintFile__


/* ****************** Includes ******************* */
#include <phantom/def_jit.h>
#include <phantom/reflection/jit/JitAddressable.h>
/* **************** Declarations ***************** */
/* *********************************************** */

o_namespace_begin(phantom, reflection, jit)

class o_jit_export JitLocalVariable : public LocalVariable, public JitAddressable
{
	
public:
    JitLocalVariable(Block* a_pBlock, Type* a_pType, const string& a_strName, const CodeLocation& a_Location, bitfield modifiers = 0);
    JitLocalVariable(Block* a_pBlock, Type* a_pType, const string& a_strName, const CodeLocation& a_Location, jit_value_t value, bitfield modifiers = 0);
	~JitLocalVariable(void) 	{}

    jit_function_t      getJitFunction() const;
    jit_value_t         getJitValue() const { return m_Value.value; }

    jit_phantom_value_t getValue() const 
    {
        return m_Value;
    }

    virtual reflection::Type*   getValueType() const { return LocalVariable::getValueType(); }

    virtual int store(jit_phantom_value_t value) const;
    virtual jit_phantom_value_t load() const
    {
        return m_Value;
    }
    virtual jit_phantom_value_t address() const;

    void setupFrame();

protected:
    jit_phantom_value_t m_Value;
};

o_namespace_end(phantom, reflection, jit)

o_classNS((phantom, reflection, jit), JitLocalVariable, (LocalVariable, JitAddressable))
{
    o_reflection
    {

    };
};
o_exposeN((phantom, reflection, jit), JitLocalVariable);


#endif