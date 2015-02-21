/* TODO LICENCE HERE */

#ifndef o_phantom_reflection_ConstType_h__
#define o_phantom_reflection_ConstType_h__

/* ****************** Includes ******************* */
/* **************** Declarations ***************** */
/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export ConstType : public Type
{
    o_type;

    o_declare_meta_type(ConstType);

    friend class phantom::reflection::Namespace;

public:
    ConstType(Type* a_pType);
    ~ConstType();

    Type*                   getConstedType() const { return m_pConstedType; }

    virtual Type*           addConst() const;
    virtual Type*           addVolatile() const;
    virtual Type*           addConstVolatile() const;

    virtual Type*           removeConstVolatile() const { return m_pConstedType; }
    virtual Type*           removeConst() const { return m_pConstedType; }
    virtual Type*           removeAllConst() const { return m_pConstedType->removeAllConst(); }
    virtual Type*           removeQualifiers() const { return m_pConstedType->removeQualifiers(); }
    virtual Type*           removeAllQualifiers() const { return m_pConstedType->removeAllQualifiers(); }

    virtual Type*           replicate(Type* a_pSource) const { return m_pConstedType->replicate(a_pSource->removeConst())->addConst(); }

    virtual ConstType*      asConstType() const { return const_cast<ConstType*>(this); }
    virtual ConstType*      asConstClass() const { return (m_pConstedType AND m_pConstedType->asClass()) ? const_cast<ConstType*>(this) : nullptr; }

    virtual string          getQualifiedName() const;
    virtual string          getDecoratedName() const;
    virtual string          getQualifiedDecoratedName() const;

    virtual void*           cast(Type* a_pTargetType, void* a_pSrc) const { return m_pConstedType->cast(a_pTargetType, a_pSrc); }
    virtual void*           upcast(Type* a_pTargetType, void* a_pSrc) const { return m_pConstedType->upcast(a_pTargetType, a_pSrc); }
    virtual void*           downcast(Type* a_pTargetType, void* a_pSrc) const { return m_pConstedType->downcast(a_pTargetType, a_pSrc); }

    /// Construction
    virtual void            construct(void* a_pBuffer) const { m_pConstedType->construct(a_pBuffer); }
    virtual void            destroy(void* a_pBuffer) const { m_pConstedType->destroy(a_pBuffer); }

    /// Build (for classes but implemented in Type and empty to make it more generic
    virtual void            build(void* a_pBuffer, const rtti_data* a_pOwner = 0) const { m_pConstedType->build(a_pBuffer, a_pOwner); }
    virtual void            unbuild(void* a_pBuffer, size_t a_uiLevel = 0) const { m_pConstedType->unbuild(a_pBuffer, a_uiLevel); }

    /// Installation (for classes but implemented in Type and empty to make it more generic
    virtual void            install(void* a_pBuffer, const rtti_data* a_pOwner = 0) const { m_pConstedType->install(a_pBuffer, a_pOwner); }
    virtual void            uninstall(void* a_pBuffer, size_t a_uiLevel = 0) const { m_pConstedType->uninstall(a_pBuffer, a_uiLevel); }

    /// Initialization (for classes but implemented in Type and empty to make it more generic
    virtual void            initialize(void* a_pBuffer) const { m_pConstedType->terminate(a_pBuffer); }
    virtual void            terminate(void* a_pBuffer) const { m_pConstedType->terminate(a_pBuffer); }

    /// Setup (Construction by default (+ installation + initialization for classes))
    virtual void            setup(void* a_pBuffer, const rtti_data* a_pOwner = 0) const { m_pConstedType->install(a_pBuffer, a_pOwner); }
    virtual void            safeSetup(void* a_pBuffer, const rtti_data* a_pOwner = 0) const  { m_pConstedType->safeSetup(a_pBuffer, a_pOwner); }
    virtual void            teardown(void* a_pBuffer, size_t a_uiLevel = 0) const { m_pConstedType->teardown(a_pBuffer, a_uiLevel); }

    /// Serialization
    virtual void            serialize(void const* a_pInstance, byte*& a_pBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { m_pConstedType->serialize(a_pInstance, a_pBuffer, a_uiSerializationMask, a_pDataBase); }
    virtual void            serialize(void const* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { m_pConstedType->serialize(a_pInstance, a_uiCount, a_uiChunkSectionSize, a_pBuffer, a_uiSerializationMask, a_pDataBase); }
    virtual void            serialize(void const* a_pInstance, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { m_pConstedType->serialize(a_pInstance, a_OutBranch, a_uiSerializationMask, a_pDataBase); }
    virtual void            serialize(void const* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { m_pConstedType->serialize(a_pInstance, a_uiCount, a_uiChunkSectionSize, a_OutBranch, a_uiSerializationMask, a_pDataBase); }
    virtual void            serializeLayout(void const* a_pInstance, byte*& a_pBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { m_pConstedType->serializeLayout(a_pInstance, a_pBuffer, a_uiSerializationMask, a_pDataBase); }
    virtual void            serializeLayout(void const* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { m_pConstedType->serializeLayout(a_pInstance, a_uiCount, a_uiChunkSectionSize, a_pBuffer, a_uiSerializationMask, a_pDataBase); }
    virtual void            serializeLayout(void const* a_pInstance, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { m_pConstedType->serializeLayout(a_pInstance, a_OutBranch, a_uiSerializationMask, a_pDataBase); }
    virtual void            serializeLayout(void const* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { m_pConstedType->serializeLayout(a_pInstance, a_uiCount, a_uiChunkSectionSize, a_OutBranch, a_uiSerializationMask, a_pDataBase); }

    virtual void            deserialize(void* a_pInstance, byte const*& a_pBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { m_pConstedType->deserialize(a_pInstance, a_pBuffer, a_uiSerializationMask, a_pDataBase); }
    virtual void            deserialize(void* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { m_pConstedType->deserialize(a_pInstance, a_uiCount, a_uiChunkSectionSize, a_pBuffer, a_uiSerializationMask, a_pDataBase); }
    virtual void            deserialize(void* a_pInstance, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { m_pConstedType->deserialize(a_pInstance, a_InBranch, a_uiSerializationMask, a_pDataBase); }
    virtual void            deserialize(void* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { m_pConstedType->deserialize(a_pInstance, a_uiCount, a_uiChunkSectionSize, a_InBranch, a_uiSerializationMask, a_pDataBase); }
    virtual void            deserializeLayout(void* a_pInstance, byte const*& a_pBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { m_pConstedType->deserializeLayout(a_pInstance, a_pBuffer, a_uiSerializationMask, a_pDataBase); }
    virtual void            deserializeLayout(void* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { m_pConstedType->deserializeLayout(a_pInstance, a_uiCount, a_uiChunkSectionSize, a_pBuffer, a_uiSerializationMask, a_pDataBase); }
    virtual void            deserializeLayout(void* a_pInstance, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { m_pConstedType->deserializeLayout(a_pInstance, a_InBranch, a_uiSerializationMask, a_pDataBase); }
    virtual void            deserializeLayout(void* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { m_pConstedType->deserializeLayout(a_pInstance, a_uiCount, a_uiChunkSectionSize, a_InBranch, a_uiSerializationMask, a_pDataBase); }

    // Restoration (replace initialization in case of deserialization)
    virtual restore_state   restore(void* a_pInstance, uint a_uiSerializationFlag, restore_pass a_uiPass) const { return m_pConstedType->restore(a_pInstance, a_uiSerializationFlag, a_uiPass); }
    virtual restore_state   restore(void* a_pChunk, uint a_uiSerializationFlag, restore_pass a_uiPass, size_t a_uiCount, size_t a_uiChunkSectionSize ) const { return m_pConstedType->restore(a_pChunk, a_uiSerializationFlag, a_uiPass, a_uiCount, a_uiChunkSectionSize); }

    /// Reset
    virtual void            remember(void const* a_pInstance, byte*& a_pBuffer) const { m_pConstedType->remember(a_pInstance, a_pBuffer); }
    virtual void            remember(void const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pBuffer) const { m_pConstedType->remember(a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pBuffer); }
    virtual void            reset(void* a_pInstance, byte const*& a_pBuffer) const { m_pConstedType->reset(a_pInstance, a_pBuffer); }
    virtual void            reset(void* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pBuffer) const { m_pConstedType->reset(a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pBuffer); }


    /// Combination
    virtual void*           newInstance() const { return m_pConstedType->newInstance(); }
    virtual void            deleteInstance(void* a_pInstance) const { m_pConstedType->deleteInstance(a_pInstance); }

    /// Relations
    virtual ERelation       getRelationWith(Type* a_pType) const { return m_pConstedType->getRelationWith(a_pType); }

    /// Value and Conversion
    virtual boolean         areValueEqual(void const* a_pSrc0, void const* a_pSrc1) const { return m_pConstedType->areValueEqual(a_pSrc0, a_pSrc1); }

    virtual void            valueFromString(const string& a_str, void* dest) const { m_pConstedType->valueFromString(a_str, dest); }
    virtual void            valueToString( string& a_str, const void* src) const { m_pConstedType->valueToString(a_str, src);  }
    virtual void            interpolate(void* a_src_start, void* a_src_end, real a_fPercent, void* a_pDest, uint mode = 0) const { m_pConstedType->interpolate(a_src_start, a_src_end, a_fPercent, a_pDest, mode); }
    virtual void            copy(void* a_pDest, void const* a_pSrc) const { m_pConstedType->copy(a_pDest, a_pSrc); }
    virtual void            smartCopy(reflection::Type* a_pDestType, void* a_pDest, void const* a_pSrc) const { m_pConstedType->smartCopy(a_pDestType, a_pDest, a_pSrc); }

    virtual void            getElements( vector<LanguageElement*>& out, Class* a_pClass = nullptr ) const;

    virtual bool            referencesData(const void* a_pInstance, const phantom::data& a_Data) const;
    virtual void            fetchExpressions(Expression* a_pInstanceExpression, vector<Expression*>& out, filter a_Filter, uint a_uiSerializationMask) const;
    
    // Traits
    virtual bool            isDefined() const { return m_pConstedType->isDefined(); }
    virtual bool            isCopyable() const { return m_pConstedType->isCopyable(); }
    virtual bool            hasCopyDisabled() const { return m_pConstedType->hasCopyDisabled(); }
    virtual bool            hasBitAnd() const { return m_pConstedType->hasBitAnd(); }
    virtual bool            hasBitAndAssign() const { return m_pConstedType->hasBitAndAssign(); }
    virtual bool            hasBitOr() const { return m_pConstedType->hasBitOr(); }
    virtual bool            hasBitOrAssign() const { return m_pConstedType->hasBitOrAssign(); }
    virtual bool            hasBitXor() const { return m_pConstedType->hasBitXor(); }
    virtual bool            hasBitXorAssign() const { return m_pConstedType->hasBitXorAssign(); }
    virtual bool            hasComplement() const { return m_pConstedType->hasComplement(); }
    virtual bool            hasDereference() const { return m_pConstedType->hasDereference(); }
    virtual bool            hasDivides() const { return m_pConstedType->hasDivides(); }
    virtual bool            hasDividesAssign() const { return m_pConstedType->hasDividesAssign(); }
    virtual bool            hasEqualTo() const { return m_pConstedType->hasEqualTo(); }
    virtual bool            hasGreater() const { return m_pConstedType->hasGreater(); }
    virtual bool            hasGreaterEqual() const { return m_pConstedType->hasGreaterEqual(); }
    virtual bool            hasLeftShift() const { return m_pConstedType->hasLeftShift(); }
    virtual bool            hasLeftShiftAssign() const { return m_pConstedType->hasLeftShiftAssign(); }
    virtual bool            hasLess() const { return m_pConstedType->hasLess(); }
    virtual bool            hasLessEqual() const { return m_pConstedType->hasLessEqual(); }
    virtual bool            hasLogicalAnd() const { return m_pConstedType->hasLogicalAnd(); }
    virtual bool            hasLogicalNot() const { return m_pConstedType->hasLogicalNot(); }
    virtual bool            hasLogicalOr() const { return m_pConstedType->hasLogicalOr(); }
    virtual bool            hasMinus() const { return m_pConstedType->hasMinus(); }
    virtual bool            hasMinusAssign() const { return m_pConstedType->hasMinusAssign(); }
    virtual bool            hasModulus() const { return m_pConstedType->hasModulus(); }
    virtual bool            hasModulusAssign() const { return m_pConstedType->hasModulusAssign(); }
    virtual bool            hasMultiplies() const { return m_pConstedType->hasMultiplies(); }
    virtual bool            hasMultipliesAssign() const { return m_pConstedType->hasMultipliesAssign(); }
    virtual bool            hasNegate() const { return m_pConstedType->hasNegate(); }
    virtual bool            hasNewOperator() const { return m_pConstedType->hasNewOperator(); }
    virtual bool            hasNotEqualTo() const { return m_pConstedType->hasNotEqualTo(); }
    virtual bool            hasNothrowAssign() const { return m_pConstedType->hasNothrowAssign(); }
    virtual bool            hasNothrowConstructor() const { return m_pConstedType->hasNothrowConstructor(); }
    virtual bool            hasNothrowCopy() const { return m_pConstedType->hasNothrowCopy(); }
    virtual bool            hasNothrowCopyConstructor() const { return m_pConstedType->hasNothrowCopyConstructor(); }
    virtual bool            hasNothrowDefaultConstructor() const { return m_pConstedType->hasNothrowDefaultConstructor(); }
    virtual bool            hasPlus() const { return m_pConstedType->hasPlus(); }
    virtual bool            hasPlusAssign() const { return m_pConstedType->hasPlusAssign(); }
    virtual bool            hasPostDecrement() const { return m_pConstedType->hasPostDecrement(); }
    virtual bool            hasPostIncrement() const { return m_pConstedType->hasPostIncrement(); }
    virtual bool            hasPreDecrement() const { return m_pConstedType->hasPreDecrement(); }
    virtual bool            hasPreIncrement() const { return m_pConstedType->hasPreIncrement(); }
    virtual bool            hasRightShift() const { return m_pConstedType->hasRightShift(); }
    virtual bool            hasRightShiftAssign() const { return m_pConstedType->hasRightShiftAssign(); }

    virtual bool            partialAccepts(Type* a_pType, size_t& a_Score, map<Placeholder*, LanguageElement*>& a_Deductions) const;

    virtual bool            equals(LanguageElement* a_pOther) const 
    {
        return Type::equals(a_pOther) OR (a_pOther->asConstType() AND m_pConstedType->equals(static_cast<ConstType*>(a_pOther)->m_pConstedType));
    }

    virtual bool            isConstConvertibleTo(Type* a_pType) const 
    {
        return equals(a_pType);
    }

    virtual Type*           getUnderlyingType() const { return m_pConstedType; }

protected:
    virtual void            referencedElementRemoved(LanguageElement* a_pElement);
    virtual ConstVolatileType*  createConstVolatileType() const { return nullptr; }
    virtual ConstType*          createConstType() const { return nullptr; }
    virtual VolatileType*       createVolatileType() const { return nullptr; }

protected:
    Type* m_pConstedType;

};

o_namespace_end(phantom, reflection)

#endif // o_phantom_reflection_ConstType_h__
