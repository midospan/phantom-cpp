#pragma once

#include <phantom/string.h>

o_declareN(class, (phantom), Module);

o_classN((phantom, qt), ModuleExplorer, o_no_copy)
(
o_protected:
    o_slot(void, libraryLoaded, (const string&));
    o_slot(void, libraryUnloaded, (const string&));
    o_slot(void, moduleLoaded, (reflection::Module*, size_t, size_t));
    o_slot(void, moduleUnloaded, (reflection::Module*, size_t, size_t));
);
