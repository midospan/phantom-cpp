/* TODO LICENCE HERE */

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include <phantom/reflection/BranchIfNotStatement.h>
#include <phantom/reflection/BranchIfNotStatement.hxx>
#include <phantom/reflection/Expression.h>
#include <phantom/reflection/Compiler.h>
/* *********************************************** */
o_registerN((phantom, reflection), BranchIfNotStatement);

o_namespace_begin(phantom, reflection) 

BranchIfNotStatement::BranchIfNotStatement( Expression* a_pExpression ) 
    : m_pExpression(a_pExpression)
    , m_pExpressionString(nullptr)
{
    if(m_pExpression->getValueType() != typeOf<bool>())
        setInvalid();
    addSubExpression(m_pExpression);
}

BranchIfNotStatement::BranchIfNotStatement( Expression* a_pExpression, LabelStatement* a_pLabelStatement )
    : BranchStatement(a_pLabelStatement)
    , m_pExpression(a_pExpression)
    , m_pExpressionString(nullptr)
{
    if(m_pExpression->getValueType() != typeOf<bool>())
        setInvalid();
    addSubExpression(m_pExpression);
}

void BranchIfNotStatement::internalEval() const 
{
    bool value;
    m_pExpression->internalEval(&value);
    evalTemporaryObjectDestructions();
    if(NOT(value))
    {
        BranchStatement::internalEval();
    }
}

void BranchIfNotStatement::flush() const
{
    m_pExpression->flush();
}

void BranchIfNotStatement::setExpressionString( string a_Expression )
{
    if(a_Expression.size())
    {
        m_pExpressionString = new string(a_Expression);
    }
}

string BranchIfNotStatement::getExpressionString() const
{
    return m_pExpression->translate();
}

void BranchIfNotStatement::restore()
{
//     BranchStatement::restore();
//     if(m_pExpression == nullptr AND m_pExpressionString)
//     {
//         m_pExpression = phantom::expressionByName(*m_pExpressionString, this);
//         if(m_pExpression)
//         {
//             if(m_pConvertedExpression == nullptr)
//                 setInvalid();
//             else
//                 addElement(m_pConvertedExpression);
//         }
//         else 
//         {
//             setInvalid();
//         }
//         delete m_pExpressionString;
//         m_pExpressionString = nullptr;
//     }
}

void BranchIfNotStatement::elementRemoved( LanguageElement* a_pElement )
{
    BranchStatement::elementRemoved(a_pElement);
    if(a_pElement == m_pExpression) // Type destroyed => expression cannot exist anymore
    {
        m_pExpression = nullptr;
    }
}

o_namespace_end(phantom, reflection)
