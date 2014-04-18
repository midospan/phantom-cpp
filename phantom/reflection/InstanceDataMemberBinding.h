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

#ifndef o_phantom_reflection_InstanceDataMemberBinding_h__
#define o_phantom_reflection_InstanceDataMemberBinding_h__



/* ****************** Includes ******************* */
#include <phantom/phantom.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, reflection), InstanceDataMemberBinding);
/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export InstanceDataMemberBinding : public LanguageElement
{
public:
    InstanceDataMemberBinding(void* a_pObject, InstanceDataMember* a_pInstanceDataMember);

    virtual Type*               getValueType() const 
    {
        return m_pInstanceDataMember->getValueType();
    }

    virtual void                getValue(void* dest) const 
    {
        m_pInstanceDataMember->getValue(m_pObject, dest);
    }

    virtual void                setValue(void const* src) const 
    {
        m_pInstanceDataMember->setValue(m_pObject, src);
    }

    virtual void*               getAddress() const 
    { 
        return m_pInstanceDataMember->getAddress(m_pObject); 
    }

    void*                       getObject() const { return m_pObject; }

    InstanceDataMember*        getInstanceDataMember() const { return m_pInstanceDataMember; }

protected:
    void referencedElementRemoved( LanguageElement* a_pElement );

protected:
    void*                   m_pObject;
    InstanceDataMember*     m_pInstanceDataMember;

};

o_namespace_end(phantom, reflection)



#endif
