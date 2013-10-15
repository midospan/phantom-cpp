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

#ifndef serialization_BundleNode_h__
#define serialization_BundleNode_h__
// #pragma message("Including "__FILE__)


/* ****************** Includes ******************* */
/* *********************************************** */
/* The *.classdef.h file must be the last #include */
#include "BundleNode.classdef.h"
/* **************** Declarations ***************** */

/* *********************************************** */
o_h_begin

class o_export BundleNode : public Node
{
    Reflection_____________________________________________________________________________________
    _____________________________________________________________________________________Reflection

    class bundle_map_sorter
    {
    public:
        bool operator()(reflection::Type* const a_pC0, reflection::Type* const a_pC1) const 
        {
            if(a_pC0->isKindOf(a_pC1)) return false;
            if(a_pC1->isKindOf(a_pC0)) return true;
            return a_pC0 < a_pC1;
        }
    };
    typedef map<reflection::Type*, Bundle*, bundle_map_sorter> bundle_map;

public:
    BundleNode(BundleDataBase* a_pOwnerDataBase, uint guid, BundleNode* a_pParentNode);
    
    virtual void    storeData(void* a_pAddress, reflection::Type* a_pDataType) 
    {
        bundle(a_pDataType)->add(a_pAddress);
    }

    virtual void    eraseData(void* a_pAddress, reflection::Type* a_pDataType) 
    {
        bundle(a_pDataType)->remove(a_pAddress);
    }
    
    virtual void    storeData(void* a_pAddress, reflection::Type* a_pDataType, size_t a_uiCount, size_t a_uiChunkSectionSize) 
    {
        bundle(a_pDataType)->add(a_pAddress, a_uiCount, a_uiChunkSectionSize);
    }

    virtual void    eraseData(void* a_pAddress, reflection::Type* a_pDataType, size_t a_uiCount, size_t a_uiChunkSectionSize) 
    {
        bundle(a_pDataType)->remove(a_pAddress, a_uiCount, a_uiChunkSectionSize);
    }
    
    
    Bundle*                 bundle(reflection::Type* a_pType) 
    {
        bundle_map::const_iterator it = m_Bundles.find(a_pType);
        if(it == m_Bundles.end()) 
        {
            return m_Bundles[a_pType] = a_pType->createBundle(this);
        }
        return it->second;
    }

    template<typename t_Ty>
    inline native::TBundle<t_Ty>*  bundle() ;

    Bundle*                 getBundle(reflection::Type* a_pBundledType) const 
    {
        bundle_map::const_iterator it = m_Bundles.find(a_pBundledType);
        if(it == m_Bundles.end()) return NULL;
        return it->second;
    }
    
protected:
    bundle_map          m_Bundles;
};

o_h_end

#else
#include "BundleNode.classdef.h"
#endif // serialization_TBundleNode_h__