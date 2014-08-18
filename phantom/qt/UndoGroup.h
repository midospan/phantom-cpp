#ifndef o_phantom_qt_UndoGroup_h__
#define o_phantom_qt_UndoGroup_h__


/* ****************** Includes ******************* */
#include <phantom/qt/qt.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, qt), UndoGroup);
/* *********************************************** */

o_namespace_begin(phantom, qt)

class o_qt_export UndoGroup : public UndoCommand, public UndoCommandContainer
{
public:
    void pushCommand(UndoCommand* a_pUndoCommand)
    {
        o_assert(a_pUndoCommand->m_pOwner == nullptr);
        m_UndoCommands.push_back(a_pUndoCommand);
        a_pUndoCommand->m_pOwner = this;
        if (getUndoStack())
            a_pUndoCommand->redo();
    }

    virtual void popCommand(UndoCommand* a_pUndoCommand)
    {
        o_assert(std::find(m_UndoCommands.begin(), m_UndoCommands.end(), a_pUndoCommand) != m_UndoCommands.end());
        if (getUndoStack())
            a_pUndoCommand->undo();
        m_UndoCommands.erase(std::find(m_UndoCommands.begin(), m_UndoCommands.end(), a_pUndoCommand));
        a_pUndoCommand->m_pOwner = nullptr;
    }

    virtual UndoStack*	getUndoStack() const
    {
        if (m_pOwner == nullptr)
            return nullptr;
        return m_pOwner->getUndoStack();
    }

protected:
    virtual void undo() 
    {
        // We need to iterate in reverse order
        for(auto it = m_UndoCommands.rbegin(); it != m_UndoCommands.rend(); ++it)
        {
            (*it)->undo();
        }
    }
    virtual void redo()
    {
        for(auto it = m_UndoCommands.begin(); it != m_UndoCommands.end(); ++it)
        {
            (*it)->redo();
        }
    }

protected:
    vector<UndoCommand*> m_UndoCommands;
};

o_namespace_end(phantom, qt)

#endif // o_phantom_qt_UndoGroup_h__
