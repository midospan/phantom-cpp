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

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include "phantom/serialization/BinaryFileTreeNode.h"
#include "phantom/serialization/BinaryFileTreeDataBase.h"
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/fstream.hpp>
#include <phantom/serialization/BinaryFileTreeDataStateBase.h>
#include <phantom/serialization/BinaryFileTreeDataStateBase.hxx>
/* *********************************************** */
o_registerN((phantom, serialization), BinaryFileTreeDataStateBase);

o_namespace_begin(phantom, serialization)

void BinaryFileTreeDataStateBase::loadState(Node* a_pNode, uint a_uiStateId)
{
    BinaryFileTreeNode* pNode = as<BinaryFileTreeNode*>(a_pNode);
    o_assert(pNode);

    BinaryFileTreeDataBase* pDB = static_cast<BinaryFileTreeDataBase*>(pNode->getOwnerDataBase());
    o_assert(pDB);

    const string & path = statePath(a_pNode, a_uiStateId);

    if (hasStateSaved(a_pNode, a_uiStateId))
	{
		const BinaryFileTreeNode::data_vector& nodeData = pNode->m_Data;
		BinaryFileTreeNode::data_vector::const_iterator it = nodeData.begin();
		BinaryFileTreeNode::data_vector::const_iterator end = nodeData.end();
		for(;it!=end;++it)
		{
			const phantom::data& d = *it;
			loadDataState(d, pDB->getGuid(d), a_pNode, a_uiStateId);
		}
	}
}

void BinaryFileTreeDataStateBase::saveState(Node* a_pNode, uint a_uiStateId)
{
    BinaryFileTreeNode* pNode = as<BinaryFileTreeNode*>(a_pNode);
    o_assert(pNode);

    BinaryFileTreeDataBase* pDB = static_cast<BinaryFileTreeDataBase*>(pNode->getOwnerDataBase());

    const string & path = statePath(a_pNode, a_uiStateId);
    if(NOT(boost::filesystem::exists(path.c_str())))
    {
        boost::filesystem::create_directories(path.c_str());
    }
    const BinaryFileTreeNode::data_vector& nodeData = pNode->m_Data;
    BinaryFileTreeNode::data_vector::const_iterator it = nodeData.begin();
    BinaryFileTreeNode::data_vector::const_iterator end = nodeData.end();
    for(;it!=end;++it)
    {
        const phantom::data& d = *it;
        saveDataState(d, pDB->getGuid(d), a_pNode, a_uiStateId);
    }
}

void BinaryFileTreeDataStateBase::loadDataState(const phantom::data& a_Data, uint guid, Node* a_pNode, uint a_uiStateId)
{
    BinaryFileTreeDataBase* pDB = static_cast<BinaryFileTreeDataBase*>(a_pNode->getOwnerDataBase());
	byte buffer[1000000];
	byte* pBuffer = &(buffer[0]);
	uint uiBufferSize = 0;
    readBinary(dataPath(a_Data, guid, a_pNode, a_uiStateId), pBuffer, uiBufferSize);
    a_Data.type()->deserialize(a_Data.address(), (const byte*&)pBuffer, m_uiSerializationFlag, pDB);
}

void BinaryFileTreeDataStateBase::saveDataState(const phantom::data& a_Data, uint guid, Node* a_pNode, uint a_uiStateId)
{
    BinaryFileTreeDataBase* pDB = static_cast<BinaryFileTreeDataBase*>(a_pNode->getOwnerDataBase());
	byte buffer[1000000];
	byte* pBuffer = &(buffer[0]);
	a_Data.type()->serialize(a_Data.address(), pBuffer, m_uiSerializationFlag, pDB);
    writeBinary(dataPath(a_Data, guid, a_pNode, a_uiStateId), &(buffer[0]), pBuffer - &(buffer[0]));
}

void BinaryFileTreeDataStateBase::readBinary(const string& a_strPath, byte* a_pBuffer, uint& a_uiBufferSize)
{
	FILE* pFile = fopen(a_strPath.c_str() , "rb");
	if (pFile != NULL)
	{
		byte* pBuffer = a_pBuffer;
		a_uiBufferSize = 0;
		while (NOT(feof(pFile)))
		{
			*reinterpret_cast<char*>(pBuffer) = fgetc(pFile);
			pBuffer++;
			a_uiBufferSize++;
		}
		fclose(pFile);
	}

	/*boost::filesystem::ifstream file(a_strPath.c_str(), boost::filesystem::ifstream::binary);
	if (file.is_open())
	{
		byte* pBuffer = a_pBuffer;
		a_uiBufferSize = 0;
		while (NOT(file.eof()))
		{
			file.read((char*)pBuffer, 1);
			pBuffer++;
			a_uiBufferSize++;
		}
		file.close();
	}*/
}

void BinaryFileTreeDataStateBase::writeBinary(const string& a_strPath, byte* a_pBuffer, uint a_uiBufferSize)
{
	FILE* pFile = fopen(a_strPath.c_str() , "wb");
	if (pFile != NULL)
	{
		for (uint i = 0; i < a_uiBufferSize; i++)
		{
			fputc((reinterpret_cast<char*>(a_pBuffer))[i], pFile);
		}
		fclose(pFile);
	}

	/*std::ofstream file(a_strPath.c_str(), std::ios::binary | std::ios::out);
	if (file.is_open())
	{
		file.write(reinterpret_cast<char*>(a_pBuffer), a_uiBufferSize);
		file.close();
	}*/
}

o_namespace_end(phantom, serialization)