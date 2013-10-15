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

#ifndef o_phantom_reflection_PolymorphicArrayClass_h__
#define o_phantom_reflection_PolymorphicArrayClass_h__




/* ****************** Includes ******************* */
#include <phantom/reflection/Class.h>
/* *********************************************** */
/* The *.classdef.h file must be the last #include */
#include "PolymorphicArrayClass.classdef.h"
/* ************* Class Declarations ************** */
o_declare(class, phantom, reflection, Namespace)
/* *********************************************** */

o_h_begin


class o_export PolymorphicArrayClass : public Class
{
public:
    o_friend(class, phantom, Phantom)
    o_friend(class, phantom, reflection, Namespace)

    Reflection_____________________________________________________________________________________
    _____________________________________________________________________________________Reflection

public:
    boolean         restore( uint a_uiSerializationFlag, uint a_uiPass) { return true; }

    virtual guid    getId() const { return 1234;}
    virtual boolean    isPolymorphicArrayClass() const { return true; }
    void            setContentType(Class* a_pType)    { m_pContentType = a_pType;    }
    Class*            getContentType(void) const        { return m_pContentType;}
    void            setup();

    virtual ERelation   getRelationWith(Type* a_pType) const;
    virtual Type*       createConstType() const;

    virtual boolean    accepts(Type* a_pType) const;

    virtual void*   allocate() const;
    virtual void    deallocate(void* a_pInstance) const;
    virtual void*   allocate(size_t a_uiCount) const;
    virtual void    deallocate(void* a_pChunk, size_t a_uiCount) const;

    void            construct(void* a_pObject) const;
    void            destroy(void* a_pObject) const;
    void            construct( void* a_pAddress, size_t a_uiCount, size_t a_uiChunkSectionSize ) const;
    void            destroy( void* a_pAddress, size_t a_uiCount, size_t a_uiChunkSectionSize ) const;

    virtual void    serialize(void const* a_pInstance, byte*& a_pOutBuffer, uint a_uiSerializationMask, data_guid_base const* a_pGuidBase) const;
    virtual void    deserialize(void* a_pInstance, byte const*& a_pInBuffer, uint a_uiSerializationMask, data_guid_base const* a_pGuidBase) const;
    virtual void    serialize(void const* a_pInstance, const property_branch& a_OutBranch, uint a_uiSerializationMask, data_guid_base const* a_pGuidBase) const;
    virtual void    deserialize(void* a_pInstance, const property_branch& a_InBranch, uint a_uiSerializationMask, data_guid_base const* a_pGuidBase) const;
    virtual void    serialize(void const* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer, uint a_uiSerializationMask, data_guid_base const* a_pGuidBase) const;
    virtual void    deserialize(void* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer, uint a_uiSerializationMask, data_guid_base const* a_pGuidBase) const;
    virtual void    serialize(void const* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, const property_branch& a_OutBranch, uint a_uiSerializationMask, data_guid_base const* a_pGuidBase) const;
    virtual void    deserialize(void* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, const property_branch& a_InBranch, uint a_uiSerializationMask, data_guid_base const* a_pGuidBase) const;
    virtual void    serializeLayout(void const* a_pInstance, byte*& a_pBuffer, uint a_uiSerializationMask, data_guid_base const* a_pGuidBase) const;
    virtual void    deserializeLayout(void* a_pInstance, byte const*& a_pBuffer, uint a_uiSerializationMask, data_guid_base const* a_pGuidBase) const;
    virtual void    serializeLayout(void const* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pBuffer, uint a_uiSerializationMask, data_guid_base const* a_pGuidBase) const;
    virtual void    deserializeLayout(void* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pBuffer, uint a_uiSerializationMask, data_guid_base const* a_pGuidBase) const;
    virtual void    serializeLayout(void const* a_pInstance, const property_branch& a_Branch, uint a_uiSerializationMask, data_guid_base const* a_pGuidBase) const;
    virtual void    deserializeLayout(void* a_pInstance, const property_branch& a_Branch, uint a_uiSerializationMask, data_guid_base const* a_pGuidBase) const;
    virtual void    serializeLayout(void const* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, const property_branch& a_Branch, uint a_uiSerializationMask, data_guid_base const* a_pGuidBase) const;
    virtual void    deserializeLayout(void* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, const property_branch& a_Branch, uint a_uiSerializationMask, data_guid_base const* a_pGuidBase) const;


    virtual void        remember(void const* a_pInstance, byte*& a_pOutBuffer) const;
    virtual void        reset(void* a_pInstance, byte const*& a_pInBuffer) const;
    virtual void        remember(void const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer) const;
    virtual void        reset(void* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer) const;

    virtual 
    serialization::Bundle*  createBundle(serialization::BundleNode* a_pOwnerNode) const;
    virtual void            destroyBundle(serialization::Bundle* a_pBundle) const;



    virtual void*   newInstance() const;
    virtual void*   newInstance(Constructor* a_pConstructor, void** a_pConstructorParam) const;
    virtual void*   newInstance(Constructor* a_pConstructor, argument::list* a_pConstructorParam) const;

    virtual void    deleteInstance(void* a_pObject) const;
    virtual void    safeDeleteInstance(void* a_pObject) const;

    virtual uint    getVirtualMethodCount(uint a_uiIndex) const;

protected:
    PolymorphicArrayClass(void);
    PolymorphicArrayClass(Class* a_pArrayContentType, bitfield a_bfModifiers = bitfield());

protected:
    Class*        m_pContentType;

};

o_h_end


#else // o_phantom_reflection_PolymorphicArrayClass_h__
#include "PolymorphicArrayClass.classdef.h"
#endif
