#pragma once

#include "utility.hxx"

// _Deque_val
o_classNTS((std), (typename, typename), (_Kty, _Alloc), _Deque_val, (_Container_base12)) {o_reflection{};};
o_exposeNT((std), (typename, typename), (_Kty, _Alloc), _Deque_val);

// deque
o_classNTS((std), (typename, typename), (t_Ty, t_Alloc), deque, (_Deque_val<t_Ty, t_Alloc>)) { o_reflection {};};
o_exposeNT((std), (typename, typename), (t_Ty, t_Alloc), deque);


o_classNTS((phantom), (typename), (t_Ty), deque, (std::deque<t_Ty, o__t1_class__contiguous_memory_allocator(t_Ty)>))
{
    o_reflection
    {

    };
};
o_exposeNT((phantom), (typename), (t_Ty), deque);