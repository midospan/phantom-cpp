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

#include "phantom/phantom.h"

o_namespace_begin(phantom, memory)


#if o__bool__enable_allocation_statistics

Statistics::counter_type    Statistics::m_AllocationCount  = 0;
Statistics::counter_type    Statistics::m_TotalAllocationCount  = 0;
Statistics::counter_type    Statistics::m_AllocatedByteCount  = 0;
Statistics::counter_type    Statistics::m_TotalAllocatedByteCount = 0;
std::map<void*, Statistics::allocation_info> Statistics::m_Allocations;
bool                        Statistics::m_Locked = false;

void phantom::memory::Statistics::Trace(std::ostream& output)
{
    Lock();
    output<<phantom::console::fg_blue<<"[Total allocation count] : "<<m_TotalAllocationCount<<std::endl;
    output<<phantom::console::fg_blue<<"[Total allocated size] : "<<m_TotalAllocatedByteCount<<std::endl;
    output<<phantom::console::fg_blue<<"[Remaining non-deallocated count] : "<<m_AllocationCount<<std::endl;
    output<<phantom::console::fg_blue<<"[Remaining non-deallocated size] : "<<m_AllocatedByteCount<<std::endl;
    output<<phantom::console::fg_gray<<std::endl;

    for(auto it = m_Allocations.begin(); it != m_Allocations.end(); ++it)
    {
        output<<phantom::console::fg_red<<"+ allocation";
        if(it->second.dynamic_init)
        {
            output<<phantom::console::fg_magenta<<" [dynamic initializer]";
        }
        output<<std::endl;
        output<<phantom::console::fg_yellow<<"\t[file: "<<it->second.file<<"]"<<std::endl;
        output<<phantom::console::fg_yellow<<"\t[line: "<<it->second.line<<"]"<<std::endl;;
        output<<phantom::console::fg_cyan<<"\t[size : "<<it->second.size<<" bytes]"<<std::endl;
        output<<phantom::console::fg_gray<<std::endl;
    }
    
    Unlock();
}

void Statistics::RegisterBytes( size_t bytes, const char* file, unsigned int line )
{
    if(m_Locked) return;
    m_AllocationCount++;
    m_TotalAllocationCount++;
    m_AllocatedByteCount += bytes;
    m_TotalAllocatedByteCount += bytes;
}

void Statistics::UnregisterBytes( size_t bytes, const char* file, unsigned int line )
{
    if(m_Locked) return;
    m_AllocationCount--;
    m_AllocatedByteCount -= bytes;
}

void Statistics::RegisterBytesN( size_t bytes, size_t n, const char* file, unsigned int line )
{
    if(m_Locked) return;
    m_AllocationCount+=n;
    m_TotalAllocationCount+=n;
    m_AllocatedByteCount += n*bytes;
    m_TotalAllocatedByteCount += n*bytes;
}

void Statistics::UnregisterBytesN( size_t bytes, size_t n, const char* file, unsigned int line )
{
    if(m_Locked) return;
    m_AllocationCount-=n;
    m_AllocatedByteCount -= n*bytes;
}

void Statistics::Lock()
{
    o_assert(!m_Locked);
    m_Locked = true;
}

void Statistics::Unlock()
{
    o_assert(m_Locked);
    m_Locked = false;
}

Statistics::allocation_info::allocation_info( const char* afile, unsigned int aline, size_t asize ) 
    : file(afile), line(aline), size(asize), dynamic_init(Phantom::getState() < Phantom::eState_Installed)
{

}


#endif

o_namespace_end(phantom, memory)


