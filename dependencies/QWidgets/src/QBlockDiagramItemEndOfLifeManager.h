#ifndef QWIDGETSITEMENDOFLIFEMANAGER_H
#define QWIDGETSITEMENDOFLIFEMANAGER_H

#include "QWidgetsPrerequisites.h"
#include <QObject>
#include <QTimer>

class QBlockDiagramItem;

class QWIDGETS_EXPORT QBlockDiagramItemEndOfLifeManager : public QObject
{
  Q_OBJECT

    QBlockDiagramItemEndOfLifeManager();
public:
    ~QBlockDiagramItemEndOfLifeManager();
    static QBlockDiagramItemEndOfLifeManager* Instance();

  void deferItemDestruction(QBlockDiagramItem* a_pItem)
  {
    Q_ASSERT(!m_ItemRemovingQueue.contains(a_pItem));
    Q_ASSERT(!m_ItemDestructionQueue.contains(a_pItem));
    m_ItemRemovingQueue.append(a_pItem);
  }

protected slots:
    void handleDeferredItemDestructions();

private:
  QTimer                    m_ItemDeferredDestructionTimer;
  QList<QBlockDiagramItem*> m_ItemRemovingQueue;
  QList<QBlockDiagramItem*> m_ItemDestructionQueue;
    
};

#endif // QWIDGETSITEMENDOFLIFEMANAGER_H
