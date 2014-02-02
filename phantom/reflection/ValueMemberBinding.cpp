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
#include <phantom/reflection/ValueMemberBinding.h>
#include <phantom/reflection/ValueMemberBinding.hxx>
/* *********************************************** */
o_registerN((phantom, reflection), ValueMemberBinding);

o_namespace_begin(phantom, reflection) 

ValueMemberBinding::ValueMemberBinding( void* a_pObject, ValueMember* a_pValueMember ) 
    : Variable(a_pValueMember->getName(), a_pValueMember->getRange() ? a_pValueMember->getRange()->clone() : nullptr, a_pValueMember->getModifiers())
    , m_pObject(nullptr)
    , m_pValueMember(a_pValueMember)
{
    o_assert(a_pObject);
    reflection::Class* pClass = phantom::classAt(a_pObject);
    // try a safe cast
    m_pObject = pClass ? pClass->cast(a_pValueMember->getOwnerClassType(), a_pObject) : a_pObject;
    // if not possible, store the pointer as given, supposing (hoping) it matches the given valueMember class owner
    if(m_pObject == nullptr)
    {
        m_pObject = a_pObject;
    }
}


o_namespace_end(phantom, reflection)