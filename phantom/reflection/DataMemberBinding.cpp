/* TODO LICENCE HERE */

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include <phantom/reflection/DataMemberBinding.h>
#include <phantom/reflection/DataMemberBinding.hxx>
/* *********************************************** */
o_registerN((phantom, reflection), DataMemberBinding);

o_namespace_begin(phantom, reflection) 

DataMemberBinding::DataMemberBinding( void* a_pObject, DataMember* a_pDataMember ) 
    : NamedElement(a_pDataMember->getName(), a_pDataMember->getModifiers())
    , m_pObject(nullptr)
    , m_pDataMember(a_pDataMember)
{
    o_assert(a_pObject);
    reflection::Class* pClass = phantom::classAt(a_pObject, 0);
    // try a safe cast
    m_pObject = pClass ? pClass->cast(a_pDataMember->getOwnerClassType(), a_pObject) : a_pObject;
    // if not possible, store the pointer as given, supposing (hoping) it matches the given valueMember class owner
    if(m_pObject == nullptr)
    {
        m_pObject = a_pObject;
    }
    addReferencedElement(m_pDataMember);
}

void DataMemberBinding::referencedElementRemoved( LanguageElement* a_pElement )
{
    LanguageElement::referencedElementRemoved(a_pElement);
    if(m_pDataMember == a_pElement)
        m_pDataMember = nullptr;
}

o_namespace_end(phantom, reflection)