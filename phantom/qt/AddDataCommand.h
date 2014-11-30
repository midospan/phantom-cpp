#pragma once
#ifndef phantom_qt_AddDataCommand_h__
#define phantom_qt_AddDataCommand_h__


/* ****************** Includes ******************* */
#include <phantom/qt/DataBaseCommand.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, qt), AddDataCommand);
/* *********************************************** */

namespace phantom { namespace qt {


/* ************************************************ *
 * \class AddDataCommand
 * \brief Command to add a node
 * ************************************************ */
class o_qt_export AddDataCommand : public DataBaseCommand
{
public:

	//================================================
	// Constructors / Destructor
	//================================================

    AddDataCommand(reflection::Type* a_pType, phantom::serialization::Node* a_pNode);
    AddDataCommand(const string& a_strTypeName, phantom::serialization::Node* a_pNode);
	~AddDataCommand();


	//================================================
	// Operations
	//================================================

    virtual void redoReplayed();
    virtual void undoReplayed();

    virtual UndoCommand* clone() const;

protected:
	//================================================
	// Fields
	//================================================
    string                          m_strTypeName;
    uint                            m_uiNodeGuid;
    uint                            m_uiGuid;
};

} // qt 
} // phantom

#endif // phantom_qt_AddDataCommand_h__
