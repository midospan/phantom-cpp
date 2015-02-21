

#ifndef o_reflection_Parameter_h__
#define o_reflection_Parameter_h__
// #pragma __PragmaPrintFile__


/* ****************** Includes ******************* */
#include <phantom/reflection/LocalVariable.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, reflection), Parameter);
/* *********************************************** */

o_namespace_begin(phantom, reflection)

class Block;
class o_export Parameter : public LocalVariable
{
    o_language_element;

    friend class Signature;

    o_declare_meta_type(Parameter);

public:
    Parameter();
    Parameter(Type* a_pType, const string& a_strName = "", Expression* a_pInitializer = nullptr, modifiers_t modifiers = 0);
	~Parameter(void) 	{}

    void setDefinitionName(const string& a_strName);

    virtual Parameter*  asParameter() const { return (Parameter*)this; }

    virtual Parameter* clone() const;
};

o_namespace_end(phantom, reflection)
    
#endif