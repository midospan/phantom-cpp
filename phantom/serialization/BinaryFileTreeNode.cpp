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
#include <phantom/serialization/BinaryFileTreeNode.h>
#include <phantom/serialization/BinaryFileTreeNode.hxx>
#include <phantom/serialization/BinaryFileTreeDataBase.h>
#include <boost/iostreams/device/mapped_file.hpp>
#include <iostream>
#include <stdio.h>
/* ** The Class Header must be the last #include * */
/* *********************************************** */
o_registerN((phantom, serialization), BinaryFileTreeNode);

o_namespace_begin(phantom, serialization)
    
BinaryFileTreeNode::BinaryFileTreeNode(BinaryFileTreeDataBase* a_pOwnerDataBase, uint guid, BinaryFileTreeNode* a_pParentNode)
    : FileTreeNode(a_pOwnerDataBase, guid, a_pParentNode) 
{

}

void BinaryFileTreeNode::saveDataAttributes()
{

}

void BinaryFileTreeNode::saveDataAttributes(const phantom::data& a_Data, uint guid)
{

}

void BinaryFileTreeNode::saveData(uint a_uiSerializationFlag, const phantom::data& a_Data, uint guid) 
{   
	// Serialize the data
	byte buffer[1000000];
	byte* pBuffer = &(buffer[0]);
	a_Data.type()->serialize(a_Data.address(), pBuffer, a_uiSerializationFlag, m_pOwnerDataBase);

	// Write the data file
	const string& path = static_cast<BinaryFileTreeDataBase*>(m_pOwnerDataBase)->dataPath(a_Data, guid, this);
    writeBinary(path.c_str(), &(buffer[0]), pBuffer - &(buffer[0]));
}

void BinaryFileTreeNode::loadData(uint a_uiSerializationFlag, const phantom::data& a_Data, uint guid) 
{
	// Read the data file
	byte buffer[1000000];
	byte* pBuffer = &(buffer[0]);
	uint uiBufferSize = 0;
    const string& path = static_cast<BinaryFileTreeDataBase*>(m_pOwnerDataBase)->dataPath(a_Data, guid, this);
    readBinary(path.c_str(), pBuffer, uiBufferSize);

	// Deserialize the data
	pBuffer = &(buffer[0]);
    a_Data.type()->deserialize(a_Data.address(), (const byte*&)pBuffer, a_uiSerializationFlag, m_pOwnerDataBase);
}

void BinaryFileTreeNode::saveData(uint a_uiSerializationFlag)
{
    data_vector::iterator it = m_Data.begin();
    data_vector::iterator end = m_Data.end();

    for(;it != end; ++it)
    {
        void* pAddress = it->address();
        uint guid = m_pOwnerDataBase->getGuid(pAddress);
        saveData(a_uiSerializationFlag, *it, guid);
    }
}

void BinaryFileTreeNode::saveIndex()
{
    data_vector::iterator it = m_Data.begin();
    data_vector::iterator end = m_Data.end();

	byte buffer[1000000];
	byte* pBuffer = &(buffer[0]);
    BinaryFileTreeDataBase* pDB = static_cast<BinaryFileTreeDataBase*>(m_pOwnerDataBase);
    for(;it != end; ++it)
    {
        void* pAddress = it->address();
        reflection::Type* pType = it->type();
        uint guid = getOwnerDataBase()->getGuid(pAddress);
		uint typeGuid = pType->getGuid();

		// Add type guid to buffer
		*reinterpret_cast<uint*>(pBuffer) = typeGuid;
		pBuffer += sizeof(uint);

		// Add guid to buffer
		*reinterpret_cast<uint*>(pBuffer) = guid;
		pBuffer += sizeof(uint);

		// Add parent guid to buffer
		const data& parent = m_pOwnerDataBase->getSubDataOwner(pAddress);
        if(NOT(parent.isNull()))
        {
			// Add separator to buffer
			*reinterpret_cast<char*>(pBuffer) = '|';
			pBuffer += sizeof(char);

            uint parentGuid = m_pOwnerDataBase->getGuid(parent);
			*reinterpret_cast<uint*>(pBuffer) = parentGuid;
			pBuffer += sizeof(uint);
        }
    }

	uint uiBufferSize = pBuffer - &(buffer[0]);
    const string& self_path = pDB->nodePath(this, getGuid(), getParentNode());
    writeBinary(self_path+'/'+"index", &(buffer[0]), uiBufferSize);
}

void BinaryFileTreeNode::saveAttributes()
{

}

void BinaryFileTreeNode::saveDataAttributesHelper(vector<string>& a_Values, const phantom::data& a_Data)
{

}

void BinaryFileTreeNode::loadDataAttributesHelper(const vector<string>& a_Values, const phantom::data& a_Data)
{

}

void BinaryFileTreeNode::loadAttributes()
{

}

void BinaryFileTreeNode::loadDataAttributes()
{

}

void BinaryFileTreeNode::loadDataAttributes(const phantom::data& a_Data, uint guid) 
{

}

bool BinaryFileTreeNode::canLoad(vector<string>* missing_types) const
{
	byte buffer[1000000];
	byte* pBuffer = &(buffer[0]);
	uint uiBufferSize = 0;
    BinaryFileTreeDataBase* pDB = static_cast<BinaryFileTreeDataBase*>(m_pOwnerDataBase);    
    const string& self_path = pDB->nodePath(const_cast<BinaryFileTreeNode*>(this), getGuid(), getParentNode());
    readBinary(self_path+'/'+"index", pBuffer, uiBufferSize);
        
    boolean result = true;
    
	// TODO : today
	/*vector<uint> parentGuids;
    for(;it != end; ++it)
    {
        const property_tree& sub_tree = it->second;
        string typeName = decodeQualifiedDecoratedNameFromIdentifierName(sub_tree.get<string>("typename"));
        reflection::Type* pType = m_pOwnerDataBase->solveTypeByName(typeName);
        if(pType == NULL)
        {
            missing_types.push_back(typeName);
            result = false;
        }
    }*/
    return result;
}

void BinaryFileTreeNode::cache()
{
    o_assert(m_Data.empty(), "already cached");

	byte buffer[1000000];
	byte* pBuffer = &(buffer[0]);
	uint uiBufferSize = 0;
    BinaryFileTreeDataBase* pDB = static_cast<BinaryFileTreeDataBase*>(m_pOwnerDataBase);
    const string& self_path = pDB->nodePath(this, getGuid(), getParentNode());
    readBinary(self_path+'/'+"index", pBuffer, uiBufferSize);

	pBuffer = &(buffer[0]);
    vector<uint> parentGuids;
    uint i = 0;
	if (uiBufferSize > 1)
	{
		while(i < uiBufferSize - 1)
		{
			// Read type guid
			byte* pTmp = &(pBuffer[i]);
			uint uiTypeGuid = *reinterpret_cast<uint const*>(pTmp);
			i += sizeof(uint);

			// Read guid
			pTmp = &(pBuffer[i]);
			uint uiGuid = *reinterpret_cast<uint const*>(pTmp);
			i += sizeof(uint);

			// Separator ?
			uint uiParentGuid = 0xFFFFFFFF;
			if (pBuffer[i] == '|')
			{
				i += sizeof(char);
				pTmp = &(pBuffer[i]);
				uiParentGuid = *reinterpret_cast<uint const*>(pTmp);
				i += sizeof(uint);
			}
			parentGuids.push_back(uiParentGuid);

			o_assert(uiGuid != 0xFFFFFFFF);
        
			reflection::Type* pType = phantom::typeByGuid(uiTypeGuid);//m_pOwnerDataBase->solveTypeByName(decodeQualifiedDecoratedNameFromIdentifierName(strTypename));
			if(pType == NULL)
			{
				switch(m_pOwnerDataBase->getActionOnMissingType())
				{
				case DataBase::e_ActionOnMissingType_IgnoreAndDestroyData:
					continue;
				case DataBase::e_ActionOnMissingType_NotifyAndDestroyData:
					continue;
				case DataBase::e_ActionOnMissingType_Exception:
					o_exception(phantom::exception::unknown_reflection_type_exception, boost::lexical_cast<phantom::string>((void*)uiTypeGuid).c_str()); // TODO : change "" by type name
				}
			}

			// TODO : specialize lexical_cast for : uint guid = reinterpret_cast<uint>(phantom::lexical_cast<void*>(strGuid));
			phantom::data the_data(pType->allocate(),pType);
			storeData(the_data);
			m_DataRestoreQueue.push_back(the_data);
			pDB->registerData(the_data, uiGuid, this);
		}
		size_t j = 0;
		size_t count = m_Data.size();
		for(;j<count;++j)
		{
			uint parentGuid = parentGuids[j];
			if(parentGuid != 0xffffffff)
			{
				const phantom::data& parentData = pDB->getData(parentGuid);
				o_assert(NOT(parentData.isNull()));
				pDB->registerSubDataOwner(m_Data[j], parentData);
			}
		}
	}
}

void BinaryFileTreeNode::build()
{
    BinaryFileTreeDataBase* pDB = static_cast<BinaryFileTreeDataBase*>(m_pOwnerDataBase);
  
    data_vector::iterator end = m_Data.end();
    // Build ( Construction + Installation)
    
    data_vector::iterator it = m_Data.begin();
    for(;it != end; ++it)
    {
        it->type()->build(it->address());
    }
}

void BinaryFileTreeNode::deserialize(uint a_uiSerializationFlag)
{
    // Deserialization
    BinaryFileTreeDataBase* pDB = static_cast<BinaryFileTreeDataBase*>(m_pOwnerDataBase);
    data_vector::iterator it = m_Data.begin();
    data_vector::iterator end = m_Data.end();
    for(;it != end; ++it)
    {
        void* pAddress = it->address();
        reflection::Type* pType = it->type();
        uint guid = pDB->getGuid(pAddress);
        const string& path = pDB->dataPath(*it, guid, pDB->getNode(pAddress));
		byte buffer[1000000];
		byte* pBuffer = &(buffer[0]);
		uint uiBufferSize = 0;
        readBinary(path.c_str(), pBuffer, uiBufferSize);

		pBuffer = &(buffer[0]);
		pType->deserialize(pAddress, (const byte*&)pBuffer, a_uiSerializationFlag, pDB);
    }
}

void BinaryFileTreeNode::restore(uint a_uiSerializationFlag)
{
    BinaryFileTreeDataBase* pDB = static_cast<BinaryFileTreeDataBase*>(m_pOwnerDataBase);

    uint pass = 0;
    int counter = 0;
    int cycle_count = m_DataRestoreQueue.size();
    while(cycle_count)
    {
        // extract the data from the queue
        phantom::data d = m_DataRestoreQueue.front();
        m_DataRestoreQueue.pop_front();
        
        restore_state state = d.type()->restore(d.address(), a_uiSerializationFlag, pass) ;;
        switch(state)
        {
        case restore_complete: // if success, we do nothing
            break;
        case restore_incomplete: // if incomplete, we reinject the data at the end of the queue to apply to it another pass later
            m_DataRestoreQueue.push_back(d);
            break;
        case restore_failed: // if failed we store the data in the destruction queue which will be handled at the node loading end
            m_DataAbortQueue.push_back(d);
            break;
        default:
            o_assert(false, "state unknown, anormal, probably a segfault somewhere which overrided the restore_state enum value");
            break;
        }
        if((++counter) == cycle_count) // reached the cycle end => increment pass, reset counters
        {
            ++pass;
            cycle_count = m_DataRestoreQueue.size();
            counter = 0;
        }
    }
}

void BinaryFileTreeNode::unbuild()
{
    BinaryFileTreeDataBase* pDB = static_cast<BinaryFileTreeDataBase*>(m_pOwnerDataBase);

    data_vector::iterator end = m_Data.end();
    // teardown ( Destruction + Uninstallation + Termination )

    data_vector::iterator it = m_Data.begin();
    for(;it != end; ++it)
    {
        it->type()->teardown(it->address());
    }

}

void BinaryFileTreeNode::uncache()
{
    BinaryFileTreeDataBase* pDB = static_cast<BinaryFileTreeDataBase*>(m_pOwnerDataBase);

    data_vector::iterator it = m_Data.begin();
    data_vector::iterator end = m_Data.end();
    for(;it != end; ++it)
    {
        const phantom::data& d = *it;
        pDB->unregisterData(d);
        d.type()->deallocate(d.address());
    }
    m_Data.clear();
}

void BinaryFileTreeNode::configure()
{
    // Remove and destroy aborted data
    if(m_DataAbortQueue.size())
    {
        o_foreach(data d, m_DataAbortQueue)
        {
            abortData(d);
        }
        saveIndex();
    }
    m_DataAbortQueue.clear();
}

void BinaryFileTreeNode::unconfigure()
{
}

void BinaryFileTreeNode::readBinary(const string& a_strPath, byte* a_pBuffer, uint& a_uiBufferSize) const
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

void BinaryFileTreeNode::writeBinary(const string& a_strPath, const byte* a_pBuffer, uint a_uiBufferSize) const
{
	FILE* pFile = fopen(a_strPath.c_str() , "wb");
	if (pFile != NULL)
	{
		for (uint i = 0; i < a_uiBufferSize; i++)
		{
			fputc((reinterpret_cast<const char*>(a_pBuffer))[i], pFile);
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

void BinaryFileTreeNode::preCache()
{
	m_pBuffer = (byte*)malloc(1000000 * sizeof(byte));
	byte* pBuffer = &(m_pBuffer[0]);
	m_uiBufferSize = 0;
	BinaryFileTreeDataBase* pDB = static_cast<BinaryFileTreeDataBase*>(m_pOwnerDataBase);
	const string& self_path = pDB->nodePath(this, getGuid(), getParentNode());
	readBinary(self_path+'/'+"index", pBuffer, m_uiBufferSize);
	m_uiBufferPos = 0;
}

bool BinaryFileTreeNode::cacheOne(uint a_uiIndex)
{
	BinaryFileTreeDataBase* pDB = static_cast<BinaryFileTreeDataBase*>(m_pOwnerDataBase);
	byte* pBuffer = &(m_pBuffer[0]);
	if (m_uiBufferPos < m_uiBufferSize-1)
	{
		// Read type guid
		byte* pTmp = &(pBuffer[m_uiBufferPos]);
		uint uiTypeGuid = *reinterpret_cast<uint const*>(pTmp);
		m_uiBufferPos += sizeof(uint);

		// Read guid
		pTmp = &(pBuffer[m_uiBufferPos]);
		uint uiGuid = *reinterpret_cast<uint const*>(pTmp);
		m_uiBufferPos += sizeof(uint);

		// Separator ?
		uint uiParentGuid = 0xFFFFFFFF;
		if (pBuffer[m_uiBufferPos] == '|')
		{
			m_uiBufferPos += sizeof(char);
			pTmp = &(pBuffer[m_uiBufferPos]);
			uiParentGuid = *reinterpret_cast<uint const*>(pTmp);
			m_uiBufferPos += sizeof(uint);
		}
		m_ParentGuids.push_back(uiParentGuid);

		o_assert(uiGuid != 0xFFFFFFFF);

		reflection::Type* pType = phantom::typeByGuid(uiTypeGuid);

		// TODO : specialize lexical_cast for : uint guid = reinterpret_cast<uint>(phantom::lexical_cast<void*>(strGuid));
		phantom::data the_data(pType->allocate(),pType);
		storeData(the_data);
		m_DataRestoreQueue.push_back(the_data);
		pDB->registerData(the_data, uiGuid, this);

		return false;
	}

	return true;
}

void BinaryFileTreeNode::postCache()
{
	BinaryFileTreeDataBase* pDB = static_cast<BinaryFileTreeDataBase*>(m_pOwnerDataBase);

	size_t i = 0;
	size_t count = m_Data.size();
	for(;i<count;++i)
	{
		uint parentGuid = m_ParentGuids[i];
		if(parentGuid != 0xffffffff)
		{
			const phantom::data& parentData = pDB->getData(parentGuid);
			o_assert(NOT(parentData.isNull()));
			pDB->registerSubDataOwner(m_Data[i], parentData);
		}
	}

	m_ParentGuids.clear();
	free(m_pBuffer);
}

void BinaryFileTreeNode::uncacheOne(const phantom::data& a_Data)
{
	data_vector::iterator it = std::find(m_Data.begin(), m_Data.end(), a_Data);
	if (it != m_Data.end())
	{
		m_Data.erase(it);
	}
	BinaryFileTreeDataBase* pDB = static_cast<BinaryFileTreeDataBase*>(m_pOwnerDataBase);
	pDB->unregisterData(a_Data);
	a_Data.type()->deallocate(a_Data.address());
}

void BinaryFileTreeNode::buildOne(const phantom::data& a_Data)
{
	BinaryFileTreeDataBase* pDB = static_cast<BinaryFileTreeDataBase*>(m_pOwnerDataBase);
	a_Data.type()->build(a_Data.address());
}

void BinaryFileTreeNode::unbuildOne(const phantom::data& a_Data)
{
	BinaryFileTreeDataBase* pDB = static_cast<BinaryFileTreeDataBase*>(m_pOwnerDataBase);
	a_Data.type()->teardown(a_Data.address());
}

void BinaryFileTreeNode::deserializeOne(const phantom::data& a_Data, uint a_uiSerializationFlag)
{
	BinaryFileTreeDataBase* pDB = static_cast<BinaryFileTreeDataBase*>(m_pOwnerDataBase);
	void* pAddress = a_Data.address();
	reflection::Type* pType = a_Data.type();
	uint guid = pDB->getGuid(pAddress);
	const string& path = pDB->dataPath(a_Data, guid, pDB->getNode(pAddress));
	byte buffer[1000000];
	byte* pBuffer = &(buffer[0]);
	uint uiBufferSize = 0;
	readBinary(path.c_str(), pBuffer, uiBufferSize);

	pBuffer = &(buffer[0]);
	pType->deserialize(pAddress, (const byte*&)pBuffer, a_uiSerializationFlag, pDB);
}

bool BinaryFileTreeNode::restoreOne(const phantom::data& a_Data, uint a_uiSerializationFlag, uint a_uiPass)
{
	BinaryFileTreeDataBase* pDB = static_cast<BinaryFileTreeDataBase*>(m_pOwnerDataBase);
	restore_state state = a_Data.type()->restore(a_Data.address(), a_uiSerializationFlag, a_uiPass);
	return state == restore_complete;
}

void BinaryFileTreeNode::saveTypes()
{ 
    byte buffer[1000000];
    byte* pBuffer = &(buffer[0]);
    BinaryFileTreeDataBase* pDB = static_cast<BinaryFileTreeDataBase*>(m_pOwnerDataBase);
    uint count = m_Types.size();

    extension::serializer<uint>::serialize(&count, pBuffer, 0xffffffff, nullptr);

    auto it = m_Types.begin();
    auto end = m_Types.end();
    for(;it != end; ++it)
    {
        reflection::Class* pClass = classOf(it->second);
        uint classGuid = pClass->getGuid();

        // Add type guid to buffer
        extension::serializer<uint>::serialize(&classGuid, pBuffer, 0xffffffff, 0);

        // Add guid to buffer
        const string & typeName = it->first;
        typeOf<string>()->serialize(&typeName, pBuffer, 0xffffffff, nullptr);

        pClass->serialize(it->second, pBuffer, 0xffffffff, nullptr);
    }

    uint uiBufferSize = pBuffer - &(buffer[0]);
    const string& self_path = pDB->nodePath(this, getGuid(), getParentNode());
    writeBinary(self_path+'/'+"types", &(buffer[0]), uiBufferSize);
}

void BinaryFileTreeNode::loadTypes()
{
    byte* pBaseBuffer = (byte*)malloc(1000000 * sizeof(byte));
    BinaryFileTreeDataBase* pDB = static_cast<BinaryFileTreeDataBase*>(m_pOwnerDataBase);
    const string& self_path = pDB->nodePath(this, getGuid(), getParentNode());
    size_t bufferSize = 0;
    readBinary(self_path+'/'+"types", pBaseBuffer, bufferSize);

    const byte* pBuffer = pBaseBuffer;
    const byte*& pBufferRef = pBuffer;
    m_uiBufferSize = 0;
    uint count;
    extension::serializer<uint>::deserialize(&count, pBufferRef, 0xffffffff, nullptr);

    for(size_t i = 0; i<count; ++i)
    {
        uint classGuid;

        // Add type guid to buffer

        // Add type guid to buffer
        extension::serializer<uint>::deserialize(&classGuid, pBufferRef, 0xffffffff, 0);

        reflection::Class* pClass = pDB->solveTypeById(classGuid)->asClass();

        // Add guid to buffer
        string typeName;
        typeOf<string>()->deserialize(&typeName, pBufferRef, 0xffffffff, nullptr);

        void* pType = pClass->allocate();
        pClass->construct(pType);
        pClass->install(pType, 0);
        pClass->deserialize(pType, pBufferRef, 0xffffffff, nullptr);
        uint pass = 0;
        restore_state state;  
        while((state = pClass->restore(pType, 0xffffffff, pass++)) == restore_incomplete);
        addType(as<reflection::Type*>(pType));
    }
    free(pBaseBuffer);
}

o_namespace_end(phantom, serialization)
