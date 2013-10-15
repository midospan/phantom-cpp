#ifndef o_phantom_math_vector_reflection_h__
#define o_phantom_math_vector_reflection_h__

// vector2

o_classNT((phantom, math), (typename), (t_Ty), vector2)
{
    o_reflection
    {
        o_attribute(t_Ty, x, o_public);
        o_attribute(t_Ty, y, o_public);

        o_method(void, set, (t_Ty a_x, t_Ty a_y));
        o_method(void, setZero, ());
        //o_method(self_type const&,  Zero, ());
        o_method(bool, isValid, (), o_const);
        o_method(t_Ty, length, (), o_const);
        o_method(t_Ty, lengthApproximated, (), o_const);
        o_method(t_Ty, lengthSquared, (), o_const);
        o_method(t_Ty, normalize, ());
        o_method(t_Ty, normalizeApproximated, ());
        o_method(self_type, normalized, (), o_const);
        o_method(self_type, normalizedApproximated, (), o_const);
        o_method(t_Ty, distance, (const self_type&), o_const);
        o_method(t_Ty, distanceApproximated, (const self_type&), o_const);
        o_method(t_Ty, distanceSquared, (const self_type&), o_const);
        o_method(self_type, to, (const self_type&), o_const);
        o_method(t_Ty, angle, (const self_type&), o_const);
        o_method(t_Ty,  clampedAngle, (const self_type&), o_const);
	    o_method(self_type, lerp, (const self_type&, const t_Ty&), o_const);
        o_method(bool, isZero, (), o_const );
        o_method(self_type, skewed, (), o_const);
        o_method(self_type, operator+, (self_type const&), o_const);
        o_method(self_type, operator-, (self_type const&), o_const);
        o_method(self_type, operator*, (self_type const&), o_const);
        o_method(self_type, operator/, (self_type const&), o_const);
        o_method(self_type const&, operator+=, (const self_type& v));
        o_method(self_type const&, operator-=, (const self_type&));
        o_method(t_Ty, dot, (self_type const&), o_const);
        o_method(t_Ty, cross, (self_type const&), o_const);
        o_method(self_type, cross, (t_Ty), o_const);
        o_method(self_type, operator+, (t_Ty), o_const);
        o_method(self_type, operator-, (t_Ty), o_const);
        o_method(self_type, operator*, (t_Ty), o_const);
        o_method(self_type, operator/, (t_Ty), o_const);
        o_method(self_type const&, operator*=, (t_Ty));
        o_method(self_type const&, operator/=, (t_Ty));
        o_method(t_Ty&, operator[], (uint));
        o_method(t_Ty const&, operator[], (uint), o_const);
        o_method(self_type, operator-, (), o_const);
        o_method(bool, operator==, (const self_type&), o_const);
        o_method(bool, operator!=, (const self_type&), o_const);
    };
};
o_exposeNT((phantom, math), (typename), (t_Ty), vector2);

// vector3

o_classNT((phantom, math), (typename), (t_Ty), vector3)
{
    o_reflection
    {
        o_attribute(t_Ty[3], a, o_public|o_union_alternative);
        o_attribute(t_Ty, x, o_public|o_transient);
        o_attribute(t_Ty, y, o_public|o_transient);
        o_attribute(t_Ty, z, o_public|o_transient);
        o_attribute(t_Ty, r, o_public|o_transient|o_union_alternative);
        o_attribute(t_Ty, g, o_public|o_transient|o_union_alternative);
        o_attribute(t_Ty, b, o_public|o_transient|o_union_alternative);
    };
};
o_exposeNT((phantom, math), (typename), (t_Ty), vector3);

// vector4

o_classNT((phantom, math), (typename), (t_Ty), vector4)
{
	o_reflection
	{
		o_attribute(t_Ty[4], a, o_public|o_union_alternative);
		o_attribute(t_Ty, x, o_public|o_transient);
		o_attribute(t_Ty, y, o_public|o_transient);
		o_attribute(t_Ty, z, o_public|o_transient);
		o_attribute(t_Ty, w, o_public|o_transient);
	};
};
o_exposeNT((phantom, math), (typename), (t_Ty), vector4);

// matrix2x2

o_classNT((phantom, math), (typename), (t_Ty), matrix2x2)
{
    o_reflection
    {
        o_attribute(t_Ty[4], a, o_public|o_union_alternative);
        o_attribute(t_Ty[2][2], m, o_public|o_union_alternative|o_transient);
        o_attribute(vector2_type, ex, o_public|o_transient);
        o_attribute(vector2_type, ey, o_public|o_transient);
    };
};
o_exposeNT((phantom, math), (typename), (t_Ty), matrix2x2);

// matrix3x3

o_classNT((phantom, math), (typename), (t_Ty), matrix3x3)
{
    o_reflection
    {
        o_attribute(t_Ty[9], a, o_public|o_union_alternative);
        o_attribute(t_Ty[3][3], m, o_public|o_union_alternative|o_transient);
        o_attribute(vector3_type, ex, o_public|o_transient);
        o_attribute(vector3_type, ey, o_public|o_transient);
        o_attribute(vector3_type, ez, o_public|o_transient);
    };
};
o_exposeNT((phantom, math), (typename), (t_Ty), matrix3x3);


// rotation2D


o_classNT((phantom, math), (typename), (t_Ty), rotation2D)
{
    o_reflection
    {
        o_accessor(t_Ty, angle, setAngle, getAngle, o_public);
        o_method(bool, operator==, (const self_type&), o_const);
        o_method(bool, operator!=, (const self_type&), o_const);
    };
};
o_exposeNT((phantom, math), (typename), (t_Ty), rotation2D);


// transform2


o_classNT((phantom, math), (typename), (t_Ty), transform2)
{
    o_reflection
    {
        o_attribute(vector2_type, position, o_public);
        o_attribute(rotation2D_type, orientation, o_public);
        o_attribute(vector2_type, scale, o_public);

        o_method(void, setIdentity, ());
        o_method(void, set, (const vector2_type&, t_Ty, const vector2_type&));
        o_method(void, set, (const vector2_type&, t_Ty));
        o_method(matrix3x3_type, getMatrix3x3, (), o_const);
        o_method(matrix3x3_type, getMatrix3x3WithoutScale, (), o_const);
        o_method(void, getMatrix3x3WithoutScale, (matrix3x3_type&), o_const);
        o_method(void, getMatrix3x3, (matrix3x3_type&), o_const);
        o_method(matrix2x2_type, getRotationMatrix2x2, (), o_const);
        o_method(void, getRotationMatrix2x2, (matrix2x2_type&), o_const);
        o_method(bool, operator==, (const self_type&), o_const);
        o_method(bool, operator!=, (const self_type&), o_const);
    };
};
o_exposeNT((phantom, math), (typename), (t_Ty), transform2);




#endif // o_phantom_math_reflection_h__
