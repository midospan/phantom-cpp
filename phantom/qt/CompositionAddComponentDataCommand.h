#pragma once
#ifndef phantom_qt_CompositionAddComponentDataCommand_h__
#define phantom_qt_CompositionAddComponentDataCommand_h__


/* ****************** Includes ******************* */
#include <phantom/qt/DataBaseCommand.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, qt), CompositionAddComponentDataCommand);
/* *********************************************** */

namespace phantom { namespace qt {


/* ************************************************ *
 * \class CompositionAddComponentDataCommand
 * \brief Command to add a node
 * ************************************************ */
class o_qt_export CompositionAddComponentDataCommand : public DataBaseCommand
{
public:

	//================================================
	// Constructors / Destructor
	//================================================

    CompositionAddComponentDataCommand(serialization::DataBase* a_pDataBase, reflection::Type* a_pType, const phantom::data& a_OwnerData, reflection::Expression* a_pCompositionExpression);
    CompositionAddComponentDataCommand(serialization::DataBase* a_pDataBase, const string& a_strTypeName, uint a_uiOwnerGuid, const string& a_strCompositionExpression);
	~CompositionAddComponentDataCommand();

	//================================================
	// Operations
	//================================================

    virtual void redoReplayed();
    virtual void undoReplayed();
    
    virtual CompositionAddComponentDataCommand* clone() const;

    string generateComponentName(serialization::DataBase* a_pDataBase, phantom::data a_Component);

protected:
	//================================================
	// Fields
	//================================================
    string                          m_strTypeName;
    string                          m_strCompositionExpression;
    uint                            m_uiOwnerGuid;

};

} // qt 
} // phantom

#endif // phantom_qt_CompositionAddComponentDataCommand_h__
