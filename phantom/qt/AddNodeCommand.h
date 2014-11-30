#pragma once
#ifndef phantom_qt_AddNodeCommand_h__
#define phantom_qt_AddNodeCommand_h__


/* ****************** Includes ******************* */
#include <phantom/qt/DataBaseCommand.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, qt), AddNodeCommand);
/* *********************************************** */

namespace phantom { namespace qt {


/* ************************************************ *
 * \class AddNodeCommand
 * \brief Command to add a node
 * ************************************************ */
class o_qt_export AddNodeCommand : public DataBaseCommand
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

    virtual void undoReplayed();
    virtual void redoReplayed();
    virtual UndoCommand* clone() const;

protected:
	//================================================
	// Fields
	//================================================
	uint							m_uiGuid;
    uint                            m_uiParentGuid;

};

} // qt 
} // phantom

#endif // phantom_qt_AddNodeCommand_h__
