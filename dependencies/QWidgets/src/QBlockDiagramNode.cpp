
#include "QBlockDiagramNode.h"
#include "QBlockDiagramLink.h"
#include "QBlockDiagramModel.h"
#include "QBlockDiagramNodeSlot.h"
#include "QBlockDiagramNodeLayout.h"
#include <QGraphicsProxyWidget>
#include <QGraphicsRectItem>
#include <QGraphicsSimpleTextItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsProxyWidget>
#include <QPainter>

QBlockDiagramNode::QBlockDiagramNode()
  : m_Size(50.f,50.f)
  , m_PreferredSize(50.f,50.f)
  , m_pLayout(NULL)
  , m_pEmbeddedWidget(NULL)
  , m_BackgroundBrush(QColor(255,255,255,192))
  , m_bHeaderVisible(true)
  
{
    setFlag (QGraphicsItem::ItemIsSelectable);
    m_pHeaderItem = new QGraphicsRectItem;
    m_pHeaderTextItem = new QGraphicsSimpleTextItem;
    m_pHeaderIconItem = new QGraphicsPixmapItem;
    m_pHeaderItem->setParentItem(this);
    m_pHeaderTextItem->setParentItem(m_pHeaderItem);
    m_pHeaderIconItem->setParentItem(m_pHeaderItem);
    m_pHeaderItem->setPen(Qt::NoPen);
}

QBlockDiagramNode::~QBlockDiagramNode()
{
    setHeaderVisible(true);
    if(m_pLayout)
        delete m_pLayout;
    if(m_pEmbeddedWidget)
        delete m_pEmbeddedWidget;
}

void QBlockDiagramNode::paint( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget /*= 0 */ )
{
    QPen pen;
    pen.setWidth(4);
    if(isSelected())
    {
        pen.setColor(QColor(255,255,255));
    }
    else
    {
        pen.setColor(QColor(200,200,200));
    }
    painter->setPen(pen);
    painter->fillRect(4,4,m_Size.width()-8,m_Size.height()-8, m_BackgroundBrush);
    painter->setBrush(m_BackgroundBrush);
    painter->drawRoundedRect(2,2,m_Size.width()-4,m_Size.height()-4,8,8);
}

void QBlockDiagramNode::addSlot( QBlockDiagramNodeSlot* a_pSlot )
{
    Q_ASSERT(std::find(m_Slots.begin(), m_Slots.end(), a_pSlot) == m_Slots.end());
    m_Slots.push_back(a_pSlot);
    a_pSlot->setParentItem(this);
    a_pSlot->m_pOwnerNode = this;
    QObject::connect(this, SIGNAL(moved()), a_pSlot, SIGNAL(moved()));
    QObject::connect(this, SIGNAL(moved()), a_pSlot, SIGNAL(moved()));
    QObject::connect(this, SIGNAL(moved()), a_pSlot, SIGNAL(moved()));
}

void QBlockDiagramNode::removeSlot( QBlockDiagramNodeSlot* a_pSlot )
{
    Q_ASSERT(a_pSlot->m_pOwnerNode == this);
    a_pSlot->disconnectAllLinkEnd();
    m_Slots.erase(std::find(m_Slots.begin(), m_Slots.end(), a_pSlot));
    a_pSlot->setParentItem(NULL);
    a_pSlot->m_pOwnerNode = NULL;
    QObject::disconnect(this, SIGNAL(moved()), a_pSlot, SIGNAL(moved()));
    QObject::disconnect(this, SIGNAL(moved()), a_pSlot, SIGNAL(moved()));
    QObject::disconnect(this, SIGNAL(moved()), a_pSlot, SIGNAL(moved()));
}

void QBlockDiagramNode::removeAllSlots()
{
	while (m_Slots.size() > 0)
	{
		QBlockDiagramNodeSlot* pSlot = m_Slots[0];
		pSlot->disconnectAllLinkEnd();
		m_Slots.erase(std::find(m_Slots.begin(), m_Slots.end(), pSlot));
		pSlot->setParentItem(NULL);
		pSlot->m_pOwnerNode = NULL;
		QObject::disconnect(this, SIGNAL(moved()), pSlot, SIGNAL(moved()));
		QObject::disconnect(this, SIGNAL(moved()), pSlot, SIGNAL(moved()));
		QObject::disconnect(this, SIGNAL(moved()), pSlot, SIGNAL(moved()));
	}
}

QVariant QBlockDiagramNode::itemChange( GraphicsItemChange change, const QVariant & value )
{
  switch(change)
  {
  case ItemSelectedChange:
    setFlag(ItemIsMovable, value.toBool());
    break;
  }
  return QBlockDiagramItem::itemChange(change, value);;
}

void QBlockDiagramNode::setLayout( QBlockDiagramNodeLayout* a_pLayout )
{
    if(a_pLayout)
    {
        Q_ASSERT(m_pLayout == NULL);
        m_pLayout = a_pLayout;
        m_pLayout->setParentNode(this);
        int i = 0;
        int count = a_pLayout->count();
        for(;i<count;++i)
        {
            a_pLayout->slotAt(i)->setParentItem(this);
        }
    }
    else
    {
        Q_ASSERT(m_pLayout != NULL);
        m_pLayout = NULL;
    }
    updateGeometry();
}

void QBlockDiagramNode::updateGeometry()
{
    QSizeF sizeH = sizeHint();
    QSizeF size(qMax(m_PreferredSize.width(), sizeH.width())
    , qMax(m_PreferredSize.height(), sizeH.height()) );
    m_Size = size;
    if(m_pLayout)
    {
        m_pLayout->update(boundingRect());
    }

    if(m_pEmbeddedWidget)
    {
        QSize cb_size = m_pEmbeddedWidget->sizeHint();
        QSizeF this_size = boundingRect().size();
        m_pEmbeddedWidget->setGeometry( this_size.width()/2.f-cb_size.width()/2.f
            , this_size.height()/2.f-cb_size.height()/2.f
            , cb_size.width()
            , cb_size.height());
    }

    QRectF headerRect;
    QRectF thisRect = boundingRect();
    QRectF textRect = m_pHeaderTextItem->boundingRect();
    float headerWidth = 20 + 16 + 10 + textRect.width() + 20;
    headerRect.setRect(0,0,headerWidth, textRect.height()+10);
    m_pHeaderTextItem->setPos(20 + 16 + 10, headerRect.height()/2 - textRect.height()/2);
    m_pHeaderIconItem->setPos(20, headerRect.height()/2 - 8);
    m_pHeaderItem->setPos(thisRect.width()/2 - headerRect.width()/2, - 20 - textRect.height()/2);
    m_pHeaderItem->setRect(headerRect);

    prepareGeometryChangeSlot();
}

QSizeF QBlockDiagramNode::sizeHint() const
{
    QSizeF layoutSize = m_pLayout 
        ? m_pLayout->sizeHint()
        : QSizeF(0,0)
        ;
    QSize widgetSize = m_pEmbeddedWidget 
        ? QSize(m_pEmbeddedWidget->width() + 8, m_pEmbeddedWidget->height() + 8)
        : QSize(0,0)
        ;
    return QSizeF(qMax(m_PreferredSize.width(), qMax((qreal)widgetSize.width(), layoutSize.width()))
        , qMax(m_PreferredSize.height(), qMax((qreal)widgetSize.height(), layoutSize.height())));
}

void QBlockDiagramNode::setEmbeddedWidget( QWidget* a_pEmbeddedWidget, int zValue )
{
    if(m_pEmbeddedWidget)
    {
        m_pGraphicsProxyWidget->setParentItem(NULL);
        m_pGraphicsProxyWidget->setWidget(NULL);
        delete m_pGraphicsProxyWidget;
        m_pGraphicsProxyWidget = NULL;
    }
    m_pEmbeddedWidget = a_pEmbeddedWidget;
    if(m_pEmbeddedWidget)
    {
        m_pGraphicsProxyWidget = new QGraphicsProxyWidget;
        m_pGraphicsProxyWidget->setZValue(zValue);
        m_pGraphicsProxyWidget->setParentItem(this);
        m_pGraphicsProxyWidget->setWidget(m_pEmbeddedWidget);
        m_pEmbeddedWidget->setAttribute(Qt::WA_NoSystemBackground);
    }
    updateGeometry();
}

void QBlockDiagramNode::setEmbeddedWidgetZValue( int zValue )
{
    m_pGraphicsProxyWidget->setZValue(zValue);
}

void QBlockDiagramNode::setHeaderText( const QString& text )
{
    m_pHeaderTextItem->setText(text);
    updateGeometry();
}

void QBlockDiagramNode::setHeaderIcon( const QIcon& icon )
{
    m_pHeaderIconItem->setPixmap(icon.pixmap(16));
    updateGeometry();
}

void QBlockDiagramNode::setHeaderVisible( bool value )
{
    if(m_bHeaderVisible == value) return;
    m_bHeaderVisible = value;
    if(value)
    {
        m_pHeaderItem->setParentItem(nullptr);
    }
    else
    {
        m_pHeaderItem->setParentItem(this);
    }
}

void QBlockDiagramNode::setHeaderBrush( const QBrush& brush )
{
    m_pHeaderItem->setBrush(brush);
}

