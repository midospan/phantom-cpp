/* ******************* Includes ****************** */
#include "phantom/qt/qt.h"
#include "UndoStackView.h"
#include "UndoStackView.hxx"
#include "UndoStack.h"
#include "UndoCommand.h"
/* *********************************************** */
o_registerN((phantom, qt), UndoStackView);

namespace phantom { namespace qt {

UndoStackView::UndoStackView( void ) 
: m_pUndoStack(nullptr)
, m_CurrentCommandIcon(":/../../bin/resources/icons/arrow_right.png")
{
    QTreeWidgetItem* pItem = new QTreeWidgetItem;
    pItem->setIcon(0, m_CurrentCommandIcon);
    pItem->setTextAlignment(1, Qt::AlignCenter);
    pItem->setText(1, "origin");
    pItem->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    pItem->setTextColor(1, QColor(64,64,64));
    addTopLevelItem(pItem);
    setColumnCount(2);
    QStringList headerLabels;
    headerLabels.append("");
    headerLabels.append("Command");
    setHeaderLabels(headerLabels);
}

void UndoStackView::setUndoStack( UndoStack* a_pUndoStack )
{
    if(m_pUndoStack == a_pUndoStack) return;
    if(m_pUndoStack)
    {
        disconnect(this, SIGNAL(currentItemChanged(QTreeWidgetItem*, QTreeWidgetItem*)), this, SLOT(slotCurrentItemChanged(QTreeWidgetItem*, QTreeWidgetItem*)));
        for(auto it = m_pUndoStack->beginCommands(); it != m_pUndoStack->endCommands(); ++it)
        {
            undoCommandAboutToBeRemoved(*it);
        }
        o_disconnect(m_pUndoStack, undoCommandAboutToBeRemoved(UndoCommand*), this, undoCommandAboutToBeRemoved(UndoCommand*));
        o_disconnect(m_pUndoStack, undoCommandAdded(UndoCommand*), this, undoCommandAdded(UndoCommand*));
    }
    m_pUndoStack = a_pUndoStack;
    if(m_pUndoStack)
    {
        o_connect(m_pUndoStack, undoCommandAboutToBeRemoved(UndoCommand*), this, undoCommandAboutToBeRemoved(UndoCommand*));
        o_connect(m_pUndoStack, undoCommandAdded(UndoCommand*), this, undoCommandAdded(UndoCommand*));
        for(auto it = m_pUndoStack->beginCommands(); it != m_pUndoStack->endCommands(); ++it)
        {
            undoCommandAdded(*it);
        }
        connect(this, SIGNAL(currentItemChanged(QTreeWidgetItem*, QTreeWidgetItem*)), this, SLOT(slotCurrentItemChanged(QTreeWidgetItem*, QTreeWidgetItem*)));
    }
}

void UndoStackView::undoCommandAdded( UndoCommand* a_pUndoCommand )
{
    o_connect(a_pUndoCommand, childCommandAdded(UndoCommand*), this, undoCommandAdded(UndoCommand*));
    o_connect(a_pUndoCommand, childCommandAboutToBeRemoved(UndoCommand*), this, undoCommandAboutToBeRemoved(UndoCommand*));

    QTreeWidgetItem* pItem = new QTreeWidgetItem;
    pItem->setText(1, a_pUndoCommand->getName().c_str());
    pItem->setData(1, Qt::UserRole, (qulonglong)a_pUndoCommand);

    if(a_pUndoCommand->getParent())
    {
        QTreeWidgetItem* pParentItem = findCommandItem(a_pUndoCommand->getParent());
        o_assert(pParentItem);
        pParentItem->insertChild(a_pUndoCommand->getIndex(), pItem);
        pItem->setFlags(0);
        pItem->setTextColor(1, QColor(200,200,200));
    }
    else 
    {
        insertTopLevelItem(a_pUndoCommand->getIndex()+1, pItem);
        setCurrentItem(pItem);
    }
    for(auto it = a_pUndoCommand->beginChildCommands(); it != a_pUndoCommand->endChildCommands(); ++it)
    {
        undoCommandAdded(*it);
    }
}

void UndoStackView::undoCommandAboutToBeRemoved( UndoCommand* a_pUndoCommand )
{
    for(auto it = a_pUndoCommand->beginChildCommands(); it != a_pUndoCommand->endChildCommands(); ++it)
    {
        undoCommandAboutToBeRemoved(*it);
    }
    if(a_pUndoCommand->getParent())
    {
        QTreeWidgetItem* pParentItem = findCommandItem(a_pUndoCommand->getParent());
        o_assert(pParentItem);
        pParentItem->removeChild(findCommandItem(a_pUndoCommand, pParentItem));
    }
    else 
    {
        takeTopLevelItem(indexOfTopLevelItem(findCommandItem(a_pUndoCommand)));
    }
    o_disconnect(a_pUndoCommand, childCommandAdded(UndoCommand*), this, undoCommandAdded(UndoCommand*));
    o_disconnect(a_pUndoCommand, childCommandAboutToBeRemoved(UndoCommand*), this, undoCommandAboutToBeRemoved(UndoCommand*));
}

QTreeWidgetItem* UndoStackView::findCommandItem( UndoCommand* a_pUndoCommand, QTreeWidgetItem* a_pParentItem /*= nullptr*/ ) const
{
    if(a_pParentItem == nullptr)
    {
        for(int i = 0; i < topLevelItemCount(); ++i)
        {
            QTreeWidgetItem* pItem = topLevelItem(i);
            UndoCommand* pCommand = (UndoCommand*)(pItem->data(1, Qt::UserRole).toULongLong());
            if(pCommand == a_pUndoCommand) return pItem;
            pItem = findCommandItem(a_pUndoCommand, pItem);
            if(pItem) return pItem;
        }
    }
    else 
    {
        for(int i = 0; i < a_pParentItem->childCount(); ++i)
        {
            QTreeWidgetItem* pItem = a_pParentItem->child(i);
            UndoCommand* pCommand = (UndoCommand*)(pItem->data(1, Qt::UserRole).toULongLong());
            if(pCommand == a_pUndoCommand) return pItem;
            pItem = findCommandItem(a_pUndoCommand, pItem);
            if(pItem) return pItem;
        }
    }
    return nullptr;
}

void UndoStackView::slotCurrentItemChanged(QTreeWidgetItem* a_pCurrent, QTreeWidgetItem* a_pPrevious)
{
    if(a_pCurrent == a_pPrevious) 
        return;
    o_assert(a_pCurrent == nullptr OR a_pCurrent->parent() == nullptr);
    o_assert(a_pPrevious == nullptr OR a_pPrevious->parent() == nullptr);
    if(a_pCurrent) a_pCurrent->setIcon(0, m_CurrentCommandIcon);
    if(a_pPrevious) a_pPrevious->setIcon(0, QIcon());
    bool found = false;
    for(int i = 0; i<topLevelItemCount(); ++i)
    {
        QTreeWidgetItem* pItem = topLevelItem(i);
        if(!found)
        {
            if(i != 0)
            {
                pItem->setTextColor(1, QColor(0,0,0));
            }
            if(topLevelItem(i) == a_pCurrent)
            {
                found = true;
                m_pUndoStack->setStackIndex(i-1);
            }
        }
        else
        {
            pItem->setTextColor(1, QColor(150,150,150));
        }
    }
}

}}
