
#include "QBlockDiagramModel.h"
#include "QBlockDiagramItem.h"
#include "QBlockDiagramLink.h"
#include "QBlockDiagramLinkEnd.h"
#include "QBlockDiagramNodeSlot.h"
#include "QBlockDiagramNode.h"

QBlockDiagramModel::QBlockDiagramModel(QObject *parent)
  : QGraphicsScene(parent)
  , m_pMouseGrabberItem(nullptr)
  , m_pUserData(nullptr)
{
    setItemIndexMethod(NoIndex);
    setBackgroundBrush(QColor(33,33,33));
}

QBlockDiagramModel::~QBlockDiagramModel()
{
}

QBlockDiagramNodeSlot* QBlockDiagramModel::nodeSlotAroundLinkEnd( QBlockDiagramLinkEnd* a_pEnd )
{
  const QList<QGraphicsItem *>& item_list	= items ();
  QGraphicsItem*  pItem = NULL;
  Q_FOREACH(pItem, item_list)
  {
    QGraphicsObject* pObject = pItem->toGraphicsObject();
    if(pObject != NULL && pObject->inherits("QBlockDiagramItem") && static_cast<QBlockDiagramItem*>(pItem)->isNodeSlot())
    {
      QBlockDiagramNodeSlot* pSlot = static_cast<QBlockDiagramNodeSlot*>(pItem);
      QLineF distance(a_pEnd->scenePos(),pSlot->scenePos());
      if(distance.length() < 20.f && pSlot->acceptsLinkEnd(a_pEnd))
      {
        return pSlot;
      }
    }
  }
  return NULL;
}

QBlockDiagramLink* QBlockDiagramModel::createLink() const
{
    return new QBlockDiagramLink;
}

void QBlockDiagramModel::destroyLink( QBlockDiagramLink* a_pLink ) const
{
    delete a_pLink;
}
