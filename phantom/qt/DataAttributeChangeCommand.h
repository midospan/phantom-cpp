#pragma once
#ifndef phantom_qt_DataAttributeChangeCommand_h__
#define phantom_qt_DataAttributeChangeCommand_h__


/* ****************** Includes ******************* */
#include <phantom/qt/UndoCommand.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, qt), DataAttributeChangeCommand);
/* *********************************************** */

namespace phantom { namespace qt {


/* ************************************************ *
 * \class DataAttributeChangeCommand
 * \brief Command to add a node
 * ************************************************ */
class o_qt_export DataAttributeChangeCommand : public UndoCommand
{
public:

	//================================================
	// Constructors / Destructor
	//================================================

    DataAttributeChangeCommand(serialization::DataBase* a_pDataBase, const phantom::data& a_Data, size_t a_uiAttributeIndex, const string& a_NewValue);
    DataAttributeChangeCommand(serialization::DataBase* a_pDataBase, uint a_uiGuid, size_t a_uiAttributeIndex, const string& a_NewValue, const string& a_OldValue);
	~DataAttributeChangeCommand();


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
	uint							m_uiGuid;
    size_t                          m_uiAttributeIndex;
    string                          m_strOldValue;
    string                          m_strNewValue;

};

} // qt 
} // phantom

#endif // phantom_qt_DataAttributeChangeCommand_h__
