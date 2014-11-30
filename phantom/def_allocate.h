
o_namespace_begin(phantom)

#define o_allocate(...) phantom::allocate<__VA_ARGS__>(o_memory_stat_insert_arguments)
#define o_allocate_n(n, ...) phantom::allocate<__VA_ARGS__>(n o_memory_stat_append_arguments)
#define o_deallocate(exp,  ...) phantom::deallocate<__VA_ARGS__>(exp o_memory_stat_append_arguments)
#define o_deallocate_n(exp, n, ...) phantom::deallocate<__VA_ARGS__>(exp, n o_memory_stat_append_arguments)

#define o_dynamic_pool_allocate(s) phantom::dynamicPoolAllocate(s o_memory_stat_append_arguments)
#define o_dynamic_pool_allocate_n(n, s) phantom::dynamicPoolAllocate(s, n  o_memory_stat_append_arguments)
#define o_dynamic_pool_deallocate(exp, s) phantom::dynamicPoolDeallocate(s, exp o_memory_stat_append_arguments)
#define o_dynamic_pool_deallocate_n(exp, n, s) phantom::dynamicPoolDeallocate(s, exp, n o_memory_stat_append_arguments)

    template<typename t_Ty>
inline t_Ty* allocate(o_memory_stat_insert_parameters)
{
    return phantom::allocator<t_Ty>::allocate(o_memory_stat_insert_parameters_use);
}

template<typename t_Ty>
inline void deallocate(t_Ty* ptr o_memory_stat_append_parameters)
{
    return phantom::allocator<t_Ty>::deallocate(ptr o_memory_stat_append_parameters_use);
}

template<typename t_Ty>
t_Ty* allocate(size_t n o_memory_stat_append_parameters)
{
    o_assert(n);
    return phantom::allocator<t_Ty>::allocate(n o_memory_stat_append_parameters_use);
}

template<typename t_Ty>
void deallocate(t_Ty* ptr, size_t n o_memory_stat_append_parameters)
{
    o_assert(n);
    return phantom::allocator<t_Ty>::deallocate(ptr, n o_memory_stat_append_parameters_use);
}

o_namespace_end(phantom)