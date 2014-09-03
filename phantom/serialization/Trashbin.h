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

#ifndef serialization_Trashbin_h__
#define serialization_Trashbin_h__
// #pragma message("Including "__FILE__)


/* ****************** Includes ******************* */
/* **************** Declarations ***************** */
o_declareN(class, (phantom, serialization), Trashbin);
/* *********************************************** */

o_namespace_begin(phantom, serialization)


class o_export Trashbin
{
    friend class DataBase;

protected:
    Trashbin(DataBase* a_pDataBase, const string& a_strUrl);

public:
    o_destructor ~Trashbin();

    void add(const vector<uint>& guids, vector<reflection::Expression*>* a_pRestoreReferenceExpressions = nullptr);
    void restore(const vector<uint>& guids);
    void erase(const vector<uint>& guids);

    const string& getUrl() const { return m_strUrl; }

protected:
    virtual void addEntries(const vector<uint>& guids) = 0;
    virtual void restoreEntries(const vector<uint>& guids) = 0;
    virtual void eraseEntries(const vector<uint>& guids) = 0;

protected:
    DataBase*                   m_pDataBase;
    string                      m_strUrl;
    map<uint, vector<string>>   m_Attributes;
    map<uint, string>           m_Types;
    map<uint, bool>             m_Nodes;
    map<uint, uint>             m_Parents;
    map<uint, string>           m_ReferenceExpressions;
    map<uint, bitfield>         m_Modifiers;
    map<uint, vector<string>>   m_RestoreExpressions;
};

o_namespace_end(phantom, serialization)

#endif // serialization_Trashbin_h__
