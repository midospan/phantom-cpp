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

#define o_global_code_typename_list_11 typename,typename,typename,typename,typename,typename,typename,typename,typename,typename,typename
    
#define o_global_code_CreateTemplateParametersListString(_func_name_) \
    o_reflection_create_template_parameters_list_string_N((o_TemplateT),(o_TemplateP),_func_name_)

#define o_global_code_TemplateSignature \
    template< o_PP_MIX((o_TemplateT),(o_TemplateP)) >

#define o_global_code_TemplateSignaturePlusCounter \
    template< o_PP_MIX((o_TemplateT),(o_TemplateP)), int t_RESERVED_counter >

#define o_global_code_Specialize__is_meta_type \
    o_namespace_begin(phantom, detail)\
    o_local_code_TemplateSpecializationSignature \
    struct is_meta_type<o_global_value_QualifiedType>\
    {\
    BOOST_STATIC_CONSTANT(bool, value = true);\
    };\
    o_namespace_end(phantom, detail)

#define o_global_code_Specialize__meta_specifiers \
    namespace phantom { \
    o_local_code_TemplateSpecializationSignature \
    struct meta_specifiers<o_global_value_QualifiedType> \
    { \
        const static int value = o_local_value_MetaSpecifiers; \
    }; \
    }
/*
// 
// #define o_global_code_Specialize__object_dynamic_cast \
//     o_namespace_begin(phantom, detail) \
//     o_local_code_TemplateSpecializationSignature \
//     struct object_dynamic_cast_<o_global_value_QualifiedType> \
//     { \
//         o_forceinline static void* apply(reflection::Class* a_pClass, o_global_value_QualifiedType* a_pBase) \
//         { \
//             return o_global_value_QualifiedEmbeddingType::PHANTOM_CODEGEN_static_member_function_DynamicCast(a_pClass, a_pBase); \
//         } \
//     }; \
//     o_namespace_end(phantom, detail)
*/


#define o_global_value_ShortType            o_Name
#define o_global_value_Type                    o_global_value_ShortType o_local_code_TemplateArgumentList
#define o_global_value_QualifiedShortType    o_local_value_Namespace::o_global_value_ShortType
#define o_global_value_QualifiedType        o_local_value_Namespace::o_global_value_Type
#define o_global_value_ShortEmbeddingType            o_local_value_ShortEmbeddingType
#define o_global_value_EmbeddingType                o_global_value_ShortEmbeddingType o_local_code_TemplateArgumentList
#define o_global_value_QualifiedEmbeddingType        o_local_value_Namespace::o_global_value_EmbeddingType
#define o_global_value_QualifiedShortEmbeddingType    o_local_value_Namespace::o_local_value_ShortEmbeddingType
#define o_global_value_ShortSuperClassCountHelper                o_PP_CAT o_PP_LEFT_PAREN o_global_value_ShortType, _Super o_PP_RIGHT_PAREN
#define o_global_value_SuperClassCountHelper                    o_global_value_ShortSuperClassCountHelper o_local_code_TemplateArgumentList

#define o_global_code_CanonicalInheritanceList_0() 
#define o_global_code_CanonicalInheritanceList_1(_s0_) o_global_code_CanonicalInheritanceList_0() public _s0_ 
#define o_global_code_CanonicalInheritanceList_2(_s0_,_s1_) o_global_code_CanonicalInheritanceList_1(_s0_) , public _s1_ 
#define o_global_code_CanonicalInheritanceList_3(_s0_,_s1_,_s2_) o_global_code_CanonicalInheritanceList_2(_s0_,_s1_) , public _s2_ 
#define o_global_code_CanonicalInheritanceList_4(_s0_,_s1_,_s2_,_s3_) o_global_code_CanonicalInheritanceList_3(_s0_,_s1_,_s2_) , public _s3_ 
#define o_global_code_CanonicalInheritanceList_5(_s0_,_s1_,_s2_,_s3_,_s4_) o_global_code_CanonicalInheritanceList_4(_s0_,_s1_,_s2_,_s3_) , public _s4_ 
#define o_global_code_CanonicalInheritanceList_6(_s0_,_s1_,_s2_,_s3_,_s4_,_s5_) o_global_code_CanonicalInheritanceList_5(_s0_,_s1_,_s2_,_s3_,_s4_) , public _s5_ 
#define o_global_code_CanonicalInheritanceList_7(_s0_,_s1_,_s2_,_s3_,_s4_,_s5_,_s6_) o_global_code_CanonicalInheritanceList_6(_s0_,_s1_,_s2_,_s3_,_s4_,_s5_) , public _s6_ 
#define o_global_code_CanonicalInheritanceList_8(_s0_,_s1_,_s2_,_s3_,_s4_,_s5_,_s6_,_s7_) o_global_code_CanonicalInheritanceList_7(_s0_,_s1_,_s2_,_s3_,_s4_,_s5_,_s6_) , public _s7_ 
#define o_global_code_CanonicalInheritanceList_9(_s0_,_s1_,_s2_,_s3_,_s4_,_s5_,_s6_,_s7_,_s8_) o_global_code_CanonicalInheritanceList_8(_s0_,_s1_,_s2_,_s3_,_s4_,_s5_,_s6_,_s7_) , public _s8_ 
#define o_global_code_CanonicalInheritanceList_10(_s0_,_s1_,_s2_,_s3_,_s4_,_s5_,_s6_,_s7_,_s8_,_s9_) o_global_code_CanonicalInheritanceList_9(_s0_,_s1_,_s2_,_s3_,_s4_,_s5_,_s6_,_s7_,_s8_) , public _s9_ 

/*
#define o_global_code_EnumTotalTrackCount   \
  enum PHANTOM_CODEGEN_enum_TotalTrackCount { PHANTOM_CODEGEN_enum_value_TotalTrackCount = PHANTOM_CODEGEN_enum_value_TrackCount + super_total_track_count_of<o_global_value_Type>::value };
*/
/*

#define o_global_value_TotalTrackCount_0() PHANTOM_CODEGEN_enum_value_TrackCount
#define o_global_value_TotalTrackCount_1()  o_global_value_TotalTrackCount_0() +  phantom::proxy_of<t_S0>::type::PHANTOM_CODEGEN_enum_value_TotalTrackCount
#define o_global_value_TotalTrackCount_2()  o_global_value_TotalTrackCount_1() +  phantom::proxy_of<t_S1>::type::PHANTOM_CODEGEN_enum_value_TotalTrackCount
#define o_global_value_TotalTrackCount_3()  o_global_value_TotalTrackCount_2() +  phantom::proxy_of<t_S2>::type::PHANTOM_CODEGEN_enum_value_TotalTrackCount
#define o_global_value_TotalTrackCount_4()  o_global_value_TotalTrackCount_3() +  phantom::proxy_of<t_S3>::type::PHANTOM_CODEGEN_enum_value_TotalTrackCount
#define o_global_value_TotalTrackCount_5()  o_global_value_TotalTrackCount_4() +  phantom::proxy_of<t_S4>::type::PHANTOM_CODEGEN_enum_value_TotalTrackCount
#define o_global_value_TotalTrackCount_6()  o_global_value_TotalTrackCount_5() +  phantom::proxy_of<t_S5>::type::PHANTOM_CODEGEN_enum_value_TotalTrackCount
#define o_global_value_TotalTrackCount_7()  o_global_value_TotalTrackCount_6() +  phantom::proxy_of<t_S6>::type::PHANTOM_CODEGEN_enum_value_TotalTrackCount
#define o_global_value_TotalTrackCount_8()  o_global_value_TotalTrackCount_7() +  phantom::proxy_of<t_S7>::type::PHANTOM_CODEGEN_enum_value_TotalTrackCount
#define o_global_value_TotalTrackCount_9()  o_global_value_TotalTrackCount_8() +  phantom::proxy_of<t_S8>::type::PHANTOM_CODEGEN_enum_value_TotalTrackCount
#define o_global_value_TotalTrackCount_10() o_global_value_TotalTrackCount_9() +  phantom::proxy_of<t_S9>::type::PHANTOM_CODEGEN_enum_value_TotalTrackCount
*/


#define o_global_code_SetupMembers() \
    o_namespace_begin(phantom,reflection,detail)            \
    o_local_code_TemplateSignature                          \
    struct member_setup_raii<o_global_value_QualifiedType>  \
    : public o_global_value_QualifiedType \
    {\
        typedef o_global_value_QualifiedType reflected_type;\
        struct raii {\
            o_local_value_QualifiedInternalReflectionClass reflection_registrer;\
        };\
    };\
    o_namespace_end(phantom,reflection,detail)


#define o_global_code_Specialize__type_name_of_forward_helper(_ns_,_type_) \
  o_global_code_Specialize__type_name_of_forward_helper_counter_L1(_ns_,_type_, __COUNTER__)

#define o_global_code_Specialize__type_name_of_forward_helper_counter_L1(_ns_,_type_, _counter_) \
  o_global_code_Specialize__type_name_of_forward_helper_counter_L0(_ns_,_type_, _counter_)

#define o_global_code_Specialize__type_name_of_forward_helper_empty_namespace(_type_) \
  o_global_code_Specialize__type_name_of_forward_helper_empty_namespace_counter_L1(_type_, __COUNTER__)

#define o_global_code_Specialize__type_name_of_forward_helper_empty_namespace_counter_L1(_type_, _counter_) \
  o_global_code_Specialize__type_name_of_forward_helper_namespace_counter_L0(_type_, _counter_)

#define o_global_code_Specialize__type_name_of_helper \
    o_namespace_begin(phantom, reflection, detail) \
    template<> \
    class type_name_of<o_global_value_QualifiedType> \
    { \
    public: \
        static const char* name() { return o_PP_QUOTE(o_global_value_ShortType); } \
        static const char* decoratedName() { return o_PP_QUOTE(o_global_value_Type); } \
        static const char* qualifiedName() \
        { \
        return o_local_value_NamespaceString"::"o_PP_QUOTE(o_global_value_ShortType);\
        } \
        static const char* qualifiedDecoratedName() \
        { \
            return o_local_value_NamespaceString"::"o_PP_QUOTE(o_global_value_Type);\
        } \
        static const char* namespaceName() \
        { \
        return o_local_value_NamespaceString;\
        } \
        static const char*  classScopeName() { return ""; }\
    }; \
    o_namespace_end(phantom, reflection, detail) 


#define o_global_code_Specialize__type_name_of_forward_helper_counter_L0(_ns_,_type_, _counter_) \
    o_namespace_begin(phantom, detail) \
    template<> \
    class type_name_of_counter<o_root_namespace::_ns_::_type_, _counter_> \
    { \
    public: \
        static const char* decoratedName() { return o_PP_QUOTE(_type_); } \
        static const char* qualifiedDecoratedName() \
        { \
            return o_root_namespace_name "::" o_PP_QUOTE(_ns_)"::"o_PP_QUOTE(_type_);\
        } \
        static const char* name() { return o_PP_QUOTE(_type_); } \
        static const char* qualifiedName() \
        { \
        return o_root_namespace_name "::" o_PP_QUOTE(_ns_)"::"o_PP_QUOTE(_type_);\
        } \
        static const char* namespaceName() \
        { \
        return o_root_namespace_name "::" o_PP_QUOTE(_ns_);\
        } \
        static const char*  classScopeName() { return ""; }\
    }; \
    o_namespace_end(phantom, detail) 

#define o_global_code_Specialize__type_name_of_forward_helper_namespace_counter_L0(_type_, _counter_) \
  o_namespace_begin(phantom, detail) \
  template<> \
class type_name_of_counter<o_root_namespace::_type_, _counter_> \
  { \
  public: \
    static const char* decoratedName() { return o_PP_QUOTE(_type_); } \
    static const char* qualifiedDecoratedName() \
    { \
    return o_root_namespace_name "::" o_PP_QUOTE(_type_);\
    } \
    static const char* name() { return o_PP_QUOTE(_type_); } \
    static const char* qualifiedName() \
    { \
    return o_root_namespace_name "::" o_PP_QUOTE(_type_);\
    } \
    static const char* namespaceName() \
    { \
    return o_root_namespace_name;\
    } \
    static const char*  classScopeName() { return ""; }\
  }; \
  o_namespace_end(phantom, detail) 


#define o_global_code_Specialize__type_name_of_forward_helper_template(_ns_,_type_,_ts_) \
    o_global_code_Specialize__type_name_of_forward_helper_template_counter_L1(_ns_,_type_,_ts_,__COUNTER__)

#define o_global_code_Specialize__type_name_of_forward_helper_template_counter_L1(_ns_,_type_,_ts_,_counter_) \
    o_global_code_Specialize__type_name_of_forward_helper_template_counter_L0(_ns_,_type_,_ts_,_counter_)

#define o_global_code_Specialize__type_name_of_forward_helper_template_empty_namespace(_type_) \
  o_global_code_Specialize__type_name_of_forward_helper_template_empty_namespace_counter_L1(_type_, __COUNTER__)

#define o_global_code_Specialize__type_name_of_forward_helper_template_empty_namespace_counter_L1(_type_, _counter_) \
  o_global_code_Specialize__type_name_of_forward_helper_template_empty_namespace_counter_L0(_type_, _counter_)


#define o_global_code_Specialize__type_name_of_forward_helper_template_counter_L0(_ns_,_type_,_ts_,_counter_) \
    o_namespace_begin(phantom, detail) \
    template< o_PP_MIX(_ts_, (o_PP_CAT o_PP_LEFT_PAREN o_PP_CREATE_TEMPLATE_ARGUMENT_LIST, o_PP_CAT(o_PP_NARG, _ts_) o_PP_RIGHT_PAREN ) ) > \
    class type_name_of_counter< o_root_namespace::_ns_::_type_ < o_PP_CAT o_PP_LEFT_PAREN o_PP_CREATE_TEMPLATE_ARGUMENT_LIST, o_PP_CAT(o_PP_NARG, _ts_) o_PP_RIGHT_PAREN >, _counter_ > \
    { \
    public: \
        static phantom::string decoratedName() \
        { \
        phantom::string str = o_PP_QUOTE(_type_) "<";\
        str += o_global_code_CreateTemplateParametersListStringMix_N(_ts_,(o_PP_CAT o_PP_LEFT_PAREN o_PP_CREATE_TEMPLATE_ARGUMENT_LIST, o_PP_CAT(o_PP_NARG, _ts_) o_PP_RIGHT_PAREN), decoratedName ) ; \
        str += '>';\
        return str;\
        } \
        static phantom::string qualifiedDecoratedName() \
        { \
        phantom::string str = o_root_namespace_name "::" o_PP_QUOTE(_ns_) "::" o_PP_QUOTE(_type_) "<";\
        str += o_global_code_CreateTemplateParametersListStringMix_N(_ts_,(o_PP_CAT o_PP_LEFT_PAREN o_PP_CREATE_TEMPLATE_ARGUMENT_LIST, o_PP_CAT(o_PP_NARG, _ts_) o_PP_RIGHT_PAREN), qualifiedDecoratedName ) ; \
        str += '>';\
        return str;\
        } \
        static const char* name() \
        { \
            return o_PP_QUOTE(_type_); \
        } \
        static const char* qualifiedName() \
        { \
            return o_root_namespace_name "::" o_PP_QUOTE(_ns_) "::" o_PP_QUOTE(_type_); \
        } \
        static const char* namespaceName() \
        { \
        return o_root_namespace_name "::" o_PP_QUOTE(_ns_);\
        } \
        static const char*  classScopeName() { return ""; }\
    };\
    o_namespace_end(phantom, detail) 


#define o_global_code_Specialize__type_name_of_forward_helper_template_empty_namespace_counter_L0(_type_,_ts_,_counter_) \
  o_namespace_begin(phantom, detail) \
  template< o_PP_MIX(_ts_, (o_PP_CAT o_PP_LEFT_PAREN o_PP_CREATE_TEMPLATE_ARGUMENT_LIST, o_PP_CAT(o_PP_NARG, _ts_) o_PP_RIGHT_PAREN ) ) > \
class type_name_of_counter< o_root_namespace::_type_ < o_PP_CAT o_PP_LEFT_PAREN o_PP_CREATE_TEMPLATE_ARGUMENT_LIST, o_PP_CAT(o_PP_NARG, _ts_) o_PP_RIGHT_PAREN >, _counter_ > \
  { \
  public: \
        static phantom::string decoratedName() \
        { \
        phantom::string str = o_PP_QUOTE(_type_) "<";\
        str += o_global_code_CreateTemplateParametersListStringMix_N(_ts_,(o_PP_CAT o_PP_LEFT_PAREN o_PP_CREATE_TEMPLATE_ARGUMENT_LIST, o_PP_CAT(o_PP_NARG, _ts_) o_PP_RIGHT_PAREN), name ) ; \
        str += '>';\
        return str;\
        } \
        static phantom::string qualifiedDecoratedName() \
        { \
        phantom::string str = o_root_namespace_name "::" o_PP_QUOTE(_type_) "<";\
        str += o_global_code_CreateTemplateParametersListStringMix_N(_ts_,(o_PP_CAT o_PP_LEFT_PAREN o_PP_CREATE_TEMPLATE_ARGUMENT_LIST, o_PP_CAT(o_PP_NARG, _ts_) o_PP_RIGHT_PAREN), qualifiedName ) ; \
        str += '>';\
        return str;\
        } \
        static const char* name() \
        { \
        return o_PP_QUOTE(_type_); \
        } \
        static const char* qualifiedName() \
        { \
        return o_root_namespace_name "::" o_PP_QUOTE(_type_); \
        } \
        static const char* namespaceName() \
        { \
        return o_root_namespace_name;\
        } \
        static const char*  classScopeName() { return ""; }\
  };\
  o_namespace_end(phantom, detail) 


/*
#define o_global_code_Specialize__type_of \
    o_namespace_begin(phantom, reflection, detail) \
    o_local_code_TemplateSpecializationSignature \
    struct type_of<o_global_value_QualifiedType> \
    { \
        static o_local_value_QualifiedReflectReturnType* object() \
        { \
            return o_global_value_QualifiedEmbeddingType::Reflect(); \
        } \
    }; \
    o_namespace_end(phantom, reflection, detail) */

#define o_global_code_Specialize__type_of_counter \
    o_namespace_begin(phantom, reflection, detail) \
    o_local_code_TemplateSpecializationSignaturePlusCounter \
    struct type_of_counter<o_global_value_QualifiedType, t_RESERVED_counter> : public type_of<o_global_value_QualifiedType> {};\
    o_namespace_end(phantom, reflection, detail) 

#define o_global_code_MaxSizeStaticAssert   BOOST_STATIC_ASSERT_MSG(sizeof(o_global_value_Type) < o__uint__max_class_size, o_PP_QUOTE(o_global_value_Type)" size exceeds the defined max size ("o_PP_QUOTE(o__uint__max_class_size)") (check o__uint__max_class_size in _custom.h)");  


#if o_COMPILER == o_COMPILER_VISUAL_STUDIO
#    define o_signal_data_declaration(...) \
    o_PP_CAT(o_signal_data_declaration_, o_PP_NARG(__VA_ARGS__))o_PP_LEFT_PAREN __VA_ARGS__ o_PP_RIGHT_PAREN
#else
#    define o_signal_data_declaration(...) \
    o_PP_CAT(o_signal_data_declaration_, o_PP_NARG(__VA_ARGS__))(__VA_ARGS__)
#endif

#    define o_signal_data_declaration_1(_signal_name_) \
  inline phantom::signal_t _signal_name_(void) const;\
  mutable phantom::connection::slot::list    PHANTOM_CODEGEN_m_slot_list_of_##_signal_name_;

#    define o_signal_data_declaration_2(_signal_name_, _t0_) \
  inline phantom::signal_t _signal_name_(_t0_ a_0) const;\
  mutable phantom::connection::slot::list    PHANTOM_CODEGEN_m_slot_list_of_##_signal_name_;

#    define o_signal_data_declaration_3(_signal_name_, _t0_, _t1_) \
  inline phantom::signal_t _signal_name_(_t0_ a_0, _t1_ a_1) const;\
  mutable phantom::connection::slot::list    PHANTOM_CODEGEN_m_slot_list_of_##_signal_name_;

#    define o_signal_data_declaration_4(_signal_name_, _t0_, _t1_, _t2_) \
  inline phantom::signal_t _signal_name_(_t0_ a_0, _t1_ a_1, _t2_ a_2) const;\
  mutable phantom::connection::slot::list    PHANTOM_CODEGEN_m_slot_list_of_##_signal_name_;

#    define o_signal_data_declaration_5(_signal_name_, _t0_, _t1_, _t2_, _t3_) \
  inline phantom::signal_t _signal_name_(_t0_ a_0, _t1_ a_1, _t2_ a_2, _t3_ a_3) const;\
  mutable phantom::connection::slot::list    PHANTOM_CODEGEN_m_slot_list_of_##_signal_name_;

#    define o_signal_data_declaration_6(_signal_name_, _t0_, _t1_, _t2_, _t3_, _t4_) \
  inline phantom::signal_t _signal_name_(_t0_ a_0, _t1_ a_1, _t2_ a_2, _t3_ a_3, _t4_ a_4) const;\
  mutable phantom::connection::slot::list    PHANTOM_CODEGEN_m_slot_list_of_##_signal_name_;

#    define o_signal_data_declaration_7(_signal_name_, _t0_, _t1_, _t2_, _t3_, _t4_, _t5_) \
  inline phantom::signal_t _signal_name_(_t0_ a_0, _t1_ a_1, _t2_ a_2, _t3_ a_3, _t4_ a_4, _t5_ a_5) const;\
  mutable phantom::connection::slot::list    PHANTOM_CODEGEN_m_slot_list_of_##_signal_name_;

#    define o_signal_data_declaration_8(_signal_name_, _t0_, _t1_, _t2_, _t3_, _t4_, _t5_, _t6_) \
  inline phantom::signal_t _signal_name_(_t0_ a_0, _t1_ a_1, _t2_ a_2, _t3_ a_3, _t4_ a_4, _t5_ a_5, _t6_ a_6) const;\
  mutable phantom::connection::slot::list    PHANTOM_CODEGEN_m_slot_list_of_##_signal_name_;

#    define o_signal_data_declaration_9(_signal_name_, _t0_, _t1_, _t2_, _t3_, _t4_, _t5_, _t6_, _t7_) \
  inline phantom::signal_t _signal_name_(_t0_ a_0, _t1_ a_1, _t2_ a_2, _t3_ a_3, _t4_ a_4, _t5_ a_5, _t6_ a_6, _t7_ a_7) const;\
  mutable phantom::connection::slot::list    PHANTOM_CODEGEN_m_slot_list_of_##_signal_name_;





#if o_COMPILER == o_COMPILER_VISUAL_STUDIO
#    define o_signal_data_definition(...) \
    o_PP_CAT(o_signal_data_definition_, o_PP_NARG(__VA_ARGS__))o_PP_LEFT_PAREN __VA_ARGS__ o_PP_RIGHT_PAREN
#else
#    define o_signal_data_definition(...) \
    o_PP_CAT(o_signal_data_definition_, o_PP_NARG(__VA_ARGS__))( __VA_ARGS__ )
#endif

#    define o_signal_data_definition_2(_class_, _signal_name_) \
  phantom::signal_t _class_::_signal_name_(void) const\
{\
  phantom::connection::slot* pSlot = PHANTOM_CODEGEN_m_slot_list_of_##_signal_name_.head();\
  while(pSlot)\
{\
  phantom::connection::pair::push(this, pSlot);\
  pSlot->subroutine()->call(pSlot->receiver(), o_no_arg );\
  pSlot = pSlot->next();\
  phantom::connection::pair::pop();\
}\
  return phantom::signal_t();\
}

#    define o_signal_data_definition_3(_class_, _signal_name_, _t0_) \
  phantom::signal_t _class_::_signal_name_(_t0_ a_0) const\
{\
  phantom::connection::slot* pSlot = PHANTOM_CODEGEN_m_slot_list_of_##_signal_name_.head();\
  while(pSlot)\
{\
  phantom::connection::pair::push(this, pSlot);\
  void* args[] = { (void*)(&a_0) };\
  pSlot->subroutine()->call( pSlot->receiver(), args );\
  pSlot = pSlot->next();\
  phantom::connection::pair::pop();\
}\
  return phantom::signal_t();\
}

#    define o_signal_data_definition_4(_class_, _signal_name_, _t0_, _t1_) \
  phantom::signal_t _class_::_signal_name_(_t0_ a_0, _t1_ a_1) const\
{\
  phantom::connection::slot* pSlot = PHANTOM_CODEGEN_m_slot_list_of_##_signal_name_.head();\
  while(pSlot)\
{\
  phantom::connection::pair::push(this, pSlot);\
  void* args[] = { (void*)(&a_0), (void*)(&a_1) };\
  pSlot->subroutine()->call( pSlot->receiver(), args );\
  pSlot = pSlot->next();\
  phantom::connection::pair::pop();\
}\
  return phantom::signal_t();\
}

#    define o_signal_data_definition_5(_class_, _signal_name_, _t0_, _t1_, _t2_) \
  phantom::signal_t _class_::_signal_name_(_t0_ a_0, _t1_ a_1, _t2_ a_2) const\
{\
  phantom::connection::slot* pSlot = PHANTOM_CODEGEN_m_slot_list_of_##_signal_name_.head();\
  while(pSlot)\
{\
  phantom::connection::pair::push(this, pSlot);\
  void* args[] = { (void*)(&a_0), (void*)(&a_1), (void*)(&a_2) };\
  pSlot->subroutine()->call( pSlot->receiver(), args );\
  pSlot = pSlot->next();\
  phantom::connection::pair::pop();\
}\
  return phantom::signal_t();\
}

#    define o_signal_data_definition_6(_class_, _signal_name_, _t0_, _t1_, _t2_, _t3_) \
  phantom::signal_t _class_::_signal_name_(_t0_ a_0, _t1_ a_1, _t2_ a_2, _t3_ a_3) const\
{\
  phantom::connection::slot* pSlot = PHANTOM_CODEGEN_m_slot_list_of_##_signal_name_.head();\
  while(pSlot)\
{\
  phantom::connection::pair::push(this, pSlot);\
  void* args[] = { (void*)(&a_0), (void*)(&a_1), (void*)(&a_2), (void*)(&a_3) };\
  pSlot->subroutine()->call( pSlot->receiver(), args );\
  pSlot = pSlot->next();\
  phantom::connection::pair::pop();\
}\
  return phantom::signal_t();\
}

#    define o_signal_data_definition_7(_class_, _signal_name_, _t0_, _t1_, _t2_, _t3_, _t4_) \
  phantom::signal_t _class_::_signal_name_(_t0_ a_0, _t1_ a_1, _t2_ a_2, _t3_ a_3, _t4_ a_4) const\
{\
  phantom::connection::slot* pSlot = PHANTOM_CODEGEN_m_slot_list_of_##_signal_name_.head();\
  while(pSlot)\
{\
  phantom::connection::pair::push(this, pSlot);\
  void* args[] = { (void*)(&a_0), (void*)(&a_1), (void*)(&a_2), (void*)(&a_3), (void*)(&a_4) };\
  pSlot->subroutine()->call( pSlot->receiver(), args );\
  pSlot = pSlot->next();\
  phantom::connection::pair::pop();\
}\
  return phantom::signal_t();\
}

#    define o_signal_data_definition_8(_class_, _signal_name_, _t0_, _t1_, _t2_, _t3_, _t4_, _t5_) \
  phantom::signal_t _class_::_signal_name_(_t0_ a_0, _t1_ a_1, _t2_ a_2, _t3_ a_3, _t4_ a_4, _t5_ a_5) const\
{\
  phantom::connection::slot* pSlot = PHANTOM_CODEGEN_m_slot_list_of_##_signal_name_.head();\
  while(pSlot)\
{\
  phantom::connection::pair::push(this, pSlot);\
  void* args[] = { (void*)(&a_0), (void*)(&a_1), (void*)(&a_2), (void*)(&a_3), (void*)(&a_4), (void*)(&a_5) };\
  pSlot->subroutine()->call( pSlot->receiver(), args );\
  pSlot = pSlot->next();\
  phantom::connection::pair::pop();\
}\
  return phantom::signal_t();\
}

#    define o_signal_data_definition_9(_class_, _signal_name_, _t0_, _t1_, _t2_, _t3_, _t4_, _t5_, _t6_) \
  phantom::signal_t _class_::_signal_name_(_t0_ a_0, _t1_ a_1, _t2_ a_2, _t3_ a_3, _t4_ a_4, _t5_ a_5, _t6_ a_6) const\
{\
  phantom::connection::slot* pSlot = PHANTOM_CODEGEN_m_slot_list_of_##_signal_name_.head();\
  while(pSlot)\
{\
  phantom::connection::pair::push(this, pSlot);\
  void* args[] = { (void*)(&a_0), (void*)(&a_1), (void*)(&a_2), (void*)(&a_3), (void*)(&a_4), (void*)(&a_5), (void*)(&a_6) };\
  pSlot->subroutine()->call( pSlot->receiver(), args );\
  pSlot = pSlot->next();\
  phantom::connection::pair::pop();\
}\
  return phantom::signal_t();\
}
#    define o_signal_data_definition_10(_class_, _signal_name_, _t0_, _t1_, _t2_, _t3_, _t4_, _t5_, _t6_, _t7_) \
  phantom::signal_t _class_, ::_signal_name_(_t0_ a_0, _t1_ a_1, _t2_ a_2, _t3_ a_3, _t4_ a_4, _t5_ a_5, _t6_ a_6, _t7_ a_7) const\
{\
  phantom::connection::slot* pSlot = PHANTOM_CODEGEN_m_slot_list_of_##_signal_name_.head();\
  while(pSlot)\
{\
  phantom::connection::pair::push(this, pSlot);\
  void* args[] = { (void*)(&a_0), (void*)(&a_1), (void*)(&a_2), (void*)(&a_3), (void*)(&a_4), (void*)(&a_5), (void*)(&a_6), (void*)(&a_7) };\
  pSlot->subroutine()->call( pSlot->receiver(), args );\
  pSlot = pSlot->next();\
  phantom::connection::pair::pop();\
}\
  return phantom::signal_t();\
}


