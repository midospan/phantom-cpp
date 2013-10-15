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
o_declare(class, phantom, reflection, Attribute)
o_declare(class, phantom, reflection, InstanceAttribute)
o_declare(class, phantom, reflection, StaticAttribute)
o_declare(class, phantom, reflection, Signal)
o_declare(class, phantom, reflection, Constructor)
o_declare(class, phantom, reflection, Method)
o_declare(class, phantom, reflection, ClassExtension)
o_declare(class, phantom, reflection, Interface)
o_declare(class, phantom, reflection, VirtualMethodTable)
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
    typedef phantom::vector<VirtualMethodTable*>    vmt_vector;

public:
    class method_search_data
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
        typedef phantom::list<Method*>                    methodList;
        typedef phantom::map<EResultType, methodList>    result_map;

        method_search_data(void) : m_pMethodSignature(NULL)
        {

        }

        void populateRequest(const string& a_strMethodName, Signature* a_pMethodSignature)
        {
            m_strMethodName = a_strMethodName;
            m_pMethodSignature = a_pMethodSignature;
        }


        methodList::iterator getResultBegin(EResultType a_eResultType)
        {
            return m_ResultMap[a_eResultType].begin();
        }
        methodList::iterator getResultEnd(EResultType a_eResultType)
        {
            return m_ResultMap[a_eResultType].end();
        }

        Signature* getMethodSignature() const { return m_pMethodSignature; }
        const string& getMethodName() const { return m_strMethodName; }

        o_destructor ~method_search_data(void)     {}

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

        void populateWithResult(EResultType a_eResult, Method* a_pMethod)
        {
            m_ResultMap[a_eResult].push_back(a_pMethod);
        }

    protected:
        string            m_strMethodName;
        Signature*        m_pMethodSignature;
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
     * \fn  void Class::filtersNonOverloadedAbstractMethodsCascade(instance_method_vector& a_Result) const;
     *
     * \brief Keep only non overloaded abstract methods cascade.
     *
     * \param [in,out]  a_pOutList If non-null, vector passed is filetered to keep only to abstract methods that haven't been overloaded, recursively through all the base classes.
     */

    void                filtersNonOverloadedAbstractMethodsCascade(instance_method_vector& a_Result) const;

    /**
     * \fn void Class::findAbstractMethods(instance_method_vector* a_pOutList) const;
     *
     * \brief Filters the vector passed as argument and keeps only inside the abstract methods that haven't been overloaded recursively in all the base classes.
     *
     * \param [out]  a_pOutList If non-null, vector filtered.
     */

    void                findAbstractMethods(instance_method_vector& a_Result) const;

    /**
     * \fn Method* Class::getMethodCascade(const string& a_strIdentifierString) const;
     *
     * \brief Gets a method (static or instance one) recursively through all the base classes.
     *
     * \param   a_strIdentifierString The identifier string (ex: \"method(int)" ).
     *
     * \return NULL if it fails, else the method.
     */

    Method*             getMethodCascade(const string& a_strIdentifierString) const;

    Method*             getMethodCascade(const string& a_strName, function_signature const* a_FunctionSignature, bitfield a_bfModifiers = bitfield()) const;

    /**
     * \fn  InstanceMethod* Class::getInstanceMethodCascade(const string& a_strName,
     *      type_vector* a_pParameterTypes) const;
     *
     * \brief Gets an instance method recursively through all the base classes.
     *
     * \param   a_strName                 The method name.
     * \param [in,out]  a_pParameterTypes If non-null, list of the parameters' types.
     *
     * \return null if it fails, else the instance method.
     */

    InstanceMethod*     getInstanceMethodCascade(const string& a_strName, type_vector* a_pParameterTypes) const;

    /**
     * \fn  virtual void Class::getInvokableMethodsCascade(const string& a_strName,
     *      Method** a_pOutPerfectMatchMethod, method_vector* a_pResultMethods,
     *      type_vector* a_pArgumentTypeList);
     *
     * \brief Gets a compatible methods cascade.
     *
     * \param   a_strName                                   The instance method name.
     * \param [in,out]  a_pParameterTypeList                If non-null, list of the parameters' types.
     * \param [in,out]  a_pPerfectlyCompatibleMatchMethod   If non-null, this parameter receives, if it exists, the method that matches perfectly the request.
     * \param [in,out]  a_pCompatibleMethods                If non-null, a vector which receives all the methods compatible with the request.
     */

    virtual void        getInvokableMethodsCascade(const string& a_strName, const vector<Type*>& a_ParameterTypeList, Method** a_pPerfectlyCompatibleMatchMethod, method_vector* a_pCompatibleMethods);

    /**
     * \fn void Class::getAllMemberCascade(vector<LanguageElement*>&) const;
     *
     * \brief Gets all members recursively through all the base classes.
     *
     * \param [in,out]  a_out a vector to store the result across recursive calls.
     */

    void                getAllMemberCascade(vector<LanguageElement*>& out) const;

    /**
     * \fn void Class::getAllPropertyCascade(vector<Property*>&) const;
     *
     * \brief Gets all properties recursively through all the base classes.
     *
     * \param [in,out]  out a vector to store the result across recursive calls.
     */
    void                getAllPropertyCascade(vector<Property*>& out) const;
    
    /**
     * \fn void Class::getAllCollectionCascade(vector<Collection*>&) const;
     *
     * \brief Gets all properties recursively through all the base classes.
     *
     * \param [in,out]  out a vector to store the result across recursive calls.
     */
    void                getAllCollectionCascade(vector<Collection*>& out) const;

    /**
     * \fn InstanceMethod* Class::findOverloadedMethods(InstanceMethod* a_pOverloadMethod, vector<InstanceMethod*>& a_Result);
     *
     * \brief Gets a base instance method.
     *
     * \param [in,out]  a_pOverloadMethod The overloaded method (must be non-NULL).
     * 					a_Result The vector containing the result
     *
     */

    void     findOverloadedMethods( InstanceMethod* a_pOverloadedMethod, vector<InstanceMethod*>& a_Result );

    /**
     * \fn InstanceMethod* Class::getInstanceMethodCascade(const string& a_strIdentifierString) const;
     *
     * \brief Gets an instance method recursively through all the base classes.
     *
     * \param   a_strIdentifierString The identifier string (ex: \"method(int)\").
     *
     * \return null if it fails, else the instance method cascade.
     */

    InstanceMethod*     getInstanceMethodCascade(const string& a_strIdentifierString) const;

    /**
     * \fn  InstanceMethod* Class::getInstanceMethodCascade(const char* a_strName,
     *      LanguageElement** a_pParameterTypes, size_t a_uiParameterCount,
     *      bitfield a_bfModifiers = bitfield()) const;
     *
     * \brief Gets an instance method recursively through all the base classes.
     *
     * \param   a_strName                 The name.
     * \param [in,out]  a_pParameterTypes If non-null, list of the parameters' types.
     * \param   a_uiParameterCount        Number of parameters.
     * \param   a_bfModifiers             (optional) method's modifiers (ex: o_const).
     *
     * \return null if it fails, else the instance method cascade.
     */

    InstanceMethod*     getInstanceMethodCascade(const char* a_strName, function_signature const* a_FunctionSignature, bitfield a_bfModifiers = bitfield()) const;

    /**
     * \fn Property* Class::getPropertyCascade(const string& a_strPropertyName) const;
     *
     * \brief Gets a property recursively through all the base classes.
     *
     * \param   a_strPropertyName The property name.
     *
     * \return null if it fails, else the property.
     */

    Property*           getPropertyCascade(const string& a_strPropertyName) const;

    /**
     * \fn Collection* Class::getCollectionCascade(const string& a_strCollectionName) const;
     *
     * \brief Gets a property recursively through all the base classes.
     *
     * \param   a_strCollectionName The collection name.
     *
     * \return null if it fails, else the property.
     */

    Collection*           getCollectionCascade(const string& a_strCollectionName) const;

    void findPublicPropertiesPointingValueTypeCascade(Type* a_pType, vector<Property*>& out) const
    {
        o_foreach(Class* pClass, m_SuperClasses)
        {
            pClass->findPublicPropertiesPointingValueTypeCascade(a_pType, out);
        }
        findPublicPropertiesPointingValueType(a_pType, out);
    }

    /**
     * \fn Attribute* Class::getAttributeCascade(const string& a_strName) const;
     *
     * \brief Gets an attribute recursively through all the base classes.
     *
     * \param   a_strAttributeName The attribute name.
     *
     * \return null if it fails, else the attribute.
     */

    Attribute*          getAttributeCascade(const string& a_strAttributeName) const;

    /**
     * \fn InstanceAttribute* Class::getInstanceAttributeCascade(const string& a_strName) const;
     *
     * \brief Gets an instance attribute recursively through all the base classes.
     *
     * \param   a_strInstanceAttributeName The instance attribute name.
     *
     * \return null if it fails, else the instance attribute.
     */

    InstanceAttribute*  getInstanceAttributeCascade(const string& a_strInstanceAttributeName) const;

    /**
     * \fn StaticAttribute* Class::getStaticAttributeCascade(const string& a_strName) const;
     *
     * \brief Gets a static attribute recursively through all the base classes.
     *
     * \param   a_strName The static attribute name.
     *
     * \return null if it fails, else the static attribute.
     */

    StaticAttribute*    getStaticAttributeCascade(const string& a_strStaticAttributeName) const;

    /**
     * \fn StaticMethod* Class::getStaticMethodCascade( const string& a_strIdentifierString ) const;
     *
     * \brief Gets a static method recursively through all the base classes.
     *
     * \param   a_strIdentifierString The identifier string.
     *
     * \return null if it fails, else the static method.
     */

    StaticMethod*       getStaticMethodCascade( const string& a_strIdentifierString ) const;

    /**
     * \fn virtual boolean Class::asClass() const
     *
     * \brief Reimplemented
     */

    virtual Class*      asClass() const { return const_cast<Class*>(this); }

    /**
     * \fn inline uint Class::getVirtualMethodTableCount() const;
     *
     * \brief Gets the virtual method table count.
     *
     * \return The virtual method table count.
     */

    inline uint         getVirtualMethodTableCount() const;
    inline 

    /**
     * \fn VirtualMethodTable* Class::getVirtualMethodTable(uint i) const;
     *
     * \brief Gets a virtual method table.
     *
     * \param   i Zero-based index of the.
     *
     * \return the virtual method table at i.
     */

    VirtualMethodTable* getVirtualMethodTable(uint i) const;

    /**
     * \fn uint Class::getVirtualMethodTableSize(uint a_uiIndex) const
     *
     * \brief Gets the size of the virtual method table at i.
     *
     * \param   a_uiIndex Zero-based index.
     *
     * \return The size.
     */

    uint                getVirtualMethodTableSize(uint a_uiIndex) const    { return getVirtualMethodTable(a_uiIndex)->getSize();    }

    /**
     * \fn InstanceMethod** Class::getVirtualMethodTableData(uint a_uiIndex) const
     *
     * \brief Gets the data (an array of InstanceMethod) of the virtual method table data.
     *
     * \param   a_uiIndex Zero-based index.
     *
     * \return the virtual method table data as an InstanceMethod* array.
     */

    InstanceMethod**    getVirtualMethodTableData(uint a_uiIndex) const    { return getVirtualMethodTable(a_uiIndex)->getMethods();    }

    

    virtual boolean     acceptMethod(const string& a_strName, Signature* a_pSignature, method_vector* a_pOutConflictingMethods = NULL) const;
    virtual boolean     acceptsOverloadedMethod(const string& a_strName, Signature* a_pSignature, method_vector* a_pOutConflictingMethods) const;

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

    void                homonymousMethodSearch( method_search_data* a_pMethodRequest );
    void                sortSuperAndRootMethods( VirtualMethodTable* a_pSuperVMT, instance_method_list* a_OutSuperMethods, instance_method_list* a_OutRootMethods ) const;

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
    InstanceMethod**    getVfTable() const ;

    virtual void        setClass(void* a_pInstance, void* a_pClass) const    { throw exception::unsupported_method_exception("this method must be overloaded in specialized subclasses which support it"); }
    virtual void        setStateMachineData(void* a_pInstance, void* a_pSmdataptr) const { throw exception::unsupported_method_exception("this method must be overloaded in specialized subclasses which support it"); }
    virtual void        setVftPtr(void* a_pInstance, InstanceMethod** a_pVftPtr) const { throw exception::unsupported_method_exception("this method must be overloaded in specialized subclasses which support it"); }
  
    virtual void        extractVirtualMethodTableInfos(const void* a_pInstance, vector<vtable_info>& vtables) = 0;
    virtual uint        getVirtualMethodCount(uint a_uiIndex) const = 0;

    // Signals and Extensions

    virtual void        addSignal(Signal* a_pSignal);
    virtual void        addExtension(ClassExtension* a_pExtension);
    ClassExtension*     getExtension(Class* a_pExtensionClass);

    template<typename t_Ty>
    inline t_Ty*        getExtension() const;
    Signal*             getSignal(const string& a_strIdentifierString) const;
    Signal*             getSignalCascade(const string& a_strIdentifierString) const;
    InstanceMethod*     getSlot(const string& a_strIdentifierString) const;
    InstanceMethod*     getSlotCascade(const string& a_strIdentifierString) const;
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
     * \fn void Class::setupVirtualMethodTables() const;
     *
     * \brief Sets up the virtual method tables.
     */

    void                setupVirtualMethodTables() const;
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
    mutable vmt_vector  m_VirtualMethodTables;
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

inline uint                Class::getVirtualMethodTableCount() const
{
    if(m_VirtualMethodTables.empty()) setupVirtualMethodTables();
    return m_VirtualMethodTables.size();
}

inline VirtualMethodTable*    Class::getVirtualMethodTable(uint i) const
{
    if(m_VirtualMethodTables.empty()) setupVirtualMethodTables();
    return m_VirtualMethodTables[i];
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
