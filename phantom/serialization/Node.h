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

#ifndef o_serialization_Node_h__
#define o_serialization_Node_h__
// #pragma message("Including "__FILE__)


/* ****************** Includes ******************* */
#include "phantom/util/TVisitor.h"
/* **************** Declarations ***************** */
o_declare(class, phantom, serialization, DataBase);
/* *********************************************** */
o_namespace_begin(phantom, serialization)

class o_export Node
{
    friend class DataBase;
    
public:
    enum EState
    {
        e_Unloaded,
        e_Cached,
        e_Built,
        e_Deserialized,
        e_Loaded,
        e_Unbuilt,
    };


    typedef vector<Node*>                               node_vector;

    typedef fastdelegate::FastDelegate< boolean (const data&) > data_filter_delegate;

    static boolean defaultDataFilter(const data& ) { return true; }

protected:
    Node(DataBase* a_pOwnerDataBase, uint a_Guid, Node* a_pParentNode);

public:
    o_terminate() 
    {
        destroyAllChildNode();
    }

public:
    boolean         isLoaded() const { return m_eState == e_Loaded; }
    boolean         isUnloaded() const { return m_eState == e_Unloaded; }
    EState          getState() const { return m_eState; }
	void			setState(EState a_eState);
    DataBase*       getOwnerDataBase() const { return m_pOwnerDataBase; }
    uint            getGuid() const { return m_Guid; }
    boolean         containsNode(Node* a_pNode) const
    {
        o_foreach(Node* pNode, m_ChildNodes)
        {
            if(pNode == a_pNode) return true;
        }
        return false;
    }
    Node*           getParentNode() const { return m_pParentNode; }
    boolean         hasParentNodeCascade(Node* a_pNode) const
    {
        if(m_pParentNode == a_pNode) return true;
        else return m_pParentNode
                        ? m_pParentNode->hasParentNodeCascade(a_pNode)
                        : false;
    }
    Node*           getChildNode(uint i) const { return m_ChildNodes[i]; }
    uint            getChildNodeCount() const { return m_ChildNodes.size(); }

    boolean	        acceptsData(const data& a_Data) const
    {
        return m_data_filter_delegate(a_Data);
    }

    void            unload();

    void            load();
    void            loadData(const phantom::data& a_Data);
    void            loadDataState(const phantom::data& a_Data, uint a_uiStateId);
    virtual void    loadAttributes() = 0;
    virtual void    loadDataAttributes() = 0;
    void            loadDataAttributes(const phantom::data& a_Data);
    virtual bool    canLoad(vector<string>* missing_types = nullptr) const = 0;
    
    void            save();
    void            saveData(const phantom::data& a_Data);
    void            saveData();
    void            saveDataState(const phantom::data& a_Data, uint a_uiStateId);
    virtual void    saveDataAttributes() = 0;
    virtual void    saveIndex() = 0;
    virtual void    saveAttributes() = 0;
    void            saveDataAttributes(const phantom::data& a_Data);
    void            saveCascade();

    void            saveState(uint a_uiState);
    void            loadState(uint a_uiState);
    void            saveStateCascade(uint a_uiStateId);
    void            loadStateCascade(uint a_uiStateId);

    bool            hasStateSaved(uint a_uiState) const;

    boolean         stepByStep();

	virtual void    preCache() = 0;
	virtual bool    cacheOne(uint a_uiIndex) = 0;
	virtual void	postCache() = 0;
	virtual void    uncacheOne(const phantom::data& a_Data) = 0;
	virtual void    buildOne(const phantom::data& a_Data) = 0;
	virtual void    unbuildOne(const phantom::data& a_Data) = 0;
	virtual void    deserializeOne(const phantom::data& a_Data, uint a_uiSerializationFlag) = 0;
	virtual bool    restoreOne(const phantom::data& a_Data, uint a_uiSerializationFlag, uint a_uiPass) = 0;

    boolean         containsDependencyOf(const data& a_Data) const;
    boolean         containsDataWhichDependsOnData(const data& a_Dependency) const;
    boolean         dependsOn(Node* a_pNode) const;
    boolean         containsDataWhichDependsOnDataCascade(const data& a_Dependency) const;
    boolean         containsDependencyOfDeep(const data& a_Data) const;
    boolean         childNodesContainDependencyOfDeep(const data& a_Data) const;

    void            getAllDescendantWhichDependsOn(const phantom::data& a_Data, vector<Node*>& a_NodeVector) const;
    void            getAllDescendantWhichDependsOn(Node* a_pNode, vector<Node*>& a_NodeVector) const;

    void            setDataFilterDelegate(data_filter_delegate a_data_filter_delegate)
    {
        m_data_filter_delegate = a_data_filter_delegate;
    }

    void            fetchData(vector<data>& a_DataVector) const;
    void            fetchDataCascade(vector<data>& a_DataVector) const;
    void            fetchDataOfType(reflection::Type* a_pType, vector<data>& a_DataVector) const;
    void            fetchDataOfTypeCascade(reflection::Type* a_pType, vector<data>& a_DataVector) const;

    void            fetchDataWhichDependsOnData(const phantom::data& a_Data, vector<data>& a_DataVector) const;
    void            fetchDataWhichDependsOnDataCascade(const phantom::data& a_Data, vector<data>& a_DataVector) const;

    void            applyNodeVisitor(util::TVisitor<Node>* visitor);

    void            applyDataVisitor(util::TVisitor<data>* visitor);

    void            destroyAllData();
    void            destroyAllDataCascade();
    
    /*
     *   /brief add a new child node to the given node
    */
    Node*           addChildNode();
	void			addChildNode(Node* a_pNode, uint a_uiGuid);

    /*
     *   /brief add a new child node to the given node
    */
    void            removeAndDeleteChildNode(Node* a_pNode);
	void            removeChildNode(Node* a_pNode);

    /*
     *   /brief add a new data to the given node
    */
    void            addData(const data& a_Data);

    /*
     *   /brief add a new data to the given node with the given guid
    */
	void			addData( const data& a_Data, uint a_uiGuid );
    
    /*
     *   /brief add new multiple contiguous data to the given node
    */
    void            addData(const data& a_Data, size_t a_uiCount, size_t a_uiChunkSectionSize);

    /*
     *   /brief remove definitely the given data from the data base by its address
    */
    void            removeData(void* a_pData);

    /*
     *   /brief remove definitely the given data from the data base
    */
    void            removeData(const phantom::data& a_Data);

    void            removeData(void* a_pData, size_t a_uiCount, size_t a_uiChunkSectionSize)
    {
        const rtti_data& objInfo = phantom::rttiDataOf(a_pData);
        o_assert(NOT(objInfo.isNull()), "Data given to the DataBase is not a phantom registered class instance and no type has been provided");
        removeData(phantom::data(objInfo.base, objInfo.object_class), a_uiCount, a_uiChunkSectionSize);
    }

    void            removeData(const phantom::data& a_Data, size_t a_uiCount, size_t a_uiChunkSectionSize);

    boolean         containsData(const data& a_Data) const;

    vector<phantom::data>::const_iterator beginData() const { return m_Data.begin(); }
    vector<phantom::data>::const_iterator endData() const { return m_Data.end(); }

    bool            isEmpty() const { return m_Data.empty(); }

    void            addDataComponentsCascade(vector<data_pair>* opt_out_to_add = nullptr, vector<data_pair>* opt_out_to_remove = nullptr);
    void            addDataComponents(vector<std::pair<phantom::data,phantom::data>>* opt_out_to_add = nullptr, vector<std::pair<phantom::data,phantom::data>>* opt_out_to_remove = nullptr);

protected:
    void            addDataComponents( const phantom::data& a_Data, size_t a_uiCurrentSize, vector<std::pair<phantom::data,phantom::data>>* opt_out_to_add /*= nullptr*/,vector<std::pair<phantom::data,phantom::data>>* opt_out_to_remove /*= nullptr*/);
    void            addDataComponents(const phantom::data& a_Data, vector<std::pair<phantom::data,phantom::data>>* opt_out_to_add = nullptr, vector<std::pair<phantom::data,phantom::data>>* opt_out_to_remove = nullptr);
    void            fetchDataComponents(const phantom::data& a_Data, vector<phantom::data>& out );
    void            fetchContainerComponents(reflection::ContainerClass* a_pContainerClass, void* a_pContainer, vector<phantom::data>& out);

    void            rebuildAllData(reflection::Type* a_pOld, reflection::Type* a_pNew, vector<data>& a_Old, vector<data>& a_New, uint a_uiStateId = 0xffffffff) ;
    void            rebuildAllDataCascade(reflection::Type* a_pOld, reflection::Type* a_pNew, vector<data>& a_Old, vector<data>& a_New, uint a_uiStateId = 0xffffffff);

    void            clearDataReferenceCascade(const vector<void*>& a_OldLayout) const;

    void            clearDataReference( const vector<void*>& layout ) const;

    void            replaceDataReferenceCascade(const vector<void*>& a_OldLayout, const phantom::data& a_New) const;

    bool            replaceDataReference(const vector<void*>& a_OldLayout, const phantom::data& a_New, bool a_SetIncompatibleToNull) const;

    void            internalAddData(const data& a_Data, uint guid);

    void            internalRemoveData(const data& a_Data);

protected:
    o_signal_data_declaration(loaded);
    o_signal_data(aboutToBeUnloaded);

protected:
    virtual void    saveData(uint a_uiSerializationFlag, const phantom::data& a_Data, uint guid) = 0;
    virtual void    loadData(uint a_uiSerializationFlag, const phantom::data& a_Data, uint guid) = 0;
    virtual void    saveDataAttributes(const phantom::data& a_Data, uint guid) = 0;
    virtual void    loadDataAttributes(const phantom::data& a_Data, uint guid) = 0;
    virtual void    cache() = 0;
    virtual void    build() = 0;
    virtual void    deserialize(uint a_uiSerializationFlag) = 0;
    virtual void    unbuild() = 0;
    virtual void    uncache() = 0;
    virtual void    restore(uint a_uiSerializationFlag) = 0;
    virtual void    configure() = 0;
    virtual void    unconfigure() = 0;


    void    storeData(const phantom::data& a_Data);
    void    eraseData(const phantom::data& a_Data);
    void    storeData(const phantom::data& a_Data, size_t a_uiCount, size_t a_uiChunkSectionSize);
    void    eraseData(const phantom::data& a_Data, size_t a_uiCount, size_t a_uiChunkSectionSize);

    void    storeNode(Node* a_pNode);
    void    eraseNode(Node* a_pNode);

    void    destroyAllChildNode();

    void    registerData(const phantom::data& a_Data, uint guid);
    void    unregisterData(const phantom::data& a_Data);
    void    abortData( const phantom::data& a_Data );

    void    saveStateCascade(DataStateBase* a_pDataStateBase, uint a_uiStateId);
    void    loadStateCascade(DataStateBase* a_pDataStateBase, uint a_uiStateId);

    const data&     findData(void* a_pAddress) const;

protected:
    typedef vector<phantom::data> data_vector;
    data_vector             m_Data;
    data_filter_delegate    m_data_filter_delegate;
    uint                    m_Guid;
    node_vector             m_ChildNodes;
    Node*                   m_pParentNode;
    DataBase*               m_pOwnerDataBase;
    EState                  m_eState;

};

o_namespace_end(phantom, serialization)

o_classN((phantom, serialization), Node)
{
    o_reflection 
    {
        o_signal(loaded, ());
        o_signal(aboutToBeUnloaded, ());
    };
};
o_exposeN((phantom, serialization), Node);

#endif // o_serialization_Node
