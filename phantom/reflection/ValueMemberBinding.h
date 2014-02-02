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

#ifndef o_phantom_reflection_ValueMemberBinding_h__
#define o_phantom_reflection_ValueMemberBinding_h__



/* ****************** Includes ******************* */


/* **************** Declarations ***************** */
/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export ValueMemberBinding : public Variable
{
public:
    ValueMemberBinding()
        : m_pObject(NULL)
        , m_pValueMember(NULL) 
    {
    }

    ValueMemberBinding(void* a_pObject, ValueMember* a_pValueMember);

    virtual Type*       getValueType() const 
    {
        return m_pValueMember->getValueType();
    }

    virtual void        getValue(void* dest) const 
    {
        m_pValueMember->getValue(m_pObject, dest);
    }

    virtual void        setValue(void const* src) const 
    {
        m_pValueMember->setValue(m_pObject, src);
    }

    virtual void*       getAddress() const 
    { 
        return m_pValueMember->getAddress(m_pObject); 
    }

    ValueMember*           getValueMember() const { return m_pValueMember; }

protected:
    void*           m_pObject;
    ValueMember*    m_pValueMember;

};

o_namespace_end(phantom, reflection)



#endif
