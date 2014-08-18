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
o_fwd(class, phantom, serialization, DataBase);
o_fwd(class, phantom, serialization, Trashbin);
o_declareN(class, (phantom, serialization), Node)
/* *********************************************** */
o_namespace_begin(phantom, serialization)

class o_export Node
{
    friend class DataBase;
    friend class Trashbin;
    
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
    o_terminate(); 

public:
    phantom::data   getData(size_t i) const { return m_Data[i]; }
    size_t          getDataCount() const { return m_Data.size(); }
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
    void            unloadCascade();

    void            load();
    void            loadData(const phantom::data& a_Data);
    void            loadDataState(const phantom::data& a_Data, uint a_uiStateId);
    virtual void    loadTypes() = 0;
    virtual void    loadAttributes() = 0;
    virtual void    loadDataAttributes() = 0;
    void            loadDataAttributes(const phantom::data& a_Data);
    virtual bool    canLoad(vector<string>* missing_types = nullptr) const = 0;
    
    void            save();
    void            saveData(const phantom::data& a_Data);
    void            saveData();
    void            saveDataState(const phantom::data& a_Data, uint a_uiStateId);
    virtual void    saveTypes() = 0;
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

    phantom::data   getData(void* a_pAddress) const;
    void            fetchData(vector<data>& a_DataVector) const;
    void            fetchDataCascade(vector<data>& a_DataVector) const;
    void            fetchDataOfType(reflection::Type* a_pType, vector<data>& a_DataVector) const;
    void            fetchDataOfTypeCascade(reflection::Type* a_pType, vector<data>& a_DataVector) const;

    void            fetchDataWhichDependsOnData(const phantom::data& a_Data, vector<data>& a_DataVector) const;
    void            fetchDataWhichDependsOnDataCascade(const phantom::data& a_Data, vector<data>& a_DataVector) const;

    void            applyNodeVisitor(TVisitor<Node>* visitor);

    void            applyDataVisitor(TVisitor<data>* visitor);

    void            destroyAllData();
    void            destroyAllDataCascade();
    
    /*
     *   /brief add a new child node to the given node
    */
    Node*           newChildNode();
    Node*           newChildNode(uint guid);

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
     *   /brief add a new component data to the given node
    */
    void            addComponentData(const data& a_Data, const data& a_OwnerData, const string& a_ReferenceExpression);

    /*
     *   /brief add a new component data to the given node with choosen guid
    */
    void            addComponentData(const data& a_Data, uint a_uiGuid, const data& a_OwnerData, const string& a_ReferenceExpression);

    /*
     *   /brief add a new data of given type to the given node (node instanciate the data)
    */
    phantom::data   newData(reflection::Type* a_pType);

    /*
     *   /brief add a new data to the given node with the given guid
    */
	void			addData( const data& a_Data, uint a_uiGuid );

    /*
     *   /brief add a new data of given type to the given node (node instanciate the data)
    */
    phantom::data   newData(reflection::Type* a_pType, uint a_uiGuid);
    
    /*
     *   /brief add new multiple contiguous data to the given node
    */
    void            addData(const data& a_Data, size_t a_uiCount, size_t a_uiChunkSectionSize);

    /*
     *   /brief remove definitely the given data from the data base by its address
    */
    void            removeData(void* a_pData);
    
    /*
     *   /brief remove definitely the given data from the data base by its address
    */
    void            removeComponentData(const data& a_Data, const data& a_OwnerData);

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

    vector<Node*>::const_iterator beginChildNodes() const { return m_ChildNodes.begin(); }
    vector<Node*>::const_iterator endChildNodes() const { return m_ChildNodes.end(); }

    bool            isEmpty() const { return m_Data.empty(); }

    void            fetchUpdatedData(const phantom::data& a_Data, vector<data_pair>& out_to_add, vector<data_pair>& out_to_remove, vector<string>& out_to_add_reference_expressions, vector<phantom::data>& a_TreatedData);
    void            fetchUpdatedData(const phantom::data& a_Data, vector<data_pair>& out_to_add, vector<data_pair>& out_to_remove, vector<string>& out_to_add_reference_expressions, std::set<phantom::data>& a_TreatedData);

    reflection::Type* getType(const string& a_strQualifiedDecoratedName) const;

    void            addType(reflection::Type* a_pType);

    void            removeType(reflection::Type* a_pType);

    void            replaceTypes(const map<reflection::Type*, reflection::Type*>& replacedTypes);

    uint            generateGuid() const;

protected:
    void            fetchUpdatedData(const phantom::data& a_Data
        , vector<data_pair>& out_to_add /*= nullptr*/
        , vector<data_pair>& out_to_remove /*= nullptr*/
        , vector<string>& out_added_pointer_reference_expressions);
    void            fetchComponentData(const phantom::data& a_Data, vector<phantom::data>& out );
    void            fetchContainerComponents(reflection::ContainerClass* a_pContainerClass, void* a_pContainer, vector<phantom::data>& out);

    void            rebuildAllData(reflection::Type* a_pOld, reflection::Type* a_pNew, vector<data>& a_Old, vector<data>& a_New, uint a_uiStateId = 0xffffffff) ;
    void            rebuildAllDataCascade(reflection::Type* a_pOld, reflection::Type* a_pNew, vector<data>& a_Old, vector<data>& a_New, uint a_uiStateId = 0xffffffff);

    void            clearDataReferenceCascade(const vector<void*>& a_OldLayout, vector<reflection::Expression*>* a_pRestoreReferenceExpressions = nullptr) const;

    void            clearDataReference( const vector<void*>& layout, vector<reflection::Expression*>* a_pRestoreReferenceExpressions = nullptr ) const;

    void            replaceDataReferenceCascade(const vector<void*>& a_OldLayout, const phantom::data& a_New) const;

    bool            replaceDataReference(const vector<void*>& a_OldLayout, const phantom::data& a_New, bool a_SetIncompatibleToNull) const;

    void            internalAddData(const data& a_Data, uint guid);

    void            internalRemoveData(const data& a_Data);

protected:
    o_signal_data(loaded);
    o_signal_data(aboutToBeUnloaded);

protected:
    virtual void    saveData(uint a_uiSerializationFlag, const phantom::data& a_Data, uint guid) = 0;
    virtual void    loadData(uint a_uiSerializationFlag, const phantom::data& a_Data, uint guid) = 0;
    virtual void    saveDataAttributes(const phantom::data& a_Data, uint guid) = 0;
    virtual void    loadDataAttributes(const phantom::data& a_Data, uint guid) = 0;
    virtual void    cache() = 0;
    virtual void    build(vector<data>& a_Data) = 0;
    virtual void    deserialize(uint a_uiSerializationFlag, vector<data>& a_Data) = 0;
    virtual void    unbuild() = 0;
    virtual void    uncache() = 0;
    virtual void    restore(uint a_uiSerializationFlag, vector<data>& a_Data) = 0;
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
    typedef map<string, reflection::Type*> type_map;
    data_vector             m_Data;
    type_map                m_Types;
    data_filter_delegate    m_data_filter_delegate;
    uint                    m_Guid;
    node_vector             m_ChildNodes;
    Node*                   m_pParentNode;
    DataBase*               m_pOwnerDataBase;
    EState                  m_eState;

};

o_namespace_end(phantom, serialization)

#endif // o_serialization_Node
