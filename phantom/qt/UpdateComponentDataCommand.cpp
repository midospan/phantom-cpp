/* ******************* Includes ****************** */
#include "phantom/qt/qt.h"
#include "UpdateComponentDataCommand.h"
#include "UpdateComponentDataCommand.hxx"
#include <phantom/serialization/Node.h>
#include <phantom/serialization/Trashbin.h>
#include "SaveDataCommand.h"
/* *********************************************** */
o_registerN((phantom, qt), UpdateComponentDataCommand);

namespace phantom { namespace qt {


//================================================
// Constructors / Destructor
//================================================
    
UpdateComponentDataCommand::UpdateComponentDataCommand( serialization::DataBase* a_pDataBase, const phantom::data& a_Data )
    : UndoCommand()
    , m_pDataBase(a_pDataBase)
    , m_bInitialized(false)
    , m_uiGuid(m_pDataBase->getGuid(a_Data))
{
    o_assert(m_uiGuid != 0xffffffff);
    o_assert(m_pDataBase);
}

UpdateComponentDataCommand::~UpdateComponentDataCommand()
{

}


//================================================
// Operations
//================================================


void UpdateComponentDataCommand::redo()
{
    // Move removed data to trashbin
    if(!m_bInitialized)
    {
        vector<data_pair> components_to_add;
        vector<data_pair> components_to_remove;
        vector<string> addedExpressions;
     
        vector<data_pair> last_components_to_add;
        vector<data_pair> last_components_to_remove;
        vector<string> last_addedExpressions;
        
        phantom::data d = m_pDataBase->getData(m_uiGuid);
        o_assert(!d.isNull());
        std::set<phantom::data> dataToSave;
        do
        {
            if(last_components_to_add.size())
            {
                vector<data_pair> to_treat = last_components_to_add;
                vector<string> to_treat_expressions = last_addedExpressions;
                last_components_to_add.clear();
                last_components_to_remove.clear();
                last_addedExpressions.clear();
                // Fetch in the new components to add
                for(size_t i = 0; i<to_treat.size(); ++i)
                {
                    serialization::Node* pNode = m_pDataBase->getNode(to_treat[i].first);
                    o_assert(pNode);
                    pNode->fetchUpdatedData(to_treat[i].first, last_components_to_add, last_components_to_remove, last_addedExpressions, dataToSave);
                }
                o_assert(last_components_to_remove.size() == 0);
            }
            else 
            {
                m_pDataBase->getNode(d)->fetchUpdatedData(d, last_components_to_add, last_components_to_remove, last_addedExpressions, dataToSave);
            }
            for(size_t i = 0; i<last_components_to_add.size(); ++i)
            {
                serialization::Node* pNode = m_pDataBase->getNode(last_components_to_add[i].second);
                m_AddedGuids.push_back(pNode->generateGuid());
                pNode->addComponentData(last_components_to_add[i].first, m_AddedGuids.back(), last_components_to_add[i].second, last_addedExpressions[i]);
                m_pDataBase->setDataAttributeValue(last_components_to_add[i].first, "name", nameOf(last_components_to_add[i].first.type()));
            }
            for(size_t i = 0; i<last_components_to_remove.size(); ++i)
            {
                m_RemovedGuids.push_back(m_pDataBase->getGuid(last_components_to_remove[i].first));
                dataToSave.insert(last_components_to_remove[i].second);
            }
        }
        while(last_components_to_add.size());
        
        m_pDataBase->getTrashbin()->add(m_RemovedGuids);
//         for(size_t i = 0; i<components_to_add.size(); ++i)
//         {
//             serialization::Node* pNode = m_pDataBase->getNode(components_to_add[i].second);
//             if(pNode)
//             {
//                 m_AddedGuids.push_back(pNode->generateGuid());
//                 pNode->addComponentData(components_to_add[i].first, m_AddedGuids.back(), components_to_add[i].second, addedExpressions[i]);
//                 m_pDataBase->setDataAttributeValue(components_to_add[i].first, "name", nameOf(components_to_add[i].first.type()));
//                 dataToSave.insert(components_to_add[i].second);
//             }
// #if !defined(NDEBUG)
//             else 
//             {
//                 bool found = false;
//                 // Owner has been removed, check if its the case
//                 for(auto it = components_to_remove.begin(); it != components_to_remove.end(); ++it)
//                 {
//                     if(it->first == components_to_add[i].second)
//                     {
//                         found = true;
//                         break;
//                     }
//                 }
//                 o_assert(found, "Cannot find missing added data in removed data list")
//             }
// #endif
//         }
        for(auto it = dataToSave.begin(); it != dataToSave.end(); ++it)
        {
            if(m_pDataBase->getNode(*it))
            {
                pushCommand(o_new(SaveDataCommand)(m_pDataBase->getNode(*it), *it));
            }
        }
        m_bInitialized = true;
    }
    else
    {
        m_pDataBase->getTrashbin()->add(m_RemovedGuids);
        m_pDataBase->getTrashbin()->restore(m_AddedGuids);
    }
}

void UpdateComponentDataCommand::undo()
{
    m_pDataBase->getTrashbin()->add(m_AddedGuids);
    m_pDataBase->getTrashbin()->restore(m_RemovedGuids);
}

}}
