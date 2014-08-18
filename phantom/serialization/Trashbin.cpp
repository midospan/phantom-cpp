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
/* *********************************************** */
o_registerN((phantom, serialization), Trashbin);

o_namespace_begin(phantom, serialization)
   
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
    for(auto it = guids.begin(); it != guids.end(); ++it)
    {
        uint guid = *it;
        o_assert(guid, "cannot add root node to trash bin");
        Node* pNode = m_pDataBase->getNode(guid);
        const string* strings;
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
            phantom::data d(m_pDataBase->getData(guid));
            o_assert(NOT(d.isNull()), "Guid is not used in the data base, neither for node or data");
            Node* pParentNode = m_pDataBase->getNode(d);
            o_emit m_pDataBase->dataAboutToBeRemoved(d, pParentNode);
            phantom::data owner = m_pDataBase->getComponentDataOwner(d);
            if(owner.isNull())
            {
                m_Parents[guid] = m_pDataBase->getNode(d)->getGuid();
            }
            else
            {
                m_ReferenceExpressions[guid] = m_pDataBase->getComponentDataReferenceExpression(d);
                m_Parents[guid] = m_pDataBase->getGuid(owner);
                m_pDataBase->unregisterComponentData(d);
            }
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

    struct sorter_parent_to_child
    {
        sorter_parent_to_child(const map<uint, uint>& a_Parents)
            : m_Parents(a_Parents)
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
                    return a_Guid0 < a_Guid1;
                }
            }
        }
        const map<uint, uint>& m_Parents;
    };

    struct node_sorter_parent_to_child
    {
        bool operator()(Node* a_pNode0, Node* a_pNode1) const 
        {
            if(a_pNode0->hasParentNodeCascade(a_pNode1))
            {
                return false;
            }
            else if(a_pNode1->hasParentNodeCascade(a_pNode0))
            {
                return true;
            }
            else 
            {
                return a_pNode0 < a_pNode1;
            }
        }
    };

    std::sort(sortedGuids.begin(), sortedGuids.end(), sorter_parent_to_child(m_Parents));
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
            Node* pParentNode = m_pDataBase->getNode(m_Parents[guid]);
            if(pParentNode == nullptr)
            {
                phantom::data ownerData = m_pDataBase->getData(m_Parents[guid]);
                if(ownerData.isNull())
                {
                    ownerData = guidToData[m_Parents[guid]];
                }
                o_assert(!ownerData.isNull());
                guidToOwnerData[guid] = ownerData;
                pParentNode = m_pDataBase->getNode(ownerData);
                o_assert(pParentNode);
            }
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
            m_pDataBase->registerData(d, guid, pNode);
            pNode->storeData(d);
            phantom::data ownerData = guidToOwnerData[guid];
            if(!ownerData.isNull())
            {
                m_pDataBase->registerComponentData(d, ownerData, expression);
            }

            // Restore component on its owner memory
            reflection::Expression* pExpression = phantom::expressionByName(expression);
            o_assert(pExpression);
            phantom::data castedData = d.cast(pExpression->getValueType()->removeReference()->removeConst()->removePointer());
            void* pAddress = castedData.address();
            pExpression->store(&pAddress);
            phantom::deleteElement(pExpression);

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
