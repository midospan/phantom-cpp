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

#ifndef serialization_DefaultNode_h__
#define serialization_DefaultNode_h__
// #pragma message("Including "__FILE__)


/* ****************** Includes ******************* */
/* *********************************************** */
/* The *.classdef.h file must be the last #include */
#include "DefaultNode.classdef.h"
/* **************** Declarations ***************** */

/* *********************************************** */
o_h_begin

class o_export DefaultNode : public Node
{
    Reflection_____________________________________________________________________________________
    _____________________________________________________________________________________Reflection

public:
    DefaultNode(DataBase* a_pOwnerDataBase, uint guid, DefaultNode* a_pParentNode)
        : Node(a_pOwnerDataBase, guid, a_pParentNode) {}
    
    virtual void    storeData(const phantom::data& a_Data, size_t a_uiCount, size_t a_uiChunkSectionSize) 
    {
        byte* pChunk = reinterpret_cast<byte*>(a_Data.address());
        reflection::Type* pType = a_Data.type();
        while(a_uiCount--)
        {
            storeData(data(pChunk, pType));
            pChunk += a_uiChunkSectionSize;
        }
    }
    virtual void    eraseData(const phantom::data& a_Data, size_t a_uiCount, size_t a_uiChunkSectionSize) 
    {
        byte* pChunk = reinterpret_cast<byte*>(a_Data.address());
        reflection::Type* pType = a_Data.type();
        while(a_uiCount--)
        {
            eraseData(data(pChunk, pType));
            pChunk += a_uiChunkSectionSize;
        }
    }

    virtual void    storeData(const phantom::data& a_Data) 
    {
        o_assert(std::find(
            m_Data.begin()
            , m_Data.end()
            , a_Data
            ) == m_Data.end());
        m_Data.push_back(a_Data); 
    }

    virtual void    eraseData(const phantom::data& a_Data) 
    {
        data_vector::iterator it = m_Data.begin();
        data_vector::iterator end = m_Data.end();
        for(;it != end; ++it)
        {
            if(it->address() == a_Data.address())
            {
                o_assert(it->type() == a_Data.type(), "the data type registered for the given address doesn't match the given data type");
                break;
            }
        }
        o_assert(it != end, "data does not exist");
        m_Data.erase(it);
    }

    virtual void    getAllData(vector<data>& a_DataVector) const
    {
        data_vector::const_iterator it = m_Data.begin();
        data_vector::const_iterator end = m_Data.end();
        for(;it!=end;++it)
        {
            a_DataVector.push_back(*it);
        }
    }
    virtual void    getAllDataWithType(reflection::Type* a_pType, vector<data>& a_DataVector) const 
    {
        data_vector::const_iterator it = m_Data.begin();
        data_vector::const_iterator end = m_Data.end();
        for(;it!=end;++it)
        {
            if(it->type() == a_pType)
            a_DataVector.push_back(*it);
        }
    }

    virtual boolean containsDataWhichDependsOnData(const data& a_Dependency) const;

    virtual void getAllDataWhichDependsOnData(const phantom::data& a_Data, vector<data>& a_DataVector) const;

    virtual boolean dependsOn(Node* a_pNode) const;

    virtual boolean containsData(const data& a_Data) const 
    {
        data_vector::const_iterator it = m_Data.begin();
        data_vector::const_iterator end = m_Data.end();
        for(;it != end; ++it)
        {
            if((*it) == a_Data) return true;
        }
        return false;
    }

    virtual boolean containsDependencyOf(const data& a_Data) const;

    virtual void    destroyAllData();

    virtual void    applyDataVisitor(util::TVisitor<data>* visitor);

    virtual const data& findData(void* a_pAddress) const 
    {
        static data s_null;
        a_pAddress = phantom::baseOf(a_pAddress);
        data_vector::const_iterator it = m_Data.begin();
        data_vector::const_iterator end = m_Data.end();
        for(;it != end; ++it)
        {
            if(it->address() == a_pAddress) return *it;
        }
        return s_null;
    }

    void addDataComponents(vector<std::pair<phantom::data,phantom::data>>* opt_out_to_add /*= nullptr*/, vector<std::pair<phantom::data,phantom::data>>* opt_out_to_remove /*= nullptr*/);
    void addDataComponents( const phantom::data& a_Data, size_t a_uiCurrentSize, vector<std::pair<phantom::data,phantom::data>>* opt_out_to_add /*= nullptr*/,vector<std::pair<phantom::data,phantom::data>>* opt_out_to_remove /*= nullptr*/);
    void addDataComponents(const phantom::data& a_Data, vector<std::pair<phantom::data,phantom::data>>* opt_out_to_add = nullptr, vector<std::pair<phantom::data,phantom::data>>* opt_out_to_remove = nullptr);

protected:
    virtual void    clearDataReference(const vector<void*>& a_OldLayout) const;
    virtual bool    replaceDataReference(const vector<void*>& a_OldLayout, const phantom::data& a_New, bool a_SetIncompatibleToNull) const;

    virtual void    rebuildAllData(reflection::Type* a_pOld, reflection::Type* a_pNew, vector<data>& a_Old, vector<data>& a_New, uint a_uiStateId = 0xffffffff);
    
protected:
    typedef vector<phantom::data> data_vector;
    data_vector     m_Data;
};

o_h_end

#else
#include "DefaultNode.classdef.h"
#endif // serialization_TDefaultNode_h__