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
// #pragma message("Including "__FILE__)


/* ****************** Includes ******************* */


/* **************** Declarations ***************** */
/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export ClassType : public Type
{
    o_declare_meta_type(ClassType);

public:
    typedef phantom::reflection::Class*                    member_key;
    typedef std::pair<member_key, LanguageElement*>        member_pair;
    typedef phantom::map<string, MemberFunction*>                member_function_map;
    typedef phantom::multimap<Class*, LanguageElement*>    member_collection;
    typedef phantom::vector<InstanceMemberFunction*>                instance_member_function_list;
    typedef phantom::vector<Type*>                        type_vector;
    typedef phantom::vector<MemberFunction*>                    member_function_vector;
    typedef phantom::vector<InstanceMemberFunction*>            instance_member_function_vector;

public:

    ClassType(const string& a_strName, bitfield a_Modifiers = 0);
    ClassType(const string& a_strName, ushort a_uiSize, ushort a_uiAlignment, bitfield a_Modifiers = 0);
    o_destructor ~ClassType(void);

    virtual void            destroyContent();

    virtual ClassType*      asClassType() const { return const_cast<ClassType*>(this); }

    void                    getMembers(vector<LanguageElement*>& a_out) const;

    virtual void            addConstructor( Constructor* a_pConstructor );
    virtual void            addValueMember( ValueMember* a_pValueMember );
    virtual void            addDataMember( DataMember* a_pDataMember );
    virtual void            addStaticDataMember( StaticDataMember* a_pDataMember );
    virtual void            addInstanceDataMember( InstanceDataMember* a_pDataMember );
    virtual void            addCollection( Collection* a_pCollection );
    virtual void            addProperty( Property* a_pProperty );
    virtual void            addMemberFunction(MemberFunction* a_MetaMemberFunction);
    virtual void            addInstanceMemberFunction(InstanceMemberFunction* a_MetaMemberFunction);
    virtual void            addStaticMemberFunction(StaticMemberFunction* a_MetaMemberFunction);

    virtual void            removeConstructor( Constructor* a_pConstructor );
    virtual void            removeValueMember( ValueMember* a_pValueMember );
    virtual void            removeDataMember( DataMember* a_pDataMember );
    virtual void            removeStaticDataMember( StaticDataMember* a_pDataMember );
    virtual void            removeInstanceDataMember( InstanceDataMember* a_pDataMember );
    virtual void            removeCollection( Collection* a_pCollection );
    virtual void            removeProperty( Property* a_pProperty );
    virtual void            removeMemberFunction(MemberFunction* a_MetaMemberFunction);
    virtual void            removeInstanceMemberFunction(InstanceMemberFunction* a_MetaMemberFunction);
    virtual void            removeStaticMemberFunction(StaticMemberFunction* a_MetaMemberFunction);


    Constructor*            getConstructor( const string& a_strIdentifierString ) const;
    ValueMember*            getValueMember(const string& a_strName) const;
    size_t                  getValueMemberCount() const;
    Collection*             getCollection(const string& a_strName) const;
    size_t                  getCollectionCount() const;
    DataMember*             getDataMember(const string& a_strName) const;
    InstanceDataMember*     getInstanceDataMember(const string& a_strName) const;
    StaticDataMember*       getStaticDataMember(const string& a_strName) const;
    Property*               getProperty(const string& a_strName) const;
    MemberFunction*         getMemberFunction(const string& a_strIdentifierString) const;
    MemberFunction*         getMemberFunction(const string& a_strName, const vector<Type*>& a_Types, vector<size_t>* a_pPartialMatchesIndexes = nullptr, bitfield a_Modifiers = 0) const;
    InstanceMemberFunction* getInstanceMemberFunction(const string& a_strIdentifierString) const;
    InstanceMemberFunction* getInstanceMemberFunction(const string& a_strName, const vector<Type*>& a_Types, vector<size_t>* a_pPartialMatchesIndexes = nullptr, bitfield a_Modifiers = 0) const;
    size_t                  getInstanceMemberFunctionCount() const;
    StaticMemberFunction*   getStaticMemberFunction( const string& a_strIdentifierString ) const;
    StaticMemberFunction*   getStaticMemberFunction( const string& a_strName, const vector<Type*>& a_Types, vector<size_t>* a_pPartialMatchesIndexes = nullptr, bitfield a_Modifiers = 0 ) const;
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
    vector<Collection*>::const_iterator             beginCollections() const;
    vector<Collection*>::const_iterator             endCollections() const;

    virtual void*           newInstance() const;

    virtual void*           newInstance(Constructor* a_pConstructor, argument::list* a_pArgs) const;
    virtual void*           newInstance(Constructor* a_pConstructor, void** a_pArgs = NULL) const;
    virtual void            deleteInstance(void* a_pObject) const = 0;
    virtual void            safeDeleteInstance(void* a_pObject) const { deleteInstance(a_pObject); }

    virtual void            interpolate(void* a_src_start, void* a_src_end, real a_fPercent, void* a_pDest, uint mode = 0) const;
    virtual void            valueFromString( const string& cs, void* dest ) const;
    virtual void            valueToString( string& s, const void* src ) const;

    virtual void            smartCopy(void* a_Instance, void const* a_pSource, reflection::Type* a_pSourceType) const;

    virtual bool            referencesData(const void* a_pInstance, const phantom::data& a_Data) const;
    virtual void            fetchReferencedData(const void* a_pInstance, vector<phantom::data>& out, uint a_uiSerializationMask) const;

    virtual LanguageElement*    solveElement(
        const string& a_strName
        , const vector<TemplateElement*>*
        , const vector<LanguageElement*>*
        , bitfield a_Modifiers = 0) const ;

    virtual Expression*           solveExpression( Expression* a_pLeftExpression
        , const string& a_strName 
        , const vector<TemplateElement*>* 
        , const vector<LanguageElement*>*
        , bitfield a_Modifiers /*= 0*/ ) const;

    virtual LanguageElement* solveParenthesisOperator(const vector<LanguageElement*>& a_Signature) const
    {
        return nullptr; // TODO : return constructor ?
    }

    virtual void getElements( vector<LanguageElement*>& out, Class* a_pClass = nullptr) const;

    // Attributes
    void addAttribute(const string& a_strName, const variant& a_Variant);
    void removeAttribute( const string& a_strName );
    const variant& getAttribute(const string& a_strName) const;

protected:
    bool canBeDestroyed() const;
    void elementAdded(LanguageElement* a_pElement);
    void elementRemoved(LanguageElement* a_pElement);

protected:
    vector<ValueMember*>            m_ValueMembers;
    vector<Property*>               m_Properties;
    vector<InstanceDataMember*>     m_InstanceDataMembers;
    vector<InstanceMemberFunction*> m_InstanceMemberFunctions;
    
    // less frequent => use vector ptrs
    vector<StaticDataMember*>*      m_pStaticDataMembers;
    vector<StaticMemberFunction*>*  m_pStaticMemberFunctions;
    vector<Collection*>*            m_pCollections;

    void*                   m_pAttributes; // use pimpl to avoid need to include variant type

};



o_namespace_end(phantom, reflection)



#endif
