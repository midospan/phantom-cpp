#pragma once

#include "phantom/reflection/StaticMemberFunction.hxx"
#include "JitSubroutine.hxx"

o_classNS((phantom, reflection, jit), JitStaticMemberFunction, (StaticMemberFunction, JitSubroutine))
{
    o_reflection
    {

    };
};
o_exposeN((phantom, reflection, jit), JitStaticMemberFunction);
