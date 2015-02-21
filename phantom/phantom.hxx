o_classN((phantom, memory), malloc_free_allocator_for_boost)
(
        );

o_classNT((phantom, memory), (typename, typename), (T, UserAllocator), malloc_free_allocator)
(
        );

o_classN((phantom), object)
(
o_public:
    o_data_member(void*, m_address);
    o_data_member(phantom::reflection::ClassType*, m_class_type);
);

o_classN((phantom), variable)
(
o_public:
    o_data_member(string,  name);
    o_data_member(variant, value);
);

#include "phantom/util/Comparator.hxx"
#include "phantom/reflection/Module.hxx"
