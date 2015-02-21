/* TODO LICENCE HERE */

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include <phantom/reflection/NamedElement.h>
#include <phantom/reflection/NamedElement.hxx>
#include <phantom/string.h>
#include <phantom/vector.hxx>
/* ** The Class Header must be the last #include * */
/* *********************************************** */
o_registerN((phantom, reflection), NamedElement);
o_registerNTI((phantom), vector, (phantom::reflection::NamedElement*));


o_namespace_begin(phantom, reflection)

static vector<NamedElement*> empty_elements;

NamedElement::NamedElement(modifiers_t a_Modifiers/* = 0*/)
    : m_uiGuid(0)
    , m_pMetaData(nullptr)
    , m_Modifiers(a_Modifiers)
    , m_pNamespace(nullptr)
{
    Register(this);
    if(m_Modifiers & o_invalid) setInvalid();
}

NamedElement::NamedElement( const string& a_strName, modifiers_t a_Modifiers /*= 0*/ )
    : m_strName(a_strName)
    , m_uiGuid(0)
    , m_pMetaData(nullptr)
    , m_Modifiers(a_Modifiers)
    , m_pNamespace(nullptr)
{
    o_assert(NOT(isProtected() AND isPrivate()), "o_private_access and o_protected_access cannot co-exist");
    Register(this);
    if(m_Modifiers & o_invalid) setInvalid();
}

NamedElement::~NamedElement()
{
    o_assert(m_uiGuid == o_invalid_guid, "probably you haven't called terminate before calling delete");
}

o_terminate_cpp(NamedElement)
{
    m_Modifiers |= o_terminated;
    if(m_pMetaData != nullptr)
    {
        size_t count = phantom::metaDataCount();
        o_delete_n(count, string) m_pMetaData;
        m_pMetaData = nullptr;
    }
    m_uiGuid = o_invalid_guid;
}

phantom::string NamedElement::getQualifiedName() const
{
    Scope* pScope = getNamingScope();
    string ownerName = pScope ? pScope->asNamedElement()->getQualifiedName() : "";
    return m_strName.empty() 
                ? ownerName 
                : ownerName.empty() 
                    ? m_strName 
                    : (ownerName + o_CS("::") + m_strName);
}

phantom::string NamedElement::getDecoratedName() const
{
    return getName();
}

phantom::string NamedElement::getQualifiedDecoratedName() const
{
    return getQualifiedName();
}

void NamedElement::setGuid(uint a_uiGuid)
{
	m_uiGuid = a_uiGuid;
}

void NamedElement::teardownMetaDataCascade( size_t count )
{
    if(m_pMetaData != nullptr)
    {
        o_delete_n(count, string) m_pMetaData;
        m_pMetaData = nullptr;
    }
    if(m_pElements)
    for(auto it = m_pElements->begin(); it != m_pElements->end(); ++it)
    {
        NamedElement* pNamedElement = (*it)->asNamedElement();
        if(pNamedElement)
        {
            pNamedElement->teardownMetaDataCascade(count);
        }
    }
}

void NamedElement::setupMetaData( size_t count )
{
    o_assert(m_pMetaData == nullptr);
}

const string& NamedElement::getMetaDataValue( size_t index ) const
{
    static string null_string;
    o_assert(index == eInvalidMetaDataIndex || index < phantom::metaDataCount());
    return m_pMetaData == nullptr ? null_string : (index != eInvalidMetaDataIndex) ? m_pMetaData[index] : null_string;
}

void NamedElement::setMetaDataValue( size_t index, const string& value )
{
    o_assert(index < phantom::metaDataCount());
    if(m_pMetaData == nullptr)
    {
        m_pMetaData = o_new_n(phantom::metaDataCount(), string);
    }
    m_pMetaData[index] = value;
}

void NamedElement::setModifiers( modifiers_t a_Modifiers )
{
    m_Modifiers = a_Modifiers;
    if(m_Modifiers & o_invalid) setInvalid();
    o_assert(NOT(isPublic() AND isProtected()), "o_public_access and o_protected_access cannot co-exist");
}

boolean NamedElement::isNative() const
{
    return (m_Modifiers & o_native) == o_native;
}

void NamedElement::setTemplateDependant()
{
    m_Modifiers |= o_template_dependant;
}

bool NamedElement::equals( LanguageElement* a_pOther ) const
{
    if(this == a_pOther) return true;
    if(a_pOther->asNamedElement() == nullptr) return false;
    return equals(static_cast<NamedElement*>(a_pOther));
}

bool NamedElement::equals( NamedElement* a_pOther ) const
{
    if(this == a_pOther) return true;
    bool bTemplate;
    if((bTemplate = testModifiers(o_template)) != a_pOther->testModifiers(o_template)) return false;
    return bTemplate AND ((getQualifiedDecoratedName() == a_pOther->getQualifiedDecoratedName()));
}

bool NamedElement::hasElementWithName( const string& a_strName ) const
{
    if(m_pElements)
    {
        for(auto it = m_pElements->begin(); it != m_pElements->end(); ++it)
        {
            NamedElement* pNamedElement = (*it)->asNamedElement();
            if(pNamedElement AND pNamedElement->getName() == a_strName) return true;
        }
    }
    return false;
}

Scope* NamedElement::getNamingScope() const
{
    return m_pNamespace ? m_pNamespace : m_pOwner ? m_pOwner->asScope() : nullptr;
}

Namespace* NamedElement::getNamespace() const
{
    return m_pNamespace;
}

void NamedElement::getDoubles( vector<NamedElement*>& out ) const
{
    Scope* pNamingScope = getNamingScope();
    if(pNamingScope)
    {
        pNamingScope->getElementDoubles(const_cast<NamedElement*>(this), out);
    }
}

bool NamedElement::hasPublicMember( NamedElement* a_pNamedElement ) const
{
    return hasElement(a_pNamedElement) AND a_pNamedElement->isPublic();
}

bool NamedElement::hasProtectedMember( NamedElement* a_pNamedElement ) const
{
    return hasElement(a_pNamedElement) AND a_pNamedElement->isProtected();
}

bool NamedElement::hasPrivateMember( NamedElement* a_pNamedElement ) const
{
    return hasElement(a_pNamedElement) AND a_pNamedElement->isPrivate();
}

string NamedElement::getUniqueName() const
{
    string up = m_pOwner ? m_pOwner->getUniqueName() : "";
    return up.size() ? up + '.' + m_strName : m_strName;
}

string NamedElement::getUniqueDecoratedName() const
{
    string up = m_pOwner ? m_pOwner->getUniqueName() : "";
    return up.size() ? up + '.' + getDecoratedName() : getDecoratedName();
}

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
// void Phantom::updateNamedElementGuid()
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

persistent_element::persistent_element()
    : m_pElement(nullptr)
{
}

persistent_element::persistent_element( const persistent_element& a_Other )
    : m_pElement(a_Other.m_pElement)
{
    if(m_pElement)
    {
        m_pElement->getModule()->registerPersistentElement(this);
    }
}

persistent_element::~persistent_element()
{
    if(m_pElement)
    {
        m_pElement->getModule()->unregisterPersistentElement(this);
    }
}

persistent_element& persistent_element::operator=( const persistent_element& a_Other )
{
    if(m_pElement == a_Other.m_pElement) return *this;
    if(m_pElement 
        AND a_Other.m_pElement 
        AND m_pElement->getModule() == a_Other.m_pElement->getModule())
    {
        m_pElement = a_Other.m_pElement;
    }
    else 
    {
        if(m_pElement)
        {
            m_pElement->getModule()->unregisterPersistentElement(this);
        }
        m_pElement = a_Other.m_pElement;
        if(m_pElement)
        {
            m_pElement->getModule()->registerPersistentElement(this);
        }
    }
    return *this;
}

o_namespace_end(phantom, reflection)

