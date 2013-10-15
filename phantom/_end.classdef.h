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


#ifndef PHANTOM_BEGIN_CLASSDEF
#    error _begin.classdef.h must be included before any include of _end.classdef.h, they work together as a preprocessor scope
#endif

// Uncomment to debug warning scope : #pragma message("warning push")
#if o_COMPILER == o_COMPILER_VISUAL_STUDIO
#pragma warning(push)
#endif
//  ==================================================================================================
//        UTILS
//  ==================================================================================================
#define o_local_match_specifier(_spec_) (((o_local_value_MetaSpecifiers)&(_spec_)) == (_spec_))

//  ==================================================================================================
//        PHANTOM EXTRA SPECIFIERS
//  ==================================================================================================


#if defined(o_TemplateP)
#    define o_local_value_TemplateSpecifier o_template
#else
#    define o_local_value_TemplateSpecifier 0
#endif

#if defined(o_Super)
#    if o_PP_NARG(o_Super) > 1
#        define o_local_value_InheritanceTypeSpecifier 0 //o_multiple_inheritance
#    else
#        define o_local_value_InheritanceTypeSpecifier 0 //o_single_inheritance
#    endif
#else
#        define o_local_value_InheritanceTypeSpecifier 0
#endif

#define o_local_value_MetaSpecifiers    (o_Flags|o_local_value_TemplateSpecifier|o_local_value_InheritanceTypeSpecifier)


#if (((o_local_value_MetaSpecifiers) & o_proxy) == o_proxy)

#   if o_COMPILER == o_COMPILER_VISUAL_STUDIO
#       pragma warning(disable:4275) // non dll-interface class used as base for dll-interface class
#   endif

#    define o_local_value_ShortEmbeddingType        o_PP_CAT(o_Name, _external_proxy)
#    define o_local_code_EmbeddingClassForwardDeclaration o_local_code_TemplateSignature class o_local_value_ShortEmbeddingType;
#    define o_local_code_Specialize__proxy_of \
    o_local_code_NamespaceAutoBegin\
    o_local_code_TemplateSignature class o_proxy_class_name;\
    o_local_code_NamespaceAutoEnd\
    namespace phantom { \
    o_local_code_TemplateSpecializationSignature \
    struct proxy_of<o_global_value_QualifiedType> { typedef o_local_value_Namespace::o_proxy_class_name o_local_code_TemplateArgumentList type; }; \
    }
#else
#    define o_local_code_EmbeddingClassForwardDeclaration
#    define o_local_value_ShortEmbeddingType        o_Name
#    define o_local_code_Specialize__proxy_of
#endif

//  ==================================================================================================
//        INTERNAL REFLECTION CLASS
//  ==================================================================================================



//  ==================================================================================================
//        USER EXTENSION
//  ==================================================================================================

#include <phantom/_user_end.classdef.h>

//  ==================================================================================================
//        STABLE META-TYPE MEMBERS ADD-MACROS
//  ==================================================================================================

//  ==================================================================================================
//        NAMESPACE STRUCTURE
//  ==================================================================================================

#define o_local_code_StaticCheck_meta_specifiers_and_type_traits_match \
  o_static_assert(NOT(o_match(o_local_value_MetaSpecifiers, o_abstract)) OR boost::is_abstract<o_global_value_QualifiedType>::value ); \
  o_static_assert(NOT(o_match(o_local_value_MetaSpecifiers, o_no_default_constructor)) OR (NOT(boost::has_trivial_default_constructor<o_global_value_QualifiedType>::value) AND NOT(boost::has_nothrow_default_constructor<o_global_value_QualifiedType>::value)) );

#ifndef o_Namespace
#   define o_local_value_Namespace                 o_PP_CREATE_SCOPE_0()
#   define o_local_value_NamespaceString           o_root_namespace_name
#   define o_local_code_NamespaceAutoBegin         o_namespace_begin_0()
#   define o_local_code_NamespaceAutoEnd           o_namespace_end_0()
#else
#   define o_local_value_Namespace                     o_PP_CREATE_SCOPE(o_Namespace) 
#   define o_local_value_NamespaceString               o_PP_QUOTE(o_local_value_Namespace)

#if o_COMPILER == o_COMPILER_VISUAL_STUDIO
#       define o_local_code_NamespaceAutoBegin             o_namespace_begin    o_PP_LEFT_PAREN o_Namespace o_PP_RIGHT_PAREN
#       define o_local_code_NamespaceAutoEnd               o_namespace_end        o_PP_LEFT_PAREN o_Namespace o_PP_RIGHT_PAREN
#else
#       define o_local_code_NamespaceAutoBegin             o_namespace_begin(o_Namespace)
#       define o_local_code_NamespaceAutoEnd               o_namespace_end(o_Namespace)
#endif

#endif

#if defined(o_Namespace)
#   if defined(o_TemplateP)
#       if defined(o_Super)
#           define o_local_declare_reflection \
                o_type_specialize_traitsNTTS((o_Namespace),(o_TemplateT),(o_TemplateP),o_Name,(o_Super))
#       else
#           define o_local_declare_reflection \
                o_type_specialize_traitsNTT((o_Namespace),(o_TemplateT),(o_TemplateP),o_Name)
#       endif
#   else
#       if defined(o_Super)
#           define o_local_declare_reflection \
                o_type_specialize_traitsNS((o_Namespace),o_Name,(o_Super))
#       else
#           define o_local_declare_reflection \
                o_type_specialize_traitsN((o_Namespace),o_Name)
#       endif
#   endif
#else
#   if defined(o_TemplateP)
#       if defined(o_Super)
#           define o_local_declare_reflection \
                o_type_specialize_traitsTTS((o_TemplateT),(o_TemplateP),o_Name,(o_Super))
#       else
#           define o_local_declare_reflection \
                o_type_specialize_traitsTT((o_TemplateT),(o_TemplateP),o_Name)
#       endif
#   else
#       if defined(o_Super)
#           define o_local_declare_reflection \
                o_type_specialize_traitsS(o_Name,(o_Super))
#       else
#           define o_local_declare_reflection \
                o_type_specialize_traits(o_Name)
#       endif
#   endif
#endif

#if defined(o_Namespace)
#   define o_local_code_concat_namespace_sequence , o_Namespace ,
#else
#    define o_local_code_concat_namespace_sequence ,
#endif

#if defined(o_TemplateP)

#if (o_local_value_MetaSpecifiers & o_proxy) == o_proxy
#    define o_local_code_ForwardDeclaration
#else
#    define o_local_code_ForwardDeclaration o_declareT(class o_local_code_concat_namespace_sequence (o_TemplateT), o_global_value_ShortType)
#endif

#    define o_h_begin    \
        o_local_code_ForwardDeclaration \
        o_global_code_Specialize__meta_specifiers \
        o_local_declare_reflection \
        o_local_code_Specialize__proxy_of \
        o_local_code_NamespaceAutoBegin

#    define o_cpp_begin    \
    o_local_code_NamespaceAutoBegin

#else // not template

#if (o_local_value_MetaSpecifiers & o_proxy) == o_proxy
#    define o_local_code_ForwardDeclaration
#else
#    define o_local_code_ForwardDeclaration  o_declare(class o_local_code_concat_namespace_sequence o_global_value_ShortType)
#endif

#    define o_h_begin    \
        o_local_code_ForwardDeclaration \
        o_global_code_Specialize__meta_specifiers \
        o_local_declare_reflection \
        o_local_code_Specialize__proxy_of \
        o_local_code_NamespaceAutoBegin


#   define o_cpp_begin    \
    o_local_code_NamespaceAutoBegin

#endif // template ?

#if defined(o_DeferredMetaElementSetup)

#   define o_local_code_inline_specifier

#   define o_h_end \
        o_global_code_MaxSizeStaticAssert \
        o_local_code_NamespaceAutoEnd \
        namespace phantom {\
        o_local_code_TemplateSpecializationSignature  struct has_deferred_cpp_reflection<o_global_value_QualifiedType> : public phantom::detail::true_ {};\
        }\
        o_local_code_StaticCheck_meta_specifiers_and_type_traits_match

#else

#   define o_local_code_inline_specifier inline

#    if defined(o_TemplateP)
#        define o_h_end \
            o_local_code_NamespaceAutoEnd \
            o_global_code_Specialize__type_of_counter \

    #else
#        define o_h_end        \
            o_global_code_MaxSizeStaticAssert \
            o_local_code_NamespaceAutoEnd        \
            o_global_code_Specialize__type_of_counter \
      o_local_code_StaticCheck_meta_specifiers_and_type_traits_match

#    endif

#endif


#define o_cpp_end    \
    o_local_code_RegisterModules_CPP \
    o_local_code_NamespaceAutoEnd



//  ==================================================================================================
//        INHERITANCE
//  ==================================================================================================


#ifdef o_Super

#    define o_local_code_Attribute_RESERVED_smdataptr

#else

#    if o__bool__use_destroyed_signal && (o_local_value_MetaSpecifiers & o_proxy) != o_proxy
#        ifdef o_DeferredMetaElementSetup
#        else
#        endif
#    else
#    endif
#    define o_local_value_TrackCountBase  1
#    if ((o_local_value_MetaSpecifiers & o_proxy) != o_proxy) && ((o_local_value_MetaSpecifiers & o_pod) != o_pod)
#        define o_local_code_Attribute_RESERVED_smdataptr \
            phantom::state::base_state_machine_data*        PHANTOM_CODEGEN_m_smdataptr;
#    else
#        define o_local_code_Attribute_RESERVED_smdataptr
#    endif

#endif

//  ==================================================================================================
//        TEMPLATE REFLECTION
//  ==================================================================================================

#ifdef o_TemplateP

#    ifndef o_TemplateT
#        define o_TemplateT o_PP_CAT(o_PP_CREATE_DEFAULT_TEMPLATE_TYPES_, o_PP_NARG(o_TemplateP))()
#    elif o_PP_NARG(o_TemplateT) != o_PP_NARG(o_TemplateP)
#        error o_TemplateT and o_TemplateP must have the same number of elements
#    endif


#    define o_local_code_NestedTemplate        o_NESTED_TEMPLATE
#    define o_local_code_TemplateNestedTypedef        o_NESTED_TYPE

#    define o_local_code_TemplateSpecializationSignature    o_global_code_TemplateSignature
#    define o_local_code_TemplateSignature    o_global_code_TemplateSignature
#    define o_local_code_TemplateArgumentList < o_TemplateP >

#    define o_local_code_TemplateSpecializationSignaturePlusCounter    o_global_code_TemplateSignaturePlusCounter

#    define o_local_code_AttributeTypeFinding(type) phantom::typeOf<type>()

#    define o_local_code_RegisterModules_CPP

#else // No template signature
      //            v

#    define o_local_code_TemplateSignature
#    define o_local_code_TemplateSpecializationSignature    template<>
#    define o_local_code_TemplateArgumentList

#    define o_local_code_TemplateSpecializationSignaturePlusCounter    template<int t_RESERVED_counter>

#    define o_local_code_SetTemplateSpecializationInfo

#    define o_local_code_NestedTemplate
#    define o_local_code_TemplateNestedTypedef

#    define o_local_code_AttributeTypeFinding(type) phantom::typeByName(o_PP_QUOTE(type))
#    define o_local_code_Selector_typedef_typename    typedef
#    define o_local_code_AutoReflectionRegistration
#    define o_local_code_RegisterModules_CPP \
        phantom::detail::dynamic_initializer_module_installer_registrer< o_global_value_Type > o_PP_CAT(g_register_module_, o_PP_CAT(o_global_value_ShortType, o_PP_CAT(o_Export,__COUNTER__))) ;

#endif

//  ==================================================================================================
//        CLASS
//  ==================================================================================================

// VALIDITY CHECK

// HEADER

#    define o_local_code_ReflectionHeader  \
        public: \
            template<typename, phantom::extension::detail::default_initializer_id> friend struct phantom::extension::detail::default_initializer_helper; \
            template<typename, phantom::extension::detail::default_installer_id> friend struct phantom::extension::detail::default_installer_helper; \
            template<typename, phantom::extension::detail::default_constructor_id> friend struct phantom::extension::detail::default_constructor_helper; \
            template<typename> friend struct phantom::extension::initializer; \
            template<typename> friend struct phantom::extension::installer; \
            template<typename> friend struct phantom::extension::constructor; \
            template<typename, phantom::uint, phantom::boolean> friend struct smdata_installer_of_helper;\
            template<typename> friend class phantom::state::native::TNativeState;\
            template<typename> friend class phantom::state::native::TNativeTrack;\
            template<typename,typename,typename,typename> friend class phantom::state::native::TNativeTransition;\
            template<typename> friend class phantom::state::native::TNativeStateMachine;\
            template<typename> friend class phantom::reflection::native::TType;\
            template<typename> friend class phantom::reflection::native::TType_;\
            template<typename,int> friend class phantom::reflection::native::TTypeHelper;\
            template<typename> friend class phantom::reflection::native::TConstType;\
            o_local_code_Attribute_RESERVED_smdataptr \
        protected: \
        private:

// FOOTER

#    define o_local_value_SetupStepMask    \


// NESTED STATE MACHINE EXTENSION VARIABLE CODE


//  ==================================================================================================
//        META-OBJECT REFLECTION SKELETON CODE
//  ==================================================================================================


#ifndef o_DeferredMetaElementSetup
#    define o_enclosed_reflection_begin \
    o_local_code_ReflectionHeader \
        o_reflection_custom_begin(o_global_value_Type)

#    define o_enclosed_reflection_end \
        o_reflection_custom_end()\
        protected: 

#else
#    define o_enclosed_reflection_begin \
    o_local_code_ReflectionHeader \
    o_reflection_custom_declare(o_global_value_Type);

#    define o_enclosed_reflection_end \
        protected: 

#    define o_enclosed_reflection_cpp_begin \
        class o_global_value_Type::enclosed_reflection : public phantom::reflection::detail::phantom_base_enclosed_reflection<o_global_value_Type>\
        {\
            enum { PHANTOM_CODEGEN_reflection_counter_value = __COUNTER__ };\
            typedef o_global_value_Type phantom_proxy_generator_reflection_self_type; \
            typedef o_global_value_Type phantom_proxy_generator_reflection_proxy_type;\
            


#    define o_enclosed_reflection_cpp_end \
        };
#endif
//  ==================================================================================================
//        DYNAMIC LIB EXPORT
//  ==================================================================================================

// WINDOWS

#if (o_OPERATING_SYSTEM == o_OPERATING_SYSTEM_WINDOWS)
// o_Export defined in .classdef.h => DLL
#    ifdef o_Export
        // The value contained in o_Export has been defined => EXPORT REQUESTED
#        if (o_Export)
#            define o_export __declspec(dllexport)
#        else // The value contained in o_Export hasn't been defined => IMPORT REQUESTED
#           if defined( __MINGW32__ )
#               define o_export
#           else
#                define o_export __declspec(dllimport)
#           endif
#       endif
#    else
// o_Export not defined in .classdef.h => EXE
#       define o_export
#   endif
#else // OTHER OS
#   define o_export
#endif
