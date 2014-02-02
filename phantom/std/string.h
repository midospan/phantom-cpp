#ifndef o_std_string_h__
#define o_std_string_h__

#include <string>

#include "utility.h"

/// STRING
#if o_COMPILER == o_COMPILER_VISUAL_STUDIO
// _String_const_iterator
o_declareNT(class, (std), (typename, typename, typename), (_Elem, _Traits, _Alloc), _String_const_iterator);
// _String_iterator
o_declareNT(class, (std), (typename, typename, typename), (_Elem, _Traits, _Alloc), _String_iterator);
#endif
// basic_string
o_declareNT(class, (std), (typename, typename, typename), (t_Elem, t_Traits, t_Ax), basic_string);

#endif // o_std_list_h__