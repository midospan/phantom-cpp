/* TODO LICENCE HERE */

#ifndef o_phantom_reflection_Class_h__
#define o_phantom_reflection_Class_h__


/* ****************** Includes ******************* */


/* **************** Declarations ***************** */
/* *********************************************** */
o_namespace_begin(phantom, reflection)


class o_export Class : public ClassType
{
    o_type;

    o_declare_meta_type(Class);

public:
    friend class phantom::Phantom;
    friend class phantom::reflection::Namespace;

    template<typename t_Ty>
    friend class phantom::reflection::native::TNativeStateMachine;

    template<typename t_Ty, bool t_value>
    friend class phantom::reflection::native::TNativeStateMachineHelper;

    template<typename t_Ty, typename t_STy> friend struct detail::base_class_adder;

    template<typename t_Ty, int t_default_installer_id>
    friend struct phantom::detail::default_installer_helper;

    template<typename t_Ty, int t_default_initializer_id>
    friend struct phantom::detail::default_initializer_helper;

protected:
    struct extra_data : ClassType::extra_data
    {
        extra_data() 
            : m_uiClassPtrOffset(0)
            , m_uiBaseSize(0)
            , m_uiStateMachineDataPtrOffset(0)
            , m_bHasVTablePtr(false)
            , m_bHasStateMachineDataPtr(false)
            , m_pInitializeClosure(0)
            , m_pRestoreClosure(0)
            , m_pTerminateClosure(0)
        {

        }
        void*                   m_pInitializeClosure;
        void*                   m_pRestoreClosure;
        void*                   m_pTerminateClosure;
        closure_call_delegate   m_ClosureCallDelegate;
        size_t                  m_uiDataMemberMemoryOffset;
        size_t                  m_uiClassPtrOffset;
        size_t                  m_uiBaseSize;
        size_t                  m_uiStateMachineDataPtrOffset;
        bool                    m_bHasVTablePtr;
        bool                    m_bHasStateMachineDataPtr;
    };

protected:
    typedef phantom::vector<Class*>                    class_vector; 
    struct base_class_data
    {
        base_class_data() {}
        base_class_data(Class* s, size_t o, modifiers_t m = o_public_access) : m_pClass(s), m_uiOffset(o), m_Access(m) {}
        modifiers_t m_Access;
        Class*      m_pClass;
        size_t      m_uiOffset;
        operator Class* () const
        {
            return m_pClass;
        }
    };
    typedef phantom::vector<base_class_data>        base_class_table;
    typedef phantom::vector<VirtualMemberFunctionTable*>    vmt_vector;
    typedef phantom::vector<std::pair<size_t, string> > saveable_base_class_table;

public:
    class member_function_search_data
    {
    public:
        enum EResultType
        {
            eResultType_None = 0,
            eResultType_IncompatibleParameterType,
            eResultType_IncompatibleParameterCount,
            eResultType_IncompatibleReturnType,
            eResultType_CovariantMatch,
            eResultType_ContravariantMatch,
            eResultType_PerfectMatch,
        };
        typedef phantom::map<EResultType, vector<Subroutine*> >    result_map;

        member_function_search_data(void) : m_pMemberFunctionSignature(NULL)
        {

        }

        void populateRequest(const string& a_strMemberFunctionName, Signature* a_pMemberFunctionSignature)
        {
            m_strMemberFunctionName = a_strMemberFunctionName;
            m_pMemberFunctionSignature = a_pMemberFunctionSignature;
        }


        vector<Subroutine*>::const_iterator getResultBegin(EResultType a_eResultType) const
        {
            return m_ResultMap.find(a_eResultType)->second.begin();
        }
        vector<Subroutine*>::const_iterator getResultEnd(EResultType a_eResultType) const
        {
            return m_ResultMap.find(a_eResultType)->second.end();
        }

        Signature* getMemberFunctionSignature() const { return m_pMemberFunctionSignature; }
        const string& getMemberFunctionName() const { return m_strMemberFunctionName; }

        o_destructor ~member_function_search_data(void)     {}

        bool containsResult() const {return NOT(m_ResultMap.empty()); }

        uint countResults(EResultType a_eResultType)
        {
            result_map::iterator it = m_ResultMap.find(a_eResultType);
            return it != m_ResultMap.end()?it->second.size():0;
        }

        bool isFound(EResultType a_eResultType)
        {
            result_map::iterator it = m_ResultMap.find(a_eResultType);
            return it != m_ResultMap.end() AND NOT(it->second.empty());
        }
        void clear()
        {
            m_ResultMap.clear();
        }

        void populateWithResult(EResultType a_eResult, Subroutine* a_pMemberFunction)
        {
            m_ResultMap[a_eResult].push_back(a_pMemberFunction);
        }

    protected:
        string            m_strMemberFunctionName;
        Signature*        m_pMemberFunctionSignature;
        result_map        m_ResultMap;
    };

    // Creates an empty class
    Class();
    Class(const string& a_strName, modifiers_t a_Modifiers = 0);

protected: // Reserved to native class derivation
    Class(const string& a_strName, ushort a_uiSize, ushort a_uiAlignment, modifiers_t a_Modifiers = 0);

public:
    ~Class(void);

    o_terminate();

    /**
     * \fn virtual void Class::valueToString( string& s, void* src) const;
     *
     * \brief Reimplementation of \ref Type::valueToString.
     *
     */

    virtual void        valueToString( string& s, const void* src) const;

    /**
     * \fn virtual void Class::valueFromString( const string& cs, void* dest) const;
     *
     * \brief Value from string.
     *
     * \param   cs           The create struct.
     * \param [in,out]  dest If non-null, destination for the.
     */

    virtual void        valueFromString( const string& cs, void* dest) const;

    /**
     * \fn  void Class::filtersNonOverloadedPureVirtualMemberFunctionsCascade(instance_member_function_vector& a_Result) const;
     *
     * \brief Keep only non overloaded abstract member_functions cascade.
     *
     * \param [in,out]  a_pOutList If non-null, vector passed is filetered to keep only to abstract member_functions that haven't been overloaded, recursively through all the base classes.
     */

    void                filtersNonOverloadedPureVirtualMemberFunctionsCascade(vector<MemberFunction*>& a_Result) const;

    /**
     * \fn void Class::findPureVirtualMemberFunctions(instance_member_function_vector* a_pOutList) const;
     *
     * \brief Filters the vector passed as argument and keeps only inside the abstract member_functions that haven't been overloaded recursively in all the base classes.
     *
     * \param [out]  a_pOutList If non-null, vector filtered.
     */

    void                findPureVirtualMemberFunctions(vector<MemberFunction*>& a_Result) const;

    /**
     * \fn Subroutine* Class::getMemberFunctionCascade(const string& a_strIdentifierString) const;
     *
     * \brief Gets a member_function (static or instance one) recursively through all the base classes.
     *
     * \param   a_strIdentifierString The identifier string (ex: \"member_function(int)" ).
     *
     * \return NULL if it fails, else the member_function.
     */

    Subroutine*             getSubroutineCascade(const string& a_strIdentifierString) const;

    Subroutine*             getSubroutineCascade(const string& a_strName, const vector<Type*>& a_FunctionSignature, modifiers_t a_Modifiers = 0) const;

    /**
     * \fn void Class::getAllMemberCascade(vector<LanguageElement*>&) const;
     *
     * \brief Gets all members recursively through all the base classes.
     *
     * \param [in,out]  a_out a vector to store the result across recursive calls.
     */

    void                getMembersCascade(vector<LanguageElement*>& out) const;

    /**
     * \fn void Class::getValueMembersCascade(vector<ValueMember*>&) const;
     *
     * \brief Gets all valueMembers recursively through all the base classes.
     *
     * \param [in,out]  out a vector to store the result across recursive calls.
     */
    void                getValueMembersCascade(vector<ValueMember*>& out) const;
    
    /**
     * \fn MemberFunction* Class::findOverriddenMemberFunctions(MemberFunction* a_pOverloadMemberFunction, vector<MemberFunction*>& a_Result);
     *
     * \brief Gets a base instance member_function.
     *
     * \param [in,out]  a_pOverloadMemberFunction The overloaded member_function (must be non-NULL).
     * 					a_Result The vector containing the result
     *
     */

    void     findOverriddenMemberFunctions( MemberFunction* a_pOverloadedMemberFunction, vector<MemberFunction*>& a_Result );

    /**
     * \fn MemberFunction* Class::getMemberFunctionCascade(const string& a_strIdentifierString) const;
     *
     * \brief Gets an instance member_function recursively through all the base classes.
     *
     * \param   a_strIdentifierString The identifier string (ex: \"member_function(int)\").
     *
     * \return null if it fails, else the instance member_function cascade.
     */

    MemberFunction*     getMemberFunctionCascade(const string& a_strIdentifierString) const;

    /**
     * \fn  MemberFunction* Class::getMemberFunctionCascade(const char* a_strName,
     *      LanguageElement** a_pParameterTypes, size_t a_uiParameterCount,
     *      modifiers_t a_Modifiers = 0) const;
     *
     * \brief Gets an instance member_function recursively through all the base classes.
     *
     * \param   a_strName                 The name.
     * \param [in,out]  a_pParameterTypes If non-null, list of the parameters' types.
     * \param   a_uiParameterCount        Number of parameters.
     * \param   a_Modifiers             (optional) member_function's modifiers (ex: o_const).
     *
     * \return null if it fails, else the instance member_function cascade.
     */

    MemberFunction*     getMemberFunctionCascade(const char* a_strName, const vector<Type*>& a_FunctionSignature, modifiers_t a_Modifiers = 0) const;

    /**
     * \fn ValueMember* Class::getValueMemberCascade(const string& a_strValueMemberName) const;
     *
     * \brief Gets a valueMember recursively through all the base classes.
     *
     * \param   a_strValueMemberName The valueMember name.
     *
     * \return null if it fails, else the valueMember.
     */

    ValueMember*           getValueMemberCascade(const string& a_strValueMemberName) const;


    void findPublicValueMembersPointingValueTypeCascade(Type* a_pType, vector<ValueMember*>& out) const
    {
        o_foreach(Class* pClass, m_BaseClasses)
        {
            pClass->findPublicValueMembersPointingValueTypeCascade(a_pType, out);
        }
        findPublicValueMembersPointingValueType(a_pType, out);
    }

    /**
     * \fn DataMember* Class::getDataMemberCascade(const string& a_strName) const;
     *
     * \brief Gets an instance dataMember recursively through all the base classes.
     *
     * \param   a_strDataMemberName The instance dataMember name.
     *
     * \return null if it fails, else the instance dataMember.
     */

    DataMember*  getDataMemberCascade(const string& a_strDataMemberName) const;

    /**
     * \fn DataMember* Class::getDataMemberCascade(const string& a_strName) const;
     *
     * \brief Gets an instance dataMember recursively through all the base classes.
     *
     * \param   a_strDataMemberName The instance dataMember name.
     *
     * \return null if it fails, else the instance dataMember.
     */

    virtual DataMember*  getDataMemberByOffset(size_t a_uiOffset) const;
    
    /**
     * \fn Property* Class::getPropertyCascade(const string& a_strPropertyName) const;
     *
     * \brief Gets a property recursively through all the base classes.
     *
     * \param   a_strPropertyName The instance dataMember name.
     *
     * \return null if it fails, else the instance dataMember.
     */

    Property*  getPropertyCascade(const string& a_strPropertyName) const;
    
    /**
     * \fn  StaticMemberFunction* Class::getStaticMemberFunctionCascade(const char* a_strName,
     *      const vector<Type*>* a_FunctionSignature, size_t a_uiParameterCount,
     *      modifiers_t a_Modifiers = 0) const;
     *
     * \brief Gets an instance member_function recursively through all the base classes.
     *
     * \param   a_strName                 The name.
     * \param [in,out]  a_pParameterTypes If non-null, list of the parameters' types.
     * \param   a_uiParameterCount        Number of parameters.
     * \param   a_Modifiers             (optional) member_function's modifiers (ex: o_const).
     *
     * \return null if it fails, else the instance member_function cascade.²
     */

    StaticMemberFunction*     getStaticMemberFunctionCascade(const string& a_strName, const vector<Type*>& a_FunctionSignature) const;
    /**
     * \fn StaticDataMember* Class::getStaticDataMemberCascade(const string& a_strName) const;
     *
     * \brief Gets a static dataMember recursively through all the base classes.
     *
     * \param   a_strName The static dataMember name.
     *
     * \return null if it fails, else the static dataMember.
     */

    StaticDataMember*    getStaticDataMemberCascade(const string& a_strStaticDataMemberName) const;

    /**
     * \fn StaticMemberFunction* Class::getStaticMemberFunctionCascade( const string& a_strIdentifierString ) const;
     *
     * \brief Gets a static member_function recursively through all the base classes.
     *
     * \param   a_strIdentifierString The identifier string.
     *
     * \return null if it fails, else the static member_function.
     */

    StaticMemberFunction*       getStaticMemberFunctionCascade( const string& a_strIdentifierString ) const;

    /**
     * \fn virtual bool Class::asClass() const
     *
     * \brief Reimplemented
     */

    virtual Class*      asClass() const { return const_cast<Class*>(this); }

    /**
     * \fn inline uint Class::getVirtualMemberFunctionTableCount() const;
     *
     * \brief Gets the virtual member_function table count.
     *
     * \return The virtual member_function table count.
     */

    inline size_t         getVirtualMemberFunctionTableCount() const;

    /**
     * \fn VirtualMemberFunctionTable* Class::getVirtualMemberFunctionTable(uint i) const;
     *
     * \brief Gets a virtual member_function table.
     *
     * \param   i Zero-based index of the.
     *
     * \return the virtual member_function table at i.
     */

    inline VirtualMemberFunctionTable* getVirtualMemberFunctionTable(size_t i) const;

    /**
     * \fn uint Class::getVirtualMemberFunctionTableSize(uint a_uiIndex) const
     *
     * \brief Gets the size of the virtual member_function table at i.
     *
     * \param   a_uiIndex Zero-based index.
     *
     * \return The size.
     */

    size_t                      getVirtualMemberFunctionTableSize(size_t a_uiIndex) const    { return getVirtualMemberFunctionTable(a_uiIndex)->getMemberFunctionCount();    }

    /**
     * \fn MemberFunction** Class::getVirtualMemberFunctionTableData(uint a_uiIndex) const
     *
     * \brief Gets the data (an array of MemberFunction) of the virtual member_function table data.
     *
     * \param   a_uiIndex Zero-based index.
     *
     * \return the virtual member_function table data as an MemberFunction* array.
     */

    virtual bool                acceptsSubroutine(Type* a_pReturnType, const string& a_strName, const vector<Type*>& a_Types, modifiers_t a_Modifiers, vector<Subroutine*>* a_pOutConflictingMemberFunctions = NULL) const;
    virtual bool                acceptsOverrideMemberFunction(Type* a_pReturnType, const string& a_strName, const vector<Type*>& a_Types, modifiers_t a_Modifiers, vector<Subroutine*>* a_pOutConflictingMemberFunctions) const;

    inline Class*               getBaseClass(size_t index) const    { return m_BaseClasses[index];    }

    inline void*                baseClassCast(void* a_pInstance, size_t index) const { return (((byte*)a_pInstance)+m_BaseClasses[index].m_uiOffset); }
    inline const void*          baseClassCast(const void* a_pInstance, size_t index) const { return (((const byte*)a_pInstance)+m_BaseClasses[index].m_uiOffset); }

    size_t                      getInheritanceLevel(size_t i) const;

    size_t                      getInheritanceLevelFromBase(Class* a_pClass) const;

    virtual bool                hasPublicMember(NamedElement* a_pLanguageElement) const;
    virtual bool                hasProtectedMember(NamedElement* a_pLanguageElement) const;
    virtual bool                hasPrivateMember(NamedElement* a_pLanguageElement) const;

    base_class_table::const_iterator beginBaseClasses() const { return m_BaseClasses.begin(); }
    base_class_table::const_iterator endBaseClasses() const { return m_BaseClasses.end(); } 
    
    vector<VirtualMemberFunctionTable*>::const_iterator beginVirtualMemberFunctionsTables() const { return m_VirtualMemberFunctionTables.begin(); }
    vector<VirtualMemberFunctionTable*>::const_iterator endVirtualMemberFunctionsTables() const { return m_VirtualMemberFunctionTables.end(); }

    vector<Signal*>::const_iterator beginSignals() const;
    vector<Signal*>::const_iterator endSignals() const;

    virtual void        addBaseClass(Class* a_pClass);

    const 
    base_class_table&   getBaseClasses() const { return m_BaseClasses; }
    modifiers_t         getBaseClassAccess(Class* a_pClass) const;
    modifiers_t         getBaseClassAccessCascade( Class* a_pClass ) const;
    uint                getBaseClassCount(void) const { return m_BaseClasses.size(); }
    bool                hasBaseClass( Class* a_pClass, modifiers_t* a_pInheritanceAccess = 0 ) const;
    bool                hasBaseClassCascade( Class* a_pClass ) const;

    Class*              getDerivedClass(uint a_uiIndex) const { return m_DerivedClasses[a_uiIndex]; }
    uint                getDerivedClassCount(void) const { return m_DerivedClasses.size(); }
    void                getDerivedClasses(vector<Class*>& out) const;
    void                getDerivedClassesCascade(vector<Class*>& out) const;
    bool                hasDerivedClass( Class* a_pClass, modifiers_t* a_pDerivedAccess = 0 ) const;
    bool                hasDerivedClassCascade(Class* a_pClass, modifiers_t* a_pDerivedAccess = 0 ) const;

    bool                hasAccessTo( NamedElement* a_pOther, NamedElement* a_pAccessContext = nullptr ) const;

    void                homonymousMemberFunctionSearch( member_function_search_data* a_pMemberFunctionRequest );
    void                sortBaseAndRootMemberFunctions( VirtualMemberFunctionTable* a_pBaseVMT, vector<MemberFunction*>* a_OutBaseMemberFunctions, vector<MemberFunction*>* a_OutRootMemberFunctions ) const;

    o_forceinline int   getBaseClassOffset(size_t a_uiClassIndex) const
    {
        return m_BaseClasses[a_uiClassIndex].m_uiOffset;
    }
    inline size_t       getBaseClassOffset(Class* a_pBaseType) const;
    inline size_t       getBaseClassOffsetCascade(Class* a_pBaseType) const;
    virtual int         getPointerCastOffset(Type* a_pType) const;
    int                 getPointerCastOffset(Class* a_pClass) const;
    bool                isRootClass() const { return m_BaseClasses.empty(); }

    virtual bool        isKindOf( Class* a_pType ) const;
    virtual bool        isKindOf( Type* a_pType ) const { return a_pType->asClass() ? isKindOf(static_cast<Class*>(a_pType)) : false; }
    virtual ERelation   getRelationWith(Type* a_pType) const;
    bool                doesInstanceDependOn(void* a_pInstance, void* a_pOther) const;
    
    virtual void        setClass(void* a_pInstance, void* a_pClass) const    { throw exception::unsupported_member_function_exception("this member_function must be overloaded in specialized subclasses which support it"); }
    virtual void        setStateMachineData(void* a_pInstance, void* a_pSmdataptr) const { throw exception::unsupported_member_function_exception("this member_function must be overloaded in specialized subclasses which support it"); }
  
    virtual void        addMemberFunction(MemberFunction* a_pMemberFunction);

    virtual void        addSignal(Signal* a_pSignal);
    virtual void        removeSignal( Signal* a_pSignal );
    Signal*             getSignal(const string& a_strIdentifierString) const;
    Signal*             getSignalCascade(const string& a_strIdentifierString) const;
    MemberFunction*     getSlot(const string& a_strIdentifierString) const;
    MemberFunction*     getSlotCascade(const string& a_strIdentifierString) const;

    StateMachine*       getStateMachine() const;
    StateMachine*       getStateMachineCascade() const;

    virtual bool        isPolymorphic() const;

    void                initializeDataMembers(void* a_pInstance) const;
    void                initializeDataMembersCascade(void* a_pInstance) const;
    void                terminateDataMembers(void* a_pInstance) const;
    void                terminateDataMembersCascade(void* a_pInstance) const;
    restore_state       restoreDataMembers( void* a_pInstance, uint a_uiSerializationFlag, restore_pass a_uiPass ) const;
    restore_state       restoreDataMembersCascade( void* a_pInstance, uint a_uiSerializationFlag, restore_pass a_uiPass ) const;

    void                installDataMembers(void* a_pInstance, const rtti_data* a_pOwner) const;
    void                uninstallDataMembers(void* a_pInstance, size_t a_uiLevel) const;
    void                installDataMembersCascade(void* a_pInstance, const rtti_data* a_pOwner) const;
    void                uninstallDataMembersCascade(void* a_pInstance, size_t a_uiLevel) const;

    // Construct               

    static void         installRTTI(Class* a_pLayoutClass, void* a_pLayout, Class* a_pBaseClass, void* a_pBase, connection::slot_pool* sp, const rtti_data* a_pOwner, const rtti_data* a_pRTTI);
    static void         uninstallRTTI(void* a_pLayout, Class* a_pLayoutClass, size_t a_uiLevel, bool a_bRemoveRTTI);

    virtual void        initialize( void* a_pInstance ) const;
    virtual void        initialize(void* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize ) const { ClassType::initialize(a_pChunk, a_uiCount, a_uiChunkSectionSize); }
    virtual void        terminate( void* a_pInstance ) const;
    virtual void        terminate(void* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize ) const { ClassType::terminate(a_pChunk, a_uiCount, a_uiChunkSectionSize); ; }
    virtual void        install( void* a_pInstance, const rtti_data* a_pOwner = 0 ) const;
    virtual void        install(void* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, const rtti_data* a_pOwner = 0 ) const { ClassType::install(a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pOwner); }
    virtual void        uninstall( void* a_pInstance, size_t a_uiLevel = 0) const;
    virtual void        uninstall(void* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, size_t a_uiLevel = 0 ) const { ClassType::uninstall(a_pChunk, a_uiCount, a_uiChunkSectionSize, a_uiLevel); ; }

    virtual 
        restore_state   restore(void* a_pInstance, uint a_uiSerializationFlag, restore_pass a_uiPass) const;

    virtual size_t      getVirtualMemberFunctionCount(size_t a_uiOffset) const;

    virtual void*       allocate() const;
    virtual void        deallocate(void* a_pInstance) const;
    virtual void*       allocate(size_t a_uiCount) const;
    virtual void        deallocate(void* a_pInstance, size_t a_uiCount) const;
    virtual void        construct(void* a_pObject) const;
    virtual void        destroy(void* a_pObject) const;
    virtual void        construct(void* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize) const;
    virtual void        destroy(void* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize) const;

    virtual void        remember(void const* a_pInstance, byte*& a_pOutBuffer) const { o_exception(exception::unsupported_member_function_exception, "not implemented"); }
    virtual void        reset(void* a_pInstance, byte const*& a_pInBuffer) const { o_exception(exception::unsupported_member_function_exception, "not implemented"); }
    virtual void        remember(void const* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer) const { o_exception(exception::unsupported_member_function_exception, "not implemented"); }
    virtual void        reset(void* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer) const { o_exception(exception::unsupported_member_function_exception, "not implemented"); }

    // TODO : COMPILER
    /*MemberFunction* addRestoreMemberFunction();
    MemberFunction* addInitializeMemberFunction();
    MemberFunction* addTerminateMemberFunction();*/

    // Build               
    virtual void        build(void* a_pInstance, const rtti_data* a_pOwner = 0) const { construct(a_pInstance); install(a_pInstance, a_pOwner); }
    virtual void        build(void* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, const rtti_data* a_pOwner = 0 ) const { construct(a_pChunk, a_uiCount, a_uiChunkSectionSize); install(a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pOwner); }
    virtual void        unbuild(void* a_pInstance, size_t a_uiLevel = 0) const { uninstall(a_pInstance, a_uiLevel); destroy(a_pInstance); }
    virtual void        unbuild(void* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, size_t a_uiLevel = 0 ) const { uninstall(a_pChunk, a_uiCount, a_uiChunkSectionSize, a_uiLevel); destroy(a_pChunk, a_uiCount, a_uiChunkSectionSize); }

    // Setup
    virtual void        setup(void* a_pInstance, const rtti_data* a_pOwner = 0) const { construct(a_pInstance); install(a_pInstance, a_pOwner); initialize(a_pInstance); }
    virtual void        safeSetup(void* a_pInstance, const rtti_data* a_pOwner = 0) const  { safeConstruct(a_pInstance); install(a_pInstance, a_pOwner); initialize(a_pInstance); }
    virtual void        setup(void* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, const rtti_data* a_pOwner = 0 ) const { construct(a_pChunk, a_uiCount, a_uiChunkSectionSize); install(a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pOwner); initialize(a_pChunk, a_uiCount, a_uiChunkSectionSize); }
    virtual void        teardown(void* a_pInstance, size_t a_uiLevel = 0) const { terminate(a_pInstance); uninstall(a_pInstance, a_uiLevel); destroy(a_pInstance); }
    virtual void        teardown(void* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, size_t a_uiLevel = 0 ) const { terminate(a_pChunk, a_uiCount, a_uiChunkSectionSize); uninstall(a_pChunk, a_uiCount, a_uiChunkSectionSize, a_uiLevel); destroy(a_pChunk, a_uiCount, a_uiChunkSectionSize); }

    virtual void        registerRtti(void* a_pThis, void* a_pBase, Class* a_pObjectClass, connection::slot_pool* a_pSlotPool, dynamic_delete_func_t a_dynamic_delete_func, const rtti_data* a_pOwner);
    virtual void        unregisterRtti(void* a_pThis, size_t a_uiLevel);
    
    void*               getSingleton() const { return m_pSingleton; }
    void                destroySingleton();
    
    // Serialization
    virtual void        serialize(void const* a_pInstance, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { o_exception(exception::unsupported_member_function_exception, "not implemented"); }
    virtual void        deserialize(void* a_pInstance, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { o_exception(exception::unsupported_member_function_exception, "not implemented"); }
    virtual void        serialize(void const* a_pInstance, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const ;
    virtual void        deserialize(void* a_pInstance, const property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const ;
    virtual void        serialize(void const* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { o_exception(exception::unsupported_member_function_exception, "not implemented"); }
    virtual void        deserialize(void* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { o_exception(exception::unsupported_member_function_exception, "not implemented"); }
    virtual void        serialize(void const* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { o_exception(exception::unsupported_member_function_exception, "not implemented"); }
    virtual void        deserialize(void* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, const property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { o_exception(exception::unsupported_member_function_exception, "not implemented"); }
    virtual void        serializeLayout(void const* a_pInstance, byte*& a_pBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { o_exception(exception::unsupported_member_function_exception, "not implemented"); }
    virtual void        deserializeLayout(void* a_pInstance, byte const*& a_pBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { o_exception(exception::unsupported_member_function_exception, "not implemented"); }
    virtual void        serializeLayout(void const* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { o_exception(exception::unsupported_member_function_exception, "not implemented"); }
    virtual void        deserializeLayout(void* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { o_exception(exception::unsupported_member_function_exception, "not implemented"); }
    virtual void        serializeLayout(void const* a_pInstance, property_tree& a_Branch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const ;
    virtual void        deserializeLayout(void* a_pInstance, const property_tree& a_Branch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const;
    virtual void        serializeLayout(void const* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, property_tree& a_Branch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { o_exception(exception::unsupported_member_function_exception, "not implemented"); }
    virtual void        deserializeLayout(void* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, const property_tree& a_Branch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { o_exception(exception::unsupported_member_function_exception, "not implemented"); }

    /**
     * \fn  void Class::interpolate( void* a_src_start, void* a_src_end, real a_fPercent,
     *      void* a_pDest, uint mode ) const;
     *
     * \brief Reimplemented.
     */

    void                interpolate( void* a_src_start, void* a_src_end, real a_fPercent, void* a_pDest, uint mode /*= 0*/ ) const;

    void*               upcast( Class* a_pBaseClass, void* a_pBaseAddress ) const;
    void*               downcast( Class* a_pDerivedClass, void* a_pBaseAddress ) const;
    void*               cast( Class* a_pClass, void* a_pBaseAddress ) const;
    void*               upcast( Type* a_pBaseType, void* a_pBaseAddress ) const;
    void*               downcast( Type* a_pDerivedType, void* a_pBaseAddress ) const;
    virtual void*       cast( Type* a_pTargetType, void* a_pBase ) const;
    virtual void        smartCopy(reflection::Type* a_pDestType, void* a_pDest, void const* a_pSrc) const;
    void*               newInstance() const;
    void*               newInstance(Constructor* a_pConstructor, void** a_pArgs) const;
    void                deleteInstance(void* a_pInstance) const;
    virtual void        safeDeleteInstance(void* a_pObject) const;

    size_t              getInstanceCount() const { return m_Instances.size(); }
    size_t              getKindCount() const;

    void                setStateMachine(StateMachine* a_pStateMachine);

    const variant&      getAttributeCascade(const string& a_strName) const;

    virtual bool        referencesData(const void* a_pInstance, const phantom::data& a_Data) const;

    virtual void        fetchExpressions( Expression* a_pInstanceExpression, vector<Expression*>& out, filter a_Filter, uint a_uiSerializationMask ) const;

    virtual bool        isCopyable() const;

    virtual bool        isCopyConstructible() const { return NOT(hasCopyDisabled()); }

    virtual bool        hasNewVTable() const;

    const extra_data*   getExtraData() const { return static_cast<extra_data*>(m_pExtraData); }

    virtual void        finalize();

protected:
    void                fireKindCreated(void* a_pObject);
    void                fireKindDestroyed(void* a_pObject);

protected:
    virtual void        addBaseClass(Class* a_pClass, size_t a_uiOffset);
    void                addDerivedClass(Class* a_pClass);
    void                removeDerivedClass(Class* a_pClass);
    void                addNewVirtualMemberFunctionTable();
    virtual VirtualMemberFunctionTable* createVirtualMemberFunctionTable() const;
    virtual VirtualMemberFunctionTable* deriveVirtualMemberFunctionTable( VirtualMemberFunctionTable* a_pVirtualMemberFunctionTable ) const;

protected:

    void                referencedElementRemoved(LanguageElement* a_pElement);

    /**
     * \fn void Class::setupVirtualMemberFunctionTables() const;
     *
     * \brief Sets up the virtual member_function tables.
     */

    void                setupVirtualMemberFunctionTables() const;
    void                registerRttiImpl(void* a_pThis, void* a_pBase, Class* a_pObjectClass, connection::slot_pool* a_pSlotPool, dynamic_delete_func_t a_dynamic_delete_func, const rtti_data* a_pOwner);
    void                unregisterRttiImpl(void* a_pThis, size_t a_uiLevel);

    void                registerInstance(void* a_pInstance);

    void                unregisterInstance(void* a_pInstance);

    void                elementRemoved(LanguageElement* a_pElement);
    bool                canBeDestroyed() const;
    bool                getBaseClassAccess( Class* a_pClass, modifiers_t* a_pInheritanceAccess ) const;
    bool                getBaseClassAccessCascade( Class* a_pClass, modifiers_t* a_pInheritanceAccess ) const;

protected:
    vector<string> getBaseClasseNames() const;
    virtual void setBaseClasseNames(vector<string> table);
    virtual void setMemberFunctions(vector<MemberFunction*> list);

protected:
    base_class_table   m_BaseClasses;
    class_vector        m_DerivedClasses;
    vector<void*>       m_Instances;
    mutable vmt_vector  m_VirtualMemberFunctionTables;
    mutable vector<vtable_info> m_VirtualTableInfos;
    StateMachine*m_pStateMachine;
    vector<Signal*>*    m_pSignals;
    size_t              m_uiInstanceCount;
    void*               m_pSingleton;
};

/// inlines

inline size_t   Class::getBaseClassOffset(Class* a_pBaseClass) const
{
    base_class_table::const_iterator it = m_BaseClasses.begin();
    base_class_table::const_iterator end = m_BaseClasses.end();
    for(;it!=end;++it)
    {
        if(it->m_pClass == a_pBaseClass) return it->m_uiOffset;
    }
    return ~size_t(0);
}

inline size_t           Class::getBaseClassOffsetCascade(Class* a_pBaseType) const
{
    if(this == a_pBaseType) return 0;
    base_class_table::const_iterator it = m_BaseClasses.begin();
    base_class_table::const_iterator end = m_BaseClasses.end();
    for(; it != end; ++it)
    {
        int sub_result = it->m_pClass->getBaseClassOffsetCascade(a_pBaseType);
        if(sub_result != ~size_t(0)) return sub_result+it->m_uiOffset;
    }
    return ~size_t(0);
}

inline size_t              Class::getVirtualMemberFunctionTableCount() const
{
    return m_VirtualMemberFunctionTables.size();
}

inline VirtualMemberFunctionTable*    Class::getVirtualMemberFunctionTable(size_t a_uiIndex) const
{
    return m_VirtualMemberFunctionTables[a_uiIndex];
}

o_namespace_end(phantom, reflection)


#endif
