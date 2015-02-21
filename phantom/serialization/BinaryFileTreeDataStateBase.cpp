/* TODO LICENCE HERE */

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

    BinaryFileTreeDataBase* pDB = static_cast<BinaryFileTreeDataBase*>(pNode->getDataBase());
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

    BinaryFileTreeDataBase* pDB = static_cast<BinaryFileTreeDataBase*>(pNode->getDataBase());

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
    BinaryFileTreeDataBase* pDB = static_cast<BinaryFileTreeDataBase*>(a_pNode->getDataBase());
	byte buffer[1000000];
	byte* pBuffer = &(buffer[0]);
	uint uiBufferSize = 0;
    readBinary(dataPath(a_Data, guid, a_pNode, a_uiStateId), pBuffer, uiBufferSize);
    a_Data.type()->deserialize(a_Data.address(), (const byte*&)pBuffer, m_uiSerializationFlag, pDB);
}

void BinaryFileTreeDataStateBase::saveDataState(const phantom::data& a_Data, uint guid, Node* a_pNode, uint a_uiStateId)
{
    BinaryFileTreeDataBase* pDB = static_cast<BinaryFileTreeDataBase*>(a_pNode->getDataBase());
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