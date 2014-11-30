#pragma once

#include "LanguageElement.hxx"
#include "TemplateElement.hxx"

o_classNB((phantom, reflection), Type, (LanguageElement, TemplateElement), o_deferred|o_abstract)
(
o_public:
    o_member_function(void*, newInstance, ());
    o_member_function(void, deleteInstance, (void*));

o_protected:
//     o_signal(kindCreated, (void*));
//     o_signal(kindDestroyed, (void*));
);





