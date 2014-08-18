/* ******************* Includes ****************** */
#include "phantom/qt/qt.h"
#include "UnloadLibraryCommand.h"
#include "UnloadLibraryCommand.hxx"
#include <phantom/ModuleLoader.h>
/* *********************************************** */
o_registerN((phantom, qt), UnloadLibraryCommand);

namespace phantom { namespace qt {


//================================================
// Constructors / Destructor
//================================================

UnloadLibraryCommand::UnloadLibraryCommand(const string& a_strPath)
    : UndoCommand()
    , m_strPath(a_strPath)
{
    setName("Unload library '"+a_strPath+"'");
}

UnloadLibraryCommand::~UnloadLibraryCommand()
{

}


//================================================
// Operations
//================================================

void UnloadLibraryCommand::undo()
{
    phantom::moduleLoader()->loadLibrary(m_strPath, phantom::topMessage("modules"));
}

void UnloadLibraryCommand::redo()
{
    o_assert(phantom::moduleLoader()->libraryCanBeUnloaded(m_strPath));
    phantom::moduleLoader()->unloadLibrary(m_strPath, phantom::topMessage("modules"));
}

}}
