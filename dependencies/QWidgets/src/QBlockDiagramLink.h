#ifndef QWIDGETSLINK_H
#define QWIDGETSLINK_H

#include "QBlockDiagramItem.h"
#include <QPen>
#include <QBrush>

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

    enum EState
    {
        e_State_Default = 0x0,
        e_State_SemiConnected = 0x1,
        e_State_Connected = 0x2,
        e_State_Highlighted = 0x4,
        e_State_Hovered = 0x8,
        e_State_Pressed = 0x10,
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

    bool        testConnected() const;
    bool        testSemiConnected() const;
    bool        hasEndMoving() const;

    void        setStatePen(EState state, const QPen& pen) { m_Pens[state] = pen; }
    void        setStateBrush(EState state, const QBrush& brush) { m_Brushes[state] = brush; }

    bool isHovered() const { return (m_States & e_State_Hovered) != 0; }
    void setHovered(bool value);

    bool isPressed() const { return (m_States & e_State_Pressed) != 0; }
    void setPressed(bool value);

    bool isSemiConnected() const { return (m_States & e_State_SemiConnected) != 0; }
    void setSemiConnected(bool value);

    bool isConnected() const { return (m_States & e_State_Connected) != 0; }
    void setConnected(bool value);

    bool isHighlighted() const { return (m_States & e_State_Highlighted) != 0; }
    void setHighlighted(bool value);

    void setState(EState state, bool value);

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
    void            updateState();
protected:
    EState dominantPenState() const 
    {
        EState majorState = e_State_Pressed;
        while(majorState)
        {
            if(m_States & majorState)
            {
                if(m_Pens.find(majorState) != m_Pens.end())
                    return majorState;
            }
            majorState = (EState)(majorState >> 1);
        }
        return majorState;
    }
    EState dominantBrushState() const 
    {
        EState majorState = e_State_Pressed;
        while(majorState)
        {
            if(m_States & majorState)
            {
                if(m_Brushes.find(majorState) != m_Brushes.end())
                    return majorState;
            }
            majorState = (EState)(majorState >> 1);
        }
        return majorState;
    }

private:
    QColor                  m_DefaultColor;
    QColor                  m_SnapColor;
    QColor                  m_ConnectColor;
    QColor                  m_MoveColor;
    QMap<EState, QBrush>    m_Brushes;
    QMap<EState, QPen>      m_Pens;
    int                     m_States;
    QBlockDiagramLinkEnd*   m_Ends[eCount];
    QPainterPath            m_Path;
    QFlags<EProperty>       m_Properties;
    QPainterPath            m_DebugPath;
    
};

#endif // QWIDGETSLINK_H
