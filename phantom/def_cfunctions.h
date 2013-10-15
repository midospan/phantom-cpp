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

#ifndef o_phantom_cfunctions_h__
#define o_phantom_cfunctions_h__



// COMPILER SPECIFIC C FUNCTIONS

#if o_COMPILER == o_COMPILER_VISUAL_STUDIO    // VISUAL STUDIO C functions
#   if defined(_UNICODE)
#       define o_auto_sprintf                swprintf
#       define o_auto_vsprintf                vswprintf
#       define o_auto_strcmp                    wcscmp
#       define o_auto_strlen                    wcslen
#   else
#       define o_auto_sprintf                sprintf
#       define o_auto_vsprintf                vsprintf
#       define o_auto_strcmp                    strcmp
#       define o_auto_strlen                    strlen
#   endif

#   define o_itoa(value,buf,size,radix) _itoa_s(value,buf,size,radix)
#   define o_secured_sprintf            sprintf_s

#elif (o_COMPILER == o_COMPILER_GCC) || (o_COMPILER == o_COMPILER_CLANG)   // GCC C functions
#   if defined(_UNICODE)
#       error wide string printf version not defined for GCC ... 
#       define o_auto_sprintf                    swprintf
#       define o_auto_vsprintf                    vswprintf
#       define o_auto_strcmp                        wcscmp
#       define o_auto_strlen                        wcslen
#   else
#       define o_auto_sprintf                sprintf
#       define o_auto_vsprintf                vsprintf
#       define o_auto_strcmp                    strcmp
#       define o_auto_strlen                    strlen
#   endif

#   define o_secured_sprintf            snprintf

#   define o_itoa(value,buf,size,radix) itoa(value,buf,radix)


#endif



#endif // _cfunctions_h__
