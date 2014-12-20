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

#ifndef o_phantom_reflection_native_TNativeMemberFunctionPointerTypeBase_h__
#define o_phantom_reflection_native_TNativeMemberFunctionPointerTypeBase_h__



/* ****************** Includes ******************* */
/* **************** Declarations ***************** */
/* *********************************************** */
using namespace fastdelegate;

o_namespace_begin(phantom, reflection, native)

template<typename t_Class>
class TNativeMemberFunctionPointerTypeBase : public MemberFunctionPointerType
{
public:
    typedef void (t_Class::*simplest_member_function_ptr)();
    TNativeMemberFunctionPointerTypeBase(Signature* a_pSignature, size_t a_Size, size_t a_Alignment, modifiers_t a_Modifiers = 0)
        : MemberFunctionPointerType(typeOf<t_Class>(), a_pSignature, a_Size, a_Alignment, a_Modifiers|o_native)
    {
    }

    virtual void call( void* a_pPointer, void* a_pCaller, void** a_pArgs ) const = 0;
    virtual void call( void* a_pPointer, void* a_pCaller, void** a_pArgs, void* a_pReturnAddress ) const 
    { 
        if(a_pReturnAddress) 
        {
            o_exception(exception::base_exception, "Expecting return address from a void function call, use call(void*, void**) instead"); 
        }
        else call(a_pPointer, a_pCaller, a_pArgs); 
    }
    
};


o_namespace_end(phantom, reflection, native)

#endif // reflection_native_TNativeMemberFunctionPointerTypeBase_h__