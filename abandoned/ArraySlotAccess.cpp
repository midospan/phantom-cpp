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
/* ** The Class Header must be the last #include * */
#include "ArraySlotAccess.h"
/* *********************************************** */
o_cpp_begin 

ArraySlotAccess::ArraySlotAccess( const string& a_strName , Property* a_pArrayProperty, Class*    a_pArrayType, uint a_uiIndex, bitfield a_bfModifiers /*= bitfield()*/ )
: Property(a_strName, a_bfModifiers)
, m_pArrayProperty(a_pArrayProperty)
, m_pArrayType(a_pArrayType)
, m_uiIndex(a_uiIndex)
, m_uiUse(0)
{

}

Type* ArraySlotAccess::getValueType() const
{
    return m_pArrayType;
}

void ArraySlotAccess::getValue( void const* a_pObject, void* dest ) const
{
    util::PolymorphicArray* pArray;
    m_pArrayProperty->getValue(a_pObject, &pArray);
    Object*    pObject = pArray->get<Object>(m_uiIndex);
    *((Object**)dest) = pObject;
}

void ArraySlotAccess::setValue( void* a_pObject, void const* src ) const
{
    util::PolymorphicArray* pArray;
    m_pArrayProperty->getValue(a_pObject, &pArray);
    Object*    pObject = *((Object**)src);
    pArray->set(m_uiIndex, pObject);
    m_pArrayProperty->setValue(a_pObject, &pArray);
}

void ArraySlotAccess::decrementUse()
{
    o_assert(m_uiUse>0);
    if(--m_uiUse == 0) 
    {
        destroy();
    }
}

o_cpp_end