#ifndef o_phantom_qt_ExpressionCommandAction_h__
#define o_phantom_qt_ExpressionCommandAction_h__


/* ****************** Includes ******************* */
#include <phantom/qt/Action.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, qt), ExpressionCommandAction);
/* *********************************************** */

o_namespace_begin(phantom, qt)

class o_qt_export ExpressionCommandAction : public Action
{
public:
    ExpressionCommandAction(UndoStack* a_pUndoStack, const string& a_strUndoExpression, const string& a_strRedoExpression);
    ExpressionCommandAction(UndoStack* a_pUndoStack, reflection::Expression* a_pNativeUndoExpression, reflection::Expression* a_pNativeRedoExpression);
	~ExpressionCommandAction(void) {}
	
    virtual void doAction();

protected:
    UndoStack* m_pUndoStack;
    reflection::Expression* m_pNativeUndoExpression;
    reflection::Expression* m_pNativeRedoExpression;
    string m_strUndoExpression;
    string m_strRedoExpression;
};

o_namespace_end(phantom, qt)

#endif // o_phantom_qt_ExpressionCommandAction_h__
