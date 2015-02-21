/* TODO LICENCE HERE */

#ifndef o_phantom_reflection_DataPointerType_h__
#define o_phantom_reflection_DataPointerType_h__

/* ****************** Includes ******************* */

/* **************** Declarations ***************** */

/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export DataPointerType : public PointerType
{
    o_type;

    o_declare_meta_type(DataPointerType);

public:
    friend class Type;

protected:
    DataPointerType(Type* a_pType);

public:
    o_destructor ~DataPointerType(void);

    virtual void*       allocate() const;
    virtual void        deallocate(void* a_pInstance) const;
    virtual void*       allocate(size_t a_uiCount) const;
    virtual void        deallocate(void* a_pChunk, size_t a_uiCount) const;

    Type*               getPointedType() const { return m_pPointedType; }


    virtual Type*       asAddressType() const { return const_cast<DataPointerType*>(this); }
    virtual 
    DataPointerType*    asDataPointerType() const { return const_cast<DataPointerType*>(this); }
    virtual 
    Type*               asClassAddressType() const { return (m_pPointedType AND m_pPointedType->asClass()) ? const_cast<DataPointerType*>(this) : nullptr; }
    virtual 
    DataPointerType*    asClassDataPointerType() const { return (m_pPointedType AND m_pPointedType->asClass()) ? const_cast<DataPointerType*>(this) : nullptr; }
    virtual 
    Type*               asConstClassAddressType() const { return (m_pPointedType AND m_pPointedType->asConstClass()) ? const_cast<DataPointerType*>(this) : nullptr; }
    virtual 
    DataPointerType*    asConstClassDataPointerType() const { return (m_pPointedType AND m_pPointedType->asConstClass()) ? const_cast<DataPointerType*>(this) : nullptr; }
    
    virtual void        copy(void* a_pDest, void const* a_pSrc) const;
    
    virtual void        valueFromString(const string& a_str, void* dest) const;

    virtual void        valueToString(string& a_str, const void* src) const;

    virtual void        valueToLiteral(string& a_str, const void* src) const;

    virtual void        serialize(void const* a_pInstance, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const;

    virtual void        deserialize(void* a_pInstance, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const;

    virtual void        serialize(void const* a_pInstance, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const;

    virtual void        deserialize(void* a_pInstance, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const;

    virtual void        serialize(void const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const;

    virtual void        deserialize(void* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const;

    virtual void        serialize(void const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const;

    virtual void        deserialize(void* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const;

    virtual uint        getDataPointerLevel() const { return m_pPointedType->getDataPointerLevel() + 1; }

    virtual void        remember(void const* a_pInstance, byte*& a_pOutBuffer) const;

    virtual void        reset(void* a_pInstance, byte const*& a_pInBuffer) const;

    virtual void        remember(void const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer) const;

    virtual void        reset(void* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer) const;

    virtual Type*       removePointer() const { return m_pPointedType; }

    virtual Type*       removeAllConst() const { return m_pPointedType->removeAllConst()->pointerType(); }

    virtual Type*       removeAllQualifiers() const { return m_pPointedType->removeAllQualifiers()->pointerType(); }

    virtual string      getQualifiedName() const { return m_pPointedType->getQualifiedName()+'*'; }
    virtual string      getDecoratedName() const { return m_pPointedType->getDecoratedName()+'*'; }
    virtual string      getQualifiedDecoratedName() const { return m_pPointedType->getQualifiedDecoratedName()+'*'; }

    virtual bool        referencesData(const void* a_pInstance, const phantom::data& a_Data) const;

    virtual bool        isCopyable() const { return true; }

    virtual bool        partialAccepts(Type* a_pType, size_t& a_Score, map<Placeholder*, LanguageElement*>& a_DeducedConstants) const;

    virtual bool        equals(LanguageElement* a_pOther) const 
    {
        return Type::equals(a_pOther) OR (a_pOther->asDataPointerType() AND m_pPointedType->equals(static_cast<DataPointerType*>(a_pOther)->m_pPointedType));
    }

    virtual Type*       getUnderlyingType() const { return m_pPointedType; }

    /// Built-in Delegates
    // 
    /// 13.6.5
    /// T *VQ & operator++(T *VQ &);
    /// T *VQ & operator--(T *VQ &);
    /// T * operator++(T *VQ &, int);
    /// T * operator--(T *VQ &, int);
    void                preIncrement(void** a_pArgs, void* a_pOutput);
    void                postIncrement(void** a_pArgs, void* a_pOutput);
    void                preDecrement(void** a_pArgs, void* a_pOutput);
    void                postDecrement(void** a_pArgs, void* a_pOutput);

    /// 13.6.6
    /// T & operator*(T *);
    /// ---------------------- 
    void                dereference(void** a_pArgs, void* a_pOutput);

    /// 13.6.7
    /// T & operator+(T *);
    /// ---------------------- 
    void                plus(void** a_pArgs, void* a_pOutput);
    

    /// 13.6.13
    /// T * operator+(T *, std::ptrdiff_t);
    /// T & operator[](T *, std::ptrdiff_t);
    /// T * operator-(T *, std::ptrdiff_t);
    /// T * operator+(std::ptrdiff_t, T *);
    /// T & operator[](std::ptrdiff_t, T *);
    void                add(void** a_pArgs, void* a_pOutput);
    void                addRev(void** a_pArgs, void* a_pOutput);
    void                bracket(void** a_pArgs, void* a_pOutput);
    void                bracketRev(void** a_pArgs, void* a_pOutput);
    void                subtract(void** a_pArgs, void* a_pOutput);
    

    /// 13.6.14
    /// ---------------------- 
    /// std::ptrdiff_t operator-(T , T );
    void                subtractPointer(void** a_pArgs, void* a_pOutput);
    // 

    /// 13.6.21
    /// ---------------------- 
    /// T *VQ & operator+=(T *VQ &, std::ptrdiff_t);
    /// T *VQ & operator-=(T *VQ &, std::ptrdiff_t);
    void                assignmentAdd(void** a_pArgs, void* a_pOutput);
    void                assignmentSubtract(void** a_pArgs, void* a_pOutput);

protected:
    virtual void        referencedElementRemoved(LanguageElement* a_pElement);

protected:
    Type*        m_pPointedType;
};

o_namespace_end(phantom, reflection)



#endif