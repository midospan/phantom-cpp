/* TODO LICENCE HERE */

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include <phantom/reflection/BranchStatement.h>
#include <phantom/reflection/BranchStatement.hxx>
#include <phantom/reflection/LabelStatement.h>
#include <phantom/reflection/Expression.h>
#include <phantom/reflection/Compiler.h>
#include <phantom/reflection/Interpreter.h>
/* *********************************************** */
o_registerN((phantom, reflection), BranchStatement);

o_namespace_begin(phantom, reflection) 

BranchStatement::BranchStatement() 
    : m_pLabelStatement(nullptr)
    , m_uiLabelStatementIndex(0xffffffff)
{
}

BranchStatement::BranchStatement(LabelStatement* a_pLabelStatement) 
    : m_pLabelStatement(nullptr)
    , m_uiLabelStatementIndex(0xffffffff)
{
    setLabelStatement(a_pLabelStatement);
}

void BranchStatement::internalEval() const 
{
    phantom::interpreter()->setNextStatement(m_pLabelStatement);
}

void BranchStatement::setLabelStatement( LabelStatement* a_pLabelStatement )
{
    if(a_pLabelStatement)
    {
        addReferencedElement(a_pLabelStatement);
        m_pLabelStatement = a_pLabelStatement;
        if(getSubroutine())
        {
            m_uiLabelStatementIndex = m_pLabelStatement->getIndex();
        }
        m_pLabelStatement->m_uiBranchCount++;
    }
    else setInvalid();
}

void BranchStatement::restore()
{
    if(m_pLabelStatement == nullptr AND m_uiLabelStatementIndex != 0xffffffff)
    {
        m_pLabelStatement = getSubroutine()->getLabelStatement(m_uiLabelStatementIndex);
        if(m_pLabelStatement)
        {
            addReferencedElement(m_pLabelStatement);
        }
    }
}

void BranchStatement::elementRemoved( LanguageElement* a_pElement )
{
    Statement::elementRemoved(a_pElement);
    if(a_pElement == m_pLabelStatement) // Expression destroyed => invalid
    {
        m_pLabelStatement = nullptr;
        m_uiLabelStatementIndex = 0xffffffff;
    }
}

void BranchStatement::ancestorChanged( LanguageElement* a_pOwner )
{
    if(getSubroutine() AND m_uiLabelStatementIndex == 0xffffffff AND m_pLabelStatement)
    {
        m_uiLabelStatementIndex = m_pLabelStatement->getIndex();
    }
}

o_namespace_end(phantom, reflection)
