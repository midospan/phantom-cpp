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

#ifndef o_phantom_macros_h__
#define o_phantom_macros_h__

/*
// TEMPLATE MSVC
#if o_COMPILER == o_COMPILER_VISUAL_STUDIO
#else
#endif
*/

/*
// TEMPLATE GCC
#if o_COMPILER == o_COMPILER_VISUAL_GCC
#else
#endif
*/

// Logical helpers
#define OR ||
#define AND &&
#define NOT(...) (!(__VA_ARGS__))

// Customizable root namespace
#define o_root_namespace
#define o_root_namespace_name          ""
#define o_root_namespace_open
#define o_root_namespace_close


// Preprocessor helpers

#define o_PP_MACRO_CYCLE_L3(_var_) o_PP_MACRO_CYCLE_L2(_var_)
#define o_PP_MACRO_CYCLE_L2(_var_) o_PP_MACRO_CYCLE_L1(_var_)
#define o_PP_MACRO_CYCLE_L1(_var_) _var_

// Thanks to the genius who found that trick to count __VA_ARGS__ arguments


#define o_PP_CAT_L1(x, y) x##y
#define o_PP_CAT_L2(x, y) o_PP_CAT_L1(x, y)

#if o_COMPILER == o_COMPILER_VISUAL_STUDIO
#define o_PP_CAT(x, y) o_PP_CAT_L2(x,y)
#else
#define o_PP_CAT(x, y) o_PP_CAT_L1(x,y)
#endif

#define o_PP_CAT_P() o_PP_CAT

// Multi level preprocessor quotifier
#define o_PP_QUOTE_L3(toSurround)    o_PP_QUOTE_L2(toSurround)
#define o_PP_QUOTE_L2(toSurround)    o_PP_QUOTE_L1(toSurround)
#define o_PP_QUOTE_L1(toSurround)    o_PP_QUOTE_L0(toSurround)
#define o_PP_QUOTE_L0(toSurround)    o_CS(#toSurround)
#define o_PP_QUOTE(toSurround)        o_PP_QUOTE_L3(toSurround)

#define o_PP_LEFT_PAREN (
#define o_PP_RIGHT_PAREN )

#if o_COMPILER == o_COMPILER_VISUAL_STUDIO
#define o_PP_ARG_N( \
    ____1, ____2, ____3, ____4, ____5, ____6, ____7, ____8, ____9, ____10, \
    ____11,____12,____13,____14,____15,____16,____17,____18,____19,____20, \
    ____21,____22,____23,____24,____25,____26,____27,____28,____29,____30, \
    ____31,____32,____33,____34,____35,____36,____37,____38,____39,____40, \
    ____41,____42,____43,____44,____45,____46,____47,____48,____49,____50, \
    ____51,____52,____53,____54,____55,____56,____57,____58,____59,____60, \
    ____61,____62,____63,____N,...) ____N
#define o_PP_NARG(...) o_PP_ARG_N o_PP_LEFT_PAREN __VA_ARGS__##,63,62,61,60,59,58,57,56,55,54,53,52,51,50,49,48,47,46,45,44,43,42,41,40,39,38,37,36,35,34,33,32,31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0 o_PP_RIGHT_PAREN

#else

#define o_PP_ARG_N( \
    ____1, ____2, ____3, ____4, ____5, ____6, ____7, ____8, ____9, ____10, \
    ____11,____12,____13,____14,____15,____16,____17,____18,____19,____20, \
    ____21,____22,____23,____24,____25,____26,____27,____28,____29,____30, \
    ____31,____32,____33,____34,____35,____36,____37,____38,____39,____40, \
    ____41,____42,____43,____44,____45,____46,____47,____48,____49,____50, \
    ____51,____52,____53,____54,____55,____56,____57,____58,____59,____60, \
    ____61,____62,____63,____N,...) ____N

/// The one to use

#define o_PP_NARG(...) \
    o_PP_NARG_(gcc_specific_C99_adapter,##__VA_ARGS__)

#define o_PP_NARG_(...) \
    o_PP_ARG_N(__VA_ARGS__,62,61,60,59,58,57,56,55,54,53,52,51,50,49,48,47,46,45,44,43,42,41,40,39,38,37,36,35,34,33,32,31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0,gcc_specific_C99_arg)

#endif

#define o_PP_NARG_FUNC() o_PP_NARG

#define o_PP_ARG_0( _a0_, ...) _a0_
#define o_PP_ARG_1( _a0_, _a1_, ...) _a1_
#define o_PP_ARG_2( _a0_, _a1_, _a2_, ...) _a2_
#define o_PP_ARG_3( _a0_, _a1_, _a2_, _a3_, ...) _a3_
#define o_PP_ARG_4( _a0_, _a1_, _a2_, _a3_, _a4_, ...) _a4_
#define o_PP_ARG_5( _a0_, _a1_, _a2_, _a3_, _a4_, _a5_, ...) _a5_
#define o_PP_ARG_6( _a0_, _a1_, _a2_, _a3_, _a4_, _a5_, _a6_, ...) _a6_
#define o_PP_ARG_7( _a0_, _a1_, _a2_, _a3_, _a4_, _a5_, _a6_, _a7_, ...) _a7_
#define o_PP_ARG_8( _a0_, _a1_, _a2_, _a3_, _a4_, _a5_, _a6_, _a7_, _a8_, ...) _a8_
#define o_PP_ARG_9( _a0_, _a1_, _a2_, _a3_, _a4_, _a5_, _a6_, _a7_, _a8_, _a9_, ...) _a9_
#define o_PP_ARG_10(_a0_, _a1_, _a2_, _a3_, _a4_, _a5_, _a6_, _a7_, _a8_, _a9_, _a10_, ...) _a10_
#define o_PP_ARG_11(_a0_, _a1_, _a2_, _a3_, _a4_, _a5_, _a6_, _a7_, _a8_, _a9_, _a10_, _a11_, ...) _a11_
#define o_PP_ARG_12(_a0_, _a1_, _a2_, _a3_, _a4_, _a5_, _a6_, _a7_, _a8_, _a9_, _a10_, _a11_, _a12_, ...) _a12_
#define o_PP_ARG_13(_a0_, _a1_, _a2_, _a3_, _a4_, _a5_, _a6_, _a7_, _a8_, _a9_, _a10_, _a11_, _a12_, _a13_, ...) _a13_
#define o_PP_ARG_14(_a0_, _a1_, _a2_, _a3_, _a4_, _a5_, _a6_, _a7_, _a8_, _a9_, _a10_, _a11_, _a12_, _a13_, _a14_, ...) _a14_
#define o_PP_ARG_15(_a0_, _a1_, _a2_, _a3_, _a4_, _a5_, _a6_, _a7_, _a8_, _a9_, _a10_, _a11_, _a12_, _a13_, _a14_, _a15_, ...) _a15_
#define o_PP_ARG_16(_a0_, _a1_, _a2_, _a3_, _a4_, _a5_, _a6_, _a7_, _a8_, _a9_, _a10_, _a11_, _a12_, _a13_, _a14_, _a15_, _a16_, ...) _a16_
#define o_PP_ARG_17(_a0_, _a1_, _a2_, _a3_, _a4_, _a5_, _a6_, _a7_, _a8_, _a9_, _a10_, _a11_, _a12_, _a13_, _a14_, _a15_, _a16_, _a17_, ...) _a17_
#define o_PP_ARG_18(_a0_, _a1_, _a2_, _a3_, _a4_, _a5_, _a6_, _a7_, _a8_, _a9_, _a10_, _a11_, _a12_, _a13_, _a14_, _a15_, _a16_, _a17_, _a18_, ...) _a18_
#define o_PP_ARG_19(_a0_, _a1_, _a2_, _a3_, _a4_, _a5_, _a6_, _a7_, _a8_, _a9_, _a10_, _a11_, _a12_, _a13_, _a14_, _a15_, _a16_, _a17_, _a18_, _a19_, ...) _a19_


#define o_PP_REMOVE_PAREN(_p_)\
     o_PP_CAT(o_PP_IDENTITY, _p_)

#define o_PP_IDENTITY(...)\
         __VA_ARGS__

#define o_PMM_L3(mmm) o_PMM_L2(mmm)
#define o_PMM_L2(mmm) o_PMM_L1(mmm)
#define o_PMM_L1(mmm) #mmm
#define o_PMM(mmm) o_PMM_L1(mmm)


#if o_COMPILER == o_COMPILER_VISUAL_STUDIO

#define o_PP_MIX(l0,l1) \
    o_PP_CAT o_PP_LEFT_PAREN o_PP_MIX_,o_PP_NARG_FUNC()l0 o_PP_RIGHT_PAREN (l0,l1)

#define o_PP_MIX_1(l0,l1)\
    o_PP_CAT(o_PP_ARG_0,l0) o_PP_CAT(o_PP_ARG_0,l1)

#define o_PP_MIX_2(l0,l1)\
    o_PP_MIX_1(l0,l1) , \
    o_PP_CAT(o_PP_ARG_1,l0) o_PP_CAT(o_PP_ARG_1,l1) \

#define o_PP_MIX_3(l0,l1)\
    o_PP_MIX_2(l0,l1) , \
    o_PP_CAT(o_PP_ARG_2,l0) o_PP_CAT(o_PP_ARG_2,l1) \

#define o_PP_MIX_4(l0,l1)\
    o_PP_MIX_3(l0,l1) , \
    o_PP_CAT(o_PP_ARG_3,l0) o_PP_CAT(o_PP_ARG_3,l1) \

#define o_PP_MIX_5(l0,l1)\
    o_PP_MIX_4(l0,l1) , \
    o_PP_CAT(o_PP_ARG_4,l0) o_PP_CAT(o_PP_ARG_4,l1) \

#define o_PP_MIX_6(l0,l1)\
    o_PP_MIX_5(l0,l1) , \
    o_PP_CAT(o_PP_ARG_5,l0) o_PP_CAT(o_PP_ARG_5,l1) \

#define o_PP_MIX_7(l0,l1)\
    o_PP_MIX_6(l0,l1) , \
    o_PP_CAT(o_PP_ARG_6,l0) o_PP_CAT(o_PP_ARG_6,l1) \

#define o_PP_MIX_8(l0,l1)\
    o_PP_MIX_7(l0,l1) , \
    o_PP_CAT(o_PP_ARG_7,l0) o_PP_CAT(o_PP_ARG_7,l1) \

#define o_PP_MIX_9(l0,l1)\
    o_PP_MIX_8(l0,l1) , \
    o_PP_CAT(o_PP_ARG_8,l0) o_PP_CAT(o_PP_ARG_8,l1) \

#define o_PP_MIX_10(l0,l1)\
    o_PP_MIX_9(l0,l1) , \
    o_PP_CAT(o_PP_ARG_9,l0) o_PP_CAT(o_PP_ARG_9,l1) \


#else

#   define o_PP_MIX(l0,l1) \
    o_PP_CAT(o_PP_MIX_,o_PP_NARG_FUNC()l0) (l0,l1)

#define o_PP_MIX_1(l0,l1)\
    o_PP_ARG_0 l0 o_PP_ARG_0 l1
                                       
#define o_PP_MIX_2(l0,l1)\
    o_PP_MIX_1(l0,l1) , \
    o_PP_ARG_1 l0 o_PP_ARG_1 l1 \
                                       
#define o_PP_MIX_3(l0,l1)\
    o_PP_MIX_2(l0,l1) , \
    o_PP_ARG_2 l0 o_PP_ARG_2 l1 \
                                       
#define o_PP_MIX_4(l0,l1)\
    o_PP_MIX_3(l0,l1) , \
    o_PP_ARG_3 l0 o_PP_ARG_3 l1 \
                                       
#define o_PP_MIX_5(l0,l1)\
    o_PP_MIX_4(l0,l1) , \
    o_PP_ARG_4 l0 o_PP_ARG_4 l1 \
                                       
#define o_PP_MIX_6(l0,l1)\
    o_PP_MIX_5(l0,l1) , \
    o_PP_ARG_5 l0 o_PP_ARG_5 l1 \
                                       
#define o_PP_MIX_7(l0,l1)\
    o_PP_MIX_6(l0,l1) , \
    o_PP_ARG_6 l0 o_PP_ARG_6 l1 \
                                       
#define o_PP_MIX_8(l0,l1)\
    o_PP_MIX_7(l0,l1) , \
    o_PP_ARG_7 l0 o_PP_ARG_7 l1 \
                                       
#define o_PP_MIX_9(l0,l1)\
    o_PP_MIX_8(l0,l1) , \
    o_PP_ARG_8 l0 o_PP_ARG_8 l1 \
                                       
#define o_PP_MIX_10(l0,l1)\
    o_PP_MIX_9(l0,l1) , \
    o_PP_ARG_9 l0 o_PP_ARG_9 l1 \

#endif


#define o_PP_CREATE_TEMPLATE_ARGUMENT_LIST1\
    t_0
#define o_PP_CREATE_TEMPLATE_ARGUMENT_LIST2 \
    o_PP_CREATE_TEMPLATE_ARGUMENT_LIST1, t_1

#define o_PP_CREATE_TEMPLATE_ARGUMENT_LIST3 \
    o_PP_CREATE_TEMPLATE_ARGUMENT_LIST2, t_2

#define o_PP_CREATE_TEMPLATE_ARGUMENT_LIST4 \
    o_PP_CREATE_TEMPLATE_ARGUMENT_LIST3, t_3

#define o_PP_CREATE_TEMPLATE_ARGUMENT_LIST5 \
    o_PP_CREATE_TEMPLATE_ARGUMENT_LIST4, t_4

#define o_PP_CREATE_TEMPLATE_ARGUMENT_LIST6 \
    o_PP_CREATE_TEMPLATE_ARGUMENT_LIST5, t_5

#define o_PP_CREATE_TEMPLATE_ARGUMENT_LIST7 \
    o_PP_CREATE_TEMPLATE_ARGUMENT_LIST6, t_6

#define o_PP_CREATE_TEMPLATE_ARGUMENT_LIST8 \
    o_PP_CREATE_TEMPLATE_ARGUMENT_LIST7, t_7

#define o_PP_CREATE_TEMPLATE_ARGUMENT_LIST9 \
    o_PP_CREATE_TEMPLATE_ARGUMENT_LIST8, t_8

#define o_PP_CREATE_TEMPLATE_ARGUMENT_LIST10 \
    o_PP_CREATE_TEMPLATE_ARGUMENT_LIST9, t_9

#if o_COMPILER == o_COMPILER_VISUAL_STUDIO
#define o_PP_CREATE_SCOPE(...) \
    o_PP_CAT_P()o_PP_LEFT_PAREN o_PP_CREATE_SCOPE_,o_PP_NARG(__VA_ARGS__) o_PP_RIGHT_PAREN (__VA_ARGS__)
#define o_PP_QUOTE_SCOPE(_namespace_) \
    o_PP_QUOTE o_PP_LEFT_PAREN o_PP_CREATE_SCOPE _namespace_ o_PP_RIGHT_PAREN
#else
#define o_PP_CREATE_SCOPE(...) \
    o_PP_CAT( o_PP_CREATE_SCOPE_, o_PP_NARG(__VA_ARGS__) ) (__VA_ARGS__)
#define o_PP_QUOTE_SCOPE(_namespace_) \
    o_PP_QUOTE( o_PP_CREATE_SCOPE _namespace_ )
#endif

#define o_PP_CREATE_SCOPE_0()
#define o_PP_CREATE_SCOPE_1(_n0_)    _n0_
#define o_PP_CREATE_SCOPE_2(_n0_,_n1_) o_PP_CREATE_SCOPE_1(_n0_)::_n1_
#define o_PP_CREATE_SCOPE_3(_n0_,_n1_,_n2_)    o_PP_CREATE_SCOPE_2(_n0_,_n1_)::_n2_
#define o_PP_CREATE_SCOPE_4(_n0_,_n1_,_n2_,_n3_) o_PP_CREATE_SCOPE_3(_n0_,_n1_,_n2_)::_n3_
#define o_PP_CREATE_SCOPE_5(_n0_,_n1_,_n2_,_n3_,_n4_) o_PP_CREATE_SCOPE_4(_n0_,_n1_,_n2_,_n3_)::_n4_
#define o_PP_CREATE_SCOPE_6(_n0_,_n1_,_n2_,_n3_,_n4_,_n5_) o_PP_CREATE_SCOPE_5(_n0_,_n1_,_n2_,_n3_,_n4_)::_n5_
#define o_PP_CREATE_SCOPE_7(_n0_,_n1_,_n2_,_n3_,_n4_,_n5_,_n6_) o_PP_CREATE_SCOPE_6(_n0_,_n1_,_n2_,_n3_,_n4_,_n5_)::_n6_
#define o_PP_CREATE_SCOPE_8(_n0_,_n1_,_n2_,_n3_,_n4_,_n5_,_n6_,_n7_) o_PP_CREATE_SCOPE_7(_n0_,_n1_,_n2_,_n3_,_n4_,_n5_,_n6_)::_n7_
#define o_PP_CREATE_SCOPE_9(_n0_,_n1_,_n2_,_n3_,_n4_,_n5_,_n6_,_n7_,_n8_) o_PP_CREATE_SCOPE_8(_n0_,_n1_,_n2_,_n3_,_n4_,_n5_,_n6_,_n7_)::_n8_
#define o_PP_CREATE_SCOPE_10(_n0_,_n1_,_n2_,_n3_,_n4_,_n5_,_n6_,_n7_,_n8_,_n9_) o_PP_CREATE_SCOPE_9(_n0_,_n1_,_n2_,_n3_,_n4_,_n5_,_n6_,_n7_,_n8_)::_n9_


#define o_PP_CREATE_DEFAULT_TEMPLATE_TYPES(...) \
    o_PP_CAT(o_PP_CREATE_DEFAULT_TEMPLATE_TYPES_, o_PP_NARG(__VA_ARGS__))()

#define o_PP_CREATE_DEFAULT_TEMPLATE_TYPES_1() typename
#define o_PP_CREATE_DEFAULT_TEMPLATE_TYPES_2() o_PP_CREATE_DEFAULT_TEMPLATE_TYPES_1(), typename
#define o_PP_CREATE_DEFAULT_TEMPLATE_TYPES_3() o_PP_CREATE_DEFAULT_TEMPLATE_TYPES_2(), typename
#define o_PP_CREATE_DEFAULT_TEMPLATE_TYPES_4() o_PP_CREATE_DEFAULT_TEMPLATE_TYPES_3(), typename
#define o_PP_CREATE_DEFAULT_TEMPLATE_TYPES_5() o_PP_CREATE_DEFAULT_TEMPLATE_TYPES_4(), typename
#define o_PP_CREATE_DEFAULT_TEMPLATE_TYPES_6() o_PP_CREATE_DEFAULT_TEMPLATE_TYPES_5(), typename
#define o_PP_CREATE_DEFAULT_TEMPLATE_TYPES_7() o_PP_CREATE_DEFAULT_TEMPLATE_TYPES_6(), typename
#define o_PP_CREATE_DEFAULT_TEMPLATE_TYPES_8() o_PP_CREATE_DEFAULT_TEMPLATE_TYPES_7(), typename
#define o_PP_CREATE_DEFAULT_TEMPLATE_TYPES_9() o_PP_CREATE_DEFAULT_TEMPLATE_TYPES_8(), typename
#define o_PP_CREATE_DEFAULT_TEMPLATE_TYPES_10() o_PP_CREATE_DEFAULT_TEMPLATE_TYPES_9(), typename


#if o_COMPILER == o_COMPILER_VISUAL_STUDIO
#define o_MAX_COMPILER_TEMPLATE_RECURSIVE_CYCLE 400
#elif o_COMPILER == o_COMPILER_GCC
#define o_MAX_COMPILER_TEMPLATE_RECURSIVE_CYCLE 100
#elif o_COMPILER == o_COMPILER_CLANG
#define o_MAX_COMPILER_TEMPLATE_RECURSIVE_CYCLE 100
#else
#error    TODO : define o_MAX_COMPILER_TEMPLATE_RECURSIVE_CYCLE for all supported compilers
#define o_MAX_COMPILER_TEMPLATE_RECURSIVE_CYCLE 400
#endif

#define o_NESTED_TEMPLATE   BOOST_NESTED_TEMPLATE
#define o_NESTED_TYPE       typename


//  ==================================================================================================
//        SHORTCUTS
//  ==================================================================================================

#if o_COMPILER == o_COMPILER_VISUAL_STUDIO

#define o_namespace_begin(...) o_PP_CAT(o_PP_CAT(o_namespace_begin_,o_PP_NARG(__VA_ARGS__)),(__VA_ARGS__))
#define o_namespace_end(...) o_PP_CAT(o_PP_CAT(o_namespace_end_,o_PP_NARG(__VA_ARGS__)),(__VA_ARGS__))
#define o_declare(...) o_PP_CAT(o_PP_CAT(o_declare_, o_PP_NARG(__VA_ARGS__)),(__VA_ARGS__) )
#define o_declareT(...) o_PP_CAT(o_PP_CAT(o_declareT_,o_PP_NARG(__VA_ARGS__)),(__VA_ARGS__))
#define o_fwd(...) o_PP_CAT(o_PP_CAT(o_fwd_, o_PP_NARG(__VA_ARGS__)),(__VA_ARGS__) )
#define o_fwdT(...) o_PP_CAT(o_PP_CAT(o_fwdT_,o_PP_NARG(__VA_ARGS__)),(__VA_ARGS__))
#define o_friend(...) o_PP_CAT(o_PP_CAT(o_friend_,o_PP_NARG(__VA_ARGS__)),(__VA_ARGS__))
#define o_using(...) o_PP_CAT(o_PP_CAT(o_using_,o_PP_NARG(__VA_ARGS__)),(__VA_ARGS__))

#else

#define o_namespace_begin(...) o_PP_CAT(o_namespace_begin_,o_PP_NARG(__VA_ARGS__)) (__VA_ARGS__)
#define o_namespace_end(...) o_PP_CAT(o_namespace_end_,o_PP_NARG(__VA_ARGS__)) (__VA_ARGS__)
#define o_declare(...) o_PP_CAT(o_declare_, o_PP_NARG(__VA_ARGS__)) (__VA_ARGS__)
#define o_declareT(...) o_PP_CAT(o_declareT_,o_PP_NARG(__VA_ARGS__)) (__VA_ARGS__)
#define o_fwd(...) o_PP_CAT(o_fwd_, o_PP_NARG(__VA_ARGS__)) (__VA_ARGS__)
#define o_fwdT(...) o_PP_CAT(o_fwdT_,o_PP_NARG(__VA_ARGS__)) (__VA_ARGS__)
#define o_friend(...) o_PP_CAT(o_friend_,o_PP_NARG(__VA_ARGS__)) (__VA_ARGS__)
#define o_using(...) o_PP_CAT(o_using_,o_PP_NARG(__VA_ARGS__)) (__VA_ARGS__)

#endif



#define o_begin_phantom_namespace() o_root_namespace_open namespace phantom {
#define o_end_phantom_namespace() } o_root_namespace_close

#define o_begin_phantom_detail_namespace()  o_begin_phantom_namespace() namespace detail {
#define o_end_phantom_detail_namespace()    } o_end_phantom_namespace()

#define o_namespace_begin_0()
#define o_namespace_begin_1(n0)  namespace n0 {
#define o_namespace_begin_2(n0,n1)  namespace n0 { namespace n1 {
#define o_namespace_begin_3(n0,n1,n2)  namespace n0 { namespace n1 { namespace n2 {
#define o_namespace_begin_4(n0,n1,n2,n3)  namespace n0 { namespace n1 { namespace n2 { namespace n3 {
#define o_namespace_begin_5(n0,n1,n2,n3,n4)  namespace n0 { namespace n1 { namespace n2 { namespace n3 { namespace n4 {
#define o_namespace_begin_6(n0,n1,n2,n3,n4,n5)  namespace n0 { namespace n1 { namespace n2 { namespace n3 { namespace n4 { namespace n5 {
#define o_namespace_begin_7(n0,n1,n2,n3,n4,n5,n6)  namespace n0 { namespace n1 { namespace n2 { namespace n3 { namespace n4 { namespace n5 { namespace n6 {
#define o_namespace_begin_8(n0,n1,n2,n3,n4,n5,n6,n7)  namespace n0 { namespace n1 { namespace n2 { namespace n3 { namespace n4 { namespace n5 { namespace n6 { namespace n7 {
#define o_namespace_begin_9(n0,n1,n2,n3,n4,n5,n6,n7,n8)  namespace n0 { namespace n1 { namespace n2 { namespace n3 { namespace n4 { namespace n5 { namespace n6 { namespace n7 { namespace n8 {
#define o_namespace_begin_10(n0,n1,n2,n3,n4,n5,n6,n7,n8,n9)  namespace n0 { namespace n1 { namespace n2 { namespace n3 { namespace n4 { namespace n5 { namespace n6 { namespace n7 { namespace n8 { namespace n9 {

#define o_namespace_end_0()
#define o_namespace_end_1(n0) }
#define o_namespace_end_2(n0,n1) }}
#define o_namespace_end_3(n0,n1,n2) }}}
#define o_namespace_end_4(n0,n1,n2,n3) }}}}
#define o_namespace_end_5(n0,n1,n2,n3,n4) }}}}}
#define o_namespace_end_6(n0,n1,n2,n3,n4,n5) }}}}} }
#define o_namespace_end_7(n0,n1,n2,n3,n4,n5,n6) }}}}} }}
#define o_namespace_end_8(n0,n1,n2,n3,n4,n5,n6,n7) }}}}} }}}
#define o_namespace_end_9(n0,n1,n2,n3,n4,n5,n6,n7,n8) }}}}} }}}}
#define o_namespace_end_10(n0,n1,n2,n3,n4,n5,n6,n7,n8,n9) }}}}} }}}}}


#define o_declare_2(t,c) o_namespace_begin_0() t c; o_namespace_end_0() o_reflection_specialize_type_name_of_forward_helper(c)
#define o_declare_3(t,n0,c) o_namespace_begin_1(n0) t c; o_namespace_end_1(n0) o_reflection_specialize_type_name_of_forward_helperN((n0),c)
#define o_declare_4(t,n0,n1,c) o_namespace_begin_2(n0, n1) t c; o_namespace_end_2(n0, n1) o_reflection_specialize_type_name_of_forward_helperN((n0,n1),c)
#define o_declare_5(t,n0,n1,n2,c) o_namespace_begin_3(n0, n1, n2) t c; o_namespace_end_3(n0, n1, n2) o_reflection_specialize_type_name_of_forward_helperN((n0,n1,n2),c)
#define o_declare_6(t,n0,n1,n2,n3,c) o_namespace_begin_4(n0, n1, n2, n3) t c; o_namespace_end_4(n0, n1, n2, n3) o_reflection_specialize_type_name_of_forward_helperN((n0,n1,n2,n3),c)
#define o_declare_7(t,n0,n1,n2,n3,n4,c) o_namespace_begin_5(n0, n1, n2, n3, n4) t c; o_namespace_end_5(n0, n1, n2, n3, n4) o_reflection_specialize_type_name_of_forward_helperN((n0,n1,n2,n3,n4),c)
#define o_declare_8(t,n0,n1,n2,n3,n4,n5,c) o_namespace_begin_6(n0, n1, n2, n3, n4, n5) t c; o_namespace_end_6(n0, n1, n2, n3, n4, n5) o_reflection_specialize_type_name_of_forward_helperN((n0,n1,n2,n3,n4,n5),c)
#define o_declare_9(t,n0,n1,n2,n3,n4,n5,n6,c) o_namespace_begin_7(n0, n1, n2, n3, n4, n5, n6 ) t c; o_namespace_end_7(n0, n1, n2, n3, n4, n5, n6 ) o_reflection_specialize_type_name_of_forward_helperN((n0,n1,n2,n3,n4,n5,n6),c)
#define o_declare_10(t,n0,n1,n2,n3,n4,n5,n6,n7,c) o_namespace_begin_8(n0, n1, n2, n3, n4, n5, n6, n7) t c; o_namespace_end_8(n0, n1, n2, n3, n4, n5, n6, n7) o_reflection_specialize_type_name_of_forward_helperN((n0,n1,n2,n3,n4,n5,n6,n7),c)
#define o_declare_11(t,n0,n1,n2,n3,n4,n5,n6,n7,n8,c) o_namespace_begin_9(n0, n1, n2, n3, n4, n5, n6, n7, n8) t c;  o_namespace_end_9(n0, n1, n2, n3, n4, n5, n6, n7, n8) o_reflection_specialize_type_name_of_forward_helperN((n0,n1,n2,n3,n4,n5,n6,n7,n8),c)
#define o_declare_12(t,n0,n1,n2,n3,n4,n5,n6,n7,n8,n9,c) o_namespace_begin_9(n0, n1, n2, n3, n4, n5, n6, n7, n8, n9) t c; o_namespace_end_9(n0, n1, n2, n3, n4, n5, n6, n7, n8, n9) o_reflection_specialize_type_name_of_forward_helperN((n0,n1,n2,n3,n4,n5,n6,n7,n8,n9),c)

#define o_declare_2(t,c) o_namespace_begin_0() t c; o_namespace_end_0() o_reflection_specialize_type_name_of_forward_helper(c)
#define o_declare_3(t,n0,c) o_namespace_begin_1(n0) t c; o_namespace_end_1(n0) o_reflection_specialize_type_name_of_forward_helperN((n0),c)
#define o_declare_4(t,n0,n1,c) o_namespace_begin_2(n0, n1) t c; o_namespace_end_2(n0, n1) o_reflection_specialize_type_name_of_forward_helperN((n0,n1),c)
#define o_declare_5(t,n0,n1,n2,c) o_namespace_begin_3(n0, n1, n2) t c; o_namespace_end_3(n0, n1, n2) o_reflection_specialize_type_name_of_forward_helperN((n0,n1,n2),c)
#define o_declare_6(t,n0,n1,n2,n3,c) o_namespace_begin_4(n0, n1, n2, n3) t c; o_namespace_end_4(n0, n1, n2, n3) o_reflection_specialize_type_name_of_forward_helperN((n0,n1,n2,n3),c)
#define o_declare_7(t,n0,n1,n2,n3,n4,c) o_namespace_begin_5(n0, n1, n2, n3, n4) t c; o_namespace_end_5(n0, n1, n2, n3, n4) o_reflection_specialize_type_name_of_forward_helperN((n0,n1,n2,n3,n4),c)
#define o_declare_8(t,n0,n1,n2,n3,n4,n5,c) o_namespace_begin_6(n0, n1, n2, n3, n4, n5) t c; o_namespace_end_6(n0, n1, n2, n3, n4, n5) o_reflection_specialize_type_name_of_forward_helperN((n0,n1,n2,n3,n4,n5),c)
#define o_declare_9(t,n0,n1,n2,n3,n4,n5,n6,c) o_namespace_begin_7(n0, n1, n2, n3, n4, n5, n6 ) t c; o_namespace_end_7(n0, n1, n2, n3, n4, n5, n6 ) o_reflection_specialize_type_name_of_forward_helperN((n0,n1,n2,n3,n4,n5,n6),c)
#define o_declare_10(t,n0,n1,n2,n3,n4,n5,n6,n7,c) o_namespace_begin_8(n0, n1, n2, n3, n4, n5, n6, n7) t c; o_namespace_end_8(n0, n1, n2, n3, n4, n5, n6, n7) o_reflection_specialize_type_name_of_forward_helperN((n0,n1,n2,n3,n4,n5,n6,n7),c)
#define o_declare_11(t,n0,n1,n2,n3,n4,n5,n6,n7,n8,c) o_namespace_begin_9(n0, n1, n2, n3, n4, n5, n6, n7, n8) t c;  o_namespace_end_9(n0, n1, n2, n3, n4, n5, n6, n7, n8) o_reflection_specialize_type_name_of_forward_helperN((n0,n1,n2,n3,n4,n5,n6,n7,n8),c)
#define o_declare_12(t,n0,n1,n2,n3,n4,n5,n6,n7,n8,n9,c) o_namespace_begin_9(n0, n1, n2, n3, n4, n5, n6, n7, n8, n9) t c; o_namespace_end_9(n0, n1, n2, n3, n4, n5, n6, n7, n8, n9) o_reflection_specialize_type_name_of_forward_helperN((n0,n1,n2,n3,n4,n5,n6,n7,n8,n9),c)

#if o_COMPILER == o_COMPILER_VISUAL_STUDIO

#define o_declareT_3(t,ts,c) o_namespace_begin_0() template<o_PP_MIX(ts, (o_PP_CAT o_PP_LEFT_PAREN o_PP_CREATE_TEMPLATE_ARGUMENT_LIST, o_PP_CAT(o_PP_NARG, ts) o_PP_RIGHT_PAREN ) )> t c;  o_reflection_specialize_type_name_of_forward_helperTT(ts, (o_PP_CAT o_PP_LEFT_PAREN o_PP_CREATE_TEMPLATE_ARGUMENT_LIST, o_PP_CAT(o_PP_NARG, ts) o_PP_RIGHT_PAREN ), c)
#define o_declareT_4(t,n0,ts,c) o_namespace_begin_1(n0) template<o_PP_MIX(ts, (o_PP_CAT o_PP_LEFT_PAREN o_PP_CREATE_TEMPLATE_ARGUMENT_LIST, o_PP_CAT(o_PP_NARG, ts) o_PP_RIGHT_PAREN ) )> t c;o_namespace_end_1(n0) o_reflection_specialize_type_name_of_forward_helperNTT((n0),ts,(o_PP_CAT o_PP_LEFT_PAREN o_PP_CREATE_TEMPLATE_ARGUMENT_LIST, o_PP_CAT(o_PP_NARG, ts) o_PP_RIGHT_PAREN ), c)
#define o_declareT_5(t,n0,n1,ts,c) o_namespace_begin_2(n0,n1) template<o_PP_MIX(ts, (o_PP_CAT o_PP_LEFT_PAREN o_PP_CREATE_TEMPLATE_ARGUMENT_LIST, o_PP_CAT(o_PP_NARG, ts) o_PP_RIGHT_PAREN ) )> t c; o_namespace_end_2(n0,n1) o_reflection_specialize_type_name_of_forward_helperNTT((n0,n1), ts,(o_PP_CAT o_PP_LEFT_PAREN o_PP_CREATE_TEMPLATE_ARGUMENT_LIST, o_PP_CAT(o_PP_NARG, ts) o_PP_RIGHT_PAREN ),c)
#define o_declareT_6(t,n0,n1,n2,ts,c) o_namespace_begin_3(n0,n1,n2) template<o_PP_MIX(ts, (o_PP_CAT o_PP_LEFT_PAREN o_PP_CREATE_TEMPLATE_ARGUMENT_LIST, o_PP_CAT(o_PP_NARG, ts) o_PP_RIGHT_PAREN ) )> t c; o_namespace_end_3(n0,n1,n2) o_reflection_specialize_type_name_of_forward_helperNTT((n0,n1,n2), ts,(o_PP_CAT o_PP_LEFT_PAREN o_PP_CREATE_TEMPLATE_ARGUMENT_LIST, o_PP_CAT(o_PP_NARG, ts) o_PP_RIGHT_PAREN ),c)
#define o_declareT_7(t,n0,n1,n2,n3,ts,c) o_namespace_begin_4(n0,n1,n2,n3) template<o_PP_MIX(ts, (o_PP_CAT o_PP_LEFT_PAREN o_PP_CREATE_TEMPLATE_ARGUMENT_LIST, o_PP_CAT(o_PP_NARG, ts) o_PP_RIGHT_PAREN ) )> t c; o_namespace_end_4(n0,n1,n2,n3) o_reflection_specialize_type_name_of_forward_helperNTT((n0,n1,n2,n3), ts,(o_PP_CAT o_PP_LEFT_PAREN o_PP_CREATE_TEMPLATE_ARGUMENT_LIST, o_PP_CAT(o_PP_NARG, ts) o_PP_RIGHT_PAREN ),c)
#define o_declareT_8(t,n0,n1,n2,n3,n4,ts,c)  o_namespace_begin_5(n0,n1,n2,n3,n4) template<o_PP_MIX(ts, (o_PP_CAT o_PP_LEFT_PAREN o_PP_CREATE_TEMPLATE_ARGUMENT_LIST, o_PP_CAT(o_PP_NARG, ts) o_PP_RIGHT_PAREN ) )> t c; o_namespace_end_5(n0,n1,n2,n3,n4)  o_reflection_specialize_type_name_of_forward_helperNTT((n0,n1,n2,n3,n4), ts,(o_PP_CAT o_PP_LEFT_PAREN o_PP_CREATE_TEMPLATE_ARGUMENT_LIST, o_PP_CAT(o_PP_NARG, ts) o_PP_RIGHT_PAREN ),c)
#define o_declareT_9(t,n0,n1,n2,n3,n4,n5,ts,c) o_namespace_begin_6(n0,n1,n2,n3,n4,n5) template<o_PP_MIX(ts, (o_PP_CAT o_PP_LEFT_PAREN o_PP_CREATE_TEMPLATE_ARGUMENT_LIST, o_PP_CAT(o_PP_NARG, ts) o_PP_RIGHT_PAREN ) )> t c; o_namespace_end_6(n0,n1,n2,n3,n4,n5)  o_reflection_specialize_type_name_of_forward_helperNTT((n0,n1,n2,n3,n4,n5), ts,(o_PP_CAT o_PP_LEFT_PAREN o_PP_CREATE_TEMPLATE_ARGUMENT_LIST, o_PP_CAT(o_PP_NARG, ts) o_PP_RIGHT_PAREN ),c)
#define o_declareT_10(t,n0,n1,n2,n3,n4,n5,n6,ts,c) o_namespace_begin_7(n0,n1,n2,n3,n4,n5,n6) template<o_PP_MIX(ts, (o_PP_CAT o_PP_LEFT_PAREN o_PP_CREATE_TEMPLATE_ARGUMENT_LIST, o_PP_CAT(o_PP_NARG, ts) o_PP_RIGHT_PAREN ) )> t c; o_namespace_end_7(n0,n1,n2,n3,n4,n5,n6)  o_reflection_specialize_type_name_of_forward_helperNTT((n0,n1,n2,n3,n4,n5,n6), ts,(o_PP_CAT o_PP_LEFT_PAREN o_PP_CREATE_TEMPLATE_ARGUMENT_LIST, o_PP_CAT(o_PP_NARG, ts) o_PP_RIGHT_PAREN ),c)
#define o_declareT_11(t,n0,n1,n2,n3,n4,n5,n6,n7,ts,c) o_namespace_begin_8(n0,n1,n2,n3,n4,n5,n6,n7) template<o_PP_MIX(ts, (o_PP_CAT o_PP_LEFT_PAREN o_PP_CREATE_TEMPLATE_ARGUMENT_LIST, o_PP_CAT(o_PP_NARG, ts) o_PP_RIGHT_PAREN ) )> t c; o_namespace_end_8(n0,n1,n2,n3,n4,n5,n6,n7)  o_reflection_specialize_type_name_of_forward_helperNTT((n0,n1,n2,n3,n4,n5,n6,n7), ts,(o_PP_CAT o_PP_LEFT_PAREN o_PP_CREATE_TEMPLATE_ARGUMENT_LIST, o_PP_CAT(o_PP_NARG, ts) o_PP_RIGHT_PAREN ),c)
#define o_declareT_12(t,n0,n1,n2,n3,n4,n5,n6,n7,n8,ts,c) o_namespace_begin_9(n0,n1,n2,n3,n4,n5,n6,n7,n8) { template<o_PP_MIX(ts, (o_PP_CAT o_PP_LEFT_PAREN o_PP_CREATE_TEMPLATE_ARGUMENT_LIST, o_PP_CAT(o_PP_NARG, ts) o_PP_RIGHT_PAREN ) )> t c; o_namespace_end_9(n0,n1,n2,n3,n4,n5,n6,n7,n8)  o_reflection_specialize_type_name_of_forward_helperNTT((n0,n1,n2,n3,n4,n5,n6,n7,n8), ts,(o_PP_CAT o_PP_LEFT_PAREN o_PP_CREATE_TEMPLATE_ARGUMENT_LIST, o_PP_CAT(o_PP_NARG, ts) o_PP_RIGHT_PAREN ),c)
#define o_declareT_13(t,n0,n1,n2,n3,n4,n5,n6,n7,n8,n9,ts,c) o_namespace_begin_10(n0,n1,n2,n3,n4,n5,n6,n7,n8,n9) { template<o_PP_MIX(ts, (o_PP_CAT o_PP_LEFT_PAREN o_PP_CREATE_TEMPLATE_ARGUMENT_LIST, o_PP_CAT(o_PP_NARG, ts) o_PP_RIGHT_PAREN ) )> t c; o_namespace_end_10(n0,n1,n2,n3,n4,n5,n6,n7,n8,n9)  o_reflection_specialize_type_name_of_forward_helperNTT((n0,n1,n2,n3,n4,n5,n6,n7,n8,n9), ts,(o_PP_CAT o_PP_LEFT_PAREN o_PP_CREATE_TEMPLATE_ARGUMENT_LIST, o_PP_CAT(o_PP_NARG, ts) o_PP_RIGHT_PAREN ),c)

#else

#define o_declareT_3(t,ts,c) o_namespace_begin_0() template<o_PP_MIX(ts, (o_PP_CAT( o_PP_CREATE_TEMPLATE_ARGUMENT_LIST, o_PP_NARG ts ) ) )> t c;  o_reflection_specialize_type_name_of_forward_helperTT(ts, (o_PP_CAT( o_PP_CREATE_TEMPLATE_ARGUMENT_LIST, o_PP_NARG ts ) ), c)
#define o_declareT_4(t,n0,ts,c) o_namespace_begin_1(n0) template<o_PP_MIX(ts, (o_PP_CAT( o_PP_CREATE_TEMPLATE_ARGUMENT_LIST, o_PP_NARG ts ) ) )> t c;o_namespace_end_1(n0) o_reflection_specialize_type_name_of_forward_helperNTT((n0),ts,(o_PP_CAT( o_PP_CREATE_TEMPLATE_ARGUMENT_LIST, o_PP_NARG ts ) ), c)
#define o_declareT_5(t,n0,n1,ts,c) o_namespace_begin_2(n0,n1) template<o_PP_MIX(ts, (o_PP_CAT( o_PP_CREATE_TEMPLATE_ARGUMENT_LIST, o_PP_NARG ts ) ) )> t c; o_namespace_end_2(n0,n1) o_reflection_specialize_type_name_of_forward_helperNTT((n0,n1), ts,(o_PP_CAT( o_PP_CREATE_TEMPLATE_ARGUMENT_LIST, o_PP_NARG ts ) ),c)
#define o_declareT_6(t,n0,n1,n2,ts,c) o_namespace_begin_3(n0,n1,n2) template<o_PP_MIX(ts, (o_PP_CAT( o_PP_CREATE_TEMPLATE_ARGUMENT_LIST, o_PP_NARG ts ) ) )> t c; o_namespace_end_3(n0,n1,n2) o_reflection_specialize_type_name_of_forward_helperNTT((n0,n1,n2), ts,(o_PP_CAT( o_PP_CREATE_TEMPLATE_ARGUMENT_LIST, o_PP_NARG ts ) ),c)
#define o_declareT_7(t,n0,n1,n2,n3,ts,c) o_namespace_begin_4(n0,n1,n2,n3) template<o_PP_MIX(ts, (o_PP_CAT( o_PP_CREATE_TEMPLATE_ARGUMENT_LIST, o_PP_NARG ts ) ) )> t c; o_namespace_end_4(n0,n1,n2,n3) o_reflection_specialize_type_name_of_forward_helperNTT((n0,n1,n2,n3), ts,(o_PP_CAT( o_PP_CREATE_TEMPLATE_ARGUMENT_LIST, o_PP_NARG ts ) ),c)
#define o_declareT_8(t,n0,n1,n2,n3,n4,ts,c)  o_namespace_begin_5(n0,n1,n2,n3,n4) template<o_PP_MIX(ts, (o_PP_CAT( o_PP_CREATE_TEMPLATE_ARGUMENT_LIST, o_PP_NARG ts ) ) )> t c; o_namespace_end_5(n0,n1,n2,n3,n4)  o_reflection_specialize_type_name_of_forward_helperNTT((n0,n1,n2,n3,n4), ts,(o_PP_CAT( o_PP_CREATE_TEMPLATE_ARGUMENT_LIST, o_PP_NARG ts ) ),c)
#define o_declareT_9(t,n0,n1,n2,n3,n4,n5,ts,c) o_namespace_begin_6(n0,n1,n2,n3,n4,n5) template<o_PP_MIX(ts, (o_PP_CAT( o_PP_CREATE_TEMPLATE_ARGUMENT_LIST, o_PP_NARG ts ) ) )> t c; o_namespace_end_6(n0,n1,n2,n3,n4,n5)  o_reflection_specialize_type_name_of_forward_helperNTT((n0,n1,n2,n3,n4,n5), ts,(o_PP_CAT( o_PP_CREATE_TEMPLATE_ARGUMENT_LIST, o_PP_NARG ts ) ),c)
#define o_declareT_10(t,n0,n1,n2,n3,n4,n5,n6,ts,c) o_namespace_begin_7(n0,n1,n2,n3,n4,n5,n6) template<o_PP_MIX(ts, (o_PP_CAT( o_PP_CREATE_TEMPLATE_ARGUMENT_LIST, o_PP_NARG ts ) ) )> t c; o_namespace_end_7(n0,n1,n2,n3,n4,n5,n6)  o_reflection_specialize_type_name_of_forward_helperNTT((n0,n1,n2,n3,n4,n5,n6), ts,(o_PP_CAT( o_PP_CREATE_TEMPLATE_ARGUMENT_LIST, o_PP_NARG ts ) ),c)
#define o_declareT_11(t,n0,n1,n2,n3,n4,n5,n6,n7,ts,c) o_namespace_begin_8(n0,n1,n2,n3,n4,n5,n6,n7) template<o_PP_MIX(ts, (o_PP_CAT( o_PP_CREATE_TEMPLATE_ARGUMENT_LIST, o_PP_NARG ts ) ) )> t c; o_namespace_end_8(n0,n1,n2,n3,n4,n5,n6,n7)  o_reflection_specialize_type_name_of_forward_helperNTT((n0,n1,n2,n3,n4,n5,n6,n7), ts,(o_PP_CAT( o_PP_CREATE_TEMPLATE_ARGUMENT_LIST, o_PP_NARG ts ) ),c)
#define o_declareT_12(t,n0,n1,n2,n3,n4,n5,n6,n7,n8,ts,c) o_namespace_begin_9(n0,n1,n2,n3,n4,n5,n6,n7,n8) { template<o_PP_MIX(ts, (o_PP_CAT( o_PP_CREATE_TEMPLATE_ARGUMENT_LIST, o_PP_NARG ts ) ) )> t c; o_namespace_end_9(n0,n1,n2,n3,n4,n5,n6,n7,n8)  o_reflection_specialize_type_name_of_forward_helperNTT((n0,n1,n2,n3,n4,n5,n6,n7,n8), ts,(o_PP_CAT( o_PP_CREATE_TEMPLATE_ARGUMENT_LIST, o_PP_NARG ts ) ),c)
#define o_declareT_13(t,n0,n1,n2,n3,n4,n5,n6,n7,n8,n9,ts,c) o_namespace_begin_10(n0,n1,n2,n3,n4,n5,n6,n7,n8,n9) { template<o_PP_MIX(ts, (o_PP_CAT( o_PP_CREATE_TEMPLATE_ARGUMENT_LIST, o_PP_NARG ts ) ) )> t c; o_namespace_end_10(n0,n1,n2,n3,n4,n5,n6,n7,n8,n9)  o_reflection_specialize_type_name_of_forward_helperNTT((n0,n1,n2,n3,n4,n5,n6,n7,n8,n9), ts,(o_PP_CAT( o_PP_CREATE_TEMPLATE_ARGUMENT_LIST, o_PP_NARG ts ) ),c)

#endif

#define o_fwd_2(t,c) o_namespace_begin_0() t c; o_namespace_end_0()
#define o_fwd_3(t,n0,c) o_namespace_begin_1(n0) t c; o_namespace_end_1(n0)
#define o_fwd_4(t,n0,n1,c) o_namespace_begin_2(n0, n1) t c; o_namespace_end_2(n0, n1)
#define o_fwd_5(t,n0,n1,n2,c) o_namespace_begin_3(n0, n1, n2) t c; o_namespace_end_3(n0, n1, n2)
#define o_fwd_6(t,n0,n1,n2,n3,c) o_namespace_begin_4(n0, n1, n2, n3) t c; o_namespace_end_4(n0, n1, n2, n3)
#define o_fwd_7(t,n0,n1,n2,n3,n4,c) o_namespace_begin_5(n0, n1, n2, n3, n4) t c; o_namespace_end_5(n0, n1, n2, n3, n4)
#define o_fwd_8(t,n0,n1,n2,n3,n4,n5,c) o_namespace_begin_6(n0, n1, n2, n3, n4, n5) t c; o_namespace_end_6(n0, n1, n2, n3, n4, n5)
#define o_fwd_9(t,n0,n1,n2,n3,n4,n5,n6,c) o_namespace_begin_7(n0, n1, n2, n3, n4, n5, n6 ) t c; o_namespace_end_7(n0, n1, n2, n3, n4, n5, n6 )
#define o_fwd_10(t,n0,n1,n2,n3,n4,n5,n6,n7,c) o_namespace_begin_8(n0, n1, n2, n3, n4, n5, n6, n7) t c; o_namespace_end_8(n0, n1, n2, n3, n4, n5, n6, n7)
#define o_fwd_11(t,n0,n1,n2,n3,n4,n5,n6,n7,n8,c) o_namespace_begin_9(n0, n1, n2, n3, n4, n5, n6, n7, n8) t c;  o_namespace_end_9(n0, n1, n2, n3, n4, n5, n6, n7, n8)
#define o_fwd_12(t,n0,n1,n2,n3,n4,n5,n6,n7,n8,n9,c) o_namespace_begin_9(n0, n1, n2, n3, n4, n5, n6, n7, n8, n9) t c; o_namespace_end_9(n0, n1, n2, n3, n4, n5, n6, n7, n8, n9)

#if o_COMPILER == o_COMPILER_VISUAL_STUDIO

#   define o_fwdT_3(t,ts,c) o_namespace_begin_0() template<o_PP_MIX(ts, (o_PP_CAT o_PP_LEFT_PAREN o_PP_CREATE_TEMPLATE_ARGUMENT_LIST, o_PP_CAT(o_PP_NARG, ts) o_PP_RIGHT_PAREN ) )> t c;
#   define o_fwdT_4(t,n0,ts,c) o_namespace_begin_1(n0) template<o_PP_MIX(ts, (o_PP_CAT o_PP_LEFT_PAREN o_PP_CREATE_TEMPLATE_ARGUMENT_LIST, o_PP_CAT(o_PP_NARG, ts) o_PP_RIGHT_PAREN ) )> t c;o_namespace_end_1(n0)
#   define o_fwdT_5(t,n0,n1,ts,c) o_namespace_begin_2(n0,n1) template<o_PP_MIX(ts, (o_PP_CAT o_PP_LEFT_PAREN o_PP_CREATE_TEMPLATE_ARGUMENT_LIST, o_PP_CAT(o_PP_NARG, ts) o_PP_RIGHT_PAREN ) )> t c; o_namespace_end_2(n0,n1)
#   define o_fwdT_6(t,n0,n1,n2,ts,c) o_namespace_begin_3(n0,n1,n2) template<o_PP_MIX(ts, (o_PP_CAT o_PP_LEFT_PAREN o_PP_CREATE_TEMPLATE_ARGUMENT_LIST, o_PP_CAT(o_PP_NARG, ts) o_PP_RIGHT_PAREN ) )> t c; o_namespace_end_3(n0,n1,n2)
#   define o_fwdT_7(t,n0,n1,n2,n3,ts,c) o_namespace_begin_4(n0,n1,n2,n3) template<o_PP_MIX(ts, (o_PP_CAT o_PP_LEFT_PAREN o_PP_CREATE_TEMPLATE_ARGUMENT_LIST, o_PP_CAT(o_PP_NARG, ts) o_PP_RIGHT_PAREN ) )> t c; o_namespace_end_4(n0,n1,n2,n3)
#   define o_fwdT_8(t,n0,n1,n2,n3,n4,ts,c)  o_namespace_begin_5(n0,n1,n2,n3,n4) template<o_PP_MIX(ts, (o_PP_CAT o_PP_LEFT_PAREN o_PP_CREATE_TEMPLATE_ARGUMENT_LIST, o_PP_CAT(o_PP_NARG, ts) o_PP_RIGHT_PAREN ) )> t c; o_namespace_end_5(n0,n1,n2,n3,n4)
#   define o_fwdT_9(t,n0,n1,n2,n3,n4,n5,ts,c) o_namespace_begin_6(n0,n1,n2,n3,n4,n5) template<o_PP_MIX(ts, (o_PP_CAT o_PP_LEFT_PAREN o_PP_CREATE_TEMPLATE_ARGUMENT_LIST, o_PP_CAT(o_PP_NARG, ts) o_PP_RIGHT_PAREN ) )> t c; o_namespace_end_6(n0,n1,n2,n3,n4,n5)
#   define o_fwdT_10(t,n0,n1,n2,n3,n4,n5,n6,ts,c) o_namespace_begin_7(n0,n1,n2,n3,n4,n5,n6) template<o_PP_MIX(ts, (o_PP_CAT o_PP_LEFT_PAREN o_PP_CREATE_TEMPLATE_ARGUMENT_LIST, o_PP_CAT(o_PP_NARG, ts) o_PP_RIGHT_PAREN ) )> t c; o_namespace_end_7(n0,n1,n2,n3,n4,n5,n6)
#   define o_fwdT_11(t,n0,n1,n2,n3,n4,n5,n6,n7,ts,c) o_namespace_begin_8(n0,n1,n2,n3,n4,n5,n6,n7) template<o_PP_MIX(ts, (o_PP_CAT o_PP_LEFT_PAREN o_PP_CREATE_TEMPLATE_ARGUMENT_LIST, o_PP_CAT(o_PP_NARG, ts) o_PP_RIGHT_PAREN ) )> t c; o_namespace_end_8(n0,n1,n2,n3,n4,n5,n6,n7)
#   define o_fwdT_12(t,n0,n1,n2,n3,n4,n5,n6,n7,n8,ts,c) o_namespace_begin_9(n0,n1,n2,n3,n4,n5,n6,n7,n8) { template<o_PP_MIX(ts, (o_PP_CAT o_PP_LEFT_PAREN o_PP_CREATE_TEMPLATE_ARGUMENT_LIST, o_PP_CAT(o_PP_NARG, ts) o_PP_RIGHT_PAREN ) )> t c; o_namespace_end_9(n0,n1,n2,n3,n4,n5,n6,n7,n8)
#   define o_fwdT_13(t,n0,n1,n2,n3,n4,n5,n6,n7,n8,n9,ts,c) o_namespace_begin_10(n0,n1,n2,n3,n4,n5,n6,n7,n8,n9) { template<o_PP_MIX(ts, (o_PP_CAT o_PP_LEFT_PAREN o_PP_CREATE_TEMPLATE_ARGUMENT_LIST, o_PP_CAT(o_PP_NARG, ts) o_PP_RIGHT_PAREN ) )> t c; o_namespace_end_10(n0,n1,n2,n3,n4,n5,n6,n7,n8,n9)


#else

#   define o_fwdT_3(t,ts,c) o_namespace_begin_0() template<o_PP_MIX(ts, (o_PP_CAT( o_PP_CREATE_TEMPLATE_ARGUMENT_LIST, o_PP_NARG_FUNC()ts)  ) )> t c;
#   define o_fwdT_4(t,n0,ts,c) o_namespace_begin_1(n0) template<o_PP_MIX(ts, (o_PP_CAT( o_PP_CREATE_TEMPLATE_ARGUMENT_LIST, o_PP_NARG_FUNC()ts) )  )> t c;o_namespace_end_1(n0)
#   define o_fwdT_5(t,n0,n1,ts,c) o_namespace_begin_2(n0,n1) template<o_PP_MIX(ts, (o_PP_CAT( o_PP_CREATE_TEMPLATE_ARGUMENT_LIST, o_PP_NARG_FUNC()ts) ) )> t c; o_namespace_end_2(n0,n1)
#   define o_fwdT_6(t,n0,n1,n2,ts,c) o_namespace_begin_3(n0,n1,n2) template<o_PP_MIX(ts, (o_PP_CAT( o_PP_CREATE_TEMPLATE_ARGUMENT_LIST, o_PP_NARG_FUNC()ts) ) )> t c; o_namespace_end_3(n0,n1,n2)
#   define o_fwdT_7(t,n0,n1,n2,n3,ts,c) o_namespace_begin_4(n0,n1,n2,n3) template<o_PP_MIX(ts, (o_PP_CAT( o_PP_CREATE_TEMPLATE_ARGUMENT_LIST, o_PP_NARG_FUNC()ts) ) )> t c; o_namespace_end_4(n0,n1,n2,n3)
#   define o_fwdT_8(t,n0,n1,n2,n3,n4,ts,c)  o_namespace_begin_5(n0,n1,n2,n3,n4) template<o_PP_MIX(ts, (o_PP_CAT( o_PP_CREATE_TEMPLATE_ARGUMENT_LIST, o_PP_NARG_FUNC()ts) ) )> t c; o_namespace_end_5(n0,n1,n2,n3,n4)
#   define o_fwdT_9(t,n0,n1,n2,n3,n4,n5,ts,c) o_namespace_begin_6(n0,n1,n2,n3,n4,n5) template<o_PP_MIX(ts, (o_PP_CAT( o_PP_CREATE_TEMPLATE_ARGUMENT_LIST, o_PP_NARG_FUNC()ts) ) )> t c; o_namespace_end_6(n0,n1,n2,n3,n4,n5)
#   define o_fwdT_10(t,n0,n1,n2,n3,n4,n5,n6,ts,c) o_namespace_begin_7(n0,n1,n2,n3,n4,n5,n6) template<o_PP_MIX(ts, (o_PP_CAT( o_PP_CREATE_TEMPLATE_ARGUMENT_LIST, o_PP_NARG_FUNC()ts) ) )> t c; o_namespace_end_7(n0,n1,n2,n3,n4,n5,n6)
#   define o_fwdT_11(t,n0,n1,n2,n3,n4,n5,n6,n7,ts,c) o_namespace_begin_8(n0,n1,n2,n3,n4,n5,n6,n7) template<o_PP_MIX(ts, (o_PP_CAT( o_PP_CREATE_TEMPLATE_ARGUMENT_LIST, o_PP_NARG_FUNC()ts) ) )> t c; o_namespace_end_8(n0,n1,n2,n3,n4,n5,n6,n7)
#   define o_fwdT_12(t,n0,n1,n2,n3,n4,n5,n6,n7,n8,ts,c) o_namespace_begin_9(n0,n1,n2,n3,n4,n5,n6,n7,n8) { template<o_PP_MIX(ts, (o_PP_CAT( o_PP_CREATE_TEMPLATE_ARGUMENT_LIST, o_PP_NARG_FUNC()ts) ) )> t c; o_namespace_end_9(n0,n1,n2,n3,n4,n5,n6,n7,n8)
#   define o_fwdT_13(t,n0,n1,n2,n3,n4,n5,n6,n7,n8,n9,ts,c) o_namespace_begin_10(n0,n1,n2,n3,n4,n5,n6,n7,n8,n9) { template<o_PP_MIX(ts, (o_PP_CAT( o_PP_CREATE_TEMPLATE_ARGUMENT_LIST, o_PP_NARG_FUNC()ts) ) )> t c; o_namespace_end_10(n0,n1,n2,n3,n4,n5,n6,n7,n8,n9)
 
#endif

#define o_using_1(c) using o_root_namespace::c;
#define o_using_2(n0, c) using o_root_namespace::n0::c;
#define o_using_3(n0,n1,c) using o_root_namespace::n0::n1::c;
#define o_using_4(n0,n1,n2,c) using o_root_namespace::n0::n1::n2::c;
#define o_using_5(n0,n1,n2,n3, c) using o_root_namespace::n0::n1::n2::n3::c;
#define o_using_6(n0,n1,n2,n3,n4, c) using o_root_namespace::n0::n1::n2::n3::n4::c;
#define o_using_7(n0,n1,n2,n3,n4,n5, c) using o_root_namespace::n0::n1::n2::n3::n4::n5::c;
#define o_using_8(n0,n1,n2,n3,n4,n5,n6, c) using o_root_namespace::n0::n1::n2::n3::n4::n5::n6::c;
#define o_using_9(n0,n1,n2,n3,n4,n5,n6,n7, c) using o_root_namespace::n0::n1::n2::n3::n4::n5::n6::n7::c;
#define o_using_10(n0,n1,n2,n3,n4,n5,n6,n7,n8, c) using o_root_namespace::n0::n1::n2::n3::n4::n5::n6::n7::n8::c;
#define o_using_11(n0,n1,n2,n3,n4,n5,n6,n7,n8,n9, c) using o_root_namespace::n0::n1::n2::n3::n4::n5::n6::n7::n8::n9::c;

#define o_friend_2(t, c) friend t o_root_namespace::c;
#define o_friend_3(t, n0, c) friend t o_root_namespace::n0::c;
#define o_friend_4(t, n0,n1,c) friend t o_root_namespace::n0::n1::c;
#define o_friend_5(t, n0,n1,n2,c) friend t o_root_namespace::n0::n1::n2::c;
#define o_friend_6(t, n0,n1,n2,n3, c) friend t o_root_namespace::n0::n1::n2::n3::c;
#define o_friend_7(t, n0,n1,n2,n3,n4, c) friend t o_root_namespace::n0::n1::n2::n3::n4::c;
#define o_friend_8(t, n0,n1,n2,n3,n4,n5, c) friend t o_root_namespace::n0::n1::n2::n3::n4::n5::c;
#define o_friend_9(t, n0,n1,n2,n3,n4,n5,n6, c) friend t o_root_namespace::n0::n1::n2::n3::n4::n5::n6::c;
#define o_friend_10(t, n0,n1,n2,n3,n4,n5,n6,n7, c) friend t o_root_namespace::n0::n1::n2::n3::n4::n5::n6::n7::c;
#define o_friend_11(t, n0,n1,n2,n3,n4,n5,n6,n7,n8, c) friend t o_root_namespace::n0::n1::n2::n3::n4::n5::n6::n7::n8::c;
#define o_friend_12(t, n0,n1,n2,n3,n4,n5,n6,n7,n8,n9, c) friend t o_root_namespace::n0::n1::n2::n3::n4::n5::n6::n7::n8::n9::c;


#define o_rebind(_t_class_)\
    template<typename t_OtherTy>\
    struct rebind\
    {\
        typedef _t_class_<t_OtherTy> other;\
    };


#define o_allow_reflection_access(_type_) o_friend_2(class, reflection, native, TClassType<_type_>)

#define o_specialize_template_bool_value(_type_, _template_, _value_) \
    template<> struct _template_<_type_> { const static bool value = _value_; };




// REFLECTION SPECIFIERS

#define o_virtual                   0x00000001
#define o_abstract                  0x00000002
#define o_reset                     0x00000004
#define o_static                    0x00000008
#define o_no_default_constructor    0x00000010
#define o_transient                 0x00000020
#define o_disable_copy              0x00000040
#define o_readonly                  0x00000080
#define o_no_rtti                   0x00000100
#define o_union_alternative         0x00000200
#define o_protected                 0x00000400
#define o_public                    0x00000800
#define o_native                    0x00001000
#define o_overloaded                0x00002000
#define o_no_reflection             0x00004000
#define o_shared                    0x00008000
#define o_template                  0x00010000
#define o_pod                       0x00020000
#define o_const                     0x00040000
#define o_noconst                   0x00080000
#define o_proxy                     0x00100000
#define o_inherits_allocator        0x00200000
#define o_slot_method               0x00400000
#define o_component                 0x00800000
#define o_owner                     0x01000000
#define o_fixed_size                0x02000000
#define o_custom_modifier_start     0x04000000


#define o_proxy_class \
    o_local_code_TemplateSignature \
    class o_export o_proxy_class_name : public o_global_value_Type

#define o_proxy_class_name o_PP_CAT(o_Name,_phantom_proxy__________)

#define o_match(_flags_, _flag_ ) (((_flags_)&(_flag_)) == _flag_)

#define o_no_arg        ((void**)0)

#define o_foreach        BOOST_FOREACH

// FORCE INLINE

#if (o_COMPILER == o_COMPILER_VISUAL_STUDIO)
#    define o_forceinline    __forceinline

#elif (o_COMPILER == o_COMPILER_GCC)
#    define o_forceinline    __inline __attribute__ ((always_inline))

#else
#    define o_forceinline inline
#endif


// EXCEPTION
#if o__bool__use_exceptions
#    define o_exception_1(_exception_class_) throw _exception_class_()
#    define o_exception_2(_exception_class_, _what_) throw _exception_class_(_what_)
#else
#    define o_exception_1(_exception_class_) o_error(false, o_PP_QUOTE(_exception_class_))
#    define o_exception_2(_exception_class_, _what_) o_error(false, (phantom::string(o_PP_QUOTE(_exception_class_))+o_CS(" : ")+o_CS(_what_)).c_str())
#endif

#if o_COMPILER == o_COMPILER_VISUAL_STUDIO
#define o_exception(...) o_PP_CAT(o_PP_CAT(o_exception_, o_PP_NARG(__VA_ARGS__)),(__VA_ARGS__))
#else
#define o_exception(...) o_PP_CAT(o_exception_, o_PP_NARG(__VA_ARGS__))(__VA_ARGS__)
#endif
// DESTRUCTOR SPECIFIERS
#define o_destructor

#define o_Get(SingletonClass) SingletonClass::Singleton()



#define o_L()                    L

#if defined(_UNICODE)
#    define o_CS(_str_)                o_PP_CAT(L,o_PP_MACRO_CYCLE_L3(_str_))
#    define o_CC(_char_)                o_PP_CAT(L,o_PP_MACRO_CYCLE_L3(_char_))
#    define o_std_cout                ::std::wcout
#    define o_std_endl                ::std::endl
#else
#    define o_CS(_str_)                _str_
#    define o_CC(_char_)                _char_
#    define o_std_cout                ::std::cout
#    define o_std_endl                ::std::endl
#endif

// COMPILER SPECIFIC C FUNCTIONS
#include <phantom/def_cfunctions.h>

#define o_CS_L1(_str_)            o_CS(_str_)
#define o_CC_L1(_char_)            o_CC(_char_)
#define o_CS_L2(_str_)            o_CS_L1(_str_)
#define o_CC_L2(_char_)            o_CC_L1(_char_)

// FRIEND SPECS

#if (o_COMPILER == o_COMPILER_GCC) || (o_COMPILER == o_COMPILER_CLANG)
#    define o_compiler_specific_friend friend class
#else
#    define o_compiler_specific_friend friend
#endif

// TEMPLATE HELPER

#define o_TT(_t_, ...) o_TT_Bis( _t_, __VA_ARGS__ )
#define o_TT_Bis(_t_, ...) _t_< __VA_ARGS__ >

// C Style Allocation

#define o_malloc(_size_) phantom::custom_malloc(_size_ o_memory_stat_append_arguments)
#define o_realloc(_ptr_,_size_) phantom::custom_realloc(_ptr_, _size_ o_memory_stat_append_arguments )
#define o_free(_ptr_) phantom::custom_free(_ptr_ o_memory_stat_append_arguments)

#if o__bool__enable_allocation_statistics
#    define o_memory_stat_allocator(_type_, ...) phantom::memory::stat_allocator<_type_,__VA_ARGS__>
#else
#    define o_memory_stat_allocator(_type_, ...) __VA_ARGS__
#endif

#define o_dynamic_delete_clean(pObject)        \
    if((pObject) != NULL) \
    { \
    phantom::dynamicDelete(pObject o_memory_stat_append_arguments);  \
    pObject = NULL;\
    }

#define o_dynamic_delete        \
    phantom::extension::detail::dynamic_delete_helper(o_memory_stat_insert_arguments) >>

#define o_profile_begin \
    phantom::uint64 PHANTOM_PROFILE_RESERVED__before = phantom::util::ToolBox::Milliseconds();

#define o_profile_end \
    phantom::uint64 PHANTOM_PROFILE_RESERVED__time = phantom::util::ToolBox::Milliseconds() - PHANTOM_PROFILE_RESERVED__before;\
    std::cerr<<"********************************************************"<<std::endl;\
    std::cerr<<__FUNCTION__<< " : " <<_PROFILE_RESERVED__time<<" ms"<<std::endl;\
    std::cerr<<"********************************************************"<<std::endl;

/*************************************************************************************************
 * ASSERTION & OTHER DEBUG MESSAGES
 *************************************************************************************************/

#define o_static_assert         BOOST_STATIC_ASSERT
#define o_static_assert_msg     BOOST_STATIC_ASSERT_MSG

#define o_unused(var) (void)var


#if o_COMPILER == o_COMPILER_VISUAL_STUDIO
#   define o_assert(...) o_PP_CAT(o_PP_CAT(o_assert_, o_PP_NARG(__VA_ARGS__)),(__VA_ARGS__))
#   define o_warning(...) o_PP_CAT(o_PP_CAT(o_warning_, o_PP_NARG(__VA_ARGS__)),(__VA_ARGS__))
#else
#   define o_assert(...) o_PP_CAT(o_assert_, o_PP_NARG(__VA_ARGS__))(__VA_ARGS__)
#   define o_warning(...) o_PP_CAT(o_warning_, o_PP_NARG(__VA_ARGS__))(__VA_ARGS__)
#endif

#    define o_error(_Expression, _Message, ...)    \
        {(void)( (!!(_Expression)) || (phantom::error BOOST_PREVENT_MACRO_SUBSTITUTION ( #_Expression, _Message, __FILE__, __LINE__), 0) );}

#if (defined(_DEBUG) || defined(DEBUG))

#   define o_warning_1(_Expression)    \
        o_warning_2(_Expression, "no detail about the assertion")

#   define o_warning_2(_Expression, _Message)    \
        {( (!!(_Expression)) || (phantom::warning BOOST_PREVENT_MACRO_SUBSTITUTION ( #_Expression, _Message, __FILE__, __LINE__), 0) );}

#   define o_assert_1(_Expression)             o_assert_2(_Expression, "no detail about the assertion")
#   define o_assert_2(_Expression, _Message)   {( (!!(_Expression)) || (phantom::assertion BOOST_PREVENT_MACRO_SUBSTITUTION ( #_Expression, _Message, __FILE__, __LINE__), 0) );}
#   define o_verify(_Expression, _Message)     o_assert(_Expression, _Message)
#   define o_debug_only(things)                things
#   define o_log(level, format, ...)           ::phantom::log BOOST_PREVENT_MACRO_SUBSTITUTION (level, __FILE__, __LINE__, format, __VA_ARGS__)

#else // _NDEBUG

#   define o_warning(_Expression, _Message, ...)
#   define o_assert_1(_Expression)
#   define o_assert_2(_Expression, _Message, ...)
#   define o_warning_1(_Expression)
#   define o_warning_2(_Expression, _Message, ...)
#   define o_debug_only(thing)
#   define o_verify(_Expression, _Message)     _Expression
#   define o_log(level, format, ...)           ::phantom::log BOOST_PREVENT_MACRO_SUBSTITUTION (level, __FILE__, __LINE__, format, __VA_ARGS__)

#endif // _DEBUG

#define o_assert_not(exp)                   o_assert(NOT(exp))
#define o_assert_default_case()             o_assert(false, "Forgotten Default Case")
#define o_assert_no_implementation()        o_assert(false, "Not Implemented")
#define o_assert_forbidden_call()           o_assert(false, "Call to this method forbidden")


#define o_check_phantom_installed()    o_assert(phantom::Phantom::getState() == Phantom::eState_Installed \
  , "Phantom must be installed. Invoke the phantom guard Phantom(int argc, char* argv[]) in your \
program entry main function to do so. It will synchronize the life time of phantom with your \
a    pplication's life time");

#define    o_check_phantom_setup_step(_setup_step_)\
  o_assert(phantom::Phantom::getSetupStep() > _setup_step_ \
  , "The Phantom step"#_setup_step_"must have been treated before accesing this function. Invoke the phantom guard Phantom(int argc, char* argv[]) in your \
program entry main function to do so. It will synchronize the life time of phantom with your \
application's life time");


/*************************************************************************************************
* DEBUG BREAK 
*************************************************************************************************/

#if o_COMPILER == o_COMPILER_VISUAL_STUDIO
#    define o_debug_execution_break()    __debugbreak()
#elif o_COMPILER == o_COMPILER_GCC
#    define o_debug_execution_break()    __builtin_trap ()
#elif o_COMPILER == o_COMPILER_CLANG
#    define o_debug_execution_break()    __builtin_trap ()
#else
#    error TODO : define o_debug_execution_break for all compilers
#endif


/*************************************************************************************************
 * MISC
 *************************************************************************************************/


// min / max //
#define o_min(a, b) (((a)<(b))?(a):(b))
#define o_max(a, b) (((a)>(b))?(a):(b))

// Mask test helper
#define o_mask_test(_variable_, _value_) ((_variable_ & _value_) == _value_)

#define o_global_value_SetupStepIndex_User_PreInheritance_1    0
#define o_global_value_SetupStepIndex_User_PreInheritance_2    1
#define o_global_value_SetupStepIndex_User_PreInheritance_3    2
#define o_global_value_SetupStepIndex_User_PreInheritance_4    3
#define o_global_value_SetupStepIndex_Inheritance                4  // (reserved)
#define o_global_value_SetupStepIndex_User_PreMembers_1        5
#define o_global_value_SetupStepIndex_User_PreMembers_2        6
#define o_global_value_SetupStepIndex_User_PreMembers_3        7
#define o_global_value_SetupStepIndex_User_PreMembers_4        8
#define o_global_value_SetupStepIndex_Reflection                    9  // (reserved)
#define o_global_value_SetupStepIndex_User_PreStateChart_1        10
#define o_global_value_SetupStepIndex_User_PreStateChart_2        11
#define o_global_value_SetupStepIndex_User_PreStateChart_3        12
#define o_global_value_SetupStepIndex_User_PreStateChart_4        13
#define o_global_value_SetupStepIndex_StateChart                14 // (reserved)
#define o_global_value_SetupStepIndex_User_PostAll_1            15
#define o_global_value_SetupStepIndex_User_PostAll_2            16
#define o_global_value_SetupStepIndex_User_PostAll_3            17
#define o_global_value_SetupStepIndex_User_PostAll_4            18
#define o_global_value_SetupStepIndex_User_PostAll_5            19
#define o_global_value_SetupStepIndex_User_PostAll_6            20
#define o_global_value_SetupStepIndex_User_PostAll_7            21
#define o_global_value_SetupStepIndex_User_PostAll_8            22
#define o_global_value_SetupStepIndex_User_PostAll_9            23
#define o_global_value_SetupStepIndex_User_PostAll_10            24
#define o_global_value_SetupStepIndex_User_PostAll_11            25
#define o_global_value_SetupStepIndex_User_PostAll_12            26
#define o_global_value_SetupStepIndex_User_PostAll_13            27
#define o_global_value_SetupStepIndex_User_PostAll_14            28
#define o_global_value_SetupStepIndex_User_PostAll_15            29
#define o_global_value_SetupStepIndex_User_PostAll_16            30
#define o_global_value_SetupStepIndex_User_Last                31

#define o_global_value_SetupStepBit_User_PreInheritance_1    0x00000001 // 0
#define o_global_value_SetupStepBit_User_PreInheritance_2    0x00000002 // 1
#define o_global_value_SetupStepBit_User_PreInheritance_3    0x00000004 // 2
#define o_global_value_SetupStepBit_User_PreInheritance_4    0x00000008 // 3
#define o_global_value_SetupStepBit_Inheritance            0x00000010 // 4  (reserved)
#define o_global_value_SetupStepBit_User_PreMembers_1        0x00000020 // 5
#define o_global_value_SetupStepBit_User_PreMembers_2        0x00000040 // 6
#define o_global_value_SetupStepBit_User_PreMembers_3        0x00000080 // 7
#define o_global_value_SetupStepBit_User_PreMembers_4        0x00000100 // 8
#define o_global_value_SetupStepBit_Reflection                0x00000200 // 9  (reserved)
#define o_global_value_SetupStepBit_User_PreStateChart_1    0x00000400 // 10
#define o_global_value_SetupStepBit_User_PreStateChart_2    0x00000800 // 11
#define o_global_value_SetupStepBit_User_PreStateChart_3    0x00001000 // 12
#define o_global_value_SetupStepBit_User_PreStateChart_4    0x00002000 // 13
#define o_global_value_SetupStepBit_StateChart                0x00004000 // 14 (reserved)
#define o_global_value_SetupStepBit_User_PostAll_1            0x00008000 // 15
#define o_global_value_SetupStepBit_User_PostAll_2            0x00010000 // 16
#define o_global_value_SetupStepBit_User_PostAll_3            0x00020000 // 17
#define o_global_value_SetupStepBit_User_PostAll_4            0x00040000 // 18
#define o_global_value_SetupStepBit_User_PostAll_5            0x00080000 // 19
#define o_global_value_SetupStepBit_User_PostAll_6            0x00100000 // 20
#define o_global_value_SetupStepBit_User_PostAll_7            0x00200000 // 21
#define o_global_value_SetupStepBit_User_PostAll_8            0x00400000 // 22
#define o_global_value_SetupStepBit_User_PostAll_9            0x00800000 // 23
#define o_global_value_SetupStepBit_User_PostAll_10        0x01000000 // 24
#define o_global_value_SetupStepBit_User_PostAll_11        0x02000000 // 25
#define o_global_value_SetupStepBit_User_PostAll_12        0x04000000 // 26
#define o_global_value_SetupStepBit_User_PostAll_13        0x08000000 // 27
#define o_global_value_SetupStepBit_User_PostAll_14        0x10000000 // 28
#define o_global_value_SetupStepBit_User_PostAll_15        0x20000000 // 29
#define o_global_value_SetupStepBit_User_PostAll_16        0x40000000 // 30
#define o_global_value_SetupStepBit_User_Last                0x80000000 // 31


// Reflection system

// Typedef
#define o_Method o_method
#define o_METHOD o_method

#define o_Attribute o_attribute
#define o_ATTRIBUTE o_attribute

#define o_Signal o_signal
#define o_SIGNAL o_signal

#define o_Accessor o_accessor
#define o_ACCESSOR o_accessor

#define o_Constructor o_constructor
#define o_CONSTRUCTOR o_constructor

#endif // Prerequisites_Macros_h__

