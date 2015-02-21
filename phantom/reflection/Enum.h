/* TODO LICENCE HERE */

#ifndef o_phantom_reflection_Enum_h__
#define o_phantom_reflection_Enum_h__



/* ****************** Includes ******************* */


/* **************** Declarations ***************** */

/* *********************************************** */
o_namespace_begin(phantom, reflection)

class o_export Enum : public PrimitiveType
{
    o_language_element;

    o_declare_meta_type(Enum);

public:
    typedef phantom::vector<NumericConstant*>   value_vector;

public:
    Enum(); // anonymous enum;
    Enum(const string& a_strName, PrimitiveType* a_pIntType, modifiers_t a_Modifiers = 0);
    o_destructor ~Enum();

    inline NumericConstant* getConstant(size_t i) const  { return m_Constants[i]; }
    inline size_t           getConstantCount() const     { return m_Constants.size(); }

    NumericConstant*        getConstant(const string& a_strKey) const;

    void                    addConstant(NumericConstant* a_pConstant);
    void                    removeConstant(NumericConstant* a_pConstant);

    virtual Enum*           asEnum() const { return const_cast<Enum*>(this); }
    virtual PrimitiveType*  asIntegralType() const { return const_cast<Enum*>(this); }

    virtual void            valueFromString(const string& a_strIn, void* a_pDest) const;
    virtual void            valueToString(string& a_strOut, const void* a_pSrc) const;

    virtual bool            isCopyable() const { return true; }

    virtual void*           allocate(size_t n) const { return m_pIntType->allocate(n); }
    virtual void*           allocate(void) const { return m_pIntType->allocate(); }
    virtual void            deallocate(void * a_pInstance,size_t n) const { m_pIntType->deallocate(a_pInstance, n); }
    virtual void            deallocate(void * a_pInstance) const { m_pIntType->deallocate(a_pInstance); }
    virtual void            construct(void * a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize) const { m_pIntType->construct(a_pInstance, a_uiCount, a_uiChunkSectionSize); }
    virtual void            construct(void * a_pInstance) const { m_pIntType->construct(a_pInstance); }
    virtual void            destroy(void * a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize) const { m_pIntType->destroy(a_pInstance, a_uiCount, a_uiChunkSectionSize); }
    virtual void            destroy(void * a_pInstance) const { m_pIntType->destroy(a_pInstance); }
    virtual void            serialize(void const* a_pInstance, byte*& a_pBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { m_pIntType->serialize(a_pInstance, a_pBuffer, a_uiSerializationMask, a_pDataBase); }
    virtual void            serialize(void const* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { m_pIntType->serialize(a_pInstance, a_uiCount, a_uiChunkSectionSize, a_pBuffer, a_uiSerializationMask, a_pDataBase); }
    virtual void            serialize(void const* a_pInstance, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { m_pIntType->serialize(a_pInstance, a_OutBranch, a_uiSerializationMask, a_pDataBase); }
    virtual void            serialize(void const* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { m_pIntType->serialize(a_pInstance, a_uiCount, a_uiChunkSectionSize, a_OutBranch, a_uiSerializationMask, a_pDataBase); }
    virtual void            deserialize(void* a_pInstance, byte const*& a_pBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { m_pIntType->deserialize(a_pInstance, a_pBuffer, a_uiSerializationMask, a_pDataBase); }
    virtual void            deserialize(void* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { m_pIntType->deserialize(a_pInstance, a_uiCount, a_uiChunkSectionSize, a_pBuffer, a_uiSerializationMask, a_pDataBase); }
    virtual void            deserialize(void* a_pInstance, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { m_pIntType->deserialize(a_pInstance, a_InBranch, a_uiSerializationMask, a_pDataBase); }
    virtual void            deserialize(void* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { m_pIntType->deserialize(a_pInstance, a_uiCount, a_uiChunkSectionSize, a_InBranch, a_uiSerializationMask, a_pDataBase); }

    virtual void            remember(void const* a_pInstance, byte*& a_pBuffer) const { m_pIntType->remember(a_pInstance, a_pBuffer); }
    virtual void            remember(void const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pBuffer) const { m_pIntType->remember(a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pBuffer); }
    virtual void            reset(void* a_pInstance, byte const*& a_pBuffer) const { m_pIntType->reset(a_pInstance, a_pBuffer); }
    virtual void            reset(void* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pBuffer) const { m_pIntType->reset(a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pBuffer); }
    virtual void            interpolate(void* a_src_start, void* a_src_end, real a_fPercent, void* a_pDest, uint mode = 0) const
    {
        m_pIntType->interpolate(a_src_start, a_src_end, a_fPercent, a_pDest, mode );
    }

    virtual void            copy(void* a_pDest, void const* a_pSrc) const 
    { 
        m_pIntType->copy(a_pDest, a_pSrc); 
    }

    void            findConstantsWithValue(void* a_pSrc, vector<Constant*>& out) const;

    value_vector::const_iterator beginConstants() const { return m_Constants.begin(); }
    value_vector::const_iterator endConstants() const { return m_Constants.end(); }

    PrimitiveType* getIntType() const { return m_pIntType; }

    virtual Type*  getUnderlyingType() const { return m_pIntType; }

protected:
    virtual void elementRemoved(LanguageElement* a_pElement);
    Enum(PrimitiveType* a_pIntType, const string& a_strName, ushort a_uiSize, ushort a_uiAlignment, modifiers_t a_Modifiers = 0);
    void ancestorChanged(LanguageElement* a_pOwner);

protected:
    value_vector    m_Constants;
    PrimitiveType*  m_pIntType;
};

o_namespace_end(phantom, reflection)


#endif
