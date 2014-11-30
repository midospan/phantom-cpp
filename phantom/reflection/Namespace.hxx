#pragma once
#include "LanguageElement.hxx"
o_classNB((phantom, reflection), Namespace, (LanguageElement), o_deferred|o_no_default_constructor) 
(
        o_signal(typeAdded, (Type*))
        o_signal(typeRemoved, (Type*))
        o_signal(templateAdded, (Template*))
        o_signal(templateRemoved, (Template*))
        o_signal(namespaceAdded, (Namespace*))
        o_signal(namespaceRemoved, (Namespace*))
        o_signal(functionAdded, (Function*))
        o_signal(functionRemoved, (Function*))
);





