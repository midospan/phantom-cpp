/* ******************* Includes ****************** */
#include "phantom/qt/qt.h"
#include "phantom/std/string.h"
#include "VariableAction.h"
#include "VariableAction.hxx"
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

VariableAction::VariableAction(const QIcon& a_Icon, const QString& a_Name, VariableNode* a_pVariable, VariableWidget* a_pVariableWidget)
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

ContainerMoveUpAction::ContainerMoveUpAction(VariableNode* a_pVariable, VariableWidget* a_pVariableWidget)
    : VariableAction(QIcon(":/../../bin/resources/icons/arrow_up.png"), "Up", a_pVariable, a_pVariableWidget) 
{
    o_assert(a_pVariable->getVariableClass()->isKindOf(typeOf<CollectionElementVariable>()));
}

void ContainerMoveUpAction::actionDone()
{
    VariableEditor* pVariableEditor = m_pVariableWidget->getVariableEditor();
    valueAboutToBeChanged();
    bool succeeded = true;
    for(size_t i = 0; i<m_pVariable->getVariableCount(); ++i)
    {
        CollectionElementVariable* pVariable = static_cast<CollectionElementVariable*>(m_pVariable->getVariable(i));
        succeeded = pVariable->moveUp() && succeeded;
    }
    if(succeeded)
    {
        QtBrowserItem* pCurrentItem = pVariableEditor->getBrowserItem(m_pVariable);
        QtBrowserItem* pPrevItem = pVariableEditor->getBrowserItem(m_pVariable->getPrev());
        pVariableEditor->updateBrowserItem(pPrevItem);
        pVariableEditor->updateBrowserItem(pCurrentItem);
        pVariableEditor->editItem(pPrevItem);
    }
    valueChanged();
}

ContainerMoveDownAction::ContainerMoveDownAction(VariableNode* a_pVariable, VariableWidget* a_pVariableWidget)
    : VariableAction(QIcon(":/../../bin/resources/icons/arrow_down.png"), "Down", a_pVariable, a_pVariableWidget) 
{
    o_assert(a_pVariable->getVariableClass()->isKindOf(typeOf<CollectionElementVariable>()));
}

void ContainerMoveDownAction::actionDone()
{
    VariableEditor* pVariableEditor = m_pVariableWidget->getVariableEditor();
    valueAboutToBeChanged();
    bool succeeded = true;
    for(size_t i = 0; i<m_pVariable->getVariableCount(); ++i)
    {
        CollectionElementVariable* pVariable = static_cast<CollectionElementVariable*>(m_pVariable->getVariable(i));
        succeeded = pVariable->moveDown() && succeeded;
    }
    if(succeeded)
    {
        QtBrowserItem* pCurrentItem = pVariableEditor->getBrowserItem(m_pVariable);
        QtBrowserItem* pNextItem = pVariableEditor->getBrowserItem(m_pVariable->getNext());
        pVariableEditor->updateBrowserItem(pNextItem);
        pVariableEditor->updateBrowserItem(pCurrentItem);
        pVariableEditor->editItem(pNextItem);
    }
    valueChanged();
}

ResetAction::ResetAction( VariableNode* a_pVariable, VariableWidget* a_pEditor ) 
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

EraseContainerIteratorAction::EraseContainerIteratorAction( VariableNode* a_pVariable, VariableWidget* a_pVariableWidget ) 
    : VariableAction(QIcon(":/../../bin/resources/icons/delete.png"), "Erase", a_pVariable, a_pVariableWidget)
{

}

void EraseContainerIteratorAction::actionDone()
{
    valueAboutToBeChanged();
    for(size_t i = 0; i<m_pVariable->getVariableCount(); ++i)
    {
        auto* pIteratorVariable = static_cast<phantom::reflection::IteratorVariable*>(m_pVariable->getVariable(i));
        phantom::reflection::ContainerClass* pContainerClass = pIteratorVariable->getContainerClass();
        pContainerClass->erase(pIteratorVariable->getContainer(), pIteratorVariable);
    }
    valueChanged();
    getVariableEditor()->reedit();
}

}}