#include <phantom/qt/qt.h>
#include <phantom/qt/AggregationVariableNodeDelegate.h>
#include <phantom/qt/AggregationVariableNodeDelegate.hxx>
#include <phantom/reflection/AggregationClass.h>
#include <phantom/serialization/Node.h>
#include "ExpressionCommand.h"
#include "VariableNode.h"
#include "VariableModel.h"
#include "UndoCommandAction.h"
#include "Menu.h"
#include <QToolBar>
#include <QComboBox>

o_registerN((phantom, qt), AggregationVariableNodeDelegate);
 
namespace phantom { namespace qt {

void AggregationVariableNodeDelegate_fetchData(serialization::Node* pNode, reflection::Type* a_pType, vector<uint>& out)
{
    for(auto it = pNode->beginData(); it != pNode->endData(); ++it)
    {
        if(it->type()->isKindOf(a_pType))
            out.push_back(pNode->getDataBase()->getGuid(*it));
    }
    if(pNode->getParentNode())
    {
        AggregationVariableNodeDelegate_fetchData(pNode->getParentNode(), a_pType, out);
    }
}

void AggregationVariableNodeDelegate::createActions( vector<Action*>& out ) const
{
    serialization::DataBase* pDataBase = m_pVariableNode->getVariableModel()->getDataBase();
    map<uint, UndoCommand*> actionCommands;
    reflection::AggregationClass* pAggregationClass = as<reflection::AggregationClass*>(m_pVariableNode->getValueType()->removeReference()->removeConst());
    
    vector<uint> commonCandidateAggregateGuids;

    for(size_t i = 0; i<m_pVariableNode->getExpressionCount(); ++i)
    {
        phantom::data d = m_pVariableNode->getVariableModel()->getData()[i];
        serialization::Node* pNode = pDataBase->getNode(d);
        vector<uint> candidateAggregateGuids;
        AggregationVariableNodeDelegate_fetchData(pNode, pAggregationClass->getAggregateClass(), candidateAggregateGuids);
        if(i == 0)
        {
            commonCandidateAggregateGuids = candidateAggregateGuids;
        }
        else 
        {
            auto commonCandidateAggregateGuidsCopy = commonCandidateAggregateGuids;
            std::sort(candidateAggregateGuids.begin(), candidateAggregateGuids.end());
            std::sort(commonCandidateAggregateGuidsCopy.begin(), commonCandidateAggregateGuidsCopy.end());
            auto end = std::set_intersection(candidateAggregateGuids.begin(), candidateAggregateGuids.end(), commonCandidateAggregateGuidsCopy.begin(), commonCandidateAggregateGuidsCopy.end(), commonCandidateAggregateGuids.begin());
            commonCandidateAggregateGuids.resize(end-commonCandidateAggregateGuids.begin());
        }
    }

    for(auto it = commonCandidateAggregateGuids.begin(); it != commonCandidateAggregateGuids.end(); ++it)
    {
        actionCommands[*it] = o_new(UndoCommand);
        actionCommands[*it]->setName("Add '" + pDataBase->getDataAttributeValue(pDataBase->getData(*it), "name") + "'");
        actionCommands[*it]->setIcon(QIcon(iconOf(pDataBase->getData(*it).type()).c_str()));
    }

    for(size_t i = 0; i<m_pVariableNode->getExpressionCount(); ++i)
    {
        reflection::Expression* pLeftExpression = m_pVariableNode->getExpression(i);
        reflection::AggregationClass* pAggregationClass = as<reflection::AggregationClass*>(pLeftExpression->getValueType()->removeReference());
        o_assert(pAggregationClass);
        vector<reflection::Class*> derivedClasses;
        vector<reflection::Class*> usableClasses;

        vector<reflection::LanguageElement*> signature;
        void* pAggregation = pLeftExpression->loadEffectiveAddress();
        size_t count = pAggregationClass->count(pAggregation);
        for(auto it = actionCommands.begin(); it != actionCommands.end(); ++it)
        {
            string baseExpression = "(("+pLeftExpression->translate()+")("+lexical_cast<string>(count-1)+"))";
            string undoExpression = baseExpression+"=(0)";
            string redoExpression = baseExpression+"=(&(@("+lexical_cast<string>(it->first)+")))";
            ExpressionCommand* pAggregationAddAggregateDataCommand = o_new(ExpressionCommand)(
                pDataBase
                , undoExpression
                , redoExpression);
            pAggregationAddAggregateDataCommand->setName("Add data");
            it->second->pushCommand(pAggregationAddAggregateDataCommand);
        }
    }
    for(auto it = actionCommands.begin(); it != actionCommands.end(); ++it)
    {
        out.push_back(o_new(UndoCommandAction)(pDataBase->getDataAttributeValue(pDataBase->getData(it->first), "name"), it->second, m_pVariableNode->getVariableModel()->getUndoStack()));
    }
}

Menu* AggregationVariableNodeDelegate::createMenu() const
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

Menu* AggregationVariableNodeDelegate::createAddMenu() const
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

QWidget* AggregationVariableNodeDelegate::createActionWidget() const
{
    vector<Action*> actions;
    createActions(actions);
    if(actions.size())
    {
        QToolBar* pToolBar = new QToolBar;
        pToolBar->setIconSize(QSize(16,16));
        pToolBar->addAction(QIcon(":/../../bin/resources/icons/add.png"), "Add", this, SLOT(popupAddRequested()));
        return pToolBar;
    }
    return nullptr;
}

void AggregationVariableNodeDelegate::popupAddRequested()
{
    Menu* pMenu = createAddMenu();
    if(pMenu)
    {
        connect(pMenu, SIGNAL(triggered(QAction*)), this, SLOT(invalidateNode()));
        pMenu->exec(QCursor::pos());
        o_dynamic_delete pMenu;
    }
}

}}