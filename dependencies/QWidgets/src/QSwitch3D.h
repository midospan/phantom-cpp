#ifndef QSwitch3D_h__
#define QSwitch3D_h__

/* ****************** Includes ******************* */
#include "QWidgetsPrerequisites.h"
#include <QTimer>
#include <QWidget>
#include <QImage>
#include <QPainter>
#include <QResizeEvent>
#include <QDockWidget>
#include <QMainWindow>
#include <QGLWidget>
/* **************** Declarations ***************** */

/* *********************************************** */
class QSwitch3D;

class QWIDGETS_EXPORT QSwitchable3D
{
    friend class QSwitch3D;

public:
    QSwitchable3D() : m_bSelected(false), m_pOwner(NULL) {}
    virtual void render(QPainter* painter, QRectF rect) = 0;
    virtual void beforeOpen() {}
    virtual void afterClose() {}
    virtual void resizeEvent(QResizeEvent* event) {}
    bool     isSelected() const { return m_bSelected; }

protected:
    void     setSelected(bool value) { m_bSelected = value; }

protected:
    QSwitch3D*      m_pOwner;

private:
    bool            m_bSelected;
};


class QWIDGETS_EXPORT QImageSwitchable3D : public QSwitchable3D
{
public:
    QImageSwitchable3D(const QImage& image)
        : m_Image(image) {}
    virtual void render(QPainter* painter, QRectF rect) 
    {
        painter->drawImage(rect, m_Image);
    }
    virtual void beforeOpen() {}
    virtual void afterClose() {}
    virtual void resizeEvent(QResizeEvent* event) {}

protected:
    QImage      m_Image;
};

class QWIDGETS_EXPORT QWidgetSwitchable3D : public QSwitchable3D
{
public:
    QWidgetSwitchable3D(QWidget* w)
        : m_pWidget(w) 
    {
        Q_ASSERT(w);
    }

    virtual void render(QPainter* painter, QRectF rect);

    virtual void beforeOpen() {}
    virtual void afterClose() {}
    virtual void resizeEvent(QResizeEvent* event) {}

    QWidget*    getWidget() const { return m_pWidget; }

protected:
    QWidget*      m_pWidget;
};

class QWIDGETS_EXPORT QStaticWidgetSwitchable3D : public QSwitchable3D
{
public:
    QStaticWidgetSwitchable3D(QWidget* w)
        : m_pWidget(w)
        , m_bNeedImageUpdate(false)
    {
        Q_ASSERT(w);
        m_QGLWidgetsToRender = w->findChildren<QGLWidget*>();
    }

    virtual void render(QPainter* painter, QRectF rect);

    virtual void beforeOpen();
    virtual void afterClose();
    virtual void resizeEvent(QResizeEvent* event) 
    { 
        m_bNeedImageUpdate = true; 
        m_ResizeSize = event->size();
    }

    void updateImage()
    {
        if(m_ResizeSize.width() != -1 && m_ResizeSize.height() != -1)
        {
            m_pWidget->resize(m_ResizeSize);
            m_pWidget->parentWidget()->resize(m_ResizeSize);
            m_pWidget->updateGeometry();
            m_StaticImage = QPixmap(m_pWidget->size()/*, QImage::Format_RGB32*/); 
            m_pWidget->render(&m_StaticImage);
            m_bNeedImageUpdate = false;
        }

    }

    QWidget*    getWidget() const { return m_pWidget; }

protected:
    QList<QGLWidget*>   m_QGLWidgetsToRender;
    QList<QDockWidget*> m_FloatingVisibleDockWidgets;
    QPixmap          m_StaticImage;  
    QWidget*        m_pWidget;
    QSize           m_ResizeSize;
    bool            m_bNeedImageUpdate;
};

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

class QWIDGETS_EXPORT QSwitch3D : public QWidget
{
    Q_OBJECT

public:
    enum EState
    {
        e_State_Opened,
        e_State_Closed,
        e_State_AnimatingOpen,
        e_State_AnimatingClose,
        e_State_AnimatingSelect,
    };

public:
    QSwitch3D() 
        : m_CurrentIndex(-1)
        , m_fFov(1.45)
        , m_State(e_State_Closed)
        , m_AnimationElapsedTime(0)
        , m_ClosingRatio(1.f)
        , m_ShiftAngle(0)
        , m_NextIndex(-1)
        , m_ForwardIncrement(0)
        , m_StepAcc(0)
        , m_bCloseRequested(false)
    {
        connect(&m_OpenAnimatorTimer, SIGNAL(timeout()), this, SLOT(updateOpen()));
        connect(&m_CloseAnimatorTimer, SIGNAL(timeout()), this, SLOT(updateClose()));
        connect(&m_SelectAnimatorTimer, SIGNAL(timeout()), this, SLOT(updateSelect()));
        //connect(&m_SelectPreviousAnimatorTimer, SIGNAL(timeout()), this, SLOT(updateSelectPrevious()));
        m_SelectAnimationDuration = 1000;
        m_OpenCloseAnimationDuration = 50;
        setMouseTracking(true);
    }
    ~QSwitch3D() {}

    virtual void resizeEvent(QResizeEvent* event) 
    {  
        QWidget::resizeEvent(event);
        //if(m_State != e_State_Opened) return;
        int i = 0;
        int count = m_Switchable3Ds.size();
        for(;i<count;++i)
        {
            m_Switchable3Ds[i]->resizeEvent(event);
        }  
    }

    void clear() { m_Switchable3Ds.clear(); m_CurrentIndex = m_NextIndex = -1; }

    void addSwitchable3D(QSwitchable3D* s3d)
    {
        Q_ASSERT(m_State == e_State_Closed);
        Q_ASSERT(s3d->m_pOwner == NULL);
        if(m_Switchable3Ds.size() == 0)
        {
            m_CurrentIndex = m_NextIndex = 0;
        }
        m_Switchable3Ds.append(s3d);
        s3d->m_pOwner = this;
    }

    void removeSwitchable3D(QSwitchable3D* s3d)
    {
        Q_ASSERT(m_State == e_State_Closed);
        Q_ASSERT(s3d->m_pOwner == this);
        m_Switchable3Ds.remove(m_Switchable3Ds.indexOf(s3d));
        if(m_Switchable3Ds.size() == 0)
        {
            m_CurrentIndex = m_NextIndex = -1;
        }
        s3d->m_pOwner = NULL;
    }

    void removeSwitchable3D(int i)
    {
        Q_ASSERT(m_State == e_State_Closed);
        m_Switchable3Ds.remove(i);
        if(m_Switchable3Ds.size() == 0)
        {
            m_CurrentIndex = -1;
        }
    }

    QSwitchable3D*  getSwitchable3D(int i) const { return m_Switchable3Ds[i]; }
    int             getSwitchable3DCount() const { return m_Switchable3Ds.size(); }

    int             getIndexFromAngle(float a_fAngle) const 
    {
        int count = m_Switchable3Ds.count();
        float angle = a_fAngle;
        while(angle < 0)
            angle += M_PI*2;
        while(angle > M_PI*2)
            angle -= M_PI*2;
        float fIndex =  count * angle / (2*M_PI);
        int index = int(fIndex);
        if(fIndex > (index+0.5f))
        {
            index = (index+1)%count;
        }
        return index;
    }

    void drawSwitchable3D(QPainter& painter, int i)
    {
        painter.save();
        int count = m_Switchable3Ds.count();
        float angle_div = 2*M_PI / count;
        float fPositionRadius = width()*3.f;
        float fVisibilityRadius = fPositionRadius + width()*0.5f;
        float fCenterPos = fVisibilityRadius / sin(m_fFov);
        float y = (height()*0.5f);
        float angle = angle_div * i - m_fAngle;
        float fDepth = fCenterPos - fPositionRadius*cos(angle);
        float fDepthRatio = 1.f - (fDepth - (fCenterPos - fPositionRadius))/ (2*fPositionRadius); 
        float fInvRealField = 1 / (fDepth * tan(m_fFov) * float(2)) ;
        float fBaseScale = 5.f * width() * fInvRealField;
        float fScale = fBaseScale;

        if(i == m_CurrentIndex)
        {
            painter.setOpacity((1.f+1.f*m_ClosingRatio)*pow(0.4f+0.6f*fDepthRatio,2));
            fScale = fBaseScale + m_ClosingRatio * (1.f - fBaseScale);
        }
        else
        {
            painter.setOpacity((1.f-1.f*m_ClosingRatio)*pow(0.4f+0.6f*fDepthRatio,2));
            fScale = fBaseScale + m_ClosingRatio * (0.001f - fBaseScale);
        }

        float x = width()*float(0.5) - fScale * fPositionRadius*sin(angle) ;

        QSwitchable3D* s3D = m_Switchable3Ds[i];
        float w = width() * fScale;
        float h = height() * fScale;
        QRectF rectF(x - 0.5f*w, y- 0.5f*h, w, h );
        s3D->render(&painter, rectF);
        //painter.drawText(rectF, QString::number(i));
        painter.setPen(QColor(127,127,127));
        painter.drawRect(rectF);
        painter.translate(0,height()+h);
        painter.scale(1,-1);
        painter.setOpacity(0.2f);
        s3D->render(&painter, rectF);
        painter.restore();
    }
    
    void paintEvent(QPaintEvent * event);

    void open(int index)
    {
        Q_ASSERT(index >= 0 && index < m_Switchable3Ds.count());
        Q_ASSERT(m_State == e_State_Closed);
        m_AnimationElapsedTime = 0;
        m_StartTime = GetTickCount();
        m_State = e_State_AnimatingOpen;
        m_CurrentIndex = m_NextIndex = index;
        m_OpenAnimatorTimer.start(0);
        m_ReferenceX = -1;
        m_ReferenceIndex = index;
        int i = 0;
        int count = m_Switchable3Ds.size();
        m_fAngle =  2 * M_PI * float(index) / count;
        for(;i<count;++i)
        {
            m_Switchable3Ds[i]->setSelected(i == m_CurrentIndex);
            m_Switchable3Ds[i]->beforeOpen();
        }

        m_bCloseRequested = false;

        emit openingStarted();
    }

    void open(QSwitchable3D* switchable3D)
    {
        open(m_Switchable3Ds.indexOf(switchable3D));
    }

    void requestClose()
    {
        Q_ASSERT(m_State != e_State_Closed);
        if(m_State == e_State_Opened)
            close();
        else
            m_bCloseRequested = true;
    }

    void close()
    {
        m_AnimationElapsedTime = 0;
        m_StartTime = GetTickCount();
        Q_ASSERT(m_State == e_State_Opened);
        m_State = e_State_AnimatingClose;
        m_CloseAnimatorTimer.start(0);
        emit closingStarted();
    }

    void selectStep(int step)
    {
        Q_ASSERT(m_State == e_State_AnimatingSelect || m_State == e_State_Opened);

        int count = m_Switchable3Ds.count();

        if(step >= count) step = count-1;
        else if(step < -count) step = -count+1;

        //bool changeWay = (m_StepAcc != 0) && ((m_StepAcc < 0) != (step < 0));
        if(((m_StepAcc < 0) != (step < 0)))
        {
            int closestIndex = getIndexFromAngle(m_fAngle);
            m_NextIndex = (closestIndex + step + count) % count;
        }
        else
        {
            m_NextIndex = (m_NextIndex+step+count) % count;
        }
        m_StepAcc = step;

        m_AnimationElapsedTime = 0;
        // normalize
        while(m_fAngle > 2*M_PI)
            m_fAngle -= 2*M_PI;
        while(m_fAngle < 0)
            m_fAngle += 2*M_PI;


        m_fTargetAngle =  2 * M_PI * float(m_NextIndex) / count;

        if(step > 0) // going forward
        {
            if(m_fTargetAngle < m_fAngle)
                m_fAngle -= 2*M_PI;
        }
        else // going backward
        {
            if(m_fTargetAngle > m_fAngle)
                m_fAngle += 2*M_PI;
        }
        m_fSourceAngle = m_fAngle;
        m_fTargetDistance = m_fTargetAngle-m_fAngle;
        m_PrevState = m_State;
        m_State = e_State_AnimatingSelect;
        if(!m_SelectAnimatorTimer.isActive())
        {
            m_StartTime = GetTickCount();
            m_SelectAnimatorTimer.start(0);
        }
    }

    
    void selectNext()
    {
        selectStep(1);
        //m_bRotateForward = true;
    }
    void selectPrevious()
    {
        selectStep(-1);
        //m_bRotateForward = false;
    }
    EState  getState() const {return m_State;}

protected slots:
    void updateOpen()
    {
        unsigned long long currentTime = GetTickCount();
        m_AnimationElapsedTime += (currentTime - m_StartTime);
        if(m_AnimationElapsedTime >= m_OpenCloseAnimationDuration)
        {
            m_State = e_State_Opened;
            m_OpenAnimatorTimer.stop();
            m_ClosingRatio = 0;
            emit openingEnded();
            if(m_bCloseRequested)
                close();
        }
        else
        {
            m_ClosingRatio = 1.f - float(m_AnimationElapsedTime)/m_OpenCloseAnimationDuration;
        }
        m_StartTime = currentTime;
        update();
    }


    void updateClose()
    {
        unsigned long long currentTime = GetTickCount();
        m_AnimationElapsedTime += (currentTime - m_StartTime);
        if(m_AnimationElapsedTime >= m_OpenCloseAnimationDuration)
        {
            m_State = e_State_Closed;
            m_CloseAnimatorTimer.stop();
            m_ClosingRatio = 1.f;
            int i = 0;
            int count = m_Switchable3Ds.size();
            for(;i<count;++i)
            {
                m_Switchable3Ds[i]->afterClose();
                m_Switchable3Ds[i]->setSelected(false);
            }
            emit closingEnded();
        }
        else
        {
            m_ClosingRatio = float(m_AnimationElapsedTime)/m_OpenCloseAnimationDuration;
        }
        m_StartTime = currentTime;
        update();

    }

    void updateSelect()
    {
        unsigned long long currentTime = GetTickCount();
        m_AnimationElapsedTime += (currentTime - m_StartTime);
        if( m_AnimationElapsedTime >= m_SelectAnimationDuration || abs(m_fTargetAngle-m_fAngle) < 0.01f )
        {
            m_SelectAnimatorTimer.stop();
            m_fAngle = m_fTargetAngle;
            m_Switchable3Ds[m_CurrentIndex]->setSelected(false);
            m_CurrentIndex = m_NextIndex;
            m_Switchable3Ds[m_CurrentIndex]->setSelected(true);
            m_State = e_State_Opened;
            m_StepAcc = 0;
            emit selected(m_CurrentIndex);
            if(m_bCloseRequested)
                close();
        }
        else
        {
            float percent = float(m_AnimationElapsedTime)/m_SelectAnimationDuration;
            m_fAngle += (m_fTargetAngle-m_fAngle)*percent;
        }
        m_StartTime = currentTime;
        update();
    }
/*

    void updateSelectPrevious()
    {
        unsigned long long currentTime = GetTickCount();
        m_AnimationElapsedTime += (currentTime - m_StartTime);
        if(m_AnimationElapsedTime >= m_AnimationDuration)
        {
            m_SelectPreviousAnimatorTimer.stop();
            m_ShiftAngle = 0;
            m_Switchable3Ds[m_CurrentIndex]->setSelected(false);
            m_CurrentIndex = m_NextIndex;
            m_Switchable3Ds[m_CurrentIndex]->setSelected(true);
            m_State = m_PrevState;
            emit selected(m_CurrentIndex);
        }
        else
        {
            float percent = float(m_AnimationElapsedTime)/m_AnimationDuration;
            float angle_div = 6.283185f / m_Switchable3Ds.count();
            m_ShiftAngle = -percent * angle_div;
        }
        update();
    }*/


signals:
    void openingStarted();
    void openingEnded();
    void closingStarted();
    void closingEnded();
    void selected(int);

protected:
    QVector<QSwitchable3D*>     m_Switchable3Ds;
    int                         m_CurrentIndex;
    int                         m_NextIndex;
    QTimer                      m_OpenAnimatorTimer;
    QTimer                      m_CloseAnimatorTimer;
    QTimer                      m_SelectAnimatorTimer;
    //QTimer                      m_SelectPreviousAnimatorTimer;
    unsigned int                m_AnimationElapsedTime;
    EState                      m_State;
    unsigned int                m_SelectAnimationDuration;
    unsigned int                m_OpenCloseAnimationDuration;
    float                       m_fFov;
    float                       m_ClosingRatio;
    unsigned long long          m_StartTime;

private:
    float                       m_fAngle;
    float                       m_fSourceAngle;
    float                       m_fTargetAngle;
    float                       m_fTargetDistance;
    int                         m_ReferenceX;
    int                         m_ReferenceIndex;
    EState                      m_PrevState;
    float                       m_ShiftAngle;
    bool                        m_bRotateForward;
    int                         m_ForwardIncrement;
    int                         m_StepAcc;
    bool                        m_bCloseRequested;
};

#endif
