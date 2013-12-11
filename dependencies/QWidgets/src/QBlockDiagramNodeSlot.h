#ifndef QWIDGETSNODESLOT_H
#define QWIDGETSNODESLOT_H

#include "QBlockDiagramConnector.h"
#include <QVector2D>

class QBlockDiagramNode;
class QBlockDiagramLink;
class QBlockDiagramLinkEnd;

class QWIDGETS_EXPORT QBlockDiagramNodeSlot : public QBlockDiagramConnector
{
  Q_OBJECT

    friend class QBlockDiagramNode;
    friend class QBlockDiagramLinkEnd;

    class QConnectionNode : public QBlockDiagramItem
    {
    public:
        QConnectionNode()
        {
        }
      QRectF      boundingRect() const { return childrenBoundingRect(); }
      void        paint(QPainter *,const QStyleOptionGraphicsItem *,QWidget *) {}
    protected:

    };

    typedef QPair<QBlockDiagramLinkEnd*, QConnectionNode*> connection_info;
    typedef QVector<connection_info>                       connection_info_vector;

public:
    QBlockDiagramNodeSlot();
    QBlockDiagramNodeSlot(const QString& a_strName);
    ~QBlockDiagramNodeSlot();

    virtual bool    acceptsLinkEnd(QBlockDiagramLinkEnd* a_pLinkEnd) const
    {
        return m_iMaxConnectionCount == -1 || (m_ConnectionInfos.count() < m_iMaxConnectionCount);
    }

    QBlockDiagramNode*      getOwnerNode() const { return m_pOwnerNode; }
    QBlockDiagramLinkEnd*   getConnectedLinkEnd(int i) const { return m_ConnectionInfos.at(i).first; }
    int                     getConnectionCount() const { return m_ConnectionInfos.count(); }

    virtual QRectF          slotBoundingRect() const;
    virtual QRectF          boundingRect() const;
    virtual bool            isNodeSlot() const { return true; }

    void                    hoverEnterEvent(QGraphicsSceneHoverEvent* event);
    void                    hoverLeaveEvent(QGraphicsSceneHoverEvent* event);

    bool                    areConnectionNodesExpanded() const
    {
      return m_bConnectionNodesExpanded;
    }

    bool                    isSlotConnected(QBlockDiagramNodeSlot* a_pSlot) const;

    bool                    isLinkEndConnected(QBlockDiagramLinkEnd* a_pLinkEnd) const 
    {
      connection_info_vector::const_iterator it = m_ConnectionInfos.begin();
      connection_info_vector::const_iterator end = m_ConnectionInfos.end();
      for(;it!=end;++it)
      {
        if((*it).first == a_pLinkEnd)
        {
          return true;
        }
      }
      return false;
    }

    void    expandConnectionNodes();
    void    collapseConnectionNodes();

    void    connectLinkEnd(QBlockDiagramLinkEnd* a_pLinkEnd);
    void    disconnectLinkEnd(QBlockDiagramLinkEnd* a_pLinkEnd);
    void    disconnectAllLinkEnd();

    void    mousePressEvent(QGraphicsSceneMouseEvent* event);
    void    mouseMoveEvent( QGraphicsSceneMouseEvent* event );
    void    mouseReleaseEvent( QGraphicsSceneMouseEvent* event );
    void    paint( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget /*= 0 */ );

    void    setFillColor(QColor color) 
    {
        m_FillColor = color;
    }

    void    setBorderColor(QColor color) 
    {
        m_BorderColor = color;
    }

    void    setMaxConnectionCount(int a_iMaxConnexionCount)
    {
        m_iMaxConnectionCount = a_iMaxConnexionCount;
    }

    void            setText(const QString& text) 
    {
        if(getText() == text) return;
        m_pTextItem->setText(text); 
        emit textChanged(text);
    }
    QString  getText() const { return m_pTextItem->text(); }
    QGraphicsSimpleTextItem* getTextItem() const { return m_pTextItem; }

    bool    isFullyConnected() const;

    void setLinkDirectionAngle(qreal angle)
    {
        m_LinkDirectionAngle = angle;
    }

    qreal getLinkDirectionAngle() const { return m_LinkDirectionAngle; }

protected:
    void    setManipulatedLinkEnd( QBlockDiagramLinkEnd* a_pLinkEnd );
    void    unsetManipulatedLinkEnd( );

signals:
    void    textChanged(const QString& text);
    void    linkEndConnected(QBlockDiagramLinkEnd* a_pLinkEnd);
    void    linkEndAboutToBeDisconnected(QBlockDiagramLinkEnd* a_pLinkEnd);
    void    connected(QBlockDiagramNodeSlot* a_pSlot);
    void    disconnected(QBlockDiagramNodeSlot* a_pSlot);
    void    aboutToBeDisconnected(QBlockDiagramNodeSlot* a_pSlot);

protected:
    QGraphicsSimpleTextItem*m_pTextItem;
    QColor                  m_FillColor;
    QColor                  m_BorderColor;
    QBlockDiagramNode*      m_pOwnerNode;
    QBlockDiagramLinkEnd*   m_pManipulatedLinkEnd;
    connection_info_vector  m_ConnectionInfos;
    int                     m_iMaxConnectionCount;
    bool                    m_bConnectionNodesExpanded;
    qreal                   m_LinkDirectionAngle;
};

#endif // QWIDGETSNODECONNECTOR_H
