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
#include <phantom/reflection/Namespace.h>
#include <phantom/reflection/Namespace.hxx>
#include <phantom/reflection/Expression.h>
#include <phantom/reflection/ConstructorCallExpression.h>
#include <phantom/reflection/Template.hxx>
#include <phantom/ModuleLoader.h>
/* *********************************************** */
o_registerN((phantom, reflection), Namespace);

o_namespace_begin(phantom, reflection) 

Namespace::Namespace( void ) 
{
}

Namespace::Namespace( const string& a_strName ) 
    : LanguageElement(a_strName, modifiers_t(o_always_valid))
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

Template* Namespace::getTemplate( const string& a_strName ) const
{
    vector<Template*>::const_iterator it = m_Templates.begin();
    vector<Template*>::const_iterator end = m_Templates.end();
    for(;it != end; ++it)
    {
        if((*it)->getName() == a_strName) return *it;
    }
    return false;
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
    Namespace* pChildNamespace = getNamespace(str);
    if(NOT(pChildNamespace)) 
    {
        pChildNamespace = o_static_new_alloc_and_construct_part(Namespace)(str);
        m_Namespaces.push_back(pChildNamespace); 
        addElement(pChildNamespace);
        o_static_new_install_and_initialize_part(pChildNamespace);
        /*typeOf<Namespace>()->install(pChildNamespace, 0);
        typeOf<Namespace>()->initialize(pChildNamespace);*/
        if(moduleLoader()->getLoadedModuleCount())
        {
            o_emit namespaceAdded(pChildNamespace);
        }
    }
    if(a_HierarchyWords->empty())
    {
        return pChildNamespace;
    }
    else
    {
        return pChildNamespace->findOrCreateNamespaceCascade(a_HierarchyWords);
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
    o_assert(getTypedef(a_pType->getName()) == NULL, "A typedef has already been registered with this type's name");
    o_assert(getNamespaceAlias(a_pType->getName()) == NULL, "A namespace alias has already been registered with this type's name");
    o_assert(std::find(m_Types.begin(), m_Types.end(), a_pType) == m_Types.end(), "Type already attached to this Namespace");
    m_Types.push_back(a_pType);
    addElement(a_pType);
    if(moduleLoader()->getLoadedModuleCount())
    {
        o_emit typeAdded(a_pType);
    }
}

void Namespace::addFunction( Function* a_pFunction )
{
    o_assert(a_pFunction->getOwner() == NULL, "Function has already been attached to a Namespace");
    o_assert(phantom::elementByName(a_pFunction->getQualifiedDecoratedName(), this) == nullptr, "Function with same signature found in current namespace");
    m_Functions.push_back(a_pFunction);
    addElement(a_pFunction);
    if(moduleLoader()->getLoadedModuleCount())
    {
        o_emit functionAdded(a_pFunction);
    }
}

void Namespace::addVariable( StaticVariable* a_pVariable )
{
    o_assert(a_pVariable->getOwner() == NULL, "Variable has already been attached to a Namespace");
    o_assert(phantom::elementByName(a_pVariable->getQualifiedDecoratedName(), this) == nullptr, "Variable with same signature found in current namespace");
    m_Variables.push_back(a_pVariable);
    addElement(a_pVariable);
    if(moduleLoader()->getLoadedModuleCount())
    {
        o_emit variableAdded(a_pVariable);
    }
}

void Namespace::addTemplate( Template* a_pTemplate )
{
    o_assert(a_pTemplate->m_pOwner == NULL, "Type has already been attached to a Namespace");
    o_assert(getTypedef(a_pTemplate->getName()) == NULL, "A typedef has already been registered with this type's name");
    o_assert(getNamespaceAlias(a_pTemplate->getName()) == NULL, "A namespace alias has already been registered with this type's name");
    o_assert(std::find(m_Templates.begin(), m_Templates.end(), a_pTemplate) == m_Templates.end(), "Template already attached to this Namespace");
    m_Templates.push_back(a_pTemplate);
    addElement(a_pTemplate);
    if(moduleLoader()->getLoadedModuleCount())
    {
        o_emit templateAdded(a_pTemplate);
    }
}

void Namespace::removeType( Type* a_pType )
{
    o_assert(a_pType->m_pOwner == this, "This type is attached to another Namespace");
    vector<Type*>::iterator found = std::find(m_Types.begin(), m_Types.end(), a_pType);
    o_assert(found != m_Types.end(), "Type not found");
    m_Types.erase(found);
    removeElement(a_pType);
    if(moduleLoader()->getLoadedModuleCount())
    {
        o_emit typeRemoved(a_pType);
    }
}

void Namespace::removeFunction( Function* a_pFunction )
{
    o_assert(a_pFunction->getOwner() == this, "This function is attached to another Namespace");
    vector<Function*>::iterator found = std::find(m_Functions.begin(), m_Functions.end(), a_pFunction);
    o_assert(found != m_Functions.end(), "Function not found");
    m_Functions.erase(found);
    removeElement(a_pFunction);
    if(moduleLoader()->getLoadedModuleCount())
    {
        o_emit functionRemoved(a_pFunction);
    }
}

void Namespace::removeVariable( StaticVariable* a_pVariable )
{
    o_assert(a_pVariable->getOwner() == this, "This function is attached to another Namespace");
    vector<StaticVariable*>::iterator found = std::find(m_Variables.begin(), m_Variables.end(), a_pVariable);
    o_assert(found != m_Variables.end(), "Variable not found");
    m_Variables.erase(found);
    removeElement(a_pVariable);
    if(moduleLoader()->getLoadedModuleCount())
    {
        o_emit variableRemoved(a_pVariable);
    }
}

void Namespace::removeTemplate( Template* a_pTemplate )
{
    o_assert(a_pTemplate->m_pOwner == this, "This type is attached to another Namespace");
    auto found = std::find(m_Templates.begin(), m_Templates.end(), a_pTemplate);
    o_assert(found != m_Templates.end(), "Template not found");
    m_Templates.erase(found);
    removeElement(a_pTemplate);
    if(moduleLoader()->getLoadedModuleCount())
    {
        o_emit templateRemoved(a_pTemplate);
    }
}

void Namespace::addNamespace( Namespace* a_pNamespace )
{
    o_assert_not(getNamespace(a_pNamespace->getName()));
    m_Namespaces.push_back(a_pNamespace); 
    addElement(a_pNamespace);
    if(moduleLoader()->getLoadedModuleCount())
    {
        o_emit namespaceAdded(a_pNamespace);
    }
}

void Namespace::removeNamespace( Namespace* a_pNamespace )
{
    o_assert(a_pNamespace->getParentNamespace() == this, "This namespace is attached to another Namespace");
    vector<Namespace*>::iterator found = std::find(m_Namespaces.begin(), m_Namespaces.end(), a_pNamespace);
    o_assert(found != m_Namespaces.end(), "Namespace not found");
    m_Namespaces.erase(found);
    removeElement(a_pNamespace);
    if(moduleLoader()->getLoadedModuleCount())
    {
        o_emit namespaceRemoved(a_pNamespace);
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
    return pType ? pType->asPrimitiveType() : nullptr;
}

Class* Namespace::getClass( size_t index ) const
{
    size_t i = 0;
    o_foreach(Type* pType, m_Types)
    {
        if(pType->asClass())
        {
            if(i == index) return static_cast<Class*>(pType);
            ++i;
        }
    }
    return nullptr;
}

Class* Namespace::getClass( const string& a_strName ) const
{
    Type* pType = getType(a_strName);
    return pType ? pType->asClass() : nullptr;
}

size_t Namespace::getClassCount() const
{
    size_t i = 0;
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

LanguageElement* Namespace::solveElement(
    const string& a_strName 
    , const vector<TemplateElement*>* a_TemplateSpecialization
    , const vector<LanguageElement*>* a_FunctionSignature
    , modifiers_t a_Modifiers /*= 0*/) const 
{
    LanguageElement* pUsing = getUsing(a_strName);
    if(pUsing)
    {
        if(a_TemplateSpecialization AND pUsing->asTemplate())
        {
            return pUsing->getOwner()->solveElement(a_strName, a_TemplateSpecialization, a_FunctionSignature, a_Modifiers);
        }
        else if(a_TemplateSpecialization == nullptr)
        {
            return pUsing;
        }
    }
    if(a_FunctionSignature)
    {
        vector<Expression*> expressions;
        vector<Type*> types;
        bool bTypes = true;
        bool bExpressions = true;
        for( auto it = a_FunctionSignature->begin(); it != a_FunctionSignature->end(); ++it)
        {
            LanguageElement* pElement = (*it);
            if(pElement)
            {
                Expression* pExpression = pElement->asExpression();
                Type* pType = pElement->asType();
                if(pExpression AND bExpressions)
                {
                    bTypes = false;
                    expressions.push_back(pExpression);
                    types.push_back(pExpression->getValueType());
                }
                else if(pType AND bTypes)
                {
                    bExpressions = false;
                    types.push_back(pType);
                }
                else return nullptr;
            }
            else return nullptr;
        }

        if(bExpressions)
        {
            o_foreach(Type* pType, m_Types)
            {
                if(pType->getName() == a_strName AND pType->asClassType())
                {
                    vector<size_t> partialMatches;
                    Constructor* pConstructor = pType->asClassType()->getConstructor(types, &partialMatches, a_Modifiers);
                    if(pConstructor == nullptr)
                        return nullptr;
                    if(pType->isCopyable())
                    {
                        return o_new(ConstructorCallExpression)(pConstructor, expressions);
                    }
                }
            }
            map<Function*, vector<size_t>> functionsPartialMatches;
            o_foreach(Function* pFunction, m_Functions)
            {
                vector<size_t> partialMatches;
                if(pFunction->matches(a_strName, types, &partialMatches, a_Modifiers))
                {
                    if(partialMatches.empty()) 
                        return o_new(CallExpression)(pFunction, expressions); 
                    functionsPartialMatches[pFunction] = partialMatches;
                }
            }
            if(functionsPartialMatches.size() == 1)
            {
                return o_new(CallExpression)(functionsPartialMatches.begin()->first, expressions);
            }
            return nullptr;
        }
        if(bTypes)
        {
            o_foreach(Function* pFunction, m_Functions)
            {
                if(pFunction->matches(a_strName, types, nullptr, a_Modifiers))
                {
                    return pFunction;
                }
            }
        }
    }
    else 
    {
        if(a_TemplateSpecialization == nullptr OR a_TemplateSpecialization->empty())
        {
            Type* pTypedef = getTypedef(a_strName);
            if(pTypedef != nullptr) return pTypedef;
            Namespace* pNamespaceAlias = getNamespaceAlias(a_strName);
            if(pNamespaceAlias != nullptr) return pNamespaceAlias;
            Template* pTemplate = getTemplate(a_strName);
            if(pTemplate != nullptr) return pTemplate;
        }
        o_foreach(Type* pType, m_Types)
        {
            if(pType->matches(a_strName, a_TemplateSpecialization, a_Modifiers))
            {
                return pType;
            }
            else if(pType->asEnum())
            {
                LanguageElement* pEnumConstant = pType->solveElement(a_strName, a_TemplateSpecialization, a_FunctionSignature, a_Modifiers);
                if(pEnumConstant) return pEnumConstant;
            }
        }
        o_foreach(StaticVariable* pVariable, m_Variables)
        {
            if(pVariable->getName() == a_strName)
            {
                return pVariable;
            }
        }
    }
    if(a_TemplateSpecialization != nullptr AND NOT(a_TemplateSpecialization->empty())) return nullptr;
    o_foreach(Namespace* pNamespace, m_Namespaces)
    {
        if(pNamespace->getName() == a_strName )
            return pNamespace;
    }
    return nullptr;
}

void Namespace::addTypedef( const string& a_strTypedef, Type* a_pType )
{
    o_assert(getNamespaceAlias(a_pType->getName()) == NULL, "A namespace alias has already been registered with this typedef's name");
    o_assert(getType(a_strTypedef) == NULL, "A type has already been registered with this typedef's name");
    o_assert(m_Typedefs.find(a_strTypedef) == m_Typedefs.end(), "Typedef already registered");
    m_Typedefs[a_strTypedef] = a_pType;
    a_pType->registerTypedef(this, a_strTypedef);
    addReferencedElement(a_pType);
}

void Namespace::removeTypedef( const string& a_strTypedef, Type* a_pType )
{
    auto found = m_Typedefs.find(a_strTypedef);
    o_assert( found != m_Typedefs.end(), "Typedef not found");
    a_pType->unregisterTypedef(this, a_strTypedef);
    m_Typedefs.erase(found);
    removeReferencedElement(a_pType);
}

void Namespace::addNamespaceAlias( const string& a_strAlias, Namespace* a_pNamespace )
{
    o_assert(getTypedef(a_strAlias) == NULL, "A typedef has already been registered with this namespace alias' name");
    o_assert(getType(a_strAlias) == NULL, "A type has already been registered with this namespace alias' name");
    o_assert(m_NamespaceAliases.find(a_strAlias) == m_NamespaceAliases.end(), "Namespace alias already registered");
    m_NamespaceAliases[a_strAlias] = a_pNamespace;
}

void Namespace::removeNamespaceAlias( const string& a_strAlias, Namespace* a_pNamespace )
{
    auto found = m_NamespaceAliases.find(a_strAlias);
    o_assert( found != m_NamespaceAliases.end(), "Namespace alias not found");
    m_NamespaceAliases.erase(found);
}

void Namespace::getElements( vector<LanguageElement*>& out, Class* a_pClass /*= nullptr*/ ) const
{
    if(a_pClass == nullptr OR typeOf<Namespace>()->isKindOf(a_pClass))
    {
        for(auto it = m_Namespaces.begin(); it != m_Namespaces.end(); ++it)
        {
            out.push_back(*it);
        }
    }

    if(a_pClass == nullptr OR typeOf<Type>()->isKindOf(a_pClass))
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

Template* Namespace::findOrCreateTemplate( const string& a_strName )
{
    Template* pTemplate = getTemplate(a_strName);
    if(pTemplate == nullptr)
    {
        pTemplate = o_new(Template)(a_strName);
        addTemplate(pTemplate);
    }
    return pTemplate;
}

void Namespace::referencedElementRemoved( LanguageElement* a_pElement )
{
    bool bFound = true;
    while(bFound)
    {
        bFound = false;
        for(auto it = m_Typedefs.begin(); it != m_Typedefs.end(); ++it)
        {
            if(it->second == a_pElement)
            {
                m_Typedefs.erase(it);
                bFound = true;
                break;
            }
        }
    }

}


void Namespace::elementRemoved(LanguageElement* a_pElement)
{
    for(auto it = m_Types.begin(); it != m_Types.end(); ++it)
    {
        if(*it == a_pElement)
        {
            m_Types.erase(it);
            break;
        }
    }
    for(auto it = m_Namespaces.begin(); it != m_Namespaces.end(); ++it)
    {
        if(*it == a_pElement)
        {
            m_Namespaces.erase(it);
            break;
        }
    }
    for(auto it = m_Templates.begin(); it != m_Templates.end(); ++it)
    {
        if(*it == a_pElement)
        {
            m_Templates.erase(it);
            break;
        }
    }
}

o_namespace_end(phantom, reflection)
