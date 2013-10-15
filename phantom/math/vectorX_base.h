#ifndef phantom_math_vectorX_base_h__
#define phantom_math_vectorX_base_h__

o_namespace_begin(phantom, math)

template<typename t_Ty>
struct vectorX_aligned16_base
{
    vectorX_aligned16_base(t_Ty a_x, t_Ty a_y)
        : x(a_x), y(a_y), z(0), w(0) {}
    vectorX_aligned16_base(t_Ty a_x, t_Ty a_y, t_Ty a_z)
        : x(a_x), y(a_y), z(a_z), w(0) {}
    vectorX_aligned16_base(t_Ty a_x, t_Ty a_y, t_Ty a_z, t_Ty a_w)
        : x(a_x), y(a_y), z(a_z), w(a_w) {}

    union
    {
        struct 
        {
            t_Ty x;
            t_Ty y;
            t_Ty z;
            t_Ty w;
        };
        t_Ty    m[4];
    };
};

o_namespace_end(phantom, math)

#endif // phantom_math_vectorX_base_h__
