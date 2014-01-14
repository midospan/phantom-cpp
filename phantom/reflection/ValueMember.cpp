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
#include "ValueMember.h"
/* *********************************************** */
o_cpp_begin 

ReflectionCPP__________________________________________________________________________________
__________________________________________________________________________________ReflectionCPP

ValueMember::ValueMember( const string& a_strName, Range* a_pRange, uint a_uiSerializationMask, bitfield a_Modifiers /*= 0*/ ) 
: LanguageElement(a_strName, a_Modifiers)
, m_uiSerializationMask(a_uiSerializationMask)
, m_pRange(a_pRange)
{

}

SubValueMember* ValueMember::getSubValueMember( const string& a_strName ) const
{
    phantom::vector<SubValueMember*>::const_iterator it = m_SubValueMembers.begin();
    for(;it != m_SubValueMembers.end();++it)
    {
        if((*it)->getName() == a_strName)
            return (*it);
    }
    return NULL;
}


// Default versions, working for any derived ValueMember, 
// but it is advise to optimize them in derived versions 
// to avoid the intermediate scratch instance

void            ValueMember::rememberValue(void const* a_pInstance, byte*& a_pOutBuffer) const
{
    phantom::reflection::Type* pType = getValueType();
    void*    scratch_instance = pType->newInstance();
    getValue(a_pInstance, scratch_instance);
    getValueType()->remember(scratch_instance, a_pOutBuffer);
    pType->deleteInstance(scratch_instance);
}

void            ValueMember::rememberValue(void const* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer) const
{
    byte const* pChunk = reinterpret_cast<byte const*>(a_pInstance);
    while(a_uiCount--)
    {
        rememberValue(pChunk, a_pOutBuffer);
        pChunk += a_uiChunkSectionSize;
    }
}

void            ValueMember::resetValue(void* a_pInstance, byte const*& a_pInBuffer) const
{
    phantom::reflection::Type* pType = getValueType();
    void*    scratch_instance = pType->newInstance();
    pType->reset(scratch_instance, a_pInBuffer);
    setValue(a_pInstance, scratch_instance);
    pType->deleteInstance(scratch_instance);
}

void            ValueMember::resetValue(void* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer) const
{
    byte* pChunk = reinterpret_cast<byte*>(a_pInstance);
    while(a_uiCount--)
    {
        resetValue(pChunk, a_pInBuffer);
        pChunk += a_uiChunkSectionSize;
    }
}

void ValueMember::serializeValue( void const* a_pInstance, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase ) const
{
    phantom::reflection::Type* pNormalizedType = getValueType()->removeReference()->removeConst();
    void*    scratch_instance = pNormalizedType->newInstance();
    getValue(a_pInstance, scratch_instance);
    pNormalizedType->serialize(scratch_instance, a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
    pNormalizedType->deleteInstance(scratch_instance);
}

void ValueMember::serializeValue( void const* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase ) const
{
    byte const* pChunk = reinterpret_cast<byte const*>(a_pInstance);
    while(a_uiCount--)
    {
        serializeValue(pChunk, a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
        pChunk += a_uiChunkSectionSize;
    }
}

void ValueMember::deserializeValue( void* a_pInstance, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase ) const
{
    phantom::reflection::Type* pNormalizedType = getValueType()->removeReference()->removeConst();
    void*    scratch_instance = pNormalizedType->newInstance();
    pNormalizedType->deserialize(scratch_instance, a_pInBuffer, a_uiSerializationMask, a_pDataBase);
    setValue(a_pInstance, scratch_instance);
    pNormalizedType->deleteInstance(scratch_instance);
}

void ValueMember::deserializeValue( void* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase ) const
{
    byte* pChunk = reinterpret_cast<byte*>(a_pInstance);
    while(a_uiCount--)
    {
        deserializeValue(pChunk, a_pInBuffer, a_uiSerializationMask, a_pDataBase);
        pChunk += a_uiChunkSectionSize;
    }
}

void ValueMember::serializeValue( void const* a_pInstance, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase ) const
{
    phantom::reflection::Type* pNormalizedType = getValueType()->removeReference()->removeConst();
    void*    scratch_instance = pNormalizedType->newInstance();
    getValue(a_pInstance, scratch_instance);
    property_tree prop_tree;
    pNormalizedType->serialize(scratch_instance, prop_tree, a_uiSerializationMask, a_pDataBase);
    a_OutBranch.add_child(getName(), prop_tree);
    pNormalizedType->deleteInstance(scratch_instance);
}

void ValueMember::serializeValue( void const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase ) const
{
    byte const* pChunk = reinterpret_cast<byte const*>(a_pChunk);
    while(a_uiCount--)
    {
        serializeValue(pChunk, a_OutBranch, a_uiSerializationMask, a_pDataBase);
        pChunk += a_uiChunkSectionSize;
    }
}

void ValueMember::deserializeValue( void* a_pInstance, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase ) const
{
    boost::optional<const property_tree&> prop_tree_opt = a_InBranch.get_child_optional(getName());
    if(prop_tree_opt.is_initialized())
    {
        phantom::reflection::Type* pNormalizedType = getValueType()->removeReference()->removeConst();
        void*    scratch_instance = pNormalizedType->newInstance();
        pNormalizedType->deserialize(scratch_instance, *prop_tree_opt, a_uiSerializationMask, a_pDataBase);
        setValue(a_pInstance, scratch_instance);
        pNormalizedType->deleteInstance(scratch_instance);
    }
}

void ValueMember::deserializeValue( void* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase ) const
{
    byte* pChunk = reinterpret_cast<byte*>(a_pChunk);
    while(a_uiCount--)
    {
        deserializeValue(pChunk, a_InBranch, a_uiSerializationMask, a_pDataBase);
        pChunk += a_uiChunkSectionSize;
    }
}

Class* ValueMember::getSortingCategoryClass() const
{
    return classOf<ValueMember>();
}

o_cpp_end