#include <phantom/qt/qt.h>
#include <phantom/qt/ComponentVariableNodeDelegate.h>
#include <phantom/qt/ComponentVariableNodeDelegate.hxx>
#include <phantom/reflection/ComponentClass.h>
#include "VariableNode.h"
#include "VariableModel.h"
#include "ExpressionCommand.h"
#include "ClassComboBoxEditor.h"

o_registerN((phantom, qt), ComponentVariableNodeDelegate);
 
namespace phantom { namespace qt {

UndoCommand* ComponentVariableNodeDelegate::createValueSetUndoCommand( const void* a_pValue ) const
{
    string newValueStr;
    string newValueDisplayStr;
    vector<string> newValueStrs;
    reflection::ComponentClass* pComponentClass = m_pVariableNode->getValueType()->removeConstReference()->asComponentClass();
    VariableModel* pVariableModel = m_pVariableNode->getVariableModel();
    serialization::DataBase* pDataBase = pVariableModel->getDataBase();

    UndoCommand* pGroup = o_new(phantom::qt::UndoCommand);

    void* pNewValue = *((void* const*)a_pValue);

    reflection::Class* pNewClass = nullptr;
    if(pNewValue)
    {
        pNewClass = as<reflection::Class*>(pNewValue);
        o_assert(pNewClass);
    }
    size_t count = m_pVariableNode->getExpressionCount();
    for(size_t i = 0; i<count; ++i)
    {
        phantom::data d = pVariableModel->getData()[i];
        void* pValue = nullptr;
        string tempRedoExpression;
        string redoExpression;
        string undoExpression;
        string baseExpression = m_pVariableNode->getExpression(i)->getName();
        void* pOldValue = nullptr;
        pComponentClass->get(m_pVariableNode->getExpression(i)->loadEffectiveAddress(), &pOldValue);
        if(pOldValue)
        {
            auto pOldClass = classOf(pOldValue);
            o_assert(pOldClass);
            string newInstanceExpression = "phantom::typeByName(\""+pOldClass->getQualifiedDecoratedName()+"\", phantom::rootNamespace())->newInstance()";
            undoExpression = "("+baseExpression+")=(("+pOldClass->getQualifiedDecoratedName()+"*)("+newInstanceExpression+"))";
        }
        else 
        {
            undoExpression = "("+baseExpression+")=nullptr";
        }
        if(pNewClass)
        {
            string newInstanceExpression = "phantom::typeByName(\""+pNewClass->getQualifiedDecoratedName()+"\", phantom::rootNamespace())->newInstance()";
            redoExpression = "("+baseExpression+")=(("+pNewClass->getQualifiedDecoratedName()+"*)("+newInstanceExpression+"))";
        }
        else 
        {
            redoExpression = "("+baseExpression+")=nullptr";
        }

        reflection::Expression* pRedoExpression = phantom::expressionByName(redoExpression);
        reflection::Expression* pUndoExpression = phantom::expressionByName(undoExpression);

        ExpressionCommand* pCommand = o_new(ExpressionCommand)(pDataBase, pUndoExpression, pRedoExpression);
        pCommand->setName( "In data : '"+ pDataBase->getDataAttributeValue(d, "name") + "' ("+phantom::lexical_cast<phantom::string>((void*)pDataBase->getGuid(d))+")");
        pGroup->pushCommand(pCommand);
    }

    if(pNewClass)
        pGroup->setName("Property changed : '" + m_pVariableNode->getQualifiedName()+ " = new "+phantom::qt::nameOf(pNewClass)+" component'");
    else
        pGroup->setName("Property changed : '" + m_pVariableNode->getQualifiedName()+ " = none'");

    return pGroup;
}

VariableWidgetEditor* ComponentVariableNodeDelegate::createEditor() const
{
    reflection::ComponentClass* pComponentClass = m_pVariableNode->getValueType()->removeConstReference()->asComponentClass();
    vector<reflection::Class*> currentClasses;
    size_t count = m_pVariableNode->getExpressionCount();
    reflection::Class* pCurrentClass = nullptr;
    for(size_t i = 0; i<count; ++i)
    {
        void* pOldValue = nullptr;
        pComponentClass->get(m_pVariableNode->getExpression(i)->loadEffectiveAddress(), &pOldValue);
        if(pOldValue)
        {
            reflection::Class* pClass = classOf(pOldValue);
            if(pCurrentClass != nullptr AND pClass != pCurrentClass)
            {
                pCurrentClass = nullptr;
                break;
            }
            pCurrentClass = pClass;
        }
    }
    return o_new(ClassComboBoxEditor)(pComponentClass->getPointedClass(), pCurrentClass, NOT(m_pVariableNode->hasModifier(o_mandatory)));
}

string ComponentVariableNodeDelegate::valueText() const
{
    VariableModel* pVariableModel = m_pVariableNode->getVariableModel();

    reflection::ComponentClass* pComponentClass = m_pVariableNode->getValueType()->removeConstReference()->asComponentClass();
    std::set<reflection::Class*> currentClasses;
    size_t count = m_pVariableNode->getExpressionCount();
    for(size_t i = 0; i<count; ++i)
    {
        void* pOldValue = nullptr;
        pComponentClass->get(m_pVariableNode->getExpression(i)->loadEffectiveAddress(), &pOldValue);
        currentClasses.insert(classOf(pOldValue));
    }
    if(currentClasses.size() == 1)
    {
        reflection::Class* pClass = *currentClasses.begin();
        if(pClass)
        {
            return nameOf(pClass);
        }
        return "none";
    }
    return "<multiple values>";
}

}}