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

#ifndef o_phantom_reflection_DataPointerType_h__
#define o_phantom_reflection_DataPointerType_h__
// #pragma message("Including "__FILE__)


/* ****************** Includes ******************* */

/* *********************************************** */
/* The *.classdef.h file must be the last #include */
#include "DataPointerType.classdef.h"
/* **************** Declarations ***************** */

/* *********************************************** */

o_h_begin

class o_export DataPointerType : public PointerType
{
public:
    Reflection_____________________________________________________________________________________
    _____________________________________________________________________________________Reflection
public:
    friend class Type;

protected:
    DataPointerType(Type* a_pType);

public:
    o_destructor ~DataPointerType(void);

    virtual void*   allocate() const
    {
        return o_allocate(void*);
    }
    virtual void    deallocate(void* a_pInstance) const
    {
        o_deallocate(static_cast<void**>(a_pInstance), void*);
    }
    virtual void*   allocate(size_t a_uiCount) const
    {
        return o_allocate_n(a_uiCount, void*);
    }
    virtual void    deallocate(void* a_pChunk, size_t a_uiCount) const
    {
        o_deallocate_n(static_cast<void**>(a_pChunk), a_uiCount, void*);
    }

    Type*               getPointedType() const { return m_pPointedType; }


    virtual DataPointerType*    asDataPointerType() const { return const_cast<DataPointerType*>(this); }

    virtual boolean     isConvertibleTo(Type* a_pType) const;
    virtual void        convertValueTo(Type* a_pDestType, void* a_pDestValue, void const* a_pSrcValue) const;

    virtual void        copy(void* a_pDest, void const* a_pSrc) const 
    {
        *static_cast<void**>(a_pDest) = *static_cast<void* const*>(a_pSrc);
    }
    
    virtual void        valueFromString(const string& a_str, void* dest) const
    {
        *reinterpret_cast<void**>(dest) = ::phantom::lexical_cast<void*>(a_str);
    }

    virtual void        valueToString(string& a_str, const void* src) const
    {
        a_str += ::phantom::lexical_cast<string>(*((void**)(src)));;
    }

    virtual void        serialize(void const* a_pInstance, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const;

    virtual void        deserialize(void* a_pInstance, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const;

    virtual void        serialize(void const* a_pInstance, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const;

    virtual void        deserialize(void* a_pInstance, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const;

    virtual void        serialize(void const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const;

    virtual void        deserialize(void* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const;

    virtual void        serialize(void const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const;

    virtual void        deserialize(void* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const;

    virtual boolean     isImplicitlyConvertibleTo(Type* a_pType) const;
    virtual boolean     hasTrivialCastTo(Type* a_pType) const;

    virtual uint        getDataPointerLevel() const { return m_pPointedType->getDataPointerLevel() + 1; }

    virtual void        remember(void const* a_pInstance, byte*& a_pOutBuffer) const
    {
        phantom::extension::resetter<void*>::remember((void* const*)a_pInstance, a_pOutBuffer);
    }

    virtual void        reset(void* a_pInstance, byte const*& a_pInBuffer) const
    {
        phantom::extension::resetter<void*>::reset((void**)a_pInstance, a_pInBuffer);
    }

    virtual void        remember(void const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer) const
    {
        phantom::extension::resetter<void*>::remember((void* const*)a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pOutBuffer);
    }

    virtual void        reset(void* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer) const
    {
        phantom::extension::resetter<void*>::reset((void**)a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pInBuffer);
    }

    virtual Type*                   removePointer() const { return m_pPointedType; }

    Type*                           createConstType() const;

    virtual string          getDecoratedName() const { return m_pPointedType->getDecoratedName()+'*'; }
    virtual string          getQualifiedDecoratedName() const { return m_pPointedType->getQualifiedDecoratedName()+'*'; }

protected:
    Type*        m_pPointedType;
};

o_h_end


#else // DataPointerType_h__
#include "DataPointerType.classdef.h"
#endif