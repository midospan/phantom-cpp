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


/* **************** Declarations ***************** */

/* *********************************************** */

o_namespace_begin(phantom, reflection)

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


public:
    Collection(const string& a_strName, Type* a_pElementType, uint a_uiSerializationMask, bitfield a_Modifiers = 0);

    o_destructor ~Collection(void) {}

    virtual void                addElement(void* a_pObject, void const* src) const = 0;
    virtual void                insertElement(void* a_pObject, size_t a_uiIndex, void const* src) const;
    virtual void                setElement(void* a_pObject, size_t a_uiIndex, void const* src) const = 0;
    virtual void                getElement(void const* a_pObject, size_t a_uiIndex, void* dest) const = 0;
    virtual size_t              getSize(void const* a_pObject) const = 0;
    virtual void                removeElement(void* a_pObject, void const* src) const = 0;
    virtual void                moveElement(void* a_pObject, void const* src, size_t a_uiIndex) const = 0;

    void                        safeAddElement(void* a_pObject, void const* src) const;
    void                        safeInsertElement(void* a_pObject, size_t a_uiIndex, void const* src) const;
    virtual void                safeSetElement(void* a_pObject, size_t a_uiIndex, void const* src) const;
    virtual void                safeGetElement(void const* a_pObject, size_t a_uiIndex, void* dest) const;
    virtual size_t              safeGetSize(void const* a_pObject) const;
    void                        safeMoveElement(void* a_pObject, size_t a_uiIndex, void const* src) const;
    void                        safeRemoveElement(void* a_pObject, void const* src) const;

    Type*                       getElementType() const { return m_pElementType; }

    virtual Collection*         asCollection() const { return (Collection*)this; }
        
    virtual Iterator*           getIterator(void* a_pInstance) const;

    virtual bool                referencesData(const void* a_pInstance, const phantom::data& a_Data) const;
    virtual void                fetchPointerReferenceExpressions(const void* a_pInstance, vector<phantom::data>& out, uint a_uiSerializationMask) const;

protected:
    virtual bool                canBeDestroyed() const;
    virtual void                referencedElementRemoved(LanguageElement* a_pElement);

protected:
    Type*                       m_pElementType;
    uint                        m_uiSerializationMask;

};

o_namespace_end(phantom, reflection)



#endif
