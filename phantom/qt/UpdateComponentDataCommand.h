#pragma once
#ifndef phantom_qt_UpdateComponentDataCommand_h__
#define phantom_qt_UpdateComponentDataCommand_h__


/* ****************** Includes ******************* */
#include <phantom/qt/UndoCommand.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, qt), UpdateComponentDataCommand);
/* *********************************************** */

namespace phantom { namespace qt {


/* ************************************************ *
 * \class UpdateComponentDataCommand
 * \brief Command to add a node
 * ************************************************ */
class o_qt_export UpdateComponentDataCommand : public UndoCommand
{
public:

	//================================================
	// Constructors / Destructor
	//================================================

    UpdateComponentDataCommand(serialization::DataBase* a_pDataBase, const phantom::data& a_Data);
	~UpdateComponentDataCommand();


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
    vector<uint>                    m_RemovedGuids;
    vector<uint>                    m_AddedGuids;
    uint                            m_uiGuid;
    bool                            m_bInitialized;

};

} // qt 
} // phantom

#endif // phantom_qt_UpdateComponentDataCommand_h__
