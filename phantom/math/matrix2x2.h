#ifndef o_math_matrix2x2
#define o_math_matrix2x2

// Rotation matrices are of the form
//   R = cos(t) -sin(t)
//       sin(t)  cos(t)
// where t > 0 indicates a counterclockwise rotation in the xy-plane.

#include "vector2.h"

o_declareNT(class, (phantom, math), (typename), (t_Ty), matrix2x2);

o_namespace_begin(phantom, math)

template<class t_Ty>
class matrix2x2
{
public:
    typedef matrix2x2<t_Ty> self_type;
    typedef vector2<t_Ty> vector2_type;

	// If makeZero is 'true', create the zero matrix; otherwise, create the
	// identity matrix.
	matrix2x2 (bool makeZero = true);

	// Copy constructor.
	matrix2x2 (const self_type& mat);

	// Input mrc is in row r, column c.
	matrix2x2 (t_Ty m00, t_Ty m01, t_Ty m10, t_Ty m11);

	// Create a matrix from an array of numbers.  The input array is
	// interpreted based on the bool input as
	//   true:  entry[0..3] = {m00,m01,m10,m11}  [row major]
	//   false: entry[0..3] = {m00,m10,m01,m11}  [column major]
	matrix2x2 (const t_Ty entry[4], bool rowMajor);

	// Create matrices based on vector input.  The bool is interpreted as
	//   true: vectors are columns of the matrix
	//   false: vectors are rows of the matrix
	matrix2x2 (const vector2_type& u, const vector2_type& v, bool columns);

	matrix2x2 (const vector2_type* vectors, bool columns);

	// Create a diagonal matrix, m01 = m10 = 0.
	matrix2x2 (t_Ty m00, t_Ty m11);

	// Create a rotation matrix (positive angle -> counterclockwise).
	matrix2x2 (t_Ty angle);

	// Create a tensor product U*V^t_Ty.
	matrix2x2 (const vector2_type& u, const vector2_type& v);

	// Assignment.
	matrix2x2& operator= (const self_type& mat);

	// Create various matrices.
	void makeZero ();
	void makeIdentity ();
	void makeDiagonal (t_Ty m00, t_Ty m11);
	void makeRotation (t_Ty angle);
	void makeTensorProduct (const vector2_type& u, const vector2_type& v);

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
	vector2_type operator* (const vector2_type& vec) const;

	// u^t_Ty*M*v
	t_Ty qForm (const vector2_type& u, const vector2_type& v) const;

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
	self_type inverse (t_Ty epsilon = (t_Ty)0) const;
	self_type adjoint () const;
	t_Ty determinant () const;

	// The matrix must be a rotation for these functions to be valid.  The
	// last function uses Gram-Schmidt orthonormalization applied to the
	// columns of the rotation matrix.  The angle must be in radians, not
	// degrees.
	void extractAngle (t_Ty& angle) const;
	void orthonormalize ();

	// The matrix must be symmetric.  factor M = R * D * R^t_Ty where
	// R = [u0|u1] is a rotation matrix with columns u0 and u1 and
	// D = diag(d0,d1) is a diagonal matrix whose diagonal entries are d0
	// and d1.  The eigenvector u[i] corresponds to eigenvector d[i].  The
	// eigenvalues are ordered as d0 <= d1.
	void eigenDecomposition (self_type& rot, self_type& diag) const;

	// Special matrices.
	static const self_type ZERO;
	static const self_type IDENTITY;

	const vector2_type&    operator[](unsigned int i) const 
	{
		o_assert(i<2);
		return (const vector2_type&)(m[i*2]);
	}

	vector2_type&    operator[](unsigned int i) 
	{
		o_assert(i<2);
		return (vector2_type&)(m[i*2]);
	}

	const t_Ty&       operator()(unsigned int col, unsigned int row) const
	{
		o_assert(col<2 && row<2);
		return m[col*2+row];
	}

	t_Ty&       operator()(unsigned int col, unsigned int row)
	{
		o_assert(col<2 && row<2);
		return m[col*2+row];
    }

    bool operator==(const self_type& other) const 
    {
        return memcmp(m, other.m, sizeof(m)) != 0;
    }

    bool operator!=(const self_type& other) const 
    {
        return memcmp(m, other.m, sizeof(m)) == 0;
    }

public:
	union
	{
        t_Ty m[4];
        t_Ty mm[2][2];
        struct 
        {
            vector2_type ex;
            vector2_type ey;
        };
	};
};

// c * M
template<class t_Ty>
inline matrix2x2<t_Ty> operator* (t_Ty scalar, const matrix2x2<t_Ty>& mat);

// v^t_Ty * M
template<class t_Ty>
inline vector2<t_Ty> operator* (const vector2<t_Ty>& vec, const matrix2x2<t_Ty>& mat);
	
	
/** Typedefs **/
typedef matrix2x2<float32> Matrix2f;
typedef matrix2x2<float64> Matrix2d;

#include "matrix2x2.inl"

o_namespace_end(phantom, math)

#endif
