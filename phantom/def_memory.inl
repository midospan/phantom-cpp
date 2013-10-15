/*
	This file is part of PHANTOM
		 P reprocessed 
		 H igh-level 
		 A llocator 
		 N ested state-machines and 
		 T emplate 
		 O riented 
		 M eta-programming

	For the latest infos and sources, see http://code.google.com/p/phantom-cpp

	Copyright (C) 2008-2011 by Vivien MILLET

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in
	all copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
	THE SOFTWARE
*/

o_namespace_begin(phantom, memory)

#if o__bool__enable_allocation_statistics

template <typename t_Ty, typename t_Allocator>
inline t_Ty*    stat_allocator<t_Ty,t_Allocator>::allocate(size_t n o_memory_stat_append_parameters)
{
    t_Ty* ptr = t_Allocator::allocate(n);
    if(Statistics::m_Locked) return ptr;
    Statistics::Lock();
    o_assert(Statistics::m_Allocations.find(ptr) == Statistics::m_Allocations.end());
    Statistics::m_Allocations[ptr] = Statistics::allocation_info(a_strFILE, a_uiLINE, sizeof(t_Ty)*n);
    Statistics::m_AllocationCount += n;
    Statistics::m_TotalAllocationCount += n;
    Statistics::m_AllocatedByteCount += sizeof(t_Ty)*n;
    Statistics::m_TotalAllocatedByteCount += sizeof(t_Ty)*n;
    Statistics::Unlock();
    return ptr;
}

template <typename t_Ty, typename t_Allocator>
inline t_Ty*	stat_allocator<t_Ty,t_Allocator>::allocate(o_memory_stat_insert_parameters)
{
    t_Ty* ptr = t_Allocator::allocate();
    if(Statistics::m_Locked) return ptr;
    Statistics::Lock();
    o_assert(Statistics::m_Allocations.find(ptr) == Statistics::m_Allocations.end());
    Statistics::m_Allocations[ptr] = Statistics::allocation_info(a_strFILE, a_uiLINE, sizeof(t_Ty));
    ++Statistics::m_AllocationCount;
	++Statistics::m_TotalAllocationCount;
	Statistics::m_AllocatedByteCount += sizeof(t_Ty);
	Statistics::m_TotalAllocatedByteCount += sizeof(t_Ty);
    Statistics::Unlock();
	return ptr;
}

template <typename t_Ty, typename t_Allocator>
inline void    stat_allocator<t_Ty,t_Allocator>::deallocate(t_Ty* a_pPtr, size_t n o_memory_stat_append_parameters)
{
    t_Allocator::deallocate(a_pPtr, n);
    if(Statistics::m_Locked) return;
    auto found = Statistics::m_Allocations.find(a_pPtr);
    o_assert(found != Statistics::m_Allocations.end());
    Statistics::Lock();
    Statistics::m_Allocations.erase(found);
    Statistics::m_AllocationCount -= n;
    Statistics::m_AllocatedByteCount -= sizeof(t_Ty)*n;
    Statistics::Unlock();
}
template <typename t_Ty, typename t_Allocator>
inline void	stat_allocator<t_Ty,t_Allocator>::deallocate(t_Ty* a_pPtr o_memory_stat_append_parameters)
{
    t_Allocator::deallocate(a_pPtr);
    if(Statistics::m_Locked) return;
    auto found = Statistics::m_Allocations.find(a_pPtr);
    o_assert(found != Statistics::m_Allocations.end());
    Statistics::Lock();
    Statistics::m_Allocations.erase(found);
    Statistics::m_AllocationCount--;
    Statistics::m_AllocatedByteCount -= sizeof(t_Ty);
    Statistics::Unlock();
}

#endif

o_namespace_end(phantom, memory)