/* TODO LICENCE HERE */

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/fstream.hpp>
#include <phantom/serialization/FileTreeNode.h>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/fstream.hpp>
#include <phantom/serialization/FileTreeDataStateBase.h>
#include <phantom/serialization/FileTreeDataStateBase.hxx>
#include <phantom/serialization/FileTreeDataBase.h>
/* *********************************************** */
o_registerN((phantom, serialization), FileTreeDataStateBase);

o_namespace_begin(phantom, serialization)

FileTreeDataStateBase::FileTreeDataStateBase( FileTreeDataBase* a_pDataBase, const string& a_Url, uint a_uiSerializationFlag ) 
    : DataStateBase(a_pDataBase, a_Url, a_uiSerializationFlag)
{
}

bool FileTreeDataStateBase::hasStateSaved( Node* a_pNode, uint a_uiStateId ) const
{
    const string & path = statePath(a_pNode, a_uiStateId);
    boost::filesystem::path p((path).c_str());
    return boost::filesystem::exists(p);
}

string FileTreeDataStateBase::statePath( Node* a_pNode, uint a_uiStateId ) const
{
    Node* pParent = a_pNode->getParentNode();
    string path = pParent
        ? statePath(pParent, a_uiStateId) 
        : getUrl() + "/[" + phantom::lexical_cast<string>(reinterpret_cast<void*>(a_uiStateId)) + "]";
    path += "/[";
    path += phantom::lexical_cast<string>(reinterpret_cast<void*>(a_pNode->getGuid()));
    path += "]";
    return path;
}

string FileTreeDataStateBase::dataPath( const phantom::data& a_Data, uint a_uiGuid, Node* a_pNode, uint a_uiStateId ) const
{
    string path = statePath(a_pNode, a_uiStateId);
    path += "/[";
    path += phantom::lexical_cast<string>(reinterpret_cast<void*>(a_uiGuid));
    path += "]";
    return path;
}

void FileTreeDataStateBase::loadState(Node* a_pNode, const vector<data>& a_DataList, uint a_uiStateId)
{
    FileTreeNode* pNode = as<FileTreeNode*>(a_pNode);
    o_assert(pNode);

    FileTreeDataBase* pDB = static_cast<FileTreeDataBase*>(pNode->getDataBase());
    o_assert(pDB);

    const string & path = statePath(a_pNode, a_uiStateId);

    if(hasStateSaved(a_pNode, a_uiStateId))
    {
        auto it = a_DataList.begin();
        auto end = a_DataList.end();
        for(;it!=end;++it)
        {
            const phantom::data& d = *it;
            loadDataState(d, pDB->getGuid(d), a_pNode, a_uiStateId);
        }
    }
}

void FileTreeDataStateBase::saveState(Node* a_pNode, const vector<data>& a_DataList, uint a_uiStateId)
{
    FileTreeNode* pNode = as<FileTreeNode*>(a_pNode);
    o_assert(pNode);

    FileTreeDataBase* pDB = static_cast<FileTreeDataBase*>(pNode->getDataBase());

    const string & path = statePath(a_pNode, a_uiStateId);
    if(NOT(boost::filesystem::exists(path.c_str())))
    {
        boost::filesystem::create_directories(path.c_str());
    }
    auto it = a_DataList.begin();
    auto end = a_DataList.end();
    for(;it!=end;++it)
    {
        const phantom::data& d = *it;
        saveDataState(d, pDB->getGuid(d), a_pNode, a_uiStateId);
    }

}

void FileTreeDataStateBase::loadDataState(const phantom::data& a_Data, uint guid, Node* a_pNode, uint a_uiStateId)
{
    FileTreeDataBase* pDB = static_cast<FileTreeDataBase*>(a_pNode->getDataBase());
    property_tree state_tree;
    const string& path = dataPath(a_Data, guid, a_pNode, a_uiStateId);
    if(boost::filesystem::exists(path.c_str()))
    {
        getFileTreeDataBase()->read(path, state_tree);
    }
    auto valueMembers_tag = state_tree.get_child_optional("valueMembers");
    if (valueMembers_tag.is_initialized())
    {
        a_Data.type()->deserialize(a_Data.address(), *valueMembers_tag, m_uiSerializationFlag, pDB);
    }
}

void FileTreeDataStateBase::saveDataState(const phantom::data& a_Data, uint guid, Node* a_pNode, uint a_uiStateId)
{
    bool bHasStateValueMember = false;
    vector<reflection::ValueMember*> valueMembers;
    a_Data.type()->asClass()->getValueMembersCascade(valueMembers);
    vector<reflection::ValueMember*>::iterator it = valueMembers.begin();
    vector<reflection::ValueMember*>::iterator end = valueMembers.end();
    for (; it != end; it++)
    {
        if ((*it)->isSaved(m_uiSerializationFlag))
        {
            bHasStateValueMember = true;
            break;
        }
    }

    if (bHasStateValueMember)
    {
        const string & nodePath = statePath(a_pNode, a_uiStateId);
        if(NOT(boost::filesystem::exists(nodePath.c_str())))
        {
            boost::filesystem::create_directories(nodePath.c_str());
        }
        FileTreeDataBase* pDB = static_cast<FileTreeDataBase*>(a_pNode->getDataBase());
        property_tree state_tree;
        property_tree valueMembers_tag;
        a_Data.type()->serialize(a_Data.address(), valueMembers_tag, m_uiSerializationFlag, pDB);
        if (NOT(valueMembers_tag.empty()))
        {
            state_tree.add_child("valueMembers", valueMembers_tag);
            getFileTreeDataBase()->write(dataPath(a_Data, guid, a_pNode, a_uiStateId), state_tree);
        }
    }
}

FileTreeDataBase* FileTreeDataStateBase::getFileTreeDataBase() const
{
    return static_cast<FileTreeDataBase*>(m_pDataBase);
}

o_namespace_end(phantom, serialization)
