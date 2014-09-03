#include <phantom/qt/qt.h>
#include <phantom/qt/CompositionComponentVariableNodeDelegate.h>
#include <phantom/qt/CompositionComponentVariableNodeDelegate.hxx>
#include <phantom/reflection/CompositionClass.h>
#include "CompositionAddComponentDataCommand.h"
#include "CompositionMoveComponentDataCommand.h"
#include "MoveToTrashbinCommand.h"
#include "VariableNode.h"
#include "UndoStack.h"
#include "VariableModel.h"
#include "UndoCommandAction.h"
#include "Menu.h"
#include <QToolBar>
#include <QComboBox>

o_registerN((phantom, qt), CompositionComponentVariableNodeDelegate);
 
namespace phantom { namespace qt {

void CompositionComponentVariableNodeDelegate::createActions( vector<Action*>& out ) const
{
    
}

Menu* CompositionComponentVariableNodeDelegate::createMenu() const
{
    Menu* pMenuAdd = createAddMenu();
    if(pMenuAdd)
    {
        Menu* pMenu = o_new(Menu);
        pMenu->addMenu(pMenuAdd);
        return pMenu;
    }
    return nullptr;
}

Menu* CompositionComponentVariableNodeDelegate::createAddMenu() const
{
    vector<Action*> actions;
    createActions(actions);
    if(actions.size())
    {
        Menu* pMenuAdd = o_new(Menu)(QIcon(":/../../bin/resources/icons/add.png"), "Add");
        for(auto it = actions.begin(); it != actions.end(); ++it)
        {
            pMenuAdd->addAction(*it);
        }
        return pMenuAdd;
    }
    return nullptr;
}

QWidget* CompositionComponentVariableNodeDelegate::createActionWidget() const
{
    QToolBar* pToolBar = new QToolBar;
    pToolBar->setIconSize(QSize(16,16));
    QAction* pAction = pToolBar->addAction(QIcon(":/../../bin/resources/icons/arrow_up.png"), "Move Up", this, SLOT(slotMoveUp()));
    pAction->setEnabled(m_uiIndex > 0);
    pAction = pToolBar->addAction(QIcon(":/../../bin/resources/icons/arrow_down.png"), "Move Down", this, SLOT(slotMoveDown()));
    pAction->setEnabled(m_uiIndex < m_uiCount-1);
    pToolBar->addAction(QIcon(":/../../bin/resources/icons/delete.png"), "Remove and destroy", this, SLOT(slotRemove()));
    return pToolBar;
}

void CompositionComponentVariableNodeDelegate::slotRemove()
{
    UndoCommand* pCommand = o_new(UndoCommand)("Remove component(s)");

    for(size_t i = 0; i<m_pVariableNode->getParentNode()->getExpressionCount(); ++i)
    {
        reflection::Expression* pLeftExpression = m_pVariableNode->getParentNode()->getExpression(i);
        reflection::CompositionClass* pCompositionClass = as<reflection::CompositionClass*>(pLeftExpression->getValueType()->removeReference()->removeConst());
        serialization::DataBase* pDataBase = m_pVariableNode->getVariableModel()->getDataBase();
        void* pAddress = nullptr;
        pCompositionClass->get(pLeftExpression->loadEffectiveAddress(), m_uiIndex, &pAddress);
        vector<uint> guids;
        guids.push_back(pDataBase->getGuid(pAddress));
        pCommand->pushCommand(
            o_new(MoveToTrashbinCommand)(pDataBase, guids)
            );
    }
    m_pVariableNode->getVariableModel()->getUndoStack()->pushCommand(pCommand);
    o_connect(pCommand, redone(), m_pVariableNode->getVariableModel(), reset());
    o_connect(pCommand, undone(), m_pVariableNode->getVariableModel(), reset());
    invalidateNode();
}

void CompositionComponentVariableNodeDelegate::slotMoveUp()
{
    UndoCommand* pCommand = o_new(UndoCommand)("Move component(s) up");

    for(size_t i = 0; i<m_pVariableNode->getParentNode()->getExpressionCount(); ++i)
    {
        reflection::Expression* pLeftExpression = m_pVariableNode->getParentNode()->getExpression(i);
        pCommand->pushCommand(
            o_new(CompositionMoveComponentDataCommand)(m_pVariableNode->getVariableModel()->getDataBase()
                , m_pVariableNode->getVariableModel()->getData()[i]
                , pLeftExpression
                , m_uiIndex
                , m_uiIndex-1)
            );
    }
    m_pVariableNode->getVariableModel()->getUndoStack()->pushCommand(pCommand);
    o_connect(pCommand, redone(), m_pVariableNode->getVariableModel(), reset());
    o_connect(pCommand, undone(), m_pVariableNode->getVariableModel(), reset());
    invalidateNode();
}

void CompositionComponentVariableNodeDelegate::slotMoveDown()
{
    UndoCommand* pCommand = o_new(UndoCommand)("Move component(s) down");

    for(size_t i = 0; i<m_pVariableNode->getParentNode()->getExpressionCount(); ++i)
    {
        reflection::Expression* pLeftExpression = m_pVariableNode->getParentNode()->getExpression(i);
        reflection::CompositionClass* pCompositionClass = as<reflection::CompositionClass*>(pLeftExpression->getValueType()->removeReference()->removeConst());
        size_t count = pCompositionClass->count(pLeftExpression->loadEffectiveAddress());
        if(m_uiIndex < count-1)
        {
            pCommand->pushCommand(
                o_new(CompositionMoveComponentDataCommand)(m_pVariableNode->getVariableModel()->getDataBase()
                , m_pVariableNode->getVariableModel()->getData()[i]
            , pLeftExpression
                , m_uiIndex
                , m_uiIndex+1)
                );
        }
    }
    m_pVariableNode->getVariableModel()->getUndoStack()->pushCommand(pCommand);
    o_connect(pCommand, redone(), m_pVariableNode->getVariableModel(), reset());
    o_connect(pCommand, undone(), m_pVariableNode->getVariableModel(), reset());
    invalidateNode();
}

}}