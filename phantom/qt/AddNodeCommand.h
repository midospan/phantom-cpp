#pragma once
#ifndef phantom_qt_AddNodeCommand_h__
#define phantom_qt_AddNodeCommand_h__


/* ****************** Includes ******************* */
#include <phantom/qt/UndoCommand.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, qt), AddNodeCommand);
/* *********************************************** */

namespace phantom { namespace qt {


/* ************************************************ *
 * \class AddNodeCommand
 * \brief Command to add a node
 * ************************************************ */
class o_qt_export AddNodeCommand : public UndoCommand
{
public:

	//================================================
	// Constructors / Destructor
	//================================================

	AddNodeCommand(phantom::serialization::Node* m_pParentNode);
	~AddNodeCommand();


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

#endif // phantom_qt_AddNodeCommand_h__
