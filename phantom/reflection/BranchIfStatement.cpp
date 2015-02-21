/* TODO LICENCE HERE */

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include <phantom/reflection/BranchIfStatement.h>
#include <phantom/reflection/BranchIfStatement.hxx>
#include <phantom/reflection/Expression.h>
#include <phantom/reflection/Compiler.h>
/* *********************************************** */
o_registerN((phantom, reflection), BranchIfStatement);

o_namespace_begin(phantom, reflection) 

BranchIfStatement::BranchIfStatement( Expression* a_pExpression ) 
    : m_pExpression(a_pExpression)
    , m_pExpressionString(nullptr)
{
    if(m_pExpression->getValueType() != typeOf<bool>())
        setInvalid();
    addSubExpression(m_pExpression);
}

BranchIfStatement::BranchIfStatement( Expression* a_pExpression, LabelStatement* a_pLabelStatement )
    : BranchStatement(a_pLabelStatement)
    , m_pExpression(a_pExpression)
    , m_pExpressionString(nullptr)
{
    if(m_pExpression->getValueType() != typeOf<bool>())
        setInvalid();
    addSubExpression(m_pExpression);
}

void BranchIfStatement::internalEval() const 
{
    bool value;
    m_pConvertedExpression->internalEval(&value);
    evalTemporaryObjectDestructions();
    if(value)
    {
        BranchStatement::internalEval();
    }
}

void BranchIfStatement::flush() const
{
    m_pConvertedExpression->flush();
}

void BranchIfStatement::setExpressionString( string a_Expression )
{
    if(a_Expression.size())
    {
        m_pExpressionString = new string(a_Expression);
    }
}

string BranchIfStatement::getExpressionString() const
{
    return m_pExpression->translate();
}

void BranchIfStatement::restore()
{
//     BranchStatement::restore();
//     if(m_pExpression == nullptr AND m_pExpressionString)
//     {
//         m_pExpression = phantom::expressionByName(*m_pExpressionString, this);
//         o_assert(m_pExpression);
//         m_pConvertedExpression = m_pExpression ? m_pExpression->implicitCast(typeOf<bool>()) : nullptr;
//         if(m_pExpression)
//         {
//             if(m_pConvertedExpression == nullptr)
//                 setInvalid();
//             else
//                 addElement(m_pConvertedExpression);
//         }
//         delete m_pExpressionString;
//         m_pExpressionString = nullptr;
//     }
}

void BranchIfStatement::elementRemoved( LanguageElement* a_pElement )
{
    BranchStatement::elementRemoved(a_pElement);
    if(a_pElement == m_pExpression) // Expression destroyed => invalid
    {
        m_pExpression = nullptr;
    }
}


o_namespace_end(phantom, reflection)
