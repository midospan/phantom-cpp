#include "phantom/phantom.h"
#include "unordered_map.h"
#include "unordered_map.hxx"
#include "string.h"
#if !defined(DEBUG) // Disable static solving on debug mode to accelerate build
#include "string.hxx"
#endif

o_registerNT((std), (typename, typename, typename, typename, typename), (t_Kty, t_Ty, t_Hash, t_Pr, t_Alloc), unordered_map);
o_registerNT((phantom), (typename, typename, typename, typename, typename), (t_Kty, t_Ty, t_Hash, t_Pr, t_Alloc), unordered_map);

// o_registerNTI((phantom), unordered_map, (int, char));
// o_registerNTI((phantom), unordered_map, (phantom::string, unsigned char));
// o_registerNTI((phantom), unordered_map, (phantom::string, signed char));
// #if o_BUILT_IN_WCHAR_T
// o_registerNTI((phantom), unordered_map, (phantom::string, wchar_t));
// #endif
// o_registerNTI((phantom), unordered_map, (phantom::string, short));
// o_registerNTI((phantom), unordered_map, (phantom::string, unsigned short));
// o_registerNTI((phantom), unordered_map, (phantom::string, int));
// o_registerNTI((phantom), unordered_map, (phantom::string, unsigned int));
// o_registerNTI((phantom), unordered_map, (phantom::string, long));
// o_registerNTI((phantom), unordered_map, (phantom::string, unsigned long));
// o_registerNTI((phantom), unordered_map, (phantom::string, long long));
// o_registerNTI((phantom), unordered_map, (phantom::string, unsigned long long));
// o_registerNTI((phantom), unordered_map, (phantom::string, float));
// o_registerNTI((phantom), unordered_map, (phantom::string, double));
// o_registerNTI((phantom), unordered_map, (phantom::string, long double));
// o_registerNTI((phantom), unordered_map, (phantom::string, bool));
// o_registerNTI((phantom), unordered_map, (phantom::string, void*));
// o_registerNTI((phantom), unordered_map, (phantom::string, phantom::string));
