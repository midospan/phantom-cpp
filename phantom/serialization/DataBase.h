/* TODO LICENCE HERE */

#ifndef serialization_DataBase_h__
#define serialization_DataBase_h__

/* ****************** Includes ******************* */

/* **************** Declarations ***************** */
o_declareN(class, (phantom, serialization), DataBase)
/* *********************************************** */

o_namespace_begin(phantom, serialization)

class DefaultNode;
class Record;

struct type_info
{
    type_info() : pointer(nullptr) {}
    type_info(string aname, reflection::Type* apointer) 
        : name(aname), pointer(apointer) {}
    bool isNull() const { return pointer == nullptr; }
    string name;
    reflection::Type* pointer;
};

typedef std::pair<type_info, type_info> type_info_pair;

struct runtime_type_info
{
    runtime_type_info() : refCount(0) {}
    runtime_type_info(string aname, reflection::Type* apointer) 
        : baseInfo(aname, apointer) , refCount(0) {}
    bool isNull() const { return baseInfo.isNull(); }
    type_info baseInfo;
    size_t refCount;
};

class o_export DataBase
{
    friend class Node;
    friend class DefaultNode;
    friend class Record;
    
protected:
    static bool ComponentExpressionFilter(reflection::Type* a_pType);

public:
    typedef map<string, string> placeholder_type_by_name_map;
    typedef map<uint, uint>     placeholder_type_by_id_map;

public:
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

    DataBase(const string& url, uint a_uiSerializationFlag = o_save_data);
    o_destructor ~DataBase(void);

    o_initialize();
    o_terminate();

    void    addData(const data& a_Data, Node* a_pNode, modifiers_t a_Modifiers = 0);

    void    addComponentData(const data& a_Data, const data& a_Owner, const string& a_ReferenceExpression, modifiers_t a_Modifiers = 0);

    void    removeData(const data& a_Data);

    bool    isDataUnloaded(uint guid);

    void    save();

    void    saveData(const data& a_Data);

    void    saveState(uint a_uiState);

    void    saveDataState(const data& a_Data, uint a_uiState);

    void    loadState(uint a_uiState);

    void    setDataStateBase(DataStateBase* a_pDataStateBase)
    {
        o_assert(m_pDataStateBase == NULL);
        m_pDataStateBase = a_pDataStateBase;
    }

    DataStateBase*  getDataStateBase() const { return m_pDataStateBase; }

    void            blockDataSlots() { o_assert(!m_bDataSlotsBlocked); m_bDataSlotsBlocked = true; }
    void            unblockDataSlots() { o_assert(m_bDataSlotsBlocked); m_bDataSlotsBlocked = false; }

    void            restoreData(uint guid);
    void            restoreNode(uint guid);

    virtual uint    createBackup() = 0;
    virtual void    destroyBackup(uint a_uiBackupId) = 0;

    virtual void    saveDataEntryBackup(uint a_uiBackupId, const phantom::data& a_Data, uint guid, Node* a_pNode) = 0;
    virtual void    saveNodeEntryBackup(uint a_uiBackupId, Node* a_pNode) = 0;
    virtual void    saveTypeBackup(uint a_uiBackupId, const string& a_strQualifiedName, const string& a_strModuleName) = 0;
    
    virtual void    restoreDataEntryBackup(uint a_uiBackupId, const phantom::data& a_Data, uint guid, Node* a_pNode) = 0;
    virtual void    restoreNodeEntryBackup(uint a_uiBackupId, Node* a_pNode) = 0;
    virtual void    restoreTypeBackup(uint a_uiBackupId, const string& a_strQualifiedName, const string& a_strModuleName) = 0;

    virtual void    swapTypeBackup(uint a_uiBackupId, const string& a_strQualifiedName, const string& a_strModuleName) = 0;
    virtual void    eraseTypeBackup(uint a_uiBackupId, const string& a_strQualifiedName, const string& a_strModuleName) = 0;
    virtual bool    hasTypeBackup(uint a_uiBackupId, const string& a_strQualifiedName, const string& a_strModuleName) const = 0;

    virtual void    clearDataReference(const phantom::data& a_data, vector<reflection::Expression*>* a_pRestoreReferenceExpressions = nullptr);

    virtual void    replaceDataReference(const phantom::data& a_old, const phantom::data& a_New);

    virtual boolean canMoveNode(Node* a_pNode, Node* a_pNewParent) const;
    virtual boolean canMoveData(const phantom::data& a_Data, Node* a_pNewParent) const;

    Node*           rootNode();

    Node*           getNode( const phantom::data& a_Data ) const
    {
        data_node_map::const_iterator found = m_DataNodeMap.find(getGuid(a_Data));
        return found == m_DataNodeMap.end() ? NULL : getNode(found->second);
    }

    Node*           getNode( uint a_uiGuid ) const;
    
    const phantom::data& getComponentDataOwner( const phantom::data& a_Data ) const;

    uint                getComponentDataOwnerGuid( uint a_ComponentGuid ) const;

    const string&   getComponentDataReferenceExpression( const phantom::data& a_Data ) const;
    void            setComponentDataReferenceExpression( const phantom::data& a_Data, const string& a_Expression );

	bool            isComponentDataOwner(const phantom::data& a_Data) const;

    uint            getGuid( Node* a_pNode ) const;
    uint            getGuid( const phantom::data& a_Data ) const;
    modifiers_t     getDataModifiers( const phantom::data& a_Data ) const;
    void            setDataModifiers( const phantom::data& a_Data, modifiers_t a_Modifiers);
    void            addDataModifiers( const phantom::data& a_Data, modifiers_t a_Modifiers);
    void            removeDataModifiers( const phantom::data& a_Data, modifiers_t a_Modifiers);
    void*           getDataAddress( uint guid ) const { return m_GuidBase.dataAddress(guid); }
    reflection::Type*getDataType( uint guid ) const { return m_GuidBase.dataType(guid); }
    const data&     getData( uint guid ) const { return m_GuidBase.getData(guid); }

    boolean         containsData(const phantom::data& a_Data) const { return m_GuidBase.getGuid(a_Data) != o_invalid_guid; }
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

    void            registerData( const phantom::data& a_Data, uint a_Guid, Node* a_pOwnerNode, modifiers_t modifiers );
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

    void            setDataPropertyValue(uint a_uiGuid, reflection::Property* a_pProperty, const variant& a_Value);

    void            setDataPropertyValue(const phantom::data& a_Data, reflection::Property* a_pProperty, const variant& a_Value);

    const variant&  getDataPropertyValue(const phantom::data& a_Data, reflection::Property* a_pProperty) const;

    const variant&  getDataPropertyValue(uint a_uiGuid, reflection::Property* a_pProperty) const;

    size_t          getAttributeCount() const { return m_AttributeNames.size(); }

    size_t          addAttribute(const string& a_name);

    size_t          getAttributeIndex(const string& a_name) const;

    const string&   getAttributeName(size_t attributeIndex) const;

    const string*   getAttributeValues( const phantom::data& a_Data ) const;

    const string*   getAttributeValues( Node* a_pNode ) const;

    size_t          getLoadedDataSize() const { return m_uiLoadedDataSize; }
    size_t          getLoadedDataResetSize() const { return m_uiLoadedDataResetSize; }
    size_t          getLoadedDataSerializedSize() const { return m_uiLoadedDataSerializedSize; }

    bool            isEmpty() const { return m_GuidBase.isEmpty(); }

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
    void            preRemoveData( const phantom::data& a_Data );
    Node*           internalAddNewNode(Node* a_pParentNode);
    Node*           internalAddNewNode(uint a_uiGuid, Node* a_pParentNode);
    void			internalAddNode(Node* a_pNode, uint a_uiGuid, Node* a_pParentNode);
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

    size_t          getRuntimeTypeReferenceCount(reflection::Type* a_pType) const;

    bool            hasRuntimeType(reflection::Type* a_pType) const;

    const runtime_type_info& getRuntimeTypeInfo( reflection::Type* a_pType ) const;

protected:
    void            removeComponentData( const phantom::data& a_Data );
    void            unloadData(const phantom::data& a_Data);
    void            reloadData();
    void            registerComponentData(const data& a_Data, const data& a_Owner, const string& a_ReferenceExpression);
    void            unregisterComponentData(const data& a_Data);

    void            incrementRuntimeTypeReferenceCount(reflection::Type* a_pType);
    void            decrementRuntimeTypeReferenceCount(reflection::Type* a_pType);

protected:
    void            moduleElementAdded(reflection::LanguageElement* a_pLanguageElement);
    void            moduleElementAboutToBeRemoved(reflection::LanguageElement* a_pLanguageElement);
    void            moduleElementsAboutToBeReplaced( const vector<reflection::LanguageElement*>& a_OldLanguageElements );
    void            moduleElementsReplaced(const vector<reflection::LanguageElement*>& a_OldLanguageElements, const vector<reflection::LanguageElement*>& a_NewLanguageElements);
    void            moduleLoaded(reflection::Module* a_pModule, size_t a_uiOldCount, size_t a_uiNewCount);
    void            moduleUnloaded( reflection::Module* a_pModule, size_t a_uiOldCount, size_t a_uiNewCount);

    virtual void    connectData( const phantom::data& a_Data, bool a_bCollectComponents = true );
    virtual void    disconnectData( const phantom::data& a_Data );

    void            componentChanged(void* a_pOldPointer, void* a_pNewPointer);
    void            componentInserted( size_t a_uiIndex, void* a_pComponent);
    void            componentAboutToBeRemoved( size_t, void* a_pComponent);
    void            componentReplaced( size_t, void* a_pOldComponent, void* a_pNewComponent);
    void            componentMoved( size_t a_uiOldIndex, size_t a_uiNewIndex, void* a_pComponent );
    void            componentSwapped( size_t a_uiOldIndex, size_t a_uiNewIndex, void* a_pComponent0, void* a_pComponent1 );

    void            aggregateInserted( size_t a_uiIndex, void* a_pAggregate );
    void            aggregateAboutToBeRemoved( size_t a_uiIndex, void* a_pAggregate );
    void            aggregateReplaced( size_t a_uiIndex, void* a_pOldAggregate, void* a_pNewAggregate );
    void            aggregateMoved( size_t a_uiOldIndex, size_t a_uiNewIndex, void* a_pAggregate );
    void            aggregateSwapped( size_t a_uiOldIndex, size_t a_uiNewIndex, void* a_pOldAggregate, void* a_pNewAggregate );

    void            propertyChanged();

protected:
    string          formatIndexExpression(size_t a_uiIndex);
    string          formatIndexedExpression(const string& a_strExpression, size_t a_uiIndex, const char chars[2]);
    void            slotNodeLoaded();
    void            slotNodeAboutToBeUnloaded();
    void            registerType(reflection::Type* a_pType);
    void            unregisterType(reflection::Type* a_pType);
    virtual void    createTypeEntry(reflection::Type* a_pType) = 0;
    virtual void    destroyTypeEntry(reflection::Type* a_pType) = 0;
    virtual void    saveType(reflection::Type* a_pType) = 0;
    virtual void    loadTypes(reflection::Module* a_pModule, vector<reflection::Type*>* a_pLoadedTypes = nullptr, const vector<string>* a_pTypeNames = nullptr) = 0;
    virtual bool    hasTypeEntry(const string& a_strQualifiedDecoratedName, const string& a_strModuleFileName) const = 0;

    void            registerPlaceholderTypeByName(const string& qualifiedName, const string& placeHolder);
    void            unregisterPlaceholderTypeByName(const string& qualifiedName);
    void            unregisterAllByPlaceholderTypeName(const string& placeholder);

    reflection::Type* getPlaceholderTypeByName(const string& qualifiedName) const;

    const string&   getPlaceholderTypeName(const string& qualifiedName) const;

    placeholder_type_by_name_map::const_iterator beginPlaceholderTypesByName() const { return m_PlaceholderTypeByNameMap.begin(); }
    placeholder_type_by_name_map::const_iterator endPlaceholderTypesByName() const { return m_PlaceholderTypeByNameMap.end(); }

    placeholder_type_by_id_map::const_iterator beginPlaceholderTypesById() const { return m_PlaceholderTypeByIdMap.begin(); }
    placeholder_type_by_id_map::const_iterator endPlaceholderTypesById() const { return m_PlaceholderTypeByIdMap.end(); }

    void savePlaceholderTypesByName( property_tree& a_Out );
    void loadPlaceholderTypesByName( const property_tree& a_In );
    void blockModuleSlots();
    void unblockModuleSlots();

    void addDataReferenceExpression( uint guid, const string& propertyAccessExpression );
    void removeDataReferenceExpression( uint guid, const string& propertyAccessExpression );
protected:
    o_signal_data(dataAboutToBeRemoved, const phantom::data&, Node*);
    o_signal_data(dataAdded, const phantom::data&, Node*);
    o_signal_data(dataAboutToBeDisconnected, const phantom::data&);
    o_signal_data(dataConnected, const phantom::data&);
    o_signal_data(dataAboutToBeReplaced, const phantom::data&, Node*);
    o_signal_data(dataReplaced, const phantom::data&, Node*);
    o_signal_data(dataAboutToBeUnloaded, const phantom::data&, Node*);
    o_signal_data(dataReloaded, const phantom::data&, Node*);
    o_signal_data(dataAboutToBeUnregistered, const phantom::data&);
    o_signal_data(dataRegistered, const phantom::data&);
    o_signal_data(dataAboutToBeAborted, const phantom::data&, Node*);
    o_signal_data(dataMoved, const phantom::data&, Node*, Node*);
    o_signal_data(dataAttributeValueChanged, const phantom::data&, size_t, const string&);
    o_signal_data(dataModifiersChanged, const phantom::data&, modifiers_t);
    o_signal_data(dataAggregationChanged, const phantom::data&, const string&, const string&);
    o_signal_data(dataCompositionChanged, const phantom::data&, const string&, const string&);
    o_signal_data(dataPropertyValueChanged, const phantom::data&, reflection::Property*, const variant&, const variant&);
    o_signal_data(componentOwnershipLost, const phantom::data&);

    o_signal_data(nodeAdded, Node*, Node*);
    o_signal_data(nodeAboutToBeRemoved, Node*, Node*);
    o_signal_data(nodeLoaded, Node*);
    o_signal_data(nodeAboutToBeUnloaded, Node*);
    o_signal_data(nodeMoved, Node*, Node*, Node*);
    o_signal_data(nodeAttributeValueChanged, Node*, size_t, const string&);
    o_signal_data(dataErased, uint);
    o_signal_data(dataRestored, uint);

    o_signal_data(componentReferenceExpressionChanged, const phantom::data&, const string&, const string&);

protected:
    typedef map<uint, uint>         data_node_map;

    typedef map<uint, string*>      attribute_map;
    typedef vector<string>          attribute_name_container;

    typedef map<uint, modifiers_t>     modifier_map;

    typedef map<uint, uint>         component_data_owner_map;
    typedef map<uint, string>       component_data_reference_expression_map;

    typedef map<uint,vector<string>>data_reference_expression_map;

    typedef map<uint, map<reflection::Property*, variant>> data_property_value_map;

    typedef map<uint, map<void*, vector<void*>>> data_aggregation_value_map;

    string                          m_strUrl;
    data_guid_base                  m_GuidBase;
    data_node_map                   m_DataNodeMap;
    component_data_owner_map        m_ComponentDataOwnerMap;
    component_data_reference_expression_map m_ComponentReferenceExpressionMap;
    attribute_map                   m_AttributeValues;
    attribute_name_container        m_AttributeNames;
    modifier_map                    m_DataModifiers;
    DataStateBase*                  m_pDataStateBase;
    EActionOnMissingType            m_eActionOnMissingType;
    size_t                          m_uiLoadedDataSize;
    size_t                          m_uiLoadedDataResetSize;
    size_t                          m_uiLoadedDataSerializedSize;
    uint                            m_uiSerializationFlag;
    data_property_value_map         m_PropertyValues;
    data_reference_expression_map   m_DataReferenceExpressions;
    data_reference_expression_map   m_DataReferenceExpressionsUnloadedToRestore;
    placeholder_type_by_name_map    m_PlaceholderTypeByNameMap;
    placeholder_type_by_id_map      m_PlaceholderTypeByIdMap;

    vector<runtime_type_info>       m_RuntimeTypes;
    vector<string>                  m_ReplacementOldTypeNames;
    struct node_pred
    {
        bool operator()(const Node* n0, const Node* n1) const;
    };
    map<Node*, vector<uint>, node_pred> m_UnloadedGuids;

    Record*                         m_pCurrentRecord;
    Record*                         m_pRedoRecord;
    Record*                         m_pUndoRecord;

    bool                            m_bDataSlotsBlocked;

private:
    mutable Node*                   m_pRootNode;
    bool                            m_bModuleSlotsBlocked;
};

o_namespace_end(phantom, serialization)

#endif
