#ifndef o_math_matrix2x4_h__
#define o_math_matrix2x4_h__

#include "vector2.h"
#include "vector4.h"

o_declareNT(class, (phantom, math), (typename), (t_Ty), matrix2x4);

o_namespace_begin(phantom, math)

template<class t_Ty>
class matrix2x4
{
public:
    typedef matrix2x4<t_Ty> self_type;
    typedef vector4<t_Ty> vector4_type;
    typedef vector2<t_Ty> vector2_type;

    // If makeZero is 'true', create the zero matrix; otherwise, create the
    // identity matrix.
    matrix2x4 ();

    // Copy constructor.
    matrix2x4 (const self_type& mat);

    // Input mrc is in row r, column c.
    matrix2x4 (t_Ty m00, t_Ty m01, t_Ty m02, t_Ty m03, t_Ty m10, t_Ty m11, t_Ty m12, t_Ty m13);

    matrix2x4 (const vector4_type* v);
    matrix2x4 (const vector2_type* v);
    matrix2x4 (const t_Ty entry[8], bool colMajor);

    // Assignment.
    matrix2x4& operator= (const self_type& mat);

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
    vector4_type operator* (const vector2_type& vec) const;
        
    // Special matrices.
    static const self_type ZERO;

    const vector4_type&    operator[](unsigned int i) const 
    {
        o_assert(i<2);
        return (const vector4_type&)(m[i*4]);
    }

    vector4_type&    operator[](unsigned int i) 
    {
        o_assert(i<2);
        return (vector4_type&)(m[i*4]);
    }

    const t_Ty&       operator()(unsigned int col, unsigned int row) const
    {
        o_assert(col<2 && row<4);
        return m[col*4+row];
    }

    t_Ty&       operator()(unsigned int col, unsigned int row)
    {
        o_assert(col<2 && row<4);
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
        t_Ty m[8];
        t_Ty mm[4][2];
        struct 
        {
            vector4_type ex;
            vector4_type ey;
        };
    };
};

// c * M
template<class t_Ty>
inline matrix2x4<t_Ty> operator* (t_Ty scalar, const matrix2x4<t_Ty>& mat);

/** Typedefs **/
typedef matrix2x4<float32> matrix2x4f;
typedef matrix2x4<float64> matrix2x4d;

#include "matrix2x4.inl"

o_namespace_end(phantom, math)

#endif // o_math_matrix2x4_h__
