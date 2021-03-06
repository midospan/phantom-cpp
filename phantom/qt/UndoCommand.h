#ifndef o_phantom_qt_UndoCommand_h__
#define o_phantom_qt_UndoCommand_h__


/* ****************** Includes ******************* */
#include <phantom/qt/qt.h>
#include <QIcon>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, qt), UndoCommand);
/* *********************************************** */

o_namespace_begin(phantom, qt)

class o_qt_export UndoCommand 
{
    friend class UndoStack;

public:
    enum EChildExecutionPolicy
    {
        e_ChildExecutionPolicy_ForwardAfterParent,
        e_ChildExecutionPolicy_BackwardAfterParent,
        e_ChildExecutionPolicy_ForwardBeforeParent,
        e_ChildExecutionPolicy_BackwardBeforeParent,
    };

public:
    UndoCommand(void);
    UndoCommand(const string& a_strName);
	~UndoCommand(void) {}

    o_terminate()
    {
        if(m_pParent)
        {
            m_pParent->removeCommand(this);
        }
        while(m_ChildCommands.size())
        {
            o_dynamic_delete m_ChildCommands.back();
        }
    }

    void            setName(const string& a_strName) { m_strName = a_strName; }
    const string&   getName() const { return m_strName; }

    void setUndoChildExecutionPolicy(EChildExecutionPolicy a_ePolicy)
    {
        m_eUndoChildExecutionPolicy = a_ePolicy;
    }
    void setRedoChildExecutionPolicy(EChildExecutionPolicy a_ePolicy)
    {
        m_eRedoChildExecutionPolicy = a_ePolicy;
    }

    virtual void undo() {}
    virtual void redo() {}

    void pushCommand(UndoCommand* a_pUndoCommand);

    void popCommand(UndoCommand* a_pUndoCommand);

    virtual bool mergeWith(UndoCommand* a_pCommand) { return false; }

    size_t getIndex() const { return m_uiIndex; }

    UndoCommand* getParent() const { return m_pParent; }

    UndoStack*	getUndoStack() const { return m_pUndoStack; }

    vector<UndoCommand*>::const_iterator beginChildCommands() const { return m_ChildCommands.begin(); }
    vector<UndoCommand*>::const_iterator endChildCommands() const { return m_ChildCommands.end(); }

    UndoCommand* cloneCascade() const;

    QIcon       getIcon() const { return m_Icon; }
    void        setIcon(const QIcon& a_Icon) { m_Icon = a_Icon; }

protected:
    virtual UndoCommand* clone() const;
    void setUndoStack(UndoStack* a_pUndoStack);
    bool internalUndo(bool isAborting = false)
    {
        return internalUndo(m_ChildCommands, true, isAborting);
    }
    bool internalRedo(bool isAborting = false)
    {
        return internalRedo(m_ChildCommands, true, isAborting);
    }
    bool internalUndo(const vector<UndoCommand*>& a_ChildCommands, bool executeThis, bool isAborting);
    bool internalRedo(const vector<UndoCommand*>& a_ChildCommands, bool executeThis, bool isAborting);
    void removeCommand( UndoCommand* a_pUndoCommand );
    void abort();

protected:
    o_signal_data(childCommandAdded, UndoCommand*);
    o_signal_data(childCommandAboutToBeRemoved, UndoCommand*);
    o_signal_data(redone);
    o_signal_data(undone);

protected:
    vector<UndoCommand*>    m_ChildCommands;
    string                  m_strName;
    UndoCommand*            m_pParent;
    UndoStack*              m_pUndoStack;
    size_t                  m_uiIndex;
    EChildExecutionPolicy   m_eUndoChildExecutionPolicy;
    EChildExecutionPolicy   m_eRedoChildExecutionPolicy;
    QIcon                   m_Icon;

private:
    bool m_bAborted;
};

o_namespace_end(phantom, qt)

#endif // o_phantom_qt_UndoCommand_h__
