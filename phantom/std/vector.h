#ifndef o_std_vector_h__
#define o_std_vector_h__

#include <vector>

#include "utility.h"

/// VECTOR
#if o_COMPILER == o_COMPILER_VISUAL_STUDIO

// _Vector_val
o_declareNT(class, (std), (typename, typename), (_Ty, _Alloc), _Vector_val);
// _Vector_const_iterator
o_declareNT(class, (std), (typename), (_Ty), _Vector_const_iterator);
// _Vector_iterator
o_declareNT(class, (std), (typename), (_Ty), _Vector_iterator);

#endif

// vector
o_declareNT(class, (std), (typename, typename), (t_Ty, t_Alloc), vector);

o_declareNT(class, (phantom), (typename), (t_Ty), vector);

#endif // vector_h__