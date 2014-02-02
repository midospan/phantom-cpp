#ifndef o_std_deque_h__
#define o_std_deque_h__

#include <deque>

#include "utility.h"

#if o_COMPILER == o_COMPILER_VISUAL_STUDIO

// _Deque_val
o_declareNT(class, (std), (typename, typename), (_Kty, _Alloc), _Deque_val);

#endif

// deque
o_declareNT(class, (std), (typename, typename), (t_Ty, t_Alloc), deque);

#endif // o_std_deque_h__