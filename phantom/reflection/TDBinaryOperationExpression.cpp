/* TODO LICENCE HERE */

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include <phantom/reflection/TDBinaryOperationExpression.h>
#include <phantom/reflection/TDBinaryOperationExpression.hxx>
/* *********************************************** */
o_registerN((phantom, reflection), TDBinaryOperationExpression);

o_namespace_begin(phantom, reflection) 
    
TDBinaryOperationExpression::TDBinaryOperationExpression( Type* a_pValueType, const string& a_strOperator, Expression* a_pLeftExpression, Expression* a_pRightExpression ) 
    : Expression(a_pValueType)
    , m_strOperator(a_strOperator)
    , m_pLeftExpression(a_pLeftExpression)
    , m_pRightExpression(a_pRightExpression)
{
    addSubExpression(m_pLeftExpression);
    addSubExpression(m_pRightExpression);
}

TDBinaryOperationExpression::~TDBinaryOperationExpression()
{
    
}


o_namespace_end(phantom, reflection)
