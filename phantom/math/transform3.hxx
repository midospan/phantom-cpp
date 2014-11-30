#pragma once

o_structureNT((phantom, math), (typename), (t_Ty), transform3)
(
    o_nested_typedef(self_type);
    o_nested_typedef(vector3_type);
    o_nested_typedef(quaternion_type);
    o_nested_typedef(matrix3x3_type);
    o_nested_typedef(matrix4x4_type);

    o_data_member(vector3_type, position);
    o_data_member(quaternion_type, orientation);
    o_data_member(vector3_type, scale);

    o_member_function(matrix4x4_type, toMatrix, (), o_const);
    o_member_function(void, toMatrix, (matrix4x4_type&), o_const);
    o_member_function(bool, operator==, (const self_type&), o_const);
    o_member_function(bool, operator!=, (const self_type&), o_const);
);