
#define o_property_7(_type_, _name_, _set_member_function_, _get_member_function_, _signal_, _modifiers_, _serialization_mask_)\
class o_PP_CAT(_name_,__LINE__) \
    {\
    friend class enclosed_reflection;\
    enum {_name_};\
    o_PP_CAT(_name_,__LINE__)()\
        {\
        auto pGetMemberFunction = phantom::reflection::native::TNativeMemberFunctionProvider<phantom_proxy_generator_reflection_self_type,((_modifiers_&o_public)==o_public)?o_public:o_protected,_type_ ()>::CreateMemberFunction( \
        o_PP_QUOTE(_get_member_function_) \
        , phantom::reflection::native::TNativeSignatureProvider<PHANTOM_CODEGEN_reflection_counter_value, _type_ ()>::CreateSignature(o_PP_QUOTE(_type_)o_CS("()"), phantom::reflection::g_PHANTOM_RESERVED_template_specialization, phantom::reflection::g_PHANTOM_RESERVED_class) \
        , &phantom_proxy_generator_reflection_proxy_type::_get_member_function_ \
        ,((_modifiers_&o_public)==o_public)?o_public:o_protected);\
        pGetMemberFunction->asLanguageElement()->addCodeLocation(phantom::sourceFile(__FILE__));\
        phantom::reflection::g_PHANTOM_RESERVED_class->addMemberFunction(pGetMemberFunction);\
        auto pSetMemberFunction = phantom::reflection::native::TNativeMemberFunctionProvider<phantom_proxy_generator_reflection_self_type,phantom::detail::int_embedder<__VA_ARGS__>::value|o_slot_member_function,void (_type_)>::CreateMemberFunction( \
        o_PP_QUOTE(_set_member_function_) \
        , phantom::reflection::native::TNativeSignatureProvider<PHANTOM_CODEGEN_reflection_counter_value, void (_type_)>::CreateSignature(o_CS("void")o_PP_QUOTE((_type_)), phantom::reflection::g_PHANTOM_RESERVED_template_specialization, phantom::reflection::g_PHANTOM_RESERVED_class) \
        , &phantom_proxy_generator_reflection_proxy_type::_set_member_function_ \
        ,(((_modifiers_&o_public)==o_public)?o_public:o_protected)|o_slot_member_function);\
        pSetMemberFunction->asLanguageElement()->addCodeLocation(phantom::sourceFile(__FILE__));\
        phantom::reflection::g_PHANTOM_RESERVED_class->addMemberFunction(pSetMemberFunction);\
        phantom::reflection::Type* pType = phantom::typeByName(o_PP_QUOTE(_type_), phantom::reflection::g_PHANTOM_RESERVED_class);\
        o_assert(pType, o_PP_QUOTE(_type_)" type not registered");\
        phantom::reflection::Signal* pSignal = phantom::reflection::native::TNativePropertySignalProvider<PHANTOM_CODEGEN_reflection_counter_value, phantom_proxy_generator_reflection_self_type, _type_>::CreateSignal(\
        o_PP_QUOTE(_signal_)\
        , o_PP_QUOTE(_type_)\
        , &phantom_proxy_generator_reflection_proxy_type::_signal_\
        , &phantom_proxy_generator_reflection_proxy_type::PHANTOM_CODEGEN_m_slot_list_of_##_signal_\
        );\
        phantom::reflection::ValueMember* pValueMember = o_new(\
        phantom::reflection::native::TNativeProperty<\
        phantom_proxy_generator_reflection_self_type, _type_>) \
        ( o_PP_QUOTE(_name_)\
        , pType\
        , pSetMemberFunction->asInstanceMemberFunction()\
        , pGetMemberFunction->asInstanceMemberFunction()\
        , pSignal\
        , &phantom_proxy_generator_reflection_proxy_type::_set_member_function_\
        , &phantom_proxy_generator_reflection_proxy_type::_get_member_function_\
        , _serialization_mask_\
        , _modifiers_\
        );\
        pValueMember->addCodeLocation(phantom::sourceFile(__FILE__));\
        phantom::reflection::g_PHANTOM_RESERVED_class->addValueMember(pValueMember);\
        }\
    } o_PP_CAT(o_PP_CAT(_name_,__LINE__),_instance);


/// COLLECTIONS

#define o_collection_9(_type_, _name_, _add_member_function_, _remove_member_function_, _move_member_function_, _set_member_function_, _get_member_function_, _size_member_function_, _modifiers_)\
class o_PP_CAT(_name_,__LINE__) \
    {\
    friend class enclosed_reflection;\
    enum {_name_};\
    o_PP_CAT(_name_,__LINE__)()\
    {\
    phantom::reflection::Type* pType = phantom::typeByName(o_PP_QUOTE(_type_),phantom::reflection::g_PHANTOM_RESERVED_class);\
    o_assert(pType, o_PP_QUOTE(_type_)" type not registered");\
    phantom::reflection::Collection* pCollection = o_new(\
    phantom::reflection::native::TNativeCollection<\
    phantom_proxy_generator_reflection_self_type, _type_>) \
    ( o_PP_QUOTE(_name_)\
    , pType\
    , &phantom_proxy_generator_reflection_proxy_type::_add_member_function_\
    , &phantom_proxy_generator_reflection_proxy_type::_remove_member_function_\
    , &phantom_proxy_generator_reflection_proxy_type::_move_member_function_\
    , &phantom_proxy_generator_reflection_proxy_type::_set_member_function_\
    , &phantom_proxy_generator_reflection_proxy_type::_get_member_function_\
    , &phantom_proxy_generator_reflection_proxy_type::_size_member_function_\
    , _modifiers_\
    );\
    pCollection->addCodeLocation(phantom::sourceFile(__FILE__));\
    phantom::reflection::g_PHANTOM_RESERVED_class->addCollection(pCollection);\
    }\
} o_PP_CAT(o_PP_CAT(_name_,__LINE__),_instance);


#define o_extension(_extension_class_, ...) \
class o_PP_CAT(_name_,__LINE__) \
    {\
    friend class enclosed_reflection;\
    o_PP_CAT(_name_,__LINE__)()\
        {\
        phantom::reflection::g_PHANTOM_RESERVED_class->addExtension(o_new(_extension_class_)(phantom::detail::int_embedder<__VA_ARGS__>::value));\
        }\
    } o_PP_CAT(o_PP_CAT(_name_,__LINE__),_instance);


#    define o_signal(_name_, _parameterslist_, ...) \
class o_PP_CAT(_name_,__LINE__) \
        {\
        friend class enclosed_reflection;\
        o_PP_CAT(_name_,__LINE__)() \
            {\
            phantom::reflection::Signal* pSignal = o_new(\
            phantom::reflection::native::TNativeSignal<\
            phantom_proxy_generator_reflection_self_type\
            , phantom::signal_t _parameterslist_>) \
            ( o_PP_QUOTE(_name_)\
            , phantom::reflection::native::TNativeSignatureProvider<PHANTOM_CODEGEN_reflection_counter_value, phantom::signal_t _parameterslist_ >::CreateSignature(\
            "phantom::signal_t" o_PP_QUOTE(_parameterslist_)\
            , phantom::reflection::g_PHANTOM_RESERVED_template_specialization\
            , phantom::reflection::g_PHANTOM_RESERVED_class\
            )\
            , &phantom_proxy_generator_reflection_proxy_type::_name_\
            , &phantom_proxy_generator_reflection_proxy_type::PHANTOM_CODEGEN_m_slot_list_of_##_name_\
            , phantom::detail::int_embedder< __VA_ARGS__ >::value\
            );\
            pSignal->addCodeLocation(phantom::sourceFile(__FILE__));\
            phantom::reflection::g_PHANTOM_RESERVED_class->addSignal(pSignal);\
            }\
        } o_PP_CAT(o_PP_CAT(_name_,__LINE__),_instance);


#    define o_data_member_4(_type_, _name_, _modifiers_, _serialization_mask_) \
class o_PP_CAT(_name_,__LINE__)\
        {\
        friend class enclosed_reflection;\
        o_PP_CAT(_name_,__LINE__)()\
            {\
            phantom::reflection::Type* pType = phantom::typeByName(o_PP_QUOTE(_type_),phantom::reflection::g_PHANTOM_RESERVED_class);\
            o_assert(pType, o_PP_QUOTE(_type_)" type not registered");\
            if(pType == nullptr) { \
            o_exception(phantom::exception::t_unknown_reflection_type_exception<_type_> \
            , "dataMember type "#_type_" (or its pointed type if it's a pointer type) must be declared previously with the macro o_declare provided by phantom so that it can be considered as a phantom type"); \
            }\
            pType->addReferenceCodeLocation(phantom::sourceFile(__FILE__));\
            auto pDataMember = phantom::reflection::native::TNativeDataMemberProvider< phantom_proxy_generator_reflection_self_type, _modifiers_, _type_ >::CreateDataMember(o_PP_QUOTE(_name_), pType, &phantom_proxy_generator_reflection_proxy_type::_name_, _serialization_mask_, _modifiers_);\
            pDataMember->asLanguageElement()->addCodeLocation(phantom::sourceFile(__FILE__));\
            phantom::reflection::g_PHANTOM_RESERVED_class->addDataMember(pDataMember);\
            }\
        } o_PP_CAT(o_PP_CAT(_name_,__LINE__),_instance);


#    define o_member_function(_returntype_, _name_, _parameterslist_, ...) \
    enum { o_PP_CAT(o_PP_CAT(member_function,__LINE__),_index) = __COUNTER__ - PHANTOM_CODEGEN_reflection_counter_value - 1 };\
class o_PP_CAT(member_function,__LINE__) \
        {\
        friend class enclosed_reflection;\
        o_PP_CAT(member_function,__LINE__)() \
            {\
            auto pMemberFunction = phantom::reflection::native::TNativeMemberFunctionProvider<phantom_proxy_generator_reflection_self_type,phantom::detail::int_embedder<__VA_ARGS__>::value,_returntype_ _parameterslist_>::CreateMemberFunction( \
            o_PP_QUOTE(_name_) \
            , phantom::reflection::native::TNativeSignatureProvider<PHANTOM_CODEGEN_reflection_counter_value, _returntype_ _parameterslist_>::CreateSignature(o_PP_QUOTE(_returntype_)o_CS("")o_PP_QUOTE(_parameterslist_), phantom::reflection::g_PHANTOM_RESERVED_template_specialization, phantom::reflection::g_PHANTOM_RESERVED_class) \
            , &phantom_proxy_generator_reflection_proxy_type::_name_ \
            ,phantom::detail::int_embedder<__VA_ARGS__>::value);\
            pMemberFunction->asLanguageElement()->addCodeLocation(phantom::sourceFile(__FILE__));\
            phantom::reflection::g_PHANTOM_RESERVED_class->addMemberFunction(pMemberFunction);\
            }\
        } o_PP_CAT(member_function,__LINE__);

#    define o_slot(_returntype_, _name_, _parameterslist_, ...) \
    enum { o_PP_CAT(o_PP_CAT(slot,__LINE__),_index) = __COUNTER__ - PHANTOM_CODEGEN_reflection_counter_value - 1 };\
class o_PP_CAT(slot,__LINE__) \
        {\
        friend class enclosed_reflection;\
        o_PP_CAT(slot,__LINE__)() \
            {\
            auto pMemberFunction = phantom::reflection::native::TNativeMemberFunctionProvider<phantom_proxy_generator_reflection_self_type,phantom::detail::int_embedder<__VA_ARGS__>::value|o_slot_member_function,_returntype_ _parameterslist_>::CreateMemberFunction( \
            o_PP_QUOTE(_name_) \
            , phantom::reflection::native::TNativeSignatureProvider<PHANTOM_CODEGEN_reflection_counter_value, _returntype_ _parameterslist_>::CreateSignature(o_PP_QUOTE(_returntype_)o_CS("")o_PP_QUOTE(_parameterslist_), phantom::reflection::g_PHANTOM_RESERVED_template_specialization, phantom::reflection::g_PHANTOM_RESERVED_class) \
            , &phantom_proxy_generator_reflection_proxy_type::_name_ \
            ,phantom::detail::int_embedder<__VA_ARGS__>::value|o_slot_member_function);\
            pMemberFunction->asLanguageElement()->addCodeLocation(phantom::sourceFile(__FILE__));\
            phantom::reflection::g_PHANTOM_RESERVED_class->addMemberFunction(pMemberFunction);\
            }\
        } o_PP_CAT(slot,__LINE__);

#    define o_constructor(_parameterslist_, ...) \
class o_PP_CAT(o_global_value_Type,__LINE__) \
        {\
        friend class enclosed_reflection;\
        o_PP_CAT(o_global_value_Type,__LINE__)() \
            {\
            auto pConstructor = o_new(phantom::reflection::native::TNativeConstructor<phantom_proxy_generator_reflection_self_type _parameterslist_>)(o_PP_QUOTE(o_local_value_ShortType), o_new(phantom::reflection::Signature)(o_CS("_")o_PP_QUOTE(_parameterslist_), phantom::reflection::g_PHANTOM_RESERVED_template_specialization),phantom::detail::int_embedder<__VA_ARGS__>::value);\
            pConstructor->addCodeLocation(phantom::sourceFile(__FILE__));\
            phantom::reflection::g_PHANTOM_RESERVED_class->addConstructor(pConstructor);\
            }\
        } o_PP_CAT(o_PP_CAT(o_global_value_Type,__LINE__),_instance);

