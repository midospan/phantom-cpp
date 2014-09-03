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

    AddComponentDataCommand(serialization::DataBase* a_pDataBase, reflection::Type* a_pType, const phantom::data& a_OwnerData, reflection::Expression* a_pExpression);
    AddComponentDataCommand(serialization::DataBase* a_pDataBase, const string& a_strTypeName, uint a_uiOwnerGuid, const string& a_strReferenceExpression);
	~AddComponentDataCommand();


	//================================================
	// Operations
	//================================================

	virtual void undo();
	virtual void redo();
    virtual AddComponentDataCommand* clone() const;

protected:
	//================================================
	// Fields
	//================================================
    serialization::DataBase*        m_pDataBase;
    string                          m_strTypeName;
    string                          m_strReferenceExpression;
    uint                            m_uiGuid;
    uint                            m_uiOwnerGuid;
    bitfield                        m_Modifiers;

};

} // qt 
} // phantom

#endif // phantom_qt_AddComponentDataCommand_h__
