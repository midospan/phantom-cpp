/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include <phantom/reflection/Block.h>
#include <phantom/reflection/Block.hxx>
#include <phantom/reflection/Parameter.h>
#include <phantom/reflection/Compiler.h>
#include <phantom/reflection/Interpreter.h>
#include <phantom/reflection/ExpressionStatement.h>
#include <phantom/reflection/CallExpression.h>
#include <phantom/reflection/ReturnStatement.h>
#include <phantom/reflection/LabelStatement.h>
#include <phantom/reflection/BranchIfNotStatement.h>
#include <phantom/reflection/BranchIfStatement.h>
#include "LocalVariable.h"
#include "LocalVariableExpression.h"
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp>
/* *********************************************** */
o_registerN((phantom, reflection), Block);
o_namespace_begin(phantom, reflection) 

Block::Block()
{

}

Block::Block(Block* a_pBlock, const string& a_strName)
    : Statement(a_strName)
{
    o_assert(a_pBlock);
    a_pBlock->addStatement(this);
}

Block::Block( Subroutine* a_pSubroutine, LocalVariable* a_pThis )
{
    a_pSubroutine->setBlock(this);
    if(a_pThis)
    {
        addLocalVariable(a_pThis);
    }
    Signature* pSignature = a_pSubroutine->getSignature();
    size_t count = pSignature->getParameterCount();
    for(size_t i = 0; i<count; ++i)
    {
        string name = pSignature->getParameterName(i);
        addLocalVariable(pSignature->getParameter(i));
    }
}

Block::~Block()
{

}

void Block::addLocalVariable( LocalVariable* a_pVariable )
{
	o_assert(getLocalVariable(a_pVariable->getName()) == nullptr);
    m_LocalVariables.push_back(a_pVariable);
    if(a_pVariable->m_iFrameOffset == LocalVariable::e_InvalidFrameOffset)
    {
        o_assert(getSubroutine());
        size_t& frameSize = getSubroutine()->m_uiFrameSize;
        a_pVariable->m_iFrameOffset = frameSize;
        frameSize+=a_pVariable->getValueType()->getSize();
    }
    if(NOT(a_pVariable->isInvalid()))
    {
        Class* pClass = a_pVariable->getValueType() ? a_pVariable->getValueType()->asClass() : nullptr;
        if(pClass)
        {
            addRAIIDestructionExpressionStatement(o_new(CallExpression)(pClass->getDestructor(), a_pVariable->createExpression()->address()));
        }
    }
    if(a_pVariable->asParameter() == nullptr) // parameters are owned by signature
    {
        addElement(a_pVariable);
    }
    else 
    {
        addReferencedElement(a_pVariable);
    }
}

void Block::addLocalVariable( Type* a_pType, const string& a_strName, Expression* a_pInit /*= nullptr*/, modifiers_t a_Modifiers /*= 0*/ )
{
    addLocalVariable(o_new(LocalVariable)(a_pType, a_strName, a_pInit, a_Modifiers));
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

void Block::internalEval() const 
{
    if(isInvalid())
    {
        o_exception(exception::reflection_runtime_exception, "Block is invalid");
    }
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

void Block::addExpressionStatement( const string& a_strExpression )
{
    addExpressionStatement(expressionByName(a_strExpression));
}

void Block::setLocalVariables(vector<LocalVariable*> list)
{
    for(auto it = list.begin(); it != list.end(); ++it)
    {
        addLocalVariable(*it);
    }
}

void Block::setStatements(vector<Statement*> list)
{
    for(auto it = list.begin(); it != list.end(); ++it)
    {
        addStatement(*it);
    }
}

void Block::setRAIIDestructionStatements(vector<Statement*> list)
{
    for(auto it = list.begin(); it != list.end(); ++it)
    {
        addRAIIDestructionStatement(*it);
    }
}

void Block::restore()
{
    for(auto it = m_LocalVariables.begin(); it != m_LocalVariables.end(); ++it)
    {
        (*it)->restore();
    }
    for(auto it = m_Statements.begin(); it != m_Statements.end(); ++it)
    {
        (*it)->restore();
    }
    for(auto it = m_RAIIDestructionStatements.begin(); it != m_RAIIDestructionStatements.end(); ++it)
    {
        (*it)->restore();
    }
}

void Block::elementRemoved( LanguageElement* a_pElement )
{
    Statement::elementRemoved(a_pElement);
    for(auto it = m_LocalVariables.begin(); it != m_LocalVariables.end(); ++it)
    {
        if((*it) == a_pElement)
        {
            *it = nullptr;
            break;
        }
    }
    for(auto it = m_Statements.begin(); it != m_Statements.end(); ++it)
    {
        if((*it) == a_pElement)
        {
            *it = nullptr;
            break;
        }
    }
    for(auto it = m_RAIIDestructionStatements.begin(); it != m_RAIIDestructionStatements.end(); ++it)
    {
        if((*it) == a_pElement)
        {
            *it = nullptr;
            break;
        }
    }
}

void Block::addReturnStatement( const string& a_strExpression )
{
    addStatement(o_new(ReturnStatement)(expressionByName(a_strExpression)));
}

void Block::addReturnStatement()
{
    addStatement(o_new(ReturnStatement));
}

void Block::addReturnStatement( Expression* a_pExpression )
{
    addStatement(o_new(ReturnStatement)(a_pExpression));
}

void Block::addForStatement( Type* a_pInitType, const string& a_strName, Expression* a_pInitExpression, Expression* a_pTest, const vector<Expression*>& a_Updates, Block** a_ppBlock )
{
    addForStatement(o_new(LocalVariable)(a_pInitType, a_strName), a_pInitExpression, a_pTest, a_Updates, a_ppBlock);
}

void Block::addForStatement( const string& a_strInitTestUpdate, Block** a_ppBlock )
{
    vector<string> words;
    split( words, a_strInitTestUpdate, boost::is_any_of(";"), boost::token_compress_on ); // SplitVec == { "hello abc","ABC","aBc goodbye" }

    if(words.size() < 3) 
    {
        if(a_ppBlock) *a_ppBlock = nullptr;
        return;
    }
    
    string init = words[0];
    string test = words[1];
    Type* pType;
    string name;
    Expression* pInitExpression;
    LocalVariable* pLocalVariable = nullptr;
    if(LocalVariable::Parse(init, pType, name, pInitExpression, this))
    {
        if(name.size())
        {
            pLocalVariable = o_new(LocalVariable)(pType, name);
        }
        else 
        {
            o_assert(pInitExpression == nullptr);
        }
    }
    else 
    {
        pInitExpression = expressionByName(init, this);
    }
    vector<Expression*> updates;
    for(size_t i = 2; i<words.size(); ++i)
    {
        updates.push_back(expressionByName(words[i], this));
    }
    addForStatement(pLocalVariable, pInitExpression, expressionByName(test, this), updates, a_ppBlock);
}

void Block::addForStatement( LocalVariable* a_pInitLocalVariable, Expression* a_pInitExpression, Expression* a_pTest, const vector<Expression*>& a_Updates, Block** a_ppBlock )
{
    Block* pForStatement = o_new(Block)(this, "for");

    LabelStatement*     pBreakLabelStatement = o_new(LabelStatement)("break");
    LabelStatement*     pContinueLabelStatement = o_new(LabelStatement)("continue");
    LabelStatement*     pCodeStartLabelStatement = o_new(LabelStatement)("for");

    // Init
    if(a_pInitLocalVariable)
    {
        pForStatement->addLocalVariable(a_pInitLocalVariable);
    }

    if(a_pInitExpression)
    {
        pForStatement->addExpressionStatement(a_pInitExpression);
    }

    // Condition
    Expression* pCondition = a_pTest;
    Expression* pConditionClone = pCondition ? pCondition->clone() : nullptr;

    BranchIfNotStatement* pBranchIfNotStatement = pCondition ? o_new(BranchIfNotStatement)(pCondition) : nullptr;
    if(pBranchIfNotStatement)
    {
        pBranchIfNotStatement->setLabelStatement(pBreakLabelStatement);
    }

    BranchStatement* pBranchIfStatement = pConditionClone 
        ? o_new(BranchIfStatement)(pConditionClone) 
        : o_new(BranchStatement);

    pBranchIfStatement->setLabelStatement(pCodeStartLabelStatement);

    // If test exists, branch to break if test fails
    if(pBranchIfNotStatement)
    {
        pForStatement->addStatement(pBranchIfNotStatement);
    }

    // Code start label
    pForStatement->addStatement(pCodeStartLabelStatement);

    // Code
    if(a_ppBlock)
    {
        *a_ppBlock = o_new(Block)(pForStatement);
    }

    // Updates

    // 'continue' goes here
    pForStatement->addStatement(pContinueLabelStatement);

    // updates
    for(auto it = a_Updates.begin(); it != a_Updates.end(); ++it)
    {
        pForStatement->addExpressionStatement(*it);
    }

    // branch to code if test exists and succeed, or direct branch if test doesn't exist
    pForStatement->addStatement(pBranchIfStatement);

    // 'break' goes here
    pForStatement->addStatement(pBreakLabelStatement);
}

void Block::addWhileStatement( const string& a_strTest, Block** a_ppBlock )
{
    Type* pType;
    string name;
    Expression* pTestExpression;
    LocalVariable* pLocalVariable = nullptr;
    if(LocalVariable::Parse(a_strTest, pType, name, pTestExpression, this))
    {
        if(name.size())
        {
            pLocalVariable = o_new(LocalVariable)(pType, name);
        }
    }
    else 
    {
        pTestExpression = expressionByName(a_strTest, this);
    }
    addWhileStatement(pLocalVariable, pTestExpression, a_ppBlock);
}

void Block::addWhileStatement( Type* a_pInitType, const string& a_strName, Expression* a_pTextExpression, Block** a_ppBlock )
{
    addWhileStatement(o_new(LocalVariable)(a_pInitType, a_strName), a_pTextExpression, a_ppBlock);
}

void Block::addWhileStatement( LocalVariable* a_pLocalVariable, Expression* a_pTextExpression, Block** a_ppBlock )
{
    Block* pWhileStatement = o_new(Block)(this, "while");
    addStatement(pWhileStatement);
    if(a_pLocalVariable)
    {
        pWhileStatement->addLocalVariable(a_pLocalVariable);
    }

    Expression* pCondition = a_pTextExpression;

    if(pCondition)
    {
        if(NOT(pCondition->getValueType()->isConvertibleTo(typeOf<bool>())))
        {
            pWhileStatement->setInvalid();
            // error(node_location(ws.m_condition), "Cannot convert from '%s' to 'bool' in while condition", pCondition->getValueType()->getQualifiedDecoratedName().c_str());
        }
    }
    else 
    {
        pWhileStatement->setInvalid();
        // error(node_location(ws.m_condition), "Invalid while condition");
    }

    Expression* pConditionClone = pCondition ? pCondition->clone() : nullptr;

    LabelStatement*     pBreakLabelStatement = o_new(LabelStatement)("break");
    LabelStatement*     pContinueLabelStatement = o_new(LabelStatement)("continue");
    LabelStatement*     pCodeStartLabelStatement = o_new(LabelStatement)("while");

    BranchIfNotStatement* pBranchIfNotStatement = o_new(BranchIfNotStatement)(pCondition);
    pBranchIfNotStatement->setLabelStatement(pBreakLabelStatement);

    BranchIfStatement* pBranchIfStatement = o_new(BranchIfStatement)(pConditionClone);
    pBranchIfStatement->setLabelStatement(pCodeStartLabelStatement);
    
    // Branch to break if test fails
    pWhileStatement->addStatement(pBranchIfNotStatement);

    // Code start label
    pWhileStatement->addStatement(pCodeStartLabelStatement);

    // Code
    if(a_ppBlock)
    {
        *a_ppBlock = o_new(Block)(pWhileStatement);
    }

    // 'continue' goes here
    pWhileStatement->addStatement(pContinueLabelStatement);

    // branch to code if test succeed
    pWhileStatement->addStatement(pBranchIfStatement);

    // 'break' goes here
    pWhileStatement->addStatement(pBreakLabelStatement);
}

void Block::addIfStatement( const string& a_strTest, Block** a_ppThen, Block** a_ppElse )
{
    Type* pType;
    string name;
    Expression* pTestExpression;
    LocalVariable* pLocalVariable = nullptr;
    if(LocalVariable::Parse(a_strTest, pType, name, pTestExpression, this))
    {
        if(name.size())
        {
            pLocalVariable = o_new(LocalVariable)(pType, name);
        }
        else 
        {
            o_assert(pTestExpression == nullptr);
        }
    }
    else 
    {
        pTestExpression = expressionByName(a_strTest, this);
    }
    addIfStatement(pLocalVariable, pTestExpression, a_ppThen, a_ppElse);
}

void Block::addIfStatement( Type* a_pInitType, const string& a_strName, Expression* a_pTextExpression, Block** a_ppThen, Block** a_ppElse )
{
    addIfStatement(o_new(LocalVariable)(a_pInitType, a_strName), a_pTextExpression, a_ppThen, a_ppElse);
}

void Block::addIfStatement( LocalVariable* a_pLocalVariable, Expression* a_pTextExpression, Block** a_ppThen, Block** a_ppElse )
{
    Block* pIfStatement = o_new(Block)(this, "if");
    addStatement(pIfStatement);
    if(a_pLocalVariable)
    {
        pIfStatement->addLocalVariable(a_pLocalVariable);
    }
    Expression* pCondition = a_pTextExpression;
    if(pCondition == nullptr)
    {
        pIfStatement->setInvalid();
    }
    LabelStatement* pElseLabel = o_new(LabelStatement)("else");
    LabelStatement* pEndLabel = nullptr;
    BranchIfNotStatement* pBranchIfNot = o_new(BranchIfNotStatement)(pCondition);
    pBranchIfNot->setLabelStatement(pElseLabel);
    pIfStatement->addStatement(pBranchIfNot);

    if(a_ppThen)
    {
        *a_ppThen = o_new(Block)(pIfStatement);
    }
    if(a_ppElse)
    {
        // at the end of 'then' part, if 'else' exists, jump to end
        BranchStatement* pBranchToEnd = o_new(BranchStatement);
        pEndLabel = o_new(LabelStatement)("if");
        pBranchToEnd->setLabelStatement(pEndLabel);
        pIfStatement->addStatement(pBranchToEnd);
    }
    pIfStatement->addStatement(pElseLabel);
    if(pEndLabel) // means we have else
    {
        *a_ppElse = o_new(Block)(pIfStatement);
        pIfStatement->addStatement(pEndLabel);
    }
}

void Block::addRAIIDestructionExpressionStatement( Expression* a_pExpression )
{
    m_RAIIDestructionStatements.insert(m_RAIIDestructionStatements.begin(), o_new(ExpressionStatement)(a_pExpression));
}

void Block::getRAIIDestructionStatementsCascade( vector<Statement*>& out ) const
{
    out.insert(out.end(), m_RAIIDestructionStatements.begin(), m_RAIIDestructionStatements.end());
    if(getBlock())
    {
        getBlock()->getRAIIDestructionStatementsCascade(out);
    }
}

void Block::referencedElementRemoved( LanguageElement* a_pElement )
{
    if(a_pElement->asParameter())
    {
        m_LocalVariables.erase(std::find(m_LocalVariables.begin(), m_LocalVariables.end(), a_pElement->asParameter()));
    }
}

o_namespace_end(phantom, reflection)