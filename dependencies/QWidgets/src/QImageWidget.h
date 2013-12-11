#ifndef QImageWidget_h__
#define QImageWidget_h__


/* ****************** Includes ******************* */
#include <QWidget>
#include <QPainter>
#include <QImage>
#include <QResizeEvent>
/* **************** Declarations ***************** */

/* *********************************************** */

class QImageWidget : public QWidget
{
public:
	QImageWidget(QWidget* parent = 0) : QWidget(parent) { setAutoFillBackground(false); }
	~QImageWidget(void) {}

    QSize   sizeHint() const { return m_Image.size(); }

    void    setImage(QImage a_Image)
    {
        m_Image = a_Image;
        m_ScaledImage = m_Image.scaled(size(), Qt::KeepAspectRatio);
    }

    void paintEvent(QPaintEvent* event)
    {
        QPainter painter(this);
        int w = m_ScaledImage.width();
        int h = m_ScaledImage.height();
        int x = width()/2.f - w/2.f;
        int y = height()/2.f - h/2.f;
        painter.drawImage(x, y, m_ScaledImage);
    }

    void resizeEvent(QResizeEvent* event)
    {
        m_ScaledImage = m_Image.scaled(event->size(), Qt::KeepAspectRatio);
    }

protected:
    QImage  m_Image;
    QImage  m_ScaledImage;

};



#endif // QImageWidget_h__
