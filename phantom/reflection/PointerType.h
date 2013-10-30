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

#ifndef o_phantom_reflection_PointerType_h__
#define o_phantom_reflection_PointerType_h__
// #pragma message("Including "__FILE__)


/* ****************** Includes ******************* */

/* *********************************************** */
/* The *.classdef.h file must be the last #include */
#include "PointerType.classdef.h"
/* **************** Declarations ***************** */

/* *********************************************** */

o_h_begin

class o_export PointerType : public PrimitiveType
{
public:
    Reflection_____________________________________________________________________________________
    _____________________________________________________________________________________Reflection
public:
    friend class Type;

protected:
    PointerType(const string& a_strName, ushort a_uiSize, ushort a_uiAlignment, uint a_uiGuid, bitfield a_bfModifiers = bitfield()) 
        : PrimitiveType(a_strName, a_uiSize, a_uiAlignment, a_uiGuid, a_bfModifiers)    
    {

    }

public:
    o_destructor ~PointerType(void)     {}

    virtual boolean        isPOD() const { return true; }
    
    virtual boolean        isPointerType() const { return true; }

    virtual void        safeConstruct(void* a_pBuffer) const 
    {
        *reinterpret_cast<void**>(a_pBuffer) = NULL;
    }
    virtual void        safeConstruct(void* a_pBuffer, size_t a_uiCount, size_t a_uiChunkSectionSize) const 
    {
        memset(a_pBuffer, 0, a_uiCount*a_uiChunkSectionSize*m_uiSize);
    }

    virtual void        construct(void* a_pBuffer) const 
    {
        // trivial
    }
    virtual void        destroy(void* a_pBuffer) const 
    {
        // trivial
    }
    virtual void        construct(void* a_pBuffer, size_t a_uiCount, size_t a_uiChunkSectionSize) const 
    {
        // trivial
    }
    virtual void        destroy(void* a_pBuffer, size_t a_uiCount, size_t a_uiChunkSectionSize) const 
    {
        // trivial
    }
    
    virtual void    interpolate(void* a_src_start, void* a_src_end, real a_fPercent, void* a_dest, uint mode) const 
    {
        o_exception(exception::unsupported_member_function_exception, "interpolation is not supported for any pointer type");
    }

protected:
};

o_h_end


#else // PointerType_h__
#include "PointerType.classdef.h"
#endif