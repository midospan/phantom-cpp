#pragma once

#include <phantom/std/string.h>

o_declareN(class, (phantom), Module);

o_classN((phantom, qt), ModuleExplorer, o_no_copy)
{
    o_reflection
    {
        o_slot(void, libraryLoaded, (const string&));
        o_slot(void, libraryUnloaded, (const string&));
        o_slot(void, moduleLoaded, (Module*, size_t, size_t));
        o_slot(void, moduleUnloaded, (Module*, size_t, size_t));
    };
};
o_exposeN((phantom, qt), ModuleExplorer);