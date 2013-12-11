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
#include "phantom/def_jit_internal.h"
#include "JitStaticMemberFunction.h"
#include "JitLocalVariable.h"
#include "JitClass.h"
/* *********************************************** */
o_registerN((phantom, reflection, jit), JitStaticMemberFunction);

o_namespace_begin(phantom, reflection, jit)

JitStaticMemberFunction::JitStaticMemberFunction( const string& a_strName, Signature* a_pSignature, bitfield a_Modifiers ) : StaticMemberFunction(a_strName, a_pSignature, a_Modifiers) 
{
}

JitStaticMemberFunction::~JitStaticMemberFunction( void )
{
}

jit_function JitStaticMemberFunction::createJitFunction( jit_context context )
{
    return jit_function_create((jit_context_t)context.context, toJitSignature(e_JitAbi_stdcall, getSignature()));
}

void JitStaticMemberFunction::call( void* a_pCallerAddress, argument::list* a_pArgs ) const
{
    o_assert(false, "call version not available with Jit compilation");
}

void JitStaticMemberFunction::call( void* a_pCallerAddress, argument::list* a_pArgs, void* a_pReturnAddress ) const
{
    o_assert(false, "call version not available with Jit compilation");
}

void JitStaticMemberFunction::call( void* a_pThis, void** a_ppArgs ) const
{
    jit_function_apply((jit_function_t)m_jit_function.function, a_ppArgs, nullptr);
}

void JitStaticMemberFunction::call( void* a_pThis, void** a_ppArgs, void* a_pReturnArea ) const
{
    jit_function_apply((jit_function_t)m_jit_function.function, a_ppArgs, a_pReturnArea);
}

void JitStaticMemberFunction::call( void** args, void* a_pReturnArea ) const
{
    jit_function_apply((jit_function_t)m_jit_function.function, args, a_pReturnArea);
}

void JitStaticMemberFunction::call( void** args ) const
{
    jit_function_apply((jit_function_t)m_jit_function.function, args, nullptr);
}

void* JitStaticMemberFunction::getClosurePointer() const
{
    return JitSubroutine::getClosurePointer();
}


o_namespace_end(phantom, reflection, jit)