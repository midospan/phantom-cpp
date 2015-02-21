/* TODO LICENCE HERE */

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include <phantom/reflection/ReturnStatement.h>
#include <phantom/reflection/ReturnStatement.hxx>
#include <phantom/reflection/Expression.h>
#include <phantom/reflection/Compiler.h>
#include <phantom/reflection/Interpreter.h>
#include <phantom/reflection/Block.h>
/* *********************************************** */
o_registerN((phantom, reflection), ReturnStatement);

o_namespace_begin(phantom, reflection) 

ReturnStatement::ReturnStatement() 
    : m_pReturnExpression(nullptr)
    , m_pConvertedReturnExpression(nullptr)
    , m_pExpressionString(nullptr)
{
}

ReturnStatement::ReturnStatement(Expression* a_pExpression) 
    : m_pReturnExpression(nullptr)
    , m_pConvertedReturnExpression(nullptr)
    , m_pExpressionString(nullptr)
{
    setExpression(a_pExpression);
}

void ReturnStatement::internalEval() const 
{
    if(m_pReturnExpression)
    {
        m_pReturnExpression->internalEval(phantom::interpreter()->getReturnAddress());
    }
    for(auto it = m_RAIIDestructionStatements.begin(); it != m_RAIIDestructionStatements.end(); ++it)
    {
        (*it)->eval();
    }
    phantom::interpreter()->setNextStatement(nullptr);
}

void ReturnStatement::checkValidity()
{
    o_assert(getSubroutine());
    if(getSubroutine()->getReturnType() == typeOf<void>() && m_pReturnExpression)
    {
        setInvalid();
    }
    else if(getSubroutine()->getReturnType() != typeOf<void>() && m_pReturnExpression == nullptr)
    {
        setInvalid();
    }
    else if(NOT(m_pReturnExpression->getValueType()->equals(getSubroutine()->getReturnType())))
    {
        setInvalid();
    }
}

void ReturnStatement::setExpression( Expression* a_pReturnExpression )
{
    o_assert(m_pReturnExpression == nullptr);
    addSubExpression(m_pReturnExpression = a_pReturnExpression);
    
    if(m_pReturnExpression)
    {
        if(getSubroutine())
        {
            checkValidity();
        }
    }
}

void ReturnStatement::setExpressionString( string a_Expression )
{
    if(a_Expression.size())
    {
        m_pExpressionString = new string(a_Expression);
    }
}

string ReturnStatement::getExpressionString() const
{
    return m_pReturnExpression ? m_pReturnExpression->translate() : string();
}

void ReturnStatement::restore()
{
    if(m_pReturnExpression == nullptr AND m_pExpressionString)
    {
        Expression* pExpression = phantom::expressionByName(*m_pExpressionString, this);
        if(pExpression)
        {
            setExpression(pExpression);
        }
        delete m_pExpressionString;
        m_pExpressionString = nullptr;
    }
}

void ReturnStatement::ancestorChanged( LanguageElement* a_pOwner )
{
    o_assert(m_pOwner == a_pOwner 
        AND m_pOwner->asBlock() 
        AND getSubroutine() );
    if(m_pReturnExpression)
    {
        checkValidity();
    }
    m_pOwner->asBlock()->getRAIIDestructionStatementsCascade(m_RAIIDestructionStatements);
}

o_namespace_end(phantom, reflection)
