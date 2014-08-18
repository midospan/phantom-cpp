#pragma once
#ifndef phantom_qt_AddComponentDataCommand_h__
#define phantom_qt_AddComponentDataCommand_h__


/* ****************** Includes ******************* */
#include <phantom/qt/UndoCommand.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, qt), AddComponentDataCommand);
/* *********************************************** */

namespace phantom { namespace qt {


/* ************************************************ *
 * \class AddComponentDataCommand
 * \brief Command to add a node
 * ************************************************ */
class o_qt_export AddComponentDataCommand : public UndoCommand
{
public:

	//================================================
	// Constructors / Destructor
	//================================================

    AddComponentDataCommand(serialization::DataBase* a_pDataBase, reflection::Type* a_pType, uint a_uiGuid, const phantom::data& a_OwnerData);
	~AddComponentDataCommand();


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
    string                          m_strTypeName;
    uint                            m_uiGuid;
    uint                            m_uiOwnerGuid;

};

} // qt 
} // phantom

#endif // phantom_qt_AddComponentDataCommand_h__
