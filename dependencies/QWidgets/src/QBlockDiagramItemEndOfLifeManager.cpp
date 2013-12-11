
#include "QBlockDiagramItemEndOfLifeManager.h"
#include "QBlockDiagramItem.h"
#include "QBlockDiagramModel.h"

QBlockDiagramItemEndOfLifeManager::QBlockDiagramItemEndOfLifeManager()
  : QObject()
{
  m_ItemDeferredDestructionTimer.start(10);
  connect(&m_ItemDeferredDestructionTimer, SIGNAL(timeout()), this, SLOT(handleDeferredItemDestructions()));
}

QBlockDiagramItemEndOfLifeManager::~QBlockDiagramItemEndOfLifeManager()
{

}

void QBlockDiagramItemEndOfLifeManager::handleDeferredItemDestructions()
{
  while(!m_ItemDestructionQueue.empty())
  {
    QBlockDiagramItem* pItem = m_ItemDestructionQueue.front();
    pItem->destroyMe();
    m_ItemDestructionQueue.pop_front();
  }
  while(!m_ItemRemovingQueue.empty())
  {
    QBlockDiagramItem* pItem = m_ItemRemovingQueue.front();
    pItem->terminate();
    if(pItem->scene())
    {
        pItem->scene()->removeItem(pItem);
    }
    m_ItemDestructionQueue.append(pItem);
    m_ItemRemovingQueue.pop_front();
  }
}

QBlockDiagramItemEndOfLifeManager* QBlockDiagramItemEndOfLifeManager::Instance()
{
  static QBlockDiagramItemEndOfLifeManager* s_Instance = new QBlockDiagramItemEndOfLifeManager;
  return s_Instance;
}