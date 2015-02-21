/* TODO LICENCE HERE */

#ifndef o_phantom_reflection_PointerAdjustmentExpression_h__
#define o_phantom_reflection_PointerAdjustmentExpression_h__



/* ****************** Includes ******************* */
#include <phantom/reflection/Expression.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, reflection), PointerAdjustmentExpression);
/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export PointerAdjustmentExpression : public Expression
{
public:
    PointerAdjustmentExpression( Type* a_pOutputAddressType, Expression* a_pPointerExpression, ptrdiff_t a_iOffset );
    ~PointerAdjustmentExpression();

    virtual PointerAdjustmentExpression* asPointerAdjustmentExpression() const { return (PointerAdjustmentExpression*)this; }

    virtual void    internalEval(void* a_pDest) const;

    virtual void    flush() const { m_pPointerExpression->flush(); }

    Expression*     getPointerExpression() const { return m_pPointerExpression; }

    ptrdiff_t       getOffset() const { return m_iOffset; }

    virtual PointerAdjustmentExpression* clone() const;

protected:
    Statement*      evaluateExpressionLifeTime( Expression* a_pExpression ) const
    {
        /// life time of sub expression is this expression life time (because only a pointer shift)
        return evaluateLifeTime();
    }

protected:
    Expression*     m_pPointerExpression;
    ptrdiff_t       m_iOffset;
};

o_namespace_end(phantom, reflection)



#endif
