/* TODO LICENCE HERE */

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include "Record.h"
#include "Record.hxx"
#include "DataBase.h"
#include "Node.h"
#include "phantom/reflection/PropertyExpression.h"
#include "phantom/reflection/Application.h"
#include <phantom/serialization/DataStateBase.h>
#include <phantom/reflection/CompositionClass.h>
/* *********************************************** */
o_registerN((phantom, serialization), Record);

o_namespace_begin(phantom, serialization)

Record::Record(DataBase* a_pDataBase)
    : m_pDataBase(a_pDataBase)
    , m_LastRemovedAddedGuid(o_invalid_guid)
    , m_LastRemovedRemovedGuid(o_invalid_guid)
    , m_LastAddedAddedGuid(o_invalid_guid)
    , m_LastAddedRemovedGuid(o_invalid_guid)
    , m_uiTypeBackupId(o_invalid_guid)
{
    m_uiBackupId = m_pDataBase->createBackup();
}

Record::Record( DataBase* a_pDataBase, uint a_uiBackupId )
    : m_pDataBase(a_pDataBase)
    , m_uiBackupId(a_uiBackupId)
    , m_LastRemovedAddedGuid(o_invalid_guid)
    , m_LastRemovedRemovedGuid(o_invalid_guid)
    , m_LastAddedAddedGuid(o_invalid_guid)
    , m_LastAddedRemovedGuid(o_invalid_guid)
    , m_uiTypeBackupId(o_invalid_guid)
{

}

Record::~Record()
{
    if(m_uiTypeBackupId != o_invalid_guid)
        m_pDataBase->destroyBackup(m_uiTypeBackupId);
}

void Record::startRecording()
{
    o_assert(m_Operations.empty());
    o_assert(m_pDataBase->m_pCurrentRecord == nullptr);
    m_pDataBase->m_pCurrentRecord = this;
}

void Record::stopRecording()
{
    o_assert(m_pDataBase->m_pCurrentRecord == this);
    m_pDataBase->m_pCurrentRecord = nullptr;
    save();
}

void Record::startUndo()
{
    o_assert(m_pDataBase->m_pUndoRecord == nullptr);
    o_assert(m_pDataBase->m_pRedoRecord == nullptr);
    m_pDataBase->m_pUndoRecord = this;
    m_DataReferenceExpressionsRemovedToRestore = m_DataReferenceExpressionsRemoved;
    m_DataReferenceExpressionsAddedToRemove = m_DataReferenceExpressionsAdded;
    m_RemovedDataGuidsToRestore = m_RemovedDataGuids;
    m_AddedDataGuidsToRemove = m_AddedDataGuids;
    m_BeginReplaceTypesToUndo = m_EndReplaceTypes;
    m_EndReplaceTypesToUndo = m_BeginReplaceTypes;
    m_AddedTypesToRemove = m_AddedTypes;
    m_RemovedTypesToRestore = m_RemovedTypes;
}

bool Record::stopUndo()
{
    o_assert(m_pDataBase->m_pUndoRecord == this);
    o_assert(m_pDataBase->m_pRedoRecord == nullptr);
    bool symetric = true;
    restore();
    //o_warning(m_RemovedComponentsToRestore.empty(), "Inconsistent property (Setting two times the same value produce two different results)");
    while(m_RemovedDataGuidsToRestore.size())
    {
        uint guid = m_RemovedDataGuidsToRestore.back();
        reflection::Type* pType = m_pDataBase->solveTypeByName(m_Types[guid]);
        o_assert(pType);
        void* pData = pType->newInstance();
        auto foundComponentReference = m_ComponentReferenceExpressions.find(guid);
        if(foundComponentReference != m_ComponentReferenceExpressions.end())
        {
            // Component
            reflection::Expression* pExpression = expressionByName("("+foundComponentReference->second+")=static_cast<"+pType->getQualifiedDecoratedName()+"*>("+lexical_cast<string>((size_t)pData)+")");
            if(pExpression)
            {
                pExpression->eval(); 
                restore();
                o_dynamic_delete (pExpression);
            }
            else m_RemovedDataGuidsToRestore.pop_back();
        }
        else 
        {
            // Orphan Data
            m_pDataBase->addData(pData, m_pDataBase->getNode(m_Parents[guid]), m_Modifiers[guid]);
            restore(); // Force individual restore to ensure connection
        }
        symetric = false;
    }
    while(m_RemovedTypesToRestore.size())
    {
        addType(m_RemovedTypesToRestore.back());
        symetric = false;
    }
    o_assert(m_BeginReplaceTypesToUndo.size() == m_EndReplaceTypesToUndo.size());
    while(m_BeginReplaceTypesToUndo.size())
    {
        beginReplaceTypes(m_BeginReplaceTypesToUndo.back());
        endReplaceTypes(m_EndReplaceTypesToUndo.back());
        o_assert(m_BeginReplaceTypesToUndo.size() == m_EndReplaceTypesToUndo.size());
        symetric = false;
    }
    while(m_DataReferenceExpressionsRemovedToRestore.size())
    {
        reflection::Expression* pExpression = expressionByName("("+m_DataReferenceExpressionsRemovedToRestore.back().second+")=(&@"+lexical_cast<string>(m_DataReferenceExpressionsRemovedToRestore.back().first)+")");
        if(pExpression)
        {
            pExpression->eval(); 
            o_dynamic_delete (pExpression);
        }
        else m_DataReferenceExpressionsRemovedToRestore.pop_back();
    }
    while(m_DataReferenceExpressionsAddedToRemove.size())
    {
        reflection::Expression* pExpression = expressionByName("("+m_DataReferenceExpressionsAddedToRemove.back().second+")=nullptr");
        if(pExpression)
        {
            pExpression->eval(); 
            o_dynamic_delete (pExpression);
        }
        else m_DataReferenceExpressionsAddedToRemove.pop_back();
    }
    while(m_AddedDataGuidsToRemove.size())
    {
        uint guid = m_AddedDataGuidsToRemove.back();
        auto foundComponentReference = m_ComponentReferenceExpressions.find(guid);
        if(foundComponentReference != m_ComponentReferenceExpressions.end())
        {
            // Component
            reflection::Expression* pExpression = expressionByName("("+foundComponentReference->second+")=nullptr");
            if(pExpression)
            {
                pExpression->eval(); // Execute either a property 'set' or a compostion 'insert' to restore the component
                o_dynamic_delete (pExpression);
            }
            else m_AddedDataGuidsToRemove.pop_back();
        }
        else 
        {
            auto d = m_pDataBase->getData(guid);
            m_pDataBase->getNode(d)->removeData(d);
        }
        symetric = false;
    }
    while(m_AddedTypesToRemove.size())
    {
        removeType(m_AddedTypesToRemove.back());
        symetric = false;
    }
    save();
    m_pDataBase->m_pUndoRecord = nullptr;
    m_LastAddedRemovedGuid = o_invalid_guid;
    m_LastRemovedAddedGuid = o_invalid_guid;
    return symetric;
}

void Record::startRedo()
{
    m_AddedDataGuidsToRestore = m_AddedDataGuids;
    m_RemovedDataGuidsToRemove = m_RemovedDataGuids;
    m_DataReferenceExpressionsAddedToRestore = m_DataReferenceExpressionsAdded;
    m_DataReferenceExpressionsRemovedToRemove = m_DataReferenceExpressionsRemoved;
    o_assert(m_pDataBase->m_pUndoRecord == nullptr);
    o_assert(m_pDataBase->m_pRedoRecord == nullptr);
    m_pDataBase->m_pRedoRecord = this;
    m_BeginReplaceTypesToRedo = m_BeginReplaceTypes;
    m_EndReplaceTypesToRedo = m_EndReplaceTypes;
    m_AddedTypesToRestore = m_AddedTypes;
    m_RemovedTypesToRemove = m_RemovedTypes;
}

bool Record::stopRedo()
{
    o_assert(m_pDataBase->m_pUndoRecord == nullptr);
    o_assert(m_pDataBase->m_pRedoRecord == this);
    restore();
    bool symetric = true;
    while(m_AddedDataGuidsToRestore.size())
    {
        uint guid = m_AddedDataGuidsToRestore.front();
        reflection::Type* pType = m_pDataBase->solveTypeByName(m_Types[guid]);
        o_assert(pType);
        void* pData = pType->newInstance();
        auto foundComponentReference = m_ComponentReferenceExpressions.find(guid);
        if(foundComponentReference != m_ComponentReferenceExpressions.end())
        {
            // Component
            reflection::Expression* pExpression = expressionByName("("+foundComponentReference->second+")=static_cast<"+pType->getQualifiedDecoratedName()+"*>("+lexical_cast<string>((size_t)pData)+")");
            if(pExpression)
            {
                pExpression->eval(); // Execute either a property 'set' or a compostion 'insert' to restore the component
                restore();
                o_dynamic_delete (pExpression);
            }
            else m_AddedDataGuidsToRestore.erase(m_AddedDataGuidsToRestore.begin());
        }
        else 
        {
            // Orphan Data
            m_pDataBase->addData(pData, m_pDataBase->getNode(m_Parents[guid]), m_Modifiers[guid]);
            restore(); // Force individual restore to ensure connection
        }
        symetric = false;
    }

    while(m_AddedTypesToRestore.size())
    {
        addType(m_AddedTypesToRestore.back());
        symetric = false;
    }
    o_assert(m_BeginReplaceTypesToUndo.size() == m_EndReplaceTypesToUndo.size());
    while(m_BeginReplaceTypesToUndo.size())
    {
        beginReplaceTypes(m_BeginReplaceTypesToRedo.back());
        endReplaceTypes(m_EndReplaceTypesToRedo.back());    
        o_assert(m_BeginReplaceTypesToUndo.size() == m_EndReplaceTypesToUndo.size());
        symetric = false;
    }
    while(m_DataReferenceExpressionsAddedToRestore.size())
    {
        reflection::Expression* pExpression = expressionByName("("+m_DataReferenceExpressionsAddedToRestore.front().second+")=(&@"+lexical_cast<string>(m_DataReferenceExpressionsAddedToRestore.front().first)+")");
        if(pExpression)
        {
            pExpression->eval(); 
            o_dynamic_delete (pExpression);
        }
        else m_DataReferenceExpressionsAddedToRestore.erase(m_DataReferenceExpressionsAddedToRestore.begin());
    }
    while(m_DataReferenceExpressionsRemovedToRemove.size())
    {
        reflection::Expression* pExpression = expressionByName("("+m_DataReferenceExpressionsRemovedToRemove.front().second+")=nullptr");
        if(pExpression)
        {
            pExpression->eval(); 
            o_dynamic_delete (pExpression);
        }
        else m_DataReferenceExpressionsRemovedToRemove.erase(m_DataReferenceExpressionsRemovedToRemove.begin());
    }
    while(m_RemovedDataGuidsToRemove.size())
    {
        uint guid = m_RemovedDataGuidsToRemove.front();
        auto foundComponentReference = m_ComponentReferenceExpressions.find(guid);
        if(foundComponentReference != m_ComponentReferenceExpressions.end())
        {
            // Component
            reflection::Expression* pExpression = expressionByName("("+foundComponentReference->second+")=nullptr");
            if(pExpression)
            {
                pExpression->eval(); // Execute either a property 'set' or a compostion 'insert' to restore the component
                o_dynamic_delete (pExpression);
            }
            else m_RemovedDataGuidsToRemove.erase(m_RemovedDataGuidsToRemove.begin());
        }
        else 
        {
            auto d = m_pDataBase->getData(guid);
            m_pDataBase->getNode(d)->removeData(d);
        }
        symetric = false;
    }
    while(m_RemovedTypesToRemove.size())
    {
        removeType(m_RemovedTypesToRemove.back());
        symetric = false;
    }
    m_pDataBase->m_pRedoRecord = nullptr;
    save();
    m_LastRemovedRemovedGuid = o_invalid_guid;
    m_LastAddedAddedGuid = o_invalid_guid;
    return symetric;
}

void Record::undo()
{
    if(isRecording())
    {
        o_exception(exception::base_exception, "Cannot undo/redo while recording");
    }
    if(!m_bDone)
    {
        o_exception(exception::base_exception, "Record already undone");
    }
    map<op, size_t> indexes;

    indexes[property_change]                        = m_PropertyDataMemberChanges.size();
    indexes[aggregation_change]                     = m_AggregationChanges.size();
    indexes[composition_change]                     = m_CompositionChanges.size();
    indexes[data_remove]                            = m_RemovedDataGuids.size();
    indexes[data_add]                               = m_AddedDataGuids.size();
    indexes[component_reference_expression_change]  = m_ComponentReferenceExpressionChanges.size();
    indexes[node_load]                              = m_LoadedNodes.size();
    indexes[node_unload]                            = m_UnloadedNodes.size();
    indexes[begin_replace_types]                    = m_BeginReplaceTypes.size();
    indexes[end_replace_types]                      = m_EndReplaceTypes.size();
    indexes[placeholder_type_name_registered]       = m_RegisteredPlaceholderTypeNames.size();
    indexes[add_type]                               = m_AddedTypes.size();
    indexes[remove_type]                            = m_RemovedTypes.size();

    for(auto it = m_Operations.rbegin(); it != m_Operations.rend(); ++it)
    {
        op op = *it;
        size_t& index = indexes[op];
        --index;
        switch(op)
        {
        case property_change:
            undoPropertyDataMemberChange(m_PropertyDataMemberChanges[index]);
            break;
        case aggregation_change:
            undoAggregationChange(m_AggregationChanges[index]);
            break;
        case composition_change:
            undoCompositionChange(m_CompositionChanges[index]);
            break;
        case data_remove:
            addData(m_RemovedDataGuids[index]);
            break;
        case data_add:
            removeData(m_AddedDataGuids[index]);
            break;
        case node_load:
            m_pDataBase->getNode(m_LoadedNodes[index])->unload();
            break;
        case node_unload:
            m_pDataBase->getNode(m_UnloadedNodes[index])->load();
            break;
        case component_reference_expression_change:
            undoComponentReferenceExpressionChange(m_ComponentReferenceExpressionChanges[index]);
            break;
        case begin_replace_types:
            beginReplaceTypes(m_BeginReplaceTypes[index]);
            break;
        case end_replace_types:
            endReplaceTypes(m_EndReplaceTypes[index]);
            break;
        case add_type:
            removeType(m_AddedTypes[index]);
            break;
        case remove_type:
            addType(m_RemovedTypes[index]);
            break;
        case placeholder_type_name_registered:
            string_string& pair = m_RegisteredPlaceholderTypeNames[index];
            m_pDataBase->unregisterPlaceholderTypeByName(pair.first);
            break;
        }
    }
    o_assert(0 == indexes[property_change]);
    o_assert(0 == indexes[aggregation_change]);
    o_assert(0 == indexes[data_remove]);
    o_assert(0 == indexes[data_add]);
    o_assert(0 == indexes[node_load]);
    o_assert(0 == indexes[node_unload]);
    o_assert(0 == indexes[component_reference_expression_change]);
    o_assert(0 == indexes[begin_replace_types]);
    o_assert(0 == indexes[end_replace_types]);
    o_assert(0 == indexes[placeholder_type_name_registered]);
    o_assert(0 == indexes[add_type]);
    o_assert(0 == indexes[remove_type]);
    restoreAddedData();
    m_bDone = false;
}

void Record::redo()
{
    if(isRecording())
    {
        o_exception(exception::base_exception, "Cannot undo/redo while recording");
    }
    if(m_bDone)
    {
        o_exception(exception::base_exception, "Record already (re)done");
    }
    map<op, size_t> indexes;
    indexes[property_change] = 0;
    indexes[aggregation_change] = 0;
    indexes[data_remove] = 0;
    indexes[data_add] = 0;
    indexes[node_load] = 0;
    indexes[node_unload] = 0;
    indexes[component_reference_expression_change] = 0;
    indexes[begin_replace_types] = 0;
    indexes[end_replace_types] = 0;
    indexes[placeholder_type_name_registered] = 0;
    indexes[add_type] = 0;
    indexes[remove_type] = 0;
    for(auto it = m_Operations.begin(); it != m_Operations.end(); ++it)
    {
        op op = *it;
        size_t& index = indexes[op];
        switch(op)
        {
        case property_change:
            redoPropertyDataMemberChange(m_PropertyDataMemberChanges[index]);
            break;
        case aggregation_change:
            redoAggregationChange(m_AggregationChanges[index]);
            break;
        case composition_change:
            redoCompositionChange(m_CompositionChanges[index]);
            break;
        case data_remove:
            removeData(m_RemovedDataGuids[index]);
            break;
        case data_add:
            addData(m_AddedDataGuids[index]);
            break;
        case node_load:
            m_pDataBase->getNode(m_LoadedNodes[index])->load();
            break;
        case node_unload:
            m_pDataBase->getNode(m_UnloadedNodes[index])->unload();
            break;
        case component_reference_expression_change:
            redoComponentReferenceExpressionChange(m_ComponentReferenceExpressionChanges[index]);
            break;
        case begin_replace_types:
            beginReplaceTypes(m_BeginReplaceTypes[index]);
            break;
        case end_replace_types:
            endReplaceTypes(m_EndReplaceTypes[index]);
            break;
        case add_type:
            addType(m_AddedTypes[index]);
            break;
        case remove_type:
            removeType(m_AddedTypes[index]);
            break;
        case placeholder_type_name_registered:
            string_string& pair = m_RegisteredPlaceholderTypeNames[index];
            m_pDataBase->registerPlaceholderTypeByName(pair.first, pair.second);
            break;
        }
        index++;
    }   
    o_assert(m_PropertyDataMemberChanges.size() == indexes[property_change]);
    o_assert(m_AggregationChanges.size() == indexes[aggregation_change]);
    o_assert(m_CompositionChanges.size() == indexes[composition_change]);
    o_assert(m_RemovedDataGuids.size() == indexes[data_remove]);
    o_assert(m_AddedDataGuids.size() == indexes[data_add]);
    o_assert(m_LoadedNodes.size() == indexes[node_load]);
    o_assert(m_UnloadedNodes.size() == indexes[node_unload]);
    o_assert(m_ComponentReferenceExpressionChanges.size() == indexes[component_reference_expression_change]);
    o_assert(m_BeginReplaceTypes.size() == indexes[begin_replace_types]);
    o_assert(m_EndReplaceTypes.size() == indexes[end_replace_types]);
    o_assert(m_RegisteredPlaceholderTypeNames.size() == indexes[placeholder_type_name_registered]);
    o_assert(m_AddedTypes.size() == indexes[add_type]);
    o_assert(m_RemovedTypes.size() == indexes[remove_type]);
    restoreAddedData();
    m_bDone = true;
    save();
}

void Record::addData(uint guid)
{
    string typeName = get(m_Types, guid);
    reflection::Type* pType = m_pDataBase->solveTypeByName(typeName);
    o_assert(pType);
    void* pData = pType->allocate();
    phantom::data d(pData, pType);
    uint ownerGuid = get(m_Parents, guid);
    Node* pNode = m_pDataBase->getNode(ownerGuid);
    phantom::data ownerData;
    if(pNode == nullptr)
    {
        ownerData = m_pDataBase->getData(ownerGuid);
        o_assert(!ownerData.isNull());
        pNode = m_pDataBase->getNode(ownerData);
        o_assert(pNode);
    }
    const string& expression = get(m_ComponentReferenceExpressions, guid);
    modifiers_t modifiers = get(m_Modifiers, guid);
    pNode->storeData(d);
    m_pDataBase->restoreDataEntryBackup(m_uiBackupId, d, guid, pNode);
    m_pDataBase->registerData(d, guid, pNode, modifiers);
    if(!ownerData.isNull())
    {
        m_pDataBase->registerComponentData(d, ownerData, expression);
    }

    for(size_t i = 0; i<m_pDataBase->getAttributeCount(); ++i)
    {
        m_pDataBase->setDataAttributeValue(d, i, get(m_Attributes, guid)[i]);
    }
    vector<phantom::data> datas;
    datas.push_back(d);
    pNode->build(datas);
    pNode->deserialize(m_pDataBase->m_uiSerializationFlag, datas);
//     const vector<string>& restoreExpressions = get(m_ReferenceExpressions, guid);
//     for(auto it = restoreExpressions.begin(); it != restoreExpressions.end(); ++it)
//     {
//         phantom::setCurrentDataBase(m_pDataBase);
//         reflection::Expression* pExpression = phantom::expressionByName(*it);
//         o_assert(pExpression);
//         pExpression->setSignalBlockedCascade(true);
//         pExpression->eval();
//     }
    m_DataToRestore[pNode].push_back(d);
}

void Record::restoreAddedData()
{
    // Restore
    for(auto it = m_DataToRestore.begin(); it != m_DataToRestore.end(); ++it)
    {
        Node* pNode = it->first;
        auto& dataList = it->second;

        pNode->restore(m_pDataBase->m_uiSerializationFlag, dataList);

        for(auto it = dataList.begin(); it != dataList.end(); ++it)
        {
            auto d = *it;
            o_emit m_pDataBase->dataAdded(d, pNode);

            if(m_pDataBase->getDataStateBase())
            {
                pNode->loadDataState(d, m_pDataBase->getDataStateBase()->getCurrentStateId());
            }
            m_pDataBase->connectData(d);
        }
    }
}

void Record::removeData(uint guid)
{
    vector<uint> guids;
    guids.push_back(guid);
    phantom::data d = m_pDataBase->getData(guid);
    o_assert(NOT(d.isNull()), "Guid is not used in the data base, neither for node or data");
    Node* pParentNode = m_pDataBase->getNode(d);
    m_pDataBase->disconnectData(d);
    m_pDataBase->destroyDataEntry(d, guid, pParentNode);
    o_emit m_pDataBase->dataAboutToBeRemoved(d, pParentNode);
    phantom::data owner = m_pDataBase->getComponentDataOwner(d);
    uint ownerGuid = m_pDataBase->getGuid(owner);
    if(!owner.isNull())
    {
        m_pDataBase->unregisterComponentData(d);
        // Remove component from its owner memory
//         reflection::Expression* pExpression = phantom::expressionByName(get(m_ComponentReferenceExpressions, guid));
//         o_assert(pExpression);
//         phantom::data castedData = d.cast(pExpression->getValueType()->removeConstReference()->removePointer());
//         void* pAddress = nullptr;
//         pExpression->setSignalBlockedCascade(true);
//         pExpression->store(&pAddress);
//         o_dynamic_delete (pExpression);
    }
    m_pDataBase->unregisterData(d);
    pParentNode->eraseData(d);
}

void Record::undoComponentReferenceExpressionChange(const uint_string_string& info)
{
    m_pDataBase->setComponentDataReferenceExpression(m_pDataBase->getData(info.first), info.second.first);
}

void Record::redoComponentReferenceExpressionChange(const uint_string_string& info)
{
    m_pDataBase->setComponentDataReferenceExpression(m_pDataBase->getData(info.first), info.second.second);
}

void Record::undoAggregationChange(const string_string& info)
{
    reflection::Expression* pExpression = phantom::expressionByName(info.first);
    // ensure aggregation notification signals are blocked to avoid change propagation 
    // (it is the responsability of the record to restore all that changed previously)
    pExpression->setSignalBlockedCascade(true); 
    pExpression->eval();
    o_dynamic_delete (pExpression);
}

void Record::redoAggregationChange(const string_string& info)
{
    reflection::Expression* pExpression = phantom::expressionByName(info.second);
    // ensure aggregation notification signals are blocked to avoid change propagation 
    // (it is the responsability of the record to restore all that changed previously)
    pExpression->setSignalBlockedCascade(true); 
    pExpression->eval();
    o_dynamic_delete (pExpression);
}

void Record::undoCompositionChange(const string_string& info)
{
    reflection::Expression* pExpression = phantom::expressionByName(info.first);
    // ensure aggregation notification signals are blocked to avoid change propagation 
    // (it is the responsability of the record to restore all that changed previously)
    pExpression->setSignalBlockedCascade(true); 
    pExpression->eval();
    o_dynamic_delete (pExpression);
}

void Record::redoCompositionChange(const string_string& info)
{
    reflection::Expression* pExpression = phantom::expressionByName(info.second);
    // ensure aggregation notification signals are blocked to avoid change propagation 
    // (it is the responsability of the record to restore all that changed previously)
    pExpression->setSignalBlockedCascade(true); 
    pExpression->eval();
    o_dynamic_delete (pExpression);
}

void Record::undoPropertyDataMemberChange( const uint_string_variant_variant& info )
{
    phantom::data d = m_pDataBase->getData(info.first);
    o_assert(!d.isNull());
    string_variant_variant svv = info.second;
    reflection::Expression* pExpression = expressionByName(svv.first);
    reflection::Property* pProperty = pExpression->getHatchedElement()->asProperty();
    o_assert(pProperty);
    variant oldValue = loadVariant(pProperty, svv.second.first);
    pExpression->store(oldValue.buffer());
    m_pDataBase->setDataPropertyValue(d, pProperty, oldValue);
    o_dynamic_delete (pExpression);
}

void Record::redoPropertyDataMemberChange( const uint_string_variant_variant& info )
{
    phantom::data d = m_pDataBase->getData(info.first);
    o_assert(!d.isNull());
    string_variant_variant svv = info.second;
    reflection::Expression* pExpression = expressionByName(svv.first);
    reflection::Property* pProperty = pExpression->getHatchedElement()->asProperty();
    o_assert(pProperty);
    variant newValue = loadVariant(pProperty, svv.second.second);
    pExpression->store(newValue.buffer());
    m_pDataBase->setDataPropertyValue(d, pProperty, newValue);
    o_dynamic_delete (pExpression);
}

variant Record::saveVariant(reflection::Property* a_pProperty, const variant& a_Value)
{
    if(a_pProperty->getEffectiveValueType()->getDataPointerLevel() == 1)
    {
        uint guid = m_pDataBase->getGuid(a_Value.as<void*>());
        if(guid == o_invalid_guid)
        {
            return a_Value;
        }
        else 
        {
            return guid;
        }
    }
    else 
    {
        return a_Value;
    }
}

variant Record::loadVariant(reflection::Property* a_pProperty, const variant& a_Value)
{
    if(a_pProperty->getEffectiveValueType()->getDataPointerLevel() == 1)
    {
        if(a_Value.type()->getDataPointerLevel() == 1)
        {
            return a_Value;
        }
        else 
        {
            o_assert(a_Value.type() == typeOf<uint>());
            uint guid = a_Value.as<uint>();
            auto d = m_pDataBase->getData(guid);
            variant result;
            result.setType(a_pProperty->getEffectiveValueType());
            void* pCasted = d.type()->cast(a_pProperty->getEffectiveValueType()->removePointer(), d.address());
            memcpy(result.buffer(), &pCasted, sizeof(void*));
            return result;
        }
    }
    else 
    {
        return a_Value;
    }
}

void Record::dataPropertyValueChanged( const phantom::data& d, reflection::Property* a_pProperty, const variant& a_OldValue, const variant& a_NewValue )
{
//     m_PropertyDataMemberChanges.push_back(
//         uint_string_variant_variant(
//         m_pDataBase->getGuid(d), 
//         string_variant_variant("(@"+lexical_cast<string>(m_pDataBase->getGuid(d))+")."+a_pProperty->getName(), variant_variant(saveVariant(a_pProperty, a_OldValue), saveVariant(a_pProperty, a_NewValue)))
//         )
//         );
//     m_Operations.push_back(property_change);
    m_SavedDataGuids.insert(m_pDataBase->getGuid(d));
}

void Record::dataAdded( const phantom::data& d, serialization::Node* a_pNode )
{
    uint guid = m_pDataBase->getGuid(d);
    m_SavedDataGuids.insert(guid);
    m_SavedNodeGuids.insert(a_pNode->getGuid());
    o_assert(std::find(m_AddedDataGuids.begin(), m_AddedDataGuids.end(), guid) == m_AddedDataGuids.end());
    o_assert(std::find(m_RemovedDataGuids.begin(), m_RemovedDataGuids.end(), guid) == m_RemovedDataGuids.end());
    m_Operations.push_back(data_add);
    remember(d, guid);
    if(m_pDataBase->m_pUndoRecord == this) // undoing
    {
        auto insertionPoint = std::find(m_AddedDataGuids.begin(), m_AddedDataGuids.end(), m_LastAddedRemovedGuid);
        m_AddedDataGuids.insert(insertionPoint, guid); // Insert before the last restored removed guid
        m_LastAddedRemovedGuid = guid;
    }
    else if(m_pDataBase->m_pRedoRecord == this) // redoing
    {
        auto insertionPoint = std::find(m_AddedDataGuids.begin(), m_AddedDataGuids.end(), m_LastAddedAddedGuid);
        if(insertionPoint == m_AddedDataGuids.end())
            m_AddedDataGuids.insert(m_AddedDataGuids.begin(), guid); // If no guid found, insert at the beginning
        else 
            m_AddedDataGuids.insert(++insertionPoint, guid); // Insert after the last restored added guid
        m_LastAddedAddedGuid = guid;
    } 
    else m_AddedDataGuids.push_back(guid);
    m_pDataBase->saveDataEntryBackup(m_uiBackupId, d, guid, a_pNode);
}

void Record::dataAboutToBeRemoved( const phantom::data& d, serialization::Node* a_pNode )
{
    uint guid = m_pDataBase->getGuid(d);
    m_SavedDataGuids.insert(guid);
    m_SavedNodeGuids.insert(a_pNode->getGuid());
    o_assert(std::find(m_AddedDataGuids.begin(), m_AddedDataGuids.end(), guid) == m_AddedDataGuids.end());
    o_assert(std::find(m_RemovedDataGuids.begin(), m_RemovedDataGuids.end(), guid) == m_RemovedDataGuids.end());

    remember(d, guid);
    if(m_pDataBase->m_pUndoRecord == this) // undoing
    {
        auto insertionPoint = std::find(m_RemovedDataGuids.begin(), m_RemovedDataGuids.end(), m_LastRemovedAddedGuid);
        m_RemovedDataGuids.insert(insertionPoint, guid); // insert before the last restored (on undo we must do things in reverse order)
        m_LastRemovedAddedGuid = guid;
    }
    else if(m_pDataBase->m_pRedoRecord == this)
    {
        auto insertionPoint = std::find(m_RemovedDataGuids.begin(), m_RemovedDataGuids.end(), m_LastRemovedRemovedGuid);
        if(insertionPoint == m_RemovedDataGuids.end())
            m_RemovedDataGuids.insert(m_RemovedDataGuids.begin(), guid); // If no guid found, insert at the beginning
        else 
            m_RemovedDataGuids.insert(++insertionPoint, guid); // insert after the last restored (on undo we must do things in normal order)
        m_LastRemovedRemovedGuid = guid;
    }
    else m_RemovedDataGuids.push_back(guid);
    
    m_Operations.push_back(data_remove);
    m_pDataBase->saveDataEntryBackup(m_uiBackupId, d, guid, a_pNode);
}

void Record::dataConnected( const phantom::data& d )
{
    // Once the data is connected, we save its entry
    uint guid = m_pDataBase->getGuid(d);
    if(std::find(m_AddedDataGuids.begin(), m_AddedDataGuids.end(), guid) != m_AddedDataGuids.end())
    {
        m_pDataBase->saveData(d);
        m_pDataBase->saveDataEntryBackup(m_uiBackupId, d, guid, m_pDataBase->getNode(d));
    }
}

bool Record::isRecording() const
{
    return m_pDataBase->m_pCurrentRecord == this;
}

void Record::remember( const phantom::data &d, uint guid )
{
    phantom::data owner = m_pDataBase->getComponentDataOwner(d);
    uint ownerGuid = m_pDataBase->getGuid(owner);
    if(owner.isNull())
    {
        set(m_Parents, guid, m_pDataBase->getNode(d)->getGuid());
    }
    else
    {
        set(m_ComponentReferenceExpressions, guid, m_pDataBase->getComponentDataReferenceExpression(d));
        set(m_Parents, guid, m_pDataBase->getGuid(owner));
    }
    set(m_Modifiers, guid, m_pDataBase->getDataModifiers(d));
    set(m_Types, guid, d.type()->getQualifiedDecoratedName());
    const string* strings = m_pDataBase->getAttributeValues(d.address()); 
    o_assert(m_Attributes.find(guid) == m_Attributes.end());
    for(size_t i = 0; i<m_pDataBase->getAttributeCount(); ++i)
    {
        m_Attributes[guid].push_back(strings[i]);
    }
}

void Record::dataAggregationChanged( const phantom::data& d, const string& a_OldValue, const string& a_NewValue )
{
    m_AggregationChanges.push_back(string_string(a_OldValue, a_NewValue));
    m_Operations.push_back(aggregation_change);
    m_SavedDataGuids.insert(m_pDataBase->getGuid(d));
}

void Record::dataCompositionChanged( const phantom::data& d, const string& a_OldValue, const string& a_NewValue )
{
    m_CompositionChanges.push_back(string_string(a_OldValue, a_NewValue));
    m_Operations.push_back(composition_change);
    m_SavedDataGuids.insert(m_pDataBase->getGuid(d));
}

void Record::componentReferenceExpressionChanged( const phantom::data& d, const string& a_OldValue, const string& a_NewValue )
{
    // m_ComponentReferenceExpressions[m_pDataBase->getGuid(d)] = a_NewValue;
}

void Record::nodeLoaded( serialization::Node* a_pNode )
{
    m_LoadedNodes.push_back(a_pNode->getGuid());
    m_Operations.push_back(node_load);
}

void Record::nodeAboutToBeUnloaded( serialization::Node* a_pNode )
{
    m_UnloadedNodes.push_back(a_pNode->getGuid());
    m_Operations.push_back(node_unload);
}

void Record::save()
{
    for(auto it = m_SavedDataGuids.begin(); it != m_SavedDataGuids.end(); ++it)
    {
        auto d = m_pDataBase->getData(*it);
        if(!d.isNull())
        {
            m_pDataBase->saveData(d);
        }
    }
    for(auto it = m_SavedNodeGuids.begin(); it != m_SavedNodeGuids.end(); ++it)
    {
        auto pNode = m_pDataBase->getNode(*it);
        if(pNode)
        {
            pNode->saveIndex();
        }
    }
}

void Record::dataAboutToBeDisconnected( const phantom::data& d )
{

}

void Record::dataAboutToBeUnregistered( const phantom::data& d )
{

}

void Record::dataRegistered( const phantom::data& d )
{

}

void Record::dataAboutToBeUnloaded( const phantom::data&, serialization::Node* )
{

}

void Record::dataReloaded( const phantom::data&, serialization::Node* )
{

}

void Record::typesAboutToBeReplaced( reflection::Module* a_pModule, const vector<reflection::Type*>& a_Types )
{
    string moduleName = a_pModule ? a_pModule->getFileName() : "";
    if(m_pDataBase->m_pCurrentRecord == this)
    {
        m_BeginReplaceTypes.push_back(string_vector_string(moduleName, vector<string>()));
        for(auto it = a_Types.begin(); it != a_Types.end(); ++it)
        {
            m_BeginReplaceTypes.back().second.push_back((*it)->getQualifiedDecoratedName());
            m_pDataBase->saveTypeBackup(typeBackupId(), (*it)->getQualifiedDecoratedName(), moduleName);
        }
        m_Operations.push_back(begin_replace_types);
    }
    else if(m_pDataBase->m_pUndoRecord == this)
    {
        size_t typesReplaced = a_Types.size();
        for(auto it = m_BeginReplaceTypesToUndo.begin(); it != m_BeginReplaceTypesToUndo.end(); )
        {
            if(it->first == moduleName)
            {
                auto& vec = it->second;
                for(auto it2 = a_Types.begin(); it2 != a_Types.end(); ++it2)
                {
                    auto found = std::find(vec.begin(), vec.end(), (*it2)->getQualifiedDecoratedName());
                    if(found != vec.end())
                    {
                        typesReplaced--;
                        vec.erase(found);
                    }
                }
                if(vec.empty())
                {
                    it = m_BeginReplaceTypesToUndo.erase(it);
                    continue;
                }
            }
            ++it;
        }
        o_assert(typesReplaced == 0, "Type restore inconsistency not handled");
    }
    else if(m_pDataBase->m_pRedoRecord == this)
    {
        size_t typesReplaced = a_Types.size();
        for(auto it = m_BeginReplaceTypesToRedo.begin(); it != m_BeginReplaceTypesToRedo.end();)
        {
            if(it->first == moduleName)
            {
                auto& vec = it->second;
                for(auto it2 = a_Types.begin(); it2 != a_Types.end(); ++it2)
                {
                    auto found = std::find(vec.begin(), vec.end(), (*it2)->getQualifiedDecoratedName());
                    if(found != vec.end())
                    {
                        typesReplaced--;
                        vec.erase(found);
                    }
                }
                if(vec.empty())
                {
                    it = m_BeginReplaceTypesToRedo.erase(it);
                    continue;
                }
            }
            ++it;
        }
        o_assert(typesReplaced == 0, "Type restore inconsistency not handled");
    }
}

void Record::typesReplaced( reflection::Module* a_pModule, const vector<reflection::Type*>& a_Types )
{
    string moduleName = a_pModule ? a_pModule->getFileName() : "";
    if(m_pDataBase->m_pCurrentRecord == this)
    {
        m_EndReplaceTypes.push_back(string_vector_string(moduleName, vector<string>()));
        for(auto it = a_Types.begin(); it != a_Types.end(); ++it)
        {
            m_EndReplaceTypes.back().second.push_back((*it)->getQualifiedDecoratedName());
        }
        m_Operations.push_back(end_replace_types);
    }
    else if(m_pDataBase->m_pUndoRecord == this)
    {
        size_t typesReplaced = a_Types.size();
        for(auto it = m_EndReplaceTypesToUndo.begin(); it != m_EndReplaceTypesToUndo.end(); )
        {
            if(it->first == moduleName)
            {
                auto& vec = it->second;
                for(auto it2 = a_Types.begin(); it2 != a_Types.end(); ++it2)
                {
                    auto found = std::find(vec.begin(), vec.end(), (*it2)->getQualifiedDecoratedName());
                    if(found != vec.end())
                    {
                        typesReplaced--;
                        vec.erase(found);
                    }
                }
                if(vec.empty())
                {
                    it = m_EndReplaceTypesToUndo.erase(it);
                    continue;
                }
            }
            ++it;
        }
        o_assert(typesReplaced == 0, "Type restore inconsistency not handled");
    }
    else if(m_pDataBase->m_pRedoRecord == this)
    {
        size_t typesReplaced = a_Types.size();
        for(auto it = m_EndReplaceTypesToRedo.begin(); it != m_EndReplaceTypesToRedo.end(); )
        {
            if(it->first == moduleName)
            {
                auto& vec = it->second;
                for(auto it2 = a_Types.begin(); it2 != a_Types.end(); ++it2)
                {
                    auto found = std::find(vec.begin(), vec.end(), (*it2)->getQualifiedDecoratedName());
                    if(found != vec.end())
                    {
                        typesReplaced--;
                        vec.erase(found);
                    }
                }
                if(vec.empty())
                {
                    it = m_EndReplaceTypesToRedo.erase(it);
                    continue;
                }
            }
            ++it;
        }
        o_assert(typesReplaced == 0, "Type restore inconsistency not handled");
    }
}

void Record::typeAboutToBeRemoved( reflection::Type* a_pType )
{
    string moduleName = a_pType->getModule() ? a_pType->getModule()->getFileName() : "";
    string_string pair = string_string(a_pType->getQualifiedDecoratedName(), moduleName);
    if(m_pDataBase->m_pCurrentRecord == this)
    {
        m_pDataBase->saveTypeBackup(typeBackupId(), a_pType->getQualifiedDecoratedName(), moduleName);
        m_RemovedTypes.push_back(pair);
        m_Operations.push_back(remove_type);
    }
    else if(m_pDataBase->m_pUndoRecord == this)
    {
        auto found = std::find(m_AddedTypesToRemove.begin(), m_AddedTypesToRemove.end(), pair);
        if(found != m_AddedTypesToRemove.end())
        {
            m_AddedTypesToRemove.erase(found);
        }
        else 
        {
            o_assert(false);
        }
    }
    else if(m_pDataBase->m_pRedoRecord == this)
    {
        auto found = std::find(m_RemovedTypesToRemove.begin(), m_RemovedTypesToRemove.end(), pair);
        if(found != m_RemovedTypesToRemove.end())
        {
            m_RemovedTypesToRemove.erase(found);
        }
        else 
        {
            o_assert(false);
        }
    }
}

void Record::typeAdded( reflection::Type* a_pType )
{
    string moduleName = a_pType->getModule() ? a_pType->getModule()->getFileName() : "";
    string_string pair = string_string(a_pType->getQualifiedDecoratedName(), moduleName);
    if(m_pDataBase->m_pCurrentRecord == this)
    {
        m_AddedTypes.push_back(pair);
        m_Operations.push_back(add_type);
    }
    else if(m_pDataBase->m_pUndoRecord == this)
    {
        auto found = std::find(m_RemovedTypesToRestore.begin(), m_RemovedTypesToRestore.end(), pair);
        if(found != m_RemovedTypesToRestore.end())
        {
            m_RemovedTypesToRestore.erase(found);
        }
        else 
        {
            o_assert(false);
        }
    }
    else if(m_pDataBase->m_pRedoRecord == this)
    {
        auto found = std::find(m_AddedTypesToRestore.begin(), m_AddedTypesToRestore.end(), pair);
        if(found != m_AddedTypesToRestore.end())
        {
            m_AddedTypesToRestore.erase(found);
        }
        else 
        {
            o_assert(false);
        }
    }
}

void Record::placeholderTypeByNameRegistered( const string& a_strQualifiedDecoratedName, const string& a_strPlaceHolderName )
{
    m_RegisteredPlaceholderTypeNames.push_back(string_string(a_strQualifiedDecoratedName, a_strPlaceHolderName));
    m_Operations.push_back(placeholder_type_name_registered);
}

void Record::beginReplaceTypes( string_vector_string& module_names )
{
    vector<reflection::LanguageElement*> m_LanguageElements;
    string moduleName = module_names.first;
    for(auto it = module_names.second.begin(); it != module_names.second.end(); ++it)
    {
        if(m_pDataBase->hasTypeBackup(typeBackupId(), *it, moduleName)) 
        {
            // A backup we the same name already exists, types replaced had the same qualified name, we need to swap to keep every backup
            m_pDataBase->swapTypeBackup(typeBackupId(), *it, moduleName);
        }
        else 
        {
            // Types replaced have different qualified names, we just save the backup
            m_pDataBase->saveTypeBackup(typeBackupId(), *it, moduleName);
        }
        reflection::Type* pType = typeByName(*it);
        o_assert(pType);
        m_LanguageElements.push_back(pType);
    }

    application()->beginReplaceElements(m_LanguageElements);
}

void Record::endReplaceTypes( string_vector_string& module_names )
{
    string moduleName = module_names.first;
    for(auto it = module_names.second.begin(); it != module_names.second.end(); ++it)
    {
        if(m_pDataBase->hasTypeEntry(moduleName, *it))
        {
            // If we already have the type entry, it means we proceed to a swap in the begin_replace pass
            // We just need to register the type
        }
        else 
        {
            m_pDataBase->restoreTypeBackup(typeBackupId(), *it, moduleName);
        }
    }
    vector<reflection::Type*> types;
    reflection::Module* pModule = moduleByFileName(moduleName);
    m_pDataBase->loadTypes(pModule, &types, &module_names.second);
    vector<reflection::LanguageElement*> elements(types.begin(), types.end());
    application()->endReplaceElements(elements);
}

void Record::addType( string_string& pair )
{
    reflection::Module* pModule = moduleByFileName(pair.second);
    m_pDataBase->restoreTypeBackup(typeBackupId(), pair.first, pair.second);
    vector<string> pairs;
    pairs.push_back(pair.first);
    vector<reflection::Type*> types;
    m_pDataBase->loadTypes(pModule, &types, &pairs);
    o_assert(types.size() == 1);
    o_assert_no_implementation();
    //pModule->addType(types.back());
}

void Record::removeType( string_string& pair )
{
    m_pDataBase->saveTypeBackup(typeBackupId(), pair.first, pair.second);
    reflection::Type* pType = typeByName(pair.first);
    reflection::Module* pModule = moduleByFileName(pair.second);
    o_assert_no_implementation();
    //pModule->removeElement(pType);
}

uint Record::restoreAddedComponentGuid( const string& a_ReferenceExpression )
{
    for(auto it = m_ComponentReferenceExpressions.begin(); it != m_ComponentReferenceExpressions.end(); ++it)
    {
        if(it->second == a_ReferenceExpression)
        {
            uint guid = it->first;
            auto found = std::find(m_AddedDataGuidsToRestore.begin(), m_AddedDataGuidsToRestore.end(), guid);
            if(found != m_AddedDataGuidsToRestore.end())
            {
                m_AddedDataGuidsToRestore.erase(found);
                m_LastAddedAddedGuid = guid;
                return guid;
            }
            return o_invalid_guid;
        }
    }
    o_warning(false, "Inconsistent property (Setting two times the same value produce two different results)");
    return o_invalid_guid;
}

uint Record::restoreRemovedComponentGuid( const string& a_ReferenceExpression )
{
    for(auto it = m_ComponentReferenceExpressions.begin(); it != m_ComponentReferenceExpressions.end(); ++it)
    {
        if(it->second == a_ReferenceExpression)
        {
            uint guid = it->first;
            auto found = std::find(m_RemovedDataGuidsToRestore.begin(), m_RemovedDataGuidsToRestore.end(), guid);
            if(found != m_RemovedDataGuidsToRestore.end())
            {
                m_RemovedDataGuidsToRestore.erase(found);
                m_LastAddedRemovedGuid = guid;
                return guid;
            }
            return o_invalid_guid;
        }
    }
    o_warning(false, "Inconsistent property (Setting two times the same value produce two different results)");
    return o_invalid_guid;
}

void Record::restoreRemovedComponent( const data& a_Data, uint a_Guid, Node* a_pNode )
{
    restoreRemovedData(a_Data, a_Guid, a_pNode);
}

// 
// uint Record::restoreAddedDataGuid()
// {
//     size_t index = m_AddedComponentIndex++;
//     o_assert(m_AddedDatas[index].second == "");
//     return m_AddedDatas[index].first;
// }
// 
// uint Record::restoreRemovedData( const data& a_Data, Node* a_pNode )
// {
//     size_t index = --m_RemovedComponentIndex;
//     o_assert(m_RemovedDatas[index].second == "");
//     uint guid = m_RemovedDatas[index].first;
//     m_pDataBase->restoreDataEntryBackup(m_uiBackupId, a_Data, guid, a_pNode);
//     a_Data.type()->terminate(a_Data.address()); // Terminate to cancel initialize
//     a_Data.type()->uninstall(a_Data.address()); // Uninstall to ensure disconnections
//     a_Data.type()->install(a_Data.address()); // Reinstall
//     a_pNode->deserializeOne(a_Data, m_pDataBase->m_uiSerializationFlag);
//     restore_state result;
//     restore_pass pass = 0;
//     while((result = a_Data.type()->restore(a_Data.address(), m_pDataBase->m_uiSerializationFlag, pass++)) == restore_incomplete);
// }

void Record::dataReferenceExpressionAdded( uint guid, const string& expression )
{
    if(m_pDataBase->m_pCurrentRecord == this)
    {
        m_DataReferenceExpressionsAdded.push_back(uint_string(guid, expression));
    }
    else if(m_pDataBase->m_pUndoRecord == this)
    {
        // A data reference has been registered while undoing, we check if it is one we had to restore
        // If so, we remove it from the restore queue (it has been automatically restored, we don't need to do it again)
        for(auto it = m_DataReferenceExpressionsRemovedToRestore.begin(); it != m_DataReferenceExpressionsRemovedToRestore.end(); ++it)
        {
            if(it->first == guid AND it->second == expression)
            {
                m_DataReferenceExpressionsRemovedToRestore.erase(it);
                break;
            }
        }
    }
    else if(m_pDataBase->m_pRedoRecord)
    {
        for(auto it = m_DataReferenceExpressionsAddedToRestore.begin(); it != m_DataReferenceExpressionsAddedToRestore.end(); ++it)
        {
            if(it->first == guid AND it->second == expression)
            {
                m_DataReferenceExpressionsAddedToRestore.erase(it);
                break;
            }
        }
    }
}

void Record::dataReferenceExpressionAboutToBeRemoved( uint guid, const string& expression )
{
    if(m_pDataBase->m_pCurrentRecord == this)
    {
        m_DataReferenceExpressionsRemoved.push_back(uint_string(guid, expression));
    }
    else if(m_pDataBase->m_pUndoRecord == this)
    {
        // A data reference has been registered while undoing, we check if it is one we had to restore
        // If so, we remove it from the restore queue (it has been automatically restored, we don't need to do it again)
        for(auto it = m_DataReferenceExpressionsAddedToRemove.begin(); it != m_DataReferenceExpressionsAddedToRemove.end(); ++it)
        {
            if(it->first == guid AND it->second == expression)
            {
                m_DataReferenceExpressionsAddedToRemove.erase(it);
                break;
            }
        }
    }
    else if(m_pDataBase->m_pRedoRecord)
    {
        for(auto it = m_DataReferenceExpressionsRemovedToRemove.begin(); it != m_DataReferenceExpressionsRemovedToRemove.end(); ++it)
        {
            if(it->first == guid AND it->second == expression)
            {
                m_DataReferenceExpressionsRemovedToRemove.erase(it);
                break;
            }
        }
    }
}

uint Record::restoreAddedDataGuid( reflection::Type* a_pType )
{
    for(auto it = m_AddedDataGuidsToRestore.begin(); it != m_AddedDataGuidsToRestore.end(); ++it)
    {
        if(m_ComponentReferenceExpressions.find(*it) == m_ComponentReferenceExpressions.end()) // not a component
        {
            o_assert(m_pDataBase->solveTypeByName(m_Types[*it]) == a_pType);
            uint guid = *it;
            m_AddedDataGuidsToRestore.erase(it);
            m_LastAddedAddedGuid = guid;
            return guid;
        }
    }
    o_assert(false);
    return o_invalid_guid;
}

uint Record::restoreRemovedDataGuid( reflection::Type* a_pType )
{
    for(auto it = m_RemovedDataGuidsToRestore.rbegin(); it != m_RemovedDataGuidsToRestore.rend(); ++it)
    {
        if(m_ComponentReferenceExpressions.find(*it) == m_ComponentReferenceExpressions.end()) // not a component
        {
            o_assert(m_pDataBase->solveTypeByName(m_Types[*it]) == a_pType);
            uint guid = *it;
            m_RemovedDataGuidsToRestore.erase(std::next(it).base());
            m_LastAddedRemovedGuid = guid;
            return guid;
        }
    }
    o_assert(false);
    return o_invalid_guid;
}

void Record::restoreRemovedData( const phantom::data& a_Data, uint guid, Node* a_pNode )
{
    a_Data.type()->terminate(a_Data.address()); // Terminate to cancel initialize
    a_Data.type()->uninstall(a_Data.address()); // Uninstall to ensure disconnections
    a_Data.type()->install(a_Data.address()); // Reinstall
    a_pNode->deserializeOne(a_Data, m_pDataBase->m_uiSerializationFlag);
    m_DataToRestore[a_pNode].push_back(a_Data);
    for(size_t i = 0; i<m_pDataBase->getAttributeCount(); ++i)
    {
        m_pDataBase->setDataAttributeValue(a_Data, i, get(m_Attributes, guid)[i]);
    }
}

void Record::restore()
{
    for(auto it = m_DataToRestore.begin(); it != m_DataToRestore.end(); ++it)
    {
        Node* pNode = it->first;
        auto& dataList = it->second;

        pNode->restore(m_pDataBase->m_uiSerializationFlag, dataList, restore_pass_local);

        for(auto it = dataList.begin(); it != dataList.end(); ++it)
        {
            auto d = *it;
            o_emit m_pDataBase->dataAdded(d, pNode);

            if(m_pDataBase->getDataStateBase())
            {
                pNode->loadDataState(d, m_pDataBase->getDataStateBase()->getCurrentStateId());
            }
            m_pDataBase->connectData(d);
        }
    }
    m_DataToRestore.clear();
}

bool Record::removeAddedGuid( uint a_Guid )
{
    // During Undo
    auto found = std::find(m_AddedDataGuidsToRemove.begin(), m_AddedDataGuidsToRemove.end(), a_Guid);
    if(found == m_AddedDataGuidsToRemove.end()) return false;
    m_LastRemovedAddedGuid = a_Guid;
    m_AddedDataGuidsToRemove.erase(found);
    return true;
}

bool Record::removeRemovedGuid( uint a_Guid )
{
    // During Redo
    auto found = std::find(m_RemovedDataGuidsToRemove.begin(), m_RemovedDataGuidsToRemove.end(), a_Guid);
    if(found == m_RemovedDataGuidsToRemove.end()) return false;
    m_LastRemovedRemovedGuid = a_Guid;
    m_RemovedDataGuidsToRemove.erase(found);
    return true;
}

uint Record::typeBackupId()
{
    if(m_uiTypeBackupId == o_invalid_guid)
    {
        m_uiTypeBackupId = m_pDataBase->createBackup();
    }
    return m_uiTypeBackupId;
}

bool Record::node_pred::operator()( const Node* n0, const Node* n1 ) const
{
    return n0->getLevel() < n1->getLevel();
}

o_namespace_end(phantom, serialization)
