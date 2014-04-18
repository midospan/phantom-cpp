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
#include "phantom/serialization/XmlFileTreeNode.h"
#include "phantom/serialization/XmlFileTreeDataBase.h"
#include <boost/property_tree_custom/xml_parser.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/fstream.hpp>
#include <phantom/serialization/XmlFileTreeDataStateBase.h>
#include <phantom/serialization/XmlFileTreeDataStateBase.hxx>
/* *********************************************** */
o_registerN((phantom, serialization), XmlFileTreeDataStateBase);

o_namespace_begin(phantom, serialization)

void XmlFileTreeDataStateBase::loadState(Node* a_pNode, uint a_uiStateId)
{
    XmlFileTreeNode* pNode = as<XmlFileTreeNode*>(a_pNode);
    o_assert(pNode);

    XmlFileTreeDataBase* pDB = static_cast<XmlFileTreeDataBase*>(pNode->getOwnerDataBase());
    o_assert(pDB);

    const string & path = statePath(a_pNode, a_uiStateId);

    if(hasStateSaved(a_pNode, a_uiStateId))
	{
		const XmlFileTreeNode::data_vector& nodeData = pNode->m_Data;
		XmlFileTreeNode::data_vector::const_iterator it = nodeData.begin();
		XmlFileTreeNode::data_vector::const_iterator end = nodeData.end();
		for(;it!=end;++it)
		{
			const phantom::data& d = *it;
			loadDataState(d, pDB->getGuid(d), a_pNode, a_uiStateId);
		}
	}
}

void XmlFileTreeDataStateBase::saveState(Node* a_pNode, uint a_uiStateId)
{
    XmlFileTreeNode* pNode = as<XmlFileTreeNode*>(a_pNode);
    o_assert(pNode);

    XmlFileTreeDataBase* pDB = static_cast<XmlFileTreeDataBase*>(pNode->getOwnerDataBase());

    const string & path = statePath(a_pNode, a_uiStateId);
    if(NOT(boost::filesystem::exists(path.c_str())))
    {
        boost::filesystem::create_directories(path.c_str());
    }
    const XmlFileTreeNode::data_vector& nodeData = pNode->m_Data;
    XmlFileTreeNode::data_vector::const_iterator it = nodeData.begin();
    XmlFileTreeNode::data_vector::const_iterator end = nodeData.end();
    for(;it!=end;++it)
    {
        const phantom::data& d = *it;
        saveDataState(d, pDB->getGuid(d), a_pNode, a_uiStateId);
    }

}

void XmlFileTreeDataStateBase::loadDataState(const phantom::data& a_Data, uint guid, Node* a_pNode, uint a_uiStateId)
{
	XmlFileTreeDataBase* pDB = static_cast<XmlFileTreeDataBase*>(a_pNode->getOwnerDataBase());
	property_tree state_tree;
	const string& path = dataPath(a_Data, guid, a_pNode, a_uiStateId);
	if(boost::filesystem::exists(path.c_str()))
	{
		boost::property_tree_custom::read_xml(path, state_tree);
	}
	auto valueMembers_tag = state_tree.get_child_optional("valueMembers");
	if (valueMembers_tag.is_initialized())
	{
		a_Data.type()->deserialize(a_Data.address(), *valueMembers_tag, m_uiSerializationFlag, pDB);
	}
}

void XmlFileTreeDataStateBase::saveDataState(const phantom::data& a_Data, uint guid, Node* a_pNode, uint a_uiStateId)
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
		XmlFileTreeDataBase* pDB = static_cast<XmlFileTreeDataBase*>(a_pNode->getOwnerDataBase());
		property_tree state_tree;
		property_tree valueMembers_tag;
		a_Data.type()->serialize(a_Data.address(), valueMembers_tag, m_uiSerializationFlag, pDB);
		if (NOT(valueMembers_tag.empty()))
		{
			state_tree.add_child("valueMembers", valueMembers_tag);
			boost::property_tree_custom::write_xml(dataPath(a_Data, guid, a_pNode, a_uiStateId), state_tree);
		}
	}
}

o_namespace_end(phantom, serialization)