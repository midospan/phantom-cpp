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
#include <boost/property_tree_custom/xml_parser.hpp>
#include <phantom/serialization/XmlFileTreeDataBase.h>
/* ** The Class Header must be the last #include * */
#include <phantom/serialization/XmlFileTreeNode.h>
/* *********************************************** */
o_registerN((phantom, serialization), XmlFileTreeNode);

o_namespace_begin(phantom, serialization)

using namespace reflection;

XmlFileTreeNode::XmlFileTreeNode(XmlFileTreeDataBase* a_pOwnerDataBase, uint guid, XmlFileTreeNode* a_pParentNode)
    : FileTreeNode(a_pOwnerDataBase, guid, a_pParentNode) 
{

}

void XmlFileTreeNode::saveDataAttributes()
{
    data_vector::iterator it = m_Data.begin();
    data_vector::iterator end = m_Data.end();

    for(;it != end; ++it)
    {
        void* pAddress = it->address();
        uint guid = m_pOwnerDataBase->getGuid(pAddress);
        saveDataAttributes(*it, guid);
    }
}
void XmlFileTreeNode::saveDataAttributes(const phantom::data& a_Data, uint guid)
{
    property_tree p_tree;
    const string& path = static_cast<XmlFileTreeDataBase*>(m_pOwnerDataBase)->dataPath(a_Data, guid, this);

    // First read the data file
    boost::property_tree_custom::read_xml(path.c_str(), p_tree);

    boost::optional<property_tree&> attribute_tree_opt = p_tree.get_child_optional("data.attributes");
    if(attribute_tree_opt.is_initialized())
    {
        (*attribute_tree_opt).clear();
        saveDataAttributesHelper(*attribute_tree_opt, a_Data);
    }
    else
    {
        property_tree attribute_tree;
        saveDataAttributesHelper(*attribute_tree_opt, a_Data);
        p_tree.add_child("data.attributes", attribute_tree);
    }
    boost::property_tree_custom::write_xml(path.c_str(), p_tree);
}

void XmlFileTreeNode::saveData(uint a_uiSerializationFlag, const phantom::data& a_Data, uint guid) 
{
    property_tree p_tree;
    property_tree properties_tree;
    const string& path = static_cast<XmlFileTreeDataBase*>(m_pOwnerDataBase)->dataPath(a_Data, guid, this);
    a_Data.type()->serialize(a_Data.address(), properties_tree, a_uiSerializationFlag, m_pOwnerDataBase);
    property_tree attribute_tree;
    saveDataAttributesHelper(attribute_tree, a_Data);
    p_tree.add_child("data.properties", properties_tree);
    p_tree.add_child("data.attributes", attribute_tree);
    boost::property_tree_custom::write_xml(path.c_str(), p_tree);
}

void XmlFileTreeNode::loadData(uint a_uiSerializationFlag, const phantom::data& a_Data, uint guid) 
{
    property_tree p_tree;
    const string& path = static_cast<XmlFileTreeDataBase*>(m_pOwnerDataBase)->dataPath(a_Data, guid, this);
    boost::property_tree_custom::read_xml(path.c_str(), p_tree);
    property_tree properties_tree = p_tree.get_child("data.properties");
    a_Data.type()->deserialize(a_Data.address(), properties_tree, a_uiSerializationFlag, m_pOwnerDataBase);
    property_tree attribute_tree;
    attribute_tree = p_tree.get_child("data.attributes");
    loadDataAttributesHelper(attribute_tree, a_Data);
}

void XmlFileTreeNode::saveData(uint a_uiSerializationFlag)
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

void XmlFileTreeNode::saveIndex()
{
    property_tree index_tree;

    data_vector::iterator it = m_Data.begin();
    data_vector::iterator end = m_Data.end();

    index_tree.add_child("index", property_tree());

    XmlFileTreeDataBase* pDB = static_cast<XmlFileTreeDataBase*>(m_pOwnerDataBase);
    for(;it != end; ++it)
    {
        void* pAddress = it->address();
        reflection::Type* pType = it->type();
        uint guid = getOwnerDataBase()->getGuid(pAddress);
        property_tree dataPath;
        dataPath.put<string>("typename", encodeQualifiedDecoratedNameToIdentifierName(pType->getQualifiedDecoratedName()));
        dataPath.put<string>("guid", phantom::lexical_cast<string>(reinterpret_cast<void*>(guid)));
        const data& parent = m_pOwnerDataBase->getSubDataOwner(pAddress);
        if(NOT(parent.isNull()))
        {
            uint parentGuid = m_pOwnerDataBase->getGuid(parent);
            dataPath.put<string>("parent", phantom::lexical_cast<string>(reinterpret_cast<void*>(parentGuid)));
        }
        index_tree.add_child("index.data", dataPath);
    }

    const string& self_path = pDB->nodePath(this, getGuid(), getParentNode());
    boost::property_tree_custom::write_xml(self_path+'/'+"index", index_tree);
    
}

void XmlFileTreeNode::saveAttributes()
{
    property_tree attribute_tree;

    XmlFileTreeDataBase* pDB = static_cast<XmlFileTreeDataBase*>(m_pOwnerDataBase);

    const string* pAttributeValues = pDB->getNodeAttributeValues(this);
    if(pAttributeValues != NULL) 
    {
        property_tree node_attribute_tree;
        size_t i = 0;
        size_t attributeCount = pDB->getAttributeCount();
        for(;i<attributeCount;++i)
        {
            node_attribute_tree.put<string>(pDB->getAttributeName(i), pAttributeValues[i]);
        }
        attribute_tree.add_child("attributes", node_attribute_tree);
    }

    const string& self_path = pDB->nodePath(this, getGuid(), getParentNode());
    boost::property_tree_custom::write_xml(self_path+'/'+"attributes", attribute_tree);
}

void XmlFileTreeNode::saveDataAttributesHelper( property_tree& tree, const phantom::data& a_Data )
{
    XmlFileTreeDataBase* pDB = static_cast<XmlFileTreeDataBase*>(m_pOwnerDataBase);

    const string* pAttributeValues = pDB->getDataAttributeValues(a_Data);
    if(pAttributeValues != NULL) 
    {
        size_t i = 0;
        size_t attributeCount = pDB->getAttributeCount();
        for(;i<attributeCount;++i)
        {
            tree.put<string>(pDB->getAttributeName(i), pAttributeValues[i]);
        }
    }
}

void XmlFileTreeNode::loadDataAttributesHelper( const property_tree& tree, const phantom::data& a_Data )
{
    XmlFileTreeDataBase* pDB = static_cast<XmlFileTreeDataBase*>(m_pOwnerDataBase);

    property_tree::const_iterator it = tree.begin();
    property_tree::const_iterator end = tree.end();
    for(;it != end; ++it)
    {
        const property_tree& attribute_tag = it->second;
        size_t attributeIndex = m_pOwnerDataBase->getAttributeIndex(it->first);
        if(attributeIndex != DataBase::e_Constant_InvalidAttributeIndex)
        {
            m_pOwnerDataBase->setDataAttributeValue(a_Data, attributeIndex, attribute_tag.data());
        }
    }
}

void XmlFileTreeNode::loadAttributes()
{
    // write data base info
    property_tree attribute_tree;
    
    XmlFileTreeDataBase* pDB = static_cast<XmlFileTreeDataBase*>(m_pOwnerDataBase);
    const string& self_path = pDB->nodePath(this, getGuid(), getParentNode());
    boost::property_tree_custom::read_xml(self_path+'/'+"attributes", attribute_tree);
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
            size_t attributeIndex = m_pOwnerDataBase->getAttributeIndex(it->first);
            if(attributeIndex != DataBase::e_Constant_InvalidAttributeIndex)
            {
                m_pOwnerDataBase->setNodeAttributeValue(this, attributeIndex, attribute_tag.data());
            }
        }
    }
}

void XmlFileTreeNode::loadDataAttributes()
{
    data_vector::iterator end = m_Data.end();
    data_vector::iterator it = m_Data.begin();
    for(;it != end; ++it)
    {
        loadDataAttributes(*it, m_pOwnerDataBase->getGuid(*it));
    }
}

void XmlFileTreeNode::loadDataAttributes(const phantom::data& a_Data, uint guid) 
{
    property_tree p_tree;
    const string& path = static_cast<XmlFileTreeDataBase*>(m_pOwnerDataBase)->dataPath(a_Data, guid, this);

    // First read the data file
    boost::property_tree_custom::read_xml(path.c_str(), p_tree);
    
    property_tree attribute_tree;
    boost::optional<property_tree&> attribute_tree_opt = p_tree.get_child_optional("data.attributes");
    if(attribute_tree_opt.is_initialized())
    {
        loadDataAttributesHelper(*attribute_tree_opt, a_Data);
    }
}

boolean XmlFileTreeNode::canLoad(vector<string>& missing_types)
{
    property_tree index_tree;
    
    XmlFileTreeDataBase* pDB = static_cast<XmlFileTreeDataBase*>(m_pOwnerDataBase);
    
    const string& self_path = pDB->nodePath(this, getGuid(), getParentNode());
    boost::property_tree_custom::read_xml(self_path+'/'+"index", index_tree);
    
    if(index_tree.empty()) return true;
    
    boolean result = true;
    vector<uint>    parentGuids;
    
    property_tree& datalist_tree = index_tree.get_child("index");
    property_tree::const_iterator it = datalist_tree.begin();
    property_tree::const_iterator end = datalist_tree.end();
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
    }
    return result;
}

void XmlFileTreeNode::cache()
{
    o_assert(m_Data.empty(), "already cached");

    property_tree index_tree;

    XmlFileTreeDataBase* pDB = static_cast<XmlFileTreeDataBase*>(m_pOwnerDataBase);

    const string& self_path = pDB->nodePath(this, getGuid(), getParentNode());
    boost::property_tree_custom::read_xml(self_path+'/'+"index", index_tree);

    if(index_tree.empty()) return;

    vector<uint>    parentGuids;

    property_tree& datalist_tree = index_tree.get_child("index");
    property_tree::const_iterator it = datalist_tree.begin();
    property_tree::const_iterator end = datalist_tree.end();
    for(;it != end; ++it)
    {
        const property_tree& sub_tree = it->second;
        const string& strGuid = sub_tree.get<string>("guid");
        ulong guid = 0xFFFFFFFF;
#if o_COMPILER == o_COMPILER_VISUAL_STUDIO
#   pragma warning(disable:4996)
#endif
        sscanf(strGuid.c_str(), "%x", &guid);
#if o_COMPILER == o_COMPILER_VISUAL_STUDIO
#   pragma warning(default:4996)
#endif        
        o_assert(guid != 0xFFFFFFFF);
        
        reflection::Type* pType = m_pOwnerDataBase->solveTypeByName(decodeQualifiedDecoratedNameFromIdentifierName(sub_tree.get<string>("typename")));
        if(pType == NULL)
        {
            switch(m_pOwnerDataBase->getActionOnMissingType())
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
        uint parentGuid = 0xFFFFFFFF;
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
        if(parentGuid != 0xffffffff)
        {
            const phantom::data& parentData = pDB->getData(parentGuid);
            o_assert(NOT(parentData.isNull()));
            pDB->registerSubDataOwner(m_Data[i], parentData);
        }
    }
}

void XmlFileTreeNode::build()
{
    XmlFileTreeDataBase* pDB = static_cast<XmlFileTreeDataBase*>(m_pOwnerDataBase);
  
    data_vector::iterator end = m_Data.end();
    // Build ( Construction + Installation)
    
    data_vector::iterator it = m_Data.begin();
    for(;it != end; ++it)
    {
        it->type()->build(it->address());
    }
    
}

void XmlFileTreeNode::deserialize(uint a_uiSerializationFlag)
{
    // Deserialization
    XmlFileTreeDataBase* pDB = static_cast<XmlFileTreeDataBase*>(m_pOwnerDataBase);
    data_vector::iterator it = m_Data.begin();
    data_vector::iterator end = m_Data.end();
    for(;it != end; ++it)
    {
        void* pAddress = it->address();
        reflection::Type* pType = it->type();
        property_tree p_tree;
        uint guid = pDB->getGuid(pAddress);
        const string& path = pDB->dataPath(*it, guid, pDB->getNode(pAddress));
        boost::property_tree_custom::read_xml(path.c_str(), p_tree);
        boost::optional<property_tree&> properties_tree_opt = p_tree.get_child_optional("data.properties");
        if(properties_tree_opt.is_initialized())
        {
            pType->deserialize(pAddress, *properties_tree_opt, a_uiSerializationFlag, pDB);
        }
    }
}

void XmlFileTreeNode::restore(uint a_uiSerializationFlag)
{
    XmlFileTreeDataBase* pDB = static_cast<XmlFileTreeDataBase*>(m_pOwnerDataBase);

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

void XmlFileTreeNode::unbuild()
{
    XmlFileTreeDataBase* pDB = static_cast<XmlFileTreeDataBase*>(m_pOwnerDataBase);

    data_vector::iterator end = m_Data.end();
    // teardown ( Destruction + Uninstallation + Termination )

    data_vector::iterator it = m_Data.begin();
    for(;it != end; ++it)
    {
        it->type()->teardown(it->address());
    }

}

void XmlFileTreeNode::uncache()
{
    XmlFileTreeDataBase* pDB = static_cast<XmlFileTreeDataBase*>(m_pOwnerDataBase);

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

void XmlFileTreeNode::configure()
{
    // Remove and destroy aborted data
    if(m_DataAbortQueue.size())
    {
        o_foreach(data d, m_DataAbortQueue)
        {
            abortData(d);
        }
        //saveIndex();
    }
    m_DataAbortQueue.clear();
}

void XmlFileTreeNode::unconfigure()
{

}

void XmlFileTreeNode::preCache()
{
	XmlFileTreeDataBase* pDB = static_cast<XmlFileTreeDataBase*>(m_pOwnerDataBase);
	const string& self_path = pDB->nodePath(this, getGuid(), getParentNode());
	boost::property_tree_custom::read_xml(self_path+'/'+"index", m_CacheTree);
}

bool XmlFileTreeNode::cacheOne(uint a_uiIndex)
{
	if (NOT(m_CacheTree.empty()))
	{
		property_tree& datalist_tree = m_CacheTree.get_child("index");
		property_tree::const_iterator it = datalist_tree.begin();
		property_tree::const_iterator end = datalist_tree.end();
		if (it != end)
		{
			XmlFileTreeDataBase* pDB = static_cast<XmlFileTreeDataBase*>(m_pOwnerDataBase);

			const property_tree& sub_tree = it->second;
			const string& strGuid = sub_tree.get<string>("guid");
			ulong guid = 0xFFFFFFFF;
#if o_COMPILER == o_COMPILER_VISUAL_STUDIO
#   pragma warning(disable:4996)
#endif
			sscanf(strGuid.c_str(), "%x", &guid);
#if o_COMPILER == o_COMPILER_VISUAL_STUDIO
#   pragma warning(default:4996)
#endif        
			o_assert(guid != 0xFFFFFFFF);

			reflection::Type* pType = m_pOwnerDataBase->solveTypeByName(decodeQualifiedDecoratedNameFromIdentifierName(sub_tree.get<string>("typename")));
			/*if(pType == NULL)
			{
				switch(m_pOwnerDataBase->getActionOnMissingType())
				{
				case DataBase::e_ActionOnMissingType_IgnoreAndDestroyData:
					continue;
				case DataBase::e_ActionOnMissingType_NotifyAndDestroyData:
					continue;
				case DataBase::e_ActionOnMissingType_Exception:
					o_exception(phantom::exception::unknown_reflection_type_exception, sub_tree.get<string>("typename").c_str());
				}
			}*/

			// TODO : specialize lexical_cast for : uint guid = reinterpret_cast<uint>(phantom::lexical_cast<void*>(strGuid));
			phantom::data the_data(pType->allocate(),pType);
			storeData(the_data);
			pDB->registerData(the_data, guid, this);

			boost::optional<string> strParentGuid_opt = sub_tree.get_optional<string>("parent");
			uint parentGuid = 0xFFFFFFFF;
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
			m_ParentGuids.push_back(parentGuid);

			datalist_tree.pop_front();

			return false;
		}
	}

	return true;
}

void XmlFileTreeNode::postCache()
{
	XmlFileTreeDataBase* pDB = static_cast<XmlFileTreeDataBase*>(m_pOwnerDataBase);

	size_t i = 0;
	size_t count = m_Data.size();
	for(;i<count;++i)
	{
		uint parentGuid = m_ParentGuids[i] ;
		if(parentGuid != 0xffffffff)
		{
			const phantom::data& parentData = pDB->getData(parentGuid);
			o_assert(NOT(parentData.isNull()));
			pDB->registerSubDataOwner(m_Data[i], parentData);
		}
	}
}

void XmlFileTreeNode::uncacheOne(const phantom::data& a_Data)
{
	data_vector::iterator it = std::find(m_Data.begin(), m_Data.end(), a_Data);
	if (it != m_Data.end())
	{
		m_Data.erase(it);
	}
	XmlFileTreeDataBase* pDB = static_cast<XmlFileTreeDataBase*>(m_pOwnerDataBase);
	pDB->unregisterData(a_Data);
	a_Data.type()->deallocate(a_Data.address());
}

void XmlFileTreeNode::buildOne(const phantom::data& a_Data)
{
	XmlFileTreeDataBase* pDB = static_cast<XmlFileTreeDataBase*>(m_pOwnerDataBase);
	a_Data.type()->build(a_Data.address());
}

void XmlFileTreeNode::unbuildOne(const phantom::data& a_Data)
{
	XmlFileTreeDataBase* pDB = static_cast<XmlFileTreeDataBase*>(m_pOwnerDataBase);
	a_Data.type()->teardown(a_Data.address());
}

void XmlFileTreeNode::deserializeOne(const phantom::data& a_Data, uint a_uiSerializationFlag)
{
	XmlFileTreeDataBase* pDB = static_cast<XmlFileTreeDataBase*>(m_pOwnerDataBase);
	void* pAddress = a_Data.address();
	reflection::Type* pType = a_Data.type();
	property_tree p_tree;
	uint guid = pDB->getGuid(pAddress);
	const string& path = pDB->dataPath(a_Data, guid, pDB->getNode(pAddress));
	boost::property_tree_custom::read_xml(path.c_str(), p_tree);
	boost::optional<property_tree&> properties_tree_opt = p_tree.get_child_optional("data.properties");
	if(properties_tree_opt.is_initialized())
	{
		pType->deserialize(pAddress, *properties_tree_opt, a_uiSerializationFlag, pDB);
	}
}

bool XmlFileTreeNode::restoreOne(const phantom::data& a_Data, uint a_uiSerializationFlag, uint a_uiPass)
{
	XmlFileTreeDataBase* pDB = static_cast<XmlFileTreeDataBase*>(m_pOwnerDataBase);
	restore_state state = a_Data.type()->restore(a_Data.address(), a_uiSerializationFlag, a_uiPass);
	return state == restore_complete;
}

o_namespace_end(phantom, serialization)
