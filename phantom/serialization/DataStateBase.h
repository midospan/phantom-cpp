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

#ifndef serialization_DataStateBase_h__
#define serialization_DataStateBase_h__
// #pragma message("Including "__FILE__)


/* ****************** Includes ******************* */
#include <phantom/phantom.h>
/* *********************************************** */

/* *********************************************** */

o_namespace_begin(phantom, serialization)

class o_export DataStateBase 
{
    friend class Node;
    friend class DataBase;

protected:
    DataStateBase(const string& a_Url, uint a_uiSerializationFlag)
        : m_strUrl(a_Url)
        , m_uiSerializationFlag(a_uiSerializationFlag)
    {
    }

    const string& getUrl() const { return m_strUrl; }

    virtual bool hasStateSaved(Node* a_pNode, uint a_uiStateId) const = 0;

protected:
    virtual void loadState(Node* a_pNode, uint a_uiStateId) = 0;
    virtual void saveState(Node* a_pNode, uint a_uiStateId) = 0;
    virtual void loadDataState(const phantom::data& a_Data, uint guid, Node* a_pNode, uint a_uiStateId) = 0;
    virtual void saveDataState(const phantom::data& a_Data, uint guid, Node* a_pNode, uint a_uiStateId) = 0;

protected:
    string  m_strUrl;
    uint    m_uiSerializationFlag;
};

o_namespace_end(phantom, serialization)

o_classN((phantom, serialization), DataStateBase)
{
    o_reflection
    {

    };
};
o_exposeN((phantom, serialization), DataStateBase);

#endif // serialization_TDataStateBase_h__
