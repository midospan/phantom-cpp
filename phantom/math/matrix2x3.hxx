#pragma once

o_structureNT((phantom, math), (typename), (t_Ty), matrix2x3)
(
    o_nested_typedef(self_type);
    o_nested_typedef(vector3_type);
    o_anonymous_union
    (
        o_data_member(t_Ty[6], m);
        o_data_member(t_Ty[3][2], mm);
        o_anonymous_struct
        (
            o_data_member(vector3_type, ex);
            o_data_member(vector3_type, ey);
        );
    );
    o_member_function(bool, operator==, (const self_type&), o_const);
    o_member_function(bool, operator!=, (const self_type&), o_const);
);