#ifndef o_math_matrix2x2_h__
#define o_math_matrix2x2_h__

o_declareNT(struct, (phantom, math), (typename), (t_Ty), matrix2x2);

o_namespace_begin(phantom, math)
    
/// A 2-by-2 matrix. Stored in column-major order.
template<typename t_Ty>
struct matrix2x2 
{
    typedef matrix2x2<t_Ty> self_type;
    typedef vector2<t_Ty>   vector2_type;

    /// The default constructor does nothing (for performance).
    matrix2x2() {}

    /// Construct this matrix using columns.
    matrix2x2(const vector2_type& c1, const vector2_type& c2)
    {
        ex = c1;
        ey = c2;
    }

    /// Construct this matrix using scalars.
    matrix2x2(t_Ty a11, t_Ty a12, t_Ty a21, t_Ty a22)
    {
        ex.x = a11; ex.y = a21;
        ey.x = a12; ey.y = a22;
    }

    /// Initialize this matrix using columns.
    void set(const vector2_type& c1, const vector2_type& c2)
    {
        ex = c1;
        ey = c2;
    }

    /// Set this to the identity matrix.
    void setIdentity()
    {
        ex.x = 1.0f; ey.x = 0.0f;
        ex.y = 0.0f; ey.y = 1.0f;
    }

    o_forceinline static self_type const&  Zero() 
    { 
        static self_type VALUE(t_Ty(0),t_Ty(0),t_Ty(0),t_Ty(0)); 
        return VALUE; 
    }
    o_forceinline static self_type const&  Identity() 
    { 
        static self_type VALUE(t_Ty(1),t_Ty(0),t_Ty(0),t_Ty(1)); 
        return VALUE; 
    }

    /// Set this matrix to all zeros.
    void setZero()
    {
        ex.x = 0.0f; ey.x = 0.0f;
        ex.y = 0.0f; ey.y = 0.0f;
    }

    self_type getInverse() const
    {
        t_Ty a = ex.x, b = ey.x, c = ex.y, d = ey.y;
        self_type B;
        t_Ty det = a * d - b * c;
        if (det != 0.0f)
        {
            det = 1.0f / det;
        }
        B.ex.x =  det * d;	B.ey.x = -det * b;
        B.ex.y = -det * c;	B.ey.y =  det * a;
        return B;
    }

    /// Solve A * x = b, where b is a column vector. This is more efficient
    /// than computing the inverse in one-shot cases.
    vector2_type solve(const vector2_type& b) const
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

    vector2_type    operator*(const vector2_type& v) const
    {
        return vector2_type(ex.x * v.x + ey.x * v.y, ex.y * v.x + ey.y * v.y);
    }

    o_forceinline bool operator == (const self_type& v)
    {
        return memcmp(v.a, a, sizeof(t_Ty)*4) == 0;
    }

    o_forceinline self_type operator + (const self_type& A)
    {
        return self_type(A.ex + ex, A.ey + ey);
    }

    union
    {
        // Array version
        t_Ty   m[4];
        t_Ty   mm[2][2];

        // 2 vector2 version
        struct
        {
            vector2_type ex;
            vector2_type ey;
        };
    };
};

typedef matrix2x2<float32> matrix2x2f;
typedef matrix2x2<float64> matrix2x2d;

o_namespace_end(phantom, math)

o_namespace_begin(phantom, extension, detail)

template<typename t_Ty>
struct safe_constructor_ <math::matrix2x2<t_Ty>>
{
    static void safeConstruct(void* a_pInstance) 
    { 
        *((math::matrix2x2<t_Ty>*)a_pInstance) = math::matrix2x2<t_Ty>::Identity();
    }
};

o_namespace_end(phantom, extension, detail)

#endif // phantom_math_matrix2x2_h__
