#ifndef o_math_matrix3x2_h__
#define o_math_matrix3x2_h__

#include "vector2.h"
#include "vector3.h"

o_declareNT(class, (phantom, math), (typename), (t_Ty), matrix3x2);

o_namespace_begin(phantom, math)

template<class t_Ty>
class matrix3x2
{
public:
    typedef matrix3x2<t_Ty> self_type;
    typedef vector2<t_Ty> vector2_type;
    typedef vector3<t_Ty> vector3_type;
    // If makeZero is 'true', create the zero matrix; otherwise, create the
    // identity matrix.
    matrix3x2 ();

    // Copy constructor.
    matrix3x2 (const self_type& mat);

    // Input mrc is in row r, column c.
    matrix3x2 (t_Ty m00, t_Ty m01, t_Ty m10, t_Ty m11, t_Ty m20, t_Ty m21);

    matrix3x2 (const vector3<t_Ty>* v);
    matrix3x2 (const vector2_type* v);
    matrix3x2 (const t_Ty entry[6], bool colMajor);

    // Assignment.
    matrix3x2& operator= (const self_type& mat);

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
    vector2_type operator* (const vector3<t_Ty>& vec) const;
        
    // Special matrices.
    static const self_type ZERO;

    const vector2_type&    operator[](unsigned int i) const 
    {
        o_assert(i<3);
        return (const vector2_type&)(m[i*2]);
    }

    vector2_type&    operator[](unsigned int i) 
    {
        o_assert(i<3);
        return (vector2_type&)(m[i*2]);
    }

    const t_Ty&       operator()(unsigned int col, unsigned int row) const
    {
        o_assert(col<3 && row<2);
        return m[col*2+row];
    }

    t_Ty&       operator()(unsigned int col, unsigned int row)
    {
        o_assert(col<3 && row<2);
        return m[col*2+row];
    }

public:
    union
    {
        t_Ty m[6];
        t_Ty mm[2][3];
        struct 
        {
            vector2_type ex;
            vector2_type ey;
            vector2_type ez;
        };
    };
};

// c * M
template<class t_Ty>
inline matrix3x2<t_Ty> operator* (t_Ty scalar, const matrix3x2<t_Ty>& mat);

/** Typedefs **/
typedef matrix3x2<float32> matrix3x2f;
typedef matrix3x2<float64> matrix3x2d;

#include "matrix3x2.inl"

o_namespace_end(phantom, math)

#endif // o_math_matrix3x2_h__
