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
#include <phantom/serialization/Node.h>
#include <phantom/serialization/Node.hxx>
#include <phantom/serialization/DataStateBase.h>
#include <phantom/reflection/DataExpression.h>
#include <phantom/reflection/ConstantExpression.h>
/* *********************************************** */
o_registerN((phantom, serialization), Node);

o_namespace_begin(phantom, serialization)

Node::Node( DataBase* a_pOwnerDataBase, uint a_Guid, Node* a_pParentNode ) : m_data_filter_delegate(&Node::defaultDataFilter)
, m_Guid(a_Guid)
, m_pOwnerDataBase(a_pOwnerDataBase)
, m_eState(e_Unloaded)
{
    o_assert(a_pParentNode != NULL  // must have a parent node
        OR a_Guid == 0);            // except the root node
    m_pParentNode = a_pParentNode;
    if(m_pParentNode)
    {
        m_pParentNode->storeNode(this);
    }
}

o_terminate_cpp(Node)
{
    for(auto it = m_ChildNodes.begin(); it != m_ChildNodes.end(); ++it)
    {
        o_dynamic_delete *it;
    }
    m_ChildNodes.clear();
    if(isLoaded())
    {
        unload();
    }
}

const data& Node::findData( void* a_pAddress ) const
{
    static data s_null;
    a_pAddress = phantom::baseOf(a_pAddress);
    data_vector::const_iterator it = m_Data.begin();
    data_vector::const_iterator end = m_Data.end();
    for(;it != end; ++it)
    {
        if(it->address() == a_pAddress) return *it;
    }
    return s_null;
}

void Node::applyNodeVisitor( TVisitor<Node>* visitor )
{
    visitor->apply(this);
    node_vector::const_iterator it = m_ChildNodes.begin();
    node_vector::const_iterator end = m_ChildNodes.end();
    for(;it!=end;++it)
    {
        (*it)->applyNodeVisitor(visitor);
    }
}

void Node::fetchDataWhichDependsOnDataCascade( const phantom::data& a_Data, vector<data>& a_DataVector ) const
{
    fetchDataWhichDependsOnData(a_Data, a_DataVector);
    node_vector::const_iterator it = m_ChildNodes.begin();
    node_vector::const_iterator end = m_ChildNodes.end();
    for(;it!=end;++it)
    {
        (*it)->fetchDataWhichDependsOnDataCascade(a_Data, a_DataVector);
    }
}

void Node::storeData( const phantom::data& a_Data )
{
    o_assert(std::find(
        m_Data.begin()
        , m_Data.end()
        , a_Data
        ) == m_Data.end());
    m_Data.push_back(a_Data);
}

void Node::storeData( const phantom::data& a_Data, size_t a_uiCount, size_t a_uiChunkSectionSize )
{
    byte* pChunk = reinterpret_cast<byte*>(a_Data.address());
    reflection::Type* pType = a_Data.type();
    while(a_uiCount--)
    {
        storeData(data(pChunk, pType));
        pChunk += a_uiChunkSectionSize;
    }
}

void Node::eraseData( const phantom::data& a_Data )
{
    data_vector::iterator it = m_Data.begin();
    data_vector::iterator end = m_Data.end();
    for(;it != end; ++it)
    {
        if(it->address() == a_Data.address())
        {
            o_assert(it->type() == a_Data.type(), "the data type registered for the given address doesn't match the given data type");
            break;
        }
    }
    o_assert(it != end, "data does not exist");
    m_Data.erase(it);
}

void Node::eraseData( const phantom::data& a_Data, size_t a_uiCount, size_t a_uiChunkSectionSize )
{
    byte* pChunk = reinterpret_cast<byte*>(a_Data.address());
    reflection::Type* pType = a_Data.type();
    while(a_uiCount--)
    {
        eraseData(data(pChunk, pType));
        pChunk += a_uiChunkSectionSize;
    }
}

void Node::storeNode( Node* a_pNode )
{
    o_assert(NOT(containsNode(a_pNode)));
    o_assert(a_pNode->m_pOwnerDataBase == m_pOwnerDataBase);
    m_ChildNodes.push_back(a_pNode);
    a_pNode->m_pParentNode = this;
}

void Node::eraseNode( Node* a_pNode )
{
    node_vector::iterator it = m_ChildNodes.begin();
    node_vector::iterator end = m_ChildNodes.end();
    for(;it!=end;++it)
    {
        if(*it == a_pNode)
            break;
    }
    o_assert(it != end);
    m_ChildNodes.erase(it);
    a_pNode->m_pParentNode = NULL;
}

boolean Node::containsData( const data& a_Data ) const
{
    data_vector::const_iterator it = m_Data.begin();
    data_vector::const_iterator end = m_Data.end();
    for(;it != end; ++it)
    {
        if((*it) == a_Data) return true;
    }
    return false;
}

void Node::registerData( const phantom::data& a_Data, uint guid )
{
    storeData(a_Data);
    m_pOwnerDataBase->registerData(a_Data, guid, this, 0);
}

void Node::unregisterData( const phantom::data& a_Data )
{
    m_pOwnerDataBase->unregisterData(a_Data);
    eraseData(a_Data);
}

void Node::setState(EState a_eState)
{
	if (m_eState != a_eState)
	{
		m_eState = a_eState;
		switch(m_eState)
		{
		case e_Loaded:
			{
				o_emit loaded();
			}
			break;
		case e_Unbuilt:
			{
				o_emit aboutToBeUnloaded();
			}
			break;
		}
	}
}

boolean Node::stepByStep()
{
    switch(m_eState)
    {
    case e_Unloaded:
        {
            o_assert(m_pParentNode->isLoaded());
            cache();
            m_eState = e_Cached;
        }
        break;
    case e_Cached:
        {
            build(m_Data);
            m_eState = e_Built;
        }
        break;
    case e_Built:
        {
            deserialize(m_pOwnerDataBase->m_uiSerializationFlag, m_Data);
            m_eState = e_Deserialized;
        }
        break;
    case e_Deserialized:
        {
            restore(m_pOwnerDataBase->m_uiSerializationFlag, m_Data);
            m_eState = e_Loaded;
			o_emit loaded();
            return true;
        }
        break;
    case e_Loaded:
        {
#ifdef _DEBUG
            node_vector::iterator it = m_ChildNodes.begin();
            node_vector::iterator end = m_ChildNodes.end();
            for(;it!=end;++it)
            {
                o_assert_not((*it)->isLoaded());
            }
#endif
			o_emit aboutToBeUnloaded();
            unbuild();
            m_eState = e_Unbuilt;
        }
        break;
    case e_Unbuilt:
        {
            uncache();
            m_eState = e_Unloaded;
            return true;
        }
        break;
    }
    return false;
}

void Node:: destroyAllDataCascade()
{
    node_vector::iterator it = m_ChildNodes.begin();
    node_vector::iterator end = m_ChildNodes.end();
    for(;it!=end;++it)
    {
        (*it)->destroyAllDataCascade();
    }
    destroyAllData();
}

void Node::destroyAllChildNode()
{
    node_vector::iterator it = m_ChildNodes.begin();
    node_vector::iterator end = m_ChildNodes.end();
    for(;it!=end;++it)
    {
        m_pOwnerDataBase->destroyNode(*it);
    }
}

void Node::addData( const data& a_Data )
{
    addData(a_Data, m_pOwnerDataBase->generateGuid());
}

data Node::newComponentData( reflection::Type* a_pType, const data& a_OwnerData, const string& a_ReferenceExpression, bitfield a_ReferenceModifiers )
{
    phantom::data d(a_pType->newInstance(), a_pType);
    addComponentData(d, a_OwnerData, a_ReferenceExpression, a_ReferenceModifiers);
    return d;
}

void Node::addComponentData( const data& a_Data, const data& a_OwnerData, const string& a_ReferenceExpression, bitfield a_ReferenceModifiers )
{
    o_assert(containsData(a_OwnerData));
    o_assert(!containsData(a_Data));
    m_pOwnerDataBase->registerComponentData(a_Data, a_OwnerData, a_ReferenceExpression, a_ReferenceModifiers);
    addData(a_Data);
}

void Node::addComponentData( const data& a_Data, uint a_uiGuid, const data& a_OwnerData, const string& a_ReferenceExpression, bitfield a_ReferenceModifiers )
{
    o_assert(containsData(a_OwnerData));
    o_assert(!containsData(a_Data));
    m_pOwnerDataBase->registerComponentData(a_Data, a_OwnerData, a_ReferenceExpression, a_ReferenceModifiers);
    addData(a_Data, a_uiGuid);
}

void Node::removeComponentData( const data& a_Data, const data& a_OwnerData )
{
    o_assert(containsData(a_OwnerData));
    o_assert(containsData(a_Data));
    //m_pOwnerDataBase->unregisterComponentData(a_Data);
    removeData(a_Data);
}

void Node::addData( const data& a_Data, uint a_uiGuid )
{
    internalAddData(a_Data, a_uiGuid);
	saveIndex();
}

void Node::addData( const data& a_Data, size_t a_uiCount, size_t a_uiChunkSectionSize )
{
    o_assert(m_eState == e_Loaded);
    o_assert(NOT(m_pOwnerDataBase->containsData(a_Data)), "The specified owner Node doesn't belong to this DataBase");
    o_assert(a_Data.type()->isSerializable());
    storeData(a_Data, a_uiCount, a_uiChunkSectionSize);
    byte* pChunk = (byte*)a_Data.address();
    reflection::Type* pType = a_Data.type();
    while(a_uiCount--)
    {
        uint guid = m_pOwnerDataBase->generateGuid();
        o_assert(guid != 0, "0 is reserved to the root node, fix your generateGuid() overloaded member_function so that is returns a guid > 0");
        data d(pChunk, pType);
        m_pOwnerDataBase->createDataEntry(d, guid, this);
        m_pOwnerDataBase->registerData(d, guid, this, 0);
        o_emit m_pOwnerDataBase->dataAdded(d, this);
        pChunk += a_uiChunkSectionSize;
    }
    saveIndex();
}

phantom::data Node::newData( reflection::Type* a_pType )
{
    phantom::data d(a_pType->newInstance(), a_pType);
    addData(d);
    return d;
}

phantom::data Node::newData( reflection::Type* a_pType, uint a_uiGuid )
{
    phantom::data d(a_pType->newInstance(), a_pType);
    addData(d, a_uiGuid);
    return d;
}

void Node::removeData( void* a_pData )
{
    const rtti_data& objInfo = phantom::rttiDataOf(a_pData);
    o_assert(NOT(objInfo.isNull()), "Data given to the DataBase is not a phantom registered class instance and no type has been provided");
    
    const phantom::data d(objInfo.base, objInfo.object_class);
    removeData(d);
}

void Node::removeData( const phantom::data& a_Data )
{
    internalRemoveData(a_Data);    
    saveIndex();
}

void Node::abortData( const phantom::data& a_Data )
{
    o_emit m_pOwnerDataBase->dataAboutToBeAborted(a_Data, this);
    uint guid = m_pOwnerDataBase->getGuid(a_Data.address());
    o_assert(guid != 0xFFFFFFFF, "Data not found in DataBase");
    m_pOwnerDataBase->releaseGuid(guid);
    m_pOwnerDataBase->destroyDataEntry(a_Data, guid, this);
    m_pOwnerDataBase->unregisterData(a_Data.address());
    eraseData(a_Data);
    const_cast<phantom::data&>(a_Data).destroy();
}

void Node::removeData( const phantom::data& a_Data, size_t a_uiCount, size_t a_uiChunkSectionSize )
{
    o_assert(containsData(a_Data));
    eraseData(a_Data, a_uiCount, a_uiChunkSectionSize);
    byte* pChunk = (byte*)a_Data.address();
    reflection::Type* pType = a_Data.type();
    while(a_uiCount--)
    {
        uint guid = m_pOwnerDataBase->getGuid(pChunk);
        o_assert(guid != 0xFFFFFFFF, "Data not found in DataBase");
        phantom::data d(pChunk, pType);
        o_emit m_pOwnerDataBase->dataAboutToBeRemoved(d, this);
        m_pOwnerDataBase->releaseGuid(guid);
        m_pOwnerDataBase->destroyDataEntry(d, guid, this);
        m_pOwnerDataBase->unregisterData(pChunk);
    }
    //saveIndex();
}

Node* Node::newChildNode()
{
    return m_pOwnerDataBase->internalAddNewNode(this);
}

Node* Node::newChildNode( uint guid )
{
    return m_pOwnerDataBase->internalAddNewNode(guid, this);
}

void Node::removeChildNode( Node* a_pNode )
{
	o_assert(containsNode(a_pNode));
	m_pOwnerDataBase->internalRemoveNode(a_pNode, a_pNode->getGuid(), a_pNode->getParentNode());
    eraseNode(a_pNode);
    o_dynamic_delete a_pNode;
}

void Node::load()
{
    if(NOT(canLoad()))
    {
        o_exception(std::exception, "Node cannot be loaded");
    }
    o_assert(m_eState == e_Unloaded);
    if(m_pParentNode AND m_pParentNode->getState() == e_Unloaded)
    {
        o_exception(std::exception, "The parent node should be loaded before loading a child node");
    }
    loadTypes();
    cache(); 
    m_eState = e_Cached;
    build(m_Data); 
    m_eState = e_Built;
    deserialize(m_pOwnerDataBase->m_uiSerializationFlag, m_Data); 
    m_eState = e_Deserialized;
    restore(m_pOwnerDataBase->m_uiSerializationFlag, m_Data); 
    m_eState = e_Loaded;
    configure();
    loadDataAttributes();
    o_emit loaded();
	// Component owners are not saved
	// Add new data components
    /*vector<std::pair<phantom::data, phantom::data>> added;
    fetchUpdatedData(&added);

    // If component have been added after loading we save the node index 
    if(NOT(added.empty())) saveIndex();*/
}

void Node::unload()
{
    node_vector::const_iterator it = m_ChildNodes.begin();
    node_vector::const_iterator end = m_ChildNodes.end();
    for(;it!=end;++it)
    {
        if((*it)->getState() != e_Unloaded)
        {
            o_exception(std::exception, "All child node should be unloaded before unloading a parent node");
        }
    }
    o_emit aboutToBeUnloaded();
    unconfigure();
    o_assert(m_eState == e_Loaded);
    unbuild(); 
    m_eState = e_Unbuilt;
    uncache(); 
    m_eState = e_Unloaded;
}

void Node::save()
{
    // Be sure all components are added before saving
    saveTypes();
    saveIndex(); 
    saveData(); 
    saveAttributes();
}

void Node::saveDataAttributes( const phantom::data& a_Data )
{
    saveDataAttributes(a_Data, m_pOwnerDataBase->getGuid(a_Data));
}

void Node::loadDataAttributes( const phantom::data& a_Data )
{
    loadDataAttributes(a_Data, m_pOwnerDataBase->getGuid(a_Data));
}

void Node::saveDataProperties( const phantom::data& a_Data)
{
    saveDataProperties(m_pOwnerDataBase->m_uiSerializationFlag, a_Data, m_pOwnerDataBase->getGuid(a_Data));
}

void Node::loadData( const phantom::data& a_Data )
{
    loadData(m_pOwnerDataBase->m_uiSerializationFlag, a_Data, m_pOwnerDataBase->getGuid(a_Data));
}

void Node::loadData( uint a_uiSerializationFlag, const phantom::data& a_Data, uint a_uiGuid )
{
    loadDataProperties(a_uiSerializationFlag, a_Data, a_uiGuid);
    if(m_pOwnerDataBase->getDataStateBase())
    {
        loadDataState(a_Data, m_pOwnerDataBase->getDataStateBase()->getCurrentStateId());
    }
    loadDataAttributes(a_Data, a_uiGuid);
}

void Node::saveStateCascade( DataStateBase* a_pDataStateBase, uint a_uiStateId )
{
    o_assert(isLoaded());
    a_pDataStateBase->saveState(this, a_uiStateId);
    node_vector::iterator it = m_ChildNodes.begin();
    node_vector::iterator end = m_ChildNodes.end();
    for(;it!=end;++it)
    {
        if((*it)->isLoaded())
            (*it)->saveStateCascade(a_pDataStateBase, a_uiStateId);
    }
}

void Node::saveStateCascade( uint a_uiStateId )
{
    o_assert(m_pOwnerDataBase->getDataStateBase(), "You must associate a DataStateBase with this DataBase to be able to load/save states");
    saveStateCascade(m_pOwnerDataBase->getDataStateBase(), a_uiStateId);
}

void Node::loadStateCascade( DataStateBase* a_pDataStateBase, uint a_uiStateId )
{
    o_assert(isLoaded());
    a_pDataStateBase->loadState(this, a_uiStateId);
    node_vector::iterator it = m_ChildNodes.begin();
    node_vector::iterator end = m_ChildNodes.end();
    for(;it!=end;++it)
    {
        if((*it)->isLoaded())
            (*it)->loadStateCascade(a_pDataStateBase, a_uiStateId);
    }
}

void Node::loadStateCascade( uint a_uiStateId )
{
    o_assert(m_pOwnerDataBase->getDataStateBase(), "You must associate a DataStateBase with this DataBase to be able to load/save states");
    loadStateCascade(m_pOwnerDataBase->getDataStateBase(), a_uiStateId);
}

void Node::saveState( uint a_uiState )
{
    o_assert(m_pOwnerDataBase->getDataStateBase(), "You must associate a DataStateBase with this DataBase to be able to load/save states");
    o_assert(isLoaded());
    m_pOwnerDataBase->getDataStateBase()->saveState(this, a_uiState);
}

void Node::loadState( uint a_uiState )
{
    o_assert(m_pOwnerDataBase->getDataStateBase(), "You must associate a DataStateBase with this DataBase to be able to load/save states");
    o_assert(isLoaded());
    //o_assert(m_pOwnerDataBase->getDataStateBase()->hasStateSaved(this, a_uiState), "No state previously saved for this node");
    if (m_pOwnerDataBase->getDataStateBase()->hasStateSaved(this, a_uiState))
	{
		m_pOwnerDataBase->getDataStateBase()->loadState(this, a_uiState);
	}
}

bool Node::hasStateSaved( uint a_uiState ) const
{
    o_assert(m_pOwnerDataBase->getDataStateBase());
    return m_pOwnerDataBase->getDataStateBase()->hasStateSaved(const_cast<Node*>(this), a_uiState);
}

void Node::rebuildAllDataCascade( reflection::Type* a_pOld, reflection::Type* a_pNew, vector<data>& a_Old, vector<data>& a_New, uint a_uiStateId /*= 0xffffffff*/ )
{
    o_foreach(Node* pChildNode, m_ChildNodes)
    {
        if(pChildNode->isLoaded())
        pChildNode->rebuildAllDataCascade(a_pOld, a_pNew, a_Old, a_New, a_uiStateId);
    }
    rebuildAllData(a_pOld, a_pNew, a_Old, a_New, a_uiStateId);
}

void Node::replaceDataReferenceCascade( const vector<void*>& a_OldLayout, const phantom::data& a_New ) const
{
    o_foreach(Node* pChildNode, m_ChildNodes)
    {
        if(pChildNode->isLoaded())
        {
            pChildNode->replaceDataReferenceCascade(a_OldLayout, a_New);
        }
    }
    bool complete = replaceDataReference(a_OldLayout, a_New, false);
    if(NOT(complete)) // incompatible types found
    {
        // so try to clear "cleanly" (with public propertys or attributes) old reference
        clearDataReference(a_OldLayout);

        // and then make a second replacement pass with forcing incompatible new data to null
        complete = replaceDataReference(a_OldLayout, a_New, true);

        o_assert(complete);
    }
}

void Node::clearDataReferenceCascade( const vector<void*>& a_OldLayout, vector<reflection::Expression*>* a_pRestoreReferenceExpressions ) const
{
    o_foreach(Node* pChildNode, m_ChildNodes)
    {
        if(pChildNode->isLoaded())
        {
            pChildNode->clearDataReferenceCascade(a_OldLayout, a_pRestoreReferenceExpressions);
        }
    }
    clearDataReference(a_OldLayout, a_pRestoreReferenceExpressions);
}

void Node::loadDataState( const phantom::data& a_Data, uint a_uiStateId )
{
    DataStateBase* pDataStateBase = m_pOwnerDataBase->getDataStateBase();
    if(pDataStateBase == nullptr)
    {
        o_exception(std::exception, "No data state base defined for the current data base");
    }
    pDataStateBase->loadDataState(a_Data, m_pOwnerDataBase->getGuid(a_Data), this, a_uiStateId);
}

void Node::saveDataState( const phantom::data& a_Data, uint a_uiStateId )
{
    DataStateBase* pDataStateBase = m_pOwnerDataBase->getDataStateBase();
    if(pDataStateBase == nullptr)
    {
        o_exception(std::exception, "No data state base defined for the current data base");
    }
    pDataStateBase->saveDataState(a_Data, m_pOwnerDataBase->getGuid(a_Data), this, a_uiStateId);
}

void Node::fetchContainerComponents(reflection::ContainerClass* a_pContainerClass, void* a_pContainer, vector<phantom::data>& out)
{
    reflection::Iterator* pIterator = a_pContainerClass->begin(a_pContainer);
    bool needAnotherPass = false;
    reflection::Type* pType = a_pContainerClass->getValueType();
    if(pType->asDataPointerType())
    {
        void* ptr = nullptr; 
        while(pIterator->hasNext())
        {
            ((reflection::Iterator*)pIterator)->getValue(&ptr);
            phantom::data d(ptr);
            if(NOT(d.isNull()))
            {
                if(m_pOwnerDataBase->containsData(d) AND m_pOwnerDataBase->getComponentDataOwner(d).isNull()) 
                {
                    // component valueMember contains a non-component data => clear it
                    ptr = nullptr;
                    a_pContainerClass->erase(a_pContainer, pIterator);
                    needAnotherPass = true;
                    break;
                }
                else out.push_back(d);
            }
            pIterator->next(&ptr); // it++
        }
    }
    else 
    {
        reflection::ContainerClass* pSubContainerClass = pType->asContainerClass();
        o_assert(pSubContainerClass);
        void* pSubContainer = pSubContainerClass->newInstance();
        while(pIterator->hasNext())
        {
            pIterator->next(pSubContainer);
            fetchContainerComponents(pSubContainerClass, pSubContainer, out);
        }
        pSubContainerClass->deleteInstance(pSubContainer);
    }

    pIterator->deleteNow();

    if(needAnotherPass)
    {

    }
}

void Node::clearDataReference( const vector<void*>& layout, vector<reflection::Expression*>* a_pRestoreReferenceExpressions ) const
{
    o_assert(isLoaded());
    data_vector::const_iterator it = m_Data.begin();
    data_vector::const_iterator end = m_Data.end();
    for(;it != end; ++it)
    {
        const phantom::data& currentData = *it;
        bool currentDataModified = false;

        auto it = layout.begin();
        auto end = layout.end();
        for(;it!=end;++it)
        {
            void* address = *it;
            // A data shouldn't have valueMember pointing on itself, so we skip
            if(currentData.address() == address) 
                continue;

            // A data type can have valueMember only if it's a ClassType (struct/union/class)
            reflection::ClassType* pClassType = currentData.type()->asClassType();
            if(pClassType)
            {
                reflection::Class* pClass = pClassType->asClass();
                vector<reflection::ValueMember*> valueMembers;
                //vector<reflection::Collection*> collections;
                if(pClass)
                {
                    pClass->getValueMembersCascade(valueMembers);
                    //pClass->getCollectionsCascade(collections);
                }
                else
                {
                    valueMembers.insert(valueMembers.end(), pClassType->beginValueMembers(), pClassType->endValueMembers());
                    //collections.insert(collections.end(), pClassType->beginCollections(), pClassType->endCollections());
                }
                struct PropertyThenAttributeSorter
                {
                    bool operator()(const reflection::ValueMember* first, const reflection::ValueMember* second) const 
                    {
                        if((first->asProperty() != nullptr) AND (second->asProperty() == nullptr)) return true;
                        if((second->asProperty() != nullptr) AND (first->asProperty() == nullptr)) return false;
                        return first < second;
                    }
                };
/*

                o_foreach(reflection::Collection* pCollection, collections)
                {
                    reflection::DataPointerType* pCollectionElementType = pCollection->getElementType()->asDataPointerType();
                    if(pCollectionElementType)
                    {
                        void* castedAddress = currentData.cast(pCollection->getOwner()->asClassType()).address();
                        bool needPass = true;
                        while(needPass)
                        {
                            needPass = false;

                            size_t i = 0;
                            size_t count = pCollection->getSize(castedAddress);
                            for(;i<count;++i)
                            {
                                void* component = NULL;
                                pCollection->getElement(castedAddress, i, &component);
                                if(component == address)
                                {
                                    pCollection->removeElement(castedAddress, &component);
                                    needPass = true;
                                    break;
                                }
                            }
                        }
                    }
                }
*/


                std::sort(valueMembers.begin(), valueMembers.end(), PropertyThenAttributeSorter());

                o_foreach(reflection::ValueMember* pValueMember, valueMembers)
                {
                    reflection::DataPointerType* pValueMemberValueType = pValueMember->getValueType()->asDataPointerType();
                    if(pValueMemberValueType)
                    {
                        // Cast the unreferenced data address to the valueMember value type
                        phantom::data castedCurrentData = currentData.cast(pValueMember->getOwnerClassType());

                        // Extract the valueMember value from the current data
                        void* pointerValue = nullptr;
                        pValueMember->getValue(castedCurrentData.address(), &pointerValue);

                        // Test it with the cleared data
                        if(pointerValue == address)
                        {
                            // if pointer are the same, clear the data reference into the current node data
                            if(a_pRestoreReferenceExpressions)
                            {
                                reflection::Expression* pGuidExpression = o_new(reflection::ConstantExpression)(phantom::constant<uint>(m_pOwnerDataBase->getGuid(currentData)), nullptr, true);
                                reflection::Expression* pDataExpression = o_new(reflection::DataExpression)(m_pOwnerDataBase, pGuidExpression);
                                reflection::Expression* pCastExpression = pDataExpression->cast(pValueMember->getOwnerClassType()->referenceType());
                                o_assert(pCastExpression);
                                reflection::Expression* pAccessExpression = pValueMember->createAccessExpression(pCastExpression);
                                pGuidExpression = o_new(reflection::ConstantExpression)(phantom::constant<uint>(m_pOwnerDataBase->getGuid(pointerValue)), nullptr, true);
                                reflection::Expression* pRightDataExpression = o_new(reflection::DataExpression)(m_pOwnerDataBase, pGuidExpression);
                                pRightDataExpression = pRightDataExpression->address();
                                pRightDataExpression = pRightDataExpression->cast(pValueMember->getValueType());
                                reflection::Expression* pAssignExpression = pAccessExpression->solveBinaryOperator("=", pRightDataExpression);
                                a_pRestoreReferenceExpressions->push_back(pAssignExpression);
                            }
                            pointerValue = nullptr;
                            pValueMember->setValue(castedCurrentData.address(), &pointerValue);
                            currentDataModified = true;
                        }
                    }
                }
            }
        }
        if(currentDataModified)
        {
            // Save if modified
            // TODO : clean this dirty hack by using const on saveData
            ((Node*)this)->saveDataProperties(currentData);
        }
    }
}

bool Node::replaceDataReference( const vector<void*>& a_OldLayout, const phantom::data& a_New, bool a_SetIncompatibleToNull ) const
{
    o_assert(isLoaded());
    bool complete = true;
    data_vector::const_iterator it = m_Data.begin();
    data_vector::const_iterator end = m_Data.end();
    for(;it != end; ++it)
    {
        phantom::data currentData = *it;
        bool currentDataModified = false;

        auto it = a_OldLayout.begin();
        auto end = a_OldLayout.end();
        for(;it!=end;++it)
        {
            void* oldAddress = *it;
            // A data shouldn't have valueMember pointing on itself, so we skip
            if(currentData.address() == oldAddress) 
                continue;

            if(currentData == m_pOwnerDataBase->getComponentDataOwner(oldAddress))
            {
                // the current data owns the old data, so we check if it can own the new data
                reflection::Collection* collection = m_pOwnerDataBase->getCollectionContainingComponentData(oldAddress);
                if(NOT(a_New.type()->isKindOf(collection->getElementType())))
                {
                    // If not, we remove the old via the interface
                    void* removed = oldAddress;
                    collection->safeRemoveElement(currentData.address(), &removed);
                    currentDataModified = true;
                }
            }
            else if(oldAddress == m_pOwnerDataBase->getComponentDataOwner(currentData).address())
            {
                // this case must be handled via the setOwner member_functions on the owned object (via propertys)
                //continue;
            }

            // A data type can have valueMember only if it's a ClassType (struct/union/class)
            reflection::ClassType* pClassType = currentData.type()->asClassType();
            if(pClassType)
            {
                reflection::Class* pClass = pClassType->asClass();
                vector<reflection::ValueMember*> valueMembers;
                if(pClass)
                {
                    pClass->getValueMembersCascade(valueMembers);
                }
                else
                {
                    valueMembers.insert(valueMembers.end(), pClassType->beginValueMembers(), pClassType->endValueMembers());
                }
                o_foreach(reflection::ValueMember* pValueMember, valueMembers)
                {
                    reflection::InstanceDataMember* pInstanceDataMember = pValueMember->asInstanceDataMember();

                    // Only treat attributes (no property or other valueMembers) 
                    // because we want real "physical memory" reference replacement
                    if(pInstanceDataMember == nullptr) continue;
                    phantom::data castedCurrentData = currentData.cast(pInstanceDataMember->getOwnerClassType());

                    // Test reference by pointer
                    reflection::DataPointerType* pValueMemberPointerValueType = pInstanceDataMember->getValueType()->asDataPointerType();
                    if(pValueMemberPointerValueType)
                    {

                        // Extract the valueMember value from the current data
                        void* pointerValue = nullptr;
                        pInstanceDataMember->getValue(castedCurrentData.address(), &pointerValue);

                        // Test it with the cleared data
                        if(pointerValue == oldAddress)
                        {
                            // if pointer are the same, replace the data reference into the current node data
                            pointerValue = a_New.cast(pValueMemberPointerValueType->getPointedType()).address();
                            if(pointerValue != nullptr OR a_SetIncompatibleToNull) // This means the type are no more compatible we need to nullify the valueMember in a second pass
                            {
                                pInstanceDataMember->setValue(castedCurrentData.address(), &pointerValue);
                                currentDataModified = true;
                            }
                            else 
                            {
                                complete = false;
                                // if null we'll try then instead of replacing, to clear the data via clearDataReference
                            }
                        }
                    }
                    else
                    {
                        // Test reference in container (still by pointer)
                        reflection::ContainerClass* pContainerClass = pInstanceDataMember->getValueType()->asContainerClass();
                        if(pContainerClass)
                        {
                            reflection::DataPointerType* pDataPointerType = pContainerClass->getValueType()->asDataPointerType();
                            if(pDataPointerType)
                            {
                                // Cast to content type worked, this may be a potential container referencing the current data
                                void* container = pContainerClass->newInstance();
                                // Get the whole container
                                pInstanceDataMember->getValue(castedCurrentData.address(), container);

                                // Iterate through the container to find a potential reference
                                void* the_old = oldAddress;
                                void* the_new = a_New.cast(pDataPointerType->getPointedType()).address();
                                int replacedCount = 0;
                                if(the_new == nullptr)
                                {
                                    // The new data is not compatible anymore with the container content type, we erase the old
                                    replacedCount = pContainerClass->eraseAll(container, &the_old);
                                }
                                else 
                                {
                                    replacedCount = pContainerClass->replaceAll(container, &the_old, &the_new);
                                }
                                if(replacedCount) //  if at least one reference has been replaced/removed,
                                    // we replace the whole collection
                                {
                                    pInstanceDataMember->setValue(castedCurrentData.address(), container);
                                    currentDataModified = true;
                                }
                                pContainerClass->deleteInstance(container);
                            }

                        }
                    }
                }
            }
        }
        if(currentDataModified)
        {
            ((Node*)this)->saveDataProperties(currentData);
        }
    }
    return complete;
}


void Node::fetchUpdatedData( const phantom::data& a_Data
                                , vector<data_pair>& out_components_to_add
                                , vector<data_pair>& out_components_to_remove
                                , vector<string>& out_components_to_add_reference_expressions
                                , vector<bitfield>& out_to_add_modifiers
                                , vector<data>& a_TreatedData )
{
    std::set<phantom::data> alreadyTreated;
    fetchUpdatedData(a_Data, out_components_to_add, out_components_to_remove, out_components_to_add_reference_expressions, out_to_add_modifiers, alreadyTreated);
    for(auto it = alreadyTreated.begin(); it != alreadyTreated.end(); ++it)
    {
        a_TreatedData.push_back(*it);
    }
}

void Node::fetchUpdatedData( const phantom::data& a_Data
                                , vector<data_pair>& out_components_to_add /*= nullptr*/
                                , vector<data_pair>& out_components_to_remove /*= nullptr*/
                                , vector<string>& out_added_pointer_reference_expressions
                                , vector<bitfield>& out_to_add_modifiers
                                , std::set<phantom::data>& treatedData)
{
    treatedData.insert(a_Data);
    bool indexOutdated = false;
    phantom::data d = a_Data;

    vector<phantom::data> new_components;
    vector<reflection::Expression*> pointerReferenceExpressions;
    auto pConstant = phantom::constant<uint>(m_pOwnerDataBase->getGuid(a_Data));
    auto pExpression = o_new(reflection::DataExpression)(m_pOwnerDataBase, o_new(reflection::ConstantExpression)(pConstant, nullptr, false)) ;
    d.type()->fetchPointerReferenceExpressions(pExpression 
                                                , pointerReferenceExpressions
                                                , 0xffffffff);
    // phantom::deleteElement(pConstant);
    phantom::deleteElement(pExpression);
    map<phantom::data, reflection::Expression*> dataReferenceExpressions;

    for(auto it = pointerReferenceExpressions.begin(); it != pointerReferenceExpressions.end(); ++it)
    {
        reflection::Expression* pExpression = *it;
        void* pAddress = nullptr;
        pExpression->load(&pAddress);// Evaluate expression to get pointer reference value
        if(pAddress == nullptr)
            continue;
        phantom::data referencedData(rttiDataOf(pAddress).data());
        if(referencedData.isNull())
            continue;
        if(pExpression->testModifiers(o_component))
        {
            auto found = dataReferenceExpressions.find(d);
            if(found == dataReferenceExpressions.end()) // if multiple references are found inside 
                                                        // a single instance, we keep only the first found which generally matches 
                                                        // a property (most valuable), and if not a data member (less valuable)
            {
                new_components.push_back(referencedData);
                dataReferenceExpressions[referencedData] = pExpression;
            }
        }
        else if(m_pOwnerDataBase->getGuid(referencedData) != 0xffffffff AND treatedData.find(referencedData) == treatedData.end())
        {
            // If data referenced exists in the data base, we treat it
            m_pOwnerDataBase->getNode(referencedData)->fetchUpdatedData(referencedData, out_components_to_add, out_components_to_remove, out_added_pointer_reference_expressions, out_to_add_modifiers, treatedData);
        }
    }

    DataBase* pDataBase = getOwnerDataBase();

    vector<phantom::data> old_components;
    size_t i = 0;
    for(;i<m_Data.size();++i)
    {
        if(pDataBase->getComponentDataOwner(m_Data[i]) == d)
        {
            old_components.push_back(m_Data[i]); 
        }
    }
    vector<phantom::data> in_both(std::min(new_components.size(), old_components.size()));
    std::sort(new_components.begin(), new_components.end());
    size_t beforeUniqueSize = new_components.size();
    auto last = std::unique(new_components.begin(), new_components.end());
    o_assert(new_components.size() == beforeUniqueSize, "Data should be unique");
    // new_components.resize(last - new_components.begin());
    std::sort(old_components.begin(), old_components.end());
    beforeUniqueSize = old_components.size();
    last = std::unique(old_components.begin(), old_components.end());
    o_assert(old_components.size() == beforeUniqueSize, "Data should be unique");
    // old_components.resize(last - old_components.begin());
    last = std::set_intersection(new_components.begin(), new_components.end(), old_components.begin(), old_components.end(), in_both.begin());
    in_both.erase(last, in_both.end());

    for(auto it = in_both.begin(); it != in_both.end(); ++it)
    {
        // Component which are found both in current and old lists are the already existing components which wont be removed, we browse them for new components
        if(treatedData.find(*it) == treatedData.end())
        {
            m_pOwnerDataBase->getNode(*it)->fetchUpdatedData(*it, out_components_to_add, out_components_to_remove, out_added_pointer_reference_expressions, out_to_add_modifiers, treatedData);
        }
    }

    std::sort(in_both.begin(), in_both.end());

    vector<phantom::data> to_remove(std::max(old_components.size(), in_both.size()));
    last = std::set_difference(old_components.begin(), old_components.end(), in_both.begin(), in_both.end(), to_remove.begin());
    to_remove.erase(last, to_remove.end());

    vector<phantom::data> to_add(std::max(new_components.size(), in_both.size()));
    last = std::set_difference(new_components.begin(), new_components.end(), in_both.begin(), in_both.end(), to_add.begin());
    to_add.erase(last, to_add.end());

    {
        auto it = to_remove.begin();
        auto end = to_remove.end();
        for(;it!=end;++it)
        {
            o_assert(m_pOwnerDataBase->containsData(*it))
            {
                out_components_to_remove.push_back(data_pair(*it, d));
                //indexOutdated = true;
                //internalRemoveData(*it);
            }
            //pDataBase->unregisterComponentData(*it);
        }
    }

    {
        auto it = to_add.begin();
        auto end = to_add.end();
        for(;it!=end;++it)
        {
            //pDataBase->registerComponentData(*it, d);
            o_assert(NOT(m_pOwnerDataBase->containsData(*it))) // the data is a shared data
            {
                out_components_to_add.push_back(data_pair(*it, d));
                phantom::reflection::Expression* pExpression = dataReferenceExpressions[*it];
                out_added_pointer_reference_expressions.push_back(pExpression->getName());
                out_to_add_modifiers.push_back(pExpression->getModifiers());
                //indexOutdated = true;
                //internalAddData(*it, m_pOwnerDataBase->generateGuid());
            }
            //saveData(*it);
        }
    }
    for(auto it = dataReferenceExpressions.begin(); it != dataReferenceExpressions.end(); ++it)
    {
        phantom::deleteElement(it->second);
    }
}
/*

void Node::fetchUpdatedData(const phantom::data& a_Data, vector<data_pair>& out_components_to_add / *= nullptr* /, vector<data_pair>& out_components_to_remove / *= nullptr* /)
{
    fetchUpdatedData(a_Data, m_Data.size(), out_components_to_add, out_components_to_remove);
    
    for(;i<m_Data.size();++i)
    {
        fetchUpdatedData(m_Data[i], out_components_to_add, out_components_to_remove);
    }
}*/

void Node::rebuildAllData( reflection::Type* a_pOld, reflection::Type* a_pNew, vector<data>& a_OldData, vector<data>& a_NewData, uint a_uiStateId /*= 0xffffffff*/ )
{
    o_assert(isLoaded());
    data_vector::iterator it = m_Data.begin();
    data_vector::iterator end = m_Data.end();
    for(;it != end; ++it)
    {
        if(it->type() == a_pOld) 
        {
            m_pOwnerDataBase->rebuildData(*it, a_pOld, a_pNew, a_OldData, a_NewData, a_uiStateId);
        }
    }
}

void Node::applyDataVisitor( TVisitor<data>* visitor )
{
    data_vector::iterator it = m_Data.begin();
    data_vector::iterator end = m_Data.end();
    for(;it != end; ++it)
    {
        visitor->apply(&(*it));
    }
    {
        node_vector::iterator it = m_ChildNodes.begin();
        node_vector::iterator end = m_ChildNodes.end();
        for(;it!=end;++it)
        {
            (*it)->applyDataVisitor(visitor);
        }
    }
}

void Node::saveData()
{
    for(auto it = m_Data.begin(); it != m_Data.end(); ++it)
    {
        saveData(*it);
    }
}

void Node::saveData( uint a_uiSerializationFlag, const phantom::data& a_Data, uint a_uiGuid )
{
    saveDataProperties(a_uiSerializationFlag, a_Data, a_uiGuid);
    if(m_pOwnerDataBase->getDataStateBase())
    {
        saveDataState(a_Data, m_pOwnerDataBase->getDataStateBase()->getCurrentStateId());
    }
    saveDataAttributes(a_Data, a_uiGuid);
}

void Node::saveData( uint a_uiSerializationFlag )
{
    data_vector::iterator it = m_Data.begin();
    data_vector::iterator end = m_Data.end();

    for(;it != end; ++it)
    {
        void* pAddress = it->address();
        uint guid = m_pOwnerDataBase->getGuid(pAddress);
        saveData(a_uiSerializationFlag, *it, guid);
    }
}

void Node::destroyAllData()
{
    data_vector::iterator it = m_Data.begin();
    data_vector::iterator end = m_Data.end();
    for(;it!=end;++it)
    {
        phantom::data d = *it;
        m_pOwnerDataBase->unregisterData(d);
        d.destroy();
    }
    m_Data.clear();
}

boolean Node::containsDataWhichDependsOnData( const data& a_Dependency ) const
{
    data_vector::const_iterator it = m_Data.begin();
    data_vector::const_iterator end = m_Data.end();
    for(;it != end; ++it)
    {
        if(m_pOwnerDataBase->dataHasDependency(*it, a_Dependency))
            return true;
    }
    return false;
}

void Node::fetchDataWhichDependsOnData(const phantom::data& a_Data, vector<data>& a_DataVector) const
{
    data_vector::const_iterator it = m_Data.begin();
    data_vector::const_iterator end = m_Data.end();
    for(;it != end; ++it)
    {
        if(m_pOwnerDataBase->dataHasDependency(*it, a_Data))
            a_DataVector.push_back(*it);
    }
}

boolean Node::dependsOn( Node* a_pNode ) const
{
    data_vector::const_iterator it = m_Data.begin();
    data_vector::const_iterator end = m_Data.end();
    for(;it != end; ++it)
    {
        if(containsDataWhichDependsOnData(*it)) 
            return true;
    }
    return false;
}

boolean Node::containsDependencyOf( const data& a_Data ) const
{
    data_vector::const_iterator it = m_Data.begin();
    data_vector::const_iterator end = m_Data.end();
    for(;it != end; ++it)
    {
        if(m_pOwnerDataBase->dataHasDependency(a_Data, *it))
            return true;
    }
    return false;
}

void Node::fetchDataOfTypeCascade( reflection::Type* a_pType, vector<data>& a_DataVector ) const
{
    fetchDataOfType(a_pType, a_DataVector);
    node_vector::const_iterator it = m_ChildNodes.begin();
    node_vector::const_iterator end = m_ChildNodes.end();
    for(;it!=end;++it)
    {
        (*it)->fetchDataOfTypeCascade(a_pType, a_DataVector);
    }
}

void Node::fetchDataCascade( vector<data>& a_DataVector ) const
{
    fetchData(a_DataVector);
    node_vector::const_iterator it = m_ChildNodes.begin();
    node_vector::const_iterator end = m_ChildNodes.end();
    for(;it!=end;++it)
    {
        (*it)->fetchDataCascade(a_DataVector);
    }
}

void Node::getAllDescendantWhichDependsOn( const phantom::data& a_Data, vector<Node*>& a_NodeVector ) const
{
    node_vector::const_iterator it = m_ChildNodes.begin();
    node_vector::const_iterator end = m_ChildNodes.end();
    for(;it!=end;++it)
    {
        if((*it)->containsDataWhichDependsOnData(a_Data))
            a_NodeVector.push_back(*it);
        (*it)->getAllDescendantWhichDependsOn(a_Data, a_NodeVector);
    }
}

void Node::getAllDescendantWhichDependsOn( Node* a_pNode, vector<Node*>& a_NodeVector ) const
{
    node_vector::const_iterator it = m_ChildNodes.begin();
    node_vector::const_iterator end = m_ChildNodes.end();
    for(;it!=end;++it)
    {
        if((*it)->dependsOn(a_pNode))
            a_NodeVector.push_back(*it);
        (*it)->getAllDescendantWhichDependsOn(a_pNode, a_NodeVector);
    }
}

boolean Node::childNodesContainDependencyOfDeep( const data& a_Data ) const
{
    node_vector::const_iterator it = m_ChildNodes.begin();
    node_vector::const_iterator end = m_ChildNodes.end();
    for(;it!=end;++it)
    {
        if((*it)->containsDependencyOfDeep(a_Data))
            return true;
    }
    return false;
}

boolean Node::containsDependencyOfDeep( const data& a_Data ) const
{
    return containsDependencyOf(a_Data)
        OR childNodesContainDependencyOfDeep(a_Data) ;
}

boolean Node::containsDataWhichDependsOnDataCascade( const data& a_Dependency ) const
{
    return containsDataWhichDependsOnData(a_Dependency)
        OR (m_pParentNode ? m_pParentNode->containsDataWhichDependsOnDataCascade(a_Dependency) : false);
}

void Node::saveCascade()
{
    o_assert(isLoaded());
    save();
    auto it = m_ChildNodes.begin();
    auto end = m_ChildNodes.end();
    for(;it!=end;++it)
    {
        if((*it)->isLoaded())
        {
            (*it)->saveCascade();
        }
    }
}

void Node::fetchData( vector<data>& a_DataVector ) const
{
    data_vector::const_iterator it = m_Data.begin();
    data_vector::const_iterator end = m_Data.end();
    for(;it!=end;++it)
    {
        a_DataVector.push_back(*it);
    }
}

void Node::fetchDataOfType( reflection::Type* a_pType, vector<data>& a_DataVector ) const
{
    data_vector::const_iterator it = m_Data.begin();
    data_vector::const_iterator end = m_Data.end();
    for(;it!=end;++it)
    {
        if(it->type() == a_pType)
            a_DataVector.push_back(*it);
    }
}

void Node::internalAddData( const data& a_Data, uint a_uiGuid )
{
    o_assert(m_eState == e_Loaded);
    o_assert(NOT(m_pOwnerDataBase->containsData(a_Data)), "The specified owner Node doesn't belong to this DataBase");
    o_assert(a_Data.type()->isSerializable());
    storeData(a_Data);
    o_assert(a_uiGuid != 0, "0 is reserved to the root node");
    o_assert(a_uiGuid != 0xffffffff, "Invalid guid");
    m_pOwnerDataBase->internalAddNewData(a_Data, a_uiGuid, this);
}

void Node::internalRemoveData( const data& a_Data )
{
    o_assert(containsData(a_Data));

    // TODO : make a virtual "removeAllComponentData(a_Data)" instead of this
    bool subDataRemovalPassNeeded = true;
    while(subDataRemovalPassNeeded)
    {
        subDataRemovalPassNeeded = false;
        vector<data> allData;
        fetchData(allData);
        size_t i = 0;
        for(;i<allData.size();++i)
        {
            if( getOwnerDataBase()->getComponentDataOwner(allData[i]) == a_Data )
            {
                removeData(allData[i]);
                allData[i].destroy();
                subDataRemovalPassNeeded = true;
                break;
            }
        }
    }


    uint guid = getOwnerDataBase()->getGuid(a_Data.address());
    o_assert(guid != 0xffffffff);
    getOwnerDataBase()->internalRemoveData(a_Data, guid, this);
    eraseData(a_Data); 
}

phantom::data Node::getData( void* a_pAddress ) const
{
    phantom::data d(a_pAddress);
    return (std::find(m_Data.begin(), m_Data.end(), d) == m_Data.end()) ? phantom::data() : d;
}

void Node::unloadCascade()
{
    o_assert(isLoaded());
    for(auto it = beginChildNodes(); it != endChildNodes(); ++it)
    {
        if((*it)->isLoaded())
        {
            (*it)->unloadCascade();
        }
    }
    unload();
}

void Node::addType( reflection::Type* a_pType )
{
    o_assert(getType(a_pType->getQualifiedDecoratedName()) == nullptr);
    m_Types[a_pType->getQualifiedDecoratedName()];
    saveTypes();
}

void Node::removeType( reflection::Type* a_pType )
{
    o_assert(getType(a_pType->getQualifiedDecoratedName()) == a_pType);
    o_assert(a_pType->asClass() == nullptr || a_pType->asClass()->getInstanceCount() == 0);
    m_Types.erase(a_pType->getQualifiedDecoratedName());
    saveTypes();
}

reflection::Type* Node::getType( const string& a_strQualifiedDecoratedName ) const
{
    auto found = m_Types.find(a_strQualifiedDecoratedName);
    return found != m_Types.end() ? found->second : nullptr;
}

void Node::replaceTypes( const map<reflection::Type*, reflection::Type*>& replacedTypes )
{
    for(auto it = replacedTypes.begin(); it != replacedTypes.end(); ++it)
    {
        reflection::Type* pOld = it->first;
        reflection::Type* pNew = it->second;

        for(auto it = m_Types.begin(); it != m_Types.end(); ++it)
        {
            if(it->second == pOld)
            {
                it->second = pNew;
                break;
            }
        }
    }
    saveTypes();
}

uint Node::generateGuid() const
{
    return m_pOwnerDataBase->generateGuid();
}

void Node::fetchDataTypes( std::set<reflection::Type*>& a_Types ) const
{
    for(auto it = m_Data.begin(); it != m_Data.end(); ++it)
    {
        a_Types.insert(it->type());
    }
}

void Node::fetchDataTypesCascade( std::set<reflection::Type*>& a_Types ) const
{
    fetchDataTypes(a_Types);
    for(auto it = m_ChildNodes.begin(); it != m_ChildNodes.end(); ++it)
    {
        (*it)->fetchDataTypesCascade(a_Types);
    }
}

o_namespace_end(phantom, serialization)
