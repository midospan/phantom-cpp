#ifndef o_math_avector3_h__
#define o_math_avector3_h__

#include "phantom/math/sse2.h"

o_declareNT(class, (phantom, math), (typename), (t_Ty), avector3);

o_namespace_begin(phantom, math)

template<typename t_Ty>
class avector3
{

    t_Ty* chunk[3];
};


