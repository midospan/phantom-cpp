#ifndef o_math_matrix3x3_h__
#define o_math_matrix3x3_h__

// The (x,y,z) coordinate system is assumed to be right-handed.  Coordinate
// axis rotation matrices are of the form
//   RX =    1       0       0
//           0     cos(t) -sin(t)
//           0     sin(t)  cos(t)
// where t > 0 indicates a counterclockwise rotation in the yz-plane
//   RY =  cos(t)    0     sin(t)
//           0       1       0
//        -sin(t)    0     cos(t)
// where t > 0 indicates a counterclockwise rotation in the zx-plane
//   RZ =  cos(t) -sin(t)    0
//         sin(t)  cos(t)    0
//           0       0       1
// where t > 0 indicates a counterclockwise rotation in the xy-plane.

#include "vector3.h"

o_declareNT(class, (phantom, math), (typename), (t_Ty), matrix3x3);

o_namespace_begin(phantom, math)

template<class t_Ty>
class matrix3x3 
{
public:
    typedef matrix3x3<t_Ty> self_type;
    typedef vector3<t_Ty> vector3_type;

	// If makeZero is 'true', create the zero matrix; otherwise, create the
	// identity matrix.
	matrix3x3 (bool makeZero = true);

	// Copy constructor.
	matrix3x3 (const matrix3x3& mat);

	// Input mrc is in row r, column c.
	matrix3x3 (t_Ty m00, t_Ty m01, t_Ty m02, t_Ty m10, t_Ty m11, t_Ty m12,
			t_Ty m20, t_Ty m21, t_Ty m22);

	// Create a matrix from an array of numbers.  The input array is
	// interpreted based on the bool input as
	//   true:  entry[0..8]={m00,m01,m02,m10,m11,m12,m20,m21,m22} [row major]
	//   false: entry[0..8]={m00,m10,m20,m01,m11,m21,m02,m12,m22} [col major]
	matrix3x3 (const t_Ty entry[9], bool rowMajor);

	// Create matrices based on vector input.  The bool is interpreted as
	//   true: vectors are columns of the matrix
	//   false: vectors are rows of the matrix
	matrix3x3 (const vector3_type& u, const vector3_type& v,
			const vector3_type& w, bool columns);
	matrix3x3 (const vector3_type* v, bool columns);

	// Create a diagonal matrix, m01 = m10 = m02 = m20 = m12 = m21 = 0.
	matrix3x3 (t_Ty m00, t_Ty m11, t_Ty m22);

	// Create rotation matrices (positive angle -> counterclockwise).  The
	// angle must be in radians, not degrees.
	matrix3x3 (const vector3_type& axis, t_Ty angle);

	// Create a tensor product U*V^t_Ty.
	matrix3x3 (const vector3_type& u, const vector3_type& v);

	// Assignment.
	self_type& operator= (const self_type& mat);

	// Create various matrices.
	self_type& makeZero ();
	self_type& makeIdentity ();
	self_type& makeDiagonal (t_Ty m00, t_Ty m11, t_Ty m22);
	self_type& makeRotation (const vector3_type& axis, t_Ty angle);
	self_type& makeTensorProduct (const vector3_type& u,
			const vector3_type& v);

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
	vector3_type operator* (const vector3_type& vec) const;

	// u^t_Ty*M*v
	t_Ty qForm (const vector3_type& u, const vector3_type& v) const;

	// M^t_Ty
	self_type transpose () const;

	// M*mat
	self_type operator* (const self_type& mat) const;

	// M^t_Ty*mat
	self_type transposeTimes (const self_type& mat) const;

	// M*mat^t_Ty
	self_type timesTranspose (const self_type& mat) const;

	// M^t_Ty*mat^t_Ty
	self_type transposeTimesTranspose (const self_type& mat) const;

	// Other operations.
	self_type timesDiagonal (const vector3_type& diag) const;  // M*D
	self_type diagonalTimes (const vector3_type& diag) const;  // D*M
	self_type inverse (t_Ty epsilon = (t_Ty)0.0) const;
	self_type adjoint () const;
	t_Ty determinant () const;

	// The matrix must be a rotation for these functions to be valid.  The
	// last function uses Gram-Schmidt orthonormalization applied to the
	// columns of the rotation matrix.  The angle must be in radians, not
	// degrees.
	void extractAxisAngle (vector3_type& axis, t_Ty& angle) const;
	void orthonormalize ();

	// The matrix must be symmetric.  factor M = R * D * R^t_Ty where
	// R = [u0|u1|u2] is a rotation matrix with columns u0, u1, and u2 and
	// D = diag(d0,d1,d2) is a diagonal matrix whose diagonal entries are d0,
	// d1, and d2.  The eigenvector u[i] corresponds to eigenvector d[i].
	// The eigenvalues are ordered as d0 <= d1 <= d2.
	//void eigenDecomposition (self_type& rot, self_type& diag) const;

	// Create rotation matrices from Euler angles.
	void makeEulerXYZ (t_Ty xAngle, t_Ty yAngle, t_Ty zAngle);
	void makeEulerXZY (t_Ty xAngle, t_Ty zAngle, t_Ty yAngle);
	void makeEulerYXZ (t_Ty yAngle, t_Ty xAngle, t_Ty zAngle);
	void makeEulerYZX (t_Ty yAngle, t_Ty zAngle, t_Ty xAngle);
	void makeEulerZXY (t_Ty zAngle, t_Ty xAngle, t_Ty yAngle);
	void makeEulerZYX (t_Ty zAngle, t_Ty yAngle, t_Ty xAngle);
	void makeEulerXYX (t_Ty x0Angle, t_Ty yAngle, t_Ty x1Angle);
	void makeEulerXZX (t_Ty x0Angle, t_Ty zAngle, t_Ty x1Angle);
	void makeEulerYXY (t_Ty y0Angle, t_Ty xAngle, t_Ty y1Angle);
	void makeEulerYZY (t_Ty y0Angle, t_Ty zAngle, t_Ty y1Angle);
	void makeEulerZXZ (t_Ty z0Angle, t_Ty xAngle, t_Ty z1Angle);
	void makeEulerZYZ (t_Ty z0Angle, t_Ty yAngle, t_Ty z1Angle);

	// Extract Euler angles from rotation matrices.
	enum EulerResult
	{
		// The solution is unique.
		EA_UNIQUE,

		// The solution is not unique.  A sum of angles is constant.
		EA_NOT_UNIQUE_SUM,

		// The solution is not unique.  A difference of angles is constant.
		EA_NOT_UNIQUE_DIF
	};

	// The return values are in the specified ranges:
	//   xAngle in [-pi,pi], yAngle in [-pi/2,pi/2], zAngle in [-pi,pi]
	// When the solution is not unique, zAngle = 0 is returned.  Generally,
	// the set of solutions is
	//   EA_NOT_UNIQUE_SUM:  zAngle + xAngle = c
	//   EA_NOT_UNIQUE_DIF:  zAngle - xAngle = c
	// for some angle c.
	EulerResult extractEulerXYZ (t_Ty& xAngle, t_Ty& yAngle, t_Ty& zAngle) const;

	// The return values are in the specified ranges:
	//   xAngle in [-pi,pi], zAngle in [-pi/2,pi/2], yAngle in [-pi,pi]
	// When the solution is not unique, yAngle = 0 is returned.  Generally,
	// the set of solutions is
	//   EA_NOT_UNIQUE_SUM:  yAngle + xAngle = c
	//   EA_NOT_UNIQUE_DIF:  yAngle - xAngle = c
	// for some angle c.
	EulerResult extractEulerXZY (t_Ty& xAngle, t_Ty& zAngle, t_Ty& yAngle) const;

	// The return values are in the specified ranges:
	//   yAngle in [-pi,pi], xAngle in [-pi/2,pi/2], zAngle in [-pi,pi]
	// When the solution is not unique, zAngle = 0 is returned.  Generally,
	// the set of solutions is
	//   EA_NOT_UNIQUE_SUM:  zAngle + yAngle = c
	//   EA_NOT_UNIQUE_DIF:  zAngle - yAngle = c
	// for some angle c.
	EulerResult extractEulerYXZ (t_Ty& yAngle, t_Ty& xAngle, t_Ty& zAngle) const;

	// The return values are in the specified ranges:
	//   yAngle in [-pi,pi], zAngle in [-pi/2,pi/2], xAngle in [-pi,pi]
	// When the solution is not unique, xAngle = 0 is returned.  Generally,
	// the set of solutions is
	//   EA_NOT_UNIQUE_SUM:  xAngle + yAngle = c
	//   EA_NOT_UNIQUE_DIF:  xAngle - yAngle = c
	// for some angle c.
	EulerResult extractEulerYZX (t_Ty& yAngle, t_Ty& zAngle, t_Ty& xAngle) const;

	// The return values are in the specified ranges:
	//   zAngle in [-pi,pi], xAngle in [-pi/2,pi/2], yAngle in [-pi,pi]
	// When the solution is not unique, yAngle = 0 is returned.  Generally,
	// the set of solutions is
	//   EA_NOT_UNIQUE_SUM:  yAngle + zAngle = c
	//   EA_NOT_UNIQUE_DIF:  yAngle - zAngle = c
	// for some angle c.
	EulerResult extractEulerZXY (t_Ty& zAngle, t_Ty& xAngle, t_Ty& yAngle) const;

	// The return values are in the specified ranges:
	//   zAngle in [-pi,pi], yAngle in [-pi/2,pi/2], xAngle in [-pi,pi]
	// When the solution is not unique, xAngle = 0 is/ returned.  Generally,
	// the set of solutions is
	//   EA_NOT_UNIQUE_SUM:  xAngle + zAngle = c
	//   EA_NOT_UNIQUE_DIF:  xAngle - zAngle = c
	// for some angle c.
	EulerResult extractEulerZYX (t_Ty& zAngle, t_Ty& yAngle, t_Ty& xAngle) const;

	// The return values are in the specified ranges:
	//   x0Angle in [-pi,pi], yAngle in [0,pi], x1Angle in [-pi,pi]
	// When the solution is not unique, x1Angle = 0 is returned.  Generally,
	// the set of solutions is
	//   EA_NOT_UNIQUE_SUM:  x1Angle + x0Angle = c
	//   EA_NOT_UNIQUE_DIF:  x1Angle - x0Angle = c
	// for some angle c.
	EulerResult extractEulerXYX (t_Ty& x0Angle, t_Ty& yAngle, t_Ty& x1Angle) const;

	// The return values are in the specified ranges:
	//   x0Angle in [-pi,pi], zAngle in [0,pi], x1Angle in [-pi,pi]
	// When the solution is not unique, x1Angle = 0 is returned.  Generally,
	// the set of solutions is
	//   EA_NOT_UNIQUE_SUM:  x1Angle + x0Angle = c
	//   EA_NOT_UNIQUE_DIF:  x1Angle - x0Angle = c
	// for some angle c.
	EulerResult extractEulerXZX (t_Ty& x0Angle, t_Ty& zAngle, t_Ty& x1Angle) const;

	// The return values are in the specified ranges:
	//   y0Angle in [-pi,pi], xAngle in [0,pi], y1Angle in [-pi,pi]
	// When the solution is not unique, y1Angle = 0 is returned.  Generally,
	// the set of solutions is
	//   EA_NOT_UNIQUE_SUM:  y1Angle + y0Angle = c
	//   EA_NOT_UNIQUE_DIF:  y1Angle - y0Angle = c
	// for some angle c.
	EulerResult extractEulerYXY (t_Ty& y0Angle, t_Ty& xAngle, t_Ty& y1Angle) const;

	// The return values are in the specified ranges:
	//   y0Angle in [-pi,pi], zAngle in [0,pi], y1Angle in [-pi,pi]
	// When the solution is not unique, y1Angle = 0 is returned.  Generally,
	// the set of solutions is
	//   EA_NOT_UNIQUE_SUM:  y1Angle + y0Angle = c
	//   EA_NOT_UNIQUE_DIF:  y1Angle - y0Angle = c
	// for some angle c.
	EulerResult extractEulerYZY (t_Ty& y0Angle, t_Ty& zAngle, t_Ty& y1Angle) const;

	// The return values are in the specified ranges:
	//   z0Angle in [-pi,pi], xAngle in [0,pi], z1Angle in [-pi,pi]
	// When the solution is not unique, z1Angle = 0 is returned.  Generally,
	// the set of solutions is
	//   EA_NOT_UNIQUE_SUM:  z1Angle + z0Angle = c
	//   EA_NOT_UNIQUE_DIF:  z1Angle - z0Angle = c
	// for some angle c.
	EulerResult extractEulerZXZ (t_Ty& z0Angle, t_Ty& xAngle, t_Ty& z1Angle) const;

	// The return values are in the specified ranges:
	//   z0Angle in [-pi,pi], yAngle in [0,pi], z1Angle in [-pi,pi]
	// When the solution is not unique, z1Angle = 0 is returned.  Generally,
	// the set of solutions is
	//   EA_NOT_UNIQUE_SUM:  z1Angle + z0Angle = c
	//   EA_NOT_UNIQUE_DIF:  z1Angle - z0Angle = c
	// for some angle c.
	EulerResult extractEulerZYZ (t_Ty& z0Angle, t_Ty& yAngle, t_Ty& z1Angle) const;

	// SLERP (spherical linear interpolation) without quaternions.  Computes
	// R(t) = R0*(transpose(R0)*R1)^t.  If Q is a rotation matrix with
	// unit-length axis U and angle A, then Q^t is a rotation matrix with
	// unit-length axis U and rotation angle t*A.
	self_type& slerp (t_Ty t, const self_type& rot0, const matrix3x3& rot1);

	/*// Singular value decomposition, M = L*D*transpose(R), where L and R are
	// orthogonal and D is a diagonal matrix whose diagonal entries are
	// nonnegative.
	void singularValueDecomposition (self_type& left, self_type& diag,
	self_type& rightTranspose) const;*/

	// Polar decomposition, M = Q*S, where Q is orthogonal and S is symmetric.
	// This uses the singular value decomposition:
	//   M = L*D*transpose(R) = (L*transpose(R))*(R*D*transpose(R)) = Q*S
	// where Q = L*transpose(R) and S = R*D*transpose(R).
	//void polarDecomposition (self_type& qMat, self_type& sMat);

	// factor M = Q*D*U with orthogonal Q, diagonal D, upper triangular U.
	//void qduDecomposition (self_type& qMat, self_type& diag, matrix3x3& uMat)
	//    const;

	// Special matrices.
	static const self_type ZERO;
	static const self_type IDENTITY;

	const vector3_type& operator[](unsigned int i) const 
	{
		o_assert(i<3);
		return (const vector3_type&)(m[i*3]);
	}

	vector3_type& operator[](unsigned int i) 
	{
		o_assert(i<3);
		return (vector3_type&)(m[i*3]);
	}

	const t_Ty& operator()(unsigned int col, unsigned int row) const
	{
		o_assert(col<3 && row<3);
		return m[col*3+row];
	}

	t_Ty& operator()(unsigned int col, unsigned int row)
	{
		o_assert(col<3 && row<3);
		return m[col*3+row];
	}

	bool operator==(const self_type& other) const 
	{
		return memcmp(m, other.m, sizeof(m)) != 0;
	}

	bool operator!=(const self_type& other) const 
	{
		return memcmp(m, other.m, sizeof(m)) == 0;
	}

private:
	// Support for eigendecomposition.  The tridiagonalize function applies
	// a Householder transformation to the matrix.  If that transformation
	// is the identity (the matrix is already tridiagonal), then the return
	// value is 'false'.  Otherwise, the transformation is a reflection and
	// the return value is 'true'.  The qlAlgorithm returns 'true' iff the
	// QL iteration scheme converged.
	//bool tridiagonalize (t_Ty diagonal[3], t_Ty subdiagonal[2]);
	//bool qlAlgorithm (t_Ty diagonal[3], t_Ty subdiagonal[2]);

public:
	union
	{
		t_Ty m[9];
        t_Ty mm[3][3];
        struct 
        {
            vector3_type ex;
            vector3_type ey;
            vector3_type ez;
        };
	};
};

// c * M
template<class t_Ty>
inline matrix3x3<t_Ty> operator* (t_Ty scalar, const matrix3x3<t_Ty>& mat);

// v^t_Ty * M
template<class t_Ty>
inline vector3<t_Ty> operator* (const vector3<t_Ty>& vec, const matrix3x3<t_Ty>& mat);

/** Typedefs **/
typedef matrix3x3<float32> matrix3x3f;
typedef matrix3x3<float64> matrix3x3d;

#include "matrix3x3.inl"

o_namespace_end(phantom, math)

#endif // o_math_matrix3x3_h__
