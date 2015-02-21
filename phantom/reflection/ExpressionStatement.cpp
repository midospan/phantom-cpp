/* TODO LICENCE HERE */

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include <phantom/reflection/ExpressionStatement.h>
#include <phantom/reflection/ExpressionStatement.hxx>
#include <phantom/reflection/Expression.h>
#include <phantom/reflection/Compiler.h>
/* *********************************************** */
o_registerN((phantom, reflection), ExpressionStatement);

o_namespace_begin(phantom, reflection) 

ExpressionStatement::ExpressionStatement()
    : m_pExpression(nullptr)
{

}

ExpressionStatement::ExpressionStatement( Expression* a_pExpression ) 
    : m_pExpression(a_pExpression)
{
    if(m_pExpression)
    {
        addElement(m_pExpression);
    }
    else 
    {
        setInvalid();
    }
}

void ExpressionStatement::internalEval() const 
{
    m_pExpression->eval();
}

void ExpressionStatement::flush() const
{
    m_pExpression->flush();
}

void ExpressionStatement::elementRemoved( LanguageElement* a_pElement )
{
    Statement::elementRemoved(a_pElement);
    if(a_pElement == m_pExpression) // Expression destroyed => invalid
    {
        m_pExpression = nullptr;
    }
}

o_namespace_end(phantom, reflection)
