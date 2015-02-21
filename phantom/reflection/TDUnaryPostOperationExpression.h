/* TODO LICENCE HERE */

#ifndef o_phantom_reflection_TDUnaryPostOperationExpression_h__
#define o_phantom_reflection_TDUnaryPostOperationExpression_h__

/* ****************** Includes ******************* */
#include <phantom/reflection/Expression.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, reflection), TDUnaryPostOperationExpression);
/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export TDUnaryPostOperationExpression : public Expression
{
    o_language_element;

public:
    TDUnaryPostOperationExpression( Type* a_pType, const string& a_strOperator, Expression* a_pExpression );

    virtual TDUnaryPostOperationExpression*asTDUnaryPostOperationExpression() const { return (TDUnaryPostOperationExpression*)this; }

    const string& getOperator() const { return m_strOperator; }

    virtual void    flush() const;

    virtual bool    isAddressable() const { return false; }

    Expression*     getExpression() const { return m_pExpression; }

    Expression*     getConvertedExpression() const { return m_pConvertedExpression; }

    virtual TDUnaryPostOperationExpression* clone() const;

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
