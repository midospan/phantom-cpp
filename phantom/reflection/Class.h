/*
    This file is part of PHANTOM
         P reprocessed 
         H igh-level 
         A llocator 
         N ested state-machines and 
         T emplate 
         O riented 
         M eta-programming

    For the latest infos and sources, see http://code.google.com/p/phantom-cpp

    Copyright (C) 2008-2011 by Vivien MILLET

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
    THE SOFTWARE
*/

#ifndef o_phantom_reflection_Class_h__
#define o_phantom_reflection_Class_h__


/* ****************** Includes ******************* */

/* *********************************************** */
/* The *.classdef.h file must be the last #include */
#include "Class.classdef.h"
/* **************** Declarations ***************** */
o_declare(class, phantom, reflection, DataMember)
o_declare(class, phantom, reflection, InstanceDataMember)
o_declare(class, phantom, reflection, StaticDataMember)
o_declare(class, phantom, reflection, Signal)
o_declare(class, phantom, reflection, Constructor)
o_declare(class, phantom, reflection, MemberFunction)
o_declare(class, phantom, reflection, ClassExtension)
o_declare(class, phantom, reflection, Interface)
o_declare(class, phantom, reflection, VirtualMemberFunctionTable)
o_declare(class, phantom, state, StateMachine)
/* *********************************************** */
o_h_begin

class o_export Class : public ClassType
{

public:
    o_friend(class, phantom, Object)
    o_friend(class, phantom, Phantom)
    o_friend(class, phantom, reflection, Namespace)

    template<typename t_Ty>
    friend class phantom::state::native::TNativeStateMachine;

    template<typename t_Ty, bool t_value>
    friend class phantom::state::native::TNativeStateMachineHelper;

    template<typename t_Ty, phantom::extension::detail::default_installer_id t_default_installer_id>
    friend struct phantom::extension::detail::default_installer_helper;

    Reflection_____________________________________________________________________________________
    _____________________________________________________________________________________Reflection

protected:
    typedef phantom::vector<Class*>                    class_vector; 
    struct super_class_data
    {
        super_class_data() {}
        super_class_data(Class* s, size_t o) : m_pClass(s), m_uiOffset(o) {}
        Class*    m_pClass;
        size_t    m_uiOffset;
        operator Class* () const
        {
            return m_pClass;
        }
    };
    typedef phantom::vector<super_class_data>        super_class_table;
    typedef phantom::vector<VirtualMemberFunctionTable*>    vmt_vector;

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
        typedef phantom::list<MemberFunction*>                    member_functionList;
        typedef phantom::map<EResultType, member_functionList>    result_map;

        member_function_search_data(void) : m_pMemberFunctionSignature(NULL)
        {

        }

        void populateRequest(const string& a_strMemberFunctionName, Signature* a_pMemberFunctionSignature)
        {
            m_strMemberFunctionName = a_strMemberFunctionName;
            m_pMemberFunctionSignature = a_pMemberFunctionSignature;
        }


        member_functionList::iterator getResultBegin(EResultType a_eResultType)
        {
            return m_ResultMap[a_eResultType].begin();
        }
        member_functionList::iterator getResultEnd(EResultType a_eResultType)
        {
            return m_ResultMap[a_eResultType].end();
        }

        Signature* getMemberFunctionSignature() const { return m_pMemberFunctionSignature; }
        const string& getMemberFunctionName() const { return m_strMemberFunctionName; }

        o_destructor ~member_function_search_data(void)     {}

        boolean containsResult() const {return NOT(m_ResultMap.empty()); }

        uint countResults(EResultType a_eResultType)
        {
            result_map::iterator it = m_ResultMap.find(a_eResultType);
            return it != m_ResultMap.end()?it->second.size():0;
        }

        boolean isFound(EResultType a_eResultType)
        {
            result_map::iterator it = m_ResultMap.find(a_eResultType);
            return it != m_ResultMap.end() AND NOT(it->second.empty());
        }
        void clear()
        {
            m_ResultMap.clear();
        }

        void populateWithResult(EResultType a_eResult, MemberFunction* a_pMemberFunction)
        {
            m_ResultMap[a_eResult].push_back(a_pMemberFunction);
        }

    protected:
        string            m_strMemberFunctionName;
        Signature*        m_pMemberFunctionSignature;
        result_map        m_ResultMap;
    };

    Class(const string& a_strName, bitfield a_bfModifiers = bitfield());
    Class(const string& a_strName, ushort a_uiSize, ushort a_uiAlignment, bitfield a_bfModifiers = bitfield());

    ~Class(void);
    
    virtual void        destroyContent();

    /**
     * \fn virtual void Class::valueToString( string& s, void* src) const;
     *
     * \brief Reimplementation of \ref Type::valueToString.
     *
     */

    virtual void        valueToString( string& s, void* src) const;

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

    void                filtersNonOverloadedPureVirtualMemberFunctionsCascade(instance_member_function_vector& a_Result) const;

    /**
     * \fn void Class::findPureVirtualMemberFunctions(instance_member_function_vector* a_pOutList) const;
     *
     * \brief Filters the vector passed as argument and keeps only inside the abstract member_functions that haven't been overloaded recursively in all the base classes.
     *
     * \param [out]  a_pOutList If non-null, vector filtered.
     */

    void                findPureVirtualMemberFunctions(instance_member_function_vector& a_Result) const;

    /**
     * \fn MemberFunction* Class::getMemberFunctionCascade(const string& a_strIdentifierString) const;
     *
     * \brief Gets a member_function (static or instance one) recursively through all the base classes.
     *
     * \param   a_strIdentifierString The identifier string (ex: \"member_function(int)" ).
     *
     * \return NULL if it fails, else the member_function.
     */

    MemberFunction*             getMemberFunctionCascade(const string& a_strIdentifierString) const;

    MemberFunction*             getMemberFunctionCascade(const string& a_strName, function_signature const* a_FunctionSignature, bitfield a_bfModifiers = bitfield()) const;

    /**
     * \fn  InstanceMemberFunction* Class::getInstanceMemberFunctionCascade(const string& a_strName,
     *      type_vector* a_pParameterTypes) const;
     *
     * \brief Gets an instance member_function recursively through all the base classes.
     *
     * \param   a_strName                 The member_function name.
     * \param [in,out]  a_pParameterTypes If non-null, list of the parameters' types.
     *
     * \return null if it fails, else the instance member_function.
     */

    InstanceMemberFunction*     getInstanceMemberFunctionCascade(const string& a_strName, type_vector* a_pParameterTypes) const;

    /**
     * \fn  virtual void Class::getInvokableMemberFunctionsCascade(const string& a_strName,
     *      MemberFunction** a_pOutPerfectMatchMemberFunction, member_function_vector* a_pResultMemberFunctions,
     *      type_vector* a_pArgumentTypeList);
     *
     * \brief Gets a compatible member_functions cascade.
     *
     * \param   a_strName                                   The instance member_function name.
     * \param [in,out]  a_pParameterTypeList                If non-null, list of the parameters' types.
     * \param [in,out]  a_pPerfectlyCompatibleMatchMemberFunction   If non-null, this parameter receives, if it exists, the member_function that matches perfectly the request.
     * \param [in,out]  a_pCompatibleMemberFunctions                If non-null, a vector which receives all the member_functions compatible with the request.
     */

    virtual void        getInvokableMemberFunctionsCascade(const string& a_strName, const vector<Type*>& a_ParameterTypeList, MemberFunction** a_pPerfectlyCompatibleMatchMemberFunction, member_function_vector* a_pCompatibleMemberFunctions);

    /**
     * \fn void Class::getAllMemberCascade(vector<LanguageElement*>&) const;
     *
     * \brief Gets all members recursively through all the base classes.
     *
     * \param [in,out]  a_out a vector to store the result across recursive calls.
     */

    void                getAllMemberCascade(vector<LanguageElement*>& out) const;

    /**
     * \fn void Class::getAllValueMemberCascade(vector<ValueMember*>&) const;
     *
     * \brief Gets all valueMembers recursively through all the base classes.
     *
     * \param [in,out]  out a vector to store the result across recursive calls.
     */
    void                getAllValueMemberCascade(vector<ValueMember*>& out) const;
    
    /**
     * \fn void Class::getAllCollectionCascade(vector<Collection*>&) const;
     *
     * \brief Gets all valueMembers recursively through all the base classes.
     *
     * \param [in,out]  out a vector to store the result across recursive calls.
     */
    void                getAllCollectionCascade(vector<Collection*>& out) const;

    /**
     * \fn InstanceMemberFunction* Class::findOverloadedMemberFunctions(InstanceMemberFunction* a_pOverloadMemberFunction, vector<InstanceMemberFunction*>& a_Result);
     *
     * \brief Gets a base instance member_function.
     *
     * \param [in,out]  a_pOverloadMemberFunction The overloaded member_function (must be non-NULL).
     * 					a_Result The vector containing the result
     *
     */

    void     findOverloadedMemberFunctions( InstanceMemberFunction* a_pOverloadedMemberFunction, vector<InstanceMemberFunction*>& a_Result );

    /**
     * \fn InstanceMemberFunction* Class::getInstanceMemberFunctionCascade(const string& a_strIdentifierString) const;
     *
     * \brief Gets an instance member_function recursively through all the base classes.
     *
     * \param   a_strIdentifierString The identifier string (ex: \"member_function(int)\").
     *
     * \return null if it fails, else the instance member_function cascade.
     */

    InstanceMemberFunction*     getInstanceMemberFunctionCascade(const string& a_strIdentifierString) const;

    /**
     * \fn  InstanceMemberFunction* Class::getInstanceMemberFunctionCascade(const char* a_strName,
     *      LanguageElement** a_pParameterTypes, size_t a_uiParameterCount,
     *      bitfield a_bfModifiers = bitfield()) const;
     *
     * \brief Gets an instance member_function recursively through all the base classes.
     *
     * \param   a_strName                 The name.
     * \param [in,out]  a_pParameterTypes If non-null, list of the parameters' types.
     * \param   a_uiParameterCount        Number of parameters.
     * \param   a_bfModifiers             (optional) member_function's modifiers (ex: o_const).
     *
     * \return null if it fails, else the instance member_function cascade.
     */

    InstanceMemberFunction*     getInstanceMemberFunctionCascade(const char* a_strName, function_signature const* a_FunctionSignature, bitfield a_bfModifiers = bitfield()) const;

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

    /**
     * \fn Collection* Class::getCollectionCascade(const string& a_strCollectionName) const;
     *
     * \brief Gets a valueMember recursively through all the base classes.
     *
     * \param   a_strCollectionName The collection name.
     *
     * \return null if it fails, else the valueMember.
     */

    Collection*           getCollectionCascade(const string& a_strCollectionName) const;

    void findPublicPropertiesPointingValueTypeCascade(Type* a_pType, vector<ValueMember*>& out) const
    {
        o_foreach(Class* pClass, m_SuperClasses)
        {
            pClass->findPublicPropertiesPointingValueTypeCascade(a_pType, out);
        }
        findPublicPropertiesPointingValueType(a_pType, out);
    }

    /**
     * \fn DataMember* Class::getDataMemberCascade(const string& a_strName) const;
     *
     * \brief Gets an dataMember recursively through all the base classes.
     *
     * \param   a_strDataMemberName The dataMember name.
     *
     * \return null if it fails, else the dataMember.
     */

    DataMember*          getDataMemberCascade(const string& a_strDataMemberName) const;

    /**
     * \fn InstanceDataMember* Class::getInstanceDataMemberCascade(const string& a_strName) const;
     *
     * \brief Gets an instance dataMember recursively through all the base classes.
     *
     * \param   a_strInstanceDataMemberName The instance dataMember name.
     *
     * \return null if it fails, else the instance dataMember.
     */

    InstanceDataMember*  getInstanceDataMemberCascade(const string& a_strInstanceDataMemberName) const;

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
     * \fn virtual boolean Class::asClass() const
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

    inline uint         getVirtualMemberFunctionTableCount() const;
    inline 

    /**
     * \fn VirtualMemberFunctionTable* Class::getVirtualMemberFunctionTable(uint i) const;
     *
     * \brief Gets a virtual member_function table.
     *
     * \param   i Zero-based index of the.
     *
     * \return the virtual member_function table at i.
     */

    VirtualMemberFunctionTable* getVirtualMemberFunctionTable(uint i) const;

    /**
     * \fn uint Class::getVirtualMemberFunctionTableSize(uint a_uiIndex) const
     *
     * \brief Gets the size of the virtual member_function table at i.
     *
     * \param   a_uiIndex Zero-based index.
     *
     * \return The size.
     */

    uint                getVirtualMemberFunctionTableSize(uint a_uiIndex) const    { return getVirtualMemberFunctionTable(a_uiIndex)->getSize();    }

    /**
     * \fn InstanceMemberFunction** Class::getVirtualMemberFunctionTableData(uint a_uiIndex) const
     *
     * \brief Gets the data (an array of InstanceMemberFunction) of the virtual member_function table data.
     *
     * \param   a_uiIndex Zero-based index.
     *
     * \return the virtual member_function table data as an InstanceMemberFunction* array.
     */

    InstanceMemberFunction**    getVirtualMemberFunctionTableData(uint a_uiIndex) const    { return getVirtualMemberFunctionTable(a_uiIndex)->getMemberFunctions();    }

    

    virtual boolean     acceptMemberFunction(const string& a_strName, Signature* a_pSignature, member_function_vector* a_pOutConflictingMemberFunctions = NULL) const;
    virtual boolean     acceptsOverloadedMemberFunction(const string& a_strName, Signature* a_pSignature, member_function_vector* a_pOutConflictingMemberFunctions) const;

    Class*              getSuperClass(int index) const    { return m_SuperClasses[index];    }

    super_class_table::const_iterator superClassBegin() const { return m_SuperClasses.begin(); }
    super_class_table::const_iterator superClassEnd() const { return m_SuperClasses.end(); } 

    virtual void        addSuperClass(Class* a_pType, size_t a_uiOffset);
    const 
    super_class_table&  getSuperClasses() const { return m_SuperClasses; }
    uint                getSuperClassCount(void) const { return m_SuperClasses.size(); }
    boolean             hasSuperClass( Class* a_pClass ) const;

    Class*              getDerivedClass(uint a_uiIndex) const { return m_DerivedClasses[a_uiIndex]; }
    uint                getDerivedClassCount(void) const { return m_DerivedClasses.size(); }
    boolean             hasDerivedClass( Class* a_pClass ) const;

    void                homonymousMemberFunctionSearch( member_function_search_data* a_pMemberFunctionRequest );
    void                sortSuperAndRootMemberFunctions( VirtualMemberFunctionTable* a_pSuperVMT, instance_member_function_list* a_OutSuperMemberFunctions, instance_member_function_list* a_OutRootMemberFunctions ) const;

    o_forceinline int   getSuperClassOffset(size_t a_uiClassIndex) const
    {
        return m_SuperClasses[a_uiClassIndex].m_uiOffset;
    }
    o_forceinline int   getSuperClassOffset(Class* a_pSuperType) const;
    inline int          getSuperClassOffsetCascade(Class* a_pSuperType) const;
    boolean             isRootClass() const { return m_SuperClasses.empty(); }

    virtual boolean     isKindOf( Class* a_pType ) const;
    virtual boolean     isKindOf( Type* a_pType ) const { return a_pType->isClass() AND isKindOf(static_cast<Class*>(a_pType)); }
    virtual ERelation   getRelationWith(Type* a_pType) const;
    boolean             doesInstanceDependOn(void* a_pInstance, void* a_pOther) const;
    
    virtual 
    InstanceMemberFunction**    getVfTable() const ;

    virtual void        setClass(void* a_pInstance, void* a_pClass) const    { throw exception::unsupported_member_function_exception("this member_function must be overloaded in specialized subclasses which support it"); }
    virtual void        setStateMachineData(void* a_pInstance, void* a_pSmdataptr) const { throw exception::unsupported_member_function_exception("this member_function must be overloaded in specialized subclasses which support it"); }
    virtual void        setVftPtr(void* a_pInstance, InstanceMemberFunction** a_pVftPtr) const { throw exception::unsupported_member_function_exception("this member_function must be overloaded in specialized subclasses which support it"); }
  
    virtual void        extractVirtualMemberFunctionTableInfos(const void* a_pInstance, vector<vtable_info>& vtables) = 0;
    virtual uint        getVirtualMemberFunctionCount(uint a_uiIndex) const = 0;

    // Signals and Extensions

    virtual void        addSignal(Signal* a_pSignal);
    virtual void        addExtension(ClassExtension* a_pExtension);
    ClassExtension*     getExtension(Class* a_pExtensionClass);

    template<typename t_Ty>
    inline t_Ty*        getExtension() const;
    Signal*             getSignal(const string& a_strIdentifierString) const;
    Signal*             getSignalCascade(const string& a_strIdentifierString) const;
    InstanceMemberFunction*     getSlot(const string& a_strIdentifierString) const;
    InstanceMemberFunction*     getSlotCascade(const string& a_strIdentifierString) const;
    state::StateMachine*getStateMachine() const;
    state::StateMachine*getStateMachineCascade() const;

    virtual boolean     isPolymorphic() const { return false; }

    virtual void        initialize( void* a_pInstance ) const {}
    virtual void        terminate( void* a_pInstance ) const {}
    virtual void        initialize( void* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize ) const {}
    virtual void        terminate( void* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize ) const {}
    
    
    virtual void        install( void* a_pInstance ) const {}
    virtual void        uninstall( void* a_pInstance ) const {}
    virtual void        install( void* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize ) const {    }
    virtual void        uninstall( void* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize ) const     {}

    // Build               
    virtual void        build(void* a_pInstance) const { construct(a_pInstance); install(a_pInstance); }
    virtual void        build(void* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize ) const { construct(a_pChunk, a_uiCount, a_uiChunkSectionSize); install(a_pChunk, a_uiCount, a_uiChunkSectionSize); }
    virtual void        unbuild(void* a_pInstance) const { install(a_pInstance); destroy(a_pInstance); }
    virtual void        unbuild(void* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize ) const { uninstall(a_pChunk, a_uiCount, a_uiChunkSectionSize); destroy(a_pChunk, a_uiCount, a_uiChunkSectionSize); }

    // Setup
    virtual void        setup(void* a_pInstance) const { construct(a_pInstance); install(a_pInstance); initialize(a_pInstance); }
    virtual void        safeSetup(void* a_pInstance) const  { safeConstruct(a_pInstance); install(a_pInstance); initialize(a_pInstance); }
    virtual void        setup(void* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize ) const { construct(a_pChunk, a_uiCount, a_uiChunkSectionSize); install(a_pChunk, a_uiCount, a_uiChunkSectionSize); initialize(a_pChunk, a_uiCount, a_uiChunkSectionSize); }
    virtual void        teardown(void* a_pInstance) const { terminate(a_pInstance); uninstall(a_pInstance); destroy(a_pInstance); }
    virtual void        teardown(void* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize ) const { terminate(a_pChunk, a_uiCount, a_uiChunkSectionSize); uninstall(a_pChunk, a_uiCount, a_uiChunkSectionSize); destroy(a_pChunk, a_uiCount, a_uiChunkSectionSize); }

    virtual void        registerRtti(void* a_pThis, void* a_pBase, Class* a_pObjectClass, connection::slot_pool* a_pSlotPool, dynamic_delete_func_t a_dynamic_delete_func);
    virtual void        unregisterRtti(void* a_pThis);
    // Serialization

    /**
     * \fn  virtual void Class::serializeLayout(void const* a_pInstance, byte*& a_pBuffer,
     *      serialization::DataBase const* a_pDataBase) const = 0;
     *
     * \brief Serialize to a binary buffer the layout of this class only (not the base class ones). If you want to serialize
     * 		  the complete layout of an instance, use serialize instead.
     *
     * \param   a_pInstance       The instance.
     * \param [in,out]  a_pBuffer [in,out] If non-null, the binary buffer.
     * \param   a_pDataBase       The guid data base.
     */

    virtual void        serializeLayout(void const* a_pInstance, byte*& a_pBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const = 0;

    /**
     * \fn  virtual void Class::deserializeLayout(void* a_pInstance, byte const*& a_pBuffer,
     *      serialization::DataBase const* a_pDataBase) const = 0;
     *
     * \brief Deserialize from a binary buffer the layout of this class only (not the base class ones). If you want to deserialize
     * 		  the complete layout of an instance, use deserialize instead.
     * \param [in,out]  a_pInstance If non-null, the instance.
     * \param   a_pBuffer           The binary buffer.
     * \param   a_pDataBase         The guid data base.
     */

    virtual void        deserializeLayout(void* a_pInstance, byte const*& a_pBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const = 0;

    /**
     * \fn  virtual void Class::serializeLayout(void const* a_pInstance, size_t a_uiCount,
     *      size_t a_uiChunkSectionSize, byte*& a_pBuffer,
     *      serialization::DataBase const* a_pDataBase) const = 0;
     *
     * \brief Serialize to a binary buffer the layout of this class only (not the base class ones) for N instances 
     * 		  contained inside the given memory chunk. 
     *
     * \param   a_pChunk                The chunk address.
     * \param   a_uiCount               Number of instances in the chunk.
     * \param   a_uiChunkSectionSize    Size of a chunk section (useful for memory aligned chunks).
     * \param   [out]  a_pBuffer        [out] If non-null, the binary buffer.
     * \param   a_pDataBase             The guid data base.
     */

    virtual void        serializeLayout(void const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const = 0;

    /**
     * \fn  virtual void Class::deserializeLayout(void* a_pInstance, size_t a_uiCount,
     *      size_t a_uiChunkSectionSize, byte const*& a_pBuffer,
     *      serialization::DataBase const* a_pDataBase) const = 0;
     *
     * \brief Deserialize from a binary buffer the layout of this class only (not the base class ones) for N instances 
     * 		  contained inside the given memory chunk. 
     *
     * \param   a_pChunk                The chunk address.
     * \param   a_uiCount               Number of instances in the chunk.
     * \param   a_uiChunkSectionSize    Size of a chunk section (useful for memory aligned chunks).
     * \param   [in] a_pBuffer          [in] The binary buffer.
     * \param   a_pDataBase             The guid data base.
     */

    virtual void        deserializeLayout(void* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const = 0;

    virtual void        serializeLayout(void const* a_pInstance, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const = 0;
    virtual void        deserializeLayout(void* a_pInstance, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const = 0;
    virtual void        serializeLayout(void const* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const = 0;
    virtual void        deserializeLayout(void* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const = 0;

    /**
     * \fn  void Class::interpolate( void* a_src_start, void* a_src_end, real a_fPercent,
     *      void* a_pDest, uint mode ) const;
     *
     * \brief Reimplemented.
     */

    void                interpolate( void* a_src_start, void* a_src_end, real a_fPercent, void* a_pDest, uint mode /*= 0*/ ) const;

    virtual void*       cast( Class* a_pBaseClass, void* a_pBaseAddress ) const;
    virtual void*       cast( Type* a_pTarget, void* a_pBase ) const 
    {
        if(a_pTarget->isClass()) return cast(static_cast<Class*>(a_pTarget), a_pBase);
        return NULL;
    }
    virtual void        smartCopy(void* a_Instance, void const* a_pSource, reflection::Type* a_pSourceType) const;
    void*               newInstance() const;
    void*               newInstance(Constructor* a_pConstructor, void** a_pArgs) const;
    void*               newInstance(Constructor* a_pConstructor, argument::list* a_pArgs) const;
    void                deleteInstance(void* a_pInstance) const;
    virtual void        safeDeleteInstance(void* a_pObject) const;
    virtual 
    LanguageElement*    getElement(
        const char* a_strQualifiedName 
        , template_specialization const*
        , function_signature const*
        , bitfield a_bfModifiers = bitfield()) const ;

    size_t              getInstanceCount() const { return m_uiRegisteredInstances; }
    size_t              getKindCount() const 
    { 
        size_t count = m_uiRegisteredInstances;
        class_vector::const_iterator it = m_DerivedClasses.begin();
        class_vector::const_iterator end = m_DerivedClasses.end();
        for(;it!=end;++it)
        {
            count += (*it)->getKindCount();
        }
        return count;
    }

    void                setStateMachine(phantom::state::StateMachine* a_pStateMachine);

protected:
    void                fireKindCreated(void* a_pObject) const;
    void                fireKindDestroyed(void* a_pObject) const;

protected:
    void                addDerivedClass(Class* a_pClass);
    void                removeDerivedClass(Class* a_pClass);

    /**
     * \fn void Class::setupVirtualMemberFunctionTables() const;
     *
     * \brief Sets up the virtual member_function tables.
     */

    void                setupVirtualMemberFunctionTables() const;
    inline void         registerRttiImpl(void* a_pThis, void* a_pBase, Class* a_pObjectClass, connection::slot_pool* a_pSlotPool, dynamic_delete_func_t a_dynamic_delete_func)
    {
        o_assert(phantom::Phantom::m_rtti_data_map->find(a_pThis) == phantom::Phantom::m_rtti_data_map->end());
        (*phantom::Phantom::m_rtti_data_map)[a_pThis] = phantom::rtti_data(a_pObjectClass, this, a_pBase, a_pSlotPool, a_dynamic_delete_func);
        a_pObjectClass->m_uiRegisteredInstances++;
    }
    inline void         unregisterRttiImpl(void* a_pThis)
    {
        phantom::Phantom::rtti_data_map::iterator found = phantom::Phantom::m_rtti_data_map->find(a_pThis);
        o_assert(found != phantom::Phantom::m_rtti_data_map->end());
        found->second.object_class->m_uiRegisteredInstances--;
        phantom::Phantom::m_rtti_data_map->erase(found);
    }

protected:
    super_class_table   m_SuperClasses;
    class_vector        m_DerivedClasses;
    mutable vmt_vector  m_VirtualMemberFunctionTables;
    state::StateMachine*m_pStateMachine;
    size_t              m_uiRegisteredInstances;

};

/// inlines

o_forceinline int    Class::getSuperClassOffset(Class* a_pSuperClass) const
{
    super_class_table::const_iterator it = m_SuperClasses.begin();
    super_class_table::const_iterator end = m_SuperClasses.end();
    for(;it!=end;++it)
    {
        if(it->m_pClass == a_pSuperClass) return it->m_uiOffset;
    }
    return -1;
}

inline int            Class::getSuperClassOffsetCascade(Class* a_pSuperType) const
{
    if(this == a_pSuperType) return 0;
    super_class_table::const_iterator it = m_SuperClasses.begin();
    super_class_table::const_iterator end = m_SuperClasses.end();
    for(; it != end; ++it)
    {
        int sub_result = it->m_pClass->getSuperClassOffsetCascade(a_pSuperType);
        if(sub_result != -1) return sub_result+it->m_uiOffset;
    }
    return -1;
}

inline uint                Class::getVirtualMemberFunctionTableCount() const
{
    if(m_VirtualMemberFunctionTables.empty()) setupVirtualMemberFunctionTables();
    return m_VirtualMemberFunctionTables.size();
}

inline VirtualMemberFunctionTable*    Class::getVirtualMemberFunctionTable(uint i) const
{
    if(m_VirtualMemberFunctionTables.empty()) setupVirtualMemberFunctionTables();
    return m_VirtualMemberFunctionTables[i];
}


template<typename t_Ty>
inline t_Ty*    Class::getExtension() const
{
    member_collection::const_iterator it = m_Members.begin();
    for(;it != m_Members.end(); ++it)
    {
        if(phantom::is<t_Ty>(*it)) 
            return static_cast<t_Ty*>(*it);
    }
    return NULL; 
}    

o_h_end


#else // o_phantom_reflection_Class_h__
#include "Class.classdef.h"
#endif
