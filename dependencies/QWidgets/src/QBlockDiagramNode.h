#ifndef QWIDGETSNODE_H
#define QWIDGETSNODE_H

#include "QBlockDiagramItem.h"
#include <QMap>
#include <QComboBox>

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

    void setBackgroundBrush(const QBrush& brush) { m_BackgroundBrush = brush; }
    void setHeaderBrush(const QBrush& brush);

    QGraphicsRectItem* getHeaderItem() const { return m_pHeaderItem; }
    QGraphicsSimpleTextItem* getHeaderTextItem() const { return m_pHeaderTextItem; }
    QGraphicsPixmapItem* getHeaderIconItem() const { return m_pHeaderIconItem; }

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
    QBrush                      m_BackgroundBrush;
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
