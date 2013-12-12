#include "phantom/phantom.h"

o_registerN((boost, details, pool), default_mutex);
o_registerN((phantom, memory), malloc_free_allocator_for_boost)
o_registerNT((phantom, memory), (typename, typename), (T, UserAllocator), malloc_free_allocator)