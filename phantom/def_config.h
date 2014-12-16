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

#ifndef o_phantom_config_h__
#define o_phantom_config_h__

#ifndef __cplusplus
#    error "Phantom is a C++ Extension, you can't compile it with a C compiler"
#endif

// ENDIANNESS
#include <boost/detail/endian.hpp>

#ifndef BOOST_LITTLE_ENDIAN
#   error Big Endian not yet handled by Phantom
#endif


// avoid definition of windows min / max macros which conflicts with std ones
#ifndef NOMINMAX
#define NOMINMAX 1
#endif

//  ==================================================================================================
//        OPERATING SYSTEM VARIABLES
//  ==================================================================================================

#define o_OPERATING_SYSTEM_WINDOWS          1
#define o_OPERATING_SYSTEM_WINDOWS_PHONE    2
#define o_OPERATING_SYSTEM_LINUX            3
#define o_OPERATING_SYSTEM_MAC              4
#define o_OPERATING_SYSTEM_IPHONE           5
#define o_OPERATING_SYSTEM_IPAD             6
#define o_OPERATING_SYSTEM_WINDOWS_CE       7

#define o_OPERATING_SYSTEM_ANDROID          8
// ...

#define o_OPERATING_SYSTEM_FAMILY_WINDOWS   1
#define o_OPERATING_SYSTEM_FAMILY_UNIX      2


//  ==================================================================================================
//        PLATFORMS VARIABLES
//  ==================================================================================================

#define o_PLATFORM_WINDOWS_PC   0
#define o_PLATFORM_WINDOWS_CE   1
#define o_PLATFORM_LINUX_PC     2 
#define o_PLATFORM_ANDROID      3 
#define o_PLATFORM_IPHONE_IPAD  4 
#define o_PLATFORM_MACINTOSH    5
// ...

//  ==================================================================================================
//        PROCESSOR BRAND VARIABLES
//  ==================================================================================================

#define o_PROCESSOR_INTEL
#define o_PROCESSOR_AMD
// ...

//  ==================================================================================================
//        ARCHITECTURE VARIABLES
//  ==================================================================================================

#define o_ARCHITECTURE_X86            0
#define o_ARCHITECTURE_X64            1
// ...

//  ==================================================================================================
//        COMPILER VARIABLES
//  ==================================================================================================

// Visual Studio

#define o_COMPILER_VISUAL_STUDIO            1

#    define o_COMPILER_VISUAL_STUDIO_VERSION                    _MSC_VER // native predefined version number
#    define o_COMPILER_VISUAL_STUDIO_MAJOR_VERSION_12           1800
#    define o_COMPILER_VISUAL_STUDIO_MAJOR_VERSION_2013        o_COMPILER_VISUAL_STUDIO_MAJOR_VERSION_12
#    define o_COMPILER_VISUAL_STUDIO_MAJOR_VERSION_11           1700
#    define o_COMPILER_VISUAL_STUDIO_MAJOR_VERSION_2012        o_COMPILER_VISUAL_STUDIO_MAJOR_VERSION_11
#    define o_COMPILER_VISUAL_STUDIO_MAJOR_VERSION_10           1600
#    define o_COMPILER_VISUAL_STUDIO_MAJOR_VERSION_2010        o_COMPILER_VISUAL_STUDIO_MAJOR_VERSION_10
#    define o_COMPILER_VISUAL_STUDIO_MAJOR_VERSION_9            1500
#    define o_COMPILER_VISUAL_STUDIO_MAJOR_VERSION_2008        o_COMPILER_VISUAL_STUDIO_MAJOR_VERSION_9
#    define o_COMPILER_VISUAL_STUDIO_MAJOR_VERSION_8            1400
#    define o_COMPILER_VISUAL_STUDIO_MAJOR_VERSION_2005        o_COMPILER_VISUAL_STUDIO_MAJOR_VERSION_8
#    define o_COMPILER_VISUAL_STUDIO_MAJOR_VERSION_7            1300
#    define o_COMPILER_VISUAL_STUDIO_MAJOR_VERSION_2003        o_COMPILER_VISUAL_STUDIO_MAJOR_VERSION_7
#    define o_COMPILER_VISUAL_STUDIO_MAJOR_VERSION_6            1200

// Intel

#define o_COMPILER_INTEL                        2
#define o_COMPILER_INTEL_VERSION                __INTEL_COMPILER

// GCC
#define    o_COMPILER_GCC                            3


#    define o_COMPILER_GCC_MAJOR_VERSION_1        1
#    define o_COMPILER_GCC_MAJOR_VERSION_2        2
#    define o_COMPILER_GCC_MAJOR_VERSION_3        3
#    define o_COMPILER_GCC_MAJOR_VERSION_4        4

#    define o_COMPILER_GCC_MAJOR_VERSION            __GNUC__
#    define o_COMPILER_GCC_MINOR_VERSION            __GNUC_MINOR__
#    define o_COMPILER_GCC_PATCH_VERSION            __GNUC_PATCHLEVEL__
#    define o_COMPILER_GCC_VERSION        (__GNUC__ * 10000 \
    + __GNUC_MINOR__ * 100 \
    + __GNUC_PATCHLEVEL__)

// Metromerks Codewarrior

#define o_COMPILER_CODEWARRIOR                    4

// BORLAND C++

#define o_COMPILER_BORLAND                        5


// CLANG
#define o_COMPILER_CLANG                          6

//  ==================================================================================================
//        CURRENT PROCESSOR/ARCHITECTURE/PLATFORM/OS/COMPILER VARIABLE VALUES
//  ==================================================================================================

#if defined(_WIN32)    || defined(WIN32)        // Microsoft Windows
#    if    defined(_WIN64) || defined(WIN64)
#        define o_ARCHITECTURE o_ARCHITECTURE_X64
#    else
#        define o_ARCHITECTURE o_ARCHITECTURE_X86
#    endif

#    if defined(UNDER_CE)            // CE
#        define o_PLATFORM                o_PLATFORM_WINDOWS_CE
#        define o_OPERATING_SYSTEM        o_OPERATING_SYSTEM_WINDOWS_CE
#        define o_OPERATING_SYSTEM_FAMILY o_OPERATING_SYSTEM_FAMILY_WINDOWS
#        define o_OPERATING_SYSTEM_NAME    "Windows CE"
#    else                            // 2000/NT/XP/VISTA/7
#        define o_PLATFORM                o_PLATFORM_WINDOWS_PC
#        define o_OPERATING_SYSTEM        o_OPERATING_SYSTEM_WINDOWS
#        define o_OPERATING_SYSTEM_FAMILY o_OPERATING_SYSTEM_FAMILY_WINDOWS
#        define o_OPERATING_SYSTEM_NAME    "Windows"
#    endif

#    ifdef _MSC_VER            // Visual Studio X
#        define o_COMPILER_NAME            "Visual Studio Compiler"
#        define o_COMPILER                o_COMPILER_VISUAL_STUDIO
#        define o_COMPILER_VERSION        _MSC_VER
#        if     _MSC_VER < 1200
#            error(That old version of visual studio is not supported \
                    by this version of phantom, please contact us if you consider \
                    it really should and why, thanks ^^ : vivien.millet@gmail.com)
#        elif _MSC_VER < 1300    // Visual Studio 6.x
#            define o_COMPILER_MAJOR_VERSION        o_COMPILER_VISUAL_STUDIO_MAJOR_VERSION_6
#        elif _MSC_VER < 1400    // Visual Studio 2003 / 7.x
#            define o_COMPILER_MAJOR_VERSION        o_COMPILER_VISUAL_STUDIO_MAJOR_VERSION_7
#        elif _MSC_VER < 1500    // Visual Studio 2005 / 8.x
#            define o_COMPILER_MAJOR_VERSION        o_COMPILER_VISUAL_STUDIO_MAJOR_VERSION_8
#        elif _MSC_VER < 1600    // Visual Studio 2008 / 9.x
#            define o_COMPILER_MAJOR_VERSION        o_COMPILER_VISUAL_STUDIO_MAJOR_VERSION_9
#        else                    // Visual Studio 2010 and newer | >= 10.x
#            define o_COMPILER_MAJOR_VERSION        o_COMPILER_VISUAL_STUDIO_MAJOR_VERSION_10
#        endif
#	endif

#    if defined(__clang__)    // CLANG

#       define o_COMPILER_NAME                "CLANG"
#       define o_COMPILER                       o_COMPILER_CLANG
#       define o_COMPILER_VERSION
#       define o_COMPILER_MAJOR_VERSION        __clang__

#    elif defined(__GNUC__)    // GCC (MINGW32)
#        define o_COMPILER_NAME                "GCC"
#        define o_COMPILER                    o_COMPILER_GCC
#        define o_COMPILER_VERSION            o_COMPILER_GCC_VERSION
#        define o_COMPILER_MAJOR_VERSION        __GNUC__
#    endif

#elif defined(__linux__) || defined(__linux) // Linux

#    define o_PLATFORM                			o_PLATFORM_LINUX_PC

#    define o_OPERATING_SYSTEM_FAMILY           o_OPERATING_SYSTEM_FAMILY_UNIX
#    define o_OPERATING_SYSTEM                  o_OPERATING_SYSTEM_LINUX
#    if defined(__clang__)    // CLANG

#       define o_COMPILER_NAME                  "CLANG"
#       define o_COMPILER                       o_COMPILER_CLANG
#       define o_COMPILER_VERSION
#       define o_COMPILER_MAJOR_VERSION        __clang__

#   elif defined(__GNUC__)    // GCC
#        define o_COMPILER_NAME                "GCC"
#        define o_COMPILER                    o_COMPILER_GCC
#        define o_COMPILER_VERSION            o_COMPILER_GCC_VERSION
#        define o_COMPILER_MAJOR_VERSION        __GNUC__

#    endif

#elif defined(__APPLE__)                    // Apple Macintosh/IPhone/IPod/IPad

#    define o_PLATFORM                			o_PLATFORM_MACINTOSH

#    define o_OPERATING_SYSTEM_FAMILY           o_OPERATING_SYSTEM_FAMILY_UNIX

#   include "TargetConditionals.h" 
#   if defined(TARGET_OS_IPHONE)
#       define o_OPERATING_SYSTEM               o_OPERATING_SYSTEM_IPHONE
#   elif defined(TARGET_OS_IPAD)
#       define o_OPERATING_SYSTEM               o_OPERATING_SYSTEM_IPAD
#   else
#       define o_OPERATING_SYSTEM               o_OPERATING_SYSTEM_MAC
#   endif

#   if defined(__clang__)    // CLANG

#       define o_COMPILER_NAME                "CLANG"
#       define o_COMPILER                       o_COMPILER_CLANG
#       define o_COMPILER_VERSION
#       define o_COMPILER_MAJOR_VERSION        __clang__

#   elif defined(__GNUC__)    // GCC

#       define o_COMPILER_NAME                  "GCC"
#       define o_COMPILER                       o_COMPILER_GCC
#       define o_COMPILER_VERSION               o_COMPILER_GCC_VERSION
#       define o_COMPILER_MAJOR_VERSION        __GNUC__

#   elif defined(__INTEL_COMPILER)    // Intel C++

#        define o_COMPILER                    o_COMPILER_INTEL
#        define o_COMPILER_VERSION            o_COMPILER_INTEL_VERSION
#    endif

#elif defined(SN_TARGET_PS3)            // Playstation 3 PPU

#elif defined(SN_TARGET_PS3_SPU)        // Playstation 3 CELL SPU

#endif

// FEATURES

#if o_COMPILER == o_COMPILER_VISUAL_STUDIO

#   define o_STD_TYPE_TRAIT_DEFINED_IS_DEFAULT_CONSTRUCTIBLE 0
#   if o_COMPILER_VISUAL_STUDIO_VERSION >= o_COMPILER_VISUAL_STUDIO_MAJOR_VERSION_2010
#       define o_HAS_CPP0X 1
#       if o_COMPILER_VISUAL_STUDIO_VERSION >= o_COMPILER_VISUAL_STUDIO_MAJOR_VERSION_2012
#           define o_HAS_CPP11 1
#       else
#           define o_HAS_CPP11 0
#       endif
#   else
#       define o_HAS_CPP0X 0
#       define o_HAS_CPP11 0
#   endif

#   define o_HAS_COMPILE_TIME_TYPEID 1

#   if defined(_NATIVE_WCHAR_T_DEFINED)
#       define o_HAS_BUILT_IN_WCHAR_T 1
#   else
#       define o_HAS_BUILT_IN_WCHAR_T 0
#   endif

#elif o_COMPILER == o_COMPILER_CLANG

#   define o_HAS_CPP0X __GXX_EXPERIMENTAL_CXX0X__
#   if o_HAS_CPP0X
#          define o_STD_TYPE_TRAIT_DEFINED_IS_DEFAULT_CONSTRUCTIBLE 1
#   else
#          define o_STD_TYPE_TRAIT_DEFINED_IS_DEFAULT_CONSTRUCTIBLE 0
#   endif

#   if defined(__WCHAR_TYPE__)
#       define o_HAS_BUILT_IN_WCHAR_T 1
#   else
#       define o_HAS_BUILT_IN_WCHAR_T 0
#   endif

#   if __has_feature(cxx_rtti)
#       define o_HAS_COMPILE_TIME_TYPEID 1
#   else
#       define o_HAS_COMPILE_TIME_TYPEID 0
#   endif

#elif  o_COMPILER == o_COMPILER_GCC

#   define o_HAS_CPP0X __GXX_EXPERIMENTAL_CXX0X__
#   if o_COMPILER_GCC_VERSION > 40601
#       define o_STD_TYPE_TRAIT_DEFINED_IS_DEFAULT_CONSTRUCTIBLE 1
#   else
#       define o_STD_TYPE_TRAIT_DEFINED_IS_DEFAULT_CONSTRUCTIBLE 0
#   endif

#   if defined(__WCHAR_TYPE__)
#       define o_HAS_BUILT_IN_WCHAR_T 1
#   else
#       define o_HAS_BUILT_IN_WCHAR_T 0
#   endif

#   if defined(__GXX_RTTI)
#       define o_HAS_COMPILE_TIME_TYPEID 1
#   else
#       define o_HAS_COMPILE_TIME_TYPEID 0
#   endif

//#   if __has_feature(cxx_rtti)
#       define o_HAS_COMPILE_TIME_TYPEID 1
/*#   else
#       define o_HAS_COMPILE_TIME_TYPEID 0
#   endif*/

#endif

#if o_HAS_CPP11
#   define o_HAS_VARIADIC_TEMPLATE 1 
#else
#   define o_HAS_VARIADIC_TEMPLATE 0 
#endif

#if !o_HAS_COMPILE_TIME_TYPEID

#       pragma message ("PHANTOM : WARNING : C++ 'typeid' not available : you have two options inside this translation unit: \n    1 : enable RTTI (no Waaaay ?)\n    2 : for every template instance which needs reflection \n           - include .hxx for every template class used (recursively, i.e. including the ones used by the template itself and so on...) (ex: std::vector<std::string> requires inclusion of 'vector.hxx' and 'string.hxx')\n           - or register explicitely every template instance generated by this use (recursively, i.e. see above) (ex: std::vector<std::string> requires explicit registration of std::basic_string<char, std::char_traits<char>, std::allocator<char> >, std::char_traits<char>, and std::allocator<char>)\n    if non of these option is used, a link error will be produced saying : unresolved symbol '[...]typeInfosOf< your_type >[...]', you are warned ;)")

#endif


#endif // o_phantom_config_h__
