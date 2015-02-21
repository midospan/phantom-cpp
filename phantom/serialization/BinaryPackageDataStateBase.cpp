/* TODO LICENCE HERE */

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include "phantom/serialization/BinaryPackageNode.h"
#include "phantom/serialization/BinaryPackageDataBase.h"
#if o__bool__use_custom_stl_partioned_allocator OR o__bool__use_custom_stl_contiguous_allocator
#include <boost/property_tree_custom/xml_parser.hpp>
#else 
#include <boost/property_tree/xml_parser.hpp>
#endif
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/fstream.hpp>
#include <phantom/serialization/BinaryPackageDataStateBase.h>
#include <phantom/serialization/BinaryPackageDataStateBase.hxx>
#include <phantom/serialization/BinaryPackageDataBase.h>
/* *********************************************** */
o_registerN((phantom, serialization), BinaryPackageDataStateBase);

o_namespace_begin(phantom, serialization)

BinaryPackageDataStateBase::BinaryPackageDataStateBase(BinaryPackageDataBase* a_pDataBase, const string& a_Url, uint a_uiSerializationFlag)
: PackageDataStateBase(a_pDataBase, a_Url, a_uiSerializationFlag)
{

}

o_destructor BinaryPackageDataStateBase::~BinaryPackageDataStateBase()
{

}

void BinaryPackageDataStateBase::loadState(Node* a_pNode, uint a_uiStateId)
{
    BinaryPackageNode* pNode = as<BinaryPackageNode*>(a_pNode);
    o_assert(pNode);

    BinaryPackageDataBase* pDB = static_cast<BinaryPackageDataBase*>(pNode->getDataBase());
    o_assert(pDB);

    /*const string & path = statePath(a_pNode, a_uiStateId);

    o_assert(hasStateSaved(a_pNode, a_uiStateId));

    const BinaryPackageNode::data_vector& nodeData = pNode->m_Data;
    BinaryPackageNode::data_vector::const_iterator it = nodeData.begin();
    BinaryPackageNode::data_vector::const_iterator end = nodeData.end();
    for(;it!=end;++it)
    {
        const phantom::data& d = *it;
        loadDataState(d, pDB->getGuid(d), a_pNode, a_uiStateId);
    }*/
}

void BinaryPackageDataStateBase::saveState(Node* a_pNode, uint a_uiStateId)
{
    BinaryPackageNode* pNode = as<BinaryPackageNode*>(a_pNode);
    o_assert(pNode);

    BinaryPackageDataBase* pDB = static_cast<BinaryPackageDataBase*>(pNode->getDataBase());

    /*const string & path = statePath(a_pNode, a_uiStateId);
    if(NOT(boost::filesystem::exists(path.c_str())))
    {
        boost::filesystem::create_directories(path.c_str());
    }
    const BinaryPackageNode::data_vector& nodeData = pNode->m_Data;
    BinaryPackageNode::data_vector::const_iterator it = nodeData.begin();
    BinaryPackageNode::data_vector::const_iterator end = nodeData.end();
    for(;it!=end;++it)
    {
        const phantom::data& d = *it;
        saveDataState(d, pDB->getGuid(d), a_pNode, a_uiStateId);
    }*/
}

void BinaryPackageDataStateBase::loadDataState(const phantom::data& a_Data, uint a_uiGuid, Node* a_pNode, uint a_uiStateId)
{
    BinaryPackageDataBase* pDB = static_cast<BinaryPackageDataBase*>(a_pNode->getDataBase());
    property_tree state_tree;
    /*property_tree_namespace::read_xml(dataPath(a_Data, a_uiGuid, a_pNode, a_uiStateId), state_tree);
    property_tree valueMembers_tag;
    valueMembers_tag = state_tree.get_child("valueMembers");
    a_Data.type()->deserialize(a_Data.address(), valueMembers_tag, m_uiSerializationFlag, pDB);*/
}

void BinaryPackageDataStateBase::saveDataState(const phantom::data& a_Data, uint a_uiGuid, Node* a_pNode, uint a_uiStateId)
{
    BinaryPackageDataBase* pDB = static_cast<BinaryPackageDataBase*>(a_pNode->getDataBase());
    property_tree state_tree;
    property_tree valueMembers_tag;
    /*a_Data.type()->serialize(a_Data.address(), valueMembers_tag, m_uiSerializationFlag, pDB);
    state_tree.add_child("valueMembers", valueMembers_tag);
    property_tree_namespace::write_xml(dataPath(a_Data, a_uiGuid, a_pNode, a_uiStateId), state_tree);*/
}

o_namespace_end(phantom, serialization)