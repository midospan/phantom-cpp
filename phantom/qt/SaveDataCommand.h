#pragma once
#ifndef phantom_qt_SaveDataCommand_h__
#define phantom_qt_SaveDataCommand_h__


/* ****************** Includes ******************* */
#include <phantom/qt/UndoCommand.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, qt), SaveDataCommand);
/* *********************************************** */

namespace phantom { namespace qt {


/* ************************************************ *
 * \class SaveDataCommand
 * \brief Command to add a node
 * ************************************************ */
class o_qt_export SaveDataCommand : public UndoCommand
{
public:

	//================================================
	// Constructors / Destructor
	//================================================

	SaveDataCommand(phantom::serialization::Node* a_pNode, const phantom::data& a_Data);
	~SaveDataCommand();


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
    uint                            m_uiParentGuid;

};

} // qt 
} // phantom

#endif // phantom_qt_SaveDataCommand_h__
