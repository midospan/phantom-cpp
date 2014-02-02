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

#ifndef serialization_XmlFileTreeNode_h__
#define serialization_XmlFileTreeNode_h__
// #pragma message("Including "__FILE__)


/* ****************** Includes ******************* */
#include "phantom/serialization/FileTreeNode.h"
/* **************** Declarations ***************** */
o_declareN(class, (phantom, serialization), XmlFileTreeNode);
o_fwd(class, phantom, serialization, XmlFileTreeDataBase);
o_fwd(class, phantom, serialization, XmlFileTreeDataStateBase);
/* *********************************************** */

o_namespace_begin(phantom, serialization)

class o_export XmlFileTreeNode : public FileTreeNode
{
    friend class XmlFileTreeDataStateBase;

public:
    XmlFileTreeNode(XmlFileTreeDataBase* a_pOwnerDataBase, uint guid, XmlFileTreeNode* a_pParentNode);
    
protected:
    virtual void    saveIndex() ;
    virtual void    saveAttributes() ;
    virtual void    saveData(uint a_uiSerializationFlag, const phantom::data& a_Data, uint guid) ;
    virtual void    saveDataAttributes();
    virtual void    saveDataAttributes(const phantom::data& a_Data, uint guid);

    virtual void    loadAttributes();
    virtual void    loadDataAttributes();
    virtual void    loadDataAttributes(const phantom::data& a_Data, uint guid);
    virtual bool    canLoad(vector<string>* missing_types) const;
    virtual void    cache();
    virtual void    build();
    virtual void    deserialize(uint a_uiSerializationFlag);
    virtual void    uncache();
    virtual void    restore(uint a_uiSerializationFlag);
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
    virtual bool    restoreOne(const phantom::data& a_Data, uint a_uiSerializationFlag, uint a_uiPass);
    virtual void    saveDataAttributesHelper(property_tree& tree, const phantom::data& a_Data);
    virtual void    loadDataAttributesHelper( const property_tree& tree, const phantom::data& a_Data );
    virtual void    loadData(uint a_uiSerializationFlag, const phantom::data& a_Data, uint guid);
    
protected:
    list<data>      m_DataRestoreQueue;
    list<data>      m_DataAbortQueue;
	property_tree	m_CacheTree;
	vector<uint>    m_ParentGuids;
};

o_namespace_end(phantom, serialization)

#endif // serialization_XmlFileTreeNode_h__