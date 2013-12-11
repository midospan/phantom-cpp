#include "QSwitch3D.h"

void QSwitch3D::paintEvent( QPaintEvent * event )
{
    QWidget::paintEvent(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    painter.setRenderHint(QPainter::HighQualityAntialiasing);
    int count = m_Switchable3Ds.count();

    float angle = m_fAngle;
    while(angle < 0)
        angle += M_PI*2;
    while(angle > M_PI*2)
        angle -= M_PI*2;
    float fCurrentVisibleIndex =  count * angle / (2*M_PI);
    int currentVisibleIndex = int(fCurrentVisibleIndex);
    if(fCurrentVisibleIndex > (currentVisibleIndex+0.5f))
    {
        currentVisibleIndex = (currentVisibleIndex+1)%count;
    }
    int i = (currentVisibleIndex + count/2) % count; // opposite to current index
    for(;i != currentVisibleIndex;i = (i+1)%count)
    {
        drawSwitchable3D(painter, i);
    }
    i = (currentVisibleIndex + count/2) % count; 
    for(;i != currentVisibleIndex;i = (i + count - 1)%count)
    {
        drawSwitchable3D(painter, i);
    }
    drawSwitchable3D(painter, currentVisibleIndex);
}

void QWidgetSwitchable3D::render( QPainter* painter, QRectF rect )
{
    m_pWidget->resize(rect.width(), rect.height());
    QImage image(m_pWidget->size(), QImage::Format_RGB32);
    m_pWidget->render(&image);
    painter->drawImage(rect, image);
}

void QStaticWidgetSwitchable3D::beforeOpen()
{
    m_StaticImage = QPixmap(m_pWidget->size()/*, QImage::Format_RGB32*/);
    if(!m_pWidget->isVisible())
    {
        m_pWidget->show();
        m_pWidget->hide();
    }
    m_pWidget->render(&m_StaticImage);
    m_pOwner->setFocus();
    /*QGLWidget* qgl = NULL;
    Q_FOREACH(qgl, m_QGLWidgetsToRender)
    {
    if(qgl->isVisible())
    {
    QWidget* parent = (QWidget*)m_pOwner;
    QPoint screenQGLCoords = qgl->mapTo(m_pWidget, QPoint(0,0));
    float w = float(qgl->width());
    float h = float(qgl->height());
    QRectF glRectF(0,0,w,h);
    QPainter painter(&m_StaticImage);
    painter.drawImage(glRectF, qgl->grabFrameBuffer(true));
    }
    }*/

    if(m_pWidget->inherits("QMainWindow"))
    {
        QMainWindow* pMainWindow = (QMainWindow*)m_pWidget;
        QList<QDockWidget*> docks = pMainWindow->findChildren<QDockWidget*>();
        QDockWidget* dock = NULL;
        Q_FOREACH(dock, docks)
        {
            if(dock->isFloating() && !dock->isHidden())
            {
                if(!m_FloatingVisibleDockWidgets.contains(dock))
                {
                    m_FloatingVisibleDockWidgets.append(dock);
                    dock->setVisible(false);
                }
            }
        }
    }
}

void QStaticWidgetSwitchable3D::render( QPainter* painter, QRectF rect )
{
    if(m_bNeedImageUpdate)
    {
        updateImage();
    }
    painter->drawPixmap(rect, m_StaticImage, m_StaticImage.rect());
}

void QStaticWidgetSwitchable3D::afterClose()
{
    if(isSelected())
    {
        QDockWidget* dock = NULL;
        Q_FOREACH(dock, m_FloatingVisibleDockWidgets)
        {
            dock->setVisible(true);
        }
        m_FloatingVisibleDockWidgets.clear();
    }
}
