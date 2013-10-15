#ifndef o_phantom_externals_boost_boost_pool_h__
#define o_phantom_externals_boost_boost_pool_h__

#include <phantom/_kernel.noclassdef.h>

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

// pool_allocator
o_classNT((boost), (typename, typename, typename), (T, UserAllocator, Mutex), pool_allocator)
{
    o_reflection {};
};
o_exposeNT((boost), (typename, typename, typename), (T, UserAllocator, Mutex), pool_allocator);


// fast_pool_allocator
o_classNT((boost), (typename, typename, typename, unsigned, unsigned), (T, UserAllocator, Mutex, NextSize, MaxSize), fast_pool_allocator)
{
    o_reflection {};
};
o_exposeNT((boost),(typename, typename, typename, unsigned, unsigned), (T, UserAllocator, Mutex, NextSize, MaxSize), fast_pool_allocator)



#endif // o_phantom_externals_boost_boost_pool_h__