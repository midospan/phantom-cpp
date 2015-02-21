#include "phantom/phantom.h"
#include "vector.h"
#include "vector.hxx"

#if o_COMPILER == o_COMPILER_VISUAL_STUDIO

o_registerNT((std), (typename, typename), (_Ty, _Alloc), _Vector_val);
o_registerNT((std), (typename), (_Ty), _Vector_const_iterator);
o_registerNT((std), (typename), (_Ty), _Vector_iterator);

#endif

o_registerNT((std), (typename, typename), (t_Ty, t_Alloc), vector);
