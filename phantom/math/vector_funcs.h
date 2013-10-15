#ifndef vector_funcs_h__
#define vector_funcs_h__

// THANKS TO BULLET, JUST NEEDED TO TEMPLATIZE ALL OF THE FUNCS

o_namespace_begin(phantom, math)

/**@brief Return the sum of two vectors (Point symantics)*/

template<typename t_Ty> 
o_forceinline vector2<t_Ty> scalarCross(t_Ty scalar, const vector2<t_Ty>& v)
{
    return vector2<t_Ty>(-scalar * v.y, scalar * v.x);
}

/**@brief Return the distance squared between two vectors */
template<typename t_Ty> 
o_forceinline t_Ty
distanceSquared(const vector3<t_Ty>& v1, const vector3<t_Ty>& v2) 
{ 
	return v1.distanceSquared(v2); 
}


/**@brief Return the distance between two vectors */
template<typename t_Ty> 
o_forceinline t_Ty
distance(const vector3<t_Ty>& v1, const vector3<t_Ty>& v2) 
{ 
	return v1.distance(v2); 
}

/**@brief Return the angle between two vectors */
template<typename t_Ty> 
o_forceinline t_Ty
angle(const vector3<t_Ty>& v1, const vector3<t_Ty>& v2) 
{ 
	return v1.angle(v2); 
}

/**@brief Return the cross product of two vectors */
template<typename t_Ty> 
o_forceinline vector3<t_Ty> 
cross(const vector3<t_Ty>& v1, const vector3<t_Ty>& v2) 
{ 
	return v1.cross(v2); 
}

template<typename t_Ty> o_forceinline t_Ty
triple(const vector3<t_Ty>& v1, const vector3<t_Ty>& v2, const vector3<t_Ty>& v3)
{
	return v1.triple(v2, v3);
}

/**@brief Return the linear interpolation between two vectors
 * @param v1 One vector 
 * @param v2 The other vector 
 * @param t The ration of this to v (t = 0 => return v1, t=1 => return v2) */
template<typename t_Ty> o_forceinline vector3<t_Ty> 
lerp(const vector3<t_Ty>& v1, const vector3<t_Ty>& v2, const t_Ty& t)
{
	return v1.lerp(v2, t);
}


/// Multiply a matrix times a vector. If a rotation matrix is provided,
/// then this transforms the vector from one frame to another.
template<typename t_Ty>
o_forceinline vector2<t_Ty> mul(const matrix2x2<t_Ty>& A, const vector2<t_Ty>& v)
{
    return vector2<t_Ty>(A.ex.x * v.x + A.ey.x * v.y, A.ex.y * v.x + A.ey.y * v.y);
}

/// Multiply a matrix transpose times a vector. If a rotation matrix is provided,
/// then this transforms the vector from one frame to another (inverse transform).

template<typename t_Ty>
o_forceinline vector2<t_Ty> mulT(const matrix2x2<t_Ty>& A, const vector2<t_Ty>& v)
{
    return vector2<t_Ty>(v.dot(A.ex), v.dot(A.ey));
}

// A * B
template<typename t_Ty>
o_forceinline matrix2x2<t_Ty> mul(const matrix2x2<t_Ty>& A, const matrix2x2<t_Ty>& B)
{
    return matrix2x2<t_Ty>(mul(A, B.ex), mul(A, B.ey));
}

// A^T * B
template<typename t_Ty>
o_forceinline matrix2x2<t_Ty> mulT(const matrix2x2<t_Ty>& A, const matrix2x2<t_Ty>& B)
{
    vector2<t_Ty> c1((A.ex).dot(B.ex), (A.ey).dot(B.ex));
    vector2<t_Ty> c2((A.ex).dot(B.ey), (A.ey).dot(B.ey));
    return matrix2x2<t_Ty>(c1, c2);
}

/// Multiply a matrix times a vector.
template<typename t_Ty>
o_forceinline vector3<t_Ty> mul(const matrix3x3<t_Ty>& A, const vector3<t_Ty>& v)
{
    return v.x * A.ex + v.y * A.ey + v.z * A.ez;
}

/// Multiply a matrix times a vector.
template<typename t_Ty>
o_forceinline vector2<t_Ty> mul22(const matrix3x3<t_Ty>& A, const vector2<t_Ty>& v)
{
    return vector2<t_Ty>(A.ex.x * v.x + A.ey.x * v.y, A.ex.y * v.x + A.ey.y * v.y);
}

/// Multiply two rotations: orientation * r
template<typename t_Ty>
o_forceinline rotation2D<t_Ty> mul(const rotation2D<t_Ty>& orientation, const rotation2D<t_Ty>& r)
{
    // [qc -qs] * [rc -rs] = [qc*rc-qs*rs -qc*rs-qs*rc]
    // [qs  qc]   [rs  rc]   [qs*rc+qc*rs -qs*rs+qc*rc]
    // s = qs * rc + qc * rs
    // c = qc * rc - qs * rs
    rotation2D<t_Ty> qr;
    qr.s = orientation.s * r.c + orientation.c * r.s;
    qr.c = orientation.c * r.c - orientation.s * r.s;
    return qr;
}

/// Transpose multiply two rotations: qT * r
template<typename t_Ty>
o_forceinline rotation2D<t_Ty> mulT(const rotation2D<t_Ty>& orientation, const rotation2D<t_Ty>& r)
{
    // [ qc qs] * [rc -rs] = [qc*rc+qs*rs -qc*rs+qs*rc]
    // [-qs qc]   [rs  rc]   [-qs*rc+qc*rs qs*rs+qc*rc]
    // s = qc * rs - qs * rc
    // c = qc * rc + qs * rs
    rotation2D<t_Ty> qr;
    qr.s = orientation.c * r.s - orientation.s * r.c;
    qr.c = orientation.c * r.c + orientation.s * r.s;
    return qr;
}

/// Rotate a vector
template<typename t_Ty>
o_forceinline vector2<t_Ty> mul(const rotation2D<t_Ty>& orientation, const vector2<t_Ty>& v)
{
    return vector2<t_Ty>(orientation.c * v.x - orientation.s * v.y, orientation.s * v.x + orientation.c * v.y);
}

/// Inverse rotate a vector
template<typename t_Ty>
o_forceinline vector2<t_Ty> mulT(const rotation2D<t_Ty>& orientation, const vector2<t_Ty>& v)
{
    return vector2<t_Ty>(orientation.c * v.x + orientation.s * v.y, -orientation.s * v.x + orientation.c * v.y);
}

template<typename t_Ty>
o_forceinline vector2<t_Ty> mul(const transform2<t_Ty>& T, const vector2<t_Ty>& v)
{
    t_Ty x = (T.orientation.c * v.x - T.orientation.s * v.y)*T.scale.x + T.position.x;
    t_Ty y = (T.orientation.s * v.x + T.orientation.c * v.y)*T.scale.y + T.position.y;

    return vector2<t_Ty>(x, y);
}

template<typename t_Ty>
o_forceinline vector2<t_Ty> mulNoScale(const transform2<t_Ty>& T, const vector2<t_Ty>& v)
{
    t_Ty x = (T.orientation.c * v.x - T.orientation.s * v.y) + T.position.x;
    t_Ty y = (T.orientation.s * v.x + T.orientation.c * v.y) + T.position.y;

    return vector2<t_Ty>(x, y);
}

template<typename t_Ty>
o_forceinline vector2<t_Ty> mulT(const transform2<t_Ty>& T, const vector2<t_Ty>& v)
{
    // TODO : check if it is the good computation for scale ...
    t_Ty px = v.x - T.position.x;
    t_Ty py = v.y - T.position.y;
    t_Ty x = (T.orientation.c * px + T.orientation.s * py);
    t_Ty y = (-T.orientation.s * px + T.orientation.c * py);

    return vector2<t_Ty>(x/T.scale.x, y/T.scale.y);
}

template<typename t_Ty>
o_forceinline vector2<t_Ty> mulTNoScale(const transform2<t_Ty>& T, const vector2<t_Ty>& v)
{
    t_Ty px = v.x - T.position.x;
    t_Ty py = v.y - T.position.y;
    t_Ty x = (T.orientation.c * px + T.orientation.s * py);
    t_Ty y = (-T.orientation.s * px + T.orientation.c * py);

    return vector2<t_Ty>(x, y);
}

// v2 = A.orientation.rotation2D(B.orientation.rotation2D(v1) + B.position) + A.position
//    = (A.orientation * B.orientation).rotation2D(v1) + A.orientation.rotation2D(B.position) + A.position
template<typename t_Ty>
o_forceinline transform2<t_Ty> mul(const transform2<t_Ty>& local, const transform2<t_Ty>& parent)
{
    transform2<t_Ty> world;
    world.orientation = mul(parent.orientation, local.orientation);
    world.position = local.position;
    world.position.x *= parent.scale.x;
    world.position.y *= parent.scale.y;
    world.position = mul(parent.orientation, world.position) ;
    world.position += parent.position;
    world.scale.set(parent.scale.x*local.scale.x, parent.scale.y*local.scale.y);
    return world;
}

// v2 = A.orientation.rotation2D(B.orientation.rotation2D(v1) + B.position) + A.position
//    = (A.orientation * B.orientation).rotation2D(v1) + A.orientation.rotation2D(B.position) + A.position
template<typename t_Ty>
o_forceinline transform2<t_Ty> mulNoScale(const transform2<t_Ty>& A, const transform2<t_Ty>& B)
{
    transform2<t_Ty> C;
    C.orientation = mul(A.orientation, B.orientation);
    C.position = mul(A.orientation, B.position) + A.position;
    return C;
}

// v2 = A.orientation' * (B.orientation * v1 + B.position - A.position)
//    = A.orientation' * B.orientation * v1 + A.orientation' * (B.position - A.position)
template<typename t_Ty>
o_forceinline transform2<t_Ty> mulT(const transform2<t_Ty>& parent, const transform2<t_Ty>& world)
{
    transform2<t_Ty> local;
    local.orientation = mulT(parent.orientation, world.orientation);
    local.position = world.position - parent.position;
    local.position = mulT(parent.orientation, local.position);
    local.position.x /= parent.scale.x;
    local.position.y /= parent.scale.y;
    local.scale.set(world.scale.x/parent.scale.x, world.scale.y/parent.scale.y);
    return local;
}

// v2 = A.orientation' * (B.orientation * v1 + B.position - A.position)
//    = A.orientation' * B.orientation * v1 + A.orientation' * (B.position - A.position)
template<typename t_Ty>
o_forceinline transform2<t_Ty> mulTNoScale(const transform2<t_Ty>& A, const transform2<t_Ty>& B)
{
    transform2<t_Ty> C;
    C.orientation = mulT(A.orientation, B.orientation);
    C.position = mulT(A.orientation, B.position - A.position);
    return C;
}

// Rot2 Vivien

template<typename t_Ty>
o_forceinline vector2<t_Ty> rotate(const vector2<t_Ty>& vec, t_Ty angle)
{
    t_Ty s = sin(angle);
    t_Ty c = cos(angle);
    return vector2<t_Ty>(vec.x*c - vec.y*s, vec.y*c + vec.x*s);
}

template<typename t_Ty>
o_forceinline vector2<t_Ty> operator * (t_Ty s, const vector2<t_Ty>& a)
{
    return vector2<t_Ty>(s * a.x, s * a.y);
}

template<typename t_Ty>
o_forceinline vector3<t_Ty> operator * (t_Ty s, const vector3<t_Ty>& a)
{
    return vector3<t_Ty>(s * a.x, s * a.y, s * a.z);
}



template <typename t_Ty>
inline vector2<t_Ty> abs(const vector2<t_Ty>& a)
{
    return vector2<t_Ty>(abs(a.x), abs(a.y));
}

template <typename t_Ty>
inline vector3<t_Ty> abs(const vector3<t_Ty>& a)
{
    return vector3<t_Ty>(abs(a.x), abs(a.y), abs(a.z));
}

template <typename t_Ty>
inline matrix2x2<t_Ty> abs(const matrix2x2<t_Ty>& A)
{
    return matrix2x2<t_Ty>(abs(A.ex), abs(A.ey));
}

template <typename t_Ty>
inline vector2<t_Ty> min(const vector2<t_Ty>& a, const vector2<t_Ty>& b)
{
    return vector2<t_Ty>(min(a.x, b.x), min(a.y, b.y));
}

template <typename t_Ty>
inline vector3<t_Ty> min(const vector3<t_Ty>& a, const vector3<t_Ty>& b)
{
    return vector3<t_Ty>(min(a.x, b.x), min(a.y, b.y), min(a.z, b.z));
}

template <typename t_Ty>
inline vector2<t_Ty> max(const vector2<t_Ty>& a, const vector2<t_Ty>& b)
{
    return vector2<t_Ty>(max(a.x, b.x), max(a.y, b.y));
}

template <typename t_Ty>
inline vector3<t_Ty> max(const vector3<t_Ty>& a, const vector3<t_Ty>& b)
{
    return vector3<t_Ty>(max(a.x, b.x), max(a.y, b.y), max(a.z, b.z));
}

template <typename t_Ty>
inline vector2<t_Ty> clamp(const vector2<t_Ty>& a, const vector2<t_Ty>& low, const vector2<t_Ty>& high)
{
    return max(low, min(a, high));
}

template <typename t_Ty>
inline vector3<t_Ty> clamp(const vector3<t_Ty>& a, const vector3<t_Ty>& low, const vector3<t_Ty>& high)
{
    return max(low, min(a, high));
}

o_namespace_end(phantom, math)

#endif // vector_funcs_h__
