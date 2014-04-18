#ifndef o_math_matrix4x2_h__
#define o_math_matrix4x2_h__

#include "vector2.h"
#include "vector4.h"

o_declareNT(class, (phantom, math), (typename), (t_Ty), matrix4x2);

o_namespace_begin(phantom, math)

template<class t_Ty>
class matrix4x2
{
public:
    typedef matrix4x2<t_Ty> self_type;
    typedef vector4<t_Ty> vector4_type;
    typedef vector2<t_Ty> vector2_type;

    // If makeZero is 'true', create the zero matrix; otherwise, create the
    // identity matrix.
    matrix4x2 ();

    // Copy constructor.
    matrix4x2 (const self_type& mat);

    // Input mrc is in row r, column c.
    matrix4x2 (t_Ty m00, t_Ty m01, t_Ty m10, t_Ty m11, t_Ty m20, t_Ty m21, t_Ty m30, t_Ty m31);

    matrix4x2 (const vector4<t_Ty>* v);
    matrix4x2 (const vector2_type* v);
    matrix4x2 (const t_Ty entry[8], bool colMajor);

    // Assignment.
    matrix4x2& operator= (const self_type& mat);

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
    vector2_type operator* (const vector4<t_Ty>& vec) const;
        
    // Special matrices.
    static const self_type ZERO;

    const vector2_type&    operator[](unsigned int i) const 
    {
        o_assert(i<4);
        return (const vector2_type&)(m[i*2]);
    }

    vector2_type&    operator[](unsigned int i) 
    {
        o_assert(i<4);
        return (vector2_type&)(m[i*2]);
    }

    const t_Ty&       operator()(unsigned int col, unsigned int row) const
    {
        o_assert(col<4 && row<2);
        return m[col*2+row];
    }

    t_Ty&       operator()(unsigned int col, unsigned int row)
    {
        o_assert(col<4 && row<2);
        return m[col*2+row];
    }

public:
    union
    {
        t_Ty m[8];
        t_Ty mm[2][4];
        struct 
        {
            vector2_type ex;
            vector2_type ey;
            vector2_type ez;
            vector2_type ew;
        };
    };
};

// c * M
template<class t_Ty>
inline matrix4x2<t_Ty> operator* (t_Ty scalar, const matrix4x2<t_Ty>& mat);



/** Typedefs **/
typedef matrix4x2<float32> matrix4x2f;
typedef matrix4x2<float64> matrix4x2d;

#include "matrix4x2.inl"

o_namespace_end(phantom, math)

#endif // o_math_matrix4x2_h__
