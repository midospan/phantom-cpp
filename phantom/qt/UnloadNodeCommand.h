#pragma once
#ifndef phantom_qt_UnloadNodeCommand_h__
#define phantom_qt_UnloadNodeCommand_h__


/* ****************** Includes ******************* */
#include <phantom/qt/DataBaseCommand.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, qt), UnloadNodeCommand);
/* *********************************************** */

namespace phantom { namespace qt {


/* ************************************************ *
 * \class UnloadNodeCommand
 * \brief Command to add a node
 * ************************************************ */
class o_qt_export UnloadNodeCommand : public DataBaseCommand
{
public:

	//================================================
	// Constructors / Destructor
	//================================================

	UnloadNodeCommand(phantom::serialization::Node* a_pNode);
	~UnloadNodeCommand();


	//================================================
	// Operations
	//================================================

    virtual void redoReplayed();
    virtual void undoReplayed();

    virtual UnloadNodeCommand* clone() const;

protected:
	//================================================
	// Fields
	//================================================
	uint							m_uiGuid;

};

} // qt 
} // phantom

#endif // phantom_qt_UnloadNodeCommand_h__
