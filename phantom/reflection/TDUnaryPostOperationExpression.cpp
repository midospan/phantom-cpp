/* TODO LICENCE HERE */

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include <phantom/reflection/TDUnaryPostOperationExpression.h>
#include <phantom/reflection/TDUnaryPostOperationExpression.hxx>
/* *********************************************** */
o_registerN((phantom, reflection), TDUnaryPostOperationExpression);

o_namespace_begin(phantom, reflection) 

TDUnaryPostOperationExpression::TDUnaryPostOperationExpression( Type* a_pType, const string& a_strOperator, Expression* a_pExpression ) 
    : Expression(a_pType)
    , m_pExpression(a_pExpression)
{
    addSubExpression(m_pExpression);
}

void TDUnaryPostOperationExpression::flush() const
{
    m_pExpression->flush();
}

TDUnaryPostOperationExpression* TDUnaryPostOperationExpression::clone() const
{
    return o_new(TDUnaryPostOperationExpression)(m_pValueType, getOperator(), m_pExpression);
}


o_namespace_end(phantom, reflection)
