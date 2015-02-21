#pragma once

#include "NamedElement.hxx"

o_classNB((phantom, reflection), Package, (NamedElement), o_deferred|o_no_default_constructor) 
(
    o_signal(sourceAboutToBeRemoved, (Source*));
    o_signal(sourceAdded, (Source*));
    o_signal(elementAboutToBeRemoved, (LanguageElement*));
    o_signal(elementAdded, (LanguageElement*));
);





