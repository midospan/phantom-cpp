// pool_allocator
o_classNT((boost), (typename, typename, typename), (T, UserAllocator, Mutex), pool_allocator)
(
);



// fast_pool_allocator
o_classNT((boost), (typename, typename, typename, unsigned, unsigned), (T, UserAllocator, Mutex, NextSize, MaxSize), fast_pool_allocator)
(
);

#ifdef WIN32
o_classN((boost, details, pool), null_mutex, o_no_copy)
(
);
#endif //WIN32

o_classN((boost), mutex, o_no_copy)
(
);

