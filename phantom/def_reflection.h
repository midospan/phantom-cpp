#ifndef o_phantom_reflection_h__
#define o_phantom_reflection_h__


#define o_reflection_register_class_type(_namespace_, ...) \
    phantom::reflection::class_type_registrer< _namespace_::__VA_ARGS__ > o_PP_CAT(g_reflection_registration_, __COUNTER__);

#define o_register_template_instance(...) \
    phantom::reflection::template_specialization_registrer< __VA_ARGS__ > o_PP_CAT(g_reflection_template_registration_, __COUNTER__);

#define o_register_typedef(_typedef_) \
    phantom::reflection::typedef_registrer  o_PP_CAT(g_reflection_registration_##_typedef_, __COUNTER__) (#_typedef_, phantom::typeOf<_typedef_>());

#define o_register_typedefN(_namespace_, _typedef_) \
    phantom::reflection::typedef_registrer  o_PP_CAT(g_reflection_registration_##_typedef_, __COUNTER__) (#_namespace_, #_typedef_, phantom::typeOf<_namespace_::_typedef_>());

#define o_register_typedefNC(_namespace_, _class_, _typedef_) \
    o_register_typedefNC_helper(_namespace_, _class_, o_PP_CAT(g_reflection_registration_friend_##_typedef_, o_PP_IDENTITY o_PP_LEFT_PAREN __COUNTER__ o_PP_RIGHT_PAREN ), _typedef_)

#define o_register_typedefNC_helper(_namespace_, _class_, _friend_class_, _typedef_) \
    class _friend_class_ : public _namespace_::_class_\
    {\
    public:\
        typedef _typedef_ wrapped_typedef;\
    };\
    phantom::reflection::typedef_registrer  o_PP_CAT(g_reflection_registration_##_typedef_, __COUNTER__) (#_namespace_"::"#_class_, #_typedef_, phantom::typeOf<_friend_class_::wrapped_typedef>());

#define o_register_typedefC(_class_, _typedef_) \
    o_register_typedefC_helper(_class_, o_PP_CAT(g_reflection_registration_friend_##_typedef_, o_PP_IDENTITY o_PP_LEFT_PAREN __COUNTER__ o_PP_RIGHT_PAREN ), _typedef_)

#define o_register_typedefC_helper(_class_, _friend_class_, _typedef_) \
    class _friend_class_ : public _class_\
    {\
    public:\
        typedef _typedef_ wrapped_typedef;\
    };\
    phantom::reflection::typedef_registrer  o_PP_CAT(g_reflection_registration_##_typedef_, __COUNTER__) (#_class_, #_typedef_, phantom::typeOf<_friend_class_::wrapped_typedef>());

#define o_reflection_register_type(_namespace_, _type_) \
    phantom::reflection::detail::type_reflection_registrer<_namespace_::_type_> o_PP_CAT(g_reflection_registration_##_type_,__COUNTER__) ;

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
    phantom::reflection::detail::type_reflection_registrer<_namespace_::_type_> o_PP_CAT(g_reflection_registration_##_type_,__COUNTER__) ;

o_namespace_begin(phantom, reflection)

// Forward declarations
template<typename t_Ty>
struct super_classes_adder;

template<typename t_Ty>
struct meta_class_type_of;

namespace native { template<typename t_Ty> class TType; }


typedef vector<Type*>               function_signature;
typedef vector<TemplateElement*>    template_specialization;

void initializeSystem();

template<typename t_Ty>
struct template_specialization_registrer
{
    inline template_specialization_registrer() ;
};


struct o_export typedef_registrer
{
    typedef_registrer(const char* a_strScope, const char* a_strTypedef, Type* a_pType);
    typedef_registrer(const char* a_strTypedef, Type* a_pType);
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

namespace detail {

    template<typename t_Ty>
    struct type_reflection_registrer
    {
        o_static_assert_msg(phantom::has_reflection<t_Ty>::value, "registered class hasn't been declared with the reflection system");
        inline static void apply(Type* a_pType) ;
    };


    template<typename t_Ty, int t_counter>
    struct type_name_of_forward_helper_;

    template<typename t_Ty>
    struct type_name_list_of_helper_;

    template<typename t_Ty, boolean t_has_reflection>
    struct meta_class_type_of_helper_;

    template<typename t_Ty>
    struct type_name_of_helper_
    {
    public:
        static const char* decoratedName()
        {
            return type_name_of_forward_helper_<t_Ty,o_MAX_COMPILER_TEMPLATE_RECURSIVE_CYCLE>::decoratedName();
        }
        static const char* qualifiedDecoratedName()
        {
            return type_name_of_forward_helper_<t_Ty,o_MAX_COMPILER_TEMPLATE_RECURSIVE_CYCLE>::qualifiedDecoratedName();
        }
        static const char* name()
        {
            return type_name_of_forward_helper_<t_Ty,o_MAX_COMPILER_TEMPLATE_RECURSIVE_CYCLE>::name();
        }
        static const char* qualifiedName()
        {
            return type_name_of_forward_helper_<t_Ty,o_MAX_COMPILER_TEMPLATE_RECURSIVE_CYCLE>::qualifiedName();
        }
        static const char* namespaceName()
        {
            return type_name_of_forward_helper_<t_Ty,o_MAX_COMPILER_TEMPLATE_RECURSIVE_CYCLE>::namespaceName();
        }
        static const char*  classScopeName()
        {
            return type_name_of_forward_helper_<t_Ty,o_MAX_COMPILER_TEMPLATE_RECURSIVE_CYCLE>::classScopeName();
        }
    };

    template<typename t_Ty, int t_counter>
    struct type_name_of_helper_counter_
    {
    public:
        static const char* decoratedName()
        {
            return type_name_of_forward_helper_<t_Ty,t_counter>::decoratedName();
        }
        static const char* qualifiedDecoratedName()
        {
            return type_name_of_forward_helper_<t_Ty,t_counter>::qualifiedDecoratedName();
        }
        static const char* name()
        {
            return type_name_of_forward_helper_<t_Ty,t_counter>::name();
        }
        static const char* qualifiedName()
        {
            return type_name_of_forward_helper_<t_Ty,t_counter>::qualifiedName();
        }
        static const char* namespaceName()
        {
            return type_name_of_forward_helper_<t_Ty,o_MAX_COMPILER_TEMPLATE_RECURSIVE_CYCLE>::namespaceName();
        }
        static const char*  classScopeName()
        {
            return type_name_of_forward_helper_<t_Ty,o_MAX_COMPILER_TEMPLATE_RECURSIVE_CYCLE>::classScopeName();
        }
    };

    template<typename t_Ty, int t_counter>
    struct type_name_of_helper_counter_<t_Ty*, t_counter>
    {
    public:
        o_forceinline static phantom::string decoratedName()
        {
            return phantom::string(type_name_of_helper_counter_<t_Ty,t_counter>::decoratedName())+'*';
        }
        o_forceinline static phantom::string qualifiedDecoratedName()
        {
            return phantom::string(type_name_of_helper_counter_<t_Ty,t_counter>::qualifiedDecoratedName())+'*';
        }
        o_forceinline static phantom::string name()
        {
            return phantom::string(type_name_of_helper_counter_<t_Ty,t_counter>::name())+'*';
        }
        o_forceinline static phantom::string qualifiedName()
        {
            return phantom::string(type_name_of_helper_counter_<t_Ty,t_counter>::qualifiedName())+'*';
        }
    };

    template<typename t_Ty, int t_counter>
    struct type_name_of_helper_counter_<t_Ty&, t_counter> : public type_name_of_helper_counter_<t_Ty, t_counter>
    {
    public:
        o_forceinline static phantom::string decoratedName()
        {
            return phantom::string(type_name_of_helper_counter_<t_Ty,t_counter>::decoratedName())+'&';
        }
        o_forceinline static phantom::string qualifiedDecoratedName()
        {
            return phantom::string(type_name_of_helper_counter_<t_Ty,t_counter>::qualifiedDecoratedName())+'&';
        }
        o_forceinline static phantom::string name()
        {
            return phantom::string(type_name_of_helper_counter_<t_Ty,t_counter>::name())+'&';
        }
        o_forceinline static phantom::string qualifiedName()
        {
            return phantom::string(type_name_of_helper_counter_<t_Ty,t_counter>::qualifiedName())+'&';
        }
    };

    template<typename t_Ty, int t_counter>
    struct type_name_of_helper_counter_<t_Ty const, t_counter> : public type_name_of_helper_counter_<t_Ty, t_counter>
    {
    public:
        o_forceinline static phantom::string decoratedName()
        {
            return phantom::string(type_name_of_helper_counter_<t_Ty,t_counter>::decoratedName())+" const";
        }
        o_forceinline static phantom::string qualifiedDecoratedName()
        {
            return phantom::string(type_name_of_helper_counter_<t_Ty,t_counter>::qualifiedDecoratedName())+" const";
        }
        o_forceinline static phantom::string name()
        {
            return phantom::string(type_name_of_helper_counter_<t_Ty,t_counter>::name())+" const";
        }
        o_forceinline static phantom::string qualifiedName()
        {
            return phantom::string(type_name_of_helper_counter_<t_Ty,t_counter>::qualifiedName())+" const";
        }
    };

    template<typename t_Ty, size_t t_size, int t_counter>
    struct type_name_of_helper_counter_<t_Ty[t_size], t_counter> : public type_name_of_helper_counter_<t_Ty, t_counter>
    {
    public:
        o_forceinline static phantom::string decoratedName()
        {
            return phantom::string(type_name_of_helper_counter_<t_Ty,t_counter>::decoratedName())+'['+phantom::lexical_cast<string>(t_size)+']';
        }
        o_forceinline static phantom::string qualifiedDecoratedName()
        {
            return phantom::string(type_name_of_helper_counter_<t_Ty,t_counter>::qualifiedDecoratedName())+'['+phantom::lexical_cast<string>(t_size)+']';
        }
        o_forceinline static phantom::string name()
        {
            return phantom::string(type_name_of_helper_counter_<t_Ty,t_counter>::name())+'['+phantom::lexical_cast<string>(t_size)+']';
        }
        o_forceinline static phantom::string qualifiedName()
        {
            return phantom::string(type_name_of_helper_counter_<t_Ty,t_counter>::qualifiedName())+'['+phantom::lexical_cast<string>(t_size)+']';
        }
    };

    template<typename t_Ty, bool t_has_reflection>
    struct type_of_helper;

    template<typename t_Ty>
    struct super_adder ;

    template<typename t_Ty>
    struct type_of_
        : public type_of_helper<t_Ty, has_reflection<t_Ty>::value>
    {

    };


    template<typename t_Ty>
    struct type_of_<t_Ty*>
    {
        static phantom::reflection::DataPointerType* object()
        {
            return phantom::pointerTypeOf(type_of<t_Ty>::object());
        }
    };

    template<typename t_Ty>
    struct type_of_<t_Ty&>
    {
        static phantom::reflection::ReferenceType* object()
        {
            return phantom::referenceTypeOf(type_of<t_Ty>::object());
        }
    };

    template<typename t_Ty, size_t t_size>
    struct type_of_<t_Ty[t_size]>
    {
        static phantom::reflection::ArrayType* object()
        {
            return phantom::arrayTypeOf(type_of<t_Ty>::object(), t_size);
        }
    };

    template<typename t_Ty>
    struct type_of_<t_Ty const>
    {
        static phantom::reflection::Type* object()
        {
            return phantom::constTypeOf(type_of<t_Ty>::object());
        }
    };

    template<typename t_Ty, bool t_has_reflection_cascade>
    struct type_of_cascade_helper : public type_of<o_NESTED_TYPE super_class_of<t_Ty,0>::type>
    {

    };

    template<typename t_Ty>
    struct type_of_cascade_helper<t_Ty, false>
    {
        static o_NESTED_TYPE phantom::reflection::meta_class_type_of<t_Ty>::type* object()
        {
            return NULL; // no reflection so Type* return is NULL
        }
    };

    template<typename t_Ty, bool t_has_reflection>
    struct type_of_helper
    {
        typedef o_NESTED_TYPE phantom::reflection::meta_class_type_of<t_Ty>::type meta_type;
        static meta_type* object()
        {
            static meta_type* s_Type = NULL;
            if(s_Type == NULL)
            {
                // We check if the type hasn't been already registered through another compilation unit template instanciation
                s_Type = static_cast<meta_type*>(phantom::typeByName(qualifiedDecoratedTypeNameOf<t_Ty>()));
                if(s_Type == NULL)
                {
                    s_Type = o_new_alloc_and_construct_part(meta_type);
                    o_new_install_and_initialize_part(s_Type);
                    super_classes_adder<t_Ty>::apply(s_Type);
                    type_reflection_registrer<t_Ty>::apply(s_Type);
                    template_specialization_adder<t_Ty>::apply(s_Type);

                    phantom::detail::module_installer_template_auto_registrer<t_Ty> raii;
                    (void)raii;

                }
            }
            return s_Type;
        }
    };

    template<typename t_Ty>
    struct type_of_helper<t_Ty, false>
        : public type_of_cascade_helper<t_Ty, has_reflection_cascade<t_Ty>::value>
    {
    };

    template<typename t_Ty, int t_counter>
    struct type_of_counter_
    {
        static phantom::reflection::Type* object()
        {
            return phantom::typeByName(type_name_of_helper_counter_<t_Ty, t_counter>::qualifiedDecoratedName());
        }
    };

    template<typename t_Ty, int t_counter>
    struct type_of_counter_<t_Ty*, t_counter>
    {
        static phantom::reflection::DataPointerType* object()
        {
            return phantom::pointerTypeOf(type_of_counter_<t_Ty, t_counter>::object());
        }
    };

    template<typename t_Ty, int t_counter>
    struct type_of_counter_<t_Ty&, t_counter>
    {
        static phantom::reflection::ReferenceType* object()
        {
            return phantom::referenceTypeOf(type_of_counter_<t_Ty, t_counter>::object());
        }
    };

    template<typename t_Ty, int t_counter>
    struct type_of_counter_<t_Ty const, t_counter>
    {
        static phantom::reflection::Type* object()
        {
            return phantom::constTypeOf(type_of_counter_<t_Ty, t_counter>::object());
        }
    };

    template<typename t_Ty, size_t t_size, int t_counter>
    struct type_of_counter_<t_Ty[t_size], t_counter>
    {
        static phantom::reflection::Type* object()
        {
            return phantom::arrayTypeOf(type_of_counter_<t_Ty, t_counter>::object(),t_size);
        }
    };

    template <typename t_FuncType>
    o_forceinline void                                        appendTypeListName(string& src)
    {
        type_name_list_of_helper_<t_FuncType>::appendNameTo(src);
    }
    template <typename t_FuncType>
    o_forceinline void                                        appendTypeListQualifiedName(string& src)
    {
        type_name_list_of_helper_<t_FuncType>::appendQualifiedNameTo(src);
    }

    template <typename t_Ty>
    class type_name_of_helper_<t_Ty*>     : public type_name_of_helper_<t_Ty>
    {
    public:
        o_forceinline static phantom::string decoratedName()
        {
            return decoratedTypeNameOf<t_Ty>()+'*';
        }
        o_forceinline static phantom::string qualifiedDecoratedName()
        {
            return qualifiedDecoratedTypeNameOf<t_Ty>()+'*';
        }
        o_forceinline static phantom::string name()
        {
            return typeNameOf<t_Ty>()+'*';
        }
        o_forceinline static phantom::string qualifiedName()
        {
            return qualifiedTypeNameOf<t_Ty>()+'*';
        }
    };

    template <typename t_Ty>
    class type_name_of_helper_<t_Ty&>     : public type_name_of_helper_<t_Ty>
    {
    public:
        o_forceinline static phantom::string decoratedName()
        {
            return decoratedTypeNameOf<t_Ty>()+'&';
        }
        o_forceinline static phantom::string qualifiedDecoratedName()
        {
            return qualifiedDecoratedTypeNameOf<t_Ty>()+'&';
        }
        o_forceinline static phantom::string name()
        {
            return typeNameOf<t_Ty>()+'&';
        }
        o_forceinline static phantom::string qualifiedName()
        {
            return qualifiedTypeNameOf<t_Ty>()+'&';
        }
    };

    template <typename t_Ty>
    class type_name_of_helper_<t_Ty const>     : public type_name_of_helper_<t_Ty>
    {
    public:
        o_forceinline static phantom::string decoratedName()
        {
            return decoratedTypeNameOf<t_Ty>()+" const";
        }
        o_forceinline static phantom::string qualifiedDecoratedName()
        {
            return qualifiedDecoratedTypeNameOf<t_Ty>()+" const";
        }
        o_forceinline static phantom::string name()
        {
            return typeNameOf<t_Ty>()+" const";
        }
        o_forceinline static phantom::string qualifiedName()
        {
            return qualifiedTypeNameOf<t_Ty>()+" const";
        }
    };

    template <typename t_Ty, size_t t_size>
    class type_name_of_helper_<t_Ty[t_size]> : public type_name_of_helper_<t_Ty>
    {
    public:
        o_forceinline static phantom::string decoratedName()
        {
            return decoratedTypeNameOf<t_Ty>()+'['+phantom::lexical_cast<string>(t_size)+']';
        }
        o_forceinline static phantom::string qualifiedDecoratedName()
        {
            return qualifiedDecoratedTypeNameOf<t_Ty>()+'['+phantom::lexical_cast<string>(t_size)+']';
        }
        o_forceinline static phantom::string name()
        {
            return typeNameOf<t_Ty>()+'['+phantom::lexical_cast<string>(t_size)+']';
        }
        o_forceinline static phantom::string qualifiedName()
        {
            return qualifiedTypeNameOf<t_Ty>()+'['+phantom::lexical_cast<string>(t_size)+']';
        }
    };

    template<typename t_Ty, int t_counter>
    struct type_name_of_forward_helper_ : public type_name_of_forward_helper_<t_Ty, t_counter-1>
    {
        // IF YOU GET A RECURSIVE TEMPLATE ERROR HERE IT'S THAT
        // YOU DIDN'T DEFINE REFLECTION FOR YOUR TYPE OR YOU DIDN'T FORWARD DECLARE
        // IT USING THE :
        //                                      o_declare...
        //
        // INDEED, THESE MACRO INTERNALLY DECLARE THE TYPE NAME AND SOME PHANTOM HELPER TEMPLATE
        o_static_assert(t_counter > o_MAX_COMPILER_TEMPLATE_RECURSIVE_CYCLE - 100);
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

    template<typename t_Ty>
    struct type_name_of_forward_helper_<t_Ty,-1>
    {
    };

    template<typename t_Ty, bool t_has_reflection_cascade>
    struct meta_class_type_of_cascade_helper
        : public meta_class_type_of<o_NESTED_TYPE super_class_of<t_Ty,0>::type>
    {

    };

    template<typename t_Ty>
    struct meta_class_type_of_cascade_helper <t_Ty, false>
    {
        typedef Type type;
    };

    template<typename t_Ty, bool t_has_reflection>
    struct meta_class_type_of_helper
    {
        typedef phantom::reflection::native::TType<t_Ty> type;
    };

    template<typename t_Ty>
    struct meta_class_type_of_helper<t_Ty, false>
        : public meta_class_type_of_cascade_helper<t_Ty, has_reflection_cascade<t_Ty>::value>
    {
    };

    template<typename t_Ty>
    struct meta_class_type_of_ : public meta_class_type_of_helper<t_Ty, has_reflection<t_Ty>::value>
    {

    };

    template<typename t_Ty>
    struct meta_class_type_of_<t_Ty*>
    {
        typedef DataPointerType type;
    };

    template<typename t_Ty>
    struct meta_class_type_of_<t_Ty&>
    {
        typedef ReferenceType type;
    };

    template<typename t_Ty>
    struct meta_class_type_of_ <t_Ty const>
    {
        typedef Type type;
    };

    template<typename t_Ty, size_t t_size>
    struct meta_class_type_of_ <t_Ty[t_size]>
    {
        typedef ArrayType type;
    };
    /*template<typename t_Ty, size_t t_size0, size_t t_size1>
    struct meta_class_type_of_ <t_Ty[t_size0][t_size1]>
    {
        typedef ArrayType type;
    };
*/

    template <typename t_Ty>
    struct root_pointed_type_of_ : public type_of_<t_Ty>
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
    struct pointed_type_of_<t_Ty*> : public type_of_<t_Ty>
    {
    };


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
                    phantom::reflection::Signal* pSignal = o_new(native::TNativeSignal<t_Ty, phantom::signal_t()>) 
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

template<typename t_Ty>
struct type_of : public detail::type_of_<t_Ty> {};

template<typename t_Ty>
struct meta_class_type_of : public detail::meta_class_type_of_<t_Ty> {};


o_namespace_end(phantom, reflection)


o_namespace_begin(phantom, state, native)

template<typename t_Ty>
class root_statechart;

o_namespace_end(phantom, state, native)



o_namespace_begin(phantom, reflection, detail)


template<typename t_Ty, bool t_is_class, int t_count>
struct super_classes_adder_helper
{

};

template<typename t_Ty>
struct super_classes_adder_helper<t_Ty,true,0>
{
    o_forceinline static void apply(phantom::reflection::Class* a_pType){}
};

template<typename t_Ty>
struct super_classes_adder_helper<t_Ty,false,0>
{
    o_forceinline static void apply(phantom::reflection::Type* a_pType){}
};

template<typename t_Ty, typename t_STy>
struct super_class_adder_;

template<typename t_Ty, int t_count>
struct super_classes_adder_helper<t_Ty,true,t_count>
{
    o_forceinline static void apply(phantom::reflection::Class* a_pClass)
    {
        super_classes_adder_helper<t_Ty, true, t_count-1>::apply(a_pClass);
        super_class_adder_<t_Ty, o_NESTED_TYPE super_class_of<t_Ty, t_count-1>::type>::apply(a_pClass);
    }
};

template<typename t_Ty, typename t_STy>
struct super_class_adder_
{
    static void apply(phantom::reflection::Class* a_pClass);
};

template<typename t_Ty>
struct super_classes_adder_
    : public super_classes_adder_helper<t_Ty, boost::is_class<t_Ty>::value AND NOT(phantom::is_signal_t<t_Ty>::value), super_class_count_of<t_Ty>::value>
{

};


#define o_define_template_signature_parameter_phantom_element_impl(_type_) \
    template<_type_ value>\
    reflection::TemplateElement* \
    reflection::detail::template_signature_parameter_phantom::_type_<value>::element()\
    {\
        return o_new(phantom::reflection::native::TConstant<_type_>)("",value);\
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
        return o_new(phantom::reflection::native::TConstant<_type_>)("",value);\
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
    static phantom::reflection::TemplateElement* element()
    {
        return phantom::typeOf<t_Ty>();
    }
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
class template_signature_parameter_class
{
public:
    static phantom::reflection::TemplateElement* element()
    {
        return phantom::typeOf<t_Ty>();
    }
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

template<typename t_Ty>
struct template_specialization_adder_
{
    o_forceinline static void  apply(phantom::reflection::Type* a_pType)
    {
    }
};

template<typename t_Ty, bool t_is_class_and_has_reflection>
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

template<typename t_Ty>
struct template_specialization_of_ : public template_specialization_of_helper<t_Ty, boost::is_class<t_Ty>::value AND phantom::has_reflection<t_Ty>::value> {};

o_namespace_end(phantom, reflection, detail)


o_namespace_begin(phantom, reflection)

template<typename t_Ty>
struct template_specialization_of : public detail::template_specialization_of_<t_Ty> {};

template<typename t_Ty>
struct template_specialization_adder : public detail::template_specialization_adder_<t_Ty> {};

template<typename t_Ty>
struct super_classes_adder : public detail::super_classes_adder_<t_Ty> {};

o_namespace_end(phantom, reflection)


#define o_reflection_specialize_template_specialization_adderNTT(_namespaces_,_template_types_, _template_params_, _name_)\
    o_namespace_begin(phantom, reflection, detail) \
    template<o_PP_MIX(_template_types_,_template_params_)> \
    struct template_specialization_adder_<o_PP_CREATE_QUALIFIED_NAME(_namespaces_,_name_) < o_PP_IDENTITY _template_params_ > >\
    {\
        static void apply(phantom::reflection::ClassType* a_pClassType)\
        {\
            phantom::reflection::Template* pTemplate = a_pClassType->getNamespace()->getTemplate(a_pClassType->getName());\
            o_assert(pTemplate, "template not registered for the current instanciation");\
            phantom::reflection::TemplateSpecialization* pTemplateSpecialization = o_new(phantom::reflection::TemplateSpecialization)(pTemplate);\
            o_reflection_add_template_parameter_reflection(_template_types_,_template_params_) \
            a_pClassType->setTemplateSpecialization(pTemplateSpecialization);\
        }\
    };\
o_namespace_end(phantom, reflection, detail)

#define o_reflection_specialize_template_specialization_adderTT(_template_types_, _template_params_, _name_)\
    o_namespace_begin(phantom, reflection, detail) \
    template<o_PP_MIX(_template_types_,_template_params_)> \
    struct template_specialization_adder_< ::_name_ < o_PP_IDENTITY _template_params_ > >\
    {\
        static void apply(phantom::reflection::ClassType* a_pClassType)\
        {\
            phantom::reflection::Template* pTemplate = a_pClassType->getNamespace()->getTemplate(a_pClassType->getName());\
            o_assert(pTemplate, "template not registered for the current instanciation");\
            phantom::reflection::TemplateSpecialization* pTemplateSpecialization = o_new(phantom::reflection::TemplateSpecialization)(pTemplate);\
            o_reflection_add_template_parameter_reflection(_template_types_,_template_params_) \
            a_pClassType->setTemplateSpecialization(pTemplateSpecialization);\
        }\
    };\
    o_namespace_end(phantom, reflection, detail)

#define o_reflection_specialize_template_specialization_adderNCTT(_namespaces_,_classes_,_template_types_, _template_params_, _name_)\
    o_namespace_begin(phantom, reflection, detail) \
    template<o_PP_MIX(_template_types_,_template_params_)> \
struct template_specialization_adder_<o_PP_CREATE_QUALIFIED_NAME_2(_namespaces_,_classes_,_name_) < o_PP_IDENTITY _template_params_ > >\
{\
    static void apply(phantom::reflection::ClassType* a_pClassType)\
{\
    phantom::reflection::Template* pTemplate = a_pClassType->getNamespace()->getTemplate(a_pClassType->getName());\
    o_assert(pTemplate, "template not registered for the current instanciation");\
    phantom::reflection::TemplateSpecialization* pTemplateSpecialization = o_new(phantom::reflection::TemplateSpecialization)(pTemplate);\
    o_reflection_add_template_parameter_reflection(_template_types_,_template_params_) \
    a_pClassType->setTemplateSpecialization(pTemplateSpecialization);\
}\
};\
    o_namespace_end(phantom, reflection, detail)

#define o_reflection_specialize_template_specialization_adderCTT(_classes_,_template_types_, _template_params_, _name_)\
    o_namespace_begin(phantom, reflection, detail) \
    template<o_PP_MIX(_template_types_,_template_params_)> \
struct template_specialization_adder_<o_PP_CREATE_QUALIFIED_NAME(_classes_,_name_) < o_PP_IDENTITY _template_params_ > >\
{\
    static void apply(phantom::reflection::ClassType* a_pClassType)\
{\
    phantom::reflection::Template* pTemplate = a_pClassType->getNamespace()->getTemplate(a_pClassType->getName());\
    o_assert(pTemplate, "template not registered for the current instanciation");\
    phantom::reflection::TemplateSpecialization* pTemplateSpecialization = o_new(phantom::reflection::TemplateSpecialization)(pTemplate);\
    o_reflection_add_template_parameter_reflection(_template_types_,_template_params_) \
    a_pClassType->setTemplateSpecialization(pTemplateSpecialization);\
}\
};\
    o_namespace_end(phantom, reflection, detail)



#if o_COMPILER == o_COMPILER_VISUAL_STUDIO

#define o_reflection_add_template_parameter_reflection(l0,l1) \
    o_PP_CAT o_PP_LEFT_PAREN o_reflection_add_template_parameter_reflection_,o_PP_NARG_FUNC()l0 o_PP_RIGHT_PAREN (l0,l1)

#define o_reflection_add_template_parameter_reflection_1(l0,l1) \
    pTemplateSpecialization->add(o_PP_QUOTE(o_PP_CAT(o_PP_ARG_0,l1)), o_PP_CAT(o_root_namespace::phantom::reflection::detail::template_signature_parameter_ ,o_PP_CAT(o_PP_ARG_0,l0))< o_PP_CAT(o_PP_ARG_0,l1) >::element()); \

#define o_reflection_add_template_parameter_reflection_2(l0,l1) \
    o_reflection_add_template_parameter_reflection_1(l0,l1) \
    pTemplateSpecialization->add(o_PP_QUOTE(o_PP_CAT(o_PP_ARG_1,l1)), o_PP_CAT(o_root_namespace::phantom::reflection::detail::template_signature_parameter_,o_PP_CAT(o_PP_ARG_1,l0))< o_PP_CAT(o_PP_ARG_1,l1) >::element());

#define o_reflection_add_template_parameter_reflection_3(l0,l1) \
    o_reflection_add_template_parameter_reflection_2(l0,l1) \
    pTemplateSpecialization->add(o_PP_QUOTE(o_PP_CAT(o_PP_ARG_2,l1)), o_PP_CAT(o_root_namespace::phantom::reflection::detail::template_signature_parameter_,o_PP_CAT(o_PP_ARG_2,l0))< o_PP_CAT(o_PP_ARG_2,l1)>::element());

#define o_reflection_add_template_parameter_reflection_4(l0,l1) \
    o_reflection_add_template_parameter_reflection_3(l0,l1) \
    pTemplateSpecialization->add(o_PP_QUOTE(o_PP_CAT(o_PP_ARG_3,l1)), o_PP_CAT(o_root_namespace::phantom::reflection::detail::template_signature_parameter_,o_PP_CAT(o_PP_ARG_3,l0))< o_PP_CAT(o_PP_ARG_3,l1)>::element());

#define o_reflection_add_template_parameter_reflection_5(l0,l1) \
    o_reflection_add_template_parameter_reflection_4(l0,l1) \
    pTemplateSpecialization->add(o_PP_QUOTE(o_PP_CAT(o_PP_ARG_4,l1)), o_PP_CAT(o_root_namespace::phantom::reflection::detail::template_signature_parameter_,o_PP_CAT(o_PP_ARG_4,l0))< o_PP_CAT(o_PP_ARG_4,l1)>::element());

#define o_reflection_add_template_parameter_reflection_6(l0,l1) \
    o_reflection_add_template_parameter_reflection_5(l0,l1) \
    pTemplateSpecialization->add(o_PP_QUOTE(o_PP_CAT(o_PP_ARG_5,l1)), o_PP_CAT(o_root_namespace::phantom::reflection::detail::template_signature_parameter_,o_PP_CAT(o_PP_ARG_5,l0))< o_PP_CAT(o_PP_ARG_5,l1) >::element());

#define o_reflection_add_template_parameter_reflection_7(l0,l1) \
    o_reflection_add_template_parameter_reflection_6(l0,l1) \
    pTemplateSpecialization->add(o_PP_QUOTE(o_PP_CAT(o_PP_ARG_6,l1)), o_PP_CAT(o_root_namespace::phantom::reflection::detail::template_signature_parameter_,o_PP_CAT(o_PP_ARG_6,l0))< o_PP_CAT(o_PP_ARG_6,l1) >::element());

#define o_reflection_add_template_parameter_reflection_8(l0,l1) \
    o_reflection_add_template_parameter_reflection_7(l0,l1) \
    pTemplateSpecialization->add(o_PP_QUOTE(o_PP_CAT(o_PP_ARG_7,l1)), o_PP_CAT(o_root_namespace::phantom::reflection::detail::template_signature_parameter_,o_PP_CAT(o_PP_ARG_7,l0))< o_PP_CAT(o_PP_ARG_7,l1) >::element());

#define o_reflection_add_template_parameter_reflection_9(l0,l1) \
    o_reflection_add_template_parameter_reflection_8(l0,l1) \
    pTemplateSpecialization->add(o_PP_QUOTE(o_PP_CAT(o_PP_ARG_8,l1)), o_PP_CAT(o_root_namespace::phantom::reflection::detail::template_signature_parameter_,o_PP_CAT(o_PP_ARG_8,l0))< o_PP_CAT(o_PP_ARG_8,l1) >::element());

#define o_reflection_add_template_parameter_reflection_10(l0,l1) \
    o_reflection_add_template_parameter_reflection_9(l0,l1) \
    pTemplateSpecialization->add(o_PP_QUOTE(o_PP_CAT(o_PP_ARG_9,l1)), o_PP_CAT(o_root_namespace::phantom::reflection::detail::template_signature_parameter_,o_PP_CAT(o_PP_ARG_9,l0))< o_PP_CAT(o_PP_ARG_9,l1) >::element());

#define o_reflection_create_template_parameters_list_string_N(l0,l1,_func_name_) \
        o_PP_CAT o_PP_LEFT_PAREN o_reflection_create_template_parameters_list_string_,o_PP_NARG_FUNC()l0 o_PP_RIGHT_PAREN (l0,l1,_func_name_)

#define o_reflection_create_template_parameters_list_string_1(l0,l1,_func_name_) \
    o_PP_CAT(o_root_namespace::phantom::reflection::detail::template_signature_parameter_ ,o_PP_CAT(o_PP_ARG_0,l0))< o_PP_CAT(o_PP_ARG_0,l1) >::_func_name_() \

#define o_reflection_create_template_parameters_list_string_2(l0,l1,_func_name_) \
    o_reflection_create_template_parameters_list_string_1(l0,l1,_func_name_) + ',' +\
    o_PP_CAT(o_root_namespace::phantom::reflection::detail::template_signature_parameter_ ,o_PP_CAT(o_PP_ARG_1,l0))< o_PP_CAT(o_PP_ARG_1,l1) >::_func_name_() \

#define o_reflection_create_template_parameters_list_string_3(l0,l1,_func_name_) \
    o_reflection_create_template_parameters_list_string_2(l0,l1,_func_name_) + ',' + \
    o_PP_CAT(o_root_namespace::phantom::reflection::detail::template_signature_parameter_ ,o_PP_CAT(o_PP_ARG_2,l0))< o_PP_CAT(o_PP_ARG_2,l1) >::_func_name_() \

#define o_reflection_create_template_parameters_list_string_4(l0,l1,_func_name_) \
    o_reflection_create_template_parameters_list_string_3(l0,l1,_func_name_) + ',' +\
    o_PP_CAT(o_root_namespace::phantom::reflection::detail::template_signature_parameter_ ,o_PP_CAT(o_PP_ARG_3,l0))< o_PP_CAT(o_PP_ARG_3,l1) >::_func_name_() \

#define o_reflection_create_template_parameters_list_string_5(l0,l1,_func_name_) \
    o_reflection_create_template_parameters_list_string_4(l0,l1,_func_name_) + ',' +\
    o_PP_CAT(o_root_namespace::phantom::reflection::detail::template_signature_parameter_ ,o_PP_CAT(o_PP_ARG_4,l0))< o_PP_CAT(o_PP_ARG_4,l1) >::_func_name_() \

#define o_reflection_create_template_parameters_list_string_6(l0,l1,_func_name_) \
    o_reflection_create_template_parameters_list_string_5(l0,l1,_func_name_) + ',' +\
    o_PP_CAT(o_root_namespace::phantom::reflection::detail::template_signature_parameter_ ,o_PP_CAT(o_PP_ARG_5,l0))< o_PP_CAT(o_PP_ARG_5,l1) >::_func_name_() \

#define o_reflection_create_template_parameters_list_string_7(l0,l1,_func_name_) \
    o_reflection_create_template_parameters_list_string_6(l0,l1,_func_name_) + ',' +\
    o_PP_CAT(o_root_namespace::phantom::reflection::detail::template_signature_parameter_ ,o_PP_CAT(o_PP_ARG_6,l0))< o_PP_CAT(o_PP_ARG_6,l1) >::_func_name_() \

#define o_reflection_create_template_parameters_list_string_8(l0,l1,_func_name_) \
    o_reflection_create_template_parameters_list_string_7(l0,l1,_func_name_) + ',' +\
    o_PP_CAT(o_root_namespace::phantom::reflection::detail::template_signature_parameter_ ,o_PP_CAT(o_PP_ARG_7,l0))< o_PP_CAT(o_PP_ARG_7,l1) >::_func_name_() \

#define o_reflection_create_template_parameters_list_string_9(l0,l1,_func_name_) \
    o_reflection_create_template_parameters_list_string_8(l0,l1,_func_name_) + ',' +\
    o_PP_CAT(o_root_namespace::phantom::reflection::detail::template_signature_parameter_ ,o_PP_CAT(o_PP_ARG_8,l0))< o_PP_CAT(o_PP_ARG_8,l1) >::_func_name_() \

#define o_reflection_create_template_parameters_list_string_10(l0,l1,_func_name_) \
    o_reflection_create_template_parameters_list_string_9(l0,l1,_func_name_) + ',' +\
    o_PP_CAT(o_root_namespace::phantom::reflection::detail::template_signature_parameter_ ,o_PP_CAT(o_PP_ARG_9,l0))< o_PP_CAT(o_PP_ARG_9,l1) >::_func_name_() \


#else // NOT VISUAL STUDIO


#define o_reflection_add_template_parameter_reflection(l0,l1) \
    o_PP_CAT( o_reflection_add_template_parameter_reflection_,o_PP_NARG_FUNC()l0 ) (l0,l1)

#define o_reflection_add_template_parameter_reflection_1(l0,l1) \
    pTemplateSpecialization->add(o_PP_QUOTE(o_PP_ARG_0 l1), o_PP_CAT(o_root_namespace::phantom::reflection::detail::template_signature_parameter_,o_PP_ARG_0 l0)< o_PP_ARG_0 l1 >::element()); \

#define o_reflection_add_template_parameter_reflection_2(l0,l1) \
    o_reflection_add_template_parameter_reflection_1(l0,l1) \
    pTemplateSpecialization->add(o_PP_QUOTE(o_PP_ARG_1 l1), o_PP_CAT(o_root_namespace::phantom::reflection::detail::template_signature_parameter_,o_PP_ARG_1 l0)< o_PP_ARG_1 l1 >::element());

#define o_reflection_add_template_parameter_reflection_3(l0,l1) \
    o_reflection_add_template_parameter_reflection_2(l0,l1) \
    pTemplateSpecialization->add(o_PP_QUOTE(o_PP_ARG_2 l1), o_PP_CAT(o_root_namespace::phantom::reflection::detail::template_signature_parameter_,o_PP_ARG_2 l0)< o_PP_ARG_2 l1>::element());

#define o_reflection_add_template_parameter_reflection_4(l0,l1) \
    o_reflection_add_template_parameter_reflection_3(l0,l1) \
    pTemplateSpecialization->add(o_PP_QUOTE(o_PP_ARG_3 l1), o_PP_CAT(o_root_namespace::phantom::reflection::detail::template_signature_parameter_,o_PP_ARG_3 l0)< o_PP_ARG_3 l1>::element());

#define o_reflection_add_template_parameter_reflection_5(l0,l1) \
    o_reflection_add_template_parameter_reflection_4(l0,l1) \
    pTemplateSpecialization->add(o_PP_QUOTE(o_PP_ARG_4 l1), o_PP_CAT(o_root_namespace::phantom::reflection::detail::template_signature_parameter_,o_PP_ARG_4 l0)< o_PP_ARG_4 l1>::element());

#define o_reflection_add_template_parameter_reflection_6(l0,l1) \
    o_reflection_add_template_parameter_reflection_5(l0,l1) \
    pTemplateSpecialization->add(o_PP_QUOTE(o_PP_ARG_5 l1), o_PP_CAT(o_root_namespace::phantom::reflection::detail::template_signature_parameter_,o_PP_ARG_5 l0)< o_PP_ARG_5 l1 >::element());

#define o_reflection_add_template_parameter_reflection_7(l0,l1) \
    o_reflection_add_template_parameter_reflection_6(l0,l1) \
    pTemplateSpecialization->add(o_PP_QUOTE(o_PP_ARG_6 l1), o_PP_CAT(o_root_namespace::phantom::reflection::detail::template_signature_parameter_,o_PP_ARG_6 l0)< o_PP_ARG_6 l1 >::element());

#define o_reflection_add_template_parameter_reflection_8(l0,l1) \
    o_reflection_add_template_parameter_reflection_7(l0,l1) \
    pTemplateSpecialization->add(o_PP_QUOTE(o_PP_ARG_7 l1), o_PP_CAT(o_root_namespace::phantom::reflection::detail::template_signature_parameter_,o_PP_ARG_7 l0)< o_PP_ARG_7 l1 >::element());

#define o_reflection_add_template_parameter_reflection_9(l0,l1) \
    o_reflection_add_template_parameter_reflection_8(l0,l1) \
    pTemplateSpecialization->add(o_PP_QUOTE(o_PP_ARG_8 l1), o_PP_CAT(o_root_namespace::phantom::reflection::detail::template_signature_parameter_,o_PP_ARG_8 l0)< o_PP_ARG_8 l1 >::element());

#define o_reflection_add_template_parameter_reflection_10(l0,l1) \
    o_reflection_add_template_parameter_reflection_9(l0,l1) \
    pTemplateSpecialization->add(o_PP_QUOTE(o_PP_ARG_9 l1), o_PP_CAT(o_root_namespace::phantom::reflection::detail::template_signature_parameter_,o_PP_ARG_9 l0)< o_PP_ARG_9 l1 >::element());


#define o_reflection_create_template_parameters_list_string_N(l0,l1,_func_name_) \
    o_PP_CAT( o_reflection_create_template_parameters_list_string_, o_PP_NARG l0 ) (l0,l1,_func_name_)

#define o_reflection_create_template_parameters_list_string_1(l0,l1,_func_name_) \
    o_PP_CAT(o_root_namespace::phantom::reflection::detail::template_signature_parameter_ ,o_PP_ARG_0 l0)< o_PP_ARG_0 l1 >::_func_name_() \

#define o_reflection_create_template_parameters_list_string_2(l0,l1,_func_name_) \
    o_reflection_create_template_parameters_list_string_1(l0,l1,_func_name_) + ',' +\
    o_PP_CAT(o_root_namespace::phantom::reflection::detail::template_signature_parameter_ ,o_PP_ARG_1 l0)< o_PP_ARG_1 l1 >::_func_name_() \

#define o_reflection_create_template_parameters_list_string_3(l0,l1,_func_name_) \
    o_reflection_create_template_parameters_list_string_2(l0,l1,_func_name_) + ',' + \
    o_PP_CAT(o_root_namespace::phantom::reflection::detail::template_signature_parameter_ ,o_PP_ARG_2 l0)< o_PP_ARG_2 l1 >::_func_name_() \

#define o_reflection_create_template_parameters_list_string_4(l0,l1,_func_name_) \
    o_reflection_create_template_parameters_list_string_3(l0,l1,_func_name_) + ',' +\
    o_PP_CAT(o_root_namespace::phantom::reflection::detail::template_signature_parameter_ ,o_PP_ARG_3 l0)< o_PP_ARG_3 l1 >::_func_name_() \

#define o_reflection_create_template_parameters_list_string_5(l0,l1,_func_name_) \
    o_reflection_create_template_parameters_list_string_4(l0,l1,_func_name_) + ',' +\
    o_PP_CAT(o_root_namespace::phantom::reflection::detail::template_signature_parameter_ ,o_PP_ARG_4 l0)< o_PP_ARG_4 l1 >::_func_name_() \

#define o_reflection_create_template_parameters_list_string_6(l0,l1,_func_name_) \
    o_reflection_create_template_parameters_list_string_5(l0,l1,_func_name_) + ',' +\
    o_PP_CAT(o_root_namespace::phantom::reflection::detail::template_signature_parameter_ ,o_PP_ARG_5 l0)< o_PP_ARG_5 l1 >::_func_name_() \

#define o_reflection_create_template_parameters_list_string_7(l0,l1,_func_name_) \
    o_reflection_create_template_parameters_list_string_6(l0,l1,_func_name_) + ',' +\
    o_PP_CAT(o_root_namespace::phantom::reflection::detail::template_signature_parameter_ ,o_PP_ARG_6 l0)< o_PP_ARG_6 l1 >::_func_name_() \

#define o_reflection_create_template_parameters_list_string_8(l0,l1,_func_name_) \
    o_reflection_create_template_parameters_list_string_7(l0,l1,_func_name_) + ',' +\
    o_PP_CAT(o_root_namespace::phantom::reflection::detail::template_signature_parameter_ ,o_PP_ARG_7 l0)< o_PP_ARG_7 l1 >::_func_name_() \

#define o_reflection_create_template_parameters_list_string_9(l0,l1,_func_name_) \
    o_reflection_create_template_parameters_list_string_8(l0,l1,_func_name_) + ',' +\
    o_PP_CAT(o_root_namespace::phantom::reflection::detail::template_signature_parameter_ ,o_PP_ARG_8 l0)< o_PP_ARG_8 l1 >::_func_name_() \

#define o_reflection_create_template_parameters_list_string_10(l0,l1,_func_name_) \
    o_reflection_create_template_parameters_list_string_9(l0,l1,_func_name_) + ',' +\
    o_PP_CAT(o_root_namespace::phantom::reflection::detail::template_signature_parameter_ ,o_PP_ARG_9 l0)< o_PP_ARG_9 l1 >::_func_name_() \

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

#define o_reflection_specialize_type_name_of_helperN(_namespaces_, _name_)    \
    o_namespace_begin(phantom, reflection, detail)                                            \
    template<>                                                                               \
    class type_name_of_helper_<o_PP_CREATE_QUALIFIED_NAME(_namespaces_,_name_)>     \
    {                                                                            \
        public:                                                                     \
        o_reflection_specialize_type_name_static_member_functionsN(_namespaces_, _name_)\
    };                                                                                                                         \
     o_namespace_end(phantom, reflection, detail)



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

#define o_reflection_specialize_type_name_static_member_functionsNTT(_namespaces_, _template_types_, _template_params_, _name_) \
    static const char* name() { return o_PP_QUOTE(_name_); } \
    static const phantom::string&    decoratedName() \
        { \
        static phantom::string n;\
        if(n.empty())\
            {\
            n = o_PP_QUOTE(_name_)"<";\
            n += o_reflection_create_template_parameters_list_string_N(_template_types_,_template_params_,decoratedName); \
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
            n += o_reflection_create_template_parameters_list_string_N(_template_types_,_template_params_,qualifiedDecoratedName); \
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

#define o_reflection_specialize_type_name_static_member_functionsTT(_template_types_, _template_params_, _name_) \
    static const char* name() { return o_PP_QUOTE(_name_); } \
    static const phantom::string&    decoratedName() \
        { \
        static phantom::string n;\
        if(n.empty())\
            {\
            n = o_PP_QUOTE(_name_)"<";\
            n += o_reflection_create_template_parameters_list_string_N(_template_types_,_template_params_,decoratedName); \
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
            n += o_reflection_create_template_parameters_list_string_N(_template_types_,_template_params_,qualifiedDecoratedName); \
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

#define o_reflection_specialize_type_name_static_member_functionsNCTT(_namespaces_, _classes_, _template_types_, _template_params_, _name_) \
    static const char* name() { return o_PP_QUOTE(_name_); } \
    static const phantom::string&    decoratedName() \
        { \
        static phantom::string n;\
        if(n.empty())\
            {\
            n = o_PP_QUOTE(_name_)"<";\
            n += o_reflection_create_template_parameters_list_string_N(_template_types_,_template_params_,decoratedName); \
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
            n += o_reflection_create_template_parameters_list_string_N(_template_types_,_template_params_,qualifiedDecoratedName); \
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

#define o_reflection_specialize_type_name_static_member_functionsCTT(_classes_, _template_types_, _template_params_, _name_) \
    static const char* name() { return o_PP_QUOTE(_name_); } \
    static const phantom::string&    decoratedName() \
        { \
        static phantom::string n;\
        if(n.empty())\
            {\
            n = o_PP_QUOTE(_name_)"<";\
            n += o_reflection_create_template_parameters_list_string_N(_template_types_,_template_params_,decoratedName); \
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
            n += o_reflection_create_template_parameters_list_string_N(_template_types_,_template_params_,qualifiedDecoratedName); \
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

#define o_reflection_specialize_type_name_of_helper(_name_)    \
    o_namespace_begin(phantom, reflection, detail)            \
    template<>                                               \
    class type_name_of_helper_< ::_name_>     \
    {                                                        \
    public:   \
    o_reflection_specialize_type_name_static_member_functions(_name_)\
    };                                                         \
    o_namespace_end(phantom, reflection, detail)

#define o_reflection_specialize_type_name_of_helperC(_classes_,_name_) \
    o_namespace_begin(phantom, reflection, detail)            \
    template<>                                               \
class type_name_of_helper_<o_PP_CREATE_QUALIFIED_NAME(_classes_,_name_)>     \
    {                                                        \
    public:   \
    o_reflection_specialize_type_name_static_member_functionsC(_classes_,_name_)\
    };                                                         \
    o_namespace_end(phantom, reflection, detail)

#define o_reflection_specialize_type_name_of_helperNC(_namespaces_,_classes_,_name_) \
    o_namespace_begin(phantom, reflection, detail)            \
    template<>                                               \
class type_name_of_helper_<o_PP_CREATE_QUALIFIED_NAME_2(_namespaces_,_classes_,_name_)>     \
    {                                                        \
    public:   \
    o_reflection_specialize_type_name_static_member_functionsNC(_namespaces_,_classes_,_name_)\
    };                                                         \
    o_namespace_end(phantom, reflection, detail)

#define o_reflection_specialize_type_name_of_helperNCTT(_namespaces_,_classes_,_template_types_,_template_names_,_name_) \
    o_namespace_begin(phantom, reflection, detail)            \
    template<>                                               \
class type_name_of_helper_<o_PP_CREATE_QUALIFIED_NAME_2(_namespaces_,_classes_,_name_)< o_PP_IDENTITY _template_params_ > >     \
    {                                                        \
    public:   \
    o_reflection_specialize_type_name_static_member_functionsNCTT(_namespaces_,_classes_,_template_types_,_template_names_,_name_)\
    };                                                         \
    o_namespace_end(phantom, reflection, detail)

#define o_reflection_specialize_type_name_of_helperCTT(_classes_,_template_types_,_template_names_,_name_) \
    o_namespace_begin(phantom, reflection, detail)            \
    template<>                                               \
class type_name_of_helper_<o_PP_CREATE_QUALIFIED_NAME(_classes_,_name_)< o_PP_IDENTITY _template_params_ > >     \
    {                                                        \
    public:   \
    o_reflection_specialize_type_name_static_member_functionsCTT(_classes_,_template_types_,_template_names_,_name_)\
    };                                                         \
    o_namespace_end(phantom, reflection, detail)

#define o_reflection_specialize_type_name_of_helperNTT(_namespaces_, _template_types_, _template_params_, _name_) \
    o_namespace_begin(phantom, reflection, detail) \
    template<o_PP_MIX(_template_types_, _template_params_)> \
class type_name_of_helper_<o_PP_CREATE_QUALIFIED_NAME(_namespaces_,_name_)< o_PP_IDENTITY _template_params_ > > \
    { \
    public: \
    o_reflection_specialize_type_name_static_member_functionsNTT(_namespaces_, _template_types_, _template_params_, _name_) \
    };\
    o_namespace_end(phantom, reflection, detail)

#define o_reflection_specialize_type_name_of_helperTT(_template_types_, _template_params_, _name_) \
    o_namespace_begin(phantom, reflection, detail) \
    template<o_PP_MIX(_template_types_, _template_params_)> \
class type_name_of_helper_< ::_name_< o_PP_IDENTITY _template_params_ > > \
    { \
    public: \
    o_reflection_specialize_type_name_static_member_functionsTT(_template_types_, _template_params_, _name_) \
    };\
    o_namespace_end(phantom, reflection, detail)

#define o_reflection_specialize_type_name_of_forward_helper(_name_)    \
    o_namespace_begin(phantom, reflection, detail)            \
    template<>                                               \
class type_name_of_forward_helper_< ::_name_,__COUNTER__>     \
    {                                                        \
    public:   \
    o_reflection_specialize_type_name_static_member_functions(_name_)\
    };                                                         \
    o_namespace_end(phantom, reflection, detail)

#define o_reflection_specialize_type_name_of_forward_helperN(_namespaces_, _name_)    \
    o_namespace_begin(phantom, reflection, detail)                                            \
    template<>                                                                               \
class type_name_of_forward_helper_<o_PP_CREATE_QUALIFIED_NAME(_namespaces_,_name_),__COUNTER__>     \
    {                                                                            \
    public:                                                          \
    o_reflection_specialize_type_name_static_member_functionsN(_namespaces_, _name_)\
    };                                                                         \
    o_namespace_end(phantom, reflection, detail)

#define o_reflection_specialize_type_name_of_forward_helperC(_classes_, _name_)    \
    o_namespace_begin(phantom, reflection, detail)                                            \
    template<>                                                                               \
class type_name_of_forward_helper_<o_PP_CREATE_QUALIFIED_NAME(_classes_,_name_),__COUNTER__>     \
    {                                                                            \
    public:                                                          \
    o_reflection_specialize_type_name_static_member_functionsC(_classes_, _name_)\
    };                                                                         \
    o_namespace_end(phantom, reflection, detail)

#define o_reflection_specialize_type_name_of_forward_helperNC(_namespaces_, _classes_, _name_)    \
    o_namespace_begin(phantom, reflection, detail)                                            \
    template<>                                                                               \
class type_name_of_forward_helper_<o_PP_CREATE_QUALIFIED_NAME_2(_namespaces_,_classes_, _name_),__COUNTER__>     \
    {                                                                            \
    public:                                                          \
    o_reflection_specialize_type_name_static_member_functionsNC(_namespaces_, _classes_, _name_)\
    };                                                                         \
    o_namespace_end(phantom, reflection, detail)

#define o_reflection_specialize_type_name_of_forward_helperNTT(_namespaces_, _template_types_, _template_params_, _name_) \
    o_namespace_begin(phantom, reflection, detail) \
    template<o_PP_MIX(_template_types_, _template_params_)> \
class type_name_of_forward_helper_<o_PP_CREATE_QUALIFIED_NAME(_namespaces_,_name_)< o_PP_IDENTITY _template_params_ >, __COUNTER__> \
    { \
    public: \
    o_reflection_specialize_type_name_static_member_functionsNTT(_namespaces_, _template_types_, _template_params_, _name_) \
    };\
    o_namespace_end(phantom, reflection, detail)

#define o_reflection_specialize_type_name_of_forward_helperCTT(_classes_, _template_types_, _template_params_, _name_) \
    o_namespace_begin(phantom, reflection, detail) \
    template<o_PP_MIX(_template_types_, _template_params_)> \
class type_name_of_forward_helper_<o_PP_CREATE_QUALIFIED_NAME(_classes_,_name_)< o_PP_IDENTITY _template_params_ >, __COUNTER__> \
    { \
    public: \
    o_reflection_specialize_type_name_static_member_functionsCTT(_classes_, _template_types_, _template_params_, _name_) \
    };\
    o_namespace_end(phantom, reflection, detail)

#define o_reflection_specialize_type_name_of_forward_helperNCTT(_namespaces_, _classes_, _template_types_, _template_params_, _name_) \
    o_namespace_begin(phantom, reflection, detail) \
    template<o_PP_MIX(_template_types_, _template_params_)> \
    class type_name_of_forward_helper_<o_PP_CREATE_QUALIFIED_NAME_2(_namespaces_,_classes_, _name_)< o_PP_IDENTITY _template_params_ >, __COUNTER__> \
    { \
    public: \
    o_reflection_specialize_type_name_static_member_functionsNCTT(_namespaces_, _classes_, _template_types_, _template_params_, _name_) \
    };\
    o_namespace_end(phantom, reflection, detail)


#define o_reflection_specialize_type_name_of_forward_helperTT(_template_types_, _template_params_, _name_) \
    o_namespace_begin(phantom, reflection, detail) \
    template<o_PP_MIX(_template_types_, _template_params_)> \
    class type_name_of_forward_helper_< ::_name_< o_PP_IDENTITY _template_params_ >,__COUNTER__> \
    { \
    public: \
    o_reflection_specialize_type_name_static_member_functionsTT(_template_types_, _template_params_, _name_) \
    };\
    o_namespace_end(phantom, reflection, detail)






#define o_reflection_specialize_type_of_counterNTT(_namespaces_, _template_types_, _template_params_, _name_) \
    o_namespace_begin(phantom, reflection, detail) \
    template<o_PP_MIX(_template_types_, _template_params_), int t_RESERVED_counter>  \
struct type_of_counter_<o_PP_CREATE_QUALIFIED_NAME(_namespaces_,_name_) < o_PP_IDENTITY _template_params_ >, t_RESERVED_counter> \
: public type_of<o_PP_CREATE_QUALIFIED_NAME(_namespaces_,_name_)< o_PP_IDENTITY _template_params_ > > {};\
    o_namespace_end(phantom, reflection, detail)

#define o_reflection_specialize_type_of_counterN(_namespaces_, _name_) \
    o_namespace_begin(phantom, reflection, detail) \
    template<int t_RESERVED_counter>  \
struct type_of_counter_<o_PP_CREATE_QUALIFIED_NAME(_namespaces_,_name_), t_RESERVED_counter> \
    : public type_of<o_PP_CREATE_QUALIFIED_NAME(_namespaces_,_name_)> {};\
    o_namespace_end(phantom, reflection, detail)

#define o_reflection_specialize_type_of_counter(_name_) \
    o_namespace_begin(phantom, reflection, detail) \
    template<int t_RESERVED_counter>  \
struct type_of_counter_<_name_, t_RESERVED_counter> \
    : public type_of< ::_name_> {};\
    o_namespace_end(phantom, reflection, detail)

#define o_reflection_specialize_type_of_counterTT(_template_types_, _template_params_, _name_) \
o_namespace_begin(phantom, reflection, detail) \
    template<o_PP_MIX(_template_types_, _template_params_), int t_RESERVED_counter>  \
    struct type_of_counter_< ::_name_< o_PP_IDENTITY _template_params_ >, t_RESERVED_counter> \
        : public type_of< ::_name_< o_PP_IDENTITY _template_params_ > > {};\
    o_namespace_end(phantom, reflection, detail)

#define o_reflection_specialize_type_of_counterNCTT(_namespaces_, _classes_, _template_types_, _template_params_, _name_) \
    o_namespace_begin(phantom, reflection, detail) \
    template<o_PP_MIX(_template_types_, _template_params_), int t_RESERVED_counter>  \
struct type_of_counter_<o_PP_CREATE_QUALIFIED_NAME_2(_namespaces_, _classes_,_name_) < o_PP_IDENTITY _template_params_ >, t_RESERVED_counter> \
    : public type_of<o_PP_CREATE_QUALIFIED_NAME_2(_namespaces_, _classes_,_name_)< o_PP_IDENTITY _template_params_ > > {};\
    o_namespace_end(phantom, reflection, detail)

#define o_reflection_specialize_type_of_counterNC(_namespaces_, _classes_, _name_) \
    o_namespace_begin(phantom, reflection, detail) \
    template<int t_RESERVED_counter>  \
struct type_of_counter_<o_PP_CREATE_QUALIFIED_NAME_2(_namespaces_,_classes_, _name_), t_RESERVED_counter> \
    : public type_of<o_PP_CREATE_QUALIFIED_NAME_2(_namespaces_, _classes_,_name_)> {};\
    o_namespace_end(phantom, reflection, detail)

#define o_reflection_specialize_type_of_counterC(_classes_, _name_) \
    o_namespace_begin(phantom, reflection, detail) \
    template<int t_RESERVED_counter>  \
struct type_of_counter_<o_PP_CREATE_QUALIFIED_NAME(_classes_,_name_), t_RESERVED_counter> \
    : public type_of<o_PP_CREATE_QUALIFIED_NAME(_classes_,_name_)> {};\
    o_namespace_end(phantom, reflection, detail)

#define o_reflection_specialize_type_of_counterCTT(_classes_, _template_types_, _template_params_, _name_) \
    o_namespace_begin(phantom, reflection, detail) \
    template<o_PP_MIX(_template_types_, _template_params_), int t_RESERVED_counter>  \
struct type_of_counter_<o_PP_CREATE_QUALIFIED_NAME(_classes_,_name_)< o_PP_IDENTITY _template_params_ >, t_RESERVED_counter> \
    : public type_of<o_PP_CREATE_QUALIFIED_NAME(_classes_,_name_)< o_PP_IDENTITY _template_params_ > > {};\
    o_namespace_end(phantom, reflection, detail)




#define o_reflection_in_cpp_deferred_setupN(_namespaces_,_name)\
    o_reflection_specialize_type_of_counterN(_namespaces_,_name)

#define o_class_declare(_name_) \
    o_declare o_PP_LEFT_PAREN class, _name_ o_PP_RIGHT_PAREN

#define o_class_declareN(_namespaces_, _name_) \
    o_declare o_PP_LEFT_PAREN class, o_PP_IDENTITY _namespaces_, _name_ o_PP_RIGHT_PAREN

#if o__bool__enable_dynamic_reflection_declaration
#   include "def_reflection_dynamic.h"
#else
#   include "def_reflection_static.h"
#endif

#if o_COMPILER == o_COMPILER_VISUAL_STUDIO
#   define o_data_member(...) o_PP_CAT(o_PP_CAT(o_data_member_,o_PP_NARG(__VA_ARGS__)),(__VA_ARGS__))
#   define o_property(...) o_PP_CAT(o_PP_CAT(o_property_,o_PP_NARG(__VA_ARGS__)),(__VA_ARGS__))
#   define o_collection(...) o_PP_CAT(o_PP_CAT(o_collection_,o_PP_NARG(__VA_ARGS__)),(__VA_ARGS__))
#   define o_range(...) o_PP_CAT(o_PP_CAT(o_range_,o_PP_NARG(__VA_ARGS__)),(__VA_ARGS__))
#else
#   define o_data_member(...) o_PP_CAT(o_data_member_,o_PP_NARG(__VA_ARGS__)) (__VA_ARGS__)
#   define o_property(...) o_PP_CAT(o_property_,o_PP_NARG(__VA_ARGS__)) (__VA_ARGS__)
#   define o_collection(...) o_PP_CAT(o_collection_,o_PP_NARG(__VA_ARGS__)) (__VA_ARGS__)
#   define o_range(...) o_PP_CAT(o_range_,o_PP_NARG(__VA_ARGS__)) (__VA_ARGS__)
#endif


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
    o_data_member_5(_type_, _name_, _range_, _modifiers_, 0xffffffff)

#define o_property_4(_type_, _name_, _set_member_function_, _get_member_function_)\
    o_property_8(_type_, _name_, _set_member_function_, _get_member_function_, m_PHANTOM_RESERVED_no_signal, (phantom::reflection::native::null_range), 0, 0xffffffff)

#define o_property_5(_type_, _name_, _set_member_function_, _get_member_function_, _signal_)\
    o_property_8(_type_, _name_, _set_member_function_, _get_member_function_, _signal_, (phantom::reflection::native::null_range), 0, 0xffffffff)

#define o_property_6(_type_, _name_, _set_member_function_, _get_member_function_, _signal_, _range_)\
    o_property_8(_type_, _name_, _set_member_function_, _get_member_function_, _signal_, _range_, 0, 0xffffffff)

#define o_property_7(_type_, _name_, _set_member_function_, _get_member_function_, _signal_, _range_, _modifiers_)\
    o_property_8(_type_, _name_, _set_member_function_, _get_member_function_, _signal_, _range_, _modifiers_, 0xffffffff)

#define o_collection_8(_type_, _name_, _add_member_function_, _remove_member_function_, _move_member_function_, _set_member_function_, _get_member_function_, _size_member_function_)\
    o_collection_9(_type_, _name_, _add_member_function_, _remove_member_function_, _move_member_function_, _set_member_function_, _get_member_function_, _size_member_function_, 0)

#define o_traits_specialize_all_super_traitNTTS_TNativeMemberFunctionXXX(_native_member_function_) \
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
    o_traits_specialize_all_super_traitNTTS(                                                                                                                                              \
    (phantom,reflection,native)                                                                                                                                                           \
    , (typename)                                                                                                                                                                          \
    , (t_Ty)                                                                                                                                                                              \
    , _native_member_function_##0                                                                                                                                                                  \
    , (_native_member_function_##Base<t_Ty>)                                                                                                                                                       \
    )                                                                                                                                                                                     \
    o_traits_specialize_all_super_traitNTTS(                                                                                                                                              \
    (phantom,reflection,native)                                                                                                                                                           \
    , (typename,typename)                                                                                                                                                                 \
    , (t_Ty, t_Param0)                                                                                                                                                                    \
    , _native_member_function_##1                                                                                                                                                                  \
    , (_native_member_function_##Base<t_Ty>)                                                                                                                                                       \
    )                                                                                                                                                                                     \
    o_traits_specialize_all_super_traitNTTS(                                                                                                                                              \
    (phantom,reflection,native)                                                                                                                                                           \
    , (typename,typename,typename)                                                                                                                                                        \
    , (t_Ty, t_Param0,t_Param1)                                                                                                                                                           \
    , _native_member_function_##2                                                                                                                                                                  \
    , (_native_member_function_##Base<t_Ty>)                                                                                                                                                       \
    )                                                                                                                                                                                     \
    o_traits_specialize_all_super_traitNTTS(                                                                                                                                              \
    (phantom,reflection,native)                                                                                                                                                           \
    , (typename,typename,typename,typename)                                                                                                                                               \
    , (t_Ty, t_Param0,t_Param1,t_Param2)                                                                                                                                                  \
    , _native_member_function_##3                                                                                                                                                                  \
    , (_native_member_function_##Base<t_Ty>)                                                                                                                                                       \
    )                                                                                                                                                                                     \
    o_traits_specialize_all_super_traitNTTS(                                                                                                                                              \
    (phantom,reflection,native)                                                                                                                                                           \
    , (typename,typename,typename,typename,typename)                                                                                                                                      \
    , (t_Ty, t_Param0, t_Param1, t_Param2, t_Param3)                                                                                                                                      \
    , _native_member_function_##4                                                                                                                                                                  \
    , (_native_member_function_##Base<t_Ty>)                                                                                                                                                       \
    )                                                                                                                                                                                     \
    o_traits_specialize_all_super_traitNTTS(                                                                                                                                              \
    (phantom,reflection,native)                                                                                                                                                           \
    , (typename,typename,typename,typename,typename,typename)                                                                                                                             \
    , (t_Ty, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4)                                                                                                                            \
    , _native_member_function_##5                                                                                                                                                                  \
    , (_native_member_function_##Base<t_Ty>)                                                                                                                                                       \
    )                                                                                                                                                                                     \
    o_traits_specialize_all_super_traitNTTS(                                                                                                                                              \
    (phantom,reflection,native)                                                                                                                                                           \
    , (typename,typename,typename,typename,typename,typename,typename)                                                                                                                    \
    , (t_Ty, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5)                                                                                                                  \
    , _native_member_function_##6                                                                                                                                                                  \
    , (_native_member_function_##Base<t_Ty>)                                                                                                                                                       \
    )                                                                                                                                                                                     \
    o_traits_specialize_all_super_traitNTTS(                                                                                                                                              \
    (phantom,reflection,native)                                                                                                                                                           \
    , (typename,typename,typename,typename,typename,typename,typename,typename)                                                                                                           \
    , (t_Ty, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6)                                                                                                        \
    , _native_member_function_##7                                                                                                                                                                  \
    , (_native_member_function_##Base<t_Ty>)                                                                                                                                                       \
    )                                                                                                                                                                                     \
    o_traits_specialize_all_super_traitNTTS(                                                                                                                                              \
    (phantom,reflection,native)                                                                                                                                                           \
    , (typename,typename,typename,typename,typename,typename,typename,typename,typename)                                                                                                  \
    , (t_Ty, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7)                                                                                              \
    , _native_member_function_##8                                                                                                                                                                  \
    , (_native_member_function_##Base<t_Ty>)                                                                                                                                                       \
    )                                                                                                                                                                                     \
    o_traits_specialize_all_super_traitNTTS(                                                                                                                                              \
    (phantom,reflection,native)                                                                                                                                                           \
    , (typename, typename)                                                                                                                                                                \
    , (t_Ty, t_Signature)                                                                                                                                                                 \
    , _native_member_function_                                                                                                                                                                     \
    , (o_NESTED_TYPE _native_member_function_##FunctionStyleSuperClassSolver<t_Ty,t_Signature>::type)                                                                                              \
    )



#define o_traits_specialize_all_super_traitNTTS_TNativeMemberFunctionRTXXX(_native_member_function_) \
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
    o_traits_specialize_all_super_traitNTTS(                                                                                                                                              \
    (phantom,reflection,native)                                                                                                                                                           \
    , (typename,typename)                                                                                                                                                                          \
    , (t_Ty, t_ReturnType)                                                                                                                                                                              \
    , _native_member_function_##0                                                                                                                                                                  \
    , (_native_member_function_##Base<t_Ty>)                                                                                                                                                       \
    )                                                                                                                                                                                     \
    o_traits_specialize_all_super_traitNTTS(                                                                                                                                              \
    (phantom,reflection,native)                                                                                                                                                           \
    , (typename,typename,typename)                                                                                                                                                                 \
    , (t_Ty, t_ReturnType, t_Param0)                                                                                                                                                                    \
    , _native_member_function_##1                                                                                                                                                                  \
    , (_native_member_function_##Base<t_Ty>)                                                                                                                                                       \
    )                                                                                                                                                                                     \
    o_traits_specialize_all_super_traitNTTS(                                                                                                                                              \
    (phantom,reflection,native)                                                                                                                                                           \
    , (typename,typename,typename,typename)                                                                                                                                                        \
    , (t_Ty, t_ReturnType, t_Param0,t_Param1)                                                                                                                                                           \
    , _native_member_function_##2                                                                                                                                                                  \
    , (_native_member_function_##Base<t_Ty>)                                                                                                                                                       \
    )                                                                                                                                                                                     \
    o_traits_specialize_all_super_traitNTTS(                                                                                                                                              \
    (phantom,reflection,native)                                                                                                                                                           \
    , (typename,typename,typename,typename,typename)                                                                                                                                               \
    , (t_Ty, t_ReturnType, t_Param0,t_Param1,t_Param2)                                                                                                                                                  \
    , _native_member_function_##3                                                                                                                                                                  \
    , (_native_member_function_##Base<t_Ty>)                                                                                                                                                       \
    )                                                                                                                                                                                     \
    o_traits_specialize_all_super_traitNTTS(                                                                                                                                              \
    (phantom,reflection,native)                                                                                                                                                           \
    , (typename,typename,typename,typename,typename,typename)                                                                                                                                      \
    , (t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3)                                                                                                                                      \
    , _native_member_function_##4                                                                                                                                                                  \
    , (_native_member_function_##Base<t_Ty>)                                                                                                                                                       \
    )                                                                                                                                                                                     \
    o_traits_specialize_all_super_traitNTTS(                                                                                                                                              \
    (phantom,reflection,native)                                                                                                                                                           \
    , (typename,typename,typename,typename,typename,typename,typename)                                                                                                                             \
    , (t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4)                                                                                                                            \
    , _native_member_function_##5                                                                                                                                                                  \
    , (_native_member_function_##Base<t_Ty>)                                                                                                                                                       \
    )                                                                                                                                                                                     \
    o_traits_specialize_all_super_traitNTTS(                                                                                                                                              \
    (phantom,reflection,native)                                                                                                                                                           \
    , (typename,typename,typename,typename,typename,typename,typename,typename)                                                                                                                    \
    , (t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5)                                                                                                                  \
    , _native_member_function_##6                                                                                                                                                                  \
    , (_native_member_function_##Base<t_Ty>)                                                                                                                                                       \
    )                                                                                                                                                                                     \
    o_traits_specialize_all_super_traitNTTS(                                                                                                                                              \
    (phantom,reflection,native)                                                                                                                                                           \
    , (typename,typename,typename,typename,typename,typename,typename,typename,typename)                                                                                                           \
    , (t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6)                                                                                                        \
    , _native_member_function_##7                                                                                                                                                                  \
    , (_native_member_function_##Base<t_Ty>)                                                                                                                                                       \
    )                                                                                                                                                                                     \
    o_traits_specialize_all_super_traitNTTS(                                                                                                                                              \
    (phantom,reflection,native)                                                                                                                                                           \
    , (typename,typename,typename,typename,typename,typename,typename,typename,typename,typename)                                                                                                  \
    , (t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7)                                                                                              \
    , _native_member_function_##8                                                                                                                                                                  \
    , (_native_member_function_##Base<t_Ty>)                                                                                                                                                       \
    )                                                                                                                                                                                     \
    o_traits_specialize_all_super_traitNTTS(                                                                                                                                              \
    (phantom,reflection,native)                                                                                                                                                           \
    , (typename, typename)                                                                                                                                                                \
    , (t_Ty, t_Signature)                                                                                                                                                                 \
    , _native_member_function_                                                                                                                                                                     \
    , (o_NESTED_TYPE _native_member_function_##FunctionStyleSuperClassSolver<t_Ty,t_Signature>::type)                                                                                              \
    )

#define o_enum_1(_values_)\
class o_PP_CAT(_name_,__LINE__) \
        {\
        o_PP_CAT(_name_,__LINE__)() \
            {\
            typedef _name_ enum_type;\
            o_enum_add_values _values_\
            }\
        };

#define o_enum_2(_name_,_values_)\
        class o_PP_CAT(_name_,__LINE__) \
        {\
            o_PP_CAT(_name_,__LINE__)() \
            {\
                phantom::reflection::Enum* pEnum = typeOf<_name_>();\
                typedef _name_ enum_type;\
                o_enum_add_values _values_\
            }\
        };

#if o_COMPILER == o_COMPILER_VISUAL_STUDIO
#define o_enum_add_values( ... ) o_PP_CAT(o_PP_CAT(o_enum_add_values_, o_PP_NARG(__VA_ARGS__)),(__VA_ARGS__) )
#else
#define o_enum_add_values( ... ) o_PP_CAT(o_enum_add_values_, o_PP_NARG(__VA_ARGS__)) (__VA_ARGS__) 
#endif

#define o_enum_add_values_1( v0) pEnum->addConstant(o_new(phantom::reflection::native::TConstant<enum_value_type>)(o_PP_QUOTE(v0), v0));
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

#if o_COMPILER == o_COMPILER_VISUAL_STUDIO
#define o_enum_add_valuesN( ... ) o_PP_CAT(o_PP_CAT(o_enum_add_valuesN_, o_PP_NARG(__VA_ARGS__)),(__VA_ARGS__) )
#else
#define o_enum_add_valuesN( ... ) o_PP_CAT(o_enum_add_valuesN_, o_PP_NARG(__VA_ARGS__)) (__VA_ARGS__)
#endif

#define o_enum_add_valuesN_2( n, v0) pEnum->addConstant(o_new(phantom::reflection::native::TConstant<enum_value_type>)(o_PP_QUOTE(v0), ::o_PP_CREATE_SCOPE n::v0));
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




#endif // o_phantom_reflection_h__
