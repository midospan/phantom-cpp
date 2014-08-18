

#ifndef MessageDisplay_h__
#define MessageDisplay_h__
// #pragma message("Including "__FILE__)


/* ****************** Includes ******************* */
#include <QTreeWidget>
#include <phantom/util/Message.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, qt), MessageDisplay);
/* *********************************************** */
namespace phantom { 

class MessageTree;
class Message;

namespace qt {

class MessageDisplayItem : public QTreeWidgetItem
{
public:
    MessageDisplayItem(Message* a_pNode);

    Message* getMessage() const { return m_pMessage; }

    void updateLook();
    void updateLookCascade();

protected:
    Message* m_pMessage;
};

class o_qt_export MessageDisplay : public QTreeWidget
{
    Q_OBJECT
public:
	MessageDisplay(void);
	~MessageDisplay(void);

    o_initialize();

    void setRootMessage(Message* a_pMessage);

    void addListenedMessage(Message* a_pMessage)
    {
        o_connect(a_pMessage, descendantAdded(Message*), this, listenedMessageChanged());
        o_connect(a_pMessage, descendantRemoved(Message*), this, listenedMessageChanged());
    }

    void removeListenedMessage(Message* a_pMessage)
    {
        o_disconnect(a_pMessage, descendantAdded(Message*), this, listenedMessageChanged());
        o_disconnect(a_pMessage, descendantRemoved(Message*), this, listenedMessageChanged());
    }

protected:
    MessageDisplayItem* getItem(Message* a_pMessage) const;
    MessageDisplayItem* getItem(Message* a_pMessage, MessageDisplayItem* a_pParentItem) const;

    void listenedMessageChanged();

protected:
    void addNodeItem(Message* a_pNode);
    void removeNodeItem(Message* a_pNode);

signals:
    void messageStreamNodeDoubleClicked(Message*);

protected slots:
    void slotItemDoubleClicked(QTreeWidgetItem*, int);

protected:
    Message* m_pRootMessage;

};

}}

#endif