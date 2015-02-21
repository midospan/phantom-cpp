#include "phantom/phantom.h"
#include "list.h"
#include "list.hxx"

#if o_COMPILER == o_COMPILER_VISUAL_STUDIO

o_registerNT((std), (typename, typename), (_Ty, _Alloc), _List_val) ;
o_registerNT((std), (typename), (_Ty), _List_const_iterator);
o_registerNT((std), (typename), (_Ty), _List_iterator);
o_registerNT((std), (typename, typename), (t_Ty, t_Alloc), list);

#endif
