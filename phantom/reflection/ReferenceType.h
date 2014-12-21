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

#ifndef o_phantom_reflection_ReferenceType_h__
#define o_phantom_reflection_ReferenceType_h__

/* ****************** Includes ******************* */

/* **************** Declarations ***************** */

/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export ReferenceType : public Type
{
    o_type;

    o_declare_meta_type(ReferenceType);

public:
    friend class Type;

protected:
    ReferenceType(Type* a_pType);

    virtual ReferenceType* asReferenceType() const { return (ReferenceType*)this; }

public:
    o_destructor ~ReferenceType(void) ;

    virtual void*   allocate() const;
    virtual void    deallocate(void* a_pInstance) const;
    virtual void*   allocate(size_t a_uiCount) const;
    virtual void    deallocate(void* a_pChunk, size_t a_uiCount) const;

    virtual void    safeConstruct(void* a_pBuffer) const;
    virtual void    safeConstruct(void* a_pBuffer, size_t a_uiCount, size_t a_uiChunkSectionSize) const;

    virtual void    construct(void* a_pBuffer) const;
    virtual void    destroy(void* a_pBuffer) const;
    virtual void    construct(void* a_pBuffer, size_t a_uiCount, size_t a_uiChunkSectionSize) const;
    virtual void    destroy(void* a_pBuffer, size_t a_uiCount, size_t a_uiChunkSectionSize) const;

    virtual void    interpolate(void* a_src_start, void* a_src_end, real a_fPercent, void* a_dest, uint mode) const 
    {
        m_pReferencedType->interpolate(a_src_start, a_src_end, a_fPercent, a_dest, mode);
    }

    Type*               getReferencedType() const { return m_pReferencedType; }

    virtual boolean     isConvertibleTo(Type* a_pType) const;
    virtual boolean     isImplicitlyConvertibleTo( Type* a_pType ) const;
    virtual void        convertValueTo(Type* a_pDestType, void* a_pDestValue, const void* a_pSrcValue) const;
    
    virtual void        valueFromString(const string& a_str, void* dest) const
    {
        m_pReferencedType->valueFromString(a_str, dest);
    }

    virtual void        valueToString(string& a_str, const void* src) const
    {
        m_pReferencedType->valueToString(a_str, src);
    }

    virtual void        serialize(void const* a_pInstance, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const
    {
        o_exception(exception::reflection_runtime_exception, "references cannot be serialized");
    }

    virtual void        deserialize(void* a_pInstance, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const
    {
        o_exception(exception::reflection_runtime_exception, "references cannot be serialized");
    }

    virtual void        serialize(void const* a_pInstance, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const
    {
        o_exception(exception::reflection_runtime_exception, "references cannot be serialized");
    }

    virtual void        deserialize(void* a_pInstance, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const
    {
        o_exception(exception::reflection_runtime_exception, "references cannot be serialized");
    }

    virtual void        serialize(void const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const
    {
        o_exception(exception::reflection_runtime_exception, "references cannot be serialized");
    }

    virtual void        deserialize(void* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const
    {
        o_exception(exception::reflection_runtime_exception, "references cannot be serialized");
    }

    virtual void        serialize(void const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const
    {
        o_exception(exception::reflection_runtime_exception, "references cannot be serialized");
    }

    virtual void        deserialize(void* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const
    {
        o_exception(exception::reflection_runtime_exception, "references cannot be serialized");
    }

    virtual void        remember(void const* a_pInstance, byte*& a_pOutBuffer) const 
    {
        o_exception(exception::reflection_runtime_exception, "references cannot be reset");
    }
    virtual void        remember(void const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pBuffer) const 
    {
        o_exception(exception::reflection_runtime_exception, "references cannot be reset");
    }
    virtual void        reset(void* a_pInstance, byte const*& a_pInBuffer) const 
    {
        o_exception(exception::reflection_runtime_exception, "references cannot be reset");
    }
    virtual void        reset(void* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pBuffer) const
    {
        o_exception(exception::reflection_runtime_exception, "references cannot be reset");
    }

    virtual Type*   removeReference() const { return m_pReferencedType; }

    virtual string  getDecoratedName() const { return m_pReferencedType->getDecoratedName()+'&'; }
    virtual string  getQualifiedDecoratedName() const { return m_pReferencedType->getQualifiedDecoratedName()+'&'; }

    virtual bool    isCopyable() const { return true; }

    virtual void    qualifiersToString( string& out ) const;

    virtual bool    templatePartialMatch(Type* a_pType, size_t& a_Score, map<TemplateParameter*, LanguageElement*>& a_DeducedConstants) const;

protected:
    virtual DataPointerType* createDataPointerType() const { return nullptr; } // cannot create reference pointers

protected:
    virtual void referencedElementRemoved(LanguageElement* a_pElement);

protected:
    Type*        m_pReferencedType;
};

o_namespace_end(phantom, reflection)



#endif