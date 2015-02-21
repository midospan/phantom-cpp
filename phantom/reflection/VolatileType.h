/* TODO LICENCE HERE */

#ifndef o_phantom_reflection_VolatileType_h__
#define o_phantom_reflection_VolatileType_h__

/* ****************** Includes ******************* */
/* **************** Declarations ***************** */
/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export VolatileType : public Type
{
    o_type;

    o_declare_meta_type(VolatileType);

    friend class phantom::reflection::Namespace;

public:
    VolatileType(Type* a_pType);
    ~VolatileType();

    Type*                   getVolatiledType() const { return m_pVolatiledType; }

    virtual Type*           addConst() const;
    virtual Type*           addVolatile() const;
    virtual Type*           addConstVolatile() const;

    virtual Type*           removeConstVolatile() const { return m_pVolatiledType; }
    virtual Type*           removeVolatile() const { return m_pVolatiledType; }
    virtual Type*           removeAllVolatile() const { return m_pVolatiledType->removeAllVolatile(); }
    virtual Type*           removeAllQualifiers() const { return m_pVolatiledType->removeAllQualifiers(); }
    virtual Type*           removeQualifiers() const { return m_pVolatiledType->removeQualifiers(); }

    virtual Type*           replicate(Type* a_pSource) const;

    virtual VolatileType*   asVolatileType() const { return const_cast<VolatileType*>(this); }
    virtual VolatileType*   asVolatileClass() const { return (m_pVolatiledType AND m_pVolatiledType->asClass()) ? const_cast<VolatileType*>(this) : nullptr; }

    virtual string          getQualifiedName() const;
    virtual string          getDecoratedName() const;
    virtual string          getQualifiedDecoratedName() const;

    virtual void*           cast(Type* a_pTargetType, void* a_pSrc) const { return m_pVolatiledType->cast(a_pTargetType, a_pSrc); }
    virtual void*           upcast(Type* a_pTargetType, void* a_pSrc) const { return m_pVolatiledType->upcast(a_pTargetType, a_pSrc); }
    virtual void*           downcast(Type* a_pTargetType, void* a_pSrc) const { return m_pVolatiledType->downcast(a_pTargetType, a_pSrc); }

    /// Volatileruction
    virtual void            construct(void* a_pBuffer) const { m_pVolatiledType->construct(a_pBuffer); }
    virtual void            destroy(void* a_pBuffer) const { m_pVolatiledType->destroy(a_pBuffer); }

    /// Build (for classes but implemented in Type and empty to make it more generic
    virtual void            build(void* a_pBuffer, const rtti_data* a_pOwner = 0) const { m_pVolatiledType->build(a_pBuffer, a_pOwner); }
    virtual void            unbuild(void* a_pBuffer, size_t a_uiLevel = 0) const { m_pVolatiledType->unbuild(a_pBuffer, a_uiLevel); }

    /// Installation (for classes but implemented in Type and empty to make it more generic
    virtual void            install(void* a_pBuffer, const rtti_data* a_pOwner = 0) const { m_pVolatiledType->install(a_pBuffer, a_pOwner); }
    virtual void            uninstall(void* a_pBuffer, size_t a_uiLevel = 0) const { m_pVolatiledType->uninstall(a_pBuffer, a_uiLevel); }

    /// Initialization (for classes but implemented in Type and empty to make it more generic
    virtual void            initialize(void* a_pBuffer) const { m_pVolatiledType->terminate(a_pBuffer); }
    virtual void            terminate(void* a_pBuffer) const { m_pVolatiledType->terminate(a_pBuffer); }

    /// Setup (Volatileruction by default (+ installation + initialization for classes))
    virtual void            setup(void* a_pBuffer, const rtti_data* a_pOwner = 0) const { m_pVolatiledType->install(a_pBuffer, a_pOwner); }
    virtual void            safeSetup(void* a_pBuffer, const rtti_data* a_pOwner = 0) const  { m_pVolatiledType->safeSetup(a_pBuffer, a_pOwner); }
    virtual void            teardown(void* a_pBuffer, size_t a_uiLevel = 0) const { m_pVolatiledType->teardown(a_pBuffer, a_uiLevel); }

    /// Serialization
    virtual void            serialize(void const* a_pInstance, byte*& a_pBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { m_pVolatiledType->serialize(a_pInstance, a_pBuffer, a_uiSerializationMask, a_pDataBase); }
    virtual void            serialize(void const* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { m_pVolatiledType->serialize(a_pInstance, a_uiCount, a_uiChunkSectionSize, a_pBuffer, a_uiSerializationMask, a_pDataBase); }
    virtual void            serialize(void const* a_pInstance, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { m_pVolatiledType->serialize(a_pInstance, a_OutBranch, a_uiSerializationMask, a_pDataBase); }
    virtual void            serialize(void const* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { m_pVolatiledType->serialize(a_pInstance, a_uiCount, a_uiChunkSectionSize, a_OutBranch, a_uiSerializationMask, a_pDataBase); }
    virtual void            serializeLayout(void const* a_pInstance, byte*& a_pBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { m_pVolatiledType->serializeLayout(a_pInstance, a_pBuffer, a_uiSerializationMask, a_pDataBase); }
    virtual void            serializeLayout(void const* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { m_pVolatiledType->serializeLayout(a_pInstance, a_uiCount, a_uiChunkSectionSize, a_pBuffer, a_uiSerializationMask, a_pDataBase); }
    virtual void            serializeLayout(void const* a_pInstance, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { m_pVolatiledType->serializeLayout(a_pInstance, a_OutBranch, a_uiSerializationMask, a_pDataBase); }
    virtual void            serializeLayout(void const* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { m_pVolatiledType->serializeLayout(a_pInstance, a_uiCount, a_uiChunkSectionSize, a_OutBranch, a_uiSerializationMask, a_pDataBase); }

    virtual void            deserialize(void* a_pInstance, byte const*& a_pBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { m_pVolatiledType->deserialize(a_pInstance, a_pBuffer, a_uiSerializationMask, a_pDataBase); }
    virtual void            deserialize(void* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { m_pVolatiledType->deserialize(a_pInstance, a_uiCount, a_uiChunkSectionSize, a_pBuffer, a_uiSerializationMask, a_pDataBase); }
    virtual void            deserialize(void* a_pInstance, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { m_pVolatiledType->deserialize(a_pInstance, a_InBranch, a_uiSerializationMask, a_pDataBase); }
    virtual void            deserialize(void* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { m_pVolatiledType->deserialize(a_pInstance, a_uiCount, a_uiChunkSectionSize, a_InBranch, a_uiSerializationMask, a_pDataBase); }
    virtual void            deserializeLayout(void* a_pInstance, byte const*& a_pBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { m_pVolatiledType->deserializeLayout(a_pInstance, a_pBuffer, a_uiSerializationMask, a_pDataBase); }
    virtual void            deserializeLayout(void* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { m_pVolatiledType->deserializeLayout(a_pInstance, a_uiCount, a_uiChunkSectionSize, a_pBuffer, a_uiSerializationMask, a_pDataBase); }
    virtual void            deserializeLayout(void* a_pInstance, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { m_pVolatiledType->deserializeLayout(a_pInstance, a_InBranch, a_uiSerializationMask, a_pDataBase); }
    virtual void            deserializeLayout(void* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { m_pVolatiledType->deserializeLayout(a_pInstance, a_uiCount, a_uiChunkSectionSize, a_InBranch, a_uiSerializationMask, a_pDataBase); }

    // Restoration (replace initialization in case of deserialization)
    virtual restore_state   restore(void* a_pInstance, uint a_uiSerializationFlag, restore_pass a_uiPass) const { return m_pVolatiledType->restore(a_pInstance, a_uiSerializationFlag, a_uiPass); }
    virtual restore_state   restore(void* a_pChunk, uint a_uiSerializationFlag, restore_pass a_uiPass, size_t a_uiCount, size_t a_uiChunkSectionSize ) const { return m_pVolatiledType->restore(a_pChunk, a_uiSerializationFlag, a_uiPass, a_uiCount, a_uiChunkSectionSize); }

    /// Reset
    virtual void            remember(void const* a_pInstance, byte*& a_pBuffer) const { m_pVolatiledType->remember(a_pInstance, a_pBuffer); }
    virtual void            remember(void const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pBuffer) const { m_pVolatiledType->remember(a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pBuffer); }
    virtual void            reset(void* a_pInstance, byte const*& a_pBuffer) const { m_pVolatiledType->reset(a_pInstance, a_pBuffer); }
    virtual void            reset(void* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pBuffer) const { m_pVolatiledType->reset(a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pBuffer); }


    /// Combination
    virtual void*           newInstance() const { return m_pVolatiledType->newInstance(); }
    virtual void            deleteInstance(void* a_pInstance) const { m_pVolatiledType->deleteInstance(a_pInstance); }

    /// Relations
    virtual ERelation       getRelationWith(Type* a_pType) const { return m_pVolatiledType->getRelationWith(a_pType); }

    /// Value and Conversion
    virtual boolean         areValueEqual(void const* a_pSrc0, void const* a_pSrc1) const { return m_pVolatiledType->areValueEqual(a_pSrc0, a_pSrc1); }

    virtual void            valueFromString(const string& a_str, void* dest) const { m_pVolatiledType->valueFromString(a_str, dest); }
    virtual void            valueToString( string& a_str, const void* src) const { m_pVolatiledType->valueToString(a_str, src);  }
    virtual void            interpolate(void* a_src_start, void* a_src_end, real a_fPercent, void* a_pDest, uint mode = 0) const { m_pVolatiledType->interpolate(a_src_start, a_src_end, a_fPercent, a_pDest, mode); }
    virtual void            copy(void* a_pDest, void const* a_pSrc) const { m_pVolatiledType->copy(a_pDest, a_pSrc); }
    virtual void            smartCopy(reflection::Type* a_pDestType, void* a_pDest, void const* a_pSrc) const { m_pVolatiledType->smartCopy(a_pDestType, a_pDest, a_pSrc); }

    virtual void            getElements( vector<LanguageElement*>& out, Class* a_pClass = nullptr ) const;

    virtual bool            referencesData(const void* a_pInstance, const phantom::data& a_Data) const;
    virtual void            fetchExpressions(Expression* a_pInstanceExpression, vector<Expression*>& out, filter a_Filter, uint a_uiSerializationMask) const;
    
    // Traits
    virtual bool            isDefined() const { return m_pVolatiledType->isDefined(); }
    virtual bool            isCopyable() const { return m_pVolatiledType->isCopyable(); }
    virtual bool            hasCopyDisabled() const { return m_pVolatiledType->hasCopyDisabled(); }
    virtual bool            hasBitAnd() const { return m_pVolatiledType->hasBitAnd(); }
    virtual bool            hasBitAndAssign() const { return m_pVolatiledType->hasBitAndAssign(); }
    virtual bool            hasBitOr() const { return m_pVolatiledType->hasBitOr(); }
    virtual bool            hasBitOrAssign() const { return m_pVolatiledType->hasBitOrAssign(); }
    virtual bool            hasBitXor() const { return m_pVolatiledType->hasBitXor(); }
    virtual bool            hasBitXorAssign() const { return m_pVolatiledType->hasBitXorAssign(); }
    virtual bool            hasComplement() const { return m_pVolatiledType->hasComplement(); }
    virtual bool            hasDereference() const { return m_pVolatiledType->hasDereference(); }
    virtual bool            hasDivides() const { return m_pVolatiledType->hasDivides(); }
    virtual bool            hasDividesAssign() const { return m_pVolatiledType->hasDividesAssign(); }
    virtual bool            hasEqualTo() const { return m_pVolatiledType->hasEqualTo(); }
    virtual bool            hasGreater() const { return m_pVolatiledType->hasGreater(); }
    virtual bool            hasGreaterEqual() const { return m_pVolatiledType->hasGreaterEqual(); }
    virtual bool            hasLeftShift() const { return m_pVolatiledType->hasLeftShift(); }
    virtual bool            hasLeftShiftAssign() const { return m_pVolatiledType->hasLeftShiftAssign(); }
    virtual bool            hasLess() const { return m_pVolatiledType->hasLess(); }
    virtual bool            hasLessEqual() const { return m_pVolatiledType->hasLessEqual(); }
    virtual bool            hasLogicalAnd() const { return m_pVolatiledType->hasLogicalAnd(); }
    virtual bool            hasLogicalNot() const { return m_pVolatiledType->hasLogicalNot(); }
    virtual bool            hasLogicalOr() const { return m_pVolatiledType->hasLogicalOr(); }
    virtual bool            hasMinus() const { return m_pVolatiledType->hasMinus(); }
    virtual bool            hasMinusAssign() const { return m_pVolatiledType->hasMinusAssign(); }
    virtual bool            hasModulus() const { return m_pVolatiledType->hasModulus(); }
    virtual bool            hasModulusAssign() const { return m_pVolatiledType->hasModulusAssign(); }
    virtual bool            hasMultiplies() const { return m_pVolatiledType->hasMultiplies(); }
    virtual bool            hasMultipliesAssign() const { return m_pVolatiledType->hasMultipliesAssign(); }
    virtual bool            hasNegate() const { return m_pVolatiledType->hasNegate(); }
    virtual bool            hasNewOperator() const { return m_pVolatiledType->hasNewOperator(); }
    virtual bool            hasNotEqualTo() const { return m_pVolatiledType->hasNotEqualTo(); }
    virtual bool            hasNothrowAssign() const { return m_pVolatiledType->hasNothrowAssign(); }
    virtual bool            hasNothrowConstructor() const { return m_pVolatiledType->hasNothrowConstructor(); }
    virtual bool            hasNothrowCopy() const { return m_pVolatiledType->hasNothrowCopy(); }
    virtual bool            hasNothrowCopyConstructor() const { return m_pVolatiledType->hasNothrowCopyConstructor(); }
    virtual bool            hasNothrowDefaultConstructor() const { return m_pVolatiledType->hasNothrowDefaultConstructor(); }
    virtual bool            hasPlus() const { return m_pVolatiledType->hasPlus(); }
    virtual bool            hasPlusAssign() const { return m_pVolatiledType->hasPlusAssign(); }
    virtual bool            hasPostDecrement() const { return m_pVolatiledType->hasPostDecrement(); }
    virtual bool            hasPostIncrement() const { return m_pVolatiledType->hasPostIncrement(); }
    virtual bool            hasPreDecrement() const { return m_pVolatiledType->hasPreDecrement(); }
    virtual bool            hasPreIncrement() const { return m_pVolatiledType->hasPreIncrement(); }
    virtual bool            hasRightShift() const { return m_pVolatiledType->hasRightShift(); }
    virtual bool            hasRightShiftAssign() const { return m_pVolatiledType->hasRightShiftAssign(); }

    virtual bool            partialAccepts(Type* a_pType, size_t& a_Score, map<Placeholder*, LanguageElement*>& a_Deductions) const;

    virtual bool            equals(LanguageElement* a_pOther) const 
    {
        return Type::equals(a_pOther) OR (a_pOther->asVolatileType() AND m_pVolatiledType->equals(static_cast<VolatileType*>(a_pOther)->m_pVolatiledType));
    }

    virtual Type*           getUnderlyingType() const { return m_pVolatiledType; }

protected:
    virtual void            referencedElementRemoved(LanguageElement* a_pElement);
    virtual ConstVolatileType*  createConstVolatileType() const { return nullptr; }
    virtual ConstType*          createConstType() const { return nullptr; }
    virtual VolatileType*       createVolatileType() const { return nullptr; }

protected:
    Type* m_pVolatiledType;

};

o_namespace_end(phantom, reflection)

#endif // o_phantom_reflection_VolatileType_h__
