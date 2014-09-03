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

#ifndef serialization_BinaryFileTreeNode_h__
#define serialization_BinaryFileTreeNode_h__
// #pragma message("Including "__FILE__)


/* ****************** Includes ******************* */
#include "phantom/serialization/FileTreeNode.h"
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/fstream.hpp>
/* **************** Declarations ***************** */
o_fwd(class, phantom, serialization, BinaryFileTreeDataBase)
o_fwd(class, phantom, serialization, BinaryFileTreeDataStateBase)
o_declareN(class, (phantom, serialization), BinaryFileTreeNode)
/* *********************************************** */

o_namespace_begin(phantom, serialization)

class o_export BinaryFileTreeNode : public FileTreeNode
{
    friend class BinaryFileTreeDataStateBase;

public:
    BinaryFileTreeNode(BinaryFileTreeDataBase* a_pOwnerDataBase, uint guid, BinaryFileTreeNode* a_pParentNode);

    virtual void    saveIndex() ;
    virtual void    saveTypes() ;
    virtual void    saveAttributes() ;
    virtual void    saveDataProperties(uint a_uiSerializationFlag, const phantom::data& a_Data, uint guid) ;
    virtual void    saveDataAttributes();
    virtual void    saveDataAttributes(const phantom::data& a_Data, uint guid);

    virtual void    loadTypes();
    virtual void    loadAttributes();
    virtual void    loadDataAttributes();
    virtual void    loadDataAttributes(const phantom::data& a_Data, uint guid);
    virtual bool    canLoad(vector<string>* missing_types) const;
    virtual void    cache();
    virtual void    build(vector<data>& a_Data);
    virtual void    deserialize(uint a_uiSerializationFlag, vector<data>& a_Data);
    virtual void    uncache();
    virtual void    restore(uint a_uiSerializationFlag, vector<data>& a_Data);
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

protected:
    void            saveDataAttributesHelper(vector<string>& a_Values, const phantom::data& a_Data);
    void            loadDataAttributesHelper(const vector<string>& a_Values, const phantom::data& a_Data);
    void            loadDataProperties(uint a_uiSerializationFlag, const phantom::data& a_Data, uint guid);

	void			readBinary(const string& a_strPath, byte* a_pBuffer, uint& a_uiBufferSize) const;
	void			writeBinary(const string& a_strPath, const byte* a_pBuffer, uint a_uiBufferSize) const;
    
protected:
    list<data>      m_DataRestoreQueue;
    list<data>      m_DataAbortQueue;
	byte*			m_pBuffer;
	uint			m_uiBufferSize;
	uint			m_uiBufferPos;
	vector<uint>    m_ParentGuids;
};

o_namespace_end(phantom, serialization)

#endif // serialization_BinaryFileTreeNode_h__