/* TODO LICENCE HERE */

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include <phantom/reflection/Alias.h>
#include <phantom/reflection/Alias.hxx>
/* *********************************************** */
o_registerN((phantom, reflection), Alias);

o_namespace_begin(phantom, reflection) 

o_define_meta_type(Alias);

Alias::Alias( modifiers_t a_Modifiers /*= 0*/ )
    : NamedElement("", a_Modifiers)
    , m_pAliases(nullptr)
    , m_pElement(nullptr)
{

}

Alias::Alias( const string& a_strName, modifiers_t a_Modifiers /*= 0*/ )
    : NamedElement(a_strName, a_Modifiers)
    , m_pAliases(nullptr)
    , m_pElement(nullptr)
{

}

Alias::Alias( NamedElement* a_pElement, const string& a_strName, modifiers_t a_Modifiers /*= 0*/ ) 
    : NamedElement(a_strName)
    , m_pElement(a_pElement)
    , m_pAliases(nullptr)
{
    if(m_pElement)
    {
        addReferencedElement(m_pElement);
    }
    else setInvalid();
}

void Alias::referencedElementRemoved( LanguageElement* a_pElement )
{
    if(m_pElement == a_pElement)
        m_pElement = nullptr;
}

Alias* Alias::getAlias( const string& a_strName ) const
{
    if(m_pAliases)
    {
        for(auto it = m_pAliases->begin(); it != m_pAliases->end(); ++it)
        {
            if((*it)->getName() == a_strName) return *it;
        }
    }
    return nullptr;
}

o_namespace_end(phantom, reflection)
