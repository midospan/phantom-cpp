/* TODO LICENCE HERE */

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include <phantom/reflection/LoadExpression.h>
#include <phantom/reflection/LoadExpression.hxx>
/* *********************************************** */
o_registerN((phantom, reflection), LoadExpression);

o_namespace_begin(phantom, reflection) 

LoadExpression::LoadExpression( Expression* a_pLoadedExpression ) 
    : Expression(a_pLoadedExpression->getValueType()->removeReference())
    , m_pLoadedExpression(a_pLoadedExpression)
{
    if(m_pLoadedExpression)
    {
        addSubExpression(m_pLoadedExpression);
        if(NOT(m_pLoadedExpression->getValueType()->asReferenceType()))
        {
            setInvalid();
        }
    }
    else setInvalid();
}

LoadExpression* LoadExpression::clone() const
{
    return o_new(LoadExpression)(m_pLoadedExpression);
}

void LoadExpression::internalEval( void* a_pDest ) const
{
    m_pValueType->copy(a_pDest, m_pLoadedExpression->loadEffectiveAddress());
}

o_namespace_end(phantom, reflection)
