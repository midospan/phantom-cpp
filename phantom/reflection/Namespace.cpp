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
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp>
/* ** The Class Header must be the last #include * */
#include <phantom/reflection/Namespace.h>
/* *********************************************** */
o_cpp_begin 

ReflectionCPP__________________________________________________________________________________
    o_signal(typeAdded, (Type*))
    o_signal(typeRemoved, (Type*))
    o_signal(packageAdded, (Namespace*))
    o_signal(packageRemoved, (Namespace*))
__________________________________________________________________________________ReflectionCPP


Namespace::Namespace( void ) 
{
}

Namespace::Namespace( const string& a_strName ) 
    : LanguageElement(a_strName)
{
}

Namespace::~Namespace( void )
{
    destroyAllNamespaceCascade();
}


void Namespace::getHierarchicalName( string* a_OutString )
{
    if(getParentNamespace()) 
    {
        getParentNamespace()->getHierarchicalName(a_OutString);
        *a_OutString += o_CC('.');
    }
    *a_OutString += getName();
}

Type* Namespace::getType( const string& a_strName ) const
{
    vector<Type*>::const_iterator it = m_Types.begin();
    vector<Type*>::const_iterator end = m_Types.end();
    for(;it != end; ++it)
    {
        if((*it)->getName() == a_strName) return *it;
    }
    return false;
}

Type* Namespace::getTypeByGuid( uint a_uiGuid ) const
{
	vector<Type*>::const_iterator it = m_Types.begin();
	vector<Type*>::const_iterator end = m_Types.end();
	for(;it != end; ++it)
	{
		if((*it)->getGuid() == a_uiGuid) return *it;
	}
	return false;
}

Type*        Namespace::pointerTypeOf(Type* a_pType, uint a_uiPointerLevel /*= 1*/) 
{
    if(a_uiPointerLevel == 0) return a_pType;
    PointerType* pPointerType = getDataPointerType(a_pType);
    if(pPointerType == NULL)
    {
        pPointerType = a_pType->createDataPointerType();
        addType(pPointerType);
    }
    return pointerTypeOf(pPointerType, a_uiPointerLevel-1);
}

Type*        Namespace::referenceTypeOf(Type* a_pType, uint a_uiReferenceLevel /*= 1*/) 
{
    if(a_uiReferenceLevel == 0) return a_pType;
    ReferenceType* pReferenceType = getReferenceType(a_pType);
    if(pReferenceType == NULL)
    {
        pReferenceType = a_pType->createReferenceType();
        addType(pReferenceType);
    }
    return referenceTypeOf(pReferenceType, a_uiReferenceLevel-1);
}

Type*        Namespace::constTypeOf(Type* a_pType) 
{
    Type* pConstType = getConstType(a_pType);
    if(pConstType == NULL)
    {
        pConstType = a_pType->createConstType();
        addType(pConstType);
    }
    return pConstType;
}

Type*        Namespace::arrayTypeOf(Type* a_pType, size_t a_uiCount) 
{
    o_assert(a_uiCount > 0);
    Type* pArrayType = getArrayType(a_pType, a_uiCount);
    if(pArrayType == NULL)
    {
        pArrayType = a_pType->createArrayType(a_uiCount);
        addType(pArrayType);
    }
    return pArrayType;
}

Namespace* Namespace::getNamespaceCascade( list<string>* a_HierarchyWords ) const
{
    string str = a_HierarchyWords->front();
    a_HierarchyWords->pop_front();
    Namespace* childNamespace = getNamespace(str);
    if(NOT(childNamespace)) return NULL;
    if(a_HierarchyWords->empty())
    {
        return childNamespace;
    }
    else
    {
        return childNamespace->getNamespaceCascade(a_HierarchyWords);
    }
    return NULL;
}

Namespace*        Namespace::findOrCreateNamespaceCascade(list<string>* a_HierarchyWords) 
{
    if(a_HierarchyWords->empty()) return this;
    string str = a_HierarchyWords->front();
    a_HierarchyWords->pop_front();
    Namespace* childNamespace = getNamespace(str);
    if(NOT(childNamespace)) 
    {
        childNamespace = o_new(Namespace)(str);
        addNamespace(childNamespace);
    }
    if(a_HierarchyWords->empty())
    {
        return childNamespace;
    }
    else
    {
        return childNamespace->findOrCreateNamespaceCascade(a_HierarchyWords);
    }
    return NULL;
}

Namespace* Namespace::findOrCreateNamespaceCascade( const string& a_strNamespaceName )
{
    list<string> words;
    split( words, a_strNamespaceName, boost::is_any_of(":. "), boost::token_compress_on ); // SplitVec == { "hello abc","ABC","aBc goodbye" }
    words.erase( std::remove_if( words.begin(), words.end(), 
        boost::bind( &string::empty, _1 ) ), words.end() );
    return findOrCreateNamespaceCascade(&words);
}

Namespace* Namespace::getNamespace( const string& a_strName ) const
{
    o_foreach(Namespace* pNamespace, m_Namespaces)
    {
        if(pNamespace->getName() == a_strName) return pNamespace;
    }
    return NULL;
}

void Namespace::destroyAllNamespaceCascade()
{
    o_foreach(Namespace* pNamespace, m_Namespaces)
    {
        o_dynamic_delete_clean(pNamespace);
    }
}

void Namespace::destroyAllCascade()
{
    {
        o_foreach(Type* pType, m_Types)
        {
            o_dynamic_delete_clean(pType);
        }
        m_Types.clear();
    }
    {
        o_foreach(Namespace* pNamespace, m_Namespaces)
        {
            pNamespace->destroyAllCascade();
            o_dynamic_delete_clean(pNamespace);
        }
        m_Namespaces.clear();
    }
}

void Namespace::release(vector<Type*>& out_types)
{
    while(!m_Types.empty())
    {
        out_types.push_back(m_Types.back());
        removeType(m_Types.back());
    }
    while(!m_Namespaces.empty())
    {
        Namespace* pNamespace = m_Namespaces.back();
        pNamespace->release(out_types);
        removeNamespace(pNamespace);
        o_dynamic_delete_clean(pNamespace);
    }

}

boolean Namespace::searchAndDestroy( Type* a_pType )
{
    vector<Type*>::iterator found = std::find(m_Types.begin(), m_Types.end(), a_pType);
    if(found != m_Types.end()) 
    {
        m_Types.erase(found);
        o_dynamic_delete_clean(a_pType);
        return true;
    }
    return false;
}


boolean                Namespace::searchAndRemove(Type* a_pType)
{
    vector<Type*>::iterator found = std::find(m_Types.begin(), m_Types.end(), a_pType);
    if(found != m_Types.end()) 
    {
        m_Types.erase(found);
        return true;
    }
    return false;
}

boolean                Namespace::searchAndRemoveCascade(Type* a_pType)
{
    if(searchAndRemove(a_pType))
        return true;
    o_foreach(Namespace* pNamespace, m_Namespaces)
    {
        if(pNamespace->searchAndRemoveCascade(a_pType))
        {
            return true;
        }
    }
    return false;
}

boolean Namespace::searchAndDestroy( Namespace* a_pNamespace )
{
    vector<Namespace*>::iterator found = std::find(m_Namespaces.begin(), m_Namespaces.end(), a_pNamespace);
    if(found != m_Namespaces.end()) 
    {
        o_dynamic_delete_clean(a_pNamespace);
        m_Namespaces.erase(found);
        return true;
    }
    return false;
}

boolean Namespace::searchAndDestroyCascade( Type* a_pType )
{
    if(searchAndDestroy(a_pType))
        return true;

    o_foreach(Namespace* pNamespace, m_Namespaces)
    {
        if(pNamespace->searchAndDestroyCascade(a_pType))
        {
            return true;
        }
    }
    return false;
}

boolean Namespace::searchAndDestroyCascade( Namespace* a_pNamespace )
{
    if(searchAndDestroy(a_pNamespace))
        return true;

    o_foreach(Namespace* pNamespace, m_Namespaces)
    {
        if(pNamespace->searchAndDestroyCascade(a_pNamespace))
        {
            return true;
        }
    }
    return false;
}

void Namespace::addType( Type* a_pType )
{
    o_assert(a_pType->m_pOwner == NULL, "Type has already been attached to a Namespace");
    o_assert(getTypedef(a_pType->getName()) == NULL, "An Typedef has already been registered with this type's name");
    o_assert(std::find(m_Types.begin(), m_Types.end(), a_pType) == m_Types.end(), "Type already attached to this Namespace");
    m_Types.push_back(a_pType);
    addElement(a_pType);
    if(Phantom::getState() == Phantom::eState_Installed)
    {
        o_emit typeAdded(a_pType);
    }
}

void Namespace::removeType( Type* a_pType )
{
    o_assert(a_pType->m_pOwner == this, "This type is attached to another Namespace");
    vector<Type*>::iterator found = std::find(m_Types.begin(), m_Types.end(), a_pType);
    o_assert(found != m_Types.end(), "Type not found");
    m_Types.erase(found);
    removeElement(a_pType);
    if(Phantom::getState() == Phantom::eState_Installed)
    {
        o_emit typeRemoved(a_pType);
    }
}

void Namespace::addNamespace( Namespace* a_pNamespace )
{
    o_assert_not(getNamespace(a_pNamespace->getName()));
    m_Namespaces.push_back(a_pNamespace); 
    addElement(a_pNamespace);
    if(Phantom::getState() == Phantom::eState_Installed)
    {
        o_emit packageAdded(a_pNamespace);
    }
}

void Namespace::removeNamespace( Namespace* a_pNamespace )
{
    o_assert(a_pNamespace->getParentNamespace() == this, "This namespace is attached to another Namespace");
    vector<Namespace*>::iterator found = std::find(m_Namespaces.begin(), m_Namespaces.end(), a_pNamespace);
    o_assert(found != m_Namespaces.end(), "Namespace not found");
    m_Namespaces.erase(found);
    removeElement(a_pNamespace);
    if(Phantom::getState() == Phantom::eState_Installed)
    {
        o_emit packageRemoved(a_pNamespace);
    }
}

Namespace* Namespace::findTypeNamespace( Type* a_pType ) const
{
    {
        o_foreach(Type* pType, m_Types)
        {
            if(pType == a_pType)
                return const_cast<Namespace*>(this);
        }
    }
    {
        o_foreach(Namespace* pNamespace, m_Namespaces)
        {
            Namespace* pFoundNamespace = pNamespace->findTypeNamespace(a_pType);
            if(pFoundNamespace != NULL)
            {
                return pFoundNamespace;
            }
        }
    }
    return NULL;
}


void Namespace::removeAllTypeCascade()
{
    m_Types.clear();
    o_foreach(Namespace* pNamespace, m_Namespaces)
    {
        pNamespace->removeAllTypeCascade();
    }    
}

Namespace* Namespace::getRootNamespace() const
{
    if(getParentNamespace() == NULL) 
        return const_cast<Namespace*>(this); 
    return getParentNamespace()->getRootNamespace();
}

void Namespace::getHierarchicalNameNoRoot( string* a_OutString )
{
    if(getParentNamespace()) 
    {
        if(getParentNamespace()->getParentNamespace())
        {
            getParentNamespace()->getHierarchicalNameNoRoot(a_OutString);
            *a_OutString += o_CC('.');
        }
        *a_OutString += getName();
    }
    
}

PrimitiveType* Namespace::getPrimitiveType( const string& a_strName ) const
{
    Type* pType = getType(a_strName);
    if(pType->isPrimitiveType()) return static_cast<PrimitiveType*>(pType);
    return NULL;
}

Class* Namespace::getPolymorphicType( uint index ) const
{
    uint i = 0;
    o_foreach(Type* pType, m_Types)
    {
        if(pType->asClass())
        {
            if(i == index) return static_cast<Class*>(pType);
            ++i;
        }
    }
    return NULL;
}

Class* Namespace::getPolymorphicType( const string& a_strName ) const
{
    Type* pType = getType(a_strName);
    if(pType->isClass()) return static_cast<Class*>(pType);
    return NULL;
}

phantom::uint Namespace::getPolymorphicTypeCount() const
{
    uint i = 0;
    o_foreach(Type* pType, m_Types)
    {
        if(pType->asClass())
        {
            ++i;
        }
    }
    return i;
}

void    Namespace::getAllTypesCascade( const string& a_strName, vector<Type*>& a_Out ) const
{
    Type* pType = getType(a_strName);
    if(pType != NULL) a_Out.push_back(pType);
    o_foreach(Namespace* pNamespace, m_Namespaces)
    {
        pNamespace->getAllTypesCascade(a_strName, a_Out);
    }
}

Type* Namespace::getTypeByGuidCascade( uint a_uiGuid ) const
{
	Type* pType = getTypeByGuid(a_uiGuid);
	if(pType != NULL) return pType;
	o_foreach(Namespace* pNamespace, m_Namespaces)
	{
		pType = pNamespace->getTypeByGuidCascade(a_uiGuid);
		if(pType != NULL) return pType;
	}
	return NULL;
}

LanguageElement* Namespace::getElement(
    const char* a_strName 
    , template_specialization const* a_TemplateSpecialization
    , function_signature const* a_FunctionSignature
    , bitfield a_bfModifiers /*= bitfield()*/) const 
{
    if(a_TemplateSpecialization == NULL OR a_TemplateSpecialization->empty())
    {
        Type* pTypedef = getTypedef(a_strName);
        if(pTypedef != NULL) return pTypedef;
    }
    o_foreach(Type* pType, m_Types)
    {
        if(pType->matches(a_strName, a_TemplateSpecialization, a_bfModifiers))
        {
            return pType;
        }
        else if(pType->isEnum())
        {
            LanguageElement* pEnumConstant = pType->getElement(a_strName, a_TemplateSpecialization, a_FunctionSignature, a_bfModifiers);
            if(pEnumConstant) return pEnumConstant;
        }
    }
    if(a_TemplateSpecialization != NULL AND NOT(a_TemplateSpecialization->empty())) return NULL;
    o_foreach(Namespace* pNamespace, m_Namespaces)
    {
        if(pNamespace->getName() == a_strName )
            return pNamespace;
    }
    return NULL;
}

void Namespace::addTypedef( const string& a_strTypedef, Type* a_pType )
{
    o_assert(m_Typedefs.find(a_strTypedef) == m_Typedefs.end(), "Typedef already registered");
    m_Typedefs[a_strTypedef] = a_pType;
}

void Namespace::removeTypedef( const string& a_strTypedef, Type* a_pType )
{
    map<string, Type*>::iterator found = m_Typedefs.find(a_strTypedef);
    o_assert( found != m_Typedefs.end(), "Typedef not found");
    m_Typedefs.erase(found);
}

DataPointerType* Namespace::getDataPointerType( Type* a_pPointedType ) const
{
    o_foreach(Type* pType, m_Types)
    {
        if(pType->isDataPointerType())
        {
            if(static_cast<DataPointerType*>(pType)->getPointedType() == a_pPointedType)
                return static_cast<DataPointerType*>(pType);
        }
    }
    return NULL;
}

ReferenceType*      Namespace::getReferenceType(Type* a_pReferencedType) const
{
    o_foreach(Type* pType, m_Types)
    {
        if(pType->isReferenceType())
        {
            if(static_cast<ReferenceType*>(pType)->getReferencedType() == a_pReferencedType)
                return static_cast<ReferenceType*>(pType);
        }
    }
    return NULL;
}

Type*      Namespace::getConstType(Type* a_pConstedType) const
{
    o_foreach(Type* pType, m_Types)
    {
        if(pType->isConstType())
        {
            if(pType->removeConst() == a_pConstedType)
                return pType;
        }
    }
    return NULL;
}

ArrayType* Namespace::getArrayType( Type* a_pStoredType, size_t a_uiCount ) const
{
    o_foreach(Type* pType, m_Types)
    {
        if(pType->isArrayType())
        {
            if(static_cast<ArrayType*>(pType)->getStoredType() == a_pStoredType
                AND static_cast<ArrayType*>(pType)->getCount() == a_uiCount)
                return static_cast<ArrayType*>(pType);
        }
    }
    return NULL;
}

void Namespace::getElements( vector<LanguageElement*>& out, Class* a_pClass /*= nullptr*/ ) const
{
    if(a_pClass == nullptr OR classOf<Namespace>()->isKindOf(a_pClass))
    {
        for(auto it = m_Namespaces.begin(); it != m_Namespaces.end(); ++it)
        {
            out.push_back(*it);
        }
    }

    if(a_pClass == nullptr OR classOf<Type>()->isKindOf(a_pClass))
    {
        for(auto it = m_Types.begin(); it != m_Types.end(); ++it)
        {
            out.push_back(*it);
        }
    }
}

Namespace* Namespace::getNamespaceCascade( const string& a_strQualifiedName ) const
{
    list<string> words;
    split( words, a_strQualifiedName, boost::is_any_of(":. "), boost::token_compress_on ); // SplitVec == { "hello abc","ABC","aBc goodbye" }
    words.erase( std::remove_if( words.begin(), words.end(), 
        boost::bind( &string::empty, _1 ) ), words.end() );
    return getNamespaceCascade(&words);
}

o_cpp_end
