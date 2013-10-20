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

/* *********************************************** */
/* The *.classdef.h file must be the last #include */
#include "ClassType.classdef.h"
/* **************** Declarations ***************** */
/* *********************************************** */

o_h_begin

class o_export ClassType : public Type
{
public:
    typedef phantom::reflection::Class*                    member_key;
    typedef std::pair<member_key, LanguageElement*>        member_pair;
    typedef phantom::map<string, MemberFunction*>                member_function_map;
    typedef phantom::multimap<Class*, LanguageElement*>    member_collection;
    typedef phantom::vector<InstanceMemberFunction*>                instance_member_function_list;
    typedef phantom::vector<Type*>                        type_vector;
    typedef phantom::vector<MemberFunction*>                    member_function_vector;
    typedef phantom::vector<InstanceMemberFunction*>            instance_member_function_vector;
    typedef member_collection::const_iterator            member_const_iterator;

    Reflection_____________________________________________________________________________________
        _____________________________________________________________________________________Reflection
public:

    ClassType(const string& a_strName, bitfield a_bfModifiers = bitfield())
        : Type(a_strName, a_bfModifiers)
        , m_pTemplateSpecialization(NULL)
    {
        m_uiSerializedSize = m_uiResetSize = 0;
    }

    ClassType(const string& a_strName, ushort a_uiSize, ushort a_uiAlignment, bitfield a_bfModifiers = bitfield())
        : Type(a_strName, a_uiSize, a_uiAlignment, a_bfModifiers)
        , m_pTemplateSpecialization(NULL)
    {
        m_uiSerializedSize = m_uiResetSize = 0;
    }

    o_destructor ~ClassType(void);

    virtual void            destroyContent();

    virtual ClassType*      asClassType() const { return const_cast<ClassType*>(this); }

    virtual boolean         isTemplateSpecialization() const { return m_pTemplateSpecialization != NULL; }
    virtual boolean         matches(template_specialization const* a_pElements) const;

    string                  getDecoratedName() const;
    string                  getQualifiedDecoratedName() const;

    void                    getAllMember(vector<LanguageElement*>& a_out) const;
    void                    getAllValueMember(vector<ValueMember*>& out) const;
    void                    getAllCollection(vector<Collection*>& out) const;


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

    Constructor*            getConstructor( const string& a_strIdentifierString ) const;
    ValueMember*               getValueMember(const string& a_strName) const;
    size_t                  getValueMemberCount() const;
    Collection*             getCollection(const string& a_strName) const;
    size_t                  getCollectionCount() const;
    DataMember*             getDataMember(const string& a_strName) const;
    InstanceDataMember*     getInstanceDataMember(const string& a_strName) const;
    StaticDataMember*       getStaticDataMember(const string& a_strName) const;
    MemberFunction*         getMemberFunction(const string& a_strIdentifierString) const;
    MemberFunction*         getMemberFunction(const string& a_strName, function_signature const* a_FunctionSignature, bitfield a_bfModifiers = bitfield()) const;
    InstanceMemberFunction* getInstanceMemberFunction(const string& a_strIdentifierString) const;
    InstanceMemberFunction* getInstanceMemberFunction(const string& a_strName, function_signature const* a_FunctionSignature, bitfield a_bfModifiers = bitfield()) const;
    size_t                  getInstanceMemberFunctionCount() const;
    StaticMemberFunction*   getStaticMemberFunction( const string& a_strIdentifierString ) const;
    StaticMemberFunction*   getStaticMemberFunction( const string& a_strName, function_signature const* a_FunctionSignature, bitfield a_bfModifiers /*= bitfield()*/ ) const;
    size_t                  getStaticMemberFunctionCount() const;

    InstanceMemberFunction* getUniqueInstanceMemberFunctionWithName(const string& a_strName) const;

    void                    findPublicPropertiesPointingValueType(Type* a_pType, vector<ValueMember*>& out) const;

    void                    setTemplateSpecialization(TemplateSpecialization* a_pTemplateSpecialization);
    TemplateSpecialization* getTemplateSpecialization() const { return m_pTemplateSpecialization; }

    member_const_iterator   valueMembersBegin() const;
    member_const_iterator   valueMembersEnd() const;

    virtual void*           newInstance() const;

    virtual void*           newInstance(Constructor* a_pConstructor, argument::list* a_pArgs) const;
    virtual void*           newInstance(Constructor* a_pConstructor, void** a_pArgs = NULL) const;
    virtual void            deleteInstance(void* a_pObject) const = 0;
    virtual void            safeDeleteInstance(void* a_pObject) const { deleteInstance(a_pObject); }

    virtual void            interpolate(void* a_src_start, void* a_src_end, real a_fPercent, void* a_pDest, uint mode = 0) const;
    virtual void            valueFromString( const string& cs, void* dest ) const;
    virtual void            valueToString( string& s, void* src ) const;

    virtual boolean         matches(const char* a_strName, template_specialization const* a_TemplateSpecialization = NULL, bitfield a_bfModifiers = bitfield()) const;
    virtual void            smartCopy(void* a_Instance, void const* a_pSource, reflection::Type* a_pSourceType) const;
    virtual boolean         isClassType() const { return true; }

    virtual LanguageElement*getElement(
        const char* a_strQualifiedName
        , template_specialization const*
        , function_signature const*
        , bitfield a_bfModifiers = bitfield()) const ;

    virtual void getElements( vector<LanguageElement*>& out, Class* a_pClass = nullptr) const;


protected:
    void                    addMember( LanguageElement* a_pMember );
    void                    removeMember( LanguageElement* a_pMember );
    
    virtual void            teardownMetaDataCascade(size_t count)
    {
        member_collection::const_iterator it = m_Members.begin();
        member_collection::const_iterator end = m_Members.end();
        for(;it != end; ++it)
        {
            it->second->teardownMetaDataCascade(count);
        }
        Type::teardownMetaDataCascade(count);
    }

protected:
    member_collection       m_Members;
    TemplateSpecialization* m_pTemplateSpecialization;

};



o_h_end


#else // o_phantom_reflection_ClassType_h__
#include "ClassType.classdef.h"
#endif
