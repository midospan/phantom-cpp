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

#ifndef o_phantom_reflection_ClassType_h__
#define o_phantom_reflection_ClassType_h__

/* ****************** Includes ******************* */

/* **************** Declarations ***************** */

/* *********************************************** */

o_namespace_begin(phantom, reflection)
    
class o_export ClassType : public Type
{
    o_declare_meta_type(ClassType);

protected:
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
        modifiers_t                        m_AccessSpecifier;
        int                             m_iState;
    };

public:
    typedef phantom::reflection::Class*                     member_key;
    typedef std::pair<member_key, LanguageElement*>         member_pair;
    typedef phantom::map<string, MemberFunction*>           member_function_map;
    typedef phantom::multimap<Class*, LanguageElement*>     member_collection;
    typedef phantom::vector<InstanceMemberFunction*>        instance_member_function_list;
    typedef phantom::vector<Type*>                          type_vector;
    typedef phantom::vector<MemberFunction*>                member_function_vector;
    typedef phantom::vector<InstanceMemberFunction*>        instance_member_function_vector;

public:
    ClassType(ETypeId a_eTypeId, extra_data* a_pExtraData);
    ClassType(ETypeId a_eTypeId, extra_data* a_pExtraData, const string& a_strName, modifiers_t a_Modifiers = 0);
    ClassType(ETypeId a_eTypeId, const string& a_strName, ushort a_uiSize, ushort a_uiAlignment, modifiers_t a_Modifiers = 0);

    o_restore(filter,pass);

    o_destructor ~ClassType(void);

    virtual bool            isDefined() const { o_assert(m_pExtraData); return m_pExtraData->m_iState >= extra_data::e_State_Compiled; }

    virtual void            destroyContent();

    virtual bool            isDefaultInstanciable() const;

    virtual bool            isDefaultConstructible() const { return Type::isDefaultConstructible() AND getConstructor(m_strName+"()") != nullptr; }

    virtual ClassType*      asClassType() const { return const_cast<ClassType*>(this); }

    void                    getMembers(vector<LanguageElement*>& a_out) const;

    void                    setDefaultAccess(modifiers_t modifier);

    modifiers_t                getDefaultAccess() const { o_assert(m_pExtraData); return m_pExtraData->m_AccessSpecifier; }

    virtual void            addConstructor( Constructor* a_pConstructor );
    virtual Constructor*    addConstructor( const string& a_strSignature );
    virtual void            addValueMember( ValueMember* a_pValueMember );
    virtual void            addDataMember( DataMember* a_pDataMember );
    virtual DataMember*     addDataMember( const string& a_strCode, uint a_uiSerializationMask = o_save_data );
    virtual void            addStaticDataMember( StaticDataMember* a_pDataMember );
    virtual void            addInstanceDataMember( InstanceDataMember* a_pDataMember );
    virtual void            addProperty( Property* a_pProperty );
    virtual Property*       addProperty( const string& a_strName, uint a_uiSerializationMask = o_save_state );
    virtual void            addMemberFunction(MemberFunction* a_MetaMemberFunction);
    virtual MemberFunction* addMemberFunction(const string& a_strCode);
    virtual void            addInstanceMemberFunction(InstanceMemberFunction* a_MetaMemberFunction);
    virtual void            addStaticMemberFunction(StaticMemberFunction* a_MetaMemberFunction);
    virtual void            addAnonymousSection(AnonymousSection* a_pAnonymousSection);
    virtual AnonymousSection*addAnonymousSection(const string& a_strCode, modifiers_t a_Modifiers = modifiers_t());

    virtual void            removeConstructor( Constructor* a_pConstructor );
    virtual void            removeValueMember( ValueMember* a_pValueMember );
    virtual void            removeDataMember( DataMember* a_pDataMember );
    virtual void            removeStaticDataMember( StaticDataMember* a_pDataMember );
    virtual void            removeInstanceDataMember( InstanceDataMember* a_pDataMember );
    virtual void            removeAnonymousSection( AnonymousSection* a_pAnonymousSection );
    virtual void            removeProperty( Property* a_pProperty );
    virtual void            removeMemberFunction(MemberFunction* a_MetaMemberFunction);
    virtual void            removeInstanceMemberFunction(InstanceMemberFunction* a_MetaMemberFunction);
    virtual void            removeStaticMemberFunction(StaticMemberFunction* a_MetaMemberFunction);


    Constructor*            getConstructor( Type* a_pType, vector<size_t>* a_pPartialMatches = nullptr, modifiers_t a_Modifiers = 0 ) const;
    Constructor*            getConstructor( const vector<Type*>& a_Types, vector<size_t>* a_pPartialMatches = nullptr, modifiers_t a_Modifiers = 0 ) const;
    Constructor*            getConstructor( const string& a_strDecoratedName ) const;
    ValueMember*            getValueMember(const string& a_strName) const;
    size_t                  getValueMemberCount() const;
    AnonymousSection*         getAnonymousSection(size_t a_uiIndex) const;
    size_t                  getAnonymousSectionCount() const;
    DataMember*             getDataMember(const string& a_strName) const;
    InstanceDataMember*     getInstanceDataMember(const string& a_strName) const;
    virtual InstanceDataMember* getInstanceDataMemberByOffset(size_t a_uiOffset) const;
    InstanceDataMember*     getInstanceDataMemberAtAddress(const void* a_pBase, const void* a_pAddress) const;
    StaticDataMember*       getStaticDataMember(const string& a_strName) const;
    Property*               getProperty(const string& a_strName) const;
    MemberFunction*         getMemberFunction(const string& a_strDecoratedName) const;
    MemberFunction*         getMemberFunction(const string& a_strName, const vector<Type*>& a_Types, vector<size_t>* a_pPartialMatchesIndexes = nullptr, modifiers_t a_Modifiers = 0) const;
    InstanceMemberFunction* getInstanceMemberFunction(const string& a_strDecoratedName) const;
    InstanceMemberFunction* getInstanceMemberFunction(const string& a_strName, const vector<Type*>& a_Types, vector<size_t>* a_pPartialMatchesIndexes = nullptr, modifiers_t a_Modifiers = 0) const;
    size_t                  getInstanceMemberFunctionCount() const;
    StaticMemberFunction*   getStaticMemberFunction( const string& a_strDecoratedName ) const;
    StaticMemberFunction*   getStaticMemberFunction( const string& a_strName, const vector<Type*>& a_Types, vector<size_t>* a_pPartialMatchesIndexes = nullptr, modifiers_t a_Modifiers = 0 ) const;
    size_t                  getStaticMemberFunctionCount() const;

    InstanceMemberFunction* getUniqueInstanceMemberFunctionWithName(const string& a_strName) const;

    void                    findPublicValueMembersPointingValueType(Type* a_pType, vector<ValueMember*>& out) const;

    vector<ValueMember*>::const_iterator            beginValueMembers() const { return m_ValueMembers.begin(); }
    vector<ValueMember*>::const_iterator            endValueMembers() const { return m_ValueMembers.end(); }
    vector<InstanceDataMember*>::const_iterator     beginInstanceDataMembers() const { return m_InstanceDataMembers.begin(); }
    vector<InstanceDataMember*>::const_iterator     endInstanceDataMembers() const { return m_InstanceDataMembers.end(); }
    vector<StaticDataMember*>::const_iterator       beginStaticDataMembers() const;
    vector<StaticDataMember*>::const_iterator       endStaticDataMembers() const;
    vector<InstanceMemberFunction*>::const_iterator beginInstanceMemberFunctions() const { return m_InstanceMemberFunctions.begin(); }
    vector<InstanceMemberFunction*>::const_iterator endInstanceMemberFunctions() const { return m_InstanceMemberFunctions.end(); }
    vector<StaticMemberFunction*>::const_iterator   beginStaticMemberFunctions() const;
    vector<StaticMemberFunction*>::const_iterator   endStaticMemberFunctions() const;
    vector<Property*>::const_iterator               beginProperties() const { return m_Properties.begin(); }
    vector<Property*>::const_iterator               endProperties() const { return m_Properties.end(); }
    vector<AnonymousSection*>::const_iterator         beginAnonymousSections() const;
    vector<AnonymousSection*>::const_iterator         endAnonymousSections() const;
    vector<Constructor*>::const_iterator            beginConstructors() const;
    vector<Constructor*>::const_iterator            endConstructors() const;

    virtual bool            isImplicitlyConvertibleTo(Type* a_pType) const;

    virtual bool            isConvertibleTo(Type* a_pType) const;
    virtual void            convertValueTo(Type* a_pDestType, void* a_pDestValue, void const* a_pSrcValue) const;

    virtual void            construct(void* a_pInstance) const;
    virtual void            destroy(void* a_pInstance) const;

    virtual void*           newInstance() const;

    virtual void*           newInstance(Constructor* a_pConstructor, void** a_pArgs = NULL) const;
    virtual void            deleteInstance(void* a_pObject) const = 0;
    virtual void            safeDeleteInstance(void* a_pObject) const { deleteInstance(a_pObject); }

    virtual void            interpolate(void* a_src_start, void* a_src_end, real a_fPercent, void* a_pDest, uint mode = 0) const;
    virtual void            valueFromString( const string& cs, void* dest ) const;
    virtual void            valueToString( string& s, const void* src ) const;

    virtual void            smartCopy(reflection::Type* a_pDestType, void* a_pDest, void const* a_pSrc) const;

    virtual bool            referencesData(const void* a_pInstance, const phantom::data& a_Data) const;
    virtual void            fetchExpressions(Expression* a_pInstanceExpression, vector<Expression*>& out, filter a_Filter, uint a_uiSerializationMask) const;

    virtual LanguageElement*    solveElement(
        const string& a_strName
        , const vector<TemplateElement*>*
        , const vector<LanguageElement*>*
        , modifiers_t a_Modifiers = 0) const ;

    virtual Expression*         solveExpression( Expression* a_pLeftExpression
        , const string& a_strName 
        , const vector<TemplateElement*>* 
        , const vector<LanguageElement*>*
        , modifiers_t a_Modifiers /*= 0*/ ) const;

    virtual Expression*         solveOperator(const string& a_strOp, const vector<Expression*>& a_Expressions, modifiers_t a_Modifiers) const;

    virtual variant             compile(Compiler* a_pCompiler);

    virtual void                getElements( vector<LanguageElement*>& out, Class* a_pClass = nullptr) const;

    // Attributes
    void                        addAttribute(const string& a_strName, const variant& a_Variant);
    void                        removeAttribute( const string& a_strName );
    const variant&              getAttribute(const string& a_strName) const;

    InstanceMemberFunction*     getDestructor() const;

protected:
    virtual void                finalize();

    bool canBeDestroyed() const;
    void elementAdded(LanguageElement* a_pElement);
    void elementRemoved(LanguageElement* a_pElement);
    virtual Constructor*            createDefaultConstructor() const;
    virtual InstanceMemberFunction* createDestructor() const;

    vector<Constructor*>            getConstructors() const { return m_pConstructors ? *m_pConstructors : vector<Constructor*>(); }
    vector<StaticDataMember*>       getStaticDataMembers() const { return m_pStaticDataMembers ? *m_pStaticDataMembers : vector<StaticDataMember*>(); }
    vector<StaticMemberFunction*>   getStaticMemberFunctions() const { return m_pStaticMemberFunctions ? *m_pStaticMemberFunctions : vector<StaticMemberFunction*>(); }
    vector<AnonymousSection*>             getAnonymousSections() const { return m_pAnonymousSections ? *m_pAnonymousSections : vector<AnonymousSection*>(); }
    vector<Property*>               getProperties() const { return m_Properties; }
    vector<InstanceDataMember*>     getInstanceDataMembers() const { return m_InstanceDataMembers; }
    vector<InstanceMemberFunction*> getInstanceMemberFunctions() const { return m_InstanceMemberFunctions; }

    virtual void                    setConstructors(vector<Constructor*> list);
    virtual void                    setStaticDataMembers(vector<StaticDataMember*> list);
    virtual void                    setStaticMemberFunctions(vector<StaticMemberFunction*>);
    virtual void                    setAnonymousSections(vector<AnonymousSection*> list);
    virtual void                    setProperties(vector<Property*> list);
    virtual void                    setInstanceDataMembers(vector<InstanceDataMember*> list);
    virtual void                    setInstanceMemberFunctions(vector<InstanceMemberFunction*> list);


protected:
    vector<ValueMember*>            m_ValueMembers;
    vector<Property*>               m_Properties;
    vector<InstanceDataMember*>     m_InstanceDataMembers;
    vector<InstanceMemberFunction*> m_InstanceMemberFunctions;
    
    // less frequent => use vector ptrs
    vector<Constructor*>*           m_pConstructors;
    vector<StaticDataMember*>*      m_pStaticDataMembers;
    vector<StaticMemberFunction*>*  m_pStaticMemberFunctions;
    vector<AnonymousSection*>*            m_pAnonymousSections;
    extra_data*                     m_pExtraData;

    void*                           m_pAttributes; // use pimpl to avoid need to include variant type

};



o_namespace_end(phantom, reflection)



#endif
