#ifndef o_std_list_h__
#define o_std_list_h__

#include <list>

#include "utility.h"

/// LIST
#if o_COMPILER == o_COMPILER_VISUAL_STUDIO
// _List_val
o_declareNT(class, (std), (typename, typename), (_Ty, _Alloc), _List_val);
// _List_const_iterator
o_declareNT(class, (std), (typename), (_Ty), _List_const_iterator);
// _List_iterator
o_declareNT(class, (std), (typename), (_Ty), _List_iterator);

#endif

// list
o_declareNT(class, (std), (typename, typename), (t_Ty, t_Alloc), list);
// Phantom std specialization
o_declareNT(class, (phantom), (typename), (t_Ty), list);

#endif // o_std_list_h__