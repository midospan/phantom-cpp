#ifndef o_phantom_externals_boost_boost_pool_h__
#define o_phantom_externals_boost_boost_pool_h__

#include <phantom/phantom.h>

// pool_allocator
o_declareNT(class, (boost), (typename, typename, typename, unsigned, unsigned), (T, UserAllocator, Mutex, NextSize, MaxSize), pool_allocator);
// fast_pool_allocator
o_declareNT(class, (boost),(typename, typename, typename, unsigned, unsigned), (T, UserAllocator, Mutex, NextSize, MaxSize), fast_pool_allocator)

#if o__int__reflection_template_use_level == 3
#include "boost.hxx"
#endif
#endif // o_phantom_externals_boost_boost_pool_h__