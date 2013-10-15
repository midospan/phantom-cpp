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

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
/* ** The Class Header must be the last #include * */
#include "ClassType.h"
/* *********************************************** */
o_cpp_begin 

ReflectionCPP__________________________________________________________________________________
__________________________________________________________________________________ReflectionCPP

ClassType::~ClassType( void )
{
    destroyContent();
}

void ClassType::destroyContent()
{
    {
        auto membersCopy = m_Members;
        member_collection::iterator it = membersCopy.begin();
        for(;it!=membersCopy.end();it++)
        {
            o_dynamic_delete_clean(it->second);
        }
        m_Members.clear();
    }

    if(m_pTemplateSpecialization)
    {
        o_dynamic_delete_clean(m_pTemplateSpecialization);
        m_pTemplateSpecialization = nullptr;
    }
}

Attribute* ClassType::getAttribute( const string& a_strName) const
{
    Attribute* pAttribute = getInstanceAttribute(a_strName);
    if(pAttribute != NULL) return pAttribute;
    return getStaticAttribute(a_strName);
}

void    ClassType::addMember( LanguageElement* a_pMember )
{
    addElement(a_pMember);
    m_Members.insert(member_pair(a_pMember->getSortingCategoryClass(), a_pMember));
}

void    ClassType::removeMember( LanguageElement* a_pMember )
{
    member_collection::const_iterator it = m_Members.lower_bound(a_pMember->getSortingCategoryClass());
    member_collection::const_iterator end = m_Members.upper_bound(a_pMember->getSortingCategoryClass());
    for(; it != end; ++it)
    {
        if(it->second == a_pMember)
        {
            m_Members.erase(it);
            return;
        }
    }
    o_assert(false);
}

InstanceAttribute* ClassType::getInstanceAttribute( const string& a_strName) const
{
    member_collection::const_iterator it = m_Members.lower_bound(classOf<Property>());
    member_collection::const_iterator end = m_Members.upper_bound(classOf<Property>());
    for(; it != end; ++it)
    {
        if(NOT(it->second->isInstanceAttribute())) continue;
        InstanceAttribute* pAttribute = static_cast<InstanceAttribute*>(it->second);
        if(pAttribute->getName() == a_strName)
            return pAttribute;
    }
    return NULL;
}

Constructor* ClassType::getConstructor( const string& a_strIdentifierString ) const
{
    //deprecated
    member_collection::const_iterator it = m_Members.lower_bound(classOf<Constructor>());
    member_collection::const_iterator end = m_Members.upper_bound(classOf<Constructor>());
    for(; it != end; ++it)
    {
        Constructor* pCtor = static_cast<Constructor*>(it->second);
    //    if(pCtor->getIdentifierString() == a_strIdentifierString)
        {
            return pCtor;
        }
    }    
    return NULL;
}

void ClassType::valueToString( string& s, void* src ) const
{
    member_const_iterator it = m_Members.lower_bound(classOf<Property>());
    member_const_iterator end = m_Members.upper_bound(classOf<Property>());
    byte scratch[phantom::max_type_size];
    s += '{';
    int c = 0;
    for(; it != end; ++it)
    {
        if(c != 0)
        {
            s += ';';
        }
        Property* pProperty = static_cast<Property*>(it->second);
        s += pProperty->getName();
        s += '=';
        pProperty->getValue(src, scratch);
        pProperty->getValueType()->valueToString(s, scratch);
        ++c;
    }
    s += '}';
}

void ClassType::valueFromString( const string& cs, void* dest ) const
{
    o_exception(exception::unsupported_method_exception, "TODO (not supported yet)");
    member_collection::const_iterator it = m_Members.lower_bound(classOf<InstanceAttribute>());
    member_collection::const_iterator end = m_Members.upper_bound(classOf<InstanceAttribute>());
    for(; it != end; ++it)
    {
        InstanceAttribute* pAttribute = static_cast<InstanceAttribute*>(it->second);
        // TODO : implement
    }
}

void ClassType::setTemplateSpecialization( TemplateSpecialization* a_pTemplateSpecialization )
{
    o_assert(m_pTemplateSpecialization == NULL);
    m_pTemplateSpecialization = a_pTemplateSpecialization;
    //m_strName += m_pTemplateSpecialization->getName();
}

InstanceMethod* ClassType::getInstanceMethod( const string& a_strIdentifierString ) const
{
    LanguageElement* pElement = phantom::elementByName(a_strIdentifierString, const_cast<ClassType*>(this));
    return (pElement AND pElement->isInstanceMethod()) 
                ? static_cast<InstanceMethod*>(pElement)
                : NULL;
}

LanguageElement*            ClassType::getElement(
    const char* a_strName 
    , template_specialization const* a_TemplateSpecialization
    , function_signature const* a_FunctionSignature
    , bitfield a_bfModifiers /*= bitfield()*/) const 
{
    LanguageElement* pElement = Type::getElement(a_strName, a_TemplateSpecialization, a_FunctionSignature, a_bfModifiers);
    if(pElement) return pElement;
    if(m_pTemplateSpecialization)
    {
        pElement = m_pTemplateSpecialization->getType(a_strName);
        if(pElement) return pElement;
    }
    if(a_FunctionSignature == NULL)
    {
        StaticAttribute* pStaticAttribute = getStaticAttribute(a_strName);
        if(pStaticAttribute)
        {
            return pStaticAttribute->asLanguageElement();
        }
        return getProperty(a_strName);
    }
    Method* pMethod = getMethod(a_strName, a_FunctionSignature, a_bfModifiers);
    return pMethod ? pMethod->asLanguageElement() : NULL;
}

InstanceMethod* ClassType::getInstanceMethod( const string& a_strName, function_signature const* a_FunctionSignature, bitfield a_bfModifiers /*= bitfield()*/ ) const
{
  member_collection::const_iterator it = m_Members.lower_bound(classOf<InstanceMethod>());
  member_collection::const_iterator end = m_Members.upper_bound(classOf<InstanceMethod>());
  for(; it != end; ++it)
  {
    InstanceMethod* pMethod = static_cast<InstanceMethod*>(it->second);
    if(pMethod->matches(a_strName, a_FunctionSignature, a_bfModifiers))
          return pMethod;
  }
  return NULL;
}

StaticMethod* ClassType::getStaticMethod( const string& a_strName, function_signature const* a_FunctionSignature, bitfield a_bfModifiers /*= bitfield()*/ ) const
{
    member_collection::const_iterator it = m_Members.lower_bound(classOf<StaticMethod>());
    member_collection::const_iterator end = m_Members.upper_bound(classOf<StaticMethod>());
    for(; it != end; ++it)
    {
        StaticMethod* pMethod = static_cast<StaticMethod*>(it->second);
        if(pMethod->matches(a_strName, a_FunctionSignature, a_bfModifiers))
            return pMethod;
    }
    return NULL;
}

StaticMethod* ClassType::getStaticMethod( const string& a_strIdentifierString ) const
{
    LanguageElement* pElement = phantom::elementByName(a_strIdentifierString, const_cast<ClassType*>(this));
    return pElement AND pElement->isStaticMethod() 
        ? static_cast<StaticMethod*>(pElement)
        : NULL;
}

Method* ClassType::getMethod(const string& a_strIdentifierString) const
{
    Method* pMethod = getInstanceMethod(a_strIdentifierString);
    if(pMethod != NULL) return pMethod;
    return getStaticMethod(a_strIdentifierString);
}

Method* ClassType::getMethod(const string& a_strName, function_signature const* a_FunctionSignature, bitfield a_bfModifiers /*= bitfield()*/) const
{
    Method* pMethod = getInstanceMethod(a_strName, a_FunctionSignature, a_bfModifiers);
    if(pMethod != NULL) return pMethod;
    return getStaticMethod(a_strName, a_FunctionSignature, a_bfModifiers);
}
/*

phantom::string ClassType::getQualifiedName() const
{
    string        str ;
    if(m_pNamespace != NULL) 
    {
        m_pNamespace->getHierarchicalNameNoRoot(&str);
        if(NOT(str.empty()))
            str+=o_CC('.');
    }
    str += m_strName.substr(0, m_strName.find_first_of(o_CC('<'))) ;
    return str;
}*/


StaticAttribute* ClassType::getStaticAttribute( const string& a_strName) const
{
    member_collection::const_iterator it = m_Members.lower_bound(classOf<StaticAttribute>());
    member_collection::const_iterator end = m_Members.upper_bound(classOf<StaticAttribute>());
    for(; it != end; ++it)
    {
        StaticAttribute* pAttribute = static_cast<StaticAttribute*>(it->second);
        if(pAttribute->getName() == a_strName)
            return pAttribute;
    }
    return NULL;
}

void ClassType::addInstanceMethod( InstanceMethod* a_pMethod )
{
    addMember(a_pMethod);
}

void ClassType::addStaticMethod( StaticMethod* a_pMethod )
{
    addMember(a_pMethod);
}

void ClassType::addMethod( Method* a_pMethod )
{
    addMember(a_pMethod->asLanguageElement());
}

void ClassType::getAllMember( vector<LanguageElement*>& out ) const
{
    member_collection::const_iterator it = m_Members.begin();
    for(;it != m_Members.end(); ++it)
    {
        out.push_back(it->second);
    }
}

Property* ClassType::getProperty( const string& a_strName ) const
{
    member_collection::const_iterator it = m_Members.lower_bound(classOf<Property>());
    member_collection::const_iterator end = m_Members.upper_bound(classOf<Property>());
    for(; it != end; ++it)
    {
        Property* pProperty = static_cast<Property*>(it->second);
        if(pProperty->getName() == a_strName)
            return pProperty;
    }
    return nullptr;
}

Collection* ClassType::getCollection( const string& a_strName ) const
{
    member_collection::const_iterator it = m_Members.lower_bound(classOf<Collection>());
    member_collection::const_iterator end = m_Members.upper_bound(classOf<Collection>());
    for(; it != end; ++it)
    {
        if(it->second->getName() == a_strName)
            return (Collection*)it->second;
    }
    return nullptr;
}

phantom::string ClassType::getDecoratedName() const
{
    return m_pTemplateSpecialization?getName()+m_pTemplateSpecialization->getDecoratedName():getName();
}

phantom::string ClassType::getQualifiedDecoratedName() const
{
    return m_pTemplateSpecialization?getQualifiedName()+m_pTemplateSpecialization->getQualifiedDecoratedName():getQualifiedName();
}

boolean ClassType::matches( template_specialization const* a_pElements ) const
{
    return m_pTemplateSpecialization
            ? m_pTemplateSpecialization->matches(a_pElements)
            : NULL;
}


ClassType::member_const_iterator ClassType::propertiesBegin() const
{
    return m_Members.lower_bound(classOf<Property>());
}

ClassType::member_const_iterator ClassType::propertiesEnd() const
{
    return m_Members.upper_bound(classOf<Property>());
}

void                    ClassType::addConstructor( Constructor* a_pConstructor )
{
    o_assert(getConstructor(""));
    addMember(a_pConstructor);
}

void                ClassType::addProperty(Property* a_pProperty)
{
    o_assert(getProperty(a_pProperty->getName()) == NULL);
    if(a_pProperty->isReset())
    {
        m_uiResetSize += a_pProperty->getValueType()->getResetSize(); 
    }
    addMember(a_pProperty);
}
void                ClassType::addAccessor( Accessor* a_pAccessor )
{
    addMember(a_pAccessor);
}
void                ClassType::addCollection( Collection* a_pCollection)
{
    addMember(a_pCollection);
}
void                ClassType::addAttribute(Attribute* a_pAttribute)
{
    addMember(a_pAttribute->asLanguageElement());
}
void                ClassType::addInstanceAttribute(InstanceAttribute* a_pAttribute)
{
    addMember(a_pAttribute);
}
void                ClassType::addStaticAttribute(StaticAttribute* a_pAttribute)
{
    addMember(a_pAttribute);
}

void ClassType::interpolate( void* a_src_start, void* a_src_end, real a_fPercent, void* a_pDest, uint mode /*= 0*/ ) const
{
    member_const_iterator it = m_Members.lower_bound(classOf<Property>());
    member_const_iterator end = m_Members.upper_bound(classOf<Property>());
    byte scratch_start[phantom::max_type_size];
    byte scratch_end[phantom::max_type_size];
    byte scratch_result[phantom::max_type_size];
    for(; it != end; ++it)
    {
        Property* pProperty = static_cast<Property*>(it->second);
        pProperty->getValue(a_src_start, scratch_start);
        pProperty->getValue(a_src_end, scratch_end);
        pProperty->getValueType()->interpolate(scratch_start, scratch_end, a_fPercent, scratch_result);
        pProperty->setValue(a_pDest, scratch_result);
    }
}

void* ClassType::newInstance( Constructor* a_pConstructor, argument::list* a_pArgs ) const
{
    void* pInstance = o_dynamic_pool_allocate(m_uiSize);
    a_pConstructor->construct(pInstance, a_pArgs);
    return pInstance;
}

void* ClassType::newInstance( Constructor* a_pConstructor, void** a_pArgs /*= NULL*/ ) const
{
    void* pInstance = o_dynamic_pool_allocate(m_uiSize);
    a_pConstructor->construct(pInstance, a_pArgs);
    return pInstance;
}

void* ClassType::newInstance() const
{
  void* pInstance = o_dynamic_pool_allocate(m_uiSize);
  construct(pInstance);
  return pInstance;
}

boolean ClassType::matches( const char* a_strName, template_specialization const* a_TemplateSpecialization /*= NULL*/, bitfield a_bfModifiers /*= 0*/ ) const
{
  if(m_strName != a_strName) 
    return false;
  bool ts_empty = a_TemplateSpecialization == NULL OR a_TemplateSpecialization->empty() ;
  if(ts_empty AND m_pTemplateSpecialization == NULL) 
    return true;
  if(!ts_empty AND m_pTemplateSpecialization != NULL) 
  {
    return m_pTemplateSpecialization->matches(a_TemplateSpecialization);
  }
  return false;
}

size_t ClassType::getPropertyCount() const
{
    return m_Members.count(classOf<Property>());
}

size_t ClassType::getCollectionCount() const
{
    return m_Members.count(classOf<Collection>());
}

size_t ClassType::getInstanceMethodCount() const
{
    return m_Members.count(classOf<InstanceMethod>());
}

size_t ClassType::getStaticMethodCount() const
{
    return m_Members.count(classOf<StaticMethod>());
}

void ClassType::findPublicPropertiesPointingValueType( Type* a_pType, vector<Property*>& out ) const
{
    member_const_iterator it = m_Members.lower_bound(classOf<Property>());
    member_const_iterator end = m_Members.upper_bound(classOf<Property>());
    for(; it != end; ++it)
    {
        Property* pProperty = static_cast<Property*>(it->second);
        DataPointerType* pPointerType = pProperty->getValueType()->asDataPointerType();
        if(pPointerType AND pProperty->isPublic() AND a_pType->isKindOf(pPointerType->getPointedType()))
        {
            out.push_back(pProperty);
        }
    }
}

void ClassType::getAllProperty(vector<Property*>& out) const
{
    member_collection::const_iterator it = m_Members.lower_bound(classOf<Property>());
    member_collection::const_iterator end = m_Members.upper_bound(classOf<Property>());
    for(;it != end; ++it)
    {
        out.push_back(static_cast<Property*>(it->second));
    }
}

void ClassType::getAllCollection(vector<Collection*>& out) const
{
    member_collection::const_iterator it = m_Members.lower_bound(classOf<Collection>());
    member_collection::const_iterator end = m_Members.upper_bound(classOf<Collection>());
    for(;it != end; ++it)
    {
        out.push_back(static_cast<Collection*>(it->second));
    }
}

void        ClassType::smartCopy(void* a_pInstance, void const* a_pSource, reflection::Type* a_pSourceType) const
{
    ClassType* pSourceClassType = a_pSourceType->asClassType();
    o_assert(pSourceClassType);
    auto it = pSourceClassType->propertiesBegin();
    auto end = pSourceClassType->propertiesEnd();
    for(; it!=end; ++it)
    {
        reflection::Property* pOldProperty = (Property*)it->second;
        reflection::Property* pNewProperty = getProperty(pOldProperty->getName());
        reflection::Type* pOldPropertyType = pOldProperty->getValueType();
        reflection::Type* pNewPropertyType = nullptr;
        if(pNewProperty != nullptr 
            AND pOldPropertyType->isImplicitlyConvertibleTo((pNewPropertyType = pNewProperty->getValueType())))
        {
            void* sourceBuffer = pOldPropertyType->newInstance();
            pOldProperty->getValue(a_pSource, sourceBuffer);
            void* newBuffer = pNewPropertyType->newInstance();
            pOldPropertyType->convertValueTo(pNewPropertyType, newBuffer, sourceBuffer);
            pNewProperty->setValue(a_pInstance, newBuffer);
            pOldPropertyType->deleteInstance(pOldProperty);
            pNewPropertyType->deleteInstance(newBuffer);
        }
    }
}

InstanceMethod* ClassType::getUniqueInstanceMethodWithName( const string& a_strName ) const
{
    InstanceMethod* pInstanceMethod = nullptr;
    member_collection::const_iterator it = m_Members.lower_bound(classOf<InstanceMethod>());
    member_collection::const_iterator end = m_Members.upper_bound(classOf<InstanceMethod>());
    for(;it != end; ++it)
    {
        if(static_cast<InstanceMethod*>(it->second)->getName() == a_strName)
        {
            if(pInstanceMethod) return nullptr;
            pInstanceMethod = static_cast<InstanceMethod*>(it->second);
        }
    }
    return pInstanceMethod;
}

void ClassType::getElements( vector<LanguageElement*>& out, Class* a_pClass ) const
{
    Type::getElements(out, a_pClass);
    auto it = m_Members.begin();
    auto end = m_Members.end();
    if(a_pClass == nullptr)
    {
        for(;it != end; ++it)
        {
            out.push_back(it->second);
        }
    }
    else 
    {
        Class* pCurrentClass = nullptr;
        bool bCurrentClassAccepted = false;
        for(;it != end; ++it)
        {
            if(pCurrentClass == nullptr OR pCurrentClass != it->first)
            {
                pCurrentClass = it->first;
                bCurrentClassAccepted = pCurrentClass->isKindOf(a_pClass);
            }
            if(bCurrentClassAccepted)
            {
                out.push_back(it->second);
            }
            it->second->getElements(out, a_pClass);
        }
    }
}

o_cpp_end