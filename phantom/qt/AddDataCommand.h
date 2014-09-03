#pragma once
#ifndef phantom_qt_AddDataCommand_h__
#define phantom_qt_AddDataCommand_h__


/* ****************** Includes ******************* */
#include <phantom/qt/UndoCommand.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, qt), AddDataCommand);
/* *********************************************** */

namespace phantom { namespace qt {


/* ************************************************ *
 * \class AddDataCommand
 * \brief Command to add a node
 * ************************************************ */
class o_qt_export AddDataCommand : public UndoCommand
{
public:

	//================================================
	// Constructors / Destructor
	//================================================

    AddDataCommand(reflection::Type* a_pType, uint guid, phantom::serialization::Node* a_pNode);
    AddDataCommand(const string& a_strTypeName, uint guid, phantom::serialization::Node* a_pNode);
	~AddDataCommand();


	//================================================
	// Operations
	//================================================

	virtual void undo();
	virtual void redo();

    virtual UndoCommand* clone() const;

protected:
	//================================================
	// Fields
	//================================================
	serialization::DataBase*        m_pDataBase;
    string                          m_strTypeName;
	uint							m_uiGuid;
    uint                            m_uiNodeGuid;
    bool                            m_bInitialized;

};

} // qt 
} // phantom

#endif // phantom_qt_AddDataCommand_h__
