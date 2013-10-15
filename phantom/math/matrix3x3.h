#ifndef phantom_math_matrix3x3_h__
#define phantom_math_matrix3x3_h__


o_namespace_begin(phantom, math)

template<typename t_Ty>
struct matrix3x3_default_base
{
    typedef vector2<t_Ty>                       vector2_type;
    typedef vector3<t_Ty>                       vector3_type;
    matrix3x3_default_base() {}
    
};


    /** \addtogroup Core
*  @{
*/
/** \addtogroup Math
*  @{
*/
/** A 3x3 matrix which can represent rotations around axes.
    @note
        <b>All the code is adapted from the Ogre and Wild Magic Matrix
        library (http://www.ogre3d.org/ ) and (http://www.geometrictools.com/).</b>
    @par
        The coordinate system is assumed to be <b>right-handed</b>.
*/
template<typename t_Ty>
struct matrix3x3 
{
    typedef matrix3x3<t_Ty> self_type;
    typedef vector2<t_Ty>   vector2_type;
    typedef vector3<t_Ty>   vector3_type;
    /** Default constructor.
        @note
            It does <b>NOT</b> initialize the matrix for efficiency.
    */
	inline matrix3x3 () {}
    inline explicit matrix3x3 (const t_Ty arr[3][3])
	{
		memcpy(m,arr,9*sizeof(t_Ty));
	}
    inline matrix3x3 (const self_type& rkMatrix)
	{
		memcpy(m,rkMatrix.m,9*sizeof(t_Ty));
	}
    inline matrix3x3 (t_Ty fEntry00, t_Ty fEntry01, t_Ty fEntry02,
                t_Ty fEntry10, t_Ty fEntry11, t_Ty fEntry12,
                t_Ty fEntry20, t_Ty fEntry21, t_Ty fEntry22)
	{
		m[0][0] = fEntry00;
		m[0][1] = fEntry01;
		m[0][2] = fEntry02;
		m[1][0] = fEntry10;
		m[1][1] = fEntry11;
		m[1][2] = fEntry12;
		m[2][0] = fEntry20;
		m[2][1] = fEntry21;
		m[2][2] = fEntry22;
	}

	/** Exchange the contents of this matrix with another. 
	*/
	inline void swap(self_type& other)
	{
		std::swap(m[0][0], other.m[0][0]);
		std::swap(m[0][1], other.m[0][1]);
		std::swap(m[0][2], other.m[0][2]);
		std::swap(m[1][0], other.m[1][0]);
		std::swap(m[1][1], other.m[1][1]);
		std::swap(m[1][2], other.m[1][2]);
		std::swap(m[2][0], other.m[2][0]);
		std::swap(m[2][1], other.m[2][1]);
		std::swap(m[2][2], other.m[2][2]);
    }

    /// Set this matrix to all zeros.
    void setZero()
    {
        ex.setZero();
        ey.setZero();
        ez.setZero();
    }

    // member access, allows use of construct mat[r][c]
    inline t_Ty* operator[] (size_t iRow) const
	{
		return (t_Ty*)m[iRow];
	}
    /*inline operator t_Ty* ()
	{
		return (t_Ty*)m[0];
	}*/
    inline vector3_type getColumn (size_t iCol) const;
    inline void setColumn(size_t iCol, const vector3_type& vec);
    inline void fromAxes(const vector3_type& xAxis, const vector3_type& yAxis, const vector3_type& zAxis);

    // assignment and comparison
    inline self_type& operator= (const self_type& rkMatrix)
	{
		memcpy(m,rkMatrix.m,9*sizeof(t_Ty));
		return *this;
	}
    inline bool operator== (const self_type& rkMatrix) const;
    inline bool operator!= (const self_type& rkMatrix) const
	{
		return !operator==(rkMatrix);
	}

    // arithmetic operations
    inline self_type operator+ (const self_type& rkMatrix) const;
    inline self_type operator- (const self_type& rkMatrix) const;
    inline self_type operator* (const self_type& rkMatrix) const;
    inline self_type operator- () const;

    // matrix * vector [3x3 * 3x1 = 3x1]
    inline vector2_type operator* (const vector2_type& rkVector) const;
    inline vector3_type operator* (const vector3_type& rkVector) const;

    // vector * matrix [1x3 * 3x3 = 1x3]
    o_export friend vector3_type operator* (const vector3_type& rkVector,
        const self_type& rkMatrix);

    // matrix * scalar
    inline self_type operator* (t_Ty fScalar) const;

    // scalar * matrix
    o_export friend self_type operator* (t_Ty fScalar, const self_type& rkMatrix);

    // utilities
    inline self_type transpose () const;
    inline bool inverse (self_type& rkInverse, t_Ty fTolerance = 1e-06) const;
    inline self_type inverse (t_Ty fTolerance = 1e-06) const;
    inline t_Ty determinant () const;

    // singular value decomposition
    inline void singularValueDecomposition (self_type& rkL, vector3_type& rkS,
        self_type& rkR) const;
    inline void singularValueComposition (const self_type& rkL,
        const vector3_type& rkS, const self_type& rkR);

    // Gram-Schmidt orthonormalization (applied to columns of rotation matrix)
    inline void orthonormalize ();

    // orthogonal Q, diagonal D, upper triangular U stored as (u01,u02,u12)
    inline void qduDecomposition (self_type& rkQ, vector3_type& rkD,
        vector3_type& rkU) const;

    inline t_Ty spectralNorm () const;

    // matrix must be orthonormal
    inline void toAngleAxis (vector3_type& rkAxis, t_Ty& rfAngle) const;

    inline void fromAngleAxis (const vector3_type& rkAxis, const t_Ty& fRadians);

    // The matrix must be orthonormal.  The decomposition is yaw*pitch*roll
    // where yaw is rotation about the Up vector, pitch is rotation about the
    // Right axis, and roll is rotation about the Direction axis.
    inline bool toEulerAnglesXYZ (t_Ty& rfYAngle, t_Ty& rfPAngle,
        t_Ty& rfRAngle) const;
    inline bool toEulerAnglesXZY (t_Ty& rfYAngle, t_Ty& rfPAngle,
        t_Ty& rfRAngle) const;
    inline bool toEulerAnglesYXZ (t_Ty& rfYAngle, t_Ty& rfPAngle,
        t_Ty& rfRAngle) const;
    inline bool toEulerAnglesYZX (t_Ty& rfYAngle, t_Ty& rfPAngle,
        t_Ty& rfRAngle) const;
    inline bool toEulerAnglesZXY (t_Ty& rfYAngle, t_Ty& rfPAngle,
        t_Ty& rfRAngle) const;
    inline bool toEulerAnglesZYX (t_Ty& rfYAngle, t_Ty& rfPAngle,
        t_Ty& rfRAngle) const;
    inline void fromEulerAnglesXYZ (const t_Ty& fYAngle, const t_Ty& fPAngle, const t_Ty& fRAngle);
    inline void fromEulerAnglesXZY (const t_Ty& fYAngle, const t_Ty& fPAngle, const t_Ty& fRAngle);
    inline void fromEulerAnglesYXZ (const t_Ty& fYAngle, const t_Ty& fPAngle, const t_Ty& fRAngle);
    inline void fromEulerAnglesYZX (const t_Ty& fYAngle, const t_Ty& fPAngle, const t_Ty& fRAngle);
    inline void fromEulerAnglesZXY (const t_Ty& fYAngle, const t_Ty& fPAngle, const t_Ty& fRAngle);
    inline void fromEulerAnglesZYX (const t_Ty& fYAngle, const t_Ty& fPAngle, const t_Ty& fRAngle);
    // eigensolver, matrix must be symmetric
    inline void eigenSolveSymmetric (t_Ty afEigenvalue[3],
        vector3_type akEigenvector[3]) const;


    /// Solve A * x = b, where b is a column vector. This is more efficient
    /// than computing the inverse in one-shot cases.
    inline vector3_type solve33(const vector3_type& b) const
    {
        t_Ty det = ex.dot(ey.cross(ez));
        if (det != 0.0f)
        {
            det = 1.0f / det;
        }
        vector3_type x;
        x.x = det * b.dot(ey.cross(ez));
        x.y = det * ex.dot(b.cross(ez));
        x.z = det * ex.dot(ey.cross(b));
        return x;
    }

    /// Solve A * x = b, where b is a column vector. This is more efficient
    /// than computing the inverse in one-shot cases.
    vector2_type solve22(const vector2_type& b) const
    {
        t_Ty a11 = ex.x, a12 = ey.x, a21 = ex.y, a22 = ey.y;
        t_Ty det = a11 * a22 - a12 * a21;
        if (det != 0.0f)
        {
            det = 1.0f / det;
        }
        vector2_type x;
        x.x = det * (a22 * b.x - a12 * b.y);
        x.y = det * (a11 * b.y - a21 * b.x);
        return x;
    }

    ///
    void getInverse22(self_type* M) const
    {
        t_Ty a = ex.x, b = ey.x, c = ex.y, d = ey.y;
        t_Ty det = a * d - b * c;
        if (det != 0.0f)
        {
            det = 1.0f / det;
        }

        M->ex.x =  det * d;	M->ey.x = -det * b; M->ex.z = 0.0f;
        M->ex.y = -det * c;	M->ey.y =  det * a; M->ey.z = 0.0f;
        M->ez.x = 0.0f; M->ez.y = 0.0f; M->ez.z = 0.0f;
    }

    /// Returns the zero matrix if singular.
    void getSymInverse33(self_type* M) const
    {
        t_Ty det = ex.dot(ey.cross(ez));
        if (det != 0.0f)
        {
            det = 1.0f / det;
        }

        t_Ty a11 = ex.x, a12 = ey.x, a13 = ez.x;
        t_Ty a22 = ey.y, a23 = ez.y;
        t_Ty a33 = ez.z;

        M->ex.x = det * (a22 * a33 - a23 * a23);
        M->ex.y = det * (a13 * a23 - a12 * a33);
        M->ex.z = det * (a12 * a23 - a13 * a22);

        M->ey.x = M->ex.y;
        M->ey.y = det * (a11 * a33 - a13 * a13);
        M->ey.z = det * (a13 * a12 - a11 * a23);

        M->ez.x = M->ex.z;
        M->ez.y = M->ey.z;
        M->ez.z = det * (a11 * a22 - a12 * a12);
    }


    static void tensorProduct (const vector3_type& rkU, const vector3_type& rkV,
        self_type& rkProduct);

	/** Determines if this matrix involves a scaling. */
	inline bool hasScale() const
	{
		// check magnitude of column vectors (==local axes)
		t_Ty t = m[0][0] * m[0][0] + m[1][0] * m[1][0] + m[2][0] * m[2][0];
		if (!math::equalsEpsilon<t_Ty>(t, 1.0, (t_Ty)1e-04))
			return true;
		t = m[0][1] * m[0][1] + m[1][1] * m[1][1] + m[2][1] * m[2][1];
		if (!math::equalsEpsilon<t_Ty>(t, 1.0, (t_Ty)1e-04))
			return true;
		t = m[0][2] * m[0][2] + m[1][2] * m[1][2] + m[2][2] * m[2][2];
		if (!math::equalsEpsilon<t_Ty>(t, 1.0, (t_Ty)1e-04))
			return true;

		return false;
	}

	/** Function for writing to a stream.
	*/
	inline o_export friend std::ostream& operator <<
		( std::ostream& o, const self_type& mat )
	{
		o << "matrix3x3(" << mat[0][0] << ", " << mat[0][1] << ", " << mat[0][2] << ", " 
                        << mat[1][0] << ", " << mat[1][1] << ", " << mat[1][2] << ", " 
                        << mat[2][0] << ", " << mat[2][1] << ", " << mat[2][2] << ")";
		return o;
	}

    o_forceinline static self_type const&  Zero() 
    { 
        static self_type VALUE(t_Ty(0),t_Ty(0),t_Ty(0),t_Ty(0),t_Ty(0),t_Ty(0),t_Ty(0),t_Ty(0),t_Ty(0)); 
        return VALUE; 
    }
    o_forceinline static self_type const&  Identity() 
    { 
        static self_type VALUE(t_Ty(1),t_Ty(0),t_Ty(0),t_Ty(0),t_Ty(1),t_Ty(0),t_Ty(0),t_Ty(0),t_Ty(1)); 
        return VALUE; 
    }

protected:
    // support for eigensolver
    void tridiagonal (t_Ty afDiag[3], t_Ty afSubDiag[3]);
    bool qlAlgorithm (t_Ty afDiag[3], t_Ty afSubDiag[3]);

    // support for singular value decomposition
    static const t_Ty msSvdEpsilon;
    static const unsigned int msSvdMaxIterations;
    static void bidiagonalize (self_type& kA, self_type& kL,
        self_type& kR);
    static void golubKahanStep (self_type& kA, self_type& kL,
        self_type& kR);

    // support for spectral norm
    static t_Ty maxCubicRoot (t_Ty afCoeff[3]);
        
    // for faster access
    friend class Matrix4;

public:
    union
    {
        // Array versions
        t_Ty   a[9];
        t_Ty   m[3][3];

        // 2 vector2 version
        struct
        {
            vector3_type ex;
            vector3_type ey;
            vector3_type ez;
        };
    };
};
/** @} */
/** @} */

o_namespace_end(phantom, math)

o_namespace_begin(phantom, extension, detail)

template<typename t_Ty>
struct safe_constructor_ <math::matrix3x3<t_Ty>>
{
    static void safeConstruct(void* a_pInstance) 
    { 
        *((math::matrix3x3<t_Ty>*)a_pInstance) = math::matrix3x3<t_Ty>::Identity();
    }
};

o_namespace_end(phantom, extension, detail)


#include "matrix3x3.inl"

#endif // phantom_math_matrix3x3_h__
