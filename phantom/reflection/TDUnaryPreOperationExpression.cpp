/* TODO LICENCE HERE */

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include <phantom/reflection/TDUnaryPreOperationExpression.h>
#include <phantom/reflection/TDUnaryPreOperationExpression.hxx>
/* *********************************************** */
o_registerN((phantom, reflection), TDUnaryPreOperationExpression);

o_namespace_begin(phantom, reflection) 

TDUnaryPreOperationExpression::TDUnaryPreOperationExpression( Type* a_pType, const string& a_strOperator, Expression* a_pExpression ) 
: Expression(a_pType)
, m_pExpression(a_pExpression)
{
    addSubExpression(m_pExpression);
}

void TDUnaryPreOperationExpression::flush() const
{
    m_pExpression->flush();
}

TDUnaryPreOperationExpression* TDUnaryPreOperationExpression::clone() const
{
    return o_new(TDUnaryPreOperationExpression)(m_pValueType, getOperator(), m_pExpression);
}


o_namespace_end(phantom, reflection)
