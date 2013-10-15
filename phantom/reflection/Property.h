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

#ifndef o_phantom_reflection_Property_h__
#define o_phantom_reflection_Property_h__
// #pragma message("Including "__FILE__)


/* ****************** Includes ******************* */
#include <phantom/reflection/LanguageElement.h>
/* *********************************************** */
/* The *.classdef.h file must be the last #include */
#include "Property.classdef.h"
/* **************** Declarations ***************** */
o_declare(class, phantom, reflection, SubProperty)
/* *********************************************** */

o_h_begin

class o_export Property : public LanguageElement
{
    Reflection_____________________________________________________________________________________
    _____________________________________________________________________________________Reflection

public:
    Property(const string& a_strName, uint a_uiSerializationMask, bitfield a_bfModifiers = bitfield());
    o_destructor ~Property(void) {}

    virtual void            getValue(void const* a_pObject, void* dest) const = 0;
    virtual void            setValue(void* a_pObject, void const* src) const = 0;

    virtual void            rememberValue(void const* a_pInstance, byte*& a_pOutBuffer) const;
    virtual void            rememberValue(void const* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer) const;
    virtual void            resetValue(void* a_pInstance, byte const*& a_pInBuffer) const;
    virtual void            resetValue(void* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer) const;

    virtual void            serializeValue(void const* a_pInstance, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const;
    virtual void            serializeValue(void const* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const;
    virtual void            serializeValue(void const* a_pInstance, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const;
    virtual void            serializeValue(void const* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const;
    virtual void            deserializeValue(void* a_pInstance, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const;
    virtual void            deserializeValue(void* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const;
    virtual void            deserializeValue(void* a_pInstance, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const;
    virtual void            deserializeValue(void* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const;

    virtual    Type*        getValueType() const = 0;

    inline SubProperty*     getSubProperty(uint i) const { return m_SubProperties[i]; }
    SubProperty*            getSubProperty(const string& a_strName) const;
    inline size_t           getSubPropertyCount() const { return m_SubProperties.size(); }

    inline uint             getSerializationMask() const { return m_uiSerializationMask; }

    
    virtual boolean            isProperty() const { return true; }

    virtual        void        copyValue(void* dest, void const* src) const 
    {
        void* sourceBuffer = getValueType()->newInstance();
        getValue(src, sourceBuffer);
        setValue(dest, sourceBuffer);
        getValueType()->deleteInstance(sourceBuffer);
    }

    virtual Class*           getSortingCategoryClass() const;

    inline ClassType*        getOwnerClassType() const { return m_pOwner->asClassType(); } 
    inline Class*           getOwnerClass() const { return m_pOwner->asClass(); }                  

    o_forceinline boolean    isSaved(uint a_uiSerializationFlag) const { return NOT(m_bfModifiers.matchesMask(o_transient)) AND ((m_uiSerializationMask & a_uiSerializationFlag) == a_uiSerializationFlag); }
    o_forceinline boolean    isReset() const { return m_bfModifiers.matchesMask(o_reset); }
    o_forceinline boolean    isTransient() const { return m_bfModifiers.matchesMask(o_transient); }

    virtual void*           getAddress(void const* a_pInstance) const { return NULL; }

protected:
    phantom::vector<SubProperty*>       m_SubProperties;
    uint                                m_uiSerializationMask;
    
};

o_h_end


#else // o_phantom_reflection_Property_h__
#include "Property.classdef.h"
#endif
