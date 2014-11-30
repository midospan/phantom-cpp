#pragma once

#include "ValueMember.hxx"

o_classNB((phantom, reflection), Property, (ValueMember), o_deferred|o_no_default_constructor) 
(
        o_property(string, signalString, setSignalString, getSignalString, o_no_signal, o_no_range, o_protected_access);
        o_property(string, setMemberFunctionString, setSetMemberFunctionString, getSetMemberFunctionString, o_no_signal, o_no_range, o_protected_access);
        o_property(string, getMemberFunctionString, setGetMemberFunctionString, getGetMemberFunctionString, o_no_signal, o_no_range, o_protected_access);
);




