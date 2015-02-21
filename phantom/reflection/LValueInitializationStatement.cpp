/* TODO LICENCE HERE */

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include <phantom/reflection/LValueInitializationStatement.h>
#include <phantom/reflection/LValueInitializationStatement.hxx>
#include <phantom/reflection/Expression.h>
#include <phantom/reflection/Block.h>
/* *********************************************** */
o_registerN((phantom, reflection), LValueInitializationStatement);

o_namespace_begin(phantom, reflection) 

LValueInitializationStatement::LValueInitializationStatement( Type* a_pValueType, Expression* a_pRightExpression ) 
    : m_pValueType(a_pValueType)
    , m_pRightExpression(a_pRightExpression)
{
    if(m_pRightExpression)
    {
        addSubExpression(m_pRightExpression);
    }
}

LValueInitializationStatement::~LValueInitializationStatement()
{
    
}

Statement* LValueInitializationStatement::evaluateExpressionLifeTime( Expression* a_pExpression ) const
{
    o_assert(m_pRightExpression == a_pExpression);
    if(getValueType()->asRValueReferenceType() 
        OR getValueType()->asConstReferenceType()) /// const T& | T&&
    {
        return getEnclosingBlock();
    }
    return const_cast<LValueInitializationStatement*>(this);
}

o_namespace_end(phantom, reflection)
