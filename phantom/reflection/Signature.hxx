#pragma once

#include "LanguageElement.hxx"

o_classNB((phantom, reflection), Signature, (LanguageElement), o_deferred|0)
(
    o_data_member(vector<string>, m_ParameterNames, o_no_range, o_protected_access);
    o_property(string, returnTypeName, setReturnTypeName, getReturnTypeName, o_no_signal, o_no_range, o_protected_access);
    o_property(vector<string>, parameterTypeNames, setParameterTypeNames, getParameterTypeNames, o_no_signal, o_no_range, o_protected_access);
);





