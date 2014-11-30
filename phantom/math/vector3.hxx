#pragma once

o_structureNT((phantom, math), (typename), (t_Ty), vector3)
(
    o_nested_typedef(self_type);
    o_anonymous_union
    (
        o_data_member(t_Ty[3], m);
        o_anonymous_struct
        (
            o_data_member(t_Ty, x);
            o_data_member(t_Ty, y);
            o_data_member(t_Ty, z);
        );
    );
    o_member_function(bool, operator==, (const self_type&), o_const);
    o_member_function(bool, operator!=, (const self_type&), o_const);
);