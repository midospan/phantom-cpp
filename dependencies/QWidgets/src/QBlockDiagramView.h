#ifndef QWIDGETSVIEW_H
#define QWIDGETSVIEW_H

#include "QWidgetsPrerequisites.h"
#include <QGraphicsView>

class QWIDGETS_EXPORT QBlockDiagramView : public QGraphicsView
{
    Q_OBJECT

public:
    QBlockDiagramView(QWidget *parent = 0);
    ~QBlockDiagramView();


    void wheelEvent( QWheelEvent *event );
    void mouseMoveEvent( QMouseEvent *event );
    void mousePressEvent( QMouseEvent *event );

private:
  float   m_fZoom;
  QPointF  m_GrabScenePos;

};

#endif // QWIDGETSVIEW_H
