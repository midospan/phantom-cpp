#pragma once
#ifndef phantom_qt_NodeAttributeChangeCommand_h__
#define phantom_qt_NodeAttributeChangeCommand_h__


/* ****************** Includes ******************* */
#include <phantom/qt/UndoCommand.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, qt), NodeAttributeChangeCommand);
/* *********************************************** */

namespace phantom { namespace qt {


/* ************************************************ *
 * \class NodeAttributeChangeCommand
 * \brief Command to add a node
 * ************************************************ */
class o_qt_export NodeAttributeChangeCommand : public UndoCommand
{
public:

	//================================================
	// Constructors / Destructor
	//================================================

	NodeAttributeChangeCommand(serialization::Node* a_pNode, size_t a_uiAttributeIndex, const string& a_NewValue);
	~NodeAttributeChangeCommand();


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
	uint							m_uiGuid;
    size_t                          m_uiAttributeIndex;
    string                          m_strOldValue;
    string                          m_strNewValue;

};

} // qt 
} // phantom

#endif // phantom_qt_NodeAttributeChangeCommand_h__
