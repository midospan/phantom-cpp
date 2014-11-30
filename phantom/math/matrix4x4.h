#ifndef o_math_matrix4x4_h__
#define o_math_matrix4x4_h__

#include <limits>
#include "vector4.h"
#include "matrix3x3.h"

// Needed for memcpy (Qt creator with mingw)
#include <string.h>

o_declareNT(class, (phantom, math), (typename), (t_Ty), matrix4x4);

o_namespace_begin(phantom, math)

template<class t_Ty>
class aabb3;

template<class t_Ty>
class quaternion;

// Colum major matrix
template<class t_Ty>
class matrix4x4
{
public:
    typedef matrix4x4<t_Ty> self_type;
    typedef vector4<t_Ty> vector4_type;

	// If makeZero is 'true', create the zero matrix; otherwise, create the
	// identity matrix.
	matrix4x4 (bool makeZero = true);

	// Copy constructor.
	matrix4x4 (const matrix3x3<t_Ty>& mat);
	matrix4x4 (const self_type& mat);

	// Input mrc is in row r, column c.
	matrix4x4 (
				t_Ty m00, t_Ty m01, t_Ty m02, t_Ty m03,
				t_Ty m10, t_Ty m11, t_Ty m12, t_Ty m13,
				t_Ty m20, t_Ty m21, t_Ty m22, t_Ty m23,
				t_Ty m30, t_Ty m31, t_Ty m32, t_Ty m33);

	// Create a matrix from a position/orientation/scale
	inline matrix4x4 (const vector3<t_Ty>& position, const vector3<t_Ty>& scale, const quaternion<t_Ty>& orientation);

	// Create a matrix from an array of numbers.  The input array is
	// interpreted based on the bool input as
	//   true:  entry[0..15]={m00,m01,m02,m03,m10,m11,m12,m13,m20,m21,m22,
	//                        m23,m30,m31,m32,m33} [row major]
	//   false: entry[0..15]={m00,m10,m20,m30,m01,m11,m21,m31,m02,m12,m22,
	//                        m32,m03,m13,m23,m33} [col major]
	matrix4x4 (const t_Ty entry[16], bool colMajor = true);

	// Assignment.
	matrix4x4& operator= (const self_type& mat);

	// Create various matrices.
	void makeZero ();
	void makeIdentity ();

	// Arithmetic operations.
	self_type operator+ (const self_type& mat) const;
	self_type operator- (const self_type& mat) const;
	self_type operator* (t_Ty scalar) const;
	self_type operator/ (t_Ty scalar) const;
	self_type operator- () const;

	// Arithmetic updates.
	self_type& operator+= (const self_type& mat);
	self_type& operator-= (const self_type& mat);
	self_type& operator*= (t_Ty scalar);
	self_type& operator/= (t_Ty scalar);

	// M*vec
	vector4_type operator* (const vector4_type& vec) const;

	// u^t_Ty*M*v
	t_Ty qForm (const vector4_type& u, const vector4_type& v) const;

	// M^t_Ty
	self_type transpose () const;

	// M*mat
	self_type operator* (const self_type& mat) const;

	// Other operations.
	self_type inverse (t_Ty epsilon = (t_Ty)0) const;
	self_type adjoint () const;
	t_Ty determinant () const;

	inline matrix3x3<t_Ty> toMatrix3x3() const
	{
		matrix3x3<t_Ty> result;
		result.m[0] = m[0];
		result.m[1] = m[1];
		result.m[2] = m[2];
		result.m[3] = m[4];
		result.m[4] = m[5];
		result.m[5] = m[6];
		result.m[6] = m[8];
		result.m[7] = m[9];
		result.m[8] = m[10];
		return result;
	}

	// Projection matrices onto a specified plane (containing an 'origin'
	// point and a unit-length 'normal').
	void makeObliqueProjection (const vector3<t_Ty>& normal,
								const vector3<t_Ty>& origin, const vector3<t_Ty>& direction);

	void makePerspectiveProjection (const vector3<t_Ty>& normal,
									const vector3<t_Ty>& origin, const vector3<t_Ty>& eye);


	void computePerspectiveProjectionParameters(t_Ty aspectRatio, t_Ty fovy, t_Ty anear, t_Ty& left, t_Ty& right, t_Ty& bottom, t_Ty& top) const
	{
		// Calculate general projection parameters
		t_Ty thetaY (fovy * (t_Ty)0.5);
		t_Ty tanThetaY = tan(thetaY);
		t_Ty tanThetaX = tanThetaY * aspectRatio;

		t_Ty nearOffsetX = (t_Ty)0;
		t_Ty nearOffsetY = (t_Ty)0;
		t_Ty half_w = tanThetaX * anear;
		t_Ty half_h = tanThetaY * anear;

		left   = - half_w + nearOffsetX;
		right  = + half_w + nearOffsetX;
		bottom = - half_h + nearOffsetY;
		top    = + half_h + nearOffsetY;
	}


	void makePerspectiveProjection(t_Ty aspectRatio, t_Ty fovy, t_Ty anear, t_Ty afar, aabb3<t_Ty>* outAABB = nullptr)
	{
		// Common calcs
		t_Ty left, right, bottom, top;

		computePerspectiveProjectionParameters(aspectRatio, fovy, anear, left, right, bottom, top);

		// The code below will dealing with general projection
		// parameters, similar glFrustum and glOrtho.
		// Doesn't optimise manually except division operator, so the
		// code more self-explaining.

		t_Ty inv_w = 1 / (right - left);
		t_Ty inv_h = 1 / (top - bottom);
		t_Ty inv_d = 1 / (afar - anear);

		// Recalc if frustum params changed
		// Calc matrix elements

		// A = 2 * near / (right - left)
		// B = 2 * near / (top - bottom)
		// C = (right + left) / (right - left)
		// D = (top + bottom) / (top - bottom)
		// q = - (far + near) / (far - near)
		// qn = - 2 * (far * near) / (far - near)

		t_Ty A = 2 * anear * inv_w;
		t_Ty B = 2 * anear * inv_h;
		t_Ty C = (right + left) * inv_w;
		t_Ty D = (top + bottom) * inv_h;
		t_Ty q, qn;
		if (afar == 0)
		{
			// Infinite far plane
			q = PROJECTION_INFINITE_FAR_PLANE_ADJUSTMENT - 1;
			qn = anear * (PROJECTION_INFINITE_FAR_PLANE_ADJUSTMENT - 2);
		}
		else
		{
			q = - (afar + anear) * inv_d;
			qn = -2 * (afar * anear) * inv_d;
		}

		// NB: This creates 'uniform' perspective projection matrix,
		// which depth range [-1,1], right-handed rules
		//
		// [ A   0   C   0  ]
		// [ 0   B   D   0  ]
		// [ 0   0   q   qn ]
		// [ 0   0   -1  0  ]
		//

		mm[0][0] = A;      mm[1][0] = (t_Ty)0.0;   mm[2][0] = C;   mm[3][0] = (t_Ty)0.0;
		mm[0][1] = (t_Ty)0.0;    mm[1][1] = B;     mm[2][1] = D;   mm[3][1] = (t_Ty)0.0;
		mm[0][2] = (t_Ty)0.0;    mm[1][2] = (t_Ty)0;     mm[2][2] = q;   mm[3][2] = qn;
		mm[0][3] = (t_Ty)0.0;    mm[1][3] = (t_Ty)0;     mm[2][3] = (t_Ty)-1;  mm[3][3] = (t_Ty)0.0;

		// Calculate bounding box (local)
		// Box is from 0, down -Z, max dimensions as determined from far plane
		// If infinite view frustum just pick a far value
		if(outAABB)
		{
			t_Ty farDist = (t_Ty)((afar == 0) ? 100000 : afar);
			// Near plane bounds
			vector3<t_Ty> min(left, bottom, -farDist);
			vector3<t_Ty> max(right, top, 0);

			// Merge with far plane bounds
			t_Ty radio = farDist / (t_Ty)((anear == 0) ? 0.0001 : anear);
			min.makeFloor(vector3<t_Ty>(left * radio, bottom * radio, -farDist));
			max.makeCeil(vector3<t_Ty>(right * radio, top * radio, 0));

			outAABB->set(min, max);
		}
	}

	void computeOrthogonalProjectionParameters(t_Ty aspectRatio, t_Ty height, t_Ty& left, t_Ty& right, t_Ty& bottom, t_Ty& top) const
	{
		// Unknown how to apply frustum offset to orthographic camera, just ignore here
		t_Ty half_w = height * aspectRatio * 0.5f;
		t_Ty half_h = height * 0.5f;

		left   = - half_w;
		right  = + half_w;
		bottom = - half_h;
		top    = + half_h;
	}

	void makeOrthogonalProjection(t_Ty aspectRatio, t_Ty height, t_Ty anear, t_Ty afar, aabb3<t_Ty>* outAABB = nullptr)
	{
		// Common calcs
		t_Ty left, right, bottom, top;
		computeOrthogonalProjectionParameters(aspectRatio, height, left, right, bottom, top);

		// The code below will dealing with general projection
		// parameters, similar glFrustum and glOrtho.
		// Doesn't optimise manually except division operator, so the
		// code more self-explaining.

		t_Ty inv_w = 1 / (right - left);
		t_Ty inv_h = 1 / (top - bottom);
		t_Ty inv_d = 1 / (afar - anear);

		t_Ty A = 2 * inv_w;
		t_Ty B = 2 * inv_h;
		t_Ty C = - (right + left) * inv_w;
		t_Ty D = - (top + bottom) * inv_h;
		t_Ty q, qn;
		if (afar == 0)
		{
			// Can not do infinite far plane here, avoid divided zero only
			q = - PROJECTION_INFINITE_FAR_PLANE_ADJUSTMENT / anear;
			qn = - PROJECTION_INFINITE_FAR_PLANE_ADJUSTMENT - 1;
		}
		else
		{
			q = - 2 * inv_d;
			qn = - (afar + anear)  * inv_d;
		}

		// NB: This creates 'uniform' orthographic projection matrix,
		// which depth range [-1,1], right-handed rules
		//
		// [ A   0   0   C  ]
		// [ 0   B   0   D  ]
		// [ 0   0   q   qn ]
		// [ 0   0   0   1  ]
		//
		// A = 2 * / (right - left)
		// B = 2 * / (top - bottom)
		// C = - (right + left) / (right - left)
		// D = - (top + bottom) / (top - bottom)
		// q = - 2 / (far - near)
		// qn = - (far + near) / (far - near)

		mm[0][0] = A;     mm[1][0] = 0.f;  mm[2][0] = 0.f;   mm[3][0] = C;
		mm[0][1] = 0.f;   mm[1][1] = B;    mm[2][1] = 0.f;   mm[3][1] = D;
		mm[0][2] = 0.f;   mm[1][2] = 0.f;  mm[2][2] = q;     mm[3][2] = qn;
		mm[0][3] = 0.f;   mm[1][3] = 0.f;  mm[2][3] = 0.f;   mm[3][3] = 1;

		/*RenderSystem* renderSystem = Root::getSingleton().getRenderSystem();
			// API specific
			renderSystem->ConvertProjectionmatrix(mProjmatrix, mProjmatrixRS);
			// API specific for Gpu Programs
			renderSystem->ConvertProjectionmatrix(mProjmatrix, mProjmatrixRSDepth, true);*/

		// Calculate bounding box (local)
		// Box is from 0, down -Z, max dimensions as determined from far plane
		// If infinite view frustum just pick a far value
		if(outAABB)
		{
			t_Ty farDist = (afar == 0) ? 100000 : afar;
			// Near plane bounds
			vector3<t_Ty> min(left, bottom, -farDist);
			vector3<t_Ty> max(right, top, 0);

			outAABB->set(min, max);
		}
	}

	// Reflection matrix through a specified plane.
	void makeReflection (const vector3<t_Ty>& normal,
							const vector3<t_Ty>& origin);

	// Special matrices.
	static const self_type ZERO;
    static const self_type IDENTITY;
    static t_Ty PROJECTION_INFINITE_FAR_PLANE_ADJUSTMENT;

	// Get the column by index (the matrix is column major)
	const vector4_type& operator[](unsigned int i) const
	{
		o_assert(i<4);
		return (const vector4_type&)(m[i*4]);
	}

	vector4_type& operator[](unsigned int i)
	{
		o_assert(i<4);
		return (vector4_type&)(m[i*4]);
	}

	const t_Ty& operator()(unsigned int col, unsigned int row) const
	{
		o_assert(col<4 && row<4);
		return m[col*4+row];
	}

	t_Ty& operator()(unsigned int col, unsigned int row)
	{
		o_assert(col<4 && row<4);
		return m[col*4+row];
	}

	bool operator==(const self_type& other) const
	{
		return memcmp(other.m, m, sizeof(m)) == 0;
	}

	bool operator!=(const self_type& other) const
    {
        return memcmp(other.m, m, sizeof(m)) != 0;
	}

public:
	union
	{
		t_Ty m[16];
        t_Ty mm[4][4];
        struct
        {
            vector4_type ex;
            vector4_type ey;
            vector4_type ez;
            vector4_type ew;
        };
	};
};

/** Typdefs **/
typedef matrix4x4<float32> matrix4x4f;
typedef matrix4x4<float64> matrix4x4d;

// c * M
template<class t_Ty>
inline matrix4x4<t_Ty> operator* (t_Ty scalar, const matrix4x4<t_Ty>& mat);

// v^t_Ty * M
template<class t_Ty>
inline vector4<t_Ty> operator* (const vector4<t_Ty>& vec,
								const matrix4x4<t_Ty>& mat);

o_namespace_end(phantom, math)

#include "quaternion.h"

o_namespace_begin(phantom, math)
#include "matrix4x4.inl"
o_namespace_end(phantom, math)

#endif
