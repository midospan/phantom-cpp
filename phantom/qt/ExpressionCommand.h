#ifndef o_phantom_qt_ExpressionCommand_h__
#define o_phantom_qt_ExpressionCommand_h__


/* ****************** Includes ******************* */
#include <phantom/qt/UndoCommand.h>
#include <phantom/variant.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, qt), ExpressionCommand);
/* *********************************************** */

o_namespace_begin(phantom, qt)

class o_qt_export ExpressionCommand : public UndoCommand
{
public:
    ExpressionCommand(const string& a_strUndoExpression, const string& a_strRedoExpression);
    ExpressionCommand(reflection::Expression* a_pNativeUndoExpression, reflection::Expression* a_pNativeRedoExpression);
	~ExpressionCommand(void) {}
	
    virtual void undo();
    virtual void redo();

    void setUndoExpression(const string& a_strExpression) { m_strUndoExpression = a_strExpression; }
    void setRedoExpression(const string& a_strExpression) { m_strRedoExpression = a_strExpression; }

protected:
    reflection::Expression* m_pNativeUndoExpression;
    reflection::Expression* m_pNativeRedoExpression;
    string m_strUndoExpression;
    string m_strRedoExpression;
};

o_namespace_end(phantom, qt)

#endif // o_phantom_qt_ExpressionCommand_h__
