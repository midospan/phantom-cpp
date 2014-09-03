#include <phantom/qt/qt.h>
#include <phantom/qt/CompositionVariableNodeDelegate.h>
#include <phantom/qt/CompositionVariableNodeDelegate.hxx>
#include <phantom/reflection/CompositionClass.h>
#include <phantom/serialization/Node.h>
#include "CompositionAddComponentDataCommand.h"
#include "UpdateComponentDataCommand.h"
#include "VariableNode.h"
#include "VariableModel.h"
#include "UndoCommandAction.h"
#include "Menu.h"
#include <QToolBar>
#include <QComboBox>

o_registerN((phantom, qt), CompositionVariableNodeDelegate);
 
namespace phantom { namespace qt {

void CompositionVariableNodeDelegate::createActions( vector<Action*>& out ) const
{
    serialization::DataBase* pDataBase = m_pVariableNode->getVariableModel()->getDataBase();
    map<reflection::Class*, UndoCommand*> actionCommands;
    vector<reflection::Class*> derivedClasses;
    reflection::CompositionClass* pCompositionClass = as<reflection::CompositionClass*>(m_pVariableNode->getValueType()->removeReference()->removeConst());
    derivedClasses.push_back(pCompositionClass->getComponentClass());
    pCompositionClass->getComponentClass()->getDerivedClassesCascade(derivedClasses);
    for(auto it = derivedClasses.begin(); it != derivedClasses.end(); ++it)
    {
        reflection::Class* pClass = *it;
        if(pClass->isDefaultConstructible() AND NOT(pClass->isAbstract()))
        {
            actionCommands[pClass] = o_new(UndoCommand);
            actionCommands[pClass]->setName("Add new component '" + nameOf(pClass) + "'");
            actionCommands[pClass]->setIcon(QIcon(iconOf(pClass).c_str()));
        }
    }
    if(actionCommands.size())
    {
        for(size_t i = 0; i<m_pVariableNode->getExpressionCount(); ++i)
        {
            reflection::Expression* pLeftExpression = m_pVariableNode->getExpression(i);
            reflection::CompositionClass* pCompositionClass = as<reflection::CompositionClass*>(pLeftExpression->getValueType()->removeReference());
            o_assert(pCompositionClass);
            vector<reflection::Class*> derivedClasses;
            vector<reflection::Class*> usableClasses;

            vector<reflection::LanguageElement*> signature;
            reflection::Expression* pSizeExpression = pLeftExpression->clone()->solveElement("count", nullptr, &signature)->asExpression();
            bool ok;
            size_t count = pSizeExpression->get().as<size_t>(&ok);
            o_assert(ok);

            for(auto it = actionCommands.begin(); it != actionCommands.end(); ++it)
            {
                UndoCommand* pCommand = o_new(UndoCommand);
                pCommand->setName("Add new component to composition");
                uint guid = pDataBase->rootNode()->generateGuid();
                CompositionAddComponentDataCommand* pCompositionAddComponentDataCommand = o_new(CompositionAddComponentDataCommand)(pDataBase
                    , it->first, guid
                    , m_pVariableNode->getVariableModel()->getData()[i], pLeftExpression);
                pCompositionAddComponentDataCommand->setName("Add new component to composition");
                pCommand->pushCommand(pCompositionAddComponentDataCommand);
                UpdateComponentDataCommand* pUpdateComponentDataCommand = o_new(UpdateComponentDataCommand)(pDataBase, guid);
                pUpdateComponentDataCommand->setName("Auto add missing components");
                pCommand->pushCommand(pUpdateComponentDataCommand);
                it->second->pushCommand(pCommand);
            }
        }
        for(auto it = actionCommands.begin(); it != actionCommands.end(); ++it)
        {
            out.push_back(o_new(UndoCommandAction)(nameOf(it->first), it->second, m_pVariableNode->getVariableModel()->getUndoStack()));
        }
    }
}

Menu* CompositionVariableNodeDelegate::createMenu() const
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

Menu* CompositionVariableNodeDelegate::createAddMenu() const
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

QWidget* CompositionVariableNodeDelegate::createActionWidget() const
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

void CompositionVariableNodeDelegate::popupAddRequested()
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