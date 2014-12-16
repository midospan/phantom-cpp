
	template<class t_Ty>
inline quaternion<t_Ty>::quaternion ()
{
	// Uninitialized for performance in array construction.
}


	template<class t_Ty>
inline quaternion<t_Ty>::quaternion (t_Ty w, t_Ty x, t_Ty y, t_Ty z)
{
	m[0] = w;
	m[1] = x;
	m[2] = y;
	m[3] = z;
}


	template<class t_Ty>
inline quaternion<t_Ty>::quaternion (const quaternion<t_Ty>& q)
{
	m[0] = q.m[0];
	m[1] = q.m[1];
	m[2] = q.m[2];
	m[3] = q.m[3];
}


	template<class t_Ty>
inline quaternion<t_Ty>::quaternion (const matrix3x3<t_Ty>& rot)
{
	fromRotationmatrix(rot);
}


	template<class t_Ty>
inline quaternion<t_Ty>::quaternion (const vector3<t_Ty>& axis, t_Ty angle)
{
	fromAxisAngle(axis, angle);
}

template<class t_Ty>
quaternion<t_Ty>::quaternion( const axis_angle<t_Ty>& axis_angle )
{
    fromAxisAngle(axis_angle.axis, axis_angle.angle.getRadian());
}

template<class t_Ty>
inline quaternion<t_Ty>::quaternion (const vector3<t_Ty> rotColumn[3])
{
	fromRotationmatrix(rotColumn);
}


template<class t_Ty>
inline quaternion<t_Ty>::operator const t_Ty* () const
{
	return m;
}


	template<class t_Ty>
inline quaternion<t_Ty>::operator t_Ty* ()
{
	return m;
}


template<class t_Ty>
inline const t_Ty& quaternion<t_Ty>::operator[] (int i) const
{
	return m[i];
}


	template<class t_Ty>
inline t_Ty& quaternion<t_Ty>::operator[] (int i)
{
	return m[i];
}


	template<class t_Ty>
inline quaternion<t_Ty>& quaternion<t_Ty>::operator= (const quaternion<t_Ty>& q)
{
	m[0] = q.m[0];
	m[1] = q.m[1];
	m[2] = q.m[2];
	m[3] = q.m[3];
	return *this;
}


template<class t_Ty>
inline bool quaternion<t_Ty>::operator== (const quaternion<t_Ty>& q) const
{
	return memcmp(m, q.m, 4*sizeof(t_Ty)) == 0;
}


template<class t_Ty>
inline bool quaternion<t_Ty>::operator!= (const quaternion<t_Ty>& q) const
{
	return memcmp(m, q.m, 4*sizeof(t_Ty)) != 0;
}


template<class t_Ty>
inline bool quaternion<t_Ty>::operator< (const quaternion<t_Ty>& q) const
{
	return memcmp(m, q.m, 4*sizeof(t_Ty)) < 0;
}


template<class t_Ty>
inline bool quaternion<t_Ty>::operator<= (const quaternion<t_Ty>& q) const
{
	return memcmp(m, q.m, 4*sizeof(t_Ty)) <= 0;
}


template<class t_Ty>
inline bool quaternion<t_Ty>::operator> (const quaternion<t_Ty>& q) const
{
	return memcmp(m, q.m, 4*sizeof(t_Ty)) > 0;
}


template<class t_Ty>
inline bool quaternion<t_Ty>::operator>= (const quaternion<t_Ty>& q) const
{
	return memcmp(m, q.m, 4*sizeof(t_Ty)) >= 0;
}


	template<class t_Ty>
inline quaternion<t_Ty> quaternion<t_Ty>::operator+ (const quaternion<t_Ty>& q)
	const
{
	quaternion<t_Ty> result;
	for (int i = 0; i < 4; ++i)
	{
		result.m[i] = m[i] + q.m[i];
	}
	return result;
}


	template<class t_Ty>
inline quaternion<t_Ty> quaternion<t_Ty>::operator- (const quaternion<t_Ty>& q)
	const
{
	quaternion<t_Ty> result;
	for (int i = 0; i < 4; ++i)
	{
		result.m[i] = m[i] - q.m[i];
	}
	return result;
}


	template<class t_Ty>
inline quaternion<t_Ty> quaternion<t_Ty>::operator* (const quaternion<t_Ty>& q)
	const
{
	// NOTE:  Multiplication is not generally commutative, so in most
	// cases p*q != q*p.

	quaternion<t_Ty> result;

	result.m[0] =
		m[0]*q.m[0] -
		m[1]*q.m[1] -
		m[2]*q.m[2] -
		m[3]*q.m[3];

	result.m[1] =
		m[0]*q.m[1] +
		m[1]*q.m[0] +
		m[2]*q.m[3] -
		m[3]*q.m[2];

	result.m[2] =
		m[0]*q.m[2] +
		m[2]*q.m[0] +
		m[3]*q.m[1] -
		m[1]*q.m[3];

	result.m[3] =
		m[0]*q.m[3] +
		m[3]*q.m[0] +
		m[1]*q.m[2] -
		m[2]*q.m[1];

	return result;
}


template<class t_Ty>
inline quaternion<t_Ty> quaternion<t_Ty>::operator* (t_Ty scalar) const
{
	quaternion<t_Ty> result;
	for (int i = 0; i < 4; ++i)
	{
		result.m[i] = scalar*m[i];
	}
	return result;
}


template<class t_Ty>
inline quaternion<t_Ty> quaternion<t_Ty>::operator/ (t_Ty scalar) const
{
	quaternion<t_Ty> result;
	int i;

	if (scalar != (t_Ty)0)
	{
		t_Ty invScalar = ((t_Ty)1)/scalar;
		for (i = 0; i < 4; ++i)
		{
			result.m[i] = invScalar*m[i];
		}
	}
	else
    {
        t_Ty max = std::numeric_limits<t_Ty>::max();
		for (i = 0; i < 4; ++i)
		{
			result.m[i] = max;
		}
	}

	return result;
}


template<class t_Ty>
inline quaternion<t_Ty> quaternion<t_Ty>::operator- () const
{
	quaternion<t_Ty> result;
	for (int i = 0; i < 4; ++i)
	{
		result.m[i] = -m[i];
	}
	return result;
}


	template<class t_Ty>
inline quaternion<t_Ty>& quaternion<t_Ty>::operator+= (const quaternion<t_Ty>& q)
{
	for (int i = 0; i < 4; ++i)
	{
		m[i] += q.m[i];
	}
	return *this;
}


	template<class t_Ty>
inline quaternion<t_Ty>& quaternion<t_Ty>::operator-= (const quaternion<t_Ty>& q)
{
	for (int i = 0; i < 4; ++i)
	{
		m[i] -= q.m[i];
	}
	return *this;
}


	template<class t_Ty>
inline quaternion<t_Ty>& quaternion<t_Ty>::operator*= (t_Ty scalar)
{
	for (int i = 0; i < 4; ++i)
	{
		m[i] *= scalar;
	}
	return *this;
}


	template<class t_Ty>
inline quaternion<t_Ty>& quaternion<t_Ty>::operator/= (t_Ty scalar)
{
	int i;

	if (scalar != (t_Ty)0)
	{
		t_Ty invScalar = ((t_Ty)1)/scalar;
		for (i = 0; i < 4; ++i)
		{
			m[i] *= invScalar;
		}
	}
	else
    {
        t_Ty max = std::numeric_limits<t_Ty>::max();
		for (i = 0; i < 4; ++i)
		{
			m[i] = max;
		}
	}

	return *this;
}


	template<class t_Ty>
inline void quaternion<t_Ty>::fromRotationmatrix (const matrix3x3<t_Ty>& rot)
{
	// Algorithm in Ken Shoemake's article in 1987 SIGGRAPH course notes
	// article "quaternion<t_Ty> Calculus and Fast Animation".

	const int next[3] = { 1, 2, 0 };

	t_Ty trace = rot(0,0) + rot(1,1) + rot(2,2);
	t_Ty root;

	if (trace > (t_Ty)0)
	{
		// |w| > 1/2, may as well choose w > 1/2
		root = sqrt(trace + (t_Ty)1);  // 2w
		m[0] = ((t_Ty)0.5)*root;
		root = ((t_Ty)0.5)/root;  // 1/(4w)
		m[1] = (rot(1,2) - rot(2,1))*root;
		m[2] = (rot(2,0) - rot(0,2))*root;
		m[3] = (rot(0,1) - rot(1,0))*root;
	}
	else
	{
		// |w| <= 1/2
		int i = 0;
		if (rot(1,1) > rot(0,0))
		{
			i = 1;
		}
		if (rot(2,2) > rot(i,i))
		{
			i = 2;
		}
		int j = next[i];
		int k = next[j];

		root = sqrt(rot(i,i) - rot(j,j) - rot(k,k) + (t_Ty)1);
		t_Ty* quat[3] = { &m[1], &m[2], &m[3] };
		*quat[i] = ((t_Ty)0.5)*root;
		root = ((t_Ty)0.5)/root;
		m[0] = (rot(j,k) - rot(k,j))*root;
		*quat[j] = (rot(i,j) + rot(j,i))*root;
		*quat[k] = (rot(i,k) + rot(k,i))*root;
	}
}


template<class t_Ty>
inline void quaternion<t_Ty>::toRotationmatrix (matrix3x3<t_Ty>& rot) const
{
	t_Ty twoX  = ((t_Ty)2)*m[1];
	t_Ty twoY  = ((t_Ty)2)*m[2];
	t_Ty twoZ  = ((t_Ty)2)*m[3];
	t_Ty twoWX = twoX*m[0];
	t_Ty twoWY = twoY*m[0];
	t_Ty twoWZ = twoZ*m[0];
	t_Ty twoXX = twoX*m[1];
	t_Ty twoXY = twoY*m[1];
	t_Ty twoXZ = twoZ*m[1];
	t_Ty twoYY = twoY*m[2];
	t_Ty twoYZ = twoZ*m[2];
	t_Ty twoZZ = twoZ*m[3];

	rot(0,0) = (t_Ty)1 - (twoYY + twoZZ);
	rot(1,0) = twoXY - twoWZ;
	rot(2,0) = twoXZ + twoWY;
	rot(0,1) = twoXY + twoWZ;
	rot(1,1) = (t_Ty)1 - (twoXX + twoZZ);
	rot(2,1) = twoYZ - twoWX;
	rot(0,2) = twoXZ - twoWY;
	rot(1,2) = twoYZ + twoWX;
	rot(2,2) = (t_Ty)1 - (twoXX + twoYY);
}


	template<class t_Ty>
inline void quaternion<t_Ty>::fromRotationmatrix (const vector3<t_Ty> rotColumn[3])
{
	matrix3x3<t_Ty> kRot;
	for (int col = 0; col < 3; ++col)
	{
		kRot(col,0) = rotColumn[col][0];
		kRot(col,1) = rotColumn[col][1];
		kRot(col,2) = rotColumn[col][2];
	}
	fromRotationmatrix(kRot);
}


template<class t_Ty>
inline void quaternion<t_Ty>::toRotationmatrix (vector3<t_Ty> rotColumn[3]) const
{
	matrix3x3<t_Ty> rot;
	toRotationmatrix(rot);
	for (int col = 0; col < 3; ++col)
	{
		rotColumn[col][0] = rot(col,0);
		rotColumn[col][1] = rot(col,1);
		rotColumn[col][2] = rot(col,2);
	}
}


	template<class t_Ty>
inline void quaternion<t_Ty>::fromAxisAngle (const vector3<t_Ty>& axis, t_Ty angle)
{
	// assert:  axis[] is unit length
	//
	// The quaternion representing the rotation is
	//   q = cos(A/2)+sin(A/2)*(x*i+y*j+z*k)

	t_Ty halfAngle = ((t_Ty)0.5)*angle;
	t_Ty sn = math::sin(halfAngle);
	m[0] = math::cos(halfAngle);
	m[1] = sn*axis[0];
	m[2] = sn*axis[1];
	m[3] = sn*axis[2];
}


template<class t_Ty>
inline void quaternion<t_Ty>::toAxisAngle (vector3<t_Ty>& axis, t_Ty& angle) const
{
	// The quaternion representing the rotation is
	//   q = cos(A/2)+sin(A/2)*(x*i+y*j+z*k)

	t_Ty sqrLength = m[1]*m[1] + m[2]*m[2]
		+ m[3]*m[3];

	if (sqrLength > epsilon<t_Ty>())
	{
		angle = ((t_Ty)2)*math::acos(m[0]);
		t_Ty invLength = invSqrt(sqrLength);
		axis[0] = m[1]*invLength;
		axis[1] = m[2]*invLength;
		axis[2] = m[3]*invLength;
	}
	else
	{
		// Angle is 0 (mod 2*pi), so any axis will do.
		angle = (t_Ty)0;
		axis[0] = (t_Ty)1;
		axis[1] = (t_Ty)0;
		axis[2] = (t_Ty)0;
	}
}


template<class t_Ty>
inline t_Ty quaternion<t_Ty>::length () const
{
	return sqrt(m[0]*m[0] + m[1]*m[1] +
			m[2]*m[2] + m[3]*m[3]);
}


template<class t_Ty>
inline t_Ty quaternion<t_Ty>::lengthSquared () const
{
	return m[0]*m[0] + m[1]*m[1] +
		m[2]*m[2] + m[3]*m[3];
}


template<class t_Ty>
inline t_Ty quaternion<t_Ty>::dot (const quaternion<t_Ty>& q) const
{
	return m[0]*q.m[0] + m[1]*q.m[1] +
		m[2]*q.m[2] + m[3]*q.m[3];
}


	template<class t_Ty>
inline t_Ty quaternion<t_Ty>::normalize (t_Ty epsilon)
{
	t_Ty len = length();

	if (len > epsilon)
	{
		t_Ty invLength = ((t_Ty)1)/len;
		m[0] *= invLength;
		m[1] *= invLength;
		m[2] *= invLength;
		m[3] *= invLength;
	}
	else
	{
		len = (t_Ty)0;
		m[0] = (t_Ty)0;
		m[1] = (t_Ty)0;
		m[2] = (t_Ty)0;
		m[3] = (t_Ty)0;
	}

	return len;
}


template<class t_Ty>
inline quaternion<t_Ty> quaternion<t_Ty>::inverse () const
{
	quaternion<t_Ty> inverse;

	t_Ty norm = lengthSquared();
	if (norm > (t_Ty)0)
	{
		t_Ty invNorm = ((t_Ty)1)/norm;
		inverse.m[0] = m[0]*invNorm;
		inverse.m[1] = -m[1]*invNorm;
		inverse.m[2] = -m[2]*invNorm;
		inverse.m[3] = -m[3]*invNorm;
	}
	else
	{
		// Return an invalid result to flag the error.
		for (int i = 0; i < 4; ++i)
		{
			inverse.m[i] = (t_Ty)0;
		}
	}

	return inverse;
}


template<class t_Ty>
inline quaternion<t_Ty> quaternion<t_Ty>::conjugate () const
{
	return quaternion(m[0], -m[1], -m[2], -m[3]);
}


template<class t_Ty>
inline quaternion<t_Ty> quaternion<t_Ty>::exp () const
{
	// If q = A*(x*i+y*j+z*k) where (x,y,z) is unit length, then
	// exp(q) = cos(A)+sin(A)*(x*i+y*j+z*k).  If sin(A) is near zero,
	// use exp(q) = cos(A)+A*(x*i+y*j+z*k) since A/sin(A) has limit 1.

	quaternion<t_Ty> result;

	t_Ty angle = sqrt(m[1]*m[1] +
			m[2]*m[2] + m[3]*m[3]);

	t_Ty sn = math::sin(angle);
	result.m[0] = math::cos(angle);

	int i;

	if (fabs(sn) >= phantom::math::epsilon<t_Ty>())
	{
		t_Ty coeff = sn/angle;
		for (i = 1; i < 4; ++i)
		{
			result.m[i] = coeff*m[i];
		}
	}
	else
	{
		for (i = 1; i < 4; ++i)
		{
			result.m[i] = m[i];
		}
	}

	return result;
}


template<class t_Ty>
inline quaternion<t_Ty> quaternion<t_Ty>::log () const
{
	// If q = cos(A)+sin(A)*(x*i+y*j+z*k) where (x,y,z) is unit length, then
	// log(q) = A*(x*i+y*j+z*k).  If sin(A) is near zero, use log(q) =
	// sin(A)*(x*i+y*j+z*k) since sin(A)/A has limit 1.

	quaternion<t_Ty> result;
	result.m[0] = (t_Ty)0;

	int i;

	if (fabs(m[0]) < (t_Ty)1)
	{
		t_Ty angle = math::acos(m[0]);
		t_Ty sn = math::sin(angle);
		if (fabs(sn) >= phantom::math::epsilon<t_Ty>())
		{
			t_Ty coeff = angle/sn;
			for (i = 1; i < 4; ++i)
			{
				result.m[i] = coeff*m[i];
			}
			return result;
		}
	}

	for (i = 1; i < 4; ++i)
	{
		result.m[i] = m[i];
	}
	return result;
}


template<class t_Ty>
inline vector3<t_Ty> quaternion<t_Ty>::rotate (const vector3<t_Ty>& vec) const
{
	// Given a vector u = (x0,y0,z0) and a unit length quaternion
	// q = <w,x,y,z>, the vector v = (x1,y1,z1) which represents the
	// rotation of u by q is v = q*u*q^{-1} where * indicates quaternion
	// multiplication and where u is treated as the quaternion <0,x0,y0,z0>.
	// Note that q^{-1} = <w,-x,-y,-z>, so no real work is required to
	// invert q.  Now
	//
	//   q*u*q^{-1} = q*<0,x0,y0,z0>*q^{-1}
	//     = q*(x0*i+y0*j+z0*k)*q^{-1}
	//     = x0*(q*i*q^{-1})+y0*(q*j*q^{-1})+z0*(q*k*q^{-1})
	//
	// As 3-vectors, q*i*q^{-1}, q*j*q^{-1}, and 2*k*q^{-1} are the columns
	// of the rotation matrix computed in quaternion<t_Ty>::toRotationmatrix.
	// The vector v is obtained as the product of that rotation matrix with
	// vector u.  As such, the quaternion representation of a rotation
	// matrix requires less space than the matrix and more time to compute
	// the rotated vector.  Typical space-time tradeoff...

	matrix3x3<t_Ty> rot;
	toRotationmatrix(rot);
	return rot*vec;
}


	template<class t_Ty>
inline quaternion<t_Ty>& quaternion<t_Ty>::slerp (t_Ty t, const quaternion<t_Ty>& p,
		const quaternion<t_Ty>& q)
{
	t_Ty cs = p.dot(q);
	t_Ty angle = -math::acos(cs);

	if (fabs(angle) >= phantom::math::epsilon<t_Ty>())
	{
		t_Ty sn = math::sin(angle);
		t_Ty invSn = ((t_Ty)1)/sn;
		t_Ty tAngle = t*angle;
		t_Ty coeff0 = math::sin(angle - tAngle)*invSn;
		t_Ty coeff1 = math::sin(tAngle)*invSn;

		m[0] = coeff0*p.m[0] + coeff1*q.m[0];
		m[1] = coeff0*p.m[1] + coeff1*q.m[1];
		m[2] = coeff0*p.m[2] + coeff1*q.m[2];
		m[3] = coeff0*p.m[3] + coeff1*q.m[3];
	}
	else
	{
		m[0] = p.m[0];
		m[1] = p.m[1];
		m[2] = p.m[2];
		m[3] = p.m[3];
	}

	return *this;
}


	template<class t_Ty>
inline quaternion<t_Ty>& quaternion<t_Ty>::slerpExtraSpins (t_Ty t,
		const quaternion<t_Ty>& p, const quaternion<t_Ty>& q, int extraSpins)
{
	t_Ty cs = p.dot(q);
	t_Ty angle = math::acos(cs);

	if (fabs(angle) >= phantom::math::epsilon<t_Ty>())
	{
		t_Ty sn = math::sin(angle);
		t_Ty phase = o_math_Pi*extraSpins*t;
		t_Ty invSin = ((t_Ty)1)/sn;
		t_Ty coeff0 = math::sin(((t_Ty)1 - t)*angle - phase)*invSin;
		t_Ty coeff1 = math::sin(t*angle + phase)*invSin;

		m[0] = coeff0*p.m[0] + coeff1*q.m[0];
		m[1] = coeff0*p.m[1] + coeff1*q.m[1];
		m[2] = coeff0*p.m[2] + coeff1*q.m[2];
		m[3] = coeff0*p.m[3] + coeff1*q.m[3];
	}
	else
	{
		m[0] = p.m[0];
		m[1] = p.m[1];
		m[2] = p.m[2];
		m[3] = p.m[3];
	}

	return *this;
}


	template<class t_Ty>
inline quaternion<t_Ty>& quaternion<t_Ty>::intermediate (const quaternion<t_Ty>& q0,
		const quaternion<t_Ty>& q1, const quaternion<t_Ty>& q2)
{
	// assert:  Q0, Q1, Q2 all unit-length
	quaternion<t_Ty> q1Inv = q1.conjugate();
	quaternion<t_Ty> p0 = q1Inv*q0;
	quaternion<t_Ty> p2 = q1Inv*q2;
	quaternion<t_Ty> arg = -((t_Ty)0.25)*(p0.log() + p2.log());
	quaternion<t_Ty> a = q1*arg.exp();
	*this = a;
	return *this;
}


	template<class t_Ty>
inline quaternion<t_Ty>& quaternion<t_Ty>::squad (t_Ty t, const quaternion<t_Ty>& q0,
		const quaternion<t_Ty>& a0, const quaternion<t_Ty>& a1, const quaternion<t_Ty>& q1)
{
	t_Ty slerpT = ((t_Ty)2)*t*((t_Ty)1 - t);
	quaternion<t_Ty> slerpP = slerp(t, q0, q1);
	quaternion<t_Ty> slerpQ = slerp(t, a0, a1);
	return slerp(slerpT, slerpP, slerpQ);
}


	template<class t_Ty>
inline quaternion<t_Ty>& quaternion<t_Ty>::align (const vector3<t_Ty>& v1,
		const vector3<t_Ty>& v2)
{
	// If V1 and V2 are not parallel, the axis of rotation is the unit-length
	// vector U = cross(V1,V2)/length(cross(V1,V2)).  The angle of rotation,
	// A, is the angle between V1 and V2.  The quaternion for the rotation is
	// q = cos(A/2) + sin(A/2)*(ux*i+uy*j+uz*k) where U = (ux,uy,uz).
	//
	// (1) Rather than extract A = acos(dot(V1,V2)), multiply by 1/2, then
	//     compute sin(A/2) and cos(A/2), we reduce the computational costs by
	//     computing the bisector B = (V1+V2)/length(V1+V2), so cos(A/2) =
	//     dot(V1,B).
	//
	// (2) The rotation axis is U = cross(V1,B)/length(cross(V1,B)), but
	//     length(cross(V1,B)) = length(V1)*length(B)*sin(A/2) = sin(A/2), in
	//     which case sin(A/2)*(ux*i+uy*j+uz*k) = (cx*i+cy*j+cz*k) where
	//     C = cross(V1,B).
	//
	// If V1 = V2, then B = V1, cos(A/2) = 1, and U = (0,0,0).  If V1 = -V2,
	// then B = 0.  This can happen even if V1 is approximately -V2 using
	// Ting point arithmetic, since vector3<t_Ty>::normalize checks for
	// closeness to zero and returns the zero vector accordingly.  The test
	// for exactly zero is usually not recommend for Ting point
	// arithmetic, but the implementation of vector3<t_Ty>::normalize guarantees
	// the comparison is robust.  In this case, the A = pi and any axis
	// perpendicular to V1 may be used as the rotation axis.

	vector3<t_Ty> bisector = v1 + v2;
	bisector.normalize();

	t_Ty cosHalfAngle = v1.dot(bisector);
	vector3<t_Ty> cross;

	m[0] = cosHalfAngle;

	if (cosHalfAngle != (t_Ty)0)
	{
		cross = v1.cross(bisector);
		m[1] = cross.x;
		m[2] = cross.y;
		m[3] = cross.z;
	}
	else
	{
		t_Ty invLength;
		if (fabs(v1[0]) >= fabs(v1[1]))
		{
			// V1.x or V1.z is the largest magnitude component.
			invLength = invSqrt(v1[0]*v1[0] + v1[2]*v1[2]);
			m[1] = -v1[2]*invLength;
			m[2] = (t_Ty)0;
			m[3] = +v1[0]*invLength;
		}
		else
		{
			// V1.y or V1.z is the largest magnitude component.
			invLength = invSqrt(v1[1]*v1[1] + v1[2]*v1[2]);
			m[1] = (t_Ty)0;
			m[2] = +v1[2]*invLength;
			m[3] = -v1[1]*invLength;
		}
	}

	return *this;
}


	template<class t_Ty>
inline void quaternion<t_Ty>::decomposeTwistTimesSwing (const vector3<t_Ty>& v1,
		quaternion<t_Ty>& twist, quaternion<t_Ty>& swing)
{
	vector3<t_Ty> v2 = rotate(v1);
	swing = align(v1, v2);
	twist = (*this)*swing.conjugate();
}


	template<class t_Ty>
inline void quaternion<t_Ty>::decomposeSwingTimesTwist (const vector3<t_Ty>& v1,
		quaternion<t_Ty>& swing, quaternion<t_Ty>& twist)
{
	vector3<t_Ty> v2 = rotate(v1);
	swing = align(v1, v2);
	twist = swing.conjugate()*(*this);
}


template<class t_Ty>
inline quaternion<t_Ty> quaternion<t_Ty>::closestX () const
{
	return closest(1);
}


template<class t_Ty>
inline quaternion<t_Ty> quaternion<t_Ty>::closestY () const
{
	return closest(2);
}


template<class t_Ty>
inline quaternion<t_Ty> quaternion<t_Ty>::closestZ () const
{
	return closest(3);
}


template<class t_Ty>
inline quaternion<t_Ty> quaternion<t_Ty>::closestXY () const
{
	quaternion<t_Ty> q;

	t_Ty det = m[0]*m[3] - m[1]*m[2];
	if(fabs(det) < (t_Ty)0.5 - epsilon<t_Ty>())
	{
		t_Ty discr = (t_Ty)1 - ((t_Ty)4)*det*det;
		discr = sqrt(fabs(discr));
		t_Ty a = m[0]*m[1] + m[2]*m[3];
		t_Ty b = m[0]*m[0] - m[1]*m[1] +
			m[2]*m[2] - m[3]*m[3];

		t_Ty c0, s0, c1, s1, invLength;

		if (b >= (t_Ty)0)
		{
			c0 = ((t_Ty)0.5)*(discr + b);
			s0 = a;
		}
		else
		{
			c0 = a;
			s0 = ((t_Ty)0.5)*(discr - b);
		}
		invLength = invSqrt(c0*c0 + s0*s0);
		c0 *= invLength;
		s0 *= invLength;

		c1 = m[0]*c0 + m[1]*s0;
		s1 = m[2]*c0 + m[3]*s0;
		invLength = invSqrt(c1*c1 + s1*s1);
		c1 *= invLength;
		s1 *= invLength;

		q[0] = c0*c1;
		q[1] = s0*c1;
		q[2] = c0*s1;
		q[3] = s0*s1;
	}
	else
	{
		t_Ty invLength = invSqrt(fabs(det));
		q[0] = m[0]*invLength;
		q[1] = m[1]*invLength;
		q[2] = (t_Ty)0;
		q[3] = (t_Ty)0;
	}

	return q;
}


template<class t_Ty>
inline quaternion<t_Ty> quaternion<t_Ty>::closestYX () const
{
	quaternion<t_Ty> alt(m[0], m[1], m[2], -m[3]);
	quaternion<t_Ty> q = alt.closestXY();
	q[3] = -q[3];
	return q;
}


template<class t_Ty>
inline quaternion<t_Ty> quaternion<t_Ty>::closestZX () const
{
	quaternion<t_Ty> alt(m[0], m[1], m[3], m[2]);
	quaternion<t_Ty> q = alt.closestXY();
	t_Ty save = q[2];
	q[2] = q[3];
	q[3] = save;
	return q;
}


template<class t_Ty>
inline quaternion<t_Ty> quaternion<t_Ty>::closestXZ () const
{
	quaternion<t_Ty> alt(m[0], m[1], -m[3], m[2]);
	quaternion<t_Ty> q = alt.closestXY();
	t_Ty save = q[2];
	q[2] = q[3];
	q[3] = -save;
	return q;
}


template<class t_Ty>
inline quaternion<t_Ty> quaternion<t_Ty>::closestYZ () const
{
	quaternion<t_Ty> alt(m[0], m[2], m[3], m[1]);
	quaternion<t_Ty> q = alt.closestXY();
	t_Ty save = q[3];
	q[3] = q[2];
	q[2] = q[1];
	q[1] = save;
	return q;
}


template<class t_Ty>
inline quaternion<t_Ty> quaternion<t_Ty>::closestZY () const
{
	quaternion<t_Ty> alt(m[0], m[2], m[3], -m[1]);
	quaternion<t_Ty> q = alt.closestXY();
	t_Ty save = q[3];
	q[3] = q[2];
	q[2] = q[1];
	q[1] = -save;
	return q;
}


	template<class t_Ty>
inline void quaternion<t_Ty>::factorXYZ (t_Ty& cx, t_Ty& sx, t_Ty& cy,
		t_Ty& sy, t_Ty& cz, t_Ty& sz)
{
	t_Ty a = m[0]*m[1] - m[2]*m[3];
	t_Ty b = ((t_Ty)0.5)*(
			m[0]*m[0]
			- m[1]*m[1]
			- m[2]*m[2]
			+ m[3]*m[3]);

	t_Ty fLength = sqrt(a*a + b*b);
	if (fLength > epsilon<t_Ty>())
	{
		t_Ty invLength = ((t_Ty)1)/fLength;
		t_Ty sigma0 = a * invLength;
		t_Ty gamma0 = b * invLength;
		if (gamma0 >= (t_Ty)0)
		{
			cx = sqrt(((t_Ty)0.5)*((t_Ty)1 + gamma0));
			sx = ((t_Ty)0.5)*sigma0/cx;
		}
		else
		{
			sx = sqrt(((t_Ty)0.5)*((t_Ty)1 - gamma0));
			cx = ((t_Ty)0.5)*sigma0/sx;
		}

		t_Ty tmp0 = cx*m[0] + sx*m[1];
		t_Ty tmp1 = cx*m[3] - sx*m[2];
		invLength = invSqrt(tmp0*tmp0 + tmp1*tmp1);
		cz = tmp0 * invLength;
		sz = tmp1 * invLength;

		if(fabs(cz) >= fabs(sz))
		{
			invLength = ((t_Ty)1)/cz;
			cy = tmp0 * invLength;
			sy = (cx*m[2] + sx*m[3]) * invLength;
		}
		else
		{
			invLength = ((t_Ty)1)/sz;
			cy = tmp1 * invLength;
			sy = (cx*m[1] - sx*m[0]) * invLength;
		}
	}
	else
	{
		// Infinitely many solutions.  Choose one of them.
		if(m[0]*m[2] + m[1]*m[3] > (t_Ty)0)
		{
			// p = (p0,p1,p0,p1)
			cx = (t_Ty)1;
			sx = (t_Ty)0;
			cy = o_math_inv_Sqrt_2;
			sy = o_math_inv_Sqrt_2;
			cz = o_math_Sqrt_2 * m[0];
			sz = o_math_Sqrt_2 * m[1];
		}
		else
		{
			// p = (p0,p1,-p0,-p1)
			cx = (t_Ty)1;
			sx = (t_Ty)0;
			cy = o_math_inv_Sqrt_2;
			sy = -o_math_inv_Sqrt_2;
			cz = o_math_Sqrt_2 * m[0];
			sz = -o_math_Sqrt_2 * m[1];
		}
	}
}


	template<class t_Ty>
inline void quaternion<t_Ty>::factorXZY (t_Ty& cx, t_Ty& sx, t_Ty& cz,
		t_Ty& sz, t_Ty& cy, t_Ty& sy)
{
	quaternion<t_Ty> alt(m[0], m[1], m[3], -m[2]);
	alt.factorXYZ(cx, sx, cz, sz, cy, sy);
	sy = -sy;
}


	template<class t_Ty>
inline void quaternion<t_Ty>::factorYZX (t_Ty& cy, t_Ty& sy, t_Ty& cz,
		t_Ty& sz, t_Ty& cx, t_Ty& sx)
{
	quaternion<t_Ty> alt(m[0], -m[2], m[3], -m[1]);
	alt.factorXYZ(cy, sy, cz, sz, cx, sx);
	sx = -sx;
	sy = -sy;
}


	template<class t_Ty>
inline void quaternion<t_Ty>::factorYXZ (t_Ty& cy, t_Ty& sy, t_Ty& cx,
		t_Ty& sx, t_Ty& cz, t_Ty& sz)
{
	quaternion<t_Ty> alt(m[0], -m[2], m[1], m[3]);
	alt.factorXYZ(cy, sy, cx, sx, cz, sz);
	sy = -sy;
}


	template<class t_Ty>
inline void quaternion<t_Ty>::factorZXY (t_Ty& cz, t_Ty& sz, t_Ty& cx,
		t_Ty& sx, t_Ty& cy, t_Ty& sy)
{
	quaternion<t_Ty> alt(m[0], -m[3], m[1], -m[2]);
	alt.factorXYZ(cz, sz, cx, sx, cy, sy);
	sy = -sy;
	sz = -sz;
}


	template<class t_Ty>
inline void quaternion<t_Ty>::factorZYX (t_Ty& cz, t_Ty& sz, t_Ty& cy,
		t_Ty& sy, t_Ty& cx, t_Ty& sx)
{
	quaternion<t_Ty> alt(m[0], m[3], -m[2], m[1]);
	alt.factorXYZ(cz, sz, cy, sy, cx, sx);
	sy = -sy;
}


template<class t_Ty>
inline quaternion<t_Ty> quaternion<t_Ty>::closestX (const constraints& xCon) const
{
	return closest(1, xCon);
}


template<class t_Ty>
inline quaternion<t_Ty> quaternion<t_Ty>::closestY (const constraints& yCon) const
{
	return closest(2, yCon);
}


template<class t_Ty>
inline quaternion<t_Ty> quaternion<t_Ty>::closestZ (const constraints& zCon) const
{
	return closest(3, zCon);
}


template<class t_Ty>
inline quaternion<t_Ty> quaternion<t_Ty>::closestXY (const constraints& xCon,
		const constraints& yCon) const
{
	quaternion<t_Ty> q, tmp;
	t_Ty c0, s0, c1, s1, invLength;

	t_Ty det = m[0]*m[3] - m[1]*m[2];
	if (fabs(det) < (t_Ty)0.5 - epsilon<t_Ty>())
	{
		t_Ty discr = sqrt(fabs((t_Ty)1 -
					((t_Ty)4)*det*det));
		t_Ty a = m[0]*m[1] + m[2]*m[3];
		t_Ty b = m[0]*m[0] - m[1]*m[1]
			+ m[2]*m[2] - m[3]*m[3];

		if (b >= (t_Ty)0)
		{
			c0 = ((t_Ty)0.5)*(discr + b);
			s0 = a;
		}
		else
		{
			c0 = a;
			s0 = ((t_Ty)0.5)*(discr - b);
		}
		invLength = invSqrt(c0*c0 + s0*s0);
		c0 *= invLength;
		s0 *= invLength;

		c1 = m[0]*c0 + m[1]*s0;
		s1 = m[2]*c0 + m[3]*s0;
		invLength = invSqrt(c1*c1 + s1*s1);
		c1 *= invLength;
		s1 *= invLength;

		if (xCon.IsValid(c0, s0) && yCon.IsValid(c1, s1))
		{
			// The maximum occurs at an interior point.
			q[0] = c0*c1;
			q[1] = s0*c1;
			q[2] = c0*s1;
			q[3] = s0*s1;
		}
		else
		{
			// The maximum occurs at a boundary point.
			quaternion<t_Ty> r(xCon.CosMinAngle, xCon.SinMinAngle,
					(t_Ty)0, (t_Ty)0);
			quaternion<t_Ty> rInv(xCon.CosMinAngle, -xCon.SinMinAngle,
					(t_Ty)0, (t_Ty)0);
			quaternion<t_Ty> prod = rInv*(*this);
			tmp = prod.closest(2, yCon);
			t_Ty dotOptAngle = prod.dot(tmp);
			q = r*tmp;

			r = quaternion(xCon.CosMaxAngle, xCon.SinMaxAngle,
					(t_Ty)0, (t_Ty)0);
			rInv = quaternion(xCon.CosMaxAngle, -xCon.SinMaxAngle,
					(t_Ty)0, (t_Ty)0);
			prod = rInv*(*this);
			tmp = prod.closest(2, yCon);
			t_Ty dotAngle = prod.dot(tmp);
			if (dotAngle > dotOptAngle)
			{
				q = r*tmp;
				dotOptAngle = dotAngle;
			}

			r = quaternion(yCon.CosMinAngle, (t_Ty)0,
					yCon.SinMinAngle, (t_Ty)0);
			rInv = quaternion(yCon.CosMinAngle, (t_Ty)0,
					-yCon.SinMinAngle, (t_Ty)0);
			prod = (*this)*rInv;
			tmp = prod.closest(1, xCon);
			dotAngle = prod.dot(tmp);
			if (dotAngle > dotOptAngle)
			{
				q = tmp*r;
				dotOptAngle = dotAngle;
			}

			r = quaternion(yCon.CosMaxAngle, (t_Ty)0,
					yCon.SinMaxAngle, (t_Ty)0);
			rInv = quaternion(yCon.CosMaxAngle, (t_Ty)0,
					-yCon.SinMaxAngle, (t_Ty)0);
			prod = (*this)*rInv;
			tmp = prod.closest(1, xCon);
			dotAngle = prod.dot(tmp);
			if (dotAngle > dotOptAngle)
			{
				q = tmp*r;
				dotOptAngle = dotAngle;
			}
		}
	}
	else
	{
		// Infinitely many solutions, choose one that satisfies the angle
		// constraints.
		t_Ty minAngle, maxAngle, angle;
		constraints con;

		if (det > (t_Ty)0)
		{
			minAngle = xCon.MinAngle - yCon.MaxAngle;
			maxAngle = xCon.MaxAngle - yCon.MinAngle;
			con.SetAngles(minAngle, maxAngle);

			tmp = closest(1, con);

			angle = atan2f(tmp[1], tmp[0]);
			if (angle < minAngle || angle > maxAngle)
			{
				angle -= (tmp[1] >= (t_Ty)0 ? o_math_Pi :
						-o_math_Pi);
				// assert(minAngle <= angle && angle <= maxAngle);
			}

			if (angle <= xCon.MaxAngle - yCon.MaxAngle)
			{
				c1 = yCon.CosMaxAngle;
				s1 = yCon.SinMaxAngle;
				angle = yCon.MaxAngle + angle;
				c0 = math::cos(angle);
				s0 = math::sin(angle);
			}
			else
			{
				c0 = xCon.CosMaxAngle;
				s0 = xCon.SinMaxAngle;
				angle = xCon.MaxAngle - angle;
				c1 = math::cos(angle);
				s1 = math::sin(angle);
			}
		}
		else
		{
			minAngle = xCon.MinAngle + yCon.MinAngle;
			maxAngle = xCon.MaxAngle + yCon.MaxAngle;
			con.SetAngles(minAngle, maxAngle);

			tmp = closest(1, con);

			angle = atan2f(tmp[1], tmp[0]);
			if (angle < minAngle || angle > maxAngle)
			{
				angle -= (tmp[1] >= (t_Ty)0 ? o_math_Pi :
						-o_math_Pi);
				// assert(minAngle <= angle && angle <= maxAngle);
			}

			if (angle >= xCon.MinAngle + yCon.MaxAngle)
			{
				c1 = yCon.CosMaxAngle;
				s1 = yCon.SinMaxAngle;
				angle = angle - yCon.MaxAngle;
				c0 = math::cos(angle);
				s0 = math::sin(angle);
			}
			else
			{
				c0 = xCon.CosMaxAngle;
				s0 = xCon.SinMaxAngle;
				angle = angle - xCon.MaxAngle;
				c1 = math::cos(angle);
				s1 = math::sin(angle);
			}
		}

		q[0] = c0*c1;
		q[1] = s0*c1;
		q[2] = c0*s1;
		q[3] = s0*s1;
		if (dot(q) < (t_Ty)0)
		{
			q = -q;
		}
	}

	return q;
}


template<class t_Ty>
inline quaternion<t_Ty> quaternion<t_Ty>::closestYX (const constraints& yCon,
		const constraints& xCon) const
{
	quaternion<t_Ty> alt(m[0], m[1], m[2], -m[3]);
	quaternion<t_Ty> q = alt.closestXY(xCon, yCon);
	q[3] = -q[3];
	return q;
}


template<class t_Ty>
inline quaternion<t_Ty> quaternion<t_Ty>::closestZX (const constraints& zCon,
		const constraints& xCon) const
{
	quaternion<t_Ty> q, tmp;
	t_Ty c2, s2, c0, s0, invLength;

	t_Ty det = m[0]*m[2] - m[1]*m[3];
	if (fabs(det) < (t_Ty)0.5 - epsilon<t_Ty>())
	{
		t_Ty discr = sqrt(fabs((t_Ty)1 -
					((t_Ty)4)*det*det));
		t_Ty a = m[0]*m[3] + m[1]*m[2];
		t_Ty b = m[0]*m[0] + m[1]*m[1]
			- m[2]*m[2] - m[3]*m[3];

		if (b >= (t_Ty)0)
		{
			c2 = ((t_Ty)0.5)*(discr + b);
			s2 = a;
		}
		else
		{
			c2 = a;
			s2 = ((t_Ty)0.5)*(discr - b);
		}
		invLength = invSqrt(c2*c2 + s2*s2);
		c2 *= invLength;
		s2 *= invLength;

		c0 = m[0]*c2 + m[3]*s2;
		s0 = m[1]*c2 + m[2]*s2;
		invLength = invSqrt(c0*c0 + s0*s0);
		c0 *= invLength;
		s0 *= invLength;

		if (zCon.IsValid(c2, s2) && xCon.IsValid(c0, s0))
		{
			// The maximum occurs at an interior point.
			q[0] = c2*c0;
			q[1] = c2*s0;
			q[2] = s2*s0;
			q[3] = s2*c0;
		}
		else
		{
			// The maximum occurs at a boundary point.
			quaternion<t_Ty> r(zCon.CosMinAngle, (t_Ty)0, (t_Ty)0,
					zCon.SinMinAngle);
			quaternion<t_Ty> rInv(zCon.CosMinAngle, (t_Ty)0, (t_Ty)0,
					-zCon.SinMinAngle);
			quaternion<t_Ty> prod = rInv*(*this);
			tmp = prod.closest(1, xCon);
			t_Ty dotOptAngle = prod.dot(tmp);
			q = r*tmp;

			r = quaternion(zCon.CosMaxAngle, (t_Ty)0, (t_Ty)0,
					zCon.SinMaxAngle);
			rInv = quaternion(zCon.CosMaxAngle, (t_Ty)0, (t_Ty)0,
					-zCon.SinMaxAngle);
			prod = rInv*(*this);
			tmp = prod.closest(1, xCon);
			t_Ty dotAngle = prod.dot(tmp);
			if (dotAngle > dotOptAngle)
			{
				q = r*tmp;
				dotOptAngle = dotAngle;
			}

			r = quaternion(xCon.CosMinAngle, xCon.SinMinAngle,
					(t_Ty)0, (t_Ty)0);
			rInv = quaternion(xCon.CosMinAngle, -xCon.SinMinAngle,
					(t_Ty)0, (t_Ty)0);
			prod = (*this)*rInv;
			tmp = prod.closest(3, zCon);
			dotAngle = prod.dot(tmp);
			if (dotAngle > dotOptAngle)
			{
				q = tmp*r;
				dotOptAngle = dotAngle;
			}

			r = quaternion(xCon.CosMaxAngle, xCon.SinMaxAngle,
					(t_Ty)0, (t_Ty)0);
			rInv = quaternion(xCon.CosMaxAngle, -xCon.SinMaxAngle,
					(t_Ty)0, (t_Ty)0);
			prod = (*this)*rInv;
			tmp = prod.closest(3, zCon);
			dotAngle = prod.dot(tmp);
			if (dotAngle > dotOptAngle)
			{
				q = tmp*r;
				dotOptAngle = dotAngle;
			}
		}
	}
	else
	{
		// Infinitely many solutions, choose one that satisfies the angle
		// constraints.
		t_Ty minAngle, maxAngle, angle;
		constraints con;

		if (det > (t_Ty)0)
		{
			minAngle = xCon.MinAngle - zCon.MaxAngle;
			maxAngle = xCon.MaxAngle - zCon.MinAngle;
			con.SetAngles(minAngle, maxAngle);

			tmp = closest(1, con);

			angle = atan2f(tmp[1], tmp[0]);
			if (angle < minAngle || angle > maxAngle)
			{
				angle -= (tmp[1] >= (t_Ty)0 ? o_math_Pi :
						-o_math_Pi);
				// assert(minAngle <= angle && angle <= maxAngle);
			}

			if (angle <= xCon.MaxAngle - zCon.MaxAngle)
			{
				c2 = zCon.CosMaxAngle;
				s2 = zCon.SinMaxAngle;
				angle = zCon.MaxAngle + angle;
				c0 = math::cos(angle);
				s0 = math::sin(angle);
			}
			else
			{
				c0 = xCon.CosMaxAngle;
				s0 = xCon.SinMaxAngle;
				angle = xCon.MaxAngle - angle;
				c2 = math::cos(angle);
				s2 = math::sin(angle);
			}
		}
		else
		{
			minAngle = xCon.MinAngle + zCon.MinAngle;
			maxAngle = xCon.MaxAngle + zCon.MaxAngle;
			con.SetAngles(minAngle, maxAngle);

			tmp = closest(1, con);

			angle = atan2f(tmp[1], tmp[0]);
			if (angle < minAngle || angle > maxAngle)
			{
				angle -= (tmp[1] >= (t_Ty)0 ? o_math_Pi :
						-o_math_Pi);
				// assert(minAngle <= angle && angle <= maxAngle);
			}

			if (angle >= xCon.MinAngle + zCon.MaxAngle)
			{
				c2 = zCon.CosMaxAngle;
				s2 = zCon.SinMaxAngle;
				angle = angle - zCon.MaxAngle;
				c0 = math::cos(angle);
				s0 = math::sin(angle);
			}
			else
			{
				c0 = xCon.CosMaxAngle;
				s0 = xCon.SinMaxAngle;
				angle = angle - xCon.MaxAngle;
				c2 = math::cos(angle);
				s2 = math::sin(angle);
			}
		}

		q[0] = c2*c0;
		q[1] = c2*s0;
		q[2] = s2*s0;
		q[3] = s2*c0;
		if (dot(q) < (t_Ty)0)
		{
			q = -q;
		}
	}

	return q;
}


template<class t_Ty>
inline quaternion<t_Ty> quaternion<t_Ty>::closestXZ (const constraints& xCon,
		const constraints& zCon) const
{
	quaternion<t_Ty> alt(m[0], m[1], -m[2], m[3]);
	quaternion<t_Ty> q = alt.closestZX(zCon,xCon);
	q[2] = -q[2];
	return q;
}


template<class t_Ty>
inline quaternion<t_Ty> quaternion<t_Ty>::closestZY (const constraints& zCon,
		const constraints& yCon) const
{
	quaternion<t_Ty> q, tmp;
	t_Ty c2, s2, c1, s1, invLength;

	t_Ty det = m[0]*m[1] + m[2]*m[3];
	if (fabs(det) < (t_Ty)0.5 - epsilon<t_Ty>())
	{
		t_Ty discr = sqrt(fabs((t_Ty)1 -
					((t_Ty)4)*det*det));
		t_Ty a = m[0]*m[3] - m[1]*m[2];
		t_Ty b = m[0]*m[0] - m[1]*m[1]
			+ m[2]*m[2] - m[3]*m[3];

		if (b >= (t_Ty)0)
		{
			c2 = ((t_Ty)0.5)*(discr + b);
			s2 = a;
		}
		else
		{
			c2 = a;
			s2 = ((t_Ty)0.5)*(discr - b);
		}
		invLength = invSqrt(c2*c2 + s2*s2);
		c2 *= invLength;
		s2 *= invLength;

		c1 = m[0]*c2 + m[3]*s2;
		s1 = m[2]*c2 - m[1]*s2;
		invLength = invSqrt(c1*c1 + s1*s1);
		c1 *= invLength;
		s1 *= invLength;

		if (zCon.IsValid(c2, s2) && yCon.IsValid(c1, s1))
		{
			// The maximum occurs at an interior point.
			q[0] = c2*c1;
			q[1] = -s2*s1;
			q[2] = c2*s1;
			q[3] = s2*c1;
		}
		else
		{
			// The maximum occurs at a boundary point.
			quaternion<t_Ty> r(zCon.CosMinAngle, (t_Ty)0, (t_Ty)0,
					zCon.SinMinAngle);
			quaternion<t_Ty> rInv(zCon.CosMinAngle, (t_Ty)0, (t_Ty)0,
					-zCon.SinMinAngle);
			quaternion<t_Ty> prod = rInv*(*this);
			tmp = prod.closest(2, yCon);
			t_Ty dotOptAngle = prod.dot(tmp);
			q = r*tmp;

			r = quaternion(zCon.CosMaxAngle, (t_Ty)0, (t_Ty)0,
					zCon.SinMaxAngle);
			rInv = quaternion(zCon.CosMaxAngle, (t_Ty)0, (t_Ty)0,
					-zCon.SinMaxAngle);
			prod = rInv*(*this);
			tmp = prod.closest(2, yCon);
			t_Ty dotAngle = prod.dot(tmp);
			if (dotAngle > dotOptAngle)
			{
				q = r*tmp;
				dotOptAngle = dotAngle;
			}

			r = quaternion(yCon.CosMinAngle, (t_Ty)0,
					yCon.SinMinAngle, (t_Ty)0);
			rInv = quaternion(yCon.CosMinAngle, (t_Ty)0,
					-yCon.SinMinAngle, (t_Ty)0);
			prod = (*this)*rInv;
			tmp = prod.closest(3, zCon);
			dotAngle = prod.dot(tmp);
			if (dotAngle > dotOptAngle)
			{
				q = tmp*r;
				dotOptAngle = dotAngle;
			}

			r = quaternion(yCon.CosMaxAngle, (t_Ty)0,
					yCon.SinMaxAngle, (t_Ty)0);
			rInv = quaternion(yCon.CosMaxAngle, (t_Ty)0,
					-yCon.SinMaxAngle, (t_Ty)0);
			prod = (*this)*rInv;
			tmp = prod.closest(3, zCon);
			dotAngle = prod.dot(tmp);
			if (dotAngle > dotOptAngle)
			{
				q = tmp*r;
				dotOptAngle = dotAngle;
			}
		}
	}
	else
	{
		// Infinitely many solutions, choose one that satisfies the angle
		// constraints.
		t_Ty minAngle, maxAngle, angle;
		constraints con;

		if (det < (t_Ty)0)
		{
			minAngle = yCon.MinAngle - zCon.MaxAngle;
			maxAngle = yCon.MaxAngle - zCon.MinAngle;
			con.SetAngles(minAngle, maxAngle);

			tmp = closest(2, con);

			angle = atan2f(tmp[2], tmp[0]);
			if (angle < minAngle || angle > maxAngle)
			{
				angle -= (tmp[2] >= (t_Ty)0 ? o_math_Pi :
						-o_math_Pi);
				// assert(minAngle <= angle && angle <= maxAngle);
			}

			if (angle <= yCon.MaxAngle - zCon.MaxAngle)
			{
				c2 = zCon.CosMaxAngle;
				s2 = zCon.SinMaxAngle;
				angle = zCon.MaxAngle + angle;
				c1 = math::cos(angle);
				s1 = math::sin(angle);
			}
			else
			{
				c1 = yCon.CosMaxAngle;
				s1 = yCon.SinMaxAngle;
				angle = yCon.MaxAngle - angle;
				c2 = math::cos(angle);
				s2 = math::sin(angle);
			}
		}
		else
		{
			minAngle = yCon.MinAngle + zCon.MinAngle;
			maxAngle = yCon.MaxAngle + zCon.MaxAngle;
			con.SetAngles(minAngle, maxAngle);

			tmp = closest(2, con);

			angle = atan2f(tmp[2], tmp[0]);
			if (angle < minAngle || angle > maxAngle)
			{
				angle -= (tmp[2] >= (t_Ty)0 ? o_math_Pi :
						-o_math_Pi);
				// assert(minAngle <= angle && angle <= maxAngle);
			}

			if (angle >= yCon.MinAngle + zCon.MaxAngle)
			{
				c2 = zCon.CosMaxAngle;
				s2 = zCon.SinMaxAngle;
				angle = angle - zCon.MaxAngle;
				c1 = math::cos(angle);
				s1 = math::sin(angle);
			}
			else
			{
				c1 = yCon.CosMaxAngle;
				s1 = yCon.SinMaxAngle;
				angle = angle - yCon.MaxAngle;
				c2 = math::cos(angle);
				s2 = math::sin(angle);
			}
		}

		q[0] = c2*c1;
		q[1] = -s2*s1;
		q[2] = c2*s1;
		q[3] = s2*c1;
		if (dot(q) < (t_Ty)0)
		{
			q = -q;
		}
	}

	return q;
}


template<class t_Ty>
inline quaternion<t_Ty> quaternion<t_Ty>::closestYZ (const constraints& yCon,
		const constraints& zCon) const
{
	quaternion<t_Ty> alt(m[0], -m[1], m[2], m[3]);
	quaternion<t_Ty> q = alt.closestZY(zCon, yCon);
	q[1] = -q[1];
	return q;
}


template<class t_Ty>
inline quaternion<t_Ty> quaternion<t_Ty>::closest (int axis) const
{
	// The appropriate nonzero components will be set later.
	quaternion<t_Ty> q((t_Ty)0, (t_Ty)0, (t_Ty)0, (t_Ty)0);
	t_Ty p0 = m[0];
	t_Ty p1 = m[axis];
	t_Ty sqrLength = p0*p0 + p1*p1;
	if (sqrLength > epsilon<t_Ty>())
	{
		// A unique closest point.
		t_Ty invLength = invSqrt(sqrLength);
		q[0] = p0*invLength;
		q[axis] = p1*invLength;
	}
	else
	{
		// Infinitely many solutions, choose the one for theta = 0.
		q[0] = (t_Ty)1;
		q[axis] = (t_Ty)0;
	}
	return q;
}


template<class t_Ty>
inline quaternion<t_Ty> quaternion<t_Ty>::closest (int axis,
		const constraints& con) const
{
	quaternion<t_Ty> q((t_Ty)0, (t_Ty)0, (t_Ty)0, (t_Ty)0);

	t_Ty p0 = m[0];
	t_Ty p1 = m[axis];
	t_Ty sqrLength = p0*p0 + p1*p1;
	if (sqrLength > epsilon<t_Ty>())
	{
		t_Ty invLength = invSqrt(sqrLength);
		p0 *= invLength;
		p1 *= invLength;
		if (con.IsValid(p0, p1))
		{
			// The maximum occurs at an interior point.
			q[0] = p0;
			q[axis] = p1;
		}
		else
		{
			// The maximum occurs at a boundary point.
			t_Ty csMin = con.CosMinAngle;
			t_Ty snMin = con.SinMinAngle;
			t_Ty dotMinAngle = p0*csMin + p1*snMin;
			if (dotMinAngle < (t_Ty)0)
			{
				csMin = -csMin;
				snMin = -snMin;
				dotMinAngle = -dotMinAngle;
			}

			t_Ty csMax = con.CosMaxAngle;
			t_Ty snMax = con.SinMaxAngle;
			t_Ty dotMaxAngle = p0*csMax + p1*snMax;
			if (dotMaxAngle < (t_Ty)0)
			{
				csMax = -csMax;
				snMax = -snMax;
				dotMaxAngle = -dotMaxAngle;
			}

			if (dotMaxAngle >= dotMinAngle)
			{
				q[0] = csMax;
				q[axis] = snMax;
			}
			else
			{
				q[0] = csMin;
				q[axis] = snMin;
			}
		}
	}
	else
	{
		// Infinitely many solutions, choose one that satisfies the angle
		// constraints.
		q[0] = con.CosAvrAngle;
		q[axis] = con.SinAvrAngle;
	}

	return q;
}



// quaternion<t_Ty>::constraints


	template<class t_Ty>
inline quaternion<t_Ty>::constraints::constraints ()
{
	// Members are uninitialized.
}


	template<class t_Ty>
inline quaternion<t_Ty>::constraints::constraints (t_Ty minAngle, t_Ty maxAngle)
{
	SetAngles(minAngle, maxAngle);
}


	template<class t_Ty>
inline void quaternion<t_Ty>::constraints::SetAngles (t_Ty minAngle, t_Ty maxAngle)
{
	MinAngle = minAngle;
	MaxAngle = maxAngle;
	CosMinAngle = math::cos(MinAngle);
	SinMinAngle = math::sin(MinAngle);
	CosMaxAngle = math::cos(MaxAngle);
	SinMaxAngle = math::sin(MaxAngle);
	DiffCosMaxMin = CosMaxAngle - CosMinAngle;
	DiffSinMaxMin = SinMaxAngle - SinMinAngle;
	t_Ty avrAngle = ((t_Ty)0.5)*(MinAngle + MaxAngle);
	CosAvrAngle = math::cos(avrAngle);
	SinAvrAngle = math::sin(avrAngle);
}


template<class t_Ty>
inline bool quaternion<t_Ty>::constraints::IsValid (t_Ty x, t_Ty y) const
{
	// (x,y) must be unit-length.

	// Test whether (x,y) satisfies the constraints.
	t_Ty xm = x - CosMinAngle;
	t_Ty ym = y - SinMinAngle;
	if (xm*DiffSinMaxMin >= ym*DiffCosMaxMin)
	{
		return true;
	}

	// Test whether (-x,-y) satisfies the constraints.
	t_Ty xp = x + CosMinAngle;
	t_Ty yp = y + SinMinAngle;
	if (xp*DiffSinMaxMin <= yp*DiffCosMaxMin)
	{
		return true;
	}

	return false;
}
