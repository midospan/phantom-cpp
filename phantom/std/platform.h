#ifndef o_std_h__
#define o_std_h__

#include <phantom/phantom.h>

#if o_COMPILER == o_COMPILER_VISUAL_STUDIO

// binary_function
o_declareNT(struct, (std), (typename, typename, typename), (t_Arg1, t_Arg2, t_Result), binary_function);
// unary_function
o_declareNT(struct, (std), (typename, typename), (t_Arg, t_Result), unary_function);
// hash
o_declareNT(class, (std), (typename), (_Kty), hash);
// equal_to
o_declareNT(struct, (std), (typename), (t_Ty), equal_to);
// _Hash_compare
o_declareNT(class, (std), (typename, typename, typename), (t_Kty, t_Hasher, t_Keyeq), _Hash_compare)
// less
o_declareNT(struct, (std), (typename), (t_Ty), less);
// reverse_iterator
o_declareNT(class, (std), (typename), (t_RanIt), reverse_iterator);
// _Tree
o_declareNT(class, (std), (typename), (t_Traits), _Tree);
// _Tree_nod
o_declareNT(class, (std), (typename), (t_Traits), _Tree_nod);
// _Tree_val
o_declareNT(class, (std), (typename), (t_Traits), _Tree_val);
// _Tree_const_iterator
o_declareNT(class, (std), (typename), (_Ty), _Tree_const_iterator);
// _Tree_iterator
o_declareNT(class, (std), (typename), (_Ty), _Tree_iterator);

#endif // VISUAL_STUDIO STL


#endif
