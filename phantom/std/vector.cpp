#include "phantom/phantom.h"
#include "string.h"
#if !defined(DEBUG) // Disable static solving on debug mode to accelerate build
#include "string.hxx"
#endif
#include "vector.h"
#include "vector.hxx"

#if o_COMPILER == o_COMPILER_VISUAL_STUDIO

o_registerNT((std), (typename, typename), (_Ty, _Alloc), _Vector_val);
o_registerNT((std), (typename), (_Ty), _Vector_const_iterator);
o_registerNT((std), (typename), (_Ty), _Vector_iterator);

#endif

o_registerNT((std), (typename, typename), (t_Ty, t_Alloc), vector);
o_registerNT((phantom), (typename), (t_Ty), vector);

o_registerNTI((phantom), vector, (char));
o_registerNTI((phantom), vector, (unsigned char));
o_registerNTI((phantom), vector, (signed char));
#if o_BUILT_IN_WCHAR_T
o_registerNTI((phantom), vector, (wchar_t));
#endif
o_registerNTI((phantom), vector, (short));
o_registerNTI((phantom), vector, (unsigned short));
o_registerNTI((phantom), vector, (int));
o_registerNTI((phantom), vector, (unsigned int));
o_registerNTI((phantom), vector, (long));
o_registerNTI((phantom), vector, (unsigned long));
o_registerNTI((phantom), vector, (long long));
o_registerNTI((phantom), vector, (unsigned long long));
o_registerNTI((phantom), vector, (float));
o_registerNTI((phantom), vector, (double));
o_registerNTI((phantom), vector, (long double));
o_registerNTI((phantom), vector, (void*));
o_registerNTI((phantom), vector, (phantom::string));
o_registerNTI((phantom), vector, (phantom::data));