/* ******************* Includes ****************** */
#include "phantom/qt/qt.h"
#include "BoolCheckBoxEditor.h"
#include "BoolCheckBoxEditor.hxx"
#include <QPainter>
/* *********************************************** */
o_registerN((phantom, qt), BoolCheckBoxEditor);

namespace phantom { namespace qt {

    BoolCheckBoxEditor::BoolCheckBoxEditor() 
        : VariableWidgetEditor( new BoolCheckImage, SIGNAL(valueChanged(bool)), typeOf<bool>())
    {

    }


    void BoolCheckImage::paintEvent( QPaintEvent * event )
    {
        QPainter painter(this);
        painter.drawPixmap(-8 + height()/2, -8 + height()/2+1, 16, 16, ((m_bValue) ? m_True : m_False).pixmap(16, 16));
        painter.drawText(height()+2, height()/2+7, ((m_bValue) ? "true" : "false"));
    }

    BoolCheckImage::BoolCheckImage() : m_True(":/../../bin/resources/icons/accept.png")
        , m_False(":/../../bin/resources/icons/exclamation.png")
        , m_bValue(false)
    {

    }

    void BoolCheckImage::setValue( bool value )
    {
        if(m_bValue == value) 
            return;
        m_bValue = value;
        update();
        emit valueChanged(value);
    }

    void BoolCheckImage::mousePressEvent( QMouseEvent * event )
    {
        setValue(!getValue());
    }

} // qt 
} // phantom 