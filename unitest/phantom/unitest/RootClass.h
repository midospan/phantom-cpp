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

    void const_tester_member_function() {}
    void const_tester_member_function() const {}

    RootClass(void);
    o_destructor ~RootClass(void) {}

    int                 instance_member_function(int a_iValue) 
    { 
        return a_iValue; 
    }
    void                set_member_function(int a_iValue)    {}
    int                 get_member_function(void) const        { return 0; }
    static RootClass*   static_member_function() 
    {
        return m_pStaticDataMember;
    }

    o_signal_data(signal, phantom::real);

    void    mult(phantom::real a_fFactor)
    {
        m_fMultAcc *= a_fFactor;
    }

    void    setInstanceDataMemberValue(phantom::uint a_uiValue)
    {
        m_uiInstanceDataMember = a_uiValue;
    }

    virtual void aVirtualMemberFunction() const { return; }
    
    phantom::uint            m_uiInstanceDataMember;
    static RootClass*        m_pStaticDataMember;
    phantom::real            m_fMultAcc;
};

o_namespace_end(unitest)

o_classN((unitest), RootClass)
{
    o_reflection 
    {
        o_member_function(int, instance_member_function, (int))
        o_member_function(RootClass*, static_member_function, (), o_static)
        o_slot(void, mult, (phantom::real))
        o_member_function(int, get_member_function, ())
        o_member_function(void, set_member_function, (int))
        o_member_function(void, aVirtualMemberFunction, (), o_virtual)
        o_signal(signal, (phantom::real))
        o_property(int, property, set_member_function, get_member_function, o_no_signal, o_no_range, o_public)
        o_data_member(phantom::uint, m_uiInstanceDataMember, o_no_range, o_protected)
        o_data_member(RootClass*, m_pStaticDataMember, o_no_range, o_static)
        o_member_function(void, const_tester_member_function,(), o_noconst)
        o_member_function(void, const_tester_member_function,(), o_const)
    };
};
o_exposeN((unitest), RootClass);


#endif
