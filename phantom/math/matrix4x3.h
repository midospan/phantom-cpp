#ifndef o_math_matrix4x3_h__
#define o_math_matrix4x3_h__

#include "vector4.h"
#include "vector3.h"

o_declareNT(class, (phantom, math), (typename), (t_Ty), matrix4x3);

o_namespace_begin(phantom, math)

template<class t_Ty>
class matrix4x3
{
public:
    typedef matrix4x3<t_Ty> self_type;
    typedef vector4<t_Ty>   vector4_type;
    typedef vector3<t_Ty>   vector3_type;
    // If makeZero is 'true', create the zero matrix; otherwise, create the
    // identity matrix.
    matrix4x3 ();

    // Copy constructor.
    matrix4x3 (const self_type& mat);

    // Input mrc is in row r, column c.
    matrix4x3 (t_Ty m00, t_Ty m01, t_Ty m02, t_Ty m10, t_Ty m11, t_Ty m12, t_Ty m20, t_Ty m21, t_Ty m22, t_Ty m30, t_Ty m31, t_Ty m32);

    matrix4x3 (const vector4<t_Ty>* v);
    matrix4x3 (const vector3_type* v);
    matrix4x3 (const t_Ty entry[12], bool colMajor);

    // Assignment.
    matrix4x3& operator= (const self_type& mat);

    // Create various matrices.
    void makeZero ();

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
    vector3_type operator* (const vector4<t_Ty>& vec) const;
        
    // Special matrices.
    static const self_type ZERO;

    const vector3_type&    operator[](unsigned int i) const 
    {
        o_assert(i<4);
        return (const vector3_type&)(m[i*3]);
    }

    vector3_type&    operator[](unsigned int i) 
    {
        o_assert(i<4);
        return (vector3_type&)(m[i*3]);
    }

    const t_Ty&       operator()(unsigned int col, unsigned int row) const
    {
        o_assert(col<4 && row<3);
        return m[col*3+row];
    }

    t_Ty&       operator()(unsigned int col, unsigned int row)
    {
        o_assert(col<4 && row<3);
        return m[col*3+row];
    }

public:
    union
    {
        t_Ty m[12];
        t_Ty mm[3][4];
        struct 
        {
            vector3_type ex;
            vector3_type ey;
            vector3_type ez;
            vector3_type ew;
        };
    };
};

// c * M
template<class t_Ty>
inline matrix4x3<t_Ty> operator* (t_Ty scalar, const matrix4x3<t_Ty>& mat);



/** Typedefs **/
typedef matrix4x3<float32> matrix4x3f;
typedef matrix4x3<float64> matrix4x3d;

#include "matrix4x3.inl"

o_namespace_end(phantom, math)

#endif // o_math_matrix4x3_h__
