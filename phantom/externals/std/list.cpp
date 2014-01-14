#include "phantom/phantom.h"

#if o_COMPILER == o_COMPILER_VISUAL_STUDIO

o_registerNT((std), (typename, typename), (_Ty, _Alloc), _List_val) ;
o_registerNT((std), (typename), (_Ty), _List_const_iterator);
o_registerNT((std), (typename), (_Ty), _List_iterator);
o_registerNT((std), (typename, typename), (t_Ty, t_Alloc), list);

#endif

o_registerNT((phantom), (typename), (t_Ty), list);
o_register(phantom::list<char>);
o_register(phantom::list<unsigned char>);
o_register(phantom::list<signed char>);
#if o_BUILT_IN_WCHAR_T
o_register(phantom::list<wchar_t>);
#endif
o_register(phantom::list<short>);
o_register(phantom::list<unsigned short>);
o_register(phantom::list<int>);
o_register(phantom::list<unsigned int>);
o_register(phantom::list<long>);
o_register(phantom::list<unsigned long>);
//o_register(phantom::list<long long>);
//o_register(phantom::list<unsigned long long>);
o_register(phantom::list<float>);
o_register(phantom::list<double>);
o_register(phantom::list<long double>);
o_register(phantom::list<bool>);
o_register(phantom::list<void*>);
o_register(phantom::list<phantom::string>);