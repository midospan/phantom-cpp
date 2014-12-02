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

#ifndef o_def_macros_detail_h__
#define o_def_macros_detail_h__

#define o_none 0
#define o_no_signal m_PHANTOM_RESERVED_no_signal
#define o_no_range (phantom::reflection::native::null_range())


#define o_members    \
    protected:\
    public: \
    typedef phantom_proxy_generator_reflection_self_type enclosed_reflection_declaration; \
    class enclosed_reflection : public phantom::reflection::detail::phantom_base_enclosed_reflection<phantom_proxy_generator_reflection_self_type>

#define o_statechart_custom(id)    \
    public: \
    typedef phantom_proxy_generator_statechart_self_type_##id enclosed_statechart_declaration; \
    enum { phantom_proxy_generator_track_counter_base_value = __COUNTER__ };\
    template<typename t_PHANTOM_RESERVED_statechart_objectclass> class enclosed_statechart \
    : public phantom::base_statechart<phantom_proxy_generator_statechart_self_type_##id, t_PHANTOM_RESERVED_statechart_objectclass>

#define o_statechart(...)    \
    o_statechart_bis o_PP_LEFT_PAREN __VA_ARGS__ o_PP_RIGHT_PAREN

#define o_statechart_bis(...)    \
    public: \
    typedef phantom_proxy_generator_statechart_self_type enclosed_statechart_declaration; \
    enum { phantom_proxy_generator_track_counter_base_value = __COUNTER__ };\
    template<typename t_PHANTOM_RESERVED_statechart_objectclass> class enclosed_statechart \
    : public phantom::base_statechart<phantom_proxy_generator_statechart_self_type, t_PHANTOM_RESERVED_statechart_objectclass>\
    {\
        __VA_ARGS__\
    };

#define o_nested_begin(_name_, ...)\
class phantom_proxy_____##_name_\
    : public _name_\
    , public phantom_proxy_generator_base_____<_name_, phantom_proxy_____##_name_ >\
{\
    o_members \
    {\
        struct initializer\
        {\
            initializer()\
            {\
                phantom::reflection::Types::savedModifiers = phantom::reflection::Types::currentModifiers;\
                phantom::reflection::Types::savedInstalledClass = phantom::reflection::Types::currentInstalledClass;\
                phantom::reflection::Types::savedInstalledTemplateSpecialization = phantom::reflection::Types::currentInstalledTemplateSpecialization;\
                typedef phantom::reflection::meta_class_type_of<_name_,##__VA_ARGS__>::type meta_type;\
                meta_type* pMetaType = o_dynamic_proxy_new(meta_type)(#_name_);\
                phantom::reflection::Types::currentInstalledClass = pMetaType;\
                phantom::reflection::Types::currentModifiers = 0;\
                phantom::reflection::Types::savedInstalledClass->addNestedType(phantom::reflection::Types::currentInstalledClass);\
                phantom::reflection::Types::currentInstalledTemplateSpecialization = phantom::reflection::Types::currentInstalledClass ? phantom::reflection::Types::currentInstalledClass->getTemplateSpecialization() : nullptr;\
            }\
        } o_nested_begin_;

#define o_nested_end(_name_)\
        struct terminator\
        {\
            terminator()\
            {\
            phantom::reflection::Types::currentInstalledClass = phantom::reflection::Types::savedInstalledClass;\
            phantom::reflection::Types::currentModifiers = phantom::reflection::Types::savedModifiers;\
                phantom::reflection::Types::currentInstalledTemplateSpecialization = phantom::reflection::Types::savedInstalledTemplateSpecialization;\
            };\
        } o_nested_end_;\
    };\
};\
o_NESTED_TYPE phantom_proxy_____##_name_::enclosed_reflection  phantom_proxy_____##_name_##_instance;


#define o_class_moduleNT(_namespaces_,_template_types_,_template_params_,_name_)\
    o_namespace_begin _namespaces_\
    template<typename t_Ty>\
    class phantom_proxy_____##_name_;\
    o_namespace_end _namespaces_\
    namespace phantom {\
    template<o_PP_MIX(_template_types_,_template_params_)>\
struct proxy_of<o_PP_CREATE_QUALIFIED_NAME(_namespaces_,_name_) < o_PP_IDENTITY _template_params_ > >\
{\
    typedef :: o_PP_CREATE_SCOPE _namespaces_::phantom_proxy_____##_name_<o_PP_CREATE_QUALIFIED_NAME(_namespaces_,_name_) < o_PP_IDENTITY _template_params_ > > type;\
};\
    }\
    template<o_PP_MIX(_template_types_,_template_params_)>\
class o_PP_CREATE_SCOPE _namespaces_::phantom_proxy_____##_name_<o_PP_CREATE_QUALIFIED_NAME(_namespaces_,_name_) < o_PP_IDENTITY _template_params_ > >\
    : public o_PP_CREATE_QUALIFIED_NAME(_namespaces_,_name_)< o_PP_IDENTITY _template_params_ >\
{\
protected:\
          typedef o_PP_CREATE_QUALIFIED_NAME(_namespaces_,_name_)< o_PP_IDENTITY _template_params_ > phantom_proxy_generator_reflection_self_type;\
          typedef :: o_PP_CREATE_SCOPE _namespaces_::phantom_proxy_____##_name_< o_PP_CREATE_QUALIFIED_NAME(_namespaces_,_name_) < o_PP_IDENTITY _template_params_ > > phantom_proxy_generator_reflection_proxy_type;\
          typedef phantom_proxy_generator_reflection_self_type phantom_proxy_generator_statechart_self_type;\
          typedef phantom_proxy_generator_reflection_proxy_type phantom_proxy_statechart_proxy_type;\
          typedef phantom_proxy_generator_reflection_self_type phantom_proxy_generator_protected_breaker_base;\
          int                                         m_PHANTOM_RESERVED_no_signal;\
          int                                         PHANTOM_CODEGEN_m_slot_list_of_m_PHANTOM_RESERVED_no_signal;

#define o_class_moduleNCT(_namespaces_,_classes_,_template_types_,_template_params_,_name_)\
    o_namespace_begin _namespaces_\
    template<typename t_Ty>\
class phantom_proxy_____##_name_;\
    o_namespace_end _namespaces_\
    namespace phantom {\
    template<o_PP_MIX(_template_types_,_template_params_)>\
struct proxy_of<o_PP_CREATE_QUALIFIED_NAME_2(_namespaces_,_classes_,_name_) < o_PP_IDENTITY _template_params_ > >\
{\
    typedef :: o_PP_CREATE_SCOPE _namespaces_::phantom_proxy_____##_name_<o_PP_CREATE_QUALIFIED_NAME_2(_namespaces_,_classes_,_name_) < o_PP_IDENTITY _template_params_ > > type;\
};\
    }\
    template<o_PP_MIX(_template_types_,_template_params_)>\
class o_PP_CREATE_SCOPE _namespaces_::phantom_proxy_____##_name_<o_PP_CREATE_QUALIFIED_NAME_2(_namespaces_,_classes_,_name_) < o_PP_IDENTITY _template_params_ > >\
    : public o_PP_CREATE_QUALIFIED_NAME_2(_namespaces_,_classes_,_name_)< o_PP_IDENTITY _template_params_ >\
{\
protected:\
          typedef o_PP_CREATE_QUALIFIED_NAME_2(_namespaces_,_classes_,_name_)< o_PP_IDENTITY _template_params_ > phantom_proxy_generator_reflection_self_type;\
          typedef :: o_PP_CREATE_SCOPE _namespaces_::phantom_proxy_____##_name_< o_PP_CREATE_QUALIFIED_NAME_2(_namespaces_,_classes_,_name_) < o_PP_IDENTITY _template_params_ > > phantom_proxy_generator_reflection_proxy_type;\
          typedef phantom_proxy_generator_reflection_self_type phantom_proxy_generator_statechart_self_type;\
          typedef phantom_proxy_generator_reflection_proxy_type phantom_proxy_statechart_proxy_type;\
          typedef phantom_proxy_generator_reflection_self_type phantom_proxy_generator_protected_breaker_base;\
          int                                         m_PHANTOM_RESERVED_no_signal;\
          int                                         PHANTOM_CODEGEN_m_slot_list_of_m_PHANTOM_RESERVED_no_signal;

#define o_class_moduleN(_namespaces_,_name_)\
    o_namespace_begin _namespaces_\
    template<typename t_Ty>\
    class phantom_proxy_____##_name_;\
    o_namespace_end _namespaces_\
    namespace phantom {\
    template<>\
    struct proxy_of<o_PP_CREATE_QUALIFIED_NAME(_namespaces_,_name_) >\
    {\
        typedef :: o_PP_CREATE_SCOPE _namespaces_::phantom_proxy_____##_name_< o_PP_CREATE_QUALIFIED_NAME(_namespaces_,_name_) > type;\
    };\
    }\
    template<>\
    class o_PP_CREATE_SCOPE _namespaces_::phantom_proxy_____##_name_< o_PP_CREATE_QUALIFIED_NAME(_namespaces_,_name_) > \
    : public o_PP_CREATE_QUALIFIED_NAME(_namespaces_,_name_)\
    {\
    protected:\
        typedef o_PP_CREATE_QUALIFIED_NAME(_namespaces_,_name_) phantom_proxy_generator_reflection_self_type;\
        typedef o_PP_CREATE_SCOPE _namespaces_::phantom_proxy_____##_name_< o_PP_CREATE_QUALIFIED_NAME(_namespaces_,_name_)> phantom_proxy_generator_reflection_proxy_type;\
        typedef phantom_proxy_generator_reflection_self_type phantom_proxy_generator_statechart_self_type;\
        typedef phantom_proxy_generator_reflection_proxy_type phantom_proxy_statechart_proxy_type;\
        typedef phantom_proxy_generator_reflection_self_type phantom_proxy_generator_protected_breaker_base;\
        int                                         m_PHANTOM_RESERVED_no_signal;\
        int                                         PHANTOM_CODEGEN_m_slot_list_of_m_PHANTOM_RESERVED_no_signal;

#define o_class_moduleC(_classes_,_name_)\
    template<typename t_Ty>\
    class phantom_proxy_____##_name_;\
    namespace phantom {\
    template<>\
    struct proxy_of<o_PP_CREATE_QUALIFIED_NAME(_classes_,_name_) >\
    {\
        typedef ::phantom_proxy_____##_name_<o_PP_CREATE_QUALIFIED_NAME(_classes_,_name_) > type;\
    };\
    }\
    template<>\
    class phantom_proxy_____##_name_<o_PP_CREATE_QUALIFIED_NAME(_classes_,_name_) > \
    : public o_PP_CREATE_QUALIFIED_NAME(_namespaces_,_name_)\
    {\
    protected:\
    typedef o_PP_CREATE_QUALIFIED_NAME(_namespaces_,_name_) phantom_proxy_generator_reflection_self_type;\
    typedef phantom_proxy_____##_name_< o_PP_CREATE_QUALIFIED_NAME(_classes_,_name_) > phantom_proxy_generator_reflection_proxy_type;\
    typedef phantom_proxy_generator_reflection_self_type phantom_proxy_generator_statechart_self_type;\
    typedef phantom_proxy_generator_reflection_proxy_type phantom_proxy_statechart_proxy_type;\
    typedef phantom_proxy_generator_reflection_self_type phantom_proxy_generator_protected_breaker_base;\
    int                                         m_PHANTOM_RESERVED_no_signal;\
    int                                         PHANTOM_CODEGEN_m_slot_list_of_m_PHANTOM_RESERVED_no_signal;

#define o_class_moduleNC(_namespaces_,_classes_,_name_)\
    o_namespace_begin _namespaces_\
    template<typename t_Ty>\
    class phantom_proxy_____##_name_;\
    o_namespace_end _namespaces_\
    namespace phantom {\
    template<>\
    struct proxy_of<o_PP_CREATE_QUALIFIED_NAME_2(_namespaces_,_classes_,_name_) >\
    {\
        typedef :: o_PP_CREATE_SCOPE _namespaces_::phantom_proxy_____##_name_< o_PP_CREATE_QUALIFIED_NAME_2(_namespaces_,_classes_,_name_) > type;\
    };\
    }\
    template<>\
    class o_PP_CREATE_SCOPE _namespaces_::phantom_proxy_____##_name_< o_PP_CREATE_QUALIFIED_NAME_2(_namespaces_,_classes_,_name_) > \
    : public o_PP_CREATE_QUALIFIED_NAME_2(_namespaces_,_classes_,_name_) \
    {\
    protected:\
    typedef o_PP_CREATE_QUALIFIED_NAME_2(_namespaces_,_classes_,_name_) phantom_proxy_generator_reflection_self_type;\
    typedef :: o_PP_CREATE_SCOPE _namespaces_::phantom_proxy_____##_name_< o_PP_CREATE_QUALIFIED_NAME_2(_namespaces_,_classes_,_name_) > phantom_proxy_generator_reflection_proxy_type;\
    typedef phantom_proxy_generator_reflection_self_type phantom_proxy_generator_statechart_self_type;\
    typedef phantom_proxy_generator_reflection_proxy_type phantom_proxy_statechart_proxy_type;\
    typedef phantom_proxy_generator_reflection_self_type phantom_proxy_generator_protected_breaker_base;\
    int                                         m_PHANTOM_RESERVED_no_signal;\
    int                                         PHANTOM_CODEGEN_m_slot_list_of_m_PHANTOM_RESERVED_no_signal;

#define o_class_moduleT(_template_types_,_template_params_,_name_)\
    template<typename t_Ty>\
    class phantom_proxy_____##_name_;\
    namespace phantom {\
    template<o_PP_MIX(_template_types_,_template_params_)>\
    struct proxy_of< ::_name_< o_PP_IDENTITY _template_params_ > >\
    {\
        typedef ::phantom_proxy_____##_name_< ::_name_ < o_PP_IDENTITY _template_params_ >  > type;\
    };\
    }\
    template<o_PP_MIX(_template_types_,_template_params_)>\
    class phantom_proxy_____##_name_< ::_name_ < o_PP_IDENTITY _template_params_ > > \
    : public ::_name_ < o_PP_IDENTITY _template_params_ >\
    {\
        protected:\
        typedef ::_name_ < o_PP_IDENTITY _template_params_ > phantom_proxy_generator_reflection_self_type;\
        typedef ::phantom_proxy_____##_name_< ::_name_ < o_PP_IDENTITY _template_params_ > > phantom_proxy_generator_reflection_proxy_type;\
        typedef phantom_proxy_generator_reflection_self_type phantom_proxy_generator_statechart_self_type;\
        typedef phantom_proxy_generator_reflection_proxy_type phantom_proxy_statechart_proxy_type;\
        typedef phantom_proxy_generator_reflection_self_type phantom_proxy_generator_protected_breaker_base;\
        int                                         m_PHANTOM_RESERVED_no_signal;\
        int                                         PHANTOM_CODEGEN_m_slot_list_of_m_PHANTOM_RESERVED_no_signal;

#define o_class_module(_name_)\
    template<typename t_Ty>\
    class phantom_proxy_____##_name_;\
    namespace phantom {\
    template<>\
    struct proxy_of< ::_name_>\
    {\
        typedef ::phantom_proxy_____##_name_< ::_name_> type;\
    };\
    }\
    template<>\
    class phantom_proxy_____##_name_< ::_name_ > \
    : public ::_name_\
        {\
        protected:\
        typedef ::_name_ phantom_proxy_generator_reflection_self_type;\
        typedef phantom_proxy_____##_name_< ::_name_ > phantom_proxy_generator_reflection_proxy_type;\
        typedef phantom_proxy_generator_reflection_self_type phantom_proxy_generator_statechart_self_type;\
        typedef phantom_proxy_generator_reflection_proxy_type phantom_proxy_statechart_proxy_type;\
        typedef phantom_proxy_generator_reflection_self_type phantom_proxy_generator_protected_breaker_base;\
        int                                         m_PHANTOM_RESERVED_no_signal;\
        int                                         PHANTOM_CODEGEN_m_slot_list_of_m_PHANTOM_RESERVED_no_signal;


#define o_union_moduleNT(_namespaces_,_template_types_,_template_params_,_name_)\
    o_namespace_begin _namespaces_\
    template<typename t_Ty>\
class phantom_proxy_____##_name_;\
    o_namespace_end _namespaces_\
    namespace phantom {\
    template<o_PP_MIX(_template_types_,_template_params_)>\
struct proxy_of<o_PP_CREATE_QUALIFIED_NAME(_namespaces_,_name_) < o_PP_IDENTITY _template_params_ > >\
{\
    typedef :: o_PP_CREATE_SCOPE _namespaces_::phantom_proxy_____##_name_<o_PP_CREATE_QUALIFIED_NAME(_namespaces_,_name_) < o_PP_IDENTITY _template_params_ > > type;\
};\
    }\
    template<o_PP_MIX(_template_types_,_template_params_)>\
class o_PP_CREATE_SCOPE _namespaces_::phantom_proxy_____##_name_<o_PP_CREATE_QUALIFIED_NAME(_namespaces_,_name_) < o_PP_IDENTITY _template_params_ > >\
{\
protected:\
    typedef o_PP_CREATE_QUALIFIED_NAME(_namespaces_,_name_)< o_PP_IDENTITY _template_params_ > phantom_proxy_generator_reflection_self_type;\
    typedef phantom::empty_struct phantom_proxy_generator_protected_breaker_base;\
    typedef phantom_proxy_generator_reflection_self_type phantom_proxy_generator_reflection_proxy_type;


#define o_union_moduleNCT(_namespaces_,_classes_,_template_types_,_template_params_,_name_)\
    o_namespace_begin _namespaces_\
    template<typename t_Ty>\
class phantom_proxy_____##_name_;\
    o_namespace_end _namespaces_\
    namespace phantom {\
    template<o_PP_MIX(_template_types_,_template_params_)>\
struct proxy_of<o_PP_CREATE_QUALIFIED_NAME_2(_namespaces_,_classes_,_name_) < o_PP_IDENTITY _template_params_ > >\
{\
    typedef :: o_PP_CREATE_SCOPE _namespaces_::phantom_proxy_____##_name_<o_PP_CREATE_QUALIFIED_NAME_2(_namespaces_,_classes_,_name_) < o_PP_IDENTITY _template_params_ > > type;\
};\
    }\
    template<o_PP_MIX(_template_types_,_template_params_)>\
class o_PP_CREATE_SCOPE _namespaces_::phantom_proxy_____##_name_<o_PP_CREATE_QUALIFIED_NAME_2(_namespaces_,_classes_,_name_) < o_PP_IDENTITY _template_params_ > >\
    {\
    protected:\
    typedef o_PP_CREATE_QUALIFIED_NAME_2(_namespaces_,_classes_,_name_)< o_PP_IDENTITY _template_params_ > phantom_proxy_generator_reflection_self_type;\
    typedef phantom::empty_struct phantom_proxy_generator_protected_breaker_base;\
    typedef phantom_proxy_generator_reflection_self_type phantom_proxy_generator_reflection_proxy_type;

#define o_union_moduleN(_namespaces_,_name_)\
    o_namespace_begin _namespaces_\
    template<typename t_Ty>\
class phantom_proxy_____##_name_;\
    o_namespace_end _namespaces_\
    namespace phantom {\
    template<>\
struct proxy_of<o_PP_CREATE_QUALIFIED_NAME(_namespaces_,_name_) >\
    {\
    typedef :: o_PP_CREATE_SCOPE _namespaces_::phantom_proxy_____##_name_< o_PP_CREATE_QUALIFIED_NAME(_namespaces_,_name_) > type;\
    };\
    }\
    template<>\
class o_PP_CREATE_SCOPE _namespaces_::phantom_proxy_____##_name_< o_PP_CREATE_QUALIFIED_NAME(_namespaces_,_name_) > \
    {\
    protected:\
    typedef o_PP_CREATE_QUALIFIED_NAME(_namespaces_,_name_) phantom_proxy_generator_reflection_self_type;\
    typedef phantom::empty_struct phantom_proxy_generator_protected_breaker_base;\
    typedef phantom_proxy_generator_reflection_self_type phantom_proxy_generator_reflection_proxy_type;

#define o_union_moduleC(_classes_,_name_)\
    template<typename t_Ty>\
class phantom_proxy_____##_name_;\
    namespace phantom {\
    template<>\
struct proxy_of<o_PP_CREATE_QUALIFIED_NAME(_classes_,_name_) >\
    {\
    typedef ::phantom_proxy_____##_name_< o_PP_CREATE_QUALIFIED_NAME(_classes_,_name_) > type;\
    };\
    }\
    template<>\
class phantom_proxy_____##_name_< o_PP_CREATE_QUALIFIED_NAME(_classes_,_name_) > \
{\
    protected:\
    typedef o_PP_CREATE_QUALIFIED_NAME(_classes_,_name_) phantom_proxy_generator_reflection_self_type;\
    typedef phantom::empty_struct phantom_proxy_generator_protected_breaker_base;\
    typedef phantom_proxy_generator_reflection_self_type phantom_proxy_generator_reflection_proxy_type;

#define o_union_moduleNC(_namespaces_,_classes_,_name_)\
    o_namespace_begin _namespaces_\
    template<typename t_Ty>\
class phantom_proxy_____##_name_;\
    o_namespace_end _namespaces_\
    namespace phantom {\
    template<>\
struct proxy_of<o_PP_CREATE_QUALIFIED_NAME_2(_namespaces_,_classes_,_name_) >\
    {\
    typedef :: o_PP_CREATE_SCOPE _namespaces_::phantom_proxy_____##_name_< o_PP_CREATE_QUALIFIED_NAME_2(_namespaces_,_classes_,_name_) > type;\
    };\
    }\
    template<>\
class o_PP_CREATE_SCOPE _namespaces_::phantom_proxy_____##_name_< o_PP_CREATE_QUALIFIED_NAME_2(_namespaces_,_classes_,_name_) > \
{\
protected:\
    typedef o_PP_CREATE_QUALIFIED_NAME_2(_namespaces_,_classes_,_name_) phantom_proxy_generator_reflection_self_type;\
    typedef phantom::empty_struct phantom_proxy_generator_protected_breaker_base;\
    typedef phantom_proxy_generator_reflection_self_type phantom_proxy_generator_reflection_proxy_type;

#define o_union_moduleT(_template_types_,_template_params_,_name_)\
    template<typename t_Ty>\
class phantom_proxy_____##_name_;\
    namespace phantom {\
    template<o_PP_MIX(_template_types_,_template_params_)>\
struct proxy_of< ::_name_< o_PP_IDENTITY _template_params_ > >\
    {\
    typedef ::phantom_proxy_____##_name_< ::_name_ < o_PP_IDENTITY _template_params_ >  > type;\
    };\
    }\
    template<o_PP_MIX(_template_types_,_template_params_)>\
class phantom_proxy_____##_name_< ::_name_ < o_PP_IDENTITY _template_params_ > > \
    {\
    protected:\
    typedef ::_name_ < o_PP_IDENTITY _template_params_ > phantom_proxy_generator_reflection_self_type;\
    typedef phantom::empty_struct phantom_proxy_generator_protected_breaker_base;\
    typedef phantom_proxy_generator_reflection_self_type phantom_proxy_generator_reflection_proxy_type;

#define o_union_module(_name_)\
    template<typename t_Ty>\
class phantom_proxy_____##_name_;\
    namespace phantom {\
    template<>\
struct proxy_of< ::_name_>\
    {\
    typedef ::phantom_proxy_____##_name_< ::_name_> type;\
    };\
    }\
    template<>\
class phantom_proxy_____##_name_< ::_name_ > \
    {\
    protected:\
    typedef ::_name_ phantom_proxy_generator_reflection_self_type;\
    typedef phantom::empty_struct phantom_proxy_generator_protected_breaker_base;\
    typedef phantom_proxy_generator_reflection_self_type phantom_proxy_generator_reflection_proxy_type;


#if o_HAS_COMPILE_TIME_TYPEID

#define o_reflection_specialize_typeInfosOf(_name_)
#define o_reflection_specialize_typeInfosOfN(_namespaces_, _name_)
#define o_reflection_specialize_typeInfosOfC(_classes_, _name_)
#define o_reflection_specialize_typeInfosOfNC(_namespaces_, _classes_, _name_) 
#define o_reflection_specialize_typeInfosOfTI_2(_template_args_, _name_) 
#define o_reflection_specialize_typeInfosOfTI_3(_template_types_, _template_args_, _name_) 
#define o_reflection_specialize_typeInfosOfNTI_3(_namespaces_, _template_args_, _name_)
#define o_reflection_specialize_typeInfosOfNTI_4(_namespaces_, _template_types_, _template_args_, _name_)
#define o_reflection_specialize_typeInfosOfCTI_3(_classes_, _template_args_, _name_)
#define o_reflection_specialize_typeInfosOfCTI_4(_classes_, _template_types_, _template_args_, _name_)
#define o_reflection_specialize_typeInfosOfNCTI_4(_namespaces_, _classes_, _template_args_, _name_) 
#define o_reflection_specialize_typeInfosOfNCTI_5(_namespaces_, _classes_, _template_types_, _template_args_, _name_)

#else

#define o_reflection_specialize_typeInfosOf(_name_)    \
    o_namespace_begin(phantom, reflection, detail)            \
    template<> o_export_typeInfosOf const type_infos& typeInfosOf<_name_>()\
    {                                                   \
        static type_infos ti("", #_name_, "");\
        return ti;\
    };                                                         \
    o_namespace_end(phantom, reflection, detail)

#define o_reflection_specialize_typeInfosOfN(_namespaces_, _name_)\
    o_namespace_begin(phantom, reflection, detail)\
    template<> o_export_typeInfosOf const type_infos& typeInfosOf<o_PP_CREATE_QUALIFIED_NAME(_namespaces_,_name_)>()\
    {\
        static type_infos ti(o_PP_QUOTE_SCOPE(_namespaces_),#_name_, "");\
        return ti;\
    };\
    o_namespace_end(phantom, reflection, detail)

#define o_reflection_specialize_typeInfosOfC(_classes_, _name_)\
    o_namespace_begin(phantom, reflection, detail)\
    template<> o_export_typeInfosOf const type_infos& typeInfosOf<o_PP_CREATE_QUALIFIED_NAME(_classes_,_name_)>()\
    {\
    static type_infos ti(o_PP_QUOTE_SCOPE(_classes_), #_name_, "");\
    return ti;\
    };\
    o_namespace_end(phantom, reflection, detail)

#define o_reflection_specialize_typeInfosOfNC(_namespaces_, _classes_, _name_)    \
    o_namespace_begin(phantom, reflection, detail)\
    template<> o_export_typeInfosOf const type_infos& typeInfosOf<o_PP_CREATE_QUALIFIED_NAME_2(_namespaces_,_classes_, _name_)>()\
    {\
    static type_infos ti(o_PP_QUOTE_SCOPE(_namespaces_) "::" o_PP_QUOTE_SCOPE(_classes_), #_name_, "");\
    return ti;\
    };\
    o_namespace_end(phantom, reflection, detail)

#define o_reflection_specialize_typeInfosOfTI_2(_template_args_, _name_) \
    o_namespace_begin(phantom, reflection, detail) \
    template<> o_export_typeInfosOf const type_infos& typeInfosOf<::_name_< o_PP_IDENTITY _template_args_ > >()\
    { \
    static type_infos ti("", #_name_, phantom::reflection::type_decoration_extractor<void _template_args_>::decoration());\
    return ti;\
    };\
    o_namespace_end(phantom, reflection, detail)

#define o_reflection_specialize_typeInfosOfTI_3(_template_types_, _template_args_, _name_) \
    o_namespace_begin(phantom, reflection, detail) \
    namespace ______tde {  \
    namespace _name_ { o_create_type_decoration_extractor(_template_types_); }\
    }\
    template<> o_export_typeInfosOf const type_infos& typeInfosOf<::_name_< o_PP_IDENTITY _template_args_ > >()\
    { \
    static type_infos ti("", #_name_, ______tde::_name_::type_decoration_extractor<o_PP_IDENTITY _template_args_>::decoration());\
    return ti;\
    };\
    o_namespace_end(phantom, reflection, detail)

#define o_reflection_specialize_typeInfosOfNTI_3(_namespaces_, _template_args_, _name_) \
    o_namespace_begin(phantom, reflection, detail) \
    template<> o_export_typeInfosOf const type_infos& typeInfosOf<o_PP_CREATE_QUALIFIED_NAME(_namespaces_,_name_)< o_PP_IDENTITY _template_args_ > >()\
    { \
    static type_infos ti(o_PP_QUOTE_SCOPE(_namespaces_), #_name_, phantom::reflection::type_decoration_extractor<void _template_args_>::decoration());\
    return ti;\
    };\
    o_namespace_end(phantom, reflection, detail)

#define o_reflection_specialize_typeInfosOfNTI_4(_namespaces_, _template_types_, _template_args_, _name_) \
    o_namespace_begin(phantom, reflection, detail) \
    namespace ______tde { o_namespace_begin _namespaces_ \
    namespace _name_ { o_create_type_decoration_extractor(_template_types_); }\
    o_namespace_end _namespaces_ }\
    template<> o_export_typeInfosOf const type_infos& typeInfosOf<o_PP_CREATE_QUALIFIED_NAME(_namespaces_,_name_)< o_PP_IDENTITY _template_args_ > >()\
    { \
        static type_infos ti(o_PP_QUOTE_SCOPE(_namespaces_), #_name_, ______tde :: o_PP_CREATE_SCOPE _namespaces_ :: _name_ ::type_decoration_extractor<o_PP_IDENTITY _template_args_>::decoration());\
        return ti;\
    };\
    o_namespace_end(phantom, reflection, detail)

#define o_reflection_specialize_typeInfosOfCTI_3(_classes_, _template_args_, _name_) \
    o_namespace_begin(phantom, reflection, detail) \
    template<> o_export_typeInfosOf const type_infos& typeInfosOf<o_PP_CREATE_QUALIFIED_NAME(_classes_,_name_)< o_PP_IDENTITY _template_args_ > >()\
    { \
    static type_infos ti(o_PP_QUOTE_SCOPE(_classes_), #_name_, phantom::reflection::type_decoration_extractor<void _template_args_>::decoration());\
    return ti;\
    };\
    o_namespace_end(phantom, reflection, detail)

#define o_reflection_specialize_typeInfosOfCTI_4(_classes_, _template_types_, _template_args_, _name_) \
    o_namespace_begin(phantom, reflection, detail) \
    namespace ______tde { o_namespace_begin _classes_ \
    namespace _name_ { o_create_type_decoration_extractor(_template_types_); }\
    o_namespace_end _classes_ }\
    template<> o_export_typeInfosOf const type_infos& typeInfosOf<o_PP_CREATE_QUALIFIED_NAME(_classes_,_name_)< o_PP_IDENTITY _template_args_ > >()\
    { \
        o_create_type_decoration_extractor(_template_types_);\
        static type_infos ti(o_PP_QUOTE_SCOPE(_classes_), #_name_, ______tde :: o_PP_CREATE_SCOPE _classes_ :: _name_ ::type_decoration_extractor<o_PP_IDENTITY _template_args_>::decoration());\
        return ti;\
    };\
    o_namespace_end(phantom, reflection, detail)

#define o_reflection_specialize_typeInfosOfNCTI_4(_namespaces_, _classes_, _template_args_, _name_) \
    o_namespace_begin(phantom, reflection, detail) \
    template<> o_export_typeInfosOf const type_infos& typeInfosOf<o_PP_CREATE_QUALIFIED_NAME_2(_namespaces_,_classes_,_name_)< o_PP_IDENTITY _template_args_ > >()\
    { \
    static type_infos ti(o_PP_QUOTE_SCOPE(_namespaces_),#_name_, phantom::reflection::type_decoration_extractor<void _template_args_>::decoration());\
    return ti;\
    };\
    o_namespace_end(phantom, reflection, detail)

#define o_reflection_specialize_typeInfosOfNCTI_5(_namespaces_, _classes_, _template_types_, _template_args_, _name_) \
    o_namespace_begin(phantom, reflection, detail) \
    namespace ______tde { o_namespace_begin _namespaces_ o_namespace_begin _classes_ \
    namespace _name_ { o_create_type_decoration_extractor(_template_types_); }\
    o_namespace_end _namespaces_ o_namespace_end _classes_ }\
    template<> o_export_typeInfosOf const type_infos& typeInfosOf<o_PP_CREATE_QUALIFIED_NAME_2(_namespaces_,_classes_,_name_)< o_PP_IDENTITY _template_args_ > >()\
    { \
    static type_infos ti(o_PP_QUOTE_SCOPE(_namespaces_) "::" o_PP_QUOTE_SCOPE(_classes_), #_name_, ______tde :: o_PP_CREATE_SCOPE _namespaces_ :: o_PP_CREATE_SCOPE _classes_ :: _name_ :: type_decoration_extractor<o_PP_IDENTITY _template_args_>::decoration());\
    return ti;\
    };\
    o_namespace_end(phantom, reflection, detail)


#endif // o_HAS_COMPILE_TIME_TYPEID

// ---------------


#define o_reflection_specialize_type_infos_of(_name_)    \
    o_namespace_begin(phantom, reflection)            \
    template<> struct type_infos_of<_name_>\
    {                                                   \
    inline static const type_infos& object() {\
        static type_infos ti("", #_name_, "");\
        return ti;\
    }\
    };                                                         \
    o_namespace_end(phantom, reflection)

#define o_reflection_specialize_type_infos_ofN(_namespaces_, _name_)\
    o_namespace_begin(phantom, reflection)\
    template<> struct type_infos_of<o_PP_CREATE_QUALIFIED_NAME(_namespaces_,_name_)>\
    {\
    inline static const type_infos& object() {\
        static type_infos ti(o_PP_QUOTE_SCOPE(_namespaces_),#_name_, "");\
        return ti;\
    }\
    };\
    o_namespace_end(phantom, reflection)

#define o_reflection_specialize_type_infos_ofC(_classes_, _name_)\
    o_namespace_begin(phantom, reflection)\
    template<> struct type_infos_of<o_PP_CREATE_QUALIFIED_NAME(_classes_,_name_)>\
    {\
    inline static const type_infos& object() {\
        static type_infos ti(o_PP_QUOTE_SCOPE(_classes_), #_name_, "");\
        return ti;\
    }\
    };\
    o_namespace_end(phantom, reflection)

#define o_reflection_specialize_type_infos_ofNC(_namespaces_, _classes_, _name_)    \
    o_namespace_begin(phantom, reflection)\
    template<> struct type_infos_of<o_PP_CREATE_QUALIFIED_NAME_2(_namespaces_,_classes_, _name_)>\
    {\
    inline static const type_infos& object() {\
        static type_infos ti(o_PP_QUOTE_SCOPE(_namespaces_) "::" o_PP_QUOTE_SCOPE(_classes_), #_name_, "");\
        return ti;\
    }\
    };\
    o_namespace_end(phantom, reflection)

#define o_reflection_specialize_type_infos_ofT(_template_types_, _template_params_, _name_) \
    o_namespace_begin(phantom, reflection) \
    template<o_PP_MIX(_template_types_, _template_params_)> \
    struct type_infos_of<::_name_< o_PP_IDENTITY _template_params_ > >\
    { \
    o_create_type_decoration_extractor(_template_types_);\
    inline static const type_infos& object() {\
        static type_infos ti("", #_name_, type_decoration_extractor<o_PP_IDENTITY _template_params_>::decoration());\
        return ti;\
    }\
    };\
    o_namespace_end(phantom, reflection)

#define o_reflection_specialize_type_infos_ofNT(_namespaces_, _template_types_, _template_params_, _name_) \
    o_namespace_begin(phantom, reflection) \
    template<o_PP_MIX(_template_types_, _template_params_)>\
    struct type_infos_of<o_PP_CREATE_QUALIFIED_NAME(_namespaces_,_name_)< o_PP_IDENTITY _template_params_ > >\
    { \
    o_create_type_decoration_extractor(_template_types_);\
    inline static const type_infos& object() {\
        static type_infos ti(o_PP_QUOTE_SCOPE(_namespaces_), #_name_, type_decoration_extractor<o_PP_IDENTITY _template_params_>::decoration());\
        return ti;\
    }\
    };\
    o_namespace_end(phantom, reflection)

#define o_reflection_specialize_type_infos_ofCT(_classes_, _template_types_, _template_params_, _name_) \
    o_namespace_begin(phantom, reflection) \
    template<o_PP_MIX(_template_types_, _template_params_)>\
    struct type_infos_of<o_PP_CREATE_QUALIFIED_NAME(_classes_,_name_)< o_PP_IDENTITY _template_params_ > >\
    { \
    o_create_type_decoration_extractor(_template_types_);\
    inline static const type_infos& object() {\
        static type_infos ti(o_PP_QUOTE_SCOPE(_classes_), #_name_, type_decoration_extractor<o_PP_IDENTITY _template_params_>::decoration());\
        return ti;\
    }\
    };\
    o_namespace_end(phantom, reflection)

#define o_reflection_specialize_type_infos_ofNCT(_namespaces_, _classes_, _template_types_, _template_params_, _name_) \
    o_namespace_begin(phantom, reflection) \
    template<o_PP_MIX(_template_types_, _template_params_)> \
    struct type_infos_of<o_PP_CREATE_QUALIFIED_NAME_2(_namespaces_,_classes_,_name_)< o_PP_IDENTITY _template_params_ > >\
    { \
    o_create_type_decoration_extractor(_template_types_);\
    inline static const type_infos& object() {\
        static type_infos ti(o_PP_QUOTE_SCOPE(_namespaces_) "::" o_PP_QUOTE_SCOPE(_classes_), #_name_, type_decoration_extractor<o_PP_IDENTITY _template_params_>::decoration());\
        return ti;\
    }\
    };\
    o_namespace_end(phantom, reflection)





#define o_reflection_specialize_type_of(_name_) \
    o_namespace_begin(phantom, reflection) \
    template<>  \
struct type_of<_name_> \
    : public detail::type_of_defined< ::_name_> {};\
    o_namespace_end(phantom, reflection)

#define o_reflection_specialize_type_ofN(_namespaces_, _name_) \
    o_namespace_begin(phantom, reflection) \
    template<>  \
struct type_of<o_PP_CREATE_QUALIFIED_NAME(_namespaces_,_name_)> \
    : public detail::type_of_defined<o_PP_CREATE_QUALIFIED_NAME(_namespaces_,_name_)> {};\
    o_namespace_end(phantom, reflection)

#define o_reflection_specialize_type_ofT(_template_types_, _template_params_, _name_) \
    o_namespace_begin(phantom, reflection) \
    template<o_PP_MIX(_template_types_, _template_params_)>  \
struct type_of< ::_name_< o_PP_IDENTITY _template_params_ > > \
    : public detail::type_of_defined< ::_name_< o_PP_IDENTITY _template_params_ >> {};\
    o_namespace_end(phantom, reflection)

#define o_reflection_specialize_type_ofNT(_namespaces_, _template_types_, _template_params_, _name_) \
    o_namespace_begin(phantom, reflection) \
    template<o_PP_MIX(_template_types_, _template_params_)>  \
struct type_of<o_PP_CREATE_QUALIFIED_NAME(_namespaces_,_name_) < o_PP_IDENTITY _template_params_ > > \
    : public detail::type_of_defined<o_PP_CREATE_QUALIFIED_NAME(_namespaces_,_name_)< o_PP_IDENTITY _template_params_ > > {};\
    o_namespace_end(phantom, reflection)

#define o_reflection_specialize_type_ofNCT(_namespaces_, _classes_, _template_types_, _template_params_, _name_) \
    o_namespace_begin(phantom, reflection) \
    template<o_PP_MIX(_template_types_, _template_params_)>  \
struct type_of<o_PP_CREATE_QUALIFIED_NAME_2(_namespaces_, _classes_,_name_) < o_PP_IDENTITY _template_params_ > > \
    : public detail::type_of_defined<o_PP_CREATE_QUALIFIED_NAME_2(_namespaces_, _classes_,_name_)< o_PP_IDENTITY _template_params_ > > {};\
    o_namespace_end(phantom, reflection)

#define o_reflection_specialize_type_ofNC(_namespaces_, _classes_, _name_) \
    o_namespace_begin(phantom, reflection) \
    template<>  \
struct type_of<o_PP_CREATE_QUALIFIED_NAME_2(_namespaces_,_classes_, _name_)> \
    : public detail::type_of_defined<o_PP_CREATE_QUALIFIED_NAME_2(_namespaces_, _classes_,_name_)> {};\
    o_namespace_end(phantom, reflection)

#define o_reflection_specialize_type_ofC(_classes_, _name_) \
    o_namespace_begin(phantom, reflection) \
    template<>  \
struct type_of<o_PP_CREATE_QUALIFIED_NAME(_classes_,_name_)> \
    : public detail::type_of_defined<o_PP_CREATE_QUALIFIED_NAME(_classes_,_name_)> {};\
    o_namespace_end(phantom, reflection)

#define o_reflection_specialize_type_ofCT(_classes_, _template_types_, _template_params_, _name_) \
    o_namespace_begin(phantom, reflection) \
    template<o_PP_MIX(_template_types_, _template_params_)>  \
struct type_of<o_PP_CREATE_QUALIFIED_NAME(_classes_,_name_)< o_PP_IDENTITY _template_params_ > > \
    : public detail::type_of_defined<o_PP_CREATE_QUALIFIED_NAME(_classes_,_name_)< o_PP_IDENTITY _template_params_ > {};\
    o_namespace_end(phantom, reflection)




#define o_reflection_in_cpp_deferred_setupN(_namespaces_,_name)\
    o_reflection_specialize_type_ofN(_namespaces_,_name)

#define o_class_declare(_name_) \
    o_declare o_PP_LEFT_PAREN class, _name_ o_PP_RIGHT_PAREN

#define o_class_declareN(_namespaces_, _name_) \
    o_declare o_PP_LEFT_PAREN class, o_PP_IDENTITY _namespaces_, _name_ o_PP_RIGHT_PAREN




#define o_reflection_specialize_template_specialization_adderT(_template_types_, _template_params_, _name_)\
    o_namespace_begin(phantom, reflection, detail) \
    template<o_PP_MIX(_template_types_,_template_params_)> \
struct template_specialization_adder< ::_name_ < o_PP_IDENTITY _template_params_> >\
    {\
    static void apply(phantom::reflection::ClassType* a_pClassType)\
        {\
        phantom::reflection::Template* pTemplate = a_pClassType->getNamespace()->findOrCreateTemplate(a_pClassType->getName());\
        phantom::reflection::TemplateSpecialization* pTemplateSpecialization = o_new(phantom::reflection::TemplateSpecialization)(pTemplate);\
        o_reflection_add_template_parameter_reflection(_template_types_,_template_params_) \
        a_pClassType->setTemplateSpecialization(pTemplateSpecialization);\
        }\
    };\
    o_namespace_end(phantom, reflection, detail)

#define o_reflection_specialize_template_specialization_adderNT(_namespaces_,_template_types_, _template_params_, _name_)\
    o_namespace_begin(phantom, reflection, detail) \
    template<o_PP_MIX(_template_types_,_template_params_)> \
struct template_specialization_adder<o_PP_CREATE_QUALIFIED_NAME(_namespaces_,_name_) < o_PP_IDENTITY _template_params_ > >\
{\
    static void apply(phantom::reflection::ClassType* a_pClassType)\
{\
    phantom::reflection::Template* pTemplate = a_pClassType->getNamespace()->findOrCreateTemplate(a_pClassType->getName());\
    phantom::reflection::TemplateSpecialization* pTemplateSpecialization = o_new(phantom::reflection::TemplateSpecialization)(pTemplate);\
    o_reflection_add_template_parameter_reflection(_template_types_,_template_params_) \
    a_pClassType->setTemplateSpecialization(pTemplateSpecialization);\
}\
};\
    o_namespace_end(phantom, reflection, detail)


#define o_reflection_specialize_template_specialization_adderCT(_classes_,_template_types_, _template_params_, _name_)\
    o_namespace_begin(phantom, reflection, detail) \
    template<o_PP_MIX(_template_types_,_template_params_)> \
struct template_specialization_adder<o_PP_CREATE_QUALIFIED_NAME(_classes_,_name_) < o_PP_IDENTITY _template_params_ > >\
{\
    static void apply(phantom::reflection::ClassType* a_pClassType)\
{\
    phantom::reflection::Template* pTemplate = a_pClassType->getNamespace()->findOrCreateTemplate(a_pClassType->getName());\
    phantom::reflection::TemplateSpecialization* pTemplateSpecialization = o_new(phantom::reflection::TemplateSpecialization)(pTemplate);\
    o_reflection_add_template_parameter_reflection(_template_types_,_template_params_) \
    a_pClassType->setTemplateSpecialization(pTemplateSpecialization);\
}\
};\
    o_namespace_end(phantom, reflection, detail)

#define o_reflection_specialize_template_specialization_adderNCT(_namespaces_,_classes_,_template_types_, _template_params_, _name_)\
    o_namespace_begin(phantom, reflection, detail) \
    template<o_PP_MIX(_template_types_,_template_params_)> \
struct template_specialization_adder<o_PP_CREATE_QUALIFIED_NAME_2(_namespaces_,_classes_,_name_) < o_PP_IDENTITY _template_params_ > >\
{\
    static void apply(phantom::reflection::ClassType* a_pClassType)\
{\
    phantom::reflection::Template* pTemplate = a_pClassType->getNamespace()->findOrCreateTemplate(a_pClassType->getName());\
    phantom::reflection::TemplateSpecialization* pTemplateSpecialization = o_new(phantom::reflection::TemplateSpecialization)(pTemplate);\
    o_reflection_add_template_parameter_reflection(_template_types_,_template_params_) \
    a_pClassType->setTemplateSpecialization(pTemplateSpecialization);\
}\
};\
    o_namespace_end(phantom, reflection, detail)


#if o_COMPILER == o_COMPILER_VISUAL_STUDIO /// VISUAL STUDIO

#define o_reflection_add_template_parameter_reflection(l0,l1) \
    o_PP_CAT o_PP_LEFT_PAREN o_reflection_add_template_parameter_reflection_,o_PP_NARG_FUNC()l0 o_PP_RIGHT_PAREN (l0,l1)

#define o_reflection_add_template_parameter_reflection_1(l0,l1) \
    pTemplateSpecialization->setArgument(o_PP_QUOTE(o_PP_CAT(o_PP_ARG_0,l1)), o_PP_CAT(template_signature_parameter_,o_PP_CAT(o_PP_ARG_0,l0))< o_PP_CAT(o_PP_ARG_0,l1) >::object()); \

#define o_reflection_add_template_parameter_reflection_2(l0,l1) \
    o_reflection_add_template_parameter_reflection_1(l0,l1) \
    pTemplateSpecialization->setArgument(o_PP_QUOTE(o_PP_CAT(o_PP_ARG_1,l1)), o_PP_CAT(template_signature_parameter_,o_PP_CAT(o_PP_ARG_1,l0))< o_PP_CAT(o_PP_ARG_1,l1) >::object());

#define o_reflection_add_template_parameter_reflection_3(l0,l1) \
    o_reflection_add_template_parameter_reflection_2(l0,l1) \
    pTemplateSpecialization->setArgument(o_PP_QUOTE(o_PP_CAT(o_PP_ARG_2,l1)), o_PP_CAT(template_signature_parameter_,o_PP_CAT(o_PP_ARG_2,l0))< o_PP_CAT(o_PP_ARG_2,l1) >::object());

#define o_reflection_add_template_parameter_reflection_4(l0,l1) \
    o_reflection_add_template_parameter_reflection_3(l0,l1) \
    pTemplateSpecialization->setArgument(o_PP_QUOTE(o_PP_CAT(o_PP_ARG_3,l1)), o_PP_CAT(template_signature_parameter_,o_PP_CAT(o_PP_ARG_3,l0))< o_PP_CAT(o_PP_ARG_3,l1) >::object());

#define o_reflection_add_template_parameter_reflection_5(l0,l1) \
    o_reflection_add_template_parameter_reflection_4(l0,l1) \
    pTemplateSpecialization->setArgument(o_PP_QUOTE(o_PP_CAT(o_PP_ARG_4,l1)), o_PP_CAT(template_signature_parameter_,o_PP_CAT(o_PP_ARG_4,l0))< o_PP_CAT(o_PP_ARG_4,l1) >::object());

#define o_reflection_add_template_parameter_reflection_6(l0,l1) \
    o_reflection_add_template_parameter_reflection_5(l0,l1) \
    pTemplateSpecialization->setArgument(o_PP_QUOTE(o_PP_CAT(o_PP_ARG_5,l1)), o_PP_CAT(template_signature_parameter_,o_PP_CAT(o_PP_ARG_5,l0))< o_PP_CAT(o_PP_ARG_5,l1) >::object());

#define o_reflection_add_template_parameter_reflection_7(l0,l1) \
    o_reflection_add_template_parameter_reflection_6(l0,l1) \
    pTemplateSpecialization->setArgument(o_PP_QUOTE(o_PP_CAT(o_PP_ARG_6,l1)), o_PP_CAT(template_signature_parameter_,o_PP_CAT(o_PP_ARG_6,l0))< o_PP_CAT(o_PP_ARG_6,l1) >::object());

#define o_reflection_add_template_parameter_reflection_8(l0,l1) \
    o_reflection_add_template_parameter_reflection_7(l0,l1) \
    pTemplateSpecialization->setArgument(o_PP_QUOTE(o_PP_CAT(o_PP_ARG_7,l1)), o_PP_CAT(template_signature_parameter_,o_PP_CAT(o_PP_ARG_7,l0))< o_PP_CAT(o_PP_ARG_7,l1) >::object());

#define o_reflection_add_template_parameter_reflection_9(l0,l1) \
    o_reflection_add_template_parameter_reflection_8(l0,l1) \
    pTemplateSpecialization->setArgument(o_PP_QUOTE(o_PP_CAT(o_PP_ARG_8,l1)), o_PP_CAT(template_signature_parameter_,o_PP_CAT(o_PP_ARG_8,l0))< o_PP_CAT(o_PP_ARG_8,l1) >::object());

#define o_reflection_add_template_parameter_reflection_10(l0,l1) \
    o_reflection_add_template_parameter_reflection_9(l0,l1) \
    pTemplateSpecialization->setArgument(o_PP_QUOTE(o_PP_CAT(o_PP_ARG_9,l1)), o_PP_CAT(template_signature_parameter_,o_PP_CAT(o_PP_ARG_9,l0))< o_PP_CAT(o_PP_ARG_9,l1) >::object());

#else /// NOT VISUAL STUDIO

#define o_reflection_add_template_parameter_reflection(l0,l1) \
    o_PP_CAT( o_reflection_add_template_parameter_reflection_,o_PP_NARG_FUNC()l0 ) (l0,l1)

#define o_reflection_add_template_parameter_reflection_1(l0,l1) \
    pTemplateSpecialization->setArgument(o_PP_QUOTE(o_PP_ARG_0 l1), o_PP_CAT(template_signature_parameter_,o_PP_ARG_0 l0)< o_PP_ARG_0 l1 >::object()); \

#define o_reflection_add_template_parameter_reflection_2(l0,l1) \
    o_reflection_add_template_parameter_reflection_1(l0,l1) \
    pTemplateSpecialization->setArgument(o_PP_QUOTE(o_PP_ARG_1 l1), o_PP_CAT(template_signature_parameter_,o_PP_ARG_1 l0)< o_PP_ARG_1 l1 >::object());

#define o_reflection_add_template_parameter_reflection_3(l0,l1) \
    o_reflection_add_template_parameter_reflection_2(l0,l1) \
    pTemplateSpecialization->setArgument(o_PP_QUOTE(o_PP_ARG_2 l1), o_PP_CAT(template_signature_parameter_,o_PP_ARG_2 l0)< o_PP_ARG_2 l1>::object());

#define o_reflection_add_template_parameter_reflection_4(l0,l1) \
    o_reflection_add_template_parameter_reflection_3(l0,l1) \
    pTemplateSpecialization->setArgument(o_PP_QUOTE(o_PP_ARG_3 l1), o_PP_CAT(template_signature_parameter_,o_PP_ARG_3 l0)< o_PP_ARG_3 l1>::object());

#define o_reflection_add_template_parameter_reflection_5(l0,l1) \
    o_reflection_add_template_parameter_reflection_4(l0,l1) \
    pTemplateSpecialization->setArgument(o_PP_QUOTE(o_PP_ARG_4 l1), o_PP_CAT(template_signature_parameter_,o_PP_ARG_4 l0)< o_PP_ARG_4 l1>::object());

#define o_reflection_add_template_parameter_reflection_6(l0,l1) \
    o_reflection_add_template_parameter_reflection_5(l0,l1) \
    pTemplateSpecialization->setArgument(o_PP_QUOTE(o_PP_ARG_5 l1), o_PP_CAT(template_signature_parameter_,o_PP_ARG_5 l0)< o_PP_ARG_5 l1 >::object());

#define o_reflection_add_template_parameter_reflection_7(l0,l1) \
    o_reflection_add_template_parameter_reflection_6(l0,l1) \
    pTemplateSpecialization->setArgument(o_PP_QUOTE(o_PP_ARG_6 l1), o_PP_CAT(template_signature_parameter_,o_PP_ARG_6 l0)< o_PP_ARG_6 l1 >::object());

#define o_reflection_add_template_parameter_reflection_8(l0,l1) \
    o_reflection_add_template_parameter_reflection_7(l0,l1) \
    pTemplateSpecialization->setArgument(o_PP_QUOTE(o_PP_ARG_7 l1), o_PP_CAT(template_signature_parameter_,o_PP_ARG_7 l0)< o_PP_ARG_7 l1 >::object());

#define o_reflection_add_template_parameter_reflection_9(l0,l1) \
    o_reflection_add_template_parameter_reflection_8(l0,l1) \
    pTemplateSpecialization->setArgument(o_PP_QUOTE(o_PP_ARG_8 l1), o_PP_CAT(template_signature_parameter_,o_PP_ARG_8 l0)< o_PP_ARG_8 l1 >::object());

#define o_reflection_add_template_parameter_reflection_10(l0,l1) \
    o_reflection_add_template_parameter_reflection_9(l0,l1) \
    pTemplateSpecialization->setArgument(o_PP_QUOTE(o_PP_ARG_9 l1), o_PP_CAT(template_signature_parameter_,o_PP_ARG_9 l0)< o_PP_ARG_9 l1 >::object());

#endif // o_COMPILER

#define o_PP_CREATE_QUALIFIED_NAME(_namespaces_,_name_) \
    :: o_PP_CREATE_SCOPE _namespaces_ :: _name_

#define o_PP_CREATE_QUALIFIED_NAME_RELATIVE(_namespaces_,_name_) \
    o_PP_CREATE_SCOPE _namespaces_ :: _name_

#if o_COMPILER == o_COMPILER_VISUAL_STUDIO

#define o_PP_CREATE_QUALIFIED_IDENTIFIER_NAME(_namespaces_,_name_) \
    o_PP_IDENTITY(o_PP_IDENTITY o_PP_LEFT_PAREN o_PP_CREATE_SCOPE_IDENTIFIER _namespaces_##_##_name_ o_PP_RIGHT_PAREN)

#define o__PP_CREATE_QUALIFIED_IDENTIFIER_NAME(_namespaces_,_name_) \
    _o_PP_IDENTITY(o_PP_IDENTITY o_PP_LEFT_PAREN o_PP_CREATE_SCOPE_IDENTIFIER _namespaces_##_##_name_ o_PP_RIGHT_PAREN)

#define o_PP_CREATE_QUALIFIED_NAME_2(_namespaces_,_classes_,_name_) \
    :: o_PP_CREATE_SCOPE _namespaces_ :: o_PP_CREATE_SCOPE _classes_ :: _name_

#define o_PP_CREATE_QUALIFIED_IDENTIFIER_NAME_2(_namespaces_,_classes_,_name_) \
    o_PP_IDENTITY(o_PP_IDENTITY o_PP_LEFT_PAREN o_PP_CREATE_SCOPE_IDENTIFIER _namespaces_##o__PP_CREATE_QUALIFIED_IDENTIFIER_NAME(_classes_, _name_) o_PP_RIGHT_PAREN)

#else

#define o_PP_CREATE_QUALIFIED_IDENTIFIER_NAME(_namespaces_,_name_) \
    o_PP_BY_LIST(o_PP_CAT, (o_PP_CREATE_SCOPE_IDENTIFIER(o_PP_IDENTITY _namespaces_), _##_name_))

#define o__PP_CREATE_QUALIFIED_IDENTIFIER_NAME(_namespaces_,_name_) \
    _o_PP_IDENTITY(o_PP_IDENTITY o_PP_LEFT_PAREN o_PP_CREATE_SCOPE_IDENTIFIER o_PP_IDENTITY(_namespaces_)_##_name_ o_PP_RIGHT_PAREN)

#define o_PP_CREATE_QUALIFIED_NAME_2(_namespaces_,_classes_,_name_) \
    :: o_PP_CREATE_SCOPE _namespaces_ :: o_PP_CREATE_SCOPE _classes_ :: _name_

#define o_PP_CREATE_QUALIFIED_IDENTIFIER_NAME_2(_namespaces_,_classes_,_name_) \
    o_PP_IDENTITY(o_PP_IDENTITY o_PP_LEFT_PAREN o_PP_CREATE_SCOPE_IDENTIFIER _namespaces_##o__PP_CREATE_QUALIFIED_IDENTIFIER_NAME(_classes_, _name_) o_PP_RIGHT_PAREN)

#endif

#if o__int__reflection_template_use_level == 3
#   include "def_macros_reflection_3.h"
#elif o__int__reflection_template_use_level == 2
#   include "def_macros_reflection_2.h"
#elif o__int__reflection_template_use_level == 1
#   include "def_macros_reflection_1.h"
#else
#   include "def_macros_reflection_0.h"
#endif

#if o_COMPILER == o_COMPILER_VISUAL_STUDIO
#   define o_data_member(...) o_PP_CAT(o_PP_CAT(o_data_member_,o_PP_NARG(__VA_ARGS__)),(__VA_ARGS__))
#   define o_property(...) o_PP_CAT(o_PP_CAT(o_property_,o_PP_NARG(__VA_ARGS__)),(__VA_ARGS__))
#   define o_range(...) o_PP_CAT(o_PP_CAT(o_range_,o_PP_NARG(__VA_ARGS__)),(__VA_ARGS__))
#   define o_nested_typedef(...) o_PP_CAT(o_PP_CAT(o_nested_typedef_,o_PP_NARG(__VA_ARGS__)),(__VA_ARGS__))
#else
#   define o_data_member(...) o_PP_CAT(o_data_member_,o_PP_NARG(__VA_ARGS__)) (__VA_ARGS__)
#   define o_property(...) o_PP_CAT(o_property_,o_PP_NARG(__VA_ARGS__)) (__VA_ARGS__)
#   define o_range(...) o_PP_CAT(o_range_,o_PP_NARG(__VA_ARGS__)) (__VA_ARGS__)
#   define o_nested_typedef(...) o_PP_CAT(o_nested_typedef_,o_PP_NARG(__VA_ARGS__)) (__VA_ARGS__)
#endif

#define o_using(where, ...)\
    static phantom::reflection::using_registrer o_PP_CAT(g_using_registrer, __LINE__)(o_PP_QUOTE##where, o_PP_QUOTE##__VA_ARGS__);

#define o_nested_using(...)\
class o_PP_CAT(nested_using, __LINE__)\
    {\
    friend class enclosed_reflection;\
    o_PP_CAT(nested_using,__LINE__)() \
        {\
        phantom::reflection::Types::currentInstalledClass->addUsing(phantom::elementByName(#__VA_ARGS__, phantom::reflection::Types::currentInstalledClass));\
        }\
    } o_PP_CAT(_nested_using,__LINE__);

#define o_friend(_who_, _friend_)\
    static phantom::reflection::friend_registrer o_PP_CAT(g_friend_registrer, __LINE__)(o_PP_QUOTE##_who_, o_PP_QUOTE##_friend_);

#define o_nested_friend(...)\
class o_PP_CAT(nested_friend, __LINE__)\
    {\
    friend class enclosed_reflection;\
    o_PP_CAT(nested_friend,__LINE__)() \
        {\
        phantom::reflection::Types::currentInstalledClass->addFriend(phantom::elementByName(#__VA_ARGS__, phantom::reflection::Types::currentInstalledClass));\
        }\
    } o_PP_CAT(_nested_friend,__LINE__);

#define o_default_template_argument_constant(parameter, ...)\
class o_PP_CAT(parameter,__LINE__) \
        {\
        friend class enclosed_reflection;\
        o_PP_CAT(parameter,__LINE__)() \
            {\
            phantom::reflection::Types::currentInstalledTemplateSpecialization->setDefaultArgument(#parameter, o_dynamic_proxy_new(phantom::reflection::native::TNumericConstant<decltype(parameter)>)(parameter, o_native));\
            }\
        } o_PP_CAT(parameter,__LINE__);

#define o_range_1(_default_) \
    phantom::reflection::native::CreateRange(_default_)

#define o_range_2(_min_, _max_) \
    phantom::reflection::native::CreateRange(_min_, _max_)

#define o_range_3(_min_, _default_, _max_) \
    phantom::reflection::native::CreateRange(_min_, _default_, _max_)

// DATA MEMBER

#define o_data_member_2(_type_, _name_) \
    o_data_member_5(_type_, _name_, (phantom::reflection::native::null_range()), 0, o_save_data)

#define o_data_member_3(_type_, _name_, _range_) \
    o_data_member_5(_type_, _name_, _range_, 0, o_save_data)

#define o_data_member_4(_type_, _name_, _range_, _modifiers_) \
    o_data_member_5(_type_, _name_, _range_, _modifiers_, ((((_modifiers_)&o_transient)==0) ? o_save_data : 0))

// PROPERTY

#define o_property_4(_type_, _name_, _set_member_function_, _get_member_function_)\
    o_property_8(_type_, _name_, _set_member_function_, _get_member_function_, m_PHANTOM_RESERVED_no_signal, (phantom::reflection::native::null_range()), 0, o_save_state )

#define o_property_5(_type_, _name_, _set_member_function_, _get_member_function_, _signal_)\
    o_property_8(_type_, _name_, _set_member_function_, _get_member_function_, _signal_, (phantom::reflection::native::null_range()), 0, o_save_state)

#define o_property_6(_type_, _name_, _set_member_function_, _get_member_function_, _signal_, _range_)\
    o_property_8(_type_, _name_, _set_member_function_, _get_member_function_, _signal_, _range_, 0, o_save_state )

#define o_property_7(_type_, _name_, _set_member_function_, _get_member_function_, _signal_, _range_, _modifiers_)\
    o_property_8(_type_, _name_, _set_member_function_, _get_member_function_, _signal_, _range_, _modifiers_, ((((_modifiers_)&o_transient)==0) ? o_save_state : 0 ) )


#if o_COMPILER == o_COMPILER_VISUAL_STUDIO
#define o_enum_add_values( ... ) o_PP_CAT(o_PP_CAT(o_enum_add_values_, o_PP_NARG(__VA_ARGS__)),(__VA_ARGS__) )
#else
#define o_enum_add_values( ... ) o_PP_CAT(o_enum_add_values_, o_PP_NARG(__VA_ARGS__)) (__VA_ARGS__)
#endif

#define o_enum_add_values_1( v0) pEnum->addConstant(o_dynamic_proxy_new(phantom::reflection::native::TNumericConstant<enum_value_type>)(o_PP_QUOTE(v0), v0, o_native));
#define o_enum_add_values_2( v0,v1) o_enum_add_values_1( v0) o_enum_add_values_1(v1)
#define o_enum_add_values_3( v0,v1,v2)  o_enum_add_values_2( v0,v1) o_enum_add_values_1(v2)
#define o_enum_add_values_4( v0,v1,v2,v3) o_enum_add_values_3( v0,v1,v2) o_enum_add_values_1(v3)
#define o_enum_add_values_5( v0,v1,v2,v3,v4) o_enum_add_values_4( v0,v1,v2,v3) o_enum_add_values_1(v4)
#define o_enum_add_values_6( v0,v1,v2,v3,v4,v5) o_enum_add_values_5( v0,v1,v2,v3,v4) o_enum_add_values_1(v5)
#define o_enum_add_values_7( v0,v1,v2,v3,v4,v5,v6) o_enum_add_values_6( v0,v1,v2,v3,v4,v5) o_enum_add_values_1(v6)
#define o_enum_add_values_8( v0,v1,v2,v3,v4,v5,v6,v7) o_enum_add_values_7( v0,v1,v2,v3,v4,v5,v6)  o_enum_add_values_1(v7)
#define o_enum_add_values_9( v0,v1,v2,v3,v4,v5,v6,v7,v8) o_enum_add_values_8( v0,v1,v2,v3,v4,v5,v6,v7) o_enum_add_values_1(v8)
#define o_enum_add_values_10(v0,v1,v2,v3,v4,v5,v6,v7,v8,v9) o_enum_add_values_9( v0,v1,v2,v3,v4,v5,v6,v7,v8) o_enum_add_values_1(v9)
#define o_enum_add_values_11(v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10) o_enum_add_values_10(v0,v1,v2,v3,v4,v5,v6,v7,v8,v9)  o_enum_add_values_1(v10)
#define o_enum_add_values_12(v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11) o_enum_add_values_11(v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10)  o_enum_add_values_1(v11)
#define o_enum_add_values_13(v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12) o_enum_add_values_12(v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11)  o_enum_add_values_1(v12)
#define o_enum_add_values_14(v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13) o_enum_add_values_13(v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12)  o_enum_add_values_1(v13)
#define o_enum_add_values_15(v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14) o_enum_add_values_14(v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13)  o_enum_add_values_1(v14)
#define o_enum_add_values_16(v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15) o_enum_add_values_15(v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14)  o_enum_add_values_1(v15)
#define o_enum_add_values_17(v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16) o_enum_add_values_16(v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15)  o_enum_add_values_1(v16)
#define o_enum_add_values_18(v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17) o_enum_add_values_17(v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16) o_enum_add_values_1(v17)
#define o_enum_add_values_19(v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17,v18) o_enum_add_values_18(v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17)  o_enum_add_values_1(v18)
#define o_enum_add_values_20(v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17,v18,v19) o_enum_add_values_19(v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17,v18)  o_enum_add_values_1(v19)
#define o_enum_add_values_21(v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17,v18,v19,v20) o_enum_add_values_20(v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17,v18,v19)  o_enum_add_values_1(v20)
#define o_enum_add_values_22(v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17,v18,v19,v20,v21) o_enum_add_values_21(v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17,v18,v19,v20)  o_enum_add_values_1(v21)
#define o_enum_add_values_23(v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17,v18,v19,v20,v21,v22) o_enum_add_values_22(v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17,v18,v19,v20,v21)  o_enum_add_values_1(v22)
#define o_enum_add_values_24(v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17,v18,v19,v20,v21,v22,v23) o_enum_add_values_23(v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17,v18,v19,v20,v21,v22)  o_enum_add_values_1(v23)
#define o_enum_add_values_25(v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17,v18,v19,v20,v21,v22,v23,v24) o_enum_add_values_24(v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17,v18,v19,v20,v21,v22,v23)  o_enum_add_values_1(v24)
#define o_enum_add_values_26(v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17,v18,v19,v20,v21,v22,v23,v24,v25) o_enum_add_values_25(v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17,v18,v19,v20,v21,v22,v23,v24)  o_enum_add_values_1(v25)
#define o_enum_add_values_27(v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17,v18,v19,v20,v21,v22,v23,v24,v25,v26) o_enum_add_values_26(v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17,v18,v19,v20,v21,v22,v23,v24,v25)  o_enum_add_values_1(v26)
#define o_enum_add_values_28(v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17,v18,v19,v20,v21,v22,v23,v24,v25,v26,v27) o_enum_add_values_27(v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17,v18,v19,v20,v21,v22,v23,v24,v25,v26)  o_enum_add_values_1(v27)
#define o_enum_add_values_29(v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17,v18,v19,v20,v21,v22,v23,v24,v25,v26,v27,v28) o_enum_add_values_28(v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17,v18,v19,v20,v21,v22,v23,v24,v25,v26,v27)  o_enum_add_values_1(v28)
#define o_enum_add_values_30(v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17,v18,v19,v20,v21,v22,v23,v24,v25,v26,v27,v28,v29) o_enum_add_values_29(v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17,v18,v19,v20,v21,v22,v23,v24,v25,v26,v27,v28)  o_enum_add_values_1(v29)
#define o_enum_add_values_31(v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17,v18,v19,v20,v21,v22,v23,v24,v25,v26,v27,v28,v29,v30) o_enum_add_values_30(v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17,v18,v19,v20,v21,v22,v23,v24,v25,v26,v27,v28,v29)  o_enum_add_values_1(v30)
#define o_enum_add_values_32(v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17,v18,v19,v20,v21,v22,v23,v24,v25,v26,v27,v28,v29,v30,v31) o_enum_add_values_31(v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17,v18,v19,v20,v21,v22,v23,v24,v25,v26,v27,v28,v29,v30)  o_enum_add_values_1(v31)
#define o_enum_add_values_33(v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17,v18,v19,v20,v21,v22,v23,v24,v25,v26,v27,v28,v29,v30,v31,v32) o_enum_add_values_32(v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17,v18,v19,v20,v21,v22,v23,v24,v25,v26,v27,v28,v29,v30,v31)  o_enum_add_values_1(v32)
#define o_enum_add_values_34(v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17,v18,v19,v20,v21,v22,v23,v24,v25,v26,v27,v28,v29,v30,v31,v32,v33) o_enum_add_values_33(v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17,v18,v19,v20,v21,v22,v23,v24,v25,v26,v27,v28,v29,v30,v31,v32)  o_enum_add_values_1(v33)
#define o_enum_add_values_35(v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17,v18,v19,v20,v21,v22,v23,v24,v25,v26,v27,v28,v29,v30,v31,v32,v33,v34) o_enum_add_values_34(v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17,v18,v19,v20,v21,v22,v23,v24,v25,v26,v27,v28,v29,v30,v31,v32,v33)  o_enum_add_values_1(v34)
#define o_enum_add_values_36(v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17,v18,v19,v20,v21,v22,v23,v24,v25,v26,v27,v28,v29,v30,v31,v32,v33,v34,v35) o_enum_add_values_35(v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17,v18,v19,v20,v21,v22,v23,v24,v25,v26,v27,v28,v29,v30,v31,v32,v33,v34)  o_enum_add_values_1(v35)
#define o_enum_add_values_37(v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17,v18,v19,v20,v21,v22,v23,v24,v25,v26,v27,v28,v29,v30,v31,v32,v33,v34,v35,v36) o_enum_add_values_36(v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17,v18,v19,v20,v21,v22,v23,v24,v25,v26,v27,v28,v29,v30,v31,v32,v33,v34,v35)  o_enum_add_values_1(v36)
#define o_enum_add_values_38(v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17,v18,v19,v20,v21,v22,v23,v24,v25,v26,v27,v28,v29,v30,v31,v32,v33,v34,v35,v36,v37) o_enum_add_values_37(v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17,v18,v19,v20,v21,v22,v23,v24,v25,v26,v27,v28,v29,v30,v31,v32,v33,v34,v35,v36)  o_enum_add_values_1(v37)
#define o_enum_add_values_39(v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17,v18,v19,v20,v21,v22,v23,v24,v25,v26,v27,v28,v29,v30,v31,v32,v33,v34,v35,v36,v37,v38) o_enum_add_values_38(v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17,v18,v19,v20,v21,v22,v23,v24,v25,v26,v27,v28,v29,v30,v31,v32,v33,v34,v35,v36,v37)  o_enum_add_values_1(v38)
#define o_enum_add_values_40(v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17,v18,v19,v20,v21,v22,v23,v24,v25,v26,v27,v28,v29,v30,v31,v32,v33,v34,v35,v36,v37,v38,v39) o_enum_add_values_39(v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17,v18,v19,v20,v21,v22,v23,v24,v25,v26,v27,v28,v29,v30,v31,v32,v33,v34,v35,v36,v37,v38)  o_enum_add_values_1(v39)


#if o_COMPILER == o_COMPILER_VISUAL_STUDIO
#define o_enum_add_valuesN( ... ) o_PP_CAT(o_PP_CAT(o_enum_add_valuesN_, o_PP_NARG(__VA_ARGS__)),(__VA_ARGS__) )
#else
#define o_enum_add_valuesN( ... ) o_PP_CAT(o_enum_add_valuesN_, o_PP_NARG(__VA_ARGS__)) (__VA_ARGS__)
#endif

#define o_enum_add_valuesN_2( n, v0) pEnum->addConstant(o_dynamic_proxy_new(phantom::reflection::native::TNumericConstant<enum_value_type>)(o_PP_QUOTE(v0), ::o_PP_CREATE_SCOPE n::v0, o_native));
#define o_enum_add_valuesN_3( n, v0,v1) o_enum_add_valuesN_2(n, v0) o_enum_add_valuesN_2(n,v1)
#define o_enum_add_valuesN_4( n, v0,v1,v2)  o_enum_add_valuesN_3(n, v0,v1) o_enum_add_valuesN_2(n,v2)
#define o_enum_add_valuesN_5( n, v0,v1,v2,v3) o_enum_add_valuesN_4(n, v0,v1,v2) o_enum_add_valuesN_2(n,v3)
#define o_enum_add_valuesN_6( n, v0,v1,v2,v3,v4) o_enum_add_valuesN_5(n, v0,v1,v2,v3) o_enum_add_valuesN_2(n,v4)
#define o_enum_add_valuesN_7( n, v0,v1,v2,v3,v4,v5) o_enum_add_valuesN_6(n, v0,v1,v2,v3,v4) o_enum_add_valuesN_2(n,v5)
#define o_enum_add_valuesN_8( n, v0,v1,v2,v3,v4,v5,v6) o_enum_add_valuesN_7(n, v0,v1,v2,v3,v4,v5) o_enum_add_valuesN_2(n,v6)
#define o_enum_add_valuesN_9( n, v0,v1,v2,v3,v4,v5,v6,v7) o_enum_add_valuesN_8(n, v0,v1,v2,v3,v4,v5,v6)  o_enum_add_valuesN_2(n,v7)
#define o_enum_add_valuesN_10( n, v0,v1,v2,v3,v4,v5,v6,v7,v8) o_enum_add_valuesN_9(n, v0,v1,v2,v3,v4,v5,v6,v7) o_enum_add_valuesN_2(n,v8)
#define o_enum_add_valuesN_11(n, v0,v1,v2,v3,v4,v5,v6,v7,v8,v9) o_enum_add_valuesN_10(n, v0,v1,v2,v3,v4,v5,v6,v7,v8) o_enum_add_valuesN_2(n,v9)
#define o_enum_add_valuesN_12(n, v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10) o_enum_add_valuesN_11(n, v0,v1,v2,v3,v4,v5,v6,v7,v8,v9)  o_enum_add_valuesN_2(n,v10)
#define o_enum_add_valuesN_13(n, v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11) o_enum_add_valuesN_12(n, v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10)  o_enum_add_valuesN_2(n,v11)
#define o_enum_add_valuesN_14(n, v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12) o_enum_add_valuesN_13(n, v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11)  o_enum_add_valuesN_2(n,v12)
#define o_enum_add_valuesN_15(n, v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13) o_enum_add_valuesN_14(n, v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12)  o_enum_add_valuesN_2(n,v13)
#define o_enum_add_valuesN_16(n, v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14) o_enum_add_valuesN_15(n, v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13)  o_enum_add_valuesN_2(n,v14)
#define o_enum_add_valuesN_17(n, v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15) o_enum_add_valuesN_16(n, v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14)  o_enum_add_valuesN_2(n,v15)
#define o_enum_add_valuesN_18(n, v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16) o_enum_add_valuesN_17(n, v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15)  o_enum_add_valuesN_2(n,v16)
#define o_enum_add_valuesN_19(n, v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17) o_enum_add_valuesN_18(n, v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16) o_enum_add_valuesN_2(n,v17)
#define o_enum_add_valuesN_20(n, v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17,v18) o_enum_add_valuesN_19(n, v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17)  o_enum_add_valuesN_2(n,v18)
#define o_enum_add_valuesN_21(n, v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17,v18,v19) o_enum_add_valuesN_20(n, v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17,v18)  o_enum_add_valuesN_2(n,v19)
#define o_enum_add_valuesN_22(n, v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17,v18,v19,v20) o_enum_add_valuesN_21(n, v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17,v18,v19)  o_enum_add_valuesN_2(n,v20)
#define o_enum_add_valuesN_23(n, v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17,v18,v19,v20,v21) o_enum_add_valuesN_22(n, v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17,v18,v19,v20)  o_enum_add_valuesN_2(n,v21)
#define o_enum_add_valuesN_24(n, v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17,v18,v19,v20,v21,v22) o_enum_add_valuesN_23(n, v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17,v18,v19,v20,v21)  o_enum_add_valuesN_2(n,v22)
#define o_enum_add_valuesN_25(n, v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17,v18,v19,v20,v21,v22,v23) o_enum_add_valuesN_24(n, v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17,v18,v19,v20,v21,v22)  o_enum_add_valuesN_2(n,v23)
#define o_enum_add_valuesN_26(n, v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17,v18,v19,v20,v21,v22,v23,v24,v25) o_enum_add_valuesN_25(n, v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17,v18,v19,v20,v21,v22,v23,v24)  o_enum_add_valuesN_2(n, v25)
#define o_enum_add_valuesN_27(n, v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17,v18,v19,v20,v21,v22,v23,v24,v25,v26) o_enum_add_valuesN_26(n, v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17,v18,v19,v20,v21,v22,v23,v24,v25)  o_enum_add_valuesN_2(n, v26)
#define o_enum_add_valuesN_28(n, v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17,v18,v19,v20,v21,v22,v23,v24,v25,v26,v27) o_enum_add_valuesN_27(n, v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17,v18,v19,v20,v21,v22,v23,v24,v25,v26)  o_enum_add_valuesN_2(n, v27)
#define o_enum_add_valuesN_29(n, v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17,v18,v19,v20,v21,v22,v23,v24,v25,v26,v27,v28) o_enum_add_valuesN_28(n, v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17,v18,v19,v20,v21,v22,v23,v24,v25,v26,v27)  o_enum_add_valuesN_2(n, v28)
#define o_enum_add_valuesN_30(n, v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17,v18,v19,v20,v21,v22,v23,v24,v25,v26,v27,v28,v29) o_enum_add_valuesN_29(n, v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17,v18,v19,v20,v21,v22,v23,v24,v25,v26,v27,v28)  o_enum_add_valuesN_2(n, v29)
#define o_enum_add_valuesN_31(n, v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17,v18,v19,v20,v21,v22,v23,v24,v25,v26,v27,v28,v29,v30) o_enum_add_valuesN_30(n, v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17,v18,v19,v20,v21,v22,v23,v24,v25,v26,v27,v28,v29)  o_enum_add_valuesN_2(n, v30)
#define o_enum_add_valuesN_32(n, v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17,v18,v19,v20,v21,v22,v23,v24,v25,v26,v27,v28,v29,v30,v31) o_enum_add_valuesN_31(n, v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17,v18,v19,v20,v21,v22,v23,v24,v25,v26,v27,v28,v29,v30)  o_enum_add_valuesN_2(n, v31)
#define o_enum_add_valuesN_33(n, v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17,v18,v19,v20,v21,v22,v23,v24,v25,v26,v27,v28,v29,v30,v31,v32) o_enum_add_valuesN_32(n, v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17,v18,v19,v20,v21,v22,v23,v24,v25,v26,v27,v28,v29,v30,v31)  o_enum_add_valuesN_2(n, v32)
#define o_enum_add_valuesN_34(n, v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17,v18,v19,v20,v21,v22,v23,v24,v25,v26,v27,v28,v29,v30,v31,v32,v33) o_enum_add_valuesN_33(n, v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17,v18,v19,v20,v21,v22,v23,v24,v25,v26,v27,v28,v29,v30,v31,v32)  o_enum_add_valuesN_2(n, v33)
#define o_enum_add_valuesN_35(n, v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17,v18,v19,v20,v21,v22,v23,v24,v25,v26,v27,v28,v29,v30,v31,v32,v33,v34) o_enum_add_valuesN_34(n, v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17,v18,v19,v20,v21,v22,v23,v24,v25,v26,v27,v28,v29,v30,v31,v32,v33)  o_enum_add_valuesN_2(n, v34)
#define o_enum_add_valuesN_36(n, v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17,v18,v19,v20,v21,v22,v23,v24,v25,v26,v27,v28,v29,v30,v31,v32,v33,v34,v35) o_enum_add_valuesN_35(n, v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17,v18,v19,v20,v21,v22,v23,v24,v25,v26,v27,v28,v29,v30,v31,v32,v33,v34)  o_enum_add_valuesN_2(n, v35)
#define o_enum_add_valuesN_37(n, v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17,v18,v19,v20,v21,v22,v23,v24,v25,v26,v27,v28,v29,v30,v31,v32,v33,v34,v35,v36) o_enum_add_valuesN_36(n, v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17,v18,v19,v20,v21,v22,v23,v24,v25,v26,v27,v28,v29,v30,v31,v32,v33,v34,v35)  o_enum_add_valuesN_2(n, v36)
#define o_enum_add_valuesN_38(n, v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17,v18,v19,v20,v21,v22,v23,v24,v25,v26,v27,v28,v29,v30,v31,v32,v33,v34,v35,v36,v37) o_enum_add_valuesN_37(n, v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17,v18,v19,v20,v21,v22,v23,v24,v25,v26,v27,v28,v29,v30,v31,v32,v33,v34,v35,v36)  o_enum_add_valuesN_2(n, v37)
#define o_enum_add_valuesN_39(n, v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17,v18,v19,v20,v21,v22,v23,v24,v25,v26,v27,v28,v29,v30,v31,v32,v33,v34,v35,v36,v37,v38) o_enum_add_valuesN_38(n, v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17,v18,v19,v20,v21,v22,v23,v24,v25,v26,v27,v28,v29,v30,v31,v32,v33,v34,v35,v36,v37)  o_enum_add_valuesN_2(n, v38)
#define o_enum_add_valuesN_40(n, v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17,v18,v19,v20,v21,v22,v23,v24,v25,v26,v27,v28,v29,v30,v31,v32,v33,v34,v35,v36,v37,v38,v39) o_enum_add_valuesN_39(n, v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17,v18,v19,v20,v21,v22,v23,v24,v25,v26,v27,v28,v29,v30,v31,v32,v33,v34,v35,v36,v37,v38)  o_enum_add_valuesN_2(n, v39)

#define o_typedef(_name_) \
    phantom::reflection::typedef_registrer<_name_>  o_PP_CAT(g_reflection_typedef_registration_##_name_, __COUNTER__) (#_name_);

#if o_COMPILER == o_COMPILER_VISUAL_STUDIO

#define o_typedefN(_namespaces_, _name_) \
    phantom::reflection::typedef_registrer<o_PP_CREATE_QUALIFIED_NAME(_namespaces_, _name_)>  o_PP_CAT(g_reflection_typedef_registration_##_name_, __COUNTER__) ( o_PP_QUOTE o_PP_LEFT_PAREN o_PP_CREATE_SCOPE _namespaces_ o_PP_RIGHT_PAREN, #_name_);

#else

#define o_typedefN(_namespaces_, _name_) \
    phantom::reflection::typedef_registrer<o_PP_CREATE_QUALIFIED_NAME(_namespaces_, _name_)>  o_PP_CAT(g_reflection_typedef_registration_##_name_, __COUNTER__) ( o_PP_QUOTE( o_PP_CREATE_SCOPE _namespaces_ ), #_name_);

#endif

//
// #define o_typedefNC(_namespace_, _class_, _typedef_) \
//     o_typedefNC_helper(_namespace_, _class_, o_PP_CAT(g_reflection_registration_typedef_friend_##_typedef_, o_PP_IDENTITY o_PP_LEFT_PAREN __COUNTER__ o_PP_RIGHT_PAREN ), _typedef_)
//
// #define o_typedefNC_helper(_namespace_, _class_, _friend_class_, _typedef_) \
//     class _friend_class_ : public _namespace_::_class_\
//     {\
//     public:\
//         typedef _typedef_ wrapped_typedef;\
//     };\
//     phantom::reflection::typedef_registrer<_friend_class_::wrapped_typedef>  o_PP_CAT(g_reflection_registration_##_typedef_, __COUNTER__) (#_namespace_"::"#_class_, #_typedef_);
//
// #define o_typedefC(_class_, _typedef_) \
//     o_typedefC_helper(_class_, o_PP_CAT(g_reflection_registration_friend_##_typedef_, o_PP_IDENTITY o_PP_LEFT_PAREN __COUNTER__ o_PP_RIGHT_PAREN ), _typedef_)

#define o_typedefC_helper(_class_, _friend_class_, _typedef_) \
class _friend_class_ : public _class_\
    {\
    public:\
    typedef _typedef_ wrapped_typedef;\
    };\
    phantom::reflection::typedef_registrer<_friend_class_::wrapped_typedef>  o_PP_CAT(g_reflection_registration_##_typedef_, __COUNTER__) (#_class_, #_typedef_);

#define o_namespace_alias(_namespace_alias_, _namespace_aliased_) \
    phantom::reflection::namespace_alias_registrer  o_PP_CAT(g_reflection_registration_##_namespace_alias_, __COUNTER__) (#_namespace_alias_, #_namespace_aliased_);


#if o_COMPILER == o_COMPILER_VISUAL_STUDIO
#define o_namespace( ... ) o_PP_CAT(o_PP_CAT(o_namespace_, o_PP_1_OR_X(__VA_ARGS__)),(__VA_ARGS__) )
#else
#define o_namespace( ... ) o_PP_CAT(o_namespace_, o_PP_1_OR_X(__VA_ARGS__)) (__VA_ARGS__)
#endif

#define o_namespace_X(...) \
    static phantom::reflection::namespace_registrer  o_PP_CAT(g_reflection_namespace_registration_, __COUNTER__) (o_PP_QUOTE_SCOPE((__VA_ARGS__)));

#define o_namespace_1(_namespace_) \
    static phantom::reflection::namespace_registrer  o_PP_CAT(g_reflection_namespace_registration_, __COUNTER__) (#_namespace_);

#define o_namespace_aliasN(_namespaces_, _namespace_alias_, _namespace_aliased_) \
    static phantom::reflection::namespace_alias_registrer  o_PP_CAT(g_reflection_registration_##_namespace_alias_, __COUNTER__) (o_PP_QUOTE o_PP_LEFT_PAREN o_PP_CREATE_SCOPE _namespaces_ o_PP_RIGHT_PAREN, #_namespace_alias_, #_namespace_aliased_);

#define o_declare_meta_type(_type_)\
    template<typename t_Ty> friend struct detail::type_of_builder;\
    template<typename t_Ty, int> friend class native::TType_;\
    friend struct phantom::reflection::Types;\
public:\
    static native::TType<_type_>* metaType;\
private:

#define o_define_meta_type(_type_)\
    native::TType<_type_>* _type_::metaType


#define o_define_template_signature_parameter_phantom_element_impl(_type_) \
    template<_type_ value>\
    reflection::TemplateElement* \
    reflection::detail::template_signature_parameter_phantom::_type_<value>::object()\
{\
    return o_dynamic_proxy_new(phantom::reflection::native::TNumericConstant<_type_>)(value, o_native);\
}

#define o_define_template_signature_parameter_phantom(_type_) \
    template<_type_ value>\
class _type_\
{\
public:\
    inline static phantom::reflection::TemplateElement* object();\
};

#define o_define_template_signature_parameter_name_phantom(_type_) \
    template<_type_ value>\
class _type_\
{\
public:\
    static phantom::string qualifiedDecoratedName()\
{\
    return phantom::lexical_cast<phantom::string>(value);\
}\
};


#define o_define_template_signature_parameter_element_impl(_type_) \
    template<_type_ value>\
    reflection::TemplateElement* \
    reflection::detail::template_signature_parameter_##_type_<value>::object()\
{\
    return o_dynamic_proxy_new(phantom::reflection::native::TNumericConstant<_type_>)("", value, o_native);\
    }

#define o_define_template_signature_parameter(_type_) \
    template<_type_ value>\
class template_signature_parameter_##_type_\
{\
public:\
    inline static phantom::reflection::TemplateElement* object();\
};\
    template<_type_ value>\
class template_signature_parameter_name_##_type_\
{\
public:\
    static phantom::string qualifiedDecoratedName()\
{\
    return phantom::lexical_cast<phantom::string>(value);\
    }\
};


#endif // o_phantom_custom_h__