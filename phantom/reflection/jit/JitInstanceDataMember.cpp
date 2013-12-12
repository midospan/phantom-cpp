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
#include <phantom/def_jit.h>
/* ** The Class Header must be the last #include * */
#include <phantom/reflection/jit/JitInstanceDataMember.h>
/* *********************************************** */
o_registerN((phantom, reflection, jit), JitInstanceDataMember);

o_namespace_begin(phantom, reflection, jit)


JitInstanceDataMember::JitInstanceDataMember( const string& a_strName, Type* a_pContentType, Range* a_pRange, uint a_uiSerializationMask, bitfield a_bfModifiers /*= bitfield()*/) 
: InstanceDataMember(a_strName, a_pContentType, a_pRange, a_uiSerializationMask, a_bfModifiers)
, m_uiOffset(0xffffffff)
{
}

void JitInstanceDataMember::copyValue( void* dest, void const* src ) const
{
    m_pContentType->copy(((byte*)dest) + m_uiOffset
            ,    ((byte const*)src) + m_uiOffset );
}

void JitInstanceDataMember::getValue( void const* a_pObject, void* dest ) const
{
    m_pContentType->copy(dest, reinterpret_cast<byte const*>(a_pObject)+m_uiOffset);
}

void JitInstanceDataMember::setValue( void* a_pObject, void const* src ) const
{
    m_pContentType->copy(reinterpret_cast<byte*>(a_pObject)+m_uiOffset, src);
}

o_namespace_end(phantom, reflection, jit)