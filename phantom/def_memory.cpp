/* TODO LICENCE HERE */

/* TODO LICENCE HERE */

#include "phantom/phantom.h"
#include "phantom/reflection/Application.h"

o_namespace_begin(phantom, memory)


#if o__bool__enable_allocation_statistics

Statistics::counter_type    Statistics::m_AllocationCount;
Statistics::counter_type    Statistics::m_TotalAllocationCount  ;
Statistics::counter_type    Statistics::m_AllocatedByteCount ;
Statistics::counter_type    Statistics::m_TotalAllocatedByteCount ;
std::map<void*, Statistics::allocation_info>* Statistics::m_Allocations;
bool                        Statistics::m_Locked ;

void phantom::memory::Statistics::Trace(std::ostream& output)
{
    Lock();
    output<<phantom::console::fg_blue<<"[Total allocation count] : "<<m_TotalAllocationCount<<std::endl;
    output<<phantom::console::fg_blue<<"[Total allocated size] : "<<m_TotalAllocatedByteCount<<std::endl;
    output<<phantom::console::fg_blue<<"[Remaining non-deallocated count] : "<<m_AllocationCount<<std::endl;
    output<<phantom::console::fg_blue<<"[Remaining non-deallocated size] : "<<m_AllocatedByteCount<<std::endl;
    output<<phantom::console::fg_gray<<std::endl;

    for(auto it = m_Allocations->begin(); it != m_Allocations->end(); ++it)
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
    : file(afile), line(aline), size(asize), dynamic_init(application() == nullptr OR application()->getLoadedModuleCount() == 0)
{

}


#endif

o_namespace_end(phantom, memory)


