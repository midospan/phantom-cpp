/* TODO LICENCE HERE */

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include "phantom/Message.h"
#include "Source.h"
#include "Source.hxx"
#include "Package.h"
#include "Import.h"
#include "Application.h"
#include <stdarg.h>
/* *********************************************** */
o_registerN((phantom, reflection), Source);

o_namespace_begin(phantom, reflection) 

o_invalid_def(Source, Package::Invalid(), nullptr, "<unknown-source>", o_invalid);

Source::Source(Package* a_pPackage, Language* a_pLanguage, const string& a_strName, modifiers_t a_Modifiers)
: NamedElement(a_strName, (a_Modifiers&o_invalid) ? a_Modifiers : (o_always_valid|a_Modifiers))
, Scope(this)
, m_pPrecompiler(nullptr)
, m_pLanguage(a_pLanguage)
{
    if(m_pLanguage == nullptr) setInvalid();
    a_pPackage->addSource(this);
}

o_initialize_cpp(Source)
{
    o_connect(this, elementAdded(LanguageElement*), m_pOwner, elementAdded(LanguageElement*));
    o_connect(this, elementAboutToBeRemoved(LanguageElement*), m_pOwner, elementAboutToBeRemoved(LanguageElement*));
}

o_terminate_cpp(Source)
{
    o_disconnect(this, elementAdded(LanguageElement*), m_pOwner, elementAdded(LanguageElement*));
    o_disconnect(this, elementAboutToBeRemoved(LanguageElement*), m_pOwner, elementAboutToBeRemoved(LanguageElement*));
}

/*

void Source::getElements(const CodePosition& a_Position, vector<LanguageElement*>& out)
{
    for(auto it = m_LanguageElements.begin(); it != m_LanguageElements.end(); ++it)
    {
        if(it->first.containsCodePosition(a_Position))
        {
            out.push_back(it->second);
        }
    }
}*/

bool Source::canBeUnloaded() const
{
    set<Module*> referencingModules;
    fetchReferencingModulesCascade(referencingModules);
    return referencingModules.empty() OR ((referencingModules.size() == 1) AND ((*referencingModules.begin()) == getModule()));
}

phantom::signal_t Source::elementAdded(LanguageElement* a_0)
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

phantom::signal_t Source::elementAboutToBeRemoved(LanguageElement* a_0)
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

Package* Source::getPackage() const
{
    return static_cast<Package*>(m_pOwner);
}

string Source::getQualifiedName() const
{
    return getPackage()->getQualifiedName()+'.'+getName();
}

void Source::addScopeElement( NamedElement* a_pElement )
{
    addElement(a_pElement);
    o_error(a_pElement->getNamespace(), "any element added at source root must have a namespace");
    if(a_pElement->getNamespace() != getPackage()->getCounterpartNamespace())
    {
        o_warning(false, "element added to source '%s' have namespace name '%s' different from source package name '%s', this could lead to scope deduction mistakes or conflicts", getName().c_str(), a_pElement->getNamespace()->getQualifiedDecoratedName().c_str(), getPackage()->getName().c_str());
    }
    if(application()->getLoadedModuleCount())
    {
        o_emit elementAdded(a_pElement);
    }
//     string elementName = a_pElement->getName();
//     std::for_each(elementName.begin(), elementName.end(), tolower);
//     if(elementName == getName()) 
}

void Source::removeScopeElement( NamedElement* a_pElement )
{
    if(application()->getLoadedModuleCount())
    {
        o_emit elementAboutToBeRemoved(a_pElement);
    }
    removeElement(a_pElement);
}

void Source::precompile()
{
    if(m_pPrecompiler == nullptr)
    {
        m_pPrecompiler = m_pLanguage->createPrecompiler(this);
    }
    m_pPrecompiler->precompileSource();
}

void Source::precompile( int pass )
{
    if(m_pPrecompiler == nullptr)
    {
        m_pPrecompiler = m_pLanguage->createPrecompiler(this);
    }
    m_pPrecompiler->precompileSource(pass);
}

void Source::outdate()
{
    if(m_pPrecompiler)
    {
        m_pLanguage->destroyPrecompiler(m_pPrecompiler);
        m_pPrecompiler = nullptr;
    }
    m_pMessage->clear();
}

void Source::error( const CodeLocation& a_Location, const char* a_Format, ... )
{
    va_list args;
    va_start(args, a_Format);
    Message* pMessage = m_pMessage->message(e_MessageType_Error, a_Location, a_Format, args);
    va_end(args);
}

void Source::warning( const CodeLocation& a_Location, const char* a_Format, ... )
{
    va_list args;
    va_start(args, a_Format);
    Message* pMessage = m_pMessage->message(e_MessageType_Warning, a_Location, a_Format, args);
    va_end(args);
}

bool Source::hasError() const
{
    return m_pMessage->getMostValuableMessageType() == e_MessageType_Error;
}

void Source::elementRemoved( LanguageElement* a_pElement )
{
    Scope::scopedElementRemoved(a_pElement);
}

void Source::finalize()
{
    Scope::finalize();
}

o_namespace_end(phantom, reflection)
