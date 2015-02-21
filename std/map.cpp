#include "phantom/phantom.h"
#include "map.h"
#include "map.hxx"
#include "string.h"
#if !defined(DEBUG) // Disable static solving on debug mode to accelerate build
#include "string.hxx"
#endif

#if o_COMPILER == o_COMPILER_VISUAL_STUDIO

o_registerNT((std, tr1), (typename, typename, typename, typename, bool), (t_Kty, t_Ty, t_Hashcomp, t_Alloc, t_Mfl), _Umap_traits);
o_registerNT((std), (class, class, class, class, bool), (t_Kty, t_Ty, t_Pr, t_Alloc, t_Mfl), _Tmap_traits);

#endif


o_registerNT((std), (typename, typename, typename, typename), (t_Kty, t_Ty, t_Pr, t_Alloc), map);
o_registerNT((std), (typename, typename, typename, typename), (t_Kty, t_Ty, t_Pr, t_Alloc), multimap);

// o_registerNTI((phantom), map, (phantom::string, char));
// o_registerNTI((phantom), map, (phantom::string, unsigned char));
// o_registerNTI((phantom), map, (phantom::string, signed char));
// #if o_HAS_BUILT_IN_WCHAR_T
// o_registerNTI((phantom), map, (phantom::string, wchar_t));
// #endif
// o_registerNTI((phantom), map, (phantom::string, short));
// o_registerNTI((phantom), map, (phantom::string, unsigned short));
// o_registerNTI((phantom), map, (phantom::string, int));
// o_registerNTI((phantom), map, (phantom::string, unsigned int));
// o_registerNTI((phantom), map, (phantom::string, long));
// o_registerNTI((phantom), map, (phantom::string, unsigned long));
// o_registerNTI((phantom), map, (phantom::string, long long));
// o_registerNTI((phantom), map, (phantom::string, unsigned long long));
// o_registerNTI((phantom), map, (phantom::string, float));
// o_registerNTI((phantom), map, (phantom::string, double));
// o_registerNTI((phantom), map, (phantom::string, long double));
// o_registerNTI((phantom), map, (phantom::string, bool));
// o_registerNTI((phantom), map, (phantom::string, void*));
// o_registerNTI((phantom), map, (phantom::string, phantom::string));