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

#ifndef o_phantom_reflection_SubProperty_h__
#define o_phantom_reflection_SubProperty_h__
// #pragma message("Including "__FILE__)


/* ****************** Includes ******************* */
#include <phantom/reflection/Property.h>
/* *********************************************** */
/* The *.classdef.h file must be the last #include */
#include "SubProperty.classdef.h"
/* **************** Declarations ***************** */

/* *********************************************** */


o_h_begin


class o_export SubProperty : public Property
{
public:
    Reflection_____________________________________________________________________________________
    _____________________________________________________________________________________Reflection
public:

    SubProperty(const string& a_strName
    , Type*        a_pContentType
    , Property* a_pParentProperty
    , uint a_uiSubOffset
    , bitfield a_bfModifiers = bitfield());
    o_destructor ~SubProperty(void)     {}

    virtual        void        getValue(void const* a_pObject, void* dest) const;
    virtual        void        setValue(void* a_pObject, void const* src) const;

    virtual        Type*        getValueType() const {return m_pContentType;}

    Property*    getParentProperty() const { return m_pParentProperty; }

protected:
    Type*        m_pContentType;
    Property*    m_pParentProperty;
    uint        m_uiSubOffset;
};

o_h_end


#else // o_phantom_reflection_SubProperty_h__
#include "SubProperty.classdef.h"
#endif
