#pragma once

o_structureNT((phantom, math), (typename), (t_Ty), angle)
(
    o_nested_typedef(self_type);
    o_property(t_Ty, degree, setDegree, getDegree);
    o_property(t_Ty, radian, setRadian, getRadian);
    o_member_function(bool, operator==, (const self_type&), o_const);
    o_member_function(bool, operator!=, (const self_type&), o_const);
);
