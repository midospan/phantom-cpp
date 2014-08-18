o_classN((phantom, memory), malloc_free_allocator_for_boost)
{
    o_reflection
    {

    };
};

o_classNT((phantom, memory), (typename, typename), (T, UserAllocator), malloc_free_allocator)
{
    o_reflection
    {

    };
};

o_classN((phantom), object)
{
    o_reflection
    {
        o_data_member(void*, m_address, o_no_range, o_public);
        o_data_member(phantom::reflection::ClassType*, m_class_type, o_no_range, o_public);
    };
};

o_classN((phantom), variable)
{
    o_reflection 
    {
        o_data_member(string,  name, o_no_range, o_public);
        o_data_member(variant, value, o_no_range, o_public);
    };
};

#include "phantom\util\Comparator.hxx"
#include "phantom\Module.hxx"
