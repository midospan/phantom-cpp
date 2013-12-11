#ifndef QWIDGETSMODEL_H
#define QWIDGETSMODEL_H

#include "QWidgetsPrerequisites.h"
#include <QGraphicsScene>
#include <QTimer>

class QBlockDiagramItem;
class QBlockDiagramNode;
class QBlockDiagramNodeSlot;
class QBlockDiagramLink;
class QBlockDiagramLinkEnd;

class QWIDGETS_EXPORT QBlockDiagramModel : public QGraphicsScene
{
  Q_OBJECT

public:
    QBlockDiagramModel(QObject *parent = 0);
    ~QBlockDiagramModel();

    virtual QBlockDiagramLink*  createLink() const;
    virtual void                destroyLink(QBlockDiagramLink* a_pLink) const;

    QBlockDiagramNodeSlot* nodeSlotAroundLinkEnd(QBlockDiagramLinkEnd* a_pEnd);

    void                setMouseGrabberItem(QBlockDiagramItem* a_pItem);
    void                unsetMouseGrabberItem(QBlockDiagramItem* a_pItem);
    QBlockDiagramItem*  getMouseGrabberItem() const { return m_pMouseGrabberItem; }

    void*               getUserData() const { return m_pUserData; }
    void                setUserData(void* a_pUserData) { m_pUserData = a_pUserData; }

protected:
    QVector<QBlockDiagramItem*> m_DiagramItems;
    QBlockDiagramItem*          m_pMouseGrabberItem;
    void*                       m_pUserData;
    
};

#endif // QWIDGETSMODEL_H
