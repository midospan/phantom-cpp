/* TODO LICENCE HERE */

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include <phantom/reflection/CommaExpression.h>
#include <phantom/reflection/CommaExpression.hxx>
/* *********************************************** */
o_registerN((phantom, reflection), CommaExpression);

o_namespace_begin(phantom, reflection) 

CommaExpression::CommaExpression(Expression* a_pLeftExpression, Expression* a_pRightExpression)
    : Expression(a_pRightExpression ? a_pRightExpression->getValueType() : nullptr)
    , m_pLeftExpression(a_pLeftExpression)
    , m_pRightExpression(a_pRightExpression)
{
    if(m_pLeftExpression)
    {
        addSubExpression(m_pLeftExpression);
    }
    else setInvalid();

    if(m_pRightExpression)
    {
        addSubExpression(m_pRightExpression);
    }
    else setInvalid();
}

void CommaExpression::internalEval( void* a_pDest ) const
{
    m_pLeftExpression->internalEval();
    m_pRightExpression->internalEval(a_pDest);
}

CommaExpression* CommaExpression::clone() const
{
    return o_new(CommaExpression)(m_pLeftExpression, m_pRightExpression);
}


o_namespace_end(phantom, reflection)
