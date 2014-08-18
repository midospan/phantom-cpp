#pragma once
#ifndef phantom_qt_UnloadLibraryCommand_h__
#define phantom_qt_UnloadLibraryCommand_h__


/* ****************** Includes ******************* */
#include <phantom/qt/UndoCommand.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, qt), UnloadLibraryCommand);
/* *********************************************** */

namespace phantom { namespace qt {


/* ************************************************ *
 * \class UnloadLibraryCommand
 * \brief Command to add a node
 * ************************************************ */
class o_qt_export UnloadLibraryCommand : public UndoCommand
{
public:

	//================================================
	// Constructors / Destructor
	//================================================

	UnloadLibraryCommand(const string& a_strPath);
	~UnloadLibraryCommand();


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

#endif // phantom_qt_UnloadLibraryCommand_h__
