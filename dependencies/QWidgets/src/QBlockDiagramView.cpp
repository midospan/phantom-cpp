
#include "QBlockDiagramView.h"
#include <qpainter>
#include <QWheelEvent>

QBlockDiagramView::QBlockDiagramView(QWidget *parent)
    : QGraphicsView(parent)
    , m_fZoom(1)
    , m_GrabScenePos(-1,-1)
{
  setRenderHint(QPainter::Antialiasing, true);
}

QBlockDiagramView::~QBlockDiagramView()
{

}

void QBlockDiagramView::wheelEvent( QWheelEvent *event )
{
  QGraphicsView::wheelEvent( event );
  int numDegrees = event->delta() / 8;
  int numSteps = numDegrees / 15;
  m_fZoom += numSteps*0.05f;
  if(m_fZoom < 0.05f) m_fZoom = 0.05f;
  if(m_fZoom > 10.f) m_fZoom = 10.f;	
  resetTransform ();
  scale(m_fZoom,m_fZoom);
}

void QBlockDiagramView::mousePressEvent( QMouseEvent *event )
{
  QGraphicsView::mousePressEvent(event);
  if(event->buttons() & Qt::MidButton)
  {
    m_GrabScenePos = mapToScene(event->pos());
  }
}

void QBlockDiagramView::mouseMoveEvent( QMouseEvent *event )
{
  QGraphicsView::mouseMoveEvent(event);
  if(event->buttons() & Qt::MidButton)
  {
    centerOn( mapToScene(event->pos())  ); 
  }
}