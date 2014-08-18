/* ******************* Includes ****************** */
#include "phantom/qt/qt.h"
#include "UndoCommand.h"
#include "UndoCommand.hxx"
/* *********************************************** */
o_registerN((phantom, qt), UndoCommand);

o_namespace_begin(phantom, qt)

UndoCommand::UndoCommand( void ) 
: m_pParent(nullptr), m_pUndoStack(nullptr), m_uiIndex(~size_t(0))
, m_eRedoChildExecutionPolicy(e_ChildExecutionPolicy_ForwardAfterParent)
, m_eUndoChildExecutionPolicy(e_ChildExecutionPolicy_BackwardBeforeParent)
{

}

UndoCommand::UndoCommand( const string& a_strName )  
    : m_pParent(nullptr), m_pUndoStack(nullptr), m_uiIndex(~size_t(0))
    , m_eRedoChildExecutionPolicy(e_ChildExecutionPolicy_ForwardAfterParent)
    , m_eUndoChildExecutionPolicy(e_ChildExecutionPolicy_BackwardBeforeParent)
{
    setName(a_strName);
}

void UndoCommand::pushCommand( UndoCommand* a_pUndoCommand )
{
    o_assert(a_pUndoCommand->m_pParent == nullptr);
    a_pUndoCommand->m_uiIndex = m_ChildCommands.size();
    m_ChildCommands.push_back(a_pUndoCommand);
    a_pUndoCommand->m_pParent = this;
    if (getUndoStack())
        a_pUndoCommand->redo();
    if(m_pUndoStack)
    {
        a_pUndoCommand->setUndoStack(m_pUndoStack);
    }

    o_emit childCommandAdded(a_pUndoCommand);
}

void UndoCommand::removeCommand( UndoCommand* a_pUndoCommand )
{
    o_assert(a_pUndoCommand->m_pParent == this);
    o_assert(std::find(m_ChildCommands.begin(), m_ChildCommands.end(), a_pUndoCommand) != m_ChildCommands.end());

    o_emit childCommandAboutToBeRemoved(a_pUndoCommand);

    m_ChildCommands.erase(std::find(m_ChildCommands.begin(), m_ChildCommands.end(), a_pUndoCommand));
    a_pUndoCommand->m_pParent = nullptr;
    a_pUndoCommand->m_uiIndex = ~size_t(0);
    if(m_pUndoStack)
    {
        a_pUndoCommand->setUndoStack(nullptr);
    }
}

void UndoCommand::popCommand( UndoCommand* a_pUndoCommand )
{
    o_assert(a_pUndoCommand->m_pParent == this);
    o_assert(std::find(m_ChildCommands.begin(), m_ChildCommands.end(), a_pUndoCommand) != m_ChildCommands.end());

    o_emit childCommandAboutToBeRemoved(a_pUndoCommand);

    if (getUndoStack())
        a_pUndoCommand->undo();
    m_ChildCommands.erase(std::find(m_ChildCommands.begin(), m_ChildCommands.end(), a_pUndoCommand));
    a_pUndoCommand->m_pParent = nullptr;
    a_pUndoCommand->m_uiIndex = ~size_t(0);
    if(m_pUndoStack)
    {
        a_pUndoCommand->setUndoStack(nullptr);
    }
}

void UndoCommand::setUndoStack( UndoStack* a_pUndoStack )
{
    o_assert((m_pUndoStack == nullptr) != (a_pUndoStack == nullptr)); 
    m_pUndoStack = a_pUndoStack;
    for(auto it = m_ChildCommands.begin(); it != m_ChildCommands.end(); ++it)
    {
        (*it)->setUndoStack(a_pUndoStack);
    }
}

void UndoCommand::internalUndo()
{
    // We need to iterate in reverse order
    switch(m_eUndoChildExecutionPolicy)
    {
    case e_ChildExecutionPolicy_BackwardAfterParent:
        {
            undo();
            for(auto it = m_ChildCommands.rbegin(); it != m_ChildCommands.rend(); ++it)
            {
                (*it)->internalUndo();
            }
        }
        break;
    case e_ChildExecutionPolicy_BackwardBeforeParent:
        {
            for(auto it = m_ChildCommands.rbegin(); it != m_ChildCommands.rend(); ++it)
            {
                (*it)->internalUndo();
            }
            undo();
        }
        break;
    case e_ChildExecutionPolicy_ForwardAfterParent:
        {
            undo();
            for(auto it = m_ChildCommands.begin(); it != m_ChildCommands.end(); ++it)
            {
                (*it)->internalUndo();
            }
        }
        break;
    case e_ChildExecutionPolicy_ForwardBeforeParent:
        {
            for(auto it = m_ChildCommands.begin(); it != m_ChildCommands.end(); ++it)
            {
                (*it)->internalUndo();
            }
            undo();
        }
        break;
    }
    o_emit undone();
}

void UndoCommand::internalRedo()
{
    // We need to iterate in reverse order
    switch(m_eRedoChildExecutionPolicy)
    {
    case e_ChildExecutionPolicy_BackwardAfterParent:
        {
            redo();
            for(auto it = m_ChildCommands.rbegin(); it != m_ChildCommands.rend(); ++it)
            {
                (*it)->internalRedo();
            }
        }
        break;
    case e_ChildExecutionPolicy_BackwardBeforeParent:
        {
            for(auto it = m_ChildCommands.rbegin(); it != m_ChildCommands.rend(); ++it)
            {
                (*it)->internalRedo();
            }
            redo();
        }
        break;
    case e_ChildExecutionPolicy_ForwardAfterParent:
        {
            redo();
            for(auto it = m_ChildCommands.begin(); it != m_ChildCommands.end(); ++it)
            {
                (*it)->internalRedo();
            }
        }
        break;
    case e_ChildExecutionPolicy_ForwardBeforeParent:
        {
            for(auto it = m_ChildCommands.begin(); it != m_ChildCommands.end(); ++it)
            {
                (*it)->internalRedo();
            }
            redo();
        }
        break;
    }
    o_emit redone();
}

o_namespace_end(phantom, qt)

