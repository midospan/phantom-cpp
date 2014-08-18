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
#include "phantom/def_export.h"
#include "phantom/def_console.h"
#include "phantom/def_memory.h"
#include "phantom/def_types.h"
#include "phantom/def_fwd.h"
#include "phantom/def_counter.h"
#include "phantom/def_traits.h"
#include "phantom/def_container.h"


o_namespace_begin(phantom)

namespace util {}

namespace detail
{
    class dynamic_initializer_handle;
    template<typename t_Ty, int t_counter>
    struct module_installer;
    template<typename t_Ty, int t_counter>
    struct module_installer_registrer;
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
    template<typename,int> struct meta_class_type_of;
    template<typename> struct base_meta_class_type_of;
    template<typename> struct canonical_meta_class_type_of;
    template<typename, int t_counter> struct template_specialization_adder;
    template<typename> struct template_specialization_of;
    template<typename> struct typedef_registrer;
    template<typename> struct type_name_of;
}

template <typename t_Ty>
o_forceinline o_NESTED_TYPE phantom::reflection::canonical_meta_class_type_of<t_Ty>::type* typeOf()
{
    static o_NESTED_TYPE phantom::reflection::canonical_meta_class_type_of<t_Ty>::type* s_pInstance = nullptr;
    if(s_pInstance == nullptr)
    {
        s_pInstance = static_cast<phantom::reflection::canonical_meta_class_type_of<t_Ty>::type*>(phantom::reflection::Types::get<t_Ty>());
    }
    return s_pInstance;
}

#define o_dynamic_type_of(...) phantom::typeByName(o_qualified_decorated_type_name_of(__VA_ARGS__))
#define o_type_of(...) phantom::reflection::detail::type_of_counter<__VA_ARGS__, o_read_compilation_counter>::object()
#define o_type_name_of(...) phantom::reflection::detail::type_name_of_counter<__VA_ARGS__, o_read_compilation_counter>::name()
#define o_qualified_type_name_of(...) phantom::reflection::detail::type_name_of_counter<__VA_ARGS__, o_read_compilation_counter>::qualifiedName()
#define o_decorated_type_name_of(...) phantom::reflection::detail::type_name_of_counter<__VA_ARGS__, o_read_compilation_counter>::decoratedName()
#define o_qualified_decorated_type_name_of(...) phantom::reflection::detail::type_name_of_counter<__VA_ARGS__, o_read_compilation_counter>::qualifiedDecoratedName()
#define o_namespace_of(...) phantom::namespaceByName(phantom::reflection::detail::type_name_of_counter<__VA_ARGS__, o_read_compilation_counter>::namespaceName())
#define o_nesting_class_of(...) phantom::classByName(phantom::reflection::detail::type_name_of_counter<__VA_ARGS__, o_read_compilation_counter>::classScopeName())

// function forwarding

o_export boolean                                        is(reflection::Class* a_pTestedClass, void*    in);
template<typename t_Ty, typename t_ITy>
inline boolean                                          is(t_ITy*    in);

template<typename t_Ty>
inline boolean                                          is(void*    in);

template<typename t_Ty, typename t_ITy>
inline t_Ty                                             as(t_ITy    in);
template<typename t_Ty>
 phantom::reflection::ReferenceType*                    referenceTypeOf();
template<typename t_Ty>
 phantom::reflection::Type*                             constTypeOf();
template<typename t_Ty>
 phantom::reflection::ArrayType*                        arrayTypeOf(size_t);
template<typename t_Ty>
 phantom::reflection::DataPointerType*                  pointerTypeOf();

o_export inline phantom::reflection::Namespace*         rootNamespace();
o_export phantom::reflection::Namespace*                namespaceByList( list<string>* a_pNamespaceNameAsStringList );
o_export phantom::reflection::Namespace*                namespaceByName( const string& a_strNamespaceName, reflection::Namespace* a_pScope = rootNamespace() );
o_export inline phantom::reflection::SourceFile*        sourceFile(const string& a_strAbsoluteName);
o_export inline void                                    discardSourceFile(phantom::reflection::SourceFile* a_pSourceFile);
o_export phantom::reflection::Type*                     typeByName(const string& a_strName, phantom::reflection::LanguageElement* a_pScope = reinterpret_cast<phantom::reflection::LanguageElement*>(rootNamespace())) ;
o_export phantom::reflection::Type*					    typeByNameCascade(const string& a_strName, phantom::reflection::LanguageElement* a_pScope = reinterpret_cast<phantom::reflection::LanguageElement*>(rootNamespace())) ; 
o_export string                                         encodeQualifiedDecoratedNameToIdentifierName(const string& a_strTypeName) ;
o_export string                                         decodeQualifiedDecoratedNameFromIdentifierName(const string& a_strTypeName) ;
o_export phantom::reflection::LanguageElement*          elementByName(const string& a_strName, phantom::reflection::LanguageElement* a_pScope = reinterpret_cast<phantom::reflection::LanguageElement*>(rootNamespace())) ;
o_export phantom::reflection::Function*                 functionByName( const string& a_strName, phantom::reflection::Namespace* a_pScope = rootNamespace() );
o_export phantom::reflection::Language*                 cplusplus();
o_export phantom::reflection::Interpreter*              interpreter();
o_export void                                           deleteElement(phantom::reflection::LanguageElement*  a_pLanguageElement) ;
o_export phantom::reflection::Expression*               expressionByName(const string& a_strName, phantom::reflection::LanguageElement* a_pScope = reinterpret_cast<phantom::reflection::LanguageElement*>(rootNamespace())) ;
o_export void                                           elementsByClass(reflection::Class* a_pClass, vector<reflection::LanguageElement*>& out, phantom::reflection::LanguageElement* a_pScope = reinterpret_cast<phantom::reflection::LanguageElement*>(rootNamespace())) ;
o_export phantom::reflection::LanguageElement*		    elementByNameCascade(const string& a_strName, phantom::reflection::Namespace* a_pScope = rootNamespace());
o_export phantom::reflection::Type*                     typeByGuid(uint guid) ;
o_export phantom::reflection::LanguageElement*          elementByGuid(uint guid) ;

template<typename t_Ty>
o_forceinline    t_Ty*                                  elementByNameAs(const string& a_strName, phantom::reflection::LanguageElement* a_pRootElement = reinterpret_cast<phantom::reflection::LanguageElement*>(rootNamespace())) { return as<t_Ty*>(elementByName(a_strName, a_pRootElement)); }
o_export phantom::reflection::Class*                    classByName(const string& a_strQualifiedName, phantom::reflection::LanguageElement* a_pRootScope = reinterpret_cast<phantom::reflection::LanguageElement*>(rootNamespace())) ;

o_export void*                                          baseOf(void const* a_pThis, size_t a_uiLevel);
o_export phantom::reflection::Class*                    classOf(void const* a_pThis, size_t a_uiLevel);
o_export phantom::reflection::Class*                    classAt(void const* a_pThis, size_t a_uiLevel);
o_export const phantom::rtti_data&                      rttiDataOf(void const* a_pThis, size_t a_uiLevel);
o_export const phantom::rtti_data&                      rttiDataOf(void const* a_pThis, reflection::Class* a_pLayoutClass);
o_export void                                           rttiLayoutOf(void const* a_pThis, vector<void*>& out, size_t a_uiLevel);
o_export void                                           dynamicDelete(void* a_pThis o_memory_stat_append_parameters);
o_export inline void                                    addRttiData(void const* a_pThis, const rtti_data& data);
o_export inline void                                    replaceRttiData(void const* a_pThis, const rtti_data& data);
o_export inline void                                    removeRttiData(void const* a_pThis, size_t a_uiLevel);

o_export void                                           assertion BOOST_PREVENT_MACRO_SUBSTITUTION ( const character* e, const character* m , const char* f , uint l);
o_export void                                           warning BOOST_PREVENT_MACRO_SUBSTITUTION (const character* e, const character* m, const char* f, uint l);
o_export void                                           error BOOST_PREVENT_MACRO_SUBSTITUTION (const character* e, const character* m, const char* f, uint l);



enum EMessageType
{
    e_MessageType_Undefined,
    e_MessageType_Information,
    e_MessageType_Success,
    e_MessageType_Warning,
    e_MessageType_Error,
};

o_export void                                           message(const string& a_strCategory, EMessageType a_eType, const phantom::variant& a_Data, char* a_Format, ... );
o_export void                                           message(const string& a_strCategory, EMessageType a_eType, const phantom::variant& a_Data, char* a_Format, va_list args);
o_export Message*                                       topMessage(const string& a_strCategory);
o_export void                                           clearMessages(const string& a_strCategory);
o_export void                                           pushMessage(const string& a_strCategory, EMessageType a_eType, const phantom::variant& a_Data, char* a_Format, ...);
o_export void                                           pushMessage(const string& a_strCategory, EMessageType a_eType, const phantom::variant& a_Data, char* a_Format, va_list args);
o_export void                                           popMessage(const string& a_strCategory);

o_export size_t                                         currentThreadId();
o_export void                                           yieldCurrentThread();

o_export void                                           installReflection(const string& a_strName, const string& a_strFileName, size_t a_PlatformHandle);
o_export void                                           uninstallReflection(const string& a_strName);

o_export void                                           pushModule(Module* a_pModule);
o_export Module*                                        popModule();
o_export Module*                                        currentModule();
o_export ModuleLoader*                                  moduleLoader();
o_export Module*                                        moduleByName(const string& a_strName);
o_export Module*                                        moduleByFileName(const string& a_strFileName);
o_export map<string, Module*>::const_iterator           beginModules();
o_export map<string, Module*>::const_iterator           endModules();
o_export void                                           release();

o_export phantom::reflection::Type*                     backupType(phantom::reflection::Type* a_pType = (phantom::reflection::Type*)0xffffffff);

o_export void                                           setCurrentDataBase(serialization::DataBase* a_pDataBase);
o_export serialization::DataBase*                       getCurrentDataBase();

template <typename t_Ty>
phantom::reflection::Constant*                          constant(t_Ty a_Constant);

o_namespace_end(phantom)

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

#include "phantom/def_exceptions.h"
#include "phantom/def_connection.h"

#include "phantom/def_extension.h"
#include "phantom/def_allocate.h"
#include "phantom/def_reflection.h"
#include "phantom/def_statechart.h"
#include "phantom/def_modules.h"
#include "phantom/def_declare.h"
#include "phantom/def_util.h"
#include "phantom/def_math.h"

#include "phantom/data.h"

#include "phantom/def_serialization.h"

o_namespace_begin(phantom)

typedef std::pair<data,data> data_pair;

o_namespace_end(phantom)

#include <phantom/object.h>

o_namespace_begin(phantom)
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
    rtti_data() 
        : object_class(0)
        , layout_class(0)
        , base(0)
        , connection_slot_allocator(0)
        , dynamic_delete_func(0)
        , level(0)
    {
    
    }
    rtti_data(phantom::reflection::Class* bc
                , phantom::reflection::Class*    tc
                , void*    b
                , connection::slot_pool* csa
                , dynamic_delete_func_t a_dynamic_delete_func
                , size_t a_level)
        : object_class(bc)
        , layout_class(tc)
        , base(b)
        , connection_slot_allocator(csa)
        , dynamic_delete_func(a_dynamic_delete_func)
        , level(a_level)
    {
        o_assert((bc == nullptr AND b == nullptr) OR dynamic_delete_func);
    }
    o_forceinline boolean isBase() const { return object_class == layout_class; }
    o_forceinline boolean isNull() const { return object_class == NULL; }
    inline void deleteNow(o_memory_stat_insert_parameters) const;

    o_forceinline void*   cast(reflection::Class* a_pTargetClass) const ;
    o_forceinline phantom::data     data() const { return phantom::data(base,(reflection::Type*)object_class); }
    o_forceinline phantom::object   object() const { return phantom::object(base,(reflection::ClassType*)object_class); }

    phantom::reflection::Class*     object_class;
    phantom::reflection::Class*     layout_class;
    void*                           base;
    connection::slot_pool*          connection_slot_allocator;
    dynamic_delete_func_t           dynamic_delete_func;
    size_t                          level;
};

#include "data.inl"
#include "object.inl"

o_export inline const phantom::rtti_data&               rttiDataOf(void const* a_pThis, size_t a_uiLevel);
o_export inline const phantom::rtti_data&               rttiDataOf(void const* a_pThis, reflection::Class* a_pLayoutClass);
 o_export inline void                                   rttiLayoutOf(void const* a_pThis, vector<void*>& out, size_t a_uiLevel);

o_export void default_assert(const character* expression, const character* message, const char* file, uint line);
o_export void default_warning(const character* expression, const character* message, const char* file, uint line);
o_export void default_error(const character* expression, const character* message, const char* file, uint line);
o_export void default_log(int level, const char* file, uint line, const char* message, va_list args);

/*

template<typename t_Ty, int t_counter>
o_forceinline phantom::reflection::Type*        pointedTypeOf()
{
    return reflection::detail::type_of<boost::remove_pointer<t_Ty>::type>::object();
}

template<typename t_Ty>
o_forceinline phantom::reflection::Type*        rootPointedTypeOf()
{
    return reflection::detail::root_pointed_type_of_<t_Ty>::object();
}*/

template <typename t_Ty>
o_forceinline string                            decoratedTypeNameOf()
{
    return phantom::reflection::detail::type_name_of_counter<t_Ty, o_read_compilation_counter>::decoratedName();
}

template <typename t_Ty>
o_forceinline string                            typeNameOf()
{
    return phantom::reflection::detail::type_name_of_counter<t_Ty, o_read_compilation_counter>::name();
}

template <typename t_Ty>
o_forceinline string                            qualifiedTypeNameOf()
{
    return phantom::reflection::detail::type_name_of_counter<t_Ty, o_read_compilation_counter>::qualifiedName();
}

template <typename t_Ty>
o_forceinline string                            qualifiedDecoratedTypeNameOf()
{
    return phantom::reflection::detail::type_name_of_counter<t_Ty, o_read_compilation_counter>::qualifiedDecoratedName();
}

template <typename t_Ty>
o_forceinline const char*                       namespaceNameOf()
{
    return phantom::reflection::detail::type_name_of_counter<t_Ty, o_read_compilation_counter>::namespaceName();
}

template <typename t_Ty>
o_forceinline const char*                       classScopeNameOf()
{
    return phantom::reflection::detail::type_name_of_counter<t_Ty, o_read_compilation_counter>::classScopeName();
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
    phantom::reflection::typedef_registrer<t_Ty>(a_strNamespace, a_strTypedef);
}

template <typename t_Ty>
o_forceinline void                              registerTypedef(const char* a_strTypedef)
{
    phantom::reflection::typedef_registrer<t_Ty>(a_strTypedef);
}

o_export boolean                 canConnect(phantom::reflection::Signal* a_pSignal, phantom::reflection::InstanceMemberFunction* a_pMemberFunction );

o_export connection::slot const*    connect(const rtti_data& a_Sender, const character* a_pSignal, const rtti_data& a_Receiver, const character* a_pMemberFunction);
o_export connection::slot const*    disconnect(const rtti_data& a_Sender, const character* a_pSignal, const rtti_data& a_Receiver, const character* a_pMemberFunction);
o_export connection::slot const*    connect(const rtti_data& a_Sender, phantom::reflection::Signal* a_pSignal, const rtti_data& a_Receiver, phantom::reflection::InstanceMemberFunction* a_pMemberFunction);
o_export connection::slot const*    disconnect(const rtti_data& a_Sender, phantom::reflection::Signal* a_pSignal, const rtti_data& a_Receiver, phantom::reflection::InstanceMemberFunction* a_pMemberFunction);
o_export connection::slot const*    tryConnect(const rtti_data& a_Sender, const character* a_pSignal, const rtti_data& a_Receiver, const character* a_pMemberFunction);
o_export connection::slot const*    tryDisconnect(const rtti_data& a_Sender, const character* a_pSignal, const rtti_data& a_Receiver, const character* a_pMemberFunction);
o_export boolean                    areConnected( const rtti_data& a_Sender, const character* a_pSignal, const rtti_data& a_Receiver, const character* a_pMemberFunction );

template<typename t_Sender, typename t_Receiver>
connection::slot const*             connect(t_Sender* a_pSender, const character* a_pSignal, t_Receiver* a_pReceiver, const character* a_pMemberFunction)
{
    reflection::Type* pSenderType = phantom::typeOf<typename boost::remove_const<t_Sender>::type>();
    reflection::Type* pReceiverType = phantom::typeOf<typename boost::remove_const<t_Receiver>::type>();
    return connect(rttiDataOf(a_pSender, pSenderType ? pSenderType->asClass() : nullptr), a_pSignal
                 , rttiDataOf(a_pReceiver, pReceiverType ? pReceiverType->asClass() : nullptr), a_pMemberFunction);
}

template<typename t_Sender, typename t_Receiver>
connection::slot const*             disconnect(t_Sender* a_pSender, const character* a_pSignal, t_Receiver* a_pReceiver, const character* a_pMemberFunction)
{
    reflection::Type* pSenderType = phantom::typeOf<typename boost::remove_const<t_Sender>::type>();
    reflection::Type* pReceiverType = phantom::typeOf<typename boost::remove_const<t_Receiver>::type>();
    return disconnect(rttiDataOf(a_pSender, pSenderType ? pSenderType->asClass() : nullptr), a_pSignal
                    , rttiDataOf(a_pReceiver, pReceiverType ? pReceiverType->asClass() : nullptr), a_pMemberFunction);
}

template<typename t_Sender, typename t_Receiver>
connection::slot const*             connect(t_Sender* a_pSender, phantom::reflection::Signal* a_pSignal, t_Receiver* a_pReceiver, phantom::reflection::InstanceMemberFunction* a_pMemberFunction)
{
    reflection::Type* pSenderType = phantom::typeOf<typename boost::remove_const<t_Sender>::type>();
    reflection::Type* pReceiverType = phantom::typeOf<typename boost::remove_const<t_Receiver>::type>();
    return connect(rttiDataOf(a_pSender, pSenderType ? pSenderType->asClass() : nullptr), a_pSignal
                 , rttiDataOf(a_pReceiver, pReceiverType ? pReceiverType->asClass() : nullptr), a_pMemberFunction);
}

template<typename t_Sender, typename t_Receiver>
connection::slot const*             disconnect(t_Sender* a_pSender, phantom::reflection::Signal* a_pSignal, t_Receiver* a_pReceiver, phantom::reflection::InstanceMemberFunction* a_pMemberFunction)
{
    reflection::Type* pSenderType = phantom::typeOf<typename boost::remove_const<t_Sender>::type>();
    reflection::Type* pReceiverType = phantom::typeOf<typename boost::remove_const<t_Receiver>::type>();
    return disconnect(rttiDataOf(a_pSender, pSenderType ? pSenderType->asClass() : nullptr), a_pSignal
                    , rttiDataOf(a_pReceiver, pReceiverType ? pReceiverType->asClass() : nullptr), a_pMemberFunction);
}

template<typename t_Sender, typename t_Receiver>
connection::slot const*             tryConnect(t_Sender* a_pSender, const character* a_pSignal, t_Receiver* a_pReceiver, const character* a_pMemberFunction)
{
    reflection::Type* pSenderType = phantom::typeOf<typename boost::remove_const<t_Sender>::type>();
    reflection::Type* pReceiverType = phantom::typeOf<typename boost::remove_const<t_Receiver>::type>();
    return tryConnect(rttiDataOf(a_pSender, pSenderType ? pSenderType->asClass() : nullptr), a_pSignal
                    , rttiDataOf(a_pReceiver, pReceiverType ? pReceiverType->asClass() : nullptr), a_pMemberFunction);
}

template<typename t_Sender, typename t_Receiver>
connection::slot const*             tryDisconnect(t_Sender* a_pSender, const character* a_pSignal, t_Receiver* a_pReceiver, const character* a_pMemberFunction)
{
    reflection::Type* pSenderType = phantom::typeOf<typename boost::remove_const<t_Sender>::type>();
    reflection::Type* pReceiverType = phantom::typeOf<typename boost::remove_const<t_Receiver>::type>();
    return tryDisconnect(rttiDataOf(a_pSender, pSenderType ? pSenderType->asClass() : nullptr), a_pSignal
                       , rttiDataOf(a_pReceiver, pReceiverType ? pReceiverType->asClass() : nullptr), a_pMemberFunction);
}

template<typename t_Sender, typename t_Receiver>
boolean                             areConnected(t_Sender* a_pSender, const character* a_pSignal, t_Receiver* a_pReceiver, const character* a_pMemberFunction )
{
    reflection::Type* pSenderType = phantom::typeOf<typename boost::remove_const<t_Sender>::type>();
    reflection::Type* pReceiverType = phantom::typeOf<typename boost::remove_const<t_Receiver>::type>();
    return areConnected(rttiDataOf(a_pSender, pSenderType ? pSenderType->asClass() : nullptr), a_pSignal
                      , rttiDataOf(a_pReceiver, pReceiverType ? pReceiverType->asClass() : nullptr), a_pMemberFunction);
}

o_export void       assertion BOOST_PREVENT_MACRO_SUBSTITUTION ( const character* e, const character* m , const char* f , uint l);
o_export void       warning BOOST_PREVENT_MACRO_SUBSTITUTION (const character* e, const character* m, const char* f, uint l);
o_export void       error BOOST_PREVENT_MACRO_SUBSTITUTION (const character* e, const character* m, const char* f, uint l);
o_export void       log BOOST_PREVENT_MACRO_SUBSTITUTION (int level, const char* file, uint line, const char* message, ...);


o_namespace_end(phantom)


#include "phantom/def_phantom_0_4.inl"

namespace detail
{
    class o_export dynamic_initializer_handle
    {
        friend o_export void installReflection(const string& a_strName);
        friend o_export void uninstallReflection(const string& a_strName);
        typedef void    (*module_installation_func)        (phantom::reflection::Type*,uint);
        friend class phantom::Phantom;
        template<typename> friend struct phantom::reflection::type_reflection_registrer;


    protected:
        dynamic_initializer_handle();
        ~dynamic_initializer_handle();
        phantom::reflection::Namespace*
            parseNamespace(const string& a_strFileName) const;

    protected:
        struct dynamic_initializer_module_installation_func
        {
            dynamic_initializer_module_installation_func() : setupFunc(NULL) {}
            dynamic_initializer_module_installation_func( phantom::reflection::Type*      a_pType, module_installation_func    a_setupFunc )
                : type(a_pType)
                , setupFunc(a_setupFunc)
            {

            }
            o_forceinline void exec(uint step)
            {
                (*setupFunc)(type, step);
            }
            o_forceinline bool operator<(const dynamic_initializer_module_installation_func& other) const;
            module_installation_func        setupFunc;
            phantom::reflection::Type*      type;
        };

        struct deferred_function_registrer_base 
        {
            virtual ~deferred_function_registrer_base() {}
            virtual void registerFunction() = 0;
        };

        template<typename t_SignatureTy, typename t_FunctionPtrTy>
        struct deferred_function_registrer : public deferred_function_registrer_base
        {
            deferred_function_registrer() {}
            deferred_function_registrer(const string& a_Namespace, const string& a_Name, const string& a_Signature, t_FunctionPtrTy a_FunctionPtr, bitfield a_Modifiers = 0)
                : m_Name(a_Name)
                , m_Namespace(a_Namespace)
                , m_Signature(a_Signature)
                , m_FunctionPtr(a_FunctionPtr)
                , m_Modifiers(a_Modifiers)
            {

            }
            virtual void registerFunction()
            {
                reflection::Namespace* pNamespace = m_Namespace.empty() ? phantom::rootNamespace() : phantom::namespaceByName(m_Namespace);
                pNamespace->addFunction(
                    phantom::reflection::native::TNativeFunctionProvider<t_SignatureTy>::CreateFunction(m_Name, phantom::reflection::Signature::Create(m_Signature.c_str(), nullptr, pNamespace), m_FunctionPtr, m_Modifiers)
                );
            }
            string m_Name;
            string m_Namespace;
            string m_Signature;
            t_FunctionPtrTy  m_FunctionPtr;
            bitfield m_Modifiers;
        };
        typedef vector<dynamic_initializer_module_installation_func>        dynamic_initializer_module_installation_func_vector;

    private:
        vector<dynamic_initializer_module_installation_func_vector>     m_DeferredSetupInfos;
        vector<reflection::Template*>                                   m_DeferredTemplates;
        vector<deferred_function_registrer_base*>               m_DeferredFunctions;
        int                                                             m_iCurrentInstallationStep;
        unordered_map<string, reflection::Type*>                        m_RegisteredTypes;
        bool                                                            m_bActive;
        bool                                                            m_bAutoRegistrationLocked;

    public:
        inline reflection::Type*    registeredTypeByName(const string& a_strQualifiedDecoratedName)
        {
            auto found = m_RegisteredTypes.find(a_strQualifiedDecoratedName);
            if(found == m_RegisteredTypes.end()) return nullptr;
            return found->second;
        }
        void    registerType( const string& a_strQualifiedDecoratedName, phantom::reflection::Type* a_pType );
        void    registerType( const string& a_strQualifiedDecoratedName, const string& a_strNamespace, const string& a_strClassScope, phantom::reflection::Type* a_pType );
        void    registerModule( phantom::reflection::Type* a_pType, module_installation_func setupFunc, uint a_uiSetupStepMask );
        void    registerTemplate( reflection::Template* a_pTemplate );
        void    installReflection(const string& a_strName, const string& a_strFileName, size_t a_PlatformHandle);
        void    uninstallReflection(const string& a_strName);
        bool    isActive() const { return m_bActive; }
        bool    isAutoRegistrationLocked() const { return m_bAutoRegistrationLocked; }
        void    setActive(bool a_bActive) { o_assert(a_bActive == !m_bActive); m_bActive = a_bActive; }
        void    setAutoRegistrationLocked(bool a_bLocked) { o_assert(a_bLocked == !m_bAutoRegistrationLocked); m_bAutoRegistrationLocked = a_bLocked; }
        template<typename t_SignatureTy, typename t_FunctionPtrTy>
        void    registerFunction( const string& a_Namespace, const string& a_Name, const string& a_Signature, t_FunctionPtrTy a_FunctionPtr, bitfield a_Modifiers = 0 )
        {
            m_DeferredFunctions.push_back(new deferred_function_registrer<t_SignatureTy, t_FunctionPtrTy>(a_Namespace, a_Name, a_Signature, a_FunctionPtr, a_Modifiers));
        }
    };
}

class o_export Phantom
{
public:
    o_friend(class, phantom, reflection, LanguageElement)
    o_friend(class, phantom, reflection, Class) // for rtti registration access
    
    template<typename,typename> friend class TNativeType;
    template<typename,uint > friend struct extension::detail::rtti_data_registrer_helper_;
    template<typename t_Ty, extension::detail::default_installer_id>  friend struct extension::detail::default_installer_helper;

    typedef boost::pool<phantom::memory::malloc_free_allocator_for_boost> dynamic_pool_type ;
    typedef phantom::map<size_t, dynamic_pool_type*>                        dynamic_pool_type_map;
    typedef void (*message_report_func)(const character*, const character*, const char*, uint);
    typedef void (*log_func)(int level, const char* file, uint line, const char* message, va_list arglist);

    typedef phantom::unordered_map<void const*, phantom::vector<rtti_data>>		rtti_data_map;
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
    friend o_export connection::slot const* connect(const rtti_data& a_Sender, const character* a_pSignal, const rtti_data& a_Receiver, const character* a_pMemberFunction);
    friend o_export connection::slot const* connect(const rtti_data& a_Sender, phantom::reflection::Signal* a_pSignal, const rtti_data& a_Receiver, phantom::reflection::InstanceMemberFunction* a_pMemberFunction);
    friend o_export connection::slot const* disconnect(const rtti_data& a_Sender, phantom::reflection::Signal* a_pSignal, const rtti_data& a_Receiver, phantom::reflection::InstanceMemberFunction* a_pMemberFunction);
    friend o_export connection::slot const* disconnect(const rtti_data& a_Sender, const character* a_pSignal, const rtti_data& a_Receiver, const character* a_pMemberFunction);
    friend o_export connection::slot const* tryConnect(const rtti_data& a_Sender, const character* a_pSignal, const rtti_data& a_Receiver, const character* a_pMemberFunction);
    friend o_export connection::slot const* tryDisconnect(const rtti_data& a_Sender, const character* a_pSignal, const rtti_data& a_Receiver, const character* a_pMemberFunction);
    friend o_export boolean                 areConnected(const rtti_data& a_Sender, const character* a_pSignal, const rtti_data& a_Receiver, const character* a_pMemberFunction);
    friend o_export void assertion BOOST_PREVENT_MACRO_SUBSTITUTION ( const character* e, const character* m , const char* f , uint l);
    friend o_export void warning BOOST_PREVENT_MACRO_SUBSTITUTION (const character* e, const character* m, const char* f, uint l);
    friend o_export void error BOOST_PREVENT_MACRO_SUBSTITUTION (const character* e, const character* m, const char* f, uint l);
    friend o_export void log BOOST_PREVENT_MACRO_SUBSTITUTION (int level, const char* file, uint line, const char* message, ...);

    friend o_export void pushModule(Module* a_pModule);
    friend o_export Module* popModule();
    friend o_export Module* currentModule();
    friend o_export void setCurrentDataBase(serialization::DataBase*);
    friend o_export serialization::DataBase* getCurrentDataBase();
    friend o_export ModuleLoader* moduleLoader();
    friend o_export Module* moduleByName(const string& a_strName);
    friend o_export Module* moduleByFileName(const string& a_strFileName);
    friend o_export map<string, Module*>::const_iterator beginModules();
    friend o_export map<string, Module*>::const_iterator endModules();
    template <typename t_Ty>
    friend phantom::reflection::Constant* constant(t_Ty a_Constant);

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

    template<typename t_Ty>
    friend phantom::reflection::ReferenceType*  referenceTypeOf();
    template<typename t_Ty>
    friend phantom::reflection::Type*           constTypeOf();
    template<typename t_Ty>
    friend phantom::reflection::ArrayType*      arrayTypeOf(size_t);
    template<typename t_Ty>
    friend phantom::reflection::DataPointerType*pointerTypeOf();


    friend o_export void*                       baseOf(void const* a_pThis, size_t a_uiLevel);
    friend o_export phantom::reflection::Class* classOf(void const* a_pThis, size_t a_uiLevel);
    friend o_export phantom::reflection::Class* classAt(void const* a_pThis, size_t a_uiLevel);
    friend o_export const phantom::rtti_data&   rttiDataOf(void const* a_pThis, size_t a_uiLevel);
    friend o_export const phantom::rtti_data&   rttiDataOf(void const* a_pThis, reflection::Class* a_pLayoutClass);
    friend o_export void                        rttiLayoutOf(void const* a_pThis, vector<void*>& out, size_t a_uiLevel);
    friend o_export void                        dynamicDelete(void* a_pThis o_memory_stat_append_parameters);
    friend o_export void                        replaceRttiData(void const* ptr, const rtti_data& data);
    friend o_export void                        addRttiData(void const* ptr, const rtti_data& data);
    friend o_export void                        removeRttiData(void const* ptr, size_t a_uiLevel);



    friend o_export void                        message(const string& a_strCategory, EMessageType a_eType, const phantom::variant& a_Data, char* a_Format, ... );
    friend o_export void                        message(const string& a_strCategory, EMessageType a_eType, const phantom::variant& a_Data, char* a_Format, va_list args );
    friend o_export Message*                    topMessage(const string& a_strCategory);
    friend o_export void                        clearMessages(const string& a_strCategory);
    friend o_export void                        pushMessage(const string& a_strCategory, EMessageType a_eType, const phantom::variant& a_Data, char* a_Format, ...);
    friend o_export void                        pushMessage(const string& a_strCategory, EMessageType a_eType, const phantom::variant& a_Data, char* a_Format, va_list args);
    friend o_export void                        popMessage(const string& a_strCategory);



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
    static boolean                    areConnected( const rtti_data& a_Sender, phantom::reflection::Signal* a_pSignal, const rtti_data& a_Receiver, phantom::reflection::InstanceMemberFunction* a_pMemberFunction );
    struct type_sorter_by_build_order
    {
        bool        operator()(reflection::Type* one, reflection::Type* another);
    };

    static void					release();


private:
    typedef map<string, Message*> message_map;
    static EState					m_eState;
    static uint						m_uiSetupStep;
    static dynamic_pool_type_map	m_DynamicPoolAllocators;
    static rtti_data_map*			m_rtti_data_map;
    static message_report_func		m_assert_func;
    static message_report_func		m_error_func;
    static message_report_func		m_warning_func;
    static log_func		            m_log_func;
    static message_map              m_Messages;
    static Phantom*					m_instance;
	static element_container*		m_elements;
    static Module*                  m_module;
    static ModuleLoader*            m_module_loader;
    static serialization::DataBase* m_current_data_base;
    static map<string, Module*>     m_modules;
    static vector<reflection::Constant*> m_Constants;
    vector<string>                  m_meta_data_names;
    static map<string, reflection::SourceFile*> m_SourceFiles;
    static reflection::Type*		m_type_of_string;

public:
    friend o_export phantom::reflection::Namespace*     namespaceByName(  const string& a_strNamespaceName, reflection::Namespace* a_pScopeNamespace);
    friend o_export phantom::reflection::Namespace*     namespaceByList( list<string>* a_pNamespaceNameAsStringList );

    friend o_export phantom::reflection::Namespace*     rootNamespace();
    friend o_export inline phantom::reflection::SourceFile* sourceFile(const string& elementName);
    friend o_export inline void                         discardSourceFile(phantom::reflection::SourceFile* a_pSourceFile);
    friend o_export inline const string&                metaDataName(size_t index) ;
    friend o_export inline size_t                       metaDataCount();
    friend o_export inline size_t                       metaDataIndex(const string& elementName);

    friend o_export inline reflection::Type*            stringType();

    friend o_export phantom::reflection::LanguageElement*elementByName( const string& a_strName, phantom::reflection::LanguageElement* a_pRootElement );
    friend o_export phantom::reflection::Function*      functionByName( const string& a_strName, phantom::reflection::Namespace* a_pRootElement );
    friend o_export phantom::reflection::Expression*    expressionByName( const string& a_strName, phantom::reflection::LanguageElement* a_pRootElement );
    friend o_export phantom::reflection::Language*      cplusplus();
    friend o_export phantom::reflection::Interpreter*   interpreter();

private:
    static phantom::reflection::Namespace* m_pRootNamespace;
    static phantom::reflection::CPlusPlus* m_pCPlusPlus;
    static phantom::reflection::Interpreter* m_pInterpreter;
    static void*                m_typeOf_cycling_address_workaround_ptr;
    template<typename, uint> friend class rtti_data_registrer_helper_;
public:

    static detail::dynamic_initializer_handle*                dynamic_initializer();
    friend o_export class detail::dynamic_initializer_handle;
};

#include "phantom/def_phantom_0_3.inl"

// Some member_functions implementations which depends on phantom::Phantom

o_export inline phantom::reflection::Namespace*     rootNamespace() { return phantom::Phantom::m_pRootNamespace; }
o_export inline phantom::reflection::SourceFile*    sourceFile(const string& absoluteName) { return phantom::Phantom::sourceFile(absoluteName); }
o_export inline void                                discardSourceFile(phantom::reflection::SourceFile* a_pSourceFile) { return phantom::Phantom::discardSourceFile(a_pSourceFile); }

enum 
{
    eInvalidMetaDataIndex = 0xffffffff,
};


o_export inline reflection::Type*                   stringType() { return Phantom::m_type_of_string; }

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
    Phantom::dynamic_initializer()->setActive(true);
    Phantom::dynamic_initializer(); // ensure modules (and especially reflection here) are initialized and ready
    phantom::typeOf<t_Ty>();
    Phantom::dynamic_initializer()->setActive(false);
}

template<typename t_Ty>
inline void reflection::type_reflection_registrer<t_Ty>::apply(Type* a_pType)
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

o_export phantom::reflection::Signature*             createSignature(const char* a_pText, phantom::reflection::TemplateSpecialization* a_pTemplateSpecialization, phantom::reflection::LanguageElement* a_pScope);

o_export inline void*                                baseOf(void const* a_pThis, size_t a_uiLevel = 0)
{
    phantom::Phantom::rtti_data_map::const_iterator found = phantom::Phantom::m_rtti_data_map->find(a_pThis);
    return (found != phantom::Phantom::m_rtti_data_map->end())
        ? found->second[a_uiLevel].base
        : const_cast<void*>(a_pThis);
    
}

o_export inline phantom::reflection::Class*          classOf(void const* a_pThis, size_t a_uiLevel)
{
    phantom::Phantom::rtti_data_map::const_iterator found = phantom::Phantom::m_rtti_data_map->find(a_pThis);
    return (found != phantom::Phantom::m_rtti_data_map->end())
                ? found->second[a_uiLevel].object_class
                : nullptr;
}

o_export inline phantom::reflection::Class*          classAt(void const* a_pThis, size_t a_uiLevel)
{
    phantom::Phantom::rtti_data_map::const_iterator found = phantom::Phantom::m_rtti_data_map->find(a_pThis);
    return (found != phantom::Phantom::m_rtti_data_map->end())
                ? found->second[a_uiLevel].layout_class
                : nullptr;
}

o_export inline const phantom::rtti_data&            rttiDataOf(void const* a_pThis, size_t a_uiLevel)
{
    static phantom::rtti_data null_info(0,0,0,0,0,0);
    phantom::Phantom::rtti_data_map::const_iterator found = phantom::Phantom::m_rtti_data_map->find(a_pThis);
    return (found != phantom::Phantom::m_rtti_data_map->end())
                ? (a_uiLevel < found->second.size())
                    ? found->second[a_uiLevel]
                    : null_info
                : null_info;
}

o_export void                                        rttiLayoutOf(void const* a_pThis, vector<void*>& out, size_t a_uiLevel)
{
    static phantom::rtti_data null_info(0,0,0,0,0,0);
    phantom::Phantom::rtti_data_map::const_iterator found = phantom::Phantom::m_rtti_data_map->find(a_pThis);
    if(found != phantom::Phantom::m_rtti_data_map->end())
    {
        void* base_address = found->second[a_uiLevel].base;
        auto it = phantom::Phantom::m_rtti_data_map->begin();
        auto end = phantom::Phantom::m_rtti_data_map->end();
        for(;it!=end;++it)
        {
            if(it->second[a_uiLevel].base == base_address)
            {
                out.push_back((void*)it->first);
            }
        }
    }
}

o_export inline void                                        addRttiData(void const* a_pThis, const rtti_data& a_RttiData)
{
    auto& rtti_datas = (*Phantom::m_rtti_data_map)[a_pThis];
    o_assert(a_RttiData.level >= rtti_datas.size());
    rtti_datas.resize(a_RttiData.level+1);
    rtti_datas[a_RttiData.level] = a_RttiData;
}

o_export inline void                                        replaceRttiData(void const* a_pThis, const rtti_data& a_RttiData)
{
    phantom::Phantom::rtti_data_map::iterator found = phantom::Phantom::m_rtti_data_map->find(a_pThis);
    o_assert(found != phantom::Phantom::m_rtti_data_map->end());
    auto& levels = found->second;
    o_assert(a_RttiData.level < levels.size());
    levels[a_RttiData.level] = a_RttiData;
}

o_export inline void                                        removeRttiData(void const* a_pThis, size_t a_uiLevel)
{
    phantom::Phantom::rtti_data_map::iterator found = phantom::Phantom::m_rtti_data_map->find(a_pThis);
    o_assert((found != phantom::Phantom::m_rtti_data_map->end() 
                && (found->second.size()-1) == a_uiLevel), "remove order must be reversed of add order (LIFO/Stack)");
    found->second.pop_back();
    while(!found->second.empty() && found->second.back().isNull())
        found->second.pop_back();

    if(found->second.empty())
    {
        phantom::Phantom::m_rtti_data_map->erase(found);
    }
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

o_export void* dynamicPoolAllocate(size_t s o_memory_stat_append_parameters);
o_export void  dynamicPoolDeallocate(size_t s, void* a_pAddress o_memory_stat_append_parameters);
o_export void* dynamicPoolAllocate(size_t s, size_t count o_memory_stat_append_parameters);
o_export void  dynamicPoolDeallocate(size_t s, void* a_pAddress, size_t count o_memory_stat_append_parameters);

o_namespace_end(phantom)

#include "phantom/def_memory.inl"
#include "phantom/reflection/native/NativeVTableInspector.h"
#include "phantom/Module.h"
#include "phantom/variant.h"
#include "phantom/reflection/LanguageElement.h"
#include "phantom/reflection/TemplateElement.h"
#include "phantom/reflection/Template.h"
#include "phantom/reflection/Signature.h"
#include "phantom/reflection/VirtualMemberFunctionTable.h"
#include "phantom/reflection/Type.h"
#include "phantom/reflection/ConstType.h"


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
#include "phantom/reflection/ReferenceType.h"
#include "phantom/reflection/ArrayType.h"
#include "phantom/reflection/ValueMember.h"
#include "phantom/reflection/Constant.h"
#include "phantom/reflection/NumericConstant.h"
#include "phantom/reflection/Variable.h"
#include "phantom/reflection/Addressable.h"
#include "phantom/reflection/Constant.h"
#include "phantom/reflection/Iterator.h"
#include "phantom/reflection/ConstIterator.h"
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
#include "phantom/reflection/Structure.h"


#include "phantom/reflection/native/TNumericConstant.h"

#include "phantom/def_phantom_0_2.inl"

#include "phantom/reflection/Enum.h"

#include "phantom/reflection/Member.h"
#include "phantom/reflection/MemberFunction.h"
#include "phantom/reflection/InstanceMemberFunction.h"
#include "phantom/reflection/StaticMemberFunction.h"

o_namespace_begin(phantom, reflection, native)

    template<typename t_Ty>
struct addressable_wrapper
{
    static void*   address(t_Ty call) { return nullptr; }
    enum { value = false };
};

template<typename t_Ty>
struct addressable_wrapper<t_Ty&>
{
    static void*   address(t_Ty& call) { return (void*)&call; }
    enum { value = true };
};

template<typename t_Ty>
struct addressable_wrapper<t_Ty const&>
{
    static void*   address(t_Ty const& call) { return nullptr; }
    enum { value = false };
};

template<typename t_Ty>
struct return_storage_type_helper
{
    typedef t_Ty type;
};

template<typename t_Ty>
struct return_storage_type_helper<t_Ty&>
{
    typedef t_Ty* type;
};

template<typename t_Ty>
struct return_storage_type_helper<const t_Ty>
{
    typedef t_Ty type;
};

template<typename t_Ty>
struct return_storage_wrapper
{
    static t_Ty& apply(const t_Ty& input)
    {
        return (t_Ty&)input;
    }
};

template<typename t_Ty>
struct return_storage_wrapper<t_Ty&>
{
    static t_Ty* apply(t_Ty& input)
    {
        return &input;
    }
};

o_namespace_end(phantom, reflection, native)

#include "phantom/reflection/native/TNativeFunction.h"
#include "phantom/reflection/native/TNativeStaticMemberFunctionBase.h"
#include "phantom/reflection/native/TNativeStaticMemberFunction.h"
#include "phantom/reflection/native/TNativeInstanceMemberFunctionBase.h"
#include "phantom/reflection/native/TNativeInstanceMemberFunction.h"
#include "phantom/reflection/native/TNativeInstanceMemberFunctionConst.h"
#include "phantom/reflection/native/TNativeConstructor.h"
#include "phantom/reflection/native/TNativeDestructor.h"

#include "phantom/reflection/native/TType.h"

#include "phantom/def_phantom_0_1.inl"




#include "phantom/reflection/native/TNativeMemberFunctionProvider.h"
#include "phantom/reflection/native/TNativeFunctionProvider.h"


#if o__int__reflection_template_use_level >= 2
#include "phantom/reflection/native/TNativeSignatureProvider.h"
#include "phantom/reflection/native/TNativePropertySignalProvider.h"
#else 
#include "phantom/reflection/native/DynamicNativeSignalProvider.h"
#endif

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

o_namespace_begin(phantom)

template <typename t_Ty>
phantom::reflection::Constant* constant(t_Ty a_Constant) 
{
    phantom::reflection::Constant* pConstant = o_dynamic_proxy_new(phantom::reflection::NumericConstant, phantom::reflection::NumericConstant::metaType, phantom::reflection::native::TNumericConstant<t_Ty>)(lexical_cast<string>(a_Constant),a_Constant);
    Phantom::m_Constants.push_back(pConstant);
    return pConstant;
}

o_forceinline bool detail::dynamic_initializer_handle::dynamic_initializer_module_installation_func::operator<( const dynamic_initializer_module_installation_func& other ) const
{
    return other.type->isKindOf(type);
}

struct variable
{
    string name;
    variant value;
};

o_namespace_end(phantom)

#if o__int__reflection_template_use_level == 3
#   include "def_phantom_deferred_reflection.inl"
#endif

#include "phantom/def_phantom_0_0.inl"

o_declareN(struct, (phantom, memory), malloc_free_allocator_for_boost);
o_declareNT(struct, (phantom, memory), (typename, typename), (T, UserAllocator), malloc_free_allocator);

#if o__int__reflection_template_use_level == 3
#   include "phantom/phantom.hxx"
#endif

o_declareN(class, (phantom), bitfield);
o_declareNT(class, (phantom), (typename), (Enum), flags);

o_declareN((phantom, connection), slot);
o_declareN((phantom, connection), pair);
o_declareNC((phantom, connection), (slot), list);

#endif // __prerequisites_h__
