#pragma once

#include "NamedElement.hxx"

o_classNB((phantom, reflection), Module, (NamedElement), o_deferred|o_no_default_constructor) 
(
    o_signal(elementAboutToBeRemoved, (LanguageElement*));
    o_signal(elementAdded, (LanguageElement*));
);





