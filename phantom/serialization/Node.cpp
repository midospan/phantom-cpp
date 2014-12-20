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
#include <phantom/reflection/InstanceDataMemberExpression.h>
/* *********************************************** */
o_registerN((phantom, serialization), Node);

o_namespace_begin(phantom, serialization)

Node::Node( DataBase* a_pDataBase, uint a_Guid, Node* a_pParentNode ) : m_data_filter_delegate(&Node::defaultDataFilter)
, m_Guid(a_Guid)
, m_pDataBase(a_pDataBase)
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

void Node::storeNode( Node* a_pNode )
{
    o_assert(NOT(containsNode(a_pNode)));
    o_assert(a_pNode->m_pDataBase == m_pDataBase);
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
    m_pDataBase->registerData(a_Data, guid, this, 0);
}

void Node::unregisterData( const phantom::data& a_Data )
{
    m_pDataBase->unregisterData(a_Data);
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
            deserialize(m_pDataBase->m_uiSerializationFlag, m_Data);
            m_eState = e_Deserialized;
        }
        break;
    case e_Deserialized:
        {
            restore(m_pDataBase->m_uiSerializationFlag, m_Data);
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
        m_pDataBase->destroyNode(*it);
    }
}

void Node::addData( const data& a_Data, modifiers_t a_Modifiers )
{
    o_assert(!containsData(a_Data));
    m_pDataBase->addData(a_Data, this, a_Modifiers);
}

data Node::newComponentData( reflection::Type* a_pType, const data& a_OwnerData, const string& a_ReferenceExpression, modifiers_t a_ReferenceModifiers )
{
    phantom::data d(a_pType->newInstance(), a_pType);
    addComponentData(d, a_OwnerData, a_ReferenceExpression, a_ReferenceModifiers);
    return d;
}

void Node::addComponentData( const data& a_Data, const data& a_OwnerData, const string& a_ReferenceExpression, modifiers_t a_ReferenceModifiers )
{
    o_assert(containsData(a_OwnerData));
    o_assert(!containsData(a_Data));
    m_pDataBase->addComponentData(a_Data, a_OwnerData, a_ReferenceExpression, a_ReferenceModifiers);
}

void Node::replaceComponentData( const data& a_OldData, const data& a_NewData )
{
    m_pDataBase->disconnectData(a_OldData);
    m_pDataBase->dataAboutToBeReplaced(a_OldData, this);
    phantom::data owner = m_pDataBase->getComponentDataOwner(a_OldData);
    string expression = m_pDataBase->getComponentDataReferenceExpression(a_OldData);
    modifiers_t modifiers = m_pDataBase->getDataModifiers(a_OldData);
    m_pDataBase->replaceDataInfo(a_OldData, a_NewData);
    a_OldData.type()->smartCopy(a_NewData.type(), a_NewData.address(), a_OldData.address());
    m_pDataBase->dataReplaced(a_NewData, this);
}

void Node::removeComponentData( const data& a_Data )
{
    o_assert(containsData(a_Data));
    const string& refExp = m_pDataBase->getComponentDataReferenceExpression(a_Data);
    o_assert(refExp.size());
    reflection::Expression* pExpression = expressionByName(refExp+"=nullptr");
    o_assert(pExpression);
    pExpression->eval();
}

phantom::data Node::newData( reflection::Type* a_pType )
{
    phantom::data d(a_pType->newInstance(), a_pType);
    m_pDataBase->addData(d, this);
    return d;
}

void Node::removeData( const phantom::data& a_Data )
{
    o_assert(containsData(a_Data));
    m_pDataBase->removeData(a_Data);
}

void Node::unloadData( const phantom::data& a_Data )
{
    o_assert(containsData(a_Data));
    m_pDataBase->unloadData(a_Data);
}

void Node::abortData( const phantom::data& a_Data )
{
    o_emit m_pDataBase->dataAboutToBeAborted(a_Data, this);
    uint guid = m_pDataBase->getGuid(a_Data);
    o_assert(guid != o_invalid_guid, "Data not found in DataBase");
    m_pDataBase->releaseGuid(guid);
    m_pDataBase->destroyDataEntry(a_Data, guid, this);
    m_pDataBase->unregisterData(a_Data);
    eraseData(a_Data);
    const_cast<phantom::data&>(a_Data).destroy();
}

Node* Node::newChildNode()
{
    return m_pDataBase->internalAddNewNode(this);
}

Node* Node::newChildNode( uint guid )
{
    return m_pDataBase->internalAddNewNode(guid, this);
}

void Node::removeChildNode( Node* a_pNode )
{
	o_assert(containsNode(a_pNode));
	m_pDataBase->internalRemoveNode(a_pNode, a_pNode->getGuid(), a_pNode->getParentNode());
    eraseNode(a_pNode);
    o_dynamic_delete a_pNode;
}

void Node::load()
{
    if(NOT(canLoad()))
    {
        o_exception(exception::base_exception, "Node cannot be loaded");
    }
    o_assert(m_eState == e_Unloaded);
    if(m_pParentNode AND m_pParentNode->getState() == e_Unloaded)
    {
        o_exception(exception::base_exception, "The parent node should be loaded before loading a child node");
    }
    cache(); 
    m_eState = e_Cached;
    build(m_Data); 
    m_eState = e_Built;
    deserialize(m_pDataBase->m_uiSerializationFlag, m_Data); 
    m_eState = e_Deserialized;
    restore(m_pDataBase->m_uiSerializationFlag, m_Data); 
    m_eState = e_Loaded;
    configure();
    loadDataAttributes();
    o_emit loaded();

    if(m_pDataBase->getDataStateBase())
    {
        loadState(m_Data, m_pDataBase->getDataStateBase()->getCurrentStateId());
    }

    // Connect data and fetch new components
    size_t oldCount = m_Data.size();
    for(size_t i = 0; i<oldCount; ++i)
    {
        m_pDataBase->connectData(m_Data[i]);
    }

    // If new data added => new components added in fact => we save the index
    if(oldCount != m_Data.size())
    {
        saveIndex();
    }
}

void Node::unload()
{
    node_vector::const_iterator it = m_ChildNodes.begin();
    node_vector::const_iterator end = m_ChildNodes.end();
    for(;it!=end;++it)
    {
        if((*it)->getState() != e_Unloaded)
        {
            o_exception(exception::base_exception, "All child node should be unloaded before unloading a parent node");
        }
    }
    // Disconnect data
    for(size_t i = 0; i<m_Data.size(); ++i)
    {
        m_pDataBase->disconnectData(m_Data[i]);
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
    saveIndex(); 
    saveData(); 
    saveAttributes();
}

void Node::saveDataAttributes( const phantom::data& a_Data )
{
    saveDataAttributes(a_Data, m_pDataBase->getGuid(a_Data));
}

void Node::loadDataAttributes( const phantom::data& a_Data )
{
    loadDataAttributes(a_Data, m_pDataBase->getGuid(a_Data));
}

void Node::saveDataProperties( const phantom::data& a_Data)
{
    saveDataProperties(m_pDataBase->m_uiSerializationFlag, a_Data, m_pDataBase->getGuid(a_Data));
}

void Node::loadData( const phantom::data& a_Data )
{
    loadData(m_pDataBase->m_uiSerializationFlag, a_Data, m_pDataBase->getGuid(a_Data));
}

void Node::loadData( uint a_uiSerializationFlag, const phantom::data& a_Data, uint a_uiGuid )
{
    loadDataProperties(a_uiSerializationFlag, a_Data, a_uiGuid);
    if(m_pDataBase->getDataStateBase())
    {
        loadDataState(a_Data, m_pDataBase->getDataStateBase()->getCurrentStateId());
    }
    loadDataAttributes(a_Data, a_uiGuid);
}

void Node::saveStateCascade( DataStateBase* a_pDataStateBase, uint a_uiStateId )
{
    o_assert(isLoaded());
    a_pDataStateBase->saveState(this, m_Data, a_uiStateId);
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
    o_assert(m_pDataBase->getDataStateBase(), "You must associate a DataStateBase with this DataBase to be able to load/save states");
    saveStateCascade(m_pDataBase->getDataStateBase(), a_uiStateId);
}

void Node::loadStateCascade( DataStateBase* a_pDataStateBase, uint a_uiStateId )
{
    o_assert(isLoaded());
    a_pDataStateBase->loadState(this, m_Data, a_uiStateId);
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
    o_assert(m_pDataBase->getDataStateBase(), "You must associate a DataStateBase with this DataBase to be able to load/save states");
    loadStateCascade(m_pDataBase->getDataStateBase(), a_uiStateId);
}

void Node::saveState( const vector<data>& a_Data, uint a_uiState )
{
    o_assert(m_pDataBase->getDataStateBase(), "You must associate a DataStateBase with this DataBase to be able to load/save states");
    o_assert(isLoaded());
    m_pDataBase->getDataStateBase()->saveState(this, a_Data, a_uiState);
}

void Node::loadState( const vector<data>& a_Data, uint a_uiState )
{
    o_assert(m_pDataBase->getDataStateBase(), "You must associate a DataStateBase with this DataBase to be able to load/save states");
    o_assert(isLoaded());
    //o_assert(m_pDataBase->getDataStateBase()->hasStateSaved(this, a_uiState), "No state previously saved for this node");
    if (m_pDataBase->getDataStateBase()->hasStateSaved(this, a_uiState))
	{
		m_pDataBase->getDataStateBase()->loadState(this, a_Data, a_uiState);
	}
}

bool Node::hasStateSaved( uint a_uiState ) const
{
    o_assert(m_pDataBase->getDataStateBase());
    return m_pDataBase->getDataStateBase()->hasStateSaved(const_cast<Node*>(this), a_uiState);
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

void Node::replaceDataReferenceCascade( const phantom::data& a_Old, const phantom::data& a_New, vector<reflection::Expression*>* a_pReplacedReferenceExpressions ) const
{
    vector<reflection::Expression*> clearedObsoleteReferencesExpressions;
    o_foreach(Node* pChildNode, m_ChildNodes)
    {
        if(pChildNode->isLoaded())
        {
            pChildNode->replaceDataReferenceCascade(a_Old, a_New, a_pReplacedReferenceExpressions);
        }
    }
    bool complete = replaceDataReference(a_Old, a_New, false);
    if(NOT(complete)) // incompatible types found
    {
        // so try to clear "cleanly" (with public propertys or attributes) old reference
        clearDataReference(a_Old, &clearedObsoleteReferencesExpressions);

        // and then make a second replacement pass with forcing incompatible new data to null
        complete = replaceDataReference(a_Old, a_New, true);

        o_assert(complete);
    }
}

void Node::clearDataReferenceCascade( const phantom::data& a_Data, vector<reflection::Expression*>* a_pRestoreReferenceExpressions ) const
{
    o_foreach(Node* pChildNode, m_ChildNodes)
    {
        if(pChildNode->isLoaded())
        {
            pChildNode->clearDataReferenceCascade(a_Data, a_pRestoreReferenceExpressions);
        }
    }
    clearDataReference(a_Data, a_pRestoreReferenceExpressions);
}

void Node::loadDataState( const phantom::data& a_Data, uint a_uiStateId )
{
    DataStateBase* pDataStateBase = m_pDataBase->getDataStateBase();
    if(pDataStateBase == nullptr)
    {
        o_exception(exception::base_exception, "No data state base defined for the current data base");
    }
    pDataStateBase->loadDataState(a_Data, m_pDataBase->getGuid(a_Data), this, a_uiStateId);
}

void Node::saveDataState( const phantom::data& a_Data, uint a_uiStateId )
{
    DataStateBase* pDataStateBase = m_pDataBase->getDataStateBase();
    if(pDataStateBase == nullptr)
    {
        o_exception(exception::base_exception, "No data state base defined for the current data base");
    }
    pDataStateBase->saveDataState(a_Data, m_pDataBase->getGuid(a_Data), this, a_uiStateId);
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
                if(m_pDataBase->containsData(d) AND m_pDataBase->getComponentDataOwner(d).isNull()) 
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

    a_pContainerClass->release(pIterator);
}

void Node::clearDataReference( const phantom::data& a_Data, const phantom::data& a_ReferencedData, vector<reflection::Expression*>* a_pRestoreReferenceExpressions ) const
{
    vector<reflection::Expression*> pointerReferenceExpressions;
    auto pConstant = phantom::constant<uint>(m_pDataBase->getGuid(a_Data));

    // Create an expression referencing our data
    auto pExpression = o_new(reflection::DataExpression)(m_pDataBase, o_new(reflection::ConstantExpression)(pConstant)) ;

    // Then collect all its pointer references (in fact all the data referenced by our data)
    a_Data.type()->fetchPointerReferenceExpressions(pExpression 
        , pointerReferenceExpressions
        , 0xffffffff);

    // For each referenced data (pointer), compare it against our old data 

    for(auto it = pointerReferenceExpressions.begin(); it != pointerReferenceExpressions.end(); ++it)
    {
        reflection::Expression* pExpression = *it;
        if(as<reflection::InstanceDataMemberExpression*>(pExpression) == nullptr) 
            continue; // components are a special case not considered as reference only but composition (stronger)
        void* pAddress = nullptr;
        pExpression->load(&pAddress);// Evaluate expression to get pointer reference value
        if(pAddress == nullptr)
            continue;
        const rtti_data& rd = rttiDataOf(pAddress);
        if(rd.isNull()) 
            continue;
        if(rd.base == a_ReferencedData.address())
        {
            // If matches, clear the reference by setting the expression to null
            pAddress = nullptr;
            pExpression->store(&pAddress);
            if(a_pRestoreReferenceExpressions) 
                a_pRestoreReferenceExpressions->push_back(pExpression);
            else o_dynamic_delete (pExpression);
        }
        else o_dynamic_delete (pExpression); // destroy the pointer reference expression
    }
//     if(pointerReferenceExpressions.empty())
//     {
//         o_dynamic_delete (pExpression); // destroy the data reference expression (no pointer reference generated)
//     }
}

void Node::clearDataReference( const phantom::data& a_ReferencedData, vector<reflection::Expression*>* a_pRestoreReferenceExpressions ) const
{
    o_assert(isLoaded());
    data_vector::const_iterator it = m_Data.begin();
    data_vector::const_iterator end = m_Data.end();
    for(;it != end; ++it)
    {
        const phantom::data& currentData = *it;
        bool currentDataModified = false;

        if(currentData == a_ReferencedData)
            continue;

        clearDataReference(currentData, a_ReferencedData, a_pRestoreReferenceExpressions);

    }
//     if(currentDataModified)
//     {
//         // Save if modified
//         // TODO : clean this dirty hack by using const on saveData
//         ((Node*)this)->saveDataProperties(currentData);
//     }
}

bool Node::replaceDataReference( const phantom::data& a_Old, const phantom::data& a_New, bool a_SetIncompatibleToNull ) const
{
    o_assert(isLoaded());
    bool complete = true;
    data_vector::const_iterator it = m_Data.begin();
    data_vector::const_iterator end = m_Data.end();
    for(;it != end; ++it)
    {
        complete = complete AND replaceDataReference(*it, a_Old, a_New, a_SetIncompatibleToNull);
    }
    return complete;
}

bool Node::replaceDataReference( const phantom::data& a_Data, const phantom::data& a_Old, const phantom::data& a_New, bool a_SetIncompatibleToNull ) const
{
    o_assert(isLoaded());
    bool complete = true;
    bool currentDataModified = false;

    vector<reflection::Expression*> pointerReferenceExpressions;
    auto pConstant = phantom::constant<uint>(m_pDataBase->getGuid(a_Data));

    // Create an expression referencing our data
    auto pExpression = o_new(reflection::DataExpression)(m_pDataBase, o_new(reflection::ConstantExpression)(pConstant)) ;

    // Then collect all its pointer references (in fact all the data referenced by our data)
    a_Data.type()->fetchPointerReferenceExpressions(pExpression 
        , pointerReferenceExpressions
        , 0xffffffff);

    // For each referenced data (pointer), compare it against our old data
    for(auto it = pointerReferenceExpressions.begin(); it != pointerReferenceExpressions.end(); ++it)
    {
        reflection::Expression* pExpression = *it;
        void* pAddress = nullptr;
        pExpression->load(&pAddress);// Evaluate expression to get pointer reference value
        if(pAddress == nullptr)
            continue;
        const rtti_data& rd = rttiDataOf(pAddress);
        if(rd.isNull()) 
            continue;
        if(rd.base == a_Old.address())
        {
            // The pointer references the old data
            // => cast the new data to fit the expression pointed type
            phantom::data castedNewData = a_New.cast(pExpression->getValueType()->removeReference()->removeConst()->asDataPointerType()->getPointedType());
            if(castedNewData.isNull())
            {
                if(a_SetIncompatibleToNull)
                {
                    // The casted data is null (cast failed) => the data cannot be referenced anymore => set it to NULL
                    pAddress = nullptr;
                    pExpression->store(&pAddress);

                    // Remember this expression as a nullified expression
                }
                else 
                {
                    complete = false;
                }
            }
            else 
            {
                pAddress = castedNewData.address();
                pExpression->store(&pAddress);
            }
        }
    }
    return complete;
}

void Node::fetchAllUpdatedData( vector<data_pair>& out_components_to_add
    , vector<data_pair>& out_components_to_remove
    , vector<string>& out_components_to_add_reference_expressions
    , vector<modifiers_t>& out_to_add_modifiers
    , vector<data>& a_TreatedData )
{
    for(size_t i = 0; i<m_Data.size(); ++i)
    {
        fetchUpdatedData(m_Data[i], out_components_to_add, out_components_to_remove, out_components_to_add_reference_expressions, out_to_add_modifiers, a_TreatedData);
    }
}

void Node::fetchAllUpdatedDataCascade( vector<Node*>& where_to_add, vector<Node*>& where_to_remove, vector<data_pair>& out_components_to_add , vector<data_pair>& out_components_to_remove , vector<string>& out_components_to_add_reference_expressions , vector<modifiers_t>& out_to_add_modifiers , vector<data>& a_TreatedData )
{
    fetchAllUpdatedData(out_components_to_add, out_components_to_remove, out_components_to_add_reference_expressions, out_to_add_modifiers, a_TreatedData);
    where_to_add.resize(where_to_add.size() + out_components_to_add.size(), this);
    where_to_remove.resize(where_to_remove.size() + out_components_to_remove.size(), this);
    for(auto it = m_ChildNodes.begin(); it != m_ChildNodes.end(); ++it)
    {
        (*it)->fetchAllUpdatedDataCascade(where_to_add, where_to_remove, out_components_to_add, out_components_to_remove, out_components_to_add_reference_expressions, out_to_add_modifiers, a_TreatedData);
    }
}

void Node::fetchUpdatedData( const phantom::data& a_Data
                                , vector<data_pair>& out_components_to_add
                                , vector<data_pair>& out_components_to_remove
                                , vector<string>& out_components_to_add_reference_expressions
                                , vector<modifiers_t>& out_to_add_modifiers
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
                                , vector<modifiers_t>& out_to_add_modifiers
                                , std::set<phantom::data>& treatedData)
{
    treatedData.insert(a_Data);
    bool indexOutdated = false;
    phantom::data d = a_Data;

    vector<phantom::data> new_components;
    vector<reflection::Expression*> pointerReferenceExpressions;
    auto pConstant = phantom::constant<uint>(m_pDataBase->getGuid(a_Data));
    auto pExpression = o_new(reflection::DataExpression)(m_pDataBase, o_new(reflection::ConstantExpression)(pConstant)) ;
    d.type()->fetchPointerReferenceExpressions(pExpression->clone() 
                                                , pointerReferenceExpressions
                                                , 0xffffffff);
    // o_dynamic_delete (pConstant);
    o_dynamic_delete (pExpression);
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
        if(m_pDataBase->getGuid(referencedData) != o_invalid_guid AND treatedData.find(referencedData) == treatedData.end())
        {
            // If data referenced exists in the data base, we treat it
            m_pDataBase->getNode(referencedData)->fetchUpdatedData(referencedData, out_components_to_add, out_components_to_remove, out_added_pointer_reference_expressions, out_to_add_modifiers, treatedData);
        }
    }

    DataBase* pDataBase = getDataBase();

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
            m_pDataBase->getNode(*it)->fetchUpdatedData(*it, out_components_to_add, out_components_to_remove, out_added_pointer_reference_expressions, out_to_add_modifiers, treatedData);
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
            o_assert(m_pDataBase->containsData(*it))
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
            o_assert(NOT(m_pDataBase->containsData(*it))) // the data is a shared data
            {
                out_components_to_add.push_back(data_pair(*it, d));
                phantom::reflection::Expression* pExpression = dataReferenceExpressions[*it];
                out_added_pointer_reference_expressions.push_back(pExpression->getName());
                out_to_add_modifiers.push_back(pExpression->getModifiers());
                //indexOutdated = true;
            }
            //saveData(*it);
        }
    }
    for(auto it = dataReferenceExpressions.begin(); it != dataReferenceExpressions.end(); ++it)
    {
        o_dynamic_delete (it->second);
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
            m_pDataBase->rebuildData(*it, a_pOld, a_pNew, a_OldData, a_NewData, a_uiStateId);
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
    if(m_pDataBase->getDataStateBase())
    {
        saveDataState(a_Data, m_pDataBase->getDataStateBase()->getCurrentStateId());
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
        uint guid = m_pDataBase->getGuid(*it);
        saveData(a_uiSerializationFlag, *it, guid);
    }
}

void Node::destroyAllData()
{
    while(m_Data.size())
    {
        phantom::data d = m_Data.back();
        m_pDataBase->unregisterData(d);
        d.destroy();
    }
}

boolean Node::containsDataWhichDependsOnData( const data& a_Dependency ) const
{
    data_vector::const_iterator it = m_Data.begin();
    data_vector::const_iterator end = m_Data.end();
    for(;it != end; ++it)
    {
        if(m_pDataBase->dataHasDependency(*it, a_Dependency))
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
        if(m_pDataBase->dataHasDependency(*it, a_Data))
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
        if(m_pDataBase->dataHasDependency(a_Data, *it))
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

uint Node::generateGuid() const
{
    return m_pDataBase->generateGuid();
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

void Node::fetchDataByTypes( map<reflection::Type*, vector<data> >& out ) const
{
    for(auto it = m_Data.begin(); it != m_Data.end(); ++it)
    {
        out[it->type()].push_back(*it);
    }
}

void Node::fetchDataByTypesCascade( map<reflection::Type*, vector<data> >& out ) const
{
    fetchDataByTypes(out);
    for(auto it = m_ChildNodes.begin(); it != m_ChildNodes.end(); ++it)
    {
        (*it)->fetchDataByTypesCascade(out);
    }
}

void Node::reload( const vector<uint>& guids )
{
    vector<phantom::data> cachedData;
    cache(&guids, &cachedData);
    build(cachedData);
    deserialize(m_pDataBase->m_uiSerializationFlag, cachedData);
    restore(m_pDataBase->m_uiSerializationFlag, cachedData);

    if(m_pDataBase->getDataStateBase())
    {
        loadState(cachedData, m_pDataBase->getDataStateBase()->getCurrentStateId());
    }
}

o_namespace_end(phantom, serialization)
