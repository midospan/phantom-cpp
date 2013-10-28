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

#ifndef o_phantom_reflection_Type_h__
#define o_phantom_reflection_Type_h__

/* ****************** Includes ******************* */

/* *********************************************** */
/* The *.classdef.h file must be the last #include */
#include "Type.classdef.h"
/* **************** Declarations ***************** */
o_declare(class, phantom, reflection, Namespace)
o_declare(class, phantom, reflection, Constructor)
o_declare(class, phantom, reflection, PointerType)
/* *********************************************** */

o_h_begin

class o_export Type : public TemplateElement
{
    o_friend(class, phantom, Object)
    o_friend(class, phantom, reflection, Namespace)

    reflection_____________________________________________________________________________________
    _____________________________________________________________________________________reflection

public:
    typedef vector<Type*> type_container;
    typedef map<string, Type*> nested_typedef_map;
    enum ERelation
    {
        eRelation_None = 0,
        eRelation_Equal,
        eRelation_Child ,
        eRelation_Parent ,
        eRelation_Compatible ,
        eRelation_GenericContentChild,
        eRelation_GenericContentParent,
    };

    class o_export alignment
    {
    public:
        class o_export computer
        {
        public:
            computer(size_t a_MaxAlignment = 0)
                : m_MaxAlignment(a_MaxAlignment)
                , m_Result(0) {}
            size_t  push(Type* a_pType);
            size_t  compute();
            o_forceinline size_t    maxAlignment() const { return m_MaxAlignment; }

            o_forceinline void        setMaxAlignement(size_t max_align)
            {
                m_MaxAlignment = max_align;
            }

        private:
            size_t    m_MaxAlignment;
            size_t    m_Result;
        };
    };

    class o_export aligner
    {
    public:
        aligner(byte* a_pStart)
            : m_pStartAddress(a_pStart)
            , m_MaxAlignment(1)
            , m_WrittenBytes(0)
        {
        }
        void skip(Type* a_pType);
        void construct(Type* a_pType);
        void safeConstruct(Type* a_pType);
        void destroy(Type* a_pType);
        void push(Type* a_pType, byte* a_pValueBytes);
        o_forceinline byte*    address() const { return m_pStartAddress+m_WrittenBytes; }
        byte*    terminate();

    protected:
        byte*    m_pStartAddress;
        size_t    m_MaxAlignment;
        size_t    m_WrittenBytes;
    };

    Type(const string& a_strName, bitfield a_bfModifiers = bitfield());
    Type(const string& a_strName, ushort a_uiSize, ushort a_uiAlignment, bitfield a_bfModifiers = bitfield());
    Type(const string& a_strName, ushort a_uiSize, ushort a_uiAlignment, uint a_uiGuid, bitfield a_bfModifiers = bitfield());
    ~Type();

    o_forceinline o_initialize() {m_uiBuildOrder = NextBuildOrderValue();}
    o_forceinline o_terminate()  {}

    o_forceinline ushort    getSize() const { return m_uiSize; }
    o_forceinline ushort    getAlignment() const { return m_uiAlignment; }
    o_forceinline ushort    getSerializedSize() const { return m_uiSerializedSize; }
    o_forceinline ushort    getResetSize() const { return m_uiResetSize; }
    o_forceinline size_t    getBuildOrder() const { return m_uiBuildOrder; }
    virtual boolean         isSerializable() const { return true; }
    virtual boolean         isPolymorphic() const { return false; }
    virtual boolean         isKindOf(Type* a_pType) const { return this == a_pType; }
    virtual Type*           asType() const { return const_cast<Type*>(this); }
    virtual Type*           removeConst() const { return const_cast<Type*>(this); }
    virtual Type*           removeReference() const { return const_cast<Type*>(this); }
    virtual Type*           removePointer() const { return const_cast<Type*>(this); }

    virtual void*           cast(Type* a_pTargetType, void* a_pSrc) const { return a_pTargetType == this ? a_pSrc : NULL; }

    /// Allocation
    virtual void*           allocate() const = 0;
    virtual void*           allocate(size_t a_uiCount) const = 0;
    virtual void            deallocate(void* a_pAddress) const = 0;
    virtual void            deallocate(void* a_pAddress, size_t a_uiCount) const = 0;

    /// Construction
    virtual void            construct(void* a_pBuffer) const = 0;
    virtual void            construct(void* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize ) const = 0;
    virtual void            safeConstruct(void* a_pBuffer) const  { construct(a_pBuffer); }
    virtual void            safeConstruct(void* a_pBuffer, size_t a_uiCount, size_t a_uiChunkSectionSize) const { construct(a_pBuffer, a_uiCount, a_uiChunkSectionSize); }
    virtual void            destroy(void* a_pBuffer) const  = 0;
    virtual void            destroy(void* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize ) const = 0;

    /// Build (Construction by default (+ installation for classes))
    virtual void            build(void* a_pBuffer) const { construct(a_pBuffer); }
    virtual void            build(void* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize ) const { construct(a_pChunk, a_uiCount, a_uiChunkSectionSize); }
    virtual void            unbuild(void* a_pBuffer) const { destroy(a_pBuffer); }
    virtual void            unbuild(void* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize ) const { destroy(a_pChunk, a_uiCount, a_uiChunkSectionSize); }

    /// Build (Construction by default (+ installation + initialization for classes))
    virtual void            setup(void* a_pBuffer) const { construct(a_pBuffer); }
    virtual void            safeSetup(void* a_pBuffer) const  { safeConstruct(a_pBuffer); }
    virtual void            setup(void* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize ) const { construct(a_pChunk, a_uiCount, a_uiChunkSectionSize); }
    virtual void            teardown(void* a_pBuffer) const { destroy(a_pBuffer); }
    virtual void            teardown(void* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize ) const { destroy(a_pChunk, a_uiCount, a_uiChunkSectionSize); }

    /// Serialization
    virtual void            serialize(void const* a_pInstance, byte*& a_pBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const = 0;
    virtual void            serialize(void const* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const = 0;
    virtual void            serialize(void const* a_pInstance, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const = 0;
    virtual void            serialize(void const* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const = 0;
    virtual void            serializeLayout(void const* a_pInstance, byte*& a_pBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { serialize(a_pInstance, a_pBuffer, a_uiSerializationMask, a_pDataBase); }
    virtual void            serializeLayout(void const* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { serialize(a_pInstance, a_uiCount, a_uiChunkSectionSize, a_pBuffer, a_uiSerializationMask, a_pDataBase); }
    virtual void            serializeLayout(void const* a_pInstance, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { serialize(a_pInstance, a_OutBranch, a_uiSerializationMask, a_pDataBase); }
    virtual void            serializeLayout(void const* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { serialize(a_pInstance, a_uiCount, a_uiChunkSectionSize, a_OutBranch, a_uiSerializationMask, a_pDataBase); }
    virtual void            deserialize(void* a_pInstance, byte const*& a_pBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const = 0;
    virtual void            deserialize(void* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const = 0;
    virtual void            deserialize(void* a_pInstance, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const = 0;
    virtual void            deserialize(void* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const = 0;
    virtual void            deserializeLayout(void* a_pInstance, byte const*& a_pBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { deserialize(a_pInstance, a_pBuffer, a_uiSerializationMask, a_pDataBase); }
    virtual void            deserializeLayout(void* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { deserialize(a_pInstance, a_uiCount, a_uiChunkSectionSize, a_pBuffer, a_uiSerializationMask, a_pDataBase); }
    virtual void            deserializeLayout(void* a_pInstance, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { deserialize(a_pInstance, a_InBranch, a_uiSerializationMask, a_pDataBase); }
    virtual void            deserializeLayout(void* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { deserialize(a_pInstance, a_uiCount, a_uiChunkSectionSize, a_InBranch, a_uiSerializationMask, a_pDataBase); }

    // Restoration (replace initialization in case of deserialization)
    virtual restore_state   restore(void* a_pInstance, uint a_uiSerializationFlag, uint a_uiPass) const { return restore_complete; }
    virtual restore_state   restore(void* a_pChunk, uint a_uiSerializationFlag, uint a_uiPass, size_t a_uiCount, size_t a_uiChunkSectionSize ) const { return restore_complete; }

    /// Reset
    virtual void            remember(void const* a_pInstance, byte*& a_pBuffer) const = 0;
    virtual void            remember(void const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pBuffer) const = 0;
    virtual void            reset(void* a_pInstance, byte const*& a_pBuffer) const = 0;
    virtual void            reset(void* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pBuffer) const = 0;

    virtual
    serialization::Bundle*  createBundle(serialization::BundleNode* a_pOwnerNode) const = 0;
    virtual void            destroyBundle(serialization::Bundle* a_pBundle) const = 0;

    /// Combination
    virtual void*           newInstance() const;
    virtual void            deleteInstance(void* a_pInstance) const;

    /// Template
    virtual boolean         isTemplateSpecialization() const { return false; }
    virtual boolean         matches(template_specialization const* a_pElements) const { return false; }

    /// Relations
    virtual ERelation       getRelationWith(Type* a_pType) const;

    /// Value and Conversion
    virtual boolean         isConvertibleTo(Type* a_pType) const;
    virtual boolean         isImplicitlyConvertibleTo(Type* a_pType) const;
    virtual void            convertValueTo(Type* a_pDestType, void* a_pDestValue, void const* a_pSrcValue) const;
    virtual boolean         areValueEqual(void const* a_pSrc0, void const* a_pSrc1) const;

    virtual boolean         isDefaultConstructible() const { return true; }

    Namespace*              getNamespace() const;
    void                    removeFromNamespace();

    Type*                   getOwnerType() const;

    virtual void            valueFromString(const string& a_str, void* dest) const = 0;
    virtual void            valueToString( string& s, void* src) const = 0;
    virtual void            interpolate(void* a_src_start, void* a_src_end, real a_fPercent, void* a_pDest, uint mode = 0) const = 0;
    virtual void            copy(void* a_pDest, void const* a_pSrc) const { o_exception(unsupported_member_function_exception, "not implemented yet"); }
    virtual void            smartCopy(void* a_pDest, void const* a_pSource, reflection::Type* a_pSourceType) const 
    {
        if(a_pSourceType == this)
        copy(a_pDest, a_pSource);
    }
    virtual bool            hasTrivialCastTo(Type* a_pType) const { return a_pType == this; }

    virtual uint            getDataPointerLevel() const { return 0; }

    virtual boolean         matches(const char* a_strName, template_specialization const* a_TemplateSpecialization = NULL, bitfield a_bfModifiers = bitfield()) const;

    size_t                  getNestedTypeCount() const
    {
        return m_pNestedTypes == NULL ? 0 : m_pNestedTypes->size();
    }

    Type*                   getNestedType(size_t index) const
    {
        o_assert(index < getNestedTypeCount());
        return (*m_pNestedTypes)[index];
    }

    void                    addNestedType(Type* a_pType);
    void                    removeNestedType(Type* a_pType);

    void                    addNestedTypedef( const string& a_strTypedef, Type* a_pType );
    void                    removeNestedTypedef( const string& a_strTypedef, Type* a_pType );
    inline Type*            getNestedTypedef(const string& a_strTypedef) const;

    virtual LanguageElement*            getElement(
        const char* a_strName
        , template_specialization const*
        , function_signature const*
        , bitfield a_bfModifiers = bitfield()) const;

    virtual void getElements( vector<LanguageElement*>& out, Class* a_pClass = nullptr ) const;

protected:
    virtual DataPointerType*createDataPointerType() const;
    virtual ReferenceType*  createReferenceType() const;
    virtual ArrayType*      createArrayType(size_t a_uiCount) const;
    virtual Type*           createConstType() const = 0;
    
    virtual void            teardownMetaDataCascade(size_t count)
    {
        if(m_pNestedTypes)
        {
            type_container::const_iterator it = m_pNestedTypes->begin();
            type_container::const_iterator end = m_pNestedTypes->end();
            for(;it != end; ++it)
            {
                (*it)->teardownMetaDataCascade(count);
            }
        }
        TemplateElement::teardownMetaDataCascade(count);
    }
    
    /**
     *  @name Signals
     */
     //@{  
#if o__bool__use_kind_creation_signal
public:
    virtual void        fireKindCreated(void* a_pObject) const;
protected:
    mutable connection::slot::list        PHANTOM_CODEGEN_m_slot_list_of_kindCreated;
    signal_t            kindCreated(void* a_pObject) const;
#endif

#if o__bool__use_kind_destruction_signal
public:
    virtual void        fireKindDestroyed(void* a_pObject) const;
protected:
    mutable connection::slot::list        PHANTOM_CODEGEN_m_slot_list_of_kindDestroyed;
    signal_t            kindDestroyed(void* a_pObject) const;
#endif

    //@}
protected:
    type_container* m_pNestedTypes;
    nested_typedef_map* m_pNestedTypedefs;
    size_t          m_uiBuildOrder;
    ushort          m_uiSize;
    ushort          m_uiAlignment;
    ushort          m_uiSerializedSize;
    ushort          m_uiResetSize;

private:
    static size_t NextBuildOrderValue() { static size_t s_NextBuildOrderValue = 0; return s_NextBuildOrderValue++; }
};

o_h_end


#else // o_phantom_reflection_Type_h__
#include "Type.classdef.h"
#endif
