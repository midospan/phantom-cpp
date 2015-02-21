/* TODO LICENCE HERE */

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include <phantom/reflection/AnonymousSection.h>
#include <phantom/reflection/AnonymousSection.hxx>
/* *********************************************** */
o_registerN((phantom, reflection), AnonymousSection);

o_namespace_begin(phantom, reflection)

o_define_meta_type(AnonymousSection) = o_type_of(AnonymousSection);

AnonymousSection::AnonymousSection( modifiers_t modifiers /*= 0*/ )
    : NamedElement("", modifiers)
{

}

void AnonymousSection::addVariable( Variable* a_pVariable )
{
    if(a_pVariable)
    {
        addReferencedElement(a_pVariable);
    } 
    else setInvalid();
    m_Variables.push_back(a_pVariable);
    o_assert(a_pVariable->m_pAnonymousSection == nullptr);
    a_pVariable->m_pAnonymousSection = this;
}

void AnonymousSection::referencedElementRemoved( LanguageElement* a_pElement )
{
    auto found = std::find(m_Variables.begin(), m_Variables.end(), a_pElement);
    if(found != m_Variables.end())
    {
        m_Variables.erase(found);
        o_assert(a_pElement->asVariable());
        static_cast<Variable*>(a_pElement)->m_pAnonymousSection = nullptr;
    }
}

o_namespace_end(phantom, reflection)
