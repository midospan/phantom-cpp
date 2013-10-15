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

#ifndef o_phantom_reflection_ScriptClass_h__
#define o_phantom_reflection_ScriptClass_h__


/* ****************** Includes ******************* */
#include <phantom/reflection/runtime/RuntimeClass.h>
/* *********************************************** */
/* The *.classdef.h file must be the last #include */
#include "ScriptClass.classdef.h"
/* **************** Declarations ***************** */

/* *********************************************** */


o_h_begin


class o_export ScriptClass : public RuntimeClass
{
public:
    Reflection_____________________________________________________________________________________
    _____________________________________________________________________________________Reflection

public:
    
    ScriptClass(const string& a_strName, ushort a_uiSize, ushort a_uiAlignment, size_t a_uiClassPtrOffset, size_t a_uiVMTPtrOffset, bitfield a_bfModifiers = bitfield()) 
        : RuntimeClass(a_strName, a_uiSize, a_uiAlignment, a_uiClassPtrOffset, a_bfModifiers)
        , m_uiVMTPtrOffset(a_uiVMTPtrOffset)
    {
//         if(NOT(a_pSuperClass->isInstanceOf<ScriptClass>()))
//         {
//             throw exception::reflection_runtime_exception("No class pointer offset provided and super class isn't a ScriptClass instance, no way to configure the virtual method table correctly");
//         }            
    }

    /*ScriptClass(const string& a_strName, Class* a_pSuperClass, bitfield a_bfModifiers = bitfield()) 
        : RuntimeClass(a_strName, a_pSuperClass, a_bfModifiers)
        , m_uiVMTPtrOffset(a_uiVMTPtrOffset)
    {
        if(NOT(a_pSuperClass->isNative()) OR NOT(a_pSuperClass->isScriptBaseClass()))
        {
            throw exception::reflection_runtime_exception("When the VMT pointer offset is provided, the super class must be the one which own that VMT pointer, i.e : a native class flagged with eFlag_Script");
        }
    }
    
    ScriptClass(const string& a_strName, Class* a_pSuperClass, size_t a_uiClassPtrOffset, size_t a_uiVMTPtrOffset, bitfield a_bfModifiers = bitfield()) 
        : RuntimeClass(a_strName, a_pSuperClass, a_uiClassPtrOffset, a_bfModifiers)
        , m_uiVMTPtrOffset(a_uiVMTPtrOffset)
    {
        if(NOT(a_pSuperClass->isNative()) OR NOT(a_pSuperClass->isScriptBaseClass()))
        {
            throw exception::reflection_runtime_exception("When the VMT pointer offset is provided, the super class must be the one which own that VMT pointer, i.e : a native class flagged with eFlag_Script");
        }
    }*/

    o_destructor ~ScriptClass(void) 
    {
    }
    o_forceinline void        initialize() {}
    o_forceinline void        uninstall() {}

protected:
    o_forceinline size_t    getVMTPtrOffset() const 
    {
        if(m_uiVMTPtrOffset == 0xffffffff)
        {
            o_assert(getSuperClassCount());
            o_assert(is<ScriptClass>(getSuperClass(0)));
            return static_cast<ScriptClass*>(getSuperClass(0))->getVMTPtrOffset();
        }
        return m_uiVMTPtrOffset; 
    }

public: 

    virtual void        construct(void* a_pObject) const
    {
        RuntimeClass::construct(a_pObject);
        *reinterpret_cast<InstanceMethod***>(reinterpret_cast<byte*>(a_pObject)+getVMTPtrOffset()) = const_cast<ScriptClass*>(this)->getVfTable();
        
    }
    
private:
    size_t                    m_uiVMTPtrOffset;

};

o_h_end


#else // ScriptClass_h__
#include "ScriptClass.classdef.h"
#endif