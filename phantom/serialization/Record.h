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

#ifndef serialization_Record_h__
#define serialization_Record_h__

/* ****************** Includes ******************* */
/* **************** Declarations ***************** */
o_declareN(class, (phantom, serialization), Record);
/* *********************************************** */

o_namespace_begin(phantom, serialization)


class o_export Record
{
    friend class DataBase;

protected:

    enum op
    {
        property_change,
        aggregation_change,
        composition_change,
        component_reference_expression_change,
        data_add,
        data_remove,
        node_load,
        node_unload,
        add_type,
        remove_type,
        begin_replace_types,
        end_replace_types,
        placeholder_type_name_registered,
    };

    typedef std::pair<uint, string_string_string> uint_string_string_string; 
    typedef std::pair<variant, variant> variant_variant;
    typedef std::pair<string, variant_variant> string_variant_variant;
    typedef std::pair<uint, string_variant_variant> uint_string_variant_variant; 
    typedef std::pair<uint, string_string> uint_string_string; 
    typedef std::pair<string, vector<string>> string_vector_string;
    typedef std::pair<uint, vector<string>> uint_vector_string;
    typedef std::pair<uint, string> uint_string;

public:
    Record(DataBase* a_pDataBase);
    Record(DataBase* a_pDataBase, uint a_uiBackupId);

public:
    o_destructor ~Record();

    void begin();
    void end();

    void startRecording();
    void stopRecording();
    void undo();

    void startUndo();
    bool stopUndo();

    void startRedo();
    bool stopRedo();

    void addType( string_string& pair );

    void removeType( string_string& pair );

    void redo();

    void beginReplaceTypes( string_vector_string& module_names );
    void endReplaceTypes( string_vector_string& module_names );

    bool isRecording() const;


protected:
    template<typename t_Value>
    const t_Value& get(const map<uint, t_Value>& a_Map, uint guid)
    {
        auto found = a_Map.find(guid);
        o_assert(found != a_Map.end());
        return found->second;
    }

    template<typename t_Value>
    void set(map<uint, t_Value>& a_Map, uint guid, const t_Value& a_Value)
    {
        auto found = a_Map.find(guid);
        o_assert(found == a_Map.end());
        a_Map[guid] = a_Value;
    }
//     void beginReplaceData(const vector<uint>& guids);
//     void endReplaceData(const vector<uint>& guids);

protected:
    void dataAdded(const phantom::data&, serialization::Node*);
    void dataConnected( const phantom::data& d );
    void dataRegistered( const phantom::data& d );
    void dataAboutToBeDisconnected( const phantom::data& d );
    void dataAboutToBeUnregistered( const phantom::data& d );
    void dataAboutToBeRemoved(const phantom::data&, serialization::Node*);
    void dataAboutToBeUnloaded(const phantom::data&, serialization::Node*);
    void dataReloaded(const phantom::data&, serialization::Node*);
    void typesAboutToBeReplaced(Module* a_pModule, const vector<reflection::Type*>& a_Types);
    void typesReplaced(Module* a_pModule, const vector<reflection::Type*>& a_Types);
    void typeAboutToBeRemoved(reflection::Type* a_pType);
    void typeAdded(reflection::Type* a_pType);
    void placeholderTypeByNameRegistered(const string& PlaceholderTypeByName, const string& a_strPlaceHolderName);
    void nodeLoaded(serialization::Node*);
    void nodeAboutToBeUnloaded(serialization::Node*);
    void dataPropertyValueChanged( const phantom::data& d, reflection::Property* a_pProperty, const variant& a_OldValue, const variant& a_NewValue );
    void dataAggregationChanged( const phantom::data& d, const string& a_OldValue, const string& a_NewValue );
    void dataCompositionChanged( const phantom::data& d, const string& a_OldValue, const string& a_NewValue );
    void componentReferenceExpressionChanged( const phantom::data& d, const string& a_OldValue, const string& a_NewValue );

    void remember( const phantom::data &d, uint guid );
    
    void undoPropertyDataMemberChange( const uint_string_variant_variant& info );
    void redoPropertyDataMemberChange( const uint_string_variant_variant& info );

    void addData(uint guid);
    void removeData(uint guid);
    
    void undoComponentReferenceExpressionChange(const uint_string_string& info);
    void redoComponentReferenceExpressionChange(const uint_string_string& info);
    
    void undoAggregationChange(const string_string& info);
    void redoAggregationChange(const string_string& info);

    void undoCompositionChange(const string_string& info);
    void redoCompositionChange(const string_string& info);

    void restoreAddedData();
    void save();

    variant saveVariant(reflection::Property* a_pProperty, const variant& a_Value);
    variant loadVariant(reflection::Property* a_pProperty, const variant& a_Value);

    uint restoreAddedDataGuid(reflection::Type* a_pType);
    uint restoreRemovedDataGuid(reflection::Type* a_pType);

    void restoreRemovedData( const phantom::data& a_Data, uint guid, Node* a_pNode );
    void restoreRemovedComponent(const data& a_Data, uint a_Guid, Node* a_pNode);
    uint restoreAddedComponentGuid(const string& a_ReferenceExpression);
    uint restoreRemovedComponentGuid(const string& a_ReferenceExpression);

    bool removeAddedGuid(uint a_Guid);

    bool removeRemovedGuid(uint a_Guid);

    void dataReferenceExpressionAdded(uint guid, const string& expression);
    void dataReferenceExpressionAboutToBeRemoved(uint guid, const string& expression);

protected:
    void restore();
    uint typeBackupId();

protected:
    struct node_pred
    {
        bool operator()(const Node* n0, const Node* n1) const;
    };
    DataBase*                           m_pDataBase;
    map<uint, vector<string>>           m_Attributes;
    map<uint, string>                   m_Types;
    map<uint, bool>                     m_Nodes;
    map<uint, uint>                     m_Parents;
    map<uint, string>                   m_ComponentReferenceExpressions;
    vector<uint_string>                 m_DataReferenceExpressionsAdded;
    vector<uint_string>                 m_DataReferenceExpressionsAddedToRestore;
    vector<uint_string>                 m_DataReferenceExpressionsAddedToRemove;
    vector<uint_string>                 m_DataReferenceExpressionsRemoved;
    vector<uint_string>                 m_DataReferenceExpressionsRemovedToRestore;
    vector<uint_string>                 m_DataReferenceExpressionsRemovedToRemove;
    map<uint, modifiers_t>                 m_Modifiers;
    map<uint, vector<string>>           m_ReferenceExpressions;
    map<Node*, vector<data>, node_pred> m_DataToRestore;
    vector<op>                          m_Operations;
    vector<uint>                        m_RemovedDataGuids;
    vector<uint>                        m_RemovedDataGuidsToRestore;
    vector<uint>                        m_RemovedDataGuidsToRemove;
    vector<uint>                        m_AddedDataGuids;
    vector<uint>                        m_AddedDataGuidsToRemove;
    vector<uint>                        m_AddedDataGuidsToRestore;
    vector<uint>                        m_UnloadedDataGuids;
    vector<uint>                        m_UnloadedDataGuidsToRemove;
    vector<uint>                        m_UnloadedDataGuidsToRestore;
    vector<uint>                        m_ReloadedDataGuids;
    vector<uint>                        m_ReloadedDataGuidsToRemove;
    vector<uint>                        m_ReloadedDataGuidsToRestore;
    vector<uint_string_variant_variant> m_PropertyDataMemberChanges;
    vector<string_string>               m_AggregationChanges;
    vector<string_string>               m_CompositionChanges;
    vector<string_string>               m_AddedTypes;
    vector<string_string>               m_RemovedTypes;
    vector<string_string>               m_AddedTypesToRemove;
    vector<string_string>               m_RemovedTypesToRemove;
    vector<string_string>               m_AddedTypesToRestore;
    vector<string_string>               m_RemovedTypesToRestore;
    vector<string_string>               m_RegisteredPlaceholderTypeNames;
    vector<string_vector_string>        m_BeginReplaceTypes;
    vector<string_vector_string>        m_EndReplaceTypes;
    vector<string_vector_string>        m_BeginReplaceTypesToUndo;
    vector<string_vector_string>        m_EndReplaceTypesToUndo;
    vector<string_vector_string>        m_BeginReplaceTypesToRedo;
    vector<string_vector_string>        m_EndReplaceTypesToRedo;
    vector<uint_string_string>          m_ComponentReferenceExpressionChanges;
    vector<uint>                        m_LoadedNodes;
    vector<uint>                        m_UnloadedNodes;
    uint                                m_uiBackupId;
    uint                                m_uiTypeBackupId;
    std::set<uint>                      m_SavedDataGuids;
    std::set<uint>                      m_SavedNodeGuids;
    uint                                m_LastRemovedAddedGuid;
    uint                                m_LastRemovedRemovedGuid;
    uint                                m_LastAddedAddedGuid;
    uint                                m_LastAddedRemovedGuid;
    uint                                m_LastRemovedReloadedGuid;
    uint                                m_LastRemovedUnloadedGuid;
    uint                                m_LastAddedReloadedGuid;
    uint                                m_LastAddedUnloadedGuid;
    bool                                m_bDone;

};

o_namespace_end(phantom, serialization)

#endif // serialization_Record_h__
