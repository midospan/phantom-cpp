/* ******************* Includes ****************** */
#include "phantom/phantom.h"
/* ** The Class Header must be the last #include * */
#include "SubDataManager.h"
/* *********************************************** */
o_cpp_begin

ReflectionCPP__________________________________________________________________________________
    o_slot(void, slotSubDataAdded, (void*))
    o_slot(void, slotSubDataRemoved, (void*))
    o_signal(subDataAdded, (const phantom::data&, const phantom::data&))
    o_signal(subDataRemoved, (const phantom::data&, const phantom::data&))
__________________________________________________________________________________ReflectionCPP


SubDataManager::SubDataManager() : m_pDataBase(NULL)
{

}
/*
SubDataManager::data_class_interface::data_class_interface( const string& a_strName
, reflection::Type* a_subDataType
, reflection::Signal* a_subDataAddingNotificationSignal
, reflection::Signal* a_subDataRemovalNotificationSignal
, reflection::InstanceMethod* a_subDataAddMethod
, reflection::InstanceMethod*         a_subDataRemoveMethod
, reflection::InstanceMethod* a_subDataIteratorGetter ) 
: subDataAddingNotificationSignal(a_subDataAddingNotificationSignal)
, subDataRemovalNotificationSignal(a_subDataRemovalNotificationSignal)
, subDataAddMethod(a_subDataAddMethod)
, subDataRemoveMethod(a_subDataRemoveMethod)
, subDataIteratorGetter(a_subDataIteratorGetter)
, subDataType(a_subDataType)
, name(a_strName)
{
    o_assert((a_subDataIteratorGetter != NULL) AND (a_subDataAddingNotificationSignal != NULL) AND (a_subDataRemovalNotificationSignal != NULL));
    o_assert(a_subDataRemovalNotificationSignal->getSignature()->getParameterCount() == 1);
    o_assert(a_subDataRemovalNotificationSignal->getSignature()->getParameterType(0)->getDataPointerLevel() == 1);
    o_assert(static_cast<reflection::DataPointerType*>(a_subDataRemovalNotificationSignal->getSignature()->getParameterType(0))->getPointedType() == a_subDataType);
    o_assert(a_subDataRemovalNotificationSignal->getSignature()->equals(a_subDataAddingNotificationSignal->getSignature()));
    o_assert(phantom::canConnect(subDataAddingNotificationSignal, phantom::typeOf<SubDataManager>()->getInstanceMethodCascade ("slotSubDataAdded(void*)")));
    o_assert(phantom::canConnect(subDataRemovalNotificationSignal,phantom::typeOf<SubDataManager>()->getInstanceMethodCascade("slotSubDataRemoved(void*)")));
    o_assert((a_subDataIteratorGetter->getReturnType() == typeOf<util::Iterator*>()));
}
*/

void SubDataManager::connectCollection( reflection::Collection* a_pCollection, const data& a_Data, bool connect )
{
    static reflection::InstanceMethod*  s_pAddSlot      = phantom::typeOf<SubDataManager>()->getInstanceMethodCascade ("slotSubDataAdded(void*)");
    static reflection::InstanceMethod*  s_pRemoveSlot   = phantom::typeOf<SubDataManager>()->getInstanceMethodCascade ("slotSubDataRemoved(void*)");
    if(connect)
    {
        //std::cout<<"connect address:"<<a_Data.address()<<" signal:"<<interf.subDataAddingNotificationSignal<<std::endl;
        a_pCollection->connect(a_Data.address(), this, s_pAddSlot, s_pRemoveSlot);
    }
    else
    {
        //std::cout<<"disconnect address:"<<a_Data.address()<<" signal:"<<interf.subDataAddingNotificationSignal<<std::endl;
        a_pCollection->disconnect(a_Data.address(), this, s_pAddSlot, s_pRemoveSlot);
    }
}
/*

void SubDataManager::addSubDataInterface( const string& a_strName
    , reflection::Class* a_pClass 
    , reflection::Type* a_pSubDataType 
    , reflection::Signal* a_subDataAddingNotificationSignal 
    , reflection::Signal* a_subDataRemovalNotificationSignal 
    , reflection::InstanceMethod* a_subDataAddMethod
    , reflection::InstanceMethod* a_subDataRemoveMethod
    , reflection::InstanceMethod* a_subDataIteratorGetter )
{
    o_assert(a_pClass == a_subDataAddingNotificationSignal->getOwner());
    o_assert(a_pClass == a_subDataRemovalNotificationSignal->getOwner());
    o_assert(a_pClass == a_subDataIteratorGetter->getOwner());

    data_class_interface dci(a_strName, a_pSubDataType
        , a_subDataAddingNotificationSignal
        , a_subDataRemovalNotificationSignal
        , a_subDataAddMethod
        , a_subDataRemoveMethod
        , a_subDataIteratorGetter);
    m_DataClassInterfaces[a_pClass].push_back(dci);
}

void SubDataManager::addSubDataInterface( const string& a_strName
    , const string& dataClassName 
    , const string& subDataTypeName 
    , const string& subDataAddingNotificationSignal 
    , const string& subDataRemovalNotificationSignal 
    , const string& subDataAddMethod
    , const string& subDataRemoveMethod
    , const string& subDataIteratorGetter )
{
    reflection::Type* pDataType = phantom::typeByName(dataClassName);
    reflection::Type* pSubDataType = phantom::typeByName(subDataTypeName);
    o_assert(pSubDataType AND pDataType AND pDataType->isClass());
    reflection::Class* pDataClass = static_cast<reflection::Class*>(pDataType);
    data_class_interface dci(
        a_strName
        , pSubDataType
        , pDataClass->getSignalCascade(subDataAddingNotificationSignal)
        , pDataClass->getSignalCascade(subDataRemovalNotificationSignal)
        , pDataClass->getInstanceMethodCascade(subDataAddMethod)
        , pDataClass->getInstanceMethodCascade(subDataRemoveMethod)
        , pDataClass->getInstanceMethodCascade(subDataIteratorGetter));
    m_DataClassInterfaces[pDataClass].push_back(dci);
}
*/

void SubDataManager::addAllDataSubDataCascade( const data& a_Data, Node* a_pNode, reflection::Class* a_pClass )
{
    vector<reflection::Collection*> collections;
    a_pClass->getAllCollectionCascade(collections);
    auto it = collections.begin();
    auto end = collections.end();
    for(;it!=end;++it)
    {
        if(NOT((*it)->isComponent())) continue; 
        util::Iterator*   pIterator = (*it)->getIterator(a_Data.cast((*it)->getOwner()->asClass()).address());
        o_assert(pIterator != NULL);
        void* subData = NULL;
        while(pIterator->hasNext())
        {
            pIterator->next(&subData); // get the subdata pointer
            registerSubData(subData, a_Data, a_pNode);
        }
        o_dynamic_delete pIterator;
    }
}

void SubDataManager::addAllDataSubData( const data& a_Data, Node* a_pNode )
{
    reflection::Class* pDataClass = a_Data.type()->asClass();
    o_assert(pDataClass, "Sub data type must be a class");
    // We switch to a recursive and layout-safe method
    addAllDataSubDataCascade(a_Data, a_pNode, pDataClass);
}

void SubDataManager::addMissingDataSubDataCascade( const data& a_Data, Node* a_pNode, reflection::Class* a_pClass )
{
    vector<reflection::Collection*> collections;
    a_pClass->getAllCollectionCascade(collections);
    auto it = collections.begin();
    auto end = collections.end();
    for(;it!=end;++it)
    {
        if(NOT((*it)->isComponent())) continue; 
        util::Iterator*   pIterator = (*it)->getIterator(a_Data.cast((*it)->getOwner()->asClass()).address());
        o_assert(pIterator != NULL);
        void* subData = NULL;
        while(pIterator->hasNext())
        {
            pIterator->next(&subData); // get the subdata pointer
            if(NOT(m_pDataBase->containsData(subData)))
            {
                registerSubData(subData, a_Data, a_pNode);
            }
        }
        o_dynamic_delete pIterator;
    }
}

void SubDataManager::addMissingDataSubData( const data& a_Data, Node* a_pNode )
{
    reflection::Class* pDataClass = a_Data.type()->asClass();
    o_assert(pDataClass, "Sub data type must be a class");
    // We switch to a recursive and layout-safe method
    addMissingDataSubDataCascade(a_Data, a_pNode, pDataClass);
}

void SubDataManager::removeAllDataSubDataCascade( const data& a_Data, Node* a_pNode, reflection::Class* a_pClass )
{
    vector<reflection::Collection*> collections;
    a_pClass->getAllCollectionCascade(collections);
    auto it = collections.begin();
    auto end = collections.end();
    for(;it!=end;++it)
    {
        if(NOT((*it)->isComponent())) continue; 
        util::Iterator*   pIterator = (*it)->getIterator(a_Data.cast((*it)->getOwner()->asClass()).address());
        o_assert(pIterator != NULL);
        void* subData = NULL;
        while(pIterator->hasNext())
        {
            pIterator->next(&subData); // get the subdata pointer
            a_pNode->removeData(subData);
        }
        o_dynamic_delete pIterator;
    }
}

void SubDataManager::removeAllDataSubData( const data& a_Data, Node* a_pNode )
{
    reflection::Class* pDataClass = a_Data.type()->asClass();
    o_assert(pDataClass, "Sub data type must be a class");
    // We switch to a recursive and layout-safe method
    removeAllDataSubDataCascade(a_Data, a_pNode, pDataClass);
}

void SubDataManager::abortAllDataSubDataCascade( const data& a_Data, Node* a_pNode, reflection::Class* a_pClass )
{
    vector<reflection::Collection*> collections;
    a_pClass->getAllCollectionCascade(collections);
    auto it = collections.begin();
    auto end = collections.end();
    for(;it!=end;++it)
    {
        if(NOT((*it)->isComponent())) continue; 
        util::Iterator*   pIterator = (*it)->getIterator(a_Data.cast((*it)->getOwner()->asClass()).address());
        o_assert(pIterator != NULL);
        void* subData = NULL;
        while(pIterator->hasNext())
        {
            pIterator->next(&subData); // get the subdata pointer
            a_pNode->abortData(subData);
        }
        o_dynamic_delete pIterator;
    }
}

void SubDataManager::abortAllDataSubData( const data& a_Data, Node* a_pNode )
{
    reflection::Class* pDataClass = a_Data.type()->asClass();
    o_assert(pDataClass, "Sub data type must be a class");
    // We switch to a recursive and layout-safe method
    abortAllDataSubDataCascade(a_Data, a_pNode, pDataClass);
}

void SubDataManager::getAllDataSubDataCascade( const data& a_Data, Node* a_pNode, vector<data>& out, reflection::Class* a_pClass )
{
    vector<reflection::Collection*> collections;
    a_pClass->getAllCollectionCascade(collections);
    auto it = collections.begin();
    auto end = collections.end();
    for(;it!=end;++it)
    {
        if(NOT((*it)->isComponent())) continue; 
        util::Iterator*   pIterator = (*it)->getIterator(a_Data.cast((*it)->getOwner()->asClass()).address());
        o_assert(pIterator != NULL);
        void* subData = NULL;
        while(pIterator->hasNext())
        {
            pIterator->next(&subData); // get the subdata pointer
            data d = a_pNode->findData(subData);
            o_assert(d.address());
            out.push_back(d);
        }
        o_dynamic_delete pIterator;
    }
}

void SubDataManager::getAllDataSubData( const data& a_Data, vector<data>& out )
{
    reflection::Class* pDataClass = a_Data.type()->asClass();
    o_assert(pDataClass, "Sub data type must be a class");
    // We switch to a recursive and layout-safe method
    Node* pNode = m_pDataBase->getNode(a_Data);
    o_assert(pNode);
    getAllDataSubDataCascade(a_Data, pNode, out, pDataClass);
    
}

void SubDataManager::slotSubDataAdded( void* a_pSubData )
{
    o_assert(m_pDataBase);
    // The sender is the owner
    void* ownerDataAddress = phantom::connection::sender();
    Node* pParentNode = m_pDataBase->getNode(ownerDataAddress);
    o_assert(pParentNode);
    phantom::data ownerData = pParentNode->findData(ownerDataAddress);
    registerSubData(a_pSubData, ownerData, pParentNode);
}

void SubDataManager::slotSubDataRemoved( void* a_pSubData )
{
    o_assert(m_pDataBase);
    void* ownerDataAddress = phantom::connection::sender();
    Node* pParentNode = m_pDataBase->getNode(ownerDataAddress);
    o_assert(pParentNode);
    phantom::data d = pParentNode->findData(a_pSubData);
    o_assert(NOT(d.isNull()));
    pParentNode->removeData(d); 
    // unregisterSubDataOwner will be called automatically in 'removeData' just above,
    // no need to recall it there
    phantom::data ownerData = pParentNode->findData(ownerDataAddress);
    o_assert(NOT(d.isNull()));
    o_emit subDataRemoved(d, ownerData);
}

void SubDataManager::registerSubData( void* a_pAddress, const phantom::data& ownerData, Node* a_pNode )
{
    phantom::data d(a_pAddress);
    o_assert(NOT(d.isNull()), "unable to solve data type, the type must be a class "
        "and the instance must have phantom rtti (via installer implicitly called by o_new");
    m_pDataBase->registerSubDataOwner(d, ownerData);
    a_pNode->addData(d);
    o_emit subDataAdded(d, ownerData);
}
/*

void SubDataManager::addSubData( const phantom::data& ownerData, const data_class_interface& sdi, void* a_pData )
{
    void* args[1] = { &a_pData };
    sdi.subDataAddMethod->safeInvoke(ownerData.address(), args, nullptr );
}

void SubDataManager::removeSubData( const phantom::data& ownerData, const data_class_interface& sdi, void* a_pData )
{
    void* args[1] = { &a_pData };
    sdi.subDataRemoveMethod->safeInvoke(ownerData.address(), args, nullptr );
}*/

void SubDataManager::connectDataCascade( const data& a_Data, reflection::Class* a_pClass )
{
    return;
    vector<reflection::Collection*> collections;
    a_pClass->getAllCollectionCascade(collections);

    auto it = collections.begin();
    auto end = collections.end();
    for(;it!=end;++it)
    {
        if(NOT((*it)->isComponent())) continue; 
        connectCollection(*it, a_Data, true);
    }
}

void SubDataManager::disconnectDataCascade( const data& a_Data, reflection::Class* a_pClass )
{
    return;
    vector<reflection::Collection*> collections;
    a_pClass->getAllCollectionCascade(collections);

    auto it = collections.begin();
    auto end = collections.end();
    for(;it!=end;++it)
    {
        if(NOT((*it)->isComponent())) continue; 
        connectCollection(*it, a_Data, false);
    }
}

void SubDataManager::connectData( const data& a_Data )
{
    reflection::Class* pDataClass = a_Data.type()->asClass();
    if(pDataClass == NULL) return;
    connectDataCascade(a_Data, pDataClass);
}

void SubDataManager::disconnectData( const data& a_Data )
{
    reflection::Class* pDataClass = a_Data.type()->asClass();
    if(pDataClass == NULL) return;
    disconnectDataCascade(a_Data, pDataClass);
}

o_cpp_end