#ifndef o_phantom_reflection_h__
#define o_phantom_reflection_h__

o_namespace_begin(phantom, reflection)

o_export void initializeSystem();

#define o_declare_meta_type(_type_)\
    template<typename t_Ty> friend struct detail::type_of_builder;\
    template<typename t_Ty> friend class native::TConstType;\
    template<typename t_Ty> friend class native::TType_;\
    friend struct phantom::reflection::Types;\
private:\
    static native::TType<_type_>* metaType

#define o_define_meta_type(_type_)\
    native::TType<_type_>* _type_::metaType

enum ETypeId
{
    e_void,
    e_char,
    e_unsigned_char,
    e_signed_char,
    e_short,
    e_unsigned_short,
    e_int,
    e_unsigned_int,
    e_long,
    e_unsigned_long,
    e_long_long,
    e_unsigned_long_long,
    e_float,
    e_double,
    e_long_double,
    e_bool,
    e_wchar_t,
    e_enum,
    e_signal_t,
    e_pointer,
    e_reference,
    e_array,
    e_struct,
    e_other,
};

struct o_export Types
{
private:
    static Type* VOID;
    static Type* CHAR;
    static Type* UNSIGNED_CHAR;
    static Type* SIGNED_CHAR;
    static Type* SHORT;
    static Type* UNSIGNED_SHORT;
    static Type* INT;
    static Type* UNSIGNED_INT;
    static Type* LONG;
    static Type* UNSIGNED_LONG;
    static Type* LONG_LONG;
    static Type* UNSIGNED_LONG_LONG;
    static Type* FLOAT;
    static Type* DOUBLE;
    static Type* LONG_DOUBLE;
    static Type* BOOL;
    static Type* STRING;
    static Type* SIGNAL_T;
    static Type* WCHAR_T;
    static Type* VOID_PTR;
     
public:
    template<typename t_Ty>
    inline static Type* get() { return detail::type_of_counter<t_Ty, o_read_compilation_counter>::object(); }

    static phantom::reflection::Class*                 currentInstalledClass;
    static phantom::reflection::Namespace*             currentInstalledNamespace;
    static phantom::reflection::TemplateSpecialization*currentInstalledTemplateSpecialization;

private:
    friend o_export void phantom::reflection::initializeSystem();
    static void Install();
    static void Register();
};

template<> inline Type* Types::get<void>() { return VOID; }
template<> inline Type* Types::get<char>() { return CHAR; }
template<> inline Type* Types::get<unsigned char>() { return UNSIGNED_CHAR; }
template<> inline Type* Types::get<signed char>() { return SIGNED_CHAR; }
template<> inline Type* Types::get<short>() { return SHORT; }
template<> inline Type* Types::get<unsigned short>() { return UNSIGNED_SHORT; }
template<> inline Type* Types::get<int>() { return INT; }
template<> inline Type* Types::get<unsigned int>() { return UNSIGNED_INT; }
template<> inline Type* Types::get<long>() { return LONG; }
template<> inline Type* Types::get<unsigned long>() { return UNSIGNED_LONG; }
template<> inline Type* Types::get<long long>() { return LONG_LONG; }
template<> inline Type* Types::get<unsigned long long>() { return UNSIGNED_LONG_LONG; }
template<> inline Type* Types::get<float>() { return FLOAT; }
template<> inline Type* Types::get<double>() { return DOUBLE; }
template<> inline Type* Types::get<long double>() { return LONG_DOUBLE; }
template<> inline Type* Types::get<bool>() { return BOOL; }
template<> inline Type* Types::get<string>() { return STRING; }
template<> inline Type* Types::get<signal_t>() { return SIGNAL_T; }
#if o_BUILT_IN_WCHAR_T == 1
template<> inline Type* Types::get<wchar_t>() { return WCHAR_T; }
#endif
template<> inline Type* Types::get<void*>() { return VOID_PTR; }

o_namespace_end(phantom, reflection)


#define o_reflection_register_class_type(_namespace_, ...) \
    phantom::reflection::class_type_registrer< _namespace_::__VA_ARGS__ > o_PP_CAT(g_reflection_registration_, __COUNTER__);

#define o_register_typedef(_typedef_) \
    phantom::reflection::typedef_registrer<_typedef_>  o_PP_CAT(g_reflection_registration_##_typedef_, __COUNTER__) (#_typedef_);

#define o_register_typedefN(_namespace_, _typedef_) \
    phantom::reflection::typedef_registrer<_namespace_::_typedef_>  o_PP_CAT(g_reflection_registration_##_typedef_, __COUNTER__) (#_namespace_, #_typedef_);

#define o_register_typedefNC(_namespace_, _class_, _typedef_) \
    o_register_typedefNC_helper(_namespace_, _class_, o_PP_CAT(g_reflection_registration_friend_##_typedef_, o_PP_IDENTITY o_PP_LEFT_PAREN __COUNTER__ o_PP_RIGHT_PAREN ), _typedef_)

#define o_register_typedefNC_helper(_namespace_, _class_, _friend_class_, _typedef_) \
    class _friend_class_ : public _namespace_::_class_\
    {\
    public:\
        typedef _typedef_ wrapped_typedef;\
    };\
    phantom::reflection::typedef_registrer<_friend_class_::wrapped_typedef>  o_PP_CAT(g_reflection_registration_##_typedef_, __COUNTER__) (#_namespace_"::"#_class_, #_typedef_);

#define o_register_typedefC(_class_, _typedef_) \
    o_register_typedefC_helper(_class_, o_PP_CAT(g_reflection_registration_friend_##_typedef_, o_PP_IDENTITY o_PP_LEFT_PAREN __COUNTER__ o_PP_RIGHT_PAREN ), _typedef_)

#define o_register_typedefC_helper(_class_, _friend_class_, _typedef_) \
    class _friend_class_ : public _class_\
    {\
    public:\
        typedef _typedef_ wrapped_typedef;\
    };\
    phantom::reflection::typedef_registrer<_friend_class_::wrapped_typedef>  o_PP_CAT(g_reflection_registration_##_typedef_, __COUNTER__) (#_class_, #_typedef_);

#define o_reflection_register_type(_namespace_, _type_) \
    phantom::reflection::type_reflection_registrer<_namespace_::_type_> o_PP_CAT(g_reflection_registration_##_type_,__COUNTER__) ;

#if o_COMPILER == o_COMPILER_VISUAL_STUDIO
#define o_register_namespace_alias(...) o_PP_CAT(o_PP_CAT(o_reflection_register_namespace_alias_, o_PP_NARG(__VA_ARGS__)),(__VA_ARGS__))
#else
#define o_register_namespace_alias(...) o_PP_CAT(o_reflection_register_namespace_alias_, o_PP_NARG(__VA_ARGS__))(__VA_ARGS__)
#endif

#define o_reflection_register_namespace_alias_2(_namespace_alias_, _namespace_aliased_) \
    phantom::reflection::namespace_alias_registrer  o_PP_CAT(g_reflection_registration_##_namespace_alias_, __COUNTER__) (#_namespace_alias_, #_namespace_aliased_);

#define o_reflection_register_namespace_alias_3( _namespace_, _namespace_alias_, _namespace_aliased_) \
    phantom::reflection::namespace_alias_registrer  o_PP_CAT(g_reflection_registration_##_namespace_alias_, __COUNTER__) (#_namespace_, #_namespace_alias_, #_namespace_aliased_);


#define o_reflection_register_type(_namespace_, _type_) \
    phantom::reflection::type_reflection_registrer<_namespace_::_type_> o_PP_CAT(g_reflection_registration_##_type_,__COUNTER__) ;

o_namespace_begin(phantom, reflection)

// Forward declarations
template<typename t_Ty, int t_counter>
struct super_classes_adder;

template<typename t_Ty>
struct meta_class_type_of;


namespace native { template<typename t_Ty> class TType; }

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
        Phantom::dynamic_initializer()->setActive(true);
        phantom::reflection::Type* pType = phantom::typeByName(a_strScope);
        phantom::reflection::Type* pTypedefType = phantom::typeOf<t_Ty>();
        if(pType)
        {
            pType->addNestedTypedef(a_strTypedef, pTypedefType);
        }
        else
        {
            Namespace* pNamespace = phantom::rootNamespace()->findOrCreateNamespaceCascade(a_strScope);
            o_assert(pNamespace);
            pNamespace->addTypedef(a_strTypedef, pTypedefType);
        }
        Phantom::dynamic_initializer()->setActive(false);
    }

    typedef_registrer( const char* a_strTypedef )
    {
        Phantom::dynamic_initializer()->setActive(true);
        phantom::rootNamespace()->addTypedef(a_strTypedef, phantom::typeOf<t_Ty>());
        Phantom::dynamic_initializer()->setActive(false);
    }
};

struct o_export namespace_alias_registrer
{
    namespace_alias_registrer(const char* a_strNamespace, const char* a_strAlias, const char* a_strAliasedNamespace);
    namespace_alias_registrer(const char* a_strAlias, const char* a_strAliasedNamespace);
};

template<typename t_Ty>
struct custom_setup
{
    o_forceinline static void apply(uint step)
    {
        /* by default do nothing ; specialize for your type to customize its reflection setup*/
    }
};


    template<typename t_Ty>
    struct type_reflection_registrer
    {
        o_static_assert_msg(phantom::has_module<t_Ty>::value, "registered class hasn't been declared with the reflection system");
        inline static void apply(Type* a_pType) ;
    };

    
    template<typename t_Ty, boolean t_has_module>
    struct meta_class_type_of_helper_;


#define o_max_type_name_of_counter_recursive_derivation 100

    namespace detail 
    {
        template<typename t_Ty, int t_init_counter, int t_counter = t_init_counter>
        struct type_name_of_counter;

        template<typename t_Ty, int t_init_counter, int t_counter>
        struct type_name_of_counter : public type_name_of_counter<t_Ty, t_init_counter, t_counter-1>
        {
            // IF YOU GET A RECURSIVE TEMPLATE ERROR HERE IT'S THAT
            // YOU DIDN'T DEFINE REFLECTION FOR YOUR TYPE OR YOU DIDN'T FORWARD DECLARE
            // IT USING THE :
            //                                      o_declare...
            //
            // INDEED, THESE MACRO INTERNALLY DECLARE THE TYPE NAME AND SOME PHANTOM HELPER TEMPLATE
            // o_static_assert(t_counter > o_max_type_name_of_counter_recursive_derivation);
            // 100 template iterations means probably that you uses a non-defined type as a member reflection type
            // and have almost 100 forward declaration of types between this undefined type forward declaration and
            // the reflection member declaration using this type
            // (WHICH BEGINS TO BE CONSEQUENT)
            //BOOST_STATIC_WARNING(t_counter == 200);
            // 200 template iterations means probably that you uses a non-defined type as a member reflection type
            // and have almost 200 forward declaration of types between this undefined type forward declaration and
            // the reflection member declaration using this type
            // (WHICH IS A LOT)
            //BOOST_STATIC_WARNING(t_counter == 100);
            // 200 template iterations means probably that you uses a non-defined type as a member reflection type
            // and have almost 200 forward declaration of types between this undefined type forward declaration and
            // the reflection member declaration using this type
            //(WHICH IS TOO MUCH ! something wrong with phantom or your use of phantom)
        };

        template<typename t_Ty, int t_init_counter>
        struct type_name_of_counter<t_Ty,t_init_counter,-1>
        {
            enum { assert_test = !boost::is_same<t_Ty,t_Ty>::value };
            o_static_assert_msg(assert_test, "t_Ty not declared with phantom o_declareX keywords, see which type on your compilation error");
        };
    
        template<typename t_Ty, int t_init_counter, int t_counter>
        struct type_name_of_counter<t_Ty*, t_init_counter, t_counter> : public type_name_of_counter<t_Ty, t_init_counter, t_counter>
        {
        public:
            o_forceinline static phantom::string decoratedName()
            {
                return phantom::string(type_name_of_counter<t_Ty,t_init_counter, t_counter>::decoratedName())+'*';
            }
            o_forceinline static phantom::string qualifiedDecoratedName()
            {
                return phantom::string(type_name_of_counter<t_Ty,t_init_counter, t_counter>::qualifiedDecoratedName())+'*';
            }
            o_forceinline static phantom::string name()
            {
                return phantom::string(type_name_of_counter<t_Ty,t_init_counter, t_counter>::name())+'*';
            }
            o_forceinline static phantom::string qualifiedName()
            {
                return phantom::string(type_name_of_counter<t_Ty,t_init_counter, t_counter>::qualifiedName())+'*';
            }
        };

        template<typename t_Ty, int t_init_counter, int t_counter>
        struct type_name_of_counter<t_Ty&, t_init_counter, t_counter> : public type_name_of_counter<t_Ty, t_init_counter, t_counter>
        {
        public:
            o_forceinline static phantom::string decoratedName()
            {
                return phantom::string(type_name_of_counter<t_Ty,t_init_counter, t_counter>::decoratedName())+'&';
            }
            o_forceinline static phantom::string qualifiedDecoratedName()
            {
                return phantom::string(type_name_of_counter<t_Ty,t_init_counter, t_counter>::qualifiedDecoratedName())+'&';
            }
            o_forceinline static phantom::string name()
            {
                return phantom::string(type_name_of_counter<t_Ty,t_init_counter, t_counter>::name())+'&';
            }
            o_forceinline static phantom::string qualifiedName()
            {
                return phantom::string(type_name_of_counter<t_Ty,t_init_counter, t_counter>::qualifiedName())+'&';
            }
        };

        template<typename t_Ty, int t_init_counter, int t_counter>
        struct type_name_of_counter<t_Ty const, t_init_counter, t_counter> : public type_name_of_counter<t_Ty, t_init_counter, t_counter>
        {
        public:
            o_forceinline static phantom::string decoratedName()
            {
                return phantom::string(type_name_of_counter<t_Ty,t_init_counter, t_counter>::decoratedName())+" const";
            }
            o_forceinline static phantom::string qualifiedDecoratedName()
            {
                return phantom::string(type_name_of_counter<t_Ty,t_init_counter, t_counter>::qualifiedDecoratedName())+" const";
            }
            o_forceinline static phantom::string name()
            {
                return phantom::string(type_name_of_counter<t_Ty,t_init_counter, t_counter>::name())+" const";
            }
            o_forceinline static phantom::string qualifiedName()
            {
                return phantom::string(type_name_of_counter<t_Ty,t_init_counter, t_counter>::qualifiedName())+" const";
            }
        };

        template<typename t_Ty, size_t t_size, int t_init_counter, int t_counter>
        struct type_name_of_counter<t_Ty[t_size], t_init_counter, t_counter> : public type_name_of_counter<t_Ty, t_init_counter, t_counter>
        {
        public:
            o_forceinline static phantom::string decoratedName()
            {
                return phantom::string(type_name_of_counter<t_Ty, t_init_counter, t_counter>::decoratedName())+'['+phantom::lexical_cast<string>(t_size)+']';
            }
            o_forceinline static phantom::string qualifiedDecoratedName()
            {
                return phantom::string(type_name_of_counter<t_Ty, t_init_counter, t_counter>::qualifiedDecoratedName())+'['+phantom::lexical_cast<string>(t_size)+']';
            }
            o_forceinline static phantom::string name()
            {
                return phantom::string(type_name_of_counter<t_Ty, t_init_counter, t_counter>::name())+'['+phantom::lexical_cast<string>(t_size)+']';
            }
            o_forceinline static phantom::string qualifiedName()
            {
                return phantom::string(type_name_of_counter<t_Ty, t_init_counter, t_counter>::qualifiedName())+'['+phantom::lexical_cast<string>(t_size)+']';
            }
        };

    } // namespace detail

    template <typename t_Ty>
    struct type_name_of : public detail::type_name_of_counter<t_Ty, o_read_compilation_counter>
    {
    };

    template <typename t_Ty>
    struct type_name_of<t_Ty*> : public type_name_of<t_Ty>
    {
    public:
        o_forceinline static phantom::string decoratedName()
        {
            return phantom::string(type_name_of<t_Ty>::decoratedName())+'*';
        }
        o_forceinline static phantom::string qualifiedDecoratedName()
        {
            return phantom::string(type_name_of<t_Ty>::qualifiedDecoratedName())+'*';
        }
        o_forceinline static phantom::string name()
        {
            return phantom::string(type_name_of<t_Ty>::name())+'*';
        }
        o_forceinline static phantom::string qualifiedName()
        {
            return phantom::string(type_name_of<t_Ty>::qualifiedName())+'*';
        }
    };

    template <typename t_Ty>
    struct type_name_of<t_Ty&> : public type_name_of<t_Ty>
    {
    public:
        o_forceinline static phantom::string decoratedName()
        {
            return phantom::string(type_name_of<t_Ty>::decoratedName())+'&';
        }
        o_forceinline static phantom::string qualifiedDecoratedName()
        {
            return phantom::string(type_name_of<t_Ty>::qualifiedDecoratedName())+'&';
        }
        o_forceinline static phantom::string name()
        {
            return phantom::string(type_name_of<t_Ty>::name())+'&';
        }
        o_forceinline static phantom::string qualifiedName()
        {
            return phantom::string(type_name_of<t_Ty>::qualifiedName())+'&';
        }
    };

    template <typename t_Ty>
    struct type_name_of<t_Ty const> : public type_name_of<t_Ty>
    {
    public:
        o_forceinline static phantom::string decoratedName()
        {
            return phantom::string(type_name_of<t_Ty>::decoratedName())+" const";
        }
        o_forceinline static phantom::string qualifiedDecoratedName()
        {
            return phantom::string(type_name_of<t_Ty>::qualifiedDecoratedName())+" const";
        }
        o_forceinline static phantom::string name()
        {
            return phantom::string(type_name_of<t_Ty>::name())+" const";
        }
        o_forceinline static phantom::string qualifiedName()
        {
            return phantom::string(type_name_of<t_Ty>::qualifiedName())+" const";
        }
    };

    template <typename t_Ty, size_t t_size>
    struct type_name_of<t_Ty[t_size]> : public type_name_of<t_Ty>
    {
    public:
        o_forceinline static phantom::string decoratedName()
        {
            return phantom::string(type_name_of<t_Ty>::decoratedName())+'['+phantom::lexical_cast<string>(t_size)+']';
        }
        o_forceinline static phantom::string qualifiedDecoratedName()
        {
            return phantom::string(type_name_of<t_Ty>::qualifiedDecoratedName())+'['+phantom::lexical_cast<string>(t_size)+']';
        }
        o_forceinline static phantom::string name()
        {
            return phantom::string(type_name_of<t_Ty>::name())+'['+phantom::lexical_cast<string>(t_size)+']';
        }
        o_forceinline static phantom::string qualifiedName()
        {
            return phantom::string(type_name_of<t_Ty>::qualifiedName())+'['+phantom::lexical_cast<string>(t_size)+']';
        }
    };


    template<typename t_Ty>
    struct super_adder ;

    namespace detail
    {

        template<typename t_Ty, bool t_has_module>
        struct type_of_helper;

        /// has_module = true (the o_classX has been declared before the type_of_counter instanciation
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
                        s_pType = new (o__t1_class__default_class_allocator(meta_type)::allocate()) meta_type;
                        if(meta_type::metaType == nullptr)
                        {
                            o_assert((boost::is_same<meta_type, o_NESTED_TYPE meta_class_type_of<Class>::type>::value));
                            meta_type::metaType = (decltype(meta_type::metaType))(s_pType); /// meta meta type (the meta type of the meta type of 'Class' is the meta type of class itself)
                        }
                        meta_type::metaType->install(s_pType, 0);
                        meta_type::metaType->initialize(s_pType);
                        *built = s_pType;
                        return true;
                    }
                }
                *built = s_pType;
                return false;
            }
        };

        template<typename t_Ty, int t_counter>
        struct type_of_counter_defined
        {
            typedef o_NESTED_TYPE meta_class_type_of<t_Ty>::type meta_type;
            static meta_type* object()
            {
                meta_type* pType = nullptr;
                const string& qualifiedDecoratedName = type_name_of_counter<t_Ty, t_counter>::qualifiedDecoratedName();
                if(type_of_builder<t_Ty>::build(&pType, qualifiedDecoratedName))
                {
                    Phantom::dynamic_initializer()->registerType(qualifiedDecoratedName, type_name_of_counter<t_Ty, t_counter>::namespaceName(), type_name_of_counter<t_Ty, t_counter>::classScopeName(), pType);
                    phantom::detail::module_installer_registrer<t_Ty, t_counter> registrer(pType);
                }
                return pType;
            }
        };

        /// has_module = false (the o_classX has been declared AFTER the type_of_counter instanciation, we don't have compile-time information yet, we use run-time information

        template<typename t_Ty, int t_counter>
        struct type_of_counter
        {
            typedef o_NESTED_TYPE phantom::reflection::base_meta_class_type_of<t_Ty>::type meta_type;
            static meta_type* object()
            {
                const string& qualifiedDecoratedName = type_name_of_counter<t_Ty, t_counter, t_counter>::qualifiedDecoratedName();
                phantom::reflection::Type* pType = phantom::typeByName(qualifiedDecoratedName);
                o_warning(pType, (string("Unknown declared type : '") + qualifiedDecoratedName + "', ensure it's registered with 'o_registerX' in any of your loaded module").c_str());
                return static_cast<meta_type*>(pType);
            }
        };

        template<typename t_Ty, int t_counter>
        struct type_of_counter<t_Ty*, t_counter>
        {
            typedef o_NESTED_TYPE phantom::reflection::base_meta_class_type_of<t_Ty*>::type meta_type;
            static DataPointerType* object()
            {
                return type_of_counter<t_Ty, t_counter>::object()->pointerType();
            }
        };

        template<typename t_Ty, int t_counter>
        struct type_of_counter<t_Ty&, t_counter>
        {
            static ReferenceType* object()
            {
                return type_of_counter<t_Ty, t_counter>::object()->referenceType();
            }
        };

        template<typename t_Ty, int t_counter>
        struct type_of_counter<t_Ty const, t_counter>
        {
            static Type* object()
            {
                return type_of_counter<t_Ty, t_counter>::object()->constType();
            }
        };

        template<typename t_Ty, size_t t_size, int t_counter>
        struct type_of_counter<t_Ty[t_size], t_counter>
        {
            static ArrayType* object()
            {
                return type_of_counter<t_Ty, t_counter>::object()->arrayType(t_size);
            }
        };

    } // namespace detail

    template<typename t_Ty>
    struct type_of
        : public detail::type_of_counter<t_Ty, o_read_compilation_counter>
    {
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

    template<typename t_Ty, size_t t_size>
    struct type_of<t_Ty[t_size]>
    {
        static ArrayType* object()
        {
            return type_of<t_Ty>::object()->arrayType(t_size);
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

    namespace detail
    {

        enum meta_type_id
        {
            meta_pointer_type, // abstract// 1
            meta_data_pointer_type,// 2
            meta_function_pointer_type,// 3

            meta_member_pointer_type, // abstract// 4
            meta_attribute_pointer_type,// 5
            meta_member_function_pointer_type,// 6

            meta_reference_type,// 7

            meta_fundamental_type,// 8
            meta_arithmetic_type, // abstract// 9
            meta_integral_type,// 10
            meta_floating_point_type,// 11

            meta_pod_struct, // 13
            meta_class,// 14

            meta_special, // 15

            meta_enum, // 16

            meta_array, // 17

            meta_container, // 18

            meta_todo,// 19
        };

        template<typename t_Ty>
        struct meta_class_type_id_of
        {
            const static int value =
                boost::is_array<t_Ty>::value
                ? meta_array
                : boost::is_enum<t_Ty>::value
                ? meta_enum
                : (boost::is_void<t_Ty>::value OR phantom::is_signal_t<t_Ty>::value)
                ? meta_special
                : ::boost::is_pointer<t_Ty>::value
                ? ::boost::is_convertible<t_Ty, void*>::value
                ? meta_data_pointer_type
                : meta_function_pointer_type
                : ::boost::is_floating_point<t_Ty>::value
                ? meta_floating_point_type
                : ::boost::is_integral<t_Ty>::value
                ? meta_integral_type
                : ::boost::is_member_function_pointer<t_Ty>::value
                ? meta_member_function_pointer_type
                : ::boost::is_member_object_pointer<t_Ty>::value
                ? meta_attribute_pointer_type
                : is_container<t_Ty>::value
                ? meta_container
                : ::boost::is_class<t_Ty>::value
                ? meta_class
                : ::boost::is_pod<t_Ty>::value
                ? meta_pod_struct
                : meta_todo;
        };


        template<typename t_Ty, int t_id>
        struct base_meta_class_type_of_helper;

#define x_specialize____meta_type_super_class_solver(_meta_type_id_,...)\
    template<typename t_Ty>\
        struct base_meta_class_type_of_helper<t_Ty, _meta_type_id_>\
        {\
        typedef __VA_ARGS__ type;\
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

        x_specialize____meta_type_super_class_solver(meta_container, o_NESTED_TYPE meta_container_class_type_of<t_Ty>::type)

            x_specialize____meta_type_super_class_solver(meta_pointer_type,phantom::reflection::PointerType)
            x_specialize____meta_type_super_class_solver(meta_data_pointer_type,phantom::reflection::DataPointerType)
            x_specialize____meta_type_super_class_solver(meta_function_pointer_type,phantom::reflection::Type)
            x_specialize____meta_type_super_class_solver(meta_member_pointer_type,phantom::reflection::Type)
            x_specialize____meta_type_super_class_solver(meta_attribute_pointer_type,phantom::reflection::Type)
            x_specialize____meta_type_super_class_solver(meta_member_function_pointer_type,phantom::reflection::Type)
            x_specialize____meta_type_super_class_solver(meta_reference_type,phantom::reflection::ReferenceType)
            x_specialize____meta_type_super_class_solver(meta_fundamental_type,phantom::reflection::native::TPrimitiveType<t_Ty>)
            x_specialize____meta_type_super_class_solver(meta_arithmetic_type,phantom::reflection::native::TPrimitiveType<t_Ty>)
            x_specialize____meta_type_super_class_solver(meta_floating_point_type,phantom::reflection::native::TPrimitiveType<t_Ty>)
            x_specialize____meta_type_super_class_solver(meta_integral_type,phantom::reflection::native::TPrimitiveType<t_Ty>)
            x_specialize____meta_type_super_class_solver(meta_pod_struct,phantom::reflection::PODStruct)
            x_specialize____meta_type_super_class_solver(meta_class,phantom::reflection::Class)
            x_specialize____meta_type_super_class_solver(meta_special,phantom::reflection::native::TPrimitiveType<t_Ty>)
            x_specialize____meta_type_super_class_solver(meta_enum,phantom::reflection::Enum)
            x_specialize____meta_type_super_class_solver(meta_todo,phantom::reflection::Type)
            x_specialize____meta_type_super_class_solver(meta_array,phantom::reflection::ArrayType)

#undef x_specialize____meta_type_super_class_solver


    } // namespace detail

    template<typename t_Ty>
    struct meta_class_type_of 
    {
        typedef phantom::reflection::native::TType<t_Ty> type;
    };

    template<typename t_Ty>
    struct base_meta_class_type_of 
        : public detail::base_meta_class_type_of_helper<t_Ty, detail::meta_class_type_id_of<t_Ty>::value>
    {
    };

    template<typename t_Ty>
    struct meta_class_type_of<t_Ty*>
    {
        typedef DataPointerType type;
    };

    template<typename t_Ty>
    struct meta_class_type_of<t_Ty&>
    {
        typedef ReferenceType type;
    };

    template<typename t_Ty>
    struct meta_class_type_of <t_Ty const>
    {
        typedef Type type;
    };

    template<typename t_Ty, size_t t_size>
    struct meta_class_type_of <t_Ty[t_size]>
    {
        typedef ArrayType type;
    };
    /*template<typename t_Ty, size_t t_size0, size_t t_size1>
    struct meta_class_type_of <t_Ty[t_size0][t_size1]>
    {
        typedef ArrayType type;
    };
*/
/*

    template <typename t_Ty>
    struct root_pointed_type_of_ : public type_of<t_Ty>
    {
    };

    template <typename t_Ty>
    struct root_pointed_type_of_<t_Ty*> : public root_pointed_type_of_<t_Ty>
    {
    };

    template <typename t_Ty>
    struct pointed_type_of_
    {
        o_static_assert_msg(sizeof(t_Ty) != sizeof(t_Ty), "t_Ty must be pointer type");
    };

    template <typename t_Ty>
    struct pointed_type_of_<t_Ty*> : public type_of<t_Ty>
    {
    };*/


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
                    phantom::reflection::Signature* pSignature = o_new(Signature);
                    pSignature->setReturnType(typeOf<phantom::signal_t>());
                    phantom::reflection::Signal* pSignal = o_dynamic_proxy_new(phantom::reflection::Signal, phantom::reflection::Signal::metaType, native::TNativeSignal<t_Ty, phantom::signal_t()>) 
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


template<typename t_Ty, int t_counter, bool t_is_class, int t_count>
struct super_classes_adder_helper
{

};

template<typename t_Ty, int t_counter>
struct super_classes_adder_helper<t_Ty, t_counter, true, 0>
{
    o_forceinline static void apply(phantom::reflection::Class* a_pType){}
};

template<typename t_Ty, int t_counter>
struct super_classes_adder_helper<t_Ty, t_counter, false, 0>
{
    o_forceinline static void apply(phantom::reflection::Type* a_pType){}
};

template<typename t_Ty, typename t_STy, int t_counter>
struct super_class_adder;

template<typename t_Ty, int t_counter, int t_count>
struct super_classes_adder_helper<t_Ty, t_counter, true, t_count>
{
    o_forceinline static void apply(phantom::reflection::Class* a_pClass)
    {
        super_classes_adder_helper<t_Ty, t_counter, true, t_count-1>::apply(a_pClass);
        super_class_adder<t_Ty, o_NESTED_TYPE super_class_of<t_Ty, t_count-1>::type, t_counter>::apply(a_pClass);
    }
};

template<typename t_Ty, typename t_STy, int t_counter>
struct super_class_adder
{
    static void apply(phantom::reflection::Class* a_pClass);
};
/*


#define o_define_template_signature_parameter_phantom_element_impl(_type_) \
    template<_type_ value>\
    reflection::TemplateElement* \
    reflection::detail::template_signature_parameter_phantom::_type_<value>::element()\
    {\
        return o_dynamic_proxy_new(phantom::reflection::Constant, phantom::reflection::Constant::metaType, phantom::reflection::native::TNumericConstant<_type_>)("",value);\
    }

#define o_define_template_signature_parameter_phantom(_type_) \
    template<_type_ value>\
    class _type_\
    {\
    public:\
    inline static phantom::reflection::TemplateElement* element();\
    static phantom::string decoratedName()\
{\
    return phantom::lexical_cast<phantom::string>(value);\
}\
    static phantom::string qualifiedDecoratedName()\
{\
    return phantom::lexical_cast<phantom::string>(value);\
}\
    static phantom::string name()\
{\
    return phantom::lexical_cast<phantom::string>(value);\
}\
    static phantom::string qualifiedName()\
{\
    return phantom::lexical_cast<phantom::string>(value);\
}\
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

#define o_define_template_signature_parameter_element_impl(_type_) \
    template<_type_ value>\
    reflection::TemplateElement* \
    reflection::detail::template_signature_parameter_##_type_<value>::element()\
    {\
        return o_dynamic_proxy_new(phantom::reflection::Constant, phantom::reflection::Constant::metaType, phantom::reflection::native::TNumericConstant<_type_>)("",value);\
    }

#define o_define_template_signature_parameter(_type_) \
    template<_type_ value>\
class template_signature_parameter_##_type_\
{\
public:\
    inline static phantom::reflection::TemplateElement* element();\
    static phantom::string decoratedName()\
    {\
        return phantom::lexical_cast<phantom::string>(value);\
    }\
    static phantom::string qualifiedDecoratedName()\
    {\
    return phantom::lexical_cast<phantom::string>(value);\
    }\
    static phantom::string name()\
    {\
    return phantom::lexical_cast<phantom::string>(value);\
    }\
    static phantom::string qualifiedName()\
    {\
    return phantom::lexical_cast<phantom::string>(value);\
    }\
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
    static phantom::reflection::TemplateElement* element();

    static phantom::string decoratedName()
    {
    return phantom::lexical_cast<phantom::string>(value);
    }
    static phantom::string qualifiedDecoratedName()
    {
    return phantom::lexical_cast<phantom::string>(value);
    }
    static phantom::string name()
    {
    return phantom::lexical_cast<phantom::string>(value);
    }
    static phantom::string qualifiedName()
    {
    return phantom::lexical_cast<phantom::string>(value);
    }
};

template<typename t_Ty>
class template_signature_parameter_typename
{
public:
    static phantom::reflection::TemplateElement* object()
    {
        return phantom::typeOf<t_Ty>();
    }
};
template<typename t_Ty>
class template_signature_parameter_name_typename
{
public:
    static phantom::string decoratedName()
    {
    return phantom::decoratedTypeNameOf<t_Ty>();
    }
    static phantom::string qualifiedDecoratedName()
    {
    return phantom::qualifiedDecoratedTypeNameOf<t_Ty>();
    }
    static phantom::string name()
    {
    return phantom::typeNameOf<t_Ty>();
    }
    static phantom::string qualifiedName()
    {
    return phantom::qualifiedTypeNameOf<t_Ty>();
    }
};

template<typename t_Ty>
class template_signature_parameter_class : public template_signature_parameter_typename<t_Ty>
{
};
*/


#define o_define_template_signature_parameter_counter_phantom_element_impl(_type_) \
    template<_type_ value, int t_counter>\
    reflection::TemplateElement* \
    reflection::detail::template_signature_parameter_counter_phantom::_type_<value, t_counter>::object()\
{\
    return o_dynamic_proxy_new(phantom::reflection::Constant, phantom::reflection::Constant::metaType, phantom::reflection::native::TNumericConstant<_type_>)(value);\
}

#define o_define_template_signature_parameter_counter_phantom(_type_) \
    template<_type_ value, int t_counter>\
class _type_\
{\
public:\
    inline static phantom::reflection::TemplateElement* object();\
};

#define o_define_template_signature_parameter_name_counter_phantom(_type_) \
    template<_type_ value, int t_counter>\
class _type_\
{\
public:\
    static phantom::string decoratedName()\
{\
    return phantom::lexical_cast<phantom::string>(value);\
}\
    static phantom::string qualifiedDecoratedName()\
{\
    return phantom::lexical_cast<phantom::string>(value);\
}\
    static phantom::string name()\
{\
    return phantom::lexical_cast<phantom::string>(value);\
}\
    static phantom::string qualifiedName()\
{\
    return phantom::lexical_cast<phantom::string>(value);\
}\
};

struct template_signature_parameter_name_counter_phantom
{
    o_define_template_signature_parameter_name_counter_phantom(boolean)
    o_define_template_signature_parameter_name_counter_phantom(uchar)
    o_define_template_signature_parameter_name_counter_phantom(schar)
    o_define_template_signature_parameter_name_counter_phantom(ushort)
    o_define_template_signature_parameter_name_counter_phantom(sshort)
    o_define_template_signature_parameter_name_counter_phantom(uint)
    o_define_template_signature_parameter_name_counter_phantom(sint)
    o_define_template_signature_parameter_name_counter_phantom(size_t)
    o_define_template_signature_parameter_name_counter_phantom(ulong)
    o_define_template_signature_parameter_name_counter_phantom(slong)
    o_define_template_signature_parameter_name_counter_phantom(longlong)
    o_define_template_signature_parameter_name_counter_phantom(ulonglong)
};


struct template_signature_parameter_counter_phantom
{
    o_define_template_signature_parameter_counter_phantom(boolean)
    o_define_template_signature_parameter_counter_phantom(uchar)
    o_define_template_signature_parameter_counter_phantom(schar)
    o_define_template_signature_parameter_counter_phantom(ushort)
    o_define_template_signature_parameter_counter_phantom(sshort)
    o_define_template_signature_parameter_counter_phantom(uint)
    o_define_template_signature_parameter_counter_phantom(sint)
    o_define_template_signature_parameter_counter_phantom(size_t)
    o_define_template_signature_parameter_counter_phantom(ulong)
    o_define_template_signature_parameter_counter_phantom(slong)
    o_define_template_signature_parameter_counter_phantom(longlong)
    o_define_template_signature_parameter_counter_phantom(ulonglong)
};

#define o_define_template_signature_parameter_counter_element_impl(_type_) \
    template<_type_ value, int t_counter>\
    reflection::TemplateElement* \
    reflection::detail::template_signature_parameter_counter_##_type_<value, t_counter>::object()\
{\
    return o_dynamic_proxy_new(phantom::reflection::Constant, phantom::reflection::Constant::metaType, phantom::reflection::native::TNumericConstant<_type_>)("",value);\
    }

#define o_define_template_signature_parameter_counter(_type_) \
template<_type_ value, int t_counter>\
class template_signature_parameter_counter_##_type_\
{\
public:\
    inline static phantom::reflection::TemplateElement* object();\
};\
template<_type_ value, int t_counter>\
class template_signature_parameter_name_counter_##_type_\
{\
public:\
    static phantom::string decoratedName()\
{\
    return phantom::lexical_cast<phantom::string>(value);\
    }\
    static phantom::string qualifiedDecoratedName()\
{\
    return phantom::lexical_cast<phantom::string>(value);\
    }\
    static phantom::string name()\
{\
    return phantom::lexical_cast<phantom::string>(value);\
    }\
    static phantom::string qualifiedName()\
{\
    return phantom::lexical_cast<phantom::string>(value);\
    }\
};

o_define_template_signature_parameter_counter(bool)
o_define_template_signature_parameter_counter(char)
o_define_template_signature_parameter_counter(short)
o_define_template_signature_parameter_counter(int)
o_define_template_signature_parameter_counter(long)
o_define_template_signature_parameter_counter(size_t)
o_define_template_signature_parameter_counter(uchar)
o_define_template_signature_parameter_counter(schar)
o_define_template_signature_parameter_counter(ushort)
o_define_template_signature_parameter_counter(sshort)
o_define_template_signature_parameter_counter(uint)
o_define_template_signature_parameter_counter(sint)
o_define_template_signature_parameter_counter(ulong)
o_define_template_signature_parameter_counter(slong)
o_define_template_signature_parameter_counter(longlong)
o_define_template_signature_parameter_counter(ulonglong)
o_define_template_signature_parameter_counter(unsigned)


    template<ulonglong value, int t_counter>
class template_signature_parameter_counter_enum
{
public:
    static phantom::reflection::TemplateElement* object();
};


template<ulonglong value, int t_counter>
class template_signature_parameter_name_counter_enum
{
    static phantom::string decoratedName()
    {
        return phantom::lexical_cast<phantom::string>(value);
    }
    static phantom::string qualifiedDecoratedName()
    {
        return phantom::lexical_cast<phantom::string>(value);
    }
    static phantom::string name()
    {
        return phantom::lexical_cast<phantom::string>(value);
    }
    static phantom::string qualifiedName()
    {
        return phantom::lexical_cast<phantom::string>(value);
    }
};

template<typename t_Ty, int t_counter>
class template_signature_parameter_counter_typename 
    : public phantom::reflection::detail::type_of_counter<t_Ty, t_counter>
{
};

template<typename t_Ty, int t_counter>
class template_signature_parameter_name_counter_typename 
    : public phantom::reflection::detail::type_name_of_counter<t_Ty, t_counter>
{
};

template<typename t_Ty, int t_counter>
class template_signature_parameter_counter_class : public template_signature_parameter_counter_typename<t_Ty, t_counter>
{
};

template<typename t_Ty, int t_counter>
class template_signature_parameter_name_counter_class : public template_signature_parameter_name_counter_typename<t_Ty, t_counter>
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
struct super_setup : public t_Ty
{
    static void apply()
    {

    }
};

template<typename t_Ty>
struct super_traits;

template<typename t_Ty>
struct dynamic_caster
{
    static void* apply(Class* a_pTargetClass, t_Ty* a_pBase)
    {
        return super_traits<t_Ty>::cast(a_pTargetClass,a_pBase);
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


template<typename t_Ty, int t_counter>
struct super_classes_adder
    : public detail::super_classes_adder_helper<t_Ty, t_counter, boost::is_class<t_Ty>::value AND NOT(phantom::is_signal_t<t_Ty>::value), super_class_count_of<t_Ty>::value>
{

};

template<typename t_Ty, int t_counter>
struct template_specialization_adder
{
    o_forceinline static void  apply(phantom::reflection::Type* a_pType)
    {
    }
};

template<typename t_Ty>
struct template_specialization_of : public detail::template_specialization_of_helper<t_Ty, boost::is_class<t_Ty>::value AND phantom::has_module<t_Ty>::value> {};

o_namespace_end(phantom, reflection)


#define o_reflection_specialize_template_specialization_adderT(_template_types_, _template_params_, _name_)\
    o_namespace_begin(phantom, reflection, detail) \
    template<o_PP_MIX(_template_types_,_template_params_), int t_counter> \
    struct template_specialization_adder< ::_name_ < o_PP_IDENTITY _template_params_>, t_counter >\
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
    template<o_PP_MIX(_template_types_,_template_params_), int t_counter> \
struct template_specialization_adder<o_PP_CREATE_QUALIFIED_NAME(_namespaces_,_name_) < o_PP_IDENTITY _template_params_ >, t_counter >\
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
    template<o_PP_MIX(_template_types_,_template_params_), int t_counter> \
struct template_specialization_adder<o_PP_CREATE_QUALIFIED_NAME(_classes_,_name_) < o_PP_IDENTITY _template_params_ >, t_counter >\
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
    template<o_PP_MIX(_template_types_,_template_params_), int t_counter> \
struct template_specialization_adder<o_PP_CREATE_QUALIFIED_NAME_2(_namespaces_,_classes_,_name_) < o_PP_IDENTITY _template_params_ >, t_counter >\
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
    pTemplateSpecialization->setArgument(o_PP_QUOTE(o_PP_CAT(o_PP_ARG_0,l1)), o_PP_CAT(o_root_namespace::phantom::reflection::detail::template_signature_parameter_counter_,o_PP_CAT(o_PP_ARG_0,l0))< o_PP_CAT(o_PP_ARG_0,l1), t_counter >::object()); \

#define o_reflection_add_template_parameter_reflection_2(l0,l1) \
    o_reflection_add_template_parameter_reflection_1(l0,l1) \
    pTemplateSpecialization->setArgument(o_PP_QUOTE(o_PP_CAT(o_PP_ARG_1,l1)), o_PP_CAT(o_root_namespace::phantom::reflection::detail::template_signature_parameter_counter_,o_PP_CAT(o_PP_ARG_1,l0))< o_PP_CAT(o_PP_ARG_1,l1), t_counter >::object());

#define o_reflection_add_template_parameter_reflection_3(l0,l1) \
    o_reflection_add_template_parameter_reflection_2(l0,l1) \
    pTemplateSpecialization->setArgument(o_PP_QUOTE(o_PP_CAT(o_PP_ARG_2,l1)), o_PP_CAT(o_root_namespace::phantom::reflection::detail::template_signature_parameter_counter_,o_PP_CAT(o_PP_ARG_2,l0))< o_PP_CAT(o_PP_ARG_2,l1), t_counter >::object());

#define o_reflection_add_template_parameter_reflection_4(l0,l1) \
    o_reflection_add_template_parameter_reflection_3(l0,l1) \
    pTemplateSpecialization->setArgument(o_PP_QUOTE(o_PP_CAT(o_PP_ARG_3,l1)), o_PP_CAT(o_root_namespace::phantom::reflection::detail::template_signature_parameter_counter_,o_PP_CAT(o_PP_ARG_3,l0))< o_PP_CAT(o_PP_ARG_3,l1), t_counter >::object());

#define o_reflection_add_template_parameter_reflection_5(l0,l1) \
    o_reflection_add_template_parameter_reflection_4(l0,l1) \
    pTemplateSpecialization->setArgument(o_PP_QUOTE(o_PP_CAT(o_PP_ARG_4,l1)), o_PP_CAT(o_root_namespace::phantom::reflection::detail::template_signature_parameter_counter_,o_PP_CAT(o_PP_ARG_4,l0))< o_PP_CAT(o_PP_ARG_4,l1), t_counter >::object());

#define o_reflection_add_template_parameter_reflection_6(l0,l1) \
    o_reflection_add_template_parameter_reflection_5(l0,l1) \
    pTemplateSpecialization->setArgument(o_PP_QUOTE(o_PP_CAT(o_PP_ARG_5,l1)), o_PP_CAT(o_root_namespace::phantom::reflection::detail::template_signature_parameter_counter_,o_PP_CAT(o_PP_ARG_5,l0))< o_PP_CAT(o_PP_ARG_5,l1), t_counter >::object());

#define o_reflection_add_template_parameter_reflection_7(l0,l1) \
    o_reflection_add_template_parameter_reflection_6(l0,l1) \
    pTemplateSpecialization->setArgument(o_PP_QUOTE(o_PP_CAT(o_PP_ARG_6,l1)), o_PP_CAT(o_root_namespace::phantom::reflection::detail::template_signature_parameter_counter_,o_PP_CAT(o_PP_ARG_6,l0))< o_PP_CAT(o_PP_ARG_6,l1), t_counter >::object());

#define o_reflection_add_template_parameter_reflection_8(l0,l1) \
    o_reflection_add_template_parameter_reflection_7(l0,l1) \
    pTemplateSpecialization->setArgument(o_PP_QUOTE(o_PP_CAT(o_PP_ARG_7,l1)), o_PP_CAT(o_root_namespace::phantom::reflection::detail::template_signature_parameter_counter_,o_PP_CAT(o_PP_ARG_7,l0))< o_PP_CAT(o_PP_ARG_7,l1), t_counter >::object());

#define o_reflection_add_template_parameter_reflection_9(l0,l1) \
    o_reflection_add_template_parameter_reflection_8(l0,l1) \
    pTemplateSpecialization->setArgument(o_PP_QUOTE(o_PP_CAT(o_PP_ARG_8,l1)), o_PP_CAT(o_root_namespace::phantom::reflection::detail::template_signature_parameter_counter_,o_PP_CAT(o_PP_ARG_8,l0))< o_PP_CAT(o_PP_ARG_8,l1), t_counter >::object());

#define o_reflection_add_template_parameter_reflection_10(l0,l1) \
    o_reflection_add_template_parameter_reflection_9(l0,l1) \
    pTemplateSpecialization->setArgument(o_PP_QUOTE(o_PP_CAT(o_PP_ARG_9,l1)), o_PP_CAT(o_root_namespace::phantom::reflection::detail::template_signature_parameter_counter_,o_PP_CAT(o_PP_ARG_9,l0))< o_PP_CAT(o_PP_ARG_9,l1), t_counter >::object());


#define o_reflection_create_template_parameters_list_string_counter_N(l0,l1, _func_name_, _counter_) \
    o_PP_CAT o_PP_LEFT_PAREN o_reflection_create_template_parameters_list_string_counter_,o_PP_NARG_FUNC()l0 o_PP_RIGHT_PAREN (l0,l1, _func_name_, _counter_)

#define o_reflection_create_template_parameters_list_string_counter_1(l0,l1, _func_name_, _counter_) \
    phantom::string(o_PP_CAT(o_root_namespace::phantom::reflection::detail::template_signature_parameter_name_counter_ ,o_PP_CAT(o_PP_ARG_0,l0))< o_PP_CAT(o_PP_ARG_0,l1), _counter_ >::_func_name_()) \

#define o_reflection_create_template_parameters_list_string_counter_2(l0,l1, _func_name_, _counter_) \
    o_reflection_create_template_parameters_list_string_counter_1(l0,l1, _func_name_, _counter_) + ',' +\
    o_PP_CAT(o_root_namespace::phantom::reflection::detail::template_signature_parameter_name_counter_ ,o_PP_CAT(o_PP_ARG_1,l0))< o_PP_CAT(o_PP_ARG_1,l1), _counter_ >::_func_name_() \

#define o_reflection_create_template_parameters_list_string_counter_3(l0,l1, _func_name_, _counter_) \
    o_reflection_create_template_parameters_list_string_counter_2(l0,l1, _func_name_, _counter_) + ',' + \
    o_PP_CAT(o_root_namespace::phantom::reflection::detail::template_signature_parameter_name_counter_ ,o_PP_CAT(o_PP_ARG_2,l0))< o_PP_CAT(o_PP_ARG_2,l1), _counter_ >::_func_name_() \

#define o_reflection_create_template_parameters_list_string_counter_4(l0,l1, _func_name_, _counter_) \
    o_reflection_create_template_parameters_list_string_counter_3(l0,l1, _func_name_, _counter_) + ',' +\
    o_PP_CAT(o_root_namespace::phantom::reflection::detail::template_signature_parameter_name_counter_ ,o_PP_CAT(o_PP_ARG_3,l0))< o_PP_CAT(o_PP_ARG_3,l1), _counter_ >::_func_name_() \

#define o_reflection_create_template_parameters_list_string_counter_5(l0,l1, _func_name_, _counter_) \
    o_reflection_create_template_parameters_list_string_counter_4(l0,l1, _func_name_, _counter_) + ',' +\
    o_PP_CAT(o_root_namespace::phantom::reflection::detail::template_signature_parameter_name_counter_ ,o_PP_CAT(o_PP_ARG_4,l0))< o_PP_CAT(o_PP_ARG_4,l1), _counter_ >::_func_name_() \

#define o_reflection_create_template_parameters_list_string_counter_6(l0,l1, _func_name_, _counter_) \
    o_reflection_create_template_parameters_list_string_counter_5(l0,l1, _func_name_, _counter_) + ',' +\
    o_PP_CAT(o_root_namespace::phantom::reflection::detail::template_signature_parameter_name_counter_ ,o_PP_CAT(o_PP_ARG_5,l0))< o_PP_CAT(o_PP_ARG_5,l1), _counter_ >::_func_name_() \

#define o_reflection_create_template_parameters_list_string_counter_7(l0,l1, _func_name_, _counter_) \
    o_reflection_create_template_parameters_list_string_counter_6(l0,l1, _func_name_, _counter_) + ',' +\
    o_PP_CAT(o_root_namespace::phantom::reflection::detail::template_signature_parameter_name_counter_ ,o_PP_CAT(o_PP_ARG_6,l0))< o_PP_CAT(o_PP_ARG_6,l1), _counter_ >::_func_name_() \

#define o_reflection_create_template_parameters_list_string_counter_8(l0,l1, _func_name_, _counter_) \
    o_reflection_create_template_parameters_list_string_counter_7(l0,l1, _func_name_, _counter_) + ',' +\
    o_PP_CAT(o_root_namespace::phantom::reflection::detail::template_signature_parameter_name_counter_ ,o_PP_CAT(o_PP_ARG_7,l0))< o_PP_CAT(o_PP_ARG_7,l1), _counter_ >::_func_name_() \

#define o_reflection_create_template_parameters_list_string_counter_9(l0,l1, _func_name_, _counter_) \
    o_reflection_create_template_parameters_list_string_counter_8(l0,l1, _func_name_, _counter_) + ',' +\
    o_PP_CAT(o_root_namespace::phantom::reflection::detail::template_signature_parameter_name_counter_ ,o_PP_CAT(o_PP_ARG_8,l0))< o_PP_CAT(o_PP_ARG_8,l1), _counter_ >::_func_name_() \

#define o_reflection_create_template_parameters_list_string_counter_10(l0,l1, _func_name_, _counter_) \
    o_reflection_create_template_parameters_list_string_counter_9(l0,l1, _func_name_, _counter_) + ',' +\
    o_PP_CAT(o_root_namespace::phantom::reflection::detail::template_signature_parameter_name_counter_ ,o_PP_CAT(o_PP_ARG_9,l0))< o_PP_CAT(o_PP_ARG_9,l1), _counter_ >::_func_name_() \

#else /// NOT VISUAL STUDIO

#define o_reflection_add_template_parameter_reflection(l0,l1) \
    o_PP_CAT( o_reflection_add_template_parameter_reflection_,o_PP_NARG_FUNC()l0 ) (l0,l1)

#define o_reflection_add_template_parameter_reflection_1(l0,l1) \
    pTemplateSpecialization->setArgument(o_PP_QUOTE(o_PP_ARG_0 l1), o_PP_CAT(o_root_namespace::phantom::reflection::detail::template_signature_parameter_counter_,o_PP_ARG_0 l0)< o_PP_ARG_0 l1, t_counter >::object()); \

#define o_reflection_add_template_parameter_reflection_2(l0,l1) \
    o_reflection_add_template_parameter_reflection_1(l0,l1) \
    pTemplateSpecialization->setArgument(o_PP_QUOTE(o_PP_ARG_1 l1), o_PP_CAT(o_root_namespace::phantom::reflection::detail::template_signature_parameter_counter_,o_PP_ARG_1 l0)< o_PP_ARG_1 l1, t_counter >::object());

#define o_reflection_add_template_parameter_reflection_3(l0,l1) \
    o_reflection_add_template_parameter_reflection_2(l0,l1) \
    pTemplateSpecialization->setArgument(o_PP_QUOTE(o_PP_ARG_2 l1), o_PP_CAT(o_root_namespace::phantom::reflection::detail::template_signature_parameter_counter_,o_PP_ARG_2 l0)< o_PP_ARG_2 l1, t_counter>::object());

#define o_reflection_add_template_parameter_reflection_4(l0,l1) \
    o_reflection_add_template_parameter_reflection_3(l0,l1) \
    pTemplateSpecialization->setArgument(o_PP_QUOTE(o_PP_ARG_3 l1), o_PP_CAT(o_root_namespace::phantom::reflection::detail::template_signature_parameter_counter_,o_PP_ARG_3 l0)< o_PP_ARG_3 l1, t_counter>::object());

#define o_reflection_add_template_parameter_reflection_5(l0,l1) \
    o_reflection_add_template_parameter_reflection_4(l0,l1) \
    pTemplateSpecialization->setArgument(o_PP_QUOTE(o_PP_ARG_4 l1), o_PP_CAT(o_root_namespace::phantom::reflection::detail::template_signature_parameter_counter_,o_PP_ARG_4 l0)< o_PP_ARG_4 l1, t_counter>::object());

#define o_reflection_add_template_parameter_reflection_6(l0,l1) \
    o_reflection_add_template_parameter_reflection_5(l0,l1) \
    pTemplateSpecialization->setArgument(o_PP_QUOTE(o_PP_ARG_5 l1), o_PP_CAT(o_root_namespace::phantom::reflection::detail::template_signature_parameter_counter_,o_PP_ARG_5 l0)< o_PP_ARG_5 l1, t_counter >::object());

#define o_reflection_add_template_parameter_reflection_7(l0,l1) \
    o_reflection_add_template_parameter_reflection_6(l0,l1) \
    pTemplateSpecialization->setArgument(o_PP_QUOTE(o_PP_ARG_6 l1), o_PP_CAT(o_root_namespace::phantom::reflection::detail::template_signature_parameter_counter_,o_PP_ARG_6 l0)< o_PP_ARG_6 l1, t_counter >::object());

#define o_reflection_add_template_parameter_reflection_8(l0,l1) \
    o_reflection_add_template_parameter_reflection_7(l0,l1) \
    pTemplateSpecialization->setArgument(o_PP_QUOTE(o_PP_ARG_7 l1), o_PP_CAT(o_root_namespace::phantom::reflection::detail::template_signature_parameter_counter_,o_PP_ARG_7 l0)< o_PP_ARG_7 l1, t_counter >::object());

#define o_reflection_add_template_parameter_reflection_9(l0,l1) \
    o_reflection_add_template_parameter_reflection_8(l0,l1) \
    pTemplateSpecialization->setArgument(o_PP_QUOTE(o_PP_ARG_8 l1), o_PP_CAT(o_root_namespace::phantom::reflection::detail::template_signature_parameter_counter_,o_PP_ARG_8 l0)< o_PP_ARG_8 l1, t_counter >::object());

#define o_reflection_add_template_parameter_reflection_10(l0,l1) \
    o_reflection_add_template_parameter_reflection_9(l0,l1) \
    pTemplateSpecialization->setArgument(o_PP_QUOTE(o_PP_ARG_9 l1), o_PP_CAT(o_root_namespace::phantom::reflection::detail::template_signature_parameter_counter_,o_PP_ARG_9 l0)< o_PP_ARG_9 l1, t_counter >::object());


#define o_reflection_create_template_parameters_list_string_counter_N(l0,l1,_func_name_, _counter_) \
    o_PP_CAT( o_reflection_create_template_parameters_list_string_counter_, o_PP_NARG l0 ) (l0,l1,_func_name_, _counter_)

#define o_reflection_create_template_parameters_list_string_counter_1(l0,l1,_func_name_, _counter_) \
    phantom::string(o_PP_CAT(o_root_namespace::phantom::reflection::detail::template_signature_parameter_name_counter_ ,o_PP_ARG_0 l0)< o_PP_ARG_0 l1, _counter_ >::_func_name_()) \

#define o_reflection_create_template_parameters_list_string_counter_2(l0,l1, _func_name_, _counter_) \
    o_reflection_create_template_parameters_list_string_counter_1(l0,l1, _func_name_, _counter_) + ',' +\
    o_PP_CAT(o_root_namespace::phantom::reflection::detail::template_signature_parameter_name_counter_ ,o_PP_ARG_1 l0)< o_PP_ARG_1 l1, _counter_ >::_func_name_() \

#define o_reflection_create_template_parameters_list_string_counter_3(l0,l1, _func_name_, _counter_) \
    o_reflection_create_template_parameters_list_string_counter_2(l0,l1, _func_name_, _counter_) + ',' + \
    o_PP_CAT(o_root_namespace::phantom::reflection::detail::template_signature_parameter_name_counter_ ,o_PP_ARG_2 l0)< o_PP_ARG_2 l1, _counter_ >::_func_name_() \

#define o_reflection_create_template_parameters_list_string_counter_4(l0,l1, _func_name_, _counter_) \
    o_reflection_create_template_parameters_list_string_counter_3(l0,l1, _func_name_, _counter_) + ',' +\
    o_PP_CAT(o_root_namespace::phantom::reflection::detail::template_signature_parameter_name_counter_ ,o_PP_ARG_3 l0)< o_PP_ARG_3 l1, _counter_ >::_func_name_() \

#define o_reflection_create_template_parameters_list_string_counter_5(l0,l1, _func_name_, _counter_) \
    o_reflection_create_template_parameters_list_string_counter_4(l0,l1, _func_name_, _counter_) + ',' +\
    o_PP_CAT(o_root_namespace::phantom::reflection::detail::template_signature_parameter_name_counter_ ,o_PP_ARG_4 l0)< o_PP_ARG_4 l1, _counter_ >::_func_name_() \

#define o_reflection_create_template_parameters_list_string_counter_6(l0,l1, _func_name_, _counter_) \
    o_reflection_create_template_parameters_list_string_counter_5(l0,l1, _func_name_, _counter_) + ',' +\
    o_PP_CAT(o_root_namespace::phantom::reflection::detail::template_signature_parameter_name_counter_ ,o_PP_ARG_5 l0)< o_PP_ARG_5 l1, _counter_ >::_func_name_() \

#define o_reflection_create_template_parameters_list_string_counter_7(l0,l1, _func_name_, _counter_) \
    o_reflection_create_template_parameters_list_string_counter_6(l0,l1, _func_name_, _counter_) + ',' +\
    o_PP_CAT(o_root_namespace::phantom::reflection::detail::template_signature_parameter_name_counter_ ,o_PP_ARG_6 l0)< o_PP_ARG_6 l1, _counter_ >::_func_name_() \

#define o_reflection_create_template_parameters_list_string_counter_8(l0,l1, _func_name_, _counter_) \
    o_reflection_create_template_parameters_list_string_counter_7(l0,l1, _func_name_, _counter_) + ',' +\
    o_PP_CAT(o_root_namespace::phantom::reflection::detail::template_signature_parameter_name_counter_ ,o_PP_ARG_7 l0)< o_PP_ARG_7 l1, _counter_ >::_func_name_() \

#define o_reflection_create_template_parameters_list_string_counter_9(l0,l1, _func_name_, _counter_) \
    o_reflection_create_template_parameters_list_string_counter_8(l0,l1, _func_name_, _counter_) + ',' +\
    o_PP_CAT(o_root_namespace::phantom::reflection::detail::template_signature_parameter_name_counter_ ,o_PP_ARG_8 l0)< o_PP_ARG_8 l1, _counter_ >::_func_name_() \

#define o_reflection_create_template_parameters_list_string_counter_10(l0,l1, _func_name_, _counter_) \
    o_reflection_create_template_parameters_list_string_counter_9(l0,l1, _func_name_, _counter_) + ',' +\
    o_PP_CAT(o_root_namespace::phantom::reflection::detail::template_signature_parameter_name_counter_ ,o_PP_ARG_9 l0)< o_PP_ARG_9 l1, _counter_ >::_func_name_() \

#endif // o_COMPILER



#define o_PP_CREATE_QUALIFIED_NAME(_namespaces_,_name_) \
    :: o_PP_CREATE_SCOPE _namespaces_ :: _name_

#define o_PP_CREATE_QUALIFIED_IDENTIFIER_NAME(_namespaces_,_name_) \
     o_PP_IDENTITY(o_PP_IDENTITY o_PP_LEFT_PAREN o_PP_CREATE_SCOPE_IDENTIFIER _namespaces_##_##_name_ o_PP_RIGHT_PAREN)

#define o__PP_CREATE_QUALIFIED_IDENTIFIER_NAME(_namespaces_,_name_) \
    _o_PP_IDENTITY(o_PP_IDENTITY o_PP_LEFT_PAREN o_PP_CREATE_SCOPE_IDENTIFIER _namespaces_##_##_name_ o_PP_RIGHT_PAREN)

#define o_PP_CREATE_QUALIFIED_NAME_2(_namespaces_,_classes_,_name_) \
    :: o_PP_CREATE_SCOPE _namespaces_ :: o_PP_CREATE_SCOPE _classes_ :: _name_

#define o_PP_CREATE_QUALIFIED_IDENTIFIER_NAME_2(_namespaces_,_classes_,_name_) \
    o_PP_IDENTITY(o_PP_IDENTITY o_PP_LEFT_PAREN o_PP_CREATE_SCOPE_IDENTIFIER _namespaces_##o__PP_CREATE_QUALIFIED_IDENTIFIER_NAME(_classes_, _name_) o_PP_RIGHT_PAREN)


#define o_reflection_specialize_type_name_static_member_functionsN(_namespaces_, _name_)\
     static const char* name() { return o_PP_QUOTE(_name_); }                             \
    static const char* decoratedName() { return o_PP_QUOTE(_name_); }                   \
    static const char* qualifiedName()                                                             \
    {                                                                   \
    return "::" o_PP_QUOTE_SCOPE(_namespaces_) "::"o_PP_QUOTE(_name_);           \
    }                                                                                                             \
    static const char* qualifiedDecoratedName()                                                                         \
    {                                                                                                                         \
    return o_PP_QUOTE_SCOPE(_namespaces_) "::"o_PP_QUOTE(_name_);           \
    }                                                                                                                           \
    static const char* namespaceName()                                                                                   \
    {                                                                                                                                \
    return o_PP_QUOTE_SCOPE(_namespaces_) ;                                          \
    }     \
    static const char* classScopeName()                                                                                   \
    {                                                                                                                                \
    return "";                                          \
    }

#define o_reflection_specialize_type_name_static_member_functionsC(_classes_, _name_)\
    static const char* name() { return o_PP_QUOTE(_name_); }                             \
    static const char* decoratedName() { return o_PP_QUOTE(_name_); }                   \
    static const char* qualifiedName()                                                             \
    {                                                                   \
    return o_PP_QUOTE_SCOPE(_classes_) "::" o_PP_QUOTE(_name_);           \
    }                                                                                                             \
    static const char* qualifiedDecoratedName()                                                                         \
    {                                                                                                                         \
    return o_PP_QUOTE_SCOPE(_classes_) "::" o_PP_QUOTE(_name_);           \
    }                                                                                                                           \
    static const char* namespaceName()                                                                                   \
    {                                                                                                                                \
    return "";                                          \
    }     \
    static const char* classScopeName()                                                                                   \
    {                                                                                                                                \
    return o_PP_QUOTE_SCOPE(_classes_) ;                                          \
    }

#define o_reflection_specialize_type_name_static_member_functionsNC(_namespaces_, _classes_, _name_)\
    static const char* name() { return o_PP_QUOTE(_name_); }                             \
    static const char* decoratedName() { return o_PP_QUOTE(_name_); }                   \
    static const char* qualifiedName()                                                             \
    {                                                                   \
    return o_PP_QUOTE_SCOPE(_namespaces_) "::" o_PP_QUOTE_SCOPE(_classes_) "::"o_PP_QUOTE(_name_);           \
    }                                                                                                             \
    static const char* qualifiedDecoratedName()                                                                         \
    {                                                                                                                         \
    return o_PP_QUOTE_SCOPE(_namespaces_) "::" o_PP_QUOTE_SCOPE(_classes_) "::"o_PP_QUOTE(_name_);           \
    }                                                                                                                           \
    static const char* namespaceName()                                                                                   \
    {                                                                                                                                \
    return o_PP_QUOTE_SCOPE(_namespaces_) ;                                          \
    }\
    static const char* classScopeName()                                                                                   \
    {                                                                                                                                \
    return o_PP_QUOTE_SCOPE(_classes_) ;                                          \
    }

#define o_reflection_specialize_type_name_static_member_functions(_name_)        \
    static const char* name() { return o_PP_QUOTE(_name_); }                             \
    static const char* decoratedName() { return o_PP_QUOTE(_name_); }                   \
    static const char* qualifiedName()                                                             \
    {                                                                   \
    return o_PP_QUOTE(_name_);           \
    }                                                                                                             \
    static const char* qualifiedDecoratedName()                                                                         \
    {                                                                                                                         \
    return o_PP_QUOTE(_name_);           \
    }                                                                                                                           \
    static const char* namespaceName()                                                                                   \
    {                                                                                                                                \
    return "";                                          \
    }\
    static const char*  classScopeName()         {             return "";        }


#define o_reflection_specialize_type_name_static_member_counter_functionsNT(_namespaces_, _template_types_, _template_params_, _name_, _counter_) \
    static const char* name() { return o_PP_QUOTE(_name_); } \
    static const phantom::string&    decoratedName() \
        { \
        static phantom::string n;\
        if(n.empty())\
            {\
            n = o_PP_QUOTE(_name_)"<";\
            n += o_reflection_create_template_parameters_list_string_counter_N(_template_types_,_template_params_,decoratedName, _counter_); \
            n += '>';\
            }\
            return n;\
        } \
        static const phantom::string&    qualifiedDecoratedName() \
        { \
        static phantom::string n;\
        if(n.empty())\
            {\
            n = o_PP_QUOTE_SCOPE(_namespaces_)  "::"o_PP_QUOTE(_name_)"<";\
            n += o_reflection_create_template_parameters_list_string_counter_N(_template_types_,_template_params_,qualifiedDecoratedName, _counter_); \
            n += '>';\
            }\
            return n;\
        } \
        static const char*    qualifiedName() \
        { \
        return o_PP_QUOTE_SCOPE(_namespaces_) "::"o_PP_QUOTE(_name_); \
        } \
        static const char* namespaceName() \
        { \
        return o_PP_QUOTE_SCOPE(_namespaces_) ;\
        } \
        static const char*  classScopeName()         {             return "";        }


#define o_reflection_specialize_type_name_static_member_counter_functionsNPT(_namespaces_, _template_types_, _template_params_, _template_spec_, _name_, _counter_) \
    static const char* name() { return o_PP_QUOTE(_name_); } \
    static const phantom::string&    decoratedName() \
        { \
        static phantom::string n;\
        if(n.empty())\
            {\
            n = o_PP_QUOTE(_name_)"<";\
            n += o_reflection_create_template_parameters_list_string_counter_NP(_template_types_,_template_params_,_template_spec_,decoratedName, _counter_); \
            n += '>';\
            }\
            return n;\
        } \
        static const phantom::string&    qualifiedDecoratedName() \
        { \
        static phantom::string n;\
        if(n.empty())\
            {\
            n = o_PP_QUOTE_SCOPE(_namespaces_)  "::"o_PP_QUOTE(_name_)"<";\
            n += o_reflection_create_template_parameters_list_string_counter_N(_template_types_,_template_params_,qualifiedDecoratedName, _counter_); \
            n += '>';\
            }\
            return n;\
        } \
        static const char*    qualifiedName() \
        { \
        return o_PP_QUOTE_SCOPE(_namespaces_) "::"o_PP_QUOTE(_name_); \
        } \
        static const char* namespaceName() \
        { \
        return o_PP_QUOTE_SCOPE(_namespaces_) ;\
        } \
        static const char*  classScopeName()         {             return "";        }

#define o_reflection_specialize_type_name_static_member_counter_functionsT(_template_types_, _template_params_, _name_, _counter_) \
    static const char* name() { return o_PP_QUOTE(_name_); } \
    static const phantom::string&    decoratedName() \
        { \
        static phantom::string n;\
        if(n.empty())\
            {\
            n = o_PP_QUOTE(_name_)"<";\
            n += o_reflection_create_template_parameters_list_string_counter_N(_template_types_,_template_params_,decoratedName, _counter_); \
            n += '>';\
            }\
            return n;\
        } \
        static const phantom::string&    qualifiedDecoratedName() \
        { \
        static phantom::string n;\
        if(n.empty())\
            {\
            n = "::"o_PP_QUOTE(_name_)"<";\
            n += o_reflection_create_template_parameters_list_string_counter_N(_template_types_,_template_params_,qualifiedDecoratedName, _counter_); \
            n += '>';\
            }\
            return n;\
        } \
        static const char*    qualifiedName() \
        { \
        return "::"o_PP_QUOTE(_name_); \
        } \
        static const char* namespaceName() \
        { \
        return "";\
        } \
        static const char*  classScopeName()         \
        {             \
        return "";\
        }

#define o_reflection_specialize_type_name_static_member_counter_functionsNCT(_namespaces_, _classes_, _template_types_, _template_params_, _name_, _counter_) \
    static const char* name() { return o_PP_QUOTE(_name_); } \
    static const phantom::string&    decoratedName() \
        { \
        static phantom::string n;\
        if(n.empty())\
            {\
            n = o_PP_QUOTE(_name_)"<";\
            n += o_reflection_create_template_parameters_list_string_counter_N(_template_types_,_template_params_,decoratedName, _counter_); \
            n += '>';\
            }\
            return n;\
        } \
        static const phantom::string&    qualifiedDecoratedName() \
        { \
        static phantom::string n;\
        if(n.empty())\
            {\
            n = o_PP_QUOTE_SCOPE(_namespaces_)  "::" o_PP_QUOTE_SCOPE(_classes_)  "::"o_PP_QUOTE(_name_)"<";\
            n += o_reflection_create_template_parameters_list_string_counter_N(_template_types_,_template_params_,qualifiedDecoratedName, _counter_); \
            n += '>';\
            }\
            return n;\
        } \
        static const char*    qualifiedName() \
        { \
        return o_PP_QUOTE_SCOPE(_namespaces_) "::" o_PP_QUOTE_SCOPE(_classes_) "::"o_PP_QUOTE(_name_); \
        } \
        static const char* namespaceName() \
        { \
        return o_PP_QUOTE_SCOPE(_namespaces_) ;\
        } \
        static const char*  classScopeName()         \
        {             \
        return o_PP_QUOTE_SCOPE(_classes_);        \
        }

#define o_reflection_specialize_type_name_static_member_counter_functionsCT(_classes_, _template_types_, _template_params_, _name_, _counter_) \
    static const char* name() { return o_PP_QUOTE(_name_); } \
    static const phantom::string&    decoratedName() \
        { \
        static phantom::string n;\
        if(n.empty())\
            {\
            n = o_PP_QUOTE(_name_)"<";\
            n += o_reflection_create_template_parameters_list_string_counter_N(_template_types_,_template_params_,decoratedName, _counter_); \
            n += '>';\
            }\
            return n;\
        } \
        static const phantom::string&    qualifiedDecoratedName() \
        { \
        static phantom::string n;\
        if(n.empty())\
            {\
            n = o_PP_QUOTE_SCOPE(_classes_)  "::"o_PP_QUOTE(_name_)"<";\
            n += o_reflection_create_template_parameters_list_string_counter_N(_template_types_,_template_params_,qualifiedDecoratedName, _counter_); \
            n += '>';\
            }\
            return n;\
        } \
        static const char*    qualifiedName() \
        { \
        return o_PP_QUOTE_SCOPE(_classes_) "::"o_PP_QUOTE(_name_); \
        } \
        static const char* namespaceName() \
        { \
        return "";\
        } \
        static const char*  classScopeName()         \
        {             \
        return o_PP_QUOTE_SCOPE(_classes_);        \
        }

/// o_reflection_specialize_type_name_of

#define o_reflection_specialize_type_name_of(_name_)    \
    o_namespace_begin(phantom, reflection)            \
    template<>                                               \
class type_name_of< ::_name_>     \
    : public detail::type_name_of_counter<::_name_, o_read_compilation_counter> {};\
    o_namespace_end(phantom, reflection)

#define o_reflection_specialize_type_name_ofN(_namespaces_,_name_) \
    o_namespace_begin(phantom, reflection)            \
    template<>                                               \
class type_name_of<o_PP_CREATE_QUALIFIED_NAME(_namespaces_,_name_)>     \
    : public detail::type_name_of_counter<o_PP_CREATE_QUALIFIED_NAME(_namespaces_,_name_), o_read_compilation_counter> {};\
    o_namespace_end(phantom, reflection)

#define o_reflection_specialize_type_name_ofC(_classes_,_name_) \
    o_namespace_begin(phantom, reflection)            \
    template<>                                               \
class type_name_of<o_PP_CREATE_QUALIFIED_NAME(_classes_,_name_)>     \
    : public detail::type_name_of_counter<o_PP_CREATE_QUALIFIED_NAME(_classes_,_name_), o_read_compilation_counter> {};\
    o_namespace_end(phantom, reflection)

#define o_reflection_specialize_type_name_ofNC(_namespaces_,_classes_,_name_) \
    o_namespace_begin(phantom, reflection)            \
    template<>                                               \
class type_name_of<o_PP_CREATE_QUALIFIED_NAME_2(_namespaces_,_classes_,_name_)>     \
    : public detail::type_name_of_counter<o_PP_CREATE_QUALIFIED_NAME_2(_namespaces_,_classes_,_name_), o_read_compilation_counter> {};\
    o_namespace_end(phantom, reflection)

#define o_reflection_specialize_type_name_ofT(_template_types_, _template_params_, _name_) \
    o_namespace_begin(phantom, reflection) \
    template<o_PP_MIX(_template_types_, _template_params_)> \
class type_name_of< ::_name_< o_PP_IDENTITY _template_params_ > > \
    : public detail::type_name_of_counter<::_name_< o_PP_IDENTITY _template_params_ >, o_read_compilation_counter> {};\
    o_namespace_end(phantom, reflection)

#define o_reflection_specialize_type_name_ofNT(_namespaces_, _template_types_, _template_params_, _name_) \
    o_namespace_begin(phantom, reflection) \
    template<o_PP_MIX(_template_types_, _template_params_)> \
class type_name_of<o_PP_CREATE_QUALIFIED_NAME(_namespaces_,_name_)< o_PP_IDENTITY _template_params_ > > \
    : public detail::type_name_of_counter<o_PP_CREATE_QUALIFIED_NAME(_namespaces_,_name_)< o_PP_IDENTITY _template_params_ >, o_read_compilation_counter> {};\
    o_namespace_end(phantom, reflection)

#define o_reflection_specialize_type_name_ofCT(_classes_,_template_types_,_template_names_,_name_) \
    o_namespace_begin(phantom, reflection)            \
    template<o_PP_MIX(_template_types_, _template_params_)>                                               \
class type_name_of<o_PP_CREATE_QUALIFIED_NAME(_classes_,_name_)< o_PP_IDENTITY _template_params_ > >     \
    : public detail::type_name_of_counter<o_PP_CREATE_QUALIFIED_NAME(_classes_,_name_)< o_PP_IDENTITY _template_params_ >, o_read_compilation_counter> {};\
    o_namespace_end(phantom, reflection)

#define o_reflection_specialize_type_name_ofNCT(_namespaces_,_classes_,_template_types_,_template_names_,_name_) \
    o_namespace_begin(phantom, reflection)            \
    template<o_PP_MIX(_template_types_, _template_params_)>                                               \
class type_name_of<o_PP_CREATE_QUALIFIED_NAME_2(_namespaces_,_classes_,_name_)< o_PP_IDENTITY _template_params_ > >     \
    : public detail::type_name_of_counter<o_PP_CREATE_QUALIFIED_NAME_2(_namespaces_,_classes_,_name_)< o_PP_IDENTITY _template_params_ >, o_read_compilation_counter> {};\
    o_namespace_end(phantom, reflection)


#define o_reflection_specialize_type_name_of_counter(_name_)    \
    o_namespace_begin(phantom, reflection, detail)            \
    template<int t_init_counter>                                               \
class type_name_of_counter< ::_name_, t_init_counter, o_read_compilation_counter>     \
    {                                                        \
    public:   \
    o_reflection_specialize_type_name_static_member_functions(_name_)\
    };                                                         \
    o_namespace_end(phantom, reflection, detail)

#define o_reflection_specialize_type_name_of_counterN(_namespaces_, _name_)    \
    o_namespace_begin(phantom, reflection, detail)                                            \
    template<int t_init_counter>                                                                               \
class type_name_of_counter<o_PP_CREATE_QUALIFIED_NAME(_namespaces_,_name_),t_init_counter, o_read_compilation_counter>     \
    {                                                                            \
    public:                                                          \
    o_reflection_specialize_type_name_static_member_functionsN(_namespaces_, _name_)\
    };                                                                         \
    o_namespace_end(phantom, reflection, detail)

#define o_reflection_specialize_type_name_of_counterC(_classes_, _name_)    \
    o_namespace_begin(phantom, reflection, detail)                                            \
    template<int t_init_counter>                                                                               \
class type_name_of_counter<o_PP_CREATE_QUALIFIED_NAME(_classes_,_name_),t_init_counter, o_read_compilation_counter>     \
    {                                                                            \
    public:                                                          \
    o_reflection_specialize_type_name_static_member_functionsC(_classes_, _name_)\
    };                                                                         \
    o_namespace_end(phantom, reflection, detail)

#define o_reflection_specialize_type_name_of_counterNC(_namespaces_, _classes_, _name_)    \
    o_namespace_begin(phantom, reflection, detail)                                            \
    template<int t_init_counter>                                                                               \
class type_name_of_counter<o_PP_CREATE_QUALIFIED_NAME_2(_namespaces_,_classes_, _name_),t_init_counter, o_read_compilation_counter>     \
    {                                                                            \
    public:                                                          \
    o_reflection_specialize_type_name_static_member_functionsNC(_namespaces_, _classes_, _name_)\
    };                                                                         \
    o_namespace_end(phantom, reflection, detail)

#define o_reflection_specialize_type_name_of_counterNT(_namespaces_, _template_types_, _template_params_, _name_) \
    o_namespace_begin(phantom, reflection, detail) \
    template<o_PP_MIX(_template_types_, _template_params_), int t_init_counter> \
class type_name_of_counter<o_PP_CREATE_QUALIFIED_NAME(_namespaces_,_name_)< o_PP_IDENTITY _template_params_ >, t_init_counter, o_read_compilation_counter> \
    { \
    public: \
    o_reflection_specialize_type_name_static_member_counter_functionsNT(_namespaces_, _template_types_, _template_params_, _name_, t_init_counter) \
    };\
    o_namespace_end(phantom, reflection, detail)

#define o_reflection_specialize_type_name_of_counterCT(_classes_, _template_types_, _template_params_, _name_) \
    o_namespace_begin(phantom, reflection, detail) \
    template<o_PP_MIX(_template_types_, _template_params_), int t_init_counter> \
class type_name_of_counter<o_PP_CREATE_QUALIFIED_NAME(_classes_,_name_)< o_PP_IDENTITY _template_params_ >, t_init_counter, o_read_compilation_counter> \
    { \
    public: \
    o_reflection_specialize_type_name_static_member_counter_functionsCT(_classes_, _template_types_, _template_params_, _name_, t_init_counter) \
    };\
    o_namespace_end(phantom, reflection, detail)

#define o_reflection_specialize_type_name_of_counterNCT(_namespaces_, _classes_, _template_types_, _template_params_, _name_) \
    o_namespace_begin(phantom, reflection, detail) \
    template<o_PP_MIX(_template_types_, _template_params_), int t_init_counter> \
    class type_name_of_counter<o_PP_CREATE_QUALIFIED_NAME_2(_namespaces_,_classes_, _name_)< o_PP_IDENTITY _template_params_ >, t_init_counter, o_read_compilation_counter> \
    { \
    public: \
    o_reflection_specialize_type_name_static_member_counter_functionsNCT(_namespaces_, _classes_, _template_types_, _template_params_, _name_, t_init_counter) \
    };\
    o_namespace_end(phantom, reflection, detail)


#define o_reflection_specialize_type_name_of_counterT(_template_types_, _template_params_, _name_) \
    o_namespace_begin(phantom, reflection, detail) \
    template<o_PP_MIX(_template_types_, _template_params_), int t_init_counter> \
    class type_name_of_counter< ::_name_< o_PP_IDENTITY _template_params_ >,t_init_counter, o_read_compilation_counter> \
    { \
    public: \
    o_reflection_specialize_type_name_static_member_counter_functionsT(_template_types_, _template_params_, _name_, t_init_counter) \
    };\
    o_namespace_end(phantom, reflection, detail)


#define o_reflection_specialize_type_name_of_impl(_name_)    \
    o_namespace_begin(phantom, reflection, detail)            \
    template<int t_init_counter, int t_counter>                                               \
class type_name_of_counter< ::_name_, t_init_counter, t_counter>     \
    {                                                        \
    public:   \
    o_reflection_specialize_type_name_static_member_functions(_name_)\
    };                                                         \
    o_namespace_end(phantom, reflection, detail)

#define o_reflection_specialize_type_name_of_implN(_namespaces_, _name_)    \
    o_namespace_begin(phantom, reflection, detail)                                            \
    template<int t_init_counter, int t_counter>                                                                               \
class type_name_of_counter<o_PP_CREATE_QUALIFIED_NAME(_namespaces_,_name_), t_init_counter, t_counter>     \
    {                                                                            \
    public:                                                          \
    o_reflection_specialize_type_name_static_member_functionsN(_namespaces_, _name_)\
    };                                                                         \
    o_namespace_end(phantom, reflection, detail)

#define o_reflection_specialize_type_name_of_implC(_classes_, _name_)    \
    o_namespace_begin(phantom, reflection, detail)                                            \
    template<int t_init_counter, int t_counter>                                                                               \
class type_name_of_counter<o_PP_CREATE_QUALIFIED_NAME(_classes_,_name_), t_init_counter, t_counter>     \
    {                                                                            \
    public:                                                          \
    o_reflection_specialize_type_name_static_member_functionsC(_classes_, _name_)\
    };                                                                         \
    o_namespace_end(phantom, reflection, detail)

#define o_reflection_specialize_type_name_of_implNC(_namespaces_, _classes_, _name_)    \
    o_namespace_begin(phantom, reflection, detail)                                            \
    template<int t_init_counter, int t_counter>                                                                               \
class type_name_of_counter<o_PP_CREATE_QUALIFIED_NAME_2(_namespaces_,_classes_, _name_), t_init_counter, t_counter>     \
    {                                                                            \
    public:                                                          \
    o_reflection_specialize_type_name_static_member_functionsNC(_namespaces_, _classes_, _name_)\
    };                                                                         \
    o_namespace_end(phantom, reflection, detail)

#define o_reflection_specialize_type_name_of_implNT(_namespaces_, _template_types_, _template_params_, _name_) \
    o_namespace_begin(phantom, reflection, detail) \
    template<o_PP_MIX(_template_types_, _template_params_), int t_init_counter, int t_counter> \
class type_name_of_counter<o_PP_CREATE_QUALIFIED_NAME(_namespaces_,_name_)< o_PP_IDENTITY _template_params_ >, t_init_counter, t_counter> \
    { \
    public: \
    o_reflection_specialize_type_name_static_member_counter_functionsNT(_namespaces_, _template_types_, _template_params_, _name_, o_read_compilation_counter) \
    };\
    o_namespace_end(phantom, reflection, detail)

#define o_reflection_specialize_type_name_of_implNPT(_namespaces_, _template_types_, _template_params_, _template_spec_, _name_) \
    o_namespace_begin(phantom, reflection, detail) \
    template<o_PP_MIX(_template_types_, _template_params_), int t_init_counter, int t_counter> \
class type_name_of_counter<o_PP_CREATE_QUALIFIED_NAME(_namespaces_,_name_)< o_PP_IDENTITY _template_params_, o_PP_IDENTITY _template_spec_ >, t_init_counter, t_counter> \
    { \
    public: \
    o_reflection_specialize_type_name_static_member_counter_functionsNPT(_namespaces_, _template_types_, _template_params_, _template_spec_, _name_, o_read_compilation_counter) \
    };\
    o_namespace_end(phantom, reflection, detail)

#define o_reflection_specialize_type_name_of_implCT(_classes_, _template_types_, _template_params_, _name_) \
    o_namespace_begin(phantom, reflection, detail) \
    template<o_PP_MIX(_template_types_, _template_params_), int t_init_counter, int t_counter> \
class type_name_of_counter<o_PP_CREATE_QUALIFIED_NAME(_classes_,_name_)< o_PP_IDENTITY _template_params_ >, t_init_counter, t_counter> \
    { \
    public: \
    o_reflection_specialize_type_name_static_member_counter_functionsCT(_classes_, _template_types_, _template_params_, _name_, o_read_compilation_counter) \
    };\
    o_namespace_end(phantom, reflection, detail)

#define o_reflection_specialize_type_name_of_implNCT(_namespaces_, _classes_, _template_types_, _template_params_, _name_) \
    o_namespace_begin(phantom, reflection, detail) \
    template<o_PP_MIX(_template_types_, _template_params_), int t_init_counter, int t_counter> \
class type_name_of_counter<o_PP_CREATE_QUALIFIED_NAME_2(_namespaces_,_classes_, _name_)< o_PP_IDENTITY _template_params_ >, t_init_counter, t_counter> \
    { \
    public: \
    o_reflection_specialize_type_name_static_member_counter_functionsNCT(_namespaces_, _classes_, _template_types_, _template_params_, _name_, o_read_compilation_counter) \
    };\
    o_namespace_end(phantom, reflection, detail)


#define o_reflection_specialize_type_name_of_implT(_template_types_, _template_params_, _name_) \
    o_namespace_begin(phantom, reflection, detail) \
    template<o_PP_MIX(_template_types_, _template_params_), int t_init_counter, int t_counter> \
class type_name_of_counter< ::_name_< o_PP_IDENTITY _template_params_ >, t_init_counter, t_counter> \
    { \
    public: \
    o_reflection_specialize_type_name_static_member_counter_functionsT(_template_types_, _template_params_, _name_, o_read_compilation_counter) \
    };\
    o_namespace_end(phantom, reflection, detail)










#define o_reflection_specialize_type_of(_name_) \
    o_namespace_begin(phantom, reflection, detail) \
    template<int t_counter>  \
struct type_of_counter<_name_, t_counter> \
    : public detail::type_of_counter_defined< ::_name_, o_read_compilation_counter> {};\
    o_namespace_end(phantom, reflection, detail)

#define o_reflection_specialize_type_ofN(_namespaces_, _name_) \
    o_namespace_begin(phantom, reflection, detail) \
    template<int t_counter>  \
struct type_of_counter<o_PP_CREATE_QUALIFIED_NAME(_namespaces_,_name_), t_counter> \
    : public detail::type_of_counter_defined<o_PP_CREATE_QUALIFIED_NAME(_namespaces_,_name_), o_read_compilation_counter> {};\
    o_namespace_end(phantom, reflection, detail)

#define o_reflection_specialize_type_ofT(_template_types_, _template_params_, _name_) \
    o_namespace_begin(phantom, reflection, detail) \
    template<o_PP_MIX(_template_types_, _template_params_), int t_counter>  \
struct type_of_counter< ::_name_< o_PP_IDENTITY _template_params_ >, t_counter> \
    : public detail::type_of_counter_defined< ::_name_< o_PP_IDENTITY _template_params_ > , o_read_compilation_counter> {};\
    o_namespace_end(phantom, reflection, detail)

#define o_reflection_specialize_type_ofNT(_namespaces_, _template_types_, _template_params_, _name_) \
    o_namespace_begin(phantom, reflection, detail) \
    template<o_PP_MIX(_template_types_, _template_params_), int t_counter>  \
struct type_of_counter<o_PP_CREATE_QUALIFIED_NAME(_namespaces_,_name_) < o_PP_IDENTITY _template_params_ >, t_counter> \
    : public detail::type_of_counter_defined<o_PP_CREATE_QUALIFIED_NAME(_namespaces_,_name_)< o_PP_IDENTITY _template_params_ > , o_read_compilation_counter> {};\
    o_namespace_end(phantom, reflection, detail)

#define o_reflection_specialize_type_ofNCT(_namespaces_, _classes_, _template_types_, _template_params_, _name_) \
    o_namespace_begin(phantom, reflection, detail) \
    template<o_PP_MIX(_template_types_, _template_params_), int t_counter>  \
struct type_of_counter<o_PP_CREATE_QUALIFIED_NAME_2(_namespaces_, _classes_,_name_) < o_PP_IDENTITY _template_params_ >, t_counter> \
    : public detail::type_of_counter_defined<o_PP_CREATE_QUALIFIED_NAME_2(_namespaces_, _classes_,_name_)< o_PP_IDENTITY _template_params_ > , o_read_compilation_counter> {};\
    o_namespace_end(phantom, reflection, detail)

#define o_reflection_specialize_type_ofNC(_namespaces_, _classes_, _name_) \
    o_namespace_begin(phantom, reflection, detail) \
    template<int t_counter>  \
struct type_of_counter<o_PP_CREATE_QUALIFIED_NAME_2(_namespaces_,_classes_, _name_), t_counter> \
    : public detail::type_of_counter_defined<o_PP_CREATE_QUALIFIED_NAME_2(_namespaces_, _classes_,_name_), o_read_compilation_counter> {};\
    o_namespace_end(phantom, reflection, detail)

#define o_reflection_specialize_type_ofC(_classes_, _name_) \
    o_namespace_begin(phantom, reflection, detail) \
    template<int t_counter>  \
struct type_of_counter<o_PP_CREATE_QUALIFIED_NAME(_classes_,_name_), t_counter> \
    : public detail::type_of_counter_defined<o_PP_CREATE_QUALIFIED_NAME(_classes_,_name_), o_read_compilation_counter> {};\
    o_namespace_end(phantom, reflection, detail)

#define o_reflection_specialize_type_ofCT(_classes_, _template_types_, _template_params_, _name_) \
    o_namespace_begin(phantom, reflection, detail) \
    template<o_PP_MIX(_template_types_, _template_params_), int t_counter>  \
struct type_of_counter<o_PP_CREATE_QUALIFIED_NAME(_classes_,_name_)< o_PP_IDENTITY _template_params_ >, t_counter> \
    : public detail::type_of_counter_defined<o_PP_CREATE_QUALIFIED_NAME(_classes_,_name_)< o_PP_IDENTITY _template_params_ > , o_read_compilation_counter> {};\
    o_namespace_end(phantom, reflection, detail)




#define o_reflection_in_cpp_deferred_setupN(_namespaces_,_name)\
    o_reflection_specialize_type_ofN(_namespaces_,_name)

#define o_class_declare(_name_) \
    o_declare o_PP_LEFT_PAREN class, _name_ o_PP_RIGHT_PAREN

#define o_class_declareN(_namespaces_, _name_) \
    o_declare o_PP_LEFT_PAREN class, o_PP_IDENTITY _namespaces_, _name_ o_PP_RIGHT_PAREN

#if o__int__reflection_template_use_level == 3
#   include "def_reflection_3.h" 
#elif o__int__reflection_template_use_level == 2
#   include "def_reflection_2.h"
#elif o__int__reflection_template_use_level == 1
#   include "def_reflection_1.h"
#else
#   include "def_reflection_0.h"
#endif

#if o_COMPILER == o_COMPILER_VISUAL_STUDIO
#   define o_data_member(...) o_PP_CAT(o_PP_CAT(o_data_member_,o_PP_NARG(__VA_ARGS__)),(__VA_ARGS__))
#   define o_property(...) o_PP_CAT(o_PP_CAT(o_property_,o_PP_NARG(__VA_ARGS__)),(__VA_ARGS__))
#   define o_collection(...) o_PP_CAT(o_PP_CAT(o_collection_,o_PP_NARG(__VA_ARGS__)),(__VA_ARGS__))
#   define o_range(...) o_PP_CAT(o_PP_CAT(o_range_,o_PP_NARG(__VA_ARGS__)),(__VA_ARGS__))
#   define o_typedef(...) o_PP_CAT(o_PP_CAT(o_typedef_,o_PP_NARG(__VA_ARGS__)),(__VA_ARGS__))
#else
#   define o_data_member(...) o_PP_CAT(o_data_member_,o_PP_NARG(__VA_ARGS__)) (__VA_ARGS__)
#   define o_property(...) o_PP_CAT(o_property_,o_PP_NARG(__VA_ARGS__)) (__VA_ARGS__)
#   define o_collection(...) o_PP_CAT(o_collection_,o_PP_NARG(__VA_ARGS__)) (__VA_ARGS__)
#   define o_range(...) o_PP_CAT(o_range_,o_PP_NARG(__VA_ARGS__)) (__VA_ARGS__)
#   define o_typedef(...) o_PP_CAT(o_typedef_,o_PP_NARG(__VA_ARGS__)) (__VA_ARGS__)
#endif

#define o_default_template_argument_constant(parameter, ...)\
class o_PP_CAT(parameter,__LINE__) \
        {\
        friend class enclosed_reflection;\
        o_PP_CAT(parameter,__LINE__)() \
            {\
            phantom::reflection::Types::currentInstalledTemplateSpecialization->setDefaultArgument(#parameter, o_dynamic_proxy_new(phantom::reflection::Constant, phantom::reflection::Constant::metaType, phantom::reflection::native::TNumericConstant<decltype(parameter)>)(parameter));\
            }\
        } o_PP_CAT(parameter,__LINE__);

#    define o_range_1(_default_) \
    phantom::reflection::native::CreateRange(_default_)

#    define o_range_2(_min_, _max_) \
    phantom::reflection::native::CreateRange(_min_, _max_)

#    define o_range_3(_min_, _default_, _max_) \
    phantom::reflection::native::CreateRange(_min_, _default_, _max_)

#    define o_data_member_2(_type_, _name_) \
    o_data_member_5(_type_, _name_, (phantom::reflection::native::null_range), 0, 0xffffffff)

#    define o_data_member_3(_type_, _name_, _range_) \
    o_data_member_5(_type_, _name_, _range_, 0, 0xffffffff)

#    define o_data_member_4(_type_, _name_, _range_, _modifiers_) \
    o_data_member_5(_type_, _name_, _range_, _modifiers_, (((_modifiers_&o_transient)==0)?0xffffffff:0))

#define o_property_4(_type_, _name_, _set_member_function_, _get_member_function_)\
    o_property_8(_type_, _name_, _set_member_function_, _get_member_function_, m_PHANTOM_RESERVED_no_signal, (phantom::reflection::native::null_range), 0, 0xffffffff)

#define o_property_5(_type_, _name_, _set_member_function_, _get_member_function_, _signal_)\
    o_property_8(_type_, _name_, _set_member_function_, _get_member_function_, _signal_, (phantom::reflection::native::null_range), 0, 0xffffffff)

#define o_property_6(_type_, _name_, _set_member_function_, _get_member_function_, _signal_, _range_)\
    o_property_8(_type_, _name_, _set_member_function_, _get_member_function_, _signal_, _range_, 0, 0xffffffff)

#define o_property_7(_type_, _name_, _set_member_function_, _get_member_function_, _signal_, _range_, _modifiers_)\
    o_property_8(_type_, _name_, _set_member_function_, _get_member_function_, _signal_, _range_, _modifiers_, (((_modifiers_&o_transient)==0)?0xffffffff:0))

#define o_collection_8(_type_, _name_, _add_member_function_, _remove_member_function_, _move_member_function_, _set_member_function_, _get_member_function_, _size_member_function_)\
    o_collection_9(_type_, _name_, _add_member_function_, _remove_member_function_, _move_member_function_, _set_member_function_, _get_member_function_, _size_member_function_, 0)

#define o_traits_specialize_all_super_traitNTS_TNativeMemberFunctionXXX(_native_member_function_) \
    o_namespace_begin(phantom, reflection, native)                                                                                                                                        \
    \
    template<typename t_Ty, typename t_Signature>                                                                                                                                             \
struct _native_member_function_##FunctionStyleSuperClassSolver;                                                                                                                                    \
    \
    template<typename t_Ty>                                                                                                                                                                   \
struct _native_member_function_##FunctionStyleSuperClassSolver<t_Ty, signal_t()>                                                                                                                   \
{                                                                                                                                                                                         \
    typedef _native_member_function_##0<t_Ty> type;                                                                                                                                                \
};                                                                                                                                                                                        \
    \
    template<typename t_Ty, typename t_Param0>                                                                                                                                                \
struct _native_member_function_##FunctionStyleSuperClassSolver<t_Ty, signal_t(t_Param0)>                                                                                                           \
{                                                                                                                                                                                         \
    typedef _native_member_function_##1<t_Ty, t_Param0> type;                                                                                                                                      \
};                                                                                                                                                                                        \
    \
    \
    template<typename t_Ty, typename t_Param0, typename t_Param1>                                                                                                                             \
struct _native_member_function_##FunctionStyleSuperClassSolver<t_Ty, signal_t(t_Param0, t_Param1)>                                                                                                 \
{                                                                                                                                                                                         \
    typedef _native_member_function_##2<t_Ty, t_Param0, t_Param1> type;                                                                                                                            \
};                                                                                                                                                                                        \
    \
    \
    template<typename t_Ty, typename t_Param0, typename t_Param1, typename t_Param2>                                                                                                          \
struct _native_member_function_##FunctionStyleSuperClassSolver<t_Ty, signal_t(t_Param0, t_Param1, t_Param2)>                                                                                       \
{                                                                                                                                                                                         \
    typedef _native_member_function_##3<t_Ty, t_Param0, t_Param1, t_Param2> type;                                                                                                                  \
};                                                                                                                                                                                        \
    \
    template<typename t_Ty, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3>                                                                                       \
struct _native_member_function_##FunctionStyleSuperClassSolver<t_Ty, signal_t(t_Param0, t_Param1, t_Param2, t_Param3)>                                                                             \
{                                                                                                                                                                                         \
    typedef _native_member_function_##4<t_Ty, t_Param0, t_Param1, t_Param2, t_Param3> type;                                                                                                        \
};                                                                                                                                                                                        \
    \
    \
    template<typename t_Ty, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3, typename t_Param4>                                                                    \
struct _native_member_function_##FunctionStyleSuperClassSolver<t_Ty, signal_t(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4)>                                                                   \
{                                                                                                                                                                                         \
    typedef _native_member_function_##5<t_Ty, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4> type;                                                                                              \
};                                                                                                                                                                                        \
    \
    \
    template<typename t_Ty, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3, typename t_Param4, typename t_Param5>                                                 \
struct _native_member_function_##FunctionStyleSuperClassSolver<t_Ty, signal_t(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5)>                                                         \
{                                                                                                                                                                                         \
    typedef _native_member_function_##6<t_Ty, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5> type;                                                                                    \
};                                                                                                                                                                                        \
    \
    template<typename t_Ty, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3, typename t_Param4, typename t_Param5, typename t_Param6>                              \
struct _native_member_function_##FunctionStyleSuperClassSolver<t_Ty, signal_t(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6)>                                               \
{                                                                                                                                                                                         \
    typedef _native_member_function_##7<t_Ty, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6> type;                                                                          \
};                                                                                                                                                                                        \
    \
    \
    \
    template<typename t_Ty, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3, typename t_Param4, typename t_Param5, typename t_Param6, typename t_Param7>           \
struct _native_member_function_##FunctionStyleSuperClassSolver<t_Ty, signal_t(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7)>                                     \
{                                                                                                                                                                                         \
    typedef _native_member_function_##8<t_Ty, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7> type;                                                                \
};                                                                                                                                                                                        \
    o_namespace_end(phantom, reflection, native)                                                                                                                                              \
    \
    o_traits_specialize_all_super_traitNTS(                                                                                                                                              \
    (phantom,reflection,native)                                                                                                                                                           \
    , (typename)                                                                                                                                                                          \
    , (t_Ty)                                                                                                                                                                              \
    , _native_member_function_##0                                                                                                                                                                  \
    , (_native_member_function_##Base<t_Ty>)                                                                                                                                                       \
    )                                                                                                                                                                                     \
    o_traits_specialize_all_super_traitNTS(                                                                                                                                              \
    (phantom,reflection,native)                                                                                                                                                           \
    , (typename,typename)                                                                                                                                                                 \
    , (t_Ty, t_Param0)                                                                                                                                                                    \
    , _native_member_function_##1                                                                                                                                                                  \
    , (_native_member_function_##Base<t_Ty>)                                                                                                                                                       \
    )                                                                                                                                                                                     \
    o_traits_specialize_all_super_traitNTS(                                                                                                                                              \
    (phantom,reflection,native)                                                                                                                                                           \
    , (typename,typename,typename)                                                                                                                                                        \
    , (t_Ty, t_Param0,t_Param1)                                                                                                                                                           \
    , _native_member_function_##2                                                                                                                                                                  \
    , (_native_member_function_##Base<t_Ty>)                                                                                                                                                       \
    )                                                                                                                                                                                     \
    o_traits_specialize_all_super_traitNTS(                                                                                                                                              \
    (phantom,reflection,native)                                                                                                                                                           \
    , (typename,typename,typename,typename)                                                                                                                                               \
    , (t_Ty, t_Param0,t_Param1,t_Param2)                                                                                                                                                  \
    , _native_member_function_##3                                                                                                                                                                  \
    , (_native_member_function_##Base<t_Ty>)                                                                                                                                                       \
    )                                                                                                                                                                                     \
    o_traits_specialize_all_super_traitNTS(                                                                                                                                              \
    (phantom,reflection,native)                                                                                                                                                           \
    , (typename,typename,typename,typename,typename)                                                                                                                                      \
    , (t_Ty, t_Param0, t_Param1, t_Param2, t_Param3)                                                                                                                                      \
    , _native_member_function_##4                                                                                                                                                                  \
    , (_native_member_function_##Base<t_Ty>)                                                                                                                                                       \
    )                                                                                                                                                                                     \
    o_traits_specialize_all_super_traitNTS(                                                                                                                                              \
    (phantom,reflection,native)                                                                                                                                                           \
    , (typename,typename,typename,typename,typename,typename)                                                                                                                             \
    , (t_Ty, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4)                                                                                                                            \
    , _native_member_function_##5                                                                                                                                                                  \
    , (_native_member_function_##Base<t_Ty>)                                                                                                                                                       \
    )                                                                                                                                                                                     \
    o_traits_specialize_all_super_traitNTS(                                                                                                                                              \
    (phantom,reflection,native)                                                                                                                                                           \
    , (typename,typename,typename,typename,typename,typename,typename)                                                                                                                    \
    , (t_Ty, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5)                                                                                                                  \
    , _native_member_function_##6                                                                                                                                                                  \
    , (_native_member_function_##Base<t_Ty>)                                                                                                                                                       \
    )                                                                                                                                                                                     \
    o_traits_specialize_all_super_traitNTS(                                                                                                                                              \
    (phantom,reflection,native)                                                                                                                                                           \
    , (typename,typename,typename,typename,typename,typename,typename,typename)                                                                                                           \
    , (t_Ty, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6)                                                                                                        \
    , _native_member_function_##7                                                                                                                                                                  \
    , (_native_member_function_##Base<t_Ty>)                                                                                                                                                       \
    )                                                                                                                                                                                     \
    o_traits_specialize_all_super_traitNTS(                                                                                                                                              \
    (phantom,reflection,native)                                                                                                                                                           \
    , (typename,typename,typename,typename,typename,typename,typename,typename,typename)                                                                                                  \
    , (t_Ty, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7)                                                                                              \
    , _native_member_function_##8                                                                                                                                                                  \
    , (_native_member_function_##Base<t_Ty>)                                                                                                                                                       \
    )                                                                                                                                                                                     \
    o_traits_specialize_all_super_traitNTS(                                                                                                                                              \
    (phantom,reflection,native)                                                                                                                                                           \
    , (typename, typename)                                                                                                                                                                \
    , (t_Ty, t_Signature)                                                                                                                                                                 \
    , _native_member_function_                                                                                                                                                                     \
    , (o_NESTED_TYPE _native_member_function_##FunctionStyleSuperClassSolver<t_Ty,t_Signature>::type)                                                                                              \
    )



#define o_traits_specialize_all_super_traitNTS_TNativeMemberFunctionRTXXX(_native_member_function_) \
    o_namespace_begin(phantom, reflection, native)                                                                                                                                        \
    \
    template<typename t_Ty, typename t_Signature>                                                                                                                                             \
struct _native_member_function_##FunctionStyleSuperClassSolver;                                                                                                                                    \
    \
    template<typename t_Ty, typename t_ReturnType>                                                                                                                                                                   \
struct _native_member_function_##FunctionStyleSuperClassSolver<t_Ty, t_ReturnType()>                                                                                                                   \
{                                                                                                                                                                                         \
    typedef _native_member_function_##0<t_Ty, t_ReturnType> type;                                                                                                                                                \
};                                                                                                                                                                                        \
    \
    template<typename t_Ty, typename t_ReturnType, typename t_Param0>                                                                                                                                                \
struct _native_member_function_##FunctionStyleSuperClassSolver<t_Ty, t_ReturnType(t_Param0)>                                                                                                           \
{                                                                                                                                                                                         \
    typedef _native_member_function_##1<t_Ty, t_ReturnType, t_Param0> type;                                                                                                                                      \
};                                                                                                                                                                                        \
    \
    \
    template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1>                                                                                                                             \
struct _native_member_function_##FunctionStyleSuperClassSolver<t_Ty, t_ReturnType(t_Param0, t_Param1)>                                                                                                 \
{                                                                                                                                                                                         \
    typedef _native_member_function_##2<t_Ty, t_ReturnType, t_Param0, t_Param1> type;                                                                                                                            \
};                                                                                                                                                                                        \
    \
    \
    template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2>                                                                                                          \
struct _native_member_function_##FunctionStyleSuperClassSolver<t_Ty, t_ReturnType(t_Param0, t_Param1, t_Param2)>                                                                                       \
{                                                                                                                                                                                         \
    typedef _native_member_function_##3<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2> type;                                                                                                                  \
};                                                                                                                                                                                        \
    \
    template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3>                                                                                       \
struct _native_member_function_##FunctionStyleSuperClassSolver<t_Ty, t_ReturnType(t_Param0, t_Param1, t_Param2, t_Param3)>                                                                             \
{                                                                                                                                                                                         \
    typedef _native_member_function_##4<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3> type;                                                                                                        \
};                                                                                                                                                                                        \
    \
    \
    template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3, typename t_Param4>                                                                    \
struct _native_member_function_##FunctionStyleSuperClassSolver<t_Ty, t_ReturnType(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4)>                                                                   \
{                                                                                                                                                                                         \
    typedef _native_member_function_##5<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4> type;                                                                                              \
};                                                                                                                                                                                        \
    \
    \
    template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3, typename t_Param4, typename t_Param5>                                                 \
struct _native_member_function_##FunctionStyleSuperClassSolver<t_Ty, t_ReturnType(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5)>                                                         \
{                                                                                                                                                                                         \
    typedef _native_member_function_##6<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5> type;                                                                                    \
};                                                                                                                                                                                        \
    \
    template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3, typename t_Param4, typename t_Param5, typename t_Param6>                              \
struct _native_member_function_##FunctionStyleSuperClassSolver<t_Ty, t_ReturnType(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6)>                                               \
{                                                                                                                                                                                         \
    typedef _native_member_function_##7<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6> type;                                                                          \
};                                                                                                                                                                                        \
    \
    \
    \
    template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3, typename t_Param4, typename t_Param5, typename t_Param6, typename t_Param7>           \
struct _native_member_function_##FunctionStyleSuperClassSolver<t_Ty, t_ReturnType(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7)>                                     \
{                                                                                                                                                                                         \
    typedef _native_member_function_##8<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7> type;                                                                \
};                                                                                                                                                                                        \
    o_namespace_end(phantom, reflection, native)                                                                                                                                              \
    \
    o_traits_specialize_all_super_traitNTS(                                                                                                                                              \
    (phantom,reflection,native)                                                                                                                                                           \
    , (typename,typename)                                                                                                                                                                          \
    , (t_Ty, t_ReturnType)                                                                                                                                                                              \
    , _native_member_function_##0                                                                                                                                                                  \
    , (_native_member_function_##Base<t_Ty>)                                                                                                                                                       \
    )                                                                                                                                                                                     \
    o_traits_specialize_all_super_traitNTS(                                                                                                                                              \
    (phantom,reflection,native)                                                                                                                                                           \
    , (typename,typename,typename)                                                                                                                                                                 \
    , (t_Ty, t_ReturnType, t_Param0)                                                                                                                                                                    \
    , _native_member_function_##1                                                                                                                                                                  \
    , (_native_member_function_##Base<t_Ty>)                                                                                                                                                       \
    )                                                                                                                                                                                     \
    o_traits_specialize_all_super_traitNTS(                                                                                                                                              \
    (phantom,reflection,native)                                                                                                                                                           \
    , (typename,typename,typename,typename)                                                                                                                                                        \
    , (t_Ty, t_ReturnType, t_Param0,t_Param1)                                                                                                                                                           \
    , _native_member_function_##2                                                                                                                                                                  \
    , (_native_member_function_##Base<t_Ty>)                                                                                                                                                       \
    )                                                                                                                                                                                     \
    o_traits_specialize_all_super_traitNTS(                                                                                                                                              \
    (phantom,reflection,native)                                                                                                                                                           \
    , (typename,typename,typename,typename,typename)                                                                                                                                               \
    , (t_Ty, t_ReturnType, t_Param0,t_Param1,t_Param2)                                                                                                                                                  \
    , _native_member_function_##3                                                                                                                                                                  \
    , (_native_member_function_##Base<t_Ty>)                                                                                                                                                       \
    )                                                                                                                                                                                     \
    o_traits_specialize_all_super_traitNTS(                                                                                                                                              \
    (phantom,reflection,native)                                                                                                                                                           \
    , (typename,typename,typename,typename,typename,typename)                                                                                                                                      \
    , (t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3)                                                                                                                                      \
    , _native_member_function_##4                                                                                                                                                                  \
    , (_native_member_function_##Base<t_Ty>)                                                                                                                                                       \
    )                                                                                                                                                                                     \
    o_traits_specialize_all_super_traitNTS(                                                                                                                                              \
    (phantom,reflection,native)                                                                                                                                                           \
    , (typename,typename,typename,typename,typename,typename,typename)                                                                                                                             \
    , (t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4)                                                                                                                            \
    , _native_member_function_##5                                                                                                                                                                  \
    , (_native_member_function_##Base<t_Ty>)                                                                                                                                                       \
    )                                                                                                                                                                                     \
    o_traits_specialize_all_super_traitNTS(                                                                                                                                              \
    (phantom,reflection,native)                                                                                                                                                           \
    , (typename,typename,typename,typename,typename,typename,typename,typename)                                                                                                                    \
    , (t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5)                                                                                                                  \
    , _native_member_function_##6                                                                                                                                                                  \
    , (_native_member_function_##Base<t_Ty>)                                                                                                                                                       \
    )                                                                                                                                                                                     \
    o_traits_specialize_all_super_traitNTS(                                                                                                                                              \
    (phantom,reflection,native)                                                                                                                                                           \
    , (typename,typename,typename,typename,typename,typename,typename,typename,typename)                                                                                                           \
    , (t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6)                                                                                                        \
    , _native_member_function_##7                                                                                                                                                                  \
    , (_native_member_function_##Base<t_Ty>)                                                                                                                                                       \
    )                                                                                                                                                                                     \
    o_traits_specialize_all_super_traitNTS(                                                                                                                                              \
    (phantom,reflection,native)                                                                                                                                                           \
    , (typename,typename,typename,typename,typename,typename,typename,typename,typename,typename)                                                                                                  \
    , (t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7)                                                                                              \
    , _native_member_function_##8                                                                                                                                                                  \
    , (_native_member_function_##Base<t_Ty>)                                                                                                                                                       \
    )                                                                                                                                                                                     \
    o_traits_specialize_all_super_traitNTS(                                                                                                                                              \
    (phantom,reflection,native)                                                                                                                                                           \
    , (typename, typename)                                                                                                                                                                \
    , (t_Ty, t_Signature)                                                                                                                                                                 \
    , _native_member_function_                                                                                                                                                                     \
    , (o_NESTED_TYPE _native_member_function_##FunctionStyleSuperClassSolver<t_Ty,t_Signature>::type)                                                                                              \
    )

#if o_COMPILER == o_COMPILER_VISUAL_STUDIO
#define o_enum_add_values( ... ) o_PP_CAT(o_PP_CAT(o_enum_add_values_, o_PP_NARG(__VA_ARGS__)),(__VA_ARGS__) )
#else
#define o_enum_add_values( ... ) o_PP_CAT(o_enum_add_values_, o_PP_NARG(__VA_ARGS__)) (__VA_ARGS__) 
#endif

#define o_enum_add_values_1( v0) pEnum->addConstant(o_dynamic_proxy_new(phantom::reflection::Constant, phantom::reflection::Constant::metaType, phantom::reflection::native::TNumericConstant<enum_value_type>)(o_PP_QUOTE(v0), v0));
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

#define o_enum_add_valuesN_2( n, v0) pEnum->addConstant(o_dynamic_proxy_new(phantom::reflection::Constant, phantom::reflection::Constant::metaType, phantom::reflection::native::TNumericConstant<enum_value_type>)(o_PP_QUOTE(v0), ::o_PP_CREATE_SCOPE n::v0));
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




#endif // o_phantom_reflection_h__
