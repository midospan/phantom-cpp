#pragma once
#ifndef phantom_qt_LoadLibraryCommand_h__
#define phantom_qt_LoadLibraryCommand_h__


/* ****************** Includes ******************* */
#include <phantom/qt/UndoCommand.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, qt), LoadLibraryCommand);
/* *********************************************** */

namespace phantom { namespace qt {


/* ************************************************ *
 * \class LoadLibraryCommand
 * \brief Command to add a node
 * ************************************************ */
class o_qt_export LoadLibraryCommand : public UndoCommand
{
public:

	//================================================
	// Constructors / Destructor
	//================================================

	LoadLibraryCommand(const string& a_strPath);
	~LoadLibraryCommand();


	//================================================
	// Operations
	//================================================

	virtual void undo();
	virtual void redo();


protected:
	//================================================
	// Fields
	//================================================
    string                          m_strPath;

};

} // qt 
} // phantom

#endif // phantom_qt_LoadLibraryCommand_h__
