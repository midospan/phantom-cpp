#pragma once

o_structureNT((phantom, math), (typename), (t_Ty), transform2)
(
    o_nested_typedef(self_type);
    o_nested_typedef(vector2_type);
    o_nested_typedef(angle_type);
    o_nested_typedef(matrix3x3_type);
    o_nested_typedef(matrix2x2_type);

    o_data_member(vector2_type, position);
    o_data_member(angle_type, orientation);
    o_data_member(vector2_type, scale);

    o_member_function(void, setIdentity, ());
    o_member_function(void, set, (const vector2_type&, t_Ty, const vector2_type&));
    o_member_function(void, set, (const vector2_type&, t_Ty));
    o_member_function(matrix3x3_type, toMatrix, (), o_const);
    o_member_function(matrix3x3_type, toMatrixWithoutScale, (), o_const);
    o_member_function(void, toMatrix, (matrix3x3_type&), o_const);
    o_member_function(void, toMatrixWithoutScale, (matrix3x3_type&), o_const);
    o_member_function(matrix2x2_type, toRotationMatrix, (), o_const);
    o_member_function(void, toRotationMatrix, (matrix2x2_type&), o_const);
    o_member_function(bool, operator==, (const self_type&), o_const);
    o_member_function(bool, operator!=, (const self_type&), o_const);
);