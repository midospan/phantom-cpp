/* TODO LICENCE HERE */

#ifndef o_phantom_reflection_DataMemberPointerAdjustmentExpression_h__
#define o_phantom_reflection_DataMemberPointerAdjustmentExpression_h__



/* ****************** Includes ******************* */
#include <phantom/reflection/Expression.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, reflection), DataMemberPointerAdjustmentExpression);
/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export DataMemberPointerAdjustmentExpression : public Expression
{
public:
    DataMemberPointerAdjustmentExpression( Type* a_pOutputPointerType, Expression* a_pPointerExpression, ptrdiff_t a_iOffset );
    ~DataMemberPointerAdjustmentExpression();

    virtual DataMemberPointerAdjustmentExpression* asDataMemberPointerAdjustmentExpression() const { return (DataMemberPointerAdjustmentExpression*)this; }

    virtual void    internalEval(void* a_pDest) const;

    virtual void    flush() const { m_pPointerExpression->flush(); }

    Expression*     getPointerExpression() const { return m_pPointerExpression; }

    ptrdiff_t       getOffset() const { return m_iOffset; }

    virtual DataMemberPointerAdjustmentExpression* clone() const;

protected:
    Expression*     m_pPointerExpression;
    ptrdiff_t       m_iOffset;
};

o_namespace_end(phantom, reflection)



#endif
