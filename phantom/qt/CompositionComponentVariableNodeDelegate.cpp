#include <phantom/qt/qt.h>
#include <phantom/qt/CompositionComponentVariableNodeDelegate.h>
#include <phantom/qt/CompositionComponentVariableNodeDelegate.hxx>
#include <phantom/reflection/CompositionClass.h>
#include "ExpressionCommand.h"
#include "CompositionRemoveComponentDataCommand.h"
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
        pCommand->pushCommand(
            o_new(CompositionRemoveComponentDataCommand)(pDataBase, m_uiIndex, m_pVariableNode->getVariableModel()->getData()[i], pLeftExpression)
            );
    }
    m_pVariableNode->getVariableModel()->getUndoStack()->pushCommand(pCommand);
}

void CompositionComponentVariableNodeDelegate::slotMoveUp()
{
    UndoCommand* pCommand = o_new(UndoCommand)("Move component(s) up");

    for(size_t i = 0; i<m_pVariableNode->getParentNode()->getExpressionCount(); ++i)
    {
        reflection::Expression* pLeftExpression = m_pVariableNode->getParentNode()->getExpression(i);
        string undoExpression = "("+pLeftExpression->translate()+").move("+lexical_cast<string>(m_uiIndex-1)+", "+lexical_cast<string>(m_uiIndex)+")";
        string redoExpression = "("+pLeftExpression->translate()+").move("+lexical_cast<string>(m_uiIndex)+", "+lexical_cast<string>(m_uiIndex-1)+")";
        pCommand->pushCommand(
            o_new(ExpressionCommand)(m_pVariableNode->getVariableModel()->getDataBase()
            , undoExpression
            , redoExpression)
            );
    }
    m_pVariableNode->getVariableModel()->getUndoStack()->pushCommand(pCommand);
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
            reflection::Expression* pLeftExpression = m_pVariableNode->getParentNode()->getExpression(i);
            string undoExpression = "("+pLeftExpression->translate()+").move("+lexical_cast<string>(m_uiIndex+1)+", "+lexical_cast<string>(m_uiIndex)+")";
            string redoExpression = "("+pLeftExpression->translate()+").move("+lexical_cast<string>(m_uiIndex)+", "+lexical_cast<string>(m_uiIndex+1)+")";
            pCommand->pushCommand(
                o_new(ExpressionCommand)(m_pVariableNode->getVariableModel()->getDataBase()
                , undoExpression
                , redoExpression)
                );
        }
    }
    m_pVariableNode->getVariableModel()->getUndoStack()->pushCommand(pCommand);
}

}}