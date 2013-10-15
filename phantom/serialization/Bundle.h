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

#ifndef serialization_Bundle_h__
#define serialization_Bundle_h__
// #pragma message("Including "__FILE__)


/* ****************** Includes ******************* */
/* *********************************************** */
/* The *.classdef.h file must be the last #include */
#include "Bundle.classdef.h"
/* **************** Declarations ***************** */

/* *********************************************** */


o_h_begin

class o_export Bundle : public Object
{
    Reflection_____________________________________________________________________________________
    _____________________________________________________________________________________Reflection

public:
    class chunk
    {
        friend class Bundle;
    public:
        o_forceinline chunk() {}
        o_forceinline chunk(void* a_address, ushort a_count, ushort a_section_size)
            : address(a_address), count(a_count) {}
    protected:
        void*   address;
        ushort  count;
        ushort  sectionSize;
    };

    Bundle(BundleNode* a_pOwnerNode, reflection::Type* a_pContentType)
        : m_pOwnerNode(a_pOwnerNode) 
        , m_pContentType(a_pContentType) 
        , m_sSize(0)
    {

    }
    o_destructor ~Bundle(void) {}

    size_t  getSize() const 
    { 
        return m_sSize; 
    }     

    virtual void add(void* a_pInstance);
    virtual void add(void* a_pChunkAddress, size_t a_uiCount, size_t a_uiChunkSectionSize);

    virtual void remove(void* a_pInstance);
    virtual void remove(void* a_pChunkAddress, size_t a_uiCount, size_t a_uiChunkSectionSize);

    void serialize(byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        vector<chunk>::const_iterator it = m_Content.begin();
        vector<chunk>::const_iterator end = m_Content.end();
        for(;it != end; ++it)
        {
            m_pContentType->serializeLayout(it->address, it->count, it->sectionSize, a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
        }
    }
    void deserialize(byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) 
    {
        vector<chunk>::const_iterator it = m_Content.begin();
        vector<chunk>::const_iterator end = m_Content.end();
        for(;it != end; ++it)
        {
            m_pContentType->deserializeLayout(it->address, it->count, it->sectionSize, a_pInBuffer, a_uiSerializationMask, a_pDataBase);
        }
    }

protected:
    vector<chunk>       m_Content;
    BundleNode*         m_pOwnerNode;
    reflection::Type*   m_pContentType;
    size_t              m_sSize;

};

o_h_end

#else
#include "Bundle.classdef.h"
#endif