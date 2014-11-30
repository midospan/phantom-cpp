#pragma once

o_structureNT((phantom, math), (typename), (t_Ty), vector2)
(
    o_nested_typedef(self_type);
    o_anonymous_union
    (
        o_data_member(t_Ty[2], m);
        o_anonymous_struct
        (
            o_data_member(t_Ty, x);
            o_data_member(t_Ty, y);
        );
    );

    o_member_function(void, set, (t_Ty a_x, t_Ty a_y));
    o_member_function(void, setZero, ());
    //o_member_function(self_type const&,  Zero, ());
    o_member_function(bool, isValid, (), o_const);
    o_member_function(t_Ty, length, (), o_const);
    o_member_function(t_Ty, lengthApproximated, (), o_const);
    o_member_function(t_Ty, lengthSquared, (), o_const);
    o_member_function(t_Ty, normalize, ());
    o_member_function(t_Ty, normalizeApproximated, ());
    o_member_function(self_type, normalized, (), o_const);
    o_member_function(self_type, normalizedApproximated, (), o_const);
    o_member_function(t_Ty, distance, (const self_type&), o_const);
    o_member_function(t_Ty, distanceApproximated, (const self_type&), o_const);
    o_member_function(t_Ty, distanceSquared, (const self_type&), o_const);
    o_member_function(self_type, to, (const self_type&), o_const);
    o_member_function(t_Ty, angleTo, (const self_type&), o_const);
    o_member_function(t_Ty,  fromPiToMinusPiAngleTo, (const self_type&), o_const);
	o_member_function(self_type, lerp, (const self_type&, const t_Ty&), o_const);
    o_member_function(bool, isZero, (), o_const );
    o_member_function(self_type, skewed, (), o_const);
    o_member_function(self_type, orthogonalCW, (), o_const);
    o_member_function(self_type, orthogonalCCW, (), o_const);
    o_member_function(self_type, operator+, (self_type const&), o_const);
    o_member_function(self_type, operator-, (self_type const&), o_const);
    o_member_function(self_type, operator*, (self_type const&), o_const);
    o_member_function(self_type, operator/, (self_type const&), o_const);
    o_member_function(self_type&, operator+=, (const self_type&));
    o_member_function(self_type&, operator-=, (const self_type&));
    o_member_function(self_type&, operator*=, (const self_type&));
    o_member_function(self_type&, operator/=, (const self_type&));
    o_member_function(t_Ty, dot, (self_type const&), o_const);
    o_member_function(t_Ty, cross, (self_type const&), o_const);
    o_member_function(self_type, cross, (t_Ty), o_const);
    o_member_function(self_type, operator+, (t_Ty), o_const);
    o_member_function(self_type, operator-, (t_Ty), o_const);
    o_member_function(self_type, operator*, (t_Ty), o_const);
    o_member_function(self_type, operator/, (t_Ty), o_const);
    o_member_function(self_type&, operator*=, (t_Ty));
    o_member_function(self_type&, operator/=, (t_Ty));
    o_member_function(t_Ty&, operator[], (uint));
    o_member_function(t_Ty const&, operator[], (uint), o_const);
    o_member_function(self_type, operator-, (), o_const);
    o_member_function(bool, operator==, (const self_type&), o_const);
    o_member_function(bool, operator!=, (const self_type&), o_const);
);