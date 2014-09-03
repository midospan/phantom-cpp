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
    , m_bAborted(false)
{

}

UndoCommand::UndoCommand( const string& a_strName )  
    : m_pParent(nullptr), m_pUndoStack(nullptr), m_uiIndex(~size_t(0))
    , m_eRedoChildExecutionPolicy(e_ChildExecutionPolicy_ForwardAfterParent)
    , m_eUndoChildExecutionPolicy(e_ChildExecutionPolicy_BackwardBeforeParent)
    , m_bAborted(false)
{
    setName(a_strName);
}

void UndoCommand::pushCommand( UndoCommand* a_pUndoCommand )
{
    o_assert(a_pUndoCommand->m_pParent == nullptr AND (
        (getUndoStack() == nullptr) OR (m_eRedoChildExecutionPolicy < e_ChildExecutionPolicy_ForwardBeforeParent))
        );
    a_pUndoCommand->m_uiIndex = m_ChildCommands.size();
    m_ChildCommands.push_back(a_pUndoCommand);
    a_pUndoCommand->m_pParent = this;
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

class blabla
{
public:
    operator int()
    {
        return 0;
    }
};

bool UndoCommand::internalUndo(const vector<UndoCommand*>& childCommands, bool executeThis, bool isAborting)
{
    m_bAborted = false;
    vector<UndoCommand*> executed;
    switch(m_eUndoChildExecutionPolicy)
    {
    case e_ChildExecutionPolicy_BackwardAfterParent:
        {
            if(executeThis) undo();
            if(m_bAborted) 
            {
                o_error(!isAborting, "Failed on aborting");
                return false;
            }
            size_t i = childCommands.size();
            while(i--)
            {
                if(!childCommands[i]->internalUndo(isAborting))
                {
                    o_error(!isAborting, "Failed on aborting");
                    std::reverse(executed.begin(), executed.end());
                    internalRedo(executed, true, true);
                    return false;
                }
                executed.push_back(childCommands[i]);
            }
        }
        break;
    case e_ChildExecutionPolicy_BackwardBeforeParent:
        {
            size_t i = childCommands.size(); 
            while(i--)
            {
                if(!childCommands[i]->internalUndo(isAborting))
                {
                    o_error(!isAborting, "Failed on aborting");
                    std::reverse(executed.begin(), executed.end());
                    internalRedo(executed, false, true);
                    return false;
                }
                executed.push_back(childCommands[i]);
            }
            if(executeThis) undo();
            if(m_bAborted) 
            {
                o_error(!isAborting, "Failed on aborting");
                std::reverse(executed.begin(), executed.end());
                internalRedo(executed, false, true);
                return false;
            }
        }
        break;
    case e_ChildExecutionPolicy_ForwardAfterParent:
        {
            if(executeThis) undo();
            if(m_bAborted) 
            {
                o_error(!isAborting, "Failed on aborting");
                return false;
            }
            for(size_t i = 0; i<childCommands.size(); ++i)
            {
                if(!childCommands[i]->internalUndo(isAborting))
                {
                    o_error(!isAborting, "Failed on aborting");
                    internalRedo(executed, true, true);
                    return false;
                }
                executed.push_back(childCommands[i]);
            }
        }
        break;
    case e_ChildExecutionPolicy_ForwardBeforeParent:
        {
            for(size_t i = 0; i<childCommands.size(); ++i)
            {
                if(!childCommands[i]->internalUndo(isAborting))
                {
                    o_error(!isAborting, "Failed on aborting");
                    internalRedo(executed, false, true);
                    return false;
                }
                executed.push_back(childCommands[i]);
            }
            if(executeThis) undo();
            if(m_bAborted) 
            {
                o_error(!isAborting, "Failed on aborting");
                internalRedo(executed, false, true);
                return false;
            }
        }
        break;
    }
    o_emit undone();
    return true;
}


bool UndoCommand::internalRedo(const vector<UndoCommand*>& childCommands, bool executeThis, bool isAborting)
{
    m_bAborted = false;
    vector<UndoCommand*> executed;
    switch(m_eRedoChildExecutionPolicy)
    {
    case e_ChildExecutionPolicy_BackwardAfterParent:
        {
            if(executeThis) redo();
            if(m_bAborted) 
            {
                o_error(!isAborting, "Failed on aborting");
                return false;
            }
            size_t i = childCommands.size(); 
            while(i--)
            {
                if(!childCommands[i]->internalRedo(isAborting))
                {
                    o_error(!isAborting, "Failed on aborting");
                    std::reverse(executed.begin(), executed.end());
                    internalUndo(executed, true, true);
                    return false;
                }
                executed.push_back(childCommands[i]);
            }
        }
        break;
    case e_ChildExecutionPolicy_BackwardBeforeParent:
        {
            size_t i = childCommands.size();
            while(i--)
            {
                if(!childCommands[i]->internalRedo(isAborting))
                {
                    o_error(!isAborting, "Failed on aborting");
                    std::reverse(executed.begin(), executed.end());
                    internalUndo(executed, false, true);
                    return false;
                }
                executed.push_back(childCommands[i]);
            }
            if(executeThis) redo();
            if(m_bAborted) 
            {
                o_error(!isAborting, "Failed on aborting");
                std::reverse(executed.begin(), executed.end());
                internalUndo(executed, false, true);
                return false;
            }
        }
        break;
    case e_ChildExecutionPolicy_ForwardAfterParent:
        {
            if(executeThis) redo();
            if(m_bAborted) 
            {
                o_error(!isAborting, "Failed on aborting");
                return false;
            }
            for(size_t i = 0; i<childCommands.size(); ++i)
            {
                if(!childCommands[i]->internalRedo(isAborting))
                {
                    o_error(!isAborting, "Failed on aborting");
                    internalUndo(executed, true, true);
                    return false;
                }
                executed.push_back(childCommands[i]);
            }
        }
        break;
    case e_ChildExecutionPolicy_ForwardBeforeParent:
        {
            for(size_t i = 0; i<childCommands.size(); ++i)
            {
                if(!childCommands[i]->internalRedo(isAborting))
                {
                    o_error(!isAborting, "Failed on aborting");
                    internalUndo(executed, false, true);
                    return false;
                }
                executed.push_back(childCommands[i]);
            }
            if(executeThis) redo();
            if(m_bAborted) 
            {
                o_error(!isAborting, "Failed on aborting");
                internalUndo(executed, false, true);
                return false;
            }
        }
        break;
    }
    o_emit redone();
    return true;
}

void UndoCommand::abort()
{
    m_bAborted = true;
}

UndoCommand* UndoCommand::cloneCascade() const
{
    UndoCommand* pUndoCommand = clone();
    for(auto it = m_ChildCommands.begin(); it != m_ChildCommands.end(); ++it)
    {
        pUndoCommand->pushCommand((*it)->cloneCascade());
    }
    pUndoCommand->setRedoChildExecutionPolicy(m_eRedoChildExecutionPolicy);
    pUndoCommand->setUndoChildExecutionPolicy(m_eUndoChildExecutionPolicy);
    return pUndoCommand;
}

UndoCommand* UndoCommand::clone() const
{
    return o_new(UndoCommand)(m_strName);
}

o_namespace_end(phantom, qt)

