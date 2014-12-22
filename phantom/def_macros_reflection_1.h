
#define o_attribute(_name_, _variant_)\
    class \
    {\
        struct reg\
        {\
            reg() \
            {\
                phantom::reflection::Types::currentInstalledClass->addAttribute(_name_, _variant_);\
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
                o_forceinline static phantom::reflection::InstanceMemberFunction* get_()\
                {\
                    return phantom::reflection::native::TNativeMemberFunctionProvider<phantom_proxy_generator_reflection_self_type,((_modifiers_&o_public_access)==o_public_access)?o_public_access:o_protected_access,_type_ ()>::CreateMemberFunction( \
                        o_PP_QUOTE(_get_member_function_) \
                        , phantom::reflection::Signature::Create(o_PP_QUOTE(_type_)"()", phantom::reflection::Types::currentInstalledTemplateSpecialization, phantom::reflection::Types::currentInstalledClass) \
                        , &protected_breaker::_get_member_function_ \
                        ,((((_modifiers_)|phantom::reflection::Types::currentModifiers)&o_public_access)==o_public_access)?o_public_access:o_protected_access)->asInstanceMemberFunction();\
                }\
                o_forceinline static phantom::reflection::InstanceMemberFunction*  set_()\
                {\
                    return phantom::reflection::native::TNativeMemberFunctionProvider<phantom_proxy_generator_reflection_self_type,phantom::detail::int_embedder<_modifiers_>::value|o_slot_member_function,void (_type_)>::CreateMemberFunction( \
                        o_PP_QUOTE(_set_member_function_) \
                        , phantom::reflection::Signature::Create("void" o_PP_QUOTE((_type_)), phantom::reflection::Types::currentInstalledTemplateSpecialization, phantom::reflection::Types::currentInstalledClass) \
                        , &protected_breaker::_set_member_function_ \
                        ,(((((_modifiers_)|phantom::reflection::Types::currentModifiers)&o_public_access)==o_public_access)?o_public_access:o_protected_access)|o_slot_member_function)->asInstanceMemberFunction();\
                }\
                o_forceinline static phantom::reflection::Signal*  signal_()\
                {\
                return phantom::reflection::native::DynamicNativePropertySignalProvider<phantom_proxy_generator_reflection_self_type, _type_>::CreateSignal(\
                        o_PP_QUOTE(_signal_)\
                        , o_PP_QUOTE(_type_)\
                        , phantom::reflection::Types::currentInstalledTemplateSpecialization\
                        , phantom::reflection::Types::currentInstalledClass\
                        , &protected_breaker::_signal_\
                        , &protected_breaker::PHANTOM_CODEGEN_m_slot_list_of_##_signal_);\
                }\
                o_forceinline static phantom::reflection::Property*  property_()\
                {\
                    phantom::reflection::InstanceMemberFunction* pGetMemberFunction = get_();\
                    if(pGetMemberFunction == nullptr) o_exception(phantom::exception::reflection_runtime_exception, "invalid property get member function");\
                    pGetMemberFunction->addCodeLocation(phantom::sourceFile(__FILE__));\
                    phantom::reflection::Types::currentInstalledClass->addMemberFunction(pGetMemberFunction);\
                    phantom::reflection::InstanceMemberFunction* pSetMemberFunction = set_();\
                    if(pSetMemberFunction == nullptr) o_exception(phantom::exception::reflection_runtime_exception, "invalid property set member function");\
                    pSetMemberFunction->addCodeLocation(phantom::sourceFile(__FILE__));\
                    phantom::reflection::Types::currentInstalledClass->addMemberFunction(pSetMemberFunction);\
                    phantom::reflection::Type* pType = phantom::typeByName(o_PP_QUOTE(_type_), phantom::reflection::Types::currentInstalledClass);\
                    o_assert(pType, o_PP_QUOTE(_type_)" type not registered");\
                    phantom::reflection::Signal* pSignal = signal_();\
                    if(pSignal) \
                    {\
                        o_assert(phantom::reflection::Types::currentInstalledClass->asClass(), "Signals only allowed in non-pod classes");\
                        phantom::reflection::Types::currentInstalledClass->asClass()->addSignal(pSignal);\
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
                                        , &protected_breaker::_set_member_function_\
                                        , &protected_breaker::_get_member_function_\
                                        , _serialization_mask_\
                                        , (_modifiers_)|phantom::reflection::Types::currentModifiers\
                                    );\
                }\
            };\
            reg() \
            {\
                phantom::reflection::Property* pProperty = protected_breaker::property_();\
                pProperty->addCodeLocation(phantom::sourceFile(__FILE__));\
                phantom::reflection::Types::currentInstalledClass->addValueMember(pProperty);\
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
                                , phantom::reflection::Signature::Create(\
                                "phantom::signal_t" o_PP_QUOTE(_parameterslist_)\
                                , phantom::reflection::Types::currentInstalledTemplateSpecialization\
                                , phantom::reflection::Types::currentInstalledClass\
                                )\
                                , &protected_breaker::_name_\
                                , un.hacked\
                                , phantom::detail::int_embedder< __VA_ARGS__ >::value\
                            );\
                    }\
                };\
                reg() \
                {\
                    phantom::reflection::Signal* pSignal = protected_breaker::signal_();\
                    pSignal->addCodeLocation(phantom::sourceFile(__FILE__));\
                    o_assert(phantom::reflection::Types::currentInstalledClass->asClass(), "Cannot add signal to pod class");\
                    phantom::reflection::Types::currentInstalledClass->asClass()->addSignal(pSignal);\
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
                    inline static phantom::reflection::DataMember* get()\
                    {\
                        typedef o_NESTED_TYPE phantom::select_type_if_union<phantom_proxy_generator_reflection_self_type, phantom_proxy_generator_reflection_self_type, protected_breaker>::type member_getter;\
                        union { \
                            o_NESTED_TYPE phantom::member_pointer_type_maker<member_getter, t_TTTTTy>::type original; \
                            o_NESTED_TYPE phantom::member_pointer_type_maker<phantom_proxy_generator_reflection_self_type, t_TTTTTy>::type hacked; \
                            t_TTTTTy* static_;\
                        } un;\
                        typedef o_NESTED_TYPE phantom::member_access_value_type<decltype(&member_getter::_name_)>::type member_value_type;\
                        phantom::reflection::detail::data_member_unambiguitor<member_value_type, phantom_proxy_generator_reflection_self_type>::set_union_value(un, &member_getter::_name_);\
                        phantom::reflection::Type* pType = phantom::typeByName(o_PP_QUOTE(_type_),phantom::reflection::Types::currentInstalledClass);\
                        o_assert(pType, o_PP_QUOTE(_type_)" type not registered");\
                        if(pType == nullptr) { \
                        o_exception(phantom::exception::t_unknown_reflection_type_exception<_type_> \
                        , o_PP_QUOTE(_type_)" type not registered"); \
                        }\
                        pType->addReferenceCodeLocation(phantom::sourceFile(__FILE__));\
                        return phantom::reflection::native::TNativeDataMemberProvider< phantom_proxy_generator_reflection_self_type, _modifiers_, t_TTTTTy >::CreateDataMember(o_PP_QUOTE(_name_), pType, phantom::reflection::detail::data_member_unambiguitor<member_value_type, phantom_proxy_generator_reflection_self_type>::get_union_value(un, &member_getter::_name_), o_range _range_, _serialization_mask_, (_modifiers_)|phantom::reflection::Types::currentModifiers);\
                    }\
                };\
                reg() \
                {\
                    auto pDataMember = protected_breaker::get();\
                    pDataMember->asLanguageElement()->addCodeLocation(phantom::sourceFile(__FILE__));\
                    phantom::reflection::Types::currentInstalledClass->addDataMember(pDataMember);\
                    if(phantom::reflection::Types::currentInstalledAnonymousSection)\
                    {\
                        phantom::reflection::InstanceDataMember* pInstanceDataMember = pDataMember->asInstanceDataMember();\
                        if(pInstanceDataMember == nullptr) { o_exception(phantom::exception::reflection_runtime_exception, "static data members cannot be added to anonymous union or anonymous struct"); }\
                        phantom::reflection::Types::currentInstalledAnonymousSection->addInstanceDataMember(pInstanceDataMember);\
                    }\
                }\
            } ;\
            reg<_type_> regi;\
        } o_PP_CAT(data_member, __COUNTER__);

#define o_anonymous_struct(...)\
    class \
    {\
        struct sub_reg\
        {\
            __VA_ARGS__\
        };\
        struct reg\
        {\
            reg() \
            {\
                phantom::reflection::AnonymousSection* pPrevAnonymousSection = phantom::reflection::Types::currentInstalledAnonymousSection;\
                phantom::reflection::Types::currentInstalledAnonymousSection = o_new(phantom::reflection::AnonymousStruct);\
                sub_reg sub_regi;\
                phantom::reflection::Types::currentInstalledClass->addAnonymousSection(phantom::reflection::Types::currentInstalledAnonymousSection);\
                phantom::reflection::Types::currentInstalledAnonymousSection = pPrevAnonymousSection;\
            }\
        } regi;\
    } o_PP_CAT(anonymous_struct,__COUNTER__);

#define o_anonymous_union(...)\
    class \
    {\
        struct sub_reg\
        {\
            __VA_ARGS__\
        };\
        struct reg\
        {\
            reg() \
            {\
                phantom::reflection::AnonymousSection* pPrevAnonymousSection = phantom::reflection::Types::currentInstalledAnonymousSection;\
                phantom::reflection::Types::currentInstalledAnonymousSection = o_new(phantom::reflection::AnonymousUnion);\
                sub_reg sub_regi;\
                phantom::reflection::Types::currentInstalledClass->addAnonymousSection(phantom::reflection::Types::currentInstalledAnonymousSection);\
                phantom::reflection::Types::currentInstalledAnonymousSection = pPrevAnonymousSection;\
            }\
        } regi;\
    } o_PP_CAT(anonymous_union,__COUNTER__);



#define o_anonymous(...)\
    class \
    {\
        struct reg\
        {\
            reg() \
            {\
                phantom::reflection::AnonymousSection* pSection = phantom::reflection::Types::currentInstalledClass->addAnonymousSection(#__VA_ARGS__, o_native);\
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
                    o_forceinline static phantom::reflection::MemberFunction* get()\
                    {\
                        return phantom::reflection::native::TNativeMemberFunctionProvider<phantom_proxy_generator_reflection_self_type,phantom::detail::int_embedder<__VA_ARGS__>::value,_returntype_ _parameterslist_>::CreateMemberFunction( \
                        o_PP_QUOTE(_name_) \
                        , phantom::reflection::Signature::Create(o_PP_QUOTE(_returntype_) "" o_PP_QUOTE(_parameterslist_), phantom::reflection::Types::currentInstalledTemplateSpecialization, phantom::reflection::Types::currentInstalledClass) \
                        , &phantom_proxy_generator_reflection_proxy_type::phantom_proxy_generator_reflection_self_type::_name_ \
                        ,phantom::detail::int_embedder<__VA_ARGS__>::value|phantom::reflection::Types::currentModifiers);\
                    }\
                };\
                reg() \
                {\
                    auto pMemberFunction = protected_breaker::get();\
                    pMemberFunction->asLanguageElement()->addCodeLocation(phantom::sourceFile(__FILE__));\
                    phantom::reflection::Types::currentInstalledClass->addMemberFunction(pMemberFunction);\
                }\
            } regi;\
        } o_PP_CAT(member_function, __COUNTER__);

#    define o_slot(_returntype_, _name_, _parameterslist_, ...) \
    class \
    {\
        struct reg\
        {\
            reg() \
            {\
                auto pMemberFunction = phantom::reflection::native::TNativeMemberFunctionProvider<phantom_proxy_generator_reflection_self_type,phantom::detail::int_embedder<__VA_ARGS__>::value|o_slot_member_function,_returntype_ _parameterslist_>::CreateMemberFunction( \
                o_PP_QUOTE(_name_) \
                , phantom::reflection::Signature::Create(o_PP_QUOTE(_returntype_) "" o_PP_QUOTE(_parameterslist_), phantom::reflection::Types::currentInstalledTemplateSpecialization, phantom::reflection::Types::currentInstalledClass) \
                , &phantom_proxy_generator_reflection_proxy_type::_name_ \
                ,phantom::detail::int_embedder<__VA_ARGS__>::value|o_slot_member_function|phantom::reflection::Types::currentModifiers);\
                pMemberFunction->asLanguageElement()->addCodeLocation(phantom::sourceFile(__FILE__));\
                phantom::reflection::Types::currentInstalledClass->addMemberFunction(pMemberFunction);\
            }\
        } regi;\
    } o_PP_CAT(slot,__COUNTER__);

#    define o_constructor(_parameterslist_, ...) \
    class \
    {\
        struct reg\
        {\
            reg() \
            {\
                auto pConstructor = o_dynamic_proxy_new(phantom::reflection::native::TNativeConstructor<phantom_proxy_generator_reflection_self_type _parameterslist_>)(phantom::reflection::Types::currentInstalledClass->getName(), phantom::reflection::Signature::Create("void" o_PP_QUOTE(_parameterslist_), phantom::reflection::Types::currentInstalledTemplateSpecialization, phantom::reflection::Types::currentInstalledClass),phantom::detail::int_embedder<__VA_ARGS__>::value|phantom::reflection::Types::currentModifiers);\
                pConstructor->addCodeLocation(phantom::sourceFile(__FILE__));\
                phantom::reflection::Types::currentInstalledClass->addConstructor(pConstructor);\
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
        template<typename wedontcare>\
        struct protected_breaker : public wedontcare {};\
        template<typename wereallydontcare>\
        struct reg\
        {\
            reg() \
            {\
                phantom::reflection::Types::currentInstalledClass->addNestedTypedef(#name, phantom::reflection::type_of<o_NESTED_TYPE protected_breaker<wereallydontcare>::name>::object());\
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
                phantom::reflection::Types::currentInstalledClass->addNestedTypedef(#name, phantom::typeByName(#part0, phantom::reflection::Types::currentInstalledClass));\
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
                phantom::reflection::Types::currentInstalledClass->addNestedTypedef(#name, phantom::typeByName(#part0 #part1, phantom::reflection::Types::currentInstalledClass));\
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
                phantom::reflection::Types::currentInstalledClass->addNestedTypedef(#name, phantom::typeByName(#part0 #part1 #part2, phantom::reflection::Types::currentInstalledClass));\
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
                phantom::reflection::Types::currentInstalledClass->addNestedTypedef(#name, phantom::typeByName(#part0 #part1 #part2 #part3, phantom::reflection::Types::currentInstalledClass));\
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
                phantom::reflection::Types::currentInstalledClass->addNestedTypedef(#name, phantom::typeByName(#part0 #part1 #part2 #part3 #part4, phantom::reflection::Types::currentInstalledClass));\
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
                phantom::reflection::Types::currentInstalledTemplateSpecialization->getTemplate()->getTemplateSignature()->setDefaultArgument(#parameter, phantom::reflection::type_of<__VA_ARGS__>::object());\
            }\
        } regi;\
    } o_PP_CAT(default_template_argument_type,__COUNTER__);
/*

#define o_nested_typedef_2(part0, name)\
class o_PP_CAT(name,__LINE__) \
        {\
        friend class enclosed_reflection;\
        o_PP_CAT(name,__LINE__)() \
            {\
            phantom::reflection::Types::currentInstalledClass->addNestedTypedef(#name, phantom::typeByName(#part0, phantom::reflection::Types::currentInstalledClass));\
            }\
        } o_PP_CAT(name,__LINE__);

#define o_nested_typedef_3(part0, part1, name)\
class o_PP_CAT(name,__LINE__) \
        {\
        friend class enclosed_reflection;\
        o_PP_CAT(name,__LINE__)() \
            {\
            phantom::reflection::Types::currentInstalledClass->addNestedTypedef(#name, phantom::typeByName(#part0","#part1, phantom::reflection::Types::currentInstalledClass));\
            }\
        } o_PP_CAT(name,__LINE__);

#define o_nested_typedef_4(part0, part1, part2, name)\
class o_PP_CAT(name,__LINE__) \
        {\
        friend class enclosed_reflection;\
        o_PP_CAT(name,__LINE__)() \
            {\
            phantom::reflection::Types::currentInstalledClass->addNestedTypedef(#name, phantom::typeByName(#part0","#part1","#part2, phantom::reflection::Types::currentInstalledClass));\
            }\
        } o_PP_CAT(name,__LINE__);

#define o_nested_typedef_5(part0, part1, part2, part3, name)\
class o_PP_CAT(name,__LINE__) \
        {\
        friend class enclosed_reflection;\
        o_PP_CAT(name,__LINE__)() \
            {\
            phantom::reflection::Types::currentInstalledClass->addNestedTypedef(#name, phantom::typeByName(#part0","#part1","#part2","#part3, phantom::reflection::Types::currentInstalledClass));\
            }\
        } o_PP_CAT(name,__LINE__);

#define o_nested_typedef_6(part0, part1, part2, part3, part4, name)\
class o_PP_CAT(name,__LINE__) \
        {\
        friend class enclosed_reflection;\
        o_PP_CAT(name,__LINE__)() \
            {\
            phantom::reflection::Types::currentInstalledClass->addNestedTypedef(#name, phantom::typeByName(#part0","#part1","#part2","#part3","#part4, phantom::reflection::Types::currentInstalledClass));\
            }\
        } o_PP_CAT(name,__LINE__);

#define o_default_template_argument_type(parameter, ...)\
class o_PP_CAT(parameter,__LINE__) \
        {\
        friend class enclosed_reflection;\
        o_PP_CAT(parameter,__LINE__)() \
            {\
            phantom::reflection::Types::currentInstalledTemplateSpecialization->setDefaultArgument(#parameter, phantom::typeByName(#__VA_ARGS__, phantom::reflection::Types::currentInstalledClass));\
            }\
        } o_PP_CAT(parameter,__LINE__);
        */

#define o_function(_returntype_, _name_, _parameters_, ...) \
    static struct o_PP_CAT(g_reflection_function_registration_##_name_, __COUNTER__)\
    {\
        virtual void registerElement()\
        {\
            phantom::reflection::Namespace* pNamespace = phantom::globalNamespace();\
            pNamespace->addFunction(\
                phantom::reflection::native::TNativeFunctionProvider<_returntype_ _parameters_>::CreateFunction(#_name_, phantom::reflection::Signature::Create(o_PP_QUOTE(_returntype_)o_PP_QUOTE(_parameters_), nullptr, pNamespace), _name_,##__VA_ARGS__)\
            );\
        }\
    } o_PP_CAT(g_reflection_function_registration_##_name_, __COUNTER__);\

#define o_functionN(_namespace_, _returntype_, _name_, _parameters_, ...)\
    o_namespace _namespace_\
    static struct o_PP_CAT(g_reflection_function_registration_##_name_, __LINE__) : public phantom::dynamic_initializer_handle::deferred_registrer_base\
    {\
        virtual void registerElement()\
        {\
            phantom::reflection::Namespace* pNamespace = phantom::namespaceByName(o_PP_QUOTE_SCOPE(_namespace_));\
            pNamespace->addFunction(\
                phantom::reflection::native::TNativeFunctionProvider<_returntype_ _parameters_>::CreateFunction(#_name_, phantom::reflection::Signature::Create(o_PP_QUOTE(_returntype_)o_PP_QUOTE(_parameters_), nullptr, pNamespace), o_PP_CREATE_SCOPE _namespace_ :: _name_,##__VA_ARGS__)\
            );\
        }\
    } o_PP_CAT(g_reflection_function_registration_##_name_, __LINE__);\

#define o_variable(_type_, _name_, _range_, ...) \
    static struct o_PP_CAT(g_reflection_variable_registration_##_name_, __LINE__) : public phantom::dynamic_initializer_handle::deferred_registrer_base\
    {\
        virtual void registerElement()\
        {\
            phantom::reflection::Namespace* pNamespace = phantom::globalNamespace();\
            pNamespace->addVariable(o_dynamic_proxy_new(phantom::reflection::native::TNativeVariable<_type_>)(phantom::typeOf<_type_>(), #_name_, &_name_, o_range _range_,##__VA_ARGS__));\
        }\
    } o_PP_CAT(g_reflection_variable_registration_##_name_, __LINE__);

#define o_variableN(_namespace_, _type_, _name_, _range_, ...) \
    o_namespace _namespace_\
    static struct o_PP_CAT(g_reflection_variable_registration_##_name_, __LINE__) : public phantom::dynamic_initializer_handle::deferred_registrer_base\
    {\
        virtual void registerElement()\
        {\
            phantom::reflection::Namespace* pNamespace = phantom::namespaceByName(o_PP_QUOTE_SCOPE(_namespace_));\
            pNamespace->addVariable(o_dynamic_proxy_new(phantom::reflection::native::TNativeVariable<_type_>)(phantom::typeOf<_type_>(), #_name_, &o_PP_CREATE_SCOPE _namespace_ :: _name_, o_range _range_,##__VA_ARGS__));\
        }\
    } o_PP_CAT(g_reflection_variable_registration_##_name_, __LINE__);

