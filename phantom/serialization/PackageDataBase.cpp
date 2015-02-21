/* TODO LICENCE HERE */

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include <phantom/serialization/PackageDataBase.h>
#include <phantom/serialization/PackageDataBase.hxx>
#include <phantom/serialization/PackageNode.h>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/fstream.hpp>
#ifdef WIN32
#include <windows.h>
#include <Lmcons.h>
#endif //WIN32
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/* *********************************************** */
o_registerN((phantom, serialization), PackageDataBase);

o_namespace_begin(phantom, serialization)

PackageDataBase::PackageDataBase(const string& a_strUrl, uint a_uiSerializationFlag) 
: DataBase(a_strUrl, a_uiSerializationFlag)
{
    const char* url_c_str = a_strUrl.c_str();
    if(NOT(boost::filesystem::exists(url_c_str)))
    {
        boost::filesystem::create_directories(url_c_str);
    }
	srand(time(NULL));
}

o_destructor PackageDataBase::~PackageDataBase()
{

}

PackageDataBase::PackageDataBaseBuffer* PackageDataBase::getBuffer()
{
	return &m_Buffer;
}

void PackageDataBase::loadNodeEntriesHelper(Node* a_pNode, const boost::filesystem::path& a_Path)
{
    o_assert(boost::filesystem::is_directory(a_Path));      // is p a directory?

    static_cast<PackageNode*>(a_pNode)->loadAttributes();

    boost::filesystem::directory_iterator it(a_Path);
    boost::filesystem::directory_iterator end;
    
    for(;it != end; ++it)
    {
        const boost::filesystem::path& dir_path = it->path();
        if(NOT(boost::filesystem::is_directory(dir_path))) continue;
        uint guid = o_invalid_guid;
#if o_COMPILER == o_COMPILER_VISUAL_STUDIO
#   pragma warning(disable:4996)
#endif
        sscanf(dir_path.stem().generic_string().c_str(), "[%x]", &guid);
#if o_COMPILER == o_COMPILER_VISUAL_STUDIO
#   pragma warning(default:4996)
#endif        
        if(guid != o_invalid_guid)
        {
            Node* pChildNode = createNode(guid, a_pNode);
            registerNode(pChildNode);
            loadNodeEntriesHelper(pChildNode, dir_path);
        }
    }
}

void PackageDataBase::loadNodeEntries()
{
    boost::filesystem::path root_path = m_strUrl.c_str();
    o_assert(boost::filesystem::exists(root_path));
    loadNodeEntriesHelper(rootNode(), root_path);
}

void PackageDataBase::unloadNodeEntries()
{
    static_cast<PackageNode*>(rootNode())->destroyAllChildNode();
}

boolean PackageDataBase::hasNodeEntry(Node* a_pNode) const
{
	return true;
}

boolean PackageDataBase::hasDataEntry(const data& a_Data, uint a_uiGuid, Node* a_pOwnerNode) const
{
	return true;
}

uint PackageDataBase::generateGuid()
{
	return 0;
}

void PackageDataBase::releaseGuid(uint a_uiGuid)
{

}

void PackageDataBase::createDataEntry(const phantom::data& a_Data, uint a_uiGuid, Node* a_pOwnerNode)
{

}

void PackageDataBase::destroyDataEntry(const phantom::data& a_Data, uint a_uiGuid, Node* a_pOwnerNode)
{

}

void PackageDataBase::moveDataEntry(const phantom::data& a_Data, uint a_uiGuid, Node* a_pOldParent, Node* a_pNewParent)
{

}

void PackageDataBase::createNodeEntry(Node* a_pNode)
{

}

void PackageDataBase::destroyNodeEntry(Node* a_pNode)
{

}

void PackageDataBase::moveNodeEntry(Node* a_pNode, Node* a_pNewParent)
{

}

o_namespace_end(phantom, serialization)
