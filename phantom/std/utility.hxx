#pragma once

#include "iosfwd.hxx"

// _Container_base
o_classN((std), _Container_base0)
{
    o_reflection {};
};
o_exposeN((std), _Container_base0);

// _Container_base12
o_classN((std), _Container_base12)
{
    o_reflection {};
};
o_exposeN((std), _Container_base12);

// _Pair_base
o_classNT((std), (typename, typename), (t_First, t_Second), _Pair_base
    , o_no_copy * (phantom::has_copy_disabled_cascade<t_First>::value 
    OR phantom::has_copy_disabled<t_Second>::value))
{
    o_reflection 
    {
    };
};
o_exposeNT((std), (typename, typename), (t_First, t_Second), _Pair_base);

// pair
o_classNT((std), (typename, typename), (t_First, t_Second), pair, o_no_copy * (phantom::has_copy_disabled_cascade<t_First>::value 
    OR phantom::has_copy_disabled<t_Second>::value))
{
    o_reflection
    {
        o_data_member(t_First, first, o_no_range, o_public) ;
        o_data_member(t_Second, second, o_no_range, o_public);
    };
};

o_exposeNT((std), (typename, typename), (t_First, t_Second), pair);