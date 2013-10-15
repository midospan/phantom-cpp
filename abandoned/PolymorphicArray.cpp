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
#include <phantom/util/Comparator.h>
#include <phantom/reflection/Namespace.h>
/* ** The Class Header must be the last #include * */
#include "PolymorphicArray.h"
/* *********************************************** */
o_namespace_begin(phantom, util) 

PolymorphicArray::PolymorphicArray( void )
{
    ____type_reflection = phantom::polymorphicArrayClassOf(classOf<Object>());
}

PolymorphicArray::PolymorphicArray( reflection::Class* a_pPolymorphicType ) 
{
    o_assert(a_pPolymorphicType);
    ____type_reflection = phantom::polymorphicArrayClassOf(a_pPolymorphicType);
}

PolymorphicArray::PolymorphicArray( reflection::Class* a_pPolymorphicType, size_t a_EnsuredCapacity ) 
{
    o_assert(a_pPolymorphicType);
    ____type_reflection = phantom::polymorphicArrayClassOf(a_pPolymorphicType);
    m_Content.reserve(a_EnsuredCapacity);
}

void PolymorphicArray::destroyContent()
{
    size_t i = 0;
    for(;i<m_Content.size();++i)
    {
        o_dynamic_delete_clean(m_Content[i]);
    }
    clear();
}

void PolymorphicArray::destroyContentCascade()
{
    size_t i = 0;
    for(;i<m_Content.size();++i)
    {
        if(m_Content[i] != NULL AND classOf(m_Content[i])->isPolymorphicArrayClass())
        {
            static_cast<PolymorphicArray*>(m_Content[i])->destroyContentCascade();
        }
        o_dynamic_delete_clean(m_Content[i]);
    }
    clear();
}



void PolymorphicArray::setAutoDestroyContent( boolean a_bValue )
{
//     if(a_bValue) __native_flags |= eNativeFlag_ArrayAutoDestroyContent; 
//     else __native_flags &= ~eNativeFlag_ArrayAutoDestroyContent;
}

PolymorphicArray::~PolymorphicArray( void )
{
//     if(__native_flags & eNativeFlag_ArrayAutoDestroyContent) 
//         destroyContent(); 
}

boolean PolymorphicArray::isAutoDestroyContent() const
{
    return false; //return (__native_flags & eNativeFlag_ArrayAutoDestroyContent) == eNativeFlag_ArrayAutoDestroyContent;
}


size_t PolymorphicArray::copyTo( PolymorphicArray* a_pDest ) const
{
    size_t i = 0;
    size_t c = 0;
    reflection::Class* pDestinationType = a_pDest->getContentType();
    for(;i<getLength();++i)
    {
        void* pObject = m_Content[i];
        if(a_pDest->accepts(pObject))
        {
            a_pDest->addBack(pObject);
            ++c;
        }
    }
    return c;
}

boolean PolymorphicArray::equals( Object* a_pObject ) const
{
    if(a_pObject == this) return true;
    if(NOT(a_pObject->isArray())) return false;
    PolymorphicArray* pOther = static_cast<PolymorphicArray*>(a_pObject);
    if(pOther->getLength() != getLength()) return false;
    size_t i = 0;
    for(;i<getLength();++i)
    {
        if(NOT(
            ____type_reflection->areValueEqual(
                m_Content[i]
                , m_Content[i]
            )
          )
        )
            return false;
    }
    return true;
}

reflection::Class* PolymorphicArray::getContentType() const
{
    o_assert(Phantom::getState() == Phantom::eState_Installed);
    return reinterpret_cast<reflection::PolymorphicArrayClass*>(getClass())->getContentType();
}

void    PolymorphicArray::initialize() {}

reflection::PolymorphicArrayClass* Reflect()
{
    return NULL;
}


o_namespace_end(phantom, util)
