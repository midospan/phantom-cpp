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

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include <phantom/reflection/Function.h>
#include <phantom/reflection/Function.hxx>
#include <phantom/reflection/CallExpression.h>
/* *********************************************** */
o_registerN((phantom, reflection), Function);


int   __stdcall o_function_test_stdcall(int) { return 0; }
int     __cdecl o_function_test_cdecl(int) { return 0; }
int  __fastcall o_function_test_fastcall(int) { return 0; }

o_function(int, o_function_test_stdcall, (int));
o_function(int, o_function_test_cdecl, (int));
o_function(int, o_function_test_fastcall, (int));

o_namespace_begin(phantom, reflection) 

Class* const Function::metaType = o_type_of(phantom::reflection::Function);

Function::Function()
{

}

Function::Function( EABI a_eABI ) : Subroutine(a_eABI)
{

}

Function::Function( const string& a_strName, Signature* a_pSignature, EABI a_eABI, modifiers_t a_Modifiers /*= 0*/ ) 
    : Subroutine(a_strName, a_pSignature, a_eABI, a_Modifiers)
{

}

Function::Function( const string& a_strName, Signature* a_pSignature, EABI a_eABI, modifiers_t a_Modifiers, int )
    : Subroutine(a_strName, a_pSignature, a_eABI, a_Modifiers)
{

}

o_namespace_end(phantom, reflection)
