/* TODO LICENCE HERE */

#ifndef o_phantom_reflection_CommaExpression_h__
#define o_phantom_reflection_CommaExpression_h__



/* ****************** Includes ******************* */
#include <phantom/reflection/Expression.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, reflection), CommaExpression);
/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export CommaExpression : public Expression
{
public:
    CommaExpression(Expression* a_pLeftExpression, Expression* a_pRightExpression);
    o_destructor ~CommaExpression(void)     {}

    virtual void internalEval(void* a_pDest) const;

    virtual CommaExpression* asCommaExpression() const { return (CommaExpression*)this; }

    virtual CommaExpression* clone() const;

    virtual void internalEval() const { m_pLeftExpression->eval(); m_pRightExpression->eval(); }

protected:
    Expression*   m_pLeftExpression;
    Expression*   m_pRightExpression;
};

o_namespace_end(phantom, reflection)



#endif
