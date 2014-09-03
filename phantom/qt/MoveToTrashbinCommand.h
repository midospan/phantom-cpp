#pragma once
#ifndef phantom_qt_MoveToTrashbinCommand_h__
#define phantom_qt_MoveToTrashbinCommand_h__


/* ****************** Includes ******************* */
#include <phantom/qt/UndoCommand.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, qt), MoveToTrashbinCommand);
/* *********************************************** */

namespace phantom { namespace qt {


/* ************************************************ *
 * \class MoveToTrashbinCommand
 * \brief Command to add a node
 * ************************************************ */
class o_qt_export MoveToTrashbinCommand : public UndoCommand
{
public:

	//================================================
	// Constructors / Destructor
	//================================================

	MoveToTrashbinCommand(serialization::DataBase* a_pDataBase, const vector<uint>& a_Guids);
	~MoveToTrashbinCommand();


	//================================================
	// Operations
	//================================================

	virtual void undo();
	virtual void redo();
    virtual MoveToTrashbinCommand* clone() const;

protected:
	//================================================
	// Fields
	//================================================
    vector<uint>                    m_Guids;
	serialization::DataBase*        m_pDataBase;

};

} // qt 
} // phantom

#endif // phantom_qt_MoveToTrashbinCommand_h__
