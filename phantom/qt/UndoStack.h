#ifndef o_phantom_qt_UndoStack_h__
#define o_phantom_qt_UndoStack_h__


/* ****************** Includes ******************* */
#include <phantom/qt/qt.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, qt), UndoStack);
/* *********************************************** */

o_namespace_begin(phantom, qt)

class UndoCommand;

class o_qt_export UndoStack 
{
public:
    UndoStack();
    virtual ~UndoStack();

    virtual UndoStack* asStack() const { return (UndoStack*)this; }

    virtual void pushCommand(UndoCommand* a_pUndoCommand);
    virtual void popCommand(UndoCommand* a_pUndoCommand);

    int getStackIndex() const
    {
        return m_iStackIndex;
    }

    void setStackIndex(int index);

    size_t getSize() const
    {
        return m_UndoCommands.size();
    }

    void redo()
    {
        if(isRedoable())
            setStackIndex(m_iStackIndex+1);
    }

    void undo()
    {
        if(isUndoable())
            setStackIndex(m_iStackIndex-1);
    }

    bool isUndoable() const;
    bool isRedoable() const;

    virtual UndoStack*	getUndoStack() const
    {
        return (UndoStack*)this;
    }

    vector<UndoCommand*>::const_iterator beginCommands() const { return m_UndoCommands.begin(); }
    vector<UndoCommand*>::const_iterator endCommands() const { return m_UndoCommands.end(); }

protected:
    o_signal_data(undoCommandAdded, UndoCommand*);
    o_signal_data(undoCommandAboutToBeRemoved, UndoCommand*);
    o_signal_data(stackIndexChanged, int);

protected:
    vector<UndoCommand*> m_UndoCommands;
    int                  m_iStackIndex;

};

o_namespace_end(phantom, qt)

#endif // o_phantom_qt_UndoStack_h__
