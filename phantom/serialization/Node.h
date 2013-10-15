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

#ifndef serialization_Node_h__
#define serialization_Node_h__
// #pragma message("Including "__FILE__)


/* ****************** Includes ******************* */
#include "phantom/util/TVisitor.h"
/* *********************************************** */
/* The *.classdef.h file must be the last #include */
#include "Node.classdef.h"
/* **************** Declarations ***************** */

/* *********************************************** */
o_h_begin

class o_export Node : public Object
{
    friend class DataBase;
    
    reflection_____________________________________________________________________________________
    _____________________________________________________________________________________reflection

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
    Node(DataBase* a_pOwnerDataBase, uint a_Guid, Node* a_pParentNode)
        : m_data_filter_delegate(&Node::defaultDataFilter)
        , m_Guid(a_Guid)
        , m_pOwnerDataBase(a_pOwnerDataBase)
        , m_eState(e_Unloaded)
    {
        o_assert(a_pParentNode != NULL  // must have a parent node
            OR a_Guid == 0);            // except the root node
        m_pParentNode = a_pParentNode;
        if(m_pParentNode)
        {
            m_pParentNode->storeNode(this);
        }
    }

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
    void            load(uint a_uiSerializationFlag);
    void            loadData(const phantom::data& a_Data);
    void            loadDataState(const phantom::data& a_Data, uint a_uiStateId);
    virtual void    loadAttributes() = 0;
    virtual void    loadDataAttributes() = 0;
    void            loadDataAttributes(const phantom::data& a_Data);
    virtual boolean canLoad(vector<string>& missing_types) = 0;
    
    void            save();
    void            save(uint a_uiSerializationFlag) { saveIndex(); saveAttributes(); saveData(a_uiSerializationFlag); }
    void            saveData(const phantom::data& a_Data);
    virtual void    saveData(uint a_uiSerializationFlag) = 0;
    void            saveDataState(const phantom::data& a_Data, uint a_uiStateId);
    virtual void    saveDataAttributes() = 0;
    virtual void    saveIndex() = 0;
    virtual void    saveAttributes() = 0;
    void            saveDataAttributes(const phantom::data& a_Data);

    
    void            saveCascade(uint a_uiSerializationFlag)
    {
        o_assert(isLoaded());
        save(a_uiSerializationFlag);
        node_vector::const_iterator it = m_ChildNodes.begin();
        node_vector::const_iterator end = m_ChildNodes.end();
        for(;it!=end;++it)
        {
            if((*it)->isLoaded())
            {
                (*it)->saveCascade(a_uiSerializationFlag);
            }
        }
    }

    void            saveState(uint a_uiState);
    void            loadState(uint a_uiState);
    void            saveStateCascade(uint a_uiStateId);
    void            loadStateCascade(uint a_uiStateId);

    bool            hasStateSaved(uint a_uiState) const;

    boolean         stepByStep(uint a_uiSerializationFlag);

	virtual void    preCache() = 0;
	virtual bool    cacheOne(uint a_uiIndex) = 0;
	virtual void	postCache() = 0;
	virtual void    uncacheOne(const phantom::data& a_Data) = 0;
	virtual void    buildOne(const phantom::data& a_Data) = 0;
	virtual void    unbuildOne(const phantom::data& a_Data) = 0;
	virtual void    deserializeOne(const phantom::data& a_Data, uint a_uiSerializationFlag) = 0;
	virtual bool    restoreOne(const phantom::data& a_Data, uint a_uiSerializationFlag, uint a_uiPass) = 0;

    virtual boolean containsData(const data& a_Data) const = 0;
    virtual boolean containsDependencyOf(const data& a_Data) const = 0;
    virtual boolean containsDataWhichDependsOnData(const data& a_Dependency) const = 0;
    virtual boolean dependsOn(Node* a_pNode) const = 0;
    boolean         containsDataWhichDependsOnDataCascade(const data& a_Dependency) const
    {
        return containsDataWhichDependsOnData(a_Dependency)
            OR (m_pParentNode ? m_pParentNode->containsDataWhichDependsOnDataCascade(a_Dependency) : false);
    }
    virtual boolean containsDependencyOfDeep(const data& a_Data) const
    {
        return containsDependencyOf(a_Data)
            OR childNodesContainDependencyOfDeep(a_Data) ;
    }
    virtual boolean childNodesContainDependencyOfDeep(const data& a_Data) const
    {
        node_vector::const_iterator it = m_ChildNodes.begin();
        node_vector::const_iterator end = m_ChildNodes.end();
        for(;it!=end;++it)
        {
            if((*it)->containsDependencyOfDeep(a_Data))
                return true;
        }
        return false;
    }

    virtual void    getAllDescendantWhichDependsOn(const phantom::data& a_Data, vector<Node*>& a_NodeVector) const
    {
        node_vector::const_iterator it = m_ChildNodes.begin();
        node_vector::const_iterator end = m_ChildNodes.end();
        for(;it!=end;++it)
        {
            if((*it)->containsDataWhichDependsOnData(a_Data))
                a_NodeVector.push_back(*it);
            (*it)->getAllDescendantWhichDependsOn(a_Data, a_NodeVector);
        }
    }
    virtual void    getAllDescendantWhichDependsOn(Node* a_pNode, vector<Node*>& a_NodeVector) const
    {
        node_vector::const_iterator it = m_ChildNodes.begin();
        node_vector::const_iterator end = m_ChildNodes.end();
        for(;it!=end;++it)
        {
            if((*it)->dependsOn(a_pNode))
                a_NodeVector.push_back(*it);
            (*it)->getAllDescendantWhichDependsOn(a_pNode, a_NodeVector);
        }
    }

    void            setDataFilterDelegate(data_filter_delegate a_data_filter_delegate)
    {
        m_data_filter_delegate = a_data_filter_delegate;
    }

    virtual void    getAllData(vector<data>& a_DataVector) const = 0;
    void            getAllDataCascade(vector<data>& a_DataVector) const
    {
        getAllData(a_DataVector);
        node_vector::const_iterator it = m_ChildNodes.begin();
        node_vector::const_iterator end = m_ChildNodes.end();
        for(;it!=end;++it)
        {
            (*it)->getAllDataCascade(a_DataVector);
        }
    }

    virtual void    getAllDataWithType(reflection::Type* a_pType, vector<data>& a_DataVector) const = 0;
    void            getAllDataWithTypeCascade(reflection::Type* a_pType, vector<data>& a_DataVector) const
    {
        getAllDataWithType(a_pType, a_DataVector);
        node_vector::const_iterator it = m_ChildNodes.begin();
        node_vector::const_iterator end = m_ChildNodes.end();
        for(;it!=end;++it)
        {
            (*it)->getAllDataWithTypeCascade(a_pType, a_DataVector);
        }
    }

    virtual void getAllDataWhichDependsOnData(const phantom::data& a_Data, vector<data>& a_DataVector) const = 0;
    void getAllDataWhichDependsOnDataCascade(const phantom::data& a_Data, vector<data>& a_DataVector) const
    {
        getAllDataWhichDependsOnData(a_Data, a_DataVector);
        node_vector::const_iterator it = m_ChildNodes.begin();
        node_vector::const_iterator end = m_ChildNodes.end();
        for(;it!=end;++it)
        {
            (*it)->getAllDataWhichDependsOnDataCascade(a_Data, a_DataVector);
        }
    }

    void    applyNodeVisitor(util::TVisitor<Node>* visitor)
    {
        visitor->apply(this);
        node_vector::const_iterator it = m_ChildNodes.begin();
        node_vector::const_iterator end = m_ChildNodes.end();
        for(;it!=end;++it)
        {
            (*it)->applyNodeVisitor(visitor);
        }
    }

    virtual void    applyDataVisitor(util::TVisitor<data>* visitor) = 0;

    virtual void    destroyAllData() = 0;
    void            destroyAllDataCascade();
    
    /*
     *   /brief add a new child node to the given node
    */
    Node*           addChildNode();

    /*
     *   /brief add a new child node to the given node
    */
    void            removeAndDeleteChildNode(Node* a_pNode);

    /*
     *   /brief add a new data to the given node
    */
    void            addData(const data& a_Data);

    /*
     *   /brief add a new data to the given node with the given guid
    */
	void			addData( const data& a_Data, UINT a_uiGuid );
    
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

    virtual void    addDataComponents(vector<data_pair>* opt_out_to_add = nullptr, vector<data_pair>* opt_out_to_remove = nullptr) = 0;
    virtual void    addDataComponents(const phantom::data& a_Data, vector<data_pair>* opt_out_to_add = nullptr, vector<data_pair>* opt_out_to_remove = nullptr) = 0;

    void            addDataComponentsCascade(vector<data_pair>* opt_out_to_add = nullptr, vector<data_pair>* opt_out_to_remove = nullptr);

protected:
    virtual void    addDataComponents(const phantom::data& a_Data, size_t a_uiCurrentSize, vector<std::pair<phantom::data,phantom::data>>* opt_out_to_add = nullptr, vector<std::pair<phantom::data,phantom::data>>* opt_out_to_remove = nullptr) = 0;
    void            fetchDataComponents(const phantom::data& a_Data, vector<phantom::data>& out );
    void            fetchContainerComponents(reflection::ContainerClass* a_pContainerClass, void* a_pContainer, vector<phantom::data>& out);

    virtual void    rebuildAllData(reflection::Type* a_pOld, reflection::Type* a_pNew, vector<data>& a_Old, vector<data>& a_New, uint a_uiStateId = 0xffffffff) = 0;
    void            rebuildAllDataCascade(reflection::Type* a_pOld, reflection::Type* a_pNew, vector<data>& a_Old, vector<data>& a_New, uint a_uiStateId = 0xffffffff);
    void            rebuildData(phantom::data& a_inOutData, reflection::Type* a_pOld, reflection::Type* a_pNewType, vector<data>& a_Old, vector<data>& a_New, uint a_uiStateId = 0xffffffff);

    void            clearDataReferenceCascade(const vector<void*>& a_OldLayout) const;
    virtual void    clearDataReference(const vector<void*>& a_OldLayout) const = 0;

    void            replaceDataReferenceCascade(const vector<void*>& a_OldLayout, const phantom::data& a_New) const;
    virtual bool    replaceDataReference(const vector<void*>& a_OldLayout, const phantom::data& a_New, bool a_SetIncompatibleToNull) const = 0;

    virtual const data& findData(void* a_pAddress) const = 0;

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

    virtual void    storeData(const data& a_Data) = 0;
    virtual void    eraseData(const data& a_Data) = 0;
    virtual void    storeData(const data& a_Data, size_t a_uiCount, size_t a_uiChunkSectionSize) = 0;
    virtual void    eraseData(const data& a_Data, size_t a_uiCount, size_t a_uiChunkSectionSize) = 0;

    void            storeNode(Node* a_pNode)
    {
        o_assert(NOT(containsNode(a_pNode)));
        o_assert(a_pNode->m_pOwnerDataBase == m_pOwnerDataBase);
        m_ChildNodes.push_back(a_pNode);
        a_pNode->m_pParentNode = this;
    }

    void            eraseNode(Node* a_pNode)
    {
        node_vector::iterator it = m_ChildNodes.begin();
        node_vector::iterator end = m_ChildNodes.end();
        for(;it!=end;++it)
        {
            if(*it == a_pNode)
                break;
        }
        o_assert(it != end);
        m_ChildNodes.erase(it);
        a_pNode->m_pParentNode = NULL;
    }

    void            destroyAllChildNode();

    void            registerData(const phantom::data& a_Data, uint guid);
    void            unregisterData(const phantom::data& a_Data);
    void            abortData( const phantom::data& a_Data );


    void            saveStateCascade(DataStateBase* a_pDataStateBase, uint a_uiStateId);
    void            loadStateCascade(DataStateBase* a_pDataStateBase, uint a_uiStateId);

protected:
    data_filter_delegate    m_data_filter_delegate;
    uint                    m_Guid;
    node_vector             m_ChildNodes;
    Node*                   m_pParentNode;
    DataBase*               m_pOwnerDataBase;
    EState                  m_eState;

};

o_h_end

#else
#include "Node.classdef.h"
#endif // serialization_TNode_h__
