

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

    void setMessageTree(MessageTree* a_pMessageTree);

protected:
    MessageDisplayItem* getItem(Message* a_pMessage) const;
    MessageDisplayItem* getItem(Message* a_pMessage, MessageDisplayItem* a_pParentItem) const;

protected:
    void addNodeItem(Message* a_pNode);
    void removeNodeItem(Message* a_pNode);

signals:
    void messageStreamNodeDoubleClicked(Message*);

protected slots:
    void slotItemDoubleClicked(QTreeWidgetItem*, int);

protected:
    MessageTree* m_pMessageTree;

};

}}

#endif