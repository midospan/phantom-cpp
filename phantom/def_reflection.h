#ifndef o_phantom_reflection_h__
#define o_phantom_reflection_h__

o_namespace_begin(phantom, reflection)


o_export void initializeSystem();


struct o_export Types
{
private:
#if defined(TYPE_VOID)
#error VOID defined
#endif
    static Type* TYPE_VOID;
    static Type* TYPE_CHAR;
    static Type* TYPE_UNSIGNED_CHAR;
    static Type* TYPE_SIGNED_CHAR;
    static Type* TYPE_SHORT;
    static Type* TYPE_UNSIGNED_SHORT;
    static Type* TYPE_INT;
    static Type* TYPE_UNSIGNED_INT;
    static Type* TYPE_LONG;
    static Type* TYPE_UNSIGNED_LONG;
    static Type* TYPE_LONG_LONG;
    static Type* TYPE_UNSIGNED_LONG_LONG;
    static Type* TYPE_FLOAT;
    static Type* TYPE_DOUBLE;
    static Type* TYPE_LONG_DOUBLE;
    static Type* TYPE_BOOL;
    static Type* TYPE_STRING;
    static Type* TYPE_SIGNAL_T;
    static Type* TYPE_NULLPTR_T;
    static Type* TYPE_WCHAR_T;
    static Type* TYPE_VOID_PTR;

public:
    template<typename t_Ty>
    inline static Type* get();

    static phantom::modifiers_t                           currentModifiers;
    static phantom::reflection::ClassType*             currentInstalledClass;
    static phantom::reflection::AnonymousSection*      currentInstalledAnonymousSection;
    static phantom::reflection::Namespace*             currentInstalledNamespace;
    static phantom::reflection::TemplateSpecialization*currentInstalledTemplateSpecialization;
    static phantom::modifiers_t                           savedModifiers;
    static phantom::reflection::ClassType*             savedInstalledClass;
    static phantom::reflection::Namespace*             savedInstalledNamespace;
    static phantom::reflection::TemplateSpecialization*savedInstalledTemplateSpecialization;

private:
    friend o_export void phantom::reflection::initializeSystem();
    static void Install();
    static void Register();
};

// Forward declarations
template<typename t_Ty>
struct base_classes_adder;

template<typename t_Ty, bool t_has_new_vtable>
struct vtable_adder_helper
{
    static void apply(Class* a_pClass)
    {
        static_cast<native::TType_<t_Ty>*>(a_pClass)->addNewVirtualMemberFunctionTable();
    }
};

template<typename t_Ty>
struct vtable_adder_helper<t_Ty, false>
{
    static void apply(Class* a_pClass)
    {

    }
};

template<typename t_Ty>
struct vtable_adder : public vtable_adder_helper<t_Ty, has_new_vtable<t_Ty>::value>
{

};


namespace detail
{

    enum meta_type_id
    {
        meta_pointer_type,
        meta_data_pointer_type,
        meta_function_pointer_type,

        meta_member_pointer_type,
        meta_data_member_pointer_type,
        meta_member_function_pointer_type,

        meta_reference_type,

        meta_fundamental_type,
        meta_arithmetic_type,
        meta_integral_type,
        meta_floating_point_type,

        meta_structure,
        meta_class,
        meta_union,

        meta_special,

        meta_enum,

        meta_array,

        meta_container,

        meta_nullptr_type,

        meta_todo,
    };

    template<typename t_Ty>
    struct meta_type_id_of
    {
        const static int value =
            boost::is_array<t_Ty>::value
            ? meta_array
            : boost::is_enum<t_Ty>::value
            ? meta_enum
            : (boost::is_void<t_Ty>::value)
            ? meta_special
            : phantom::is_data_pointer<t_Ty>::value
            ? meta_data_pointer_type
            : boost::is_pointer<t_Ty>::value
            ? meta_function_pointer_type
            : ::boost::is_floating_point<t_Ty>::value
            ? meta_floating_point_type
            : ::phantom::is_nullptr_t<t_Ty>::value
            ? meta_nullptr_type
            : ::boost::is_integral<t_Ty>::value
            ? meta_integral_type
            : ::boost::is_member_function_pointer<t_Ty>::value
            ? meta_member_function_pointer_type
            : ::boost::is_member_object_pointer<t_Ty>::value
            ? meta_data_member_pointer_type
            : is_container<t_Ty>::value
            ? meta_container
            : boost::is_union<t_Ty>::value
            ? meta_union
            : boost::is_class<t_Ty>::value
            ? is_structure<t_Ty>::value
            ? meta_structure
            : meta_class
            : meta_todo;
    };


    template<typename t_Ty, int t_id>
    struct base_meta_class_type_of_helper;

    template<typename t_Ty, bool t_is_fundamental>
    struct canonical_meta_class_type_of_helper
    {
        typedef PrimitiveType type;
    };

    template<typename t_Ty>
    struct canonical_meta_class_type_of_helper<t_Ty, false>
    {
        typedef o_NESTED_TYPE base_meta_class_type_of<t_Ty>::type type;
    };

    template<typename t_Ty, bool t_is_map, bool t_is_set, bool t_is_sequential>
    struct meta_container_class_type_of_helper
    {
        typedef Class type;
    };

    template<typename t_Ty>
    struct meta_container_class_type_of_helper<t_Ty, true, false, false>
    {
        typedef native::TMapContainerClass<t_Ty> type;
    };

    template<typename t_Ty>
    struct meta_container_class_type_of_helper<t_Ty, false, true, false>
    {
        typedef native::TSetContainerClass<t_Ty> type;
    };

    template<typename t_Ty>
    struct meta_container_class_type_of_helper<t_Ty, false, false, true>
    {
        typedef native::TSequentialContainerClass<t_Ty> type;
    };

    template<typename t_Ty>
    struct meta_container_class_type_of : public meta_container_class_type_of_helper<t_Ty, is_map_container<t_Ty>::value, is_set_container<t_Ty>::value, is_sequential_container<t_Ty>::value>
    {
        o_static_assert(is_container<t_Ty>::value);
    };


#define x_specialize____meta_type_base_class_solver(_meta_type_id_,...)\
    template<typename t_Ty>\
    struct base_meta_class_type_of_helper<t_Ty, _meta_type_id_>\
    {\
    typedef __VA_ARGS__ type;\
    };

    x_specialize____meta_type_base_class_solver(meta_container, o_NESTED_TYPE meta_container_class_type_of<t_Ty>::type)

        x_specialize____meta_type_base_class_solver(meta_pointer_type,phantom::reflection::PointerType)
        x_specialize____meta_type_base_class_solver(meta_data_pointer_type,phantom::reflection::DataPointerType)
        x_specialize____meta_type_base_class_solver(meta_function_pointer_type,phantom::reflection::Type)
        x_specialize____meta_type_base_class_solver(meta_member_pointer_type,phantom::reflection::Type)
        x_specialize____meta_type_base_class_solver(meta_data_member_pointer_type,phantom::reflection::Type)
        x_specialize____meta_type_base_class_solver(meta_member_function_pointer_type,phantom::reflection::Type)
        x_specialize____meta_type_base_class_solver(meta_reference_type,phantom::reflection::ReferenceType)
        x_specialize____meta_type_base_class_solver(meta_fundamental_type,phantom::reflection::native::TFundamentalType<t_Ty>)
        x_specialize____meta_type_base_class_solver(meta_arithmetic_type,phantom::reflection::native::TArithmeticType<t_Ty>)
        x_specialize____meta_type_base_class_solver(meta_floating_point_type,phantom::reflection::native::TFloatingPointType<t_Ty>)
        x_specialize____meta_type_base_class_solver(meta_integral_type,phantom::reflection::native::TIntegralType<t_Ty>)
        x_specialize____meta_type_base_class_solver(meta_nullptr_type,phantom::reflection::native::TPrimitiveType<t_Ty>)
        x_specialize____meta_type_base_class_solver(meta_structure,phantom::reflection::Structure)
        x_specialize____meta_type_base_class_solver(meta_union,phantom::reflection::Union)
        x_specialize____meta_type_base_class_solver(meta_class,phantom::reflection::Class)
        x_specialize____meta_type_base_class_solver(meta_special,phantom::reflection::native::TPrimitiveType<t_Ty>)
        x_specialize____meta_type_base_class_solver(meta_enum,phantom::reflection::Enum)
        x_specialize____meta_type_base_class_solver(meta_todo,phantom::reflection::Type)
        x_specialize____meta_type_base_class_solver(meta_array,phantom::reflection::ArrayType)

#undef x_specialize____meta_type_base_class_solver

    enum advanced_pointer_type
    {
        member_function_pointer,
        function_pointer,
        member_object_pointer,
    };

    template<typename t_Ty, advanced_pointer_type t_advanced_pointer_type>
    struct meta_class_type_of_advanced_pointer;


    template<typename t_Ty>
    struct meta_class_type_of_advanced_pointer<t_Ty, member_function_pointer>
    {
        typedef phantom::reflection::native::TNativeMemberFunctionPointerType<t_Ty> type;
    };

    template<typename t_Ty>
    struct meta_class_type_of_advanced_pointer<t_Ty, function_pointer>
    {
        o_static_assert(is_function_pointer<t_Ty>::value);
        typedef phantom::reflection::native::TNativeFunctionPointerType<t_Ty> type;
    };

    template<typename t_Ty>
    struct meta_class_type_of_advanced_pointer<t_Ty, member_object_pointer>
    {
        typedef phantom::reflection::native::TNativeDataMemberPointerType<t_Ty> type;
    };

    template<typename t_Ty, bool is_advanced_pointer, int t_TemplateNestedModifiers = 0>
    struct meta_class_type_of_helper : public meta_class_type_of_advanced_pointer<t_Ty
        , boost::is_member_function_pointer<t_Ty>::value 
            ? member_function_pointer
            : boost::is_member_object_pointer<t_Ty>::value 
                ? member_object_pointer
                : function_pointer>
    {
    };

    template<typename t_Ty, int t_TemplateNestedModifiers>
    struct meta_class_type_of_helper<t_Ty, false, t_TemplateNestedModifiers>
    {
        typedef phantom::reflection::native::TType<t_Ty, t_TemplateNestedModifiers> type;
    };

} // namespace detail

template<typename t_Ty, int t_TemplateNestedModifiers = 0>
struct meta_class_type_of 
    : public detail::meta_class_type_of_helper<t_Ty, boost::is_member_pointer<t_Ty>::value OR phantom::is_function_pointer<t_Ty>::value, t_TemplateNestedModifiers>
{
};

template<typename t_Ty>
struct base_meta_class_type_of
    : public detail::base_meta_class_type_of_helper<t_Ty, detail::meta_type_id_of<t_Ty>::value>
{
};

template<typename t_Ty>
struct canonical_meta_class_type_of
    : public detail::canonical_meta_class_type_of_helper<t_Ty, boost::is_fundamental<t_Ty>::value>
{
};

template<typename t_Ty>
struct meta_class_type_of<t_Ty*, 0>
{
    typedef DataPointerType type;
};

template<typename t_Ty>
struct meta_class_type_of<t_Ty&, 0>
{
    typedef ReferenceType type;
};

template<typename t_Ty>
struct meta_class_type_of <t_Ty const, 0>
{
    typedef ConstType type;
};

template<typename t_Ty, size_t t_size>
struct meta_class_type_of <t_Ty[t_size], 0>
{
    typedef ArrayType type;
};

namespace native { template<typename t_Ty, int> class TType; }

template<typename t_Ty>
struct template_specialization_registrer
{
    inline template_specialization_registrer() ;
};

template<typename t_Ty>
struct typedef_registrer
{
    typedef_registrer( const char* a_strScope, const char* a_strTypedef )
    {
        dynamic_initializer()->setActive(true);
        phantom::reflection::Type* pType = phantom::typeByName(a_strScope);
        phantom::reflection::Type* pTypedefType = phantom::typeOf<t_Ty>();
        if(pType)
        {
            pType->addNestedTypedef(a_strTypedef, pTypedefType);
        }
        else
        {
            Namespace* pNamespace = phantom::globalNamespace()->findOrCreateNamespaceCascade(a_strScope);
            o_assert(pNamespace);
            pNamespace->addTypedef(a_strTypedef, pTypedefType);
        }
        dynamic_initializer()->setActive(false);
    }

    typedef_registrer( const char* a_strTypedef )
    {
        dynamic_initializer()->setActive(true);
        phantom::globalNamespace()->addTypedef(a_strTypedef, phantom::typeOf<t_Ty>());
        dynamic_initializer()->setActive(false);
    }
};

struct o_export namespace_registrer
{
    namespace_registrer(const char* a_strNamespace);
};

struct o_export namespace_alias_registrer
{
    namespace_alias_registrer(const char* a_strNamespace, const char* a_strAlias, const char* a_strAliasedNamespace);
    namespace_alias_registrer(const char* a_strAlias, const char* a_strAliasedNamespace);
};

struct o_export using_registrer
{
    using_registrer(const char* a_strWhere, const char* a_strElement);
};

struct o_export friend_registrer
{
    friend_registrer(const char* a_strWhere, const char* a_strFriend);
};

template<typename t_Ty>
struct custom_setup
{
    o_forceinline static void apply(uint step)
    {
        /* by default do nothing ; specialize for your type to customize its reflection setup*/
    }
};

    template<typename t_Ty, boolean t_has_module>
    struct meta_class_type_of_helper_;


#define o_max_type_name_of_counter_recursive_derivation 100

    template<typename t_Ty>
    struct base_adder ;

    namespace detail
    {

        template<typename t_Ty, bool t_has_module>
        struct type_of_helper;

        template<typename t_Ty>
        struct type_of_builder
        {
            typedef o_NESTED_TYPE meta_class_type_of<t_Ty>::type meta_type;
            static bool build(meta_type** built, const string& qualifiedDecoratedName)
            {
                static meta_type* s_pType = NULL;
                if(s_pType == NULL)
                {
                    // We check if the type hasn't been already registered through another compilation unit template instanciation
                    s_pType = static_cast<meta_type*>(typeByName(qualifiedDecoratedName));
                    if(s_pType == NULL)
                    {
                        s_pType = new (phantom::allocator<meta_type>::allocate(o_memory_stat_insert_arguments)) meta_type(typeNameOf<t_Ty>());
                        if(meta_type::metaType == nullptr)
                        {
                            o_assert((boost::is_same<meta_type, o_NESTED_TYPE meta_class_type_of<Class>::type>::value));
                            meta_type::metaType = (decltype(meta_type::metaType))(s_pType); /// meta meta type (the meta type of the meta type of 'Class' is the meta type of class itself)
                        }
                        meta_type::metaType->install(s_pType, 0);
                        // Force installing proxy deleter (TODO : use meta programming to choose it automatically in the installer)
                        ((rtti_data&)rttiDataOf(s_pType, (size_t)0)).dynamic_delete_func = &dynamic_proxy_deleter<meta_type>::dynamicDelete;
                        meta_type::metaType->initialize(s_pType);
                        *built = s_pType;
                        return true;
                    }
                }
                *built = s_pType;
                return false;
            }
        };

        template<typename t_Ty>
        struct type_of_defined
        {
            typedef o_NESTED_TYPE meta_class_type_of<t_Ty>::type meta_type;
            static meta_type* object()
            {
                meta_type* pType = nullptr;
                const type_infos& typeInfos = type_infos_of<t_Ty>::object();
                const string& qualifiedDecoratedName = typeInfos.qualified_decorated_name();
                if(type_of_builder<t_Ty>::build(&pType, qualifiedDecoratedName))
                {
                    dynamic_initializer()->registerType(qualifiedDecoratedName, typeInfos.scope, pType);
                    phantom::detail::module_installer_registrer<t_Ty> registrer(pType);
                }
                return pType;
            }
        };
    } // namespace detail

    template<typename t_Ty>
    struct type_of
    {
        typedef o_NESTED_TYPE phantom::reflection::base_meta_class_type_of<t_Ty>::type meta_type;
        static meta_type* object()
        {
            static meta_type* s_pCache = nullptr;
            if(s_pCache == nullptr)
            {
                const string& qualifiedDecoratedName = qualifiedDecoratedTypeNameOf<t_Ty>();
                s_pCache = static_cast<meta_type*>(phantom::typeByName(qualifiedDecoratedName));
                o_warning(s_pCache, (string("Unknown declared type : '") + qualifiedDecoratedName + "', ensure it's registered with 'o_registerX' in any of your loaded module").c_str());
            }
            return s_pCache;
        }
    };

    template<typename t_Ty>
    struct type_of<t_Ty*>
    {
        static DataPointerType* object()
        {
            return type_of<t_Ty>::object()->pointerType();
        }
    };

    template<typename t_Ty>
    struct type_of<t_Ty&>
    {
        static ReferenceType* object()
        {
            return type_of<t_Ty>::object()->referenceType();
        }
    };

    template<typename t_Ty>
    struct type_of<t_Ty const>
    {
        static Type* object()
        {
            return type_of<t_Ty>::object()->constType();
        }
    };

    template<typename t_Ty, size_t t_size>
    struct type_of<t_Ty[t_size]>
    {
        static ArrayType* object()
        {
            return type_of<t_Ty>::object()->arrayType(t_size);
        }
    };

namespace detail
{
    template<typename t_Ty, bool t_has_destroyed_signal>
    class phantom_base_enclosed_reflection_helper
    {
        class proxy : public t_Ty
        {
        public:
            class sub_proxy
            {
            public:
                sub_proxy()
                {
                    phantom::reflection::Signature* pSignature = phantom::reflection::Signature::Create();
                    pSignature->setReturnType(Types::get<signal_t>());
                    phantom::reflection::Signal* pSignal = o_dynamic_proxy_new(phantom::reflection::native::TNativeSignal<t_Ty, phantom::signal_t()>)
                        ( "destroyed"
                        , pSignature
                        , &proxy::PHANTOM_CODEGEN_destroyed
                        , &proxy::PHANTOM_CODEGEN_m_slot_list_of_PHANTOM_CODEGEN_destroyed
                        , 0
                        );
                    phantom::typeOf<t_Ty>()->addSignal(pSignal);
                }
            };
        };

        typename proxy::sub_proxy m_Proxy;
    };


    template<typename t_Ty>
    class phantom_base_enclosed_reflection_helper<t_Ty, false>
    {
    public:
        phantom_base_enclosed_reflection_helper()
        {

        }
    };

    template<typename t_Ty>
    class phantom_base_enclosed_reflection : public phantom_base_enclosed_reflection_helper<t_Ty, has_destroyed_signal<t_Ty>::value>
    {
    public:
        phantom_base_enclosed_reflection()
        {
        }
    };

} // detail


o_namespace_end(phantom, reflection)


o_namespace_begin(phantom, state, native)

template<typename t_Ty>
class root_statechart;

o_namespace_end(phantom, state, native)



o_namespace_begin(phantom, reflection, detail)


template<typename t_Ty, bool t_is_class, int t_count>
struct base_classes_adder_helper
{

};

template<typename t_Ty>
struct base_classes_adder_helper<t_Ty, true, 0>
{
    o_forceinline static void apply(phantom::reflection::Class* a_pType){}
};

template<typename t_Ty>
struct base_classes_adder_helper<t_Ty, false, 0>
{
    o_forceinline static void apply(phantom::reflection::Type* a_pType){}
};

template<typename t_Ty, int t_count>
struct base_classes_adder_helper<t_Ty, true, t_count>
{
    o_forceinline static void apply(phantom::reflection::Class* a_pClass)
    {
        base_classes_adder_helper<t_Ty, true, t_count-1>::apply(a_pClass);
        base_class_adder<t_Ty, o_NESTED_TYPE base_class_of<t_Ty, t_count-1>::type>::apply(a_pClass);
    }
};

template<typename t_Ty, typename t_STy>
struct base_class_adder
{
    static void apply(phantom::reflection::Class* a_pClass)
    {
#if (o_COMPILER != o_COMPILER_GCC) && (o_COMPILER != o_COMPILER_CLANG)
        enum { is_virtual_base_of = boost::is_virtual_base_of<t_STy,t_Ty>::value };
        o_static_assert_msg(!is_virtual_base_of, "phantom reflection system doesn't support virtual inheritance ... yet ... or never");
#endif
        t_Ty* pClass = reinterpret_cast<t_Ty*>((void*)1);
        t_STy* pBaseClass = static_cast<t_STy*>(pClass);
        phantom::uint uiOffset = reinterpret_cast<phantom::uint>(reinterpret_cast<void*>(pBaseClass))-1;
        a_pClass->addBaseClass(type_of<t_STy>::object(), uiOffset);
    }
};

struct template_signature_parameter_name_phantom
{
    o_define_template_signature_parameter_name_phantom(boolean)
    o_define_template_signature_parameter_name_phantom(uchar)
    o_define_template_signature_parameter_name_phantom(schar)
    o_define_template_signature_parameter_name_phantom(ushort)
    o_define_template_signature_parameter_name_phantom(sshort)
    o_define_template_signature_parameter_name_phantom(uint)
    o_define_template_signature_parameter_name_phantom(sint)
    o_define_template_signature_parameter_name_phantom(size_t)
    o_define_template_signature_parameter_name_phantom(ulong)
    o_define_template_signature_parameter_name_phantom(slong)
    o_define_template_signature_parameter_name_phantom(longlong)
    o_define_template_signature_parameter_name_phantom(ulonglong)
};


struct template_signature_parameter_phantom
{
    o_define_template_signature_parameter_phantom(boolean)
    o_define_template_signature_parameter_phantom(uchar)
    o_define_template_signature_parameter_phantom(schar)
    o_define_template_signature_parameter_phantom(ushort)
    o_define_template_signature_parameter_phantom(sshort)
    o_define_template_signature_parameter_phantom(uint)
    o_define_template_signature_parameter_phantom(sint)
    o_define_template_signature_parameter_phantom(size_t)
    o_define_template_signature_parameter_phantom(ulong)
    o_define_template_signature_parameter_phantom(slong)
    o_define_template_signature_parameter_phantom(longlong)
    o_define_template_signature_parameter_phantom(ulonglong)
};

o_define_template_signature_parameter(bool)
o_define_template_signature_parameter(char)
o_define_template_signature_parameter(short)
o_define_template_signature_parameter(int)
o_define_template_signature_parameter(long)
o_define_template_signature_parameter(size_t)
o_define_template_signature_parameter(uchar)
o_define_template_signature_parameter(schar)
o_define_template_signature_parameter(ushort)
o_define_template_signature_parameter(sshort)
o_define_template_signature_parameter(uint)
o_define_template_signature_parameter(sint)
o_define_template_signature_parameter(ulong)
o_define_template_signature_parameter(slong)
o_define_template_signature_parameter(longlong)
o_define_template_signature_parameter(ulonglong)
o_define_template_signature_parameter(unsigned)


template<ulonglong value>
class template_signature_parameter_enum
{
public:
    static phantom::reflection::LanguageElement* object();
};


template<ulonglong value>
class template_signature_parameter_name_enum
{
    static phantom::string qualifiedDecoratedName()
    {
        return phantom::lexical_cast<phantom::string>(value);
    }
};

template<typename t_Ty>
struct template_signature_parameter_typename : public type_of<t_Ty>
{
};

template<typename t_Ty>
struct template_signature_parameter_name_typename
{
    static phantom::string qualifiedDecoratedName()
    {
        return qualifiedDecoratedTypeNameOf<t_Ty>();
    }
};

template<typename t_Ty>
struct template_signature_parameter_class : public template_signature_parameter_typename<t_Ty>
{
};

template<typename t_Ty>
class template_signature_parameter_name_class : public template_signature_parameter_name_typename<t_Ty>
{
};


























template<typename t_Ty>
struct member_registrer : public t_Ty
{
    struct raii;
};

template<typename t_Ty, bool t_has_statechart>
struct statechart_registrer_helper
{
    struct raii
    {
    };
};

template<typename t_Ty>
struct statechart_registrer : public statechart_registrer_helper<t_Ty, has_statechart<t_Ty>::value>
{
};

template<typename t_Ty>
struct statechart_registrer_helper <t_Ty, true>
{
    struct raii
    {
        phantom::statechart<t_Ty,t_Ty> sc;
    };
};

template<typename t_Ty>
struct default_class_setup : public t_Ty
{
    static void apply(uint step)
    {
        switch(step)
        {
        case o_global_value_SetupStepIndex_Reflection:
            {
                o_NESTED_TYPE member_registrer<t_Ty>::raii raii;
                (void)raii;
            }
            break;
        case o_global_value_SetupStepIndex_StateChart:
            {
                o_NESTED_TYPE statechart_registrer<t_Ty>::raii raii;
                (void)raii;
            }
            break;
        default:
            custom_setup<t_Ty>::apply(step);
        }
    }
};

template<typename t_Ty>
struct setup : public default_class_setup<t_Ty>
{

};

template<typename t_Ty>
struct base_setup : public t_Ty
{
    static void apply()
    {

    }
};

template<typename t_Ty>
struct base_traits;

template<typename t_Ty>
struct dynamic_caster
{
    static void* apply(Class* a_pTargetClass, t_Ty* a_pBase)
    {
        return base_traits<t_Ty>::cast(a_pTargetClass,a_pBase);
    }
};

template<typename t_Ty, bool t_is_class_and_has_module>
struct template_specialization_of_helper
{
    static phantom::reflection::TemplateSpecialization* object()
    {
        return NULL;
    }
};

template<typename t_Ty>
struct template_specialization_of_helper<t_Ty,true>
{
    static phantom::reflection::TemplateSpecialization* object()
    {
        return type_of<t_Ty>::object()->getTemplateSpecialization();
    }
};

o_namespace_end(phantom, reflection, detail)

o_namespace_begin(phantom, reflection)


template<typename t_Ty>
struct base_classes_adder
    : public detail::base_classes_adder_helper<t_Ty, boost::is_class<t_Ty>::value AND NOT(phantom::is_signal_t<t_Ty>::value), base_class_count_of<t_Ty>::value>
{

};

template<typename t_Ty>
struct template_specialization_adder
{
    o_forceinline static void  apply(phantom::reflection::Type* a_pType)
    {
    }
};

template<typename t_Ty>
struct template_specialization_of : public detail::template_specialization_of_helper<t_Ty, boost::is_class<t_Ty>::value AND phantom::has_module<t_Ty>::value> {};


template<typename t_Ty>
           inline Type* Types::get() {
               return type_of<t_Ty>::object(); }
template<> inline Type* Types::get<void>() { return TYPE_VOID; }
template<> inline Type* Types::get<char>() { return TYPE_CHAR; }
template<> inline Type* Types::get<unsigned char>() { return TYPE_UNSIGNED_CHAR; }
template<> inline Type* Types::get<signed char>() { return TYPE_SIGNED_CHAR; }
template<> inline Type* Types::get<short>() { return TYPE_SHORT; }
template<> inline Type* Types::get<unsigned short>() { return TYPE_UNSIGNED_SHORT; }
template<> inline Type* Types::get<int>() { return TYPE_INT; }
template<> inline Type* Types::get<unsigned int>() { return TYPE_UNSIGNED_INT; }
template<> inline Type* Types::get<long>() { return TYPE_LONG; }
template<> inline Type* Types::get<unsigned long>() { return TYPE_UNSIGNED_LONG; }
template<> inline Type* Types::get<long long>() { return TYPE_LONG_LONG; }
template<> inline Type* Types::get<unsigned long long>() { return TYPE_UNSIGNED_LONG_LONG; }
template<> inline Type* Types::get<float>() { return TYPE_FLOAT; }
template<> inline Type* Types::get<double>() { return TYPE_DOUBLE; }
template<> inline Type* Types::get<long double>() { return TYPE_LONG_DOUBLE; }
template<> inline Type* Types::get<bool>() { return TYPE_BOOL; }
template<> inline Type* Types::get<string>() { return TYPE_STRING; }
template<> inline Type* Types::get<signal_t>() { return TYPE_SIGNAL_T; }
template<> inline Type* Types::get<std::nullptr_t>() { return TYPE_NULLPTR_T; }
#if o_HAS_BUILT_IN_WCHAR_T == 1
template<> inline Type* Types::get<wchar_t>() { return TYPE_WCHAR_T; }
#endif
template<> inline Type* Types::get<void*>() { return TYPE_VOID_PTR; }

namespace detail
{

template<typename t_ValueType, typename t_SelfType>
struct data_member_unambiguitor
{
    typedef t_ValueType value_type;
    typedef t_SelfType self_type;
    template<typename t_AnonymousUnion>
    inline static void set_union_value(t_AnonymousUnion& a_Union, value_type* a_StaticMember)
    {
        a_Union.static_ = a_StaticMember;
    }
    template<typename t_Owner, typename t_AnonymousUnion>
    inline static void set_union_value(t_AnonymousUnion& a_Union, value_type (t_Owner::*a_InstanceMember) )
    {
        a_Union.original = a_InstanceMember;
    }
    template<typename t_AnonymousUnion>
    inline static value_type* get_union_value(t_AnonymousUnion& a_Union, value_type* a_StaticMember)
    {
        return a_Union.static_;
    }
    typedef value_type (self_type::*mp);
    template<typename t_Owner, typename t_AnonymousUnion>
    inline static mp get_union_value(t_AnonymousUnion& a_Union, value_type (t_Owner::*a_InstanceMember) )
    {
        return a_Union.hacked;
    }
};

}

#define o_specialize_fundamental_type_infos_of(_type_) \
    template<>\
    struct type_infos_of<_type_>\
{\
    static const type_infos& object()\
    {\
        static type_infos ti("",o_PP_QUOTE(_type_),"");\
        return ti;\
    }\
};

o_specialize_fundamental_type_infos_of(char);
o_specialize_fundamental_type_infos_of(unsigned char);
o_specialize_fundamental_type_infos_of(signed char);
#if o_HAS_BUILT_IN_WCHAR_T
o_specialize_fundamental_type_infos_of(wchar_t);
#endif
o_specialize_fundamental_type_infos_of(short);
o_specialize_fundamental_type_infos_of(unsigned short);
o_specialize_fundamental_type_infos_of(int);
o_specialize_fundamental_type_infos_of(unsigned int);
o_specialize_fundamental_type_infos_of(long);
o_specialize_fundamental_type_infos_of(unsigned long);
o_specialize_fundamental_type_infos_of(long long);
o_specialize_fundamental_type_infos_of(unsigned long long);
o_specialize_fundamental_type_infos_of(float);
o_specialize_fundamental_type_infos_of(double);
o_specialize_fundamental_type_infos_of(long double);
o_specialize_fundamental_type_infos_of(bool);
o_specialize_fundamental_type_infos_of(void);

template<>
struct type_infos_of<std::nullptr_t>
{
    static const type_infos& object()
    {
        static type_infos ti("std","nullptr_t","");
        return ti;
    }
};

o_namespace_end(phantom, reflection)

o_namespace_begin(phantom)

template <typename t_Ty>
o_forceinline o_NESTED_TYPE phantom::reflection::canonical_meta_class_type_of<t_Ty>::type* typeOf()
{
    static o_NESTED_TYPE phantom::reflection::canonical_meta_class_type_of<t_Ty>::type* s_pInstance = nullptr;
    if(s_pInstance == nullptr)
    {
        s_pInstance = static_cast<o_NESTED_TYPE phantom::reflection::canonical_meta_class_type_of<t_Ty>::type*>(phantom::reflection::Types::get<t_Ty>());
    }
    return s_pInstance;
}

o_namespace_end(phantom)

#endif // o_phantom_reflection_h__
