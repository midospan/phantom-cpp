/* ******************* Includes ****************** */
#include "phantom/qt/qt.h"
#include "ExpressionCommand.h"
#include "ExpressionCommand.hxx"
#include "phantom/reflection/Expression.h"
/* *********************************************** */
o_registerN((phantom, qt), ExpressionCommand);

o_namespace_begin(phantom, qt)

ExpressionCommand::ExpressionCommand( const string& a_strUndoExpression, const string& a_strRedoExpression ) 
    : m_strUndoExpression(a_strUndoExpression)
    , m_strRedoExpression(a_strRedoExpression)
    , m_pNativeUndoExpression(nullptr)
    , m_pNativeRedoExpression(nullptr)
{

}

ExpressionCommand::ExpressionCommand( reflection::Expression* a_pNativeUndoExpression, reflection::Expression* a_pNativeRedoExpression )
    : m_strUndoExpression(a_pNativeUndoExpression->getName())
    , m_strRedoExpression(a_pNativeRedoExpression->getName())
    , m_pNativeUndoExpression(a_pNativeUndoExpression->isNative() ? a_pNativeUndoExpression : nullptr)
    , m_pNativeRedoExpression(a_pNativeRedoExpression->isNative() ? a_pNativeRedoExpression : nullptr)
{
}

void ExpressionCommand::undo()
{
    reflection::Expression* pExpression = m_pNativeUndoExpression;
    if(pExpression == nullptr)
    {
        pExpression = phantom::expressionByName(m_strUndoExpression);
        o_assert(pExpression);
        if(pExpression->isNative()) // means execution wont change in time because statically defined in native C++
        {
            m_pNativeUndoExpression = pExpression;
        }
    }
    pExpression->eval();
}

void ExpressionCommand::redo()
{
    reflection::Expression* pExpression = m_pNativeRedoExpression;
    if(pExpression == nullptr)
    {
        pExpression = phantom::expressionByName(m_strRedoExpression);
        o_assert(pExpression);
        if(pExpression->isNative()) // means execution wont change in time because statically defined in native C++
        {
            m_pNativeRedoExpression = pExpression;
        }
    }
    pExpression->eval();
}

o_namespace_end(phantom, qt)

