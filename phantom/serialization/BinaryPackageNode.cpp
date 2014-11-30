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
#if o__bool__use_custom_stl_partioned_allocator OR o__bool__use_custom_stl_contiguous_allocator
#include <boost/property_tree_custom/xml_parser.hpp>
#else 
#include <boost/property_tree/xml_parser.hpp>
#endif
#include <phantom/serialization/BinaryPackageDataBase.h>
#include <phantom/serialization/BinaryPackageNode.h>
#include <phantom/serialization/BinaryPackageNode.hxx>
/* *********************************************** */
o_registerN((phantom, serialization), BinaryPackageNode);

o_namespace_begin(phantom, serialization)

BinaryPackageNode::BinaryPackageNode(BinaryPackageDataBase* a_pDataBase, uint a_uiGuid, BinaryPackageNode* a_pParentNode)
: PackageNode(a_pDataBase, a_uiGuid, a_pParentNode) 
{

}

void BinaryPackageNode::saveDataAttributes()
{
    data_vector::iterator it = m_Data.begin();
    data_vector::iterator end = m_Data.end();

    for(;it != end; ++it)
    {
        void* pAddress = it->address();
        uint guid = m_pDataBase->getGuid(pAddress);
        saveDataAttributes(*it, guid);
    }
}

void BinaryPackageNode::saveDataAttributes(const phantom::data& a_Data, uint a_uiGuid)
{
	saveDataAttributesHelper(a_Data);
}

void BinaryPackageNode::loadDataAttributes()
{
    data_vector::iterator end = m_Data.end();
    data_vector::iterator it = m_Data.begin();
    for(;it != end; ++it)
    {
        loadDataAttributes(*it, m_pDataBase->getGuid(*it));
    }
}

void BinaryPackageNode::loadDataAttributes(const phantom::data& a_Data, uint a_uiGuid) 
{
    loadDataAttributesHelper(a_Data);
}

void BinaryPackageNode::saveDataProperties(uint a_uiSerializationFlag, const phantom::data& a_Data, uint a_uiGuid) 
{
	BinaryPackageDataBase* pDB = static_cast<BinaryPackageDataBase*>(m_pDataBase);
	PackageDataBase::PackageDataBaseBuffer* pBuffer = pDB->getBuffer();

    // a_Data.type()->serialize(a_Data.address(), pBuffer->m_pCurrent, a_uiSerializationFlag, m_pDataBase);
    // saveDataAttributesHelper(a_Data);
}

void BinaryPackageNode::loadDataProperties(uint a_uiSerializationFlag, const phantom::data& a_Data, uint a_uiGuid) 
{
	BinaryPackageDataBase* pDB = static_cast<BinaryPackageDataBase*>(m_pDataBase);
	PackageDataBase::PackageDataBaseBuffer* pBuffer = pDB->getBuffer();

    //a_Data.type()->deserialize(a_Data.address(), pBuffer->m_pCurrent, a_uiSerializationFlag, m_pDataBase);
    loadDataAttributesHelper(a_Data);
}

void BinaryPackageNode::saveIndex()
{
    /*property_tree index_tree;

    data_vector::iterator it = m_Data.begin();
    data_vector::iterator end = m_Data.end();

    index_tree.add_child("index", property_tree());

    BinaryPackageDataBase* pDB = static_cast<BinaryPackageDataBase*>(m_pDataBase);
    for(;it != end; ++it)
    {
        void* pAddress = it->address();
        reflection::Type* pType = it->type();
        uint guid = getDataBase()->getGuid(pAddress);
        property_tree dataPath;
        dataPath.put<string>("typename", encodeQualifiedDecoratedNameToIdentifierName(pType->getQualifiedDecoratedName()));
        dataPath.put<string>("guid", phantom::lexical_cast<string>(reinterpret_cast<void*>(guid)));
        const data& parent = m_pDataBase->getComponentDataOwner(pAddress);
        if(NOT(parent.isNull()))
        {
            uint parentGuid = m_pDataBase->getGuid(parent);
            dataPath.put<string>("parent", phantom::lexical_cast<string>(reinterpret_cast<void*>(parentGuid)));
        }
        index_tree.add_child("index.data", dataPath);
    }*/

    /*const string& self_path = pDB->nodePath(this, getGuid(), getParentNode());
    property_tree_namespace::write_xml(self_path+'/'+"index", index_tree);*/
}

void BinaryPackageNode::saveDataAttributesHelper(const phantom::data& a_Data)
{
    BinaryPackageDataBase* pDB = static_cast<BinaryPackageDataBase*>(m_pDataBase);
	PackageDataBase::PackageDataBaseBuffer* pBuffer = pDB->getBuffer();

	const string* pDataMemberValues = pDB->getDataAttributeValues(a_Data);
    if(pDataMemberValues != NULL) 
    {
        size_t i = 0;
        size_t fieldCount = pDB->getAttributeCount();
        for(;i<fieldCount;++i)
        {
			//pBuffer->m_pCurrent
            //a_Tree.put<string>(pDB->getDataMemberName(i), pDataMemberValues[i]);
        }
    }
}

void BinaryPackageNode::loadDataAttributesHelper(const phantom::data& a_Data)
{
    /*BinaryPackageDataBase* pDB = static_cast<BinaryPackageDataBase*>(m_pDataBase);

    property_tree::const_iterator it = a_Tree.begin();
    property_tree::const_iterator end = a_Tree.end();
    for(;it != end; ++it)
    {
        const property_tree& attribute_tag = it->second;
        size_t attributeIndex = m_pDataBase->getDataMemberIndex(it->first);
        if(attributeIndex != DataBase::e_Constant_InvalidAttributeIndex)
        {
            m_pDataBase->setDataAttributeValue(a_Data, attributeIndex, attribute_tag.data());
        }
    }*/
}

void BinaryPackageNode::saveAttributes()
{
    BinaryPackageDataBase* pDB = static_cast<BinaryPackageDataBase*>(m_pDataBase);

    const string* pDataMemberValues = pDB->getNodeAttributeValues(this);
    if(pDataMemberValues != NULL) 
    {
        size_t i = 0;
        size_t fieldCount = pDB->getAttributeCount();
        for(;i<fieldCount;++i)
        {
			//buffer
            //node_attribute_tree.put<string>(pDB->getDataMemberName(i), pDataMemberValues[i]);
        }
    }

    /*const string& self_path = pDB->nodePath(this, getGuid(), getParentNode());
    property_tree_namespace::write_xml(self_path+'/'+"attributes", attribute_tree);*/
}

void BinaryPackageNode::loadAttributes()
{
    // write data base info
    property_tree attribute_tree;
    
    BinaryPackageDataBase* pDB = static_cast<BinaryPackageDataBase*>(m_pDataBase);
    /*const string& self_path = pDB->nodePath(this, getGuid(), getParentNode());
    property_tree_namespace::read_xml(self_path+'/'+"attributes", attribute_tree);
    if(attribute_tree.empty()) return;

    boost::optional<property_tree&> opt_datalist_tree = attribute_tree.get_child_optional("attributes");
    if(opt_datalist_tree.is_initialized())
    {
        property_tree& datalist_tree = *opt_datalist_tree;
        property_tree::const_iterator it = datalist_tree.begin();
        property_tree::const_iterator end = datalist_tree.end();
        for(;it != end; ++it)
        {
            const property_tree& attribute_tag = it->second;
            size_t attributeIndex = m_pDataBase->getDataMemberIndex(it->first);
            if(attributeIndex != DataBase::e_Constant_InvalidAttributeIndex)
            {
                m_pDataBase->setNodeAttributeValue(this, attributeIndex, attribute_tag.data());
            }
        }
    }*/
}

boolean BinaryPackageNode::canLoad(map<string, vector<string>>* missing_types_per_module)
{
    property_tree index_tree;
    
    BinaryPackageDataBase* pDB = static_cast<BinaryPackageDataBase*>(m_pDataBase);
    
    /*const string& self_path = pDB->nodePath(this, getGuid(), getParentNode());
    property_tree_namespace::read_xml(self_path+'/'+"index", index_tree);*/
    
    if(index_tree.empty()) return true;
    
    boolean result = true;
    vector<uint>    parentGuids;
    
    /*property_tree& datalist_tree = index_tree.get_child("index");
    property_tree::const_iterator it = datalist_tree.begin();
    property_tree::const_iterator end = datalist_tree.end();
    for(;it != end; ++it)
    {
        const property_tree& sub_tree = it->second;
        string typeName = decodeQualifiedDecoratedNameFromIdentifierName(sub_tree.get<string>("typename"));
        reflection::Type* pType = m_pDataBase->solveTypeByName(typeName);
        if(pType == NULL)
        {
            a_MissingTypes.push_back(typeName);
            result = false;
        }
    }*/
    return result;
}

void BinaryPackageNode::cache()
{
    o_assert(m_Data.empty(), "already cached");

    property_tree index_tree;

    BinaryPackageDataBase* pDB = static_cast<BinaryPackageDataBase*>(m_pDataBase);

    /*const string& self_path = pDB->nodePath(this, getGuid(), getParentNode());
    property_tree_namespace::read_xml(self_path+'/'+"index", index_tree);

    if(index_tree.empty()) return;

    vector<uint>    parentGuids;

    property_tree& datalist_tree = index_tree.get_child("index");
    property_tree::const_iterator it = datalist_tree.begin();
    property_tree::const_iterator end = datalist_tree.end();
    for(;it != end; ++it)
    {
        const property_tree& sub_tree = it->second;
        const string& strGuid = sub_tree.get<string>("guid");
        ulong guid = o_invalid_guid;
#if o_COMPILER == o_COMPILER_VISUAL_STUDIO
#   pragma warning(disable:4996)
#endif
        sscanf(strGuid.c_str(), "%x", &guid);
#if o_COMPILER == o_COMPILER_VISUAL_STUDIO
#   pragma warning(default:4996)
#endif        
        o_assert(guid != o_invalid_guid);
        
        reflection::Type* pType = m_pDataBase->solveTypeByName(decodeQualifiedDecoratedNameFromIdentifierName(sub_tree.get<string>("typename")));
        if(pType == NULL)
        {
            switch(m_pDataBase->getActionOnMissingType())
            {
            case DataBase::e_ActionOnMissingType_IgnoreAndDestroyData:
                continue;
            case DataBase::e_ActionOnMissingType_NotifyAndDestroyData:
                continue;
            case DataBase::e_ActionOnMissingType_Exception:
                o_exception(phantom::exception::unknown_reflection_type_exception, sub_tree.get<string>("typename").c_str());
            }
        }

        // TODO : specialize lexical_cast for : uint guid = reinterpret_cast<uint>(phantom::lexical_cast<void*>(strGuid));
        phantom::data the_data(pType->allocate(),pType);
        storeData(the_data);
        m_DataRestoreQueue.push_back(the_data);
        pDB->registerData(the_data, guid, this);

        boost::optional<string> strParentGuid_opt = sub_tree.get_optional<string>("parent");
        uint parentGuid = o_invalid_guid;
        if(strParentGuid_opt.is_initialized())        
        {
#if o_COMPILER == o_COMPILER_VISUAL_STUDIO
#   pragma warning(disable:4996)
#endif
            sscanf((*strParentGuid_opt).c_str(), "%x", &parentGuid);
#if o_COMPILER == o_COMPILER_VISUAL_STUDIO
#   pragma warning(default:4996)
#endif        
        }
        parentGuids.push_back(parentGuid);
    }
    size_t i = 0;
    size_t count = m_Data.size();
    for(;i<count;++i)
    {
        uint parentGuid = parentGuids[i] ;
        if(parentGuid != o_invalid_guid)
        {
            const phantom::data& parentData = pDB->getData(parentGuid);
            o_assert(NOT(parentData.isNull()));
            pDB->registerComponentData(m_Data[i], parentData);
        }
    }*/
}

void BinaryPackageNode::uncache()
{
	BinaryPackageDataBase* pDB = static_cast<BinaryPackageDataBase*>(m_pDataBase);

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

void BinaryPackageNode::build()
{
    BinaryPackageDataBase* pDB = static_cast<BinaryPackageDataBase*>(m_pDataBase);
  
    data_vector::iterator end = m_Data.end();
    // Build ( Construction + Installation)
    
    data_vector::iterator it = m_Data.begin();
    for(;it != end; ++it)
    {
        it->type()->build(it->address());
    }   
}

void BinaryPackageNode::unbuild()
{
	BinaryPackageDataBase* pDB = static_cast<BinaryPackageDataBase*>(m_pDataBase);

	data_vector::iterator end = m_Data.end();
	// teardown ( Destruction + Uninstallation + Termination )

	data_vector::iterator it = m_Data.begin();
	for(;it != end; ++it)
	{
		it->type()->teardown(it->address());
	}

}

void BinaryPackageNode::deserialize(uint a_uiSerializationFlag)
{
    // Deserialization
    /*BinaryPackageDataBase* pDB = static_cast<BinaryPackageDataBase*>(m_pDataBase);
    data_vector::iterator it = m_Data.begin();
    data_vector::iterator end = m_Data.end();
    for(;it != end; ++it)
    {
        void* pAddress = it->address();
        reflection::Type* pType = it->type();
        property_tree p_tree;
        uint guid = pDB->getGuid(pAddress);
        const string& path = pDB->dataPath(*it, guid, pDB->getNode(pAddress));
        property_tree_namespace::read_xml(path.c_str(), p_tree);
        boost::optional<property_tree&> valueMembers_tree_opt = p_tree.get_child_optional("data.valueMembers");
        if(valueMembers_tree_opt.is_initialized())
        {
            pType->deserialize(pAddress, *valueMembers_tree_opt, a_uiSerializationFlag, pDB);
        }
    }*/
}

void BinaryPackageNode::restore(uint a_uiSerializationFlag)
{
    BinaryPackageDataBase* pDB = static_cast<BinaryPackageDataBase*>(m_pDataBase);

    restore_pass pass = restore_pass_local;
    int counter = 0;
    int cycle_count = m_DataRestoreQueue.size();
    while(cycle_count AND pass <= restore_pass_global_5)
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
            pass = restore_pass(pass+1);
            cycle_count = m_DataRestoreQueue.size();
            counter = 0;
        }
    }
}

void BinaryPackageNode::configure()
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

void BinaryPackageNode::unconfigure()
{

}

o_namespace_end(phantom, serialization)
