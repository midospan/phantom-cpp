#pragma once
#ifndef phantom_qt_DataBaseCommand_h__
#define phantom_qt_DataBaseCommand_h__


/* ****************** Includes ******************* */
#include <phantom/qt/UndoCommand.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, qt), DataBaseCommand);
/* *********************************************** */

namespace phantom { namespace qt {


/* ************************************************ *
 * \class DataBaseCommand
 * \brief Command to add a node
 * ************************************************ */
class o_qt_export DataBaseCommand : public UndoCommand
{
public:

	//================================================
	// Constructors / Destructor
	//================================================

    DataBaseCommand( serialization::DataBase* a_pDataBase );
    DataBaseCommand( const string& a_strName, serialization::DataBase* a_pDataBase );
	~DataBaseCommand();


	//================================================
	// Operations
    //================================================

    virtual void record() { redoReplayed(); }

    virtual void redoReplayed() = 0;
    virtual void undoReplayed() = 0;

	virtual void undo();
    virtual void redo();

protected:
    virtual void asymetricRedo(Message* a_pMessage) {}
    virtual void asymetricUndo(Message* a_pMessage) {}

protected:
    //================================================
    // Fields
    //================================================
    static uint sm_uiBackupId;

    serialization::DataBase*        m_pDataBase;
    serialization::Record*          m_pRecord;
    bool                            m_bRecorded;

};

} // qt 
} // phantom

#endif // phantom_qt_DataBaseCommand_h__
