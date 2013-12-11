#ifndef QWIDGETSLINK_H
#define QWIDGETSLINK_H

#include "QBlockDiagramItem.h"

class QBlockDiagramLinkEnd;
class QBlockDiagramNodeSlot;
class QBlockDiagramModel;

class QWIDGETS_EXPORT QBlockDiagramLink : public QBlockDiagramItem
{
  Q_OBJECT

    friend class QBlockDiagramNodeSlot;
    friend class QBlockDiagramLinkEnd;

public:
  enum EEnd
  {
    eFirst,
    eSecond,
    eCount
  };
  enum EProperty
  {
    destroyOnDisconnectedEnd = 0x1,
  };

public:
    QBlockDiagramLink();
    ~QBlockDiagramLink();

    QBlockDiagramLinkEnd* getEnd(EEnd a_Id) const     {      return m_Ends[a_Id];     }

    virtual void	paint ( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0 );

    virtual QRectF  boundingRect() const;

    virtual bool isLink() const { return true; }

    bool  isDestroyOnDisconnectedEndEnabled() const 
    {
      return (m_Properties & destroyOnDisconnectedEnd) == destroyOnDisconnectedEnd;
    }

    void setDestroyOnDisconnectedEndEnabled(bool value)
    {
      if(value) m_Properties |= destroyOnDisconnectedEnd;
      else m_Properties &= ~destroyOnDisconnectedEnd;
    }

    virtual void terminate();

    QVariant itemChange(GraphicsItemChange id, const QVariant& value);

    bool        isSnaped() const;

    bool        isConnected() const;
    bool        isSemiConnected() const;
    bool        hasEndMoving() const;

    void        setDefaultColor(const QColor& a_Color) { m_DefaultColor = a_Color; }
    void        setConnectColor(const QColor& a_Color) { m_ConnectColor = a_Color; }
    void        setSnapColor(const QColor& a_Color) { m_SnapColor = a_Color; }
    void        setMoveColor(const QColor& a_Color) { m_MoveColor = a_Color; }

    const QColor&        getConnectColor(void) const { return m_ConnectColor ; }
    const QColor&        getSnapColor(void) const { return m_SnapColor ; }
    const QColor&        getMoveColor(void) const { return m_MoveColor ; }
    virtual QColor       getCurrentColor() const;

    QBlockDiagramLinkEnd* getEndTwin(QBlockDiagramLinkEnd const* a_pEnd) const 
    { 
        if(a_pEnd == m_Ends[eFirst])
        {
            return m_Ends[eSecond];
        }
        Q_ASSERT(a_pEnd == m_Ends[eSecond]);
        return m_Ends[eFirst];
    }

protected slots:
    virtual   void  prepareGeometryChangeSlot();
    void            linkEndDestroyed();

protected:
    bool            isValid() const { return m_Ends[eFirst] != NULL && m_Ends[eSecond] != NULL; }

private:
    QColor                  m_DefaultColor;
    QColor                  m_SnapColor;
    QColor                  m_ConnectColor;
    QColor                  m_MoveColor;
    QBlockDiagramLinkEnd*   m_Ends[eCount];
    QPainterPath            m_Path;
    QFlags<EProperty>       m_Properties;
    QPainterPath            m_DebugPath;
    
};

#endif // QWIDGETSLINK_H
