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

#ifndef unitest_RootClass_h__
#define unitest_RootClass_h__

/* ****************** Includes ******************* */
#include "phantom/phantom.h"
/* **************** Declarations ***************** */
/* *********************************************** */

o_namespace_begin(unitest)
    
class RootClass
{

public:
    o_initialize() {}
    o_terminate() {}

    void const_tester_method() {}
    void const_tester_method() const {}

    RootClass(void);
    o_destructor ~RootClass(void) {}

    int                 instance_method(int a_iValue) 
    { 
        return a_iValue; 
    }
    void                set_method(int a_iValue)    {}
    int                 get_method(void) const        { return 0; }
    static RootClass*   static_method() 
    {
        return m_pStaticAttribute;
    }

    o_signal_data(signal, phantom::real);

    void    mult(phantom::real a_fFactor)
    {
        m_fMultAcc *= a_fFactor;
    }

    void    setInstanceAttributeValue(phantom::uint a_uiValue)
    {
        m_uiInstanceAttribute = a_uiValue;
    }

    virtual void aVirtualMethod() const { return; }
    
    phantom::uint            m_uiInstanceAttribute;
    static RootClass*        m_pStaticAttribute;
    phantom::real            m_fMultAcc;
};

o_namespace_end(unitest)

o_classN((unitest), RootClass)
{
    o_reflection 
    {
        o_method(int, instance_method, (int))
        o_method(RootClass*, static_method, (), o_static)
        o_slot(void, mult, (phantom::real))
        o_method(int, get_method, ())
        o_method(void, set_method, (int))
        o_method(void, aVirtualMethod, (), o_virtual)
        o_signal(signal, (phantom::real))
        o_accessor(int, accessor, set_method, get_method, o_public)
        o_attribute(phantom::uint, m_uiInstanceAttribute, o_protected)
        o_attribute(RootClass*, m_pStaticAttribute, o_static)
        o_method(void, const_tester_method,(), o_noconst)
        o_method(void, const_tester_method,(), o_const)
    };
};
o_exposeN((unitest), RootClass);


#endif
