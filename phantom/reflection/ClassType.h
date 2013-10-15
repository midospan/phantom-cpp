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
    typedef phantom::map<string, Method*>                method_map;
    typedef phantom::multimap<Class*, LanguageElement*>    member_collection;
    typedef phantom::vector<InstanceMethod*>                instance_method_list;
    typedef phantom::vector<Type*>                        type_vector;
    typedef phantom::vector<Method*>                    method_vector;
    typedef phantom::vector<InstanceMethod*>            instance_method_vector;
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
    void                    getAllProperty(vector<Property*>& out) const;
    void                    getAllCollection(vector<Collection*>& out) const;


    virtual void            addConstructor( Constructor* a_pConstructor );
    virtual void            addProperty( Property* a_pProperty );
    virtual void            addAttribute( Attribute* a_pAttribute );
    virtual void            addStaticAttribute( StaticAttribute* a_pAttribute );
    virtual void            addInstanceAttribute( InstanceAttribute* a_pAttribute );
    virtual void            addCollection( Collection* a_pCollection );
    virtual void            addAccessor( Accessor* a_pAccessor );
    virtual void            addMethod(Method* a_MetaMethod);
    virtual void            addInstanceMethod(InstanceMethod* a_MetaMethod);
    virtual void            addStaticMethod(StaticMethod* a_MetaMethod);

    Constructor*            getConstructor( const string& a_strIdentifierString ) const;
    Property*               getProperty(const string& a_strName) const;
    size_t                  getPropertyCount() const;
    Collection*               getCollection(const string& a_strName) const;
    size_t                  getCollectionCount() const;
    Attribute*              getAttribute(const string& a_strName) const;
    InstanceAttribute*      getInstanceAttribute(const string& a_strName) const;
    StaticAttribute*        getStaticAttribute(const string& a_strName) const;
    Method*                 getMethod(const string& a_strIdentifierString) const;
    Method*                 getMethod(const string& a_strName, function_signature const* a_FunctionSignature, bitfield a_bfModifiers = bitfield()) const;
    InstanceMethod*         getInstanceMethod(const string& a_strIdentifierString) const;
    InstanceMethod*         getInstanceMethod(const string& a_strName, function_signature const* a_FunctionSignature, bitfield a_bfModifiers = bitfield()) const;
    size_t                  getInstanceMethodCount() const;
    StaticMethod*           getStaticMethod( const string& a_strIdentifierString ) const;
    StaticMethod*           getStaticMethod( const string& a_strName, function_signature const* a_FunctionSignature, bitfield a_bfModifiers /*= bitfield()*/ ) const;
    size_t                  getStaticMethodCount() const;

    InstanceMethod*         getUniqueInstanceMethodWithName(const string& a_strName) const;

    void                    findPublicPropertiesPointingValueType(Type* a_pType, vector<Property*>& out) const;

    void                    setTemplateSpecialization(TemplateSpecialization* a_pTemplateSpecialization);
    TemplateSpecialization* getTemplateSpecialization() const { return m_pTemplateSpecialization; }

    member_const_iterator   propertiesBegin() const;
    member_const_iterator   propertiesEnd() const;

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
