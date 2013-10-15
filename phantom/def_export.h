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

#ifndef o_phantom_export_h__
#define o_phantom_export_h__


/* ****************** Includes ******************* */

/* *********************************************** */

//==========================================================
// Macro for export / import
//==========================================================

#ifdef _VISUAL_ASSIST_HELPER
    #define _VISUAL_ASSIST_HELPER
    #undef    _VISUAL_ASSIST_HELPER
#endif

#ifdef _VISUAL_ASSIST_HELPER
    #define PHANTOM_STATIC_LIB
    #define PHANTOMENGINEDLL_EXPORTS
#endif

#if (o_OPERATING_SYSTEM == o_OPERATING_SYSTEM_WINDOWS) && !defined(PHANTOM_STATIC_LIB)
#    ifdef _PHANTOM_KERNEL
#        define o_export __declspec(dllexport)
#    else
#       if defined( __MINGW32__ )
#           define o_export
#       else
#            define o_export __declspec(dllimport)
#       endif
#    endif
#else
#    define o_export
#endif    // #if (o_OPERATING_SYSTEM == o_OPERATING_SYSTEM_WINDOWS) && !defined(PHANTOM_STATIC_LIB)

//==========================================================
// Deactivation of warning 4251
// "T1 needs a DLL interface to be used by T2 class clients"
//==========================================================

#ifdef _MSC_VER
#   pragma warning(disable : 4251)
#endif

#endif // o_phantom_export_h__
