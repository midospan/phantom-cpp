#pragma once

o_structureNT((phantom, math), (typename), (t_Ty), rect)
(
    o_nested_typedef(self_type);
o_protected:
    o_data_member(t_Ty, m_x);
    o_data_member(t_Ty, m_y);
    o_data_member(t_Ty, m_w, (t_Ty(0), std::numeric_limits<t_Ty>::max()));
    o_data_member(t_Ty, m_h, (t_Ty(0), std::numeric_limits<t_Ty>::max()));
o_public:
    o_property(t_Ty, x, setX, getX);
    o_property(t_Ty, y, setY, getY);
    o_property(t_Ty, width, setWidth, getWidth, o_no_signal, (t_Ty(0), std::numeric_limits<t_Ty>::max()));
    o_property(t_Ty, height, setHeight, getHeight, o_no_signal, (t_Ty(0), std::numeric_limits<t_Ty>::max()));
    o_member_function(bool, operator==, (const self_type&), o_const);
    o_member_function(bool, operator!=, (const self_type&), o_const);
);
