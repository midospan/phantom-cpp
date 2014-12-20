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
#include <phantom/serialization/DataBase.h>
#include <phantom/serialization/DataBase.hxx>
#include <phantom/serialization/DataStateBase.h>
#include <phantom/serialization/Node.h>
#include <phantom/serialization/Record.h>
#include <phantom/reflection/DataExpression.h>
#include <phantom/reflection/ConstantExpression.h>
#include <phantom/reflection/CompositionClass.h>
#include <phantom/reflection/AggregationClass.h>
#include <phantom/reflection/ComponentClass.h>
#include <phantom/ModuleLoader.h>
/* *********************************************** */
o_registerN((phantom, serialization), DataBase);

o_namespace_begin(phantom, serialization)

struct runtime_type_info_sorter
{
    bool operator()(runtime_type_info const& r0, runtime_type_info const& r1) const
    {
        return r0.baseInfo.pointer < r1.baseInfo.pointer;
    }
};

DataBase::DataBase( const string& url, uint a_uiSerializationFlag ) 
: m_strUrl(url)
, m_pRootNode(nullptr)
, m_uiLoadedDataSize(0)
, m_uiLoadedDataResetSize(0)
, m_uiLoadedDataSerializedSize(0)
, m_uiSerializationFlag(a_uiSerializationFlag)
, m_pDataStateBase(nullptr)
, m_eActionOnMissingType(e_ActionOnMissingType_IgnoreAndDestroyData)
, m_bDataSlotsBlocked(false)
, m_pCurrentRecord(nullptr)
, m_pUndoRecord(nullptr)
, m_pRedoRecord(nullptr)
, m_bModuleSlotsBlocked(false)
{
}

DataBase::~DataBase( void )
{
}

o_initialize_cpp(DataBase)
{

}

o_terminate_cpp(DataBase)
{
    if(m_pRootNode)
    {
        destroyNode(m_pRootNode);
    }
}

void            DataBase::moveNode(Node* a_pNode, Node* a_pNewParent)
{
    if(NOT(canMoveNode(a_pNode,a_pNewParent))) 
    {
        o_exception(exception::base_exception, "forbidden action");
    }
    Node* pOldParent = a_pNode->getParentNode();
    if(pOldParent == a_pNewParent) return;
    pOldParent->eraseNode(a_pNode);
    moveNodeEntry(a_pNode, a_pNewParent);
    a_pNewParent->storeNode(a_pNode);
    o_emit nodeMoved(a_pNode, pOldParent, a_pNewParent);
}

void            DataBase::moveData(const phantom::data& a_Data, Node* a_pNewOwnerNode)
{
    if(NOT(canMoveData(a_Data,a_pNewOwnerNode)))
    {
        o_exception(exception::base_exception, "forbidden action");
    }
    void* pAddress = a_Data.address();
    uint guid = getGuid(pAddress);
    o_assert(guid != o_invalid_guid);
    Node* pOldOwnerNode = getNode(pAddress);
    if(pOldOwnerNode == a_pNewOwnerNode) return;
    pOldOwnerNode->eraseData(a_Data);
    o_assert(isDataCompatibleWithNode(a_Data, a_pNewOwnerNode));
    moveDataEntry(a_Data, guid, pOldOwnerNode, a_pNewOwnerNode);
    a_pNewOwnerNode->storeData(a_Data);
    o_emit dataMoved(a_Data, pOldOwnerNode, a_pNewOwnerNode);
}

void DataBase::registerData( const phantom::data& a_Data, uint a_Guid, Node* a_pNode, modifiers_t modifiers )
{
    o_assert(hasDataEntry(a_Data, a_Guid, a_pNode), "Data must have an entry created to be registered");
    o_assert(NOT(isDataRegistered(a_Data.address())), "Data already registered");
    o_assert(a_Guid != o_invalid_guid);
    o_assert(isDataCompatibleWithNode(a_Data, a_pNode));
    m_DataModifiers[a_Guid] |= modifiers;
    m_uiLoadedDataSize += a_Data.type()->getSize();
    m_uiLoadedDataResetSize += a_Data.type()->getResetSize();
    m_uiLoadedDataSerializedSize += a_Data.type()->getSerializedSize();
    m_GuidBase.add(a_Guid, a_Data);
    size_t fieldCount = getAttributeCount();
    if(fieldCount)
    {
        string* values = o_allocate_n(fieldCount, string);
        size_t i = 0;
        for(;i<fieldCount;++i)
        {
            new (&values[i]) string();
        }
        o_assert(m_AttributeValues.find(a_Guid) == m_AttributeValues.end());
        m_AttributeValues[a_Guid] = values;
    }
    if(NOT(a_Data.type()->isNative()))
    {
        incrementRuntimeTypeReferenceCount(a_Data.type());
    }
    m_DataNodeMap[a_Guid] = a_pNode->getGuid();
    a_pNode->storeData(a_Data);
    if(m_pCurrentRecord)
    {
        m_pCurrentRecord->dataRegistered(a_Data);
    }
    o_emit dataRegistered(a_Data);
}

void DataBase::unregisterData( const phantom::data& a_Data )
{
    o_assert(isDataRegistered(a_Data.address()), "Data not registered");

    if(m_pCurrentRecord)
    {
        m_pCurrentRecord->dataAboutToBeUnregistered(a_Data);
    }
    o_emit dataAboutToBeUnregistered(a_Data);

    if(!getComponentDataOwner(a_Data).isNull())
        unregisterComponentData(a_Data);
    uint guid = getGuid(a_Data);
    auto found = m_DataNodeMap.find(guid);
    o_assert(found != m_DataNodeMap.end());
    getNode(found->second)->eraseData(a_Data);
    m_DataNodeMap.erase(found);
    if(NOT(a_Data.type()->isNative()))
    {
        decrementRuntimeTypeReferenceCount(a_Data.type());
    }
    m_uiLoadedDataSize -= a_Data.type()->getSize();
    m_uiLoadedDataResetSize -= a_Data.type()->getResetSize();
    m_uiLoadedDataSerializedSize -= a_Data.type()->getSerializedSize();
    m_GuidBase.remove(a_Data.address());
    size_t fieldCount = getAttributeCount();
    if(fieldCount)
    {
        attribute_map::iterator found = m_AttributeValues.find(guid);
        string* values = found->second;
        size_t i = 0;
        for(;i<fieldCount;++i)
        {
            values[i].~string();
        }
        o_deallocate_n(values, fieldCount, string);
        m_AttributeValues.erase(found);
    }
}

void DataBase::registerNode( Node* a_pNode )
{
    o_assert(hasNodeEntry(a_pNode), "Node must have an entry created to be registered");
    o_assert(NOT(isNodeRegistered(a_pNode)), "Node already registered");
    o_assert(a_pNode->getGuid() != o_invalid_guid);
    m_GuidBase.add(a_pNode->getGuid(), phantom::data(a_pNode, classOf(a_pNode)));
    size_t fieldCount = getAttributeCount();
    if(fieldCount)
    {
        string* values = o_allocate_n(fieldCount, string);
        size_t i = 0;
        for(;i<fieldCount;++i)
        {
            new (&values[i]) string();
        }
        o_assert(m_AttributeValues.find(a_pNode->getGuid()) == m_AttributeValues.end());
        m_AttributeValues[a_pNode->getGuid()] = values;
    }
    o_connect(a_pNode, loaded(), this, slotNodeLoaded());
    o_connect(a_pNode, aboutToBeunloaded(), this, slotNodeAboutToBeUnloaded());
}

void DataBase::unregisterNode( Node* a_pNode )
{
    o_assert(a_pNode != rootNode(), "Root node cannot be unregistered");
    o_assert(isNodeRegistered(a_pNode), "Node not registered in database");
    o_disconnect(a_pNode, loaded(), this, slotNodeLoaded());
    o_disconnect(a_pNode, aboutToBeunloaded(), this, slotNodeAboutToBeUnloaded());
    m_GuidBase.remove(a_pNode);
    size_t fieldCount = getAttributeCount();
    if(fieldCount)
    {
        attribute_map::iterator found = m_AttributeValues.find(a_pNode->getGuid());
        string* values = found->second;
        size_t i = 0;
        for(;i<fieldCount;++i)
        {
            values[i].~string();
        }
        o_deallocate_n(values, fieldCount, string);
        m_AttributeValues.erase(found);
    }
    o_assert(a_pNode->getParentNode(), "Node should have a parent");
}

Node* DataBase::internalAddNewNode( Node* a_pParentNode )
{
    return internalAddNewNode(generateGuid(), a_pParentNode);
}

Node* DataBase::internalAddNewNode( uint a_uiGuid, Node* a_pParentNode )
{
    Node* pNewNode = createNode(a_uiGuid, a_pParentNode);
    internalAddNode(pNewNode, a_uiGuid, a_pParentNode);
    return pNewNode;
}

void DataBase::internalAddNode( Node* a_pNode, uint a_uiGuid, Node* a_pParentNode )
{
	createNodeEntry(a_pNode);	
	registerNode(a_pNode);
	a_pNode->save();
	o_emit nodeAdded(a_pNode, a_pParentNode);
}
/*

void DataBase::internalDeleteNode( Node* a_pNode )
{
    o_emit nodeAboutToBeRemoved(a_pNode, a_pNode->getParentNode());
    uint guid = getGuid(a_pNode);
    o_assert(guid != o_invalid_guid);
    unregisterNode(a_pNode);
    destroyNodeEntry(a_pNode);
    destroyNode(a_pNode);
    releaseGuid(guid);
}*/

void DataBase::replaceDataInfo( const phantom::data& a_Old, const phantom::data& a_New )
{
    // Guid base
    uint guid = m_GuidBase.getGuid(a_Old);
    m_GuidBase.remove(a_Old.address());
    m_GuidBase.add(guid, a_New);

    m_uiLoadedDataSize -= a_Old.type()->getSize();
    m_uiLoadedDataSize += a_New.type()->getSize();
}

reflection::Type* DataBase::solveTypeByName( const string& a_strQualifiedDecoratedName ) const
{
    reflection::Type* pType = phantom::typeByName(a_strQualifiedDecoratedName);
    if(pType) return pType;
    return getPlaceholderTypeByName(a_strQualifiedDecoratedName);
}

void    DataBase::registerPlaceholderTypeByName(const string& a_strQualifiedDecoratedName, const string& a_strPlaceHolderName)
{
    o_assert(getPlaceholderTypeName(a_strQualifiedDecoratedName).empty());
    o_assert(a_strPlaceHolderName != a_strQualifiedDecoratedName);
    m_PlaceholderTypeByNameMap[a_strQualifiedDecoratedName] = a_strPlaceHolderName;
    if(m_pCurrentRecord)
    {
        m_pCurrentRecord->placeholderTypeByNameRegistered(a_strQualifiedDecoratedName, a_strPlaceHolderName);
    }
}

void    DataBase::unregisterPlaceholderTypeByName(const string& qualifiedName)
{
    o_assert(NOT(getPlaceholderTypeName(qualifiedName).empty()));
    m_PlaceholderTypeByNameMap.erase(qualifiedName);
}

reflection::Type* DataBase::getPlaceholderTypeByName( const string& qualifiedName ) const
{
    auto found = m_PlaceholderTypeByNameMap.find(qualifiedName);
    return (found != m_PlaceholderTypeByNameMap.end()) ? solveTypeByName(found->second) : nullptr;
}

const string& DataBase::getPlaceholderTypeName( const string& qualifiedName ) const
{
    static string nullstr;
    auto found = m_PlaceholderTypeByNameMap.find(qualifiedName);
    return found != m_PlaceholderTypeByNameMap.end() ? found->second : nullstr;
}

void DataBase::unregisterAllByPlaceholderTypeName( const string& placeholder )
{
    vector<string> keysToRemove;
    auto it = m_PlaceholderTypeByNameMap.begin();
    auto end = m_PlaceholderTypeByNameMap.end();
    for(;it!=end;++it)
    {
        if(it->second == placeholder)
            keysToRemove.push_back(it->first);
    }
    {
        auto it = keysToRemove.begin();
        auto end = keysToRemove.end();
        for(;it!=end;++it)
        {
            m_PlaceholderTypeByNameMap.erase(*it);
        }
    }
}

void DataBase::savePlaceholderTypesByName( property_tree& a_Out )
{
    for(auto it = m_PlaceholderTypeByNameMap.begin(); it != m_PlaceholderTypeByNameMap.end(); ++it)
    {
        a_Out.add(it->first, it->second);
    }
}

void DataBase::loadPlaceholderTypesByName( const property_tree& a_In )
{
    for(auto it = a_In.begin(); it != a_In.end(); ++it)
    {
        m_PlaceholderTypeByNameMap[it->first] = it->second.get_value<string>();
    }
}

reflection::Type* DataBase::solveTypeById(uint id) const
{
    o_assert(false, "implementation not complete");
    return nullptr;
}

void DataBase::clearDataReference( const phantom::data& a_data, vector<reflection::Expression*>* a_pRestoreReferenceExpressions )
{
    rootNode()->clearDataReferenceCascade(a_data, a_pRestoreReferenceExpressions);
}

void DataBase::replaceDataReference( const phantom::data& a_old, const phantom::data& a_New ) 
{
    rootNode()->replaceDataReferenceCascade(a_old, a_New, nullptr);
}

boolean DataBase::canMoveNode( Node* a_pNode, Node* a_pNewParent ) const
{
    Node* pOldParent = a_pNode->getParentNode();
    o_assert(pOldParent);
    vector<Node*> dependentNodes;
    pOldParent->getAllDescendantWhichDependsOn(a_pNode, dependentNodes);
    vector<Node*>::const_iterator it = dependentNodes.begin();
    vector<Node*>::const_iterator end = dependentNodes.end();
    for(;it!=end;++it)
    {
        Node* pNode = *it;
        if(NOT( pNode == a_pNewParent OR pNode->hasParentNodeCascade(a_pNewParent) ))
        {
            return false;
        }
    }
    return true;
}

boolean DataBase::canMoveData( const phantom::data& a_Data, Node* a_pNewParent ) const
{
    Node* pOldParent = getNode(a_Data);
    o_assert(pOldParent);
    vector<Node*> dependentNodes;
    pOldParent->getAllDescendantWhichDependsOn(a_Data, dependentNodes);
    if(pOldParent->containsDataWhichDependsOnData(a_Data))
        dependentNodes.push_back(pOldParent);
    vector<Node*>::const_iterator it = dependentNodes.begin();
    vector<Node*>::const_iterator end = dependentNodes.end();
    for(;it!=end;++it)
    {
        Node* pNode = *it;
        if(NOT( pNode == a_pNewParent OR pNode->hasParentNodeCascade(a_pNewParent) ))
        {
            return false;
        }
    }
    return a_pNewParent->acceptsData(a_Data);
}
void DataBase::rebuildData( phantom::data& a_inOutData, reflection::Type* a_pOld, reflection::Type* a_pNewType, vector<data>& a_Old, vector<data>& a_New, uint a_uiStateId /*= o_invalid_guid*/ )
{
    o_assert(a_inOutData.type() == a_pOld);
    o_assert((a_pOld->asClass() != nullptr) == (a_pNewType->asClass() != nullptr), "to be replaced, types must be of the same 'type', both classes or both not classes");

    phantom::data newData(a_pNewType->allocate(), a_pNewType);
    a_pNewType->build(newData.address());
    phantom::data oldData = a_inOutData;

    // Replace by the new data
    a_inOutData = newData;

    a_Old.push_back(oldData);
    a_New.push_back(newData);
}

void DataBase::saveState( uint a_uiState )
{
    o_assert(m_pDataStateBase, "You must associate a DataStateBase with this DataBase to be able to load/save states");
    if(rootNode()->isLoaded())
    {
        rootNode()->saveStateCascade(m_pDataStateBase, a_uiState);
    }
}

void DataBase::loadState( uint a_uiState )
{
    o_assert(m_pDataStateBase, "You must associate a DataStateBase with this DataBase to be able to load/save states");
    if(rootNode()->isLoaded())
    {
        rootNode()->loadStateCascade(m_pDataStateBase, a_uiState);
    }
}

void DataBase::save()
{
    if(rootNode()->isLoaded())
    {
        rootNode()->saveCascade();
    }
}

Node* DataBase::rootNode()
{
    if (m_pRootNode == NULL)
    {
        m_pRootNode = createNode(0, NULL);
        if(NOT(hasNodeEntry(m_pRootNode)))
        {
            createNodeEntry(m_pRootNode);
            m_pRootNode->save();
        }
        registerNode(m_pRootNode);
    }
    return m_pRootNode;
}

boolean DataBase::isDataCompatibleWithNode( const phantom::data& a_Data, Node* a_pOwnerNode ) const
{
    return NOT(a_pOwnerNode->childNodesContainDependencyOfDeep(a_Data))
        AND a_pOwnerNode->acceptsData(a_Data);
}

void DataBase::dataDestroyed( void* a_pAddress )
{
    Node* pDataNode = getNode(a_pAddress);
    if(pDataNode) return; // Means that this instance is not in the database
    pDataNode->removeData(a_pAddress);
}

const string& DataBase::getDataAttributeValue( const phantom::data& a_Data, size_t attributeIndex ) const
{
    o_assert(attributeIndex < getAttributeCount());
    static string null_string;
    attribute_map::const_iterator found = m_AttributeValues.find(getGuid(a_Data));
    if(found != m_AttributeValues.end())
    {
        return (found->second)[attributeIndex];
    }
    return null_string;
}

const string& DataBase::getDataAttributeValue( const phantom::data& a_Data, const string& attributeName ) const
{
    return getDataAttributeValue(a_Data, getAttributeIndex(attributeName));
}

const string& DataBase::getNodeAttributeValue( Node* a_pNode, size_t attributeIndex ) const
{
    o_assert(attributeIndex < getAttributeCount());
    static string null_string;
    attribute_map::const_iterator found = m_AttributeValues.find(a_pNode->getGuid());
    if(found != m_AttributeValues.end())
    {
        return (found->second)[attributeIndex];
    }
    return null_string;
}

const string& DataBase::getNodeAttributeValue( Node* a_pNode, const string& attributeName ) const
{
    return getNodeAttributeValue(a_pNode, getAttributeIndex(attributeName));
}

const string* DataBase::getDataAttributeValues( const phantom::data& a_Data )
{
    attribute_map::const_iterator found = m_AttributeValues.find(getGuid(a_Data));
    return found != m_AttributeValues.end() ? found->second : NULL;
}

const string* DataBase::getNodeAttributeValues( Node* a_pNode ) const
{
    attribute_map::const_iterator found = m_AttributeValues.find(a_pNode->getGuid());
    return found != m_AttributeValues.end() ? found->second : NULL;
}

const string* DataBase::getAttributeValues( const phantom::data& a_Data ) const
{
    attribute_map::const_iterator found = m_AttributeValues.find(getGuid(a_Data));
    return found != m_AttributeValues.end() ? found->second : NULL;
}

const string* DataBase::getAttributeValues( Node* a_pNode ) const
{
    attribute_map::const_iterator found = m_AttributeValues.find(a_pNode->getGuid());
    return found != m_AttributeValues.end() ? found->second : NULL;
}

void DataBase::setDataAttributeValue( const phantom::data& a_Data, size_t attributeIndex, const string& value )
{
    o_assert(attributeIndex < getAttributeCount());
    m_AttributeValues[getGuid(a_Data)][attributeIndex] = value;
    o_emit dataAttributeValueChanged(a_Data, attributeIndex, value);
    getNode(a_Data)->saveDataAttributes(a_Data);
}

void DataBase::setDataAttributeValue( const phantom::data& a_Data, const string& fieldName, const string& value )
{
    setDataAttributeValue(a_Data, getAttributeIndex(fieldName), value);
}

void DataBase::setNodeAttributeValue( Node* a_pNode, size_t attributeIndex, const string& value )
{
    o_assert(attributeIndex < getAttributeCount());
    m_AttributeValues[a_pNode->getGuid()][attributeIndex] = value;
    o_emit nodeAttributeValueChanged(a_pNode, attributeIndex, value);
    a_pNode->saveAttributes();
}

void DataBase::setNodeAttributeValue( Node* a_pNode, const string& fieldName, const string& value )
{
    setNodeAttributeValue(a_pNode, getAttributeIndex(fieldName), value);
}

size_t DataBase::addAttribute( const string& a_name )
{
    o_assert(m_GuidBase.isEmpty(), "Cannot add dataMember after data");
    m_AttributeNames.push_back(a_name);
    return m_AttributeNames.size()-1;
}

size_t DataBase::getAttributeIndex( const string& a_name ) const
{
    size_t i = 0;
    size_t count = m_AttributeNames.size();
    for(;i<count;++i)
    {
        if(m_AttributeNames[i] == a_name) return i;
    }
    return ~size_t(0);
}

const string& DataBase::getAttributeName( size_t attributeIndex ) const
{
    o_assert(attributeIndex < getAttributeCount());
    return m_AttributeNames[attributeIndex];
}

void DataBase::registerComponentData( const data& a_Data, const data& a_Owner, const string& a_ReferenceExpression )
{
    uint guid = getGuid(a_Data);
    //o_assert(guid != o_invalid_guid);
    o_assert(m_ComponentDataOwnerMap.find(guid) == m_ComponentDataOwnerMap.end());
    o_assert(m_ComponentReferenceExpressionMap.find(guid) == m_ComponentReferenceExpressionMap.end());
    m_ComponentDataOwnerMap[guid] = getGuid(a_Owner);
    m_ComponentReferenceExpressionMap[guid] = a_ReferenceExpression;
}

void DataBase::unregisterComponentData( const data& a_Data )
{
    uint guid = getGuid(a_Data);
    o_assert(guid != o_invalid_guid);
    o_assert(m_ComponentDataOwnerMap.find(guid) != m_ComponentDataOwnerMap.end());
    o_assert(m_ComponentReferenceExpressionMap.find(guid) != m_ComponentReferenceExpressionMap.end());
    m_ComponentDataOwnerMap.erase(guid);
    m_ComponentReferenceExpressionMap.erase(guid);
}

void DataBase::saveData( const phantom::data& a_Data )
{
    getNode(a_Data)->saveData(a_Data);
    if(m_pDataStateBase)
    {
        saveDataState(a_Data, m_pDataStateBase->getCurrentStateId());
    }
}

void DataBase::saveDataState( const phantom::data& a_Data, uint a_uiState )
{
    getNode(a_Data)->saveDataState(a_Data, a_uiState);
}

uint DataBase::getGuid( const phantom::data& a_Data ) const
{
    return m_GuidBase.getGuid(a_Data.address());
}

modifiers_t DataBase::getDataModifiers( const phantom::data& a_Data ) const
{
    auto found = m_DataModifiers.find(getGuid(a_Data));
    return found == m_DataModifiers.end() ? 0 : found->second;
}

void DataBase::setDataModifiers( const phantom::data& a_Data, modifiers_t a_Modifiers)
{
    m_DataModifiers[getGuid(a_Data)] = a_Modifiers;
    o_emit dataModifiersChanged(a_Data, a_Modifiers);
}

void DataBase::addDataModifiers( const phantom::data& a_Data, modifiers_t a_Modifiers)
{
    m_DataModifiers[getGuid(a_Data)] |= a_Modifiers;
    o_emit dataModifiersChanged(a_Data, a_Modifiers);
}

void DataBase::removeDataModifiers( const phantom::data& a_Data, modifiers_t a_Modifiers)
{
    m_DataModifiers[getGuid(a_Data)] &= ~a_Modifiers;
    o_emit dataModifiersChanged(a_Data, a_Modifiers);
}

uint DataBase::getGuid( Node* a_pNode ) const
{
    return m_GuidBase.getGuid(a_pNode);
}

boolean DataBase::containsDataAddress( void* a_pData ) const
{
    return m_GuidBase.getGuid(phantom::baseOf(a_pData)) != o_invalid_guid;
}

boolean DataBase::isDataRegistered( void* a_pData ) const
{
    return m_GuidBase.getGuid(phantom::baseOf(a_pData)) != o_invalid_guid;
}

boolean DataBase::isNodeRegistered( Node* a_pNode ) const
{
    return m_GuidBase.getGuid(a_pNode) != o_invalid_guid;
}

void DataBase::internalRemoveNode( Node* a_pNode, uint a_uiGuid, Node* a_pParentNode )
{
    o_assert(a_uiGuid != o_invalid_guid);
    o_emit nodeAboutToBeRemoved(a_pNode, a_pParentNode);
    unregisterNode(a_pNode);
    destroyNodeEntry(a_pNode);
    releaseGuid(a_uiGuid);
}

bool DataBase::isComponentDataOwner( const phantom::data& a_Data ) const
{
    uint guid = getGuid(a_Data);
    o_assert(guid != o_invalid_guid);
    component_data_owner_map::const_iterator it = m_ComponentDataOwnerMap.begin();
    component_data_owner_map::const_iterator end = m_ComponentDataOwnerMap.end();
    for (;it != end; it++)
    {
        if (it->second == guid)
        {
            return true;
        }
    }
    return false;
}

Node* DataBase::getNode( uint a_uiGuid ) const
{
    return as<Node*>(m_GuidBase.getData(a_uiGuid).address());
}

size_t DataBase::getRuntimeTypeReferenceCount( reflection::Type* a_pType ) const
{
    for(auto it = m_RuntimeTypes.begin(); it != m_RuntimeTypes.end(); ++it)
    {
        if(it->baseInfo.pointer == a_pType) return it->refCount;
    }
    return 0;
}

const runtime_type_info& DataBase::getRuntimeTypeInfo( reflection::Type* a_pType ) const
{
    static const runtime_type_info null_info;
    for(auto it = m_RuntimeTypes.begin(); it != m_RuntimeTypes.end(); ++it)
    {
        if(it->baseInfo.pointer == a_pType) return *it;
    }
    return null_info;
}

bool DataBase::hasRuntimeType( reflection::Type* a_pType ) const
{
    for(auto it = m_RuntimeTypes.begin(); it != m_RuntimeTypes.end(); ++it)
    {
        if(it->baseInfo.pointer == a_pType) return true;
    }
    return false;
}

void DataBase::incrementRuntimeTypeReferenceCount( reflection::Type* a_pType )
{
    for(auto it = m_RuntimeTypes.begin(); it != m_RuntimeTypes.end(); ++it)
    {
        if(it->baseInfo.pointer == a_pType) 
        {
            it->refCount++;
            return;
        }
    }
    o_assert(false);
}

void DataBase::decrementRuntimeTypeReferenceCount( reflection::Type* a_pType )
{
    for(auto it = m_RuntimeTypes.begin(); it != m_RuntimeTypes.end(); ++it)
    {
        if(it->baseInfo.pointer == a_pType) 
        {
            o_assert(it->refCount);
            it->refCount--;
            return;
        }
    }
    o_assert(false);
}

void DataBase::registerType(reflection::Type* a_pType)
{
    o_assert(a_pType);
    o_assert(getRuntimeTypeInfo(a_pType).isNull());
    m_RuntimeTypes.push_back(runtime_type_info(a_pType->getQualifiedDecoratedName(), a_pType));
}

void DataBase::unregisterType(reflection::Type* a_pType)
{
    o_assert(a_pType);
    const runtime_type_info& info = getRuntimeTypeInfo(a_pType);
    o_assert(!info.isNull());
    if(info.refCount)
    {
        o_exception(exception::base_exception, "A type being removed still has data which uses it in the data base");
    }
    for(auto it = m_RuntimeTypes.begin(); it != m_RuntimeTypes.end(); ++it)
    {
        if(it->baseInfo.pointer == a_pType) 
        {
            m_RuntimeTypes.erase(it);
            return;
        }
    }
    o_assert(false);
}

void DataBase::moduleElementAdded( reflection::LanguageElement* a_pLanguageElement )
{
    if(m_bModuleSlotsBlocked) return;
    reflection::Type* pType = a_pLanguageElement->asClassType();
    if(pType AND NOT(pType->isNative()) AND pType->asClass())
    {
        createTypeEntry(pType);
        registerType(pType);
        if(m_pCurrentRecord)
        {
            m_pCurrentRecord->typeAdded(pType);
        }
        else if(m_pUndoRecord)
        {
            m_pUndoRecord->typeAdded(pType);
        }
        else if(m_pRedoRecord)
        {
            m_pRedoRecord->typeAdded(pType);
        }
    }
}

void DataBase::moduleElementAboutToBeRemoved( reflection::LanguageElement* a_pLanguageElement )
{
    if(m_bModuleSlotsBlocked) return;
    reflection::Type* pType = a_pLanguageElement->asType();
    if(pType AND NOT(pType->isNative()) AND pType->asClass())
    {
        if(m_pCurrentRecord)
        {
            m_pCurrentRecord->typeAboutToBeRemoved(pType);
        }
        else if(m_pUndoRecord)
        {
            m_pUndoRecord->typeAboutToBeRemoved(pType);
        }
        else if(m_pRedoRecord)
        {
            m_pRedoRecord->typeAboutToBeRemoved(pType);
        }
        unregisterType(pType);
        destroyTypeEntry(pType);
    }
}

void DataBase::moduleElementsAboutToBeReplaced( const vector<reflection::LanguageElement*>& a_OldLanguageElements )
{
    if(m_bModuleSlotsBlocked) return;
    o_assert(m_ReplacementOldTypeNames.empty());
    vector<reflection::Type*> typesAboutToBeReplaced;
    o_assert(m_UnloadedGuids.empty());
    for(auto it = a_OldLanguageElements.begin(); it != a_OldLanguageElements.end(); ++it)
    {
        reflection::Type* pOldType = (*it)->asType();
        if(pOldType)
        {
            o_assert(NOT(pOldType->isNative()));
            m_ReplacementOldTypeNames.push_back(pOldType->getQualifiedDecoratedName());
            vector<phantom::data> obsoleteData;
            rootNode()->fetchDataOfTypeCascade(pOldType, obsoleteData); // TODO replace by a fetchDataDependingOnType(pOldType, obsoleteData);
            for(auto it = obsoleteData.begin(); it != obsoleteData.end(); ++it)
            {
                unloadData(*it);
            }
            typesAboutToBeReplaced.push_back(pOldType);
        }
    }
    if(m_pCurrentRecord)
    {
        m_pCurrentRecord->typesAboutToBeReplaced(as<Module*>(connection::sender()), typesAboutToBeReplaced);
    }
    else if(m_pUndoRecord)
    {
        m_pUndoRecord->typesAboutToBeReplaced(as<Module*>(connection::sender()), typesAboutToBeReplaced);
    }
    else if(m_pRedoRecord)
    {
        m_pRedoRecord->typesAboutToBeReplaced(as<Module*>(connection::sender()), typesAboutToBeReplaced);
    }
    for(auto it = typesAboutToBeReplaced.begin(); it != typesAboutToBeReplaced.end(); ++it)
    {
        unregisterType(*it);
        destroyTypeEntry(*it);
    }
}

void DataBase::moduleElementsReplaced( const vector<reflection::LanguageElement*>& a_OldLanguageElements, const vector<reflection::LanguageElement*>& a_NewLanguageElements )
{
    if(m_bModuleSlotsBlocked) return;
    vector<reflection::Type*> typesReplaced;
    for(size_t i = 0; i<a_NewLanguageElements.size(); ++i)
    {
        reflection::Type* pNewType = a_NewLanguageElements[i]->asType();
        if(pNewType)
        {
            createTypeEntry(pNewType);
            registerType(pNewType);
            o_assert(NOT(pNewType->isNative()));
            if(pNewType->getQualifiedDecoratedName() != m_ReplacementOldTypeNames[i]) // New and old type names don't match
            {
                registerPlaceholderTypeByName(m_ReplacementOldTypeNames[i], pNewType->getQualifiedDecoratedName());
            }
            typesReplaced.push_back(pNewType);
        }
    }
    if(m_pCurrentRecord)
    {
        m_pCurrentRecord->typesReplaced(as<Module*>(connection::sender()), typesReplaced);
    }
    else if(m_pUndoRecord)
    {
        m_pUndoRecord->typesReplaced(as<Module*>(connection::sender()), typesReplaced);
    }
    else if(m_pRedoRecord)
    {
        m_pRedoRecord->typesReplaced(as<Module*>(connection::sender()), typesReplaced);
    }
    reloadData();
    m_ReplacementOldTypeNames.clear();
}

void DataBase::moduleLoaded( Module* a_pModule, size_t a_uiOldCount, size_t a_uiNewCount)
{
    if(m_bModuleSlotsBlocked) return;
    if(a_uiOldCount == 0)
    {
        o_connect(a_pModule, elementAdded(reflection::LanguageElement*), this, moduleElementAdded(reflection::LanguageElement*));
        o_connect(a_pModule, elementAboutToBeRemoved(reflection::LanguageElement*), this, moduleElementAboutToBeRemoved(reflection::LanguageElement*));
        o_connect(a_pModule, elementsAboutToBeReplaced(const vector<reflection::LanguageElement*>&), this, moduleElementsAboutToBeReplaced(const vector<reflection::LanguageElement*>&));
        o_connect(a_pModule, elementsReplaced(const vector<reflection::LanguageElement*>&, const vector<reflection::LanguageElement*>&), this, moduleElementsReplaced(const vector<reflection::LanguageElement*>&, const vector<reflection::LanguageElement*>&));

        vector<reflection::Type*> types;
        loadTypes(a_pModule, &types);
        for(auto it = types.begin(); it != types.end(); ++it)
        {
            a_pModule->addLanguageElement(*it);
        }
    }
}

void DataBase::moduleUnloaded( Module* a_pModule, size_t a_uiOldCount, size_t a_uiNewCount)
{
    if(m_bModuleSlotsBlocked) return;
    if(a_uiNewCount == 0)
    {
        vector<reflection::Type*> toRemove;
        for(auto it = m_RuntimeTypes.begin(); it != m_RuntimeTypes.end(); ++it)
        {
            reflection::Type* pType = m_RuntimeTypes.back().baseInfo.pointer;
            if(pType->getModule() == a_pModule)
            {
                toRemove.push_back(pType);
            }
        }
        for(auto it = toRemove.begin(); it != toRemove.end(); ++it)
        {
            a_pModule->removeLanguageElement(*it);
        }
        o_disconnect(a_pModule, elementAdded(reflection::LanguageElement*), this, moduleElementAdded(reflection::LanguageElement*));
        o_disconnect(a_pModule, elementAboutToBeRemoved(reflection::LanguageElement*), this, moduleElementAboutToBeRemoved(reflection::LanguageElement*));
        o_disconnect(a_pModule, elementsAboutToBeReplaced(const vector<reflection::LanguageElement*>&), this, moduleElementsAboutToBeReplaced(const vector<reflection::LanguageElement*>&));
        o_disconnect(a_pModule, elementsReplaced(const vector<reflection::LanguageElement*>&, const vector<reflection::LanguageElement*>&), this, moduleElementsReplaced(const vector<reflection::LanguageElement*>&, const vector<reflection::LanguageElement*>&));
    }
}

string DataBase::formatIndexExpression( size_t a_uiIndex )
{
    string indexString = lexical_cast<string>(a_uiIndex);
    while(indexString.size() < 10)  // Format all index like this : [         1]
        //                              [         2]
        //                              [     10000]
    {
        indexString = ' ' + indexString;
    }
    return indexString;
}

string DataBase::formatIndexedExpression(const string& a_strExpression, size_t a_uiIndex, const char chars[2])
{
    return "("+a_strExpression+")"+ chars[0] + formatIndexExpression(a_uiIndex) + chars[1];
}

void DataBase::connectData( const phantom::data& a_Data, bool a_bCollectComponents )
{
    Node* pNode = getNode(a_Data);
    uint guid = getGuid(a_Data);
    vector<reflection::Expression*> expressions;
    auto pConstant = phantom::constant<uint>(getGuid(a_Data));

    // Create an expression referencing our data
    auto pExpression = o_new(reflection::DataExpression)(this, o_new(reflection::ConstantExpression)(pConstant)) ;

    a_Data.type()->fetchExpressions(pExpression 
        , expressions
        , &reflection::Type::NoFilter
        , m_uiSerializationFlag);

    reflection::Class* pDataBaseClass = classOf(this);

    for(auto it = expressions.begin(); it != expressions.end(); ++it)
    {
        reflection::Expression* pExpression = *it;
        reflection::Type* pEffectiveValueType = pExpression->getValueType()->removeConstReference();
        reflection::LanguageElement* pHatchedElement = pExpression->getHatchedElement();
        reflection::Property* pProperty = pHatchedElement ? pHatchedElement->asProperty() : nullptr;
        reflection::InstanceDataMember* pInstanceDataMember = pHatchedElement ? pHatchedElement->asInstanceDataMember() : nullptr;
        reflection::CompositionClass* pCompositionClass = pEffectiveValueType->asCompositionClass();
        reflection::AggregationClass* pAggregationClass = pEffectiveValueType->asAggregationClass();
        reflection::ComponentClass* pComponentClass = pEffectiveValueType->asComponentClass();
        // We look for pointer properties with notification signals 
        if(pProperty AND pProperty->getSignal()) 
        {
            reflection::InstanceMemberFunction* pSlot = pDataBaseClass->getSlot("propertyChanged()");
            o_verify(phantom::connect(a_Data.address(), pProperty->getSignal(), this, pSlot), "");
                
            variant& value = m_PropertyValues[guid][pProperty];
            value.setType(pProperty->getEffectiveValueType());
            pProperty->getValue(a_Data.cast(pProperty->getOwnerClassType()).address(), value.buffer());
            if(pProperty->getEffectiveValueType()->getDataPointerLevel() == 1)
            {
                // Add new reference if found
                {
                    void* pNewPointer = *(void**)value.buffer();
                    phantom::data d = pNewPointer;
                    uint newGuid = getGuid(d);
                    if(newGuid != o_invalid_guid)
                    {
                        addDataReferenceExpression(newGuid, pExpression->translate());
                    }
                }
            }
        } 
        else if(pInstanceDataMember AND pInstanceDataMember->isSaved(m_uiSerializationFlag))
        {
            if(pCompositionClass)
                // We look for composition/aggregation data members
            {
                void* pComposition = pExpression->loadEffectiveAddress();
                o_assert(pComposition);
                const rtti_data& rd = rttiDataOf(pComposition, pCompositionClass);
                if(!rd.isNull())
                {
                    o_verify(phantom::connect( rd, pCompositionClass->getInsertedSignal(), rttiDataOf(this), pDataBaseClass->getSlot("componentInserted(size_t, void*)")), "");
                    o_verify(phantom::connect( rd, pCompositionClass->getAboutToBeRemovedSignal(), rttiDataOf(this), pDataBaseClass->getSlot("componentAboutToBeRemoved(size_t, void*)")), "");
                    o_verify(phantom::connect( rd, pCompositionClass->getSwappedSignal(), rttiDataOf(this), pDataBaseClass->getSlot("componentSwapped(size_t, size_t, void*, void*)")), "");
                    o_verify(phantom::connect( rd, pCompositionClass->getMovedSignal(), rttiDataOf(this), pDataBaseClass->getSlot("componentMoved(size_t, size_t, void*)")), "");
                    o_verify(phantom::connect( rd, pCompositionClass->getReplacedSignal(), rttiDataOf(this), pDataBaseClass->getSlot("componentReplaced(size_t, void*, void*)")), "");
                }
                // Remember the expression string associated with the access to the composition
                if(a_bCollectComponents)
                {
                    size_t count = pCompositionClass->count(pComposition);
                    for(size_t i = 0 ;i<count; ++i)
                    {
                        void* pComponent = nullptr;
                        pCompositionClass->get(pComposition, i, &pComponent);
                        if(pComponent != nullptr AND getGuid(pComponent) == o_invalid_guid)
                        {
                            string expression = formatIndexedExpression(pExpression->translate(), i, "()");
                            pNode->addComponentData(pComponent, a_Data, expression, pExpression->getModifiers());
//                                 if(m_pCurrentRecord)
//                                 {
//                                     m_pCurrentRecord->dataCompositionChanged(a_Data, oldValueExpression, newValueExpression);
//                                 }
//                                 o_emit dataCompositionChanged(a_Data, oldValueExpression, newValueExpression);
                        }
                    }
                }
            }
            else if(pAggregationClass)
            {
                void* pAggregation = pExpression->loadEffectiveAddress();
                o_assert(pAggregation);
                const rtti_data& rd = rttiDataOf(pAggregation, pAggregationClass);
                if(!rd.isNull())
                {
                    o_verify(phantom::connect( rd, pAggregationClass->getInsertedSignal(), rttiDataOf(this), pDataBaseClass->getSlot("aggregateInserted(size_t, void*)")), "");
                    o_verify(phantom::connect( rd, pAggregationClass->getAboutToBeRemovedSignal(), rttiDataOf(this), pDataBaseClass->getSlot("aggregateAboutToBeRemoved(size_t, void*)")), "");
                    o_verify(phantom::connect( rd, pAggregationClass->getSwappedSignal(), rttiDataOf(this), pDataBaseClass->getSlot("aggregateSwapped(size_t, size_t, void*, void*)")), "");
                    o_verify(phantom::connect( rd, pAggregationClass->getMovedSignal(), rttiDataOf(this), pDataBaseClass->getSlot("aggregateMoved(size_t, size_t, void*)")), "");
                    o_verify(phantom::connect( rd, pAggregationClass->getReplacedSignal(), rttiDataOf(this), pDataBaseClass->getSlot("aggregateReplaced(size_t, void*, void*)")), "");
                }
                string expression = pExpression->translate();
                size_t count = pAggregationClass->count(pAggregation);
                for(size_t i = 0 ;i<count; ++i)
                {
                    void* pAggregate = nullptr;
                    pAggregationClass->get(pAggregation, i, &pAggregate);
                    if(pAggregate != nullptr)
                    {
                        uint aggregateGuid = getGuid(pAggregate);
                        if(aggregateGuid != o_invalid_guid)
                        {
                            addDataReferenceExpression(aggregateGuid, formatIndexedExpression(expression, i, "()"));
//                                 string expression = formatIndexedExpression(pExpression->translate(), i, "()");
//                                 string oldValueExpression = expression+"=0";
//                                 string newValueExpression = expression+"=&(@"+lexical_cast<string>(getGuid(pAggregate))+")";
//                                 if(m_pCurrentRecord)
//                                 {
//                                     m_pCurrentRecord->dataAggregationChanged(a_Data, oldValueExpression, newValueExpression);
//                                 }
//                                 o_emit dataAggregationChanged(a_Data, oldValueExpression, newValueExpression);
                        }
                    }
                }
            }
            else if(pComponentClass)
            {
                void* pComponent = pExpression->loadEffectiveAddress();
                o_assert(pComponent);
                const rtti_data& rd = rttiDataOf(pComponent, pComponentClass);
                if(!rd.isNull())
                {
                    o_verify(phantom::connect( rd, pComponentClass->getChangedSignal(), rttiDataOf(this), pDataBaseClass->getSlot("componentChanged(void*, void*)")), "");
                }
                string expression = pExpression->translate();
                void* pPointer = nullptr;
                pComponentClass->get(pComponent, &pPointer);
                if(pPointer != nullptr AND getGuid(pPointer) == o_invalid_guid)
                {
                    pNode->addComponentData(pPointer, a_Data, expression, pExpression->getModifiers());
                }
            }
        }
       
        o_dynamic_delete (pExpression);
    }
    if(m_pCurrentRecord)
    {
        m_pCurrentRecord->dataConnected(a_Data);
    }
    o_emit dataConnected(a_Data);
}

void DataBase::disconnectData( const phantom::data& a_Data )
{
    if(m_pCurrentRecord)
    {
        m_pCurrentRecord->dataAboutToBeDisconnected(a_Data);
    }
    o_emit dataAboutToBeDisconnected(a_Data);
    uint guid = getGuid(a_Data);
    // Disconnections will be done on deleting data
    m_PropertyValues.erase(guid);
    m_DataReferenceExpressions.erase(guid);
}

void DataBase::componentChanged(void* a_pOldPointer, void* a_pNewPointer)
{
    if(m_bDataSlotsBlocked) return;

    uint newGuid = getGuid(a_pNewPointer);

    // If new pointer is a reloaded guid, we skip adding the component
    if(isDataUnloaded(newGuid))
        return;

    uint oldGuid = getGuid(a_pOldPointer);

    // If old pointer is an unloaded guid, we skip removing the component
    if(isDataUnloaded(oldGuid))
        return;

    void* pComponent = connection::sender();
    reflection::Signal* pSignal = connection::signal();
    reflection::ComponentClass* pComponentClass = pSignal->getOwnerClass()->asComponentClass();
    const rtti_data& rd = rttiDataOf(pComponent, pComponentClass);
    auto owner = rd.root()->data();
    uint ownerGuid = getGuid(owner);
    o_assert(!owner.isNull());
    string componentExpression = rd.referenceExpressionString(this);
    o_assert(componentExpression.size());
    o_assert(newGuid == o_invalid_guid);
    if(oldGuid != o_invalid_guid)
    {
        o_assert(oldGuid != o_invalid_guid);
        if(newGuid == o_invalid_guid)
        {
            if(isDataUnloaded(ownerGuid))
            {
                unloadData(a_pOldPointer);
            }
            else 
            {
                removeComponentData(a_pOldPointer);
            }
        }
        else 
        {
            getNode(owner)->replaceComponentData(a_pOldPointer, a_pNewPointer);
        }
    }
    else // Old component null 
    {
        o_assert(oldGuid == o_invalid_guid);
        if(!isDataUnloaded(ownerGuid))
        {
            getNode(owner)->addComponentData(a_pNewPointer, owner, componentExpression, pComponentClass->getModifiers());
        }
    }
}

void DataBase::componentInserted( size_t a_uiIndex, void* a_pComponent )
{
    if(m_bDataSlotsBlocked) return;
    uint newGuid = getGuid(a_pComponent);
    if(isDataUnloaded(newGuid))
        return;
    o_assert(newGuid == o_invalid_guid);
    void* pComposition = connection::sender();
    reflection::Signal* pSignal = connection::signal();
    reflection::CompositionClass* pCompositionClass = as<reflection::CompositionClass*>(pSignal->getOwnerClass());
    const rtti_data& rd = rttiDataOf(pComposition, pCompositionClass);
    auto owner = rd.root()->data();
    uint ownerGuid = getGuid(owner);
    o_assert(NOT(isDataUnloaded(ownerGuid)));
    const rtti_data& new_component_rd = rttiDataOf(a_pComponent);
    size_t count = pCompositionClass->count(pComposition);

    string compositionExpression = rd.referenceExpressionString(this);
    o_assert(compositionExpression.size());
    phantom::data d = new_component_rd.data();
    for(size_t i = a_uiIndex; i< count; ++i)
    {
        void* pComponent = nullptr;
        pCompositionClass->get(pComposition, i, &pComponent);
        if(i == a_uiIndex)
        {
            getNode(owner)->addComponentData(d, owner, formatIndexedExpression(compositionExpression, i, "()"), pCompositionClass->getModifiers());
            string expression = formatIndexedExpression(compositionExpression, a_uiIndex, "()");
            string oldValueExpression = expression+"=nullptr";
            string newValueExpression = expression+"=&(@("+lexical_cast<string>(getGuid(a_pComponent))+"))";
            if(m_pCurrentRecord)
            {
                m_pCurrentRecord->dataCompositionChanged(owner, oldValueExpression, newValueExpression);
            }
            o_emit dataCompositionChanged(owner, oldValueExpression, newValueExpression);
        }
        else setComponentDataReferenceExpression(pComponent, formatIndexedExpression(compositionExpression, i, "()"));
    }
}

void DataBase::componentAboutToBeRemoved( size_t a_uiIndex, void* a_pComponent )
{
    if(m_bDataSlotsBlocked) return;
    uint oldGuid = getGuid(a_pComponent);
    if(isDataUnloaded(oldGuid))
        return;
    void* pComposition = connection::sender();
    reflection::Signal* pSignal = connection::signal();
    reflection::CompositionClass* pCompositionClass = as<reflection::CompositionClass*>(pSignal->getOwnerClass());
    const rtti_data& rd = rttiDataOf(pComposition, pCompositionClass);
    auto owner = rd.root()->data();
    uint ownerGuid = getGuid(owner);
    const rtti_data& new_component_rd = rttiDataOf(a_pComponent);
    size_t count = pCompositionClass->count(pComposition);
    string compositionExpression = rd.referenceExpressionString(this);
    o_assert(compositionExpression.size());

    string expression = formatIndexedExpression(compositionExpression, a_uiIndex, "()");
    string oldValueExpression = expression+"=&(@("+lexical_cast<string>(getGuid(a_pComponent))+"))";
    string newValueExpression = expression+"=nullptr";
    if(m_pCurrentRecord)
    {
        m_pCurrentRecord->dataCompositionChanged(owner, oldValueExpression, newValueExpression);
    }
    o_emit dataCompositionChanged(owner, oldValueExpression, newValueExpression);

    if(isDataUnloaded(ownerGuid))
    {
        unloadData(a_pComponent);
    }
    else 
    {
        removeComponentData(a_pComponent);
    }

    // The components after the one removed must have their index decremented in their reference expression
    for(size_t i = a_uiIndex+1; i< count; ++i)
    {
        void* pComponent = nullptr;
        pCompositionClass->get(pComposition, i, &pComponent);
        setComponentDataReferenceExpression(pComponent, formatIndexedExpression(compositionExpression, i-1, "()"));
    }
}

void DataBase::componentReplaced( size_t a_uiIndex, void* a_pOldComponent, void* a_pNewComponent )
{
    if(m_bDataSlotsBlocked) return;
    void* pComposition = connection::sender();
    reflection::Signal* pSignal = connection::signal();
    reflection::CompositionClass* pCompositionClass = as<reflection::CompositionClass*>(pSignal->getOwnerClass());

    const rtti_data& rd = rttiDataOf(pComposition, pCompositionClass);
    auto owner = rd.root()->data();
    uint ownerGuid = getGuid(owner);
    const rtti_data& old_component_rd = rttiDataOf(a_pOldComponent);
    const rtti_data& new_component_rd = rttiDataOf(a_pNewComponent);
    getNode(owner)->replaceComponentData(old_component_rd.data(), new_component_rd.data());

    string compositionExpression = rd.referenceExpressionString(this);
    string indexString = formatIndexExpression(a_uiIndex);
    string oldValueExpression = compositionExpression+".set("+indexString+", &(@("+lexical_cast<string>(getGuid(a_pOldComponent))+")))";
    string newValueExpression = compositionExpression+".set("+indexString+", &(@("+lexical_cast<string>(getGuid(a_pNewComponent))+")))";

    if(m_pCurrentRecord)
    {
        m_pCurrentRecord->dataCompositionChanged(owner, oldValueExpression, newValueExpression);
    }
    o_emit dataCompositionChanged(owner, oldValueExpression, newValueExpression);
}

void DataBase::componentMoved( size_t a_uiOldIndex, size_t a_uiNewIndex, void* a_pComponent )
{
    if(m_bDataSlotsBlocked) return;
    void* pComposition = connection::sender();
    
    reflection::Signal* pSignal = connection::signal();
    reflection::CompositionClass* pCompositionClass = as<reflection::CompositionClass*>(pSignal->getOwnerClass());
    const rtti_data& rd = rttiDataOf(pComposition, pCompositionClass);
    auto owner = rd.root()->data();
    string compositionExpression = rd.referenceExpressionString(this);
    o_assert(compositionExpression.size());
    if(a_uiOldIndex > a_uiNewIndex)
    {
        for(size_t i = a_uiNewIndex+1; i<=a_uiOldIndex; ++i)
        {
            void* pComponent = nullptr;
            void* pPrevComponent = nullptr;
            pCompositionClass->get(pComposition, i, &pComponent);
            pCompositionClass->get(pComposition, i-1, &pPrevComponent);
            setComponentDataReferenceExpression(pComponent, getComponentDataReferenceExpression(pPrevComponent));
        }
    }
    else 
    {
        for(size_t i = a_uiOldIndex; i<a_uiNewIndex; ++i)
        {
            void* pComponent = nullptr;
            void* pNextComponent = nullptr;
            pCompositionClass->get(pComposition, i, &pComponent);
            pCompositionClass->get(pComposition, i+1, &pNextComponent);
            setComponentDataReferenceExpression(pComponent, getComponentDataReferenceExpression(pNextComponent));
        }
    }
    setComponentDataReferenceExpression(a_pComponent, formatIndexedExpression(compositionExpression, a_uiNewIndex, "()"));

    string oldIndexString = formatIndexExpression(a_uiOldIndex);
    string newIndexString = formatIndexExpression(a_uiNewIndex);
    string oldValueExpression = compositionExpression+".move("+newIndexString+", "+oldIndexString+")";
    string newValueExpression = compositionExpression+".move("+oldIndexString+", "+newIndexString+")";

    if(m_pCurrentRecord)
    {
        m_pCurrentRecord->dataCompositionChanged(owner, oldValueExpression, newValueExpression);
    }
    o_emit dataCompositionChanged(owner, oldValueExpression, newValueExpression);
}

void DataBase::componentSwapped( size_t a_uiOldIndex, size_t a_uiNewIndex, void* a_pComponent0, void* a_pComponent1 )
{
    if(m_bDataSlotsBlocked) return;
    void* pComposition = connection::sender();
    reflection::Signal* pSignal = connection::signal();
    const rtti_data& component_rd0 = rttiDataOf(a_pComponent0);
    const rtti_data& component_rd1 = rttiDataOf(a_pComponent1);

    reflection::CompositionClass* pCompositionClass = as<reflection::CompositionClass*>(pSignal->getOwnerClass());
    const rtti_data& rd = rttiDataOf(pComposition, pCompositionClass);
    o_assert(!rd.isNull());

    auto owner = rd.root()->data();

    o_assert(getComponentDataOwner(component_rd0.data()) == getComponentDataOwner(component_rd1.data()));
    // Swap reference expressions
    string exp0 = getComponentDataReferenceExpression(component_rd0.base);
    setComponentDataReferenceExpression(component_rd0.base, getComponentDataReferenceExpression(component_rd1.base));
    setComponentDataReferenceExpression(component_rd1.base, exp0);
    string oldIndexString = formatIndexExpression(a_uiOldIndex);
    string newIndexString = formatIndexExpression(a_uiNewIndex);
    string compositionExpression = rd.referenceExpressionString(this);
    o_assert(compositionExpression.size());
    string oldValueExpression = compositionExpression+".swap("+newIndexString+", "+oldIndexString+")";
    string newValueExpression = compositionExpression+".swap("+oldIndexString+", "+newIndexString+")";

    if(m_pCurrentRecord)
    {
        m_pCurrentRecord->dataCompositionChanged(owner, oldValueExpression, newValueExpression);
    }
    o_emit dataCompositionChanged(owner, oldValueExpression, newValueExpression);
}

void DataBase::propertyChanged()
{
    if(m_bDataSlotsBlocked) return;
    phantom::data d(connection::sender());
    uint guid = getGuid(d);
    reflection::Property* pProperty = connection::signal()->getProperty();
    o_assert(pProperty);
    string dataExpression = "@("+lexical_cast<string>(getGuid(d))+")";
    string propertyAccessExpression = "("+dataExpression+")."+pProperty->getName();
    // Backup value
    variant& value = m_PropertyValues[guid][pProperty];
    variant oldValue = value;
    o_assert(value.type() == pProperty->getEffectiveValueType());
    pProperty->getValue(d.cast(pProperty->getOwnerClassType()).address(), value.buffer());
    if(pProperty->getEffectiveValueType()->getDataPointerLevel() == 1)
    {
        // Remove old reference if found
        {
            void* pOldPointer = *(void**)oldValue.buffer();
            phantom::data d = pOldPointer;
            uint oldGuid = getGuid(d);
            if(oldGuid != o_invalid_guid)
            {
                removeDataReferenceExpression(oldGuid, propertyAccessExpression);
            }
        }
        // Add new reference if found
        {
            void* pNewPointer = *(void**)value.buffer();
            phantom::data d = pNewPointer;
            uint newGuid = getGuid(d);
            if(newGuid != o_invalid_guid)
            {
                addDataReferenceExpression(newGuid, propertyAccessExpression);
            }
        }

    }
    if(m_pCurrentRecord)
    {
        m_pCurrentRecord->dataPropertyValueChanged(d, pProperty, oldValue, value);
    }
    o_emit dataPropertyValueChanged(d, pProperty, oldValue, value);
    if(m_pCurrentRecord == nullptr AND m_pUndoRecord == nullptr AND m_pRedoRecord == nullptr)
    {
        saveData(d);
    }
}

void DataBase::aggregateInserted( size_t a_uiIndex, void* a_pAggregate )
{
    void* pAggregation = connection::sender();
    reflection::Signal* pSignal = connection::signal();
    reflection::AggregationClass* pAggregationClass = as<reflection::AggregationClass*>(pSignal->getOwnerClass());
    const rtti_data& rd = rttiDataOf(pAggregation, pAggregationClass);
    auto owner = rd.root()->data();
    string baseExpression = rd.referenceExpressionString(this);
    o_assert(baseExpression.size());
    string expression = formatIndexedExpression(baseExpression, a_uiIndex, "()");
    uint aggregateGuid = getGuid(a_pAggregate);
    string oldValueExpression = expression+"=nullptr";
    string newValueExpression;
    if(aggregateGuid != o_invalid_guid)
    {
        newValueExpression = expression+"=&(@("+lexical_cast<string>(aggregateGuid)+"))";
        addDataReferenceExpression(aggregateGuid, expression);
    }
    else 
    {
        newValueExpression = expression+"=static_cast<"+(pAggregationClass->getAggregateClass()->getQualifiedDecoratedName())+"*>(0x"+lexical_cast<string>(a_pAggregate)+")";
    }
    if(m_pCurrentRecord)
    {
        m_pCurrentRecord->dataAggregationChanged(owner, oldValueExpression, newValueExpression);
    }
    o_emit dataAggregationChanged(owner, oldValueExpression, newValueExpression);
}

void DataBase::aggregateAboutToBeRemoved( size_t a_uiIndex, void* a_pAggregate )
{
    void* pAggregation = connection::sender();
    reflection::Signal* pSignal = connection::signal();
    reflection::AggregationClass* pAggregationClass = as<reflection::AggregationClass*>(pSignal->getOwnerClass());
    const rtti_data& rd = rttiDataOf(pAggregation, pAggregationClass);
    o_assert(!rd.isNull());
    auto owner = rd.root()->data();
    string baseExpression = rd.referenceExpressionString(this);
    o_assert(baseExpression.size());
    string expression = formatIndexedExpression(baseExpression, a_uiIndex, "()");
    uint aggregateGuid = getGuid(a_pAggregate);
    string oldValueExpression;
    if(aggregateGuid != o_invalid_guid)
    {
        oldValueExpression = expression+"=(&(@("+lexical_cast<string>(aggregateGuid)+")))";
        removeDataReferenceExpression(aggregateGuid, expression);
    }
    else 
    {
        oldValueExpression = expression+"=static_cast<"+(pAggregationClass->getAggregateClass()->getQualifiedDecoratedName())+"*>(0x"+lexical_cast<string>(a_pAggregate)+")";
    }
    string newValueExpression = expression+"=nullptr";
    if(m_pCurrentRecord)
    {
        m_pCurrentRecord->dataAggregationChanged(owner, oldValueExpression, newValueExpression);
    }
    o_emit dataAggregationChanged(owner, oldValueExpression, newValueExpression);
}

void DataBase::aggregateReplaced( size_t a_uiIndex, void* a_pOldAggregate, void* a_pNewAggregate )
{
    void* pAggregation = connection::sender();
    reflection::Signal* pSignal = connection::signal();
    reflection::AggregationClass* pAggregationClass = as<reflection::AggregationClass*>(pSignal->getOwnerClass());    
    const rtti_data& rd = rttiDataOf(pAggregation, pAggregationClass);
    auto owner = rd.root()->data();
    string aggregationExpression = rd.referenceExpressionString(this);
    o_assert(aggregationExpression.size());
    string indexString = formatIndexExpression(a_uiIndex);
    string insert_remove_expression = formatIndexedExpression(aggregationExpression, a_uiIndex, "()");
    string set_get_expression = formatIndexedExpression(aggregationExpression, a_uiIndex, "[]");

    // Replace data references
    uint oldAggregateGuid = getGuid(a_pOldAggregate);
    uint newAggregateGuid = getGuid(a_pNewAggregate);
    string oldValueExpression;
    string newValueExpression;
    if(oldAggregateGuid != o_invalid_guid)
    {
        removeDataReferenceExpression(oldAggregateGuid, insert_remove_expression);
        oldValueExpression = set_get_expression+"=&(@("+lexical_cast<string>(oldAggregateGuid)+"))";
    }
    else 
    {
        oldValueExpression = set_get_expression+"=static_cast<"+(pAggregationClass->getAggregateClass()->getQualifiedDecoratedName())+"*>(0x"+lexical_cast<string>(a_pOldAggregate)+")";
    }
    if(newAggregateGuid != o_invalid_guid)
    {
        newValueExpression = set_get_expression+"=&(@("+lexical_cast<string>(newAggregateGuid)+"))";
        addDataReferenceExpression(newAggregateGuid, insert_remove_expression);
    }
    else 
    {
        newValueExpression = set_get_expression+"=static_cast<"+(pAggregationClass->getAggregateClass()->getQualifiedDecoratedName())+"*>(0x"+lexical_cast<string>(a_pNewAggregate)+")";
    }

    if(m_pCurrentRecord)
    {
        m_pCurrentRecord->dataAggregationChanged(owner, oldValueExpression, newValueExpression);
    }
    o_emit dataAggregationChanged(owner, oldValueExpression, newValueExpression);
}

void DataBase::aggregateMoved( size_t a_uiOldIndex, size_t a_uiNewIndex, void* a_pAggregate )
{
    void* pAggregation = connection::sender();
    reflection::Signal* pSignal = connection::signal();
    reflection::AggregationClass* pAggregationClass = as<reflection::AggregationClass*>(pSignal->getOwnerClass());
    const rtti_data& rd = rttiDataOf(pAggregation, pAggregationClass);
    auto owner = rd.root()->data();
    string aggregationExpression = rd.referenceExpressionString(this);
    o_assert(aggregationExpression.size());
    string oldIndexString = formatIndexExpression(a_uiOldIndex);
    string newIndexString = formatIndexExpression(a_uiNewIndex);
    string oldValueExpression = aggregationExpression+".move("+newIndexString+", "+oldIndexString+")";
    string newValueExpression = aggregationExpression+".move("+oldIndexString+", "+newIndexString+")";

    string old_insert_remove_expression = formatIndexedExpression(aggregationExpression, a_uiOldIndex, "()");
    string new_insert_remove_expression = formatIndexedExpression(aggregationExpression, a_uiNewIndex, "()");

    // Update data references
    uint aggregateGuid = getGuid(a_pAggregate);
    if(aggregateGuid != o_invalid_guid)
    {
        removeDataReferenceExpression(aggregateGuid, old_insert_remove_expression);
        addDataReferenceExpression(aggregateGuid, new_insert_remove_expression);
    }

    if(m_pCurrentRecord)
    {
        m_pCurrentRecord->dataAggregationChanged(owner, oldValueExpression, newValueExpression);
    }
    o_emit dataAggregationChanged(owner, oldValueExpression, newValueExpression);
}

void DataBase::aggregateSwapped( size_t a_uiOldIndex, size_t a_uiNewIndex, void* a_pOldAggregate, void* a_pNewAggregate )
{
    void* pAggregation = connection::sender();
    reflection::Signal* pSignal = connection::signal();
    reflection::AggregationClass* pAggregationClass = as<reflection::AggregationClass*>(pSignal->getOwnerClass());
    const rtti_data& rd = rttiDataOf(pAggregation, pAggregationClass);
    auto owner = rd.root()->data();
    string aggregationExpression = rd.referenceExpressionString(this);
    o_assert(aggregationExpression.size());
    string oldIndexString = formatIndexExpression(a_uiOldIndex);
    string newIndexString = formatIndexExpression(a_uiNewIndex);
    string old_insert_remove_expression = formatIndexedExpression(aggregationExpression, a_uiOldIndex, "()");
    string new_insert_remove_expression = formatIndexedExpression(aggregationExpression, a_uiNewIndex, "()");
    string oldValueExpression = aggregationExpression+".swap("+newIndexString+", "+oldIndexString+")";
    string newValueExpression = aggregationExpression+".swap("+oldIndexString+", "+newIndexString+")";

    // Swap data references
    uint oldAggregateGuid = getGuid(a_pOldAggregate);
    uint newAggregateGuid = getGuid(a_pNewAggregate);
    if(oldAggregateGuid != o_invalid_guid)
    {
        removeDataReferenceExpression(oldAggregateGuid, old_insert_remove_expression);
        addDataReferenceExpression(oldAggregateGuid, new_insert_remove_expression);
    }
    if(newAggregateGuid != o_invalid_guid)
    {
        removeDataReferenceExpression(newAggregateGuid, new_insert_remove_expression);
        addDataReferenceExpression(newAggregateGuid, old_insert_remove_expression);
    }

    if(m_pCurrentRecord)
    {
        m_pCurrentRecord->dataAggregationChanged(owner, oldValueExpression, newValueExpression);
    }
    o_emit dataAggregationChanged(owner, oldValueExpression, newValueExpression);
}

const phantom::data& DataBase::getComponentDataOwner( const phantom::data& a_Data ) const
{
    return getData(getComponentDataOwnerGuid(getGuid(a_Data)));
}

uint DataBase::getComponentDataOwnerGuid( uint a_ComponentGuid ) const
{
    component_data_owner_map::const_iterator found = m_ComponentDataOwnerMap.find(a_ComponentGuid);
    return found == m_ComponentDataOwnerMap.end() ? o_invalid_guid : found->second;
}

const string& DataBase::getComponentDataReferenceExpression( const phantom::data& a_Data ) const
{
    static string null_string;
    component_data_reference_expression_map::const_iterator found = m_ComponentReferenceExpressionMap.find(getGuid(a_Data));
    return found == m_ComponentReferenceExpressionMap.end() ? null_string : found->second;
}

void DataBase::setComponentDataReferenceExpression( const phantom::data& a_Data, const string& a_Expression )
{
    component_data_reference_expression_map::iterator found = m_ComponentReferenceExpressionMap.find(getGuid(a_Data));
    string oldExp = found->second;
    found->second = a_Expression;
    if(m_pCurrentRecord)
    {
        m_pCurrentRecord->componentReferenceExpressionChanged(a_Data, oldExp, a_Expression);
    }
    else if(m_pUndoRecord)
    {
        m_pUndoRecord->componentReferenceExpressionChanged(a_Data, oldExp, a_Expression);
    }
    else if(m_pRedoRecord)
    {
        m_pRedoRecord->componentReferenceExpressionChanged(a_Data, oldExp, a_Expression);
    }
    o_emit componentReferenceExpressionChanged(a_Data, oldExp, a_Expression);
}

bool DataBase::ComponentExpressionFilter( reflection::Type* a_pType )
{
    a_pType = a_pType->removeReference()->removeConst();
    return a_pType->asDataPointerType() 
        OR as<reflection::CompositionClass*>(a_pType) 
        OR as<reflection::AggregationClass*>(a_pType);
}

void DataBase::setDataPropertyValue( const phantom::data& a_Data, reflection::Property* a_pProperty, const variant& a_Value )
{
    setDataPropertyValue(getGuid(a_Data), a_pProperty, a_Value);
}

void DataBase::setDataPropertyValue( uint a_uiGuid, reflection::Property* a_pProperty, const variant& a_Value )
{
    m_PropertyValues[a_uiGuid][a_pProperty] = a_Value;
}

const variant& DataBase::getDataPropertyValue( const phantom::data& a_Data, reflection::Property* a_pProperty ) const
{
    return getDataPropertyValue(getGuid(a_Data), a_pProperty);
}

const variant& DataBase::getDataPropertyValue( uint a_uiGuid, reflection::Property* a_pProperty ) const
{
    static variant null_variant;
    auto found = m_PropertyValues.find(a_uiGuid);
    if(found != m_PropertyValues.end())
    {
        auto it = found->second.find(a_pProperty);
        if(it != found->second.end())
        {
            return it->second;
        }
    }
    return null_variant;
}

void DataBase::slotNodeLoaded()
{
    Node* pNode = (Node*)connection::sender();
    if(m_pCurrentRecord)
    {
        m_pCurrentRecord->nodeLoaded(pNode);
    }
    o_emit nodeLoaded(pNode);
}

void DataBase::slotNodeAboutToBeUnloaded()
{
    Node* pNode = (Node*)connection::sender();
    if(m_pCurrentRecord)
    {
        m_pCurrentRecord->nodeAboutToBeUnloaded(pNode);
    }
    o_emit nodeAboutToBeUnloaded(pNode);
}

void DataBase::addData( const phantom::data& a_Data, Node* a_pNode, modifiers_t a_Modifiers /*= 0*/ )
{
    uint guid = o_invalid_guid;
    if(m_pUndoRecord)
    {
        guid = m_pUndoRecord->restoreRemovedDataGuid(a_Data.type());
        o_assert(guid != o_invalid_guid);
        restoreDataEntryBackup(m_pUndoRecord->m_uiBackupId, a_Data, guid, a_pNode);
    }
    else if(m_pRedoRecord)
    {
        guid = m_pRedoRecord->restoreAddedDataGuid(a_Data.type());
        o_assert(guid != o_invalid_guid);
        createDataEntry(a_Data, guid, a_pNode);
    }
    else 
    {
        guid = generateGuid();
        o_assert(guid != o_invalid_guid);
        createDataEntry(a_Data, guid, a_pNode);
    }
    registerData(a_Data, guid, a_pNode, a_Modifiers);
    if(m_pUndoRecord)
    {
        m_pUndoRecord->restoreRemovedData(a_Data, guid, a_pNode);
    }
    else 
    {
        if(m_pCurrentRecord)
        {
            m_pCurrentRecord->dataAdded(a_Data, a_pNode);
        }
        o_emit dataAdded(a_Data, a_pNode);
        connectData(a_Data);
    }
    a_pNode->saveData(a_Data);
    a_pNode->saveIndex();
}

void DataBase::addComponentData( const data& a_Data, const data& a_Owner, const string& a_ReferenceExpression, modifiers_t a_Modifiers /*= 0*/ )
{
    Node* pNode = getNode(a_Owner);
    o_assert(pNode);
    uint guid = o_invalid_guid;
    bool bInconsistentUndoRecord = false;
    bool bInconsistentRedoRecord = false;
    if(m_pUndoRecord)
    {
        guid = m_pUndoRecord->restoreRemovedComponentGuid(a_ReferenceExpression);
        if(guid == o_invalid_guid)
        {
            bInconsistentUndoRecord = true;
            guid = generateGuid();
            createDataEntry(a_Data, guid, pNode);
        }
        else 
        {
            restoreDataEntryBackup(m_pUndoRecord->m_uiBackupId, a_Data, guid, pNode);
        }
    }
    else if(m_pRedoRecord)
    {
        guid = m_pRedoRecord->restoreAddedComponentGuid(a_ReferenceExpression);
        if(guid == o_invalid_guid)
        {
            guid = generateGuid();
            createDataEntry(a_Data, guid, pNode);
            bInconsistentRedoRecord = true;
        }
        else 
        {
            createDataEntry(a_Data, guid, pNode);
        }
    }
    else 
    {
        guid = generateGuid();
        createDataEntry(a_Data, guid, pNode);
    }
    o_assert(guid != o_invalid_guid);
    registerData(a_Data, guid, pNode, a_Modifiers);
    registerComponentData(a_Data, a_Owner, a_ReferenceExpression);
    if(m_pUndoRecord)
    {
        if(NOT(bInconsistentUndoRecord))
        {
            m_pUndoRecord->restoreRemovedComponent(a_Data, guid, pNode);
            return;
        }
        m_pUndoRecord->dataAboutToBeRemoved(a_Data, pNode); // simulate the data was removed to store its info in the record
    }
    else if(m_pRedoRecord)
    {
        if(bInconsistentRedoRecord)
        {
            m_pRedoRecord->dataAdded(a_Data, pNode); // simulate the data was removed to store its info in the record
        }
    }
    if(m_pCurrentRecord)
    {
        m_pCurrentRecord->dataAdded(a_Data, pNode);
    }
    o_emit dataAdded(a_Data, pNode);
    connectData(a_Data);
    pNode->saveData(a_Data);
    pNode->saveIndex();
}

void DataBase::removeComponentData( const phantom::data& a_Data )
{
    o_assert(NOT(getComponentDataOwner(a_Data).isNull()), "Data is not a component");
    Node* pNode = getNode(a_Data);
    uint guid = getGuid(a_Data);
    preRemoveData(a_Data);
    disconnectData(a_Data);
    if(m_pUndoRecord)
    {
        if(!m_pUndoRecord->removeAddedGuid(guid))
        {
            m_pUndoRecord->dataAdded(a_Data, pNode); // simulate the data was added to store its info in the record
        }
    }
    else if(m_pRedoRecord)
    {
        if(!m_pRedoRecord->removeRemovedGuid(guid))
        {
            m_pRedoRecord->dataAboutToBeRemoved(a_Data, pNode); // simulate the data was removed to store its info in the record
        }
    }
    else if(m_pCurrentRecord)
    {
        m_pCurrentRecord->dataAboutToBeRemoved(a_Data, pNode);
    }
    o_emit dataAboutToBeRemoved(a_Data, pNode);
    unregisterComponentData(a_Data);
    unregisterData(a_Data);
    destroyDataEntry(a_Data, guid, pNode);
    releaseGuid(guid);
    pNode->saveIndex();
}

void DataBase::removeData( const phantom::data& a_Data )
{
    if(NOT(getComponentDataOwner(a_Data).isNull())) // has owner, use removeComponentData instead
    {
        removeComponentData(a_Data);
        return;
    }
    Node* pNode = getNode(a_Data);
    uint guid = getGuid(a_Data);
    preRemoveData(a_Data);
    disconnectData(a_Data);
    bool bInconsistenUndoRecord = false;
    bool bInconsistenRedoRecord = false;
    if(m_pUndoRecord)
    {
        if(!m_pUndoRecord->removeAddedGuid(guid))
        {
            m_pUndoRecord->dataAdded(a_Data, pNode); // simulate the data was added to store its info in the record
        }
    }
    else if(m_pRedoRecord)
    {
        if(!m_pRedoRecord->removeRemovedGuid(guid))
        {
            m_pUndoRecord->dataAboutToBeRemoved(a_Data, pNode); // simulate the data was removed to store its info in the record
        }
    }
    else if(m_pCurrentRecord)
    {
        m_pCurrentRecord->dataAboutToBeRemoved(a_Data, pNode);
    }
    o_emit dataAboutToBeRemoved(a_Data, pNode);
    unregisterData(a_Data);
    destroyDataEntry(a_Data, guid, pNode);
    releaseGuid(guid);
    pNode->saveIndex();
}

bool DataBase::node_pred::operator()( const Node* n0, const Node* n1 ) const
{
    return n0->getLevel() < n1->getLevel();
}

void DataBase::unloadData( const phantom::data& a_Data )
{    
    saveData(a_Data);
    uint guid = getGuid(a_Data);
    Node* pNode = getNode(a_Data);
    o_assert(std::find(m_UnloadedGuids[pNode].begin(), m_UnloadedGuids[pNode].end(), guid) == m_UnloadedGuids[pNode].end());
    m_UnloadedGuids[pNode].push_back(guid);

    auto found = m_DataReferenceExpressions.find(guid);
    if(found != m_DataReferenceExpressions.end())
    {
        auto& expressions = found->second;
        for(auto it = expressions.begin(); it != expressions.end(); ++it)
        {
            o_assert(it->size());
            reflection::Expression* pExpression = expressionByName((*it)+"=nullptr");
            o_assert(pExpression);
            pExpression->eval();
            o_dynamic_delete (pExpression);
        }
        m_DataReferenceExpressionsUnloadedToRestore[guid] = expressions;
    }

    bool componentRemoved = true;
    while(componentRemoved)
    {
        componentRemoved = false;
        for(auto it = pNode->beginData(); it != pNode->endData(); ++it)
        {
            if( getComponentDataOwner(*it) == a_Data )
            {
                pNode->removeComponentData(*it);
                componentRemoved = true;
                break;
            }
        }
    }

    if(!getComponentDataOwner(a_Data).isNull())
    {
        reflection::Expression* pExpression = expressionByName(m_ComponentReferenceExpressionMap[guid]+"=nullptr");
        o_assert(pExpression);
        pExpression->eval();
        o_dynamic_delete (pExpression);
    }

    disconnectData(a_Data);

    if(m_pCurrentRecord)
    {
        m_pCurrentRecord->dataAboutToBeUnloaded(a_Data, pNode);
    }
    o_emit dataAboutToBeUnloaded(a_Data, pNode);

    unregisterData(a_Data);
}

void DataBase::reloadData()
{
    for(auto it = m_UnloadedGuids.begin(); it != m_UnloadedGuids.end(); ++it)
    {
        Node* pNode = it->first;
        pNode->reload(it->second);
        auto& guidList = it->second;
        for(auto it = guidList.begin(); it != guidList.end(); ++it)
        {
            auto d = getData(*it);
            if(m_pCurrentRecord)
            {
                m_pCurrentRecord->dataReloaded(d, pNode);
            }
            o_emit dataReloaded(d, pNode);
            connectData(d);
        }
        // Restore components only if their parents are not among the unloaded guids
        for(auto it = guidList.begin(); it != guidList.end(); ++it)
        {
            uint guid = *it;
            auto foundParent = m_ComponentDataOwnerMap.find(guid);
            if(foundParent != m_ComponentDataOwnerMap.end()) // data is a component
            {
                uint ownerGuid = foundParent->second;
                auto foundParentUnloaded = std::find(guidList.begin(), guidList.end(), ownerGuid);
                if(foundParentUnloaded == guidList.end()) // component owner is not unloaded, we need to restore the component on it
                {
                    auto found = m_ComponentReferenceExpressionMap.find(guid);
                    o_assert(found != m_ComponentReferenceExpressionMap.end());
                    o_assert(found->second.size());
                    reflection::Expression* pExpression = expressionByName(found->second+"=(&@"+lexical_cast<string>(*it)+")");
                    if(pExpression)
                    {
                        pExpression->eval();
                    }
                    else 
                    {
                        // Expression not valid, component cannot be restored, we remove it
                        removeComponentData(getData(guid));
                    }
                    o_dynamic_delete (pExpression);
                }
            }
        }
        // Restore data references
        for(auto it = guidList.begin(); it != guidList.end(); ++it)
        {
            uint guid = *it;
            auto& expressions = m_DataReferenceExpressionsUnloadedToRestore[guid];
            while(expressions.size())
            {
                reflection::Expression* pExpression = expressionByName(expressions.back()+"=(&@"+lexical_cast<string>(guid)+")");
                if(pExpression)
                {
                    pExpression->eval();
                }
                o_dynamic_delete (pExpression);
            }
        }
    }
    
    m_DataReferenceExpressionsUnloadedToRestore.clear();
    m_UnloadedGuids.clear();
}

bool DataBase::isDataUnloaded( uint guid )
{
    for(auto it = m_UnloadedGuids.begin(); it != m_UnloadedGuids.end(); ++it)
    {
        if(std::find(it->second.begin(), it->second.end(), guid) != it->second.end()) return true;
    }
    return false;
}

void DataBase::blockModuleSlots()
{
    m_bModuleSlotsBlocked = true;
}

void DataBase::unblockModuleSlots()
{
    m_bModuleSlotsBlocked = false;
}

void DataBase::preRemoveData( const phantom::data& a_Data )
{
    uint guid = getGuid(a_Data);
    Node* pNode = getNode(a_Data);
    auto found = m_DataReferenceExpressions.find(guid);
    if(found != m_DataReferenceExpressions.end())
    {
        auto& expressions = found->second;
        while(expressions.size())
        {
            o_assert(expressions.back().size());
            reflection::Expression* pExpression = expressionByName(expressions.back()+"=(0)");
            o_assert(pExpression);
            pExpression->eval();
            o_dynamic_delete (pExpression);
        }
    }

    bool componentRemoved = true;
    while(componentRemoved)
    {
        componentRemoved = false;
        for(auto it = pNode->beginData(); it != pNode->endData(); ++it)
        {
            if( getComponentDataOwner(*it) == a_Data )
            {
                pNode->removeComponentData(*it);
                componentRemoved = true;
                break;
            }
        }
    }
}

void DataBase::addDataReferenceExpression( uint guid, const string& propertyAccessExpression )
{
    m_DataReferenceExpressions[guid].push_back(propertyAccessExpression);
    if(isDataUnloaded(guid))
    {
        auto& expressions = m_DataReferenceExpressionsUnloadedToRestore[guid];
        auto found = std::find(expressions.begin(), expressions.end(), propertyAccessExpression);
        o_assert(found != expressions.end());
        expressions.erase(found);
    }
    else if(m_pCurrentRecord)
    {
        m_pCurrentRecord->dataReferenceExpressionAdded(guid, propertyAccessExpression);
    }
    else if(m_pUndoRecord)
    {
        m_pUndoRecord->dataReferenceExpressionAdded(guid, propertyAccessExpression);
    }
    else if(m_pRedoRecord)
    {
        m_pRedoRecord->dataReferenceExpressionAdded(guid, propertyAccessExpression);
    }
}

void DataBase::removeDataReferenceExpression( uint guid, const string& propertyAccessExpression )
{
    if(isDataUnloaded(guid))
    {
        m_DataReferenceExpressionsUnloadedToRestore[guid].push_back(propertyAccessExpression);
    }
    else if(m_pCurrentRecord)
    {
        m_pCurrentRecord->dataReferenceExpressionAboutToBeRemoved(guid, propertyAccessExpression);
    }
    else if(m_pUndoRecord)
    {
        m_pUndoRecord->dataReferenceExpressionAboutToBeRemoved(guid, propertyAccessExpression);
    }
    else if(m_pRedoRecord)
    {
        m_pRedoRecord->dataReferenceExpressionAboutToBeRemoved(guid, propertyAccessExpression);
    }
    auto& ref = m_DataReferenceExpressions[guid];
    ref.erase(std::find(ref.begin(), ref.end(), propertyAccessExpression));
}

o_namespace_end(phantom, serialization)
