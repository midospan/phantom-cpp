/* TODO LICENCE HERE */

#ifndef o_phantom_reflection_MemberFunctionPointerAdjustmentExpression_h__
#define o_phantom_reflection_MemberFunctionPointerAdjustmentExpression_h__



/* ****************** Includes ******************* */
#include <phantom/reflection/Expression.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, reflection), MemberFunctionPointerAdjustmentExpression);
/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export MemberFunctionPointerAdjustmentExpression : public Expression
{
public:
    MemberFunctionPointerAdjustmentExpression( MemberFunctionPointerType* a_pOutputPointerType, Expression* a_pPointerExpression, ptrdiff_t a_iOffset );
    ~MemberFunctionPointerAdjustmentExpression();

    virtual MemberFunctionPointerAdjustmentExpression* asMemberFunctionPointerAdjustmentExpression() const { return (MemberFunctionPointerAdjustmentExpression*)this; }

    virtual void    internalEval(void* a_pDest) const;

    virtual void    flush() const { m_pPointerExpression->flush(); }

    Expression*     getPointerExpression() const { return m_pPointerExpression; }

    ptrdiff_t       getOffset() const { return m_iOffset; }

    virtual MemberFunctionPointerAdjustmentExpression* clone() const;

protected:
    Expression*     m_pPointerExpression;
    ptrdiff_t       m_iOffset;
};

o_namespace_end(phantom, reflection)



#endif
