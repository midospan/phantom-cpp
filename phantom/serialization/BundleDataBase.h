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

#ifndef serialization_BundleDataBase_h__
#define serialization_BundleDataBase_h__
// #pragma message("Including "__FILE__)


/* ****************** Includes ******************* */
/* *********************************************** */
/* The *.classdef.h file must be the last #include */
#include "BundleDataBase.classdef.h"
/* **************** Declarations ***************** */

/* *********************************************** */

o_h_begin

class o_export BundleDataBase : public DataBase
{
    friend class BundleNode;

    Reflection_____________________________________________________________________________________
        
    _____________________________________________________________________________________Reflection

public:
    BundleDataBase(const string& url) : DataBase(url) {}
    o_destructor ~BundleDataBase(void)     {}

    virtual void    loadNodeEntries() = 0;
    virtual void    unloadNodeEntries() = 0;

    virtual boolean hasNodeEntry(Node* a_pNode) const = 0;
    virtual boolean hasDataEntry(void* a_pData) const = 0;

    virtual string  dataPath(void* a_pData) = 0;
    
protected: 
        
    virtual uint    generateGuid() = 0;
    virtual void    releaseGuid(uint guid) = 0;
    
    virtual Node*   createNode(uint a_Guid, Node* a_pParentNode) const = 0;
    virtual void    destroyNode(Node* a_pNode) const = 0;
    
    virtual void    createDataEntry(void* a_pData, reflection::Type* a_pDataType, uint a_Guid, Node* a_pOwnerNode) = 0;
    virtual void    destroyDataEntry(void* a_pData, reflection::Type* a_pDataType, uint a_Guid, Node* a_pOwnerNode) = 0;
    virtual void    moveDataEntry(void* a_pData, reflection::Type* a_pDataType, uint a_Guid, Node* a_pOldParent, Node* a_pNewParent) = 0;

    virtual void    createNodeEntry(Node* a_pNode) = 0;
    virtual void    destroyNodeEntry(Node* a_pNode) = 0;
    virtual void    moveNodeEntry(Node* a_pNode, Node* a_pNewParent) = 0;
            
protected:
};

o_h_end

#else // serialization_BundleDataBase_h__
#include "BundleDataBase.classdef.h"
#endif 