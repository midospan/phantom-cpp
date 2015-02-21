/* TODO LICENCE HERE */

#ifndef o_phantom_reflection_ConstVolatileType_h__
#define o_phantom_reflection_ConstVolatileType_h__

/* ****************** Includes ******************* */
/* **************** Declarations ***************** */
/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export ConstVolatileType : public Type
{
    o_type;

    o_declare_meta_type(ConstVolatileType);

    friend class phantom::reflection::Namespace;

public:
    ConstVolatileType(Type* a_pType);
    ~ConstVolatileType();

    Type*                   getConstVolatiledType() const { return m_pConstVolatiledType; }

    virtual Type*           addConst() const { return const_cast<ConstVolatileType*>(this); }
    virtual Type*           addVolatile() const { return const_cast<ConstVolatileType*>(this); }
    virtual Type*           addConstVolatile() const { return const_cast<ConstVolatileType*>(this); }

    virtual Type*           removeConst() const { return m_pConstVolatiledType->volatileType(); }
    virtual Type*           removeVolatile() const { return m_pConstVolatiledType->constType(); }
    virtual Type*           removeConstVolatile() const { return m_pConstVolatiledType; }
    virtual Type*           removeAllConstVolatile() const { return m_pConstVolatiledType->removeAllConstVolatile(); }
    virtual Type*           removeAllQualifiers() const { return m_pConstVolatiledType->removeAllQualifiers(); }
    virtual Type*           removeQualifiers() const { return m_pConstVolatiledType->removeQualifiers(); }

    virtual Type*           replicate(Type* a_pSource) const { return m_pConstVolatiledType->replicate(a_pSource->removeConstVolatile())->addConstVolatile(); }

    virtual ConstVolatileType*   asConstVolatileType() const { return const_cast<ConstVolatileType*>(this); }
    virtual ConstVolatileType*   asConstVolatileClass() const { return (m_pConstVolatiledType AND m_pConstVolatiledType->asClass()) ? const_cast<ConstVolatileType*>(this) : nullptr; }

    virtual string          getQualifiedName() const;
    virtual string          getDecoratedName() const;
    virtual string          getQualifiedDecoratedName() const;

    virtual void*           cast(Type* a_pTargetType, void* a_pSrc) const { return m_pConstVolatiledType->cast(a_pTargetType, a_pSrc); }
    virtual void*           upcast(Type* a_pTargetType, void* a_pSrc) const { return m_pConstVolatiledType->upcast(a_pTargetType, a_pSrc); }
    virtual void*           downcast(Type* a_pTargetType, void* a_pSrc) const { return m_pConstVolatiledType->downcast(a_pTargetType, a_pSrc); }

    /// ConstVolatileruction
    virtual void            construct(void* a_pBuffer) const { m_pConstVolatiledType->construct(a_pBuffer); }
    virtual void            destroy(void* a_pBuffer) const { m_pConstVolatiledType->destroy(a_pBuffer); }

    /// Build (for classes but implemented in Type and empty to make it more generic
    virtual void            build(void* a_pBuffer, const rtti_data* a_pOwner = 0) const { m_pConstVolatiledType->build(a_pBuffer, a_pOwner); }
    virtual void            unbuild(void* a_pBuffer, size_t a_uiLevel = 0) const { m_pConstVolatiledType->unbuild(a_pBuffer, a_uiLevel); }

    /// Installation (for classes but implemented in Type and empty to make it more generic
    virtual void            install(void* a_pBuffer, const rtti_data* a_pOwner = 0) const { m_pConstVolatiledType->install(a_pBuffer, a_pOwner); }
    virtual void            uninstall(void* a_pBuffer, size_t a_uiLevel = 0) const { m_pConstVolatiledType->uninstall(a_pBuffer, a_uiLevel); }

    /// Initialization (for classes but implemented in Type and empty to make it more generic
    virtual void            initialize(void* a_pBuffer) const { m_pConstVolatiledType->terminate(a_pBuffer); }
    virtual void            terminate(void* a_pBuffer) const { m_pConstVolatiledType->terminate(a_pBuffer); }

    /// Setup (ConstVolatileruction by default (+ installation + initialization for classes))
    virtual void            setup(void* a_pBuffer, const rtti_data* a_pOwner = 0) const { m_pConstVolatiledType->install(a_pBuffer, a_pOwner); }
    virtual void            safeSetup(void* a_pBuffer, const rtti_data* a_pOwner = 0) const  { m_pConstVolatiledType->safeSetup(a_pBuffer, a_pOwner); }
    virtual void            teardown(void* a_pBuffer, size_t a_uiLevel = 0) const { m_pConstVolatiledType->teardown(a_pBuffer, a_uiLevel); }

    /// Serialization
    virtual void            serialize(void const* a_pInstance, byte*& a_pBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { m_pConstVolatiledType->serialize(a_pInstance, a_pBuffer, a_uiSerializationMask, a_pDataBase); }
    virtual void            serialize(void const* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { m_pConstVolatiledType->serialize(a_pInstance, a_uiCount, a_uiChunkSectionSize, a_pBuffer, a_uiSerializationMask, a_pDataBase); }
    virtual void            serialize(void const* a_pInstance, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { m_pConstVolatiledType->serialize(a_pInstance, a_OutBranch, a_uiSerializationMask, a_pDataBase); }
    virtual void            serialize(void const* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { m_pConstVolatiledType->serialize(a_pInstance, a_uiCount, a_uiChunkSectionSize, a_OutBranch, a_uiSerializationMask, a_pDataBase); }
    virtual void            serializeLayout(void const* a_pInstance, byte*& a_pBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { m_pConstVolatiledType->serializeLayout(a_pInstance, a_pBuffer, a_uiSerializationMask, a_pDataBase); }
    virtual void            serializeLayout(void const* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { m_pConstVolatiledType->serializeLayout(a_pInstance, a_uiCount, a_uiChunkSectionSize, a_pBuffer, a_uiSerializationMask, a_pDataBase); }
    virtual void            serializeLayout(void const* a_pInstance, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { m_pConstVolatiledType->serializeLayout(a_pInstance, a_OutBranch, a_uiSerializationMask, a_pDataBase); }
    virtual void            serializeLayout(void const* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { m_pConstVolatiledType->serializeLayout(a_pInstance, a_uiCount, a_uiChunkSectionSize, a_OutBranch, a_uiSerializationMask, a_pDataBase); }

    virtual void            deserialize(void* a_pInstance, byte const*& a_pBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { m_pConstVolatiledType->deserialize(a_pInstance, a_pBuffer, a_uiSerializationMask, a_pDataBase); }
    virtual void            deserialize(void* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { m_pConstVolatiledType->deserialize(a_pInstance, a_uiCount, a_uiChunkSectionSize, a_pBuffer, a_uiSerializationMask, a_pDataBase); }
    virtual void            deserialize(void* a_pInstance, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { m_pConstVolatiledType->deserialize(a_pInstance, a_InBranch, a_uiSerializationMask, a_pDataBase); }
    virtual void            deserialize(void* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { m_pConstVolatiledType->deserialize(a_pInstance, a_uiCount, a_uiChunkSectionSize, a_InBranch, a_uiSerializationMask, a_pDataBase); }
    virtual void            deserializeLayout(void* a_pInstance, byte const*& a_pBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { m_pConstVolatiledType->deserializeLayout(a_pInstance, a_pBuffer, a_uiSerializationMask, a_pDataBase); }
    virtual void            deserializeLayout(void* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { m_pConstVolatiledType->deserializeLayout(a_pInstance, a_uiCount, a_uiChunkSectionSize, a_pBuffer, a_uiSerializationMask, a_pDataBase); }
    virtual void            deserializeLayout(void* a_pInstance, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { m_pConstVolatiledType->deserializeLayout(a_pInstance, a_InBranch, a_uiSerializationMask, a_pDataBase); }
    virtual void            deserializeLayout(void* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { m_pConstVolatiledType->deserializeLayout(a_pInstance, a_uiCount, a_uiChunkSectionSize, a_InBranch, a_uiSerializationMask, a_pDataBase); }

    // Restoration (replace initialization in case of deserialization)
    virtual restore_state   restore(void* a_pInstance, uint a_uiSerializationFlag, restore_pass a_uiPass) const { return m_pConstVolatiledType->restore(a_pInstance, a_uiSerializationFlag, a_uiPass); }
    virtual restore_state   restore(void* a_pChunk, uint a_uiSerializationFlag, restore_pass a_uiPass, size_t a_uiCount, size_t a_uiChunkSectionSize ) const { return m_pConstVolatiledType->restore(a_pChunk, a_uiSerializationFlag, a_uiPass, a_uiCount, a_uiChunkSectionSize); }

    /// Reset
    virtual void            remember(void const* a_pInstance, byte*& a_pBuffer) const { m_pConstVolatiledType->remember(a_pInstance, a_pBuffer); }
    virtual void            remember(void const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pBuffer) const { m_pConstVolatiledType->remember(a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pBuffer); }
    virtual void            reset(void* a_pInstance, byte const*& a_pBuffer) const { m_pConstVolatiledType->reset(a_pInstance, a_pBuffer); }
    virtual void            reset(void* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pBuffer) const { m_pConstVolatiledType->reset(a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pBuffer); }


    /// Combination
    virtual void*           newInstance() const { return m_pConstVolatiledType->newInstance(); }
    virtual void            deleteInstance(void* a_pInstance) const { m_pConstVolatiledType->deleteInstance(a_pInstance); }

    /// Relations
    virtual ERelation       getRelationWith(Type* a_pType) const { return m_pConstVolatiledType->getRelationWith(a_pType); }

    /// Value and Conversion
    virtual boolean         areValueEqual(void const* a_pSrc0, void const* a_pSrc1) const { return m_pConstVolatiledType->areValueEqual(a_pSrc0, a_pSrc1); }

    virtual void            valueFromString(const string& a_str, void* dest) const { m_pConstVolatiledType->valueFromString(a_str, dest); }
    virtual void            valueToString( string& a_str, const void* src) const { m_pConstVolatiledType->valueToString(a_str, src);  }
    virtual void            interpolate(void* a_src_start, void* a_src_end, real a_fPercent, void* a_pDest, uint mode = 0) const { m_pConstVolatiledType->interpolate(a_src_start, a_src_end, a_fPercent, a_pDest, mode); }
    virtual void            copy(void* a_pDest, void const* a_pSrc) const { m_pConstVolatiledType->copy(a_pDest, a_pSrc); }
    virtual void            smartCopy(reflection::Type* a_pDestType, void* a_pDest, void const* a_pSrc) const { m_pConstVolatiledType->smartCopy(a_pDestType, a_pDest, a_pSrc); }

    virtual void            getElements( vector<LanguageElement*>& out, Class* a_pClass = nullptr ) const;

    virtual bool            referencesData(const void* a_pInstance, const phantom::data& a_Data) const;
    virtual void            fetchExpressions(Expression* a_pInstanceExpression, vector<Expression*>& out, filter a_Filter, uint a_uiSerializationMask) const;
    
    // Traits
    virtual bool            isDefined() const { return m_pConstVolatiledType->isDefined(); }
    virtual bool            isCopyable() const { return m_pConstVolatiledType->isCopyable(); }
    virtual bool            hasCopyDisabled() const { return m_pConstVolatiledType->hasCopyDisabled(); }
    virtual bool            hasBitAnd() const { return m_pConstVolatiledType->hasBitAnd(); }
    virtual bool            hasBitAndAssign() const { return m_pConstVolatiledType->hasBitAndAssign(); }
    virtual bool            hasBitOr() const { return m_pConstVolatiledType->hasBitOr(); }
    virtual bool            hasBitOrAssign() const { return m_pConstVolatiledType->hasBitOrAssign(); }
    virtual bool            hasBitXor() const { return m_pConstVolatiledType->hasBitXor(); }
    virtual bool            hasBitXorAssign() const { return m_pConstVolatiledType->hasBitXorAssign(); }
    virtual bool            hasComplement() const { return m_pConstVolatiledType->hasComplement(); }
    virtual bool            hasDereference() const { return m_pConstVolatiledType->hasDereference(); }
    virtual bool            hasDivides() const { return m_pConstVolatiledType->hasDivides(); }
    virtual bool            hasDividesAssign() const { return m_pConstVolatiledType->hasDividesAssign(); }
    virtual bool            hasEqualTo() const { return m_pConstVolatiledType->hasEqualTo(); }
    virtual bool            hasGreater() const { return m_pConstVolatiledType->hasGreater(); }
    virtual bool            hasGreaterEqual() const { return m_pConstVolatiledType->hasGreaterEqual(); }
    virtual bool            hasLeftShift() const { return m_pConstVolatiledType->hasLeftShift(); }
    virtual bool            hasLeftShiftAssign() const { return m_pConstVolatiledType->hasLeftShiftAssign(); }
    virtual bool            hasLess() const { return m_pConstVolatiledType->hasLess(); }
    virtual bool            hasLessEqual() const { return m_pConstVolatiledType->hasLessEqual(); }
    virtual bool            hasLogicalAnd() const { return m_pConstVolatiledType->hasLogicalAnd(); }
    virtual bool            hasLogicalNot() const { return m_pConstVolatiledType->hasLogicalNot(); }
    virtual bool            hasLogicalOr() const { return m_pConstVolatiledType->hasLogicalOr(); }
    virtual bool            hasMinus() const { return m_pConstVolatiledType->hasMinus(); }
    virtual bool            hasMinusAssign() const { return m_pConstVolatiledType->hasMinusAssign(); }
    virtual bool            hasModulus() const { return m_pConstVolatiledType->hasModulus(); }
    virtual bool            hasModulusAssign() const { return m_pConstVolatiledType->hasModulusAssign(); }
    virtual bool            hasMultiplies() const { return m_pConstVolatiledType->hasMultiplies(); }
    virtual bool            hasMultipliesAssign() const { return m_pConstVolatiledType->hasMultipliesAssign(); }
    virtual bool            hasNegate() const { return m_pConstVolatiledType->hasNegate(); }
    virtual bool            hasNewOperator() const { return m_pConstVolatiledType->hasNewOperator(); }
    virtual bool            hasNotEqualTo() const { return m_pConstVolatiledType->hasNotEqualTo(); }
    virtual bool            hasNothrowAssign() const { return m_pConstVolatiledType->hasNothrowAssign(); }
    virtual bool            hasNothrowConstructor() const { return m_pConstVolatiledType->hasNothrowConstructor(); }
    virtual bool            hasNothrowCopy() const { return m_pConstVolatiledType->hasNothrowCopy(); }
    virtual bool            hasNothrowCopyConstructor() const { return m_pConstVolatiledType->hasNothrowCopyConstructor(); }
    virtual bool            hasNothrowDefaultConstructor() const { return m_pConstVolatiledType->hasNothrowDefaultConstructor(); }
    virtual bool            hasPlus() const { return m_pConstVolatiledType->hasPlus(); }
    virtual bool            hasPlusAssign() const { return m_pConstVolatiledType->hasPlusAssign(); }
    virtual bool            hasPostDecrement() const { return m_pConstVolatiledType->hasPostDecrement(); }
    virtual bool            hasPostIncrement() const { return m_pConstVolatiledType->hasPostIncrement(); }
    virtual bool            hasPreDecrement() const { return m_pConstVolatiledType->hasPreDecrement(); }
    virtual bool            hasPreIncrement() const { return m_pConstVolatiledType->hasPreIncrement(); }
    virtual bool            hasRightShift() const { return m_pConstVolatiledType->hasRightShift(); }
    virtual bool            hasRightShiftAssign() const { return m_pConstVolatiledType->hasRightShiftAssign(); }

    virtual bool            partialAccepts(Type* a_pType, size_t& a_Score, map<Placeholder*, LanguageElement*>& a_Deductions) const;

    virtual bool            equals(LanguageElement* a_pOther) const 
    {
        return Type::equals(a_pOther) OR (a_pOther->asConstVolatileType() AND m_pConstVolatiledType->equals(static_cast<ConstVolatileType*>(a_pOther)->m_pConstVolatiledType));
    }

    virtual Type*           getUnderlyingType() const { return m_pConstVolatiledType; }

protected:
    virtual void                referencedElementRemoved(LanguageElement* a_pElement);
    virtual ConstVolatileType*  createConstVolatileType() const { return nullptr; }
    virtual ConstType*          createConstType() const { return nullptr; }
    virtual VolatileType*       createVolatileType() const { return nullptr; }

protected:
    Type* m_pConstVolatiledType;

};

o_namespace_end(phantom, reflection)

#endif // o_phantom_reflection_ConstVolatileType_h__
