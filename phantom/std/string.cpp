#include "phantom/phantom.h"
#include "string.h"
#include "string.hxx"
#include "vector.hxx"

o_registerNT((std), (typename, typename, typename), (t_Elem, t_Traits, t_Ax), basic_string);

o_registerNT((std), (typename), (_Elem), char_traits);
o_registerNT((std), (typename, typename, typename), (_Elem, _Traits, _Alloc), _String_iterator);
o_registerNT((std), (typename, typename, typename), (_Elem, _Traits, _Alloc), _String_const_iterator);
// ensures that std::basic_string will be available for string based search
// into the reflection system

o_registerN((phantom), string);
o_registerNTI((phantom), vector, (phantom::string));

// registers the basic_string's typedef std::string
o_typedefN((std), string);

// registers the basic_string's typedef std::wstring
o_typedefN((std), wstring);

// registers the basic_string's typedef phantom::string (see typedef.h)
o_typedefN((phantom), string);

// registers the basic_string's typedef phantom::wstring (see typedef.h)
o_typedefN((phantom), wstring);
