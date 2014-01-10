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



#ifndef o_phantom_Phantom_h__
#define o_phantom_Phantom_h__

// ********************************************************************* //
// ******************************************************************* ///
// **************************** PREREQUISITES ************************** //
// ******************************************************************* ///
// ********************************************************************* //

#ifndef DOXYGEN_SRC_PREPROCESSING

/* ************** PHANTOM CONFIGURATION *********** */
#include "phantom/def_config.h"
#include "phantom/def_custom.h"
/* ************* UNIVERSAL PREDEFINITION ********** */
#ifdef _UNICODE
#    ifndef UNICODE
#        define UNICODE
#    endif
#elif defined(UNICODE)
#    define _UNICODE
#endif

#ifdef _DEBUG
#    ifndef DEBUG
#        define DEBUG
#    endif
#elif defined(DEBUG)
#    define _DEBUG
#endif

// Ensure export in phantom(_d).dll when using o_export
#include <phantom/_kernel.noclassdef.h>
/* ******************* NEDMALLOC ****************** */
#if o__bool__nedalloc
#    include <phantom/memory/nedmalloc.h>
#endif
/* ********************** STD ********************* */
#if o_COMPILER == o_COMPILER_VISUAL_STUDIO

#     if defined(_NATIVE_WCHAR_T_DEFINED)
#         define o_BUILT_IN_WCHAR_T 1
#     else
#         define o_BUILT_IN_WCHAR_T 0
#     endif

#elif o_COMPILER == o_COMPILER_GCC
#        define o_BUILT_IN_WCHAR_T 0
#endif

#if (o_COMPILER == o_COMPILER_GCC)
#include <inttypes.h>
#include <stdlib.h>
#endif

#if (o_OPERATING_SYSTEM == o_OPERATING_SYSTEM_WINDOWS)
#    include <conio.h>
#endif

#include <assert.h>
#include <stdio.h>
#include <cstdio>

#include <iostream>
#include <memory>
#include <iomanip>
#include <sstream>
#include <string>
#include <map>
#include <set>
#include <bitset>
#if o_HAS_CPP0X 
#   include <unordered_set>
#   include <unordered_map>
#else
#   include <tr1/unordered_set>
#   include <tr1/unordered_map>
#endif
#include <list>
#include <deque>
#include <queue>
#include <stack>
#include <vector>
#include <limits>
#include <algorithm>
/* ********************* BOOST ******************** */
#if !defined(Q_MOC_RUN)
#include <boost/foreach.hpp>
#include <boost/pool/pool_alloc.hpp>
#include <boost/pool/object_pool.hpp>
#include <boost/type_traits.hpp>
#include <boost/lexical_cast.hpp>
#if o__bool__enable_serialization
#include <boost/property_tree_custom/ptree.hpp>
#endif
#endif // Q_MOC_RUN

/* ***************** FASTDELEGATE ***************** */
#include <fastdelegate/FastDelegate.h>
#include <fastdelegate/FastDelegateBind.h>
/* *************** END DEPENDENCIES *************** */
#else
#include "phantom/def_custom.h"
#endif

/* ******************** PHANTOM ******************* */
#include "phantom/def_macros.h"
#include "phantom/def_alias.h"
#include "phantom/_global.classdef.h"
#include "phantom/def_export.h"
#include "phantom/def_console.h"
#include "phantom/def_memory.h"
#include "phantom/def_types.h"
#include "phantom/def_fwd.h"
#include "phantom/def_traits.h"
#include "phantom/def_container.h"


o_begin_phantom_namespace()

namespace util {}

namespace detail
{
    class dynamic_initializer_handle;
    template<typename t_Ty>
    struct module_installer_template_auto_registrer;
    template<typename t_Ty, boolean t_is_reflected_class>
    struct is_helper;
    template<typename t_Ty, boolean t_is_ptr_to_reflected_class>
    struct as_helper;

}

namespace connection
{
    class slot;
    class slot_pool;
}

namespace reflection
{
    template<typename> struct type_of;
    template<typename> struct class_of;
    template<typename> struct meta_class_type_of;
    template<typename> struct template_specialization_adder;
    template<typename> struct template_specialization_of;
    struct typedef_registrer;

    namespace detail
    {
        template<typename> struct type_name_of_helper_;
        template<typename> struct root_pointed_type_of_;
        template<typename> struct pointed_type_of_;
    }

    static phantom::reflection::Class*                 g_PHANTOM_RESERVED_class = 0;
    static phantom::reflection::Namespace*             g_PHANTOM_RESERVED_namespace = 0;
    static phantom::reflection::TemplateSpecialization*g_PHANTOM_RESERVED_template_specialization = 0;
}

template <typename t_Ty>
o_forceinline o_NESTED_TYPE phantom::reflection::meta_class_type_of<t_Ty>::type* typeOf()
{
    return phantom::reflection::type_of<t_Ty>::object();
}

template<typename t_Ty>
typename phantom::reflection::meta_class_type_of<t_Ty>::type*  classOf()
{
    o_static_assert(boost::is_class<t_Ty>::value);
    return phantom::reflection::type_of<t_Ty>::object();
}

// function forwarding

o_export boolean                                        is(reflection::Class* a_pTestedClass, void*    in);
template<typename t_Ty, typename t_ITy>
inline boolean                                          is(t_ITy*    in);

template<typename t_Ty>
inline boolean                                          is(void*    in);

template<typename t_Ty, typename t_ITy>
inline t_Ty                                             as(t_ITy    in);
template <typename t_Ty>
 o_NESTED_TYPE phantom::reflection::meta_class_type_of<t_Ty>::type* typeOf();
template<typename t_Ty>
 phantom::reflection::ReferenceType*                    referenceTypeOf();
template<typename t_Ty>
 phantom::reflection::Type*                             constTypeOf();
template<typename t_Ty>
 phantom::reflection::ArrayType*                        arrayTypeOf(size_t);
template<typename t_Ty>
 phantom::reflection::DataPointerType*                  pointerTypeOf();

 o_export phantom::reflection::Namespace*               namespaceByList( list<string>* a_pNamespaceNameAsStringList );
 o_export phantom::reflection::Namespace*               namespaceByName( const string& a_strNamespaceName );
 o_export inline phantom::reflection::Namespace*        rootNamespace();
 o_export inline phantom::reflection::SourceFile*       sourceFile(const string& a_strAbsoluteName);
 o_export inline void                                   discardSourceFile(phantom::reflection::SourceFile* a_pSourceFile);
 o_export phantom::reflection::Type*                    typeByName(const string& a_strName, phantom::reflection::LanguageElement* a_pRootScope = reinterpret_cast<phantom::reflection::LanguageElement*>(rootNamespace())) ;
 o_export phantom::reflection::Type*					typeByNameCascade(const string& a_strName, phantom::reflection::LanguageElement* a_pRootScope = reinterpret_cast<phantom::reflection::LanguageElement*>(rootNamespace())) ; 
 o_export string                                        encodeQualifiedDecoratedNameToIdentifierName(const string& a_strTypeName) ;
 o_export string                                        decodeQualifiedDecoratedNameFromIdentifierName(const string& a_strTypeName) ;
 o_export phantom::reflection::LanguageElement*         elementByName(const string& a_strName, phantom::reflection::LanguageElement* a_pRootElement = reinterpret_cast<phantom::reflection::LanguageElement*>(rootNamespace())) ;
 o_export void                                          elementsByClass(reflection::Class* a_pClass, vector<reflection::LanguageElement*>& out, phantom::reflection::LanguageElement* a_pRootElement = reinterpret_cast<phantom::reflection::LanguageElement*>(rootNamespace())) ;
 o_export phantom::reflection::LanguageElement*			elementByNameCascade(const string& a_strName, phantom::reflection::Namespace* a_pNamespace = rootNamespace());
 o_export phantom::reflection::Type*                    typeByGuid(uint guid) ;
 o_export phantom::reflection::LanguageElement*         elementByGuid(uint guid) ;
 template<typename t_Ty>
 o_forceinline    t_Ty*                                 elementByNameAs(const string& a_strName, phantom::reflection::LanguageElement* a_pRootElement = reinterpret_cast<phantom::reflection::LanguageElement*>(rootNamespace())) { return as<t_Ty*>(elementByName(a_strName, a_pRootElement)); }
 o_export phantom::reflection::Class*                   classByName(const string& a_strQualifiedName, phantom::reflection::LanguageElement* a_pRootScope = reinterpret_cast<phantom::reflection::LanguageElement*>(rootNamespace())) ;

 o_export void*                                         baseOf(void const* in);
 o_export phantom::reflection::Class*                   classOf(void const* in);
 o_export phantom::reflection::Class*                   classAt(void const* in);
 o_export const phantom::rtti_data&                     rttiDataOf(void const* in);
 o_export void                                          rttiLayoutOf(void const* in, vector<void*>& out);
 o_export void                                          dynamicDelete(void* in o_memory_stat_append_parameters);
 o_export inline void                                   addRttiData(void const* in, const rtti_data& data);
 o_export inline void                                   replaceRttiData(void const* in, const rtti_data& data);
 o_export inline void                                   removeRttiData(void const* in);

 o_export void                                          assertion BOOST_PREVENT_MACRO_SUBSTITUTION ( const character* e, const character* m , const char* f , uint l);
 o_export void                                          warning BOOST_PREVENT_MACRO_SUBSTITUTION (const character* e, const character* m, const char* f, uint l);
 o_export void                                          error BOOST_PREVENT_MACRO_SUBSTITUTION (const character* e, const character* m, const char* f, uint l);

 o_export size_t                                        currentThreadId();
 o_export void                                          yieldCurrentThread();

 o_export void                                          installReflection(const string& a_strName, const string& a_strFileName, size_t a_PlatformHandle);
 o_export void                                          uninstallReflection(const string& a_strName);

 o_export void                                          pushModule(Module* a_pModule);
 o_export Module*                                       popModule();
 o_export Module*                                       currentModule();
 o_export Module*                                       moduleByName(const string& a_strName);
 o_export Module*                                       moduleByFileName(const string& a_strFileName);
 o_export map<string, Module*>::const_iterator          beginModules();
 o_export map<string, Module*>::const_iterator          endModules();
 o_export void                                          release();

/**
 * \brief data stores a memory address with the reflection Type associated
 */
class data
{
public:
    data() : m_address(0), m_type(0) {}
    data(void* a_pAddress, reflection::Type* a_pType)
        : m_address(a_pAddress)
        , m_type(a_pType)
    {

    }
    inline bool isNull() const { return m_address == NULL; }
    template<typename t_Ty>
    inline data(t_Ty* const a_address);

    template<typename t_Ty>
    inline data const& operator=(t_Ty* const a_address);

    template<typename t_Ty>
    inline t_Ty* as() const;

    phantom::data       cast(reflection::Type* a_pTargetType) const;
    void*               address() const { return m_address; }
    reflection::Type*   type() const { return m_type; }
    boolean             operator==(const phantom::data& a_Other) const
    {
        return a_Other.m_address == m_address AND a_Other.m_type == m_type;
    }
    boolean             operator!=(const phantom::data& a_Other) const
    {
        return a_Other.m_address != m_address OR a_Other.m_type != m_type;
    }
    boolean             operator<(const phantom::data& a_Other) const
    {
        return m_address == a_Other.m_address ? m_type < a_Other.m_type : m_address < a_Other.m_address;
    }
    inline void        destroy() ;

protected:
    void*              m_address;
    reflection::Type*  m_type;
};

typedef data variable;
typedef std::pair<data,data> data_pair;

/**
  * \brief object stores a memory address with the reflection ClassType associated
  */
class object
{
public:
    object() : m_address(0), m_class_type(0) {}
    object(void* a_pAddress, reflection::ClassType* a_pClassType)
        : m_address(a_pAddress)
        , m_class_type(a_pClassType)
    {

    }
    template<typename t_Ty>
    inline object(t_Ty* const a_address);

    template<typename t_Ty>
    inline object& operator=(t_Ty* const a_address);

    template<typename t_Ty>
    inline t_Ty* as  ();

    boolean isNull() const { return m_address == nullptr; }
    void destroy();

    operator data  ()
    {
        return data(m_address,(reflection::Type*)m_class_type);
    }

    boolean             operator==(const phantom::object& a_Other) const
    {
        return a_Other.m_address == m_address AND a_Other.m_class_type == m_class_type;
    }

    boolean             operator!=(const phantom::object& a_Other) const
    {
        return a_Other.m_address != m_address OR a_Other.m_class_type != m_class_type;
    }

    void*                   address() const { return m_address; }
    reflection::ClassType*  classType() const { return m_class_type; }

protected:
    void*                   m_address;
    reflection::ClassType*  m_class_type;
};


/**
 * \struct rtti_data
 *
 * \brief Information about each layout part of any object instanciated with phantom.
 *
 * \description This struct is used to store all information needed
 * 				internally by phantom to perform operations on objects
 * 				such as cast and slot connections. It keeps internally
 * 				all the memory layout address of all objects to apply
 * 				dynamic cast. For example if a class C multi-inherits from the classes
 * 				A and B, any instance of C will have two rtti_data stored in
 * 				the phantom system : one for the A layout, one for the B layout.
 * 				That means that each object instanciated with o_new will have at least,
 * 				by default, a memory overhead of :
 * 				sizeof(rtti_data) + unordered_map entry overhead
 * 				If you don't want your object to have rtti_data stored, you can use o_default_new
 * 				which mimics the C++ standard new operator. This implies that you won't be
 * 				able to use dynamic cast on these objects or connect them via the signal/slot system.
 */

struct rtti_data
{
    rtti_data() {}
    rtti_data(phantom::reflection::Class* bc
                , phantom::reflection::Class*    tc
                , void*    b
                , connection::slot_pool* csa
                , dynamic_delete_func_t a_dynamic_delete_func)
        : object_class(bc)
        , layout_class(tc)
        , base(b)
        , connection_slot_allocator(csa)
        , dynamic_delete_func(a_dynamic_delete_func)
    {
        o_assert((bc == nullptr AND b == nullptr) OR dynamic_delete_func);
    }
    o_forceinline boolean isBase() const { return object_class == layout_class; }
    o_forceinline boolean isNull() const { return object_class == NULL; }
    inline void deleteNow(o_memory_stat_insert_parameters) const;

    o_forceinline void*   cast(reflection::Class* a_pTargetClass) const ;
    o_forceinline phantom::data   data() const { return phantom::data(base,(reflection::Type*)object_class); }
    o_forceinline phantom::data   object() const { return phantom::object(base,(reflection::ClassType*)object_class); }

    phantom::reflection::Class*     object_class;
    phantom::reflection::Class*     layout_class;
    void*                           base;
    connection::slot_pool*          connection_slot_allocator;
    dynamic_delete_func_t           dynamic_delete_func;
};


template<typename t_Ty>
inline data::data(t_Ty* const a_address)
{
    const rtti_data& rd = rttiDataOf(a_address);
    m_address = rd.base ? rd.base : a_address;
    if(rd.object_class)
        m_type = (phantom::reflection::Type*)rd.object_class ;
    else
        m_type = typeOf<t_Ty>();
    o_assert(m_type, "t_Ty must have reflection");
}


 template<typename t_Ty>
 inline data const& data::operator=(t_Ty* const a_address)
 {
     const rtti_data& rd = rttiDataOf(a_address);
     m_address = rd.base ? rd.base : a_address;
     if(rd.object_class)
         m_type = (phantom::reflection::Type*)rd.object_class ;
     else
         m_type = typeOf<t_Ty>();
     return *this;
 }


 template<typename t_Ty>
 inline object::object(t_Ty* const a_address)
 {
     // class
     const rtti_data& rd = rttiDataOf(a_address);
     m_address = rd.base ? rd.base : a_address;
     if(rd.object_class)
         m_class_type = (phantom::reflection::ClassType*)rd.object_class ;
     else
         m_class_type = typeOf<t_Ty>();
 }

 template<typename t_Ty>
 inline object& object::operator=(t_Ty* const a_address)
 {
     const rtti_data& rd = rttiDataOf(a_address);
     m_address = rd.base ? rd.base : a_address;
     if(rd.object_class)
         m_class_type = (phantom::reflection::ClassType*)rd.object_class ;
     else
         m_class_type = typeOf<t_Ty>();
     return *this;
 }

 o_export inline const phantom::rtti_data&            rttiDataOf(void const* in);
 o_export inline void                                 rttiLayoutOf(void const* in, vector<void*>& out);

o_export void default_assert(const character* expression, const character* message, const char* file, uint line);
o_export void default_warning(const character* expression, const character* message, const char* file, uint line);
o_export void default_error(const character* expression, const character* message, const char* file, uint line);
o_export void default_log(int level, const char* file, uint line, const char* message, va_list args);


template<typename t_Ty>
o_forceinline phantom::reflection::Type*        pointedTypeOf()
{
    return reflection::detail::pointed_type_of_<t_Ty>::object();
}

template<typename t_Ty>
o_forceinline phantom::reflection::Type*        rootPointedTypeOf()
{
    return reflection::detail::root_pointed_type_of_<t_Ty>::object();
}

template <typename t_Ty>
o_forceinline string                            decoratedTypeNameOf()
{
    return reflection::detail::type_name_of_helper_<t_Ty>::decoratedName();
}

template <typename t_Ty>
o_forceinline string                            typeNameOf()
{
    return reflection::detail::type_name_of_helper_<t_Ty>::name();
}

template <typename t_Ty>
o_forceinline string                            qualifiedTypeNameOf()
{
    return reflection::detail::type_name_of_helper_<t_Ty>::qualifiedName();
}

template <typename t_Ty>
o_forceinline string                            qualifiedDecoratedTypeNameOf()
{
    return reflection::detail::type_name_of_helper_<t_Ty>::qualifiedDecoratedName();
}

template <typename t_Ty>
o_forceinline const char*                       namespaceNameOf()
{
    return reflection::detail::type_name_of_helper_<t_Ty>::namespaceName();
}

template <typename t_Ty>
o_forceinline const char*                       classScopeNameOf()
{
    return reflection::detail::type_name_of_helper_<t_Ty>::classScopeName();
}

template <typename t_Ty>
o_forceinline
    phantom::reflection::TemplateSpecialization* templateSpecializationOf()
{
    return phantom::reflection::template_specialization_of<t_Ty>::object();
}

template <typename t_Ty>
o_forceinline phantom::reflection::Type*        registerType()
{
    return phantom::typeOf<t_Ty>();
}

template <typename t_Ty>
o_forceinline void                              registerTypedef(const char* a_strNamespace, const char* a_strTypedef)
{
    phantom::reflection::typedef_registrer(a_strNamespace, a_strTypedef, phantom::typeOf<t_Ty>());
}

template <typename t_Ty>
o_forceinline void                              registerTypedef(const char* a_strTypedef)
{
    phantom::reflection::typedef_registrer(a_strTypedef, phantom::typeOf<t_Ty>());
}

o_export boolean           canConnect(phantom::reflection::Signal* a_pSignal, phantom::reflection::InstanceMemberFunction* a_pMemberFunction );
o_export connection::slot const* connect(void* a_pSender, const character* a_pSignal, void* a_pReceiver, const character* a_pMemberFunction);
o_export connection::slot const* disconnect(void* a_pSender, const character* a_pSignal, void* a_pReceiver, const character* a_pMemberFunction);
o_export connection::slot const* connect(void* a_pSender, phantom::reflection::Signal* a_pSignal, void* a_pReceiver, phantom::reflection::InstanceMemberFunction* a_pMemberFunction);
o_export connection::slot const* disconnect(void* a_pSender, phantom::reflection::Signal* a_pSignal, void* a_pReceiver, phantom::reflection::InstanceMemberFunction* a_pMemberFunction);
o_export connection::slot const* tryConnect(void* a_pSender, const character* a_pSignal, void* a_pReceiver, const character* a_pMemberFunction);
o_export connection::slot const* tryDisconnect(void* a_pSender, const character* a_pSignal, void* a_pReceiver, const character* a_pMemberFunction);

o_export void       assertion BOOST_PREVENT_MACRO_SUBSTITUTION ( const character* e, const character* m , const char* f , uint l);
o_export void       warning BOOST_PREVENT_MACRO_SUBSTITUTION (const character* e, const character* m, const char* f, uint l);
o_export void       error BOOST_PREVENT_MACRO_SUBSTITUTION (const character* e, const character* m, const char* f, uint l);
o_export void       log BOOST_PREVENT_MACRO_SUBSTITUTION (int level, const char* file, uint line, const char* message, ...);


o_end_phantom_namespace()

/* EXTENSION (allocator, constructor, installer, serializer, initializer,  ... to be continued) */

template<typename t_Ty>
class phantom_proxy_generator__________;

template<typename t_Ty, typename t_Proxy>
class phantom_proxy_generator_base_____
{
protected:
    typedef t_Ty phantom_proxy_generator_reflection_self_type;
    typedef t_Ty phantom_proxy_generator_statechart_self_type;
    typedef t_Proxy phantom_proxy_generator_reflection_proxy_type;
    typedef t_Proxy phantom_proxy_statechart_proxy_type;

    int                                         m_PHANTOM_RESERVED_no_signal;
    int                                         PHANTOM_CODEGEN_m_slot_list_of_m_PHANTOM_RESERVED_no_signal;
};

namespace phantom {
    namespace state {
        namespace native {
            template <typename t_Ty>            class state_machine_data;
        }
        class base_state_machine_data;
    }
    namespace serialization {
        class data_guid_base;
    }
    using serialization::data_guid_base;
}

#include "phantom/def_connection.h"
#include "phantom/def_serialization.h"
#include "phantom/def_extension.h"

o_namespace_begin(phantom)

#define o_allocate(...) phantom::allocate<__VA_ARGS__>(o_memory_stat_insert_arguments)
#define o_allocate_n(n, ...) phantom::allocate<__VA_ARGS__>(n o_memory_stat_append_arguments)
#define o_deallocate(exp,  ...) phantom::deallocate<__VA_ARGS__>(exp o_memory_stat_append_arguments)
#define o_deallocate_n(exp, n, ...) phantom::deallocate<__VA_ARGS__>(exp, n o_memory_stat_append_arguments)

#define o_dynamic_pool_allocate(s) phantom::dynamicPoolAllocate(s o_memory_stat_append_arguments)
#define o_dynamic_pool_allocate_n(n, s) phantom::dynamicPoolAllocate(s, n  o_memory_stat_append_arguments)
#define o_dynamic_pool_deallocate(exp, s) phantom::dynamicPoolDeallocate(s, exp o_memory_stat_append_arguments)
#define o_dynamic_pool_deallocate_n(exp, n, s) phantom::dynamicPoolDeallocate(s, exp, n o_memory_stat_append_arguments)

template<typename t_Ty>
inline t_Ty* allocate(o_memory_stat_insert_parameters)
{
    return phantom::extension::allocator<t_Ty>::allocate(o_memory_stat_insert_parameters_use);
}

template<typename t_Ty>
inline void deallocate(t_Ty* ptr o_memory_stat_append_parameters)
{
    return phantom::extension::allocator<t_Ty>::deallocate(ptr o_memory_stat_append_parameters_use);
}

template<typename t_Ty>
t_Ty* allocate(size_t n o_memory_stat_append_parameters)
{
    o_assert(n);
    return phantom::extension::allocator<t_Ty>::allocate(n o_memory_stat_append_parameters_use);
}

template<typename t_Ty>
void deallocate(t_Ty* ptr, size_t n o_memory_stat_append_parameters)
{
    o_assert(n);
    return phantom::extension::allocator<t_Ty>::deallocate(ptr, n o_memory_stat_append_parameters_use);
}

o_namespace_end(phantom)



#include "phantom/def_reflection.h"
#include "phantom/def_statechart.h"

#include "phantom/def_modules.h"

o_declare(class, phantom, Phantom)
    o_declare(class, phantom, Object)

    o_declare(class, phantom, util, Iterator)

    o_declare(class, phantom, reflection, SourceFile)
    o_declare(class, phantom, reflection, Signature)
    o_declare(class, phantom, reflection, Subroutine)
    o_declare(class, phantom, reflection, Function)
    o_declare(class, phantom, reflection, Variable)
    o_declare(class, phantom, reflection, IteratorConstant)
    o_declare(class, phantom, reflection, IteratorVariable)
    o_declare(class, phantom, reflection, StaticVariable)
    o_declare(class, phantom, reflection, Member)
    o_declare(class, phantom, reflection, MemberFunction)
    o_declare(class, phantom, reflection, StaticMemberFunction)
    o_declare(class, phantom, reflection, Constructor)
    o_declare(class, phantom, reflection, InstanceMemberFunction)
    o_declare(class, phantom, reflection, Signal)
    o_declare(class, phantom, reflection, DataMember)
    o_declare(class, phantom, reflection, InstanceDataMember)
    o_declare(class, phantom, reflection, StaticDataMember)
    o_declare(class, phantom, reflection, Property)
    o_declare(class, phantom, reflection, Collection)
    o_declare(class, phantom, reflection, ValueMember)
    o_declare(class, phantom, reflection, ValueMemberBinding)
    o_declare(class, phantom, reflection, Type)
    o_declare(class, phantom, reflection, PrimitiveType)
    o_declare(class, phantom, reflection, PointerType)
    o_declare(class, phantom, reflection, DataPointerType)
    o_declare(class, phantom, reflection, ConstDataPointerType)
    o_declare(class, phantom, reflection, ReferenceType)
    o_declare(class, phantom, reflection, ConstReferenceType)
    o_declare(class, phantom, reflection, ArrayType)
    o_declare(class, phantom, reflection, Class)
    o_declare(class, phantom, reflection, PODUnion)
    o_declare(class, phantom, reflection, PODStruct)
    o_declare(class, phantom, reflection, Union)
    o_declare(class, phantom, reflection, Enum)
    o_declare(class, phantom, reflection, LanguageElement)
    o_declare(class, phantom, reflection, TemplateElement)
    o_declare(class, phantom, reflection, Constant)
    o_declare(class, phantom, reflection, VirtualMemberFunctionTable)
    o_declare(class, phantom, reflection, Namespace)
    o_declare(class, phantom, reflection, TemplateSpecialization)

    o_declare(class, phantom, state, StateMachine)
    o_declare(class, phantom, state, StateMachineElement)
    o_declare(class, phantom, state, State)
    o_declare(class, phantom, state, Track)
    o_declare(class, phantom, state, Event)
    o_declare(class, phantom, state, Reaction)
    o_declareT(class, phantom, state, native, (typename), TNativeState)
    o_declareT(class, phantom, state, native, (typename, typename, typename, typename), TNativeTransition)
    o_declareT(class, phantom, state, native, (typename), TNativeTrack)
    o_declareT(class, phantom, state, native, (typename,phantom::boolean), TNativeTrackHelper)
    o_declareT(class, phantom, state, native, (typename), TNativeStateMachine)
    o_declareT(class, phantom, state, native, (typename,bool), TNativeStateMachineHelper)

    o_declare(class, phantom, serialization, Node)
    o_declare(class, phantom, serialization, DefaultNode)
    o_declare(class, phantom, serialization, DataBase)
    o_declare(class, phantom, serialization, DataStateBase)

#include "phantom/def_util.h"
#include "phantom/def_exceptions.h"
#include "phantom/def_math.h"

    o_declareT(class, phantom, reflection, native, (typename,typename), TNativeInstanceMemberFunction0 )
    o_declareT(class, phantom, reflection, native, (typename,typename,typename), TNativeInstanceMemberFunction1 )
    o_declareT(class, phantom, reflection, native, (typename,typename,typename,typename), TNativeInstanceMemberFunction2 )
    o_declareT(class, phantom, reflection, native, (typename,typename,typename,typename,typename), TNativeInstanceMemberFunction3 )
    o_declareT(class, phantom, reflection, native, (typename,typename,typename,typename,typename,typename), TNativeInstanceMemberFunction4 )
    o_declareT(class, phantom, reflection, native, (typename,typename,typename,typename,typename,typename,typename), TNativeInstanceMemberFunction5 )
    o_declareT(class, phantom, reflection, native, (typename,typename,typename,typename,typename,typename,typename,typename), TNativeInstanceMemberFunction6 )
    o_declareT(class, phantom, reflection, native, (typename,typename,typename,typename,typename,typename,typename,typename,typename), TNativeInstanceMemberFunction7 )
    o_declareT(class, phantom, reflection, native, (typename,typename,typename,typename,typename,typename,typename,typename,typename,typename), TNativeInstanceMemberFunction8 )

    o_declareT(class, phantom, reflection, native, (typename,typename), TNativeInstanceMemberFunctionConst0 )
    o_declareT(class, phantom, reflection, native, (typename,typename,typename), TNativeInstanceMemberFunctionConst1 )
    o_declareT(class, phantom, reflection, native, (typename,typename,typename,typename), TNativeInstanceMemberFunctionConst2 )
    o_declareT(class, phantom, reflection, native, (typename,typename,typename,typename,typename), TNativeInstanceMemberFunctionConst3 )
    o_declareT(class, phantom, reflection, native, (typename,typename,typename,typename,typename,typename), TNativeInstanceMemberFunctionConst4 )
    o_declareT(class, phantom, reflection, native, (typename,typename,typename,typename,typename,typename,typename), TNativeInstanceMemberFunctionConst5 )
    o_declareT(class, phantom, reflection, native, (typename,typename,typename,typename,typename,typename,typename,typename), TNativeInstanceMemberFunctionConst6 )
    o_declareT(class, phantom, reflection, native, (typename,typename,typename,typename,typename,typename,typename,typename,typename), TNativeInstanceMemberFunctionConst7 )
    o_declareT(class, phantom, reflection, native, (typename,typename,typename,typename,typename,typename,typename,typename,typename,typename), TNativeInstanceMemberFunctionConst8 )

    o_declareT(class, phantom, reflection, native, (typename,typename), TNativeInterfaceMemberFunction0 )
    o_declareT(class, phantom, reflection, native, (typename,typename,typename), TNativeInterfaceMemberFunction1 )
    o_declareT(class, phantom, reflection, native, (typename,typename,typename,typename), TNativeInterfaceMemberFunction2 )
    o_declareT(class, phantom, reflection, native, (typename,typename,typename,typename,typename), TNativeInterfaceMemberFunction3 )
    o_declareT(class, phantom, reflection, native, (typename,typename,typename,typename,typename,typename), TNativeInterfaceMemberFunction4 )
    o_declareT(class, phantom, reflection, native, (typename,typename,typename,typename,typename,typename,typename), TNativeInterfaceMemberFunction5 )
    o_declareT(class, phantom, reflection, native, (typename,typename,typename,typename,typename,typename,typename,typename), TNativeInterfaceMemberFunction6 )
    o_declareT(class, phantom, reflection, native, (typename,typename,typename,typename,typename,typename,typename,typename,typename), TNativeInterfaceMemberFunction7 )
    o_declareT(class, phantom, reflection, native, (typename,typename,typename,typename,typename,typename,typename,typename,typename,typename), TNativeInterfaceMemberFunction8 )

    o_declareT(class, phantom, reflection, native, (typename,typename), TNativeInterfaceMemberFunctionConst0 )
    o_declareT(class, phantom, reflection, native, (typename,typename,typename), TNativeInterfaceMemberFunctionConst1 )
    o_declareT(class, phantom, reflection, native, (typename,typename,typename,typename), TNativeInterfaceMemberFunctionConst2 )
    o_declareT(class, phantom, reflection, native, (typename,typename,typename,typename,typename), TNativeInterfaceMemberFunctionConst3 )
    o_declareT(class, phantom, reflection, native, (typename,typename,typename,typename,typename,typename), TNativeInterfaceMemberFunctionConst4 )
    o_declareT(class, phantom, reflection, native, (typename,typename,typename,typename,typename,typename,typename), TNativeInterfaceMemberFunctionConst5 )
    o_declareT(class, phantom, reflection, native, (typename,typename,typename,typename,typename,typename,typename,typename), TNativeInterfaceMemberFunctionConst6 )
    o_declareT(class, phantom, reflection, native, (typename,typename,typename,typename,typename,typename,typename,typename,typename), TNativeInterfaceMemberFunctionConst7 )
    o_declareT(class, phantom, reflection, native, (typename,typename,typename,typename,typename,typename,typename,typename,typename,typename), TNativeInterfaceMemberFunctionConst8 )

    o_declareT(class, phantom, reflection, native, (typename), TConstant)

    o_declareT(class, phantom, reflection, native, (typename), TType)
    o_declareT(class, phantom, reflection, native, (typename, typename), TNativeSignal)
    o_declareT(class, phantom, reflection, native, (typename, typename), TNativeInstanceMemberFunction)
    o_declareT(class, phantom, reflection, native, (typename, typename), TNativeInstanceMemberFunctionConst)
    o_declareT(class, phantom, reflection, native, (typename, typename), TNativeInterfaceMemberFunction)
    o_declareT(class, phantom, reflection, native, (typename, typename), TNativeInterfaceMemberFunctionConst)
    o_declareT(class, phantom, reflection, native, (typename, typename), TNativeStaticMemberFunction)
    o_declareT(class, phantom, reflection, native, (typename, typename), TNativeInstanceDataMember)
    o_declareT(class, phantom, reflection, native, (typename, typename), TNativeStaticDataMember)

    o_declareT(class, phantom, reflection, native, (typename, uint, typename), TNativeDataMemberProvider)

#ifdef o_NO_FUNCTION_STYLE_TEMPLATE_SIGNATURE
    o_declareT(class, phantom, reflection, native, (typename, uint, typename, typename, typename), TNativeMemberFunctionProvider)
    o_declareT(class, phantom, reflection, native, (typename, uint, typename, typename, typename), TNativeInterfaceMemberFunctionProvider)
    o_declareT(class, phantom, reflection, native, (typename, typename, typename), TNativeSignatureProvider)
#else
    o_declareT(class, phantom, reflection, native, (typename, uint, typename), TNativeMemberFunctionProvider)
    o_declareT(class, phantom, reflection, native, (typename, uint, typename), TNativeInterfaceMemberFunctionProvider)
    o_declareT(class, phantom, reflection, native, (int, typename), TNativeSignatureProvider)
#endif


o_begin_phantom_namespace()


// type_name_of_helper_ specializations for primitive types
o_namespace_begin(reflection, detail)

template<>
class type_name_of_helper_<phantom::signal_t>
{
public:
       static const char*    decoratedName() { return o_PP_QUOTE(signal_t); }
       static const char*    qualifiedDecoratedName() { return "phantom::" o_PP_QUOTE(signal_t); }
       static const char*    name() { return o_PP_QUOTE(signal_t); }
       static const char*    qualifiedName() { return "phantom::" o_PP_QUOTE(signal_t); }
       static const char*    namespaceName() { return "phantom"; }
       static const char*    classScopeName() { return ""; }
};
template<int t_counter>
class type_name_of_helper_counter_<signal_t,t_counter> : public type_name_of_helper_<phantom::signal_t>
{
};

#define o_specialize_type_name_of_for_primitive_type(_type_) \
    template<>\
    class type_name_of_helper_<_type_>\
    {\
    public:\
        static const char*    decoratedName() { return o_PP_QUOTE(_type_); }\
        static const char*    qualifiedDecoratedName() { return o_PP_QUOTE(_type_); }\
        static const char*    name() { return o_PP_QUOTE(_type_); }\
        static const char*    qualifiedName() { return o_PP_QUOTE(_type_); }\
        static const char*    namespaceName() { return ""; }\
        static const char*    classScopeName() { return ""; }\
    };\
    template<int t_counter>\
    class type_name_of_helper_counter_<_type_,t_counter> : public type_name_of_helper_<_type_>\
    {\
    };


o_specialize_type_name_of_for_primitive_type(char);
o_specialize_type_name_of_for_primitive_type(unsigned char);
o_specialize_type_name_of_for_primitive_type(signed char);
#if o_BUILT_IN_WCHAR_T
o_specialize_type_name_of_for_primitive_type(wchar_t);
#endif
o_specialize_type_name_of_for_primitive_type(short);
o_specialize_type_name_of_for_primitive_type(unsigned short);
o_specialize_type_name_of_for_primitive_type(int);
o_specialize_type_name_of_for_primitive_type(unsigned int);
o_specialize_type_name_of_for_primitive_type(long);
o_specialize_type_name_of_for_primitive_type(unsigned long);
o_specialize_type_name_of_for_primitive_type(long long);
o_specialize_type_name_of_for_primitive_type(unsigned long long);
o_specialize_type_name_of_for_primitive_type(float);
o_specialize_type_name_of_for_primitive_type(double);
o_specialize_type_name_of_for_primitive_type(long double);
o_specialize_type_name_of_for_primitive_type(bool);
o_specialize_type_name_of_for_primitive_type(void);

o_namespace_end(reflection, detail)

namespace detail
{
    class o_export dynamic_initializer_handle
    {
        friend o_export void installReflection(const string& a_strName);
        friend o_export void uninstallReflection(const string& a_strName);
        typedef void    (*module_installation_func)        (uint);
        friend class phantom::Phantom;
        template<typename> friend struct phantom::reflection::detail::type_reflection_registrer;


    protected:
        dynamic_initializer_handle();
        ~dynamic_initializer_handle();
        phantom::reflection::Namespace*
            parseNamespace(const string& a_strFileName) const;

        void                    deferMetaInitialization(Object* a_pObject)
        {
            m_DeferredReflectionSetupObjects.push_back(a_pObject);
        }

    protected:
        struct dynamic_initializer_module_installation_func
        {
            dynamic_initializer_module_installation_func() : setupFunc(NULL){}
            dynamic_initializer_module_installation_func( module_installation_func    a_setupFunc )
                : setupFunc(a_setupFunc)
            {

            }
            o_forceinline void exec(uint step)
            {
                (*setupFunc)(step);
            }
            module_installation_func        setupFunc;
        };
        typedef vector<dynamic_initializer_module_installation_func>        dynamic_initializer_module_installation_func_vector;

    private:
        vector<dynamic_initializer_module_installation_func_vector>     m_DeferredSetupInfos;
        vector<reflection::Template*>                                   m_DeferredTemplates;
        vector<Object*>                                                 m_DeferredReflectionSetupObjects;

    public:
        void    registerType( phantom::reflection::Type* a_pType );
        void    registerType( const string& a_strNamespace, const string& a_strClassScope, phantom::reflection::Type* a_pType );
        void    registerModule( module_installation_func setupFunc, uint a_uiSetupStepMask, bool a_bDeferred = true );
        void    registerTemplate( reflection::Template* a_pTemplate );
        void    installReflection(const string& a_strName, const string& a_strFileName, size_t a_PlatformHandle);
        void    uninstallReflection(const string& a_strName);
    };
}

class o_export Phantom
{
public:
    o_friend(class, phantom, Object)
    o_friend(class, phantom, reflection, LanguageElement)
    o_friend(class, phantom, reflection, Class) // for rtti registration access
    
    template<typename,typename> friend class TNativeType;
    template<typename,uint > friend struct extension::detail::rtti_data_registrer_helper_;
    template<typename t_Ty, extension::detail::default_installer_id>  friend struct extension::detail::default_installer_helper;

    typedef boost::pool<phantom::memory::malloc_free_allocator_for_boost> dynamic_pool_type ;
    typedef phantom::map<size_t, dynamic_pool_type*>                        dynamic_pool_type_map;
    typedef void (*message_report_func)(const character*, const character*, const char*, uint);
    typedef void (*log_func)(int level, const char* file, uint line, const char* message, va_list arglist);

    typedef phantom::unordered_map<void const*, phantom::rtti_data>		rtti_data_map;
	typedef phantom::unordered_map<string, size_t>						element_map;
	typedef phantom::vector<phantom::reflection::LanguageElement*>		element_container;
    typedef phantom::vector<string>										meta_data_container;

    template<unsigned alloc_size>
    class static_size_allocator : public boost::singleton_pool<boost::fast_pool_allocator_tag, alloc_size>
    {};
   
    template<size_t t_size>
    friend void*                staticPoolAllocate() ;

    template<size_t t_size>
    friend void*                staticPoolDeallocate(void* ptr) ;

    template<size_t t_size>
    friend void*                staticPoolAllocateN(typename static_size_allocator<t_size>::size_type n) ;

    template<size_t t_size>
    friend void                 staticPoolDeallocateN(void* ptr, typename static_size_allocator<t_size>::size_type n) ;

    friend o_export void*       dynamicPoolAllocate(size_t s o_memory_stat_append_parameters);
    friend o_export void        dynamicPoolDeallocate(size_t s, void* a_pAddress o_memory_stat_append_parameters);
    friend o_export void*       dynamicPoolAllocate(size_t s, size_t count o_memory_stat_append_parameters);
    friend o_export void        dynamicPoolDeallocate(size_t s, void* a_pAddress, size_t count o_memory_stat_append_parameters);
    friend o_export connection::slot const* connect(void* a_pSender, const character* a_pSignal, void* a_pReceiver, const character* a_pMemberFunction);
    friend o_export connection::slot const* connect(void* a_pSender, phantom::reflection::Signal* a_pSignal, void* a_pReceiver, phantom::reflection::InstanceMemberFunction* a_pMemberFunction);
    friend o_export connection::slot const* disconnect(void* a_pSender, phantom::reflection::Signal* a_pSignal, void* a_pReceiver, phantom::reflection::InstanceMemberFunction* a_pMemberFunction);
    friend o_export connection::slot const* disconnect(void* a_pSender, const character* a_pSignal, void* a_pReceiver, const character* a_pMemberFunction);
    friend o_export connection::slot const* tryConnect(void* a_pSender, const character* a_pSignal, void* a_pReceiver, const character* a_pMemberFunction);
    friend o_export connection::slot const* tryDisconnect(void* a_pSender, const character* a_pSignal, void* a_pReceiver, const character* a_pMemberFunction);
    friend o_export void assertion BOOST_PREVENT_MACRO_SUBSTITUTION ( const character* e, const character* m , const char* f , uint l);
    friend o_export void warning BOOST_PREVENT_MACRO_SUBSTITUTION (const character* e, const character* m, const char* f, uint l);
    friend o_export void error BOOST_PREVENT_MACRO_SUBSTITUTION (const character* e, const character* m, const char* f, uint l);
    friend o_export void log BOOST_PREVENT_MACRO_SUBSTITUTION (int level, const char* file, uint line, const char* message, ...);

    friend o_export void pushModule(Module* a_pModule);
    friend o_export Module* popModule();
    friend o_export Module* currentModule();
    friend o_export Module* moduleByName(const string& a_strName);
    friend o_export Module* moduleByFileName(const string& a_strFileName);
    friend o_export map<string, Module*>::const_iterator beginModules();
    friend o_export map<string, Module*>::const_iterator endModules();

    friend o_export void release();

    enum EState
    {
        eState_NotInstalled,
        eState_DynamicInitializerDone_StartingInitialization,
        eState_Reflection_InheritanceSetup,
        eState_Reflection_ContentSetup,
        eState_Reflection_StateChartSetup,
        eState_Reflection_DeferredSetup,
        eState_Installed,
        eState_Uninstalling,
        eState_Uninstalled
    };

    static EState               getState()        { return m_eState; }
    static uint                 getSetupStep()    { return m_uiSetupStep; }
    static void                 setAssertFunc(message_report_func a_func) { m_assert_func = a_func; }
    static void                 setErrorFunc(message_report_func a_func) { m_error_func = a_func; }
    static void                 setLogFunc(log_func a_func) { m_log_func = a_func; }
    static void                 setWarningFunc(message_report_func a_func) { m_warning_func = a_func; }
    static phantom::reflection::SourceFile* sourceFile(const string& absoluteName);
    static void                 discardSourceFile(phantom::reflection::SourceFile* a_pSourceFile);
    //static void                 completeElement(const string& a_Prefix, const reflection::CodePosition& a_Position, vector<reflection::LanguageElement*>& out);
    static element_map          getElementMap();
    static void					setElementMap(element_map a_element_map);
    static void					registerLanguageElement(phantom::reflection::LanguageElement* pElement);
    static void					unregisterLanguageElement(phantom::reflection::LanguageElement* pElement);
    static void					updateLanguageElementGuid();

    Phantom(int argc = 0, char* argv[] = NULL, int metadatasize = 0, char* metadata[] = NULL);
    ~Phantom();

    template <typename t_Ty>
    friend o_NESTED_TYPE phantom::reflection::meta_class_type_of<t_Ty>::type* typeOf();
    template<typename t_Ty>
    friend phantom::reflection::ReferenceType*                  referenceTypeOf();
    template<typename t_Ty>
    friend phantom::reflection::Type*                           constTypeOf();
    template<typename t_Ty>
    friend phantom::reflection::ArrayType*                      arrayTypeOf(size_t);
    template<typename t_Ty>
    friend phantom::reflection::DataPointerType*                pointerTypeOf();


    friend o_export void*                                       baseOf(void const* in);
    friend o_export phantom::reflection::Class*                 classOf(void const* in);
    friend o_export phantom::reflection::Class*                 classAt(void const* in);
    friend o_export const phantom::rtti_data&                   rttiDataOf(void const* in);
    friend o_export void                                        rttiLayoutOf(void const* in, vector<void*>& out);
    friend o_export void                                        dynamicDelete(void* in o_memory_stat_append_parameters);
    friend o_export void                                        replaceRttiData(void const* ptr, const rtti_data& data);
    friend o_export void                                        addRttiData(void const* ptr, const rtti_data& data);
    friend o_export void                                        removeRttiData(void const* ptr);


    template<typename t_OutTy>
    friend t_OutTy     polymorphic_cast(void*    in);
    template<typename t_OutTy, typename t_InTy>
    friend t_OutTy     as(t_InTy    in);
    template<typename t_Ty, typename t_InTy>
    friend boolean     is(t_InTy    in);

private:
    static void    setState(EState s) ;
    static connection::slot const*    internalConnect( const rtti_data& a_Sender, reflection::Signal* a_pSignal, const rtti_data& a_Receiver, reflection::InstanceMemberFunction* a_pMemberFunction );
    static connection::slot const*    internalDisconnect( const rtti_data& a_Sender, phantom::reflection::Signal* a_pSignal, const rtti_data& a_Receiver, phantom::reflection::InstanceMemberFunction* a_pMemberFunction );

    struct type_sorter_by_build_order
    {
        bool        operator()(reflection::Type* one, reflection::Type* another);
    };

    static void					release();


private:
    static EState					m_eState;
    static uint						m_uiSetupStep;
    static dynamic_pool_type_map	m_DynamicPoolAllocators;
    static rtti_data_map*			m_rtti_data_map;
    static message_report_func		m_assert_func;
    static message_report_func		m_error_func;
    static message_report_func		m_warning_func;
    static log_func		            m_log_func;
    static Phantom*					m_instance;
	static element_container*		m_elements;
    static Module*      m_module;
    static map<string, Module*> m_modules;

    vector<string>                  m_meta_data_names;
    static map<string, reflection::SourceFile*> m_SourceFiles;

public:
    friend o_export phantom::reflection::Namespace*     namespaceByName(  const string& a_strNamespaceName);
    friend o_export phantom::reflection::Namespace*     namespaceByList( list<string>* a_pNamespaceNameAsStringList );

    friend o_export phantom::reflection::Namespace*     rootNamespace();
    friend o_export inline phantom::reflection::SourceFile* sourceFile(const string& elementName);
    friend o_export inline void                         discardSourceFile(phantom::reflection::SourceFile* a_pSourceFile);
    friend o_export inline const string&                metaDataName(size_t index) ;
    friend o_export inline size_t                       metaDataCount();
    friend o_export inline size_t                       metaDataIndex(const string& elementName);

private:
    static phantom::reflection::Namespace*                m_pRootNamespace;
    static void*                m_typeOf_cycling_address_workaround_ptr;
    template<typename, uint> friend class rtti_data_registrer_helper_;
public:

    static detail::dynamic_initializer_handle*                dynamic_initializer();
    friend o_export class detail::dynamic_initializer_handle;
};


namespace detail
{


    template<typename t_Ty, bool t_has_reflection>
    struct reflection_installer_helper
    {

    };

    template<typename t_Ty>
    struct reflection_installer_helper<t_Ty, true>
        : public proxy_of<t_Ty>::type::enclosed_reflection
    {
        reflection_installer_helper() 
        { 
            auto pType = typeOf<t_Ty>(); 
            o_assert(phantom::currentModule(), "no module pushed for the current registered type") ;
            o_assert(pType->getModule() == nullptr);
            phantom::currentModule()->addLanguageElement(pType);
        } // ensure type is registered even if no members is added
    };

    template<typename t_Ty>
    struct reflection_installer : public reflection_installer_helper<t_Ty, has_enclosed_reflection<t_Ty>::value>
    {

    };

    template<typename t_Ty, bool t_has_statechart>
    struct statechart_installer_helper
    {

    };

    template<typename t_Ty>
    struct statechart_installer_helper<t_Ty, true>
        : public proxy_of<t_Ty>::type::o_NESTED_TEMPLATE enclosed_statechart<t_Ty>
    {
        statechart_installer_helper()
        {
            classOf<t_Ty>()->setStateMachine(phantom::state::native::TNativeStateMachine<t_Ty>::Instance());
        }
    };

    template<typename t_Ty>
    struct statechart_installer : public statechart_installer_helper<t_Ty, has_statechart<t_Ty>::value>
    {

    };

    template<typename t_Ty, bool t_has_reflection, bool t_has_statechart>
    struct module_installer_helper
    {
    };

    template<typename t_Ty>
    struct module_installer_helper<t_Ty, true, true>
    {
        static void apply(uint step)
        {
            reflection::Class* saved_class = reflection::g_PHANTOM_RESERVED_class;
            reflection::TemplateSpecialization* saved_template_specialization = reflection::g_PHANTOM_RESERVED_template_specialization;
            reflection::g_PHANTOM_RESERVED_class = phantom::typeOf<t_Ty>()->asClass();
            reflection::g_PHANTOM_RESERVED_template_specialization = reflection::g_PHANTOM_RESERVED_class ? reflection::g_PHANTOM_RESERVED_class->getTemplateSpecialization() : nullptr;
            switch(step)
            {
            case o_global_value_SetupStepIndex_Reflection:
                {
                    reflection_installer<t_Ty> m_reflection_module_installer;
                    (void)m_reflection_module_installer;
                }
                break;
            case o_global_value_SetupStepIndex_StateChart:
                {
                    statechart_installer<t_Ty> m_statechart_module_installer;
                    (void)m_statechart_module_installer;
                }
                break;
            }
            reflection::g_PHANTOM_RESERVED_class = saved_class;
            reflection::g_PHANTOM_RESERVED_template_specialization = saved_template_specialization;
        }
    };

    template<typename t_Ty>
    struct module_installer_helper<t_Ty, false, true>
    {
        static void apply(uint step)
        {
            reflection::Class* saved_class = reflection::g_PHANTOM_RESERVED_class;
            reflection::TemplateSpecialization* saved_template_specialization = reflection::g_PHANTOM_RESERVED_template_specialization;
            reflection::g_PHANTOM_RESERVED_class = phantom::typeOf<t_Ty>()->asClass();
            reflection::g_PHANTOM_RESERVED_template_specialization = reflection::g_PHANTOM_RESERVED_class ? reflection::g_PHANTOM_RESERVED_class->getTemplateSpecialization() : nullptr;
            switch(step)
            {
            case o_global_value_SetupStepIndex_StateChart:
                {
                    statechart_installer<t_Ty> m_statechart_module_installer;
                    (void)m_statechart_module_installer;
                }
                break;
            }
            reflection::g_PHANTOM_RESERVED_class = saved_class;
            reflection::g_PHANTOM_RESERVED_template_specialization = saved_template_specialization;
        }
    };

    template<typename t_Ty>
    struct module_installer_helper<t_Ty, true, false>
    {
        static void apply(uint step)
        {
            reflection::Class* saved_class = reflection::g_PHANTOM_RESERVED_class;
            reflection::TemplateSpecialization* saved_template_specialization = reflection::g_PHANTOM_RESERVED_template_specialization;
            reflection::g_PHANTOM_RESERVED_class = phantom::typeOf<t_Ty>()->asClass();
            reflection::g_PHANTOM_RESERVED_template_specialization = reflection::g_PHANTOM_RESERVED_class ? reflection::g_PHANTOM_RESERVED_class->getTemplateSpecialization() : nullptr;
            switch(step)
            {
            case o_global_value_SetupStepIndex_Reflection:
                {
                    reflection_installer<t_Ty> m_reflection_module_installer;
                    (void)m_reflection_module_installer;
                }
                break;
            }
            reflection::g_PHANTOM_RESERVED_class = saved_class;
            reflection::g_PHANTOM_RESERVED_template_specialization = saved_template_specialization;
        }
    };

    template<typename t_Ty>
    struct module_installer
        : public module_installer_helper<t_Ty, has_reflection<t_Ty>::value, has_statechart<t_Ty>::value>
    {
    };

    template<typename t_Ty>
    struct dynamic_initializer_module_installer_registrer
    {
        dynamic_initializer_module_installer_registrer()
        {
            Phantom::dynamic_initializer();

            // Ensure the creation of the meta type
            phantom::typeOf<t_Ty>();
            /// If you get an error : 'apply' : is not a member of 'phantom::detail::module_installer'
            /// It's probably because you didn't declare a reflection scope (internal or external) for the given t_Ty class
            Phantom::dynamic_initializer()->registerModule(&module_installer<t_Ty>::apply, setup_steps_mask_of<t_Ty>::value);
        }
    };

    struct o_export dynamic_initializer_template_registrer
    {
        dynamic_initializer_template_registrer(const string& a_strNamespace, const string& a_strName);
    };

    template<typename t_Ty, bool t_is_template>
    struct module_installer_template_auto_registrer_helper
    {

    };
    template<typename t_Ty>
    struct module_installer_template_auto_registrer_helper<t_Ty, true>
    {
        module_installer_template_auto_registrer_helper()
        {
            Phantom::dynamic_initializer();
            auto pType = typeOf<t_Ty>();
            /*Module* pModule = nullptr;
            if(Phantom::getState() == Phantom::eState_Installed)
            {
                o_assert(pType->getTemplate());
                pModule = pType->getTemplate()->getModule();
                if(pModule)
                {
                    pType->getTemplate()->getModule()->addLanguageElement(pType);
                }
            }*/
            Phantom::dynamic_initializer()->registerModule(&module_installer<t_Ty>::apply, setup_steps_mask_of<t_Ty>::value, true);
        }
    };
    template<typename t_Ty>
    struct module_installer_template_auto_registrer
        : public module_installer_template_auto_registrer_helper<t_Ty, phantom::is_template<t_Ty>::value>
    {
    };

}

// Some member_functions implementations which depends on phantom::Phantom

o_export inline phantom::reflection::Namespace*     rootNamespace() { return phantom::Phantom::m_pRootNamespace; }
o_export inline phantom::reflection::SourceFile*    sourceFile(const string& absoluteName) { return phantom::Phantom::sourceFile(absoluteName); }
o_export inline void                                discardSourceFile(phantom::reflection::SourceFile* a_pSourceFile) { return phantom::Phantom::discardSourceFile(a_pSourceFile); }

enum 
{
    eInvalidMetaDataIndex = 0xffffffff,
};

o_export inline size_t                              metaDataIndex(const string& elementName)
{
    const vector<string>& metaData = phantom::Phantom::m_instance->m_meta_data_names;
    size_t i = 0;
    size_t count = metaData.size();
    for(;i<count;++i)
    {
        if(metaData[i] == elementName) return i;
    }
    return eInvalidMetaDataIndex;
}
o_export void                                       setMetaDataValue(const string& elementName, size_t index, const string& value);
o_export inline void                                setMetaDataValue(const string& elementName, const string& metaDataName, const string& value) 
{ 
    setMetaDataValue(elementName, metaDataIndex(metaDataName), value);
}

o_export const string&                              metaDataValue(const string& elementName, size_t index);
o_export inline const string&                       metaDataValue(const string& elementName, const string& metaDataName) 
{ 
    return metaDataValue(elementName, metaDataIndex(metaDataName));
}
o_export inline size_t                              metaDataCount() 
{
    return phantom::Phantom::m_instance->m_meta_data_names.size();
}
o_export inline const string&                       metaDataName(size_t index) 
{
    return phantom::Phantom::m_instance->m_meta_data_names[index];
}

template<typename t_Ty>
inline reflection::template_specialization_registrer<t_Ty>::template_specialization_registrer()
{
    Phantom::dynamic_initializer(); // ensure modules (and especially reflection here) are initialized and ready
    phantom::typeOf<t_Ty>();
}

template<typename t_Ty>
inline void reflection::detail::type_reflection_registrer<t_Ty>::apply(Type* a_pType)
{
    phantom::detail::dynamic_initializer_handle* pDynamicInitializer = Phantom::dynamic_initializer();
    pDynamicInitializer->registerType(phantom::namespaceNameOf<t_Ty>(), phantom::classScopeNameOf<t_Ty>(), a_pType);
}

template<size_t t_size>
o_forceinline void*                                  staticPoolAllocate() { return phantom::Phantom::static_size_allocator<t_size>::ordered_malloc(); }
template<size_t t_size>
o_forceinline void                                   staticPoolDeallocate(void* ptr) { phantom::Phantom::static_size_allocator<t_size>::ordered_free(ptr); }
template<size_t t_size>
o_forceinline void*                                  staticPoolAllocateN(typename phantom::Phantom::static_size_allocator<t_size>::size_type n) { return phantom::Phantom::static_size_allocator<t_size>::ordered_malloc(n); }
template<size_t t_size>
o_forceinline void                                   staticPoolDeallocateN(void* ptr, typename phantom::Phantom::static_size_allocator<t_size>::size_type n) { phantom::Phantom::static_size_allocator<t_size>::ordered_free(ptr,n); }

o_export inline void*                                baseOf(void const* in)
{
    phantom::Phantom::rtti_data_map::const_iterator found = phantom::Phantom::m_rtti_data_map->find(in);
    return (found != phantom::Phantom::m_rtti_data_map->end())?found->second.base:const_cast<void*>(in);
}
o_export inline phantom::reflection::Class*          classOf(void const* in)
{
    phantom::Phantom::rtti_data_map::const_iterator found = phantom::Phantom::m_rtti_data_map->find(in);
    return (found != phantom::Phantom::m_rtti_data_map->end())?found->second.object_class:NULL;
}
o_export inline phantom::reflection::Class*          classAt(void const* in)
{
    phantom::Phantom::rtti_data_map::const_iterator found = phantom::Phantom::m_rtti_data_map->find(in);
    return (found != phantom::Phantom::m_rtti_data_map->end())?found->second.layout_class:NULL;
}

o_export inline const phantom::rtti_data&            rttiDataOf(void const* in)
{
    static phantom::rtti_data null_info(0,0,0,0,0);
    phantom::Phantom::rtti_data_map::const_iterator found = phantom::Phantom::m_rtti_data_map->find(in);
    return (found != phantom::Phantom::m_rtti_data_map->end())?found->second:null_info;
}

o_export void                                        rttiLayoutOf(void const* in, vector<void*>& out)
{
    static phantom::rtti_data null_info(0,0,0,0,0);
    phantom::Phantom::rtti_data_map::const_iterator found = phantom::Phantom::m_rtti_data_map->find(in);
    if(found != phantom::Phantom::m_rtti_data_map->end())
    {
        void* base_address = found->second.base;
        auto it = phantom::Phantom::m_rtti_data_map->begin();
        auto end = phantom::Phantom::m_rtti_data_map->end();
        for(;it!=end;++it)
        {
            if(it->second.base == base_address)
            {
                out.push_back((void*)it->first);
            }
        }
    }
}


o_export inline void                                        addRttiData(void const* in, const rtti_data& data)
{
    phantom::Phantom::rtti_data_map::const_iterator found = phantom::Phantom::m_rtti_data_map->find(in);
    o_assert(found == phantom::Phantom::m_rtti_data_map->end());
    (*phantom::Phantom::m_rtti_data_map)[in] = data;
}
o_export inline void                                        replaceRttiData(void const* in, const rtti_data& data)
{
    phantom::Phantom::rtti_data_map::const_iterator found = phantom::Phantom::m_rtti_data_map->find(in);
    o_assert(found != phantom::Phantom::m_rtti_data_map->end());
    (*phantom::Phantom::m_rtti_data_map)[in] = data;
}
o_export inline void                                        removeRttiData(void const* in)
{
    phantom::Phantom::rtti_data_map::const_iterator found = phantom::Phantom::m_rtti_data_map->find(in);
    o_assert(found != phantom::Phantom::m_rtti_data_map->end());
    phantom::Phantom::m_rtti_data_map->erase(found);
}


template<typename t_OutTy, typename t_InTy>
o_forceinline t_OutTy                                 polymorphic_cast(t_InTy  in)
{
    return as<t_OutTy>(in);
}

template<typename t_Ty, typename t_ITy>
boolean        is(t_ITy*    in)
{
    return detail::is_helper<t_Ty
        , is_reflected_class<t_ITy>::value
    >::apply(in);
}


o_export inline void*                                custom_malloc(size_t s o_memory_stat_append_parameters)
{
    return o__func__malloc(s);
}
o_export inline void                                 custom_free(void* ptr o_memory_stat_append_parameters)
{
    o__func__free(ptr);
}
o_export inline void*                                custom_realloc(void* ptr, size_t s o_memory_stat_append_parameters)
{
    return o__func__realloc(ptr, s);
}

template<typename t_Ty>
o_forceinline    phantom::reflection::DataPointerType*      pointerTypeOf()
{
    return typeOf<t_Ty>()->pointerType();
}
template<typename t_Ty>
o_forceinline    phantom::reflection::ReferenceType*        referenceTypeOf()
{
    return typeOf<t_Ty>()->referenceType();
}
template<typename t_Ty>
o_forceinline    phantom::reflection::Type*                 constTypeOf()
{
    return typeOf<t_Ty>()->constType();
}
template<typename t_Ty>
o_forceinline    phantom::reflection::ArrayType*            arrayTypeOf(size_t a_uiCount)
{
    return typeOf<t_Ty>()->arrayType(a_uiCount);
}
template<typename t_Ty>
o_forceinline    phantom::reflection::PrimitiveType*        basicTypeOf()
{
    o_assert(false, "basicTypeOf not redefined for that basic type");
    return NULL;
}

o_export inline void*                                       dynamicPoolAllocate(size_t s o_memory_stat_append_parameters)
{
    o_assert(s);
#if o__bool__enable_allocation_statistics
    phantom::memory::Statistics::RegisterBytes(s o_memory_stat_append_parameters_use);
#endif
    phantom::Phantom::dynamic_pool_type_map::iterator it = Phantom::m_DynamicPoolAllocators.find(s);
    if(it != Phantom::m_DynamicPoolAllocators.end())
    {
        return it->second->ordered_malloc();
    }
    phantom::Phantom::dynamic_pool_type*    new_pool = o_allocate(phantom::Phantom::dynamic_pool_type);
    new (new_pool) phantom::Phantom::dynamic_pool_type(s);
    Phantom::m_DynamicPoolAllocators[s] = new_pool;
    return new_pool->ordered_malloc();
}
o_export inline void                                        dynamicPoolDeallocate(size_t s, void* a_pAddress o_memory_stat_append_parameters)
{
    o_assert(s);
#if o__bool__enable_allocation_statistics
    phantom::memory::Statistics::UnregisterBytes(s o_memory_stat_append_parameters_use);
#endif
    phantom::Phantom::dynamic_pool_type_map::iterator it = Phantom::m_DynamicPoolAllocators.find(s);
    if(it != Phantom::m_DynamicPoolAllocators.end())
    {
        return it->second->ordered_free(a_pAddress);
    }
    phantom::Phantom::dynamic_pool_type*    new_pool = o_allocate(phantom::Phantom::dynamic_pool_type);
    new (new_pool) phantom::Phantom::dynamic_pool_type(s);
    Phantom::m_DynamicPoolAllocators[s] = new_pool;
    new_pool->ordered_free(a_pAddress);
}
o_export inline void*                                dynamicPoolAllocate(size_t s, size_t count o_memory_stat_append_parameters)
{
    o_assert(s);
    o_assert(count);
#if o__bool__enable_allocation_statistics
    phantom::memory::Statistics::RegisterBytesN(s, count o_memory_stat_append_parameters_use);
#endif
    phantom::Phantom::dynamic_pool_type_map::iterator it = Phantom::m_DynamicPoolAllocators.find(s);
    if(it != Phantom::m_DynamicPoolAllocators.end())
    {
        return it->second->ordered_malloc(count);
    }
    phantom::Phantom::dynamic_pool_type*    new_pool = o_allocate(phantom::Phantom::dynamic_pool_type);
    new (new_pool) phantom::Phantom::dynamic_pool_type(s);
    Phantom::m_DynamicPoolAllocators[s] = new_pool;
    return new_pool->ordered_malloc(count);
}
o_export inline void                                dynamicPoolDeallocate(size_t s, void* a_pAddress, size_t count o_memory_stat_append_parameters)
{
    o_assert(s);
    o_assert(count);
#if o__bool__enable_allocation_statistics
    phantom::memory::Statistics::UnregisterBytesN(s, count o_memory_stat_append_parameters_use);
#endif
    phantom::Phantom::dynamic_pool_type_map::iterator it = Phantom::m_DynamicPoolAllocators.find(s);
    if(it != Phantom::m_DynamicPoolAllocators.end())
    {
        return it->second->ordered_free(a_pAddress, count);
    }
    phantom::Phantom::dynamic_pool_type*    new_pool = o_allocate(phantom::Phantom::dynamic_pool_type);
    new (new_pool) phantom::Phantom::dynamic_pool_type(s);
    Phantom::m_DynamicPoolAllocators[s] = new_pool;
    new_pool->ordered_free(a_pAddress, count);
}




o_end_phantom_namespace()



#include "phantom/def_memory.inl"
#include "phantom/Object.h"
#include "phantom/reflection/native/NativeVTableInspector.h"
#include "phantom/Module.h"
#include "phantom/reflection/LanguageElement.h"
#include "phantom/reflection/TemplateElement.h"
#include "phantom/reflection/Template.h"
#include "phantom/reflection/Signature.h"
#include "phantom/reflection/VirtualMemberFunctionTable.h"
#include "phantom/reflection/Type.h"


// Inlining as soon as possible the member_function which use Type class
template<typename t_Ty>
t_Ty* phantom::data::as() const
{
    reflection::Type* targetType = typeOf<t_Ty>();
    o_assert(targetType, "t_Ty must have reflection");
    o_assert(m_type->isKindOf(targetType));
    if(m_type == targetType) return static_cast<t_Ty*>(m_address);
    return static_cast<t_Ty*>(m_type->cast(targetType, m_address));
}


inline phantom::data       phantom::data::cast(reflection::Type* a_pTargetType) const
{
    void* castedAddress = m_type->cast(a_pTargetType, m_address);
    return phantom::data(castedAddress, castedAddress ? a_pTargetType : NULL);
}

inline void        phantom::data::destroy() 
{ 
    m_type->teardown(m_address); m_type->deallocate(m_address); m_address = NULL; m_type = NULL; 
}


#include "phantom/reflection/SourceFile.h"
#include "phantom/reflection/PrimitiveType.h"
#include "phantom/reflection/PointerType.h"
#include "phantom/reflection/DataPointerType.h"
#include "phantom/reflection/ConstDataPointerType.h"
#include "phantom/reflection/ReferenceType.h"
#include "phantom/reflection/ConstReferenceType.h"
#include "phantom/reflection/ArrayType.h"
#include "phantom/reflection/ConstArrayType.h"
#include "phantom/reflection/ValueMember.h"
#include "phantom/reflection/Constant.h"
#include "phantom/reflection/Variable.h"
#include "phantom/util/Iterator.h"
#include "phantom/reflection/IteratorConstant.h"
#include "phantom/reflection/IteratorVariable.h"
#include "phantom/reflection/ValueMemberBinding.h"
#include "phantom/reflection/Subroutine.h"
#include "phantom/reflection/Constructor.h"
#include "phantom/reflection/Function.h"
#include "phantom/reflection/StaticVariable.h"
#include "phantom/reflection/ClassType.h"

// Inlining as soon as possible the member_function which use ClassType class
template<typename t_Ty>
t_Ty* phantom::object::as  ()
{
    reflection::ClassType* targetType = typeOf<t_Ty>();
    o_assert(m_class_type->isKindOf(targetType));
    if(m_class_type == targetType) return static_cast<t_Ty*>(m_address);
    return static_cast<t_Ty*>(m_class_type->cast(targetType, m_address));
}

#include "phantom/reflection/Class.h"

// Inlining as soon as possible the member_function which use Class class

#include "phantom/def_modules_phantom_reflection_Class_dependency.inl"

// Continue including ...

#include "phantom/reflection/ContainerClass.h"
#include "phantom/reflection/SequentialContainerClass.h"
#include "phantom/reflection/MapContainerClass.h"
#include "phantom/reflection/SetContainerClass.h"
#include "phantom/serialization/DataBase.h"

o_forceinline void*   phantom::rtti_data::cast(phantom::reflection::Class* a_pTargetClass) const
{
    return object_class->cast(a_pTargetClass, base);
}

#include "phantom/reflection/PODUnion.h"
#include "phantom/reflection/Union.h"
#include "phantom/reflection/PODStruct.h"

#include "phantom/reflection/native/TConstant.h"

// Implementing some member_functions which depend on TConstant

o_begin_phantom_namespace()

o_define_template_signature_parameter_phantom_element_impl(boolean)
o_define_template_signature_parameter_phantom_element_impl(uchar)
o_define_template_signature_parameter_phantom_element_impl(schar)
o_define_template_signature_parameter_phantom_element_impl(ushort)
o_define_template_signature_parameter_phantom_element_impl(sshort)
o_define_template_signature_parameter_phantom_element_impl(uint)
o_define_template_signature_parameter_phantom_element_impl(sint)
o_define_template_signature_parameter_phantom_element_impl(size_t)
o_define_template_signature_parameter_phantom_element_impl(ulong)
o_define_template_signature_parameter_phantom_element_impl(slong)
o_define_template_signature_parameter_phantom_element_impl(longlong)
o_define_template_signature_parameter_phantom_element_impl(ulonglong)

o_define_template_signature_parameter_element_impl(bool)
o_define_template_signature_parameter_element_impl(char)
o_define_template_signature_parameter_element_impl(short)
o_define_template_signature_parameter_element_impl(int)
o_define_template_signature_parameter_element_impl(long)
o_define_template_signature_parameter_element_impl(size_t)
o_define_template_signature_parameter_element_impl(uchar)
o_define_template_signature_parameter_element_impl(schar)
o_define_template_signature_parameter_element_impl(ushort)
o_define_template_signature_parameter_element_impl(sshort)
o_define_template_signature_parameter_element_impl(uint)
o_define_template_signature_parameter_element_impl(sint)
o_define_template_signature_parameter_element_impl(ulong)
o_define_template_signature_parameter_element_impl(slong)
o_define_template_signature_parameter_element_impl(longlong)
o_define_template_signature_parameter_element_impl(ulonglong)
o_define_template_signature_parameter_element_impl(unsigned)

template<ulonglong value>
phantom::reflection::TemplateElement*
reflection::detail::template_signature_parameter_enum<value>::element()
{
    return o_new(phantom::reflection::native::TConstant<ulonglong>)("", value);
}

o_end_phantom_namespace()

#include "phantom/reflection/Enum.h"

#include "phantom/reflection/native/TType.h"

o_namespace_begin(phantom, extension, detail)

#define o_phantom_extension_fundamental_converter_case(d) \
    if(a_pDestType == phantom::typeOf<d>())\
    {\
        *((d*)dest) = (d)*src;\
    }

#define o_phantom_extension_fundamental_converter_can_case(d) \
    if(a_pDestType == phantom::typeOf<d>())\
    {\
        return true;\
    }

#define o_phantom_extension_fundamental_converter(s) \
    template<>\
    struct converter_<s>\
    {\
        static void convert(reflection::Type* a_pDestType, void* dest, const s* src)\
    {\
            o_phantom_extension_fundamental_converter_case(bool)\
            else o_phantom_extension_fundamental_converter_case(char)\
            else o_phantom_extension_fundamental_converter_case(unsigned char)\
            else o_phantom_extension_fundamental_converter_case(short)\
            else o_phantom_extension_fundamental_converter_case(unsigned short)\
            else o_phantom_extension_fundamental_converter_case(int)\
            else o_phantom_extension_fundamental_converter_case(unsigned int)\
            else o_phantom_extension_fundamental_converter_case(long)\
            else o_phantom_extension_fundamental_converter_case(unsigned long)\
            else o_phantom_extension_fundamental_converter_case(long long)\
            else o_phantom_extension_fundamental_converter_case(unsigned long long)\
            else o_phantom_extension_fundamental_converter_case(long double)\
            else o_phantom_extension_fundamental_converter_case(float)\
            else o_phantom_extension_fundamental_converter_case(double)\
            else if(a_pDestType->isEnum()) \
            { \
                switch(a_pDestType->getSize())\
                {\
                case 1:\
                    convert(typeOf<unsigned char>(), dest, src);\
                    break;\
                case 2:\
                    convert(typeOf<unsigned short>(), dest, src);\
                    break;\
                case 4:\
                    convert(typeOf<unsigned int>(), dest, src);\
                    break;\
                case 8:\
                    convert(typeOf<unsigned long long>(), dest, src);\
                    break;\
                default:\
                    o_assert(false, "invalid size for enum type");\
                }\
            }\
            else default_converter<s>::convert(a_pDestType, dest, src);\
    }\
    static bool isConvertibleTo(reflection::Type* a_pDestType)\
{\
            if(a_pDestType == typeOf<s>()) return true;\
            else o_phantom_extension_fundamental_converter_can_case(bool)\
            else o_phantom_extension_fundamental_converter_can_case(char)\
            else o_phantom_extension_fundamental_converter_can_case(unsigned char)\
            else o_phantom_extension_fundamental_converter_can_case(short)\
            else o_phantom_extension_fundamental_converter_can_case(unsigned short)\
            else o_phantom_extension_fundamental_converter_can_case(int)\
            else o_phantom_extension_fundamental_converter_can_case(unsigned int)\
            else o_phantom_extension_fundamental_converter_can_case(long)\
            else o_phantom_extension_fundamental_converter_can_case(unsigned long)\
            else o_phantom_extension_fundamental_converter_can_case(long long)\
            else o_phantom_extension_fundamental_converter_can_case(unsigned long long)\
            else o_phantom_extension_fundamental_converter_can_case(long double)\
            else o_phantom_extension_fundamental_converter_can_case(float)\
            else o_phantom_extension_fundamental_converter_can_case(double)\
            else if(a_pDestType->isEnum()) { return true; }\
            return default_converter<s>::isConvertibleTo(a_pDestType);\
        }\
        static bool isImplicitlyConvertibleTo(reflection::Type* a_pDestType)\
        {\
            if(a_pDestType == typeOf<s>()) return true;\
            else o_phantom_extension_fundamental_converter_can_case(bool)\
            else o_phantom_extension_fundamental_converter_can_case(char)\
            else o_phantom_extension_fundamental_converter_can_case(unsigned char)\
            else o_phantom_extension_fundamental_converter_can_case(short)\
            else o_phantom_extension_fundamental_converter_can_case(unsigned short)\
            else o_phantom_extension_fundamental_converter_can_case(int)\
            else o_phantom_extension_fundamental_converter_can_case(unsigned int)\
            else o_phantom_extension_fundamental_converter_can_case(long)\
            else o_phantom_extension_fundamental_converter_can_case(unsigned long)\
            else o_phantom_extension_fundamental_converter_can_case(long long)\
            else o_phantom_extension_fundamental_converter_can_case(unsigned long long)\
            else o_phantom_extension_fundamental_converter_can_case(long double)\
            else o_phantom_extension_fundamental_converter_can_case(float)\
            else o_phantom_extension_fundamental_converter_can_case(double)\
            return default_converter<s>::isImplicitlyConvertibleTo(a_pDestType);\
        }\
    };

#pragma warning(disable:4800)

o_phantom_extension_fundamental_converter(bool)
o_phantom_extension_fundamental_converter(char)
o_phantom_extension_fundamental_converter(unsigned char)
o_phantom_extension_fundamental_converter(short)
o_phantom_extension_fundamental_converter(unsigned short)
o_phantom_extension_fundamental_converter(int)
o_phantom_extension_fundamental_converter(unsigned int)
o_phantom_extension_fundamental_converter(long)
o_phantom_extension_fundamental_converter(unsigned long)
o_phantom_extension_fundamental_converter(long long)
o_phantom_extension_fundamental_converter(unsigned long long)
o_phantom_extension_fundamental_converter(long double)
o_phantom_extension_fundamental_converter(float)
o_phantom_extension_fundamental_converter(double)


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



#pragma warning(default:4800)

o_namespace_end(phantom, extension, detail)

#include "phantom/reflection/Member.h"

#include "phantom/reflection/MemberFunction.h"
#include "phantom/reflection/InstanceMemberFunction.h"
#include "phantom/reflection/StaticMemberFunction.h"
#include "phantom/reflection/native/TNativeStaticMemberFunctionBase.h"
#include "phantom/reflection/native/TNativeStaticMemberFunction.h"
#include "phantom/reflection/native/TNativeInstanceMemberFunctionBase.h"
#include "phantom/reflection/native/TNativeInstanceMemberFunction.h"
#include "phantom/reflection/native/TNativeInstanceMemberFunctionConst.h"
#include "phantom/reflection/native/TNativeMemberFunctionProvider.h"
#include "phantom/reflection/native/TRange.h"

#include "phantom/reflection/DataMember.h"
#include "phantom/reflection/InstanceDataMember.h"
#include "phantom/reflection/StaticDataMember.h"
#include "phantom/reflection/Property.h"
#include "phantom/reflection/Collection.h"
#include "phantom/reflection/native/TNativeInstanceDataMember.h"
#include "phantom/reflection/native/TNativeProperty.h"
#include "phantom/reflection/native/TNativeCollection.h"
#include "phantom/reflection/native/TNativeStaticDataMember.h"
#include "phantom/reflection/native/TNativeDataMemberProvider.h"
#include "phantom/util/Comparator.h"

#include "phantom/reflection/SubValueMember.h"
#include "phantom/reflection/TemplateSpecialization.h"
#include "phantom/reflection/Signal.h"
#include "phantom/reflection/native/TNativeSignalBase.h"
#include "phantom/reflection/native/TNativeSignal.h"
#include "phantom/reflection/ClassExtension.h"
#include "phantom/reflection/PureVirtualMemberFunction.h"
#include "phantom/reflection/Function.h"

// DEFINE INLINE TEMPLATE FUNCS WHICH USE REFLECTION CLASSES (GCC constraint)

#include "phantom/state/StateMachineElement.h"

#include "phantom/state/Event.h"
#include "phantom/state/Reaction.h"
#include "phantom/state/StateMachine.h"
#include "phantom/state/Track.h"
#include "phantom/state/State.h"

#include "phantom/state/native/TNativeStateMachine.h"
#include "phantom/state/native/TNativeTrack.h"
#include "phantom/state/native/TNativeState.h"

#include "phantom/def_modules_phantom_state_StateMachine_dependency.inl"

#include "phantom/reflection/Namespace.h"

o_reflection_in_cpp_deferred_setupN((phantom, reflection), Class)
o_reflection_in_cpp_deferred_setupN((phantom), Object)
o_reflection_in_cpp_deferred_setupN((phantom, util), Comparator)
o_reflection_in_cpp_deferred_setupN((phantom, util), Iterator)
o_reflection_in_cpp_deferred_setupN((phantom, reflection), LanguageElement)
o_reflection_in_cpp_deferred_setupN((phantom, reflection), TemplateElement)
o_reflection_in_cpp_deferred_setupN((phantom, reflection), Template)
o_reflection_in_cpp_deferred_setupN((phantom, reflection), Function)
o_reflection_in_cpp_deferred_setupN((phantom, reflection), Constant)
o_reflection_in_cpp_deferred_setupN((phantom, reflection), ClassType)
o_reflection_in_cpp_deferred_setupN((phantom, reflection), Union)
o_reflection_in_cpp_deferred_setupN((phantom, reflection), Member)
o_reflection_in_cpp_deferred_setupN((phantom, reflection), MemberFunction)
o_reflection_in_cpp_deferred_setupN((phantom, reflection), InstanceDataMember)
o_reflection_in_cpp_deferred_setupN((phantom, reflection), InstanceMemberFunction)
o_reflection_in_cpp_deferred_setupN((phantom, reflection), ContainerClass)
o_reflection_in_cpp_deferred_setupN((phantom, reflection), SequentialContainerClass)
o_reflection_in_cpp_deferred_setupN((phantom, reflection), MapContainerClass)
o_reflection_in_cpp_deferred_setupN((phantom, reflection), SetContainerClass)
o_reflection_in_cpp_deferred_setupN((phantom, reflection), Variable)
o_reflection_in_cpp_deferred_setupN((phantom, reflection), StaticVariable)
o_reflection_in_cpp_deferred_setupN((phantom, reflection), IteratorConstant)
o_reflection_in_cpp_deferred_setupN((phantom, reflection), IteratorVariable)
o_reflection_in_cpp_deferred_setupN((phantom, reflection), StaticDataMember)
o_reflection_in_cpp_deferred_setupN((phantom, reflection), StaticMemberFunction)
o_reflection_in_cpp_deferred_setupN((phantom, reflection), Signal)
o_reflection_in_cpp_deferred_setupN((phantom, reflection), Signature)
o_reflection_in_cpp_deferred_setupN((phantom, reflection), SourceFile)
o_reflection_in_cpp_deferred_setupN((phantom, reflection), Subroutine)
o_reflection_in_cpp_deferred_setupN((phantom, reflection), Constructor)
o_reflection_in_cpp_deferred_setupN((phantom, reflection), Type)
o_reflection_in_cpp_deferred_setupN((phantom, reflection), PointerType)
o_reflection_in_cpp_deferred_setupN((phantom, reflection), DataPointerType)
o_reflection_in_cpp_deferred_setupN((phantom, reflection), ReferenceType)
o_reflection_in_cpp_deferred_setupN((phantom, reflection), ConstDataPointerType)
o_reflection_in_cpp_deferred_setupN((phantom, reflection), ConstReferenceType)
o_reflection_in_cpp_deferred_setupN((phantom, reflection), PrimitiveType)
o_reflection_in_cpp_deferred_setupN((phantom, reflection), Property)
o_reflection_in_cpp_deferred_setupN((phantom, reflection), ValueMember)
o_reflection_in_cpp_deferred_setupN((phantom, reflection), Namespace)
o_reflection_in_cpp_deferred_setupN((phantom, reflection), DataMember)
o_reflection_in_cpp_deferred_setupN((phantom, reflection), SubValueMember)
o_reflection_in_cpp_deferred_setupN((phantom, reflection), TemplateSpecialization)
o_reflection_in_cpp_deferred_setupN((phantom, reflection), ClassExtension)
o_reflection_in_cpp_deferred_setupN((phantom, reflection), VirtualMemberFunctionTable)
o_reflection_in_cpp_deferred_setupN((phantom, reflection), PureVirtualMemberFunction)
o_reflection_in_cpp_deferred_setupN((phantom, reflection), PODUnion)
o_reflection_in_cpp_deferred_setupN((phantom, reflection), PODStruct)
o_reflection_in_cpp_deferred_setupN((phantom, reflection), Range)
o_reflection_in_cpp_deferred_setupN((phantom, state), State)
o_reflection_in_cpp_deferred_setupN((phantom, state), Event)
o_reflection_in_cpp_deferred_setupN((phantom, state), Track)
o_reflection_in_cpp_deferred_setupN((phantom, state), Reaction)
o_reflection_in_cpp_deferred_setupN((phantom, state), StateMachine)
o_reflection_in_cpp_deferred_setupN((phantom, state), StateMachineElement)
o_reflection_in_cpp_deferred_setupN((phantom, serialization), DataBase)

#include "phantom/reflection/Block.h"
#include "phantom/reflection/LocalVariable.h"


#define o_specialize_type_of_counter_for_primitive_type(_type_) \
    o_namespace_begin(phantom,reflection,detail)\
    template<int t_counter>\
    class type_of_counter_<_type_,t_counter> : public type_of_<_type_>\
    {\
    };\
    o_namespace_end(phantom,reflection,detail)


o_specialize_type_of_counter_for_primitive_type(char);
o_specialize_type_of_counter_for_primitive_type(phantom::signal_t);
o_specialize_type_of_counter_for_primitive_type(unsigned char);
o_specialize_type_of_counter_for_primitive_type(signed char);
#if o_BUILT_IN_WCHAR_T
o_specialize_type_of_counter_for_primitive_type(wchar_t);
#endif
o_specialize_type_of_counter_for_primitive_type(short);
o_specialize_type_of_counter_for_primitive_type(unsigned short);
o_specialize_type_of_counter_for_primitive_type(int);
o_specialize_type_of_counter_for_primitive_type(unsigned int);
o_specialize_type_of_counter_for_primitive_type(long);
o_specialize_type_of_counter_for_primitive_type(unsigned long);
o_specialize_type_of_counter_for_primitive_type(long long);
o_specialize_type_of_counter_for_primitive_type(unsigned long long);
o_specialize_type_of_counter_for_primitive_type(float);
o_specialize_type_of_counter_for_primitive_type(double);
o_specialize_type_of_counter_for_primitive_type(long double);
o_specialize_type_of_counter_for_primitive_type(bool);
o_specialize_type_of_counter_for_primitive_type(void);


// Data serializer
namespace phantom
{
    namespace extension
    {
        template<>
        class serializer<phantom::data>
        {
        public:
            static void serialize(phantom::data const* a_pInstance, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
            {
                uint guid = a_pDataBase ? a_pDataBase->getGuid(*a_pInstance) : (uint)(a_pInstance->address());
                serializer<uint>::serialize(&guid, a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
            }
            static void deserialize(phantom::data* a_pInstance, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
            {
                uint guid = 0;
                serializer<size_t>::deserialize(&guid, a_pInBuffer, a_uiSerializationMask, a_pDataBase);
                *a_pInstance = a_pDataBase ? a_pDataBase->getData(guid) : phantom::data((void*)guid);
            }
            static void serialize(phantom::data const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
            {
                byte const* pChunk = reinterpret_cast<byte const*>(a_pChunk);
                while(a_uiCount--)
                {
                    phantom::data const* pInstance = reinterpret_cast<phantom::data const*>(pChunk);
                    serialize(pInstance, a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
                    pChunk += a_uiChunkSectionSize;
                }
            }
            static void deserialize(phantom::data* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
            {
                byte* pChunk = reinterpret_cast<byte*>(a_pChunk);
                while(a_uiCount--)
                {
                    phantom::data* pInstance = reinterpret_cast<phantom::data*>(pChunk);
                    deserialize(pInstance, a_pInBuffer, a_uiSerializationMask, a_pDataBase);
                    pChunk += a_uiChunkSectionSize;
                }
            }
            static void serialize(phantom::data const* a_pInstance, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
            {
                uint guid = a_pDataBase ? a_pDataBase->getGuid(*a_pInstance) : (uint)a_pInstance->address();
                a_OutBranch.put_value(phantom::lexical_cast<string>(guid));
            }
            static void deserialize(phantom::data* a_pInstance, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
            {
                boost::optional<string> opt = a_InBranch.get_value_optional<string>();
                if(opt.is_initialized())
                {
                    uint guid = phantom::lexical_cast<uint>(*opt);
                    *a_pInstance = a_pDataBase ? a_pDataBase->getData(guid) : phantom::data((void*)guid);
                }
                else *a_pInstance = phantom::data();
            }
            static void serialize(phantom::data const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
            {
                byte const* pChunk = reinterpret_cast<byte const*>(a_pChunk);
                int i = 0;
                while(a_uiCount--)
                {
                    phantom::data const* pInstance = reinterpret_cast<phantom::data const*>(pChunk);
                    serialize(pInstance, a_OutBranch, a_uiSerializationMask, a_pDataBase);
                    pChunk += a_uiChunkSectionSize;
                }
            }
            static void deserialize(phantom::data* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
            {
                byte* pChunk = reinterpret_cast<byte*>(a_pChunk);
                int i = 0;
                while(a_uiCount--)
                {
                    phantom::data* pInstance = reinterpret_cast<phantom::data*>(pChunk);
                    deserialize(pInstance, a_InBranch, a_uiSerializationMask, a_pDataBase);
                    pChunk += a_uiChunkSectionSize;
                }
            }
            static void serializeLayout(phantom::data const* a_pInstance, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
            {
                serialize(a_pInstance, a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
            }
            static void deserializeLayout(phantom::data* a_pInstance, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
            {
                deserialize(a_pInstance, a_pInBuffer, a_uiSerializationMask, a_pDataBase);
            }
            static void serializeLayout(phantom::data const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
            {
                serialize(a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
            }
            static void deserializeLayout(phantom::data* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
            {
                deserialize(a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pInBuffer, a_uiSerializationMask, a_pDataBase);
            }
            static void serializeLayout(phantom::data const* a_pInstance, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
            {
                serialize(a_pInstance, a_OutBranch, a_uiSerializationMask, a_pDataBase);
            }
            static void deserializeLayout(phantom::data* a_pInstance, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
            {
                deserialize(a_pInstance, a_InBranch, a_uiSerializationMask, a_pDataBase);
            }
            static void serializeLayout(phantom::data const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
            {
                serialize(a_pChunk, a_uiCount, a_uiChunkSectionSize, a_OutBranch, a_uiSerializationMask, a_pDataBase);
            }
            static void deserializeLayout(phantom::data* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
            {
                deserialize(a_pChunk, a_uiCount, a_uiChunkSectionSize, a_InBranch, a_uiSerializationMask, a_pDataBase);
            }
        };
    }
}

o_classN((phantom), data)
{
    o_reflection
    {
        o_data_member(void*, m_address, o_no_range, o_public);
        o_data_member(phantom::reflection::Type*, m_type, o_no_range, o_public);
    };
};
o_exposeN((phantom), data);

o_classN((phantom), object)
{
    o_reflection
    {
        o_data_member(void*, m_address, o_no_range, o_public);
        o_data_member(phantom::reflection::ClassType*, m_class_type, o_no_range, o_public);
    };
};
o_exposeN((phantom), object);

//#if defined(o__bool__enable_bitfield_type)
o_classN((phantom), bitfield)
{
    o_reflection
    {
        o_data_member(int, m_iContent, o_no_range, o_protected);
    };
};
o_exposeN((phantom), bitfield);
//#endif

o_classN((phantom, reflection), CodePosition)
{
    o_reflection
    {
        o_data_member(int, line, (0, std::numeric_limits<int>::max()), o_public);
        o_data_member(int, column, (0, std::numeric_limits<int>::max()), o_public);
    };
};
o_exposeN((phantom, reflection), CodePosition);

o_classN((phantom, reflection), CodeLocation)
{
    o_reflection
    {
        o_data_member(CodePosition, m_Start, o_no_range, o_protected);
        o_data_member(CodePosition, m_End, o_no_range, o_protected);
        o_property(const CodePosition&, start, setStart, getStart, o_no_signal, o_no_range, o_transient|o_public);
        o_property(const CodePosition&, end, setEnd, getEnd, o_no_signal, o_no_range, o_transient|o_public);
    };
};
o_exposeN((phantom, reflection), CodeLocation);

// PARTIAL BOOST INTEGRATION
#include "phantom/externals/boost/boost_thread.h"
#include "phantom/externals/boost/boost_pool.h"

// PARTIAL STL INTEGRATION (specific for each compiler)
#include "phantom/externals/std/std.h"
#include "phantom/variant.h"

#endif // __prerequisites_h__
