/* TODO LICENCE HERE */

#ifndef o_phantom_reflection_RValueExpression_h__
#define o_phantom_reflection_RValueExpression_h__



/* ****************** Includes ******************* */
#include <phantom/reflection/Expression.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, reflection), RValueExpression);
/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export RValueExpression : public Expression
{
    o_language_element;

public:
    RValueExpression(Expression* a_pReferenceableExpression);

    virtual void                    internalEval(void* a_pDest) const;

    virtual RValueExpression*    asRValueExpression() const  { return const_cast<RValueExpression*>(this); }

    virtual void flush() const { m_pReferencedExpression->flush(); }
        
    virtual Expression*     dereference() const
    {
        Expression* pExp = m_pReferencedExpression;
        const_cast<RValueExpression*>(this)->removeElement(pExp);
        o_dynamic_delete const_cast<RValueExpression*>(this);
        return pExp;
    }

    Expression* getReferencedExpression() const { return m_pReferencedExpression; }

    virtual RValueExpression*     clone() const;
protected:
    Expression* m_pReferencedExpression;
};

o_namespace_end(phantom, reflection)



#endif
