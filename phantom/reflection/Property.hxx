#pragma once

#include "ValueMember.hxx"

o_classNB((phantom, reflection), Property, (ValueMember), o_deferred|o_no_default_constructor) 
(
o_protected:
    o_property(string, signalString, setSignalString, getSignalString);
    o_property(string, setMemberFunctionString, setSetMemberFunctionString, getSetMemberFunctionString);
    o_property(string, getMemberFunctionString, setGetMemberFunctionString, getGetMemberFunctionString);
);




