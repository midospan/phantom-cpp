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

#ifndef o_phantom_reflection_runtime_JitInstanceAttribute_h__
#define o_phantom_reflection_runtime_JitInstanceAttribute_h__


/* ****************** Includes ******************* */
#include <phantom/def_runtime.h>
/* ************* Class Declarations ************** */

/* *********************************************** */

o_namespace_begin(phantom, reflection, runtime)

class o_runtime_export JitInstanceAttribute : public InstanceAttribute
{
    friend class JitClass;
    
public:

    JitInstanceAttribute(const string& a_strName, Type* a_pContentType, uint a_uiSerializationMask, bitfield a_uiModifiers = bitfield());
    o_destructor ~JitInstanceAttribute() {}

    virtual void*        getAddress( void const* a_pObject ) const 
    {
        return reinterpret_cast<void*>(reinterpret_cast<byte*>(const_cast<void*>(a_pObject))+m_uiOffset);
    }
    virtual void        getValue( void const* a_pObject, void* dest ) const;
    virtual void        setValue( void* a_pObject, void const* src ) const;
    void                copyValue(void* dest, void const* src) const;
    size_t              getOffset() const { return m_uiOffset; }

protected:
    void                setOffset(size_t a_uiOffset) { m_uiOffset = a_uiOffset; }

protected:
    size_t              m_uiOffset;

};

o_namespace_end(phantom, reflection, runtime)

o_classNS((phantom, reflection, runtime), JitInstanceAttribute, (InstanceAttribute))
{
    o_reflection {};
};
o_exposeN((phantom, reflection, runtime), JitInstanceAttribute);


#else // o_phantom_reflection_runtime_JitInstanceAttribute_h__

#endif
