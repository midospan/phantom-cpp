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
#include <phantom/serialization/DefaultNode.h>
/* *********************************************** */
o_cpp_begin


ReflectionCPP__________________________________________________________________________________
__________________________________________________________________________________ReflectionCPP


void DefaultNode::applyDataVisitor( util::TVisitor<data>* visitor )
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

void DefaultNode::destroyAllData()
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

boolean DefaultNode::containsDataWhichDependsOnData( const data& a_Dependency ) const
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


void DefaultNode::getAllDataWhichDependsOnData(const phantom::data& a_Data, vector<data>& a_DataVector) const
{
    data_vector::const_iterator it = m_Data.begin();
    data_vector::const_iterator end = m_Data.end();
    for(;it != end; ++it)
    {
        if(m_pOwnerDataBase->dataHasDependency(*it, a_Data))
            a_DataVector.push_back(*it);
    }
}

boolean DefaultNode::dependsOn( Node* a_pNode ) const
{
    o_assert(is<DefaultNode>(a_pNode));
    DefaultNode* pDefaultNode = static_cast<DefaultNode*>(a_pNode);
    data_vector::const_iterator it = m_Data.begin();
    data_vector::const_iterator end = m_Data.end();
    for(;it != end; ++it)
    {
        if(containsDataWhichDependsOnData(*it)) 
            return true;
    }
    return false;
}

boolean DefaultNode::containsDependencyOf( const data& a_Data ) const
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

void DefaultNode::clearDataReference( const vector<void*>& layout ) const
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
                vector<reflection::Collection*> collections;
                if(pClass)
                {
                    pClass->getAllValueMemberCascade(valueMembers);
                    pClass->getAllCollectionCascade(collections);
                }
                else
                {
                    pClassType->getAllValueMember(valueMembers);
                    pClassType->getAllCollection(collections);
                }
                struct PropertyThenAttributeSorter
                {
                    bool operator()(const reflection::ValueMember* first, const reflection::ValueMember* second) const 
                    {
                        if(first->isProperty() AND NOT(second->isProperty())) return true;
                        if(second->isProperty() AND NOT(first->isProperty())) return false;
                        return first < second;
                    }
                };

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
            ((DefaultNode*)this)->saveData(currentData);
        }
    }
}


bool    DefaultNode::replaceDataReference(const vector<void*>& a_OldLayout, const phantom::data& a_New, bool a_SetIncompatibleToNull) const
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

            if(currentData == m_pOwnerDataBase->getSubDataOwner(oldAddress))
            {
                // the current data owns the old data, so we check if it can own the new data
                reflection::Collection* collection = m_pOwnerDataBase->getCollectionContainingSubData(oldAddress);
                if(NOT(a_New.type()->isKindOf(collection->getElementType())))
                {
                    // If not, we remove the old via the interface
                    void* removed = oldAddress;
                    collection->safeRemoveElement(currentData.address(), &removed);
                    currentDataModified = true;
                }
            }
            else if(oldAddress == m_pOwnerDataBase->getSubDataOwner(currentData).address())
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
                    pClass->getAllValueMemberCascade(valueMembers);
                }
                else
                {
                    pClassType->getAllValueMember(valueMembers);
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
            ((DefaultNode*)this)->saveData(currentData);
        }
    }
    return complete;
}


void DefaultNode::rebuildAllData( reflection::Type* a_pOld, reflection::Type* a_pNew, vector<data>& a_OldData, vector<data>& a_NewData, uint a_uiStateId /*= 0xffffffff*/ )
{
    o_assert(isLoaded());
    data_vector::iterator it = m_Data.begin();
    data_vector::iterator end = m_Data.end();
    for(;it != end; ++it)
    {
        if(it->type() == a_pOld) 
        {
            rebuildData(*it, a_pOld, a_pNew, a_OldData, a_NewData, a_uiStateId);
        }
    }
}

void DefaultNode::addDataComponents(vector<std::pair<phantom::data,phantom::data>>* opt_out_to_add /*= nullptr*/, vector<std::pair<phantom::data,phantom::data>>* opt_out_to_remove /*= nullptr*/)
{
    size_t i = 0;
    for(;i<m_Data.size();++i)
    {
        addDataComponents(m_Data[i], m_Data.size(), opt_out_to_add, opt_out_to_remove);
    }
}


void DefaultNode::addDataComponents( const phantom::data& a_Data, size_t a_uiCurrentSize, vector<std::pair<phantom::data,phantom::data>>* opt_out_to_add /*= nullptr*/, vector<std::pair<phantom::data,phantom::data>>* opt_out_to_remove /*= nullptr*/)
{
	phantom::data d = a_Data;

    vector<phantom::data> new_components;
    fetchDataComponents(d, new_components);

    DataBase* pDataBase = getOwnerDataBase();

    vector<phantom::data> old_components;
    size_t i = 0;
    for(;i<a_uiCurrentSize;++i)
    {
        if(pDataBase->getSubDataOwner(m_Data[i]) == d)
        {
            old_components.push_back(m_Data[i]);
        }
    }
    vector<phantom::data> in_both(std::min(new_components.size(), old_components.size()));
    std::sort(new_components.begin(), new_components.end());
    auto last = std::unique(new_components.begin(), new_components.end());
    new_components.resize(last - new_components.begin());
    std::sort(old_components.begin(), old_components.end());
    last = std::unique(old_components.begin(), old_components.end());
    old_components.resize(last - old_components.begin());
    last = std::set_intersection(new_components.begin(), new_components.end(), old_components.begin(), old_components.end(), in_both.begin());
    in_both.erase(last, in_both.end());

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
			if(m_pOwnerDataBase->containsData(*it))
			{
				removeData(*it);
			}
			pDataBase->unregisterSubDataOwner(*it);
			if(opt_out_to_remove) opt_out_to_remove->push_back(std::pair<phantom::data, phantom::data>(d, *it));
		}
	}

    {
        auto it = to_add.begin();
        auto end = to_add.end();
        for(;it!=end;++it)
        {
            pDataBase->registerSubDataOwner(*it, d);
            if(opt_out_to_add) opt_out_to_add->push_back(std::pair<phantom::data, phantom::data>(d, *it));
            if(NOT(m_pOwnerDataBase->containsData(*it))) // the data is a shared data
            {
                addData(*it);
            }
        }
    }
}

void DefaultNode::addDataComponents(const phantom::data& a_Data, vector<std::pair<phantom::data,phantom::data>>* opt_out_to_add /*= nullptr*/, vector<std::pair<phantom::data,phantom::data>>* opt_out_to_remove /*= nullptr*/)
{
    size_t initSize = m_Data.size();
    addDataComponents(a_Data, m_Data.size(), opt_out_to_add, opt_out_to_remove);
    size_t addedCount = m_Data.size() - initSize;

    size_t i = m_Data.size() - addedCount;
    for(;i<addedCount;++i)
    {
        addDataComponents(m_Data[i], opt_out_to_add, opt_out_to_remove);
    }
}

o_cpp_end