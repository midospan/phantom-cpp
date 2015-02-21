/* TODO LICENCE HERE */

#ifndef o_phantom_reflection_StringLiteralExpression_h__
#define o_phantom_reflection_StringLiteralExpression_h__



/* ****************** Includes ******************* */
#include <phantom/reflection/Expression.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, reflection), StringLiteralExpression);
/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export StringLiteralExpression : public Expression
{
    o_language_element;

public:
    StringLiteralExpression(const string& literal, const string& a_Value);
    o_destructor ~StringLiteralExpression(void)     {}

    virtual StringLiteralExpression*    asStringLiteralExpression() const { return (StringLiteralExpression*)this; }

    virtual void* evalStorage() const { return (void*)&m_Value; }

    virtual void    internalEval(void* a_pDest) const;

    const char*     getString() const { return m_Value; }

    const string&   getLiteral() const { return m_literal; }

    virtual bool    isAddressable() const { return true; }

    virtual bool    isReferenceable() const { return true; }

    virtual StringLiteralExpression*     clone() const;

protected:
    const string& m_literal;
    const char* m_Value;
};

o_namespace_end(phantom, reflection)



#endif
