#pragma once

#include "phantom/std/vector.h"
#include "phantom/std/map.h"

o_classN((unitest), RootClass)
{
    o_reflection 
    {
        o_member_function(int, instance_member_function, (int));
        o_member_function(RootClass*, static_member_function, (), o_static);
        o_slot(void, mult, (phantom::real));
        o_member_function(void, aVirtualMemberFunction, (), o_virtual);
        o_signal(signal, (phantom::real));
        o_property(int, property, set_member_function, get_member_function, o_no_signal, o_no_range, o_public);
        o_data_member(phantom::uint, m_uiInstanceDataMember, o_no_range, o_protected);
        o_data_member(RootClass*, m_pStaticDataMember, o_no_range, o_static);
        o_data_member(phantom::vector<RootClass*>, m_SelfVector, o_no_range, o_protected);
        o_typedef(self_map);
        o_data_member(self_map, m_SelfMap, o_no_range, o_protected);
        o_member_function(void, const_tester_member_function,(), o_noconst);
        o_member_function(void, const_tester_member_function,(), o_const);
    };
};
o_exposeN((unitest), RootClass);