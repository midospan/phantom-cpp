#ifndef o_phantom_serialization_SubDataManager_h__
#define o_phantom_serialization_SubDataManager_h__


/* ****************** Includes ******************* */

/* *********************************************** */
/* The *.classdef.h file must be the last #include */
#include "SubDataManager.classdef.h"
/* **************** Declarations ***************** */

/* *********************************************** */

o_h_begin

class o_export SubDataManager
{
    friend class DataBase;
    friend class Node;

    reflection_____________________________________________________________________
    _____________________________________________________________________reflection

public:
    /*struct data_class_interface 
    {
        data_class_interface()
            : subDataType(nullptr)
            , subDataAddingNotificationSignal(nullptr)
            , subDataRemovalNotificationSignal(nullptr)
            , subDataAddMethod(nullptr)
            , subDataRemoveMethod(nullptr)
            , subDataIteratorGetter(nullptr)
        {

        }

        data_class_interface(const string& a_strName
            , reflection::Type* a_subDataType
            , reflection::Signal* a_subDataAddingNotificationSignal
            , reflection::Signal*         a_subDataRemovalNotificationSignal
            , reflection::InstanceMethod* a_subDataAddMethod
            , reflection::InstanceMethod*         a_subDataRemoveMethod
            , reflection::InstanceMethod* a_subDataIteratorGetter);
        string                      name;
        reflection::Type*           subDataType;
        reflection::Signal*         subDataAddingNotificationSignal;
        reflection::Signal*         subDataRemovalNotificationSignal;
        reflection::InstanceMethod* subDataAddMethod;
        reflection::InstanceMethod* subDataRemoveMethod;
        reflection::InstanceMethod* subDataIteratorGetter;
    };*/

public:
    SubDataManager();

    /*void addSubDataInterface(const string& a_strName, reflection::Class* a_pClass
        , reflection::Type* a_pSubDataType
        , reflection::Signal* a_subDataAddingNotificationSignal
        , reflection::Signal* a_subDataRemovalNotificationSignal
        , reflection::InstanceMethod* a_subDataAddMethod
        , reflection::InstanceMethod* a_subDataRemoveMethod
        , reflection::InstanceMethod* a_subDataIteratorGetter);*/

    /*void removeAllSubDataInterfaceForClass(reflection::Class* a_pClass);*/
    /*
    void addSubDataInterface(const string& a_strName, const string& dataClassName
        , const string& subDataTypeName
        , const string& subDataAddingNotificationSignal
        , const string& subDataRemovalNotificationSignal
        , const string& subDataAddMethod
        , const string& subDataRemoveMethod
        , const string& subDataIteratorGetter);*/

protected:
    o_signal_data(subDataAdded, const phantom::data&, const phantom::data&)
    o_signal_data(subDataRemoved, const phantom::data&, const phantom::data&)

    void        addAllDataSubData(const data& a_Data, Node* a_pNode);
    void        addMissingDataSubData(const data& a_Data, Node* a_pNode);
    void        removeAllDataSubData(const data& a_Data, Node* a_pNode);
    void        abortAllDataSubData(const data& a_Data, Node* a_pNode);
    void        getAllDataSubData(const data& a_Data, vector<data>& out);

    void        addAllDataSubDataCascade(const data& a_Data, Node* a_pNode, reflection::Class* a_pClass);
    void        addMissingDataSubDataCascade(const data& a_Data, Node* a_pNode, reflection::Class* a_pClass);
    void        removeAllDataSubDataCascade(const data& a_Data, Node* a_pNode, reflection::Class* a_pClass);
    void        abortAllDataSubDataCascade(const data& a_Data, Node* a_pNode, reflection::Class* a_pClass);
    void        getAllDataSubDataCascade(const data& a_Data, Node* a_pNode, vector<data>& out, reflection::Class* a_pClass);
    /*
    void        addSubData(const phantom::data& ownerData, const data_class_interface& sdi, void* a_pData);
    void        removeSubData(const phantom::data& ownerData, const data_class_interface& sdi, void* a_pData);*/

protected:
    void        slotSubDataAdded(void* a_pSubData);
    void        slotSubDataRemoved(void* a_pSubData);
    void        registerSubData(void* a_pAddress, const phantom::data& ownerData, Node* a_pNode);

protected:
    void connectData(const data& a_Data);
    void connectDataCascade(const data& a_Data, reflection::Class* a_pClass);
    void disconnectData(const data& a_Data);
    void disconnectDataCascade(const data& a_Data, reflection::Class* a_pClass);

    void connectCollection(reflection::Collection* a_pCollection, const data& a_Data, bool connect);

protected:
    DataBase*                   m_pDataBase;
};

o_h_end

#else
#include "SubDataManager.classdef.h"
#endif
