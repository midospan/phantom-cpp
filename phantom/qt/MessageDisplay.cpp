/* ******************* Includes ****************** */
#include <phantom/qt/qt.h>
#include "MessageDisplay.h"
#include "MessageDisplay.hxx"
#include <phantom/Message.h>
/* *********************************************** */
o_registerN((phantom, qt), MessageDisplay);

namespace phantom { namespace qt {
    
MessageDisplay::MessageDisplay( void ) 
: m_pRootMessage( nullptr )
{
    setColumnCount(1);
    QStringList headerLabels;
    headerLabels.append("Message");
    setHeaderLabels(headerLabels);
    connect(this, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), this, SLOT(slotItemDoubleClicked(QTreeWidgetItem*,int)));
}

o_initialize_cpp(MessageDisplay)
{
    
}

void MessageDisplay::setRootMessage(Message* a_pMessage)
{
    if(m_pRootMessage == a_pMessage) return;
    if(m_pRootMessage)
    {
        size_t i = 0;
        size_t count = m_pRootMessage->getChildCount();
        for(;i<count;++i)
        {
            Message* pChild = m_pRootMessage->getChild(i);
            removeNodeItem(pChild);
        }
        o_disconnect(m_pRootMessage, childAdded(Message*), this, addNodeItem(Message*));
        o_disconnect(m_pRootMessage, childRemoved(Message*), this, removeNodeItem(Message*));
        Q_ASSERT(this->topLevelItemCount() == 0);
    }
    m_pRootMessage = a_pMessage;
    if(m_pRootMessage)
    {
        o_connect(m_pRootMessage, childAdded(Message*), this, addNodeItem(Message*));
        o_connect(m_pRootMessage, childRemoved(Message*), this, removeNodeItem(Message*));
        size_t i = 0;
        size_t count = m_pRootMessage->getChildCount();
        for(;i<count;++i)
        {
            Message* pChild = m_pRootMessage->getChild(i);
            addNodeItem(pChild);
        }
    }
}

MessageDisplay::~MessageDisplay( void )
{

}

MessageDisplayItem* MessageDisplay::getItem( Message* a_pMessage ) const
{
    int i = 0;
    int count = topLevelItemCount () ;
    for(;i<count;++i)
    {
        MessageDisplayItem* pItem = static_cast<MessageDisplayItem*>( topLevelItem(i) );
        if(pItem->getMessage() == a_pMessage) return pItem;
        pItem = getItem(a_pMessage, pItem);
        if(pItem) return pItem;
    }
    return NULL;
}

MessageDisplayItem* MessageDisplay::getItem( Message* a_pMessage, MessageDisplayItem* a_pParentItem ) const
{
    int i = 0;
    int count = a_pParentItem->childCount();
    for(;i<count;++i)
    {
        MessageDisplayItem* pItem = static_cast<MessageDisplayItem*>( a_pParentItem->child(i) );
        if(pItem->getMessage() == a_pMessage) return pItem;
        pItem = getItem(a_pMessage, pItem);
        if(pItem) return pItem;
    }
    return NULL;
}
void MessageDisplay::addNodeItem( Message* a_pNode )
{
    MessageDisplayItem* pParentItem = getItem(a_pNode->getParent());
    MessageDisplayItem* pItem = new MessageDisplayItem(a_pNode);
    o_connect(a_pNode, childAdded(Message*), this, addNodeItem(Message*));
    o_connect(a_pNode, childRemoved(Message*), this, removeNodeItem(Message*));
    if(pParentItem)
    {
        pParentItem->addChild(pItem);
        pParentItem->updateLookCascade();
    }
    else
    {
        o_assert(a_pNode->getParent() == m_pRootMessage);
        addTopLevelItem(pItem);
    }
    size_t i = 0;
    size_t count = a_pNode->getChildCount();
    for(;i<count;++i)
    {
        addNodeItem(a_pNode->getChild(i));
    }
    scrollToItem(pItem);
}

void MessageDisplay::removeNodeItem( Message* a_pNode )
{
    MessageDisplayItem* pItem = getItem(a_pNode);
    size_t i = 0;
    size_t count = a_pNode->getChildCount();
    for(;i<count;++i)
    {
        removeNodeItem(a_pNode->getChild(i));
    }
    o_disconnect(a_pNode, childAdded(Message*), this, addNodeItem(Message*));
    o_disconnect(a_pNode, childRemoved(Message*), this, removeNodeItem(Message*));
    o_assert(pItem);
    if(pItem->parent())
    {
        pItem->parent()->removeChild(pItem);
    }
    else 
    {
        takeTopLevelItem(indexOfTopLevelItem(pItem));
    }
    delete pItem;
}

void MessageDisplay::slotItemDoubleClicked( QTreeWidgetItem* a_pItem, int )
{
    if(a_pItem == nullptr) return;

    Message* pMessage = ((MessageDisplayItem*)a_pItem)->getMessage();
    pMessage->open();
}

void MessageDisplay::listenedMessageChanged()
{
    Message* pMessage = as<Message*>(connection::sender());
    o_assert(pMessage);
    setRootMessage(pMessage);
}


MessageDisplayItem::MessageDisplayItem( Message* a_pNode ) : m_pMessage(a_pNode)
{
    updateLook();
}

void MessageDisplayItem::updateLook()
{
    Message* message = m_pMessage;
    setText(0,  message ? message->getText().c_str() : "");
    switch(m_pMessage->getMostValuableMessageType())
    {
    case e_MessageType_Error:
        setIcon(0, QIcon(":/../../bin/resources/icons/exclamation.png"));
        break;
    case e_MessageType_Warning:
        setIcon(0, QIcon(":/../../bin/resources/icons/error.png"));
        break;
    case e_MessageType_Information:
        setIcon(0, QIcon(":/../../bin/resources/icons/information.png"));
        break;
    case e_MessageType_Success:
        setIcon(0, QIcon(":/../../bin/resources/icons/accept.png"));
        break;
    }
}

void MessageDisplayItem::updateLookCascade()
{
    updateLook();
    if(parent())
        ((MessageDisplayItem*)parent())->updateLookCascade() ;
}

}}