#include "phantom/phantom.h"

o_registerN((boost, details, pool), default_mutex);
o_registerN((phantom, memory), malloc_free_allocator_for_boost)