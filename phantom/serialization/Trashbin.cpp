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
#include "Trashbin.h"
#include "Trashbin.hxx"
/* *********************************************** */
o_registerN((phantom, serialization), Trashbin);

o_namespace_begin(phantom, serialization)
   
Trashbin::Trashbin()
{

}

Trashbin::~Trashbin()
{

}

uint Trashbin::getDataCount() const
{
	return m_Datas.size();
}

const data& Trashbin::getData(uint a_uiIndex) const
{
	return m_Datas[a_uiIndex].m_Data;
}

data Trashbin::getDataByGuid(size_t a_uiGuid) const
{
	RemovedData d;
	d.m_uiGuid = a_uiGuid;

	vector<RemovedData>::const_iterator it = std::find(m_Datas.begin(), m_Datas.end(), d);
	if (it != m_Datas.end())
	{
		return it->m_Data;
	}
	return data();
}

data Trashbin::getDataByAddress(void* a_pAddress) const
{
	RemovedData d;
	d.m_Data = data(a_pAddress, 0);

	vector<RemovedData>::const_iterator it = std::find(m_Datas.begin(), m_Datas.end(), d);
	if (it != m_Datas.end())
	{
		return it->m_Data;
	}
	return data();
}

Node* Trashbin::getNodeOf(const data& a_Data) const
{
	RemovedData d;
	d.m_Data = a_Data;

	vector<RemovedData>::const_iterator it = std::find(m_Datas.begin(), m_Datas.end(), d);
	if (it != m_Datas.end())
	{
		return it->m_pNode;
	}
	return NULL;
}

uint Trashbin::getNodeCount() const
{
	return m_Nodes.size();
}

Node* Trashbin::getNode(uint a_uiIndex) const
{
	return m_Nodes[a_uiIndex].m_pNode;
}

Node* Trashbin::getNodeByGuid(size_t a_uiGuid) const
{
	RemovedNode node;
	node.m_uiGuid = a_uiGuid;

	vector<RemovedNode>::const_iterator it = std::find(m_Nodes.begin(), m_Nodes.end(), node);
	if (it != m_Nodes.end())
	{
		return it->m_pNode;
	}
	return NULL;
}

Node* Trashbin::getNodeOf(Node* a_pNode) const
{
	RemovedNode node;
	node.m_pNode = a_pNode;

	vector<RemovedNode>::const_iterator it = std::find(m_Nodes.begin(), m_Nodes.end(), node);
	if (it != m_Nodes.end())
	{
		return it->m_pParentNode;
	}
	return NULL;
}

void Trashbin::addData(const data& a_Data, Node* a_pParentNode, uint a_uiGuid)
{
	o_assert(getDataByGuid(a_uiGuid).isNull());

	RemovedData d;
	d.m_Data = a_Data;
	d.m_pNode = a_pParentNode;
	d.m_uiGuid = a_uiGuid;
	m_Datas.push_back(d);
}

void Trashbin::removeData(const data& a_Data)
{
	RemovedData d;
	d.m_Data = a_Data;

	vector<RemovedData>::const_iterator it = std::find(m_Datas.begin(), m_Datas.end(), d);
	o_assert(it != m_Datas.end());

	m_Datas.erase(it);
}

void Trashbin::removeDataByGuid(uint a_uiGuid)
{
	RemovedData d;
	d.m_uiGuid = a_uiGuid;

	vector<RemovedData>::const_iterator it = std::find(m_Datas.begin(), m_Datas.end(), d);
	o_assert(it != m_Datas.end());

	m_Datas.erase(it);
}

void Trashbin::addNode(Node* a_pNode, Node* a_pParentNode, uint a_uiGuid)
{
	o_assert(getNodeByGuid(a_uiGuid) == NULL);

	RemovedNode node;
	node.m_pNode = a_pNode;
	node.m_pParentNode = a_pParentNode;
	node.m_uiGuid = a_uiGuid;

	m_Nodes.push_back(node);
}

void Trashbin::removeNode(Node* a_pNode)
{
	RemovedNode node;
	node.m_pNode = a_pNode;

	vector<RemovedNode>::const_iterator it = std::find(m_Nodes.begin(), m_Nodes.end(), node);
	o_assert(it != m_Nodes.end());

	m_Nodes.erase(it);
}

void Trashbin::removeNodeByGuid(uint a_uiGuid)
{
	RemovedNode node;
	node.m_uiGuid = a_uiGuid;

	vector<RemovedNode>::const_iterator it = std::find(m_Nodes.begin(), m_Nodes.end(), node);
	o_assert(it != m_Nodes.end());

	m_Nodes.erase(it);
}

void Trashbin::clean()
{
	m_Datas.clear();
	m_Nodes.clear();
}

void Trashbin::rebuildAllData(reflection::Type* a_pOld, reflection::Type* a_pNew, vector<data>& a_OldData, vector<data>& a_NewData, uint a_uiStateId /*= 0xffffffff*/)
{
    for(auto it = m_Datas.begin(); it != m_Datas.end(); ++it)
    {
        if(it->m_Data.type() == a_pOld) 
        {
            m_pDataBase->rebuildData(it->m_Data, a_pOld, a_pNew, a_OldData, a_NewData, a_uiStateId);
        }
    }
}

o_namespace_end(phantom, serialization)
