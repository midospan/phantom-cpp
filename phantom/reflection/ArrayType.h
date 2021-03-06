/* TODO LICENCE HERE */

#ifndef o_phantom_reflection_ArrayType_h__
#define o_phantom_reflection_ArrayType_h__
// #pragma message("Including "__FILE__)


/* ****************** Includes ******************* */
/* **************** Declarations ***************** */

/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export ArrayType : public Type
{
    o_type;

    o_declare_meta_type(ArrayType);

public:
    friend class Type;

protected:
    ArrayType(Type* a_pItemType, size_t a_uiCount, modifiers_t modifiers = 0);

public:
    o_destructor ~ArrayType(void);

    virtual boolean     isPOD() const { return m_pItemType->isPOD(); }
    virtual boolean     isArrayType() const { return true; }
    virtual ArrayType*  asArrayType() const { return (ArrayType*)this; }
    size_t              getItemCount() const { return m_uiCount; }

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
        return m_pItemType->allocate(m_uiCount);
    }
    virtual void    deallocate(void* a_pInstance) const
    {
        m_pItemType->deallocate(a_pInstance, m_uiCount);
    }
    virtual void*   allocate(size_t a_uiCount) const
    {
        return m_pItemType->allocate(m_uiCount*a_uiCount);
    }
    virtual void    deallocate(void* a_pChunk, size_t a_uiCount) const
    {
        m_pItemType->deallocate(a_pChunk, m_uiCount*a_uiCount);
    }

    Type*               getItemType() const { return m_pItemType; }

    void*               getItemAddress(void* a_pArrayAddress, size_t a_uiIndex) const 
    { 
        return ((byte*)a_pArrayAddress)+(a_uiIndex*m_pItemType->getSize()); 
    }

    const void*         getItemAddress(const void* a_pArrayAddress, size_t a_uiIndex) const 
    { 
        return ((const byte*)a_pArrayAddress)+(a_uiIndex*m_pItemType->getSize()); 
    }

    void                getItemValue(const void* a_pArrayAddress, size_t a_uiIndex, void* a_pDest) const 
    { 
        return m_pItemType->copy(a_pDest, getItemAddress(a_pArrayAddress, a_uiIndex)); 
    }

    void                setItemValue(void* a_pArrayAddress, size_t a_uiIndex, const void* a_pSrc) const 
    { 
        return m_pItemType->copy(getItemAddress(a_pArrayAddress, a_uiIndex), a_pSrc); 
    }
    
    virtual void        valueFromString(const string& a_str, void* dest) const;

    virtual void        valueToString(string& a_str, const void* src) const;

    virtual void        serialize(void const* a_pInstance, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const
    {
        m_pItemType->serialize(a_pInstance, m_uiCount, m_uiSize/m_uiCount, a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
    }

    virtual void        deserialize(void* a_pInstance, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const
    {
        m_pItemType->deserialize(a_pInstance, m_uiCount, m_uiSize/m_uiCount, a_pInBuffer, a_uiSerializationMask, a_pDataBase);
    }

    virtual void        serialize(void const* a_pInstance, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const;

    virtual void        deserialize(void* a_pInstance, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const;

    virtual void        serialize(void const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const
    {
        byte const* pChunk = reinterpret_cast<byte const*>(a_pChunk);
        while(a_uiCount--)
        {
            m_pItemType->serialize(pChunk, m_uiCount, m_uiSize/m_uiCount, a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
            pChunk += a_uiChunkSectionSize;
        }
    }

    virtual void        deserialize(void* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const
    {
        byte* pChunk = reinterpret_cast<byte*>(a_pChunk);
        while(a_uiCount--)
        {
            m_pItemType->deserialize(pChunk, m_uiCount, m_uiSize/m_uiCount, a_pInBuffer, a_uiSerializationMask, a_pDataBase);
            pChunk += a_uiChunkSectionSize;
        }
    }

    virtual void        serialize(void const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const
    {
        byte const* pChunk = reinterpret_cast<byte const*>(a_pChunk);
        while(a_uiCount--)
        {
            m_pItemType->serialize(pChunk, m_uiCount, m_uiSize/m_uiCount, a_OutBranch, a_uiSerializationMask, a_pDataBase);
            pChunk += a_uiChunkSectionSize;
        }
    }

    virtual void        deserialize(void* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const
    {
        byte* pChunk = reinterpret_cast<byte*>(a_pChunk);
        while(a_uiCount--)
        {
            m_pItemType->deserialize(pChunk, m_uiCount, m_uiSize/m_uiCount, a_InBranch, a_uiSerializationMask, a_pDataBase);
            pChunk += a_uiChunkSectionSize;
        }
    }

    virtual void        remember(void const* a_pInstance, byte*& a_pOutBuffer) const 
    {
        m_pItemType->remember(a_pInstance, m_uiCount, m_uiSize/m_uiCount, a_pOutBuffer);
    }
    virtual void        remember(void const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer) const 
    {
        byte const* pChunk = reinterpret_cast<byte const*>(a_pChunk);
        while(a_uiCount--)
        {
            m_pItemType->remember(pChunk, m_uiCount, m_uiSize/m_uiCount, a_pOutBuffer);
            pChunk += a_uiChunkSectionSize;
        }
    }
    virtual void        reset(void* a_pInstance, byte const*& a_pInBuffer) const 
    {
        m_pItemType->reset(a_pInstance, m_uiCount, m_uiSize/m_uiCount, a_pInBuffer);
    }
    virtual void        reset(void* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pBuffer) const
    {
        byte* pChunk = reinterpret_cast<byte*>(a_pChunk);
        while(a_uiCount--)
        {
            m_pItemType->reset(pChunk, m_uiCount, m_uiSize/m_uiCount, a_pBuffer);
            pChunk += a_uiChunkSectionSize;
        }
    }

    virtual Type*           addConst() const { return m_pItemType->addConst()->addArray(m_uiCount); }

    virtual Type*           addVolatile() const { return m_pItemType->addVolatile()->addArray(m_uiCount); }

    virtual Type*           addConstVolatile() const { return m_pItemType->addConstVolatile()->addArray(m_uiCount); }

    virtual Type*           removeArray() const { return m_pItemType; }

    virtual Type*           removeAllConst() const { return m_pItemType->removeAllConst()->arrayType(m_uiCount); }

    virtual Type*           removeAllQualifiers() const { return m_pItemType->removeAllQualifiers()->arrayType(m_uiCount); }

    virtual string          getQualifiedName() const;
    virtual string          getDecoratedName() const;
    virtual string          getQualifiedDecoratedName() const;

    virtual void            copy(void* a_pDest, void const* a_pSrc) const;
    virtual bool            isCopyable() const { return m_pItemType->isCopyable(); }

    virtual Type*           asPOD() const { return m_pItemType->asPOD() ? (Type*)this : nullptr; }

    virtual bool            partialAccepts(Type* a_pType, size_t& a_Score, map<Placeholder*, LanguageElement*>& a_Deductions ) const;

    virtual bool            equals(LanguageElement* a_pOther) const 
    {
        return Type::equals(a_pOther) OR (a_pOther->asArrayType() AND m_pItemType->equals(static_cast<ArrayType*>(a_pOther)->m_pItemType) AND m_uiCount == static_cast<ArrayType*>(a_pOther)->m_uiCount);
    }

    virtual Type*           getUnderlyingType() const { return m_pItemType; }

protected:
    size_t                  getElementCount() const { return m_uiCount; } // just to check compile error, must be removed !!
    virtual void            referencedElementRemoved(LanguageElement* a_pItem);
    virtual ConstType*      createConstType() const { return nullptr; }
    virtual DataPointerType*createDataPointerType() const { return nullptr; }

protected:
    Type*       m_pItemType;
    size_t      m_uiCount;
};

o_namespace_end(phantom, reflection)



#endif