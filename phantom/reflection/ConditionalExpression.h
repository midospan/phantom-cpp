/* TODO LICENCE HERE */

#ifndef o_phantom_reflection_ConditionalExpression_h__
#define o_phantom_reflection_ConditionalExpression_h__



/* ****************** Includes ******************* */
#include <phantom/reflection/Expression.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, reflection), ConditionalExpression);
/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export ConditionalExpression : public Expression
{
public:
    ConditionalExpression(Expression* a_pTestExpression, Expression* a_pThenExpression, Expression* a_pElseExpression);
    o_destructor ~ConditionalExpression(void)     {}

    virtual void internalEval(void* a_pDest) const;

    virtual ConditionalExpression* asConditionalExpression() const { return (ConditionalExpression*)this; }

    virtual ConditionalExpression* clone() const;

protected:
    Expression*   m_pTestExpression;
    Expression*   m_pConvertedTestExpression;
    Expression*   m_pThenExpression;
    Expression*   m_pConvertedThenExpression;
    Expression*   m_pElseExpression;
    Expression*   m_pConvertedElseExpression;
};

o_namespace_end(phantom, reflection)



#endif
