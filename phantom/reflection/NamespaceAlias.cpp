/* TODO LICENCE HERE */

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include <phantom/reflection/NamespaceAlias.h>
#include <phantom/reflection/NamespaceAlias.hxx>
/* *********************************************** */
o_registerN((phantom, reflection), NamespaceAlias);

o_namespace_begin(phantom, reflection) 

Class* const NamespaceAlias::metaType = o_type_of(phantom::reflection::NamespaceAlias);

NamespaceAlias::NamespaceAlias( const string& a_strName, Namespace* a_pNamespace, modifiers_t a_Modifiers /*= 0*/ ) : NamedElement(a_strName, a_Modifiers)
    , m_pNamespace(a_pNamespace)
{
    if(m_pNamespace)
        addReferencedElement(m_pNamespace);
    else 
        setInvalid();
}

void NamespaceAlias::referencedElementRemoved( LanguageElement* a_pElement )
{
    if(m_pNamespace == a_pElement)
        m_pNamespace = nullptr;
}

o_namespace_end(phantom, reflection)
