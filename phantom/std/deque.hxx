#pragma once

#include "utility.hxx"

#if o_COMPILER == o_COMPILER_VISUAL_STUDIO

/// std::_Deque_val
o_classNTB((std), (typename, typename), (_Kty, _Alloc), _Deque_val, (_Container_base12)) (
);

/// std::deque
o_classNTB((std), (typename, typename), (t_Ty, t_Alloc), deque, (_Deque_val<t_Ty, t_Alloc>)) (
);

/// phantom::deque
o_classNTB((phantom), (typename), (t_Ty), deque, (std::deque<t_Ty, o__t1_class__contiguous_memory_allocator(t_Ty)>))
(
);

#elif o_COMPILER == o_COMPILER_GCC

/// std::deque
o_classNT((std), (typename, typename), (t_Ty, t_Alloc), deque) (
);

/// phantom::deque
o_classNTB((phantom), (typename), (t_Ty), deque, (std::deque<t_Ty, o__t1_class__contiguous_memory_allocator(t_Ty)>))
(
);

#else
#   error std::deque reflection is not declared for this compiler
#endif
