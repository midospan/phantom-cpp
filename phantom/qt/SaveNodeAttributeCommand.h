#pragma once
#ifndef phantom_qt_SaveNodeAttributeCommand_h__
#define phantom_qt_SaveNodeAttributeCommand_h__


/* ****************** Includes ******************* */
#include <phantom/qt/UndoCommand.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, qt), SaveNodeAttributeCommand);
/* *********************************************** */

namespace phantom { namespace qt {


/* ************************************************ *
 * \class SaveNodeAttributeCommand
 * \brief Command to add a node
 * ************************************************ */
class o_qt_export SaveNodeAttributeCommand : public UndoCommand
{
public:

	//================================================
	// Constructors / Destructor
	//================================================

	SaveNodeAttributeCommand(phantom::serialization::Node* a_pNode);
	~SaveNodeAttributeCommand();


	//================================================
	// Operations
	//================================================

	virtual void undo();
	virtual void redo();


protected:
	//================================================
	// Fields
	//================================================
	serialization::DataBase*        m_pDataBase;
	uint							m_uiGuid;

};

} // qt 
} // phantom

#endif // phantom_qt_SaveNodeAttributeCommand_h__
