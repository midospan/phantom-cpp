#ifndef o_math_matrix2x3
#define o_math_matrix2x3

#include "vector2.h"
#include "vector3.h"

o_declareNT(class, (phantom, math), (typename), (t_Ty), matrix2x3);

o_namespace_begin(phantom, math)

template<class t_Ty>
class matrix2x3
{
public:
    typedef matrix2x3<t_Ty> self_type;
    typedef vector3<t_Ty> vector3_type;

    // If makeZero is 'true', create the zero matrix; otherwise, create the
    // identity matrix.
    matrix2x3 ();

    // Copy constructor.
    matrix2x3 (const self_type& mat);

    // Input mrc is in row r, column c.
    matrix2x3 (t_Ty m00, t_Ty m01, t_Ty m02, t_Ty m10, t_Ty m11, t_Ty m12);

    matrix2x3 (const vector3_type* v);
    matrix2x3 (const vector2<t_Ty>* v);
    matrix2x3 (const t_Ty entry[6], bool colMajor);

    // Assignment.
    matrix2x3& operator= (const self_type& mat);

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
    vector3_type operator* (const vector2<t_Ty>& vec) const;
        
    // Special matrices.
    static const self_type ZERO;

    const vector3_type&    operator[](unsigned int i) const 
    {
        o_assert(i<2);
        return (const vector3_type&)(m[i*3]);
    }

    vector3_type&    operator[](unsigned int i) 
    {
        o_assert(i<2);
        return (vector3_type&)(m[i*3]);
    }

    const t_Ty&       operator()(unsigned int col, unsigned int row) const
    {
        o_assert(col<2 && row<3);
        return m[col*3+row];
    }

    t_Ty&       operator()(unsigned int col, unsigned int row)
    {
        o_assert(col<2 && row<3);
        return m[col*3+row];
    }

public:
    union
    {
        t_Ty m[6];
        t_Ty mm[3][2];
        struct 
        {
            vector3_type ex;
            vector3_type ey;
        };
    };
};

// c * M
template<class t_Ty>
inline matrix2x3<t_Ty> operator* (t_Ty scalar, const matrix2x3<t_Ty>& mat);

/** Typedefs **/
typedef matrix2x3<float32> matrix2x3f;
typedef matrix2x3<float64> matrix2x3d;

#include "matrix2x3.inl"

o_namespace_end(phantom, math)

#endif // o_math_matrix2x3
