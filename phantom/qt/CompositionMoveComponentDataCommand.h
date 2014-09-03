#pragma once
#ifndef phantom_qt_CompositionMoveComponentDataCommand_h__
#define phantom_qt_CompositionMoveComponentDataCommand_h__


/* ****************** Includes ******************* */
#include <phantom/qt/UndoCommand.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, qt), CompositionMoveComponentDataCommand);
/* *********************************************** */

namespace phantom { namespace qt {


/* ************************************************ *
 * \class CompositionMoveComponentDataCommand
 * \brief Command to add a node
 * ************************************************ */
class o_qt_export CompositionMoveComponentDataCommand : public UndoCommand
{
public:

	//================================================
	// Constructors / Destructor
	//================================================

    CompositionMoveComponentDataCommand(serialization::DataBase* a_pDataBase, const phantom::data& a_OwnerData, reflection::Expression* a_pCompositionExpression, size_t oldIndex, size_t newIndex);
    CompositionMoveComponentDataCommand(serialization::DataBase* a_pDataBase, uint a_uiOwnerGuid, const string& a_strCompositionExpression, size_t oldIndex, size_t newIndex);
	~CompositionMoveComponentDataCommand();


	//================================================
	// Operations
	//================================================

	virtual void undo();
	virtual void redo();
    virtual CompositionMoveComponentDataCommand* clone() const;

protected:
    void createSubCommands(reflection::Expression* a_pCompositionExpression);

protected:
	//================================================
	// Fields
	//================================================
    serialization::DataBase*        m_pDataBase;
    string                          m_strTypeName;
    string                          m_strCompositionExpression;
    uint                            m_uiOwnerGuid;
    size_t                          m_uiNewIndex;
    size_t                          m_uiOldIndex;

};

} // qt 
} // phantom

#endif // phantom_qt_CompositionMoveComponentDataCommand_h__
