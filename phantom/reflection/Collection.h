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

#ifndef o_phantom_reflection_Collection_h__
#define o_phantom_reflection_Collection_h__
// #pragma message("Including "__FILE__)


/* ****************** Includes ******************* */

/* *********************************************** */
/* The *.classdef.h file must be the last #include */
#include "Collection.classdef.h"
/* **************** Declarations ***************** */

/* *********************************************** */

o_h_begin

class o_export Collection : public LanguageElement
{
public:
    enum EAvailableOperationBit
    {
        e_AvailableOperationBit_Add = 0x1,
        e_AvailableOperationBit_Insert = 0x2,
        e_AvailableOperationBit_Move = 0x4,
        e_AvailableOperationBit_Remove = 0x8,
    };

    Reflection_____________________________________________________________________________________
    _____________________________________________________________________________________Reflection

public:
    Collection(const string& a_strName, Type* a_pElementType, bitfield a_Modifiers = 0);

    o_destructor ~Collection(void) {}

    virtual void                addElement(void* a_pObject, void const* src) const = 0;
    virtual void                insertElement(void* a_pObject, size_t a_uiIndex, void const* src) const 
    {
        addElement(a_pObject, src);
        moveElement(a_pObject, src, a_uiIndex);
    }
    virtual void                setElement(void* a_pObject, size_t a_uiIndex, void const* src) const = 0;
    virtual void                getElement(void const* a_pObject, size_t a_uiIndex, void* dest) const = 0;
    virtual size_t              getSize(void const* a_pObject) const = 0;
    virtual void                removeElement(void* a_pObject, void const* src) const = 0;
    virtual void                moveElement(void* a_pObject, void const* src, size_t a_uiIndex) const = 0;

    void                safeAddElement(void* a_pObject, void const* src) const 
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
    void                safeInsertElement(void* a_pObject, size_t a_uiIndex, void const* src) const 
    {
        safeAddElement(a_pObject, src);
        safeMoveElement(a_pObject, a_uiIndex, src);
    }
    virtual void         safeSetElement(void* a_pObject, size_t a_uiIndex, void const* src) const 
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
    virtual void         safeGetElement(void const* a_pObject, size_t a_uiIndex, void* dest) const 
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
    virtual size_t safeGetSize(void const* a_pObject) const 
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
    void                safeMoveElement(void* a_pObject, size_t a_uiIndex, void const* src) const 
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
    void                safeRemoveElement(void* a_pObject, void const* src) const 
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

    Type*                       getElementType() const { return m_pElementType; }

    virtual boolean             isCollection() const { return true; }
    virtual Collection*         asCollection() const { return (Collection*)this; }
        
    virtual reflection::Class*  getSortingCategoryClass() const { return classOf<Collection>(); }

    virtual util::Iterator*     getIterator(void* a_pInstance) const;

protected:
    Type*   m_pElementType;

};

o_h_end


#else // o_phantom_reflection_Collection_h__
#include "Collection.classdef.h"
#endif
