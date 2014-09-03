#ifndef QWIDGETSNODE_H
#define QWIDGETSNODE_H

#include "QBlockDiagramItem.h"
#include <QMap>
#include <QComboBox>
#include <QPen>

class QBlockDiagramNodeSlot;
class QBlockDiagramNodeLayout;

enum QBlockDiagramNodeFlag
{
    AutoGenerateLink = 0x1,
};

typedef  QFlags<QBlockDiagramNodeFlag> QBlockDiagramNodeFlags;

class QWidget;
class QGraphicsProxyWidget;
class QGraphicsRectItem;
class QGraphicsSimpleTextItem;
class QGraphicsPixmapItem;

class QWIDGETS_EXPORT QBlockDiagramNode : public QBlockDiagramItem
{
    Q_OBJECT

    typedef QVector<QBlockDiagramNodeSlot*> SlotContainer;

public:
    enum EState
    {
        e_State_Default = 0x0,
        e_State_Selected = 0x1,
        e_State_Highlighted = 0x2,
        e_State_Hovered = 0x4,
        e_State_Pressed = 0x8,
        e_State_Preselected = 0x10,
        e_State_Invalid = 0x20,
        e_State_Customized = 0x40,
    };

public:
    QBlockDiagramNode();
    ~QBlockDiagramNode();

    virtual void	paint ( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0 );

    void setHeaderText(const QString& text);

    void setHeaderIcon(const QIcon& icon);

    void setHeaderVisible(bool value);

    virtual QRectF  boundingRect() const 
    {
      qreal penWidth = 1;
      return QRectF(0, 0, m_Size.width(), m_Size.height());
    }

    virtual bool    isNode() const { return true; }

    QVariant        itemChange ( GraphicsItemChange change, const QVariant & value );

    void            addSlot(QBlockDiagramNodeSlot* a_pSlot);
    void            removeSlot(QBlockDiagramNodeSlot* a_pSlot);
	virtual void    removeAllSlots();
    QVector2D       computeSlotDir(QBlockDiagramNodeSlot* a_pSlot) const;

    void            setLayout(QBlockDiagramNodeLayout* a_pLayout);

    void            updateGeometry();

    void            setNodeFlag(QBlockDiagramNodeFlag a_Flag, bool value = true)
    {
        if(value)
            m_NodeFlags |= a_Flag;
        else
            m_NodeFlags &= ~a_Flag;
    }

    QBlockDiagramNodeFlags  nodeFlags() const { return m_NodeFlags; }
    
    virtual QSizeF               sizeHint() const;

    void    setEmbeddedWidget(QWidget* a_pEmbeddedWidget, int zValue = 100000);
    void    setEmbeddedWidgetZValue(int zValue);

    void setStatePen(EState state, const QPen& pen) { m_Pens[state] = pen; }
    void setStateBrush(EState state, const QBrush& brush) { m_Brushes[state] = brush; }
    void setHeaderBrush(const QBrush& brush);

    QGraphicsRectItem* getHeaderItem() const { return m_pHeaderItem; }
    QGraphicsSimpleTextItem* getHeaderTextItem() const { return m_pHeaderTextItem; }
    QGraphicsPixmapItem* getHeaderIconItem() const { return m_pHeaderIconItem; }

    bool isPreselected() const { return (m_States & e_State_Preselected) != 0; }
    void setPreselected(bool value); // used by selection rectangle;

    bool isHovered() const { return (m_States & e_State_Hovered) != 0; }
    void setHovered(bool value);

    bool isPressed() const { return (m_States & e_State_Pressed) != 0; }
    void setPressed(bool value);

    bool isCustomized() const { return (m_States & e_State_Customized) != 0; }
    void setCustomized(bool value);

    bool isInvalid() const { return (m_States & e_State_Invalid) != 0; }
    void setInvalid(bool value);

    bool isHighlighted() const { return (m_States & e_State_Highlighted) != 0; }
    void setHighlighted(bool value);

    void setState(EState state, bool value);

protected:
    EState dominantPenState() const 
    {
        EState majorState = e_State_Invalid;
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
        EState majorState = e_State_Invalid;
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

protected:
    virtual void selected() 
    {
        setState(e_State_Selected, true);
    }
    virtual void deselected() 
    {
        setState(e_State_Selected, false);
    }

private:
    QBlockDiagramNodeFlags      m_NodeFlags;
    QGraphicsRectItem*          m_pHeaderItem;
    QGraphicsPixmapItem*        m_pHeaderIconItem;
    QGraphicsSimpleTextItem*    m_pHeaderTextItem;
    SlotContainer               m_Slots;
    QSizeF                      m_PreferredSize;
    QSizeF                      m_Size;
    QBlockDiagramNodeLayout*    m_pLayout;
    QGraphicsProxyWidget*       m_pGraphicsProxyWidget;
    QWidget*                    m_pEmbeddedWidget;
    QMap<EState, QBrush>        m_Brushes;
    QMap<EState, QPen>          m_Pens;
    int                         m_States;
    bool                        m_bHeaderVisible;

    
};

class QWIDGETS_EXPORT QBlockDiagramComboBox : public QComboBox
{
    Q_OBJECT

public:
    QBlockDiagramComboBox(QBlockDiagramNode* a_pNode)
        : m_pNode(a_pNode)
    {
        connect(this, SIGNAL(activated(int)), this, SLOT(popupClosed(int)));
    }

    virtual void showPopup()
    {
        m_pNode->setEmbeddedWidgetZValue(100000); // ensure popup is on top of everything
        QComboBox::showPopup();
    }

    protected slots:
        void popupClosed(int)
        {
            m_pNode->setEmbeddedWidgetZValue(-100000); // ensure popup is on top of everything
        }

protected:
    QBlockDiagramNode*  m_pNode;

};
#endif // QWIDGETSNODE_H
