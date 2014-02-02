#include "phantom/phantom.h"
#include "list.h"
#include "list.hxx"
#include "string.h"
#if !defined(DEBUG) // Disable static solving on debug mode to accelerate build
#include "string.hxx"
#endif

#if o_COMPILER == o_COMPILER_VISUAL_STUDIO

o_registerNT((std), (typename, typename), (_Ty, _Alloc), _List_val) ;
o_registerNT((std), (typename), (_Ty), _List_const_iterator);
o_registerNT((std), (typename), (_Ty), _List_iterator);
o_registerNT((std), (typename, typename), (t_Ty, t_Alloc), list);

#endif

o_registerNT((phantom), (typename), (t_Ty), list);
o_registerNTI((phantom), list, (char));
o_registerNTI((phantom), list, (unsigned char));
o_registerNTI((phantom), list, (signed char));
#if o_BUILT_IN_WCHAR_T
o_registerNTI((phantom), list, (wchar_t));
#endif
o_registerNTI((phantom), list, (short));
o_registerNTI((phantom), list, (unsigned short));
o_registerNTI((phantom), list, (int));
o_registerNTI((phantom), list, (unsigned int));
o_registerNTI((phantom), list, (long));
o_registerNTI((phantom), list, (unsigned long));
//o_registerNTI((phantom), list, (long long));
//o_registerNTI((phantom), list, (unsigned long long));
o_registerNTI((phantom), list, (float));
o_registerNTI((phantom), list, (double));
o_registerNTI((phantom), list, (long double));
o_registerNTI((phantom), list, (bool));
o_registerNTI((phantom), list, (void*));
o_registerNTI((phantom), list, (phantom::string));