#pragma once

#include "NamedElement.hxx"

o_classNB((phantom, reflection), ValueMember, (NamedElement), o_deferred|o_abstract) 
(
o_protected:
    o_data_member(uint, m_uiSerializationMask);
    o_property(Range*, range, setRange, getRange);
);




