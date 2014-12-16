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
#include <phantom/serialization/FileTreeDataBase.h>
#include <phantom/serialization/FileTreeNode.h>
#include <phantom/serialization/FileTreeNode.hxx>
#include "phantom/ModuleLoader.h"
/* *********************************************** */
o_registerN((phantom, serialization), FileTreeNode);

o_namespace_begin(phantom, serialization)

FileTreeNode::FileTreeNode(FileTreeDataBase* a_pDataBase, uint guid, FileTreeNode* a_pParentNode)
    : Node(a_pDataBase, guid, a_pParentNode) {}

string FileTreeNode::path() const
{
    return static_cast<FileTreeDataBase const*>(m_pDataBase)->nodePath(const_cast<FileTreeNode*>(this), m_Guid, m_pParentNode);
}

string FileTreeNode::relativePath() const
{
    return static_cast<FileTreeDataBase const*>(m_pDataBase)->relativeNodePath(const_cast<FileTreeNode*>(this), m_Guid, m_pParentNode);
}

void FileTreeNode::saveDataAttributes()
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
void FileTreeNode::saveDataAttributes(const phantom::data& a_Data, uint guid)
{
    property_tree p_tree;
    const string& path = static_cast<FileTreeDataBase*>(m_pDataBase)->dataPath(a_Data, guid, this);

    // First read the data file
    read(path.c_str(), p_tree);

    boost::optional<property_tree&> attribute_tree_opt = p_tree.get_child_optional("data.attributes");
    if(attribute_tree_opt.is_initialized())
    {
        (*attribute_tree_opt).clear();
        saveDataAttributesHelper(*attribute_tree_opt, a_Data);
    }
    else
    {
        property_tree attribute_tree;
        saveDataAttributesHelper(attribute_tree, a_Data);
        p_tree.add_child("data.attributes", attribute_tree);
    }
    write(path.c_str(), p_tree);
}

void FileTreeNode::saveDataProperties(uint a_uiSerializationFlag, const phantom::data& a_Data, uint guid) 
{
    property_tree p_tree;
    property_tree valueMembers_tree;
    const string& path = static_cast<FileTreeDataBase*>(m_pDataBase)->dataPath(a_Data, guid, this);
    a_Data.type()->serialize(a_Data.address(), valueMembers_tree, a_uiSerializationFlag, m_pDataBase);
    property_tree attribute_tree;
    saveDataAttributesHelper(attribute_tree, a_Data);
    p_tree.add_child("data.valueMembers", valueMembers_tree);
    p_tree.add_child("data.attributes", attribute_tree);
    write(path.c_str(), p_tree);
}

void FileTreeNode::loadDataProperties(uint a_uiSerializationFlag, const phantom::data& a_Data, uint guid) 
{
    property_tree p_tree;
    const string& path = static_cast<FileTreeDataBase*>(m_pDataBase)->dataPath(a_Data, guid, this);
    read(path.c_str(), p_tree);
    property_tree valueMembers_tree = p_tree.get_child("data.valueMembers");
    a_Data.type()->deserialize(a_Data.address(), valueMembers_tree, a_uiSerializationFlag, m_pDataBase);
    property_tree attribute_tree;
    attribute_tree = p_tree.get_child("data.attributes");
    loadDataAttributesHelper(attribute_tree, a_Data);
}

void FileTreeNode::saveIndex()
{
    property_tree index_tree;

    data_vector::iterator it = m_Data.begin();
    data_vector::iterator end = m_Data.end();

    index_tree.add_child("index", property_tree());

    FileTreeDataBase* pDB = static_cast<FileTreeDataBase*>(m_pDataBase);
    for(;it != end; ++it)
    {
        void* pAddress = it->address();
        reflection::Type* pType = it->type();
        uint guid = getDataBase()->getGuid(pAddress);
        uint modifiers = m_pDataBase->getDataModifiers(*it);
        property_tree dataPath;
        dataPath.put<string>("typename", pType->getQualifiedDecoratedName());
        dataPath.put<string>("module", pType->getModule() ? pType->getModule()->getFileName() : "");
        dataPath.put<string>("guid", phantom::lexical_cast<string>(reinterpret_cast<void*>(guid)));
        dataPath.put<string>("modifiers", phantom::lexical_cast<string>(reinterpret_cast<void*>(modifiers)));
        const data& parent = m_pDataBase->getComponentDataOwner(pAddress);
        if(NOT(parent.isNull()))
        {
            uint parentGuid = m_pDataBase->getGuid(parent);
            dataPath.put<string>("parent", phantom::lexical_cast<string>(reinterpret_cast<void*>(parentGuid)));
            dataPath.put<string>("reference_expression", m_pDataBase->getComponentDataReferenceExpression(*it));
        }
        index_tree.add_child("index.data", dataPath);
    }

    const string& self_path = pDB->nodePath(this, getGuid(), getParentNode());

    write(self_path+'/'+"index", index_tree);
}

void FileTreeNode::saveAttributes()
{
    property_tree attribute_tree;

    FileTreeDataBase* pDB = static_cast<FileTreeDataBase*>(m_pDataBase);

    const string* pDataMemberValues = pDB->getNodeAttributeValues(this);
    if(pDataMemberValues != NULL) 
    {
        property_tree node_attribute_tree;
        size_t i = 0;
        size_t attributeCount = pDB->getAttributeCount();
        for(;i<attributeCount;++i)
        {
            node_attribute_tree.put<string>(pDB->getAttributeName(i), pDataMemberValues[i]);
        }
        attribute_tree.add_child("attributes", node_attribute_tree);
    }

    const string& self_path = pDB->nodePath(this, getGuid(), getParentNode());
    write(self_path+'/'+"attributes", attribute_tree);
}

void FileTreeNode::saveDataAttributesHelper( property_tree& tree, const phantom::data& a_Data )
{
    FileTreeDataBase* pDB = static_cast<FileTreeDataBase*>(m_pDataBase);

    const string* pDataMemberValues = pDB->getDataAttributeValues(a_Data);
    if(pDataMemberValues != NULL) 
    {
        size_t i = 0;
        size_t attributeCount = pDB->getAttributeCount();
        for(;i<attributeCount;++i)
        {
            tree.put<string>(pDB->getAttributeName(i), pDataMemberValues[i]);
        }
    }
}

void FileTreeNode::loadDataAttributesHelper( const property_tree& tree, const phantom::data& a_Data )
{
    FileTreeDataBase* pDB = static_cast<FileTreeDataBase*>(m_pDataBase);

    property_tree::const_iterator it = tree.begin();
    property_tree::const_iterator end = tree.end();
    for(;it != end; ++it)
    {
        const property_tree& attribute_tag = it->second;
        size_t attributeIndex = m_pDataBase->getAttributeIndex(it->first);
        if(attributeIndex != ~size_t(0))
        {
            m_pDataBase->setDataAttributeValue(a_Data, attributeIndex, attribute_tag.data());
        }
    }
}

void FileTreeNode::loadAttributes()
{
    // write data base info
    property_tree attribute_tree;

    FileTreeDataBase* pDB = static_cast<FileTreeDataBase*>(m_pDataBase);
    const string& self_path = pDB->nodePath(this, getGuid(), getParentNode());
    read(self_path+'/'+"attributes", attribute_tree);
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
            size_t attributeIndex = m_pDataBase->getAttributeIndex(it->first);
            if(attributeIndex != ~size_t(0))
            {
                m_pDataBase->setNodeAttributeValue(this, attributeIndex, attribute_tag.data());
            }
        }
    }
}

void FileTreeNode::loadDataAttributes()
{
    data_vector::iterator end = m_Data.end();
    data_vector::iterator it = m_Data.begin();
    for(;it != end; ++it)
    {
        loadDataAttributes(*it, m_pDataBase->getGuid(*it));
    }
}

void FileTreeNode::loadDataAttributes(const phantom::data& a_Data, uint guid) 
{
    property_tree p_tree;
    const string& path = static_cast<FileTreeDataBase*>(m_pDataBase)->dataPath(a_Data, guid, this);

    // First read the data file
    read(path.c_str(), p_tree);

    property_tree attribute_tree;
    boost::optional<property_tree&> attribute_tree_opt = p_tree.get_child_optional("data.attributes");
    if(attribute_tree_opt.is_initialized())
    {
        loadDataAttributesHelper(*attribute_tree_opt, a_Data);
    }
}

bool FileTreeNode::canLoad(map<string, vector<string> >* missing_types_per_module) const
{
    FileTreeDataBase* pDB = static_cast<FileTreeDataBase*>(m_pDataBase);
    const string& self_path = pDB->nodePath(const_cast<FileTreeNode*>(this), getGuid(), getParentNode());

    property_tree index_tree;

    read(self_path+'/'+"index", index_tree);

    if(index_tree.empty()) return true;


    boolean result = true;
    vector<uint>    parentGuids;

    property_tree& datalist_tree = index_tree.get_child("index");
    property_tree::const_iterator it = datalist_tree.begin();
    property_tree::const_iterator end = datalist_tree.end();
    for(;it != end; ++it)
    {
        const property_tree& sub_tree = it->second;
        string typeName = sub_tree.get<string>("typename");
        string moduleName = sub_tree.get<string>("module");
        bool bModuleLoaded = moduleLoader()->isModuleLoaded(moduleName);
        reflection::Type* pType = m_pDataBase->solveTypeByName(typeName);
        if(pType == NULL)
        {
            if(NOT(bModuleLoaded))
            {
                o_warning(false, (string("Missing type : ")+typeName).c_str());
                if(missing_types_per_module) 
                    (*missing_types_per_module)[moduleName].push_back(typeName);
                result = false;
            }
        }
    }
    return result;
}

void FileTreeNode::cache()
{
    cache(nullptr, nullptr);
}

void FileTreeNode::cache( const vector<uint>* a_pGuids, vector<data>* a_pCachedData )
{
    o_assert(m_Data.empty() OR a_pCachedData, "already cached");

    property_tree index_tree;

    FileTreeDataBase* pDB = static_cast<FileTreeDataBase*>(m_pDataBase);

    const string& self_path = pDB->nodePath(this, getGuid(), getParentNode());
    read(self_path+'/'+"index", index_tree);

    if(index_tree.empty()) return;

    vector<uint>    parentGuids;
    vector<string>  referenceExpressions;

    property_tree& datalist_tree = index_tree.get_child("index");
    property_tree::const_iterator it = datalist_tree.begin();
    property_tree::const_iterator end = datalist_tree.end();
    for(;it != end; ++it)
    {
        const property_tree& sub_tree = it->second;
        const string& strGuid = sub_tree.get<string>("guid");
        const string& strModifiers = sub_tree.get<string>("modifiers");
        uint guid = o_invalid_guid;
        uint modifiers = 0;
#if o_COMPILER == o_COMPILER_VISUAL_STUDIO
#   pragma warning(disable:4996)
#endif
        sscanf(strGuid.c_str(), "%x", &guid);
        sscanf(strModifiers.c_str(), "%x", &modifiers);
#if o_COMPILER == o_COMPILER_VISUAL_STUDIO
#   pragma warning(default:4996)
#endif        
        o_assert(guid != o_invalid_guid);

        if(a_pGuids != nullptr AND std::find(a_pGuids->begin(), a_pGuids->end(), guid) == a_pGuids->end())
            continue;

        string typeName = sub_tree.get<string>("typename");
        string moduleName = sub_tree.get<string>("module");
        reflection::Type* pType = m_pDataBase->solveTypeByName(typeName);
        bool bModuleLoaded = moduleLoader()->isModuleLoaded(moduleName);
        if(pType == NULL)
        {
            if(bModuleLoaded)
            {
                continue; // If type was a runtime type and we cannot find it anymore in the module, we skip the data and continue
            }
            switch(m_pDataBase->getActionOnMissingType())
            {
            case DataBase::e_ActionOnMissingType_IgnoreAndDestroyData:
                continue;
            case DataBase::e_ActionOnMissingType_NotifyAndDestroyData:
                continue;
            case DataBase::e_ActionOnMissingType_Exception:
                {
                    string message = sub_tree.get<string>("typename");
                    o_exception(phantom::exception::unknown_reflection_type_exception, message.c_str());
                }
            }
        }

        // TODO : specialize lexical_cast for : uint guid = reinterpret_cast<uint>(phantom::lexical_cast<void*>(strGuid));
        phantom::data the_data(pType->allocate(),pType);
        if(a_pCachedData)
        {
            a_pCachedData->push_back(the_data);
        }
        pDB->registerData(the_data, guid, this, modifiers);

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
            referenceExpressions.push_back(sub_tree.get<string>("reference_expression"));
        }
        else 
        {
            referenceExpressions.push_back("");
        }
        parentGuids.push_back(parentGuid);

    }
    vector<data>& cachedData = a_pCachedData ? *a_pCachedData : m_Data;
    size_t i = 0;
    size_t count = cachedData.size();
    for(;i<count;++i)
    {
        uint parentGuid = parentGuids[i] ;
        if(parentGuid != o_invalid_guid)
        {
            const phantom::data& parentData = pDB->getData(parentGuid);
            o_assert(NOT(parentData.isNull()));
            pDB->registerComponentData(cachedData[i], parentData, referenceExpressions[i]);
        }
    }
}

void FileTreeNode::build(vector<data>& a_Data)
{
    FileTreeDataBase* pDB = static_cast<FileTreeDataBase*>(m_pDataBase);

    data_vector::iterator end = a_Data.end();
    // Build ( Construction + Installation)

    data_vector::iterator it = a_Data.begin();
    for(;it != end; ++it)
    {
        it->type()->build(it->address());
    }

}

void FileTreeNode::deserialize(uint a_uiSerializationFlag, vector<data>& a_Data)
{
    // Deserialization
    FileTreeDataBase* pDB = static_cast<FileTreeDataBase*>(m_pDataBase);
    data_vector::iterator it = a_Data.begin();
    data_vector::iterator end = a_Data.end();
    for(;it != end; ++it)
    {
        void* pAddress = it->address();
        reflection::Type* pType = it->type();
        property_tree p_tree;
        uint guid = pDB->getGuid(pAddress);
        const string& path = pDB->dataPath(*it, guid, pDB->getNode(pAddress));
        read(path, p_tree);
        boost::optional<property_tree&> valueMembers_tree_opt = p_tree.get_child_optional("data.valueMembers");
        if(valueMembers_tree_opt.is_initialized())
        {
            pType->deserialize(pAddress, *valueMembers_tree_opt, a_uiSerializationFlag, pDB);
        }
    }
}

void FileTreeNode::restore(uint a_uiSerializationFlag, vector<data>& a_Data, restore_pass firstPass /*= restore_pass_local*/)
{
    FileTreeDataBase* pDB = static_cast<FileTreeDataBase*>(m_pDataBase);
    list<data> dataCopy(a_Data.begin(), a_Data.end());
    restore_pass pass = firstPass;
    int counter = 0;
    int cycle_count = dataCopy.size();
    while(cycle_count AND pass <= restore_pass_global_5)
    {
        // extract the data from the queue
        phantom::data d = dataCopy.front();
        dataCopy.pop_front();

        restore_state state = d.type()->restore(d.address(), a_uiSerializationFlag, pass) ;;
        switch(state)
        {
        case restore_complete: // if success, we do nothing
            break;
        case restore_incomplete: // if incomplete, we reinject the data at the end of the queue to apply to it another pass later
            dataCopy.push_back(d);
            break;
        case restore_failed: // if failed we store the data in the destruction queue which will be handled at the node loading end
            dataCopy.push_back(d);
            break;
        default:
            o_assert(false, "state unknown, anormal, probably a segfault somewhere which overrided the restore_state enum value");
            break;
        }
        if((++counter) == cycle_count) // reached the cycle end => increment pass, reset counters
        {
            pass = restore_pass(pass+1);
            cycle_count = dataCopy.size();
            counter = 0;
        }
    }
}

void FileTreeNode::unbuild()
{
    FileTreeDataBase* pDB = static_cast<FileTreeDataBase*>(m_pDataBase);

    data_vector::iterator end = m_Data.end();
    // teardown ( Destruction + Uninstallation + Termination )

    data_vector::iterator it = m_Data.begin();
    for(;it != end; ++it)
    {
        if(m_pDataBase->getComponentDataOwner(*it).isNull())
        {
            it->type()->teardown(it->address());
        }
    }

}

void FileTreeNode::uncache()
{
    FileTreeDataBase* pDB = static_cast<FileTreeDataBase*>(m_pDataBase);
    auto datas = m_Data;

    static_cast<FileTreeDataBase*>(m_pDataBase)->sortComponentDataFirst(datas.rbegin(), datas.rend());
    for(auto it = datas.begin(); it != datas.end(); ++it)
    {
        if(m_pDataBase->getComponentDataOwner(*it).isNull())
        {
            it->type()->deallocate(it->address());
        }
        unregisterData(*it);
    }
}

void FileTreeNode::configure()
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

void FileTreeNode::unconfigure()
{

}

void FileTreeNode::preCache()
{
    FileTreeDataBase* pDB = static_cast<FileTreeDataBase*>(m_pDataBase);
    const string& self_path = pDB->nodePath(this, getGuid(), getParentNode());
    read(self_path+'/'+"index", m_CacheTree);
}

bool FileTreeNode::cacheOne(uint a_uiIndex)
{
    if (NOT(m_CacheTree.empty()))
    {
        property_tree& datalist_tree = m_CacheTree.get_child("index");
        property_tree::const_iterator it = datalist_tree.begin();
        property_tree::const_iterator end = datalist_tree.end();
        if (it != end)
        {
            FileTreeDataBase* pDB = static_cast<FileTreeDataBase*>(m_pDataBase);

            const property_tree& sub_tree = it->second;
            const string& strGuid = sub_tree.get<string>("guid");
            const string& strModifiers = sub_tree.get<string>("modifiers");
            uint guid = o_invalid_guid;
            uint modifiers = 0;
#if o_COMPILER == o_COMPILER_VISUAL_STUDIO
#   pragma warning(disable:4996)
#endif
            sscanf(strGuid.c_str(), "%x", &guid);
            sscanf(strModifiers.c_str(), "%x", &modifiers);
#if o_COMPILER == o_COMPILER_VISUAL_STUDIO
#   pragma warning(default:4996)
#endif        
            o_assert(guid != o_invalid_guid);

            string typeName = sub_tree.get<string>("typename");
            string moduleName = sub_tree.get<string>("module");
            reflection::Type* pType = m_pDataBase->solveTypeByName(typeName);
            bool bModuleLoaded = moduleLoader()->isModuleLoaded(moduleName);
            if(pType == NULL)
            {
                if(bModuleLoaded)
                {
                    return false; // If type was a runtime type and we cannot find it anymore in the module, we skip the data and continue
                }
                switch(m_pDataBase->getActionOnMissingType())
                {
                case DataBase::e_ActionOnMissingType_IgnoreAndDestroyData:
                    return false;
                case DataBase::e_ActionOnMissingType_NotifyAndDestroyData:
                    return false;
                case DataBase::e_ActionOnMissingType_Exception:
                    o_exception(phantom::exception::unknown_reflection_type_exception, sub_tree.get<string>("typename").c_str());
                }
            }

            // TODO : specialize lexical_cast for : uint guid = reinterpret_cast<uint>(phantom::lexical_cast<void*>(strGuid));
            phantom::data the_data(pType->allocate(),pType);
            pDB->registerData(the_data, guid, this, modifiers);

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
                m_ReferenceExpressions.push_back(sub_tree.get<string>("reference_expression"));
            }
            else 
            {
                m_ReferenceExpressions.push_back("");
            }

            m_ParentGuids.push_back(parentGuid);
            datalist_tree.pop_front();

            return false;
        }
    }

    return true;
}

void FileTreeNode::postCache()
{
    FileTreeDataBase* pDB = static_cast<FileTreeDataBase*>(m_pDataBase);

    size_t i = 0;
    size_t count = m_Data.size();
    for(;i<count;++i)
    {
        uint parentGuid = m_ParentGuids[i] ;

        if(parentGuid != o_invalid_guid)
        {
            const phantom::data& parentData = pDB->getData(parentGuid);
            o_assert(NOT(parentData.isNull()));
            pDB->registerComponentData(m_Data[i], parentData, m_ReferenceExpressions[i]);
        }
    }
}

void FileTreeNode::uncacheOne(const phantom::data& a_Data)
{
    FileTreeDataBase* pDB = static_cast<FileTreeDataBase*>(m_pDataBase);
    pDB->unregisterData(a_Data);
    a_Data.type()->deallocate(a_Data.address());
}

void FileTreeNode::buildOne(const phantom::data& a_Data)
{
    FileTreeDataBase* pDB = static_cast<FileTreeDataBase*>(m_pDataBase);
    a_Data.type()->build(a_Data.address());
}

void FileTreeNode::unbuildOne(const phantom::data& a_Data)
{
    FileTreeDataBase* pDB = static_cast<FileTreeDataBase*>(m_pDataBase);
    a_Data.type()->teardown(a_Data.address());
}

void FileTreeNode::deserializeOne(const phantom::data& a_Data, uint a_uiSerializationFlag)
{
    FileTreeDataBase* pDB = static_cast<FileTreeDataBase*>(m_pDataBase);
    void* pAddress = a_Data.address();
    reflection::Type* pType = a_Data.type();
    property_tree p_tree;
    uint guid = pDB->getGuid(pAddress);
    const string& path = pDB->dataPath(a_Data, guid, pDB->getNode(pAddress));
    read(path.c_str(), p_tree);
    boost::optional<property_tree&> valueMembers_tree_opt = p_tree.get_child_optional("data.valueMembers");
    if(valueMembers_tree_opt.is_initialized())
    {
        pType->deserialize(pAddress, *valueMembers_tree_opt, a_uiSerializationFlag, pDB);
    }
}

bool FileTreeNode::restoreOne(const phantom::data& a_Data, uint a_uiSerializationFlag, restore_pass a_uiPass)
{
    FileTreeDataBase* pDB = static_cast<FileTreeDataBase*>(m_pDataBase);
    restore_state state = a_Data.type()->restore(a_Data.address(), a_uiSerializationFlag, a_uiPass);
    return state == restore_complete;
}

void FileTreeNode::write( const string& a_Path, const property_tree& a_Tree ) const
{
    static_cast<FileTreeDataBase*>(m_pDataBase)->write(a_Path, a_Tree);
}

void FileTreeNode::read( const string& a_Path, property_tree& a_Tree ) const
{
    static_cast<FileTreeDataBase*>(m_pDataBase)->read(a_Path, a_Tree);
}

o_namespace_end(phantom, serialization)

