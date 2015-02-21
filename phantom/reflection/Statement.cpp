/* TODO LICENCE HERE */

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include <phantom/reflection/Statement.h>
#include <phantom/reflection/Statement.hxx>
#include <phantom/reflection/Block.h>
#include <phantom/reflection/CallExpression.h>
#include <phantom/vector.hxx>
/* *********************************************** */
o_registerN((phantom, reflection), Statement);
o_registerNTI((phantom), vector, (phantom::reflection::Statement*));

o_namespace_begin(phantom, reflection) 

Statement::Statement()
    : m_uiIndexInBlock(~size_t(0))
    , m_pTemporaryObjectExpressions(nullptr)
{

}

Block* Statement::getRootBlock() const
{
    Block* pBlock = getEnclosingBlock();
    return pBlock ? pBlock->getRootBlock() : nullptr;
}

Subroutine* Statement::getSubroutine() const
{
    Block* pBlock = getEnclosingBlock();
    return  pBlock ? pBlock->getSubroutine() : nullptr;
}

Statement* Statement::getNextStatement() const
{
    Block* pBlock = getEnclosingBlock();
    if(pBlock == nullptr) return nullptr;
    size_t nextIndex = m_uiIndexInBlock+1;
    if(nextIndex == pBlock->getStatementCount())
        return pBlock->getNextStatement();
    return pBlock->getStatement(nextIndex);
}

void Statement::evalTemporaryObjectDestructions() const
{
    if(m_pTemporaryObjectExpressions)
    {
        for(auto it = m_pTemporaryObjectExpressions->begin(); it != m_pTemporaryObjectExpressions->end(); ++it)
        {
            (*it)->eval();
        }
    }
}

void Statement::addTemporaryObjectDestruction( CallExpression* a_pExpression )
{
    if(m_pTemporaryObjectExpressions == nullptr)
    {
        m_pTemporaryObjectExpressions = new list<CallExpression*>;
    }
    m_pTemporaryObjectExpressions->push_front(a_pExpression);
}

o_namespace_end(phantom, reflection)
