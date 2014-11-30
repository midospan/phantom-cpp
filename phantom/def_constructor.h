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

#ifndef o_def_constructor_h__
#define o_def_constructor_h__

o_namespace_begin(phantom)

/* constructor */
namespace detail
{
    enum default_constructor_id
    {
        default_constructor_placement_new,
        default_constructor_default_construction_forbidden,
        default_constructor_all_default_forbidden,
        default_constructor_none,
    };

    template<typename t_Ty>
    struct default_constructor_helper<t_Ty, default_constructor_all_default_forbidden>
    {
    public:
        o_forceinline static void construct(t_Ty* a_pInstance) { o_unused(a_pInstance); o_exception(exception::unsupported_member_function_exception, "type is abstract and cannot be constructed/destroyed"); }
        o_forceinline static void destroy(t_Ty* a_pInstance) { o_unused(a_pInstance); o_exception( exception::unsupported_member_function_exception, "type is abstract and cannot be constructed/destroyed"); }
        o_forceinline static void construct(t_Ty* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize) { o_unused(a_pInstance); o_unused(a_uiCount); o_unused(a_uiChunkSectionSize); o_exception( exception::unsupported_member_function_exception, "type is abstract and cannot be constructed/destroyed"); }
        o_forceinline static void destroy(t_Ty* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize) { o_unused(a_pInstance); o_unused(a_uiCount); o_unused(a_uiChunkSectionSize); o_exception( exception::unsupported_member_function_exception, "type is abstract and cannot be constructed/destroyed"); }
    };

    template<typename t_Ty>
    struct default_constructor_helper<t_Ty, default_constructor_none>
    {
    public:
        o_forceinline static void construct(t_Ty* a_pInstance) {o_unused(a_pInstance);  }
        o_forceinline static void destroy(t_Ty* a_pInstance) {o_unused(a_pInstance);  }
        o_forceinline static void construct(t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize) { o_unused(a_pChunk); o_unused(a_uiCount); o_unused(a_uiChunkSectionSize); }
        o_forceinline static void destroy(t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize) {o_unused(a_pChunk); o_unused(a_uiCount); o_unused(a_uiChunkSectionSize);  }
    };

    template<typename t_Ty>
    struct default_constructor_helper<t_Ty, default_constructor_default_construction_forbidden>
    {
    public:
        o_forceinline static void construct(t_Ty* a_pInstance) { o_unused(a_pInstance); o_exception(exception::unsupported_member_function_exception, "type hasn't default constructor and cannot be constructed"); }
        o_forceinline static void destroy(t_Ty* a_pInstance) { destructor_protection_hacker<t_Ty>::apply(a_pInstance); }
        o_forceinline static void construct(t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize) { o_unused(a_pChunk); o_unused(a_uiCount); o_unused(a_uiChunkSectionSize); o_exception(exception::unsupported_member_function_exception, "type hasn't default constructor and cannot be constructed"); }
        o_forceinline static void destroy(t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize)
        {
            byte* pChunk = reinterpret_cast<byte*>(a_pChunk);
            for(;a_uiCount--;pChunk += a_uiChunkSectionSize)
                destructor_protection_hacker<t_Ty>::apply(pChunk);
        }
    };

    template<typename t_Ty>
    struct default_constructor_helper<t_Ty, default_constructor_placement_new>
    {
    public:
        o_forceinline static void construct(t_Ty* a_pInstance) { constructor_protection_hacker<t_Ty>::apply(a_pInstance); }
        o_forceinline static void destroy(t_Ty* a_pInstance) { destructor_protection_hacker<t_Ty>::apply(a_pInstance); }
        o_forceinline static void construct(t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize)
        {
            byte* pChunk = reinterpret_cast<byte*>(a_pChunk);
            for(;a_uiCount--;pChunk += a_uiChunkSectionSize)
                phantom::constructor_caller<t_Ty()>::apply(pChunk, nullptr);
        }
        o_forceinline static void destroy(t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize)
        {
            byte* pChunk = reinterpret_cast<byte*>(a_pChunk);
            for(;a_uiCount--;pChunk += a_uiChunkSectionSize)
                destructor_protection_hacker<t_Ty>::apply(pChunk);
        }
    };

    template<typename t_Ty>
    struct safe_constructor_ 
    {
        static void safeConstruct(void* a_pInstance) { constructor<t_Ty>::construct((t_Ty*)a_pInstance); }
    };
    template<> struct safe_constructor_<bool>                  {    static void safeConstruct(void* a_pInstance) { *((bool*)a_pInstance) = 0; } };
    template<> struct safe_constructor_<char>                  {    static void safeConstruct(void* a_pInstance) { *((char*)a_pInstance) = 0; } };
    template<> struct safe_constructor_<unsigned char>         {    static void safeConstruct(void* a_pInstance) { *((unsigned char*)a_pInstance) = 0; } };
    template<> struct safe_constructor_<short>                 {    static void safeConstruct(void* a_pInstance) { *((short*)a_pInstance) = 0; } };
    template<> struct safe_constructor_<unsigned short>        {    static void safeConstruct(void* a_pInstance) { *((unsigned short*)a_pInstance) = 0; } };
    template<> struct safe_constructor_<int>                   {    static void safeConstruct(void* a_pInstance) { *((int*)a_pInstance) = 0; } };
    template<> struct safe_constructor_<unsigned int>          {    static void safeConstruct(void* a_pInstance) { *((unsigned int*)a_pInstance) = 0; } };
    template<> struct safe_constructor_<long>                  {    static void safeConstruct(void* a_pInstance) { *((long*)a_pInstance) = 0; } };
    template<> struct safe_constructor_<unsigned long>         {    static void safeConstruct(void* a_pInstance) { *((unsigned long*)a_pInstance) = 0; } };
    template<> struct safe_constructor_<long long>             {    static void safeConstruct(void* a_pInstance) { *((long long*)a_pInstance) = 0; } };
    template<> struct safe_constructor_<unsigned long long>    {    static void safeConstruct(void* a_pInstance) { *((unsigned long long*)a_pInstance) = 0; } };
    template<> struct safe_constructor_<long double>           {    static void safeConstruct(void* a_pInstance) { *((long double*)a_pInstance) = 0; } };
    template<> struct safe_constructor_<float>                 {    static void safeConstruct(void* a_pInstance) { *((float*)a_pInstance) = 0; } };
    template<> struct safe_constructor_<double>                {    static void safeConstruct(void* a_pInstance) { *((double*)a_pInstance) = 0; } };
}

template<typename t_Ty>
struct default_constructor : public detail::default_constructor_helper<t_Ty,
    boost::is_abstract<t_Ty>::value
    ? phantom::has_virtual_destructor_cascade<t_Ty>::value
    ? detail::default_constructor_default_construction_forbidden
    : detail::default_constructor_all_default_forbidden // abstract
    : boost::is_class<t_Ty>::value
    ? boost::is_pod<t_Ty>::value
    ? detail::default_constructor_none
    : NOT(phantom::is_default_constructible_and_not_abstract<t_Ty>::value)
    ? detail::default_constructor_default_construction_forbidden // no default constructor
    : detail::default_constructor_placement_new
    : detail::default_constructor_none
>
{
    o_rebind(default_constructor)
};


////////////////////////////////////////////////////////////////////////////////////////////////////
/// \struct constructor
///
/// \brief  Constructor. (see instance creation process)
/// 		Construction : By default Phantom uses C++ placement new for instanciable classes
/// 		Destruction : By default Phantom uses C++ destructor call for instanciable classes
///
////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename t_Ty>
struct constructor : public default_constructor<t_Ty>
{
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \struct safe_constructor
///
/// \brief  safe_constructor.
/// 		Provides safe construction of type instances
///
////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename t_Ty>
struct safe_constructor : public detail::safe_constructor_<t_Ty>
{
};

o_namespace_end(phantom)

#endif // o_def_constructor_h__