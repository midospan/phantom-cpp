
#include "QBlockDiagramItem.h"
#include "QBlockDiagramModel.h"
#include "QBlockDiagramItemEndOfLifeManager.h"

QBlockDiagramItem::QBlockDiagramItem()
  : QGraphicsObject()
  , m_pUserData(NULL)
{
  QObject::connect(this, SIGNAL(xChanged()), this, SIGNAL(moved()));
  QObject::connect(this, SIGNAL(yChanged()), this, SIGNAL(moved()));
  QObject::connect(this, SIGNAL(zChanged()), this, SIGNAL(moved()));
}

QBlockDiagramItem::QBlockDiagramItem(const QString& a_strName)
  : QGraphicsObject()
  , m_strName(a_strName)
  , m_pUserData(NULL)
{
  QObject::connect(this, SIGNAL(xChanged()), this, SIGNAL(moved()));
  QObject::connect(this, SIGNAL(yChanged()), this, SIGNAL(moved()));
  QObject::connect(this, SIGNAL(zChanged()), this, SIGNAL(moved()));
}

QBlockDiagramItem::~QBlockDiagramItem()
{

}

QBlockDiagramModel* QBlockDiagramItem::scene() const
{
  return static_cast<QBlockDiagramModel*>(QGraphicsObject::scene());
}

void QBlockDiagramItem::deferDestruction()
{
  QBlockDiagramItemEndOfLifeManager::Instance()->deferItemDestruction(this);
}