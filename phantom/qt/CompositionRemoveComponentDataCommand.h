#pragma once
#ifndef phantom_qt_CompositionRemoveComponentDataCommand_h__
#define phantom_qt_CompositionRemoveComponentDataCommand_h__


/* ****************** Includes ******************* */
#include <phantom/qt/DataBaseCommand.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, qt), CompositionRemoveComponentDataCommand);
/* *********************************************** */

namespace phantom { namespace qt {


/* ************************************************ *
 * \class CompositionRemoveComponentDataCommand
 * \brief Command to add a node
 * ************************************************ */
class o_qt_export CompositionRemoveComponentDataCommand : public DataBaseCommand
{
public:

	//================================================
	// Constructors / Destructor
	//================================================

    CompositionRemoveComponentDataCommand(serialization::DataBase* a_pDataBase, size_t a_uiIndex, const phantom::data& a_OwnerData, reflection::Expression* a_pCompositionExpression);
    CompositionRemoveComponentDataCommand(serialization::DataBase* a_pDataBase, size_t a_uiIndex, uint a_OwnerGuid, const string& a_strCompositionExpression);
	~CompositionRemoveComponentDataCommand();

	//================================================
	// Operations
	//================================================

    virtual void redoReplayed();
    virtual void undoReplayed();
    
    virtual CompositionRemoveComponentDataCommand* clone() const;

    string generateComponentName(serialization::DataBase* a_pDataBase, phantom::data a_Component);

protected:
	//================================================
	// Fields
	//================================================
    string                          m_strTypeName;
    string                          m_strCompositionExpression;
    uint                            m_uiOwnerGuid;
    size_t                          m_uiIndex;

};

} // qt 
} // phantom

#endif // phantom_qt_CompositionRemoveComponentDataCommand_h__
