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
        phantom::extension::installer<t_Ty>::install(instance, 0);
        phantom::extension::initializer<t_Ty>::initialize(instance);
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
            phantom::extension::constructor<t_Ty>::construct(pChunk);
            phantom::extension::installer<t_Ty>::install(pChunk, 0);
            phantom::extension::initializer<t_Ty>::initialize(pChunk);
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
        phantom::extension::constructor<t_Ty>::destroy(instance);
        phantom::extension::allocator<t_Ty>::deallocate(static_cast<t_Ty*>(instance) o_memory_stat_append_parameters_use);
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
        phantom::extension::initializer<t_Ty>::terminate(static_cast<t_Ty*>(instance));
        phantom::extension::installer<t_Ty>::uninstall(static_cast<t_Ty*>(instance), 0);
        phantom::extension::constructor<t_Ty>::destroy(static_cast<t_Ty*>(instance));
        phantom::extension::allocator<t_Ty>::deallocate(static_cast<t_Ty*>(instance) o_memory_stat_append_parameters_use);
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
            phantom::extension::initializer<t_Ty>::terminate(pChunk);
            phantom::extension::installer<t_Ty>::uninstall(pChunk, 0);
            phantom::extension::constructor<t_Ty>::destroy(pChunk);
            ++pChunk;
        }
        phantom::extension::allocator<t_Ty>::deallocate(static_cast<t_Ty*>(instance), count o_memory_stat_append_parameters_use);
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

template<typename t_Ty, typename t_ProxyType>
struct proxy_new_helper
{
    o_forceinline proxy_new_helper(phantom::reflection::Type* a_pType)
        : m_pType(a_pType)
    {
        phantom::reflection::LanguageElement* pElement = (t_Ty*)nullptr; // ensure derives from Object
        t_ProxyType* pProxy = (t_Ty*)nullptr; // ensure derives from Proxy
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

template<typename t_Ty, typename t_ProxyType>
struct proxy_delete_helper
{
    o_forceinline proxy_delete_helper(phantom::reflection::Type* a_pType o_memory_stat_append_parameters)
        : m_pType(a_pType)
    {
        phantom::reflection::LanguageElement* pElement = (t_Ty*)nullptr; // ensure derives from Object
        t_ProxyType* pProxy = (t_Ty*)nullptr; // ensure derives from Proxy
        o_assert(m_pType);
#if o__bool__enable_allocation_statistics
        this->a_strFILE = a_strFILE;
        this->a_uiLINE = a_uiLINE;
#endif
    }
    template <typename _Tyy>
    o_forceinline void    operator>>(_Tyy* instance)
    {
        ((t_Ty*)instance)->~t_Ty();
        m_pType->terminate(instance);
        m_pType->uninstall(instance, 0);
        o__t1_class__default_class_allocator(t_Ty)::deallocate(((t_Ty*)instance));
    }
#if o__bool__enable_allocation_statistics
    const char* a_strFILE;
    int  a_uiLINE;
#endif
    phantom::reflection::Type* m_pType;

};

o_namespace_end(phantom, extension, detail)

o_namespace_begin(phantom, extension)
template<typename t_Ty>
struct dynamic_deleter
{
    o_forceinline static void dynamicDelete(void* a_pBase o_memory_stat_append_parameters)
    {
        phantom::extension::detail::delete_helper<t_Ty>(o_memory_stat_insert_parameters_use) >> a_pBase;
    }
};

o_namespace_end(phantom, extension)



    /// Phantom strongly typed "new" / "delete" "operators" (note the quotes ... for more about that, just check the code bellow)


#define o_full_dynamic_new(...) \
    phantom::extension::detail::dynamic_new_helper(phantom::backupType(phantom::typeByName(#__VA_ARGS__))) >> new (phantom::backupType()->allocate()) __VA_ARGS__

#define o_static_new(...) \
    phantom::extension::detail::new_helper() >> new (o_allocate(__VA_ARGS__)) __VA_ARGS__

#define o_static_new_n(n, ...) \
    phantom::extension::detail::new_n_helper(n) >> o_allocate_n(n, __VA_ARGS__)

#define o_static_delete(...) \
    phantom::extension::detail::delete_helper<__VA_ARGS__>(o_memory_stat_insert_arguments) >>\

#define o_static_delete_n(n, ...) \
    phantom::extension::detail::delete_n_helper<__VA_ARGS__>(n o_memory_stat_append_arguments) >>

#define o_dynamic_new(...) \
    phantom::extension::detail::new_helper() >> new (o_allocate(__VA_ARGS__)) __VA_ARGS__

#define o_static_new_alloc_and_construct_part(...) \
    new (o_allocate(__VA_ARGS__)) __VA_ARGS__

#define o_static_new_install_and_initialize_part(instance) \
    phantom::extension::detail::new_helper() >> instance

#define o_dynamic_proxy_new(proxy, ptr, ...) \
    phantom::extension::detail::proxy_new_helper<__VA_ARGS__, proxy>(ptr) >> new (o__t1_class__default_class_allocator(__VA_ARGS__)::allocate()) __VA_ARGS__

#define o_dynamic_proxy_delete(proxy, ptr, ...) \
    phantom::extension::detail::proxy_delete_helper<__VA_ARGS__, proxy>(ptr o_memory_stat_append_arguments) >> 


#if o__int__reflection_template_use_level == 3

#define o_proxy_new(proxy, ...) \
    o_new(__VA_ARGS__)

#define o_proxy_delete(proxy, ...) \
    o_delete(__VA_ARGS__) 

#define o_new(...) o_static_new(__VA_ARGS__)

#define o_new_n(n, ...) o_static_new_n(n, __VA_ARGS__)

#define o_new_alloc_and_construct_part(...) o_static_new_alloc_and_construct_part(__VA_ARGS__)

#define o_new_install_and_initialize_part(instance) o_static_new_install_and_initialize_part(instance)

#define o_delete(...) o_static_delete(__VA_ARGS__)

#define o_delete_n(n, ...) o_static_delete_n(n,__VA_ARGS__)


#elif o__int__reflection_template_use_level == 2 || o__int__reflection_template_use_level == 1

#define o_proxy_new(proxy, ...) \
    phantom::extension::detail::proxy_new_helper<__VA_ARGS__, proxy>(o_type_of(proxy)) >> new (o__t1_class__default_class_allocator(__VA_ARGS__)::allocate()) __VA_ARGS__

#define o_proxy_delete(proxy, ...) \
    phantom::extension::detail::proxy_delete_helper<__VA_ARGS__, proxy>(o_type_of(proxy) o_memory_stat_append_arguments) >> 

#define o_new(...) \
    phantom::extension::detail::dynamic_new_helper(phantom::backupType()) >> new (phantom::backupType(o_type_of(__VA_ARGS__))->allocate()) __VA_ARGS__

#define o_new_n(n, ...) \
    phantom::extension::detail::dynamic_new_n_helper(phantom::backupType(), n) >> (__VA_ARGS__*)phantom::backupType(o_type_of(__VA_ARGS__))->allocate(n)

#define o_delete(...) \
    phantom::extension::detail::dynamic_delete_helper<__VA_ARGS__>(o_type_of(__VA_ARGS__) o_memory_stat_append_arguments) >>

#define o_delete_n(n, ...) \
    phantom::extension::detail::dynamic_delete_n_helper<__VA_ARGS__>(o_type_of(__VA_ARGS__), n o_memory_stat_append_arguments) >>

#define o_new_alloc_and_construct_part(...) o_static_new_alloc_and_construct_part(__VA_ARGS__)

#define o_new_install_and_initialize_part(instance) o_static_new_install_and_initialize_part(instance)

#else // if o__int__reflection_template_use_level == 0

#define o_proxy_new(proxy, ...) \
    phantom::extension::detail::proxy_new_helper<__VA_ARGS__, proxy>(phantom::backupType(o_dynamic_type_of(proxy))) >> new (o__t1_class__default_class_allocator(__VA_ARGS__)::allocate()) __VA_ARGS__

#define o_proxy_delete(proxy, ...) \
    phantom::extension::detail::proxy_delete_helper<__VA_ARGS__, proxy>(o_dynamic_type_of(proxy) o_memory_stat_append_arguments) >> 

#define o_new(...) \
    phantom::extension::detail::new_helper(phantom::backupType(phantom::typeByName(#__VA_ARGS__))) >> new (phantom::backupType()->allocate()) __VA_ARGS__

#define o_force_static_new(...)\
    phantom::extension::detail::force_static_new_helper() >> new (o_allocate(__VA_ARGS__)) __VA_ARGS__

#define o_new_n(n, ...) \
    phantom::extension::detail::new_n_helper(phantom::backupType(phantom::typeByName(#__VA_ARGS__)), n) >> phantom::backupType()->allocate(n)

#define o_new_alloc_and_construct_part(...) \
    new (phantom::typeByName(#__VA_ARGS__))->allocate()) __VA_ARGS__

#define o_delete(...) \
    phantom::extension::detail::delete_helper<__VA_ARGS__>(phantom::typeByName(#__VA_ARGS__) o_memory_stat_append_arguments) >>

#define o_force_static_delete(...) \
    phantom::extension::detail::force_static_delete_helper<__VA_ARGS__>(o_memory_stat_insert_arguments) >>

#define o_delete_n(n, ...) \
    phantom::extension::detail::delete_n_helper<__VA_ARGS__>(phantom::typeByName(#__VA_ARGS__), n o_memory_stat_append_arguments) >>

#define o_new_alloc_and_construct_part(...) o_static_new_alloc_and_construct_part(__VA_ARGS__)

#define o_new_install_and_initialize_part(instance) o_static_new_install_and_initialize_part(instance)

#endif