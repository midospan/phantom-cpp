
#include "QBlockDiagramLinkEnd.h"
#include "QBlockDiagramLink.h"
#include "QBlockDiagramNodeSlot.h"
#include "QBlockDiagramNode.h"
#include "QBlockDiagramModel.h"
#include <QPainter>
#include <qmath.h>

QBlockDiagramLinkEnd::QBlockDiagramLinkEnd(QBlockDiagramLink* a_pOwnerLink)
  : QBlockDiagramConnector()
  , m_pOwnerLink(a_pOwnerLink)
  , m_pConnectedSlot(NULL)
  , m_pSnapedSlot(NULL)
  , m_bIsMoving(false)
{
  setFlag (QGraphicsItem::ItemIsMovable);
  setFlag (QGraphicsItem::ItemIsSelectable);
}

QBlockDiagramLinkEnd::~QBlockDiagramLinkEnd()
{
}

void QBlockDiagramLinkEnd::connect( QBlockDiagramNodeSlot* a_pSlot )
{
  Q_ASSERT(m_pConnectedSlot == NULL && a_pSlot != NULL);
  a_pSlot->connectLinkEnd(this);
}

void QBlockDiagramLinkEnd::disconnect()
{
  Q_ASSERT(m_pConnectedSlot != NULL);
  m_pConnectedSlot->disconnectLinkEnd(this);
}

QRectF QBlockDiagramLinkEnd::boundingRect() const
{
  return QRectF(-8, -8, 16, 16);
}

QVector2D QBlockDiagramLinkEnd::computeDir() const
{
  if(getCurrentSlot() == NULL) return QVector2D(0,0);
  return QVector2D( cos(getCurrentSlot()->getLinkDirectionAngle()*M_PI/180.f), sin(getCurrentSlot()->getLinkDirectionAngle()*M_PI/180.f) );
}

void QBlockDiagramLinkEnd::mousePressEvent( QGraphicsSceneMouseEvent * event )
{
  QBlockDiagramConnector::mousePressEvent(event);
  if(m_pConnectedSlot)
  {
      m_pConnectedSlot->setZValue(10000);
      m_pConnectedSlot->getOwnerNode()->setZValue(10000);
  }
}

void QBlockDiagramLinkEnd::mouseMoveEvent( QGraphicsSceneMouseEvent * event )
{
    QBlockDiagramConnector::mouseMoveEvent(event);
    m_bIsMoving = true;
    m_pSnapedSlot = scene()->nodeSlotAroundLinkEnd(this);
    if(m_pSnapedSlot != NULL)
    {
      setPos(pos()+(m_pSnapedSlot->scenePos()-scenePos()));
    }
}

void QBlockDiagramLinkEnd::mouseReleaseEvent( QGraphicsSceneMouseEvent * event )
{
    QBlockDiagramConnector::mouseReleaseEvent(event);
    m_pOwnerLink->prepareGeometryChangeSlot();
    m_bIsMoving = false;
    if(m_pConnectedSlot)
    {
        m_pConnectedSlot->setZValue(0);
        m_pConnectedSlot->getOwnerNode()->setZValue(0);
    }
    QBlockDiagramNodeSlot* pSlot = scene()->nodeSlotAroundLinkEnd(this);
    if(pSlot == NULL && m_pOwnerLink->isDestroyOnDisconnectedEndEnabled())
    {
      m_pSnapedSlot = NULL;
      m_pOwnerLink->deferDestruction();
      return;
    }
    if(pSlot == m_pConnectedSlot) 
    {
        m_pSnapedSlot = NULL;
        return;
    }
    if(pSlot) 
    {
      if(m_pConnectedSlot)
      {
        disconnect();
      }
      connect(pSlot);
    }
    else
    {
      disconnect();
    }
    m_pSnapedSlot = NULL;
}

QBlockDiagramLinkEnd* QBlockDiagramLinkEnd::getTwin() const
{
    return m_pOwnerLink->getEndTwin(this);
}

void QBlockDiagramLinkEnd::paint( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget /*= 0 */ )
{
    QPen pen(QColor(200,200,200));
    pen.setWidthF(2);
    painter->setPen(pen);
    painter->setBrush(m_pOwnerLink->getCurrentColor());
    painter->drawEllipse(boundingRect());
    if(getConnectedSlot() && !isMoving() && !getTwin()->isMoving())
    {
        if(getConnectedSlot()->getConnectionCount() > 1 && !getConnectedSlot()->areConnectionNodesExpanded())
        {
            QFont f = painter->font();
            f.setPointSize(7);
            f.setWeight(99);
            painter->setFont(f);
            painter->drawText(boundingRect(), Qt::AlignCenter, QString::number(getConnectedSlot()->getConnectionCount()));
        }
    }
}