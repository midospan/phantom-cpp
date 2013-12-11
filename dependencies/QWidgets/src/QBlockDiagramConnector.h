#ifndef QWIDGETSCONNECTOR_H
#define QWIDGETSCONNECTOR_H

#include "QBlockDiagramItem.h"

class QWIDGETS_EXPORT QBlockDiagramConnector : public QBlockDiagramItem
{
  Q_OBJECT

public:
    QBlockDiagramConnector();
    QBlockDiagramConnector(const QString& a_strName);
    ~QBlockDiagramConnector();


    virtual void	paint ( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0 ) = 0;

    virtual bool isConnector() const { return true; }
protected:
    
};

#endif // QWIDGETSCONNECTOR_H
