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
/* ** The Class Header must be the last #include * */
#include <phantom/serialization/Node.h>
/* *********************************************** */
o_cpp_begin

ReflectionCPP__________________________________________________________________________________
o_signal(loaded, ())
o_signal(aboutToBeUnloaded, ())
__________________________________________________________________________________ReflectionCPP


void Node::registerData( const phantom::data& a_Data, uint guid )
{
    storeData(a_Data);
    m_pOwnerDataBase->registerData(a_Data, guid, this);
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

boolean Node::stepByStep(uint a_uiSerializationFlag)
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
            build();
            m_eState = e_Built;
        }
        break;
    case e_Built:
        {
            deserialize(a_uiSerializationFlag);
            m_eState = e_Deserialized;
        }
        break;
    case e_Deserialized:
        {
            restore(a_uiSerializationFlag);
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
    o_assert(m_eState == e_Loaded);
    o_assert(NOT(m_pOwnerDataBase->containsData(a_Data)), "The specified owner Node doesn't belong to this DataBase");
    o_assert(a_Data.type()->isSerializable());
    storeData(a_Data);
    uint guid = m_pOwnerDataBase->generateGuid();
    o_assert(guid != 0, "0 is reserved to the root node, fix your generateGuid() overloaded method so that is returns a guid > 0");
    m_pOwnerDataBase->createDataEntry(a_Data, guid, this);
    m_pOwnerDataBase->registerData(a_Data, guid, this);
    o_emit m_pOwnerDataBase->dataAdded(a_Data, this);
    //saveIndex();
}

void Node::addData( const data& a_Data, UINT a_uiGuid )
{
	o_assert(m_eState == e_Loaded);
	o_assert(NOT(m_pOwnerDataBase->containsData(a_Data)), "The specified owner Node doesn't belong to this DataBase");
	o_assert(a_Data.type()->isSerializable());
	storeData(a_Data);
	o_assert(a_uiGuid != 0, "0 is reserved to the root node");
	m_pOwnerDataBase->createDataEntry(a_Data, a_uiGuid, this);
	m_pOwnerDataBase->registerData(a_Data, a_uiGuid, this);
	o_emit m_pOwnerDataBase->dataAdded(a_Data, this);
	//saveIndex();
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
        o_assert(guid != 0, "0 is reserved to the root node, fix your generateGuid() overloaded method so that is returns a guid > 0");
        data d(pChunk, pType);
        m_pOwnerDataBase->createDataEntry(d, guid, this);
        m_pOwnerDataBase->registerData(d, guid, this);
        o_emit m_pOwnerDataBase->dataAdded(d, this);
        pChunk += a_uiChunkSectionSize;
    }
    //saveIndex();
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
    o_assert(containsData(a_Data));

    // TODO : make a virtual "removeAllSubData(a_Data)" instead of this
    bool subDataRemovalPassNeeded = true;
    while(subDataRemovalPassNeeded)
    {
        subDataRemovalPassNeeded = false;
        vector<data> allData;
        getAllData(allData);
        size_t i = 0;
        for(;i<allData.size();++i)
        {
            if( getOwnerDataBase()->getSubDataOwner(allData[i]) == a_Data )
            {
                removeData(allData[i]);
                subDataRemovalPassNeeded = true;
                break;
            }
        }
    }
    

    // Ensure clearing/dereferencing in other data
    getOwnerDataBase()->clearDataReference(a_Data);
    
    o_emit m_pOwnerDataBase->dataAboutToBeRemoved(a_Data, this);
    uint guid = m_pOwnerDataBase->getGuid(a_Data.address());
    o_assert(guid != 0xFFFFFFFF, "Data not found in DataBase");
    m_pOwnerDataBase->releaseGuid(guid);
    m_pOwnerDataBase->destroyDataEntry(a_Data, guid, this);
    m_pOwnerDataBase->unregisterData(a_Data);
    eraseData(a_Data); 
    //saveIndex();
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

Node* Node::addChildNode()
{
    return m_pOwnerDataBase->createNewNode(this);
}

void Node::addChildNode(Node* a_pNode, uint a_uiGuid)
{
	return m_pOwnerDataBase->addNode(a_pNode, this, a_uiGuid);
}

void Node::removeAndDeleteChildNode( Node* a_pNode )
{
    o_assert(containsNode(a_pNode));
    return m_pOwnerDataBase->deleteNode(a_pNode);
}

void Node::removeChildNode( Node* a_pNode )
{
	o_assert(containsNode(a_pNode));
	return m_pOwnerDataBase->removeNode(a_pNode);
}

void Node::load()
{
    load(m_pOwnerDataBase->m_uiSerializationFlag);

	// Component owners are not saved
	// Add new data components
    /*vector<std::pair<phantom::data, phantom::data>> added;
    addDataComponents(&added);

    // If component have been added after loading we save the node index 
    if(NOT(added.empty())) saveIndex();*/
}

void Node::load( uint a_uiSerializationFlag )
{
    o_assert(m_eState == e_Unloaded);
    if(m_pParentNode AND m_pParentNode->getState() == e_Unloaded)
    {
        o_exception(std::exception, "The parent node should be loaded before loading a child node");
    }
    cache(); 
    m_eState = e_Cached;
    build(); 
    m_eState = e_Built;
    deserialize(a_uiSerializationFlag); 
    m_eState = e_Deserialized;
    restore(a_uiSerializationFlag); 
    m_eState = e_Loaded;
    configure();
    loadDataAttributes();
    o_emit loaded();
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
    addDataComponents();
    save(m_pOwnerDataBase->m_uiSerializationFlag);
}

void Node::saveDataAttributes( const phantom::data& a_Data )
{
    saveDataAttributes(a_Data, m_pOwnerDataBase->getGuid(a_Data));
}

void Node::loadDataAttributes( const phantom::data& a_Data )
{
    loadDataAttributes(a_Data, m_pOwnerDataBase->getGuid(a_Data));
}

void Node::saveData( const phantom::data& a_Data )
{
    saveData(m_pOwnerDataBase->m_uiSerializationFlag, a_Data, m_pOwnerDataBase->getGuid(a_Data));
}

void Node::loadData( const phantom::data& a_Data )
{
    loadData(m_pOwnerDataBase->m_uiSerializationFlag, a_Data, m_pOwnerDataBase->getGuid(a_Data));
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

phantom::signal_t Node::loaded(void) const
{
    phantom::connection::slot* pSlot = PHANTOM_CODEGEN_m_slot_list_of_loaded.head();
    while(pSlot)
    {
        phantom::connection::pair::push(this, pSlot);
        pSlot->subroutine()->invoke(pSlot->receiver(), o_no_arg );
        pSlot = pSlot->next();
        phantom::connection::pair::pop();
    }
    return phantom::signal_t();
}

void Node::rebuildData( phantom::data& a_inOutData, reflection::Type* a_pOld, reflection::Type* a_pNewType, vector<data>& a_Old, vector<data>& a_New, uint a_uiStateId /*= 0xffffffff*/ )
{
    o_assert(a_inOutData.type() == a_pOld);
    o_assert(a_pOld->isClass() == a_pNewType->isClass(), "to be replaced, types must be of the same 'type', both classes or both not classes");

    phantom::data newData(a_pNewType->allocate(), a_pNewType);
    a_pNewType->build(newData.address());
    phantom::data oldData = a_inOutData;

    // Replace by the new data
    a_inOutData = newData;

    a_Old.push_back(oldData);
    a_New.push_back(newData);
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
        // so try to clear "cleanly" (with public accessors or attributes) old reference
        clearDataReference(a_OldLayout);

        // and then make a second replacement pass with forcing incompatible new data to null
        complete = replaceDataReference(a_OldLayout, a_New, true);

        o_assert(complete);
    }
}

void Node::clearDataReferenceCascade( const vector<void*>& a_OldLayout ) const
{
    o_foreach(Node* pChildNode, m_ChildNodes)
    {
        if(pChildNode->isLoaded())
        {
            pChildNode->clearDataReferenceCascade(a_OldLayout);
        }
    }
    clearDataReference(a_OldLayout);
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
    reflection::IteratorVariable* pIterator = a_pContainerClass->begin(a_pContainer);
    bool needAnotherPass = false;
    reflection::Type* pType = a_pContainerClass->getValueType();
    if(pType->isDataPointerType())
    {
        void* ptr = nullptr; 
        while(pIterator->hasNext())
        {
            ((util::Iterator*)pIterator)->getValue(&ptr);
            phantom::data d(ptr);
            if(NOT(d.isNull()))
            {
                if(m_pOwnerDataBase->containsData(d) AND m_pOwnerDataBase->getSubDataOwner(d).isNull()) 
                {
                    // component property contains a non-component data => clear it
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

    o_dynamic_delete pIterator;

    if(needAnotherPass)
    {

    }
}

void Node::fetchDataComponents(const phantom::data& a_Data, vector<phantom::data>& out )
{
    reflection::Class* pClass = a_Data.type()->asClass();
    if(pClass == nullptr) return;
    vector<reflection::Property*> properties;
    pClass->getAllPropertyCascade(properties);

    struct AccessorThenAttributeSorter
    {
        bool operator()(const reflection::Property* first, const reflection::Property* second) const 
        {
            if(first->isAccessor() AND NOT(second->isAccessor())) return true;
            if(second->isAccessor() AND NOT(first->isAccessor())) return false;
            return first < second;
        }
    };

    std::sort(properties.begin(), properties.end(), AccessorThenAttributeSorter());

    auto it = properties.begin();
    auto end = properties.end();
    for(;it!=end;++it)
    {
        reflection::Property* pProperty = *it;
        if(pProperty->isComponent())
        {
            reflection::Type* pType = pProperty->getValueType();
            if(pType->isDataPointerType())
            {
                void* ptr = nullptr;
                pProperty->getValue(a_Data.cast(pProperty->getOwnerClass()).address(), &ptr);
                phantom::data d(ptr);
                o_warning(ptr == nullptr OR NOT(d.isNull()), "Non rtti registered data contained in a o_component property => cannot be saved properly");
                if(NOT(d.isNull()))
                {
                    if(m_pOwnerDataBase->containsData(d) && m_pOwnerDataBase->getSubDataOwner(d).isNull()) 
                    {
                        // component property contains a non-component data => clear it
                        ptr = nullptr;
                        pProperty->setValue(a_Data.cast(pProperty->getOwnerClass()).address(), &ptr);
                    }
                    else out.push_back(d);
                }
            }
            else 
            {
                reflection::ContainerClass* pContainerClass = pType->asContainerClass();
                o_assert(pContainerClass);
                void* pContainer = pContainerClass->newInstance();
                pProperty->getValue(a_Data.cast(pProperty->getOwnerClass()).address(), pContainer);
                fetchContainerComponents(pContainerClass, pContainer, out);
                pContainerClass->deleteInstance(pContainer);
            }
        }
    }
}



void Node::addDataComponentsCascade(vector<std::pair<phantom::data,phantom::data>>* opt_out_to_add /*= nullptr*/, vector<std::pair<phantom::data,phantom::data>>* opt_out_to_remove /*= nullptr*/)
{
    addDataComponents(opt_out_to_add, opt_out_to_remove);
    auto it = m_ChildNodes.begin();
    auto end = m_ChildNodes.end();
    for(;it!=end;++it)
    {
        (*it)->addDataComponentsCascade(opt_out_to_add, opt_out_to_remove);
    }
}


o_cpp_end
