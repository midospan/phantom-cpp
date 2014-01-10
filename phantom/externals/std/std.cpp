#include "phantom/phantom.h"

#if o_COMPILER == o_COMPILER_VISUAL_STUDIO

o_registerN((std), _Container_base0);
o_registerN((std), _Container_base12);

o_registerNT((std), (typename, typename, typename), (_Elem, _Traits, _Alloc), _String_const_iterator);

o_registerNT((std), (typename, typename, typename), (t_Elem, t_Traits, t_Ax), basic_string);
o_registerNT((std), (typename), (_Elem), char_traits);
o_registerNT((std), (typename, typename, typename), (_Elem, _Traits, _Alloc), _String_iterator);
o_registerNT((std), (typename, typename, typename), (_Elem, _Traits, _Alloc), _String_const_iterator);
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

o_registerNT((std), (typename), (t_Traits), _Hash);
o_registerNT((std, tr1), (typename, typename, typename, typename, bool), (t_Kty, t_Ty, t_Hashcomp, t_Alloc, t_Mfl), _Umap_traits);
o_registerNT((std), (typename, typename, typename), (t_Kty, t_Hasher, t_Keyeq), _Hash_compare);

// _Vector_val
o_registerNT((std), (typename, typename), (_Ty, _Alloc), _Vector_val);
o_registerNT((std), (typename), (_Ty), _Vector_const_iterator);
o_registerNT((std), (typename), (_Ty), _Vector_iterator);
o_registerNT((std), (typename, typename), (t_Ty, t_Alloc), vector);
o_registerNT((std), (typename, typename), (_Ty, _Alloc), _List_nod);
o_registerNT((std), (typename, typename), (_Ty, _Alloc), _List_val) ;
o_registerNT((std), (typename), (_Ty), _List_const_iterator);
o_registerNT((std), (typename), (_Ty), _List_iterator);
o_registerNT((std), (typename, typename), (t_Ty, t_Alloc), list);
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

o_register(std::vector<int>);
o_register(std::map<std::string,std::string>);
o_register(std::multimap<std::string,std::string>);
o_register(std::unordered_set<int>);
o_register(std::set<int>);

#endif // o_COMPILER == o_COMPILER_VISUAL_STUDIO

o_registerNT((phantom), (typename), (t_Ty), vector);
o_registerNT((phantom), (typename,typename,typename), (t_Key,t_Value,t_Pred), map);
o_registerNT((phantom), (typename), (t_Ty), list);
o_registerNT((phantom), (typename), (t_Ty), deque);
o_registerNT((phantom), (typename, typename, typename, typename), (t_Kty, t_Ty, t_Hash, t_Pr), unordered_map);
o_registerNT((phantom), (typename, typename, typename), (t_Kty, t_Ty, t_Pr), multimap);

// ensures that std::basic_string will be available for string based search
// into the reflection system
o_register(std::allocator<char>);
o_register(std::char_traits<char>);
o_register(phantom::string);

// registers the basic_string's typedef std::string 
o_register_typedefN(std, string);

// registers the basic_string's typedef std::wstring 
o_register_typedefN(std, wstring);

// registers the basic_string's typedef phantom::string (see typedef.h)
o_register_typedefN(phantom, string);

// registers the basic_string's typedef phantom::wstring (see typedef.h)
o_register_typedefN(phantom, wstring);

// Various specialization test
o_register(phantom::unordered_map<std::string,int>);
o_register(phantom::map<std::string,std::string>);


//o_register(std::multiset<std::string>);