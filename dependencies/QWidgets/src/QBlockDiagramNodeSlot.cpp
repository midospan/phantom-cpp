
#include "QBlockDiagramNodeSlot.h"
#include "QBlockDiagramLinkEnd.h"
#include "QBlockDiagramLink.h"
#include "QBlockDiagramModel.h"
#include "QBlockDiagramNode.h"
#include <QPainter>
#include <Qmath.h>
#include <QGraphicsSimpleTextItem>

QBlockDiagramNodeSlot::QBlockDiagramNodeSlot(const QString& a_strName)
  : QBlockDiagramConnector(a_strName)
  , m_FillColor(20,190,150)
  , m_BorderColor(33,33,33)
  , m_bConnectionNodesExpanded(false)
  , m_pManipulatedLinkEnd(NULL)
  , m_iMaxConnectionCount(1)
  , m_LinkDirectionAngle(0)
{
    setFlag (QGraphicsItem::ItemIsSelectable);
    setAcceptHoverEvents(true);
    m_pTextItem = new QGraphicsSimpleTextItem();
    m_pTextItem->setParentItem(this);
}

QBlockDiagramNodeSlot::QBlockDiagramNodeSlot()
    : m_FillColor(20,190,150)
    , m_BorderColor(33,33,33)
    , m_bConnectionNodesExpanded(false)
    , m_pManipulatedLinkEnd(NULL)
    , m_iMaxConnectionCount(1)
    , m_LinkDirectionAngle(0)
{
    setFlag (QGraphicsItem::ItemIsSelectable);
    setAcceptHoverEvents(true);
    m_pTextItem = new QGraphicsSimpleTextItem();
    m_pTextItem->setParentItem(this);
}

QBlockDiagramNodeSlot::~QBlockDiagramNodeSlot()
{

}

QRectF QBlockDiagramNodeSlot::boundingRect() const
{
  if(areConnectionNodesExpanded())
  {
    return childrenBoundingRect().united(slotBoundingRect());
  }
  else
  {
    return slotBoundingRect();
  }
}

void QBlockDiagramNodeSlot::expandConnectionNodes()
{
  Q_ASSERT(!m_bConnectionNodesExpanded);
  m_bConnectionNodesExpanded = true;
    if(m_ConnectionInfos.empty()) return;
  connection_info_vector::const_iterator it = m_ConnectionInfos.begin();
  connection_info_vector::const_iterator end = m_ConnectionInfos.end();
  qreal spacing = 20.f;
  qreal firstY = -(m_ConnectionInfos.count()-1)*spacing*0.5f; 
  qreal rot = getLinkDirectionAngle()*M_PI/180;
  int i = 0;
  int x = 24.f;
  for(;it!=end;++it)
  {
    int y = firstY+spacing*i;
    (*it).second->setPos(x*cos(rot)-y*sin(rot),y*cos(rot)+x*sin(rot));
    (*it).first->getOwnerLink()->prepareGeometryChangeSlot();
    ++i;
  }
}

void QBlockDiagramNodeSlot::collapseConnectionNodes()
{
  Q_ASSERT(m_bConnectionNodesExpanded);

  if(!m_ConnectionInfos.empty())
  {
      connection_info_vector::const_iterator it = m_ConnectionInfos.begin();
      connection_info_vector::const_iterator end = m_ConnectionInfos.end();
      for(;it!=end;++it)
      {
          (*it).second->setPos(0,0);
          (*it).first->setPos(0,0);
          (*it).first->getOwnerLink()->prepareGeometryChangeSlot();
      }
  }
  m_bConnectionNodesExpanded = false;
}

void QBlockDiagramNodeSlot::connectLinkEnd( QBlockDiagramLinkEnd* a_pLinkEnd )
{
    Q_ASSERT(acceptsLinkEnd(a_pLinkEnd));
  Q_ASSERT(!isLinkEndConnected(a_pLinkEnd));
  QConnectionNode* pConnectionNode = new QConnectionNode;

  // parent the link end
  pConnectionNode->setParentItem(this);
  a_pLinkEnd->setPos(0,0);
  a_pLinkEnd->setParentItem(pConnectionNode);
  m_ConnectionInfos.append(connection_info(a_pLinkEnd, pConnectionNode));
  a_pLinkEnd->m_pConnectedSlot = this;
  QObject::connect(this, SIGNAL(moved()), a_pLinkEnd, SIGNAL(moved()));
  QObject::connect(a_pLinkEnd, SIGNAL(moved()), this, SLOT(prepareGeometryChangeSlot()));
  a_pLinkEnd->getOwnerLink()->prepareGeometryChange();
  emit linkEndConnected(a_pLinkEnd);
  if(a_pLinkEnd->getTwin()->getConnectedSlot())
  {
      emit connected(a_pLinkEnd->getTwin()->getConnectedSlot());
      emit a_pLinkEnd->getTwin()->getConnectedSlot()->connected(this);
  }
}

void QBlockDiagramNodeSlot::disconnectLinkEnd( QBlockDiagramLinkEnd* a_pLinkEnd )
{
    if(a_pLinkEnd->getTwin()->getConnectedSlot())
    {
        emit aboutToBeDisconnected(a_pLinkEnd->getTwin()->getConnectedSlot());
        emit a_pLinkEnd->getTwin()->getConnectedSlot()->aboutToBeDisconnected(this);
    }
    emit linkEndAboutToBeDisconnected(a_pLinkEnd);
    QObject::disconnect(this, SIGNAL(moved()), a_pLinkEnd, SIGNAL(moved()));
    QObject::disconnect(a_pLinkEnd, SIGNAL(moved()), this, SLOT(prepareGeometryChangeSlot()));
    a_pLinkEnd->m_pConnectedSlot = NULL;

    // unparent the link end
    QPointF scene_pos = a_pLinkEnd->scenePos();
    a_pLinkEnd->setParentItem(NULL);
  
    a_pLinkEnd->setPos(scene_pos);
    Q_ASSERT(isLinkEndConnected(a_pLinkEnd));
    connection_info_vector::iterator it = m_ConnectionInfos.begin();
    connection_info_vector::iterator end = m_ConnectionInfos.end();
    for(;it!=end;++it)
    {
        if((*it).first == a_pLinkEnd) break;
    }
    Q_ASSERT(it != end);
    QConnectionNode* pConnectionNode = it->second;
    Q_ASSERT(pConnectionNode->childItems().empty());
    pConnectionNode->setParentItem(NULL);
    pConnectionNode->deferDestruction();
    m_ConnectionInfos.erase(it);
    a_pLinkEnd->getOwnerLink()->prepareGeometryChange();
    if(a_pLinkEnd->getTwin()->getConnectedSlot())
    {
        emit disconnected(a_pLinkEnd->getTwin()->getConnectedSlot());
        emit a_pLinkEnd->getTwin()->getConnectedSlot()->disconnected(this);
    }
}

void QBlockDiagramNodeSlot::hoverEnterEvent( QGraphicsSceneHoverEvent* event )
{
  if(m_ConnectionInfos.size() > 0)
  {
      expandConnectionNodes();
  }
}

void QBlockDiagramNodeSlot::hoverLeaveEvent( QGraphicsSceneHoverEvent* event )
{
    if(areConnectionNodesExpanded())
    {
        collapseConnectionNodes();
    }
}

QRectF QBlockDiagramNodeSlot::slotBoundingRect() const
{
  return QRectF(-8,-8,16,16);
}

void QBlockDiagramNodeSlot::paint( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget /*= 0 */ )
{
  QPen pen(m_BorderColor);
  pen.setWidthF(4);
  painter->setPen(pen);
  painter->setBrush(m_FillColor);
  painter->drawEllipse(slotBoundingRect());
  painter->setPen(m_FillColor);
  if(areConnectionNodesExpanded())
  {
      connection_info_vector::iterator it = m_ConnectionInfos.begin();
      connection_info_vector::iterator end = m_ConnectionInfos.end();
      for(;it!=end;++it)
      {
          painter->drawLine(it->second->pos()+it->first->pos(), QPointF(0,0));
      }
      if(getConnectionCount() > 1)
      {
          QFont f = painter->font();
          f.setPointSize(7);
          f.setWeight(99);
          painter->setFont(f);
          painter->drawText(getConnectedLinkEnd(0)->boundingRect(), Qt::AlignCenter, QString::number(getConnectionCount()));
      }
  }
}

void QBlockDiagramNodeSlot::mousePressEvent( QGraphicsSceneMouseEvent* event )
{
    if((m_pOwnerNode->nodeFlags() & AutoGenerateLink) == AutoGenerateLink)
    {
        QBlockDiagramLink* pNewLink = scene()->createLink();
        scene()->addItem(pNewLink);
        pNewLink->getEnd(QBlockDiagramLink::eFirst)->connect(this);
        if(acceptsLinkEnd(pNewLink->getEnd(QBlockDiagramLink::eSecond)))
        {
            pNewLink->getEnd(QBlockDiagramLink::eSecond)->connect(this);
        }
        else
        {
            pNewLink->getEnd(QBlockDiagramLink::eSecond)->setPos(pNewLink->getEnd(QBlockDiagramLink::eFirst)->scenePos());
        }
        setManipulatedLinkEnd(pNewLink->getEnd(QBlockDiagramLink::eSecond));
        m_pManipulatedLinkEnd->mousePressEvent( event );
    }
}

void QBlockDiagramNodeSlot::mouseMoveEvent( QGraphicsSceneMouseEvent* event )
{
    if(m_pManipulatedLinkEnd)
    {
        m_pManipulatedLinkEnd->mouseMoveEvent(event);
    }
}
void QBlockDiagramNodeSlot::mouseReleaseEvent( QGraphicsSceneMouseEvent* event )
{
    if(m_pManipulatedLinkEnd)
    {
        m_pManipulatedLinkEnd->mouseReleaseEvent(event);
        unsetManipulatedLinkEnd();
    }
}
void QBlockDiagramNodeSlot::setManipulatedLinkEnd( QBlockDiagramLinkEnd* a_pLinkEnd )
{
    Q_ASSERT(a_pLinkEnd != NULL);
    Q_ASSERT(m_pManipulatedLinkEnd == NULL);
    m_pManipulatedLinkEnd = a_pLinkEnd;
}

void QBlockDiagramNodeSlot::unsetManipulatedLinkEnd()
{
    Q_ASSERT(m_pManipulatedLinkEnd);
    m_pManipulatedLinkEnd = NULL;
}

bool QBlockDiagramNodeSlot::isFullyConnected() const
{
    connection_info_vector::const_iterator it = m_ConnectionInfos.begin();
    connection_info_vector::const_iterator end = m_ConnectionInfos.end();
    for(;it!=end;++it)
    {
        if(!(it->first->getTwin()->getConnectedSlot())) return false;
    }
    return !(m_ConnectionInfos.empty());
}

void QBlockDiagramNodeSlot::disconnectAllLinkEnd()
{
    while(!(m_ConnectionInfos.empty()))
    {
        disconnectLinkEnd(m_ConnectionInfos.back().first);
    }
}

bool QBlockDiagramNodeSlot::isSlotConnected( QBlockDiagramNodeSlot* a_pSlot ) const
{
    connection_info_vector::const_iterator it = m_ConnectionInfos.begin();
    connection_info_vector::const_iterator end = m_ConnectionInfos.end();
    for(;it!=end;++it)
    {
        if((*it).first->getTwin()->getConnectedSlot() == a_pSlot)
        {
            return true;
        }
    }
    return false;
}
