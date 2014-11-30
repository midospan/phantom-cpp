#ifndef o_phantom_qt_ExpressionCommand_h__
#define o_phantom_qt_ExpressionCommand_h__


/* ****************** Includes ******************* */
#include <phantom/qt/DataBaseCommand.h>
#include <phantom/variant.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, qt), ExpressionCommand);
/* *********************************************** */

o_namespace_begin(phantom, qt)

class o_qt_export ExpressionCommand : public DataBaseCommand
{
public:
    ExpressionCommand(serialization::DataBase* a_pDataBase, const string& a_strUndoExpression, const string& a_strRedoExpression);
    ExpressionCommand(serialization::DataBase* a_pDataBase, reflection::Expression* a_pUndoExpression, reflection::Expression* a_pRedoExpression);
	~ExpressionCommand(void) {}
	
    virtual void undoReplayed();
    virtual void redoReplayed();

    void setUndoExpression(const string& a_strExpression) { m_strUndoExpression = a_strExpression; }
    void setRedoExpression(const string& a_strExpression) { m_strRedoExpression = a_strExpression; }

protected:
    virtual void asymetricRedo(Message* a_pMessage);
    virtual void asymetricUndo(Message* a_pMessage);

protected:
    reflection::Expression* m_pPersistentUndoExpression;
    reflection::Expression* m_pPersistentRedoExpression;
    string m_strUndoExpression;
    string m_strRedoExpression;
};

o_namespace_end(phantom, qt)

#endif // o_phantom_qt_ExpressionCommand_h__
