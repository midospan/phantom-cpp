#pragma once
#ifndef phantom_qt_ComponentReferenceExpressionChangeCommand_h__
#define phantom_qt_ComponentReferenceExpressionChangeCommand_h__


/* ****************** Includes ******************* */
#include <phantom/qt/UndoCommand.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, qt), ComponentReferenceExpressionChangeCommand);
/* *********************************************** */

namespace phantom { namespace qt {


/* ************************************************ *
 * \class ComponentReferenceExpressionChangeCommand
 * \brief Command to add a node
 * ************************************************ */
class o_qt_export ComponentReferenceExpressionChangeCommand : public UndoCommand
{
public:

	//================================================
	// Constructors / Destructor
	//================================================

    ComponentReferenceExpressionChangeCommand(serialization::DataBase* a_pDataBase, const phantom::data& a_Data, const string& a_NewValue);
    ComponentReferenceExpressionChangeCommand(serialization::DataBase* a_pDataBase, uint a_uiGuid, const string& a_NewValue, const string& a_OldValue);
	~ComponentReferenceExpressionChangeCommand();


	//================================================
	// Operations
	//================================================

	virtual void undo();
	virtual void redo();

    virtual UndoCommand* clone() const;

protected:
	//================================================
	// Fields
	//================================================
	serialization::DataBase*        m_pDataBase;
	uint							m_uiGuid;
    string                          m_strOldValue;
    string                          m_strNewValue;

};

} // qt 
} // phantom

#endif // phantom_qt_ComponentReferenceExpressionChangeCommand_h__
