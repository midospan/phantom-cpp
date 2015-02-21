#pragma once

#include "Type.hxx"
#include "Scope.hxx"

o_classNB((phantom, reflection), ClassType, (Type, Scope), o_deferred|o_abstract) 
(
o_protected:
    o_property(vector<DataMember*>, instanceDataMembers,setDataMembers, getDataMembers);
    o_property(vector<MemberFunction*>, instanceMemberFunctions,setMemberFunctions, getMemberFunctions);
    o_property(vector<Constructor*>, constructors, setConstructors, getConstructors);
    o_property(vector<Property*>, properties, setProperties, getProperties);
    o_signal(dataMemberAdded, (DataMember*));
    o_signal(dataMemberRemoved, (DataMember*));
    o_signal(constructorAdded, (Constructor*));
    o_signal(constructorRemoved, (Constructor*));
    o_signal(memberFunctionAdded, (MemberFunction*));
    o_signal(memberFunctionRemoved, (MemberFunction*));
    o_signal(propertyAdded, (Property*));
    o_signal(propertyRemoved, (Property*));
    o_signal(memberAnonymousSectionAdded, (MemberAnonymousSection*));
    o_signal(memberAnonymousSectionRemoved, (MemberAnonymousSection*));
);





