/* TODO LICENCE HERE */

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include <phantom/reflection/PropertyBinding.h>
#include <phantom/reflection/PropertyBinding.hxx>
/* *********************************************** */
o_registerN((phantom, reflection), PropertyBinding);

o_namespace_begin(phantom, reflection) 

PropertyBinding::PropertyBinding( void* a_pObject, Property* a_pProperty ) 
    : m_pObject(a_pObject)
    , m_pProperty(a_pProperty)
{
    reflection::Class* pClass = phantom::classAt(a_pObject, 0);
    // try a safe cast
    m_pObject = pClass ? pClass->cast(a_pProperty->getOwnerClassType(), a_pObject) : a_pObject;
    // if not possible, store the pointer as given, supposing (hoping) it matches the given valueMember class owner
    if(m_pObject == nullptr)
    {
        m_pObject = a_pObject;
    }
    addReferencedElement(a_pProperty);
}

o_initialize_cpp(PropertyBinding)
{
    if(m_pProperty->getSignal())
    {
        auto thisRtti = rttiDataOf(this);
        phantom::connect(rttiDataOf(m_pObject, getProperty()->getOwnerClass()), getProperty()->getSignal(), thisRtti, thisRtti.object_class->getSignalCascade("valueChanged()"), __FILE__, __LINE__);
    }
}

void PropertyBinding::referencedElementRemoved( LanguageElement* a_pElement )
{
    if(m_pProperty == a_pElement)
        m_pProperty = nullptr;
}

PropertyBinding* PropertyBinding::clone() const
{
    return o_new(PropertyBinding)(m_pObject, m_pProperty);
}

o_namespace_end(phantom, reflection)