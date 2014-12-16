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

#ifndef serialization_FileTreeNode_h__
#define serialization_FileTreeNode_h__

/* ****************** Includes ******************* */
#include "phantom/serialization/Node.h"
/* **************** Declarations ***************** */
o_fwd(class, phantom, serialization, FileTreeDataBase)
o_declareN(class, (phantom, serialization), FileTreeNode)
/* *********************************************** */
o_namespace_begin(phantom, serialization)

class o_export FileTreeNode : public Node
{
    friend class FileTreeDataBase;

public:
    FileTreeNode(FileTreeDataBase* a_pDataBase, uint guid, FileTreeNode* a_pParentNode);
    
    string  path() const;

    string relativePath() const;

    void write(const string& a_Path, const property_tree& a_Tree) const;

    void read(const string& a_Path, property_tree& a_Tree) const;

protected:
    virtual void    saveIndex();
    virtual void    saveAttributes();
    virtual void    saveDataProperties(uint a_uiSerializationFlag, const phantom::data& a_Data, uint guid) ;
    virtual void    saveDataAttributes();
    virtual void    saveDataAttributes(const phantom::data& a_Data, uint guid);

    virtual void    loadAttributes();
    virtual void    loadDataAttributes();
    virtual void    loadDataAttributes(const phantom::data& a_Data, uint guid);
    virtual bool    canLoad(map<string, vector<string> >* missing_types_per_module) const;
    virtual void    cache();
    virtual void    cache(const vector<uint>* a_pGuids, vector<data>* a_pCachedData);
    virtual void    build(vector<data>& a_Data);
    virtual void    deserialize(uint a_uiSerializationFlag, vector<data>& a_Data);
    virtual void    restore(uint a_uiSerializationFlag, vector<data>& a_Data, restore_pass firstPass = restore_pass_local);
    virtual void    uncache();
    virtual void    unbuild();
    virtual void    configure();
    virtual void    unconfigure();

    virtual void    preCache();
    virtual bool    cacheOne(uint a_uiIndex);
    virtual void    postCache();
    virtual void    uncacheOne(const phantom::data& a_Data);
    virtual void    buildOne(const phantom::data& a_Data);
    virtual void    unbuildOne(const phantom::data& a_Data);
    virtual void    deserializeOne(const phantom::data& a_Data, uint a_uiSerializationFlag);
    virtual bool    restoreOne(const phantom::data& a_Data, uint a_uiSerializationFlag, restore_pass a_uiPass);
    virtual void    saveDataAttributesHelper(property_tree& tree, const phantom::data& a_Data);
    virtual void    loadDataAttributesHelper( const property_tree& tree, const phantom::data& a_Data );
    virtual void    loadDataProperties(uint a_uiSerializationFlag, const phantom::data& a_Data, uint guid);

protected:
    list<data>      m_DataAbortQueue;
    property_tree	m_CacheTree;
    vector<uint>    m_ParentGuids;
    vector<string>  m_ReferenceExpressions;
};

o_namespace_end(phantom, serialization)

#endif // serialization_TFileTreeNode_h__