/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include <phantom/reflection/Block.h>
#include <phantom/reflection/Block.hxx>
#include <phantom/reflection/Compiler.h>
#include <phantom/reflection/Interpreter.h>
#include <phantom/reflection/ExpressionStatement.h>
#include "LocalVariable.h"
#include "LocalVariableAccess.h"
/* *********************************************** */
o_registerN((phantom, reflection), Block);
o_namespace_begin(phantom, reflection) 

Block::Block()
{

}

Block::Block(const string& a_strName)
    : Statement(a_strName)
{

}

Block::~Block()
{

}

void Block::addLocalVariable( LocalVariable* a_pVariable )
{
	o_assert(getLocalVariable(a_pVariable->getName()) == nullptr);
    o_assert(getSubroutine());
    m_LocalVariables.push_back(a_pVariable);
    size_t& frameSize = getSubroutine()->m_uiFrameSize;
    a_pVariable->m_iFrameOffset = frameSize;
    frameSize += a_pVariable->getValueType()->getSize();
    addElement(a_pVariable);
}

LocalVariable* Block::getLocalVariableCascade( const string& a_strName ) const
{
	LocalVariable* pResult = getLocalVariable(a_strName);
	return pResult 
            ? pResult 
            : getBlock() 
                ? getBlock()->getLocalVariableCascade(a_strName) 
                : nullptr;
}

LocalVariable* Block::getLocalVariable( const string& a_strName ) const
{
    for(auto it = m_LocalVariables.begin(); it != m_LocalVariables.end(); ++it)
    {
        if((*it)->getName() == a_strName)
        {
            return *it;
        }
    }
    return nullptr;
}

void Block::getAccessibleLocalVariables( vector<LocalVariable*>& out, const CodePosition& position ) const
{
    if(getBlock()) getBlock()->getAccessibleLocalVariables(out, position);
    for(auto it = m_LocalVariables.begin(); it != m_LocalVariables.end(); ++it)
    {
        LocalVariable* pLocalVariable = *it;
        if(pLocalVariable->isAccessibleAtCodePosition(position))
        {
            out.push_back(pLocalVariable);
        }
    }
}

LocalVariable* Block::getAccessibleLocalVariable( const string& a_strName, const CodePosition& a_Position ) const
{
    LocalVariable* pLocalVariable = getLocalVariable(a_strName);
    if(pLocalVariable && pLocalVariable->isAccessibleAtCodePosition(a_Position)) return pLocalVariable;
    return getBlock() ? getBlock()->getAccessibleLocalVariable(a_strName, a_Position) : nullptr;
}

reflection::LanguageElement* Block::solveElement( const string& a_strName, const vector<TemplateElement*>* a_pTS, const vector<LanguageElement*>* a_pFS, bitfield a_Modifiers /* = bitfield */ ) const
{
    LocalVariable* pLocal = getLocalVariable(a_strName);
    if(pLocal) return o_new(LocalVariableAccess)(pLocal);
    int blockIndex = -1;
    sscanf(a_strName.c_str(), "%d", &blockIndex);
    if(blockIndex >= 0 AND blockIndex < (int)m_Statements.size())
    {
        size_t c = 0;
        for(auto it = m_Statements.begin(); it != m_Statements.end(); ++it)
        {
            Block* pChildBlock = (*it)->asBlock();
            if(pChildBlock)
            {
                if(c == blockIndex)
                {
                    return pChildBlock;
                }
                ++c;
            }
        }
    }
    return nullptr;
}

Block* Block::findBlockAtCodePosition( const CodePosition& a_Position ) const
{
    if(containsCodePosition(a_Position))
    {
        for(auto it = m_Statements.begin(); it != m_Statements.end(); ++it)
        {
            Block* pChildBlock = (*it)->asBlock();
            if(pChildBlock)
            {
                Block* pBlock = pChildBlock->findBlockAtCodePosition(a_Position);
                if(pBlock) return pBlock;
            }
        }
        return const_cast<Block*>(this);
    }
    return nullptr;
}

void Block::getLocalVariablesCascade( vector<LocalVariable*>& out ) const
{
    out.insert(out.end(), m_LocalVariables.begin(), m_LocalVariables.end());
    for(auto it = m_Statements.begin(); it != m_Statements.end(); ++it)
    {
        Block* pChildBlock = (*it)->asBlock();
        if(pChildBlock)
        {
            pChildBlock->getLocalVariablesCascade(out);
        }
    }
}

Subroutine* Block::getSubroutine() const
{
    LanguageElement* pElement = getRootBlock()->getOwner();
    return pElement ? pElement->asSubroutine() : nullptr;
}

bool Block::containsLine( int line ) const
{
    return getCodeLocation().containsLine(line);
}

void Block::getAccessibleElementsAt( const CodePosition& a_Position, vector<LanguageElement*>& a_Elements ) const
{
    vector<reflection::LocalVariable*> locals;
    getAccessibleLocalVariables(locals, a_Position);
    a_Elements.insert(a_Elements.end(), locals.begin(), locals.end());
    vector<reflection::Block*> blocks;
    size_t i = 0;
    for(auto it = m_Statements.begin(); it != m_Statements.end(); ++it)
    {
        Block* pChildBlock = (*it)->asBlock();
        if(pChildBlock)
        {
            pChildBlock->getAccessibleElementsAt(a_Position, a_Elements);
        }
    }
}

void Block::addStatement( Statement* a_pStatement )
{
    addElement(a_pStatement);
    a_pStatement->m_uiIndexInBlock = m_Statements.size();
    m_Statements.push_back(a_pStatement); 
}

variant Block::compile( Compiler* a_pCompiler )
{
    return a_pCompiler->compile(this);
}

void Block::eval() const
{
    Statement* pStatement = getFirstStatementCascade();
    if(pStatement)
    {
        phantom::interpreter()->setNextStatement(pStatement);
    }
}

void Block::prependStatements( const vector<Statement*>& a_Statements )
{
    for(auto it = a_Statements.begin(); it != a_Statements.end(); ++it)
    {
        addElement(*it);
    }
    m_Statements.insert(m_Statements.begin(), a_Statements.begin(), a_Statements.end());
}

Statement* Block::getFirstStatementCascade() const
{
    Statement* pFirstStatement = nullptr;
    for(auto it = m_Statements.begin(); it != m_Statements.end(); ++it)
    {
        if(*it)
        {
            Block* pBlock = (*it)->asBlock();
            if(pBlock)
            {
                Statement* pFirstStatement = pBlock->getFirstStatementCascade();
                if(pFirstStatement) return pFirstStatement;
            }
            else return *it; 
        }
    }
    return nullptr;
}

void Block::addExpressionStatement( Expression* a_pExpression )
{
    addStatement(o_new(ExpressionStatement)(a_pExpression));
}

o_namespace_end(phantom, reflection)