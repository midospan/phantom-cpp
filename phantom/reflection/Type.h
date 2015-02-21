/* TODO LICENCE HERE */

#ifndef o_phantom_reflection_Type_h__
#define o_phantom_reflection_Type_h__

/* ****************** Includes ******************* */
#include "LanguageElement.h"
/* **************** Declarations ***************** */
/* *********************************************** */

#define o_custom_type(Visitor_, Language_) \
    o_custom_language_element(Visitor_, Language_)
    

#define o_type o_custom_type(phantom::reflection::LanguageElementVisitor, phantom::reflection::Language)

o_namespace_begin(phantom, reflection)

enum ETypeId
{
    e_void,
    e_bool,
    e_char,
    e_uchar,
    e_schar,
    e_short,
    e_ushort,
#if o_HAS_BUILT_IN_WCHAR_T
    e_wchar_t,
#endif
#if o_HAS_BUILT_IN_CHAR16_T
    e_char16_t,
#endif
#if o_HAS_BUILT_IN_CHAR32_T
    e_char32_t,
#endif
    e_int,
    e_uint,
    e_long,
    e_ulong,
    e_longlong,
    e_ulonglong,
    e_float,
    e_double,
    e_longdouble,
    e_enum,
    e_pointer,
    e_nullptr_t,
    e_signal_t,
    e_member_pointer,
    e_reference,
    e_rvalue_reference,
    e_array,
    e_structure,
    e_union,
    e_class,
    e_placeholder,
    e_template_dependant,
    e_other,
};

class o_export Type : public NamedElement
{
    o_type;

    friend class phantom::reflection::Scope;
    friend class phantom::reflection::Alias;

    o_declare_meta_type(Type);

    o_invalid_decl(Type);

    friend class DataPointerType;
    friend class ReferenceType;
    friend class LValueReferenceType;
    friend class RValueReferenceType;
    friend class ConstType;
    friend class VolatileType;
    friend class ConstVolatileType;
    friend class ArrayType;

public:
    typedef fastdelegate::FastDelegate<bool(Type*)> filter;
    static bool DataPointerFilter(Type* a_pType)
    {
        return a_pType->removeReference()->removeQualifiers()->asDataPointerType() != nullptr;
    }
    static bool NoFilter(Type* a_pType)
    {
        return true;
    }

    enum ERelation
    {
        e_Relation_None = 0,
        e_Relation_Equal,
        e_Relation_Child ,
        e_Relation_Parent ,
        e_Relation_Compatible ,
        e_Relation_GenericContentChild,
        e_Relation_GenericContentParent,
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
        byte*terminate();

    protected:
        byte*    m_pStartAddress;
        size_t    m_MaxAlignment;
        size_t    m_WrittenBytes;
    };

    static int ConversionRank(ETypeId id);

    Type(ETypeId a_eTypeId, modifiers_t a_Modifiers = 0);
    Type(ETypeId a_eTypeId, const string& a_strName, modifiers_t a_Modifiers = 0);
    Type(ETypeId a_eTypeId, const string& a_strName, ushort a_uiSize, ushort a_uiAlignment, modifiers_t a_Modifiers = 0);
    ~Type();

    o_terminate();

    o_forceinline ETypeId   getTypeId() const { return m_eTypeId; }
    o_forceinline ushort    getSize() const { return m_uiSize; }
    o_forceinline ushort    getAlignment() const { return m_uiAlignment; }
    o_forceinline ushort    getSerializedSize() const { return m_uiSerializedSize; }
    o_forceinline ushort    getResetSize() const { return m_uiResetSize; }
    o_forceinline size_t    getBuildOrder() const { return m_uiBuildOrder; }
    o_forceinline bool      isSingleton() const { return ((m_Modifiers & o_singleton) == o_singleton); }    
    virtual boolean         isSerializable() const { return isDefaultInstanciable(); }
    virtual bool            isDefaultConstructible() const { return (m_Modifiers & o_no_default_constructor) == 0; }
    virtual bool            isDefaultInstanciable() const { return NOT(isAbstract()) AND isDefaultConstructible(); }
    virtual boolean         isKindOf(Type* a_pType) const { return equals(a_pType) OR a_pType->isTemplateDependant(); }
    virtual Type*           asType() const { return const_cast<Type*>(this); }
    virtual ComponentClass* asComponentClass() const { return nullptr; }
    virtual CompositionClass* asCompositionClass() const { return nullptr; }
    virtual AggregationClass* asAggregationClass() const { return nullptr; }
    virtual LanguageElement*asTemplateElement() const { return const_cast<Type*>(this); }
    virtual LanguageElement*asLanguageElement() const { return const_cast<Type*>(this); }

    virtual Type*           getUnderlyingType() const { return nullptr; }

    virtual Type*           addConst() const;
    virtual Type*           addVolatile() const;
    Type*                   addConstLValueReference() const;
    Type*                   addConstRValueReference() const;
    Type*                   addConstVolatile() const;
    virtual Type*           addArray(size_t a_uiCount) const;
    virtual Type*           addLValueReference() const;
    virtual Type*           addRValueReference() const;
    virtual Type*           addPointer() const;
    virtual Type*           addCustom(int id) const;

    virtual Type*           removeConst() const { return const_cast<Type*>(this); }
    virtual Type*           removeVolatile() const { return const_cast<Type*>(this); }
    virtual Type*           removeConstVolatile() const { return const_cast<Type*>(this); }
    virtual Type*           removeQualifiers() const { return const_cast<Type*>(this); }
    Type*                   removeConstReference() const { return removeReference()->removeConst(); }
    Type*                   removeConstLValueReference() const { return removeLValueReference()->removeConst(); }
    Type*                   removeConstRValueReference() const { return removeRValueReference()->removeConst(); }
    virtual Type*           removeArray() const { return const_cast<Type*>(this); }
    virtual Type*           removeReference() const { return const_cast<Type*>(this); }
    virtual Type*           removeLValueReference() const { return const_cast<Type*>(this); }
    virtual Type*           removeRValueReference() const { return const_cast<Type*>(this); }
    virtual Type*           removePointer() const { return const_cast<Type*>(this); }
    virtual Type*           removeAllConst() const { return const_cast<Type*>(this); }
    virtual Type*           removeAllVolatile() const { return const_cast<Type*>(this); }
    virtual Type*           removeAllConstVolatile() const { return const_cast<Type*>(this); }
    virtual Type*           removeAllQualifiers() const { return const_cast<Type*>(this); }
    virtual Type*           removeCustom(int id) const { return const_cast<Type*>(this); }

    virtual Type*           replicate(Type* a_pInput) const { return a_pInput; }

    virtual void*           cast(Type* a_pTargetType, void* a_pSrc) const { return a_pTargetType == this ? a_pSrc : nullptr; }
    virtual void*           upcast(Type* a_pTargetType, void* a_pSrc) const { return a_pTargetType == this ? a_pSrc : nullptr; }
    virtual void*           downcast(Type* a_pTargetType, void* a_pSrc) const { return a_pTargetType == this ? a_pSrc : nullptr; }


    /// Allocation

    virtual void*           allocate() const;

    virtual void            deallocate(void* a_pInstance) const;

    virtual void*           allocate(size_t a_uiCount) const;

    virtual void            deallocate(void* a_pChunk, size_t a_uiCount) const;

#if o__bool__enable_allocation_statistics
    virtual void*           allocate(o_memory_stat_insert_parameters) const { return allocate(); }
    virtual void*           allocate(size_t a_uiCount o_memory_stat_append_parameters) const { return allocate(a_uiCount); }
    virtual void            deallocate(void* a_pAddress o_memory_stat_append_parameters) const { deallocate(a_pAddress); }
    virtual void            deallocate(void* a_pAddress, size_t a_uiCount o_memory_stat_append_parameters) const { deallocate(a_pAddress, a_uiCount); }
#endif

    /// Construction
    virtual void            construct(void* a_pBuffer) const {}
    virtual void            construct(void* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize ) const;
    virtual void            safeConstruct(void* a_pBuffer) const  { construct(a_pBuffer); }
    virtual void            safeConstruct(void* a_pBuffer, size_t a_uiCount, size_t a_uiChunkSectionSize) const { construct(a_pBuffer, a_uiCount, a_uiChunkSectionSize); }
    virtual void            destroy(void* a_pBuffer) const {}
    virtual void            destroy( void* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize ) const;

    /// Build (Construction by default (+ installation for classes))
    virtual void            build(void* a_pBuffer, const rtti_data* a_pOwner = 0) const { construct(a_pBuffer); }
    virtual void            build(void* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, const rtti_data* a_pOwner = 0) const { construct(a_pChunk, a_uiCount, a_uiChunkSectionSize); }
    virtual void            unbuild(void* a_pBuffer, size_t a_uiLevel = 0) const { destroy(a_pBuffer); }
    virtual void            unbuild(void* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, size_t a_uiLevel = 0) const { destroy(a_pChunk, a_uiCount, a_uiChunkSectionSize); }

    /// Installation (for classes but implemented in Type and empty to make it more generic
    virtual void            install(void* a_pBuffer, const rtti_data* a_pOwner = 0) const { }
    virtual void            install(void* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, const rtti_data* a_pOwner = 0 ) const;
    virtual void            uninstall(void* a_pBuffer, size_t a_uiLevel = 0) const { }
    virtual void            uninstall(void* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, size_t a_uiLevel = 0 ) const;

    /// Initialization (for classes but implemented in Type and empty to make it more generic
    virtual void            initialize(void* a_pBuffer) const { }
    virtual void            initialize(void* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize ) const;
    virtual void            terminate(void* a_pBuffer) const { }
    virtual void            terminate(void* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize ) const;

    /// Setup (Construction by default (+ installation + initialization for classes))
    virtual void            setup(void* a_pBuffer, const rtti_data* a_pOwner = 0) const { construct(a_pBuffer); }
    virtual void            safeSetup(void* a_pBuffer, const rtti_data* a_pOwner = 0) const  { safeConstruct(a_pBuffer); }
    virtual void            setup(void* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, const rtti_data* a_pOwner = 0 ) const { construct(a_pChunk, a_uiCount, a_uiChunkSectionSize); }
    virtual void            teardown(void* a_pBuffer, size_t a_uiLevel = 0) const { destroy(a_pBuffer); }
    virtual void            teardown(void* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, size_t a_uiLevel = 0 ) const { destroy(a_pChunk, a_uiCount, a_uiChunkSectionSize); }

    /// Serialization
    virtual void            serialize(void const* a_pInstance, byte*& a_pBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { o_exception(exception::unsupported_member_function_exception, "not available for this class"); }
    virtual void            serialize(void const* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { o_exception(exception::unsupported_member_function_exception, "not available for this class"); }
    virtual void            serialize(void const* a_pInstance, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { o_exception(exception::unsupported_member_function_exception, "not available for this class"); }
    virtual void            serialize(void const* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { o_exception(exception::unsupported_member_function_exception, "not available for this class"); }
    virtual void            serializeLayout(void const* a_pInstance, byte*& a_pBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { serialize(a_pInstance, a_pBuffer, a_uiSerializationMask, a_pDataBase); }
    virtual void            serializeLayout(void const* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { serialize(a_pInstance, a_uiCount, a_uiChunkSectionSize, a_pBuffer, a_uiSerializationMask, a_pDataBase); }
    virtual void            serializeLayout(void const* a_pInstance, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { serialize(a_pInstance, a_OutBranch, a_uiSerializationMask, a_pDataBase); }
    virtual void            serializeLayout(void const* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { serialize(a_pInstance, a_uiCount, a_uiChunkSectionSize, a_OutBranch, a_uiSerializationMask, a_pDataBase); }
    virtual void            deserialize(void* a_pInstance, byte const*& a_pBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { o_exception(exception::unsupported_member_function_exception, "not available for this class"); }
    virtual void            deserialize(void* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { o_exception(exception::unsupported_member_function_exception, "not available for this class"); }
    virtual void            deserialize(void* a_pInstance, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { o_exception(exception::unsupported_member_function_exception, "not available for this class"); }
    virtual void            deserialize(void* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { o_exception(exception::unsupported_member_function_exception, "not available for this class"); }
    virtual void            deserializeLayout(void* a_pInstance, byte const*& a_pBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { deserialize(a_pInstance, a_pBuffer, a_uiSerializationMask, a_pDataBase); }
    virtual void            deserializeLayout(void* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { deserialize(a_pInstance, a_uiCount, a_uiChunkSectionSize, a_pBuffer, a_uiSerializationMask, a_pDataBase); }
    virtual void            deserializeLayout(void* a_pInstance, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { deserialize(a_pInstance, a_InBranch, a_uiSerializationMask, a_pDataBase); }
    virtual void            deserializeLayout(void* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { deserialize(a_pInstance, a_uiCount, a_uiChunkSectionSize, a_InBranch, a_uiSerializationMask, a_pDataBase); }

    // Restoration (replace initialization in case of deserialization)
    virtual restore_state   restore(void* a_pInstance, uint a_uiSerializationFlag, restore_pass a_uiPass) const { return restore_complete; }
    virtual restore_state   restore(void* a_pChunk, uint a_uiSerializationFlag, restore_pass a_uiPass, size_t a_uiCount, size_t a_uiChunkSectionSize ) const { return restore_complete; }

    /// Reset
    virtual void            remember(void const* a_pInstance, byte*& a_pBuffer) const { o_exception(exception::unsupported_member_function_exception, "not available for this class"); }
    virtual void            remember(void const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pBuffer) const { o_exception(exception::unsupported_member_function_exception, "not available for this class"); }
    virtual void            reset(void* a_pInstance, byte const*& a_pBuffer) const { o_exception(exception::unsupported_member_function_exception, "not available for this class"); }
    virtual void            reset(void* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pBuffer) const { o_exception(exception::unsupported_member_function_exception, "not available for this class"); }


    /// Combination
    virtual void*           newInstance() const;
    virtual void            deleteInstance(void* a_pInstance) const;
    
    /// Relations
    virtual ERelation       getRelationWith(Type* a_pType) const;

    /// Value and Conversion
    virtual boolean         areValueEqual(void const* a_pSrc0, void const* a_pSrc1) const;

    virtual void            valueFromString(const string& a_str, void* dest) const { o_exception(exception::unsupported_member_function_exception, "not available for this class"); }
    virtual void            valueToString( string& s, const void* src) const { o_exception(exception::unsupported_member_function_exception, "not available for this class"); }
    virtual void            valueToLiteral( string& s, const void* src ) const;
    virtual void            interpolate(void* a_src_start, void* a_src_end, real a_fPercent, void* a_pDest, uint mode = 0) const { o_exception(exception::unsupported_member_function_exception, "not available for this class"); }
    virtual void            copy(void* a_pDest, void const* a_pSrc) const { o_exception(exception::unsupported_member_function_exception, "not implemented yet"); }
    virtual void            smartCopy(reflection::Type* a_pDestType, void* a_pDest, void const* a_pSource) const;

    virtual void            getElements( vector<LanguageElement*>& out, Class* a_pClass = nullptr ) const;

    virtual bool            referencesData(const void* a_pInstance, const phantom::data& a_Data) const;
    
    void                    fetchPointerReferenceExpressions(Expression* a_pInstanceExpression, vector<Expression*>& out, uint a_uiSerializationMask = 0xffffffff) const { fetchExpressions(a_pInstanceExpression, out, filter(&Type::DataPointerFilter), a_uiSerializationMask); }

    virtual void            fetchExpressions(Expression* a_pInstanceExpression, vector<Expression*>& out, filter a_Filter = filter(&Type::NoFilter), uint a_uiSerializationMask = 0xffffffff) const { o_unused(a_pInstanceExpression); o_unused(out); o_unused(a_Filter); o_unused(a_uiSerializationMask); }
    // Traits
    virtual bool            isCopyable() const { return false; }

    conversion*             conversionTo(Type* a_pOutput, int conversionType = 0, LanguageElement* a_pContextScope = nullptr, int a_iUserDefinedConversionsAllowed = e_implicit_functions);
    
    o_forceinline bool      hasPlacementExtension() const { return testModifiers(o_placement_extension); }

    virtual bool            hasNewVTable() const { return false; }
    virtual bool            hasCopyDisabled() const { return false; }
    virtual bool            hasBitAnd() const { return false; }
    virtual bool            hasBitAndAssign() const { return false; }
    virtual bool            hasBitOr() const { return false; }
    virtual bool            hasBitOrAssign() const { return false; }
    virtual bool            hasBitXor() const { return false; }
    virtual bool            hasBitXorAssign() const { return false; }
    virtual bool            hasComplement() const { return false; }
    virtual bool            hasDereference() const { return false; }
    virtual bool            hasDivides() const { return false; }
    virtual bool            hasDividesAssign() const { return false; }
    virtual bool            hasEqualTo() const { return false; }
    virtual bool            hasGreater() const { return false; }
    virtual bool            hasGreaterEqual() const { return false; }
    virtual bool            hasLeftShift() const { return false; }
    virtual bool            hasLeftShiftAssign() const { return false; }
    virtual bool            hasLess() const { return false; }
    virtual bool            hasLessEqual() const { return false; }
    virtual bool            hasLogicalAnd() const { return false; }
    virtual bool            hasLogicalNot() const { return false; }
    virtual bool            hasLogicalOr() const { return false; }
    virtual bool            hasMinus() const { return false; }
    virtual bool            hasMinusAssign() const { return false; }
    virtual bool            hasModulus() const { return false; }
    virtual bool            hasModulusAssign() const { return false; }
    virtual bool            hasMultiplies() const { return false; }
    virtual bool            hasMultipliesAssign() const { return false; }
    virtual bool            hasNegate() const { return false; }
    virtual bool            hasNewOperator() const { return false; }
    virtual bool            hasNotEqualTo() const { return false; }
    virtual bool            hasNothrowAssign() const { return false; }
    virtual bool            hasNothrowConstructor() const { return false; }
    virtual bool            hasNothrowCopy() const { return false; }
    virtual bool            hasNothrowCopyConstructor() const { return false; }
    virtual bool            hasNothrowDefaultConstructor() const { return false; }
    virtual bool            hasPlus() const { return false; }
    virtual bool            hasPlusAssign() const { return false; }
    virtual bool            hasPostDecrement() const { return false; }
    virtual bool            hasPostIncrement() const { return false; }
    virtual bool            hasPreDecrement() const { return false; }
    virtual bool            hasPreIncrement() const { return false; }
    virtual bool            hasRightShift() const { return false; }
    virtual bool            hasRightShiftAssign() const { return false; }

    virtual Type*           promote() const { return const_cast<Type*>(this); } /// standard 4.x

    inline bool             isPromotedArithmeticType() const /// standard 13.6.2
    {
        return asFloatingPointType() OR isPromotedIntegralType();
    }

    inline bool             isPromotedIntegralType() const  /// standard 13.6.2
    {
        return asIntegralType() AND promote() == const_cast<Type*>(this);
    }

    virtual uint            getDataPointerLevel() const { return 0; }

    Scope*                  getScope() const;
    void                    removeFromScope();

    Type*                   getOwnerType() const;
    
    size_t                  getExtendedTypeCount() const
    {
        return m_pExtendedTypes == NULL ? 0 : m_pExtendedTypes->size();
    }

    Type*                   getExtendedType(size_t index) const
    {
        o_assert(index < getExtendedTypeCount());
        return (*m_pExtendedTypes)[index];
    }

    Type*                   getCommonAncestor(Type* a_pType) const;

    DataPointerType*        getDataPointerType() const;
    LValueReferenceType*    getLValueReferenceType() const;
    RValueReferenceType*    getRValueReferenceType() const;
    ArrayType*              getArrayType(size_t a_uiCount) const;
    ConstType*              getConstType() const;
    VolatileType*           getVolatileType() const;
    ConstVolatileType*      getConstVolatileType() const;

    Type*                   pointerType(size_t a_uiPointerLevel) const;
    DataPointerType*        pointerType() const;
    LValueReferenceType*    lvalueReferenceType() const;
    RValueReferenceType*    rvalueReferenceType() const;
    ArrayType*              arrayType(size_t a_uiCount) const;
    ConstType*              constType() const;
    VolatileType*           volatileType() const;
    ConstVolatileType*      constVolatileType() const;

    TemplateSpecialization* getTemplateSpecialization() const { return m_pOwner ? m_pOwner->asTemplateSpecialization() : nullptr; }
    Template*               getTemplate() const;

    virtual int             getPointerCastOffset(Type* a_pType) const { return equals(a_pType) ? 0 : o_invalid_offset; }

    virtual bool            partialAccepts(LanguageElement* a_pLanguageElement, size_t& a_Score, map<Placeholder*, LanguageElement*>& a_Deductions) const;
    virtual bool            partialAccepts(Type* a_pType, size_t& a_Score, map<Placeholder*, LanguageElement*>& a_Deductions) const;

protected:
    virtual void            elementRemoved(LanguageElement* a_pElement);
    virtual DataPointerType*createDataPointerType() const;
    virtual LValueReferenceType*  createLValueReferenceType() const;
    virtual RValueReferenceType* createRValueReferenceType() const;
    virtual ArrayType*      createArrayType(size_t a_uiCount) const;
    virtual ConstType*      createConstType() const;
    virtual VolatileType*   createVolatileType() const;
    virtual ConstVolatileType* createConstVolatileType() const;
    void                    removeExtendedType(Type* a_pType);
    
    virtual void            referencedElementRemoved(LanguageElement* a_pElement);

    virtual void            setOwnerByQualifiedDecoratedName(string a_Owner);
    /**
     *  @name Signals
     */
     //@{  
#if o__bool__use_kind_creation_signal
public:
    virtual void        fireKindCreated(void* a_pObject);
protected:
    connection::slot::list        PHANTOM_CODEGEN_m_slot_list_of_kindCreated;
    signal_t            kindCreated(void* a_pObject);
#endif

#if o__bool__use_kind_destruction_signal
public:
    virtual void        fireKindDestroyed(void* a_pObject);
protected:
    connection::slot::list        PHANTOM_CODEGEN_m_slot_list_of_kindDestroyed;
    signal_t            kindDestroyed(void* a_pObject);
#endif

    //@}
protected:
    ETypeId         m_eTypeId;
    mutable vector<Type*>* m_pExtendedTypes;
    size_t          m_uiBuildOrder;
    ushort          m_uiSize;
    ushort          m_uiAlignment;
    ushort          m_uiSerializedSize;
    ushort          m_uiResetSize;

private:
    static size_t NextBuildOrderValue() { static size_t s_NextBuildOrderValue = 0; return s_NextBuildOrderValue++; }
};

o_namespace_end(phantom, reflection)



#endif
