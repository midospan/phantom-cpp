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
#include <sstream>
/* ** The Class Header must be the last #include * */
#include <phantom/reflection/PolymorphicArrayClass.h>
/* *********************************************** */

o_cpp_begin 

ReflectionCPP__________________________________________________________________________________
__________________________________________________________________________________ReflectionCPP

PolymorphicArrayClass::PolymorphicArrayClass( Class* a_pArrayContentType, bitfield a_bfModifiers /*= bitfield()*/)
: Class(a_pArrayContentType->getDecoratedName() + o_CS("[]"), sizeof(util::PolymorphicArray), boost::alignment_of<util::PolymorphicArray>::value, a_bfModifiers|(a_pArrayContentType->isNative()?o_native:0))
, m_pContentType(a_pArrayContentType)
{
}

PolymorphicArrayClass::PolymorphicArrayClass( void ) 
    : Class(o_CS("Object[]"), sizeof(util::PolymorphicArray), boost::alignment_of<util::PolymorphicArray>::value)
    , m_pContentType(classOf<Object>())
{

}

void PolymorphicArrayClass::setup()
{

}

PolymorphicArrayClass::ERelation PolymorphicArrayClass::getRelationWith( Type* a_pType ) const
{
    if(a_pType->isPolymorphicArrayClass())
    {
        Class* pOtherContentType = static_cast<PolymorphicArrayClass*>(a_pType)->getContentType();
        switch(m_pContentType->getRelationWith(pOtherContentType))
        {
        case eRelation_None : return eRelation_None;
        case eRelation_Equal : return eRelation_Equal;
        case eRelation_Child : return eRelation_GenericContentChild;
        case eRelation_Parent : return eRelation_GenericContentParent;
        case eRelation_GenericContentChild : return eRelation_GenericContentChild;
        case eRelation_GenericContentParent : return eRelation_GenericContentParent;
        }
        return eRelation_None;
    } 
    else 
    {
        return Class::getRelationWith(a_pType);
    }
}

boolean PolymorphicArrayClass::accepts( Type* a_pType ) const
{
    if(a_pType->isPolymorphicArrayClass())
    {
        if(a_pType->isConvertibleTo(const_cast<PolymorphicArrayClass*>(this))) return true;
        PolymorphicArrayClass* pArrayClass = static_cast<PolymorphicArrayClass*>(a_pType);
        return pArrayClass->getContentType()->isConvertibleTo(m_pContentType);
    }
    return false;
}

void* PolymorphicArrayClass::newInstance( Constructor* a_pConstructor, argument::list* a_pConstructorParam ) const
{
    util::PolymorphicArray* pInstance = phantom::extension::allocator<util::PolymorphicArray>::allocate();
    new (pInstance) util::PolymorphicArray(m_pContentType);
    return pInstance;
}

void* PolymorphicArrayClass::newInstance( Constructor* a_pConstructor, void** a_pConstructorParam ) const
{
    util::PolymorphicArray* pInstance = phantom::extension::allocator<util::PolymorphicArray>::allocate();
    new (pInstance) util::PolymorphicArray(m_pContentType);
    return pInstance;
}

void* PolymorphicArrayClass::newInstance() const
{
    util::PolymorphicArray* pInstance = phantom::extension::allocator<util::PolymorphicArray>::allocate();
    new (pInstance) util::PolymorphicArray(m_pContentType);
    return pInstance;
}

void PolymorphicArrayClass::construct( void* a_pObject ) const
{
    new (a_pObject) util::PolymorphicArray(m_pContentType);
}

void PolymorphicArrayClass::destroy( void* a_pObject ) const
{
    static_cast<util::PolymorphicArray*>(a_pObject)->~PolymorphicArray();
}

void PolymorphicArrayClass::construct( void* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize ) const
{
    byte* pChunk = reinterpret_cast<byte*>(a_pChunk);
    while(a_uiCount--)
    {
        new (reinterpret_cast<util::PolymorphicArray*>(pChunk)) util::PolymorphicArray();
        pChunk += a_uiChunkSectionSize;
    }
}

void PolymorphicArrayClass::destroy( void* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize ) const
{
    byte* pChunk = reinterpret_cast<byte*>(a_pChunk);
    while(a_uiCount--)
    {
        (reinterpret_cast<util::PolymorphicArray*>(pChunk))->util::PolymorphicArray::~PolymorphicArray();
        pChunk += a_uiChunkSectionSize;
    }
}

void PolymorphicArrayClass::deleteInstance( void* a_pObject ) const
{
    static_cast<util::PolymorphicArray*>(a_pObject)->~PolymorphicArray();
    phantom::extension::allocator<util::PolymorphicArray>::deallocate(reinterpret_cast<util::PolymorphicArray*>(a_pObject));
}

phantom::uint PolymorphicArrayClass::getVirtualMethodCount( uint a_uiIndex ) const
{
    return static_cast<reflection::Class*>(classOf<Object>())->getVirtualMethodCount(a_uiIndex);
}

void PolymorphicArrayClass::safeDeleteInstance( void* a_pObject ) const
{
    phantom::as<util::PolymorphicArray*>(a_pObject)->~PolymorphicArray();
    phantom::extension::allocator<util::PolymorphicArray>::deallocate(reinterpret_cast<util::PolymorphicArray*>(a_pObject));
}

void PolymorphicArrayClass::serialize( void const* a_pInstance, byte*& a_pOutBuffer, uint a_uiSerializationMask, data_guid_base const* a_pGuidBase ) const
{
    phantom::extension::serializer<util::PolymorphicArray>::serialize(static_cast<util::PolymorphicArray const*>(a_pInstance), a_pOutBuffer, a_uiSerializationMask, a_pGuidBase);
}

void PolymorphicArrayClass::serialize( void const* a_pInstance, const property_branch& a_OutBranch, uint a_uiSerializationMask, data_guid_base const* a_pGuidBase ) const
{
    phantom::extension::serializer<util::PolymorphicArray>::serialize(static_cast<util::PolymorphicArray const*>(a_pInstance), a_OutBranch, a_uiSerializationMask, a_pGuidBase);
}

void PolymorphicArrayClass::serialize( void const* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer, uint a_uiSerializationMask, data_guid_base const* a_pGuidBase ) const
{
    phantom::extension::serializer<util::PolymorphicArray>::serialize(static_cast<util::PolymorphicArray const*>(a_pInstance), a_uiCount, a_uiChunkSectionSize,a_pOutBuffer, a_uiSerializationMask, a_pGuidBase);
}

void PolymorphicArrayClass::serialize( void const* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, const property_branch& a_OutBranch, uint a_uiSerializationMask, data_guid_base const* a_pGuidBase ) const
{
    phantom::extension::serializer<util::PolymorphicArray>::serialize(static_cast<util::PolymorphicArray const*>(a_pInstance), a_uiCount, a_uiChunkSectionSize,a_OutBranch, a_uiSerializationMask, a_pGuidBase);
}

void PolymorphicArrayClass::deserialize( void* a_pInstance, byte const*& a_pInBuffer, uint a_uiSerializationMask, data_guid_base const* a_pGuidBase ) const
{
    phantom::extension::serializer<util::PolymorphicArray>::deserialize(static_cast<util::PolymorphicArray*>(a_pInstance), a_pInBuffer, a_uiSerializationMask, a_pGuidBase);
}

void PolymorphicArrayClass::deserialize( void* a_pInstance, const property_branch& a_InBranch, uint a_uiSerializationMask, data_guid_base const* a_pGuidBase ) const
{
    phantom::extension::serializer<util::PolymorphicArray>::deserialize(static_cast<util::PolymorphicArray*>(a_pInstance), a_InBranch, a_uiSerializationMask, a_pGuidBase);
}

void PolymorphicArrayClass::deserialize( void* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer, uint a_uiSerializationMask, data_guid_base const* a_pGuidBase ) const
{
    phantom::extension::serializer<util::PolymorphicArray>::deserialize(static_cast<util::PolymorphicArray*>(a_pInstance), a_uiCount, a_uiChunkSectionSize,a_pInBuffer, a_uiSerializationMask, a_pGuidBase);
}

void PolymorphicArrayClass::deserialize( void* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, const property_branch& a_InBranch, uint a_uiSerializationMask, data_guid_base const* a_pGuidBase ) const
{
    phantom::extension::serializer<util::PolymorphicArray>::deserialize(static_cast<util::PolymorphicArray*>(a_pInstance), a_uiCount, a_uiChunkSectionSize,a_InBranch, a_uiSerializationMask, a_pGuidBase);
}

void PolymorphicArrayClass::serializeLayout( void const* a_pInstance, byte*& a_pBuffer, uint a_uiSerializationMask, data_guid_base const* a_pGuidBase ) const
{
    phantom::extension::serializer<util::PolymorphicArray>::serializeLayout(static_cast<util::PolymorphicArray const*>(a_pInstance), a_pBuffer, a_uiSerializationMask, a_pGuidBase);
}

void PolymorphicArrayClass::serializeLayout( void const* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pBuffer, uint a_uiSerializationMask, data_guid_base const* a_pGuidBase ) const
{
    phantom::extension::serializer<util::PolymorphicArray>::serializeLayout(static_cast<util::PolymorphicArray const*>(a_pInstance), a_uiCount, a_uiChunkSectionSize, a_pBuffer, a_uiSerializationMask, a_pGuidBase);
}

void PolymorphicArrayClass::serializeLayout( void const* a_pInstance, const property_branch& a_Branch, uint a_uiSerializationMask, data_guid_base const* a_pGuidBase ) const
{
    phantom::extension::serializer<util::PolymorphicArray>::serializeLayout(static_cast<util::PolymorphicArray const*>(a_pInstance), a_Branch, a_uiSerializationMask, a_pGuidBase);
}

void PolymorphicArrayClass::serializeLayout( void const* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, const property_branch& a_Branch, uint a_uiSerializationMask, data_guid_base const* a_pGuidBase ) const
{
    phantom::extension::serializer<util::PolymorphicArray>::serializeLayout(static_cast<util::PolymorphicArray const*>(a_pInstance), a_uiCount, a_uiChunkSectionSize, a_Branch, a_uiSerializationMask, a_pGuidBase);
}

void PolymorphicArrayClass::deserializeLayout( void* a_pInstance, byte const*& a_pBuffer, uint a_uiSerializationMask, data_guid_base const* a_pGuidBase ) const
{
    phantom::extension::serializer<util::PolymorphicArray>::deserializeLayout(static_cast<util::PolymorphicArray*>(a_pInstance), a_pBuffer, a_uiSerializationMask, a_pGuidBase);
}

void PolymorphicArrayClass::deserializeLayout( void* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pBuffer, uint a_uiSerializationMask, data_guid_base const* a_pGuidBase ) const
{
    phantom::extension::serializer<util::PolymorphicArray>::deserializeLayout(static_cast<util::PolymorphicArray*>(a_pInstance), a_uiCount, a_uiChunkSectionSize, a_pBuffer, a_uiSerializationMask, a_pGuidBase);
}

void PolymorphicArrayClass::deserializeLayout( void* a_pInstance, const property_branch& a_Branch, uint a_uiSerializationMask, data_guid_base const* a_pGuidBase ) const
{
    phantom::extension::serializer<util::PolymorphicArray>::deserializeLayout(static_cast<util::PolymorphicArray*>(a_pInstance), a_Branch, a_uiSerializationMask, a_pGuidBase);
}

void PolymorphicArrayClass::deserializeLayout( void* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, const property_branch& a_Branch, uint a_uiSerializationMask, data_guid_base const* a_pGuidBase ) const
{
    phantom::extension::serializer<util::PolymorphicArray>::deserializeLayout(static_cast<util::PolymorphicArray*>(a_pInstance), a_uiCount, a_uiChunkSectionSize, a_Branch, a_uiSerializationMask, a_pGuidBase);
}

serialization::Bundle* PolymorphicArrayClass::createBundle( serialization::BundleNode* a_pOwnerNode ) const
{
    return o_new(serialization::native::TBundle<util::PolymorphicArray>)(a_pOwnerNode);
}

void PolymorphicArrayClass::destroyBundle( serialization::Bundle* a_pBundle ) const
{
    o_delete(serialization::native::TBundle<util::PolymorphicArray>) a_pBundle;
}

void*   PolymorphicArrayClass::allocate() const
{
    return phantom::extension::allocator<util::PolymorphicArray>::allocate();
}
void    PolymorphicArrayClass::deallocate(void* a_pInstance) const
{
    phantom::extension::allocator<util::PolymorphicArray>::deallocate(static_cast<util::PolymorphicArray*>(a_pInstance));
}
void*   PolymorphicArrayClass::allocate(size_t a_uiCount) const
{
    return phantom::extension::allocator<util::PolymorphicArray>::allocate(a_uiCount);
}
void    PolymorphicArrayClass::deallocate(void* a_pChunk, size_t a_uiCount) const
{
    phantom::extension::allocator<util::PolymorphicArray>::deallocate(static_cast<util::PolymorphicArray*>(a_pChunk), a_uiCount);
}

Type* PolymorphicArrayClass::createConstType() const
{
    return o_new(native::TConstType<PolymorphicArrayClass>)(const_cast<PolymorphicArrayClass*>(this));
}

void PolymorphicArrayClass::remember( void const* a_pInstance, byte*& a_pOutBuffer ) const
{
    phantom::extension::resetter<util::PolymorphicArray>::remember((util::PolymorphicArray const*)a_pInstance, a_pOutBuffer);
}

void PolymorphicArrayClass::remember( void const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer ) const
{
    phantom::extension::resetter<util::PolymorphicArray>::remember((util::PolymorphicArray const*)a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pOutBuffer);
}

void PolymorphicArrayClass::reset( void* a_pInstance, byte const*& a_pInBuffer ) const
{
    phantom::extension::resetter<util::PolymorphicArray>::reset((util::PolymorphicArray*)a_pInstance, a_pInBuffer);
}

void PolymorphicArrayClass::reset( void* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer ) const
{
    phantom::extension::resetter<util::PolymorphicArray>::reset((util::PolymorphicArray*)a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pInBuffer);
}

o_cpp_end

