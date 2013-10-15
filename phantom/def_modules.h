#ifndef o_phantom_modules__
#define o_phantom_modules__

#define o_anonymous_enum(_values_) 
#define o_anonymous_enumN(_namespaces_,_values_) 
#define o_anonymous_enumNTT(_namespaces_,_template_types_,_template_params_,_values_) 
#define o_anonymous_enumTT(_template_types_,_template_params_,_values_) 
#define o_anonymous_enumC(_classes_,_values_) 
#define o_anonymous_enumCTT(_classes_,_template_types_,_template_params_,_values_) 
#define o_anonymous_enumNC(_namespaces_,_classes_,_values_) 
#define o_anonymous_enumNCTT(_namespaces_,_classes_,_template_types_,_template_params_,_values_) 

#define o_expose(_name_) \
    o_reflection_specialize_type_of_counter(_name_)

#define o_exposeN(_namespaces_,_name_) \
    o_reflection_specialize_type_of_counterN(_namespaces_,_name_)

#define o_exposeNT(_namespaces_,_template_types_,_template_params_,_name_) \
    o_reflection_specialize_type_of_counterNTT(_namespaces_,_template_types_,_template_params_,_name_)

#define o_exposeT(_template_types_,_template_params_,_name_) \
    o_reflection_specialize_type_of_counterTT(_template_types_,_template_params_,_name_)

#define o_exposeC(_classes_,_name_) \
    o_reflection_specialize_type_of_counterC(_classes_,_name_)

#define o_exposeCT(_classes_,_template_types_,_template_params_,_name_) \
    o_reflection_specialize_type_of_counterCTT(_classes_,_template_types_,_template_params_,_name_)

#define o_exposeNC(_namespaces_,_classes_,_name_) \
    o_reflection_specialize_type_of_counterNC(_namespaces_,_classes_,_name_)

#define o_exposeNCT(_namespaces_,_classes_,_template_types_,_template_params_,_name_) \
    o_reflection_specialize_type_of_counterNCTT(_namespaces_,_classes_,_template_types_,_template_params_,_name_)


#define o_enum(_name_,_values_) \
    o_reflection_specialize_type_name_of_forward_helper(_name_)\
    o_type_specialize_traits(_name_) \
    o_enum_module(_name_,_values_)\

#define o_enumN(_namespaces_,_name_,_values_) \
     o_reflection_specialize_type_name_of_forward_helperN(_namespaces_,_name_)\
     o_type_specialize_traitsN(_namespaces_,_name_) \
     o_enum_moduleN(_namespaces_,_name_,_values_)\

#define o_enumC(_classes_,_name_,_values_) \
    o_reflection_specialize_type_name_of_forward_helperC(_classes_,_name_)\
    o_type_specialize_traitsC(_classes_,_name_) \
    o_enum_moduleC(_classes_,_name_,_values_)\

#define o_enumNC(_namespaces_,_classes_,_name_,_values_) \
    o_reflection_specialize_type_name_of_forward_helperNC(_namespaces_,_classes_,_name_)\
    o_type_specialize_traitsNC(_namespaces_,_classes_,_name_) \
    o_enum_moduleNC(_namespaces_,_classes_,_name_,_values_)\

#define o_type_specialize_traitsNTTS(_namespaces_,_template_types_,_template_params_,_name_,_supers_)  \
    o_reflection_specialize_type_name_of_helperNTT(_namespaces_,_template_types_,_template_params_,_name_) \
    o_reflection_specialize_template_specialization_adderNTT(_namespaces_,_template_types_,_template_params_,_name_)\
    o_traits_specialize_all_super_traitNTTS(_namespaces_, _template_types_,_template_params_, _name_,_supers_)\
    o_traits_specializeNTT(is_template, (const static bool value = true), _namespaces_, _template_types_,_template_params_, _name_)

#define o_type_specialize_traitsNTT(_namespaces_,_template_types_,_template_params_,_name_)  \
    o_reflection_specialize_type_name_of_helperNTT(_namespaces_,_template_types_,_template_params_,_name_) \
    o_reflection_specialize_template_specialization_adderNTT(_namespaces_,_template_types_,_template_params_,_name_)\
    o_traits_specializeNTT(is_template, (const static bool value = true), _namespaces_, _template_types_,_template_params_, _name_)

#define o_type_specialize_traitsNCTT(_namespaces_,_classes_,_template_types_,_template_params_,_name_)  \
    o_reflection_specialize_type_name_of_helperNCTT(_namespaces_,_classes_,_template_types_,_template_params_,_name_) \
    o_reflection_specialize_template_specialization_adderNCTT(_namespaces_,_classes_,_template_types_,_template_params_,_name_)\
    o_traits_specializeNCTT(is_template, (const static bool value = true), _namespaces_, _classes_, _template_types_,_template_params_, _name_)

#define o_type_specialize_traitsTTS(_template_types_,_template_params_,_name_,_supers_)  \
    o_reflection_specialize_type_name_of_helperTT(_template_types_,_template_params_,_name_) \
    o_reflection_specialize_template_specialization_adderTT(_template_types_,_template_params_,_name_)\
    o_traits_specialize_all_super_traitTTS(_template_types_,_template_params_, _name_,_supers_)\
    o_traits_specializeTT(is_template, (const static bool value = true), _template_types_,_template_params_, _name_)

#define o_type_specialize_traitsCTTS(_classes_,_template_types_,_template_params_,_name_,_supers_)  \
    o_reflection_specialize_type_name_of_helperCTT(_classes_,_template_types_,_template_params_,_name_) \
    o_reflection_specialize_template_specialization_adderCTT(_classes_,_template_types_,_template_params_,_name_)\
    o_traits_specialize_all_super_traitCTTS(_classes_,_template_types_,_template_params_, _name_,_supers_)\
    o_traits_specializeCTT(is_template, (const static bool value = true), _classes_, _template_types_,_template_params_, _name_)

#define o_type_specialize_traitsTT(_template_types_,_template_params_,_name_)  \
    o_reflection_specialize_type_name_of_helperTT(_template_types_,_template_params_,_name_) \
    o_reflection_specialize_template_specialization_adderTT(_template_types_,_template_params_,_name_)\
    o_traits_specializeTT(is_template, (const static bool value = true), _template_types_,_template_params_, _name_)

#define o_type_specialize_traitsNS(_namespaces_,_name_,_supers_)  \
    o_reflection_specialize_type_name_of_helperN(_namespaces_,_name_) \
    o_traits_specialize_all_super_traitNS(_namespaces_,_name_,_supers_)

#define o_type_specialize_traitsN(_namespaces_,_name_)  \
    o_reflection_specialize_type_name_of_helperN(_namespaces_,_name_) 

#define o_type_specialize_traitsC(_classes_,_name_)  \
    o_reflection_specialize_type_name_of_helperC(_classes_,_name_) 
    
#define o_type_specialize_traitsNC(_namespaces_,_classes_,_name_)  \
    o_reflection_specialize_type_name_of_helperNC(_namespaces_,_classes_,_name_) 

#define o_type_specialize_traitsNCS(_namespaces_,_classes_,_name_,_supers_)  \
    o_reflection_specialize_type_name_of_helperNC(_namespaces_,_classes_,_name_) \
    o_traits_specialize_all_super_traitNS(_namespaces_, _name_,_supers_)

#define o_type_specialize_traitsS(_name_, _supers_)  \
    o_reflection_specialize_type_name_of_helper(_name_) \
    o_traits_specialize_all_super_traitS(_name_,_supers_)

#define o_type_specialize_traits(_name_)  \
    o_reflection_specialize_type_name_of_helper(_name_) 

#define o_class(_name_,...) \
    o_reflection_specialize_type_name_of_forward_helper(_name_)\
    o_type_specialize_traits(_name_) \
    o_traits_specialize(meta_specifiers, (enum {value = phantom::detail::int_embedder<__VA_ARGS__>::value};), _name_)\
    o_class_module(_name_)

#define o_classC(_classes_,_name_,...) \
    o_reflection_specialize_type_name_of_forward_helperC(_classes_, _name_)\
    o_type_specialize_traitsC(_classes_,_name_) \
    o_traits_specializeC(meta_specifiers, (enum {value = phantom::detail::int_embedder<__VA_ARGS__>::value};), _classes_, _name_)\
    o_class_moduleC(_classes_,_name_)

#define o_classN(_namespaces_,_name_,...) \
    o_reflection_specialize_type_name_of_forward_helperN(_namespaces_,_name_)\
    o_type_specialize_traitsN(_namespaces_,_name_) \
    o_traits_specializeN(meta_specifiers, (enum {value = phantom::detail::int_embedder<__VA_ARGS__>::value};), _namespaces_, _name_)\
    o_class_moduleN(_namespaces_,_name_)

#define o_classNC(_namespaces_,_classes_,_name_,...) \
    o_reflection_specialize_type_name_of_forward_helperNC(_namespaces_,_classes_,_name_)\
    o_type_specialize_traitsNC(_namespaces_,_classes_,_name_) \
    o_traits_specializeNC(meta_specifiers, (enum {value = phantom::detail::int_embedder<__VA_ARGS__>::value};), _namespaces_, _classes_, _name_)\
    o_class_moduleNC(_namespaces_,_classes_,_name_)

#define o_classS(_name_,_supers_,...) \
    o_reflection_specialize_type_name_of_forward_helper(_name_)\
    o_type_specialize_traitsS(_name_,_supers_) \
    o_traits_specialize(meta_specifiers, (enum {value = phantom::detail::int_embedder<__VA_ARGS__>::value};), _name_)\
    o_class_module(_name_)

#define o_classT(_template_types_,_template_params_,_name_,...) \
    o_reflection_specialize_type_name_of_forward_helperTT(_template_types_,_template_params_,_name_)\
    o_type_specialize_traitsTT(_namespaces_,_template_types_,_template_params_,_name_) \
    o_traits_specializeTT(meta_specifiers, (enum {value = phantom::detail::int_embedder<__VA_ARGS__>::value};), _template_types_,_template_params_, _name_)\
    o_class_moduleTT(_template_types_,_template_params_,_name_)

#define o_classTS(_template_types_,_template_params_,_name_,_supers_,...) \
    o_reflection_specialize_type_name_of_forward_helperTT(_template_types_,_template_params_,_name_)\
    o_type_specialize_traitsTTS(_template_types_,_template_params_,_name_,_supers_) \
    o_traits_specialize(meta_specifiers, (enum {value = phantom::detail::int_embedder<__VA_ARGS__>::value};), _template_types_,_template_params_, _name_)\
    o_class_moduleTT(_template_types_,_template_params_,_name_)

#define o_classNT(_namespaces_,_template_types_,_template_params_,_name_,...) \
    o_reflection_specialize_type_name_of_forward_helperNTT(_namespaces_,_template_types_,_template_params_,_name_)\
    o_type_specialize_traitsNTT(_namespaces_,_template_types_,_template_params_,_name_) \
    o_traits_specializeNTT(meta_specifiers, (enum {value = phantom::detail::int_embedder<__VA_ARGS__>::value};), _namespaces_, _template_types_,_template_params_, _name_)\
    o_class_moduleNTT(_namespaces_,_template_types_,_template_params_,_name_)

#define o_classNTS(_namespaces_,_template_types_,_template_params_,_name_,_supers_,...) \
    o_reflection_specialize_type_name_of_forward_helperNTT(_namespaces_,_template_types_,_template_params_,_name_)\
    o_type_specialize_traitsNTTS(_namespaces_,_template_types_,_template_params_,_name_,_supers_) \
    o_traits_specializeNTT(meta_specifiers, (enum {value = phantom::detail::int_embedder<__VA_ARGS__>::value};), _namespaces_, _template_types_,_template_params_, _name_)\
    o_class_moduleNTT(_namespaces_,_template_types_,_template_params_,_name_)

#define o_classNCS(_namespaces_,_classes_,_name_,_supers_,...) \
    o_reflection_specialize_type_name_of_forward_helperNC(_namespaces_,_classes_,_name_)\
    o_type_specialize_traitsNCS(_namespaces_,_classes_,_name_,_supers_) \
    o_traits_specializeNC(meta_specifiers, (enum {value = phantom::detail::int_embedder<__VA_ARGS__>::value};), _namespaces_, _classes_, _name_)\
    o_class_moduleNC(_namespaces_,_classes_,_name_)

#define o_classNS(_namespaces_,_name_,_supers_,...) \
    o_reflection_specialize_type_name_of_forward_helperN(_namespaces_,_name_)\
    o_type_specialize_traitsNS(_namespaces_,_name_,_supers_) \
    o_traits_specializeN(meta_specifiers, (enum {value = phantom::detail::int_embedder<__VA_ARGS__>::value};), _namespaces_, _name_)\
    o_class_moduleN(_namespaces_,_name_)

#define o_register(_name_)\
    phantom::detail::dynamic_initializer_module_installer_registrer< ::_name_ > o_PP_CAT(g_register_module_, o_PP_CAT(_name_, __COUNTER__)) ;

#define o_registerN(_namespaces_,_name_)\
    phantom::detail::dynamic_initializer_module_installer_registrer< o_PP_CREATE_QUALIFIED_NAME(_namespaces_,_name_) > o_PP_CAT(g_register_module_, o_PP_CAT(_name_, __COUNTER__)) ;

#define o_registerC(_classes_,_name_)\
    phantom::detail::dynamic_initializer_module_installer_registrer< o_PP_CREATE_QUALIFIED_NAME(_classes_,_name_) > o_PP_CAT(g_register_module_, o_PP_CAT(_name_, __COUNTER__)) ;

#define o_registerNC(_namespaces_,_classes_,_name_)\
    phantom::detail::dynamic_initializer_module_installer_registrer< o_PP_CREATE_QUALIFIED_NAME_2(_namespaces_,_classes_,_name_) > o_PP_CAT(g_register_module_, o_PP_CAT(_name_, __COUNTER__)) ;

#define o_reflection_custom_begin(_type_)    \
    protected:\
    enum { PHANTOM_CODEGEN_reflection_counter_value = __COUNTER__};\
    public: \
    typedef _type_ enclosed_reflection_declaration; \
    class enclosed_reflection : public phantom::reflection::detail::phantom_base_enclosed_reflection<_type_>\
    {\
        typedef _type_ phantom_proxy_generator_reflection_self_type; \
        typedef _type_ phantom_proxy_generator_reflection_proxy_type;\

#define o_reflection_custom_end()    \
    };


#define o_reflection_custom_declare(_type_)\
    protected:\
                  enum { PHANTOM_CODEGEN_reflection_counter_value = __COUNTER__};\
    public: \
            typedef _type_ enclosed_reflection_declaration; \
              class enclosed_reflection;

#define o_reflection    \
    protected:\
    enum { PHANTOM_CODEGEN_reflection_counter_value = __COUNTER__};\
    public: \
    typedef phantom_proxy_generator_reflection_self_type enclosed_reflection_declaration; \
    class enclosed_reflection : public phantom::reflection::detail::phantom_base_enclosed_reflection<phantom_proxy_generator_reflection_self_type>

#define o_statechart_custom(id)    \
    public: \
    typedef phantom_proxy_generator_statechart_self_type_##id enclosed_statechart_declaration; \
    enum { phantom_proxy_generator_track_counter_base_value = __COUNTER__ };\
    template<typename t_PHANTOM_RESERVED_statechart_objectclass> class enclosed_statechart \
    : public phantom::super_statechart<phantom_proxy_generator_statechart_self_type_##id, t_PHANTOM_RESERVED_statechart_objectclass>

#define o_statechart    \
    public: \
    typedef phantom_proxy_generator_statechart_self_type enclosed_statechart_declaration; \
    enum { phantom_proxy_generator_track_counter_base_value = __COUNTER__ };\
    template<typename t_PHANTOM_RESERVED_statechart_objectclass> class enclosed_statechart \
    : public phantom::super_statechart<phantom_proxy_generator_statechart_self_type, t_PHANTOM_RESERVED_statechart_objectclass>

#define o_class_moduleNTT(_namespaces_,_template_types_,_template_params_,_name_)\
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
class :: o_PP_CREATE_SCOPE _namespaces_::phantom_proxy_____##_name_<o_PP_CREATE_QUALIFIED_NAME(_namespaces_,_name_) < o_PP_IDENTITY _template_params_ > >\
    : public o_PP_CREATE_QUALIFIED_NAME(_namespaces_,_name_)< o_PP_IDENTITY _template_params_ >\
    , public phantom_proxy_generator_base_____<o_PP_CREATE_QUALIFIED_NAME(_namespaces_,_name_)< o_PP_IDENTITY _template_params_ >, :: o_PP_CREATE_SCOPE _namespaces_::phantom_proxy_____##_name_<o_PP_CREATE_QUALIFIED_NAME(_namespaces_,_name_) < o_PP_IDENTITY _template_params_ > > >

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
    class :: o_PP_CREATE_SCOPE _namespaces_::phantom_proxy_____##_name_< o_PP_CREATE_QUALIFIED_NAME(_namespaces_,_name_) > \
    : public o_PP_CREATE_QUALIFIED_NAME(_namespaces_,_name_)\
    , public phantom_proxy_generator_base_____< o_PP_CREATE_QUALIFIED_NAME(_namespaces_,_name_), :: o_PP_CREATE_SCOPE _namespaces_::phantom_proxy_____##_name_< o_PP_CREATE_QUALIFIED_NAME(_namespaces_,_name_) > >

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
    , public phantom_proxy_generator_base_____<o_PP_CREATE_QUALIFIED_NAME(_namespaces_,_name_), phantom_proxy_____##_name_<o_PP_CREATE_QUALIFIED_NAME(_classes_,_name_) >>

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
    class :: o_PP_CREATE_SCOPE _namespaces_::phantom_proxy_____##_name_< o_PP_CREATE_QUALIFIED_NAME_2(_namespaces_,_classes_,_name_) > \
    : public o_PP_CREATE_QUALIFIED_NAME_2(_namespaces_,_classes_,_name_), \
    public phantom_proxy_generator_base_____<o_PP_CREATE_QUALIFIED_NAME_2(_namespaces_,_classes_,_name_), :: o_PP_CREATE_SCOPE _namespaces_::phantom_proxy_____##_name_< o_PP_CREATE_QUALIFIED_NAME_2(_namespaces_,_classes_,_name_) >>

#define o_class_moduleTT(_template_types_,_template_params_,_name_)\
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
    , public phantom_proxy_generator_base_____< ::_name_ < o_PP_IDENTITY _template_params_ >, ::phantom_proxy_____##_name_< ::_name_ < o_PP_IDENTITY _template_params_ > > >

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
    , public phantom_proxy_generator_base_____< ::_name_, phantom_proxy_____##_name_< ::_name_ >>

#define o_enum_module(_name_, _values_)\
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
    class phantom_proxy_____##_name_< ::_name_ >\
    {\
    typedef ::_name_ phantom_proxy_generator_reflection_self_type;\
        o_reflection {\
            struct o_PP_CAT(_name_,__LINE__) \
            {\
                typedef phantom_proxy_generator_reflection_self_type enum_value_type;\
                o_PP_CAT(_name_,__LINE__)() \
                {\
                    phantom::reflection::Enum* pEnum = phantom::typeOf<phantom_proxy_generator_reflection_self_type>();\
                    o_enum_add_values _values_\
                }\
            }o_PP_CAT(o_PP_CAT(_name_,__LINE__),_instance);\
        };\
    };

#define o_enum_moduleC(_classes_, _name_, _values_)\
    template<typename t_Ty>\
    class phantom_proxy_____##_name_;\
    namespace phantom {\
    template<>\
    struct proxy_of< o_PP_CREATE_QUALIFIED_NAME(_classes_,_name_)>\
    {\
        typedef ::phantom_proxy_____##_name_<o_PP_CREATE_QUALIFIED_NAME(_classes_,_name_)> type;\
    };\
    }\
    template<>\
    class phantom_proxy_____##_name_< o_PP_CREATE_QUALIFIED_NAME(_classes_,_name_) > \
        : public o_PP_CREATE_SCOPE _classes_\
        , public phantom_proxy_generator_base_____< o_PP_CREATE_SCOPE _classes_, phantom_proxy_____##_name_< o_PP_CREATE_QUALIFIED_NAME(_classes_,_name_) > >\
    {\
    typedef o_PP_CREATE_QUALIFIED_NAME(_classes_, _name_) phantom_proxy_generator_reflection_self_type;\
        o_reflection {\
        struct o_PP_CAT(_name_,__LINE__) \
        {\
            o_PP_CAT(_name_,__LINE__)() \
            {\
                typedef phantom_proxy_generator_reflection_self_type enum_value_type;\
                phantom::reflection::Enum* pEnum = phantom::typeOf< phantom_proxy_generator_reflection_self_type >();\
                o_enum_add_values _values_\
            }\
        }o_PP_CAT(o_PP_CAT(_name_,__LINE__),_instance);\
    };\
};

#if o_COMPILER == o_COMPILER_VISUAL_STUDIO
#define o_enum_moduleN(_namespaces_, _name_, _values_)\
    o_namespace_begin _namespaces_\
    template<typename t_Ty>\
    class phantom_proxy_____##_name_;\
    o_namespace_end _namespaces_\
    namespace phantom {\
    template<>\
    struct proxy_of< o_PP_CREATE_QUALIFIED_NAME(_namespaces_,_name_)>\
    {\
        typedef :: o_PP_CREATE_SCOPE _namespaces_::phantom_proxy_____##_name_<o_PP_CREATE_QUALIFIED_NAME(_namespaces_,_name_)> type;\
    };\
    }\
    template<>\
    class :: o_PP_CREATE_SCOPE _namespaces_::phantom_proxy_____##_name_<o_PP_CREATE_QUALIFIED_NAME(_namespaces_,_name_)> \
    {\
    typedef o_PP_CREATE_QUALIFIED_NAME(_namespaces_, _name_) phantom_proxy_generator_reflection_self_type;\
        o_reflection {\
            struct o_PP_CAT(_name_,__LINE__) \
            {\
                o_PP_CAT(_name_,__LINE__)() \
                {\
                    typedef phantom_proxy_generator_reflection_self_type enum_value_type;\
                    phantom::reflection::Enum* pEnum = phantom::typeOf< phantom_proxy_generator_reflection_self_type >();\
                    o_enum_add_valuesN o_PP_LEFT_PAREN _namespaces_, o_PP_IDENTITY _values_ o_PP_RIGHT_PAREN \
                }\
            } o_PP_CAT(o_PP_CAT(_name_,__LINE__),_instance);\
        };\
    };
#else
#define o_enum_moduleN(_namespaces_, _name_, _values_)\
    o_namespace_begin _namespaces_\
    template<typename t_Ty>\
    class phantom_proxy_____##_name_;\
    o_namespace_end _namespaces_\
    namespace phantom {\
    template<>\
    struct proxy_of< o_PP_CREATE_QUALIFIED_NAME(_namespaces_,_name_)>\
    {\
    typedef :: o_PP_CREATE_SCOPE _namespaces_::phantom_proxy_____##_name_<o_PP_CREATE_QUALIFIED_NAME(_namespaces_,_name_)> type;\
    };\
    }\
    template<>\
    class :: o_PP_CREATE_SCOPE _namespaces_::phantom_proxy_____##_name_<o_PP_CREATE_QUALIFIED_NAME(_namespaces_,_name_)> \
    {\
    typedef o_PP_CREATE_QUALIFIED_NAME(_namespaces_, _name_) phantom_proxy_generator_reflection_self_type;\
    o_reflection {\
    struct o_PP_CAT(_name_,__LINE__) \
            {\
            o_PP_CAT(_name_,__LINE__)() \
                {\
                typedef phantom_proxy_generator_reflection_self_type enum_value_type;\
                phantom::reflection::Enum* pEnum = phantom::typeOf< phantom_proxy_generator_reflection_self_type >();\
                o_enum_add_valuesN( _namespaces_, o_PP_IDENTITY _values_ ) \
                }\
            } o_PP_CAT(o_PP_CAT(_name_,__LINE__),_instance);\
        };\
    };

#endif

#define o_enum_moduleNC(_namespaces_, _classes_, _name_, _values_)\
    o_namespace_begin _namespaces_\
    template<typename t_Ty>\
    class phantom_proxy_____##_name_;\
    o_namespace_end _namespaces_\
    namespace phantom {\
    template<>\
    struct proxy_of< o_PP_CREATE_QUALIFIED_NAME_2(_namespaces_, _classes_,_name_)>\
    {\
        typedef :: o_PP_CREATE_SCOPE _namespaces_::phantom_proxy_____##_name_<o_PP_CREATE_QUALIFIED_NAME_2(_namespaces_, _classes_,_name_)> type;\
    };\
    }\
    template<>\
    class :: o_PP_CREATE_SCOPE _namespaces_::phantom_proxy_____##_name_<o_PP_CREATE_QUALIFIED_NAME_2(_namespaces_, _classes_,_name_)> \
    : public :: o_PP_CREATE_SCOPE  _namespaces_ :: o_PP_CREATE_SCOPE _classes_\
    , public phantom_proxy_generator_base_____< :: o_PP_CREATE_SCOPE  _namespaces_ :: o_PP_CREATE_SCOPE _classes_, :: o_PP_CREATE_SCOPE _namespaces_::phantom_proxy_____##_name_<o_PP_CREATE_QUALIFIED_NAME_2(_namespaces_, _classes_,_name_)>>\
    {\
        typedef o_PP_CREATE_QUALIFIED_NAME_2(_namespaces_, _classes_,_name_) phantom_proxy_generator_reflection_self_type;\
        o_reflection {\
            struct o_PP_CAT(_name_,__LINE__) \
            {\
                o_PP_CAT(_name_,__LINE__)() \
                {\
                    typedef phantom_proxy_generator_reflection_self_type enum_value_type;\
                    phantom::reflection::Enum* pEnum = phantom::typeOf< phantom_proxy_generator_reflection_self_type >();\
                    o_enum_add_values _values_\
                }\
            }o_PP_CAT(o_PP_CAT(_name_,__LINE__),_instance);\
        };\
    };


// Phantom methods
#define o_initialize()                  void PHANTOM_CODEGEN_initialize()
#define o_terminate()                   void PHANTOM_CODEGEN_terminate()
#define o_restore(filter,pass)          phantom::restore_state PHANTOM_CODEGEN_restore(phantom::uint filter, phantom::uint pass)

#define o_initialize_cpp(classname)                  void classname::PHANTOM_CODEGEN_initialize()
#define o_terminate_cpp(classname)                   void classname::PHANTOM_CODEGEN_terminate()
#define o_restore_cpp(classname,filter,pass)          phantom::restore_state classname::PHANTOM_CODEGEN_restore(phantom::uint filter, phantom::uint pass)


#define o_destroyed                         typedef int PHANTOM_CODEGEN_destroyed_marker; o_signal_data(PHANTOM_CODEGEN_destroyed)


#endif // o_phantom_modules__