/* TODO LICENCE HERE */

#ifndef o_def_new_delete_h__
#define o_def_new_delete_h__

o_namespace_begin(phantom)

struct o_export default_new_helper
{
    o_forceinline default_new_helper()
    {

    }
    template<typename t_Ty>
    o_forceinline t_Ty*    operator>>(t_Ty* instance)
    {
        return instance;
    }
};

/// ################################ DYNAMIC NEW / DELETE ##################################

struct o_export dynamic_new_helper
{
    o_forceinline dynamic_new_helper(phantom::reflection::Type* a_pType)
        : m_pType(a_pType)
    {
        o_assert(m_pType);
    }
    template<typename t_Ty>
    o_forceinline t_Ty*    operator>>(t_Ty* instance)
    {
        m_pType->install(instance, 0);
        m_pType->initialize(instance);
        return instance;
    }
    phantom::reflection::Type* m_pType;
};

struct o_export dynamic_new_n_helper
{
    o_forceinline dynamic_new_n_helper(phantom::reflection::Type* a_pType, size_t n)
        : m_pType(a_pType)
        , count(n)
    {
        o_assert(m_pType);
    }
    template<typename t_Ty>
    o_forceinline t_Ty*    operator>>(t_Ty* instance)
    {
        t_Ty* pChunk = instance;
        while(count--)
        {
            m_pType->setup(pChunk);
            ++pChunk;
        }
        return instance;
    }
    size_t count;
    phantom::reflection::Type* m_pType;
};


template<typename t_Ty>
struct dynamic_default_delete_helper
{
    o_forceinline dynamic_default_delete_helper(phantom::reflection::Type* a_pType o_memory_stat_append_parameters)
        : m_pType(a_pType)
    {
        o_assert(m_pType);
#if o__bool__enable_allocation_statistics
        this->a_strFILE = a_strFILE;
        this->a_uiLINE = a_uiLINE;
#endif
    }
    template <typename _Tyy>
    o_forceinline void    operator>>(_Tyy* instance)
    {
        m_pType->destroy(instance);
        m_pType->deallocate(static_cast<t_Ty*>(instance) o_memory_stat_append_parameters_use);
    }
#if o__bool__enable_allocation_statistics
    const char* a_strFILE;
    int  a_uiLINE;
#endif
    phantom::reflection::Type* m_pType;

};

template<typename t_Ty>
struct dynamic_delete_helper
{
    o_forceinline dynamic_delete_helper(phantom::reflection::Type* a_pType o_memory_stat_append_parameters)
        : m_pType(a_pType)
    {
        o_assert(m_pType);
#if o__bool__enable_allocation_statistics
        this->a_strFILE = a_strFILE;
        this->a_uiLINE = a_uiLINE;
#endif
    }
    template <typename _Tyy>
    o_forceinline void    operator>>(_Tyy* instance)
    {
        m_pType->teardown(instance);
        m_pType->deallocate(static_cast<t_Ty*>(instance) o_memory_stat_append_parameters_use);
    }
#if o__bool__enable_allocation_statistics
    const char* a_strFILE;
    int  a_uiLINE;
#endif
    phantom::reflection::Type* m_pType;

};

template<typename t_Ty>
struct dynamic_delete_n_helper
{
public:
    o_forceinline dynamic_delete_n_helper(phantom::reflection::Type* a_pType, size_t n o_memory_stat_append_parameters)
        : m_pType(a_pType) 
        , count(n)
    {
        o_assert(m_pType);
#if o__bool__enable_allocation_statistics
        this->a_strFILE = a_strFILE;
        this->a_uiLINE = a_uiLINE;
#endif
    }
    template <typename _Tyy>
    o_forceinline void    operator>>(_Tyy* instance)
    {
        t_Ty* pChunk = static_cast<t_Ty*>(instance);
        size_t i = count;
        while(i--)
        {
            m_pType->teardown(pChunk);
            ++pChunk;
        }
        m_pType->deallocate(static_cast<t_Ty*>(instance), count o_memory_stat_append_parameters_use);
    }
#if o__bool__enable_allocation_statistics
    const char* a_strFILE;
    int  a_uiLINE;
#endif
    phantom::reflection::Type* m_pType;
    size_t count;

};


/// ################################ STATIC NEW / DELETE ##################################

struct o_export new_helper
{
    o_forceinline new_helper()
    {

    }
    template<typename t_Ty>
    o_forceinline t_Ty*    operator>>(t_Ty* instance)
    {
        phantom::installer<t_Ty>::install(typeOf<t_Ty>(), instance, 0);
        phantom::initializer<t_Ty>::initialize(typeOf<t_Ty>(), instance);
        return instance;
    }
};

struct o_export new_n_helper
{
    o_forceinline new_n_helper(size_t n)
        : count(n)
    {

    }
    template<typename t_Ty>
    o_forceinline t_Ty*    operator>>(t_Ty* instance)
    {
        t_Ty* pChunk = instance;
        while(count--)
        {
            phantom::constructor<t_Ty>::construct(pChunk);
            phantom::installer<t_Ty>::install(typeOf<t_Ty>(), pChunk, 0);
            phantom::initializer<t_Ty>::initialize(typeOf<t_Ty>(), pChunk);
            ++pChunk;
        }
        return instance;
    }
    size_t count;
};

template<typename t_Ty>
struct default_delete_helper
{
    o_forceinline default_delete_helper(o_memory_stat_insert_parameters)
    {
#if o__bool__enable_allocation_statistics
        this->a_strFILE = a_strFILE;
        this->a_uiLINE = a_uiLINE;
#endif
    }
    template <typename _Tyy>
    o_forceinline void    operator>>(_Tyy* instance)
    {
        phantom::constructor<t_Ty>::destroy(instance);
        phantom::allocator<t_Ty>::deallocate(static_cast<t_Ty*>(instance) o_memory_stat_append_parameters_use);
    }
#if o__bool__enable_allocation_statistics
    const char* a_strFILE;
    int  a_uiLINE;
#endif

};

template<typename t_Ty>
struct delete_helper
{
    o_forceinline delete_helper(o_memory_stat_insert_parameters)
    {
#if o__bool__enable_allocation_statistics
        this->a_strFILE = a_strFILE;
        this->a_uiLINE = a_uiLINE;
#endif
    }
    template <typename _Tyy>
    o_forceinline void    operator>>(_Tyy* instance)
    {
        phantom::initializer<t_Ty>::terminate(typeOf<t_Ty>(), static_cast<t_Ty*>(instance));
        phantom::installer<t_Ty>::uninstall(typeOf<t_Ty>(), static_cast<t_Ty*>(instance), 0);
        phantom::constructor<t_Ty>::destroy(static_cast<t_Ty*>(instance));
        phantom::allocator<t_Ty>::deallocate(static_cast<t_Ty*>(instance) o_memory_stat_append_parameters_use);
    }
#if o__bool__enable_allocation_statistics
    const char* a_strFILE;
    int  a_uiLINE;
#endif

};

template<typename t_Ty>
struct delete_n_helper
{
public:
    o_forceinline delete_n_helper(size_t n o_memory_stat_append_parameters)
        : count(n)
    {
#if o__bool__enable_allocation_statistics
        this->a_strFILE = a_strFILE;
        this->a_uiLINE = a_uiLINE;
#endif
    }
    template <typename _Tyy>
    o_forceinline void    operator>>(_Tyy* instance)
    {
        t_Ty* pChunk = static_cast<t_Ty*>(instance);
        size_t i = count;
        while(i--)
        {
            phantom::initializer<t_Ty>::terminate(typeOf<t_Ty>(), pChunk);
            phantom::installer<t_Ty>::uninstall(typeOf<t_Ty>(), pChunk, 0);
            phantom::constructor<t_Ty>::destroy(pChunk);
            ++pChunk;
        }
        phantom::allocator<t_Ty>::deallocate(static_cast<t_Ty*>(instance), count o_memory_stat_append_parameters_use);
    }
#if o__bool__enable_allocation_statistics
    const char* a_strFILE;
    int  a_uiLINE;
#endif
    size_t count;

};

struct o_export dynamic_delete_function_helper
{
    o_forceinline dynamic_delete_function_helper(o_memory_stat_insert_parameters)
    {
#if o__bool__enable_allocation_statistics
        this->a_strFILE = a_strFILE;
        this->a_uiLINE = a_uiLINE;
#endif
    }
    void    operator>>(void* instance);
#if o__bool__enable_allocation_statistics
    const char* a_strFILE;
    int  a_uiLINE;
#endif
};

template<typename t_Ty>
struct proxy_new_helper
{
    o_forceinline proxy_new_helper()
    {
    }
    o_forceinline t_Ty*    operator>>(t_Ty* instance)
    {
        t_Ty::metaType->install(instance, 0);
        // Force dynamic delete function to the proxy one
        ((rtti_data&)rttiDataOf(instance, (size_t)0)).dynamic_delete_func = &phantom::dynamic_proxy_deleter<t_Ty>::dynamicDelete;
        t_Ty::metaType->initialize(instance);
        return instance;
    }
};

template<typename t_Ty>
struct proxy_delete_helper
{
    o_forceinline proxy_delete_helper(o_memory_stat_insert_parameters)
    {
#if o__bool__enable_allocation_statistics
        this->a_strFILE = a_strFILE;
        this->a_uiLINE = a_uiLINE;
#endif
    }
    template <typename _Tyy>
    o_forceinline void    operator>>(_Tyy* instance)
    {
        t_Ty::metaType->terminate(instance);
        t_Ty::metaType->uninstall(instance, 0);
        static_cast<t_Ty*>(instance)->~t_Ty();
        phantom::allocator<t_Ty>::deallocate(static_cast<t_Ty*>(instance) o_memory_stat_append_parameters_use);
    }
#if o__bool__enable_allocation_statistics
    const char* a_strFILE;
    int  a_uiLINE;
#endif

};

template<typename t_Ty>
struct dynamic_deleter
{
    o_forceinline static void dynamicDelete(void* a_pBase o_memory_stat_append_parameters)
    {
        phantom::delete_helper<t_Ty>(o_memory_stat_insert_parameters_use) >> a_pBase;
    }
};

template<typename t_Ty>
struct dynamic_proxy_deleter
{
    o_forceinline static void dynamicDelete(void* a_pBase o_memory_stat_append_parameters)
    {
        o_dynamic_proxy_delete(t_Ty) a_pBase;
    }
};

o_namespace_end(phantom)



#endif // o_def_new_delete_h__