#pragma once

#include "phantom/reflection/Class.hxx"

o_classNS((phantom, reflection, jit), JitClass, (Class))
{
    o_reflection 
    {
        o_signal(aboutToBeReplaced, (JitClass*,JitClass*));
    };
};

o_exposeN((phantom, reflection, jit), JitClass);
