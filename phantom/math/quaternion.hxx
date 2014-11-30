#pragma once

o_structureNT((phantom, math), (typename), (t_Ty), axis_angle)
(
    o_nested_typedef(self_type);
    o_data_member(vector3<t_Ty>, axis);
    o_data_member(math::angle<t_Ty>, angle);
    o_member_function(bool, operator==, (const self_type&), o_const);
    o_member_function(bool, operator!=, (const self_type&), o_const);
);

o_structureNT((phantom, math), (typename), (t_Ty), quaternion)
(
    o_nested_typedef(self_type);
    o_data_member(t_Ty, x);
    o_data_member(t_Ty, y);
    o_data_member(t_Ty, z);
    o_data_member(t_Ty, w);
    o_property(axis_angle<t_Ty>, axisAngle, setAxisAngle, getAxisAngle);
    o_member_function(bool, operator==, (const self_type&), o_const);
    o_member_function(bool, operator!=, (const self_type&), o_const);
);
o_traits_specializeNT(has_has_something, (static const bool value = false;), (phantom, math), (typename), (t_Ty), quaternion);
