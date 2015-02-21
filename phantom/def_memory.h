/* TODO LICENCE HERE */

#ifndef o_phantom_memory_h__
#define o_phantom_memory_h__



/* ****************** Includes ******************* */
o_fwd(class, phantom, dynamic_initializer_handle);
/* *********************************************** */

o_namespace_begin(phantom, memory)


// boost::object_pool alternative adapted for phantom
struct malloc_free_allocator_for_boost
{
    typedef std::size_t        size_type;
    typedef std::ptrdiff_t    difference_type;

    static char * malloc BOOST_PREVENT_MACRO_SUBSTITUTION(const size_type bytes)
    { return static_cast<char *>( o__func__malloc(bytes)); }
    static void free BOOST_PREVENT_MACRO_SUBSTITUTION(char * const block)
    { o__func__free(block); }
};

template<typename T, typename UserAllocator = malloc_free_allocator_for_boost>
struct malloc_free_allocator
{
public:
    typedef T value_type;
    typedef UserAllocator user_allocator;
    typedef value_type * pointer;
    typedef const value_type * const_pointer;
    typedef value_type & reference;
    typedef const value_type & const_reference;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;

    template <typename U>
    struct rebind
    {
        typedef malloc_free_allocator<U, user_allocator> other;
    };

public:
    malloc_free_allocator()
    {
    }

    // default copy constructor

    // default assignment operator

    // not explicit, mimicking std::allocator [20.4.1]
    template <typename U>
    malloc_free_allocator(
        const malloc_free_allocator<U, UserAllocator> &)
    {
    }

    // default destructor

    static pointer address(reference r)
    { return &r; }
    static const_pointer address(const_reference s)
    { return &s; }
    static size_type max_size()
    { return (std::numeric_limits<size_type>::max)(); }
    void construct(const pointer ptr, const value_type & t)
    { new (ptr) T(t); }
    void destroy(const pointer ptr)
    {
        ptr->~T();
        (void) ptr; // avoid unused variable warning
    }

    bool operator==(const malloc_free_allocator &) const
    { return true; }
    bool operator!=(const malloc_free_allocator &) const
    { return false; }

    static pointer allocate(const size_type n)
    {
        const pointer ret = (const pointer)user_allocator::malloc(n*sizeof(value_type));
        if (ret == 0)
            boost::throw_exception(std::bad_alloc());
        return ret;
    }
    static pointer allocate(const size_type n, const void * const)
    {
        return allocate(n);
    }
    static pointer allocate()
    {
        const pointer ret = (pointer)user_allocator::malloc(sizeof(value_type));
        if (ret == 0)
            boost::throw_exception(std::bad_alloc());
        return ret;
    }
    static void deallocate(const pointer ptr, const size_type n)
    {
        user_allocator::free((char*const)ptr);
    }
    static void deallocate(const pointer ptr)
    {
        user_allocator::free((char*const)ptr);
    }
};

#if o__bool__enable_allocation_statistics

#define o_memory_stat_insert_arguments __FILE__,__LINE__
#define o_memory_stat_prepend_arguments __FILE__,__LINE__,
#define o_memory_stat_prepend_arguments_10 __FILE__,__LINE__,
#define o_memory_stat_prepend_arguments_9 __FILE__,__LINE__,
#define o_memory_stat_prepend_arguments_8 __FILE__,__LINE__,
#define o_memory_stat_prepend_arguments_7 __FILE__,__LINE__,
#define o_memory_stat_prepend_arguments_6 __FILE__,__LINE__,
#define o_memory_stat_prepend_arguments_5 __FILE__,__LINE__,
#define o_memory_stat_prepend_arguments_4 __FILE__,__LINE__,
#define o_memory_stat_prepend_arguments_3 __FILE__,__LINE__,
#define o_memory_stat_prepend_arguments_2 __FILE__,__LINE__,
#define o_memory_stat_prepend_arguments_1 __FILE__,__LINE__,
#define o_memory_stat_prepend_arguments_0 __FILE__,__LINE__
#define o_memory_stat_append_arguments ,__FILE__,__LINE__
#define o_memory_stat_insert_parameters const char* a_strFILE, size_t a_uiLINE
#define o_memory_stat_prepend_parameters const char* a_strFILE, size_t a_uiLINE,
#define o_memory_stat_append_parameters ,const char* a_strFILE, size_t a_uiLINE
#define o_memory_stat_insert_parameters_use a_strFILE, a_uiLINE
#define o_memory_stat_prepend_parameters_use a_strFILE, a_uiLINE,
#define o_memory_stat_append_parameters_use ,a_strFILE, a_uiLINE


class o_export    Statistics
{
    template <typename t_Ty, typename t_Allocator> friend  class stat_allocator;
    friend  class phantom::dynamic_initializer_handle;
public:
#if o_COMPILER == o_COMPILER_VISUAL_STUDIO
        typedef __int64 counter_type ;
#else
        typedef int64_t counter_type ;
#endif

    static counter_type    AllocationCount() { return m_AllocationCount; }
    static counter_type    TotalAllocationCount() { return m_TotalAllocationCount; }
    static counter_type    TotalAllocatedByteCount() { return m_TotalAllocatedByteCount; }
    static counter_type    AllocatedByteCount() { return m_AllocatedByteCount; }

    static void RegisterBytes(size_t bytes, const char* file, unsigned int line);
    static void UnregisterBytes(size_t bytes, const char* file, unsigned int line);
    static void RegisterBytesN(size_t bytes, size_t n, const char* file, unsigned int line);
    static void UnregisterBytesN(size_t bytes, size_t n, const char* file, unsigned int line);
    static void Trace(std::ostream& output);
    static void Lock();
    static void Unlock();

private:
    static counter_type    m_AllocationCount;
    static counter_type    m_TotalAllocationCount;
    static counter_type    m_AllocatedByteCount;
    static counter_type    m_TotalAllocatedByteCount;
    struct o_export allocation_info
    {
        allocation_info() : file(0), line(0), size(0) {}
        allocation_info(const char* afile, unsigned int aline, size_t asize);

        const char* file;
        unsigned int line;
        size_t size;
        bool dynamic_init;
    };
    static std::map<void*, allocation_info>*  m_Allocations;
    static bool            m_Locked;

};


template<typename t_Ty, typename _Allocator>
class stat_allocator
{
public:
    inline static t_Ty*    allocate(o_memory_stat_insert_parameters);
    inline static t_Ty*    allocate(size_t n o_memory_stat_append_parameters);
    inline static void    deallocate(t_Ty* a_pPtr o_memory_stat_append_parameters);
    inline static void    deallocate(t_Ty* a_pPtr, size_t n o_memory_stat_append_parameters);
};
#else

#define o_memory_stat_insert_arguments
#define o_memory_stat_prepend_arguments_10
#define o_memory_stat_prepend_arguments_9
#define o_memory_stat_prepend_arguments_8
#define o_memory_stat_prepend_arguments_7
#define o_memory_stat_prepend_arguments_6
#define o_memory_stat_prepend_arguments_5
#define o_memory_stat_prepend_arguments_4
#define o_memory_stat_prepend_arguments_3
#define o_memory_stat_prepend_arguments_2
#define o_memory_stat_prepend_arguments_1
#define o_memory_stat_prepend_arguments_0
#define o_memory_stat_prepend_arguments
#define o_memory_stat_append_arguments
#define o_memory_stat_insert_parameters
#define o_memory_stat_prepend_parameters
#define o_memory_stat_append_parameters
#define o_memory_stat_insert_parameters_use
#define o_memory_stat_prepend_parameters_use
#define o_memory_stat_append_parameters_use

#endif

o_namespace_end(phantom, memory)

#endif // __memory_h__
