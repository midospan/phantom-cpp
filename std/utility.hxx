#pragma once

#include "iosfwd.hxx"

#if o_COMPILER == o_COMPILER_VISUAL_STUDIO
// _Container_base
o_classN((std), _Container_base0)
(
        );


// _Container_base12
o_classN((std), _Container_base12)
(
        );


// _Pair_base
o_classNT((std), (typename, typename), (t_First, t_Second), _Pair_base
    , o_no_copy * (phantom::has_copy_disabled_cascade<t_First>::value
    OR phantom::has_copy_disabled<t_Second>::value))
(
);

#endif // o_COMPILER == o_COMPILER_VISUAL_STUDIO

// pair
o_classNT((std), (typename, typename), (t_First, t_Second), pair, o_no_copy_of(t_First)|o_no_copy_of(t_Second))
(
o_public:
    o_data_member(t_First, first);
    o_data_member(t_Second, second);
);

