
#include "QBlockDiagramLink.h"
#include "QBlockDiagramLinkEnd.h"
#include "QBlockDiagramModel.h"
#include "QBlockDiagramNodeSlot.h"
#include "QBlockDiagramNode.h"
#include <QPainter>
#include <qmath.h>

QBlockDiagramLink::QBlockDiagramLink()
    : m_States(0)
{
    m_Pens[e_State_Default].setColor(QColor(255,255,255));
    m_Pens[e_State_Default].setWidth(2);
    m_Brushes[e_State_Default] = QBrush(QColor(255,255,255,192));
    setZValue(-1);
    m_Ends[eFirst] = new QBlockDiagramLinkEnd(this);
    m_Ends[eSecond] = new QBlockDiagramLinkEnd(this);
    connect(m_Ends[eFirst], SIGNAL(moved()), this, SLOT(prepareGeometryChangeSlot()));
    connect(m_Ends[eSecond], SIGNAL(moved()), this, SLOT(prepareGeometryChangeSlot()));
    connect(m_Ends[eFirst], SIGNAL(parentChanged()), this, SLOT(prepareGeometryChangeSlot()));
    connect(m_Ends[eSecond], SIGNAL(parentChanged()), this, SLOT(prepareGeometryChangeSlot()));
    connect(m_Ends[eFirst], SIGNAL(destroyed()), this, SLOT(linkEndDestroyed()));
    connect(m_Ends[eSecond], SIGNAL(destroyed()), this, SLOT(linkEndDestroyed()));
    setFlag (QGraphicsItem::ItemIsSelectable);
}

QBlockDiagramLink::~QBlockDiagramLink()
{
}

QRectF QBlockDiagramLink::boundingRect() const
{
  return m_Path.boundingRect().united(m_DebugPath.boundingRect());
}

void QBlockDiagramLink::paint( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget /*= 0 */ )
{
    if(!(isValid())) return;
  /*QColor color = m_Ends[eFirst]->getConnectedSlot() 
                    ? m_Ends[eSecond]->getConnectedSlot() 
                        ? QColor(200,200,180)
                        : QColor(200,150,0)
                    : m_Ends[eSecond]->getConnectedSlot() 
                        ? QColor(200,150,0)
                        : QColor(200,70,0);*/
  painter->setPen(m_Pens[dominantPenState()]);
  painter->drawPath(m_Path);

  //painter->drawPath(m_DebugPath);
}

void QBlockDiagramLink::prepareGeometryChangeSlot()
{
    if(!(isValid())) return;
    m_Path = m_DebugPath = QPainterPath();
    QPointF start_pos = m_Ends[eFirst]->scenePos ();
    QPointF end_pos = m_Ends[eSecond]->scenePos ();
    QVector2D start_dir = m_Ends[eFirst]->computeDir();
    QVector2D end_dir = m_Ends[eSecond]->computeDir();

    QPointF dir_between_p = end_pos - start_pos;
    QVector2D dir_between(dir_between_p.x(), dir_between_p.y());
    dir_between.normalize();
    QVector2D refdir = start_dir.isNull() ? -end_dir : start_dir;
    refdir.normalize();

    QVector2D dir_start = QVector2D::dotProduct(dir_between, refdir) >= 0 ? refdir : -refdir;
    QVector2D dir_end = QVector2D::dotProduct(-dir_between, refdir) >= 0 ? refdir : -refdir;

    qreal start_w = m_Ends[eFirst]->boundingRect().width();
    qreal end_w = m_Ends[eSecond]->boundingRect().width();
    start_pos.setX(start_pos.x() + dir_start.x()*start_w*0.5f);
    start_pos.setY(start_pos.y() + dir_start.y()*start_w*0.5f);
    end_pos.setX(end_pos.x() + dir_end.x()*end_w*0.5f);
    end_pos.setY(end_pos.y() + dir_end.y()*end_w*0.5f);

    m_Path.moveTo(start_pos);
    m_DebugPath.moveTo(start_pos);

    QBlockDiagramNodeSlot* pStartSlot = m_Ends[eFirst]->getCurrentSlot();
    QBlockDiagramNodeSlot* pEndSlot = m_Ends[eSecond]->getCurrentSlot();
    QBlockDiagramNodeSlot* pStartSnapedSlot = m_Ends[eFirst]->getSnapedSlot();
    QBlockDiagramNodeSlot* pEndSnapedSlot = m_Ends[eSecond]->getSnapedSlot();
    bool                   bStartFlying = pStartSnapedSlot == NULL && m_Ends[eFirst]->isMoving();
    bool                   bEndFlying = pEndSnapedSlot == NULL && m_Ends[eSecond]->isMoving();

    qreal start_offset = 60.f;//pStartSlot ? pStartSlot->getOwnerNode()->boundingRect().height() : 0.f;//qAbs(end_pos.x()-start_pos.x())*0.5f;
    qreal end_offset = 60.f;//pEndSlot ? pEndSlot->getOwnerNode()->boundingRect().height() : 0.f;//qAbs(end_pos.y()-start_pos.y())*0.5f;


    if(pStartSlot == pEndSlot && !bStartFlying && ! bEndFlying)
    {
        QPointF vecL(start_dir.x()*cos(M_PI*0.25f)-start_dir.y()*sin(M_PI*0.25f)
            , start_dir.y()*cos(M_PI*0.25f) + start_dir.x()*sin(M_PI*0.25f) );

        QPointF vecR(start_dir.x()*cos(-M_PI*0.25f)-start_dir.y()*sin(-M_PI*0.25f)
            , start_dir.y()*cos(-M_PI*0.25f) + start_dir.x()*sin(-M_PI*0.25f) );

        QPointF mid0 = start_pos+vecL*start_offset;
        QPointF mid1 = start_pos+vecR*end_offset;

        m_Path.cubicTo(mid0, mid1, end_pos);

    }
    else if(pStartSlot 
        && pEndSlot 
        && pStartSlot->getOwnerNode() == pEndSlot->getOwnerNode()
        && !bStartFlying && ! bEndFlying)
    {
        QPointF mid0( start_pos.x() + start_dir.x()*start_offset 
            , start_pos.y() + start_dir.y()*start_offset);
        QPointF mid1( end_pos.x() + end_dir.x()*end_offset
            , end_pos.y() + end_dir.y()*end_offset);

        m_Path.cubicTo(mid0, mid1, end_pos);
    }
    else
    {
        QPointF middle_point = (start_pos+end_pos)*0.5f;

        // start cubic
        QPointF start_potential_third_pos_1(start_pos.x(), middle_point.y()); 
        QPointF start_potential_third_pos_2(middle_point.x(), start_pos.y());

        QVector2D start_dir_to_potential_third_pos_1(start_potential_third_pos_1.x()-start_pos.x(), start_potential_third_pos_1.y()-start_pos.y());
        QVector2D start_dir_to_potential_third_pos_2(start_potential_third_pos_2.x()-start_pos.x(), start_potential_third_pos_2.y()-start_pos.y());

        qreal start_dot1 = QVector2D::dotProduct(start_dir_to_potential_third_pos_1.normalized(), start_dir);
        qreal start_dot2 = QVector2D::dotProduct(start_dir_to_potential_third_pos_2.normalized(), start_dir);

        QPointF start_third_pos;

        if(/*qAbs*/(start_dot1) > /*qAbs*/(start_dot2))
        {
            start_third_pos = start_potential_third_pos_1;
        }
        else
        {
            start_third_pos = start_potential_third_pos_2;
        }

        m_DebugPath.lineTo(start_potential_third_pos_1);
        m_DebugPath.lineTo(start_potential_third_pos_2);
        //m_Path.cubicTo(start_second_pos, start_third_pos, middle_point);

        // end cubic
        QPointF end_potential_third_pos_1(end_pos.x(), middle_point.y()); 
        QPointF end_potential_third_pos_2(middle_point.x(), end_pos.y());

        QVector2D end_dir_to_potential_third_pos_1(end_potential_third_pos_1.x()-end_pos.x(), end_potential_third_pos_1.y()-end_pos.y());
        QVector2D end_dir_to_potential_third_pos_2(end_potential_third_pos_2.x()-end_pos.x(), end_potential_third_pos_2.y()-end_pos.y());

        qreal end_dot1 = QVector2D::dotProduct(end_dir_to_potential_third_pos_1.normalized(), end_dir);
        qreal end_dot2 = QVector2D::dotProduct(end_dir_to_potential_third_pos_2.normalized(), end_dir);

        QPointF end_third_pos;

        if(/*qAbs*/(end_dot1) > /*qAbs*/(end_dot2))
        {
            end_third_pos = end_potential_third_pos_1;
        }
        else
        {
            end_third_pos = end_potential_third_pos_2;
        }

        m_DebugPath.lineTo(middle_point);
        m_DebugPath.lineTo(end_potential_third_pos_1);
        m_DebugPath.lineTo(end_potential_third_pos_2);
        m_DebugPath.lineTo(end_pos);
        m_Path.cubicTo(start_third_pos, end_third_pos, end_pos);
    }

    m_Ends[eFirst]->prepareGeometryChange();
    m_Ends[eSecond]->prepareGeometryChange();

    prepareGeometryChange();
}

QVariant QBlockDiagramLink::itemChange( GraphicsItemChange id, const QVariant& value )
{
  switch(id)
  {
  case QGraphicsItem::ItemSceneChange:
    {
      QGraphicsScene * scn = qVariantValue<QGraphicsScene *>(value);
      if(scene() != NULL) 
      {
        if(m_Ends[eFirst]->getConnectedSlot())
        {
          m_Ends[eFirst]->disconnect();
        }
        if(m_Ends[eSecond]->getConnectedSlot())
        {
          m_Ends[eSecond]->disconnect();
        }
        m_Ends[eFirst]->scene()->removeItem(m_Ends[eFirst]);
        m_Ends[eSecond]->scene()->removeItem(m_Ends[eSecond]);
      }
      if(scn != NULL)
      {
        scn->addItem(m_Ends[eFirst]);
        scn->addItem(m_Ends[eSecond]);
      }
      break;
    }
  }
  return QBlockDiagramItem::itemChange(id, value);
}

void QBlockDiagramLink::terminate()
{
    QBlockDiagramItem::terminate();
    if(m_Ends[eFirst]->getConnectedSlot())
    {
    m_Ends[eFirst]->disconnect();
    }
    if(m_Ends[eSecond]->getConnectedSlot())
    {
    m_Ends[eSecond]->disconnect();
    }
    m_Ends[eFirst]->deferDestruction();
    m_Ends[eSecond]->deferDestruction();
}

bool QBlockDiagramLink::isSnaped() const
{
    return (m_Ends[eFirst]->getSnapedSlot() || m_Ends[eSecond]->getSnapedSlot());
}

bool QBlockDiagramLink::testConnected() const
{
    return m_Ends[eFirst]->getConnectedSlot() && m_Ends[eSecond]->getConnectedSlot();
}

bool QBlockDiagramLink::testSemiConnected() const
{
    return m_Ends[eFirst]->getConnectedSlot() && !m_Ends[eSecond]->getConnectedSlot()
        || !m_Ends[eFirst]->getConnectedSlot() && m_Ends[eSecond]->getConnectedSlot();
}

bool QBlockDiagramLink::hasEndMoving() const
{
    return m_Ends[eFirst]->isMoving() || m_Ends[eSecond]->isMoving();
}

void QBlockDiagramLink::linkEndDestroyed()
{
    if(isValid())
    {
        /*disconnect(m_Ends[eFirst], SIGNAL(moved()), this, SLOT(prepareGeometryChangeSlot()));
        disconnect(m_Ends[eSecond], SIGNAL(moved()), this, SLOT(prepareGeometryChangeSlot()));
        disconnect(m_Ends[eFirst], SIGNAL(parentChanged()), this, SLOT(prepareGeometryChangeSlot()));
        disconnect(m_Ends[eSecond], SIGNAL(parentChanged()), this, SLOT(prepareGeometryChangeSlot()));
        disconnect(m_Ends[eFirst], SIGNAL(destroyed()), this, SLOT(linkEndDestroyed()));
        disconnect(m_Ends[eSecond], SIGNAL(destroyed()), this, SLOT(linkEndDestroyed()));*/
        m_Ends[eFirst] = NULL;
        m_Ends[eSecond] = NULL;
    }
}

void QBlockDiagramLink::updateState()
{
    setConnected(testConnected());
    setSemiConnected(testSemiConnected());
}

void QBlockDiagramLink::setHovered( bool value )
{
    setState(e_State_Hovered, value);
}

void QBlockDiagramLink::setPressed( bool value )
{
    setState(e_State_Pressed, value);
}

void QBlockDiagramLink::setHighlighted( bool value )
{
    setState(e_State_Highlighted, value);
}

void QBlockDiagramLink::setConnected( bool value )
{
    setState(e_State_Connected, value);
}

void QBlockDiagramLink::setSemiConnected( bool value )
{
    setState(e_State_SemiConnected, value);
}

void QBlockDiagramLink::setState( EState state, bool value )
{
    if(value == ((m_States & state) != 0)) return;
    if(value) 
    {
        m_States |= state;
    }
    else 
    {
        m_States &= ~state;
    }
}

class A 
{

};


class B : public A
{

};