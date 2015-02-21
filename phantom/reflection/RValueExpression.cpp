/* TODO LICENCE HERE */

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include <phantom/reflection/RValueExpression.h>
#include <phantom/reflection/RValueExpression.hxx>
/* *********************************************** */
o_registerN((phantom, reflection), RValueExpression);

o_namespace_begin(phantom, reflection) 

RValueExpression::RValueExpression( Expression* a_pReferencedExpression ) 
    : Expression(a_pReferencedExpression->getValueType()->removeReference()->rvalueReferenceType())
    , m_pReferencedExpression(a_pReferencedExpression)
{
    if(m_pReferencedExpression)
    {
        addSubExpression(m_pReferencedExpression);
        if(m_pReferencedExpression->asReferenceType()
            OR !m_pReferencedExpression->hasEffectiveAddress())
        {
            setInvalid();
        }
    }
    else setInvalid();
}

RValueExpression* RValueExpression::clone() const
{
    return o_new(RValueExpression)(m_pReferencedExpression);
}

void RValueExpression::internalEval( void* a_pDest ) const
{
    *((void**)a_pDest) = m_pReferencedExpression->loadEffectiveAddress();
}

o_namespace_end(phantom, reflection)
