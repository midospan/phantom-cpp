/* ******************* Includes ****************** */
#include "phantom/qt/qt.h"
#include "ExpressionCommandAction.h"
#include "ExpressionCommandAction.hxx"
#include "phantom/reflection/ExpressionCommand.h"
/* *********************************************** */
o_registerN((phantom, qt), ExpressionCommandAction);

o_namespace_begin(phantom, qt)

ExpressionCommandAction::ExpressionCommandAction( UndoStack* a_pUndoStack, const string& a_strUndoExpression, const string& a_strRedoExpression ) 
    : m_strUndoExpression(a_strUndoExpression)
    , m_strRedoExpression(a_strRedoExpression)
    , m_pNativeUndoExpression(nullptr)
    , m_pNativeRedoExpression(nullptr)
    , m_pUndoStack(a_pUndoStack)
{

}

ExpressionCommandAction::ExpressionCommandAction( UndoStack* a_pUndoStack, reflection::Expression* a_pNativeUndoExpression, reflection::Expression* a_pNativeRedoExpression )
    : m_strUndoExpression(a_pNativeUndoExpression->getName())
    , m_strRedoExpression(a_pNativeRedoExpression->getName())
    , m_pNativeUndoExpression(a_pNativeUndoExpression->isNative() ? a_pNativeUndoExpression : nullptr)
    , m_pNativeRedoExpression(a_pNativeRedoExpression->isNative() ? a_pNativeRedoExpression : nullptr)
    , m_pUndoStack(a_pUndoStack)
{
}

void ExpressionCommandAction::doAction()
{
    if(m_pNativeRedoExpression)
    {
        o_assert(m_pNativeUndoExpression);
        m_pUndoStack->pushCommand(o_new(ExpressionCommand)(m_pNativeUndoExpression, m_pNativeRedoExpression));
    }
    else 
    {
        m_pUndoStack->pushCommand(o_new(ExpressionCommand)(m_strUndoExpression, m_strRedoExpression));
    }
}

o_namespace_end(phantom, qt)

