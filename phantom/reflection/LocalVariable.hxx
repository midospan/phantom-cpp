#pragma once

#include "LanguageElement.hxx"

o_classNB((phantom, reflection), LocalVariable, (LanguageElement))
(
        o_data_member(int, m_iFrameOffset, o_no_range, o_protected_access);
        o_property(string, valueTypeName, setValueTypeName, getValueTypeName, o_no_signal, o_no_range, o_protected_access);
);
