/* TODO LICENCE HERE */

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include <phantom/reflection/BuiltInOperatorExpression.h>
#include <phantom/reflection/BuiltInOperatorExpression.hxx>
#include <phantom/reflection/BuiltInOperator.h>
/* *********************************************** */
o_registerN((phantom, reflection), BuiltInOperatorExpression);

o_namespace_begin(phantom, reflection) 

BuiltInOperatorExpression::BuiltInOperatorExpression( BuiltInOperator* a_pOperator, Type* a_pResultType, Expression** a_Arguments, operation_delegate_t a_Delegate ) 
    : Expression(a_pResultType)
    , m_pOperator(a_pOperator)
    , m_Delegate(a_Delegate)
{
    if(m_Delegate.empty())
        setInvalid();
    addReferencedElement(m_pOperator);
    memcpy(m_Arguments, a_Arguments, sizeof(m_Arguments));
}

BuiltInOperatorExpression::~BuiltInOperatorExpression()
{
    
}

void BuiltInOperatorExpression::internalEval( void* a_pDest ) const
{
    void* addresses[2];
    size_t i = m_pOperator->getOperandCount();
    while(i--) // evaluate arguments from right to left
    {
        Expression* pArgument = m_Arguments[i];
        addresses[i] = pArgument->loadEffectiveAddress();
    }
    m_Delegate(addresses, a_pDest);
}

void BuiltInOperatorExpression::internalEval() const
{
    BuiltInOperatorExpression::internalEval(m_Buffer);
}

BuiltInOperatorExpression* BuiltInOperatorExpression::clone() const
{
    return o_new(BuiltInOperatorExpression)(m_pOperator, m_pValueType, (Expression**)m_Arguments, m_Delegate);
}

void BuiltInOperatorExpression::flush() const
{
    size_t i = m_pOperator->getOperandCount();
    while(i--)
        m_Arguments[i]->flush();
}

o_namespace_end(phantom, reflection)
