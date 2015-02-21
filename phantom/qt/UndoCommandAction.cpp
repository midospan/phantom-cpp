/* ******************* Includes ****************** */
#include "phantom/qt/qt.h"
#include "phantom/string.h"
#include "UndoCommandAction.h"
#include "UndoCommandAction.hxx"
#include "VariableModel.h"
#include "VariableNode.h"
#include "VariableEditor.h"
#include "VariableWidget.h"
#include "UndoStack.h"
#include "UndoCommand.h"
#include "VariableWidgetEditor.h"
#include <phantom/reflection/CallExpression.h>
#include <QLineEdit>
/* *********************************************** */
o_registerN((phantom, qt), UndoCommandAction);

namespace phantom {
namespace qt {

UndoCommandAction::UndoCommandAction(const string& a_strName, UndoCommand* a_pUndoCommand, UndoStack* a_pUndoStack)
    : Action(a_pUndoCommand->getIcon(), a_strName.c_str())
    , m_strName(a_strName)
    , m_pUndoStack(a_pUndoStack)
    , m_pUndoCommand(a_pUndoCommand)
{
    o_assert(m_pUndoCommand);
    o_assert(m_pUndoStack);
}

UndoCommandAction::~UndoCommandAction()
{
    o_dynamic_delete m_pUndoCommand;
}

void UndoCommandAction::doAction()
{
    m_pUndoStack->pushCommand(m_pUndoCommand->cloneCascade()); 
}

}}