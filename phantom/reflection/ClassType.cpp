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

ClassType::ClassType( const string& a_strName, bitfield a_Modifiers /*= 0*/ ) 
    : Type(a_strName, a_Modifiers)
    , m_pAttributes(nullptr)
{
    m_uiSerializedSize = m_uiResetSize = 0;
}

ClassType::ClassType( const string& a_strName, ushort a_uiSize, ushort a_uiAlignment, bitfield a_Modifiers /*= 0*/ ) 
    : Type(a_strName, a_uiSize, a_uiAlignment, a_Modifiers)
    , m_pAttributes(nullptr)
{
    m_uiSerializedSize = m_uiResetSize = 0;
}

ClassType::~ClassType( void )
{
    destroyContent();
}

void ClassType::destroyContent()
{
    if(m_pAttributes)
    {
        delete ((map<string, variant>*)m_pAttributes);
        m_pAttributes = nullptr;
    }
}

DataMember* ClassType::getDataMember( const string& a_strName) const
{
    DataMember* pDataMember = getInstanceDataMember(a_strName);
    if(pDataMember != NULL) return pDataMember;
    return getStaticDataMember(a_strName);
}

void ClassType::elementAdded(LanguageElement* a_pElement)
{
    Type::elementAdded(a_pElement);
    m_Members.insert(member_pair(a_pElement->getSortingCategoryClass(), a_pElement));
}

void ClassType::elementRemoved(LanguageElement* a_pElement)
{
    Type::elementRemoved(a_pElement);
    member_collection::const_iterator it = m_Members.lower_bound(a_pElement->getSortingCategoryClass());
    member_collection::const_iterator end = m_Members.upper_bound(a_pElement->getSortingCategoryClass());
    for(; it != end; ++it)
    {
        if(it->second == a_pElement)
        {
            m_Members.erase(it);
            return;
        }
    }
    o_assert(false);
}

InstanceDataMember* ClassType::getInstanceDataMember( const string& a_strName) const
{
    member_collection::const_iterator it = m_Members.lower_bound(classOf<ValueMember>());
    member_collection::const_iterator end = m_Members.upper_bound(classOf<ValueMember>());
    for(; it != end; ++it)
    {
        InstanceDataMember* pDataMember = it->second->asInstanceDataMember();
        if(pDataMember && pDataMember->getName() == a_strName)
            return pDataMember;
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

void ClassType::valueToString( string& s, const void* src ) const
{
    member_const_iterator it = m_Members.lower_bound(classOf<ValueMember>());
    member_const_iterator end = m_Members.upper_bound(classOf<ValueMember>());
    if(it == end) 
        return;
    byte scratch[phantom::max_type_size];
    s += '{';
    int c = 0;
    for(; it != end; ++it)
    {
        if(c != 0)
        {
            s += ';';
            s += ' ';
        }
        ValueMember* pValueMember = static_cast<ValueMember*>(it->second);
        s += pValueMember->getName();
        s += '=';
        pValueMember->getValue(src, scratch);
        pValueMember->getValueType()->valueToString(s, scratch);
        ++c;
    }
    s += '}';
}

void ClassType::valueFromString( const string& cs, void* dest ) const
{
    o_exception(exception::unsupported_member_function_exception, "TODO (not supported yet)");
}

InstanceMemberFunction* ClassType::getInstanceMemberFunction( const string& a_strIdentifierString ) const
{
    LanguageElement* pElement = phantom::elementByName(a_strIdentifierString, const_cast<ClassType*>(this));
    return pElement ? pElement->asInstanceMemberFunction() : nullptr; 
}

LanguageElement*            ClassType::getElement(
    const char* a_strName 
    , template_specialization const* a_TemplateSpecialization
    , function_signature const* a_FunctionSignature
    , bitfield a_Modifiers /*= 0*/) const 
{
    LanguageElement* pElement = nullptr;
    pElement = Type::getElement(a_strName, a_TemplateSpecialization, a_FunctionSignature, a_Modifiers);
    if(pElement) return pElement;
    if(a_FunctionSignature == NULL)
    {
        StaticDataMember* pStaticDataMember = getStaticDataMember(a_strName);
        if(pStaticDataMember)
        {
            return pStaticDataMember->asLanguageElement();
        }
        return getValueMember(a_strName);
    }
    MemberFunction* pMemberFunction = getMemberFunction(a_strName, a_FunctionSignature, a_Modifiers);
    return pMemberFunction ? pMemberFunction->asLanguageElement() : NULL;
}

InstanceMemberFunction* ClassType::getInstanceMemberFunction( const string& a_strName, function_signature const* a_FunctionSignature, bitfield a_Modifiers /*= 0*/ ) const
{
  member_collection::const_iterator it = m_Members.lower_bound(classOf<InstanceMemberFunction>());
  member_collection::const_iterator end = m_Members.upper_bound(classOf<InstanceMemberFunction>());
  for(; it != end; ++it)
  {
    InstanceMemberFunction* pMemberFunction = static_cast<InstanceMemberFunction*>(it->second);
    if(pMemberFunction->matches(a_strName, a_FunctionSignature, a_Modifiers))
          return pMemberFunction;
  }
  return NULL;
}

StaticMemberFunction* ClassType::getStaticMemberFunction( const string& a_strName, function_signature const* a_FunctionSignature, bitfield a_Modifiers /*= 0*/ ) const
{
    member_collection::const_iterator it = m_Members.lower_bound(classOf<StaticMemberFunction>());
    member_collection::const_iterator end = m_Members.upper_bound(classOf<StaticMemberFunction>());
    for(; it != end; ++it)
    {
        StaticMemberFunction* pMemberFunction = static_cast<StaticMemberFunction*>(it->second);
        if(pMemberFunction->matches(a_strName, a_FunctionSignature, a_Modifiers))
            return pMemberFunction;
    }
    return NULL;
}

StaticMemberFunction* ClassType::getStaticMemberFunction( const string& a_strIdentifierString ) const
{
    LanguageElement* pElement = phantom::elementByName(a_strIdentifierString, const_cast<ClassType*>(this));
    return pElement ? pElement->asStaticMemberFunction() : nullptr; 
}

MemberFunction* ClassType::getMemberFunction(const string& a_strIdentifierString) const
{
    MemberFunction* pMemberFunction = getInstanceMemberFunction(a_strIdentifierString);
    if(pMemberFunction != NULL) return pMemberFunction;
    return getStaticMemberFunction(a_strIdentifierString);
}

MemberFunction* ClassType::getMemberFunction(const string& a_strName, function_signature const* a_FunctionSignature, bitfield a_Modifiers /*= 0*/) const
{
    MemberFunction* pMemberFunction = getInstanceMemberFunction(a_strName, a_FunctionSignature, a_Modifiers);
    if(pMemberFunction != NULL) return pMemberFunction;
    return getStaticMemberFunction(a_strName, a_FunctionSignature, a_Modifiers);
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


StaticDataMember* ClassType::getStaticDataMember( const string& a_strName) const
{
    member_collection::const_iterator it = m_Members.lower_bound(classOf<StaticDataMember>());
    member_collection::const_iterator end = m_Members.upper_bound(classOf<StaticDataMember>());
    for(; it != end; ++it)
    {
        StaticDataMember* pDataMember = static_cast<StaticDataMember*>(it->second);
        if(pDataMember->getName() == a_strName)
            return pDataMember;
    }
    return NULL;
}

void ClassType::addInstanceMemberFunction( InstanceMemberFunction* a_pMemberFunction )
{
    addElement(a_pMemberFunction);
}

void ClassType::addStaticMemberFunction( StaticMemberFunction* a_pMemberFunction )
{
    addElement(a_pMemberFunction);
}

void ClassType::addMemberFunction( MemberFunction* a_pMemberFunction )
{
    addElement(a_pMemberFunction->asLanguageElement());
}

void ClassType::getAllMember( vector<LanguageElement*>& out ) const
{
    member_collection::const_iterator it = m_Members.begin();
    for(;it != m_Members.end(); ++it)
    {
        out.push_back(it->second);
    }
}

ValueMember* ClassType::getValueMember( const string& a_strName ) const
{
    member_collection::const_iterator it = m_Members.lower_bound(classOf<ValueMember>());
    member_collection::const_iterator end = m_Members.upper_bound(classOf<ValueMember>());
    for(; it != end; ++it)
    {
        ValueMember* pValueMember = static_cast<ValueMember*>(it->second);
        if(pValueMember->getName() == a_strName)
            return pValueMember;
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


ClassType::member_const_iterator ClassType::valueMembersBegin() const
{
    return m_Members.lower_bound(classOf<ValueMember>());
}

ClassType::member_const_iterator ClassType::valueMembersEnd() const
{
    return m_Members.upper_bound(classOf<ValueMember>());
}

void                    ClassType::addConstructor( Constructor* a_pConstructor )
{
    o_assert(getConstructor(""));
    addElement(a_pConstructor);
}

void                ClassType::addValueMember(ValueMember* a_pValueMember)
{
    o_assert(getValueMember(a_pValueMember->getName()) == NULL);
    if(a_pValueMember->isReset())
    {
        m_uiResetSize += a_pValueMember->getValueType()->getResetSize(); 
    }
    addElement(a_pValueMember);
}
void                ClassType::addProperty( Property* a_pProperty )
{
    addElement(a_pProperty);
}
void                ClassType::addCollection( Collection* a_pCollection)
{
    addElement(a_pCollection);
}
void                ClassType::addDataMember(DataMember* a_pDataMember)
{
    addElement(a_pDataMember->asLanguageElement());
}
void                ClassType::addInstanceDataMember(InstanceDataMember* a_pDataMember)
{
    addElement(a_pDataMember);
}
void                ClassType::addStaticDataMember(StaticDataMember* a_pDataMember)
{
    addElement(a_pDataMember);
}

void ClassType::interpolate( void* a_src_start, void* a_src_end, real a_fPercent, void* a_pDest, uint mode /*= 0*/ ) const
{
    member_const_iterator it = m_Members.lower_bound(classOf<ValueMember>());
    member_const_iterator end = m_Members.upper_bound(classOf<ValueMember>());
    byte scratch_start[phantom::max_type_size];
    byte scratch_end[phantom::max_type_size];
    byte scratch_result[phantom::max_type_size];
    for(; it != end; ++it)
    {
        ValueMember* pValueMember = static_cast<ValueMember*>(it->second);
        pValueMember->getValue(a_src_start, scratch_start);
        pValueMember->getValue(a_src_end, scratch_end);
        pValueMember->getValueType()->interpolate(scratch_start, scratch_end, a_fPercent, scratch_result);
        pValueMember->setValue(a_pDest, scratch_result);
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

size_t ClassType::getValueMemberCount() const
{
    return m_Members.count(classOf<ValueMember>());
}

size_t ClassType::getCollectionCount() const
{
    return m_Members.count(classOf<Collection>());
}

size_t ClassType::getInstanceMemberFunctionCount() const
{
    return m_Members.count(classOf<InstanceMemberFunction>());
}

size_t ClassType::getStaticMemberFunctionCount() const
{
    return m_Members.count(classOf<StaticMemberFunction>());
}

void ClassType::findPublicPropertiesPointingValueType( Type* a_pType, vector<ValueMember*>& out ) const
{
    member_const_iterator it = m_Members.lower_bound(classOf<ValueMember>());
    member_const_iterator end = m_Members.upper_bound(classOf<ValueMember>());
    for(; it != end; ++it)
    {
        ValueMember* pValueMember = static_cast<ValueMember*>(it->second);
        DataPointerType* pPointerType = pValueMember->getValueType()->asDataPointerType();
        if(pPointerType AND pValueMember->isPublic() AND a_pType->isKindOf(pPointerType->getPointedType()))
        {
            out.push_back(pValueMember);
        }
    }
}

void ClassType::getAllValueMember(vector<ValueMember*>& out) const
{
    member_collection::const_iterator it = m_Members.lower_bound(classOf<ValueMember>());
    member_collection::const_iterator end = m_Members.upper_bound(classOf<ValueMember>());
    for(;it != end; ++it)
    {
        out.push_back(static_cast<ValueMember*>(it->second));
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
    auto it = pSourceClassType->valueMembersBegin();
    auto end = pSourceClassType->valueMembersEnd();
    for(; it!=end; ++it)
    {
        reflection::ValueMember* pOldValueMember = (ValueMember*)it->second;
        reflection::ValueMember* pNewValueMember = getValueMember(pOldValueMember->getName());
        reflection::Type* pOldValueMemberType = pOldValueMember->getValueType();
        reflection::Type* pNewValueMemberType = nullptr;
        if(pNewValueMember != nullptr 
            AND pOldValueMemberType->isImplicitlyConvertibleTo((pNewValueMemberType = pNewValueMember->getValueType())))
        {
            void* sourceBuffer = pOldValueMemberType->newInstance();
            pOldValueMember->getValue(a_pSource, sourceBuffer);
            void* newBuffer = pNewValueMemberType->newInstance();
            pOldValueMemberType->convertValueTo(pNewValueMemberType, newBuffer, sourceBuffer);
            pNewValueMember->setValue(a_pInstance, newBuffer);
            pOldValueMemberType->deleteInstance(pOldValueMember);
            pNewValueMemberType->deleteInstance(newBuffer);
        }
    }
}

InstanceMemberFunction* ClassType::getUniqueInstanceMemberFunctionWithName( const string& a_strName ) const
{
    InstanceMemberFunction* pInstanceMemberFunction = nullptr;
    member_collection::const_iterator it = m_Members.lower_bound(classOf<InstanceMemberFunction>());
    member_collection::const_iterator end = m_Members.upper_bound(classOf<InstanceMemberFunction>());
    for(;it != end; ++it)
    {
        if(static_cast<InstanceMemberFunction*>(it->second)->getName() == a_strName)
        {
            if(pInstanceMemberFunction) return nullptr;
            pInstanceMemberFunction = static_cast<InstanceMemberFunction*>(it->second);
        }
    }
    return pInstanceMemberFunction;
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

void ClassType::addAttribute( const string& a_strName, const variant& a_Variant )
{
    if(m_pAttributes == nullptr)
        m_pAttributes = new map<string, variant>;
    map<string, variant>* pAttributes = static_cast<map<string, variant>*>(m_pAttributes);
    (*pAttributes)[a_strName] = a_Variant;
}

void ClassType::removeAttribute( const string& a_strName )
{
    o_assert(m_pAttributes);
    map<string, variant>* pAttributes = static_cast<map<string, variant>*>(m_pAttributes);
    auto found = pAttributes->find(a_strName);
    o_assert(found != pAttributes->end());
    pAttributes->erase(found);
    if(pAttributes->empty())
    {
        delete ((map<string, variant>*)pAttributes);
        m_pAttributes = nullptr;
    }
}

const variant& ClassType::getAttribute( const string& a_strName ) const
{
    static variant null_variant;
    if(m_pAttributes == nullptr) return null_variant;
    map<string, variant>* pAttributes = static_cast<map<string, variant>*>(m_pAttributes);
    auto found = pAttributes->find(a_strName);
    if(found != pAttributes->end()) return found->second;
    return null_variant;
}

bool ClassType::canBeDestroyed() const
{
    return Type::canBeDestroyed();
}

void ClassType::teardownMetaDataCascade( size_t count )
{
    member_collection::const_iterator it = m_Members.begin();
    member_collection::const_iterator end = m_Members.end();
    for(;it != end; ++it)
    {
        it->second->teardownMetaDataCascade(count);
    }
    Type::teardownMetaDataCascade(count);
}



o_cpp_end