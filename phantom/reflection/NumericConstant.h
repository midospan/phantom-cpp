/* TODO LICENCE HERE */

#ifndef o_phantom_reflection_NumericConstant_h__
#define o_phantom_reflection_NumericConstant_h__

/* ****************** Includes ******************* */
/* **************** Declarations ***************** */
/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export NumericConstant : public Constant
{
public:
    static Class* const metaType;

public:
    NumericConstant()
    {

    }
    NumericConstant(const string& a_strName, modifiers_t modifiers = 0)
        : Constant(a_strName, modifiers)
    {

    }

    virtual LanguageElement* asTemplateElement() const { return const_cast<NumericConstant*>(this); }
    virtual LanguageElement* asLanguageElement() const { return const_cast<NumericConstant*>(this); }
    virtual NumericConstant* asNumericConstant() const { return const_cast<NumericConstant*>(this); }


protected:
};

o_namespace_end(phantom, reflection)



#endif
