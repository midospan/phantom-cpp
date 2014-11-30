#ifndef o_qt_UndoCommandAction_h__
#define o_qt_UndoCommandAction_h__

/* ****************** Includes ******************* */
#include "Action.h"
/* **************** Declarations ***************** */
o_declareN(class, (phantom, qt), UndoCommandAction);
/* *********************************************** */

namespace phantom { namespace qt {

class VariableEditor;
class VariableNode;
class UndoCommand;
class UndoStack;

class o_qt_export UndoCommandAction : public Action
{
    friend class VariableNode;

public:
    UndoCommandAction(const string& a_strQualifiedName, UndoCommand* a_pCommand, UndoStack* a_pUndoStack);
    ~UndoCommandAction();

    virtual void doAction();

protected:
    string                  m_strName;
    UndoCommand*            m_pUndoCommand;
    UndoStack*              m_pUndoStack;
};
/*

class o_qt_export ResetAction : public UndoCommandAction
{
public:
    ResetAction();

protected:
    virtual void actionDone();
};
*/

}}

#endif // o_qt_UndoCommandAction_h__
