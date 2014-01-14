#include "phantom/phantom.h"

#if o_COMPILER == o_COMPILER_VISUAL_STUDIO

o_registerNT((std), (typename, typename), (t_First, t_Second), _Pair_base);
o_registerNT((std), (typename), (_Ty), _Tree_iterator);
o_registerNT((std), (typename), (_Ty), _Tree_const_iterator);
o_registerNT((std), (typename), (t_Traits), _Tree_val);
o_registerNT((std), (typename), (t_Traits), _Tree_nod);
o_registerNT((std), (typename), (t_Traits), _Tree);
o_registerNT((std), (class, class, class, class, bool), (t_Kty, t_Ty, t_Pr, t_Alloc, t_Mfl), _Tmap_traits);
o_registerNT((std), (typename, typename), (t_First, t_Second), pair);
o_registerNT((std), (typename, typename, typename, typename), (t_Kty, t_Ty, t_Pr, t_Alloc), map);
o_registerNT((std), (typename, typename, typename, typename, typename), (t_Kty, t_Ty, t_Hash, t_Pr, t_Alloc), unordered_map);
o_registerNT((std), (typename, typename, typename, typename), (t_Kty, t_Ty, t_Pr, t_Alloc), multimap);

#endif

o_registerNT((std), (typename), (t_Traits), _Hash);
o_registerNT((std, tr1), (typename, typename, typename, typename, bool), (t_Kty, t_Ty, t_Hashcomp, t_Alloc, t_Mfl), _Umap_traits);
o_registerNT((std), (typename, typename, typename), (t_Kty, t_Hasher, t_Keyeq), _Hash_compare);
o_registerNT((phantom), (typename,typename,typename), (t_Key,t_Value,t_Pred), map);
o_register(phantom::map<phantom::string, char>);
o_register(phantom::map<phantom::string, unsigned char>);
o_register(phantom::map<phantom::string, signed char>);
#if o_BUILT_IN_WCHAR_T
o_register(phantom::map<phantom::string, wchar_t>);
#endif
o_register(phantom::map<phantom::string, short>);
o_register(phantom::map<phantom::string, unsigned short>);
o_register(phantom::map<phantom::string, int>);
o_register(phantom::map<phantom::string, unsigned int>);
o_register(phantom::map<phantom::string, long>);
o_register(phantom::map<phantom::string, unsigned long>);
o_register(phantom::map<phantom::string, long long>);
o_register(phantom::map<phantom::string, unsigned long long>);
o_register(phantom::map<phantom::string, float>);
o_register(phantom::map<phantom::string, double>);
o_register(phantom::map<phantom::string, long double>);
o_register(phantom::map<phantom::string, bool>);
o_register(phantom::map<phantom::string, void*>);
o_register(phantom::map<phantom::string, phantom::string>);