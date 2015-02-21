/* ******************* Includes ****************** */
#include "phantom/qt/qt.h"
#include "UnloadLibraryCommand.h"
#include "UnloadLibraryCommand.hxx"
#include <phantom/reflection/Application.h>
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
    if(!phantom::application()->loadLibrary(m_strPath, phantom::topMessage("")))
    {
        abort();
    }
}

void UnloadLibraryCommand::redo()
{
    o_assert(phantom::application()->libraryCanBeUnloaded(m_strPath), "Library cannot be unloaded");
    if(!phantom::application()->unloadLibrary(m_strPath, phantom::topMessage("")))
    {
        abort();
    }
}

UnloadLibraryCommand* UnloadLibraryCommand::clone() const
{
    return o_new(UnloadLibraryCommand)(m_strPath);
}

}}
