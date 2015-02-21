/* TODO LICENCE HERE */

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include "Package.h"
#include "Package.hxx"
/* *********************************************** */
o_registerN((phantom, reflection), Package);

o_namespace_begin(phantom, reflection)
    
 o_invalid_def(Package, Module::Invalid(), "<unknown-package>");

Package::Package( Module* a_pModule, const string& a_strName )
    : NamedElement(a_strName, (a_strName == "<unknown-package>") ? o_invalid : o_always_valid)
    , m_pNamespace(nullptr)
{
    m_pNamespace = phantom::globalNamespace()->findOrCreateNamespaceCascade(m_strName, ".");
    o_assert(m_pNamespace);
    addReferencedElement(m_pNamespace);
    a_pModule->addPackage(this);
}

Package::~Package()
{

}

o_initialize_cpp(Package)
{
    o_connect(this, elementAdded(LanguageElement*), m_pOwner, elementAdded(LanguageElement*));
    o_connect(this, elementAboutToBeRemoved(LanguageElement*), m_pOwner, elementAboutToBeRemoved(LanguageElement*));
}

o_terminate_cpp(Package)
{
    o_disconnect(this, elementAdded(LanguageElement*), m_pOwner, elementAdded(LanguageElement*));
    o_disconnect(this, elementAboutToBeRemoved(LanguageElement*), m_pOwner, elementAboutToBeRemoved(LanguageElement*));
}

bool Package::canBeUnloaded() const
{
    for(auto it = m_Sources.begin(); it != m_Sources.end(); ++it)
    {
        if(NOT((*it)->canBeUnloaded())) return false;
    }
    return true;
}

void Package::addSource(Source* a_pSource)
{
    o_assert(a_pSource->m_pOwner == nullptr);
    o_assert(getSource(a_pSource->getName()) == nullptr, "a source with same name already exists in this package");
    m_Sources.push_back(a_pSource);
    addElement(a_pSource);
    o_emit sourceAdded(a_pSource);
}

Source* Package::addSource( Language* a_pLanguage, const string& a_strSource )
{
    if(getSource(a_strSource))
    {
        return nullptr;
    }
    return o_new(Source)(this, a_pLanguage, a_strSource);
}

void Package::elementRemoved( LanguageElement* a_pElement )
{
    if(a_pElement->asNamespace())
    {
        m_pNamespace = nullptr;
    }
    else if(a_pElement->asSource())
    {
        Source* pSource = static_cast<Source*>(a_pElement);
        o_emit sourceAboutToBeRemoved(pSource);
        o_assert(pSource->m_pOwner == this);
        m_Sources.erase(std::find(m_Sources.begin(), m_Sources.end(), pSource));
    }
}

void Package::removeSource(Source* a_pSource)
{
    removeElement(a_pSource);
}

bool Package::hasSource( Source* a_pSource ) const
{
    return std::find(m_Sources.begin(), m_Sources.end(), a_pSource) != m_Sources.end();
}

phantom::signal_t Package::sourceAdded(Source* a_0)
{
    if(PHANTOM_CODEGEN_m_slot_list_of_sourceAdded.unblocked())
    {
        phantom::connection::slot* pSlot = PHANTOM_CODEGEN_m_slot_list_of_sourceAdded.head();
        while(pSlot)
        {
            phantom::connection::pair::push(this, pSlot);
            void* args[] = { (void*)(&a_0) };
            pSlot->subroutine()->call( pSlot->receiver(), args );
            pSlot = pSlot->next();
            phantom::connection::pair::pop();
        }
    }
    return phantom::signal_t();
}

phantom::signal_t Package::sourceAboutToBeRemoved(Source* a_0)
{
    if(PHANTOM_CODEGEN_m_slot_list_of_sourceAboutToBeRemoved.unblocked())
    {
        phantom::connection::slot* pSlot = PHANTOM_CODEGEN_m_slot_list_of_sourceAboutToBeRemoved.head();
        while(pSlot)
        {
            phantom::connection::pair::push(this, pSlot);
            void* args[] = { (void*)(&a_0) };
            pSlot->subroutine()->call( pSlot->receiver(), args );
            pSlot = pSlot->next();
            phantom::connection::pair::pop();
        }
    }
    return phantom::signal_t();
}

Source* Package::getSource( const string& a_strName ) const
{
    for(auto it = m_Sources.begin(); it != m_Sources.end(); ++it)
    {
        if((*it)->getName() == a_strName)
            return *it;
    }
    return nullptr;
}

void Package::setNamespace( Namespace* a_pNamespace )
{
    o_assert((m_pNamespace == nullptr) != (a_pNamespace == nullptr));
    if(a_pNamespace == nullptr)
    {
        removeElement(a_pNamespace);
    }
    else 
    {
        m_pNamespace = a_pNamespace;
        addElement(m_pNamespace);
    }
}

phantom::signal_t Package::elementAdded(LanguageElement* a_0)
{
    if(PHANTOM_CODEGEN_m_slot_list_of_elementAdded.unblocked())
    {
        phantom::connection::slot* pSlot = PHANTOM_CODEGEN_m_slot_list_of_elementAdded.head();
        while(pSlot)
        {
            phantom::connection::pair::push(this, pSlot);
            void* args[] = { (void*)(&a_0) };
            pSlot->subroutine()->call( pSlot->receiver(), args );
            pSlot = pSlot->next();
            phantom::connection::pair::pop();
        }
    }
    return phantom::signal_t();
}

phantom::signal_t Package::elementAboutToBeRemoved(LanguageElement* a_0)
{
    if(PHANTOM_CODEGEN_m_slot_list_of_elementAboutToBeRemoved.unblocked())
    {
        phantom::connection::slot* pSlot = PHANTOM_CODEGEN_m_slot_list_of_elementAboutToBeRemoved.head();
        while(pSlot)
        {
            phantom::connection::pair::push(this, pSlot);
            void* args[] = { (void*)(&a_0) };
            pSlot->subroutine()->call( pSlot->receiver(), args );
            pSlot = pSlot->next();
            phantom::connection::pair::pop();
        }
    }
    return phantom::signal_t();
}

string Package::getQualifiedName() const
{
    return m_pOwner->getQualifiedDecoratedName() + ':' + getName();
}

string Package::getUniqueName() const
{
    string up = m_pOwner ? static_cast<NamedElement*>(m_pOwner)->getUniqueName() : "";
    return up.size() ? up + '@' + m_strName : m_strName;
}

string Package::getUniqueDecoratedName() const
{
    string up = m_pOwner ? static_cast<NamedElement*>(m_pOwner)->getUniqueName() : "";
    return up.size() ? up + '@' + getDecoratedName() : getDecoratedName();
}

o_namespace_end(phantom, reflection)
