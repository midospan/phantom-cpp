/*
    This file is part of PHANTOM
         P reprocessed 
         H igh-level 
         A llocator 
         N ested state-machines and 
         T emplate 
         O riented 
         M eta-programming

    For the latest infos and sources, see http://code.google.com/p/phantom-cpp

    Copyright (C) 2008-2011 by Vivien MILLET

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
    THE SOFTWARE
*/

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include "Trashbin.h"
#include "Trashbin.hxx"
#include "DataBase.h"
#include "Node.h"
#include "phantom/reflection/Expression.h"
#include <phantom/serialization/DataStateBase.h>
/* *********************************************** */
o_registerN((phantom, serialization), Trashbin);

o_namespace_begin(phantom, serialization)

struct add_sorter
{
    add_sorter(DataBase* a_pDataBase)
        : m_pDataBase(a_pDataBase) {}

    bool operator()(const phantom::data& d0, const phantom::data& d1)
    {
        phantom::data ownerD0 = m_pDataBase->getComponentDataOwner(d0);
        phantom::data ownerD1 = m_pDataBase->getComponentDataOwner(d1);

        // Compute the component order
        uint uiOrderD0 = 0;
        uint uiOrderD1 = 0;
        while(NOT(ownerD0.isNull()))
        {
            uiOrderD0++;
            ownerD0 = m_pDataBase->getComponentDataOwner(ownerD0);
        }
        while(NOT(ownerD1.isNull()))
        {
            uiOrderD1++;
            ownerD1 = m_pDataBase->getComponentDataOwner(ownerD1);
        }

        if(uiOrderD0 == uiOrderD1) 
        {
            if(uiOrderD0)
            {
                return m_pDataBase->getComponentDataReferenceExpression(d0) > m_pDataBase->getComponentDataReferenceExpression(d1);
            }
            return d0.address() < d1.address();
        }

        // by order
        return uiOrderD0 > uiOrderD1;
    }
    DataBase* m_pDataBase;
};

struct restore_sorter
{
    restore_sorter(const map<uint, uint>& a_Parents, const map<uint, string>& a_ReferenceExpressions)
        : m_Parents(a_Parents)
        , m_ReferenceExpressions(a_ReferenceExpressions)
    {

    }
    bool operator()(uint a_Guid0, uint a_Guid1) const 
    {
        auto found = m_Parents.find(a_Guid0);
        if((found != m_Parents.end()) AND (found->second == a_Guid1))
        {
            return false;
        }
        else 
        {
            found = m_Parents.find(a_Guid1);
            if((found != m_Parents.end()) AND (found->second == a_Guid0))
            {
                return true;
            }
            else 
            {
                auto foundRef0 = m_ReferenceExpressions.find(a_Guid0);
                auto foundRef1 = m_ReferenceExpressions.find(a_Guid1);
                if(foundRef0 == m_ReferenceExpressions.end() AND foundRef1 == m_ReferenceExpressions.end())
                {
                    return a_Guid0 < a_Guid1;
                }
                else if(foundRef0 == m_ReferenceExpressions.end())
                {
                    return true;
                }
                else if(foundRef1 == m_ReferenceExpressions.end())
                {
                    return false;
                }
                else 
                {
                    return foundRef0->second < foundRef1->second;
                }
            }
        }
    }
    const map<uint, uint>& m_Parents;
    const map<uint, string>& m_ReferenceExpressions;
};

Trashbin::Trashbin(DataBase* a_pDataBase, const string& a_strUrl)
    : m_pDataBase(a_pDataBase)
    , m_strUrl(a_strUrl)
{

}

Trashbin::~Trashbin()
{

}

void Trashbin::add( const vector<uint>& guids, vector<reflection::Expression*>* a_pRestoreReferenceExpressions /*= nullptr*/ )
{
    addEntries(guids);
    vector<Node*> nodesToDelete;
    std::set<Node*> nodesWithIndexToSave;
    phantom::vector<phantom::data> datas;
    const string* strings;
    for(auto it = guids.begin(); it != guids.end(); ++it)
    {
        uint guid = *it;
        o_assert(guid, "cannot add root node to trash bin");
        Node* pNode = m_pDataBase->getNode(guid);
        if(pNode)
        {
            m_Parents[guid] = pNode->getParentNode()->getGuid();
            strings = m_pDataBase->getAttributeValues(pNode); 
            for(size_t i = 0; i<m_pDataBase->getAttributeCount(); ++i)
            {
                m_Attributes[guid].push_back(strings[i]);
            }
            o_emit m_pDataBase->nodeAboutToBeRemoved(pNode, pNode->getParentNode());
            m_pDataBase->unregisterNode(pNode);
            pNode->getParentNode()->eraseNode(pNode);
            m_Nodes[guid] = true;
            nodesToDelete.push_back(pNode);
        }
        else 
        {
            datas.push_back(m_pDataBase->getData(guid));
        }
    }
    
    std::sort(datas.begin(), datas.end(), add_sorter(m_pDataBase));
    for(auto it = datas.begin(); it != datas.end(); ++it)
    {
        phantom::data d = *it;
        uint guid = m_pDataBase->getGuid(d);
        o_assert(NOT(d.isNull()), "Guid is not used in the data base, neither for node or data");
        Node* pParentNode = m_pDataBase->getNode(d);
        o_emit m_pDataBase->dataAboutToBeRemoved(d, pParentNode);
        phantom::data owner = m_pDataBase->getComponentDataOwner(d);
        uint ownerGuid = m_pDataBase->getGuid(owner);
        if(owner.isNull())
        {
            m_Parents[guid] = m_pDataBase->getNode(d)->getGuid();
        }
        else
        {
            m_ReferenceExpressions[guid] = m_pDataBase->getComponentDataReferenceExpression(d);
            m_Parents[guid] = m_pDataBase->getGuid(owner);
            m_pDataBase->unregisterComponentData(d);

            if(std::find(guids.begin(), guids.end(), ownerGuid) == guids.end())
            {
                // Remove component from its owner memory
                reflection::Expression* pExpression = phantom::expressionByName(m_ReferenceExpressions[guid]);
                o_assert(pExpression);
                phantom::data castedData = d.cast(pExpression->getValueType()->removeReference()->removeConst()->removePointer());
                void* pAddress = nullptr;
                pExpression->store(&pAddress);
                phantom::deleteElement(pExpression);
                pParentNode->saveData(owner);
            }
        }
        m_Modifiers[guid] = m_pDataBase->getModifiers(d);
        m_Types[guid] = d.type()->getQualifiedDecoratedName();
        strings = m_pDataBase->getAttributeValues(d.address()); 
        for(size_t i = 0; i<m_pDataBase->getAttributeCount(); ++i)
        {
            m_Attributes[guid].push_back(strings[i]);
        }
        vector<reflection::Expression*> restoreExpressions;
        m_pDataBase->clearDataReference(d, &restoreExpressions);
        for(auto it = restoreExpressions.begin(); it != restoreExpressions.end(); ++it)
        {
            m_RestoreExpressions[guid].push_back((*it)->getName()); // store expression by name (to be reevaluated and be updated to any reflection internal state change)
            phantom::deleteElement(*it); // then delete it
        }
        m_pDataBase->unregisterData(d);
        pParentNode->eraseData(d);
        d.destroy();
        nodesWithIndexToSave.insert(pParentNode);
        m_Nodes[guid] = false;
    }
    for(auto it = nodesToDelete.begin(); it != nodesToDelete.end(); ++it)
    {
        nodesWithIndexToSave.erase(*it);
    }
    // Save nodes' indexes
    for(auto it = nodesWithIndexToSave.begin(); it != nodesWithIndexToSave.end(); ++it)
    {
        (*it)->saveIndex();
    }
    // Delete nodes
    for(auto it = nodesToDelete.begin(); it != nodesToDelete.end(); ++it)
    {
        o_assert((*it)->isEmpty(), "A node added to the trashbin must have all its data added too or must be empty");
        o_dynamic_delete *it;
    }
}

void Trashbin::restore( const vector<uint>& guids )
{
    restoreEntries(guids);
    vector<uint> sortedGuids = guids;

    
    std::sort(sortedGuids.begin(), sortedGuids.end(), restore_sorter(m_Parents, m_ReferenceExpressions));
    map<Node*, vector<data>> dataToLoad;
    map<Node*, vector<uint>> guidToLoad;
    map<uint, data> guidToData;
    map<uint, data> guidToOwnerData;
    for(auto it = sortedGuids.begin(); it != sortedGuids.end(); ++it)
    {
        uint guid = *it;
        if(m_Nodes[guid]) // node
        {
            Node* pParentNode = m_pDataBase->getNode(m_Parents[guid]);
            Node* pNode = pParentNode->newChildNode(guid);
            o_assert(pParentNode->isLoaded() AND pNode->canLoad());
            pNode->load();
            for(size_t i = 0; i<m_pDataBase->getAttributeCount(); ++i)
            {
                m_pDataBase->setNodeAttributeValue(pNode, i, m_Attributes[guid][i]);
            }
        }
        else
        {
            string typeName = m_Types[guid];
            o_assert(m_Types.find(guid) != m_Types.end());
            reflection::Type* pType = m_pDataBase->solveTypeByName(typeName);
            o_assert(pType);
            void* pData = pType->allocate();
            phantom::data restoredData(pData, pType);
            Node* pParentNode = nullptr;
            auto parentIt = m_Parents.begin();
            uint curGuid = guid;
            while(pParentNode == nullptr AND (((parentIt = m_Parents.find(curGuid)) != m_Parents.end())))
            {
                uint parentGuid = parentIt->second;
                pParentNode = m_pDataBase->getNode(parentGuid);
                if(pParentNode == nullptr)
                {
                    phantom::data ownerData = m_pDataBase->getData(parentGuid);
                    if(ownerData.isNull())
                    {
                        ownerData = guidToData[parentGuid];
                    }
                    o_assert(!ownerData.isNull());
                    guidToOwnerData[guid] = ownerData;
                    pParentNode = m_pDataBase->getNode(ownerData);
                }
                curGuid = parentIt->second;
            }
            o_assert(pParentNode);
            guidToData[guid] = restoredData;
            dataToLoad[pParentNode].push_back(restoredData); // simply load data individualy with siblings (not node)
            guidToLoad[pParentNode].push_back(guid);
        }
    }
    /*for(auto it = nodesToCreate.begin(); it != nodesToCreate.end(); ++it)
    {
        Node* pNode = *it;
        o_assert(pNode->getParentNode());
        o_assert(pNode->getParentNode()->isLoaded() AND pNode->canLoad());
        pNode->load();
    }*/
    std::set<data> dataToSave;
    for(auto it = dataToLoad.begin(); it != dataToLoad.end(); ++it)
    {
        Node* pNode = it->first;
        auto& datas = it->second;
        auto& guids = guidToLoad[pNode];

        //o_assert(nodesToLoad.find(pNode) == nodesToLoad.end());
        pNode->build(datas);
        
        for(size_t i = 0; i<datas.size(); ++i)
        {
            phantom::data d = datas[i];
            uint guid = guids[i];
            const string& expression = m_ReferenceExpressions[guid];
            bitfield modifiers = m_Modifiers[guid];
            m_pDataBase->registerData(d, guid, pNode, modifiers);
            pNode->storeData(d);
            phantom::data ownerData = guidToOwnerData[guid];
            if(!ownerData.isNull())
            {
                m_pDataBase->registerComponentData(d, ownerData, expression, 0);
                if(std::find(datas.begin(), datas.end(), ownerData) == datas.end())
                {
                    // If owner data is not in trashbin 
                    // -> restore its component reference and save it
                    reflection::Expression* pExpression = phantom::expressionByName(expression);
                    o_assert(pExpression);
                    phantom::data castedData = d.cast(pExpression->getValueType()->removeReference()->removeConst()->removePointer());
                    void* pAddress = castedData.address();
                    pExpression->store(&pAddress);
                    phantom::deleteElement(pExpression);
                    dataToSave.insert(ownerData);
                }
            }

            for(size_t i = 0; i<m_pDataBase->getAttributeCount(); ++i)
            {
                m_pDataBase->setDataAttributeValue(d, i, m_Attributes[guid][i]);
            }
        }

        pNode->deserialize(m_pDataBase->m_uiSerializationFlag, datas);
        pNode->restore(m_pDataBase->m_uiSerializationFlag, datas);
        for(size_t i = 0; i<datas.size(); ++i)
        {
            o_emit m_pDataBase->dataAdded(datas[i], pNode);
        }
        pNode->saveIndex();
        if(m_pDataBase->getDataStateBase())
        {
            for(size_t i = 0; i<datas.size(); ++i)
            {
                pNode->loadDataState(datas[i], m_pDataBase->getDataStateBase()->getCurrentStateId());
            }
        }
    }
    for(auto it = sortedGuids.begin(); it != sortedGuids.end(); ++it)
    {
        uint guid = *it;
        vector<string>& restoreExpressions = m_RestoreExpressions[guid];
        for(auto it = restoreExpressions.begin(); it != restoreExpressions.end(); ++it)
        {
            phantom::setCurrentDataBase(m_pDataBase);
            reflection::Expression* pExpression = phantom::expressionByName(*it);
            o_assert(pExpression);
            pExpression->eval();
        }
        m_Parents.erase(guid);
        m_Types.erase(guid);
        m_Nodes.erase(guid);
        m_Attributes.erase(guid);
        m_ReferenceExpressions.erase(guid);
        m_Modifiers.erase(guid);
    }
    for(auto it = dataToSave.begin(); it != dataToSave.end(); ++it)
    {
        m_pDataBase->saveData(*it);
    }
}

void Trashbin::erase( const vector<uint>& guids )
{
    eraseEntries(guids);
    for(auto it = guids.begin(); it != guids.end(); ++it)
    {
        m_pDataBase->releaseGuid(*it);
        m_Parents.erase(*it);
        m_Types.erase(*it);
        m_Nodes.erase(*it);
    }
}


o_namespace_end(phantom, serialization)
