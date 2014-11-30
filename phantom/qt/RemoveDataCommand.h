#pragma once
#ifndef phantom_qt_RemoveDataCommand_h__
#define phantom_qt_RemoveDataCommand_h__


/* ****************** Includes ******************* */
#include <phantom/qt/DataBaseCommand.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, qt), RemoveDataCommand);
/* *********************************************** */

namespace phantom { namespace qt {


/* ************************************************ *
 * \class RemoveDataCommand
 * \brief Command to add a node
 * ************************************************ */
class o_qt_export RemoveDataCommand : public DataBaseCommand
{
public:

	//================================================
	// Constructors / Destructor
	//================================================

	RemoveDataCommand(serialization::DataBase* a_pDataBase, const vector<uint>& a_Guids);
	~RemoveDataCommand();


	//================================================
	// Operations
	//================================================

	virtual void redoReplayed();
    virtual void undoReplayed();
    virtual void record();
    virtual RemoveDataCommand* clone() const;

protected:
	//================================================
	// Fields
	//================================================
    vector<uint>            m_Guids;
    map<uint, string>       m_Types;
    map<uint, string>       m_ComponentReferenceExpressions;
    map<uint, uint>         m_Nodes;
};

} // qt 
} // phantom

#endif // phantom_qt_RemoveDataCommand_h__
