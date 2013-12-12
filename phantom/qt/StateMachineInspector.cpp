/* ******************* Includes ****************** */
#include "phantom/qt/qt.h"
#include "StateMachineInspector.h"
/* *********************************************** */
o_registerN((phantom, qt), StateMachineInspector);

 
namespace phantom { 
namespace qt {

StateMachineInspector::StateMachineInspector( void )
    : m_pStateMachine(nullptr)
    , m_pDataBase(nullptr)
{
    m_pStateMachineTreeWidget = new QTreeWidget;
    m_pStateMachineTreeWidget->setColumnCount(2);
    QStringList labels;
    labels.append("");
    labels.append("");
    m_pStateMachineTreeWidget->setHeaderLabels(labels);
    m_pStateMachineTreeWidget->setHeaderHidden(true);
    setLayout(new QVBoxLayout);
    layout()->addWidget(m_pStateMachineTreeWidget);
    layout()->setMargin(0);
    hide();
}

void StateMachineInspector::editData( const vector<phantom::data>& a_data )
{
    if(NOT(m_EditedData.empty()))
    {
        // end edition
        m_pStateMachineTreeWidget->clear();
        m_EditedData.clear();
        m_pStateMachine = nullptr;
    }
    m_EditedData = a_data;
    if(NOT(m_EditedData.empty()))
    {
        // start edition
        reflection::Type* pCommonType = m_EditedData.front().type();
        for(auto it = m_EditedData.begin()+1; it != m_EditedData.end(); ++it)
        {
            pCommonType = pCommonType ? pCommonType->getCommonAncestor(it->type()) : nullptr;
        }

        reflection::Class* pClass = pCommonType ? pCommonType->asClass() : nullptr;
        
        if(pClass == nullptr) 
        {
            hide();
            return; // No class, no edition
        }
        m_pStateMachine = pClass->getStateMachineCascade();
        if(m_pStateMachine == nullptr) 
        {
            hide();
            return; // No state machine, no edition
        }

        size_t i = 0;
        size_t count = m_pStateMachine->getTrackCount();
        for(;i<count;++i)
        {
            m_pStateMachineTreeWidget->addTopLevelItem(new StateTrackItem(m_pStateMachine->getTrack(i)));
        }

        i = 0;
        count = m_pStateMachine->getEventCount();
        for(;i<count;++i)
        {
            m_pStateMachineTreeWidget->addTopLevelItem(new StateEventItem(this, m_pStateMachine, i));
        }

        show();
    }
    else hide();

}

void StateMachineInspector::start()
{
    if(m_pStateMachine == nullptr) return;
    vector<void*> addresses;
    for(auto it = m_EditedData.begin(); it != m_EditedData.end(); ++it)
    {
        addresses.push_back(it->cast(m_pStateMachine->getOwnerClass()).address());
    }
    int i = 0;
    int count = m_pStateMachineTreeWidget->topLevelItemCount () ;
    for(;i<count;++i)
    {
        static_cast<StateMachineTreeWidgetItem*>( m_pStateMachineTreeWidget->topLevelItem(i) )->start(addresses);
    }
}

void StateMachineInspector::update()
{
    if(m_pStateMachine == nullptr) return;
    vector<void*> addresses;
    for(auto it = m_EditedData.begin(); it != m_EditedData.end(); ++it)
    {
        addresses.push_back(it->cast(m_pStateMachine->getOwnerClass()).address());
    }
    int i = 0;
    int count = m_pStateMachineTreeWidget->topLevelItemCount () ;
    for(;i<count;++i)
    {
        static_cast<StateMachineTreeWidgetItem*>( m_pStateMachineTreeWidget->topLevelItem(i) )->update(addresses);
    }
}

void StateMachineInspector::stop()
{
    if(m_pStateMachine == nullptr) return;
    vector<void*> addresses;
    for(auto it = m_EditedData.begin(); it != m_EditedData.end(); ++it)
    {
        addresses.push_back(it->cast(m_pStateMachine->getOwnerClass()).address());
    }
    int i = 0;
    int count = m_pStateMachineTreeWidget->topLevelItemCount () ;
    for(;i<count;++i)
    {
        static_cast<StateMachineTreeWidgetItem*>( m_pStateMachineTreeWidget->topLevelItem(i) )->stop(addresses);
    }
}

StateMachineTreeWidgetItem* StateMachineInspector::getItem( void* a_pContent ) const
{
    int i = 0;
    int count = m_pStateMachineTreeWidget->topLevelItemCount () ;
    for(;i<count;++i)
    {
        StateMachineTreeWidgetItem* pItem = static_cast<StateMachineTreeWidgetItem*>( m_pStateMachineTreeWidget->topLevelItem(i) );
        if(pItem->getContent() == a_pContent) return pItem;
        pItem = getItem(a_pContent, pItem);
        if(pItem) return pItem;
    }
    return NULL;
}

StateMachineTreeWidgetItem* StateMachineInspector::getItem( void* a_pContent, StateMachineTreeWidgetItem* a_pParentItem ) const
{
    int i = 0;
    int count = a_pParentItem->childCount();
    for(;i<count;++i)
    {
        StateMachineTreeWidgetItem* pItem = static_cast<StateMachineTreeWidgetItem*>( a_pParentItem->child(i) );
        if(pItem->getContent() == a_pContent) return pItem;
        pItem = getItem(a_pContent, pItem);
        if(pItem) return pItem;
    }
    return NULL;
}

void StateMachineInspector::dataReplaced( const phantom::data& a_Old, const phantom::data& a_New )
{
    auto found = std::find(m_EditedData.begin(), m_EditedData.end(), a_Old);
    if(found == m_EditedData.end())
        return;
    *found = a_New;
    editData(m_EditedData);
}

void StateMachineInspector::dataAboutToBeRemoved(const phantom::data& a_Old, phantom::serialization::Node*)
{
    auto found = std::find(m_EditedData.begin(), m_EditedData.end(), a_Old);
    if(found == m_EditedData.end())
        return;
    m_EditedData.erase(found);
    editData(m_EditedData);
}

void StateMachineInspector::setDataBase( serialization::DataBase* a_pDataBase )
{
    if(m_pDataBase == a_pDataBase) return;
    if(m_pDataBase)
    {
        o_disconnect(m_pDataBase, dataAboutToBeRemoved(const phantom::data&, serialization::Node*), this, dataAboutToBeRemoved(const phantom::data&, serialization::Node*));
        o_disconnect(m_pDataBase, dataReplaced(const phantom::data&, const phantom::data&), this, dataReplaced(const phantom::data&, const phantom::data&));
    }
    m_pDataBase = a_pDataBase;
    if(m_pDataBase)
    {
        o_connect(m_pDataBase, dataAboutToBeRemoved(const phantom::data&, serialization::Node*), this, dataAboutToBeRemoved(const phantom::data&, serialization::Node*));
        o_connect(m_pDataBase, dataReplaced(const phantom::data&, const phantom::data&), this, dataReplaced(const phantom::data&, const phantom::data&));
    }
}

void StateEventPostAction::post()
{
    for(auto it = m_Addresses.begin(); it != m_Addresses.end(); ++it)
    {
        m_pInspector->eventPosted(m_pStateMachine, *it, m_uiEventId);
    }
}

}
}