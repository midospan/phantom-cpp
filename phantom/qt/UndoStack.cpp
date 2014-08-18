/* ******************* Includes ****************** */
#include "phantom/qt/qt.h"
#include "UndoStack.h"
#include "UndoStack.hxx"
#include "UndoCommand.h"
/* *********************************************** */
o_registerN((phantom, qt), UndoStack);

o_namespace_begin(phantom, qt)

UndoStack::UndoStack() 
: m_iStackIndex(-1)
{

}

UndoStack::~UndoStack()
{
    for(auto it = m_UndoCommands.rbegin(); it != m_UndoCommands.rend(); ++it)
    {
        o_dynamic_delete *it;
    }
}

void UndoStack::pushCommand( UndoCommand* a_pUndoCommand )
{
    o_assert(a_pUndoCommand->m_uiIndex == ~size_t(0));
    o_assert(a_pUndoCommand->m_pUndoStack == nullptr);
    o_assert(std::find(m_UndoCommands.begin(), m_UndoCommands.end(), a_pUndoCommand) == m_UndoCommands.end());
    while(m_UndoCommands.size() > (size_t)(m_iStackIndex+1))
    {
        o_emit undoCommandAboutToBeRemoved(m_UndoCommands.back());
        o_dynamic_delete m_UndoCommands.back();
        m_UndoCommands.pop_back();
    }
    a_pUndoCommand->m_uiIndex = m_UndoCommands.size();
    a_pUndoCommand->setUndoStack(this);
    m_UndoCommands.push_back(a_pUndoCommand);
    a_pUndoCommand->internalRedo();
    m_iStackIndex++;
    o_emit undoCommandAdded(a_pUndoCommand);
    o_emit stackIndexChanged(m_iStackIndex);
}


void UndoStack::popCommand( UndoCommand* a_pUndoCommand )
{
    o_assert(m_UndoCommands[a_pUndoCommand->m_uiIndex] == a_pUndoCommand);
    o_assert(a_pUndoCommand->m_pUndoStack == this);
    size_t foundIndex = 0xffffffff;
    o_emit undoCommandAboutToBeRemoved(a_pUndoCommand);
    for(size_t i = 0; i<m_UndoCommands.size()-1; ++i)
    {
        if(m_UndoCommands[i] == a_pUndoCommand)
        {
            foundIndex = i;
            a_pUndoCommand->m_uiIndex = ~size_t(0);
            a_pUndoCommand->setUndoStack(nullptr);
        }
        if(foundIndex != ~size_t(0))
        {
            m_UndoCommands[i] = m_UndoCommands[i+1];
        }
    }
    o_assert(foundIndex != ~size_t(0) OR m_UndoCommands.back() == a_pUndoCommand);
    if(foundIndex == ~size_t(0)) foundIndex = m_UndoCommands.size()-1;
    if(m_iStackIndex >= foundIndex)
        m_iStackIndex--;
    a_pUndoCommand->internalUndo();
    m_UndoCommands.pop_back();
}

void UndoStack::setStackIndex( int index )
{
    if(m_iStackIndex == index) return;
    o_assert(index < (int)m_UndoCommands.size());
    while(m_iStackIndex < index)
    {
        m_iStackIndex++;
        m_UndoCommands[m_iStackIndex]->internalRedo();
        /*for(int i = m_iStackIndex+1; i<(int)m_UndoCommands.size(); ++i)
        {
            m_UndoCommands[i]->previousCommandRedone(m_UndoCommands[m_iStackIndex]);
        }*/
    }
    while(m_iStackIndex > index )
    {
        m_UndoCommands[m_iStackIndex--]->internalUndo();
    }
    o_emit stackIndexChanged(m_iStackIndex);
}

bool UndoStack::isUndoable() const
{
    return m_iStackIndex > -1;
}

bool UndoStack::isRedoable() const
{
    return m_iStackIndex < ((int)m_UndoCommands.size())-1;
}

o_namespace_end(phantom, qt)