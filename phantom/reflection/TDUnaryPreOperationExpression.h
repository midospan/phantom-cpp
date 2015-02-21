/* TODO LICENCE HERE */

#ifndef o_phantom_reflection_TDUnaryPreOperationExpression_h__
#define o_phantom_reflection_TDUnaryPreOperationExpression_h__

/* ****************** Includes ******************* */
#include <phantom/reflection/Expression.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, reflection), TDUnaryPreOperationExpression);
/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export TDUnaryPreOperationExpression : public Expression
{
    o_language_element;

public:
    TDUnaryPreOperationExpression( Type* a_pType, const string& a_strOperator, Expression* a_pExpression );

    virtual TDUnaryPreOperationExpression*asTDUnaryPreOperationExpression() const { return (TDUnaryPreOperationExpression*)this; }

    virtual void    flush() const;

    virtual bool    isAddressable() const { return false; }

    Expression*     getExpression() const { return m_pExpression; }

    Expression*     getConvertedExpression() const { return m_pConvertedExpression; }

    const string&   getOperator() const { return m_strOperator; }

    virtual TDUnaryPreOperationExpression* clone() const;

protected:
    void internalEval(void* a_pDest) const 
    {
        o_exception_no_implementation();
    }

protected:
    string          m_strOperator;
    Expression*     m_pExpression;
    Expression*     m_pConvertedExpression;
};


o_namespace_end(phantom, reflection)



#endif
