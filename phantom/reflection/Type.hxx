#pragma once

#include "NamedElement.hxx"

o_classNB((phantom, reflection), Type, (NamedElement), o_deferred)
(
o_public:
    o_member_function(void*, newInstance, ());
    o_member_function(void, deleteInstance, (void*));

o_protected:
    o_signal(kindCreated, (void*));
    o_signal(kindDestroyed, (void*));
);





