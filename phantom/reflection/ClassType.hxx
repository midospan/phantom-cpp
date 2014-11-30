#pragma once

#include "Type.hxx"

o_classNB((phantom, reflection), ClassType, (Type), o_deferred|o_abstract) 
(
    o_property(vector<InstanceDataMember*>, instanceDataMembers,setInstanceDataMembers, getInstanceDataMembers, o_no_signal, o_no_range, o_protected_access);
    o_property(vector<InstanceMemberFunction*>, instanceMemberFunctions,setInstanceMemberFunctions, getInstanceMemberFunctions, o_no_signal, o_no_range, o_protected_access);
    o_property(vector<Constructor*>, constructors, setConstructors, getConstructors, o_no_signal, o_no_range, o_protected_access);
    o_property(vector<Property*>, properties, setProperties, getProperties, o_no_signal, o_no_range, o_protected_access);
    o_property(vector<StaticDataMember*>, staticDataMembers,setStaticDataMembers, getStaticDataMembers, o_no_signal, o_no_range, o_protected_access);
    o_property(vector<StaticMemberFunction*>, staticMemberFunctions,setStaticMemberFunctions, getStaticMemberFunctions, o_no_signal, o_no_range, o_protected_access);
);





