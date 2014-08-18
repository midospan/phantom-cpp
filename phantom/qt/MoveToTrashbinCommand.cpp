/* ******************* Includes ****************** */
#include "phantom/qt/qt.h"
#include "MoveToTrashbinCommand.h"
#include "MoveToTrashbinCommand.hxx"
#include <phantom/serialization/Trashbin.h>
/* *********************************************** */
o_registerN((phantom, qt), MoveToTrashbinCommand);

namespace phantom { namespace qt {


//================================================
// Constructors / Destructor
//================================================

MoveToTrashbinCommand::MoveToTrashbinCommand(serialization::DataBase* a_pDataBase, const vector<uint>& a_Guids)
: m_Guids(a_Guids)
, m_pDataBase(a_pDataBase)
{
    setName("Remove");
    for(auto it = a_Guids.begin(); it != a_Guids.end(); ++it)
    {
        pushCommand(o_new(UndoCommand)((m_pDataBase->getNode(*it) ? "Node '" : "Data '") + m_pDataBase->getAttributeValues(m_pDataBase->getData(*it).address())[0] + "' ("+lexical_cast<string>((void*)(*it))+")" ));
    }
}

MoveToTrashbinCommand::~MoveToTrashbinCommand()
{

}

//================================================
// Operations
//================================================

void MoveToTrashbinCommand::redo()
{
    m_pDataBase->getTrashbin()->add(m_Guids);
}

void MoveToTrashbinCommand::undo()
{
    m_pDataBase->getTrashbin()->restore(m_Guids);
}

}}
