/* ******************* Includes ****************** */
#include "phantom/qt/qt.h"
#include "phantom/std/string.h"
#include "VariableAction.h"
#include "VariableAction.hxx"
#include "VariableModel.h"
#include "VariableEditor.h"
#include "VariableWidget.h"
#include "VariableWidgetEditor.h"
#include <phantom/reflection/CallExpression.h>
#include <QLineEdit>
/* *********************************************** */
o_registerN((phantom, qt), VariableAction);

namespace phantom {
namespace qt {

VariableAction::VariableAction(const QIcon& a_Icon, const QString& a_Name, EVariableActionLayout a_Layout, VariableNode* a_pVariableNode, VariableEditor* a_pVariableEditor)
    : QAction(a_Icon, a_Name, (QtTreePropertyBrowser*)a_pVariableEditor)
    , m_pVariableNode(a_pVariableNode)
    , m_Layout(a_Layout)
{
    connect(this, SIGNAL(triggered()), this, SLOT(slotTriggered()));
}

void VariableAction::slotTriggered()
{
    o_emit actionAboutToBeDone();
    doNow();
    o_emit actionDone();
}

VariableEditor* VariableAction::getVariableEditor() const
{
    return static_cast<VariableEditor*>((QtTreePropertyBrowser*)parent());
}

VariableAction::~VariableAction()
{

}

void VariableAction::doNow()
{
}
/*
void ResetAction::actionDone()
{
    void* pBufferDefault = m_pVariable->getValueType()->newInstance();
    m_pVariable->getRange()->getDefault(pBufferDefault);
    VariableWidgetEditor* pEditor = m_pVariableWidget->getVariableWidgetEditor();
    pEditor->setValue(pBufferDefault);
    m_pVariable->getValueType()->deleteInstance(pBufferDefault);
    pEditor->getWidget()->setFocus();
    QLineEdit* pLineEdit;
    if(pLineEdit = qobject_cast<QLineEdit*>(pEditor->getWidget()))
        pLineEdit->selectAll();
}
*/

}}