#ifndef o_math_quaternion_h__
#define o_math_quaternion_h__

#include "angle.h"
#include "matrix3x3.h"

o_declareNT(class, (phantom, math), (typename), (t_Ty), quaternion);
o_declareNT(class, (phantom, math), (typename), (t_Ty), axis_angle);

o_namespace_begin(phantom, math)

template<class t_Ty>
class axis_angle
{
public:
    typedef axis_angle<t_Ty> self_type;
    axis_angle() : axis(0, 1, 0), angle(0.f) {} // default rotate around Y (arbitrary, but chosen to fit most common cases in 3D
    axis_angle(const vector3<t_Ty>& ax, t_Ty ag) : axis(ax), angle(ag) {}
    axis_angle(const vector3<t_Ty>& ax, math::angle<t_Ty> ag) : axis(ax), angle(ag) {}
    inline bool operator== (const self_type& aa) const { return aa.axis == axis AND aa.angle == angle; }
    inline bool operator!= (const self_type& aa) const { return !operator==(aa); }
    vector3<t_Ty>      axis;
    math::angle<t_Ty>  angle;
};

template<class t_Ty>
class quaternion
{
public:
    typedef quaternion<t_Ty> self_type;
	// A quaternion is q = w + x*i + y*j + z*k where (w,x,y,z) is not
	// necessarily a unit-length vector in 4D.

	// Construction.
	quaternion ();  // uninitialized
	quaternion (t_Ty w, t_Ty x, t_Ty y, t_Ty z);
	quaternion (const quaternion<t_Ty>& q);

	// quaternion for the input rotation matrix.
	quaternion (const matrix3x3<t_Ty>& rot);

	// quaternion for the rotation of the axis-angle pair.
	quaternion (const vector3<t_Ty>& axis, t_Ty angle);

    // quaternion for the rotation of the axis-angle pair.
    quaternion (const axis_angle<t_Ty>& axis_angle);

	// quaternion for the rotation matrix with specified columns.
	quaternion (const vector3<t_Ty> rotColumn[3]);

	// Coordinate access as an array:  0 = w, 1 = x, 2 = y, 3 = z.
	inline operator const t_Ty* () const;
	inline operator t_Ty* ();
	inline const t_Ty& operator[] (int i) const;
	inline t_Ty& operator[] (int i);

	// Assignment.
	inline quaternion<t_Ty>& operator= (const quaternion<t_Ty>& q);

	// Comparison (for use by STL containers).
	inline bool operator== (const quaternion<t_Ty>& q) const;
	inline bool operator!= (const quaternion<t_Ty>& q) const;
	inline bool operator<  (const quaternion<t_Ty>& q) const;
	inline bool operator<= (const quaternion<t_Ty>& q) const;
	inline bool operator>  (const quaternion<t_Ty>& q) const;
	inline bool operator>= (const quaternion<t_Ty>& q) const;

	// Arithmetic operations.
	inline quaternion<t_Ty> operator+ (const quaternion<t_Ty>& q) const;
	inline quaternion<t_Ty> operator- (const quaternion<t_Ty>& q) const;
	inline quaternion<t_Ty> operator* (const quaternion<t_Ty>& q) const;
	inline quaternion<t_Ty> operator* (t_Ty scalar) const;
	inline quaternion<t_Ty> operator/ (t_Ty scalar) const;
	inline quaternion<t_Ty> operator- () const;

	friend quaternion<t_Ty> operator* (t_Ty scalar,
			const quaternion<t_Ty>& q)
	{
		return q*scalar;
	}

	// Arithmetic updates.
	inline quaternion<t_Ty>& operator+= (const quaternion<t_Ty>& q);
	inline quaternion<t_Ty>& operator-= (const quaternion<t_Ty>& q);
	inline quaternion<t_Ty>& operator*= (t_Ty scalar);
	inline quaternion<t_Ty>& operator/= (t_Ty scalar);

	// Conversion between quaternions, matrices, and axis-angle.
	inline void fromRotationmatrix (const matrix3x3<t_Ty>& rot);

	inline void toRotationmatrix (matrix3x3<t_Ty>& rot) const;

	inline void fromRotationmatrix (const vector3<t_Ty> rotColumn[3]);

	inline void toRotationmatrix (vector3<t_Ty> rotColumn[3]) const;

	inline void fromAxisAngle (const vector3<t_Ty>& axis, t_Ty angle);

    inline void setAxisAngle (axis_angle<t_Ty> axis_angle)
    {
        fromAxisAngle(axis_angle.axis, axis_angle.angle.getRadian());
    }

    inline axis_angle<t_Ty> getAxisAngle () const
    {
        t_Ty angle;
        vector3<t_Ty> axis;
        toAxisAngle(axis, angle);
        return axis_angle<t_Ty>(axis, angle);
    }

	inline void toAxisAngle (vector3<t_Ty>& axis, t_Ty& angle) const;

	inline void fromAxes (const vector3<t_Ty>& xaxis, const vector3<t_Ty>& yaxis, const vector3<t_Ty>& zaxis)
	{
		matrix3x3<t_Ty> kRot;

		kRot[0][0] = xaxis.x;
		kRot[0][1] = xaxis.y;
		kRot[0][2] = xaxis.z;

		kRot[1][0] = yaxis.x;
		kRot[1][1] = yaxis.y;
		kRot[1][2] = yaxis.z;

		kRot[2][0] = zaxis.x;
		kRot[2][1] = zaxis.y;
		kRot[2][2] = zaxis.z;

		fromRotationmatrix(kRot);

	}
	//-----------------------------------------------------------------------
	void toAxes(vector3<t_Ty>* akAxis) const
	{
		matrix3x3<t_Ty> kRot;

		toRotationmatrix(kRot);

		for (size_t iCol = 0; iCol < 3; iCol++)
		{
			akAxis[iCol].x = kRot[(unsigned int)iCol][0];
			akAxis[iCol].y = kRot[(unsigned int)iCol][1];
			akAxis[iCol].z = kRot[(unsigned int)iCol][2];
		}
	}

	// Functions of a quaternion.
	inline t_Ty length () const;  // length of 4-tuple
	inline t_Ty lengthSquared () const;  // squared length of 4-tuple
	inline t_Ty dot (const quaternion<t_Ty>& q) const;  // dot product of 4-tuples
	inline t_Ty normalize (t_Ty epsilon = std::numeric_limits<t_Ty>::epsilon());
	quaternion<t_Ty> inverse () const;  // apply to non-zero quaternion
	quaternion<t_Ty> conjugate () const;  // negate x, y, and z terms
	quaternion<t_Ty> exp () const;  // apply to quaternion with w = 0
	quaternion<t_Ty> log () const;  // apply to unit-length quaternion

	// Rotation of a vector by a quaternion.
	vector3<t_Ty> rotate (const vector3<t_Ty>& vec) const;

	// Spherical linear interpolation.
	quaternion<t_Ty>& slerp (t_Ty t, const quaternion<t_Ty>& p, const quaternion<t_Ty>& q);
	quaternion<t_Ty>& slerpExtraSpins (t_Ty t, const quaternion<t_Ty>& p,
			const quaternion<t_Ty>& q, int extraSpins);
	// ------------------------------------
	// linearly interpolate each component, then normalize the quaternion
	// Unlike spherical interpolation, this does not rotate at a constant velocity,
	// although that's not necessarily a bad thing
	// ------------------------------------
	inline quaternion<t_Ty>& nlerp(t_Ty t, const quaternion &a, const quaternion &b, const bool bReduceTo360 )
	{
		t_Ty t1 = (t_Ty)1.0 - t;

		if ( bReduceTo360 && a.dot(b) < (t_Ty)0.0 )
			*this = a * t1 + b * -t;
		else
			*this = a * t1 + b * t;

		normalize();
		return *this;
	}
	// intermediate terms for spherical quadratic interpolation.
	quaternion<t_Ty>& intermediate (const quaternion<t_Ty>& q0, const quaternion<t_Ty>& q1,
			const quaternion<t_Ty>& q2);

	// Spherical quadratic interpolation.
	quaternion<t_Ty>& squad (t_Ty t, const quaternion<t_Ty>& q0, const quaternion<t_Ty>& a0,
			const quaternion<t_Ty>& a1, const quaternion<t_Ty>& q1);

	// Compute a quaternion that rotates unit-length vector V1 to unit-length
	// vector V2.  The rotation is about the axis perpendicular to both V1 and
	// V2, with angle of that between V1 and V2.  If V1 and V2 are parallel,
	// any axis of rotation will do, such as the permutation (z2,x2,y2), where
	// V2 = (x2,y2,z2).
	quaternion<t_Ty>& align (const vector3<t_Ty>& v1, const vector3<t_Ty>& v2);

	// Decompose a quaternion into q = qTwist * qSwing, where q is 'this'
	// quaternion.  If V1 is the input axis and V2 is the rotation of V1 by
	// q, qSwing represents the rotation about the axis perpendicular to
	// V1 and V2 (see quaternion::align), and qTwist is a rotation about V1.
	void decomposeTwistTimesSwing (const vector3<t_Ty>& v1,
			quaternion<t_Ty>& twist, quaternion<t_Ty>& swing);

	// Decompose a quaternion into q = qSwing * qTwist, where q is 'this'
	// quaternion.  If V1 is the input axis and V2 is the rotation of V1 by
	// q, qSwing represents the rotation about the axis perpendicular to
	// V1 and V2 (see quaternion::align), and qTwist is a rotation about V1.
	void decomposeSwingTimesTwist (const vector3<t_Ty>& v1,
			quaternion<t_Ty>& swing, quaternion<t_Ty>& twist);

	// *** Find closest quaternions with unconstrained angles.

	// Closest quaternion of the form (cx + sx*i).
	quaternion<t_Ty> closestX () const;

	// Closest quaternion of the form (cy + sy*j).
	quaternion<t_Ty> closestY () const;

	// Closest quaternion of the form (cz + sz*k).
	quaternion<t_Ty> closestZ () const;

	// Closest quaternion of the form (cx + sx*i)*(cy + sy*j).
	quaternion<t_Ty> closestXY () const;

	// Closest quaternion of the form (cy + sy*j)*(cx + sx*i).
	quaternion<t_Ty> closestYX () const;

	// Closest quaternion of the form (cz + sz*k)*(cx + sx*i).
	quaternion<t_Ty> closestZX () const;

	// Closest quaternion of the form (cx + sx*i)*(cz + sz*k).
	quaternion<t_Ty> closestXZ () const;

	// Closest quaternion of the form (cy + sy*j)*(cz + sz*k).
	quaternion<t_Ty> closestYZ () const;

	// Closest quaternion of the form (cz + sz*k)*(cy + sy*j).
	quaternion<t_Ty> closestZY () const;

	// factor to (cx + sx*i)*(cy + sy*j)*(cz + sz*k).
	void factorXYZ(t_Ty& cx, t_Ty& sx, t_Ty& cy, t_Ty& sy, t_Ty& cz,
			t_Ty& sz);

	// factor to (cx + sx*i)*(cz + sz*k)*(cy + sy*j).
	void factorXZY(t_Ty& cx, t_Ty& sx, t_Ty& cz, t_Ty& sz, t_Ty& cy,
			t_Ty& sy);

	// factor to (cy + sy*j)*(cz + sz*k)*(cx + sx*i).
	void factorYZX(t_Ty& cy, t_Ty& sy, t_Ty& cz, t_Ty& sz, t_Ty& cx,
			t_Ty& sx);

	// factor to (cy + sy*j)*(cx + sx*i)*(cz + sz*k).
	void factorYXZ(t_Ty& cy, t_Ty& sy, t_Ty& cx, t_Ty& sx, t_Ty& cz,
			t_Ty& sz);

	// factor to (cz + sz*k)*(cx + sx*i)*(cy + sy*j).
	void factorZXY(t_Ty& cz, t_Ty& sz, t_Ty& cx, t_Ty& sx, t_Ty& cy,
			t_Ty& sy);

	// factor to (cz + sz*k)*(cy + sy*j)*(cx + sx*i).
	void factorZYX(t_Ty& cz, t_Ty& sz, t_Ty& cy, t_Ty& sy, t_Ty& cx,
			t_Ty& sx);

	// *** Find closest quaternions with constrained angles.
	class constraints
	{
		public:
			constraints ();  // uninitialized
			constraints (t_Ty minAngle, t_Ty maxAngle);
			void SetAngles (t_Ty minAngle, t_Ty maxAngle);
			bool IsValid (t_Ty x, t_Ty y) const;

			t_Ty MinAngle;       // in [-o_math_Pi/2,o_math_Pi/2]
			t_Ty MaxAngle;       // in [m_fMinAngle/2,o_math_Pi/2]
			t_Ty CosMinAngle;    // = cos(m_fMinAngle)
			t_Ty SinMinAngle;    // = sin(m_fMinAngle)
			t_Ty CosMaxAngle;    // = cos(m_fMaxAngle)
			t_Ty SinMaxAngle;    // = sin(m_fMaxAngle)
			t_Ty DiffCosMaxMin;  // = cos(m_fMaxAngle) - cos(m_fMinAngle)
			t_Ty DiffSinMaxMin;  // = sin(m_fMaxAngle) - sin(m_fMinAngle)
			t_Ty CosAvrAngle;    // = cos((m_fMinAngle + m_fMaxAngle)/2)
			t_Ty SinAvrAngle;    // = sin((m_fMinAngle + mMFaxAngle)/2)
	};

	// Closest constrained quaternion of the form (cx + sx*i).
	quaternion<t_Ty> closestX (const constraints& xCon) const;

	// Closest constrained quaternion of the form (cy + sy*j).
	quaternion<t_Ty> closestY (const constraints& yCon) const;

	// Closest constrained quaternion of the form (cz + sz*k).
	quaternion<t_Ty> closestZ (const constraints& zCon) const;

	// Closest constrained quaternion of the form (cx + sx*i)*(cy + sy*j).
	quaternion<t_Ty> closestXY (const constraints& xCon,
			const constraints& yCon) const;

	// Closest constrained quaternion of the form (cy + sy*j)*(cx + sx*i).
	quaternion<t_Ty> closestYX (const constraints& yCon,
			const constraints& xCon) const;

	// Closest constrained quaternion of the form (cz + sz*k)*(cx + sx*i).

	quaternion<t_Ty> closestZX (const constraints& zCon,
			const constraints& xCon) const;

	// Closest constrained quaternion of the form (cx + sx*i)*(cz + sz*k).

	quaternion<t_Ty> closestXZ (const constraints& xCon,
			const constraints& zCon) const;

	// Closest constrained quaternion of the form (cz + sz*k)*(cy + sy*j).

	quaternion<t_Ty> closestZY (const constraints& zCon,
			const constraints& yCon) const;

	// Closest constrained quaternion of the form (cy + sy*j)*(cz + sz*k).

	quaternion<t_Ty> closestYZ (const constraints& yCon,
			const constraints& zCon) const;

	// Special quaternions.
	static const quaternion<t_Ty> ZERO;
	static const quaternion<t_Ty> IDENTITY;

private:
	// Closest unconstrained quaternion of the form:
	//   (cx + sx*i) when axis = 1,
	//   (cy + sy*j) when axis = 2,
	//   (cz + sz*k) when axis = 3
	quaternion<t_Ty> closest (int axis) const;

	// Closest constrained quaternion of the form:
	//   (cx + sx*i) when axis = 1,
	//   (cy + sy*j) when axis = 2,
	//   (cz + sz*k) when axis = 3

	quaternion<t_Ty> closest (int axis, const constraints& con) const;

public:
	// Order of storage is (w,x,y,z).
	union
	{
		t_Ty m[4];
		struct
		{
			t_Ty w;
			t_Ty x;
			t_Ty y;
			t_Ty z;
		};
	};
};

/** typedefs **/
typedef quaternion<float32> quaternionf;
typedef quaternion<float64> quaterniond;

#	include "quaternion.inl"

o_namespace_end(phantom, math)

#endif
