#pragma once

#include "ClassType.hxx"

o_classNB((phantom, reflection), Class, (ClassType), o_deferred|o_abstract) 
(
    o_property(vector<string>, baseClasseNames, setBaseClasseNames, getBaseClasseNames, o_no_signal, o_no_range, o_protected_access);
);
o_static_assert(phantom::base_class_count_of<phantom::reflection::Class>::value);




