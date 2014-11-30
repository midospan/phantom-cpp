#pragma once

#include "LanguageElement.hxx"

o_classNB((phantom, reflection), ValueMember, (LanguageElement), o_deferred|o_abstract) 
(
        o_data_member(uint, m_uiSerializationMask, o_no_range, o_protected_access);
        o_property(string, valueTypeName, setValueTypeName, getValueTypeName, o_no_signal, o_no_range, o_protected_access);
        o_property(Range*, range, setRange, getRange, o_no_signal, o_no_range, o_protected_access);
);




