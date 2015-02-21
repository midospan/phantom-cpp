/* TODO LICENCE HERE */

#ifndef o_phantom_reflection_ClassType_h__
#define o_phantom_reflection_ClassType_h__

/* ****************** Includes ******************* */

/* **************** Declarations ***************** */

/* *********************************************** */

o_namespace_begin(phantom, reflection)
    
class o_export ClassType : public Type, public Scope
{
    o_type;

    o_declare_meta_type(ClassType);

public:
    struct extra_data
    {
        enum EState
        {
            e_State_NotCompiled = 0,
            e_State_MemberSetup = 100,
            e_State_Finalized = 150,
            e_State_Compiling = 200,
            e_State_Compiled = 300,
            e_State_Linked = 300,
        };

        extra_data()
            : m_uiDataMemberMemoryOffset(0)
            , m_uiAlignmentFixingOffset(0)
            , m_uiDataTypeCount(0)
            , m_iState(e_State_NotCompiled)
            , m_AccessSpecifier(0)
        {

        }
        virtual ~extra_data() {}

        vector<Type*>                   m_DataMemberTypes;
        size_t                          m_uiDataMemberMemoryOffset;
        size_t                          m_uiAlignmentFixingOffset;
        Type::alignment::computer       m_AlignmentComputer;
        size_t                          m_uiDataTypeCount;
        modifiers_t                     m_AccessSpecifier;
        int                             m_iState;
    };

    static ClassType* Invalid();

protected:
    ClassType(ETypeId a_eTypeId, extra_data* a_pExtraData, modifiers_t a_Modifiers = 0);
    ClassType(ETypeId a_eTypeId, extra_data* a_pExtraData, const string& a_strName, modifiers_t a_Modifiers = 0);
    ClassType(ETypeId a_eTypeId, const string& a_strName, ushort a_uiSize, ushort a_uiAlignment, modifiers_t a_Modifiers = 0);

public:
    o_restore(filter,pass);

    o_destructor ~ClassType(void);

    virtual bool            isDefined() const { o_assert(m_pExtraData); return m_pExtraData->m_iState >= extra_data::e_State_Compiled; }

    virtual void            destroyContent();

    virtual bool            isDefaultInstanciable() const;

    virtual bool            isDefaultConstructible() const { return Type::isDefaultConstructible() AND getConstructor(m_strName+"()") != nullptr; }

    virtual ClassType*      asClassType() const { return const_cast<ClassType*>(this); }
    virtual Scope*          asScope() const { return const_cast<ClassType*>(this); }

    void                    setDefaultAccess(modifiers_t modifier);

    modifiers_t             getDefaultAccess() const { o_assert(m_pExtraData); return m_pExtraData->m_AccessSpecifier; }

    virtual void            addConstructor( Constructor* a_pConstructor );
    virtual Constructor*    addConstructor( const string& a_strSignature );
    virtual void            addValueMember( ValueMember* a_pValueMember );
    virtual void            addStaticDataMember( StaticDataMember* a_pDataMember );
    virtual void            addDataMember( DataMember* a_pDataMember );
    virtual void            addProperty( Property* a_pProperty );
    virtual Property*       addProperty( const string& a_strName, uint a_uiSerializationMask = o_save_state );
    virtual void            addMemberFunction(MemberFunction* a_MetaMemberFunction);
    virtual void            addStaticMemberFunction(StaticMemberFunction* a_MetaMemberFunction);
    virtual Subroutine*     addSubroutine(const string& a_strCode);
    virtual void            addSubroutine(Subroutine* a_pSubroutine);

    virtual void            removeConstructor( Constructor* a_pConstructor );
    virtual void            removeValueMember( ValueMember* a_pValueMember );
    virtual void            removeStaticDataMember( StaticDataMember* a_pDataMember );
    virtual void            removeDataMember( DataMember* a_pDataMember );
    virtual void            removeProperty( Property* a_pProperty );
    virtual void            removeMemberFunction(MemberFunction* a_MetaMemberFunction);
    virtual void            removeStaticMemberFunction(StaticMemberFunction* a_MetaMemberFunction);

    Constructor*            getDefaultConstructor(modifiers_t a_Modifiers = 0) const;
    Constructor*            getCopyConstructor(modifiers_t a_Modifiers = 0) const;
    Constructor*            getConstructor( const vector<Type*>& a_Types, modifiers_t a_Modifiers = 0 ) const;
    Constructor*            getConstructor( const string& a_strDecoratedName ) const;
    ValueMember*            getValueMember(const string& a_strName) const;
    size_t                  getValueMemberCount() const;
    DataMember*             getDataMember(const string& a_strName) const;
    virtual DataMember*     getDataMemberByOffset(size_t a_uiOffset) const;
    DataMember*             getDataMemberAtAddress(const void* a_pBase, const void* a_pAddress) const;
    StaticDataMember*       getStaticDataMember(const string& a_strName) const;
    Property*               getProperty(const string& a_strName) const;
    Subroutine*             getSubroutine(const string& a_strDecoratedName) const;
    virtual Subroutine*     getSubroutine(const string& a_strName, const vector<Type*>& a_Types, modifiers_t a_Qualifiers = 0) const;
    MemberFunction*         getMemberFunction(const string& a_strDecoratedName) const;
    MemberFunction*         getMemberFunction(const string& a_strName, const vector<Type*>& a_Types, modifiers_t a_Qualifiers = 0) const;
    size_t                  getMemberFunctionCount() const;
    StaticMemberFunction*   getStaticMemberFunction( const string& a_strDecoratedName ) const;
    StaticMemberFunction*   getStaticMemberFunction( const string& a_strName, const vector<Type*>& a_Types ) const;
    size_t                  getStaticMemberFunctionCount() const;

    MemberFunction* getUniqueMemberFunctionWithName(const string& a_strName) const;

    void                    findPublicValueMembersPointingValueType(Type* a_pType, vector<ValueMember*>& out) const;

    vector<ValueMember*>::const_iterator            beginValueMembers() const { return m_ValueMembers.begin(); }
    vector<ValueMember*>::const_iterator            endValueMembers() const { return m_ValueMembers.end(); }
    vector<DataMember*>::const_iterator             beginDataMembers() const { return m_DataMembers.begin(); }
    vector<DataMember*>::const_iterator             endDataMembers() const { return m_DataMembers.end(); }
    vector<StaticDataMember*>::const_iterator       beginStaticDataMembers() const;
    vector<StaticDataMember*>::const_iterator       endStaticDataMembers() const;
    vector<MemberFunction*>::const_iterator         beginMemberFunctions() const { return m_MemberFunctions.begin(); }
    vector<MemberFunction*>::const_iterator         endMemberFunctions() const { return m_MemberFunctions.end(); }
    vector<StaticMemberFunction*>::const_iterator   beginStaticMemberFunctions() const;
    vector<StaticMemberFunction*>::const_iterator   endStaticMemberFunctions() const;
    vector<Property*>::const_iterator               beginProperties() const { return m_Properties.begin(); }
    vector<Property*>::const_iterator               endProperties() const { return m_Properties.end(); }
    vector<Constructor*>::const_iterator            beginConstructors() const;
    vector<Constructor*>::const_iterator            endConstructors() const;
    void                                            getMembers( vector<LanguageElement*>& out ) const;

    bool                                            matchesTemplateArguments( const vector<LanguageElement*>& a_Elements ) const;

    virtual void                                    addMemberAnonymousSection(MemberAnonymousSection* a_pMemberAnonymousSection);
    virtual MemberAnonymousSection*                 addMemberAnonymousSection(const string& a_strCode, modifiers_t a_Modifiers = 0);
    virtual void                                    removeMemberAnonymousSection( MemberAnonymousSection* a_pMemberAnonymousSection );
    MemberAnonymousSection*                         getMemberAnonymousSection(size_t a_uiIndex) const;
    size_t                                          getMemberAnonymousSectionCount() const;
    vector<MemberAnonymousSection*>::const_iterator beginMemberAnonymousSections() const;
    vector<MemberAnonymousSection*>::const_iterator endMemberAnonymousSections() const;
    vector<MemberAnonymousSection*>                 getMemberAnonymousSections() const { return m_pMemberAnonymousSections ? *m_pMemberAnonymousSections : vector<MemberAnonymousSection*>(); }

    virtual void                    construct(void* a_pInstance) const;
    virtual void                    destroy(void* a_pInstance) const;

    virtual void*                   newInstance() const;

    virtual void*                   newInstance(Constructor* a_pConstructor, void** a_pArgs = NULL) const;
    virtual void                    deleteInstance(void* a_pObject) const;
    virtual void                    safeDeleteInstance(void* a_pObject) const { deleteInstance(a_pObject); }

    virtual void                    interpolate(void* a_src_start, void* a_src_end, real a_fPercent, void* a_pDest, uint mode = 0) const;
    virtual void                    valueFromString( const string& cs, void* dest ) const;
    virtual void                    valueToString( string& s, const void* src ) const;

    virtual void                    smartCopy(reflection::Type* a_pDestType, void* a_pDest, void const* a_pSrc) const;

    virtual bool                    referencesData(const void* a_pInstance, const phantom::data& a_Data) const;
    virtual void                    fetchExpressions(Expression* a_pInstanceExpression, vector<Expression*>& out, filter a_Filter, uint a_uiSerializationMask) const;

    virtual void                    getElements( vector<LanguageElement*>& out, Class* a_pClass = nullptr) const;

    // Attributes
    void                            addAttribute(const string& a_strName, const variant& a_Variant);
    void                            removeAttribute( const string& a_strName );
    const variant&                  getAttribute(const string& a_strName) const;

    MemberFunction*                 getDestructor() const;

    const extra_data*               getExtraData() const { return m_pExtraData; }

    virtual bool                    acceptsSubroutine( Type* a_pReturnType, const string& a_strName, const vector<Type*>& a_Types, modifiers_t a_Modifiers, vector<Subroutine*>* a_pOutConflictingSubroutines = nullptr ) const;

    Template*                       getTemplate() const;

    virtual bool                    isTemplateInstance() const { return getTemplateSpecialization( )!= NULL; }

    TemplateSpecialization*         getTemplateSpecialization() const { return m_pOwner ? m_pOwner->asTemplateSpecialization() : nullptr; }

    string                          getDecoration() const;
    virtual string                  getQualifiedDecoratedName() const;
    virtual string                  getDecoratedName() const;

    MemberFunctionPointerType*      memberFunctionPointerType( Type* a_pReturnType, const vector<Type*>& a_ParameterTypes, modifiers_t a_RefQualifiers);
    DataMemberPointerType*          dataMemberPointerType( Type* a_pValueType );

    void                            addFriend(LanguageElement* a_pFriend);
    bool                            hasFriend(LanguageElement* a_pFriend) const;

    virtual void                    finalize();
    virtual void                    checkCompleteness() const;

protected:
    virtual void                    referencedElementRemoved(LanguageElement* a_pElement);

    bool                            canBeDestroyed() const;
    void                            elementRemoved(LanguageElement* a_pElement);
    virtual Constructor*            createDefaultConstructor() const;
    virtual Constructor*            createDefaultCopyConstructor() const;
    virtual MemberFunction*         createDestructor() const;

    vector<Constructor*>            getConstructors() const { return m_pConstructors ? *m_pConstructors : vector<Constructor*>(); }
    vector<Property*>               getProperties() const { return m_Properties; }
    vector<DataMember*>             getDataMembers() const { return m_DataMembers; }
    vector<MemberFunction*>         getMemberFunctions() const { return m_MemberFunctions; }

    virtual void                    setConstructors(vector<Constructor*> list);
    virtual void                    setProperties(vector<Property*> list);
    virtual void                    setDataMembers(vector<DataMember*> list);
    virtual void                    setMemberFunctions(vector<MemberFunction*> list);
    virtual void                    addScopeElement(NamedElement* a_pElement) { addElement(a_pElement); }
    virtual void                    removeScopeElement(NamedElement* a_pElement) { removeElement(a_pElement); }

protected:
    o_signal_data(dataMemberAdded, DataMember*);
    o_signal_data(dataMemberRemoved, DataMember*);
    o_signal_data(constructorAdded, Constructor*);
    o_signal_data(constructorRemoved, Constructor*);
    o_signal_data(memberFunctionAdded, MemberFunction*);
    o_signal_data(memberFunctionRemoved, MemberFunction*);
    o_signal_data(propertyAdded, Property*);
    o_signal_data(propertyRemoved, Property*);
    o_signal_data(memberAnonymousSectionAdded, MemberAnonymousSection*);
    o_signal_data(memberAnonymousSectionRemoved, MemberAnonymousSection*);

protected:
    vector<ValueMember*>            m_ValueMembers;
    vector<Property*>               m_Properties;
    vector<DataMember*>             m_DataMembers;
    vector<MemberFunction*>         m_MemberFunctions;
    vector<MemberAnonymousSection*>*m_pMemberAnonymousSections;
    vector<MemberFunctionPointerType*>* m_pMemberFunctionPointerTypes;
    vector<DataMemberPointerType*>* m_pDataMemberPointerType;
    vector<LanguageElement*>*       m_pFriends;
    
    // less frequent => use vector ptrs
    vector<Constructor*>*           m_pConstructors;
    extra_data*                     m_pExtraData;

    void*                           m_pAttributes; // use pimpl to avoid need to include variant type
};

o_namespace_end(phantom, reflection)



#endif
