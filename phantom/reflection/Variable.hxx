#pragma once

#include "LanguageElement.hxx"

o_classNB((phantom, reflection), Variable, (LanguageElement), o_deferred|o_abstract) 
(
        o_signal(valueChanged, (), o_protected_access);
);





