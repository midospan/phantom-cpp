/* ******************* Includes ****************** */
#include "phantom/qt/qt.h"
#include "MoveToTrashbinCommand.h"
#include "MoveToTrashbinCommand.hxx"
#include <phantom/serialization/Trashbin.h>
#include <phantom/serialization/Node.h>
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
    vector<phantom::data> allData;
    m_pDataBase->rootNode()->fetchDataCascade(allData);
    for(size_t i = 0; i<m_Guids.size(); ++i)
    {
        phantom::data d = m_pDataBase->getData(m_Guids[i]);
        for(auto it = allData.begin(); it != allData.end(); ++it)
        {
            if(m_pDataBase->getComponentDataOwner(*it) == d)
                m_Guids.push_back(m_pDataBase->getGuid(*it));
        }
    }
    std::sort(m_Guids.begin(), m_Guids.end());
    m_Guids.resize(std::unique(m_Guids.begin(), m_Guids.end())-m_Guids.begin());
    for(auto it = m_Guids.begin(); it != m_Guids.end(); ++it)
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

MoveToTrashbinCommand* MoveToTrashbinCommand::clone() const
{
    return o_new(MoveToTrashbinCommand)(m_pDataBase, m_Guids);
}

}}
