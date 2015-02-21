/* TODO LICENCE HERE */

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
    ReferenceType(Type* a_pType, const string& a_strName);

public:
    o_destructor ~ReferenceType(void) ;

    virtual Type*           asAddressType() const { return const_cast<ReferenceType*>(this); }
    virtual ReferenceType*  asReferenceType() const { return const_cast<ReferenceType*>(this); }
    virtual Type*           asClassAddressType() const { return (m_pReferencedType AND m_pReferencedType->asClass()) ? const_cast<ReferenceType*>(this) : nullptr; }
    virtual ReferenceType*  asClassReferenceType() const { return (m_pReferencedType AND m_pReferencedType->asClass()) ? const_cast<ReferenceType*>(this) : nullptr; }
    virtual Type*           asConstClassAddressType() const { return (m_pReferencedType AND m_pReferencedType->asConstClass()) ? const_cast<ReferenceType*>(this) : nullptr; }
    virtual ReferenceType*  asConstClassReferenceType() const { return (m_pReferencedType AND m_pReferencedType->asConstClass()) ? const_cast<ReferenceType*>(this) : nullptr; }

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

    virtual Type*   addLValueReference() const = 0;

    virtual Type*   addRValueReference() const = 0;

    virtual Type*   removeAllConst() const = 0;

    virtual Type*   removeAllQualifiers() const = 0;

    virtual Type*   replicate(Type* a_pSource) const  = 0;

    virtual string  getDecoratedName() const = 0;
    virtual string  getQualifiedDecoratedName() const = 0;

    virtual bool    isCopyable() const { return true; }

    virtual void    copy(void* a_pDest, void const* a_pSrc) const { *(void**)a_pDest = *(void*const*)a_pSrc; }

    virtual bool    partialAccepts(Type* a_pType, size_t& a_Score, map<Placeholder*, LanguageElement*>& a_DeducedConstants) const = 0;

    virtual bool    equals(LanguageElement* a_pOther) const = 0;

    void address(void** a_pArgs, void* a_pOutput)
    {
        *(void**)a_pOutput = a_pArgs[0];
    }

    virtual Type*           getUnderlyingType() const { return m_pReferencedType; }

    void                    memcpyStoreDelegate(void** a_pArgs, void* a_pOutput) 
    { 
        memcpy( a_pArgs[0], a_pArgs[1], m_pReferencedType->getSize());
        *(void**)a_pOutput = (void*)a_pArgs[0];
    }

protected:
    virtual ConstType* createConstType() const { return nullptr; } // cannot create reference const
    virtual DataPointerType* createDataPointerType() const { return nullptr; } // cannot create pointers on reference 
    virtual ReferenceType* createReferenceType() const { return nullptr; } // cannot create reference of reference
    virtual RValueReferenceType* createRValueReferenceType() const { return nullptr; } // cannot create rvalue reference of reference

protected:
    virtual void referencedElementRemoved(LanguageElement* a_pElement);

protected:
    Type*        m_pReferencedType;
};

o_namespace_end(phantom, reflection)

#endif // o_phantom_reflection_ReferenceType_h__