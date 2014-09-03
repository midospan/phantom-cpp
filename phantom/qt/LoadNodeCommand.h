#pragma once
#ifndef phantom_qt_LoadNodeCommand_h__
#define phantom_qt_LoadNodeCommand_h__


/* ****************** Includes ******************* */
#include <phantom/qt/UndoCommand.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, qt), LoadNodeCommand);
/* *********************************************** */

namespace phantom { namespace qt {


/* ************************************************ *
 * \class LoadNodeCommand
 * \brief Command to add a node
 * ************************************************ */
class o_qt_export LoadNodeCommand : public UndoCommand
{
public:

	//================================================
	// Constructors / Destructor
	//================================================

	LoadNodeCommand(phantom::serialization::Node* a_pNode);
	~LoadNodeCommand();


	//================================================
	// Operations
	//================================================

	virtual void undo();
	virtual void redo();
    virtual LoadNodeCommand* clone() const;

protected:
	//================================================
	// Fields
	//================================================
	serialization::DataBase*        m_pDataBase;
	uint							m_uiGuid;

};

} // qt 
} // phantom

#endif // phantom_qt_LoadNodeCommand_h__
