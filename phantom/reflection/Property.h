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

#ifndef o_phantom_reflection_Property_h__
#define o_phantom_reflection_Property_h__
// #pragma message("Including "__FILE__)


/* ****************** Includes ******************* */

/* *********************************************** */
/* The *.classdef.h file must be the last #include */
#include "Property.classdef.h"
/* **************** Declarations ***************** */

/* *********************************************** */

o_h_begin

class o_export Property : public ValueMember
{
public:
    Reflection_____________________________________________________________________________________
    _____________________________________________________________________________________Reflection

public:
    Property(const string& a_strName
        , Type* a_pValueType
        , InstanceMemberFunction* a_pSetMemberFunction
        , InstanceMemberFunction* a_pGetMemberFunction
        , Signal* a_pChangeNotificationSignal
        , Range* a_pRange
    , uint a_uiSerializationMask
    , bitfield a_Modifiers = 0);

    o_destructor ~Property(void) {}

    virtual void getValue(void const* a_pObject, void* dest) const = 0;
    virtual void setValue(void* a_pObject, void const* src) const = 0;
    Type*        getValueType() const { return m_pValueType; }
    virtual Property*      asProperty() const { return (Property*)this; }
        
    InstanceMemberFunction* getSetMemberFunction() const { return m_pSetMemberFunction; }
    InstanceMemberFunction* getGetMemberFunction() const { return m_pGetMemberFunction; }
    Signal* getChangeNotificationSignal() const { return m_pChangeNotificationSignal; }

protected:
    virtual void referencedElementRemoved(LanguageElement* a_pElement);

protected:
    Type*   m_pValueType;
    Signal* m_pChangeNotificationSignal;
    InstanceMemberFunction* m_pSetMemberFunction;
    InstanceMemberFunction* m_pGetMemberFunction;
};

o_h_end


#else // o_phantom_reflection_Property_h__
#include "Property.classdef.h"
#endif
