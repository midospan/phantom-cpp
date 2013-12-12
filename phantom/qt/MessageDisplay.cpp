/* ******************* Includes ****************** */
#include <phantom/qt/qt.h>
#include "MessageDisplay.h"
#include <phantom/util/MessageTree.h>
#include <phantom/util/Message.h>
/* ** The Class Header must be the last #include * */
/* *********************************************** */
o_registerN((phantom, qt), MessageDisplay);

namespace phantom { namespace qt {
    
MessageDisplay::MessageDisplay( void ) 
: m_pMessageTree( nullptr )
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

void MessageDisplay::setMessageTree(MessageTree* a_pMessageTree)
{
    if(m_pMessageTree == a_pMessageTree) return;
    if(m_pMessageTree)
    {
        o_disconnect(m_pMessageTree->getRootMessage(), childAdded(Message*), this, addNodeItem(Message*));
        o_disconnect(m_pMessageTree->getRootMessage(), childRemoved(Message*), this, removeNodeItem(Message*));
        clear();
    }
    m_pMessageTree = a_pMessageTree;
    if(m_pMessageTree)
    {
        o_connect(m_pMessageTree->getRootMessage(), childAdded(Message*), this, addNodeItem(Message*));
        o_connect(m_pMessageTree->getRootMessage(), childRemoved(Message*), this, removeNodeItem(Message*));
        size_t i = 0;
        size_t count = m_pMessageTree->getRootMessage()->getChildCount();
        for(;i<count;++i)
        {
            Message* pChild = m_pMessageTree->getRootMessage()->getChild(i);
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
        o_assert(a_pNode->getParent() == m_pMessageTree->getRootMessage());
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
    o_disconnect(a_pNode, childAdded(Message*), this, addNodeItem(Message*));
    o_disconnect(a_pNode, childRemoved(Message*), this, removeNodeItem(Message*));
    o_assert(pItem);
    if(pItem->parent())
    {
        pItem->parent()->removeChild(pItem);
    }
    delete pItem;
}

void MessageDisplay::slotItemDoubleClicked( QTreeWidgetItem* a_pItem, int )
{
    if(a_pItem == nullptr) return;

    Message* pMessage = ((MessageDisplayItem*)a_pItem)->getMessage();
    pMessage->open();
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
    case Message::e_Type_Error:
        setIcon(0, QIcon(":/../../bin/resources/icons/exclamation.png"));
        break;
    case Message::e_Type_Warning:
        setIcon(0, QIcon(":/../../bin/resources/icons/error.png"));
        break;
    case Message::e_Type_Information:
        setIcon(0, QIcon(":/../../bin/resources/icons/information.png"));
        break;
    case Message::e_Type_Success:
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