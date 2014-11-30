#pragma once

o_structureNT((phantom, math), (typename), (t_Ty), segment2)
(
    o_nested_typedef(self_type);
    o_nested_typedef(vector2_type);
    o_data_member(vector2_type, start);
    o_data_member(vector2_type, end);
    o_member_function(bool, operator==, (const self_type&), o_const);
    o_member_function(bool, operator!=, (const self_type&), o_const);
);