#pragma once
#ifndef phantom_qt_LoadNodeCommand_h__
#define phantom_qt_LoadNodeCommand_h__


/* ****************** Includes ******************* */
#include <phantom/qt/DataBaseCommand.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, qt), LoadNodeCommand);
/* *********************************************** */

namespace phantom { namespace qt {


/* ************************************************ *
 * \class LoadNodeCommand
 * \brief Command to add a node
 * ************************************************ */
class o_qt_export LoadNodeCommand : public DataBaseCommand
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

    virtual void redoReplayed();
    virtual void undoReplayed();
    virtual LoadNodeCommand* clone() const;

protected:
	//================================================
	// Fields
	//================================================
	uint							m_uiGuid;

};

} // qt 
} // phantom

#endif // phantom_qt_LoadNodeCommand_h__
