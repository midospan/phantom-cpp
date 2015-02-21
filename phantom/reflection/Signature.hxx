#pragma once

#include "NamedElement.hxx"

o_classNB((phantom, reflection), Signature, (NamedElement), o_deferred|0)
(
o_protected:
    o_property(string, returnTypeName, setReturnTypeName, getReturnTypeName);
    o_property(vector<Parameter*>, parameters, setParameters, getParameters);
);





