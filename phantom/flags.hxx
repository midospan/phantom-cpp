#pragma once

o_namespace_begin(phantom)

template<typename Enum> 
struct has_has_something<flags<Enum>> 
{ 
    const static bool value = false; 
};

o_namespace_end(phantom)

o_classNT((phantom), (typename), (Enum), flags, o_pod)
{
    o_reflection 
    {
        o_member_function(int, operator int, (), o_protected);
    };
};
