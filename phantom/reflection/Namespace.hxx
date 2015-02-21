#pragma once

#include "NamedElement.hxx"
#include "Scope.hxx"

o_classNB((phantom, reflection), Namespace, (NamedElement, Scope), o_deferred|o_no_default_constructor) 
(
    o_signal(namespaceAdded, (Namespace*))
    o_signal(namespaceRemoved, (Namespace*))
    o_signal(namespaceAliasAdded, (Alias*))
    o_signal(namespaceAliasRemoved, (Alias*))
    o_signal(anonymousSectionAdded, (AnonymousSection*))
    o_signal(anonymousSectionRemoved, (AnonymousSection*))
);





