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

#ifndef serialization_PackageDataBase_h__
#define serialization_PackageDataBase_h__


/* ****************** Includes ******************* */
#include "DataBase.h"
/* *********************************************** */
/* The *.classdef.h file must be the last #include */
#include "phantom/def_export.h"
/* **************** Declarations ***************** */
namespace boost { namespace filesystem { class path; } }
/* *********************************************** */

o_namespace_begin(phantom, serialization)


class o_export PackageDataBase : public DataBase
{
public:

	struct PackageDataBaseBuffer
	{
		uint	m_uiBufferSize;
		byte*	m_pBuffer;
		byte*	m_pCurrent;
	};

    PackageDataBase(const string& a_strUrl, uint a_uiSerializationFlag);
    o_destructor ~PackageDataBase();
	
	PackageDataBaseBuffer*			getBuffer();

	virtual void					loadNodeEntries();
    virtual void					unloadNodeEntries();

	virtual boolean					hasNodeEntry(Node* a_pNode) const;
	virtual boolean					hasDataEntry(const data& a_Data, uint a_uiGuid, Node* a_pOwnerNode) const;

	virtual uint					generateGuid();
	virtual void					releaseGuid(uint a_uiGuid);

	virtual void					createDataEntry(const phantom::data& a_Data, uint a_uiGuid, Node* a_pOwnerNode);
	virtual void					destroyDataEntry(const phantom::data& a_Data, uint a_uiGuid, Node* a_pOwnerNode);
	virtual void					moveDataEntry(const phantom::data& a_Data, uint a_uiGuid, Node* a_pOldParent, Node* a_pNewParent);

	virtual void					createNodeEntry(Node* a_pNode);
	virtual void					destroyNodeEntry(Node* a_pNode);
	virtual void					moveNodeEntry(Node* a_pNode, Node* a_pNewParent); 


protected:

	void							loadNodeEntriesHelper(Node* a_pNode, const boost::filesystem::path& a_Path);


protected:

	PackageDataBaseBuffer			m_Buffer;
};

o_namespace_end(phantom, serialization)

o_classNS((phantom, serialization), PackageDataBase, (DataBase))
{
    o_reflection
	{

	};
};
o_exposeN((phantom, serialization), PackageDataBase);

#endif //serialization_PackageDataBase_h__