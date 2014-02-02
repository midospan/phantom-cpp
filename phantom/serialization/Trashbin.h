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

#ifndef serialization_Trashbin_h__
#define serialization_Trashbin_h__
// #pragma message("Including "__FILE__)


/* ****************** Includes ******************* */
/* **************** Declarations ***************** */
o_declareN(class, (phantom, serialization), Trashbin);
/* *********************************************** */

o_namespace_begin(phantom, serialization)


class o_export Trashbin
{
	struct RemovedData
	{
		bool	operator==(const RemovedData& a_Other) const
		{
			return m_uiGuid == a_Other.m_uiGuid
				OR m_Data.address() == a_Other.m_Data.address();
		}

		data	m_Data;
		Node*	m_pNode;
		size_t	m_uiGuid;
	};

	struct RemovedNode
	{
		bool	operator==(const RemovedNode& a_Other) const
		{
			return m_uiGuid == a_Other.m_uiGuid
				OR m_pNode == a_Other.m_pNode;
		}

		Node*	m_pNode;
		Node*	m_pParentNode;
		size_t	m_uiGuid;
	};

    friend class DataBase;

public:

    Trashbin();
    o_destructor ~Trashbin();

	uint				getDataCount() const;
	const data&			getData(uint a_uiIndex) const;
	data				getDataByGuid(size_t a_uiGuid) const;
	data				getDataByAddress(void* a_pAddress) const;
	Node*				getNodeOf(const data& a_Data) const;

	uint				getNodeCount() const;
	Node*				getNode(uint a_uiIndex) const;
	Node*				getNodeByGuid(size_t a_uiGuid) const;
	Node*				getNodeOf(Node* a_pNode) const;

	void				addData(const data& a_Data, Node* a_pParentNode, uint a_uiGuid);
	void				removeData(const data& a_Data);
	void				removeDataByGuid(uint a_uiGuid);

	void				addNode(Node* a_pNode, Node* a_pParentNode, uint a_uiGuid);
	void				removeNode(Node* a_pNode);
	void				removeNodeByGuid(uint a_uiGuid);

	void				clean();

    void                rebuildAllData(reflection::Type* a_pOld, reflection::Type* a_pNew, vector<data>& a_OldData, vector<data>& a_NewData, uint a_uiStateId = 0xffffffff);

protected:
    DataBase*           m_pDataBase;
	vector<RemovedData>	m_Datas;
	vector<RemovedNode>	m_Nodes;
};

o_namespace_end(phantom, serialization)

#endif // serialization_Trashbin_h__
