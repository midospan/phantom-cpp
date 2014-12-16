#pragma once

o_namespace_begin(phantom)

template<typename Enum> 
struct has_has_something<flags<Enum> > 
{ 
    const static bool value = false; 
};

o_namespace_end(phantom)

o_structureNT((phantom), (typename), (Enum), flags_bit)
(
    o_property(bool, value, setValue, getValue);
);

o_structureNT((phantom), (typename), (Enum), const_flags_bit)
(
);

o_structureNT((phantom), (typename), (Enum), flags)
(
    o_nested_typedef(bit);
    o_nested_typedef(const_bit);
    o_nested_typedef(enum_type);
    o_member_function(int, operator int, ());
    o_member_function(bit, operator[], (Enum));
);
