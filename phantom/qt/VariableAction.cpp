/* ******************* Includes ****************** */
#include "phantom/qt/qt.h"
#include "VariableAction.h"
#include "VariableManager.h"
#include "VariableEditor.h"
#include "VariableWidget.h"
#include "VariableWidgetEditor.h"
#include <QLineEdit>
/* *********************************************** */
o_registerN((phantom, qt), VariableAction);
o_registerN((phantom, qt), ResetAction);
o_registerN((phantom, qt), EraseContainerIteratorAction);
o_registerN((phantom, qt), ContainerMoveDownAction);
o_registerN((phantom, qt), ContainerMoveUpAction);

namespace phantom {
namespace qt {

VariableAction::VariableAction(const QIcon& a_Icon, const QString& a_Name, reflection::Variable* a_pVariable, VariableWidget* a_pVariableWidget)
    : QAction(a_Icon, a_Name, a_pVariableWidget)
    , m_pVariable(a_pVariable)
    , m_pVariableWidget(a_pVariableWidget)
{
    connect(this, SIGNAL(triggered()), this, SLOT(slotActionDone()));
}

void VariableAction::slotActionDone()
{
    emit getVariableEditor()->variableAboutToBeAccessed(m_pVariable);
    actionDone();
    emit getVariableEditor()->variableAccessed(m_pVariable);
}

VariableEditor* VariableAction::getVariableEditor() const
{
    return m_pVariableWidget->getVariableEditor();
}

VariableAction::~VariableAction()
{

}

void VariableAction::valueChanged()
{
    getVariableEditor()->variableAboutToBeChanged(m_pVariable);
}

void VariableAction::valueAboutToBeChanged()
{
    getVariableEditor()->variableChanged(m_pVariable);
}

ContainerMoveUpAction::ContainerMoveUpAction(CollectionElementVariable* a_pVariable, VariableWidget* a_pVariableWidget)
    : VariableAction(QIcon(":/../../bin/resources/icons/arrow_up.png"), "Up", a_pVariable, a_pVariableWidget) 
{
}

void ContainerMoveUpAction::actionDone()
{
    VariableEditor* pVariableEditor = m_pVariableWidget->getVariableEditor();
    valueAboutToBeChanged();
    if(static_cast<CollectionElementVariable*>(m_pVariable)->moveUp())
    {
        QtBrowserItem* pCurrentItem = pVariableEditor->getBrowserItem(m_pVariable);
        QtBrowserItem* pPrevItem = pVariableEditor->getBrowserItem(static_cast<CollectionElementVariable*>(m_pVariable)->getPrev());
        pVariableEditor->updateBrowserItem(pPrevItem);
        pVariableEditor->updateBrowserItem(pCurrentItem);
        pVariableEditor->editItem(pPrevItem);
    }
    valueChanged();
}

ContainerMoveDownAction::ContainerMoveDownAction(CollectionElementVariable* a_pVariable, VariableWidget* a_pVariableWidget)
    : VariableAction(QIcon(":/../../bin/resources/icons/arrow_down.png"), "Down", a_pVariable, a_pVariableWidget) 
{
}

void ContainerMoveDownAction::actionDone()
{
    VariableEditor* pVariableEditor = m_pVariableWidget->getVariableEditor();
    valueAboutToBeChanged();
    if(static_cast<CollectionElementVariable*>(m_pVariable)->moveDown())
    {
        QtBrowserItem* pCurrentItem = pVariableEditor->getBrowserItem(m_pVariable);
        QtBrowserItem* pNextItem = pVariableEditor->getBrowserItem(static_cast<CollectionElementVariable*>(m_pVariable)->getNext());
        pVariableEditor->updateBrowserItem(pNextItem);
        pVariableEditor->updateBrowserItem(pCurrentItem);
        pVariableEditor->editItem(pNextItem);
    }
    valueChanged();
}

ResetAction::ResetAction( reflection::Variable* a_pVariable, VariableWidget* a_pEditor ) 
    : VariableAction(QIcon(":/../../bin/resources/icons/arrow_refresh.png"), "Reset", a_pVariable, a_pEditor)
{

}

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

EraseContainerIteratorAction::EraseContainerIteratorAction( phantom::reflection::IteratorVariable* a_pVariable, VariableWidget* a_pVariableWidget ) 
    : VariableAction(QIcon(":/../../bin/resources/icons/delete.png"), "Erase", a_pVariable, a_pVariableWidget)
{

}

void EraseContainerIteratorAction::actionDone()
{
    auto* pIteratorVariable = static_cast<phantom::reflection::IteratorVariable*>(m_pVariable);
    phantom::reflection::ContainerClass* pContainerClass = pIteratorVariable->getContainerClass();
    valueAboutToBeChanged();
    pContainerClass->erase(pIteratorVariable->getContainer(), pIteratorVariable);
    valueChanged();
    getVariableEditor()->reedit();
}

}}