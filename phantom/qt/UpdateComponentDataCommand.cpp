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

UpdateComponentDataCommand::UpdateComponentDataCommand( serialization::DataBase* a_pDataBase, uint guid )
    : UndoCommand()
    , m_pDataBase(a_pDataBase)
    , m_bInitialized(false)
    , m_uiGuid(guid)
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
        vector<bitfield> last_addedModifiers;
        
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
                last_addedModifiers.clear();
                // Fetch in the new components to add
                for(size_t i = 0; i<to_treat.size(); ++i)
                {
                    serialization::Node* pNode = m_pDataBase->getNode(to_treat[i].first);
                    o_assert(pNode);
                    pNode->fetchUpdatedData(to_treat[i].first, last_components_to_add, last_components_to_remove, last_addedExpressions, last_addedModifiers, dataToSave);
                }
                o_assert(last_components_to_remove.size() == 0);
            }
            else 
            {
                m_pDataBase->getNode(d)->fetchUpdatedData(d, last_components_to_add, last_components_to_remove, last_addedExpressions, last_addedModifiers, dataToSave);
            }
            for(size_t i = 0; i<last_components_to_add.size(); ++i)
            {
                serialization::Node* pNode = m_pDataBase->getNode(last_components_to_add[i].second);
                m_AddedGuids.push_back(pNode->generateGuid());
                pNode->addComponentData(last_components_to_add[i].first, m_AddedGuids.back(), last_components_to_add[i].second, last_addedExpressions[i], last_addedModifiers[i]);
                m_SavedNodeIndexGuids.push_back(pNode->getGuid());
                m_pDataBase->setDataAttributeValue(last_components_to_add[i].first, "name", m_Delegate.empty() ? nameOf(last_components_to_add[i].first.type()) : m_Delegate(m_pDataBase, last_components_to_add[i].first));
            }
            for(size_t i = 0; i<last_components_to_remove.size(); ++i)
            {
                m_RemovedGuids.push_back(m_pDataBase->getGuid(last_components_to_remove[i].first));
                dataToSave.insert(last_components_to_remove[i].second);
            }
        }
        while(last_components_to_add.size());

        std::sort(m_RemovedGuids.begin(), m_RemovedGuids.end());
        std::unique(m_RemovedGuids.begin(), m_RemovedGuids.end());

        std::sort(m_SavedNodeIndexGuids.begin(), m_SavedNodeIndexGuids.end());
        std::unique(m_SavedNodeIndexGuids.begin(), m_SavedNodeIndexGuids.end());

        m_pDataBase->getTrashbin()->add(m_RemovedGuids);

        // save
        {
            auto pNode = m_pDataBase->getNode(d);
            m_SavedDataGuids.push_back(m_pDataBase->getGuid(d));
            for(auto it = dataToSave.begin(); it != dataToSave.end(); ++it)
            {
                m_SavedDataGuids.push_back(m_pDataBase->getGuid(*it));
            }
            std::sort(m_SavedDataGuids.begin(), m_SavedDataGuids.end());
            std::unique(m_SavedDataGuids.begin(), m_SavedDataGuids.end());
        }

        m_bInitialized = true;
    }
    else
    {
        m_pDataBase->getTrashbin()->add(m_RemovedGuids);
        m_pDataBase->getTrashbin()->restore(m_AddedGuids);
    }

    for(auto it = m_SavedDataGuids.begin(); it != m_SavedDataGuids.end(); ++it)
    {
        phantom::data d = m_pDataBase->getData(*it);
        if(!d.isNull())
        {
            serialization::Node* pNode = m_pDataBase->getNode(d);
            pNode->saveData(d);
        }
    }
    for(auto it = m_SavedNodeIndexGuids.begin(); it != m_SavedNodeIndexGuids.end(); ++it)
    {
        serialization::Node* pNode = m_pDataBase->getNode(*it);
        if(pNode) pNode->saveIndex();
    }
}

void UpdateComponentDataCommand::undo()
{
    m_pDataBase->getTrashbin()->add(m_AddedGuids);
    m_pDataBase->getTrashbin()->restore(m_RemovedGuids);

    for(auto it = m_SavedDataGuids.begin(); it != m_SavedDataGuids.end(); ++it)
    {
        phantom::data d = m_pDataBase->getData(*it);
        if(!d.isNull())
        {
            serialization::Node* pNode = m_pDataBase->getNode(d);
            pNode->saveData(d);
        }
    }
    for(auto it = m_SavedNodeIndexGuids.begin(); it != m_SavedNodeIndexGuids.end(); ++it)
    {
        serialization::Node* pNode = m_pDataBase->getNode(*it);
        if(pNode) pNode->saveIndex();
    }
}

UpdateComponentDataCommand* UpdateComponentDataCommand::clone() const
{
    return o_new(UpdateComponentDataCommand)(m_pDataBase, m_uiGuid);
}

}}
