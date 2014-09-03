#pragma once
#ifndef phantom_qt_CompositionAddComponentDataCommand_h__
#define phantom_qt_CompositionAddComponentDataCommand_h__


/* ****************** Includes ******************* */
#include <phantom/qt/UndoCommand.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, qt), CompositionAddComponentDataCommand);
/* *********************************************** */

namespace phantom { namespace qt {


/* ************************************************ *
 * \class CompositionAddComponentDataCommand
 * \brief Command to add a node
 * ************************************************ */
class o_qt_export CompositionAddComponentDataCommand : public UndoCommand
{
public:

	//================================================
	// Constructors / Destructor
	//================================================

    CompositionAddComponentDataCommand(serialization::DataBase* a_pDataBase, reflection::Type* a_pType, uint a_uiGuid, const phantom::data& a_OwnerData, reflection::Expression* a_pCompositionExpression);
    CompositionAddComponentDataCommand(serialization::DataBase* a_pDataBase, const string& a_strTypeName, uint a_uiGuid, uint a_uiOwnerGuid, const string& a_strCompositionExpression);
	~CompositionAddComponentDataCommand();


	//================================================
	// Operations
	//================================================

	virtual void undo();
	virtual void redo();
    virtual CompositionAddComponentDataCommand* clone() const;

    string generateComponentName(serialization::DataBase* a_pDataBase, phantom::data a_Component);

protected:
	//================================================
	// Fields
	//================================================
    serialization::DataBase*        m_pDataBase;
    string                          m_strTypeName;
    string                          m_strCompositionExpression;
    uint                            m_uiGuid;
    uint                            m_uiOwnerGuid;
    bitfield                        m_Modifiers;

};

} // qt 
} // phantom

#endif // phantom_qt_CompositionAddComponentDataCommand_h__
