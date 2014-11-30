#pragma once

#include "phantom/std/vector.h"
#include "phantom/std/map.h"

o_classN((unitest), RootClass)
(
o_public:
    o_nested_typedef(self_map);
    o_member_function(int, instance_member_function, (int));
    o_member_function(RootClass*, static_member_function, ());
    o_member_function(void, aVirtualMemberFunction, (), o_virtual);
    o_member_function(void, const_tester_member_function, (), o_noconst);
    o_member_function(void, const_tester_member_function, (), o_const);
    o_slot(void, mult, (phantom::real));
    o_signal(signal, (phantom::real));
    o_property(int, property, set_member_function, get_member_function);
    o_property(int, propertyNotified, set_property, get_property, propertyChanged);

o_protected:
    o_constructor((int));
    o_member_function(void, protected_member_function, ());
    o_data_member(self_map, m_SelfMap);
    o_data_member(phantom::uint, m_uiInstanceDataMember);
    o_data_member(RootClass*, m_pStaticDataMember);
    o_data_member(phantom::vector<RootClass*>, m_SelfVector);
);
