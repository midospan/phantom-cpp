#ifndef QWIDGETSLINKEND_H
#define QWIDGETSLINKEND_H

#include "QBlockDiagramConnector.h"
#include <QVector2D>

class QBlockDiagramLink;
class QBlockDiagramNodeSlot;

class QWIDGETS_EXPORT QBlockDiagramLinkEnd : public QBlockDiagramConnector
{
  Q_OBJECT

    friend class QBlockDiagramLink;
    friend class QBlockDiagramNodeSlot;

protected:
    QBlockDiagramLinkEnd(QBlockDiagramLink* a_pOwnerLink);

public:
    ~QBlockDiagramLinkEnd();

    QBlockDiagramLink*  getOwnerLink() const { return m_pOwnerLink; }

    QBlockDiagramLinkEnd*   getTwin() const;

    virtual QRectF  boundingRect() const;
   
    void  connect(QBlockDiagramNodeSlot* a_pSlot);
    void  disconnect();
    virtual bool isLinkEnd() const { return true; }
    virtual void	paint ( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0 );

    virtual void mousePressEvent( QGraphicsSceneMouseEvent * event );
    virtual void mouseMoveEvent( QGraphicsSceneMouseEvent * event );
    virtual void mouseReleaseEvent( QGraphicsSceneMouseEvent * event );

    QBlockDiagramNodeSlot*  getConnectedSlot() const { return m_pConnectedSlot; }
    QBlockDiagramNodeSlot*  getCurrentSlot() const { return m_pSnapedSlot ? m_pSnapedSlot : m_pConnectedSlot; }
    QBlockDiagramNodeSlot*  getSnapedSlot() const { return m_pSnapedSlot; }

    bool                    isMoving() const { return m_bIsMoving; }

    QVector2D       computeDir() const;
    
private:
    QBlockDiagramLink*      m_pOwnerLink;
    QBlockDiagramNodeSlot*  m_pConnectedSlot;
    QBlockDiagramNodeSlot*  m_pSnapedSlot;
    bool                    m_bIsMoving;
    
};

#endif // QWIDGETSLINKCONNECTOR_H
