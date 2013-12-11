#ifndef QWIDGETSNODESLOTLAYOUT_H
#define QWIDGETSNODESLOTLAYOUT_H

#include "QWidgetsPrerequisites.h"
#include <QObject>
#include <QRectF>

class QBlockDiagramNode;
class QBlockDiagramNodeSlot;

class QWIDGETS_EXPORT QBlockDiagramNodeLayout : public QObject
{
  Q_OBJECT

    friend class QBlockDiagramNode;

public:
    QBlockDiagramNodeLayout();
    ~QBlockDiagramNodeLayout();

    virtual void update(QRectF a_Bounds) = 0;

    virtual void  addSlot(QBlockDiagramNodeSlot* a_pSlot) = 0;

    virtual QBlockDiagramNodeSlot*  slotAt(int i) const = 0;
    virtual int                     count() const = 0;
    virtual QSizeF  sizeHint() const = 0;

protected:
    void setParentNode(QBlockDiagramNode*  a_pParentNode);

protected:
    QBlockDiagramNode*  m_pParentNode;

};

#endif // QWIDGETSNODESLOTLAYOUT_H
