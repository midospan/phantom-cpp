
#define o_attribute(_name_, _variant_)\
    class \
    {\
        struct reg\
        {\
            reg() \
            {\
                phantom::reflection::native::currentClassType()->addAttribute(_name_, _variant_);\
            }\
        } regi;\
    } o_PP_CAT(attribute,__COUNTER__);

//
// #if o_COMPILER == o_COMPILER_VISUAL_STUDIO  /// visual studio 2010 accepts protected member function pointer to be accessed from a derived class
// #define _o_member_func_pointer_access(_name_) &phantom_proxy_generator_reflection_self_type::_name_
// #else // o_COMPILER == o_COMPILER_VISUAL_STUDIO
// /// GCC doesn't, others not tested yet, we need to use the derived one
// #define _o_member_func_pointer_access(_name_) &protected_breaker::_name_
// #endif

#define o_property_8(_type_, _name_, _set_member_function_, _get_member_function_, _signal_, _range_, _modifiers_, _serialization_mask_)\
    o_static_assert_msg( ((((_modifiers_)&o_transient) == 0) OR (_serialization_mask_ == 0)), "if transient, property must have a null serialization mask" );\
    class \
    {\
        enum {_name_};\
        struct reg\
        {\
            struct protected_breaker : public phantom_proxy_generator_protected_breaker_base\
            {\
                int m_PHANTOM_RESERVED_no_signal;\
                int PHANTOM_CODEGEN_m_slot_list_of_m_PHANTOM_RESERVED_no_signal;\
                o_forceinline static phantom::reflection::MemberFunction* get_()\
                {\
                    return phantom::reflection::native::TNativeMemberFunctionProvider<phantom_proxy_generator_reflection_self_type,((_modifiers_&o_public_access)==o_public_access)?o_public_access:o_protected_access,_type_ ()>::CreateMemberFunction( \
                        o_PP_QUOTE(_get_member_function_) \
                        , o_PP_QUOTE(_type_)"()"\
                        , &phantom_proxy_generator_reflection_proxy_type::phantom_proxy_generator_reflection_self_type::_get_member_function_ \
                        ,((((_modifiers_)|phantom::reflection::native::currentModifiers())&o_public_access)==o_public_access)?o_public_access:o_protected_access)->asMemberFunction();\
                }\
                o_forceinline static phantom::reflection::MemberFunction*  set_()\
                {\
                    return phantom::reflection::native::TNativeMemberFunctionProvider<phantom_proxy_generator_reflection_self_type,phantom::detail::int_embedder<_modifiers_>::value|o_slot_member_function,void (_type_)>::CreateMemberFunction( \
                        o_PP_QUOTE(_set_member_function_) \
                        , "void" o_PP_QUOTE((_type_)) \
                        , &phantom_proxy_generator_reflection_proxy_type::phantom_proxy_generator_reflection_self_type::_set_member_function_ \
                        ,(((((_modifiers_)|phantom::reflection::native::currentModifiers())&o_public_access)==o_public_access)?o_public_access:o_protected_access)|o_slot_member_function)->asMemberFunction();\
                }\
                o_forceinline static phantom::reflection::Signal*  signal_()\
                {\
                return phantom::reflection::native::DynamicNativePropertySignalProvider<phantom_proxy_generator_reflection_self_type, _type_>::CreateSignal(\
                        o_PP_QUOTE(_signal_)\
                        , o_PP_QUOTE(_type_)\
                        , &protected_breaker::_signal_\
                        , &protected_breaker::PHANTOM_CODEGEN_m_slot_list_of_##_signal_);\
                }\
                o_forceinline static phantom::reflection::Property*  property_()\
                {\
                    phantom::reflection::MemberFunction* pGetMemberFunction = get_();\
                    if(pGetMemberFunction == nullptr) o_exception(phantom::exception::reflection_runtime_exception, "invalid property get member function");\
                    phantom::reflection::MemberFunction* pSetMemberFunction = set_();\
                    if(pSetMemberFunction == nullptr) o_exception(phantom::exception::reflection_runtime_exception, "invalid property set member function");\
                    phantom::reflection::Type* pType = phantom::typeByName(o_PP_QUOTE(_type_), phantom::reflection::native::currentClassType(), o_native);\
                    o_assert(pType, o_PP_QUOTE(_type_)" type not registered");\
                    phantom::reflection::Signal* pSignal = signal_();\
                    if(pSignal) \
                    {\
                        o_assert(phantom::reflection::native::currentClassType()->asClass(), "Signals only allowed in non-pod classes");\
                    }\
                    return o_dynamic_proxy_new(phantom::reflection::native::TNativeProperty<\
                                    phantom_proxy_generator_reflection_self_type, _type_>) \
                                    ( \
                                          pType\
                                        , o_PP_QUOTE(_name_)\
                                        , pSetMemberFunction\
                                        , pGetMemberFunction\
                                        , pSignal\
                                        , o_range _range_\
                                        , &phantom_proxy_generator_reflection_proxy_type::phantom_proxy_generator_reflection_self_type::_set_member_function_\
                                        , &phantom_proxy_generator_reflection_proxy_type::phantom_proxy_generator_reflection_self_type::_get_member_function_\
                                        , _serialization_mask_\
                                        , (_modifiers_)|phantom::reflection::native::currentModifiers()\
                                    );\
                }\
            };\
            reg() \
            {\
                phantom::reflection::Property* pProperty = protected_breaker::property_();\
                phantom::reflection::native::currentClassType()->addValueMember(pProperty);\
            }\
        } regi;\
    } o_PP_CAT(property, __COUNTER__);


#    define o_signal(_name_, _parameterslist_, ...) \
        class \
        {\
            struct reg\
            {\
                struct protected_breaker : public phantom_proxy_generator_protected_breaker_base\
                {\
                    o_forceinline static phantom::reflection::Signal*  signal_()\
                    {\
                    union { \
                    phantom::connection::slot::list (protected_breaker::*original); \
                    phantom::connection::slot::list (phantom_proxy_generator_reflection_self_type::*hacked); \
                    } un;\
                    un.original = &protected_breaker::PHANTOM_CODEGEN_m_slot_list_of_##_name_;\
                    return o_dynamic_proxy_new(\
                            phantom::reflection::native::TNativeSignal<\
                            phantom_proxy_generator_reflection_self_type\
                            , phantom::signal_t _parameterslist_>) \
                            ( o_PP_QUOTE(_name_)\
                                , "phantom::signal_t" o_PP_QUOTE(_parameterslist_)\
                                , &protected_breaker::_name_\
                                , un.hacked\
                                , phantom::detail::int_embedder< __VA_ARGS__ >::value\
                            );\
                    }\
                };\
                reg() \
                {\
                    phantom::reflection::Signal* pSignal = protected_breaker::signal_();\
                    o_assert(phantom::reflection::native::currentClassType()->asClass(), "Cannot add signal to pod class");\
                }\
            } regi;\
        } o_PP_CAT(signal, __COUNTER__);

#    define o_data_member_5(_type_, _name_, _range_, _modifiers_, _serialization_mask_) \
    o_static_assert_msg( ((((_modifiers_)&o_transient) == 0) OR (_serialization_mask_ == 0)), "if transient, data member must have a null serialization mask" );\
        class _name_\
        {\
            template<typename t_TTTTTy>\
            struct reg\
            {\
                struct protected_breaker : public phantom_proxy_generator_protected_breaker_base\
                {\
                    inline static phantom::reflection::LanguageElement* get()\
                    {\
                        typedef o_NESTED_TYPE phantom::select_type_if_union<phantom_proxy_generator_reflection_self_type, phantom_proxy_generator_reflection_self_type, protected_breaker>::type member_getter;\
                        union { \
                            o_NESTED_TYPE phantom::member_pointer_type_maker<member_getter, t_TTTTTy>::type original; \
                            o_NESTED_TYPE phantom::member_pointer_type_maker<phantom_proxy_generator_reflection_self_type, t_TTTTTy>::type hacked; \
                            t_TTTTTy* static_;\
                        } un;\
                        typedef o_NESTED_TYPE phantom::member_access_value_type<decltype(&member_getter::_name_)>::type member_value_type;\
                        phantom::reflection::detail::data_member_unambiguitor<member_value_type, phantom_proxy_generator_reflection_self_type>::set_union_value(un, &member_getter::_name_);\
                        phantom::reflection::Type* pType = phantom::typeByName(o_PP_QUOTE(_type_),phantom::reflection::native::currentClassType(), o_native);\
                        o_assert(pType, o_PP_QUOTE(_type_)" type not registered");\
                        if(pType == nullptr) { \
                        o_exception(phantom::exception::t_unknown_reflection_type_exception<_type_> \
                        , o_PP_QUOTE(_type_)" type not registered"); \
                        }\
                        return phantom::reflection::native::TNativeDataMemberProvider< phantom_proxy_generator_reflection_self_type, _modifiers_, t_TTTTTy >::CreateDataMember(o_PP_QUOTE(_name_), pType, phantom::reflection::detail::data_member_unambiguitor<member_value_type, phantom_proxy_generator_reflection_self_type>::get_union_value(un, &member_getter::_name_), o_range _range_, _serialization_mask_, (_modifiers_)|phantom::reflection::native::currentModifiers());\
                    }\
                };\
                reg() \
                {\
                    auto pMember = protected_breaker::get();\
                    o_assert(pMember);\
                    o_assert(phantom::reflection::native::currentClassType());\
                    if(pMember->asDataMember())\
                    {\
                        phantom::reflection::native::currentClassType()->addDataMember(pMember->asDataMember());\
                    }\
                    else\
                    {\
                        phantom::reflection::native::currentClassType()->addVariable(pMember->asVariable());\
                    }\
                    if(phantom::reflection::native::currentMemberAnonymousSection())\
                    {\
                        phantom::reflection::DataMember* pDataMember = pMember->asDataMember();\
                        if(pDataMember == nullptr) { o_exception(phantom::exception::reflection_runtime_exception, "static data members cannot be added to anonymous union or anonymous struct"); }\
                        phantom::reflection::native::currentMemberAnonymousSection()->addDataMember(pDataMember);\
                    }\
                }\
            } ;\
            reg<_type_> regi;\
        } o_PP_CAT(data_member, __COUNTER__);

#define o_anonymous_struct(...)\
    o_anonymous_section(struct, __VA_ARGS__)

#define o_anonymous_union(...)\
    o_anonymous_section(union, __VA_ARGS__)

#define o_anonymous_structG(...)\
    static o_anonymous_struct(__VA_ARGS__)

#define o_anonymous_unionG(...)\
    static o_anonymous_union(__VA_ARGS__)

#define o_anonymous_section(keyword, ...)\
    class \
    {\
        struct sub_reg\
        {\
            __VA_ARGS__\
        };\
        struct reg\
        {\
            typedef phantom::reflection::AnonymousStruct Anonymousstruct;             \
            typedef phantom::reflection::AnonymousUnion Anonymousunion;               \
            typedef phantom::reflection::MemberAnonymousStruct MemberAnonymousstruct; \
            typedef phantom::reflection::MemberAnonymousUnion MemberAnonymousunion;   \
            reg() \
            {\
                if(phantom::reflection::native::currentAnonymousSection())\
                {\
                    auto pAS = o_new(Anonymous##keyword);\
                    phantom::reflection::native::currentAnonymousSection()->addAnonymousSection(pAS);\
                    phantom::reflection::native::pushAnonymousSection(pAS);\
                    sub_reg sub_regi;\
                    phantom::reflection::native::popAnonymousSection();\
                }\
                else if(phantom::reflection::native::currentScope()->asLanguageElement()->asNamespace())\
                {\
                    auto pAS = o_new(Anonymous##keyword);\
                    phantom::reflection::native::currentScope()->asLanguageElement()->asNamespace()->addAnonymousSection(pAS);\
                    phantom::reflection::native::pushAnonymousSection(pAS);\
                    sub_reg sub_regi;\
                    phantom::reflection::native::popAnonymousSection();\
                }\
                else if(phantom::reflection::native::currentMemberAnonymousSection())\
                {\
                    auto pAS = o_new(MemberAnonymous##keyword);\
                    phantom::reflection::native::currentMemberAnonymousSection()->addMemberAnonymousSection(pAS);\
                    phantom::reflection::native::pushMemberAnonymousSection(pAS);\
                    sub_reg sub_regi;\
                    phantom::reflection::native::popMemberAnonymousSection();\
                }\
                else if(phantom::reflection::native::currentScope()->asLanguageElement()->asClassType())\
                {\
                    auto pAS = o_new(MemberAnonymous##keyword);\
                    phantom::reflection::native::currentScope()->asLanguageElement()->asClassType()->addMemberAnonymousSection(pAS);\
                    phantom::reflection::native::pushMemberAnonymousSection(pAS);\
                    sub_reg sub_regi;\
                    phantom::reflection::native::popMemberAnonymousSection();\
                }\
                else \
                o_exception(phantom::exception::reflection_runtime_exception, "anonymous "#keyword" declared outside legal scope");\
            }\
        } regi;\
    } o_PP_CAT(anonymous_##keyword,__COUNTER__);

#define o_anonymous(...)\
    class \
    {\
        struct reg\
        {\
            reg() \
            {\
                phantom::reflection::AnonymousSection* pSection = phantom::reflection::native::currentClassType()->addAnonymousSection(#__VA_ARGS__, o_native);\
                if(pSection == nullptr)\
                {\
                    o_exception(exception::reflection_runtime_exception, "Error in anonymous section declaration, forgot union or struct ? have you declared every data member ?");\
                }\
            }\
        } regi;\
    } o_PP_CAT(anonymous,__COUNTER__);\


#    define o_member_function(_returntype_, _name_, _parameterslist_, ...) \
        class\
        {\
            struct reg\
            {\
                struct protected_breaker : public phantom_proxy_generator_protected_breaker_base\
                {\
                    o_forceinline static void add()\
                    {\
                        auto pMemberFunction = phantom::reflection::native::TNativeMemberFunctionProvider<phantom_proxy_generator_reflection_self_type,phantom::detail::int_embedder<__VA_ARGS__>::value,_returntype_ _parameterslist_>::CreateMemberFunction( \
                        o_PP_QUOTE(_name_) \
                        , o_PP_QUOTE(_returntype_) "" o_PP_QUOTE(_parameterslist_)\
                        , &phantom_proxy_generator_reflection_proxy_type::phantom_proxy_generator_reflection_self_type::_name_ \
                        ,phantom::detail::int_embedder<__VA_ARGS__>::value|phantom::reflection::native::currentModifiers());\
                    }\
                };\
                reg() \
                {\
                    protected_breaker::add();\
                }\
            } regi;\
        } o_PP_CAT(member_function, __COUNTER__);

#    define o_slot(_returntype_, _name_, _parameterslist_, ...) \
        class\
        {\
            struct reg\
            {\
                struct protected_breaker : public phantom_proxy_generator_protected_breaker_base\
                {\
                    o_forceinline static void add()\
                    {\
                        auto pMemberFunction = phantom::reflection::native::TNativeMemberFunctionProvider<phantom_proxy_generator_reflection_self_type,phantom::detail::int_embedder<__VA_ARGS__>::value,_returntype_ _parameterslist_>::CreateMemberFunction( \
                        o_PP_QUOTE(_name_) \
                        , o_PP_QUOTE(_returntype_) "" o_PP_QUOTE(_parameterslist_)\
                        , &phantom_proxy_generator_reflection_proxy_type::phantom_proxy_generator_reflection_self_type::_name_ \
                        ,phantom::detail::int_embedder<__VA_ARGS__>::value|o_slot_member_function|phantom::reflection::native::currentModifiers());\
                    }\
                };\
                reg() \
                {\
                    protected_breaker::add();\
                }\
            } regi;\
        } o_PP_CAT(slot, __COUNTER__);

#    define o_constructor(_parameterslist_, ...) \
    class \
    {\
        struct reg\
        {\
            reg() \
            {\
                auto pConstructor = o_dynamic_proxy_new(phantom::reflection::native::TNativeConstructor<phantom_proxy_generator_reflection_self_type _parameterslist_>)(phantom::reflection::native::currentClassType()->getName(), "void" o_PP_QUOTE(_parameterslist_), phantom::detail::int_embedder<__VA_ARGS__>::value|phantom::reflection::native::currentModifiers());\
            }\
        } regi;\
    } o_PP_CAT(constructor,__COUNTER__);

#if o_COMPILER == o_COMPILER_VISUAL_STUDIO
#define o_nested_typedef_add_internal_typedef(name)
#else
#define o_nested_typedef_add_internal_typedef(name) \
    template<typename wereallydontcare>\
    static o_NESTED_TYPE wereallydontcare::name nested_typedef_add_internal_typedef##name();\
    typedef decltype(nested_typedef_add_internal_typedef##name<phantom_proxy_generator_reflection_self_type>()) name;
#endif

#define o_nested_typedef_1(name)\
    class \
    {\
        template<typename t_TTTy>\
        struct protected_breaker : public t_TTTy {};\
        template<typename t_TTTy>\
        struct reg\
        {\
            reg() \
            {\
                phantom::reflection::native::currentClassType()->addAlias(phantom::reflection::type_of<o_NESTED_TYPE protected_breaker<t_TTTy>::name>::object(), #name, o_native);\
            }\
        };\
        reg<phantom_proxy_generator_protected_breaker_base> regi;\
    } o_PP_CAT(typedef,__COUNTER__);\
    o_nested_typedef_add_internal_typedef(name)

#define o_nested_typedef_2(part0, name)\
    class \
    {\
        struct reg\
        {\
            reg() \
            {\
                phantom::reflection::native::currentClassType()->addAlias(phantom::typeByName(#part0, phantom::reflection::native::currentClassType()), #name, o_native);\
            }\
        } regi;\
    } o_PP_CAT(typedef,__COUNTER__);\
    o_nested_typedef_add_internal_typedef(name)

#define o_nested_typedef_3(part0, part1, name)\
    class \
    {\
        struct reg\
        {\
            reg() \
            {\
                phantom::reflection::native::currentClassType()->addAlias(phantom::typeByName(#part0 #part1, phantom::reflection::native::currentClassType()), #name, o_native);\
            }\
        } regi;\
    } o_PP_CAT(typedef,__COUNTER__);\
    o_nested_typedef_add_internal_typedef(name)

#define o_nested_typedef_4(part0, part1, part2, name)\
    class \
    {\
        struct reg\
        {\
            reg() \
            {\
                phantom::reflection::native::currentClassType()->addAlias(phantom::typeByName(#part0 #part1 #part2, phantom::reflection::native::currentClassType()), #name, o_native);\
            }\
        } regi;\
    } o_PP_CAT(typedef,__COUNTER__);\
    o_nested_typedef_add_internal_typedef(name)

#define o_nested_typedef_5(part0, part1, part2, part3, name)\
    class \
    {\
        struct reg\
        {\
            reg() \
            {\
                phantom::reflection::native::currentClassType()->addAlias(phantom::typeByName(#part0 #part1 #part2 #part3, phantom::reflection::native::currentClassType()), #name, o_native);\
            }\
        } regi;\
    } o_PP_CAT(typedef,__COUNTER__);\
    o_nested_typedef_add_internal_typedef(name)

#define o_nested_typedef_6(part0, part1, part2, part3, part4, name)\
    class \
    {\
        struct reg\
        {\
            reg() \
            {\
                phantom::reflection::native::currentClassType()->addAlias(phantom::typeByName(#part0 #part1 #part2 #part3 #part4, phantom::reflection::native::currentClassType()), #name, o_native);\
            }\
        } regi;\
    } o_PP_CAT(typedef,__COUNTER__);\
    o_nested_typedef_add_internal_typedef(name)

#define o_default_template_argument_type(parameter, ...)\
    class \
    {\
        struct reg\
        {\
            reg() \
            {\
                phantom::reflection::native::currentClassType()->getTemplateSpecialization()->setDefaultArgument(#parameter, phantom::reflection::type_of<__VA_ARGS__>::object());\
            }\
        } regi;\
    } o_PP_CAT(default_template_argument_type,__COUNTER__);
