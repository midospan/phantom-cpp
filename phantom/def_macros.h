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

#ifndef o_def_macros_h__
#define o_def_macros_h__

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
#define o_PP_QUOTE_L6(...)    o_PP_QUOTE_L5(__VA_ARGS__)
#define o_PP_QUOTE_L5(...)    o_PP_QUOTE_L4(__VA_ARGS__)
#define o_PP_QUOTE_L4(...)    o_PP_QUOTE_L3(__VA_ARGS__)
#define o_PP_QUOTE_L3(...)    o_PP_QUOTE_L2(__VA_ARGS__)
#define o_PP_QUOTE_L2(...)    o_PP_QUOTE_L1(__VA_ARGS__)
#define o_PP_QUOTE_L1(...)    o_PP_QUOTE_L0(__VA_ARGS__)
#define o_PP_QUOTE_L0(...)    #__VA_ARGS__
#define o_PP_QUOTE(...)        o_PP_QUOTE_L3(__VA_ARGS__)

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

#define o_PP_NARG(...)   o_PP_ARG_N o_PP_LEFT_PAREN __VA_ARGS__##,63,62,61,60,59,58,57,56,55,54,53,52,51,50,49,48,47,46,45,44,43,42,41,40,39,38,37,36,35,34,33,32,31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0 o_PP_RIGHT_PAREN

#define o_PP_1_OR_X(...) o_PP_ARG_N o_PP_LEFT_PAREN __VA_ARGS__##, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,X,X,X,X,X,X,X,X,1,0 o_PP_RIGHT_PAREN

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

#define o_PP_1_OR_X(...) \
    o_PP_1_OR_X_(gcc_specific_C99_adapter,##__VA_ARGS__)

#define o_PP_1_OR_X_(...) \
    o_PP_ARG_N(__VA_ARGS__, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,X,X,X,X,X,X,X,X,1,0,gcc_specific_C99_arg)

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


#define o_PP_IDENTITY(...)\
    __VA_ARGS__

#define _o_PP_IDENTITY(...)\
    _##__VA_ARGS__

#define o_PMM_L3(mmm) o_PMM_L2(mmm)
#define o_PMM_L2(mmm) o_PMM_L1(mmm)
#define o_PMM_L1(mmm) #mmm
#define o_PMM(mmm) o_PMM_L1(mmm)


#define o_PP_POP_FRONT(l0)\
    o_PP_LEFT_PAREN o_PP_POP_FRONT_ARG l0  o_PP_RIGHT_PAREN

#define o_PP_POP_FRONT_ARG(a, ...)\
    __VA_ARGS__

#define o_PP_REPLACE_WITH_DEFAULT_ARGUMENTS_BY_LIST(l0)\
    o_PP_REPLACE_WITH_DEFAULT_ARGUMENTS l0

#define o_PP_REPLACE_WITH_DEFAULT_ARGUMENTS(l0, l1)\
    o_PP_CAT o_PP_LEFT_PAREN o_PP_REPLACE_WITH_DEFAULT_ARGUMENTS_,o_PP_NARG_FUNC()l0 o_PP_RIGHT_PAREN (l0, l1)

#define o_PP_REPLACE_WITH_DEFAULT_ARGUMENTS_1(l0, l1)\
    (o_PP_CAT o_PP_LEFT_PAREN o_PP_REPLACE_WITH_DEFAULT_ARGUMENTS_1_,o_PP_NARG_FUNC()l1 o_PP_RIGHT_PAREN (l0, l1))

#define o_PP_REPLACE_WITH_DEFAULT_ARGUMENTS_2(l0, l1)\
    (o_PP_CAT o_PP_LEFT_PAREN o_PP_REPLACE_WITH_DEFAULT_ARGUMENTS_1_,o_PP_NARG_FUNC()l1 o_PP_RIGHT_PAREN (l0, l1))

#define o_PP_REPLACE_WITH_DEFAULT_ARGUMENTS_3(l0, l1)\
    (o_PP_CAT o_PP_LEFT_PAREN o_PP_REPLACE_WITH_DEFAULT_ARGUMENTS_3_,o_PP_NARG_FUNC()l1 o_PP_RIGHT_PAREN (l0, l1))

#define o_PP_REPLACE_WITH_DEFAULT_ARGUMENTS_4(l0, l1)\
    (o_PP_CAT o_PP_LEFT_PAREN o_PP_REPLACE_WITH_DEFAULT_ARGUMENTS_4_,o_PP_NARG_FUNC()l1 o_PP_RIGHT_PAREN (l0, l1))

#define o_PP_REPLACE_WITH_DEFAULT_ARGUMENTS_5(l0, l1)\
    (o_PP_CAT o_PP_LEFT_PAREN o_PP_REPLACE_WITH_DEFAULT_ARGUMENTS_5_,o_PP_NARG_FUNC()l1 o_PP_RIGHT_PAREN (l0, l1))

#define o_PP_REPLACE_WITH_DEFAULT_ARGUMENTS_6(l0, l1)\
    (o_PP_CAT o_PP_LEFT_PAREN o_PP_REPLACE_WITH_DEFAULT_ARGUMENTS_6_,o_PP_NARG_FUNC()l1 o_PP_RIGHT_PAREN (l0, l1))

#define o_PP_REPLACE_WITH_DEFAULT_ARGUMENTS_7(l0, l1)\
    (o_PP_CAT o_PP_LEFT_PAREN o_PP_REPLACE_WITH_DEFAULT_ARGUMENTS_7_,o_PP_NARG_FUNC()l1 o_PP_RIGHT_PAREN (l0, l1))

#define o_PP_REPLACE_WITH_DEFAULT_ARGUMENTS_8(l0, l1)\
    (o_PP_CAT o_PP_LEFT_PAREN o_PP_REPLACE_WITH_DEFAULT_ARGUMENTS_8_,o_PP_NARG_FUNC()l1 o_PP_RIGHT_PAREN (l0, l1))

#define o_PP_REPLACE_WITH_DEFAULT_ARGUMENTS_9(l0, l1)\
    (o_PP_CAT o_PP_LEFT_PAREN o_PP_REPLACE_WITH_DEFAULT_ARGUMENTS_9_,o_PP_NARG_FUNC()l1 o_PP_RIGHT_PAREN (l0, l1))

#define o_PP_REPLACE_WITH_DEFAULT_ARGUMENTS_1_1(l0, l1) o_PP_IDENTITY l1

#define o_PP_REPLACE_WITH_DEFAULT_ARGUMENTS_2_1(l0, l1) \
    o_PP_ARG_0 l0 , o_PP_REPLACE_WITH_DEFAULT_ARGUMENTS_1_1((o_PP_POP_FRONT_ARG l0), l1)

#define o_PP_REPLACE_WITH_DEFAULT_ARGUMENTS_2_2(l0, l1) o_PP_IDENTITY l1

#define o_PP_REPLACE_WITH_DEFAULT_ARGUMENTS_3_1(l0, l1) \
    o_PP_ARG_0 l0 , o_PP_REPLACE_WITH_DEFAULT_ARGUMENTS_2_1((o_PP_POP_FRONT_ARG l0), l1)

#define o_PP_REPLACE_WITH_DEFAULT_ARGUMENTS_3_2(l0, l1) \
    o_PP_ARG_0 l0 , o_PP_REPLACE_WITH_DEFAULT_ARGUMENTS_2_2((o_PP_POP_FRONT_ARG l0), l1)

#define o_PP_REPLACE_WITH_DEFAULT_ARGUMENTS_3_3(l0, l1) o_PP_IDENTITY l1

#define o_PP_REPLACE_WITH_DEFAULT_ARGUMENTS_4_1(l0, l1)\
    o_PP_ARG_0 l0 , o_PP_REPLACE_WITH_DEFAULT_ARGUMENTS_3_1((o_PP_POP_FRONT_ARG l0), l1)

#define o_PP_REPLACE_WITH_DEFAULT_ARGUMENTS_4_2(l0, l1)\
    o_PP_ARG_0 l0 , o_PP_REPLACE_WITH_DEFAULT_ARGUMENTS_3_2((o_PP_POP_FRONT_ARG l0), l1)

#define o_PP_REPLACE_WITH_DEFAULT_ARGUMENTS_4_3(l0, l1)\
    o_PP_ARG_0 l0 , o_PP_REPLACE_WITH_DEFAULT_ARGUMENTS_3_3((o_PP_POP_FRONT_ARG l0), l1)

#define o_PP_REPLACE_WITH_DEFAULT_ARGUMENTS_4_4(l0, l1) o_PP_IDENTITY l1

#define o_PP_REPLACE_WITH_DEFAULT_ARGUMENTS_5_1(l0, l1) \
    o_PP_ARG_0 l0 , o_PP_REPLACE_WITH_DEFAULT_ARGUMENTS_4_1((o_PP_POP_FRONT_ARG l0), l1)

#define o_PP_REPLACE_WITH_DEFAULT_ARGUMENTS_5_2(l0, l1) \
    o_PP_ARG_0 l0 , o_PP_REPLACE_WITH_DEFAULT_ARGUMENTS_4_2((o_PP_POP_FRONT_ARG l0), l1)

#define o_PP_REPLACE_WITH_DEFAULT_ARGUMENTS_5_3(l0, l1) \
    o_PP_ARG_0 l0 , o_PP_REPLACE_WITH_DEFAULT_ARGUMENTS_4_3((o_PP_POP_FRONT_ARG l0), l1)

#define o_PP_REPLACE_WITH_DEFAULT_ARGUMENTS_5_4(l0, l1) \
    o_PP_ARG_0 l0 , o_PP_REPLACE_WITH_DEFAULT_ARGUMENTS_4_4((o_PP_POP_FRONT_ARG l0), l1)

#define o_PP_REPLACE_WITH_DEFAULT_ARGUMENTS_5_5(l0, l1) o_PP_IDENTITY l1

#define o_PP_REPLACE_WITH_DEFAULT_ARGUMENTS_6_1(l0, l1) \
    o_PP_ARG_0 l0 , o_PP_REPLACE_WITH_DEFAULT_ARGUMENTS_5_1((o_PP_POP_FRONT_ARG l0), l1)

#define o_PP_REPLACE_WITH_DEFAULT_ARGUMENTS_6_2(l0, l1) \
    o_PP_ARG_0 l0 , o_PP_REPLACE_WITH_DEFAULT_ARGUMENTS_5_2((o_PP_POP_FRONT_ARG l0), l1)

#define o_PP_REPLACE_WITH_DEFAULT_ARGUMENTS_6_3(l0, l1) \
    o_PP_ARG_0 l0 , o_PP_REPLACE_WITH_DEFAULT_ARGUMENTS_5_3((o_PP_POP_FRONT_ARG l0), l1)

#define o_PP_REPLACE_WITH_DEFAULT_ARGUMENTS_6_4(l0, l1) \
    o_PP_ARG_0 l0 , o_PP_REPLACE_WITH_DEFAULT_ARGUMENTS_5_4((o_PP_POP_FRONT_ARG l0), l1)

#define o_PP_REPLACE_WITH_DEFAULT_ARGUMENTS_6_5(l0, l1) \
    o_PP_ARG_0 l0 , o_PP_REPLACE_WITH_DEFAULT_ARGUMENTS_5_4((o_PP_POP_FRONT_ARG l0), l1)

#define o_PP_REPLACE_WITH_DEFAULT_ARGUMENTS_6_6(l0, l1) o_PP_IDENTITY l1

#define o_PP_REPLACE_WITH_DEFAULT_ARGUMENTS_7_1(l0, l1) \
    o_PP_ARG_0 l0 , o_PP_REPLACE_WITH_DEFAULT_ARGUMENTS_6_1((o_PP_POP_FRONT_ARG l0), l1)

#define o_PP_REPLACE_WITH_DEFAULT_ARGUMENTS_7_2(l0, l1) \
    o_PP_ARG_0 l0 , o_PP_REPLACE_WITH_DEFAULT_ARGUMENTS_6_2((o_PP_POP_FRONT_ARG l0), l1)

#define o_PP_REPLACE_WITH_DEFAULT_ARGUMENTS_7_3(l0, l1) \
    o_PP_ARG_0 l0 , o_PP_REPLACE_WITH_DEFAULT_ARGUMENTS_6_3((o_PP_POP_FRONT_ARG l0), l1)

#define o_PP_REPLACE_WITH_DEFAULT_ARGUMENTS_7_4(l0, l1) \
    o_PP_ARG_0 l0 , o_PP_REPLACE_WITH_DEFAULT_ARGUMENTS_6_4((o_PP_POP_FRONT_ARG l0), l1)

#define o_PP_REPLACE_WITH_DEFAULT_ARGUMENTS_7_5(l0, l1) \
    o_PP_ARG_0 l0 , o_PP_REPLACE_WITH_DEFAULT_ARGUMENTS_6_5((o_PP_POP_FRONT_ARG l0), l1)

#define o_PP_REPLACE_WITH_DEFAULT_ARGUMENTS_7_6(l0, l1) \
    o_PP_ARG_0 l0 , o_PP_REPLACE_WITH_DEFAULT_ARGUMENTS_6_6((o_PP_POP_FRONT_ARG l0), l1)

#define o_PP_REPLACE_WITH_DEFAULT_ARGUMENTS_7_7(l0, l1) o_PP_IDENTITY l1



#define o_PP_REPLACE_WITH_DEFAULT_ARGUMENTS_8_1(l0, l1) \
    o_PP_ARG_0 l0 , o_PP_REPLACE_WITH_DEFAULT_ARGUMENTS_7_1((o_PP_POP_FRONT_ARG l0), l1)

#define o_PP_REPLACE_WITH_DEFAULT_ARGUMENTS_8_2(l0, l1) \
    o_PP_ARG_0 l0 , o_PP_REPLACE_WITH_DEFAULT_ARGUMENTS_7_2((o_PP_POP_FRONT_ARG l0), l1)

#define o_PP_REPLACE_WITH_DEFAULT_ARGUMENTS_8_3(l0, l1) \
    o_PP_ARG_0 l0 , o_PP_REPLACE_WITH_DEFAULT_ARGUMENTS_7_3((o_PP_POP_FRONT_ARG l0), l1)

#define o_PP_REPLACE_WITH_DEFAULT_ARGUMENTS_8_4(l0, l1) \
    o_PP_ARG_0 l0 , o_PP_REPLACE_WITH_DEFAULT_ARGUMENTS_7_4((o_PP_POP_FRONT_ARG l0), l1)

#define o_PP_REPLACE_WITH_DEFAULT_ARGUMENTS_8_5(l0, l1) \
    o_PP_ARG_0 l0 , o_PP_REPLACE_WITH_DEFAULT_ARGUMENTS_7_5((o_PP_POP_FRONT_ARG l0), l1)

#define o_PP_REPLACE_WITH_DEFAULT_ARGUMENTS_8_6(l0, l1) \
    o_PP_ARG_0 l0 , o_PP_REPLACE_WITH_DEFAULT_ARGUMENTS_7_6((o_PP_POP_FRONT_ARG l0), l1)

#define o_PP_REPLACE_WITH_DEFAULT_ARGUMENTS_8_7(l0, l1) \
    o_PP_ARG_0 l0 , o_PP_REPLACE_WITH_DEFAULT_ARGUMENTS_7_7((o_PP_POP_FRONT_ARG l0), l1)

#define o_PP_REPLACE_WITH_DEFAULT_ARGUMENTS_8_8(l0, l1) o_PP_IDENTITY l1


#define o_PP_REPLACE_WITH_DEFAULT_ARGUMENTS_9_1(l0, l1) \
    o_PP_ARG_0 l0 , o_PP_REPLACE_WITH_DEFAULT_ARGUMENTS_8_1((o_PP_POP_FRONT_ARG l0), l1)

#define o_PP_REPLACE_WITH_DEFAULT_ARGUMENTS_9_2(l0, l1) \
    o_PP_ARG_0 l0 , o_PP_REPLACE_WITH_DEFAULT_ARGUMENTS_8_2((o_PP_POP_FRONT_ARG l0), l1)

#define o_PP_REPLACE_WITH_DEFAULT_ARGUMENTS_9_3(l0, l1) \
    o_PP_ARG_0 l0 , o_PP_REPLACE_WITH_DEFAULT_ARGUMENTS_8_3((o_PP_POP_FRONT_ARG l0), l1)

#define o_PP_REPLACE_WITH_DEFAULT_ARGUMENTS_9_4(l0, l1) \
    o_PP_ARG_0 l0 , o_PP_REPLACE_WITH_DEFAULT_ARGUMENTS_8_4((o_PP_POP_FRONT_ARG l0), l1)

#define o_PP_REPLACE_WITH_DEFAULT_ARGUMENTS_9_5(l0, l1) \
    o_PP_ARG_0 l0 , o_PP_REPLACE_WITH_DEFAULT_ARGUMENTS_8_5((o_PP_POP_FRONT_ARG l0), l1)

#define o_PP_REPLACE_WITH_DEFAULT_ARGUMENTS_9_6(l0, l1) \
    o_PP_ARG_0 l0 , o_PP_REPLACE_WITH_DEFAULT_ARGUMENTS_8_6((o_PP_POP_FRONT_ARG l0), l1)

#define o_PP_REPLACE_WITH_DEFAULT_ARGUMENTS_9_7(l0, l1) \
    o_PP_ARG_0 l0 , o_PP_REPLACE_WITH_DEFAULT_ARGUMENTS_8_7((o_PP_POP_FRONT_ARG l0), l1)

#define o_PP_REPLACE_WITH_DEFAULT_ARGUMENTS_9_8(l0, l1) \
    o_PP_ARG_0 l0 , o_PP_REPLACE_WITH_DEFAULT_ARGUMENTS_8_8((o_PP_POP_FRONT_ARG l0), l1)

#define o_PP_REPLACE_WITH_DEFAULT_ARGUMENTS_9_9(l0, l1) o_PP_IDENTITY l1

#define o_PP_BY_LIST_BIS_2(name, l0)\
    o_PP_BY_LIST_BIS(name, l0)

#define o_PP_BY_LIST_BIS(name, l0)\
            name l0

#define o_PP_BY_LIST(name, l0)\
             o_PP_BY_LIST_BIS_2(name, l0)

#include "macros/PP_ADD_PREFIX_EACH.h"

#define o_PP_ADD_PREFIX_EACH_1(prefix, p0) \
    o_PP_CAT(prefix, p0)

#define o_PP_ADD_PREFIX_EACH_2(prefix, p0, p1) \
    o_PP_ADD_PREFIX_EACH_1(prefix, p0), o_PP_CAT(prefix, p1)

#define o_PP_ADD_PREFIX_EACH_3(prefix, p0, p1, p2) \
    o_PP_ADD_PREFIX_EACH_2(prefix, p0, p1), o_PP_CAT(prefix, p2)

#define o_PP_ADD_PREFIX_EACH_4(prefix, p0, p1, p2, p3) \
    o_PP_ADD_PREFIX_EACH_3(prefix, p0, p1, p2), o_PP_CAT(prefix, p3)

#define o_PP_ADD_PREFIX_EACH_5(prefix, p0, p1, p2, p3, p4) \
    o_PP_ADD_PREFIX_EACH_4(prefix, p0, p1, p2, p3), o_PP_CAT(prefix, p4)

#define o_PP_ADD_PREFIX_EACH_6(prefix, p0, p1, p2, p3, p4, p5) \
    o_PP_ADD_PREFIX_EACH_5(prefix, p0, p1, p2, p3, p4), o_PP_CAT(prefix, p5)

#define o_PP_ADD_PREFIX_EACH_7(prefix, p0, p1, p2, p3, p4, p5, p6) \
    o_PP_ADD_PREFIX_EACH_6(prefix, p0, p1, p2, p3, p4, p5), o_PP_CAT(prefix, p6)

#define o_PP_ADD_PREFIX_EACH_8(prefix, p0, p1, p2, p3, p4, p5, p6, p7) \
    o_PP_ADD_PREFIX_EACH_7(prefix, p0, p1, p2, p3, p4, p5, p6), o_PP_CAT(prefix, p7)

#define o_PP_ADD_PREFIX_EACH_9(prefix, p0, p1, p2, p3, p4, p5, p6, p7, p8) \
    o_PP_ADD_PREFIX_EACH_8(prefix, p0, p1, p2, p3, p4, p5, p6, p7), o_PP_CAT(prefix, p8)

#if o_COMPILER == o_COMPILER_VISUAL_STUDIO
#define o_PP_ADD_SUFFIX_EACH(suffix, ...)\
    o_PP_CAT(o_PP_CAT(o_PP_ADD_SUFFIX_EACH_,o_PP_NARG(__VA_ARGS__)),(suffix,##__VA_ARGS__))
#else
#define o_PP_ADD_SUFFIX_EACH(...) \
    o_PP_CAT_P()o_PP_LEFT_PAREN o_PP_ADD_SUFFIX_EACH_,o_PP_NARG(__VA_ARGS__) o_PP_RIGHT_PAREN (suffix,##__VA_ARGS__)
#endif

#define o_PP_ADD_SUFFIX_EACH_1(suffix, p0) \
    o_PP_CAT(p0, suffix)

#define o_PP_ADD_SUFFIX_EACH_2(suffix, p0, p1) \
    o_PP_ADD_SUFFIX_EACH_1(suffix, p0), o_PP_CAT(p1, suffix)

#define o_PP_ADD_SUFFIX_EACH_3(suffix, p0, p1, p2) \
    o_PP_ADD_SUFFIX_EACH_2(suffix, p0, p1), o_PP_CAT(p2, suffix)

#define o_PP_ADD_SUFFIX_EACH_4(suffix, p0, p1, p2, p3) \
    o_PP_ADD_SUFFIX_EACH_3(suffix, p0, p1, p2), o_PP_CAT(p3, suffix)

#define o_PP_ADD_SUFFIX_EACH_5(suffix, p0, p1, p2, p3, p4) \
    o_PP_ADD_SUFFIX_EACH_4(suffix, p0, p1, p2, p3), o_PP_CAT(p4, suffix)

#define o_PP_ADD_SUFFIX_EACH_6(suffix, p0, p1, p2, p3, p4, p5) \
    o_PP_ADD_SUFFIX_EACH_5(suffix, p0, p1, p2, p3, p4), o_PP_CAT(p5, suffix)

#define o_PP_ADD_SUFFIX_EACH_7(suffix, p0, p1, p2, p3, p4, p5, p6) \
    o_PP_ADD_SUFFIX_EACH_6(suffix, p0, p1, p2, p3, p4, p5), o_PP_CAT(p6, suffix)

#define o_PP_ADD_SUFFIX_EACH_8(suffix, p0, p1, p2, p3, p4, p5, p6, p7) \
    o_PP_ADD_SUFFIX_EACH_7(suffix, p0, p1, p2, p3, p4, p5, p6), o_PP_CAT(p7, suffix)

#define o_PP_ADD_SUFFIX_EACH_9(suffix, p0, p1, p2, p3, p4, p5, p6, p7, p8) \
    o_PP_ADD_SUFFIX_EACH_8(suffix, p0, p1, p2, p3, p4, p5, p6, p7), o_PP_CAT(p8, suffix)


#define o_PP_ADD_PAREN_EACH_LIST(l0)\
    (o_PP_ADD_PAREN_EACH l0)

#if o_COMPILER == o_COMPILER_VISUAL_STUDIO
#define o_PP_ADD_PAREN_EACH(...)\
    o_PP_CAT(o_PP_CAT(o_PP_ADD_PAREN_EACH_,o_PP_NARG(__VA_ARGS__)),(__VA_ARGS__))
#else
#define o_PP_ADD_PAREN_EACH(...) \
    o_PP_CAT_P()o_PP_LEFT_PAREN o_PP_ADD_PAREN_EACH_,o_PP_NARG(__VA_ARGS__) o_PP_RIGHT_PAREN (__VA_ARGS__)
#endif

#define o_PP_ADD_PAREN_EACH_1(p0) \
    (p0)

#define o_PP_ADD_PAREN_EACH_2(p0, p1) \
    o_PP_ADD_PAREN_EACH_1(p0), (p1)

#define o_PP_ADD_PAREN_EACH_3(p0, p1, p2) \
    o_PP_ADD_PAREN_EACH_2(p0, p1), (p2)

#define o_PP_ADD_PAREN_EACH_4(p0, p1, p2, p3) \
    o_PP_ADD_PAREN_EACH_3(p0, p1, p2), (p3)

#define o_PP_ADD_PAREN_EACH_5(p0, p1, p2, p3, p4) \
    o_PP_ADD_PAREN_EACH_4(p0, p1, p2, p3), (p4)

#define o_PP_ADD_PAREN_EACH_6(p0, p1, p2, p3, p4, p5) \
    o_PP_ADD_PAREN_EACH_5(p0, p1, p2, p3, p4), (p5)

#define o_PP_ADD_PAREN_EACH_7(p0, p1, p2, p3, p4, p5, p6) \
    o_PP_ADD_PAREN_EACH_6(p0, p1, p2, p3, p4, p5), (p6)

#define o_PP_ADD_PAREN_EACH_8(p0, p1, p2, p3, p4, p5, p6, p7) \
    o_PP_ADD_PAREN_EACH_7(p0, p1, p2, p3, p4, p5, p6), (p7)

#define o_PP_ADD_PAREN_EACH_9(p0, p1, p2, p3, p4, p5, p6, p7, p8) \
    o_PP_ADD_PAREN_EACH_8(p0, p1, p2, p3, p4, p5, p6, p7), (p8)


#define o_PP_REMOVE_PAREN_EACH_BY_LIST_3(l0)\
    o_PP_REMOVE_PAREN_EACH_BY_LIST_2 l0
#define o_PP_REMOVE_PAREN_EACH_BY_LIST_2(l0)\
    o_PP_REMOVE_PAREN_EACH_BY_LIST l0
#define o_PP_REMOVE_PAREN_EACH_BY_LIST(l0)\
    o_PP_REMOVE_PAREN_EACH l0

#define o_PP_REMOVE_PAREN_EACH_LIST(l0)\
    (o_PP_REMOVE_PAREN_EACH l0)

#if o_COMPILER == o_COMPILER_VISUAL_STUDIO
#define o_PP_REMOVE_PAREN_EACH(...)\
    o_PP_CAT(o_PP_CAT(o_PP_REMOVE_PAREN_EACH_,o_PP_NARG(__VA_ARGS__)),(__VA_ARGS__))
#else
#define o_PP_REMOVE_PAREN_EACH(...) \
    o_PP_CAT_P()o_PP_LEFT_PAREN o_PP_REMOVE_PAREN_EACH_,o_PP_NARG(__VA_ARGS__) o_PP_RIGHT_PAREN (__VA_ARGS__)
#endif

#define o_PP_REMOVE_PAREN_EACH_1(p0) \
    o_PP_IDENTITY p0

#define o_PP_REMOVE_PAREN_EACH_2(p0, p1) \
    o_PP_REMOVE_PAREN_EACH_1(p0), o_PP_IDENTITY p1

#define o_PP_REMOVE_PAREN_EACH_3(p0, p1, p2) \
    o_PP_REMOVE_PAREN_EACH_2(p0, p1), o_PP_IDENTITY p2

#define o_PP_REMOVE_PAREN_EACH_4(p0, p1, p2, p3) \
    o_PP_REMOVE_PAREN_EACH_3(p0, p1, p2), o_PP_IDENTITY p3

#define o_PP_REMOVE_PAREN_EACH_5(p0, p1, p2, p3, p4) \
    o_PP_REMOVE_PAREN_EACH_4(p0, p1, p2, p3), o_PP_IDENTITY p4

#define o_PP_REMOVE_PAREN_EACH_6(p0, p1, p2, p3, p4, p5) \
    o_PP_REMOVE_PAREN_EACH_5(p0, p1, p2, p3, p4), o_PP_IDENTITY p5

#define o_PP_REMOVE_PAREN_EACH_7(p0, p1, p2, p3, p4, p5, p6) \
    o_PP_REMOVE_PAREN_EACH_6(p0, p1, p2, p3, p4, p5), o_PP_IDENTITY p6

#define o_PP_REMOVE_PAREN_EACH_8(p0, p1, p2, p3, p4, p5, p6, p7) \
    o_PP_REMOVE_PAREN_EACH_7(p0, p1, p2, p3, p4, p5, p6), o_PP_IDENTITY p7

#define o_PP_REMOVE_PAREN_EACH_9(p0, p1, p2, p3, p4, p5, p6, p7, p8) \
    o_PP_REMOVE_PAREN_EACH_8(p0, p1, p2, p3, p4, p5, p6, p7), o_PP_IDENTITY p8



#if o_COMPILER == o_COMPILER_VISUAL_STUDIO
#define o_PP_QUOTE_EACH(...)\
    o_PP_CAT_P()o_PP_LEFT_PAREN o_PP_QUOTE_EACH_,o_PP_NARG(__VA_ARGS__) o_PP_RIGHT_PAREN (__VA_ARGS__)
#else
#define o_PP_QUOTE_EACH(...) \
    o_PP_CAT_P()o_PP_LEFT_PAREN o_PP_QUOTE_EACH_,o_PP_NARG(__VA_ARGS__) o_PP_RIGHT_PAREN (__VA_ARGS__)
#endif

#define o_PP_QUOTE_EACH_1(p0) \
    o_PP_QUOTE(p0)

#define o_PP_QUOTE_EACH_2(p0, p1) \
    o_PP_QUOTE_EACH_1(p0), o_PP_QUOTE(p1)

#define o_PP_QUOTE_EACH_3(p0, p1, p2) \
    o_PP_QUOTE_EACH_2(p0, p1), o_PP_QUOTE(p2)

#define o_PP_QUOTE_EACH_4(p0, p1, p2, p3) \
    o_PP_QUOTE_EACH_3(p0, p1, p2), o_PP_QUOTE(p3)

#define o_PP_QUOTE_EACH_5(p0, p1, p2, p3, p4) \
    o_PP_QUOTE_EACH_4(p0, p1, p2, p3), o_PP_QUOTE(p4)

#define o_PP_QUOTE_EACH_6(p0, p1, p2, p3, p4, p5) \
    o_PP_QUOTE_EACH_5(p0, p1, p2, p3, p4), o_PP_QUOTE(p5)

#define o_PP_QUOTE_EACH_7(p0, p1, p2, p3, p4, p5, p6) \
    o_PP_QUOTE_EACH_6(p0, p1, p2, p3, p4, p5), o_PP_QUOTE(p6)

#define o_PP_QUOTE_EACH_8(p0, p1, p2, p3, p4, p5, p6, p7) \
    o_PP_QUOTE_EACH_7(p0, p1, p2, p3, p4, p5, p6), o_PP_QUOTE(p7)

#define o_PP_QUOTE_EACH_9(p0, p1, p2, p3, p4, p5, p6, p7, p8) \
    o_PP_QUOTE_EACH_8(p0, p1, p2, p3, p4, p5, p6, p7), o_PP_QUOTE(p8)

#define o_PP_SURROUND_L1(p, s, arg)\
    p##arg##s

#define o_PP_SURROUND(p, s, arg)\
    o_PP_SURROUND_L1(p, s, arg)

#define o_PP_SURROUND_EACH_BIS(...)\
    o_PP_SURROUND_EACH o_PP_LEFT_PAREN __VA_ARGS__ o_PP_RIGHT_PAREN

#define o_PP_SURROUND_EACH_BY_LIST(l0)\
    o_PP_SURROUND_EACH l0

#define o_PP_SURROUND_EACH_BY_LIST_2(l0) o_PP_SURROUND_EACH_BY_LIST l0

#define o_PP_SURROUND_EACH_BY_LIST_3(l0) o_PP_SURROUND_EACH_BY_LIST_2 l0
#define o_PP_SURROUND_EACH_BY_LIST_4(l0) o_PP_SURROUND_EACH_BY_LIST_3 l0
#define o_PP_SURROUND_EACH_BY_LIST_5(l0) o_PP_SURROUND_EACH_BY_LIST_4 l0

#if o_COMPILER == o_COMPILER_VISUAL_STUDIO
#define o_PP_SURROUND_EACH(p, s, ...)\
    o_PP_CAT_P()o_PP_LEFT_PAREN o_PP_SURROUND_EACH_,o_PP_NARG(__VA_ARGS__) o_PP_RIGHT_PAREN (p, s,##__VA_ARGS__)
#else
#define o_PP_SURROUND_EACH(p, s, ...) \
    o_PP_CAT_P()o_PP_LEFT_PAREN o_PP_SURROUND_EACH_,o_PP_NARG(__VA_ARGS__) o_PP_RIGHT_PAREN (p, s,##__VA_ARGS__)
#endif
#define o_PP_SURROUND_EACH_1(p, s, p0) \
    o_PP_SURROUND(p, s, p0)

#define o_PP_SURROUND_EACH_2(p, s, p0, p1) \
    o_PP_SURROUND_EACH_1(p, s, p0), o_PP_SURROUND(p, s, p1)

#define o_PP_SURROUND_EACH_3(p, s, p0, p1, p2) \
    o_PP_SURROUND_EACH_2(p, s, p0, p1), o_PP_SURROUND(p, s, p2)

#define o_PP_SURROUND_EACH_4(p, s, p0, p1, p2, p3) \
    o_PP_SURROUND_EACH_3(p, s, p0, p1, p2), o_PP_SURROUND(p, s, p3)

#define o_PP_SURROUND_EACH_5(p, s, p0, p1, p2, p3, p4) \
    o_PP_SURROUND_EACH_4(p, s, p0, p1, p2, p3), o_PP_SURROUND(p, s, p4)

#define o_PP_SURROUND_EACH_6(p, s, p0, p1, p2, p3, p4, p5) \
    o_PP_SURROUND_EACH_5(p, s, p0, p1, p2, p3, p4), o_PP_SURROUND(p, s, p5)

#define o_PP_SURROUND_EACH_7(p, s, p0, p1, p2, p3, p4, p5, p6) \
    o_PP_SURROUND_EACH_6(p, s, p0, p1, p2, p3, p4, p5), o_PP_SURROUND(p, s, p6)

#define o_PP_SURROUND_EACH_8(p, s, p0, p1, p2, p3, p4, p5, p6, p7) \
    o_PP_SURROUND_EACH_7(p, s, p0, p1, p2, p3, p4, p5, p6), o_PP_SURROUND(p, s, p7)

#define o_PP_SURROUND_EACH_9(p, s, p0, p1, p2, p3, p4, p5, p6, p7, p8) \
    o_PP_SURROUND_EACH_8(p, s, p0, p1, p2, p3, p4, p5, p6, p7), o_PP_SURROUND(p, s, p8)


//#pragma message(o_PP_QUOTE(o_PP_POP_FRONT((a, b, c, d, e))))

#define o_create_template_default_arguments(template_types, default_args)\
    o_PP_BY_LIST(o_PP_REMOVE_PAREN_EACH, o_PP_BY_LIST(o_PP_REPLACE_WITH_DEFAULT_ARGUMENTS, (/*4*/o_PP_BY_LIST(o_PP_ADD_PAREN_EACH_LIST, (/*5*/ (/*6*/o_PP_BY_LIST(o_PP_ADD_PREFIX_EACH, (/*7*/____, o_PP_IDENTITY template_types /*7*/)/*6*/)) /*5*/)), default_args  /*4*/) ) )

#define o_add_template_default_arguments(template_types, template_params, default_args)\
    o_PP_BY_LIST(o_PP_MIX, (\
        (o_PP_BY_LIST(o_PP_ADD_SUFFIX_EACH, (< , o_PP_BY_LIST(o_PP_ADD_PREFIX_EACH, (template_signature_parameter_, o_PP_IDENTITY template_types)) ) ))\
        , (o_create_template_default_arguments(template_types, default_args))))
     //o_PP_SURROUND_EACH_BY_LIST_5 o_PP_LEFT_PAREN o_PP_LEFT_PAREN ((((template_signature<, >::object(),  o_create_template_default_arguments(template_types, default_args)))))  o_PP_RIGHT_PAREN   o_PP_RIGHT_PAREN

#define MESSAGE_TO_PRINT o_add_template_default_arguments((typename, typename, typename, int), (t_A, t_B, t_C, t_i), ((caca), (eValueEnum0)))

//o_create_template_default_arguments((typename, typename, typename, int), ((std::allocator<t_Ty, std::pair<int, float>>), (eValueEnum0)))


//o_add_template_default_arguments((typename, typename, typename, int), (t_A, t_B, t_C, t_i), ((std::allocator<t_Ty, std::pair<int, float>>), (eValueEnum0)))


#if o_COMPILER == o_COMPILER_VISUAL_STUDIO

#define o_PP_MIX(l0,l1) \
    o_PP_CAT o_PP_LEFT_PAREN o_PP_MIX_,o_PP_NARG_FUNC()l0 o_PP_RIGHT_PAREN (l0,l1)

#define o_PP_MIX_1(l0,l1)\
    o_PP_BY_LIST(o_PP_CAT, (o_PP_ARG_0,l0)) o_PP_BY_LIST(o_PP_CAT, (o_PP_ARG_0,l1))

#define o_PP_MIX_2(l0,l1)\
    o_PP_MIX_1(l0,l1) , \
    o_PP_BY_LIST(o_PP_CAT, (o_PP_ARG_1,l0)) o_PP_BY_LIST(o_PP_CAT, (o_PP_ARG_1,l1)) \

#define o_PP_MIX_3(l0,l1)\
    o_PP_MIX_2(l0,l1) , \
    o_PP_BY_LIST(o_PP_CAT, (o_PP_ARG_2,l0)) o_PP_BY_LIST(o_PP_CAT, (o_PP_ARG_2,l1)) \

#define o_PP_MIX_4(l0,l1)\
    o_PP_MIX_3(l0,l1) , \
    o_PP_BY_LIST(o_PP_CAT, (o_PP_ARG_3,l0)) o_PP_BY_LIST(o_PP_CAT, (o_PP_ARG_3,l1)) \

#define o_PP_MIX_5(l0,l1)\
    o_PP_MIX_4(l0,l1) , \
    o_PP_BY_LIST(o_PP_CAT, (o_PP_ARG_4,l0)) o_PP_BY_LIST(o_PP_CAT, (o_PP_ARG_4,l1)) \

#define o_PP_MIX_6(l0,l1)\
    o_PP_MIX_5(l0,l1) , \
    o_PP_BY_LIST(o_PP_CAT, (o_PP_ARG_5,l0)) o_PP_BY_LIST(o_PP_CAT, (o_PP_ARG_5,l1)) \

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
/*

#pragma message(o_PP_QUOTE_L4(MESSAGE_TO_PRINT))

#define MESSAGE_TO_PRINT2 o_PP_ARG_0(template_signature_parameter_typename<, template_signature_parameter_typename<, template_signature_parameter_typename<, template_signature_parameter_int<) o_PP_ARG_0(____typename, ____typename, caca, eValueEnum0) , o_PP_ARG_1(template_signature_parameter_typename<, template_signature_parameter_typename<, template_signature_parameter_typename<, template_signature_parameter_int<) o_PP_ARG_1(____typename, ____typename, caca, eValueEnum0) , o_PP_ARG_2(template_signature_parameter_typename<, template_signature_parameter_typename<, template_signature_parameter_typename<, template_signature_parameter_int<) o_PP_ARG_2(____typename, ____typename, caca, eValueEnum0) , o_PP_ARG_3(template_signature_parameter_typename<, template_signature_parameter_typename<, template_signature_parameter_typename<, template_signature_parameter_int<) o_PP_ARG_3(____typename, ____typename, caca, eValueEnum0)

#pragma message(o_PP_QUOTE_L4(MESSAGE_TO_PRINT2))*/


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
#define o_PP_CREATE_SCOPE_IDENTIFIER(...) \
    o_PP_CAT_P()o_PP_LEFT_PAREN o_PP_CREATE_SCOPE_IDENTIFIER_,o_PP_NARG(__VA_ARGS__) o_PP_RIGHT_PAREN (__VA_ARGS__)
#define o_PP_QUOTE_SCOPE(_namespace_) \
    o_PP_QUOTE o_PP_LEFT_PAREN o_PP_CREATE_SCOPE _namespace_ o_PP_RIGHT_PAREN
#else
#define o_PP_CREATE_SCOPE(...) \
    o_PP_CAT( o_PP_CREATE_SCOPE_, o_PP_NARG(__VA_ARGS__) ) (__VA_ARGS__)
#define o_PP_CREATE_SCOPE_IDENTIFIER(...) \
    o_PP_CAT( o_PP_CREATE_SCOPE_IDENTIFIER_, o_PP_NARG(__VA_ARGS__) ) (__VA_ARGS__)
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

#define o_PP_CREATE_SCOPE_IDENTIFIER_0()
#define o_PP_CREATE_SCOPE_IDENTIFIER_1(_n0_) _n0_
#define o_PP_CREATE_SCOPE_IDENTIFIER_2(_n0_,_n1_) o_PP_CREATE_SCOPE_IDENTIFIER_1(_n0_)_##_n1_
#define o_PP_CREATE_SCOPE_IDENTIFIER_3(_n0_,_n1_,_n2_)    o_PP_CREATE_SCOPE_IDENTIFIER_2(_n0_,_n1_)_##_n2_
#define o_PP_CREATE_SCOPE_IDENTIFIER_4(_n0_,_n1_,_n2_,_n3_) o_PP_CREATE_SCOPE_IDENTIFIER_3(_n0_,_n1_,_n2_)_##_n3_
#define o_PP_CREATE_SCOPE_IDENTIFIER_5(_n0_,_n1_,_n2_,_n3_,_n4_) o_PP_CREATE_SCOPE_IDENTIFIER_4(_n0_,_n1_,_n2_,_n3_)_##_n4_
#define o_PP_CREATE_SCOPE_IDENTIFIER_6(_n0_,_n1_,_n2_,_n3_,_n4_,_n5_) o_PP_CREATE_SCOPE_IDENTIFIER_5(_n0_,_n1_,_n2_,_n3_,_n4_)_##_n5_
#define o_PP_CREATE_SCOPE_IDENTIFIER_7(_n0_,_n1_,_n2_,_n3_,_n4_,_n5_,_n6_) o_PP_CREATE_SCOPE_IDENTIFIER_6(_n0_,_n1_,_n2_,_n3_,_n4_,_n5_)_##_n6_
#define o_PP_CREATE_SCOPE_IDENTIFIER_8(_n0_,_n1_,_n2_,_n3_,_n4_,_n5_,_n6_,_n7_) o_PP_CREATE_SCOPE_IDENTIFIER_7(_n0_,_n1_,_n2_,_n3_,_n4_,_n5_,_n6_)_##_n7_
#define o_PP_CREATE_SCOPE_IDENTIFIER_9(_n0_,_n1_,_n2_,_n3_,_n4_,_n5_,_n6_,_n7_,_n8_) o_PP_CREATE_SCOPE_IDENTIFIER_8(_n0_,_n1_,_n2_,_n3_,_n4_,_n5_,_n6_,_n7_)_##_n8_
#define o_PP_CREATE_SCOPE_IDENTIFIER_10(_n0_,_n1_,_n2_,_n3_,_n4_,_n5_,_n6_,_n7_,_n8_,_n9_) o_PP_CREATE_SCOPE_IDENTIFIER_9(_n0_,_n1_,_n2_,_n3_,_n4_,_n5_,_n6_,_n7_,_n8_)_##_n9_

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
#define o_MAXIMUM_DECLARATION_COUNTER 800
#elif o_COMPILER == o_COMPILER_GCC
#define o_MAXIMUM_DECLARATION_COUNTER 800
#elif o_COMPILER == o_COMPILER_CLANG
#define o_MAXIMUM_DECLARATION_COUNTER 800
#else
#error    TODO : define o_MAXIMUM_DECLARATION_COUNTER for all supported compilers
#define o_MAXIMUM_DECLARATION_COUNTER 800
#endif

#define o_NESTED_TEMPLATE   BOOST_NESTED_TEMPLATE
#define o_NESTED_TYPE       typename
#if o_COMPILER == o_COMPILER_VISUAL_STUDIO
#define o_DOUBLE_NESTED_TYPE o_NESTED_TYPE o_NESTED_TYPE
#else
#define o_DOUBLE_NESTED_TYPE o_NESTED_TYPE
#endif



//  ==================================================================================================
//        SHORTCUTS
//  ==================================================================================================

#define o_fwdN(type, namespaces, name) o_namespace_begin namespaces type name; o_namespace_end namespaces;
#define o_fwdNT(type, namespaces, ts, name) o_namespace_begin namespaces template<o_PP_IDENTITY ts> type name; o_namespace_end namespaces;

#if o_COMPILER == o_COMPILER_VISUAL_STUDIO

#define o_namespace_begin(...) o_PP_CAT(o_PP_CAT(o_namespace_begin_,o_PP_NARG(__VA_ARGS__)),(__VA_ARGS__))
#define o_namespace_end(...) o_PP_CAT(o_PP_CAT(o_namespace_end_,o_PP_NARG(__VA_ARGS__)),(__VA_ARGS__))
#define o_fwd(...) o_PP_CAT(o_PP_CAT(o_fwd_, o_PP_NARG(__VA_ARGS__)),(__VA_ARGS__) )
#define o_fwdT(...) o_PP_CAT(o_PP_CAT(o_fwdT_,o_PP_NARG(__VA_ARGS__)),(__VA_ARGS__))
#if o__int__reflection_template_use_level == 0
#   define o_fwd_declare(...) o_fwd(__VA_ARGS__)
#   define o_fwd_declareT(...) o_fwdT(__VA_ARGS__)
#else
#   define o_fwd_declare(...) o_PP_CAT(o_PP_CAT(o_fwd_declare_, o_PP_NARG(__VA_ARGS__)),(__VA_ARGS__) )
#   define o_fwd_declareT(...) o_PP_CAT(o_PP_CAT(o_fwd_declareT_,o_PP_NARG(__VA_ARGS__)),(__VA_ARGS__))
#endif

#else // !o_COMPILER == o_COMPILER_VISUAL_STUDIO

#define o_namespace_begin(...) o_PP_CAT(o_namespace_begin_,o_PP_NARG(__VA_ARGS__)) (__VA_ARGS__)
#define o_namespace_end(...) o_PP_CAT(o_namespace_end_,o_PP_NARG(__VA_ARGS__)) (__VA_ARGS__)
#define o_fwd(...) o_PP_CAT(o_fwd_, o_PP_NARG(__VA_ARGS__)) (__VA_ARGS__)
#define o_fwdT(...) o_PP_CAT(o_fwdT_,o_PP_NARG(__VA_ARGS__)) (__VA_ARGS__)
#if o__int__reflection_template_use_level == 0
#   define o_fwd_declare(...) o_fwd(__VA_ARGS__)
#   define o_fwd_declareT(...) o_fwdT(__VA_ARGS__)
#else
#   define o_fwd_declare(...) o_PP_CAT(o_fwd_declare_, o_PP_NARG(__VA_ARGS__)) (__VA_ARGS__)
#   define o_fwd_declareT(...) o_PP_CAT(o_fwd_declareT_,o_PP_NARG(__VA_ARGS__)) (__VA_ARGS__)
#endif

#endif // o_COMPILER == o_COMPILER_VISUAL_STUDIO

#define o_begin_phantom_detail_namespace()  o_namespace_begin(phantom) namespace detail {
#define o_end_phantom_detail_namespace()    } o_namespace_end(phantom)

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

#   define o_fwdT_3(t,ts,c) o_namespace_begin_0() template<o_PP_IDENTITY ts> t c;
#   define o_fwdT_4(t,n0,ts,c) o_namespace_begin_1(n0) template<o_PP_IDENTITY ts> t c;o_namespace_end_1(n0)
#   define o_fwdT_5(t,n0,n1,ts,c) o_namespace_begin_2(n0,n1) template<o_PP_IDENTITY ts> t c; o_namespace_end_2(n0,n1)
#   define o_fwdT_6(t,n0,n1,n2,ts,c) o_namespace_begin_3(n0,n1,n2) template<o_PP_IDENTITY ts> t c; o_namespace_end_3(n0,n1,n2)
#   define o_fwdT_7(t,n0,n1,n2,n3,ts,c) o_namespace_begin_4(n0,n1,n2,n3) template<o_PP_IDENTITY ts> t c; o_namespace_end_4(n0,n1,n2,n3)
#   define o_fwdT_8(t,n0,n1,n2,n3,n4,ts,c)  o_namespace_begin_5(n0,n1,n2,n3,n4) template<o_PP_IDENTITY ts> t c; o_namespace_end_5(n0,n1,n2,n3,n4)
#   define o_fwdT_9(t,n0,n1,n2,n3,n4,n5,ts,c) o_namespace_begin_6(n0,n1,n2,n3,n4,n5) template<o_PP_IDENTITY ts> t c; o_namespace_end_6(n0,n1,n2,n3,n4,n5)
#   define o_fwdT_10(t,n0,n1,n2,n3,n4,n5,n6,ts,c) o_namespace_begin_7(n0,n1,n2,n3,n4,n5,n6) template<o_PP_IDENTITY ts> t c; o_namespace_end_7(n0,n1,n2,n3,n4,n5,n6)
#   define o_fwdT_11(t,n0,n1,n2,n3,n4,n5,n6,n7,ts,c) o_namespace_begin_8(n0,n1,n2,n3,n4,n5,n6,n7) template<o_PP_IDENTITY ts> t c; o_namespace_end_8(n0,n1,n2,n3,n4,n5,n6,n7)
#   define o_fwdT_12(t,n0,n1,n2,n3,n4,n5,n6,n7,n8,ts,c) o_namespace_begin_9(n0,n1,n2,n3,n4,n5,n6,n7,n8) { template<o_PP_IDENTITY ts> t c; o_namespace_end_9(n0,n1,n2,n3,n4,n5,n6,n7,n8)
#   define o_fwdT_13(t,n0,n1,n2,n3,n4,n5,n6,n7,n8,n9,ts,c) o_namespace_begin_10(n0,n1,n2,n3,n4,n5,n6,n7,n8,n9) { template<o_PP_IDENTITY ts> t c; o_namespace_end_10(n0,n1,n2,n3,n4,n5,n6,n7,n8,n9)

#else

#   define o_fwdT_3(t,ts,c) o_namespace_begin_0() template<o_PP_IDENTITY ts> t c;
#   define o_fwdT_4(t,n0,ts,c) o_namespace_begin_1(n0) template<o_PP_IDENTITY ts> t c;o_namespace_end_1(n0)
#   define o_fwdT_5(t,n0,n1,ts,c) o_namespace_begin_2(n0,n1) template<o_PP_IDENTITY ts> t c; o_namespace_end_2(n0,n1)
#   define o_fwdT_6(t,n0,n1,n2,ts,c) o_namespace_begin_3(n0,n1,n2) template<o_PP_IDENTITY ts> t c; o_namespace_end_3(n0,n1,n2)
#   define o_fwdT_7(t,n0,n1,n2,n3,ts,c) o_namespace_begin_4(n0,n1,n2,n3) template<o_PP_IDENTITY ts> t c; o_namespace_end_4(n0,n1,n2,n3)
#   define o_fwdT_8(t,n0,n1,n2,n3,n4,ts,c)  o_namespace_begin_5(n0,n1,n2,n3,n4) template<o_PP_IDENTITY ts> t c; o_namespace_end_5(n0,n1,n2,n3,n4)
#   define o_fwdT_9(t,n0,n1,n2,n3,n4,n5,ts,c) o_namespace_begin_6(n0,n1,n2,n3,n4,n5) template<o_PP_IDENTITY ts> t c; o_namespace_end_6(n0,n1,n2,n3,n4,n5)
#   define o_fwdT_10(t,n0,n1,n2,n3,n4,n5,n6,ts,c) o_namespace_begin_7(n0,n1,n2,n3,n4,n5,n6) template<o_PP_IDENTITY ts> t c; o_namespace_end_7(n0,n1,n2,n3,n4,n5,n6)
#   define o_fwdT_11(t,n0,n1,n2,n3,n4,n5,n6,n7,ts,c) o_namespace_begin_8(n0,n1,n2,n3,n4,n5,n6,n7) template<o_PP_IDENTITY ts> t c; o_namespace_end_8(n0,n1,n2,n3,n4,n5,n6,n7)
#   define o_fwdT_12(t,n0,n1,n2,n3,n4,n5,n6,n7,n8,ts,c) o_namespace_begin_9(n0,n1,n2,n3,n4,n5,n6,n7,n8) template<o_PP_IDENTITY ts> t c; o_namespace_end_9(n0,n1,n2,n3,n4,n5,n6,n7,n8)
#   define o_fwdT_13(t,n0,n1,n2,n3,n4,n5,n6,n7,n8,n9,ts,c) o_namespace_begin_10(n0,n1,n2,n3,n4,n5,n6,n7,n8,n9) template<o_PP_IDENTITY ts> t c; o_namespace_end_10(n0,n1,n2,n3,n4,n5,n6,n7,n8,n9)

#endif

#define o_rebind(_t_class_)\
    template<typename t_OtherTy>\
    struct rebind\
    {\
        typedef _t_class_<t_OtherTy> other;\
    };


#define o_specialize_template_bool_value(_type_, _template_, _value_) \
    template<> struct _template_<_type_> { const static bool value = _value_; };

// REFLECTION SPECIFIERS

#define o_public\
    class\
    {\
        struct reg\
        {\
            reg() { phantom::reflection::Types::currentModifiers = o_public_access; }\
        } regi;\
    } o_PP_CAT(public, __COUNTER__);\
    private

#define o_protected\
    class\
    {\
        struct reg\
        {\
            reg() { phantom::reflection::Types::currentModifiers = o_protected_access; }\
        } regi;\
    } o_PP_CAT(protected, __COUNTER__);\
    private

#define o_private\
    class\
    {\
        struct reg\
        {\
            reg() { phantom::reflection::Types::currentModifiers = o_private_access; }\
        } regi;\
    } o_PP_CAT(private, __COUNTER__);\
    private

#define o_virtual                   0x00000001ULL
#define o_abstract                  0x00000002ULL
#define o_pure_virtual              0x00000004ULL
#define o_static                    0x00000008ULL
#define o_no_default_constructor    0x00000010ULL
#define o_transient                 0x00000020ULL
#define o_no_copy                   0x00000040ULL
#define o_readonly                  0x00000080ULL
#define o_placement_extension       0x00000100ULL // auto installation and initialization on data members
#define o_no_placement_extension    0x00000200ULL // force no auto installation and initialization on data member if type has placement extension
#define o_protected_access          0x00000400ULL
#define o_public_access             0x00000800ULL
#define o_private_access            0x00000000ULL // private is by default if nothing set
#define o_native                    0x00001000ULL
#define o_overloaded                0x00002000ULL
#define o_singleton                 0x00004000ULL
#define o_shared                    0x00008000ULL
#define o_template                  0x00010000ULL
#define o_reset                     0x00020000ULL
#define o_const                     0x00040000ULL
#define o_noconst                   0x00080000ULL
#define o_always_valid              0x00100000ULL
#define o_inherits_allocator        0x00200000ULL
#define o_slot_member_function      0x00400000ULL
//#define o_component                 0x008000ULL00
#define o_owner                     0x01000000ULL
#define o_fixed_size                0x02000000ULL
#define o_deferred                  0x04000000ULL
#define o_invalid                   0x08000000ULL
#define o_mandatory                 0x10000000ULL
#define o_stdcall                   o_readonly  // reuse non-colliding modifiers (o_readonly cannot be combined with o_stdcall)
#define o_fastcall                  o_singleton //
#define o_union_alternative         0x20000000ULL

// CONSTANTS
#define o_invalid_guid (~(uint)0)

// HELPERS
#define o_component(type) phantom::component<type>
#define o_composition(type) phantom::composition<type>
#define o_aggregation(type) phantom::aggregation<type>
#define o_no_copy_of(...)\
    (o_no_copy * (phantom::has_copy_disabled_cascade<__VA_ARGS__>::value))

// DEFAULT SERIALIZATION MASKS
#define o_save_data     0x1
#define o_save_state    0x2


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

#define o_char_is_blank(c) (((c) == ' ') OR ((c) == '\t') OR ((c) == '\n') OR ((c) == '\r'))
#define o_char_is_identifier(c) ( (((c) >= '0') AND ((c) <= '9')) OR ((((c)|0x100000) >= 'a') AND (((c)|0x100000) <= 'z')) OR (c) == '_' )

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
    phantom::dynamic_delete_function_helper(o_memory_stat_insert_arguments) >>

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
#if defined(__GNUC__)
#define o_deprecate(foo, msg) foo __attribute__((deprecated(msg)))
#elif defined(_MSC_VER)
#define o_deprecate(foo, msg) __declspec(deprecated(msg)) foo
#else
#error This compiler is not supported
#endif

namespace static_warning_detail
{
    struct true_type {};
    struct false_type {};
    template <int test> struct converter : public true_type {};
    template <> struct converter<0> : public false_type {};
}

#define o_static_warning(cond, msg) \
struct o_PP_CAT(static_warning,__LINE__) { \
    o_deprecate(void _(::static_warning_detail::false_type const& ),msg) {}; \
    void _(::static_warning_detail::true_type const& ) {}; \
    o_PP_CAT(static_warning,__LINE__)() {_(::static_warning_detail::converter<(cond)>());} \
}

// Note: using STATIC_WARNING_TEMPLATE changes the meaning of a program in a small way.
// It introduces a member/variable declaration.  This means at least one byte of space
// in each structure/class instantiation.  STATIC_WARNING should be preferred in any
// non-template situation.
//  'token' must be a program-wide unique identifier.
#define o_static_warning_template(token, cond, msg) \
    o_static_warning(cond, msg) o_PP_CAT(o_PP_CAT(_localvar_, token),__LINE__)


#define o_static_assert         BOOST_STATIC_ASSERT
#define o_static_assert_msg     BOOST_STATIC_ASSERT_MSG

#define o_unused(var) (void)var



#if o_COMPILER == o_COMPILER_VISUAL_STUDIO
#   define o_exception(...) o_PP_CAT(o_PP_CAT(o_exception_, o_PP_NARG(__VA_ARGS__)),(__VA_ARGS__))
#   define o_assert(...) o_PP_CAT(o_PP_CAT(o_assert_, o_PP_NARG(__VA_ARGS__)),(__VA_ARGS__))
#   define o_warning(...) o_PP_CAT(o_PP_CAT(o_warning_, o_PP_NARG(__VA_ARGS__)),(__VA_ARGS__))
#else
#   define o_exception(...) o_PP_CAT(o_exception_, o_PP_NARG(__VA_ARGS__))(__VA_ARGS__)
#   define o_assert(...) o_PP_CAT(o_assert_, o_PP_NARG(__VA_ARGS__))(__VA_ARGS__)
#   define o_warning(...) o_PP_CAT(o_warning_, o_PP_NARG(__VA_ARGS__))(__VA_ARGS__)
#endif

// EXCEPTION
#if o__bool__use_exceptions
#    define o_exception_1(_exception_class_) throw _exception_class_()
#    define o_exception_2(_exception_class_, _what_) throw _exception_class_(_what_)
#else
#    define o_exception_1(_exception_class_) o_error(false, #_exception_class_)
#    define o_exception_2(_exception_class_, _what_) o_error( false, phantom::to_astring(#_exception_class_) + phantom::to_astring(" : ") + phantom::to_astring(_exception_class_(phantom::to_string(_what_).c_str()).what()) )
#endif

#define o_message(type, ...) // TODO : define
#define o_push_message(type, ...)
#define o_pop_message(type, ...)

#if (defined(_DEBUG) || defined(DEBUG))

#   define o_warning_1(_Expression)    \
        o_warning_2(_Expression, "no detail about the assertion")

#   define o_warning_2(_Expression, _Message)    \
        {( (!!(_Expression)) || (phantom::warning BOOST_PREVENT_MACRO_SUBSTITUTION ( #_Expression, _Message, __FILE__, __LINE__), 0) );}


#   define o_assert_1(_Expression)             o_assert_2(_Expression, "no detail about the assertion")
#   define o_assert_2(_Expression, _Message)   {( (!!(_Expression)) || (phantom::assertion BOOST_PREVENT_MACRO_SUBSTITUTION ( o_CS(#_Expression), phantom::to_astring(_Message).c_str(), __FILE__, __LINE__), 0) );}
#    define o_error(_Expression, _Message, ...)    \
        {(void)( (!!(_Expression)) || (phantom::error BOOST_PREVENT_MACRO_SUBSTITUTION ( o_CS(#_Expression), phantom::to_astring(_Message).c_str(), __FILE__, __LINE__), 0) );}

#   define o_verify(_Expression, _Message)     o_assert(_Expression, _Message)
#   define o_debug_only(things)                things
#   define o_log(level, format, ...)           ::phantom::log BOOST_PREVENT_MACRO_SUBSTITUTION (level, __FILE__, __LINE__, format, __VA_ARGS__)

#else // _NDEBUG

#   define o_assert_1(_Expression)
#   define o_assert_2(_Expression, _Message, ...)
#   define o_warning_1(_Expression)
#   define o_warning_2(_Expression, _Message, ...)
#   define o_debug_only(thing)
#   define o_verify(_Expression, _Message)     _Expression
#   define o_log(level, format, ...)           ::phantom::log BOOST_PREVENT_MACRO_SUBSTITUTION (level, __FILE__, __LINE__, format, __VA_ARGS__)
#   define o_error(_Expression, _Message, ...)    \
            {(void)( (!!(_Expression)) || (phantom::error BOOST_PREVENT_MACRO_SUBSTITUTION ( o_CS(#_Expression), phantom::to_astring(_Message).c_str(), __FILE__, __LINE__), 0) );}

#endif // _DEBUG

#define o_assert_not(exp)                   o_assert(NOT(exp))
#define o_assert_default_case()             o_assert(false, "Forgotten Default Case")
#define o_assert_no_implementation()        o_assert(false, "Not Implemented")
#define o_assert_forbidden_call()           o_assert(false, "Call to this member_function forbidden")

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

#define o_block_signal(name) \
    PHANTOM_CODEGEN_m_slot_list_of_##name.block();

#define o_unblock_signal(name) \
    PHANTOM_CODEGEN_m_slot_list_of_##name.unblock();

#define o_is_signal_blocked(name)\
    (PHANTOM_CODEGEN_m_slot_list_of_##name.blocked())

#define o_is_signal_unblocked(name)\
    (PHANTOM_CODEGEN_m_slot_list_of_##name.unblocked())

#define o_is_signal_connected(name)\
    (PHANTOM_CODEGEN_m_slot_list_of_##name.head() != nullptr)

#if o_COMPILER == o_COMPILER_VISUAL_STUDIO
#    define o_signal_data(...) \
    o_PP_CAT(o_signal_data_, o_PP_NARG(__VA_ARGS__))o_PP_LEFT_PAREN __VA_ARGS__ o_PP_RIGHT_PAREN
#else
#    define o_signal_data(...) \
    o_PP_CAT(o_signal_data_, o_PP_NARG(__VA_ARGS__))( __VA_ARGS__ )
#endif


#    define o_signal_data_1(_signal_name_) \
    phantom::connection::slot::list    PHANTOM_CODEGEN_m_slot_list_of_##_signal_name_;\
    inline phantom::signal_t _signal_name_(void)\
    {\
        if(PHANTOM_CODEGEN_m_slot_list_of_##_signal_name_.unblocked())\
        {\
            phantom::connection::slot* pSlot = PHANTOM_CODEGEN_m_slot_list_of_##_signal_name_.head();\
            while(pSlot )\
            {\
                phantom::connection::pair::push(this, pSlot);\
                pSlot->subroutine()->call(pSlot->receiver(), o_no_arg );\
                pSlot = pSlot->next();\
                phantom::connection::pair::pop();\
            }\
        }\
        return phantom::signal_t();\
    }

#    define o_signal_data_2(_signal_name_, _t0_) \
    phantom::connection::slot::list    PHANTOM_CODEGEN_m_slot_list_of_##_signal_name_;\
    inline phantom::signal_t _signal_name_(_t0_ a_0)\
{\
    if(PHANTOM_CODEGEN_m_slot_list_of_##_signal_name_.unblocked())\
    {\
        phantom::connection::slot* pSlot = PHANTOM_CODEGEN_m_slot_list_of_##_signal_name_.head();\
        while(pSlot)\
        {\
            phantom::connection::pair::push(this, pSlot);\
            void* args[1] = { (void*)(&a_0) };\
            pSlot->subroutine()->call( pSlot->receiver(), args );\
            pSlot = pSlot->next();\
            phantom::connection::pair::pop();\
        }\
    }\
    return phantom::signal_t();\
}

#    define o_signal_data_3(_signal_name_, _t0_, _t1_) \
    phantom::connection::slot::list    PHANTOM_CODEGEN_m_slot_list_of_##_signal_name_;\
    inline phantom::signal_t _signal_name_(_t0_ a_0, _t1_ a_1)\
{\
    if(PHANTOM_CODEGEN_m_slot_list_of_##_signal_name_.unblocked())\
    {\
        phantom::connection::slot* pSlot = PHANTOM_CODEGEN_m_slot_list_of_##_signal_name_.head();\
        while(pSlot)\
        {\
            phantom::connection::pair::push(this, pSlot);\
            void* args[2] = { (void*)(&a_0), (void*)(&a_1) };\
            pSlot->subroutine()->call( pSlot->receiver(), args );\
            pSlot = pSlot->next();\
            phantom::connection::pair::pop();\
        }\
    }\
    return phantom::signal_t();\
}

#    define o_signal_data_4(_signal_name_, _t0_, _t1_, _t2_) \
    phantom::connection::slot::list    PHANTOM_CODEGEN_m_slot_list_of_##_signal_name_;\
    inline phantom::signal_t _signal_name_(_t0_ a_0, _t1_ a_1, _t2_ a_2)\
{\
    if(PHANTOM_CODEGEN_m_slot_list_of_##_signal_name_.unblocked())\
    {\
        phantom::connection::slot* pSlot = PHANTOM_CODEGEN_m_slot_list_of_##_signal_name_.head();\
        while(pSlot)\
        {\
            phantom::connection::pair::push(this, pSlot);\
            void* args[3] = { (void*)(&a_0), (void*)(&a_1), (void*)(&a_2) };\
            pSlot->subroutine()->call( pSlot->receiver(), args );\
            pSlot = pSlot->next();\
            phantom::connection::pair::pop();\
        }\
    }\
    return phantom::signal_t();\
}

#    define o_signal_data_5(_signal_name_, _t0_, _t1_, _t2_, _t3_) \
    phantom::connection::slot::list    PHANTOM_CODEGEN_m_slot_list_of_##_signal_name_;\
    inline phantom::signal_t _signal_name_(_t0_ a_0, _t1_ a_1, _t2_ a_2, _t3_ a_3)\
{\
    if(PHANTOM_CODEGEN_m_slot_list_of_##_signal_name_.unblocked())\
    {\
        phantom::connection::slot* pSlot = PHANTOM_CODEGEN_m_slot_list_of_##_signal_name_.head();\
        while(pSlot)\
        {\
            phantom::connection::pair::push(this, pSlot);\
            void* args[4] = { (void*)(&a_0), (void*)(&a_1), (void*)(&a_2), (void*)(&a_3) };\
            pSlot->subroutine()->call( pSlot->receiver(), args );\
            pSlot = pSlot->next();\
            phantom::connection::pair::pop();\
        }\
    }\
    return phantom::signal_t();\
}

#    define o_signal_data_6(_signal_name_, _t0_, _t1_, _t2_, _t3_, _t4_) \
    phantom::connection::slot::list    PHANTOM_CODEGEN_m_slot_list_of_##_signal_name_;\
    inline phantom::signal_t _signal_name_(_t0_ a_0, _t1_ a_1, _t2_ a_2, _t3_ a_3, _t4_ a_4)\
{\
    if(PHANTOM_CODEGEN_m_slot_list_of_##_signal_name_.unblocked())\
    {\
        phantom::connection::slot* pSlot = PHANTOM_CODEGEN_m_slot_list_of_##_signal_name_.head();\
        while(pSlot)\
        {\
            phantom::connection::pair::push(this, pSlot);\
            void* args[5] = { (void*)(&a_0), (void*)(&a_1), (void*)(&a_2), (void*)(&a_3), (void*)(&a_4) };\
            pSlot->subroutine()->call( pSlot->receiver(), args );\
            pSlot = pSlot->next();\
            phantom::connection::pair::pop();\
        }\
    }\
    return phantom::signal_t();\
}

#    define o_signal_data_7(_signal_name_, _t0_, _t1_, _t2_, _t3_, _t4_, _t5_) \
    phantom::connection::slot::list    PHANTOM_CODEGEN_m_slot_list_of_##_signal_name_;\
    inline phantom::signal_t _signal_name_(_t0_ a_0, _t1_ a_1, _t2_ a_2, _t3_ a_3, _t4_ a_4, _t5_ a_5)\
{\
    if(PHANTOM_CODEGEN_m_slot_list_of_##_signal_name_.unblocked())\
    {\
        phantom::connection::slot* pSlot = PHANTOM_CODEGEN_m_slot_list_of_##_signal_name_.head();\
        while(pSlot)\
        {\
            phantom::connection::pair::push(this, pSlot);\
            void* args[6] = { (void*)(&a_0), (void*)(&a_1), (void*)(&a_2), (void*)(&a_3), (void*)(&a_4), (void*)(&a_5) };\
            pSlot->subroutine()->call( pSlot->receiver(), args );\
            pSlot = pSlot->next();\
            phantom::connection::pair::pop();\
        }\
    }\
    return phantom::signal_t();\
}

#    define o_signal_data_8(_signal_name_, _t0_, _t1_, _t2_, _t3_, _t4_, _t5_, _t6_) \
    phantom::connection::slot::list    PHANTOM_CODEGEN_m_slot_list_of_##_signal_name_;\
    inline phantom::signal_t _signal_name_(_t0_ a_0, _t1_ a_1, _t2_ a_2, _t3_ a_3, _t4_ a_4, _t5_ a_5, _t6_ a_6)\
{\
    if(PHANTOM_CODEGEN_m_slot_list_of_##_signal_name_.unblocked())\
    {\
        phantom::connection::slot* pSlot = PHANTOM_CODEGEN_m_slot_list_of_##_signal_name_.head();\
        while(pSlot)\
        {\
            phantom::connection::pair::push(this, pSlot);\
            void* args[7] = { (void*)(&a_0), (void*)(&a_1), (void*)(&a_2), (void*)(&a_3), (void*)(&a_4), (void*)(&a_5), (void*)(&a_6) };\
            pSlot->subroutine()->call( pSlot->receiver(), args );\
            pSlot = pSlot->next();\
            phantom::connection::pair::pop();\
        }\
    }\
    return phantom::signal_t();\
}

#    define o_signal_data_9(_signal_name_, _t0_, _t1_, _t2_, _t3_, _t4_, _t5_, _t6_, _t7_) \
    phantom::connection::slot::list    PHANTOM_CODEGEN_m_slot_list_of_##_signal_name_;\
    inline phantom::signal_t _signal_name_(_t0_ a_0, _t1_ a_1, _t2_ a_2, _t3_ a_3, _t4_ a_4, _t5_ a_5, _t6_ a_6, _t7_ a_7)\
{\
    if(PHANTOM_CODEGEN_m_slot_list_of_##_signal_name_.unblocked())\
    {\
        phantom::connection::slot* pSlot = PHANTOM_CODEGEN_m_slot_list_of_##_signal_name_.head();\
        while(pSlot)\
        {\
            phantom::connection::pair::push(this, pSlot);\
            void* args[8] = { (void*)(&a_0), (void*)(&a_1), (void*)(&a_2), (void*)(&a_3), (void*)(&a_4), (void*)(&a_5), (void*)(&a_6), (void*)(&a_7) };\
            pSlot->subroutine()->call( pSlot->receiver(), args );\
            pSlot = pSlot->next();\
            phantom::connection::pair::pop();\
        }\
    }\
    return phantom::signal_t();\
}





#define o_global_value_SetupStepIndex_TemplateSignature         0
#define o_global_value_SetupStepIndex_User_PreInheritance_1    1
#define o_global_value_SetupStepIndex_User_PreInheritance_2    2
#define o_global_value_SetupStepIndex_VTable                    3
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

#define o_global_value_SetupStepBit_TemplateSignature       0x00000001 // 0
#define o_global_value_SetupStepBit_User_PreInheritance_1    0x00000002 // 1
#define o_global_value_SetupStepBit_User_PreInheritance_2    0x00000004 // 2
#define o_global_value_SetupStepBit_VTable                  0x00000008 // 3
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
#define o_MemberFunction o_member_function
#define o_MEMBER_FUNCTION o_member_function
#define o_Method o_member_function
#define o_METHOD o_member_function
#define o_method o_member_function

#define o_DataMember o_data_member
#define o_DATA_MEMBER o_data_member

#define o_Field o_data_member
#define o_FIELD o_data_member
#define o_field o_data_member

#define o_Signal o_signal
#define o_SIGNAL o_signal

#define o_Property o_property
#define o_PROPERTY o_property

#define o_Constructor o_constructor
#define o_CONSTRUCTOR o_constructor


#define o_anonymous_enum(_values_)
#define o_anonymous_enumN(_namespaces_,_values_)
#define o_anonymous_enumNT(_namespaces_,_template_types_,_template_params_,_values_)
#define o_anonymous_enumT(_template_types_,_template_params_,_values_)
#define o_anonymous_enumC(_classes_,_values_)
#define o_anonymous_enumCT(_classes_,_template_types_,_template_params_,_values_)
#define o_anonymous_enumNC(_namespaces_,_classes_,_values_)
#define o_anonymous_enumNCT(_namespaces_,_classes_,_template_types_,_template_params_,_values_)

#define o_enum(_name_) \
    o_type_specialize_traits(_name_) \
    o_enum_module(_name_)

#define o_enumN(_namespaces_,_name_) \
    o_type_specialize_traitsN(_namespaces_,_name_) \
    o_enum_moduleN(_namespaces_,_name_)

#define o_enumC(_classes_,_name_) \
    o_type_specialize_traitsC(_classes_,_name_) \
    o_enum_moduleC(_classes_,_name_)

#define o_enumNC(_namespaces_,_classes_,_name_) \
    o_type_specialize_traitsNC(_namespaces_,_classes_,_name_) \
    o_enum_moduleNC(_namespaces_,_classes_,_name_)



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

#define o_enum_module(_name_)\
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
    o_members {\
struct reg \
            {\
            typedef phantom_proxy_generator_reflection_self_type enum_value_type;\
            reg() \
                {\
                phantom::reflection::Enum* pEnum = o_enum_module_access_type(_name_);\
                o_enum_constants

#define o_enum_constants(...)\
    o_enum_add_values(__VA_ARGS__)\
                }\
            } regi;\
        };\
    };

#define o_enum_moduleC(_classes_, _name_)\
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
    o_members {\
struct reg \
        {\
        reg() \
            {\
            typedef phantom_proxy_generator_reflection_self_type enum_value_type;\
            phantom::reflection::Enum* pEnum = o_enum_module_access_typeC(_classes_, _name_);\
            o_enum_constants

#define o_enum_add_values_delayed2() o_enum_add_values
#define o_enum_add_values_delayed o_enum_add_values_delayed2 o_PP_LEFT_PAREN o_PP_RIGHT_PAREN

#define o_enum_moduleN(_namespaces_, _name_)\
    o_namespace_begin _namespaces_\
    template<typename t_Ty>\
class phantom_proxy_____##_name_;\
    namespace __PHANTOM_ENUM_##_name_ { namespace __PHANTOM_ENUM_namespace = :: o_PP_CREATE_SCOPE _namespaces_; }\
    o_namespace_end _namespaces_\
    namespace phantom {\
    template<>\
struct proxy_of< o_PP_CREATE_QUALIFIED_NAME(_namespaces_,_name_)>\
        {\
        typedef :: o_PP_CREATE_SCOPE _namespaces_::phantom_proxy_____##_name_<o_PP_CREATE_QUALIFIED_NAME(_namespaces_,_name_)> type;\
        };\
    }\
    template<>\
class o_PP_CREATE_SCOPE _namespaces_::phantom_proxy_____##_name_<o_PP_CREATE_QUALIFIED_NAME(_namespaces_,_name_)> \
    {\
    typedef o_PP_CREATE_QUALIFIED_NAME(_namespaces_, _name_) phantom_proxy_generator_reflection_self_type;\
    o_members {\
struct reg \
            {\
            reg() \
                {\
                using o_PP_CREATE_QUALIFIED_NAME(_namespaces_, _name_);\
                typedef phantom_proxy_generator_reflection_self_type enum_value_type;\
                phantom::reflection::Enum* pEnum = o_enum_module_access_typeN(_namespaces_, _name_);\
                o_enum_constants_end


#define o_enum_constants_end(...)\
    o_enum_add_values(__VA_ARGS__) \
                }\
            } regi;\
        };\
    };

#define o_PP_ADD_PREFIX_EACH_DELAYED_BIS() o_PP_ADD_PREFIX_EACH
#define o_PP_ADD_PREFIX_EACH_DELAYED o_PP_ADD_PREFIX_EACH_DELAYED_BIS o_PP_LEFT_PAREN o_PP_RIGHT_PAREN

#define o_enum_constantsN_begin(_namespaces_)\

#define o_enum_moduleNC(_namespaces_, _classes_, _name_)\
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
class o_PP_CREATE_SCOPE _namespaces_::phantom_proxy_____##_name_<o_PP_CREATE_QUALIFIED_NAME_2(_namespaces_, _classes_,_name_)> \
    : public :: o_PP_CREATE_SCOPE  _namespaces_ :: o_PP_CREATE_SCOPE _classes_\
    , public phantom_proxy_generator_base_____< :: o_PP_CREATE_SCOPE  _namespaces_ :: o_PP_CREATE_SCOPE _classes_, :: o_PP_CREATE_SCOPE _namespaces_::phantom_proxy_____##_name_<o_PP_CREATE_QUALIFIED_NAME_2(_namespaces_, _classes_,_name_)>>\
    {\
    typedef o_PP_CREATE_QUALIFIED_NAME_2(_namespaces_, _classes_,_name_) phantom_proxy_generator_reflection_self_type;\
    o_members {\
struct reg \
            {\
            reg() \
                {\
                typedef phantom_proxy_generator_reflection_self_type enum_value_type;\
                phantom::reflection::Enum* pEnum = o_enum_module_access_typeNC(_namespaces_, _classes_, _name_);\
                o_enum_constants

#define o_type_specialize_traitsNT(_namespaces_,_template_types_,_template_params_,_name_)  \
    o_traits_specializeNT(has_module, (const static bool value = true), _namespaces_, _template_types_,_template_params_, _name_)\
    o_reflection_specialize_type_infos_ofNT(_namespaces_,_template_types_,_template_params_,_name_)\
    o_reflection_specialize_type_ofNT(_namespaces_,_template_types_,_template_params_,_name_)\
    o_reflection_specialize_template_specialization_adderNT(_namespaces_,_template_types_,_template_params_,_name_)\
    o_traits_specializeNT(is_template, (const static bool value = true), _namespaces_, _template_types_,_template_params_, _name_)
/*

#define o_type_specialize_traitsNTC(_namespaces_,_template_types_,_template_params_,_name_)  \
    o_traits_specializeNTC(has_module, (const static bool value = true), _namespaces_, _template_types_,_template_params_, _class_, _name_)\
    o_reflection_specialize_typeInfosOf_implNTC(_namespaces_,_template_types_,_template_params_, _class_,_name_) \
    o_reflection_specialize_type_ofNTC(_namespaces_,_template_types_,_template_params_, _class_,_name_)\
    o_traits_specializeNTC(is_template, (const static bool value = true), _namespaces_, _template_types_,_template_params_, _class_, _name_)
*/

#define o_type_specialize_traitsNTB(_namespaces_,_template_types_,_template_params_,_name_,_bases_)  \
    o_traits_specializeNT(has_module, (const static bool value = true), _namespaces_, _template_types_,_template_params_, _name_)\
    o_reflection_specialize_type_infos_ofNT(_namespaces_,_template_types_,_template_params_,_name_)\
    o_reflection_specialize_type_ofNT(_namespaces_,_template_types_,_template_params_,_name_)\
    o_reflection_specialize_template_specialization_adderNT(_namespaces_,_template_types_,_template_params_,_name_)\
    o_traits_specialize_all_base_traitNTB(_namespaces_, _template_types_,_template_params_, _name_,_bases_)\
    o_traits_specializeNT(is_template, (const static bool value = true), _namespaces_, _template_types_,_template_params_, _name_)

#define o_type_specialize_traitsCT(_classes_,_template_types_,_template_params_,_name_)  \
    o_traits_specializeCT(has_module, (const static bool value = true), _classes_, _template_types_,_template_params_, _name_)\
    o_reflection_specialize_type_infos_ofCT(_classes_,_template_types_,_template_params_,_name_)\
    o_reflection_specialize_type_ofCT(_classes_,_template_types_,_template_params_,_name_)\
    o_reflection_specialize_template_specialization_adderCT(_classes_,_template_types_,_template_params_,_name_)\
    o_traits_specializeCT(is_template, (const static bool value = true), _classes_, _template_types_,_template_params_, _name_)

#define o_type_specialize_traitsCTB(_classes_,_template_types_,_template_params_,_name_,_bases_)  \
    o_traits_specializeCT(has_module, (const static bool value = true), _classes_, _template_types_,_template_params_, _name_)\
    o_reflection_specialize_type_infos_ofCT(_classes_,_template_types_,_template_params_,_name_)\
    o_reflection_specialize_type_ofCT(_classes_,_template_types_,_template_params_,_name_)\
    o_reflection_specialize_template_specialization_adderCT(_classes_,_template_types_,_template_params_,_name_)\
    o_traits_specialize_all_base_traitCTB(_classes_,_template_types_,_template_params_, _name_,_bases_)\
    o_traits_specializeCT(is_template, (const static bool value = true), _classes_, _template_types_,_template_params_, _name_)

#define o_type_specialize_traitsNCT(_namespaces_,_classes_,_template_types_,_template_params_,_name_)  \
    o_traits_specializeNCT(has_module, (const static bool value = true), _namespaces_, _classes_, _template_types_,_template_params_, _name_)\
    o_reflection_specialize_type_infos_ofNCT(_namespaces_,_classes_,_template_types_,_template_params_,_name_)\
    o_reflection_specialize_type_ofNCT(_namespaces_,_classes_,_template_types_,_template_params_,_name_)\
    o_reflection_specialize_template_specialization_adderNCT(_namespaces_,_classes_,_template_types_,_template_params_,_name_)\
    o_traits_specializeNCT(is_template, (const static bool value = true), _namespaces_, _classes_, _template_types_,_template_params_, _name_)

#define o_type_specialize_traitsNCTB(_namespaces_,_classes_,_template_types_,_template_params_,_name_, _bases_)  \
    o_traits_specializeNCT(has_module, (const static bool value = true), _namespaces_, _classes_, _template_types_,_template_params_, _name_)\
    o_reflection_specialize_type_infos_ofNCT(_namespaces_,_classes_,_template_types_,_template_params_,_name_)\
    o_reflection_specialize_type_ofNCT(_namespaces_,_classes_,_template_types_,_template_params_,_name_)\
    o_reflection_specialize_template_specialization_adderNCT(_namespaces_,_classes_,_template_types_,_template_params_,_name_)\
    o_traits_specialize_all_base_traitNCTB(_namespaces_,_classes_,_template_types_,_template_params_, _name_,_bases_)\
    o_traits_specializeNCT(is_template, (const static bool value = true), _namespaces_, _classes_, _template_types_,_template_params_, _name_)

#define o_type_specialize_traitsT(_template_types_,_template_params_,_name_)  \
    o_traits_specializeT(has_module, (const static bool value = true), _template_types_,_template_params_, _name_)\
    o_reflection_specialize_type_infos_ofT(_template_types_,_template_params_,_name_)\
    o_reflection_specialize_type_ofT(_template_types_,_template_params_,_name_)\
    o_reflection_specialize_template_specialization_adderT(_template_types_,_template_params_,_name_)\
    o_traits_specializeT(is_template, (const static bool value = true), _template_types_,_template_params_, _name_)

#define o_type_specialize_traitsTB(_template_types_,_template_params_,_name_,_bases_)  \
    o_traits_specializeT(has_module, (const static bool value = true), _template_types_,_template_params_, _name_)\
    o_reflection_specialize_type_infos_ofT(_template_types_,_template_params_,_name_)\
    o_reflection_specialize_type_ofT(_template_types_,_template_params_,_name_)\
    o_reflection_specialize_template_specialization_adderT(_template_types_,_template_params_,_name_)\
    o_traits_specialize_all_base_traitTB(_template_types_,_template_params_, _name_,_bases_)\
    o_traits_specializeT(is_template, (const static bool value = true), _template_types_,_template_params_, _name_)

#define o_type_specialize_traitsN(_namespaces_,_name_)  \
    o_traits_specializeN(has_module, (const static bool value = true), _namespaces_, _name_)\
    o_reflection_specialize_type_infos_ofN(_namespaces_,_name_)\
    o_reflection_specialize_type_ofN(_namespaces_,_name_)

#define o_type_specialize_traitsNB(_namespaces_,_name_,_bases_)  \
    o_traits_specializeN(has_module, (const static bool value = true), _namespaces_, _name_)\
    o_reflection_specialize_type_infos_ofN(_namespaces_,_name_)\
    o_reflection_specialize_type_ofN(_namespaces_,_name_)\
    o_traits_specialize_all_base_traitNB(_namespaces_,_name_,_bases_)

#define o_type_specialize_traitsC(_classes_,_name_)  \
    o_traits_specializeN(has_module, (const static bool value = true), _classes_, _name_)\
    o_reflection_specialize_type_infos_ofC(_classes_,_name_)\
    o_reflection_specialize_type_ofC(_classes_,_name_)

#define o_type_specialize_traitsCB(_classes_,_name_)  \
    o_traits_specializeN(has_module, (const static bool value = true), _classes_, _name_)\
    o_reflection_specialize_type_infos_ofC(_classes_,_name_)\
    o_reflection_specialize_type_ofC(_classes_,_name_)\
    o_traits_specialize_all_base_traitB(_name_,_bases_)

#define o_type_specialize_traitsNC(_namespaces_,_classes_,_name_)  \
    o_traits_specializeNC(has_module, (const static bool value = true), _namespaces_,_classes_, _name_)\
    o_reflection_specialize_type_infos_ofNC(_namespaces_,_classes_,_name_)\
    o_reflection_specialize_type_ofNC(_namespaces_,_classes_,_name_)

#define o_type_specialize_traitsNCB(_namespaces_,_classes_,_name_,_bases_)  \
    o_traits_specializeNC(has_module, (const static bool value = true), _namespaces_,_classes_, _name_)\
    o_reflection_specialize_type_infos_ofNC(_namespaces_,_classes_,_name_)\
    o_reflection_specialize_type_ofNC(_namespaces_,_classes_,_name_)\
    o_traits_specialize_all_base_traitNCB(_namespaces_, _classes_,_name_,_bases_)

#define o_type_specialize_traitsB(_name_, _bases_)  \
    o_traits_specialize(has_module, (const static bool value = true), _name_)\
    o_reflection_specialize_type_infos_of(_name_)\
    o_reflection_specialize_type_of(_name_)\
    o_traits_specialize_all_base_traitB(_name_,_bases_)

#define o_type_specialize_traits(_name_)  \
    o_traits_specialize(has_module, (const static bool value = true), _name_)\
    o_reflection_specialize_type_infos_of(_name_)\
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

/// o_declare (only if typeid disabled)

#define o_declare_1(_name_)

#define o_declare_2(_type_, _name_) o_fwd(_type_, _name_)

#define o_declareN_2(_namespaces_, _name_) 

#define o_declareN_3(_type_, _namespaces_, _name_) o_fwdN(_type_, _namespaces_, _name_)

#define o_declareC_2(_classes_, _name_) 

#define o_declareNC_3(_namespaces_, _classes_, _name_) 

#define o_declareT_3(_template_types_,_template_params_, _name_) 

#define o_declareT_4(_type_, _template_types_, _template_params_, _name_) o_fwdT(_type_, _template_types_, _name_)

#define o_declareNT_4(_namespaces_, _template_types_,_template_params_, _name_) 

#define o_declareNT_5(_type_, _namespaces_, _template_types_,_template_params_, _name_) o_fwdNT(_type_, _namespaces_, _template_types_, _name_)
// 
// #else
// 
// #define o_declare_1(_name_) 
// 
// #define o_declare_2(_type_, _name_) o_fwd(_type_, _name_) o_declare_1(_name_)
// 
// #define o_declareN_2(_namespaces_, _name_) 
// 
// #define o_declareN_3(_type_, _namespaces_, _name_) o_fwdN(_type_, _namespaces_, _name_) 
// 
// #define o_declareC_2(_classes_, _name_) 
// 
// #define o_declareNC_3(_namespaces_, _classes_, _name_)
// 
// #define o_declareT_3(_template_types_,_template_params_, _name_) \
//     o_reflection_specialize_type_infos_ofT(_template_types_,_template_params_, _name_)
// 
// #define o_declareT_4(_type_, _template_types_, _template_params_, _name_) \
//     o_fwdT(_type_, _template_types_, _name_) o_declareT_3(_template_types_, _template_params_, _name_)
// 
// #define o_declareNT_4(_namespaces_, _template_types_,_template_params_, _name_) \
//     o_reflection_specialize_type_infos_ofT(_namespaces_, _template_types_,_template_params_, _name_)
// 
// #define o_declareNT_5(_type_, _namespaces_, _template_types_,_template_params_, _name_) \
//     o_fwdNT(_type_, _namespaces_, _template_types_, _name_) o_declareNT_4(_namespaces_, _template_types_,_template_params_, _name_)
// 
// #endif

#define o_union_meta_specifier_static_asserts(name, ...)\
    o_static_assert_msg(((phantom::detail::int_embedder<__VA_ARGS__>::value & o_placement_extension) == 0), "unions cannot have placement extension (auto installation and initialization on data members)");



#define o_union(_name_,...) \
    o_union_meta_specifier_static_asserts(_name_,##__VA_ARGS__)\
    o_type_specialize_traits(_name_) \
    o_traits_specialize(meta_specifiers, (enum {value = phantom::detail::int_embedder<__VA_ARGS__>::value};), _name_)\
    o_union_module(_name_)\
    o_members_list

#define o_unionC(_classes_,_name_,...) \
    o_union_meta_specifier_static_asserts(_name_,##__VA_ARGS__)\
    o_type_specialize_traitsC(_classes_,_name_) \
    o_traits_specializeC(meta_specifiers, (enum {value = phantom::detail::int_embedder<__VA_ARGS__>::value};), _classes_, _name_)\
    o_union_moduleC(_classes_,_name_)\
    o_members_list

#define o_unionN(_namespaces_,_name_,...) \
    o_union_meta_specifier_static_asserts(_name_,##__VA_ARGS__)\
    o_type_specialize_traitsN(_namespaces_,_name_) \
    o_traits_specializeN(meta_specifiers, (enum {value = phantom::detail::int_embedder<__VA_ARGS__>::value};), _namespaces_, _name_)\
    o_union_moduleN(_namespaces_,_name_)\
    o_members_list

#define o_unionNC(_namespaces_,_classes_,_name_,...) \
    o_union_meta_specifier_static_asserts(_name_,##__VA_ARGS__)\
    o_type_specialize_traitsNC(_namespaces_,_classes_,_name_) \
    o_traits_specializeNC(meta_specifiers, (enum {value = phantom::detail::int_embedder<__VA_ARGS__>::value};), _namespaces_, _classes_, _name_)\
    o_union_moduleNC(_namespaces_,_classes_,_name_)\
    o_members_list

#define o_unionT(_template_types_,_template_params_,_name_,...) \
    o_union_meta_specifier_static_asserts(_name_,##__VA_ARGS__)\
    o_type_specialize_traitsT(_template_types_,_template_params_,_name_) \
    o_traits_specializeT(meta_specifiers, (enum {value = phantom::detail::int_embedder<__VA_ARGS__>::value};), _template_types_,_template_params_, _name_)\
    o_union_moduleT(_template_types_,_template_params_,_name_)\
    o_members_list

#define o_unionNT(_namespaces_,_template_types_,_template_params_,_name_,...) \
    o_union_meta_specifier_static_asserts(_name_,##__VA_ARGS__)\
    o_type_specialize_traitsNT(_namespaces_,_template_types_,_template_params_,_name_) \
    o_traits_specializeNT(meta_specifiers, (enum {value = phantom::detail::int_embedder<__VA_ARGS__>::value};), _namespaces_, _template_types_,_template_params_, _name_)\
    o_union_moduleNT(_namespaces_,_template_types_,_template_params_,_name_)\
    o_members_list

#define o_unionNCT(_namespaces_,_classes_,_template_types_,_template_params_,_name_,...) \
    o_union_meta_specifier_static_asserts(_name_,##__VA_ARGS__)\
    o_type_specialize_traitsNCT(_namespaces_,_classes_,_template_types_,_template_params_,_name_) \
    o_traits_specializeNCT(meta_specifiers, (enum {value = phantom::detail::int_embedder<__VA_ARGS__>::value};), _namespaces_,_classes_, _template_types_,_template_params_, _name_)\
    o_union_moduleNCT(_namespaces_,_classes_,_template_types_,_template_params_,_name_)\
    o_members_list


#define o_structure_meta_specifier_static_asserts(name, ...)\
    o_static_assert_msg(((phantom::detail::int_embedder<__VA_ARGS__>::value & o_placement_extension) == 0), "structures cannot have placement extension (auto installation and initialization on data members)");


#define o_structure(_name_,...) \
    o_structure_meta_specifier_static_asserts(_name_,##__VA_ARGS__)\
    o_type_specialize_traits(_name_) \
    o_traits_specialize(is_structure, (static const bool value = true;), _name_)\
    o_traits_specialize(meta_specifiers, (enum {value = phantom::detail::int_embedder<__VA_ARGS__>::value};), _name_)\
    o_class_module(_name_)\
    o_members_list

#define o_structureC(_classes_,_name_,...) \
    o_structure_meta_specifier_static_asserts(_name_,##__VA_ARGS__)\
    o_type_specialize_traitsC(_classes_,_name_) \
    o_traits_specializeC(is_structure, (static const bool value = true;), _classes_, _name_)\
    o_traits_specializeC(meta_specifiers, (enum {value = phantom::detail::int_embedder<__VA_ARGS__>::value};), _classes_, _name_)\
    o_class_moduleC(_classes_,_name_)\
    o_members_list

#define o_structureN(_namespaces_,_name_,...) \
    o_structure_meta_specifier_static_asserts(_name_,##__VA_ARGS__)\
    o_type_specialize_traitsN(_namespaces_,_name_) \
    o_traits_specializeN(is_structure, (static const bool value = true;), _namespaces_, _name_)\
    o_traits_specializeN(meta_specifiers, (enum {value = phantom::detail::int_embedder<__VA_ARGS__>::value};), _namespaces_, _name_)\
    o_class_moduleN(_namespaces_,_name_)\
    o_members_list

#define o_structureNC(_namespaces_,_classes_,_name_,...) \
    o_structure_meta_specifier_static_asserts(_name_,##__VA_ARGS__)\
    o_type_specialize_traitsNC(_namespaces_,_classes_,_name_) \
    o_traits_specializeNC(is_structure, (static const bool value = true;), _namespaces_,_classes_,_name_)\
    o_traits_specializeNC(meta_specifiers, (enum {value = phantom::detail::int_embedder<__VA_ARGS__>::value};), _namespaces_, _classes_, _name_)\
    o_class_moduleNC(_namespaces_,_classes_,_name_)\
    o_members_list

#define o_structureT(_template_types_,_template_params_,_name_,...) \
    o_structure_meta_specifier_static_asserts(_name_,##__VA_ARGS__)\
    o_type_specialize_traitsT(_template_types_,_template_params_,_name_) \
    o_traits_specializeT(is_structure, (static const bool value = true;), _template_types_,_template_params_,_name_)\
    o_traits_specializeT(meta_specifiers, (enum {value = phantom::detail::int_embedder<__VA_ARGS__>::value};), _template_types_,_template_params_, _name_)\
    o_class_moduleT(_template_types_,_template_params_,_name_)\
    o_members_list

#define o_structureNT(_namespaces_,_template_types_,_template_params_,_name_,...) \
    o_structure_meta_specifier_static_asserts(_name_,##__VA_ARGS__)\
    o_type_specialize_traitsNT(_namespaces_,_template_types_,_template_params_,_name_) \
    o_traits_specializeNT(is_structure, (static const bool value = true;), _namespaces_,_template_types_,_template_params_,_name_)\
    o_traits_specializeNT(meta_specifiers, (enum {value = phantom::detail::int_embedder<__VA_ARGS__>::value};), _namespaces_, _template_types_,_template_params_, _name_)\
    o_class_moduleNT(_namespaces_,_template_types_,_template_params_,_name_)\
    o_members_list

#define o_structureNCT(_namespaces_,_classes_,_template_types_,_template_params_,_name_,...) \
    o_structure_meta_specifier_static_asserts(_name_,##__VA_ARGS__)\
    o_type_specialize_traitsNCT(_namespaces_,_classes_,_template_types_,_template_params_,_name_) \
    o_traits_specializeNCT(is_structure, (static const bool value = true;), _namespaces_,_classes_,_template_types_,_template_params_,_name_)\
    o_traits_specializeNCT(meta_specifiers, (enum {value = phantom::detail::int_embedder<__VA_ARGS__>::value};), _namespaces_,_classes_, _template_types_,_template_params_, _name_)\
    o_class_moduleNCT(_namespaces_,_classes_,_template_types_,_template_params_,_name_)\
    o_members_list






#define o_class(_name_,...) \
    o_type_specialize_traits(_name_) \
    o_traits_specialize(meta_specifiers, (enum {value = phantom::detail::int_embedder<__VA_ARGS__>::value};), _name_)\
    o_class_module(_name_)\
    o_members_list

#define o_classC(_classes_,_name_,...) \
    o_type_specialize_traitsC(_classes_,_name_) \
    o_traits_specializeC(meta_specifiers, (enum {value = phantom::detail::int_embedder<__VA_ARGS__>::value};), _classes_, _name_)\
    o_class_moduleC(_classes_,_name_)\
    o_members_list

#define o_classN(_namespaces_,_name_,...) \
    o_type_specialize_traitsN(_namespaces_,_name_) \
    o_traits_specializeN(meta_specifiers, (enum {value = phantom::detail::int_embedder<__VA_ARGS__>::value};), _namespaces_, _name_)\
    o_class_moduleN(_namespaces_,_name_)\
    o_members_list

#define o_classNC(_namespaces_,_classes_,_name_,...) \
    o_type_specialize_traitsNC(_namespaces_,_classes_,_name_) \
    o_traits_specializeNC(meta_specifiers, (enum {value = phantom::detail::int_embedder<__VA_ARGS__>::value};), _namespaces_, _classes_, _name_)\
    o_class_moduleNC(_namespaces_,_classes_,_name_)\
    o_members_list

#define o_classT(_template_types_,_template_params_,_name_,...) \
    o_type_specialize_traitsT(_template_types_,_template_params_,_name_) \
    o_traits_specializeT(meta_specifiers, (enum {value = phantom::detail::int_embedder<__VA_ARGS__>::value};), _template_types_,_template_params_, _name_)\
    o_class_moduleT(_template_types_,_template_params_,_name_)\
    o_members_list

#define o_classNT(_namespaces_,_template_types_,_template_params_,_name_,...) \
    o_type_specialize_traitsNT(_namespaces_,_template_types_,_template_params_,_name_) \
    o_traits_specializeNT(meta_specifiers, (enum {value = phantom::detail::int_embedder<__VA_ARGS__>::value};), _namespaces_, _template_types_,_template_params_, _name_)\
    o_class_moduleNT(_namespaces_,_template_types_,_template_params_,_name_)\
    o_members_list

#define o_classB(_name_,_bases_,...) \
    o_type_specialize_traitsB(_name_,_bases_) \
    o_traits_specialize(meta_specifiers, (enum {value = phantom::detail::int_embedder<__VA_ARGS__>::value};), _name_)\
    o_class_module(_name_)\
    o_members_list

#define o_classTB(_template_types_,_template_params_,_name_,_bases_,...) \
    o_type_specialize_traitsTB(_template_types_,_template_params_,_name_,_bases_) \
    o_traits_specialize(meta_specifiers, (enum {value = phantom::detail::int_embedder<__VA_ARGS__>::value};), _template_types_,_template_params_, _name_)\
    o_class_moduleT(_template_types_,_template_params_,_name_)\
    o_members_list

#define o_classNTB(_namespaces_,_template_types_,_template_params_,_name_,_bases_,...) \
    o_type_specialize_traitsNTB(_namespaces_,_template_types_,_template_params_,_name_,_bases_) \
    o_traits_specializeNT(meta_specifiers, (enum {value = phantom::detail::int_embedder<__VA_ARGS__>::value};), _namespaces_, _template_types_,_template_params_, _name_)\
    o_class_moduleNT(_namespaces_,_template_types_,_template_params_,_name_)\
    o_members_list

#define o_classNCB(_namespaces_,_classes_,_name_,_bases_,...) \
    o_type_specialize_traitsNCB(_namespaces_,_classes_,_name_,_bases_) \
    o_traits_specializeNC(meta_specifiers, (enum {value = phantom::detail::int_embedder<__VA_ARGS__>::value};), _namespaces_, _classes_, _name_)\
    o_class_moduleNC(_namespaces_,_classes_,_name_)\
    o_members_list

#define o_classNCT(_namespaces_,_classes_,_template_types_,_template_params_,_name_,_bases_,...) \
    o_type_specialize_traitsNCT(_namespaces_,_classes_,_template_types_,_template_params_,_name_) \
    o_traits_specializeNCT(meta_specifiers, (enum {value = phantom::detail::int_embedder<__VA_ARGS__>::value};), _namespaces_, _classes_,_template_types_,_template_params_, _name_)\
    o_class_moduleNCT(_namespaces_,_classes_,_template_types_,_template_params_,_name_)\
    o_members_list

#define o_classNCTB(_namespaces_,_classes_,_template_types_,_template_params_,_name_,_bases_,...) \
    o_type_specialize_traitsNCTB(_namespaces_,_classes_,_template_types_,_template_params_,_name_,_bases_) \
    o_traits_specializeNCT(meta_specifiers, (enum {value = phantom::detail::int_embedder<__VA_ARGS__>::value};), _namespaces_, _classes_,_template_types_,_template_params_, _name_)\
    o_class_moduleNCT(_namespaces_,_classes_,_template_types_,_template_params_,_name_)\
    o_members_list

#define o_classNB(_namespaces_,_name_,_bases_,...) \
    o_type_specialize_traitsNB(_namespaces_,_name_,_bases_) \
    o_traits_specializeN(meta_specifiers, (enum {value = phantom::detail::int_embedder<__VA_ARGS__>::value};), _namespaces_, _name_)\
    o_class_moduleN(_namespaces_,_name_)\
    o_members_list

#define o_members_list(...)\
        o_members \
        {\
            __VA_ARGS__\
        };\
    };

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

#define o_register_common(...)\
    o_static_assert_msg(phantom::has_reflection<__VA_ARGS__>::value, o_PP_QUOTE(__VA_ARGS__)" : undeclared reflection (ensure you included the corresponding .hxx)");\
    static phantom::detail::dynamic_initializer_module_installer_registrer< __VA_ARGS__> o_PP_CAT(g_register_module_, __COUNTER__) ;

#define o_register(_name_)\
    o_reflection_specialize_typeInfosOf(_name_)\
    o_register_common(_name_)

#define o_registerN(_namespaces_, _name_)\
    o_reflection_specialize_typeInfosOfN(_namespaces_, _name_)\
    o_namespace _namespaces_ \
    o_register_common(o_PP_CREATE_QUALIFIED_NAME(_namespaces_,_name_))\

#define o_registerC(_classes_, _name_)\
    o_reflection_specialize_typeInfosOfC(_classes_, _name_)\
    o_register_common(o_PP_CREATE_QUALIFIED_NAME(_classes_,_name_))

#define o_registerNC(_namespaces_, _classes_, _name_)\
    o_reflection_specialize_typeInfosOfNC(_namespaces_, _classes_, _name_)\
    o_namespace _namespaces_ \
    o_register_common(o_PP_CREATE_QUALIFIED_NAME_2(_namespaces_,_classes_,_name_))

#if o_COMPILER == o_COMPILER_VISUAL_STUDIO
#   define o_registerTI(...) o_PP_CAT(o_PP_CAT(o_registerTI_,o_PP_NARG(__VA_ARGS__)),(__VA_ARGS__))
#   define o_registerCTI(...) o_PP_CAT(o_PP_CAT(o_registerCTI_,o_PP_NARG(__VA_ARGS__)),(__VA_ARGS__))
#   define o_registerNTI(...) o_PP_CAT(o_PP_CAT(o_registerNTI_,o_PP_NARG(__VA_ARGS__)),(__VA_ARGS__))
#   define o_registerNCTI(...) o_PP_CAT(o_PP_CAT(o_registerNCTI_,o_PP_NARG(__VA_ARGS__)),(__VA_ARGS__))
#else
#   define o_registerTI(...) o_PP_CAT(o_registerTI_,o_PP_NARG(__VA_ARGS__)) (__VA_ARGS__)
#   define o_registerCTI(...) o_PP_CAT(o_registerCTI_,o_PP_NARG(__VA_ARGS__)) (__VA_ARGS__)
#   define o_registerNTI(...) o_PP_CAT(o_registerNTI_,o_PP_NARG(__VA_ARGS__)) (__VA_ARGS__)
#   define o_registerNCTI(...) o_PP_CAT(o_registerNCTI_,o_PP_NARG(__VA_ARGS__)) (__VA_ARGS__)
#endif

#define o_registerTI_2(_name_, _template_args_)\
    o_reflection_specialize_typeInfosOfTI_2(_template_args_,_name_)\
    o_register_common(_name_<o_PP_IDENTITY _template_args_>);

#define o_registerTI_3(_name_, _template_types_, _template_args_)\
    o_reflection_specialize_typeInfosOfTI_3(_namespaces_,_template_types_,_template_args_,_name_)\
    o_register_common(_name_<o_PP_IDENTITY _template_args_>);

#define o_registerCTI_3(_classes_, _name_, _template_args_)\
    o_reflection_specialize_typeInfosOfCTI_3(_classes_,_template_args_,_name_)\
    o_register_common(o_PP_CREATE_QUALIFIED_NAME(_classes_,_name_)<o_PP_IDENTITY _template_args_>);

#define o_registerCTI_4(_classes_, _name_, _template_types_, _template_args_)\
    o_reflection_specialize_typeInfosOfCTI_4(_classes_,_template_types_,_template_args_,_name_)\
    o_register_common(o_PP_CREATE_QUALIFIED_NAME(_classes_,_name_)<o_PP_IDENTITY _template_args_>);

#define o_registerNTI_3(_namespaces_, _name_, _template_args_)\
    o_reflection_specialize_typeInfosOfNTI_3(_namespaces_,_template_args_,_name_)\
    o_namespace _namespaces_ \
    o_register_common(o_PP_CREATE_QUALIFIED_NAME(_namespaces_,_name_)<o_PP_IDENTITY _template_args_>);

#define o_registerNTI_4(_namespaces_, _name_, _template_types_, _template_args_)\
    o_reflection_specialize_typeInfosOfNTI_4(_namespaces_,_template_types_,_template_args_,_name_)\
    o_namespace _namespaces_ \
    o_register_common(o_PP_CREATE_QUALIFIED_NAME(_namespaces_,_name_)<o_PP_IDENTITY _template_args_>);

#define o_registerNCTI_4(_namespaces_, _classes_, _name_,  _template_args_)\
    o_reflection_specialize_typeInfosOfNCTI_4(_namespaces_,_classes_,_template_args_,_name_)\
    o_namespace _namespaces_ \
    o_register_common(o_PP_CREATE_QUALIFIED_NAME_2(_namespaces_,_classes_,_name_)<o_PP_IDENTITY _template_args_>);

#define o_registerNCTI_5(_namespaces_, _classes_, _name_, _template_types_, _template_args_)\
    o_reflection_specialize_typeInfosOfNCTI_5(_namespaces_,_classes_,_template_types_,_template_args_,_name_)\
    o_namespace _namespaces_ \
    o_register_common(o_PP_CREATE_QUALIFIED_NAME_2(_namespaces_,_classes_,_name_)<o_PP_IDENTITY _template_args_>);

#define o_registerT(_template_types_, _template_params_, _name_)\
    static phantom::detail::dynamic_initializer_template_registrer o_PP_CAT(g_register_template_, o_PP_CAT(_name_, __COUNTER__)) ("",  #_name_) ;

#define o_registerNT(_namespaces_, _template_types_, _template_params_, _name_, ...)\
    static phantom::detail::dynamic_initializer_template_registrer o_PP_CAT(g_register_template_, o_PP_CAT(_name_, __COUNTER__)) (o_PP_QUOTE(o_PP_CREATE_SCOPE _namespaces_),  #_name_) ;

#if o_OPERATING_SYSTEM == o_OPERATING_SYSTEM_WINDOWS
#define o_module(name)\
    BOOL WINAPI DllMain(HINSTANCE _HDllHandle, DWORD _Reason, LPVOID _Reserved)\
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


// Phantom member_functions
#define o_initialize()                  void PHANTOM_CODEGEN_initialize()
#define o_terminate()                   void PHANTOM_CODEGEN_terminate()
#define o_restore(filter,pass)          phantom::restore_state PHANTOM_CODEGEN_restore(phantom::uint filter, phantom::restore_pass pass)

#define o_initialize_cpp(classname)                  void classname::PHANTOM_CODEGEN_initialize()
#define o_terminate_cpp(classname)                   void classname::PHANTOM_CODEGEN_terminate()
#define o_restore_cpp(classname,filter,pass)          phantom::restore_state classname::PHANTOM_CODEGEN_restore(phantom::uint filter, phantom::restore_pass pass)

#define o_destroyed                         typedef int PHANTOM_CODEGEN_destroyed_marker; o_signal_data(PHANTOM_CODEGEN_destroyed)


#include "def_macros_reflection.h"

/// Phantom strongly typed "new" / "delete" "operators" (note the quotes ... for more about that, just check the code bellow)

#define o_full_dynamic_new(...) \
    phantom::dynamic_new_helper(phantom::backupType(phantom::typeByName(#__VA_ARGS__))) >> new (phantom::backupType()->allocate()) __VA_ARGS__

#define o_static_new(...) \
    phantom::new_helper() >> new (o_allocate(__VA_ARGS__)) __VA_ARGS__

#define o_static_new_n(n, ...) \
    phantom::new_n_helper(n) >> o_allocate_n(n, __VA_ARGS__)

#define o_static_delete(...) \
    phantom::delete_helper<__VA_ARGS__>(o_memory_stat_insert_arguments) >>\

#define o_static_delete_n(n, ...) \
    phantom::delete_n_helper<__VA_ARGS__>(n o_memory_stat_append_arguments) >>

#define o_dynamic_new(...) \
    phantom::new_helper() >> new (o_allocate(__VA_ARGS__)) __VA_ARGS__

#define o_static_new_alloc_and_construct_part(...) \
    new (o_allocate(__VA_ARGS__)) __VA_ARGS__

#define o_static_new_install_and_initialize_part(instance) \
    phantom::new_helper() >> instance

#define o_dynamic_proxy_new(...) \
    phantom::proxy_new_helper<__VA_ARGS__>() >> new (phantom::allocator<__VA_ARGS__>::allocate(o_memory_stat_insert_arguments)) __VA_ARGS__

#define o_dynamic_proxy_delete(...) \
    phantom::proxy_delete_helper<__VA_ARGS__>(o_memory_stat_insert_arguments) >>


#if o__int__reflection_template_use_level == 3

#define o_new(...) o_static_new(__VA_ARGS__)

#define o_new_n(n, ...) o_static_new_n(n, __VA_ARGS__)

#define o_new_alloc_and_construct_part(...) o_static_new_alloc_and_construct_part(__VA_ARGS__)

#define o_new_install_and_initialize_part(instance) o_static_new_install_and_initialize_part(instance)

#define o_delete(...) o_static_delete(__VA_ARGS__)

#define o_delete_n(n, ...) o_static_delete_n(n,__VA_ARGS__)


#elif o__int__reflection_template_use_level == 2 || o__int__reflection_template_use_level == 1

#define o_new(...) \
    phantom::dynamic_new_helper(phantom::backupType()) >> new (phantom::backupType(o_type_of(__VA_ARGS__))->allocate()) __VA_ARGS__

#define o_new_n(n, ...) \
    phantom::dynamic_new_n_helper(phantom::backupType(), n) >> (__VA_ARGS__*)phantom::backupType(o_type_of(__VA_ARGS__))->allocate(n)

#define o_delete(...) \
    phantom::dynamic_delete_helper<__VA_ARGS__>(o_type_of(__VA_ARGS__) o_memory_stat_append_arguments) >>

#define o_delete_n(n, ...) \
    phantom::dynamic_delete_n_helper<__VA_ARGS__>(o_type_of(__VA_ARGS__), n o_memory_stat_append_arguments) >>

#define o_new_alloc_and_construct_part(...) o_static_new_alloc_and_construct_part(__VA_ARGS__)

#define o_new_install_and_initialize_part(instance) o_static_new_install_and_initialize_part(instance)

#else // if o__int__reflection_template_use_level == 0

#define o_new(...) \
    phantom::new_helper(phantom::backupType(phantom::typeByName(#__VA_ARGS__))) >> new (phantom::backupType()->allocate()) __VA_ARGS__

#define o_force_static_new(...)\
    phantom::force_static_new_helper() >> new (o_allocate(__VA_ARGS__)) __VA_ARGS__

#define o_new_n(n, ...) \
    phantom::new_n_helper(phantom::backupType(phantom::typeByName(#__VA_ARGS__)), n) >> phantom::backupType()->allocate(n)

#define o_new_alloc_and_construct_part(...) \
    new (phantom::typeByName(#__VA_ARGS__))->allocate()) __VA_ARGS__

#define o_delete(...) \
    phantom::delete_helper<__VA_ARGS__>(phantom::typeByName(#__VA_ARGS__) o_memory_stat_append_arguments) >>

#define o_force_static_delete(...) \
    phantom::force_static_delete_helper<__VA_ARGS__>(o_memory_stat_insert_arguments) >>

#define o_delete_n(n, ...) \
    phantom::delete_n_helper<__VA_ARGS__>(phantom::typeByName(#__VA_ARGS__), n o_memory_stat_append_arguments) >>

#define o_new_alloc_and_construct_part(...) o_static_new_alloc_and_construct_part(__VA_ARGS__)

#define o_new_install_and_initialize_part(instance) o_static_new_install_and_initialize_part(instance)

#endif


#endif // o_def_macros_h__


