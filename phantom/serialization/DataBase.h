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

#ifndef serialization_DataBase_h__
#define serialization_DataBase_h__
// #pragma message("Including "__FILE__)


/* ****************** Includes ******************* */
#include "phantom/Object.h"
/* **************** Declarations ***************** */
o_declareN(class, (phantom, serialization), DataBase)
/* *********************************************** */
o_namespace_begin(phantom, serialization)

class DefaultNode;
class DataTypeManager;
class Trashbin;

class o_export DataBase
{
    friend class Node;
    friend class DefaultNode;
    friend class Trashbin;

public:
    enum Constant
    {
        e_Constant_InvalidAttributeIndex = 0xffffffff,
        e_Constant_InvalidGuidValue = 0xffffffff
    };

    enum EActionOnMissingType
    {
        e_ActionOnMissingType_IgnoreAndDestroyData,
        e_ActionOnMissingType_NotifyAndDestroyData,
        e_ActionOnMissingType_Exception,
    };

protected:
    struct data_sorter_component_data_first
    {
        data_sorter_component_data_first(DataBase* a_pDataBase)
            : m_pDataBase(a_pDataBase) {}
        bool operator()(const phantom::data& d0, const phantom::data& d1)
        {
            phantom::data ownerD0 = m_pDataBase->getComponentDataOwner(d0);
            phantom::data ownerD1 = m_pDataBase->getComponentDataOwner(d1);

			// Compute the component order
			uint uiOrderD0 = 0;
			uint uiOrderD1 = 0;
			while(NOT(ownerD0.isNull()))
			{
				uiOrderD0++;
				ownerD0 = m_pDataBase->getComponentDataOwner(ownerD0);
			}
			while(NOT(ownerD1.isNull()))
			{
				uiOrderD1++;
				ownerD1 = m_pDataBase->getComponentDataOwner(ownerD1);
			}

            if(uiOrderD0 == uiOrderD1) // by adress
			{
				return d0.address() < d1.address();
			}

            // by order
            return uiOrderD0 < uiOrderD1;
        }
        DataBase* m_pDataBase;
    };

    struct data_sorter_owner_data_first
    {
        data_sorter_owner_data_first(DataBase* a_pDataBase)
            : m_pDataBase(a_pDataBase) {}
        bool operator()(const phantom::data& d1, const phantom::data& d0)
        {
			phantom::data ownerD0 = m_pDataBase->getComponentDataOwner(d0);
			phantom::data ownerD1 = m_pDataBase->getComponentDataOwner(d1);

			// Compute the component order
			uint uiOrderD0 = 0;
			uint uiOrderD1 = 0;
			while(NOT(ownerD0.isNull()))
			{
				uiOrderD0++;
				ownerD0 = m_pDataBase->getComponentDataOwner(ownerD0);
			}
			while(NOT(ownerD1.isNull()))
			{
				uiOrderD1++;
				ownerD1 = m_pDataBase->getComponentDataOwner(ownerD1);
			}

			if(uiOrderD0 == uiOrderD1) 
			{
				bool bD0IsOwner = m_pDataBase->isComponentDataOwner(d0);
				bool bD1IsOwner = m_pDataBase->isComponentDataOwner(d1);
				if (bD0IsOwner AND bD1IsOwner) // by adress
				{
					return d0.address() < d1.address();
				}
				return bD1IsOwner;
			}

			// by order
			return uiOrderD0 > uiOrderD1;
        }
        DataBase* m_pDataBase;
    };

    struct data_sorter_by_address
    {
        bool operator()(const phantom::data& d1, const phantom::data& d0)
        {
            return d0.address() < d1.address();
        }
    };
public:
    template<typename t_It>
    void sortComponentDataFirst(t_It first, t_It end)
    {
        std::sort(first, end, data_sorter_component_data_first(this));
    }

    template<typename t_It>
    void sortOwnerDataFirst(t_It first, t_It end)
    {
        std::sort(first, end, data_sorter_owner_data_first(this));
    }

    DataBase(const string& url, uint a_uiSerializationFlag = 0);
    o_destructor ~DataBase(void);

    o_initialize();
    o_terminate();

    void    save();

    void    saveData(const phantom::data& a_Data);

    void    saveState(uint a_uiState);

    void    saveDataState(const phantom::data& a_Data, uint a_uiState);

    void    loadState(uint a_uiState);

    void    setDataStateBase(DataStateBase* a_pDataStateBase)
    {
        o_assert(m_pDataStateBase == NULL);
        m_pDataStateBase = a_pDataStateBase;
    }

    DataStateBase*  getDataStateBase() const { return m_pDataStateBase; }

    Trashbin*       getTrashbin() const;
    Trashbin*		addTrashbin(const string& a_strUrl);

    void            restoreData(uint guid);
    void            restoreNode(uint guid);

    virtual void    clearDataReference(const phantom::data& a_data, vector<reflection::Expression*>* a_pRestoreReferenceExpressions = nullptr);

    virtual void    replaceDataReference(const phantom::data& a_old, const phantom::data& a_New);

    void            addType(reflection::Type* a_pType);
    void            removeType(reflection::Type* a_pType);
    void            replaceType(reflection::Type* a_pOld, reflection::Type* a_pNew, uint a_uiCurrentState = 0xffffffff);
    void            replaceTypes(const map<reflection::Type*, reflection::Type*>& replacedTypes, uint a_uiCurrentState = 0xffffffff);

    virtual boolean canMoveNode(Node* a_pNode, Node* a_pNewParent) const;
    virtual boolean canMoveData(const phantom::data& a_Data, Node* a_pNewParent) const;

    void            terminate();
    
    Node*           rootNode();

    Node*           getNode( const phantom::data& a_Data ) const
    {
        data_node_map::const_iterator found = m_DataNodeMap.find(a_Data.address());
        return found == m_DataNodeMap.end() ? NULL : found->second;
    }

    Node*           getNode( void* a_pAddress ) const
    {
        data_node_map::const_iterator found = m_DataNodeMap.find(phantom::baseOf(a_pAddress, 0));
        return found == m_DataNodeMap.end() ? NULL : found->second;
    }

    Node*                   getNode( uint a_uiGuid ) const;
    
    const phantom::data&    getComponentDataOwner( const phantom::data& a_Data ) const
    {
        static phantom::data null_data;
        component_data_owner_map::const_iterator found = m_ComponentDataOwnerMap.find(a_Data.address());
        return found == m_ComponentDataOwnerMap.end() ? null_data : found->second;
    }

    const string&           getComponentDataReferenceExpression( const phantom::data& a_Data ) const
    {
        static string null_string;
        component_data_reference_expression_map::const_iterator found = m_ComponentReferenceExpressionMap.find(a_Data.address());
        return found == m_ComponentReferenceExpressionMap.end() ? null_string : found->second;
    }

	bool                    isComponentDataOwner(const phantom::data& a_Data) const
	{
		component_data_owner_map::const_iterator it = m_ComponentDataOwnerMap.begin();
		component_data_owner_map::const_iterator end = m_ComponentDataOwnerMap.end();
		for (;it != end; it++)
		{
			if (it->second == a_Data)
			{
				return true;
			}
		}
		return false;
	}

    uint            getGuid( Node* a_pNode ) const;
    uint            getGuid( const phantom::data& a_Data ) const;
    void*           getDataAddress( uint guid ) const { return m_GuidBase.dataAddress(guid); }
    reflection::Type*getDataType( uint guid ) const { return m_GuidBase.dataType(guid); }
    const data&     getData( uint guid ) const { return m_GuidBase.getData(guid); }

    boolean         containsData(const phantom::data& a_Data) const { return m_GuidBase.getGuid(a_Data) != 0xffffffff; }
    boolean         containsDataAddress(void* a_pData) const;
    virtual void    loadNodeEntries() = 0;
    virtual void    unloadNodeEntries() = 0;

    virtual boolean hasNodeEntry(Node* a_pNode) const = 0;
    virtual boolean hasDataEntry(const data& a_Data, uint guid, Node* a_pOwnerNode) const = 0;

    void            moveNode(Node* a_pNode, Node* a_pNewParent);
    void            moveData(const phantom::data& a_Data, Node* a_pNewOwnerNode);

    boolean         dataHasDependency(const data& a_Data, const data& a_CandidateDependency) const
    {
        return a_Data.type()->referencesData(a_Data.address(), a_CandidateDependency);
    }

    void            registerData( const phantom::data& a_Data, uint a_Guid, Node* a_pOwnerNode );
    void            unregisterData( const phantom::data& a_Data);

    void            registerNode(Node* a_pNode);
    void            unregisterNode(Node* a_pNode);

    const string&   getDataAttributeValue(const phantom::data& a_Data, size_t attributeIndex) const;

    const string&   getDataAttributeValue(const phantom::data& a_Data, const string& attributeName) const;

    const string&   getNodeAttributeValue(Node* a_pNode, size_t attributeIndex) const;

    const string&   getNodeAttributeValue(Node* a_pNode, const string& attributeName) const;

    const string*   getDataAttributeValues(const phantom::data& a_data);

    const string*   getNodeAttributeValues(Node* a_pNode) const;

    void            setDataAttributeValue(const phantom::data& a_Data, size_t attributeIndex, const string& value);

    void            setDataAttributeValue(const phantom::data& a_Data, const string& fieldName, const string& value);

    void            setNodeAttributeValue(Node* a_pNode, size_t attributeIndex, const string& value);

    void            setNodeAttributeValue(Node* a_pNode, const string& fieldName, const string& value);

    size_t          getAttributeCount() const { return m_AttributeNames.size(); }

    size_t          addAttribute(const string& a_name);

    size_t          getAttributeIndex(const string& a_name) const;

    const string&   getAttributeName(size_t attributeIndex) const;

    const string*   getAttributeValues( void* a_pAddress ) const;

    size_t          getLoadedDataSize() const { return m_uiLoadedDataSize; }
    size_t          getLoadedDataResetSize() const { return m_uiLoadedDataResetSize; }
    size_t          getLoadedDataSerializedSize() const { return m_uiLoadedDataSerializedSize; }

    bool            isEmpty() const { return m_GuidBase.isEmpty(); }

    void            setDataTypeManager(DataTypeManager* a_pDataTypeManager);
    DataTypeManager*getDataTypeManager() const { return m_pDataTypeManager; }

    boolean         isDataRegistered(void* a_pData) const;

    boolean         isNodeRegistered(Node* a_pNode) const;

    const string&   getUrl() const { return m_strUrl; }
    boolean         isDataCompatibleWithNode(const phantom::data& a_Data, Node* a_pOwnerNode) const;

    void            setActionOnMissingType(EActionOnMissingType a_eAction)
    {
        m_eActionOnMissingType = a_eAction;
    }

    EActionOnMissingType  getActionOnMissingType() const
    {
        return m_eActionOnMissingType;
    }

    reflection::Type* solveTypeByName(const string& a_strName) const;
    reflection::Type* solveTypeById(uint id) const;


protected:
    o_signal_data(dataAdded, const phantom::data&, Node*);
    o_signal_data(dataReplaced, const phantom::data&, const phantom::data&);
    o_signal_data(dataAboutToBeRemoved, const phantom::data&, Node*);
    o_signal_data(dataAboutToBeAborted, const phantom::data&, Node*);
    o_signal_data(dataMoved, const phantom::data&, Node*, Node*);
    o_signal_data(dataAttributeValueChanged, const phantom::data&, size_t, const string&);

    o_signal_data(subDataOwnershipLost, const phantom::data&);

    o_signal_data(nodeAdded, Node*, Node*);
    o_signal_data(nodeAboutToBeRemoved, Node*, Node*);
    o_signal_data(nodeMoved, Node*, Node*, Node*);
    o_signal_data(nodeAttributeValueChanged, Node*, size_t, const string&);
    o_signal_data(dataErased, uint);
    o_signal_data(dataRestored, uint);

    virtual Trashbin* createTrashBin(const string& a_strUrl) const { return nullptr; }

    Node*           internalAddNewNode(Node* a_pParentNode);
    Node*           internalAddNewNode(uint a_uiGuid, Node* a_pParentNode);
    void			internalAddNode(Node* a_pNode, uint a_uiGuid, Node* a_pParentNode);
    void			internalAddData(const phantom::data& a_Data, uint a_uiGuid, Node* a_pOwnerNode);
    void			internalAddNewData(const phantom::data& a_Data, uint a_uiGuid, Node* a_pOwnerNode);
    void            internalRemoveData(const phantom::data& a_Data, uint a_Guid, Node* a_pOwnerNode);
    void			internalRemoveNode(Node* a_pNode, uint a_uiGuid, Node* a_pParentNode);

    virtual void    dataDestroyed(void* a_pAddress);

    void            replaceDataInfo(const phantom::data& a_Old, const phantom::data& a_New);

    virtual uint    generateGuid() = 0;
    virtual void    releaseGuid(uint guid) = 0;

    virtual Node*   createNode(uint a_Guid, Node* a_pParentNode) const = 0;
    virtual void    destroyNode(Node* a_pNode) const = 0;

    virtual void    createDataEntry(const phantom::data& a_Data, uint a_Guid, Node* a_pOwnerNode) = 0;
    virtual void    destroyDataEntry(const phantom::data& a_Data, uint a_Guid, Node* a_pOwnerNode) = 0;
    virtual void    moveDataEntry(const phantom::data& a_Data, uint a_Guid, Node* a_pOldParent, Node* a_pNewParent) = 0;

    virtual void    createNodeEntry(Node* a_pNode) = 0;
    virtual void    destroyNodeEntry(Node* a_pNode) = 0;
    virtual void    moveNodeEntry(Node* a_pNode, Node* a_pNewParent) = 0;       

    void            rebuildData( phantom::data& a_inOutData, reflection::Type* a_pOld, reflection::Type* a_pNewType, vector<data>& a_Old, vector<data>& a_New, uint a_uiStateId /*= 0xffffffff*/ );  

protected:
    void            registerComponentData(const data& a_Data, const data& a_Owner, const string& a_ReferenceExpression);
    void            unregisterComponentData(const data& a_Data);
    reflection::Collection* getCollectionContainingComponentData(const phantom::data& d) const;

protected:
    typedef map<void*, Node*>       data_node_map;
    typedef map<uint, Node*>        guid_node_map;

    typedef map<void*, string*>     attribute_map;
    typedef vector<string>          attribute_name_container;

    typedef map<void*,  data>       component_data_owner_map;
    typedef map<void*, string>      component_data_reference_expression_map;

    string                          m_strUrl;
    data_guid_base                  m_GuidBase;
    data_node_map                   m_DataNodeMap;
    component_data_owner_map        m_ComponentDataOwnerMap;
    component_data_reference_expression_map m_ComponentReferenceExpressionMap;
    attribute_map                   m_AttributeValues;
    attribute_name_container        m_AttributeNames;
    DataTypeManager*                m_pDataTypeManager;
    DataStateBase*                  m_pDataStateBase;
	Trashbin*						m_pTrashbin;
    EActionOnMissingType            m_eActionOnMissingType;
    size_t                          m_uiLoadedDataSize;
    size_t                          m_uiLoadedDataResetSize;
    size_t                          m_uiLoadedDataSerializedSize;
    uint                            m_uiSerializationFlag;

private:
    mutable Node*                   m_pRootNode;
};

o_namespace_end(phantom, serialization)

#endif
