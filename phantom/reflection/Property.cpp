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
/* ** The Class Header must be the last #include * */
#include "Property.h"
/* *********************************************** */
o_cpp_begin 

ReflectionCPP__________________________________________________________________________________
__________________________________________________________________________________ReflectionCPP

Property::Property( const string& a_strName, Type* a_pValueType, InstanceMemberFunction* a_pSetMemberFunction, InstanceMemberFunction* a_pGetMemberFunction, Signal* a_pChangeNotificationSignal, Range* a_pRange, uint a_uiSerializationMask, bitfield a_Modifiers /*= 0*/ ) 
    : ValueMember(a_strName, a_pRange, a_uiSerializationMask, a_Modifiers) 
    , m_pValueType(a_pValueType)
    , m_pSetMemberFunction(a_pSetMemberFunction)
    , m_pGetMemberFunction(a_pGetMemberFunction)
    , m_pChangeNotificationSignal(a_pChangeNotificationSignal)
{
    o_assert(m_pGetMemberFunction->getSignature()->getReturnType() == m_pValueType);
    o_assert(m_pSetMemberFunction->getSignature()->getParameterCount() == 1 && m_pSetMemberFunction->getSignature()->getParameterType(0) == m_pValueType);
    o_assert(m_pChangeNotificationSignal == nullptr 
        || m_pChangeNotificationSignal->getSignature()->getParameterCount() == 0 
        || (m_pChangeNotificationSignal->getSignature()->getParameterCount() == 1 && m_pChangeNotificationSignal->getSignature()->getParameterType(0) == m_pValueType));
    // TODO : fix this, put it in o_property ...
    if(m_pChangeNotificationSignal && m_pChangeNotificationSignal->getOwner() == nullptr)
        a_pSetMemberFunction->getOwnerClass()->addSignal(m_pChangeNotificationSignal);
    addReferencedElement(a_pValueType);
    addReferencedElement(a_pSetMemberFunction);
    addReferencedElement(a_pGetMemberFunction);
    if(m_pChangeNotificationSignal)
        addReferencedElement(m_pChangeNotificationSignal);
}

void Property::referencedElementRemoved( LanguageElement* a_pElement )
{
    ValueMember::referencedElementRemoved(a_pElement);
    if(m_pChangeNotificationSignal == a_pElement)
        m_pChangeNotificationSignal = nullptr;
    else if(m_pGetMemberFunction == a_pElement)
        m_pGetMemberFunction = nullptr;
    else if(m_pSetMemberFunction == a_pElement)
        m_pSetMemberFunction = nullptr;
}


o_cpp_end
