#ifndef o_phantom_modules__
#define o_phantom_modules__

#define o_anonymous_enum(_values_) 
#define o_anonymous_enumN(_namespaces_,_values_) 
#define o_anonymous_enumNT(_namespaces_,_template_types_,_template_params_,_values_) 
#define o_anonymous_enumT(_template_types_,_template_params_,_values_) 
#define o_anonymous_enumC(_classes_,_values_) 
#define o_anonymous_enumCT(_classes_,_template_types_,_template_params_,_values_) 
#define o_anonymous_enumNC(_namespaces_,_classes_,_values_) 
#define o_anonymous_enumNCT(_namespaces_,_classes_,_template_types_,_template_params_,_values_) 

#define o_expose(_name_) /*\
    o_reflection_specialize_type_of(_name_)\
    o_reflection_specialize_type_name_of(_name_)*/

#define o_exposeN(_namespaces_,_name_) /*\
    o_reflection_specialize_type_ofN(_namespaces_,_name_)\
    o_reflection_specialize_type_name_ofN(_namespaces_,_name_)*/

#define o_exposeNT(_namespaces_,_template_types_,_template_params_,_name_) /*\
    o_reflection_specialize_type_ofNT(_namespaces_,_template_types_,_template_params_,_name_)\
    o_reflection_specialize_type_name_ofNT(_namespaces_,_template_types_,_template_params_,_name_)*/

#define o_exposeT(_template_types_,_template_params_,_name_) /*\
    o_reflection_specialize_type_ofT(_template_types_,_template_params_,_name_)\
    o_reflection_specialize_type_name_ofT(_template_types_,_template_params_,_name_)*/

#define o_exposeC(_classes_,_name_) /*\
    o_reflection_specialize_type_ofC(_classes_,_name_)\
    o_reflection_specialize_type_name_ofC(_classes_,_name_)*/

#define o_exposeCT(_classes_,_template_types_,_template_params_,_name_) /*\
    o_reflection_specialize_type_ofCT(_classes_,_template_types_,_template_params_,_name_)\
    o_reflection_specialize_type_name_ofCT(_classes_,_template_types_,_template_params_,_name_)*/

#define o_exposeNC(_namespaces_,_classes_,_name_) /*\
    o_reflection_specialize_type_ofNC(_namespaces_,_classes_,_name_)\
    o_reflection_specialize_type_name_ofNC(_namespaces_,_classes_,_name_)*/

#define o_exposeNCT(_namespaces_,_classes_,_template_types_,_template_params_,_name_) /*\
    o_reflection_specialize_type_ofNCT(_namespaces_,_classes_,_template_types_,_template_params_,_name_)\
    o_reflection_specialize_type_name_ofNCT(_namespaces_,_classes_,_template_types_,_template_params_,_name_)*/


#define o_enum(_name_,_values_) \
    o_inc_compilation_counter\
    o_type_specialize_traits(_name_) \
    o_enum_module(_name_,_values_)\

#define o_enumN(_namespaces_,_name_,_values_) \
    o_inc_compilation_counter\
     o_type_specialize_traitsN(_namespaces_,_name_) \
     o_enum_moduleN(_namespaces_,_name_,_values_)\

#define o_enumC(_classes_,_name_,_values_) \
    o_inc_compilation_counter\
    o_type_specialize_traitsC(_classes_,_name_) \
    o_enum_moduleC(_classes_,_name_,_values_)\

#define o_enumNC(_namespaces_,_classes_,_name_,_values_) \
    o_inc_compilation_counter\
    o_type_specialize_traitsNC(_namespaces_,_classes_,_name_) \
    o_enum_moduleNC(_namespaces_,_classes_,_name_,_values_)\

#define o_type_specialize_traitsNT(_namespaces_,_template_types_,_template_params_,_name_)  \
    o_traits_specializeNT(has_module, (const static bool value = true), _namespaces_, _template_types_,_template_params_, _name_)\
    o_reflection_specialize_type_name_of_implNT(_namespaces_,_template_types_,_template_params_,_name_) \
    o_reflection_specialize_type_ofNT(_namespaces_,_template_types_,_template_params_,_name_)\
    o_reflection_specialize_template_specialization_adderNT(_namespaces_,_template_types_,_template_params_,_name_)\
    o_traits_specializeNT(is_template, (const static bool value = true), _namespaces_, _template_types_,_template_params_, _name_)
/*

#define o_type_specialize_traitsNTC(_namespaces_,_template_types_,_template_params_,_name_)  \
    o_traits_specializeNTC(has_module, (const static bool value = true), _namespaces_, _template_types_,_template_params_, _class_, _name_)\
    o_reflection_specialize_type_name_of_implNTC(_namespaces_,_template_types_,_template_params_, _class_,_name_) \
    o_reflection_specialize_type_ofNTC(_namespaces_,_template_types_,_template_params_, _class_,_name_)\
    o_traits_specializeNTC(is_template, (const static bool value = true), _namespaces_, _template_types_,_template_params_, _class_, _name_)
*/

#define o_type_specialize_traitsNTS(_namespaces_,_template_types_,_template_params_,_name_,_supers_)  \
    o_traits_specializeNT(has_module, (const static bool value = true), _namespaces_, _template_types_,_template_params_, _name_)\
    o_reflection_specialize_type_name_of_implNT(_namespaces_,_template_types_,_template_params_,_name_) \
    o_reflection_specialize_type_ofNT(_namespaces_,_template_types_,_template_params_,_name_)\
    o_reflection_specialize_template_specialization_adderNT(_namespaces_,_template_types_,_template_params_,_name_)\
    o_traits_specialize_all_super_traitNTS(_namespaces_, _template_types_,_template_params_, _name_,_supers_)\
    o_traits_specializeNT(is_template, (const static bool value = true), _namespaces_, _template_types_,_template_params_, _name_)

#define o_type_specialize_traitsCT(_classes_,_template_types_,_template_params_,_name_)  \
    o_traits_specializeCT(has_module, (const static bool value = true), _classes_, _template_types_,_template_params_, _name_)\
    o_reflection_specialize_type_name_of_implCT(_classes_,_template_types_,_template_params_,_name_) \
    o_reflection_specialize_type_ofCT(_classes_,_template_types_,_template_params_,_name_)\
    o_reflection_specialize_template_specialization_adderCT(_classes_,_template_types_,_template_params_,_name_)\
    o_traits_specializeCT(is_template, (const static bool value = true), _classes_, _template_types_,_template_params_, _name_)

#define o_type_specialize_traitsCTS(_classes_,_template_types_,_template_params_,_name_,_supers_)  \
    o_traits_specializeCT(has_module, (const static bool value = true), _classes_, _template_types_,_template_params_, _name_)\
    o_reflection_specialize_type_name_of_implCT(_classes_,_template_types_,_template_params_,_name_) \
    o_reflection_specialize_type_ofCT(_classes_,_template_types_,_template_params_,_name_)\
    o_reflection_specialize_template_specialization_adderCT(_classes_,_template_types_,_template_params_,_name_)\
    o_traits_specialize_all_super_traitCTS(_classes_,_template_types_,_template_params_, _name_,_supers_)\
    o_traits_specializeCT(is_template, (const static bool value = true), _classes_, _template_types_,_template_params_, _name_)

#define o_type_specialize_traitsNCT(_namespaces_,_classes_,_template_types_,_template_params_,_name_)  \
    o_traits_specializeNCT(has_module, (const static bool value = true), _namespaces_, _classes_, _template_types_,_template_params_, _name_)\
    o_reflection_specialize_type_name_of_implNCT(_namespaces_,_classes_,_template_types_,_template_params_,_name_) \
    o_reflection_specialize_type_ofNCT(_namespaces_,_classes_,_template_types_,_template_params_,_name_)\
    o_reflection_specialize_template_specialization_adderNCT(_namespaces_,_classes_,_template_types_,_template_params_,_name_)\
    o_traits_specializeNCT(is_template, (const static bool value = true), _namespaces_, _classes_, _template_types_,_template_params_, _name_)

#define o_type_specialize_traitsNCTS(_namespaces_,_classes_,_template_types_,_template_params_,_name_, _supers_)  \
    o_traits_specializeNCT(has_module, (const static bool value = true), _namespaces_, _classes_, _template_types_,_template_params_, _name_)\
    o_reflection_specialize_type_name_of_implNCT(_namespaces_,_classes_,_template_types_,_template_params_,_name_) \
    o_reflection_specialize_type_ofNCT(_namespaces_,_classes_,_template_types_,_template_params_,_name_)\
    o_reflection_specialize_template_specialization_adderNCT(_namespaces_,_classes_,_template_types_,_template_params_,_name_)\
    o_traits_specialize_all_super_traitNCTS(_namespaces_,_classes_,_template_types_,_template_params_, _name_,_supers_)\
    o_traits_specializeNCT(is_template, (const static bool value = true), _namespaces_, _classes_, _template_types_,_template_params_, _name_)

#define o_type_specialize_traitsT(_template_types_,_template_params_,_name_)  \
    o_traits_specializeT(has_module, (const static bool value = true), _template_types_,_template_params_, _name_)\
    o_reflection_specialize_type_name_of_implT(_template_types_,_template_params_,_name_) \
    o_reflection_specialize_type_ofT(_template_types_,_template_params_,_name_)\
    o_reflection_specialize_template_specialization_adderT(_template_types_,_template_params_,_name_)\
    o_traits_specializeT(is_template, (const static bool value = true), _template_types_,_template_params_, _name_)

#define o_type_specialize_traitsTS(_template_types_,_template_params_,_name_,_supers_)  \
    o_traits_specializeT(has_module, (const static bool value = true), _template_types_,_template_params_, _name_)\
    o_reflection_specialize_type_name_of_implT(_template_types_,_template_params_,_name_) \
    o_reflection_specialize_type_ofT(_template_types_,_template_params_,_name_)\
    o_reflection_specialize_template_specialization_adderT(_template_types_,_template_params_,_name_)\
    o_traits_specialize_all_super_traitTS(_template_types_,_template_params_, _name_,_supers_)\
    o_traits_specializeT(is_template, (const static bool value = true), _template_types_,_template_params_, _name_)

#define o_type_specialize_traitsN(_namespaces_,_name_)  \
    o_traits_specializeN(has_module, (const static bool value = true), _namespaces_, _name_)\
    o_reflection_specialize_type_name_of_implN(_namespaces_,_name_) \
    o_reflection_specialize_type_ofN(_namespaces_,_name_)

#define o_type_specialize_traitsNS(_namespaces_,_name_,_supers_)  \
    o_traits_specializeN(has_module, (const static bool value = true), _namespaces_, _name_)\
    o_reflection_specialize_type_name_of_implN(_namespaces_,_name_) \
    o_reflection_specialize_type_ofN(_namespaces_,_name_)\
    o_traits_specialize_all_super_traitNS(_namespaces_,_name_,_supers_)

#define o_type_specialize_traitsC(_classes_,_name_)  \
    o_traits_specializeN(has_module, (const static bool value = true), _classes_, _name_)\
    o_reflection_specialize_type_name_of_implC(_classes_,_name_) \
    o_reflection_specialize_type_ofC(_classes_,_name_)

#define o_type_specialize_traitsCS(_classes_,_name_)  \
    o_traits_specializeN(has_module, (const static bool value = true), _classes_, _name_)\
    o_reflection_specialize_type_name_of_implC(_classes_,_name_) \
    o_reflection_specialize_type_ofC(_classes_,_name_)\
    o_traits_specialize_all_super_traitS(_name_,_supers_)

#define o_type_specialize_traitsNC(_namespaces_,_classes_,_name_)  \
    o_traits_specializeNC(has_module, (const static bool value = true), _namespaces_,_classes_, _name_)\
    o_reflection_specialize_type_name_of_implNC(_namespaces_,_classes_,_name_) \
    o_reflection_specialize_type_ofNC(_namespaces_,_classes_,_name_)

#define o_type_specialize_traitsNCS(_namespaces_,_classes_,_name_,_supers_)  \
    o_traits_specializeNC(has_module, (const static bool value = true), _namespaces_,_classes_, _name_)\
    o_reflection_specialize_type_name_of_implNC(_namespaces_,_classes_,_name_) \
    o_reflection_specialize_type_ofNC(_namespaces_,_classes_,_name_)\
    o_traits_specialize_all_super_traitNCS(_namespaces_, _classes_,_name_,_supers_)

#define o_type_specialize_traitsS(_name_, _supers_)  \
    o_traits_specialize(has_module, (const static bool value = true), _name_)\
    o_reflection_specialize_type_name_of_impl(_name_) \
    o_reflection_specialize_type_of(_name_)\
    o_traits_specialize_all_super_traitS(_name_,_supers_)

#define o_type_specialize_traits(_name_)  \
    o_traits_specialize(has_module, (const static bool value = true), _name_)\
    o_reflection_specialize_type_name_of_impl(_name_) \
    o_reflection_specialize_type_of(_name_)


#if o_COMPILER == o_COMPILER_VISUAL_STUDIO
#define o_declare( ... ) o_PP_CAT(o_PP_CAT(o_declare_, o_PP_NARG(__VA_ARGS__)),(__VA_ARGS__) )
#define o_declareN( ... ) o_PP_CAT(o_PP_CAT(o_declareN_, o_PP_NARG(__VA_ARGS__)),(__VA_ARGS__) )
#define o_declareC( ... ) o_PP_CAT(o_PP_CAT(o_declareC_, o_PP_NARG(__VA_ARGS__)),(__VA_ARGS__) )
#define o_declareNC( ... ) o_PP_CAT(o_PP_CAT(o_declareNC_, o_PP_NARG(__VA_ARGS__)),(__VA_ARGS__) )
#define o_declareT( ... ) o_PP_CAT(o_PP_CAT(o_declareT_, o_PP_NARG(__VA_ARGS__)),(__VA_ARGS__) )
#define o_declareNT( ... ) o_PP_CAT(o_PP_CAT(o_declareNT_, o_PP_NARG(__VA_ARGS__)),(__VA_ARGS__) )
#define o_declareTC( ... ) o_PP_CAT(o_PP_CAT(o_declareT_, o_PP_NARG(__VA_ARGS__)),(__VA_ARGS__) )
//#define o_declareNTC( ... ) o_PP_CAT(o_PP_CAT(o_declareNTC_, o_PP_NARG(__VA_ARGS__)),(__VA_ARGS__) )
#else
#define o_declare( ... ) o_PP_CAT(o_declare_, o_PP_NARG(__VA_ARGS__)) (__VA_ARGS__) 
#define o_declareN( ... ) o_PP_CAT(o_declareN_, o_PP_NARG(__VA_ARGS__)) (__VA_ARGS__) 
#define o_declareC( ... ) o_PP_CAT(o_declareC_, o_PP_NARG(__VA_ARGS__)) (__VA_ARGS__) 
#define o_declareNC( ... ) o_PP_CAT(o_declareNC_, o_PP_NARG(__VA_ARGS__)) (__VA_ARGS__) 
#define o_declareT( ... ) o_PP_CAT(o_declareT_, o_PP_NARG(__VA_ARGS__)) (__VA_ARGS__) 
#define o_declareNT( ... ) o_PP_CAT(o_declareNT_, o_PP_NARG(__VA_ARGS__)) (__VA_ARGS__) 
#define o_declareTC( ... ) o_PP_CAT(o_declareCT_, o_PP_NARG(__VA_ARGS__)) (__VA_ARGS__) 
//#define o_declareNTC( ... ) o_PP_CAT(o_declareNTC_, o_PP_NARG(__VA_ARGS__)) (__VA_ARGS__) 
#endif

#define o_declare_1(_name_) \
    o_inc_compilation_counter\
    o_reflection_specialize_type_name_of_counter(_name_)

#define o_declare_2(_type_, _name_) \
    o_inc_compilation_counter\
    _type_ _name_;\
    o_reflection_specialize_type_name_of_counter(_name_)

#define o_declareN_2(_namespaces_, _name_) \
    o_inc_compilation_counter\
    o_reflection_specialize_type_name_of_counterN(_namespaces_, _name_)

#define o_declareN_3(_type_, _namespaces_, _name_) \
    o_inc_compilation_counter\
    o_namespace_begin _namespaces_\
        _type_ _name_;\
    o_namespace_end _namespaces_\
    o_reflection_specialize_type_name_of_counterN(_namespaces_, _name_)

#define o_declareC_2(_classes_, _name_) \
    o_inc_compilation_counter\
    o_reflection_specialize_type_name_of_counterC(_classes_, _name_)

#define o_declareNC_3(_namespaces_, _classes_, _name_) \
    o_inc_compilation_counter\
    o_reflection_specialize_type_name_of_counterNC(_namespaces_, _classes_, _name_)

#define o_declareT_4(_type_, _namespaces_, _template_types_,_template_params_, _name_) \
    o_inc_compilation_counter\
    o_reflection_specialize_type_name_of_counterT(_template_types_,_template_params_, _name_)

#define o_declareT_5(_type_, _namespaces_, _template_types_,_template_params_, _name_) \
    o_inc_compilation_counter\
    template<o_PP_MIX(_template_types_,_template_params_)> _type_ _name_;\
    o_reflection_specialize_type_name_of_counterT(_template_types_,_template_params_, _name_)

#define o_declareNT_4(_namespaces_, _template_types_,_template_params_, _name_) \
    o_inc_compilation_counter\
    o_reflection_specialize_type_name_of_counterNT(_namespaces_, _template_types_,_template_params_, _name_)

#define o_declareNT_5(_type_, _namespaces_, _template_types_,_template_params_, _name_) \
    o_inc_compilation_counter\
    o_namespace_begin _namespaces_\
    template<o_PP_MIX(_template_types_,_template_params_)> _type_ _name_;\
    o_namespace_end _namespaces_\
        o_reflection_specialize_type_name_of_counterNT(_namespaces_, _template_types_,_template_params_, _name_)

// #define o_declareNTC_5(_namespaces_, _template_types_,_template_params_, _class_, _name_) \
//     o_inc_compilation_counter\
//     o_reflection_specialize_type_name_of_counterNTC(_namespaces_, _template_types_,_template_params_, _class_, _name_)

#define o_class(_name_,...) \
    o_inc_compilation_counter\
    o_type_specialize_traits(_name_) \
    o_traits_specialize(meta_specifiers, (enum {value = phantom::detail::int_embedder<__VA_ARGS__>::value};), _name_)\
    o_class_module(_name_)

#define o_classC(_classes_,_name_,...) \
    o_inc_compilation_counter\
    o_type_specialize_traitsC(_classes_,_name_) \
    o_traits_specializeC(meta_specifiers, (enum {value = phantom::detail::int_embedder<__VA_ARGS__>::value};), _classes_, _name_)\
    o_class_moduleC(_classes_,_name_)
    
#define o_classN(_namespaces_,_name_,...) \
    o_inc_compilation_counter\
    o_type_specialize_traitsN(_namespaces_,_name_) \
    o_traits_specializeN(meta_specifiers, (enum {value = phantom::detail::int_embedder<__VA_ARGS__>::value};), _namespaces_, _name_)\
    o_class_moduleN(_namespaces_,_name_)

#define o_classNC(_namespaces_,_classes_,_name_,...) \
    o_inc_compilation_counter\
    o_type_specialize_traitsNC(_namespaces_,_classes_,_name_) \
    o_traits_specializeNC(meta_specifiers, (enum {value = phantom::detail::int_embedder<__VA_ARGS__>::value};), _namespaces_, _classes_, _name_)\
    o_class_moduleNC(_namespaces_,_classes_,_name_)

#define o_classS(_name_,_supers_,...) \
    o_inc_compilation_counter\
    o_type_specialize_traitsS(_name_,_supers_) \
    o_traits_specialize(meta_specifiers, (enum {value = phantom::detail::int_embedder<__VA_ARGS__>::value};), _name_)\
    o_class_module(_name_)

#define o_classT(_template_types_,_template_params_,_name_,...) \
    o_inc_compilation_counter\
    o_type_specialize_traitsT(_template_types_,_template_params_,_name_) \
    o_traits_specializeT(meta_specifiers, (enum {value = phantom::detail::int_embedder<__VA_ARGS__>::value};), _template_types_,_template_params_, _name_)\
    o_class_moduleT(_template_types_,_template_params_,_name_)

#define o_classTS(_template_types_,_template_params_,_name_,_supers_,...) \
    o_inc_compilation_counter\
    o_type_specialize_traitsTS(_template_types_,_template_params_,_name_,_supers_) \
    o_traits_specialize(meta_specifiers, (enum {value = phantom::detail::int_embedder<__VA_ARGS__>::value};), _template_types_,_template_params_, _name_)\
    o_class_moduleT(_template_types_,_template_params_,_name_)

#define o_classNT(_namespaces_,_template_types_,_template_params_,_name_,...) \
    o_inc_compilation_counter\
    o_type_specialize_traitsNT(_namespaces_,_template_types_,_template_params_,_name_) \
    o_traits_specializeNT(meta_specifiers, (enum {value = phantom::detail::int_embedder<__VA_ARGS__>::value};), _namespaces_, _template_types_,_template_params_, _name_)\
    o_class_moduleNT(_namespaces_,_template_types_,_template_params_,_name_)

// #define o_classNTC(_namespaces_,_template_types_,_template_params_, _class_, _name_, ...) \
//     o_inc_compilation_counter\
//     o_type_specialize_traitsNTC(_namespaces_,_template_types_,_template_params_,_class_,_name_) \
//     o_traits_specializeNTC(meta_specifiers, (enum {value = phantom::detail::int_embedder<__VA_ARGS__>::value};), _namespaces_, _template_types_,_template_params_, _class_, _name_)\
//     o_class_moduleNTC(_namespaces_,_template_types_,_template_params_,_name_)

#define o_classNTS(_namespaces_,_template_types_,_template_params_,_name_,_supers_,...) \
    o_inc_compilation_counter\
    o_type_specialize_traitsNTS(_namespaces_,_template_types_,_template_params_,_name_,_supers_) \
    o_traits_specializeNT(meta_specifiers, (enum {value = phantom::detail::int_embedder<__VA_ARGS__>::value};), _namespaces_, _template_types_,_template_params_, _name_)\
    o_class_moduleNT(_namespaces_,_template_types_,_template_params_,_name_)

#define o_classNCS(_namespaces_,_classes_,_name_,_supers_,...) \
    o_inc_compilation_counter\
    o_type_specialize_traitsNCS(_namespaces_,_classes_,_name_,_supers_) \
    o_traits_specializeNC(meta_specifiers, (enum {value = phantom::detail::int_embedder<__VA_ARGS__>::value};), _namespaces_, _classes_, _name_)\
    o_class_moduleNC(_namespaces_,_classes_,_name_)

#define o_classNS(_namespaces_,_name_,_supers_,...) \
    o_inc_compilation_counter\
    o_type_specialize_traitsNS(_namespaces_,_name_,_supers_) \
    o_traits_specializeN(meta_specifiers, (enum {value = phantom::detail::int_embedder<__VA_ARGS__>::value};), _namespaces_, _name_)\
    o_class_moduleN(_namespaces_,_name_)

#define o_register_associated_templates(type)\
    o_register_associated_template_list o_PP_LEFT_PAREN o__list__registered_associated_templates(type) o_PP_RIGHT_PAREN

#if o_COMPILER == o_COMPILER_VISUAL_STUDIO
#   define o_register_associated_template_list(...) o_PP_CAT(o_PP_CAT(o_register_associated_template_list_,o_PP_NARG(__VA_ARGS__)),(__VA_ARGS__))
#else
#   define o_register_associated_template_list(...) o_PP_CAT(o_register_associated_template_list_,o_PP_NARG(__VA_ARGS__)) (__VA_ARGS__)
#endif

#define o_register_associated_template_list_1(t0) o_register(t0)
#define o_register_associated_template_list_2(t0, t1) o_register_associated_template_list_1(t0) o_register(t1)
#define o_register_associated_template_list_3(t0, t1, t2) o_register_associated_template_list_2(t0, t1) o_register(t2)
#define o_register_associated_template_list_4(t0, t1, t2, t3) o_register_associated_template_list_3(t0, t1, t2) o_register(t3)
#define o_register_associated_template_list_5(t0, t1, t2, t3, t4) o_register_associated_template_list_4(t0, t1, t2, t3) o_register(t4)


#define o_registerTI(_name_, _template_args_)\
    static phantom::detail::dynamic_initializer_module_installer_registrer< _name_<o_PP_IDENTITY _template_args_>, o_read_compilation_counter> o_PP_CAT(g_register_module_, __COUNTER__) ;

#define o_registerNTI(_namespaces_, _name_, _template_args_)\
    static phantom::detail::dynamic_initializer_module_installer_registrer< o_PP_CREATE_QUALIFIED_NAME(_namespaces_,_name_)<o_PP_IDENTITY _template_args_>, o_read_compilation_counter > o_PP_CAT(g_register_module_, __COUNTER__) ;

#define o_register(_name_)\
    static phantom::detail::dynamic_initializer_module_installer_registrer< _name_, o_read_compilation_counter > o_PP_CAT(g_register_module_, __COUNTER__) ;

#define o_registerN(_namespaces_, _name_)\
    static phantom::detail::dynamic_initializer_module_installer_registrer< o_PP_CREATE_QUALIFIED_NAME(_namespaces_,_name_), o_read_compilation_counter > o_PP_CAT(g_register_module_, o_PP_CAT(_name_, __COUNTER__)) ;

#define o_registerC(_classes_, _name_)\
    static phantom::detail::dynamic_initializer_module_installer_registrer< o_PP_CREATE_QUALIFIED_NAME(_classes_,_name_), o_read_compilation_counter> o_PP_CAT(g_register_module_, o_PP_CAT(_name_, __COUNTER__)) ;

#define o_registerNC(_namespaces_, _classes_, _name_)\
    static phantom::detail::dynamic_initializer_module_installer_registrer< o_PP_CREATE_QUALIFIED_NAME_2(_namespaces_,_classes_,_name_), o_read_compilation_counter > o_PP_CAT(g_register_module_, o_PP_CAT(_name_, __COUNTER__)) ;

#define o_registerT(_template_types_, _template_params_, _name_)\
    static phantom::detail::dynamic_initializer_template_registrer o_PP_CAT(g_register_template_, o_PP_CAT(_name_, __COUNTER__)) ("",  #_name_) ;

#define o_registerNT(_namespaces_, _template_types_, _template_params_, _name_)\
    static phantom::detail::dynamic_initializer_template_registrer o_PP_CAT(g_register_template_, o_PP_CAT(_name_, __COUNTER__)) (o_PP_QUOTE(o_PP_CREATE_SCOPE _namespaces_),  #_name_) ;




#define o_scope_registerTI(_name_, _template_args_)\
    o_scope_registerphantom::detail::scope_registrer< _name_<o_PP_IDENTITY _template_args_>, o_read_compilation_counter> o_PP_CAT(g_register_module_, __COUNTER__) ;

#define o_scope_registerNTI(_namespaces_, _name_, _template_args_)\
    phantom::detail::scope_registrer< o_PP_CREATE_QUALIFIED_NAME(_namespaces_,_name_)<o_PP_IDENTITY _template_args_>, o_read_compilation_counter > o_PP_CAT(g_register_module_, __COUNTER__) ;

#define o_scope_register(...)\
    phantom::detail::scope_registrer< _name_, o_read_compilation_counter > o_PP_CAT(g_register_module_, __COUNTER__) ;

#define o_scope_registerN(_namespaces_, _name_)\
    phantom::detail::scope_registrer< o_PP_CREATE_QUALIFIED_NAME(_namespaces_,_name_), o_read_compilation_counter > o_PP_CAT(g_register_module_, o_PP_CAT(_name_, __COUNTER__)) ;

#define o_scope_registerC(_classes_, _name_)\
    phantom::detail::scope_registrer< o_PP_CREATE_QUALIFIED_NAME(_classes_,_name_), o_read_compilation_counter> o_PP_CAT(g_register_module_, o_PP_CAT(_name_, __COUNTER__)) ;

#define o_scope_registerNC(_namespaces_, _classes_, _name_)\
    phantom::detail::scope_registrer< o_PP_CREATE_QUALIFIED_NAME_2(_namespaces_,_classes_,_name_), o_read_compilation_counter > o_PP_CAT(g_register_module_, o_PP_CAT(_name_, __COUNTER__)) ;


#define o_reflection_custom_begin(_type_)    \
    protected:\
    enum { PHANTOM_CODEGEN_reflection_counter_value = o_read_compilation_counter};\
    public: \
    typedef _type_ enclosed_reflection_declaration; \
    class enclosed_reflection : public phantom::reflection::detail::phantom_base_enclosed_reflection<_type_>\
    {\
        typedef _type_ phantom_proxy_generator_reflection_self_type; \
        typedef _type_ phantom_proxy_generator_reflection_proxy_type;\

#define o_reflection_custom_end()    \
    };


#if o_OPERATING_SYSTEM == o_OPERATING_SYSTEM_WINDOWS
#define o_module(name)\
    BOOL WINAPI DllMain(_In_ HINSTANCE _HDllHandle, _In_ DWORD _Reason, _In_opt_ LPVOID _Reserved)\
{\
    switch(_Reason)\
    {\
    case DLL_PROCESS_ATTACH:\
    {\
        char moduleName[512];\
        GetModuleFileName(_HDllHandle, moduleName, 512);\
        phantom::installReflection(name, moduleName, (size_t)_HDllHandle);\
        }\
    break;\
    case DLL_PROCESS_DETACH:\
    phantom::uninstallReflection(name);\
    if(strcmp(name, "phantom") == 0) phantom::release();\
    break;\
    case DLL_THREAD_ATTACH:\
    break;\
    case DLL_THREAD_DETACH:\
    break;\
    }\
    return TRUE;\
}

#endif

#define o_reflection_custom_declare(_type_)\
    protected:\
                  enum { PHANTOM_CODEGEN_reflection_counter_value = o_read_compilation_counter};\
    public: \
            typedef _type_ enclosed_reflection_declaration; \
              class enclosed_reflection;

#define o_reflection    \
    protected:\
    enum { PHANTOM_CODEGEN_reflection_counter_value = o_read_compilation_counter};\
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

#define o_nested_begin(_name_, ...)\
class phantom_proxy_____##_name_\
    : public _name_\
    , public phantom_proxy_generator_base_____<_name_, phantom_proxy_____##_name_ >\
{\
    o_reflection \
    {\
        struct initializer\
        {\
            initializer()\
            {\
                phantom::reflection::Types::savedInstalledClass = phantom::reflection::Types::currentInstalledClass;\
                phantom::reflection::Types::savedInstalledTemplateSpecialization = phantom::reflection::Types::currentInstalledTemplateSpecialization;\
                typedef phantom::reflection::meta_class_type_of<_name_,##__VA_ARGS__>::type meta_type;\
                meta_type* pMetaType = new (o__t1_class__default_class_allocator(meta_type)::allocate()) meta_type(#_name_);\
                meta_type::metaType->install(pMetaType, 0);\
                meta_type::metaType->initialize(pMetaType);\
                phantom::reflection::Types::currentInstalledClass = pMetaType;\
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
class :: o_PP_CREATE_SCOPE _namespaces_::phantom_proxy_____##_name_<o_PP_CREATE_QUALIFIED_NAME(_namespaces_,_name_) < o_PP_IDENTITY _template_params_ > >\
    : public o_PP_CREATE_QUALIFIED_NAME(_namespaces_,_name_)< o_PP_IDENTITY _template_params_ >\
    , public phantom_proxy_generator_base_____<o_PP_CREATE_QUALIFIED_NAME(_namespaces_,_name_)< o_PP_IDENTITY _template_params_ >, :: o_PP_CREATE_SCOPE _namespaces_::phantom_proxy_____##_name_<o_PP_CREATE_QUALIFIED_NAME(_namespaces_,_name_) < o_PP_IDENTITY _template_params_ > > >


// #define o_class_moduleNTC(_namespaces_,_template_types_,_template_params_,_class_,_name_)\
//     o_namespace_begin _namespaces_\
//     template<typename t_Ty>\
// class phantom_proxy_____##_class_##______##_name_;\
//     o_namespace_end _namespaces_\
//     namespace phantom {\
//     template<o_PP_MIX(_template_types_,_template_params_)>\
// struct proxy_of< o_NESTED_TYPE o_PP_CREATE_QUALIFIED_NAME(_namespaces_,_class_) < o_PP_IDENTITY _template_params_ >::_name_ >\
// {\
//     typedef :: o_PP_CREATE_SCOPE _namespaces_::phantom_proxy_____##_class_##______##_name_< o_NESTED_TYPE o_PP_CREATE_QUALIFIED_NAME(_namespaces_,_class_) < o_PP_IDENTITY _template_params_ >::_name_ > type;\
// };\
//     }\
//     template<o_PP_MIX(_template_types_,_template_params_)>\
// class :: o_PP_CREATE_SCOPE _namespaces_::phantom_proxy_____##_class_##______##_name_< o_PP_CREATE_QUALIFIED_NAME(_namespaces_,_class_) < o_PP_IDENTITY _template_params_ >::_name_ >\
//     : public o_PP_CREATE_QUALIFIED_NAME(_namespaces_,_class_)< o_PP_IDENTITY _template_params_ >\
//     , public o_NESTED_TYPE o_PP_CREATE_QUALIFIED_NAME(_namespaces_,_class_)< o_PP_IDENTITY _template_params_ >::_name_\
//     , public phantom_proxy_generator_base_____<o_NESTED_TYPE o_PP_CREATE_QUALIFIED_NAME(_namespaces_,_class_)< o_PP_IDENTITY _template_params_ >::_name_, :: o_PP_CREATE_SCOPE _namespaces_::phantom_proxy_____##_class_##______##_name_< o_NESTED_TYPE o_PP_CREATE_QUALIFIED_NAME(_namespaces_,_class_) < o_PP_IDENTITY _template_params_ >::_name_ > >


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

#if o__int__reflection_template_use_level == 0
#define o_enum_module_access_type(name) static_cast<phantom::reflection::Enum*>(phantom::typeByName(#name))
#define o_enum_module_access_typeN(namespaces, name) static_cast<phantom::reflection::Enum*>(phantom::typeByName(o_PP_QUOTE o_PP_LEFT_PAREN o_PP_CREATE_QUALIFIED_NAME(namespaces, name) o_PP_RIGHT_PAREN ))
#define o_enum_module_access_typeNC(namespaces, classes, name) static_cast<phantom::reflection::Enum*>(phantom::typeByName(o_PP_QUOTE o_PP_LEFT_PAREN o_PP_CREATE_QUALIFIED_NAME_2(namespaces, classes, name) o_PP_RIGHT_PAREN))
#define o_enum_module_access_typeC(classes, name) static_cast<phantom::reflection::Enum*>(phantom::typeByName(o_PP_QUOTE o_PP_LEFT_PAREN o_PP_CREATE_QUALIFIED_NAME(classes, name) o_PP_RIGHT_PAREN))
#else
#define o_enum_module_access_type(name) phantom::typeOf<phantom_proxy_generator_reflection_self_type>()
#define o_enum_module_access_typeN(namespaces, name) phantom::typeOf<phantom_proxy_generator_reflection_self_type>()
#define o_enum_module_access_typeNC(namespaces, classes, name) phantom::typeOf<phantom_proxy_generator_reflection_self_type>()
#define o_enum_module_access_typeC(classes, name) phantom::typeOf<phantom_proxy_generator_reflection_self_type>()
#endif

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
                    phantom::reflection::Enum* pEnum = o_enum_module_access_type(_name_);\
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
                phantom::reflection::Enum* pEnum = o_enum_module_access_typeC(_classes_, _name_);\
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
                    phantom::reflection::Enum* pEnum = o_enum_module_access_typeN(_namespaces_, _name_);\
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
                phantom::reflection::Enum* pEnum = o_enum_module_access_typeN(_namespaces_, _name_);\
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
                    phantom::reflection::Enum* pEnum = o_enum_module_access_typeNC(_namespaces_, _classes_, _name_);\
                    o_enum_add_values _values_\
                }\
            }o_PP_CAT(o_PP_CAT(_name_,__LINE__),_instance);\
        };\
    };


// Phantom member_functions
#define o_initialize()                  void PHANTOM_CODEGEN_initialize()
#define o_terminate()                   void PHANTOM_CODEGEN_terminate()
#define o_restore(filter,pass)          phantom::restore_state PHANTOM_CODEGEN_restore(phantom::uint filter, phantom::uint pass)

#define o_initialize_cpp(classname)                  void classname::PHANTOM_CODEGEN_initialize()
#define o_terminate_cpp(classname)                   void classname::PHANTOM_CODEGEN_terminate()
#define o_restore_cpp(classname,filter,pass)          phantom::restore_state classname::PHANTOM_CODEGEN_restore(phantom::uint filter, phantom::uint pass)


#define o_destroyed                         typedef int PHANTOM_CODEGEN_destroyed_marker; o_signal_data(PHANTOM_CODEGEN_destroyed)


#endif // o_phantom_modules__