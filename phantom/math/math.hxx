#pragma once

o_classNT((phantom, math), (typename), (t_Ty), vector2)
{
    o_reflection
    {
        o_typedef(self_type);
        o_data_member(t_Ty, x, o_no_range, o_public);
        o_data_member(t_Ty, y, o_no_range, o_public);

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
    };
};

o_classNT((phantom, math), (typename), (t_Ty), vector3)
{
    o_reflection
    {
        o_data_member(t_Ty[3], m, o_no_range, o_public|o_union_alternative);
        o_data_member(t_Ty, x, o_no_range, o_public|o_transient);
        o_data_member(t_Ty, y, o_no_range, o_public|o_transient);
        o_data_member(t_Ty, z, o_no_range, o_public|o_transient);
    };
};

o_classNT((phantom, math), (typename), (t_Ty), vector4)
{
	o_reflection
	{
		o_data_member(t_Ty[4], m, o_no_range, o_public|o_union_alternative);
		o_data_member(t_Ty, x, o_no_range, o_public|o_transient);
		o_data_member(t_Ty, y, o_no_range, o_public|o_transient);
		o_data_member(t_Ty, z, o_no_range, o_public|o_transient);
		o_data_member(t_Ty, w, o_no_range, o_public|o_transient);
	};
};

o_classNT((phantom, math), (typename), (t_Ty), matrix2x2)
{
    o_reflection
    {
        o_typedef(vector2_type);
        o_data_member(t_Ty[4], m, o_no_range, o_public|o_union_alternative);
        o_data_member(t_Ty[2][2], mm, o_no_range, o_public|o_union_alternative|o_transient);
        o_data_member(vector2_type, ex, o_no_range, o_public|o_transient);
        o_data_member(vector2_type, ey, o_no_range, o_public|o_transient);
    };
};

o_classNT((phantom, math), (typename), (t_Ty), matrix2x3)
{
    o_reflection
    {
        o_typedef(vector3_type);
        o_data_member(t_Ty[6], m, o_no_range, o_public|o_union_alternative);
        o_data_member(t_Ty[3][2], mm, o_no_range, o_public|o_union_alternative|o_transient);
        o_data_member(vector3_type, ex, o_no_range, o_public|o_transient);
        o_data_member(vector3_type, ey, o_no_range, o_public|o_transient);
    };
};

o_classNT((phantom, math), (typename), (t_Ty), matrix2x4)
{
    o_reflection
    {
        o_typedef(vector4_type);
        o_data_member(t_Ty[8], m, o_no_range, o_public|o_union_alternative);
        o_data_member(t_Ty[4][2], mm, o_no_range, o_public|o_union_alternative|o_transient);
        o_data_member(vector4_type, ex, o_no_range, o_public|o_transient);
        o_data_member(vector4_type, ey, o_no_range, o_public|o_transient);
    };
};

o_classNT((phantom, math), (typename), (t_Ty), matrix3x2)
{
    o_reflection
    {
        o_typedef(vector2_type);
        o_data_member(t_Ty[6], m, o_no_range, o_public|o_union_alternative);
        o_data_member(t_Ty[2][3], mm, o_no_range, o_public|o_union_alternative|o_transient);
        o_data_member(vector2_type, ex, o_no_range, o_public|o_transient);
        o_data_member(vector2_type, ey, o_no_range, o_public|o_transient);
        o_data_member(vector2_type, ez, o_no_range, o_public|o_transient);
    };
};

o_classNT((phantom, math), (typename), (t_Ty), matrix3x3)
{
    o_reflection
    {
        o_typedef(vector3_type);
        o_data_member(t_Ty[9], m, o_no_range, o_public|o_union_alternative);
        o_data_member(t_Ty[3][3], mm, o_no_range, o_public|o_union_alternative|o_transient);
        o_data_member(vector3_type, ex, o_no_range, o_public|o_transient);
        o_data_member(vector3_type, ey, o_no_range, o_public|o_transient);
        o_data_member(vector3_type, ez, o_no_range, o_public|o_transient);
    };
};

o_classNT((phantom, math), (typename), (t_Ty), matrix3x4)
{
    o_reflection
    {
        o_typedef(vector4_type);
        o_data_member(t_Ty[12], m, o_no_range, o_public|o_union_alternative);
        o_data_member(t_Ty[4][3], mm, o_no_range, o_public|o_union_alternative|o_transient);
        o_data_member(vector4_type, ex, o_no_range, o_public|o_transient);
        o_data_member(vector4_type, ey, o_no_range, o_public|o_transient);
        o_data_member(vector4_type, ez, o_no_range, o_public|o_transient);
    };
};

o_classNT((phantom, math), (typename), (t_Ty), matrix4x2)
{
    o_reflection
    {
        o_typedef(vector2_type);
        o_data_member(t_Ty[8], m, o_no_range, o_public|o_union_alternative);
        o_data_member(t_Ty[2][4], mm, o_no_range, o_public|o_union_alternative|o_transient);
        o_data_member(vector2_type, ex, o_no_range, o_public|o_transient);
        o_data_member(vector2_type, ey, o_no_range, o_public|o_transient);
        o_data_member(vector2_type, ez, o_no_range, o_public|o_transient);
        o_data_member(vector2_type, ew, o_no_range, o_public|o_transient);
    };
};

o_classNT((phantom, math), (typename), (t_Ty), matrix4x3)
{
    o_reflection
    {
        o_typedef(vector3_type);
        o_data_member(t_Ty[12], m, o_no_range, o_public|o_union_alternative);
        o_data_member(t_Ty[3][4], mm, o_no_range, o_public|o_union_alternative|o_transient);
        o_data_member(vector3_type, ex, o_no_range, o_public|o_transient);
        o_data_member(vector3_type, ey, o_no_range, o_public|o_transient);
        o_data_member(vector3_type, ez, o_no_range, o_public|o_transient);
        o_data_member(vector3_type, ew, o_no_range, o_public|o_transient);
    };
};

o_classNT((phantom, math), (typename), (t_Ty), matrix4x4)
{
    o_reflection
    {
        o_typedef(vector4_type);
        o_data_member(t_Ty[16], m, o_no_range, o_public|o_union_alternative);
        o_data_member(t_Ty[4][4], mm, o_no_range, o_public|o_union_alternative|o_transient);
        o_data_member(vector4_type, ex, o_no_range, o_public|o_transient);
        o_data_member(vector4_type, ey, o_no_range, o_public|o_transient);
        o_data_member(vector4_type, ez, o_no_range, o_public|o_transient);
        o_data_member(vector4_type, ew, o_no_range, o_public|o_transient);
    };
};

o_classNT((phantom, math), (typename), (t_Ty), angle)
{
    o_reflection
    {
        o_typedef(self_type);
        o_property(t_Ty, degree, setDegree, getDegree, o_no_signal, o_no_range, o_public|o_transient);
        o_property(t_Ty, radian, setRadian, getRadian, o_no_signal, o_no_range, o_public);
        o_member_function(bool, operator==, (const self_type&), o_const);
        o_member_function(bool, operator!=, (const self_type&), o_const);
    };
};

o_classNT((phantom, math), (typename), (t_Ty), transform2)
{
    o_reflection
    {
        o_typedef(self_type);
        o_typedef(vector2_type);
        o_typedef(angle_type);
        o_typedef(matrix3x3_type);
        o_typedef(matrix2x2_type);

        o_data_member(vector2_type, position, o_no_range, o_public);
        o_data_member(angle_type, orientation, o_no_range, o_public);
        o_data_member(vector2_type, scale, o_no_range, o_public);

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
    };
};
o_classNT((phantom, math), (typename), (t_Ty), axis_angle)
{
    o_reflection
    {
        o_data_member(vector3<t_Ty>, axis, o_no_range, o_public);
        o_data_member(math::angle<t_Ty>, angle, o_no_range, o_public);
    };
};

o_classNT((phantom, math), (typename), (t_Ty), quaternion)
{
    o_reflection
    {
        o_data_member(t_Ty, x, o_no_range);
        o_data_member(t_Ty, y, o_no_range);
        o_data_member(t_Ty, z, o_no_range);
        o_data_member(t_Ty, w, o_no_range);
        o_property(axis_angle<t_Ty>, axisAngle, setAxisAngle, getAxisAngle, o_no_signal, o_no_range, o_public|o_transient);
    };
};
o_traits_specializeNT(has_has_something, (static const bool value = false;), (phantom, math), (typename), (t_Ty), quaternion);

o_classNT((phantom, math), (typename), (t_Ty), transform3)
{
    o_reflection
    {
        o_typedef(self_type);
        o_typedef(vector3_type);
        o_typedef(quaternion_type);
        o_typedef(matrix3x3_type);
        o_typedef(matrix4x4_type);

        o_data_member(vector3_type, position, o_no_range, o_public);
        o_data_member(quaternion_type, orientation, o_no_range, o_public);
        o_data_member(vector3_type, scale, o_no_range, o_public);

        o_member_function(matrix4x4_type, toMatrix, (), o_const);
        o_member_function(void, toMatrix, (matrix4x4_type&), o_const);
        o_member_function(bool, operator==, (const self_type&), o_const);
        o_member_function(bool, operator!=, (const self_type&), o_const);
    };
};

o_classNT((phantom, math), (typename), (t_Ty), aabb2)
{
    o_reflection
    {
        o_typedef(vector2_type);
        o_data_member(vector2_type, min, o_no_range, o_public);
        o_data_member(vector2_type, max, o_no_range, o_public);
    };
};

o_classNT((phantom, math), (typename), (t_Ty), line2)
{
    o_reflection
    {
        o_typedef(vector2_type);
        o_data_member(vector2_type, point, o_no_range, o_public);
        o_data_member(vector2_type, direction, o_no_range, o_public);
    };
};

o_classNT((phantom, math), (typename), (t_Ty), segment2)
{
    o_reflection
    {
        o_typedef(vector2_type);
        o_data_member(vector2_type, start, o_no_range, o_public);
        o_data_member(vector2_type, end, o_no_range, o_public);
    };
};

o_classNT((phantom, math), (typename), (t_Ty), aabb3)
{
    o_reflection
    {
        o_typedef(self_type);
        o_typedef(vector3_type);
        o_data_member(vector3_type, min, o_no_range, o_public);
        o_data_member(vector3_type, max, o_no_range, o_public);
    };
};

o_classNT((phantom, math), (typename), (t_Ty), line3)
{
    o_reflection
    {
        o_typedef(vector3_type);
        o_data_member(vector3_type, point, o_no_range, o_public);
        o_data_member(vector3_type, direction, o_no_range, o_public);
    };
};

o_classNT((phantom, math), (typename), (t_Ty), plane3)
{
    o_reflection
    {
        o_typedef(self_type);
        o_typedef(vector3_type);
        o_data_member(vector3_type, normal, o_no_range, o_public);
        o_data_member(t_Ty, d, o_no_range, o_public);
    };
};

o_classNT((phantom, math), (typename), (t_Ty), rect)
{
    o_reflection
    {
        o_typedef(self_type);
        o_data_member(t_Ty, m_x, o_no_range, o_protected);
        o_data_member(t_Ty, m_y, o_no_range, o_protected);
        o_data_member(t_Ty, m_w, (t_Ty(0), std::numeric_limits<t_Ty>::max()), o_protected);
        o_data_member(t_Ty, m_h, (t_Ty(0), std::numeric_limits<t_Ty>::max()), o_protected);
        o_property(t_Ty, x, setX, getX, o_no_signal, o_no_range, o_protected);
        o_property(t_Ty, y, setY, getY, o_no_signal, o_no_range, o_protected);
        o_property(t_Ty, width, setWidth, getWidth, o_no_signal, (t_Ty(0), std::numeric_limits<t_Ty>::max()), o_protected);
        o_property(t_Ty, height, setHeight, getHeight, o_no_signal, (t_Ty(0), std::numeric_limits<t_Ty>::max()), o_protected);
    };
};
