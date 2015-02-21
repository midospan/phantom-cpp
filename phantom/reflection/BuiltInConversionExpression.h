/* TODO LICENCE HERE */

#ifndef o_phantom_reflection_BuiltInConversionExpression_h__
#define o_phantom_reflection_BuiltInConversionExpression_h__



/* ****************** Includes ******************* */
#include <phantom/reflection/Expression.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, reflection), BuiltInConversionExpression);
/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export BuiltInConversionExpression : public Expression
{
    o_language_element;

public:
    BuiltInConversionExpression( Expression* a_pInputExpression, conversion* a_pConversion, int a_iConversionType );
    ~BuiltInConversionExpression();

    o_terminate();

    virtual BuiltInConversionExpression*  asBuiltInConversionExpression() const { return (BuiltInConversionExpression*)this; }

    virtual void    internalEval(void* a_pDest) const;

    virtual void    flush() const { m_pInputExpression->flush(); }

    Expression* getInputExpression() const { return m_pInputExpression; }

    virtual BuiltInConversionExpression*     clone() const;

    const conversion* getConversion() const { return m_pConversion; }

    bool hasValueStorage() const { return true; }

    void* evalStorage() const;

    int getConversionType() const { return m_iConversionType; }

protected:
    virtual void referencedElementRemoved(LanguageElement* a_pElement);
    virtual void elementRemoved( LanguageElement* a_pElement );

protected:
    Expression*     m_pInputExpression;
    void*           m_pTempValue;
    void*           m_pStorage;
    conversion*     m_pConversion;
    int             m_iConversionType;
};

o_namespace_end(phantom, reflection)

#endif // o_phantom_reflection_BuiltInConversionExpression_h__
