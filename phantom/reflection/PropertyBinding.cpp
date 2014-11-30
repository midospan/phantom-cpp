/*
    This file is part of PHANTOM
         P reprocessed 
         H igh-level 
         A llocator 
         N ested state-machines and 
         T emplate 
         O riented 
         M eta-programming

    For the latest infos and sources, see http://code.google.com/p/phantom-cpp

    Copyright (C) 2008-2011 by Vivien MILLET

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
    THE SOFTWARE
*/

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
    Variable::referencedElementRemoved(a_pElement);
    if(m_pProperty == a_pElement)
        m_pProperty = nullptr;
}

PropertyBinding* PropertyBinding::clone() const
{
    return o_new(PropertyBinding)(m_pObject, m_pProperty);
}

o_namespace_end(phantom, reflection)