#pragma once

#include "NamedElement.hxx"

o_classNB((phantom, reflection), LocalVariable, (NamedElement), o_deferred)
(
o_protected:
    o_data_member(int, m_iFrameOffset);
    o_property(string, valueTypeName, setValueTypeName, getValueTypeName);
);
