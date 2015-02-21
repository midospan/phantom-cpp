#pragma once

#include "NamedElement.hxx"

o_classNB((phantom, reflection), Variable, (NamedElement), o_deferred|o_no_default_constructor) 
(
o_protected:
    o_property(string, valueTypeName, setValueTypeName, getValueTypeName);
    o_property(Range*, range, setRange, getRange);
);




