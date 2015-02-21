/* TODO LICENCE HERE */

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include <phantom/reflection/LanguageElement.h>
#include <phantom/reflection/LanguageElement.hxx>
#include "phantom/Message.h"
#include <phantom/string.h>
#include <phantom/vector.hxx>
#include <stdarg.h>
/* ** The Class Header must be the last #include * */
/* *********************************************** */
o_registerN((phantom, reflection), LanguageElement);
o_registerNTI((phantom), vector, (phantom::reflection::LanguageElement*));


o_namespace_begin(phantom, reflection)

o_invalid_def(LanguageElement);

static vector<LanguageElement*>* empty_elements;

LanguageElement::LanguageElement()
    : m_pElements(nullptr)
    , m_pReferencedElements(nullptr)
    , m_pReferencingElements(nullptr)
    , m_pOwner(nullptr)
    , m_pStatusMessage(nullptr)
{
    if(empty_elements == 0)
    {
        empty_elements = new vector<LanguageElement*>;
    }
	Register(this);
}

LanguageElement::~LanguageElement()
{
}

o_terminate_cpp(LanguageElement)
{
    setInvalid();
    o_assert(canBeDestroyed());
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
    if(m_pStatusMessage)
        o_dynamic_delete m_pStatusMessage;

    Unregister(this);
}

vector<LanguageElement*>::const_iterator LanguageElement::beginElements() const
{
    return m_pElements ? m_pElements->begin() : empty_elements->begin();
}

vector<LanguageElement*>::const_iterator LanguageElement::endElements() const
{
    return m_pElements ? m_pElements->end() : empty_elements->end();
}

vector<LanguageElement*>::const_iterator LanguageElement::beginReferencedElements() const
{
    return m_pReferencedElements ? m_pReferencedElements->begin() : empty_elements->begin();
}

vector<LanguageElement*>::const_iterator LanguageElement::endReferencedElements() const
{
    return m_pReferencedElements ? m_pReferencedElements->end() : empty_elements->end();
}

vector<LanguageElement*>::const_iterator LanguageElement::beginReferencingElements() const
{
    return m_pReferencedElements ? m_pReferencedElements->begin() : empty_elements->begin();
}

vector<LanguageElement*>::const_iterator LanguageElement::endReferencingElements() const
{
    return m_pReferencingElements ? m_pReferencingElements->end() : empty_elements->end();
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
    // ownedElementAdded(a_pElement);
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
    if(a_pElement->isInvalid()) setInvalid();
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

bool LanguageElement::canBeDestroyed() const
{
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
}

void LanguageElement::elementRemoved( LanguageElement* a_pElement )
{
}

void LanguageElement::referencedElementInvalidated( LanguageElement* a_pElement )
{

}

Block* LanguageElement::getEnclosingBlock() const
{
    Block* pBlock;
    return m_pOwner ? ((pBlock = m_pOwner->asBlock()) ? m_pOwner->asBlock() : m_pOwner->getEnclosingBlock()) : nullptr ;
}

Scope* LanguageElement::getEnclosingScope() const
{
    Scope* pScope;
    return m_pOwner ? ((pScope = m_pOwner->asScope()) ? pScope : m_pOwner->getEnclosingScope()) : nullptr ;
}

Namespace* LanguageElement::getEnclosingNamespace() const
{
    Namespace* pNamespace;
    return m_pOwner ? ((pNamespace = m_pOwner->asNamespace()) ? pNamespace : m_pOwner->getEnclosingNamespace()) : nullptr ;
}

Statement* LanguageElement::getEnclosingStatement() const
{
    return m_pOwner ? (m_pOwner->asStatement() ? m_pOwner->asStatement() : m_pOwner->getEnclosingStatement()) : nullptr ;
}

void LanguageElement::internalAncestorChanged( LanguageElement* a_pOwner )
{
    if(m_pElements)
    {
        vector<LanguageElement*> elementsCopy(m_pElements->begin(), m_pElements->end()); /// copy to allow element adding during recursive deep call
        for(auto it = elementsCopy.begin(); it != elementsCopy.end(); ++it)
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
    return m_pOwner ? m_pOwner->isNative() : false;
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

bool LanguageElement::isInvalid() const
{
    return m_pStatusMessage AND m_pStatusMessage->getType() == e_MessageType_Error;
}

void LanguageElement::setInvalid()
{
    if(isInvalid() OR isAlwaysValid())
        return;
    o_assert(!isNative());
    if(m_pStatusMessage == nullptr) 
        m_pStatusMessage = o_new(Message)(e_MessageType_Error, "undefined error");
    else 
        m_pStatusMessage->setType(e_MessageType_Error);
    /// When an element becomes invalid, the following becomes invalid too :
    /// - the elements who have reference to it
    /// - its owner element
    /// - its children elements  
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

ReferenceType* LanguageElement::asConstReferenceType() const
{
    ReferenceType* pReferenceType = asReferenceType(); 
    return (pReferenceType AND pReferenceType->getReferencedType()->asConstType()) 
        ? pReferenceType 
        : nullptr;
}

/*

bool LanguageElement::hasTemplateDependantElement() const
{
    if(m_pElements)
    {
        for(auto it = m_pElements->begin(); it != m_pElements->end(); ++it)
        {
            if((*it)->isTemplateDependant()) return true;
        }
    }
    return false;
}

bool LanguageElement::hasTemplateDependantReferencedElement() const
{
    if(m_pReferencedElements)
    {
        for(auto it = m_pReferencedElements->begin(); it != m_pReferencedElements->end(); ++it)
        {
            if((*it)->isTemplateDependant()) return true;
        }
    }
    return false;
}*/

bool LanguageElement::partialAccepts( LanguageElement* a_pLanguageElement, size_t& a_Score, map<Placeholder*, LanguageElement*>& a_Deductions ) const
{
    if(a_pLanguageElement == this) 
    {
        a_Score = ~size_t(0);
        return true;
    }
    return false;
}

bool LanguageElement::equals( LanguageElement* a_pOther ) const
{
    return (this == a_pOther);
}

void LanguageElement::elementDefined( LanguageElement* a_pElement )
{

}

Module* LanguageElement::getModule() const
{
    return m_pOwner ? m_pOwner->getModule() : nullptr;
}

void LanguageElement::addScopedElement( LanguageElement* a_pElement )
{
    o_assert(a_pElement->m_pOwner == nullptr); 
    a_pElement->m_pOwner = this; 
    addReferencedElement(a_pElement);
}

void LanguageElement::removeScopedElement( LanguageElement* a_pElement )
{
    o_assert(a_pElement->m_pOwner == this); 
    a_pElement->m_pOwner = nullptr; 
    removeReferencedElement(a_pElement);
}

void LanguageElement::replaceElement( LanguageElement* a_pOldElement, LanguageElement* a_pNewElement )
{
    *std::find(m_pElements->begin(), m_pElements->end(), a_pOldElement) = a_pNewElement;
}

void LanguageElement::fetchReferencedModules( set<Module*>& a_Modules ) const
{
    if(m_pReferencedElements)
    {
        for(auto it = m_pReferencedElements->begin(); it != m_pReferencedElements->end(); ++it)
        {
            a_Modules.insert((*it)->getModule());
        }
    }
}

void LanguageElement::fetchReferencingModules( set<Module*>& a_Modules ) const
{
    if(m_pReferencingElements)
    {
        for(auto it = m_pReferencingElements->begin(); it != m_pReferencingElements->end(); ++it)
        {
            a_Modules.insert((*it)->getModule());
        }
    }
}

void LanguageElement::fetchReferencedModulesCascade( set<Module*>& a_Modules ) const
{
    fetchReferencedModules(a_Modules);
    if(m_pElements)
    {
        for(auto it = m_pElements->begin(); it != m_pElements->end(); ++it)
        {
            (*it)->fetchReferencedModulesCascade(a_Modules);
        }
    }
}

void LanguageElement::fetchReferencingModulesCascade( set<Module*>& a_Modules ) const
{
    fetchReferencingModules(a_Modules);
    if(m_pElements)
    {
        for(auto it = m_pElements->begin(); it != m_pElements->end(); ++it)
        {
            (*it)->fetchReferencingModulesCascade(a_Modules);
        }
    }
}

void LanguageElement::fetchElements( vector<LanguageElement*>& a_Elements ) const
{
    if(m_pElements)
    {
        a_Elements.insert(a_Elements.end(), m_pElements->begin(), m_pElements->end());
    }
}

void LanguageElement::fetchElementsCascade( vector<LanguageElement*>& a_Elements ) const
{
    fetchElements(a_Elements);
    if(m_pElements)
    {
        for(auto it = m_pElements->begin(); it != m_pElements->end(); ++it)
        {
            (*it)->fetchElementsCascade(a_Elements);
        }
    }
}

bool LanguageElement::hasReferencedElement( LanguageElement* a_pLanguageElement ) const
{
    if(m_pReferencedElements)
    {
        for(auto it = m_pReferencedElements->begin(); it != m_pReferencedElements->end(); ++it)
        {
            if(*it == a_pLanguageElement) return true;
        }
    }
    return false;
}

bool LanguageElement::hasReferencingElement( LanguageElement* a_pLanguageElement ) const
{
    if(m_pReferencingElements)
    {
        for(auto it = m_pReferencingElements->begin(); it != m_pReferencingElements->end(); ++it)
        {
            if(*it == a_pLanguageElement) return true;
        }
    }
    return false;
}

void LanguageElement::dumpElementList( ostream& out ) const
{
    if(m_pElements)
    {
        for(auto it = m_pElements->begin(); it != m_pElements->end(); ++it)
        {
            out << (*it)->getUniqueDecoratedName() << std::endl;
        }
    }
}

void LanguageElement::dumpElementListCascade( ostream& out ) const
{
    if(m_pElements)
    {
        dumpElementList(out);
        for(auto it = m_pElements->begin(); it != m_pElements->end(); ++it)
        {
            (*it)->dumpElementListCascade(out);
        }
    }
}

Language* LanguageElement::getLanguage() const
{
    Source* pSource = getSource();
    return pSource ? pSource->getLanguage() : phantom::application()->getDefaultLanguage();
}

bool LanguageElement::hasAccessTo( NamedElement* a_pElement, NamedElement* a_pAccessElementOwner /*= nullptr*/ ) const
{
    return static_cast<LanguageElement const*>(a_pElement)->equals(const_cast<LanguageElement*>(this))
        OR hasElement(a_pElement)
        OR (m_pOwner AND m_pOwner->hasAccessTo(a_pElement))
        OR (a_pAccessElementOwner AND (a_pAccessElementOwner->hasPublicMember(a_pElement) OR a_pAccessElementOwner->hasFriend(const_cast<LanguageElement*>(this))))
        OR (!a_pAccessElementOwner AND (a_pElement->isPublic() OR ((a_pElement->m_pOwner AND a_pElement->m_pOwner->hasFriend(const_cast<LanguageElement*>(this))))));
}

Message* LanguageElement::error( const char* a_Format, ... )
{
    setInvalid();
    va_list args;
    va_start(args, a_Format);
    m_pStatusMessage->format(a_Format, args);
    va_end(args);
    return m_pStatusMessage;
}

Message* LanguageElement::subError( const char* a_Format, ... )
{
    o_assert(m_pStatusMessage)
    va_list args;
    va_start(args, a_Format);
    Message* pSubMessage = m_pStatusMessage->error(this, a_Format, args);
    va_end(args);
    return pSubMessage;
}

void LanguageElement::addNamedElement( NamedElement* a_pElement )
{
    if(isNative())
    {
        /// If native => check doubles only in debug version and assert if needed
        o_debug_only(
            if(a_pElement->getName().size() AND m_pElements) /// we accept anonymous doubles
                for(auto it = m_pElements->begin(); it != m_pElements->end(); ++it)
                {
                    NamedElement* pNamedElement = (*it)->asNamedElement();
                    o_assert(pNamedElement == nullptr OR pNamedElement->getDecoratedName() != a_pElement->getDecoratedName(), "equal element already added : be careful not having duplicate member declarations in your class, or check not registering not two type with same name in the same source");
                }
                );
    }
    else 
    {
        /// If not native => check doubles and invalidate if needed
        if(a_pElement->getName().size() AND m_pElements)
            for(auto it = m_pElements->begin(); it != m_pElements->end(); ++it)
            {
                NamedElement* pNamedElement = (*it)->asNamedElement();
                if(pNamedElement AND pNamedElement->getDecoratedName() == a_pElement->getDecoratedName())
                {
                    setInvalid();
                    break;
                }
            }
    }
    addElement(a_pElement);
}

bool LanguageElement::isTemplateElement() const
{
    TemplateSpecialization* pSpec = getAscendantTemplateSpecialization();
    return pSpec AND (NOT(pSpec->isFull()) OR pSpec->isTemplateElement());
}

bool LanguageElement::isTemplateDependant() const
{
    if(m_pElements)
    {
        for(auto it = m_pElements->begin(); it != m_pElements->end(); ++it)
        {
            if((*it)->isTemplateDependant()) return true;
        }
    }
    return false;
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

NamedElement* LanguageElement::getUniqueElement( const string& name, modifiers_t modifiers ) const
{
    NamedElement* pElement = nullptr;
    if(m_pElements)
    {
        for(auto it = m_pElements->begin(); it != m_pElements->end(); ++it)
        {
            NamedElement* pNamedElement = (*it)->asNamedElement();
            if(pNamedElement AND pNamedElement->getName() == name AND pNamedElement->testModifiers(modifiers))
            {
                if(pElement) return nullptr;
                else pElement = pNamedElement;
            }
        }
    }
    return pElement;
}

Expression* LanguageElement::toExpression( Expression* a_pOptExpression ) const
{
    return getLanguage()->toExpression(const_cast<LanguageElement*>(this), a_pOptExpression);
}

bool LanguageElement::hasNamingScopeCascade( Scope* a_pScope ) const
{
    Scope* pScope = getNamingScope();
    return (pScope != nullptr) AND ((pScope == a_pScope) OR pScope->asLanguageElement()->hasNamingScopeCascade(a_pScope));
}

string LanguageElement::translate( int a_TranslationType /*= e_translation_qualified_decorated_name*/, LanguageElement* a_pScope /*= globalNamespace()*/ ) const
{
    string result; 
    getLanguage()->translate(const_cast<LanguageElement*>(this), result, a_TranslationType, a_pScope); 
    return result;
}

void LanguageElement::translate( string& out, int a_TranslationType /*= e_translation_qualified_decorated_name*/, LanguageElement* a_pScope /*= globalNamespace()*/ ) const
{
    getLanguage()->translate(const_cast<LanguageElement*>(this), out, a_TranslationType, a_pScope);
}

o_namespace_end(phantom, reflection)

