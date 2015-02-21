/* TODO LICENCE HERE */

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp>
#include "Namespace.h"
#include "Namespace.hxx"
#include "Expression.h"
#include "ConstructorCallExpression.h"
#include "Template.hxx"
#include "Application.h"
#include "Package.h"
/* *********************************************** */
o_registerN((phantom, reflection), Namespace);

o_namespace_begin(phantom, reflection) 

o_invalid_def(Namespace, "<unknown-namespace>", o_invalid);

static vector<AnonymousSection*>    m_EmptyAnonymousSections;

Namespace::Namespace(modifiers_t a_Modifiers /*= 0*/) 
    : NamedElement("", (a_Modifiers&o_invalid) ? (a_Modifiers|o_public_access) : (o_always_valid|o_public_access|a_Modifiers))
    , Scope(this)
    , m_pAnonymousSections(nullptr)
    , m_pFunctionPointerTypes(nullptr)
{
}

Namespace::Namespace( const string& a_strName, modifiers_t a_Modifiers /*= 0*/ ) 
    : NamedElement(a_strName, (a_Modifiers&o_invalid) ? (a_Modifiers|o_public_access) : (o_always_valid|o_public_access|a_Modifiers))
    , Scope(this)
    , m_pAnonymousSections(nullptr)
    , m_pFunctionPointerTypes(nullptr)
{
}

Namespace::~Namespace( void )
{

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
        addNamedElement(pChildNamespace);
        o_static_new_install_and_initialize_part(pChildNamespace);
        /*typeOf<Namespace>()->install(pChildNamespace, 0);
        typeOf<Namespace>()->initialize(pChildNamespace);*/
        if(application()->getLoadedModuleCount())
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

Namespace* Namespace::findOrCreateNamespaceCascade( const string& a_strNamespaceName, const char* separatorPattern )
{
    list<string> words;
    split( words, a_strNamespaceName, boost::is_any_of(separatorPattern), boost::token_compress_on ); // SplitVec == { "hello abc","ABC","aBc goodbye" }
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

Alias* Namespace::getNamespaceAlias( const string& a_strName ) const
{
    o_foreach(Alias* pNamespaceAlias, m_NamespaceAliases)
    {
        if(pNamespaceAlias->getName() == a_strName) return pNamespaceAlias;
    }
    return nullptr;
}

void Namespace::release(vector<Type*>& out_types)
{
    Scope::release(out_types);
    while(!m_Namespaces.empty())
    {
        Namespace* pNamespace = m_Namespaces.back();
        pNamespace->release(out_types);
        removeNamespace(pNamespace);
        o_dynamic_delete_clean(pNamespace);
    }
}

void Namespace::addNamespace( Namespace* a_pNamespace )
{
    o_assert_not(getNamespace(a_pNamespace->getName()));
    m_Namespaces.push_back(a_pNamespace); 
    addNamedElement(a_pNamespace);
    if(application()->getLoadedModuleCount())
    {
        o_emit namespaceAdded(a_pNamespace);
    }
}

void Namespace::removeNamespace( Namespace* a_pNamespace )
{
    removeElement(a_pNamespace);
}

Namespace* Namespace::getRootNamespace() const
{
    if(getParentNamespace() == NULL) 
        return const_cast<Namespace*>(this); 
    return getParentNamespace()->getRootNamespace();
}

#define o_assert_simple_name_collision(elem) \
    o_assert(!hasElementWithName(elem->getName()), "An element has already been registered with name %s in scope %s", elem->getName().c_str(), m_pThisElement->getQualifiedDecoratedName().c_str());

Alias* Namespace::addNamespaceAlias( const string& a_strAlias, Namespace* a_pNamespace )
{
    Alias* pAlias = o_new(Alias)(a_pNamespace, a_strAlias);
    addAlias(pAlias);
    m_NamespaceAliases.push_back(pAlias);
    return pAlias;
}

void Namespace::removeNamespaceAlias( const string& a_strAlias )
{
    for(auto it = m_NamespaceAliases.begin(); it != m_NamespaceAliases.end(); ++it)
    {
        if((*it)->getName() == a_strAlias)
        {
            removeElement(*it);
            return;
        }
    }
    o_assert(false, "namespace alias not found");
}

Namespace* Namespace::getNamespaceCascade( const string& a_strQualifiedName, const char* a_SeparatorList ) const
{
    list<string> words;
    split( words, a_strQualifiedName, boost::is_any_of(a_SeparatorList), boost::token_compress_on ); // SplitVec == { "hello abc","ABC","aBc goodbye" }
    words.erase( std::remove_if( words.begin(), words.end(), 
        boost::bind( &string::empty, _1 ) ), words.end() );
    return getNamespaceCascade(&words);
}

void Namespace::elementRemoved(LanguageElement* a_pElement)
{
    LanguageElement::elementRemoved(a_pElement);
    if(a_pElement->asNamespace())
    {
        Namespace* pNamespace = static_cast<Namespace*>(a_pElement);
        o_assert(pNamespace->getParentNamespace() == this, "This namespace is attached to another Namespace");
        vector<Namespace*>::iterator found = std::find(m_Namespaces.begin(), m_Namespaces.end(), pNamespace);
        o_assert(found != m_Namespaces.end(), "Namespace not found");
        m_Namespaces.erase(found);
        if(application()->getLoadedModuleCount())
        {
            o_emit namespaceRemoved(pNamespace);
        }
    }
}

vector<AnonymousSection*>::const_iterator Namespace::beginAnonymousSections() const
{
    return m_pAnonymousSections ? m_pAnonymousSections->begin() : m_EmptyAnonymousSections.begin();
}

vector<AnonymousSection*>::const_iterator Namespace::endAnonymousSections() const
{
    return m_pAnonymousSections ? m_pAnonymousSections->end() : m_EmptyAnonymousSections.end();
}

AnonymousSection* Namespace::getAnonymousSection( size_t a_uiIndex ) const
{
    o_assert(m_pAnonymousSections);
    return (*m_pAnonymousSections)[a_uiIndex];
}

void Namespace::addAnonymousSection( AnonymousSection* a_pAnonymousSection )
{
    o_assert(a_pAnonymousSection->getOwner());
    if(m_pAnonymousSections == nullptr)
    {
        m_pAnonymousSections = new vector<AnonymousSection*>;
    }
    m_pAnonymousSections->push_back(a_pAnonymousSection);
    addScopedElement(a_pAnonymousSection);
    if(application()->getLoadedModuleCount())
    {
        o_emit anonymousSectionAdded(a_pAnonymousSection);
    }
}

void Namespace::removeAnonymousSection( AnonymousSection* a_pAnonymousSection)
{
    removeElement(a_pAnonymousSection);
}

size_t Namespace::getAnonymousSectionCount() const
{
    return m_pAnonymousSections ? m_pAnonymousSections->size() : 0;
}

// ex: union(m, struct(x, y, union(z, w)))
AnonymousSection* Namespace::addAnonymousSection( const string& a_strCode, modifiers_t a_Modifiers )
{
    Scope* pOwner = this;
    string str = a_strCode;
    str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
    str.erase(std::remove(str.begin(), str.end(), '\t'), str.end());
    str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());
    str.erase(std::remove(str.begin(), str.end(), '\r'), str.end());
    enum state 
    {
        state_union_or_struct,
        state_list,
        state_ended,
    };
    state s = state_union_or_struct;
    string word;
    vector<AnonymousSection*> sections;
    AnonymousSection* pSection = nullptr;
    for(auto it = str.begin(); it != str.end(); ++it)
    {
        char c = *it;
        switch(s)
        {
        case state_union_or_struct:
            if(o_char_is_identifier(c))
            {
                word += c;
            }
            else if(c == '(')
            {
                if(word == "union")
                {
                    sections.push_back(o_new(AnonymousUnion));
                }
                else if(word == "struct")
                {
                    sections.push_back(o_new(AnonymousStruct));
                }
                else 
                {
                    o_dynamic_delete (sections.front());
                    return nullptr;
                }
                s = state_list;
                word.clear();
            }
            else 
            {
                o_dynamic_delete (sections.front());
                return nullptr;
            }
            break;

        case state_list:
            if(o_char_is_identifier(c))
            {
                word += c;
            }
            else if(c == '(')
            {
                if(word == "union")
                {
                    sections.push_back(o_new(AnonymousUnion));
                }
                else if(word == "struct")
                {
                    sections.push_back(o_new(AnonymousStruct));
                }
                else 
                {
                    if(sections.size())
                    {
                        o_dynamic_delete (sections.front());
                    }
                    return nullptr;
                }
                word.clear();
            }
            else if(c == ',')
            {
                if(word.size())
                {
                    if(sections.empty())
                        return nullptr;
                    Variable* pElement = getVariable(word);
                    if(pElement == nullptr)
                    {
                        if(sections.size())
                        {
                            o_dynamic_delete (sections.front());
                        }
                        return nullptr;
                    }
                    sections.back()->addVariable(pElement);
                }
                // data member
                word.clear();
            }
            else if(c == ')')
            {
                if(sections.empty())
                    return nullptr;
                pSection = sections.back();
                sections.pop_back();
                if(sections.empty())
                {
                    addAnonymousSection(pSection);
                    s = state_ended;
                }
                else 
                {
                    sections.back()->addAnonymousSection(pSection);
                    s = state_list;
                }
            }
            else 
            {
                if(sections.size())
                {
                    o_dynamic_delete (sections.front());
                }
                return nullptr;
            }
            break;

        case state_ended:
            if(sections.size())
            {
                o_dynamic_delete (sections.front());
            }
            return nullptr;
        }
    }
    return pSection;
}

vector<Alias*>::const_iterator Namespace::beginNamespaceAliases() const
{
    return m_NamespaceAliases.begin();
}

vector<Alias*>::const_iterator Namespace::endNamespaceAliases() const
{
    return m_NamespaceAliases.end();
}

void Namespace::referencedElementRemoved( LanguageElement* a_pElement )
{
    Scope::scopedElementRemoved(a_pElement);
    LanguageElement::referencedElementRemoved(a_pElement);
    if(a_pElement->asNamespace())
        for(auto it = m_Namespaces.begin(); it != m_Namespaces.end(); ++it)
        {
            if(*it == a_pElement)
            {
                m_Namespaces.erase(it);
                if(application()->getLoadedModuleCount())
                {
                    o_emit namespaceRemoved(*it);
                }
                return;
            }
        }
    else if(a_pElement->asAlias())
        for(auto it = m_NamespaceAliases.begin(); it != m_NamespaceAliases.end(); ++it)
        {
            if(*it == a_pElement)
            {
                m_NamespaceAliases.erase(it);
                if(application()->getLoadedModuleCount())
                {
                    o_emit namespaceAliasRemoved(*it);
                }
                return;
            }
        }
    else if(m_pAnonymousSections AND a_pElement->asAnonymousSection())
        for(auto it = m_pAnonymousSections->begin(); it != m_pAnonymousSections->end(); ++it)
        {
            if(*it == a_pElement)
            {
                if(application()->getLoadedModuleCount())
                {
                    o_emit anonymousSectionRemoved(*it);
                }
                m_pAnonymousSections->erase(it);
                if(m_pAnonymousSections->empty())
                {
                    delete m_pAnonymousSections;
                    m_pAnonymousSections = nullptr;
                }
                return;
            }
        }
}

Namespace* Namespace::getNamespaceAliased( const string& a_strAlias ) const
{
    Alias* pAlias = getNamespaceAlias(a_strAlias);
    return pAlias ? static_cast<Namespace*>(pAlias->getAliasedElement()) : nullptr;
}

FunctionPointerType* Namespace::functionPointerType( Type* a_pReturnType, EABI a_eABI, const vector<Type*>& a_ParameterTypes )
{
    if(m_pFunctionPointerTypes) 
    {
        for(auto it = m_pFunctionPointerTypes->begin(); it != m_pFunctionPointerTypes->end(); ++it)
        {
            if((*it)->getABI() == a_eABI 
                AND (*it)->getSignature()->getReturnType()->equals(a_pReturnType) 
                AND (*it)->getSignature()->matches(a_ParameterTypes, 0))
            {
                return *it;
            }
        }
    }    
    else m_pFunctionPointerTypes = new vector<FunctionPointerType*>;
    FunctionPointerType* pPointer = o_new(FunctionPointerType)(o_new(Signature)(a_pReturnType, a_ParameterTypes), a_eABI, 0);
    m_pFunctionPointerTypes->push_back(pPointer);
    addNamedElement(pPointer);
    return pPointer;
}

string Namespace::asPath(char separator) const
{
    Namespace* pParent = m_pOwner ? m_pOwner->asNamespace() : nullptr;
    string prefix = pParent ? pParent->asPath(separator) : "";
    return prefix.empty() ? m_strName : prefix+separator+m_strName;
}

void Namespace::addScopeElement( NamedElement* a_pElement )
{
    o_assert(a_pElement->m_pNamespace == nullptr);
    if(a_pElement->isNative())
        m_Modifiers |= o_native; // a namespace become native once any native element is added to iterencedElements)
    a_pElement->m_pNamespace = this;
    addReferencedElement(a_pElement);
}

void Namespace::removeScopeElement( NamedElement* a_pElement )
{
    o_assert(a_pElement->m_pNamespace == this);
    removeReferencedElement(a_pElement);
    a_pElement->m_pNamespace = nullptr;
}

void Namespace::getElementDoubles( NamedElement* a_pElement, vector<NamedElement*>& out ) const
{
    if(m_pReferencedElements)
    for(auto it = m_pReferencedElements->begin(); it != m_pReferencedElements->end(); ++it)
    {
        // Browse namespace elements to find doubles of given element
        if(*it == a_pElement) continue;
        NamedElement* pNamedElement = a_pElement->asNamedElement();
        if(pNamedElement AND a_pElement->getDecoratedName() == pNamedElement->getDecoratedName())
        {
            o_assert(a_pElement->getModule() != pNamedElement->getModule());
            out.push_back(pNamedElement);
        }
    }
}

o_namespace_end(phantom, reflection)

