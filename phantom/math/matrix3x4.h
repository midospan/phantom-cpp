#ifndef o_math_matrix3x4_h__
#define o_math_matrix3x4_h__

#include "vector3.h"
#include "vector4.h"

o_declareNT(class, (phantom, math), (typename), (t_Ty), matrix3x4);

o_namespace_begin(phantom, math)

template<class t_Ty>
class matrix3x4
{
public:
    typedef matrix3x4<t_Ty> self_type;
    typedef vector4<t_Ty> vector4_type;

    // If makeZero is 'true', create the zero matrix; otherwise, create the
    // identity matrix.
    matrix3x4 ();

    // Copy constructor.
    matrix3x4 (const self_type& mat);

    // Input mrc is in row r, column c.
    matrix3x4 (t_Ty m00, t_Ty m01, t_Ty m02, t_Ty m03, t_Ty m10, t_Ty m11, t_Ty m12, t_Ty m13, t_Ty m20, t_Ty m21, t_Ty m22, t_Ty m23);

    matrix3x4 (const vector4_type* v);
    matrix3x4 (const vector3<t_Ty>* v);
    matrix3x4 (const t_Ty entry[6], bool colMajor);

    // Assignment.
    matrix3x4& operator= (const self_type& mat);

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
    vector4_type operator* (const vector3<t_Ty>& vec) const;
        
    // Special matrices.
    static const self_type ZERO;

    const vector3<t_Ty>&    operator[](unsigned int i) const 
    {
        o_assert(i<3);
        return (const vector4_type&)(m[i*4]);
    }

    vector3<t_Ty>&    operator[](unsigned int i) 
    {
        o_assert(i<3);
        return (vector3<t_Ty>&)(m[i*4]);
    }

    const t_Ty&       operator()(unsigned int col, unsigned int row) const
    {
        o_assert(col<3 && row<4);
        return m[col*4+row];
    }

    t_Ty&       operator()(unsigned int col, unsigned int row)
    {
        o_assert(col<3 && row<4);
        return m[col*4+row];
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
        t_Ty m[12];
        t_Ty mm[4][3];
        struct 
        {
            vector4_type ex;
            vector4_type ey;
            vector4_type ez;
        };
    };
};

// c * M
template<class t_Ty>
inline matrix3x4<t_Ty> operator* (t_Ty scalar, const matrix3x4<t_Ty>& mat);



/** Typedefs **/
typedef matrix3x4<float32> matrix3x4f;
typedef matrix3x4<float64> matrix3x4d;

#include "matrix3x4.inl"

o_namespace_end(phantom, math)

#endif
