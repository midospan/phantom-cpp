/* TODO LICENCE HERE */

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include <phantom/reflection/MemberAnonymousSection.h>
#include <phantom/reflection/MemberAnonymousSection.hxx>
/* *********************************************** */
o_registerN((phantom, reflection), MemberAnonymousSection);

o_namespace_begin(phantom, reflection)

o_define_meta_type(MemberAnonymousSection) = o_type_of(MemberAnonymousSection);

MemberAnonymousSection::MemberAnonymousSection( modifiers_t modifiers /*= 0*/ )
    : NamedElement("", modifiers)
{

}

void MemberAnonymousSection::addDataMember( DataMember* a_pDataMember )
{
    if(a_pDataMember)
    {
        addReferencedElement(a_pDataMember);
    } 
    else setInvalid();
    m_DataMembers.push_back(a_pDataMember);
    o_assert(a_pDataMember->m_pMemberAnonymousSection == nullptr);
    a_pDataMember->m_pMemberAnonymousSection = this;
}

void MemberAnonymousSection::referencedElementRemoved( LanguageElement* a_pElement )
{
    auto found = std::find(m_DataMembers.begin(), m_DataMembers.end(), a_pElement);
    if(found != m_DataMembers.end())
    {
        m_DataMembers.erase(found);
        o_assert(a_pElement->asDataMember());
        static_cast<DataMember*>(a_pElement)->m_pMemberAnonymousSection = nullptr;
    }
}

o_namespace_end(phantom, reflection)
