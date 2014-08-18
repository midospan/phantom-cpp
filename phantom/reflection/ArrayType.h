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

#ifndef o_phantom_reflection_ArrayType_h__
#define o_phantom_reflection_ArrayType_h__
// #pragma message("Including "__FILE__)


/* ****************** Includes ******************* */
#include "Type.h"
/* **************** Declarations ***************** */

/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export ArrayType : public Type
{
    o_declare_meta_type(ArrayType);

public:
    friend class Type;

protected:
    ArrayType(Type* a_pElementType, size_t a_uiCount);

public:
    o_destructor ~ArrayType(void)     {}

    virtual boolean     isPOD() const { return m_pElementType->isPOD(); }
    virtual boolean     isArrayType() const { return true; }
    virtual ArrayType*  asArrayType() const { return (ArrayType*)this; }
    size_t              getElementCount() const { return m_uiCount; }

    virtual void        safeConstruct(void* a_pBuffer) const 
    {
        *reinterpret_cast<void**>(a_pBuffer) = NULL;
    }
    virtual void        safeConstruct(void* a_pBuffer, size_t a_uiCount, size_t a_uiChunkSectionSize) const 
    {
        memset(a_pBuffer, 0, a_uiCount*a_uiChunkSectionSize*m_uiSize);
    }

    virtual void        construct(void* a_pBuffer) const 
    {
        // trivial
    }
    virtual void        destroy(void* a_pBuffer) const 
    {
        // trivial
    }
    virtual void        construct(void* a_pBuffer, size_t a_uiCount, size_t a_uiChunkSectionSize) const 
    {
        // trivial
    }
    virtual void        destroy(void* a_pBuffer, size_t a_uiCount, size_t a_uiChunkSectionSize) const 
    {
        // trivial
    }
    
    virtual void    interpolate(void* a_src_start, void* a_src_end, real a_fPercent, void* a_dest, uint mode) const 
    {
        o_exception(exception::unsupported_member_function_exception, "interpolation is not supported for any array type");
    }


    virtual void*   allocate() const
    {
        return m_pElementType->allocate(m_uiCount);
    }
    virtual void    deallocate(void* a_pInstance) const
    {
        m_pElementType->deallocate(a_pInstance, m_uiCount);
    }
    virtual void*   allocate(size_t a_uiCount) const
    {
        return m_pElementType->allocate(m_uiCount*a_uiCount);
    }
    virtual void    deallocate(void* a_pChunk, size_t a_uiCount) const
    {
        m_pElementType->deallocate(a_pChunk, m_uiCount*a_uiCount);
    }

    Type*               getElementType() const { return m_pElementType; }

    void*               getElementAddress(void* a_pArrayAddress, size_t a_uiIndex) const 
    { 
        return ((byte*)a_pArrayAddress)+(a_uiIndex*m_pElementType->getSize()); 
    }

    const void*         getElementAddress(const void* a_pArrayAddress, size_t a_uiIndex) const 
    { 
        return ((const byte*)a_pArrayAddress)+(a_uiIndex*m_pElementType->getSize()); 
    }

    void                getElementValue(const void* a_pArrayAddress, size_t a_uiIndex, void* a_pDest) const 
    { 
        return m_pElementType->copy(a_pDest, getElementAddress(a_pArrayAddress, a_uiIndex)); 
    }

    void                setElementValue(void* a_pArrayAddress, size_t a_uiIndex, const void* a_pSrc) const 
    { 
        return m_pElementType->copy(getElementAddress(a_pArrayAddress, a_uiIndex), a_pSrc); 
    }
    
    virtual boolean     isConvertibleTo(Type* a_pType) const;

    virtual boolean     isImplicitlyConvertibleTo( Type* a_pType ) const;

    virtual void        convertValueTo(Type* a_pDestType, void* a_pDestValue, void const* a_pSrcValue) const;

    virtual void        valueFromString(const string& a_str, void* dest) const
    {
        *reinterpret_cast<void**>(dest) = ::phantom::lexical_cast<void*>(a_str);
    }

    virtual void        valueToString(string& a_str, const void* src) const
    {
        a_str += ::phantom::lexical_cast<string>(*((void**)src));
    }

    virtual void        serialize(void const* a_pInstance, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const
    {
        m_pElementType->serialize(a_pInstance, m_uiCount, m_uiSize/m_uiCount, a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
    }

    virtual void        deserialize(void* a_pInstance, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const
    {
        m_pElementType->deserialize(a_pInstance, m_uiCount, m_uiSize/m_uiCount, a_pInBuffer, a_uiSerializationMask, a_pDataBase);
    }

    virtual void        serialize(void const* a_pInstance, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const;

    virtual void        deserialize(void* a_pInstance, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const;

    virtual void        serialize(void const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const
    {
        byte const* pChunk = reinterpret_cast<byte const*>(a_pChunk);
        while(a_uiCount--)
        {
            m_pElementType->serialize(pChunk, m_uiCount, m_uiSize/m_uiCount, a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
            pChunk += a_uiChunkSectionSize;
        }
    }

    virtual void        deserialize(void* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const
    {
        byte* pChunk = reinterpret_cast<byte*>(a_pChunk);
        while(a_uiCount--)
        {
            m_pElementType->deserialize(pChunk, m_uiCount, m_uiSize/m_uiCount, a_pInBuffer, a_uiSerializationMask, a_pDataBase);
            pChunk += a_uiChunkSectionSize;
        }
    }

    virtual void        serialize(void const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const
    {
        byte const* pChunk = reinterpret_cast<byte const*>(a_pChunk);
        while(a_uiCount--)
        {
            m_pElementType->serialize(pChunk, m_uiCount, m_uiSize/m_uiCount, a_OutBranch, a_uiSerializationMask, a_pDataBase);
            pChunk += a_uiChunkSectionSize;
        }
    }

    virtual void        deserialize(void* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const
    {
        byte* pChunk = reinterpret_cast<byte*>(a_pChunk);
        while(a_uiCount--)
        {
            m_pElementType->deserialize(pChunk, m_uiCount, m_uiSize/m_uiCount, a_InBranch, a_uiSerializationMask, a_pDataBase);
            pChunk += a_uiChunkSectionSize;
        }
    }

    virtual void        remember(void const* a_pInstance, byte*& a_pOutBuffer) const 
    {
        m_pElementType->remember(a_pInstance, m_uiCount, m_uiSize/m_uiCount, a_pOutBuffer);
    }
    virtual void        remember(void const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer) const 
    {
        byte const* pChunk = reinterpret_cast<byte const*>(a_pChunk);
        while(a_uiCount--)
        {
            m_pElementType->remember(pChunk, m_uiCount, m_uiSize/m_uiCount, a_pOutBuffer);
            pChunk += a_uiChunkSectionSize;
        }
    }
    virtual void        reset(void* a_pInstance, byte const*& a_pInBuffer) const 
    {
        m_pElementType->reset(a_pInstance, m_uiCount, m_uiSize/m_uiCount, a_pInBuffer);
    }
    virtual void        reset(void* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pBuffer) const
    {
        byte* pChunk = reinterpret_cast<byte*>(a_pChunk);
        while(a_uiCount--)
        {
            m_pElementType->reset(pChunk, m_uiCount, m_uiSize/m_uiCount, a_pBuffer);
            pChunk += a_uiChunkSectionSize;
        }
    }


    virtual Type*                   removeArray() const { return m_pElementType; }

    virtual string          getDecoratedName() const { return m_pElementType->getDecoratedName()+'['+phantom::lexical_cast<string>(m_uiCount)+']'; }
    virtual string          getQualifiedDecoratedName() const { return m_pElementType->getQualifiedDecoratedName()+'['+phantom::lexical_cast<string>(m_uiCount)+']'; }

    virtual void            copy(void* a_pDest, void const* a_pSrc) const;
    virtual bool            isCopyable() const { return m_pElementType->isCopyable(); }

    virtual Type*           asPOD() const { return m_pElementType->asPOD() ? (Type*)this : nullptr; }

    virtual Expression*     solveOperator(const string& a_strOperator, const vector<Expression*>& a_Expressions, bitfield a_Modifiers) const;

protected:
    virtual void referencedElementRemoved(LanguageElement* a_pElement);
protected:
    Type*       m_pElementType;
    size_t      m_uiCount;
};

o_namespace_end(phantom, reflection)



#endif