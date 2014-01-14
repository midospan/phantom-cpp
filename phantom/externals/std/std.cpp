#include "phantom/phantom.h"

#if o_COMPILER == o_COMPILER_VISUAL_STUDIO

o_registerN((std), _Container_base0);
o_registerN((std), _Container_base12);


// _Vector_val
o_registerNT((std), (typename), (_Elem), allocator);
o_registerNT((std), (typename, typename, typename), (t_Arg1, t_Arg2, t_Result), binary_function);
o_registerNT((std), (typename, typename), (t_Arg, t_Result), unary_function);
o_registerNT((std), (typename), (t_Ty), less);
o_registerNT((std, tr1), (typename, typename, typename, bool), (t_Kty, t_Tr, t_Alloc, t_Mfl), _Uset_traits);
o_registerNT((std), (typename, typename, typename, typename), (t_Kty, t_Hash, t_Keyeq, t_Alloc), unordered_set);
o_registerNT((std), (typename), (_Kty), hash);
o_registerNT((std), (typename), (t_Ty), equal_to);
o_registerNT((std), (typename), (t_RanIt), reverse_iterator);
o_registerNT((std), (typename, typename, typename), (t_Ty, t_Pr, t_Alloc), set);
o_registerNT((std), (typename, typename, typename, bool), (t_Kty, t_Tr, t_Alloc, t_Mfl), _Tset_traits);
o_registerNT((std), (typename, typename, typename), (t_Kty, t_Pr, t_Alloc), multiset);
o_registerNT((std), (typename, typename), (_Kty, _Alloc), _Deque_val);
o_registerNT((std), (typename, typename), (t_Ty, t_Alloc), deque);


#endif // o_COMPILER == o_COMPILER_VISUAL_STUDIO


o_registerNT((phantom), (typename), (t_Ty), deque);
o_registerNT((phantom), (typename, typename, typename, typename), (t_Kty, t_Ty, t_Hash, t_Pr), unordered_map);
o_registerNT((phantom), (typename, typename, typename), (t_Kty, t_Ty, t_Pr), multimap);


o_register(std::unordered_set<int>);
o_register(std::set<int>);

// Various specialization test
o_register(phantom::unordered_map<phantom::string,int>);

//o_register(std::multiset<std::string>);