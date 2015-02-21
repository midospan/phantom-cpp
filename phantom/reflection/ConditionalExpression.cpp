/* TODO LICENCE HERE */

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include <phantom/reflection/ConditionalExpression.h>
#include <phantom/reflection/ConditionalExpression.hxx>
#include <phantom/reflection/ConstantExpression.h>
/* *********************************************** */
o_registerN((phantom, reflection), ConditionalExpression);

o_namespace_begin(phantom, reflection) 

ConditionalExpression::ConditionalExpression(Expression* a_pTestExpression, Expression* a_pThenExpression, Expression* a_pElseExpression)
    : Expression(a_pThenExpression->getValueType())
    , m_pTestExpression(a_pTestExpression)
    , m_pThenExpression(a_pThenExpression)
    , m_pElseExpression(a_pElseExpression)
{
    if(m_pTestExpression->getValueType() != typeOf<bool>()) setInvalid();
    if(!m_pElseExpression->getValueType()->equals(m_pThenExpression->getValueType())) setInvalid();
    addSubExpression(m_pTestExpression);
    addSubExpression(m_pThenExpression);
    addSubExpression(m_pElseExpression);
}

void ConditionalExpression::internalEval( void* a_pDest ) const
{
    bool result = false;
    m_pTestExpression->load(&result);
    if(result)
    {
        m_pThenExpression->internalEval(a_pDest);
    }
    else 
    {
        m_pElseExpression->internalEval(a_pDest);
    }
}

ConditionalExpression* ConditionalExpression::clone() const
{
    return o_new(ConditionalExpression)(m_pTestExpression, m_pThenExpression, m_pElseExpression);
}


o_namespace_end(phantom, reflection)
