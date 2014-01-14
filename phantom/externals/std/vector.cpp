#include "phantom/phantom.h"

#if o_COMPILER == o_COMPILER_VISUAL_STUDIO

o_registerNT((std), (typename, typename), (_Ty, _Alloc), _Vector_val);
o_registerNT((std), (typename), (_Ty), _Vector_const_iterator);
o_registerNT((std), (typename), (_Ty), _Vector_iterator);

#endif

o_registerNT((std), (typename, typename), (t_Ty, t_Alloc), vector);
o_registerNT((phantom), (typename), (t_Ty), vector);

o_register(phantom::vector<char>);
o_register(phantom::vector<unsigned char>);
o_register(phantom::vector<signed char>);
#if o_BUILT_IN_WCHAR_T
o_register(phantom::vector<wchar_t>);
#endif
o_register(phantom::vector<short>);
o_register(phantom::vector<unsigned short>);
o_register(phantom::vector<int>);
o_register(phantom::vector<unsigned int>);
o_register(phantom::vector<long>);
o_register(phantom::vector<unsigned long>);
o_register(phantom::vector<long long>);
//o_register(phantom::vector<unsigned long long>);
//o_register(phantom::vector<float>);
o_register(phantom::vector<double>);
o_register(phantom::vector<long double>);
o_register(phantom::vector<void*>);
o_register(phantom::vector<phantom::string>);