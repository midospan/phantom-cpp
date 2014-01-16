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
#include "Collection.h"
/* *********************************************** */
o_cpp_begin 

ReflectionCPP__________________________________________________________________________________
__________________________________________________________________________________ReflectionCPP

Collection::Collection( const string& a_strName, Type* a_pElementType, bitfield a_Modifiers /*= 0*/ ) 
    : LanguageElement(a_strName, a_Modifiers) 
    , m_pElementType(a_pElementType)
{
    addReferencedElement(m_pElementType);
}

util::Iterator*     Collection::getIterator(void* a_pInstance) const
{
    return nullptr; // TODO : implement
}

bool Collection::canBeDestroyed() const
{
    return LanguageElement::canBeDestroyed() && (m_pElementType == nullptr OR m_pElementType->canBeDestroyed());
}

void Collection::safeAddElement( void* a_pObject, void const* src ) const
{
    reflection::Class* pOwnerClass = m_pOwner->asClass();
    if(pOwnerClass)
    {
        const rtti_data& rttiData = phantom::rttiDataOf(a_pObject);
        addElement( rttiData.cast(pOwnerClass), src);
    }
    else
    {
        addElement( a_pObject, src);
    }
}

void Collection::safeInsertElement( void* a_pObject, size_t a_uiIndex, void const* src ) const
{
    safeAddElement(a_pObject, src);
    safeMoveElement(a_pObject, a_uiIndex, src);
}

void Collection::safeSetElement( void* a_pObject, size_t a_uiIndex, void const* src ) const
{
    reflection::Class* pOwnerClass = m_pOwner->asClass();
    if(pOwnerClass)
    {
        const rtti_data& rttiData = phantom::rttiDataOf(a_pObject);
        setElement( rttiData.cast(pOwnerClass), a_uiIndex, src );
    }
    else
    {
        setElement( a_pObject, a_uiIndex, src);
    }
}

void Collection::safeGetElement( void const* a_pObject, size_t a_uiIndex, void* dest ) const
{
    reflection::Class* pOwnerClass = m_pOwner->asClass();
    if(pOwnerClass)
    {
        const rtti_data& rttiData = phantom::rttiDataOf(a_pObject);
        getElement( rttiData.cast(pOwnerClass), a_uiIndex, dest );
    }
    else
    {
        getElement( a_pObject, a_uiIndex, dest );
    }
}

size_t Collection::safeGetSize( void const* a_pObject ) const
{
    reflection::Class* pOwnerClass = m_pOwner->asClass();
    if(pOwnerClass)
    {
        const rtti_data& rttiData = phantom::rttiDataOf(a_pObject);
        return getSize( rttiData.cast(pOwnerClass) );
    }
    else
    {
        return getSize( a_pObject );
    }
}

void Collection::safeMoveElement( void* a_pObject, size_t a_uiIndex, void const* src ) const
{
    reflection::Class* pOwnerClass = m_pOwner->asClass();
    if(pOwnerClass)
    {
        const rtti_data& rttiData = phantom::rttiDataOf(a_pObject);
        moveElement( rttiData.cast(pOwnerClass), src, a_uiIndex );
    }
    else
    {
        moveElement( a_pObject, src, a_uiIndex);
    }
}

void Collection::safeRemoveElement( void* a_pObject, void const* src ) const
{
    reflection::Class* pOwnerClass = m_pOwner->asClass();
    if(pOwnerClass)
    {
        const rtti_data& rttiData = phantom::rttiDataOf(a_pObject);
        removeElement( rttiData.cast(pOwnerClass), src);
    }
    else
    {
        removeElement( a_pObject, src);
    }
}

void Collection::insertElement( void* a_pObject, size_t a_uiIndex, void const* src ) const
{
    addElement(a_pObject, src);
    moveElement(a_pObject, src, a_uiIndex);
}

void Collection::referencedElementRemoved( LanguageElement* a_pElement )
{
    o_assert(a_pElement == m_pElementType);
    m_pElementType = nullptr;
}

o_cpp_end
