/* ******************* Includes ****************** */
#include "phantom/qt/qt.h"
#include "LoadLibraryCommand.h"
#include "LoadLibraryCommand.hxx"
#include <phantom/ModuleLoader.h>
/* *********************************************** */
o_registerN((phantom, qt), LoadLibraryCommand);

namespace phantom { namespace qt {


//================================================
// Constructors / Destructor
//================================================

LoadLibraryCommand::LoadLibraryCommand(const string& a_strPath)
    : UndoCommand()
    , m_strPath(a_strPath)
{
    setName("Load library '"+a_strPath+"'");
}

LoadLibraryCommand::~LoadLibraryCommand()
{

}


//================================================
// Operations
//================================================

void LoadLibraryCommand::undo()
{
    o_assert(phantom::moduleLoader()->libraryCanBeUnloaded(m_strPath), "Library cannot be unloaded");
    if(!phantom::moduleLoader()->unloadLibrary(m_strPath, phantom::topMessage("")))
    {
        abort();
    }
}

void LoadLibraryCommand::redo()
{
     if(!phantom::moduleLoader()->loadLibrary(m_strPath, phantom::topMessage("")))
    {
        abort();
    }
}

LoadLibraryCommand* LoadLibraryCommand::clone() const
{
    return o_new(LoadLibraryCommand)(m_strPath);
}

}}
