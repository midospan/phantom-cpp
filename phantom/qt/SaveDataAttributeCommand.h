#pragma once
#ifndef phantom_qt_SaveDataAttributeCommand_h__
#define phantom_qt_SaveDataAttributeCommand_h__


/* ****************** Includes ******************* */
#include <phantom/qt/UndoCommand.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, qt), SaveDataAttributeCommand);
/* *********************************************** */

namespace phantom { namespace qt {


/* ************************************************ *
 * \class SaveDataAttributeCommand
 * \brief Command to add a node
 * ************************************************ */
class o_qt_export SaveDataAttributeCommand : public UndoCommand
{
public:

	//================================================
	// Constructors / Destructor
	//================================================

	SaveDataAttributeCommand(phantom::serialization::Node* a_pNode, const phantom::data& a_Data);
	~SaveDataAttributeCommand();


	//================================================
	// Operations
	//================================================

	virtual void undo();
	virtual void redo();
    virtual SaveDataAttributeCommand* clone() const;

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

#endif // phantom_qt_SaveDataAttributeCommand_h__
