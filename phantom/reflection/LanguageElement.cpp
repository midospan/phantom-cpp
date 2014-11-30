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
#include <phantom/reflection/LanguageElement.h>
#include <phantom/reflection/LanguageElement.hxx>
#include <phantom/std/string.h>
#include <phantom/std/vector.hxx>
/* ** The Class Header must be the last #include * */
/* *********************************************** */
o_registerN((phantom, reflection), LanguageElement);
o_registerNTI((phantom), vector, (phantom::reflection::LanguageElement*));

o_namespace_begin(phantom, reflection)

LanguageElement::LanguageElement()
    : m_uiGuid(0)
    , m_pMetaData(nullptr)
    , m_CodeLocations(nullptr)
    , m_DeclarationCodeLocations(nullptr)
    , m_ReferenceCodeLocations(nullptr)
    , m_pElements(nullptr)
    , m_pReferencedElements(nullptr)
    , m_pReferencingElements(nullptr)
    , m_pOwner(nullptr)
    , m_Modifiers(0)
    , m_pModule(nullptr)
    , m_pTemplateSpecialization(nullptr)
    , m_pExtension(nullptr)
    , m_pLanguage(cplusplus())
    , m_pUsings(nullptr)
    , m_pFriends(nullptr)
{
	Register(this);
}

LanguageElement::LanguageElement( const string& a_strName, modifiers_t a_Modifiers /*= 0*/ )
    : m_strName(a_strName)
    , m_uiGuid(0)
    , m_pMetaData(nullptr)
    , m_CodeLocations(nullptr)
    , m_DeclarationCodeLocations(nullptr)
    , m_ReferenceCodeLocations(nullptr)
    , m_pElements(nullptr)
    , m_pReferencedElements(nullptr)
    , m_pReferencingElements(nullptr)
    , m_pOwner(nullptr)
    , m_Modifiers(a_Modifiers)
    , m_pModule(nullptr)
    , m_pTemplateSpecialization(nullptr)
    , m_pExtension(nullptr)
    , m_pLanguage(cplusplus())
    , m_pUsings(nullptr)
    , m_pFriends(nullptr)
{
    o_assert(NOT(isPublic() AND isProtected()), "o_public_access and o_protected_access cannot co-exist");
	Register(this);
}

LanguageElement::~LanguageElement()
{
    o_assert(m_uiGuid == o_invalid_guid, "probably you haven't called terminate before calling delete");
}

o_terminate_cpp(LanguageElement)
{
    setInvalid();
    if(m_pModule)
    {
        m_pModule->removeLanguageElement(this);
    }
    if(m_pExtension)
    {
        o_dynamic_delete m_pExtension;
    }
    o_assert(canBeDestroyed());
    if(m_pMetaData != nullptr)
    {
        size_t count = phantom::metaDataCount();
        o_delete_n(count, string) m_pMetaData;
        m_pMetaData = nullptr;
    }
    if(m_pOwner)
    {
        m_pOwner->setInvalid(); // it is not a user removal, we mark the owner as invalid
        m_pOwner->removeElement(this);
    }
    while(m_pReferencingElements)
    {
        m_pReferencingElements->back()->setInvalid(); // it is not a user removal, we mark the referencing element as invalid
        m_pReferencingElements->back()->removeReferencedElement(this);
    }
    while(m_pReferencedElements)
    {
        removeReferencedElement(m_pReferencedElements->back());
    }
    while(m_pElements)
    {
        o_dynamic_delete m_pElements->back();
    }
    while(m_CodeLocations && m_CodeLocations->size())
    {
        removeCodeLocation(m_CodeLocations->back());
    }
    while(m_ReferenceCodeLocations && m_ReferenceCodeLocations->size())
    {
        removeReferenceCodeLocation(m_ReferenceCodeLocations->back());
    }
    while(m_DeclarationCodeLocations && m_DeclarationCodeLocations->size())
    {
        removeDeclarationCodeLocation(m_DeclarationCodeLocations->back());
    }
    Unregister(this);
    m_uiGuid = o_invalid_guid;
}

phantom::string LanguageElement::getQualifiedName() const
{
    string ownerName = m_pOwner ? m_pOwner->getQualifiedName() : "";
    return ownerName.empty() ? m_strName : ownerName + o_CS("::") + m_strName;
}

phantom::string LanguageElement::getDecoratedName() const
{
    return m_pTemplateSpecialization?getName()+m_pTemplateSpecialization->getDecoratedName():getName();
}

phantom::string LanguageElement::getQualifiedDecoratedName() const
{
    return m_pTemplateSpecialization?getQualifiedName()+m_pTemplateSpecialization->getQualifiedDecoratedName():getQualifiedName();
}

void LanguageElement::addCodeLocation( const CodeLocation& location )
{
    if(m_CodeLocations == nullptr)
    {
        m_CodeLocations = new vector<CodeLocation>();
    }
    m_CodeLocations->push_back(location);
    if(location.getSourceFile() && location != CodeLocation(location.getSourceFile()))
    {
        location.getSourceFile()->addElement(location, this);
    }
}

void LanguageElement::setGuid(uint a_uiGuid)
{
	m_uiGuid = a_uiGuid;
}

void LanguageElement::removeCodeLocation( const CodeLocation& location )
{
    o_assert(m_CodeLocations);
    if(location.getSourceFile() && location != CodeLocation(location.getSourceFile()))
    {
        location.getSourceFile()->removeElement(location, this);
    }
    m_CodeLocations->erase(std::find(m_CodeLocations->begin(), m_CodeLocations->end(), location));
    if(m_CodeLocations->empty())
    {
        delete m_CodeLocations;
        m_CodeLocations = nullptr;
    }
}

void LanguageElement::addDeclarationCodeLocation( const CodeLocation& location )
{
    if(m_DeclarationCodeLocations == nullptr)
    {
        m_DeclarationCodeLocations = new vector<CodeLocation>();
    }
    m_DeclarationCodeLocations->push_back(location);
    if(location.getSourceFile() && location != CodeLocation(location.getSourceFile()))
    {
        location.getSourceFile()->addElementDeclaration(location, this);
    }
}

void LanguageElement::addReferenceCodeLocation( const CodeLocation& location )
{
    if(m_ReferenceCodeLocations == nullptr)
    {
        m_ReferenceCodeLocations = new vector<CodeLocation>();
    }
    m_ReferenceCodeLocations->push_back(location);
    if(location.getSourceFile() && location != CodeLocation(location.getSourceFile()))
    {
        location.getSourceFile()->addElementReference(location, this);
    }
}

void LanguageElement::removeReferenceCodeLocation( const CodeLocation& location )
{
    o_assert(m_ReferenceCodeLocations);
    if(location.getSourceFile() && location != CodeLocation(location.getSourceFile()))
    {
        location.getSourceFile()->removeElementReference(location, this);
    }
    m_ReferenceCodeLocations->erase(std::find(m_ReferenceCodeLocations->begin(), m_ReferenceCodeLocations->end(), location));
    if(m_ReferenceCodeLocations->empty())
    {
        delete m_ReferenceCodeLocations;
        m_ReferenceCodeLocations = nullptr;
    }
}

void LanguageElement::removeDeclarationCodeLocation( const CodeLocation& location )
{
    o_assert(m_DeclarationCodeLocations);
    if(location.getSourceFile() && location != CodeLocation(location.getSourceFile()))
    {
        location.getSourceFile()->removeElementDeclaration(location, this);
    }
    m_DeclarationCodeLocations->erase(std::find(m_DeclarationCodeLocations->begin(), m_DeclarationCodeLocations->end(), location));
    if(m_DeclarationCodeLocations->empty())
    {
        delete m_DeclarationCodeLocations;
        m_DeclarationCodeLocations = nullptr;
    }
}

LanguageElement* LanguageElement::getLeafElementAt( const CodePosition& a_Position ) const
{
    if(m_pElements)
    {
        for(auto it = m_pElements->begin(); it != m_pElements->end(); ++it)
        {
            LanguageElement* pElement = (*it)->getLeafElementAt(a_Position);
            if(pElement) return pElement;
        }
    }
    if(containsCodePosition(a_Position)) return const_cast<LanguageElement*>(this);
    return nullptr;
}

LanguageElement* LanguageElement::solveElement( const string& a_strName , const vector<TemplateElement*>* , const vector<LanguageElement*>* , modifiers_t a_Modifiers /*= 0*/ ) const
{
    if(m_pTemplateSpecialization)
    {
        LanguageElement* pElement = m_pTemplateSpecialization->getType(a_strName);
        if(pElement) return pElement;
    }
    return nullptr;
}

void LanguageElement::setTemplateSpecialization( TemplateSpecialization* a_pTemplateSpecialization )
{
    o_assert(m_pTemplateSpecialization == nullptr);
    o_assert(a_pTemplateSpecialization == nullptr OR a_pTemplateSpecialization->m_pOwner == nullptr);
    if(a_pTemplateSpecialization)
    {
        addElement(a_pTemplateSpecialization);
    }
}

Template* LanguageElement::getTemplate() const
{
    return m_pTemplateSpecialization ? m_pTemplateSpecialization->getTemplate() : nullptr;
}

void LanguageElement::getAccessibleElementsAt( const CodePosition& a_Position, vector<LanguageElement*>& a_Elements ) const
{
    if(m_pElements)
    {
        a_Elements.insert(a_Elements.end(), m_pElements->begin(), m_pElements->end());
    }
}

void LanguageElement::getElements( vector<LanguageElement*>& out, Class* a_pClass /*= nullptr*/ ) const
{
    if(m_pElements)
    {
        for(auto it = m_pElements->begin(); it != m_pElements->end(); ++it)
        {
            if(a_pClass == nullptr OR classOf(*it)->isKindOf(a_pClass))
            {
                out.push_back(*it);
            }
        }
    }
}

void LanguageElement::getElementsCascade( vector<LanguageElement*>& out, Class* a_pClass /*= nullptr*/ ) const
{
    vector<LanguageElement*> subElements;
    getElements(out, a_pClass);
    if(m_pElements)
    {
        for(auto it = m_pElements->begin(); it != m_pElements->end(); ++it)
        {
            (*it)->getElementsCascade(out, a_pClass);
        }
    }
}

void LanguageElement::addElement( LanguageElement* a_pElement )
{
    o_assert(a_pElement != this);
    o_assert(a_pElement->m_pOwner == nullptr);
    if(m_pElements == nullptr)
    {
        m_pElements = new vector<LanguageElement*>;
    }
    m_pElements->push_back(a_pElement);
    a_pElement->setOwner(this);
    elementAdded(a_pElement);
    if(a_pElement->isInvalid())
    {
        setInvalid();
    }
}

void LanguageElement::removeElement( LanguageElement* a_pElement )
{
    o_assert(a_pElement->m_pOwner == this);
    elementRemoved(a_pElement);
    m_pElements->erase(std::find(m_pElements->begin(), m_pElements->end(), a_pElement));
    if(m_pElements->size() == 0)
    {
        delete m_pElements;
        m_pElements = nullptr;
    }
    a_pElement->m_pOwner = nullptr;
}

void LanguageElement::addReferencedElement( LanguageElement* a_pElement )
{
    if(m_pReferencedElements == nullptr)
    {
        m_pReferencedElements = new vector<LanguageElement*>;
    }
    // Allows added referenced element to be already added, because it happens
    // a lot that the same element is used in different referencements in a same element
    // example : function return type and arguments
    if(std::find(m_pReferencedElements->begin(), m_pReferencedElements->end(), a_pElement) == m_pReferencedElements->end())
    {
        m_pReferencedElements->push_back(a_pElement);
        a_pElement->registerReferencingElement(this);
        referencedElementAdded(a_pElement);
    }
}

void LanguageElement::removeReferencedElement( LanguageElement* a_pElement )
{
    m_pReferencedElements->erase(std::find(m_pReferencedElements->begin(), m_pReferencedElements->end(), a_pElement));
    if(m_pReferencedElements->size() == 0)
    {
        delete m_pReferencedElements;
        m_pReferencedElements = nullptr;
    }
    a_pElement->unregisterReferencingElement(this);
    referencedElementRemoved(a_pElement);
}
void LanguageElement::referencedElementAdded( LanguageElement* a_pElement )
{

}

void LanguageElement::referencedElementRemoved( LanguageElement* a_pElement )
{
    if(m_pFriends)
    {
        auto friendFound = std::find(m_pFriends->begin(), m_pFriends->end(), a_pElement);
        if(friendFound != m_pFriends->end())
        {
            m_pFriends->erase(friendFound);
            if(m_pFriends->empty())
            {
                delete m_pFriends;
                m_pFriends = nullptr;
            }
        }
    }
    if(m_pUsings)
    {
        auto usingFound = m_pUsings->find(a_pElement->getName());
        if(usingFound != m_pUsings->end())
        {
            o_assert(a_pElement == usingFound->second);
            m_pUsings->erase(usingFound);
            if(m_pUsings->empty())
            {
                delete m_pUsings;
                m_pUsings = nullptr;
            }
        }
    }
}

void LanguageElement::registerReferencingElement( LanguageElement* a_pElement )
{
    if(m_pReferencingElements == nullptr)
    {
        m_pReferencingElements = new vector<LanguageElement*>;
    }
    m_pReferencingElements->push_back(a_pElement);
}

void LanguageElement::unregisterReferencingElement( LanguageElement* a_pElement )
{
    m_pReferencingElements->erase(std::find(m_pReferencingElements->begin(), m_pReferencingElements->end(), a_pElement));
    if(m_pReferencingElements->size() == 0)
    {
        delete m_pReferencingElements;
        m_pReferencingElements = nullptr;
    }
}

void LanguageElement::teardownMetaDataCascade( size_t count )
{
    if(m_pMetaData != nullptr)
    {
        o_delete_n(count, string) m_pMetaData;
        m_pMetaData = nullptr;
    }
    if(m_pElements)
    for(auto it = m_pElements->begin(); it != m_pElements->end(); ++it)
    {
        (*it)->teardownMetaDataCascade(count);
    }
}

void LanguageElement::setupMetaData( size_t count )
{
    o_assert(m_pMetaData == nullptr);
}

const string& LanguageElement::getMetaDataValue( size_t index ) const
{
    static string null_string;
    o_assert(index == eInvalidMetaDataIndex || index < phantom::metaDataCount());
    return m_pMetaData == nullptr ? null_string : (index != eInvalidMetaDataIndex) ? m_pMetaData[index] : null_string;
}

void LanguageElement::setMetaDataValue( size_t index, const string& value )
{
    o_assert(index < phantom::metaDataCount());
    if(m_pMetaData == nullptr)
    {
        m_pMetaData = o_new_n(phantom::metaDataCount(), string);
    }
    m_pMetaData[index] = value;
}

bool LanguageElement::containsCodePosition( const CodePosition& position ) const
{
    if(m_CodeLocations)
    {
        for(auto it = m_CodeLocations->begin(); it != m_CodeLocations->end(); ++it)
        {
            if(it->containsCodePosition(position)) return true;
        }
    }
    return false;
}

const CodeLocation& LanguageElement::getCodeLocation( size_t index ) const
{
    static CodeLocation defaultLocation;
    if(m_CodeLocations) return (*m_CodeLocations)[index];
    return defaultLocation;
}

void LanguageElement::setModifiers( modifiers_t a_Modifiers )
{
    m_Modifiers = a_Modifiers;
    o_assert(NOT(isPublic() AND isProtected()), "o_public_access and o_protected_access cannot co-exist");
}

bool LanguageElement::matches( const string& a_strName, const vector<TemplateElement*>* a_TemplateSpecialization /*= NULL*/, modifiers_t a_Modifiers /*= 0*/ ) const
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

bool LanguageElement::matches( const vector<TemplateElement*>* a_pElements ) const
{
    return m_pTemplateSpecialization
        ? m_pTemplateSpecialization->matches(a_pElements)
        : NULL;
}

void LanguageElement::setModule( Module* a_pModule )
{
    m_pModule = a_pModule;
    moduleChanged(a_pModule);
}

void LanguageElement::moduleChanged( Module* a_pModule )
{
    // TODO : use polymorphism
    if(asNamespace()) return;
    if(a_pModule)
    {
        if(m_pElements)
        {
            for(auto it = m_pElements->begin(); it != m_pElements->end(); ++it)
            {
                if((*it)->getModule() == nullptr AND ((*it)->asType() == nullptr))
                {
                    a_pModule->addLanguageElement(*it);
                }
            }
        }
    }
}

bool LanguageElement::canBeDestroyed() const
{
    if(m_pTemplateSpecialization) return m_pTemplateSpecialization->canBeDestroyed() ;
    if(m_pElements)
    {
        for(auto it = m_pElements->begin(); it != m_pElements->end(); ++it)
        {
            if(NOT((*it)->canBeDestroyed())) return false;
        }
    }
    return true;
}

void LanguageElement::checkCompleteness() const
{
    if(m_pTemplateSpecialization)
        m_pTemplateSpecialization->checkCompleteness();
}

void LanguageElement::elementAdded( LanguageElement* a_pElement )
{
    TemplateSpecialization* pTemplateSpecialization = a_pElement->asTemplateSpecialization();
    if(pTemplateSpecialization)
    {
        o_assert(m_pTemplateSpecialization == nullptr);
        m_pTemplateSpecialization = pTemplateSpecialization;
    }
}

void LanguageElement::elementRemoved( LanguageElement* a_pElement )
{
    TemplateSpecialization* pTemplateSpecialization = a_pElement->asTemplateSpecialization();
    if(pTemplateSpecialization)
    {
        o_assert(m_pTemplateSpecialization == pTemplateSpecialization);
        m_pTemplateSpecialization = nullptr;
    }
}

variant LanguageElement::compile( Compiler* a_pCompiler )
{
    return variant();
}

bool LanguageElement::isInvalid() const
{
    return (m_Modifiers & o_invalid) != 0;
}

void LanguageElement::referencedElementInvalidated( LanguageElement* a_pElement )
{

}

Block* LanguageElement::getBlock() const
{
    return m_pOwner ? (m_pOwner->asBlock() ? m_pOwner->asBlock() : m_pOwner->getBlock()) : nullptr ;
}

void LanguageElement::internalAncestorChanged( LanguageElement* a_pOwner )
{
    if(m_pElements)
    {
        for(auto it = m_pElements->begin(); it != m_pElements->end(); ++it)
        {
            (*it)->internalAncestorChanged(a_pOwner);
        }
    }
    ancestorChanged(m_pOwner);
}

void LanguageElement::setOwner( LanguageElement* a_pOwner )
{
    o_assert(m_pOwner == nullptr);
    m_pOwner = a_pOwner;
    internalAncestorChanged(m_pOwner);
}

void LanguageElement::ancestorChanged( LanguageElement* a_pOwner )
{
    o_unused(a_pOwner);
}

boolean LanguageElement::isNative() const
{
    return (m_Modifiers & o_native) != 0;
}

LanguageElement* LanguageElement::getHatchedElement() const
{
    return nullptr;
}

LanguageElement* LanguageElement::hatch()
{
    LanguageElement* pLanguageElement = getHatchedElement();
    if(pLanguageElement == nullptr)
        return this;
    o_dynamic_delete (this);
    return pLanguageElement;
}

void LanguageElement::setOwnerByQualifiedDecoratedName( string a_Owner )
{

}

string LanguageElement::getOwnerQualifiedDecoratedName() const
{
    return m_pOwner ? m_pOwner->getQualifiedDecoratedName() : "";
}

void LanguageElement::setInvalid()
{
    if((m_Modifiers & o_invalid) != 0 OR (m_Modifiers & o_always_valid) != 0)
        return;
    m_Modifiers |= o_invalid;
    if(m_pReferencingElements)
    {
        for(auto it = m_pReferencingElements->begin(); it != m_pReferencingElements->end(); ++it)
        {
            (*it)->setInvalid();
            (*it)->referencedElementInvalidated(this);
        }
    }
    if(m_pOwner) m_pOwner->setInvalid();
    if(m_pElements)
    {
        for(auto it = m_pElements->begin(); it != m_pElements->end(); ++it)
        {
            (*it)->setInvalid();
            (*it)->elementInvalidated(this);
        }
    }
    invalidated();
}

void LanguageElement::invalidated()
{

}

void LanguageElement::elementInvalidated( LanguageElement* a_pElement )
{

}

void LanguageElement::addUsing( LanguageElement* a_pLanguageElement )
{
    if(m_pUsings == nullptr)
    {
        m_pUsings = new map<string, LanguageElement*>;
    }
    else if(m_pUsings->find(a_pLanguageElement->getName()) != m_pUsings->end())
    {
        o_exception(exception::reflection_runtime_exception, "Conflict with another using directive");
    }
    (*m_pUsings)[a_pLanguageElement->getName()] = a_pLanguageElement;
    addReferencedElement(a_pLanguageElement);
}

LanguageElement* LanguageElement::getUsing( const string& a_strName ) const
{
    if(m_pUsings == nullptr) return nullptr;
    auto found = m_pUsings->find(a_strName);
    return found == m_pUsings->end() ? nullptr : found->second;
}

void LanguageElement::addFriend( LanguageElement* a_pFriend )
{
    if(m_pFriends == nullptr)
    {
        m_pFriends = new vector<LanguageElement*>;
    }
    o_assert(!hasFriend(a_pFriend));
    m_pFriends->push_back(a_pFriend);
    addReferencedElement(a_pFriend);
}

bool LanguageElement::hasFriend( LanguageElement* a_pFriend ) const
{
    return std::find(m_pFriends->begin(), m_pFriends->end(), a_pFriend) != m_pFriends->end();
}

vector<LanguageElement*> LanguageElement::sm_Elements;// TODO remove

// void setElementMap(element_map a_element_map)
// {
//     uint uiGuid;
//     element_container::iterator it = g_elements->begin();
//     element_container::iterator end = g_elements->end();
//     for (; it != end; it++)
//     {
//         uiGuid = a_element_map[(*it)->getQualifiedDecoratedName()];
//         (*it)->setGuid(uiGuid);
//     }
// }

//
// element_map getElementMap()
// {
//     element_map element_map;
//     element_container::iterator it = g_elements->begin();
//     element_container::iterator end = g_elements->end();
//     for (; it != end; it++)
//     {
//         element_map[(*it)->getQualifiedDecoratedName()] = (*it)->getGuid();
//     }
//
//     return element_map;
// }
//
// void Phantom::updateLanguageElementGuid()
// {
//     static uint s_uitransientGuid = 0;
//
//     element_container::iterator it = g_elements->begin();
//     element_container::iterator end = g_elements->end();
//     for (; it != end; it++)
//     {
//         s_uitransientGuid++;
//         (*it)->setGuid(s_uitransientGuid);
//     }
// }

o_namespace_end(phantom, reflection)
