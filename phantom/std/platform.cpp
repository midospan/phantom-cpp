#include "phantom/phantom.h"
#include "platform.h"
#include "platform.hxx"

#if o_COMPILER == o_COMPILER_VISUAL_STUDIO

// _Vector_val
o_registerNT((std), (typename), (_Elem), allocator);
o_registerNT((std), (typename, typename, typename), (t_Arg1, t_Arg2, t_Result), binary_function);
o_registerNT((std), (typename, typename), (t_Arg, t_Result), unary_function);
o_registerNT((std), (typename), (t_Ty), less);
o_registerNT((std), (typename), (_Kty), hash);
o_registerNT((std), (typename), (t_Ty), equal_to);
o_registerNT((std), (typename), (t_RanIt), reverse_iterator);
o_registerNT((std), (typename, typename), (_Kty, _Alloc), _Deque_val);
o_registerNT((std), (typename, typename), (t_Ty, t_Alloc), deque);
o_registerNT((std), (typename), (_Ty), _Tree_iterator);
o_registerNT((std), (typename), (_Ty), _Tree_const_iterator);
o_registerNT((std), (typename), (t_Traits), _Tree_val);
o_registerNT((std), (typename), (t_Traits), _Tree_nod);
o_registerNT((std), (typename), (t_Traits), _Tree);
o_registerNT((std), (typename), (t_Traits), _Hash);


#endif // o_COMPILER == o_COMPILER_VISUAL_STUDIO

