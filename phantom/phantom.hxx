o_classN((phantom, memory), malloc_free_allocator_for_boost)
{
    o_reflection
    {

    };
};
o_exposeN((phantom, memory), malloc_free_allocator_for_boost);


o_classNT((phantom, memory), (typename, typename), (T, UserAllocator), malloc_free_allocator)
{
    o_reflection
    {

    };
};
o_exposeNT((phantom, memory), (typename, typename), (T, UserAllocator), malloc_free_allocator);


o_classN((phantom), object)
{
    o_reflection
    {
        o_data_member(void*, m_address, o_no_range, o_public);
        o_data_member(phantom::reflection::ClassType*, m_class_type, o_no_range, o_public);
    };
};
o_exposeN((phantom), object);


#include "phantom\util\Comparator.hxx"
#include "phantom\util\Iterator.hxx"
#include "phantom\Module.hxx"
