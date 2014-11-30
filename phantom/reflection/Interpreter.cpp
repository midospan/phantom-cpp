/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include "Interpreter.h"
#include "Interpreter.hxx"
#include <phantom/reflection/LanguageElement.h>
#include "phantom/Message.h"
#include "phantom/reflection/Block.h"
#include "phantom/reflection/LocalVariable.h"
/* *********************************************** */
o_registerN((phantom, reflection), Interpreter);

o_namespace_begin(phantom, reflection) 

Interpreter::Interpreter( void )
    : m_pStack(nullptr)
    , m_pStackPointer(0)
    , m_pBasePointer(0)
{
}

Interpreter::~Interpreter( void )
{
    if(m_pStack)
    {
        o_free(m_pStack);
    }
}

bool Interpreter::call( Subroutine* a_pSubroutine, void** a_ppArgs, size_t a_uiCount, void* a_pReturnAddress )
{
    if(m_pStack == nullptr)
    {
        m_pStack = (byte*)o_malloc(8192);
    }

    byte* pPrevBasePointer = m_pBasePointer;
    byte* pPrevStackPointer = m_pStackPointer;
    if(m_pStackPointer == 0)
    {
        o_assert(pPrevBasePointer == 0);
        o_assert(pPrevStackPointer == 0);
        m_pStackPointer = m_pStack;
    }
    m_pBasePointer = m_pStackPointer;
    Block* pBlock = a_pSubroutine->getBlock();
    size_t count = pBlock->getLocalVariableCount();
    if(a_uiCount != count) 
        return false;
    while(count--)
    {
        LocalVariable* pLocalVariable = pBlock->getLocalVariable(count);
        byte* address = m_pStackPointer + pLocalVariable->getFrameOffset();
        Type* pValueType = pLocalVariable->getValueType();
        pValueType->construct(address);
        pLocalVariable->getValueType()->copy(address, a_ppArgs[count]);
    }
    m_pStackPointer += a_pSubroutine->getFrameSize();
    Statement* pFirstStatement = pBlock->getFirstStatementCascade();
    if(pFirstStatement)
    {
        m_StatementStack.push_back(pFirstStatement);
        m_ReturnAddresses.push_back(a_pReturnAddress);
        while(m_StatementStack.back())
        {
            Statement* pCurrentStatement = m_StatementStack.back();
            pCurrentStatement->eval();
            if(pCurrentStatement == m_StatementStack.back()) // no branch done
            {
                m_StatementStack.back() = m_StatementStack.back()->getNextStatement();
            }
        }
        m_StatementStack.pop_back();
        m_ReturnAddresses.pop_back();
    }
    m_pBasePointer = pPrevBasePointer;
    m_pStackPointer = pPrevStackPointer;
    return true;
}

void Interpreter::setNextStatement( Statement* a_pStatement )
{
    m_StatementStack.back() = a_pStatement;
}


o_namespace_end(phantom, reflection)