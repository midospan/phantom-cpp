/* TODO LICENCE HERE */

#ifndef o_phantom_reflection_WStringLiteralExpression_h__
#define o_phantom_reflection_WStringLiteralExpression_h__



/* ****************** Includes ******************* */
#include <phantom/reflection/Expression.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, reflection), WStringLiteralExpression);
/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export WStringLiteralExpression : public Expression
{
    o_language_element;

public:
    WStringLiteralExpression(const string& literal, const wstring& a_Value);
    o_destructor ~WStringLiteralExpression(void)     {}

    virtual WStringLiteralExpression*    asWStringLiteralExpression() const { return (WStringLiteralExpression*)this; }

    virtual void*   evalStorage() const { return (void*)&m_Value; }

    virtual void    internalEval(void* a_pDest) const;

    const wchar_t*  getString() const { return m_Value; }

    const string&   getLiteral() const { return m_literal; }

    virtual bool    isAddressable() const { return true; }

    virtual bool    isReferenceable() const { return true; }

    virtual WStringLiteralExpression*     clone() const;

protected:
    const string& m_literal;
    const wchar_t* m_Value;
};

o_namespace_end(phantom, reflection)



#endif
