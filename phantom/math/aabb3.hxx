#pragma once

o_structureNT((phantom, math), (typename), (t_Ty), aabb3)
(
    o_nested_typedef(self_type);
    o_nested_typedef(vector3_type);
    o_data_member(vector3_type, min);
    o_data_member(vector3_type, max);
    o_member_function(bool, operator==, (const self_type&), o_const);
    o_member_function(bool, operator!=, (const self_type&), o_const);
);