#include <phantom/qt/qt.h>
#include <phantom/qt/AggregationAggregateVariableNodeDelegate.h>
#include <phantom/qt/AggregationAggregateVariableNodeDelegate.hxx>
#include <phantom/reflection/AggregationClass.h>
#include "ExpressionCommand.h"
#include "VariableNode.h"
#include "UndoStack.h"
#include "VariableModel.h"
#include "UndoCommandAction.h"
#include "Menu.h"
#include <QToolBar>
#include <QComboBox>

o_registerN((phantom, qt), AggregationAggregateVariableNodeDelegate);
 
namespace phantom { namespace qt {

void AggregationAggregateVariableNodeDelegate::createActions( vector<Action*>& out ) const
{
    
}

Menu* AggregationAggregateVariableNodeDelegate::createMenu() const
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

Menu* AggregationAggregateVariableNodeDelegate::createAddMenu() const
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

QWidget* AggregationAggregateVariableNodeDelegate::createActionWidget() const
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

void AggregationAggregateVariableNodeDelegate::slotRemove()
{
    UndoCommand* pCommand = o_new(UndoCommand)("Remove aggregate(s)");

    for(size_t i = 0; i<m_pVariableNode->getParentNode()->getExpressionCount(); ++i)
    {
        reflection::Expression* pLeftExpression = m_pVariableNode->getParentNode()->getExpression(i);
        reflection::AggregationClass* pAggregationClass = as<reflection::AggregationClass*>(pLeftExpression->getValueType()->removeReference()->removeConst());
        serialization::DataBase* pDataBase = m_pVariableNode->getVariableModel()->getDataBase();
        void* pAggregate = nullptr;
        pAggregationClass->get(pLeftExpression->loadEffectiveAddress(), m_uiIndex, &pAggregate);
        string undoExpression = "(("+pLeftExpression->getName()+")("+lexical_cast<string>(m_uiIndex)+")) = 0";
        uint guid = pDataBase->getGuid(pAggregate);
        o_assert(guid != 0xffffffff);
        string redoExpression = "(("+pLeftExpression->getName()+")("+lexical_cast<string>(m_uiIndex)+")) = (&(@("+lexical_cast<string>(guid)+")))";
        pCommand->pushCommand(
            o_new(ExpressionCommand)(pDataBase, undoExpression, redoExpression)
            );
    }
    m_pVariableNode->getVariableModel()->getUndoStack()->pushCommand(pCommand);
    invalidateNode();
}

void AggregationAggregateVariableNodeDelegate::slotMoveUp()
{
    UndoCommand* pCommand = o_new(UndoCommand)("Move reference(s) up");

    for(size_t i = 0; i<m_pVariableNode->getParentNode()->getExpressionCount(); ++i)
    {
        reflection::Expression* pLeftExpression = m_pVariableNode->getParentNode()->getExpression(i);
        string undoExpression = "("+pLeftExpression->getName()+").move("+lexical_cast<string>(m_uiIndex-1)+", "+lexical_cast<string>(m_uiIndex)+")";
        string redoExpression = "("+pLeftExpression->getName()+").move("+lexical_cast<string>(m_uiIndex)+", "+lexical_cast<string>(m_uiIndex-1)+")";
        pCommand->pushCommand(
            o_new(ExpressionCommand)(m_pVariableNode->getVariableModel()->getDataBase()
                , undoExpression
                , redoExpression)
            );
    }
    m_pVariableNode->getVariableModel()->getUndoStack()->pushCommand(pCommand);
    invalidateNode();
}

void AggregationAggregateVariableNodeDelegate::slotMoveDown()
{
    UndoCommand* pCommand = o_new(UndoCommand)("Move reference(s) down");

    for(size_t i = 0; i<m_pVariableNode->getParentNode()->getExpressionCount(); ++i)
    {
        reflection::Expression* pLeftExpression = m_pVariableNode->getParentNode()->getExpression(i);
        reflection::AggregationClass* pAggregationClass = as<reflection::AggregationClass*>(pLeftExpression->getValueType()->removeReference()->removeConst());
        size_t count = pAggregationClass->count(pLeftExpression->loadEffectiveAddress());
        if(m_uiIndex < count-1)
        {
            reflection::Expression* pLeftExpression = m_pVariableNode->getParentNode()->getExpression(i);
            string undoExpression = "("+pLeftExpression->getName()+").move("+lexical_cast<string>(m_uiIndex+1)+", "+lexical_cast<string>(m_uiIndex)+")";
            string redoExpression = "("+pLeftExpression->getName()+").move("+lexical_cast<string>(m_uiIndex)+", "+lexical_cast<string>(m_uiIndex+1)+")";
            pCommand->pushCommand(
                o_new(ExpressionCommand)(m_pVariableNode->getVariableModel()->getDataBase()
                , undoExpression
                , redoExpression)
                );
        }
    }
    m_pVariableNode->getVariableModel()->getUndoStack()->pushCommand(pCommand);
    invalidateNode();
}

}}