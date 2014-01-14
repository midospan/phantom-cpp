#include "phantom/phantom.h"

o_registerNT((std), (typename, typename, typename), (t_Elem, t_Traits, t_Ax), basic_string);
o_registerNT((std), (typename), (_Elem), char_traits);
o_registerNT((std), (typename, typename, typename), (_Elem, _Traits, _Alloc), _String_iterator);
o_registerNT((std), (typename, typename, typename), (_Elem, _Traits, _Alloc), _String_const_iterator);
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