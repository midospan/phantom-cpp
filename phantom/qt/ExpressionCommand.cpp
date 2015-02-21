/* ******************* Includes ****************** */
#include "phantom/qt/qt.h"
#include "ExpressionCommand.h"
#include "ExpressionCommand.hxx"
#include "phantom/reflection/Expression.h"
#include <phantom/Message.h>
/* *********************************************** */
o_registerN((phantom, qt), ExpressionCommand);

o_namespace_begin(phantom, qt)

ExpressionCommand::ExpressionCommand( serialization::DataBase* a_pDataBase, const string& a_strUndoExpression, const string& a_strRedoExpression ) 
    : DataBaseCommand(a_pDataBase)
    , m_strUndoExpression(a_strUndoExpression)
    , m_strRedoExpression(a_strRedoExpression)
    , m_pPersistentUndoExpression(nullptr)
    , m_pPersistentRedoExpression(nullptr)
{

}

ExpressionCommand::ExpressionCommand( serialization::DataBase* a_pDataBase, reflection::Expression* a_pUndoExpression, reflection::Expression* a_pRedoExpression )
    : DataBaseCommand(a_pDataBase)
    , m_strUndoExpression(a_pUndoExpression->translate())
    , m_strRedoExpression(a_pRedoExpression->translate())
    , m_pPersistentUndoExpression(a_pUndoExpression->isPersistent() ? a_pUndoExpression : nullptr)
    , m_pPersistentRedoExpression(a_pRedoExpression->isPersistent() ? a_pRedoExpression : nullptr)
{

}

void ExpressionCommand::redoReplayed()
{
    reflection::Expression* pExpression = m_pPersistentRedoExpression;
    if(pExpression == nullptr)
    {
        pExpression = phantom::expressionByName(m_strRedoExpression);
        o_assert(pExpression);
        if(pExpression->isPersistent()) // means execution wont change in time because statically defined in native C++
        {
            m_pPersistentRedoExpression = pExpression;
        }
    }
    pExpression->eval();
}

void ExpressionCommand::undoReplayed()
{
    reflection::Expression* pExpression = m_pPersistentUndoExpression;
    if(pExpression == nullptr)
    {
        pExpression = phantom::expressionByName(m_strUndoExpression);
        o_assert(pExpression);
        if(pExpression->isPersistent()) // means execution wont change in time because statically defined in native C++
        {
            m_pPersistentUndoExpression = pExpression;
        }
    }
    pExpression->eval();
}

void ExpressionCommand::asymetricRedo(Message* a_pMessage) 
{
    a_pMessage->warning(data(), "On executing expression : %s", m_strRedoExpression.c_str());
}

void ExpressionCommand::asymetricUndo(Message* a_pMessage) 
{
    a_pMessage->warning(data(), "On executing expression : %s", m_strUndoExpression.c_str());
}

o_namespace_end(phantom, qt)

