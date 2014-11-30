#pragma once

#include "LanguageElement.hxx"

o_classNB((phantom, reflection), StaticVariable, (LanguageElement), o_deferred|o_no_default_constructor) 
(
        o_property(string, valueTypeName, setValueTypeName, getValueTypeName, o_no_signal, o_no_range, o_protected_access);
        o_property(Range*, range, setRange, getRange, o_no_signal, o_no_range, o_protected_access);
);




