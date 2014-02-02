#ifndef phantom_qt_BoolCheckBoxEditor_h__
#define phantom_qt_BoolCheckBoxEditor_h__


/* ****************** Includes ******************* */
#include <phantom/qt/VariableWidgetEditor.h>
#include <qtpropertybrowserutils_p.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, qt), BoolCheckBoxEditor);
/* *********************************************** */

namespace phantom { namespace qt {

    class BoolCheckImage : public QWidget
    {
        Q_OBJECT 

    public:
        BoolCheckImage();

        //virtual QSize sizeHint() const { return QSize(16,16); }

        virtual void paintEvent(QPaintEvent * event);

        void setValue(bool value);

        bool getValue() const { return m_bValue; }

        void mousePressEvent(QMouseEvent * event);

signals:
        void valueChanged(bool);

    protected:

        QIcon m_True;
        QIcon m_False;
        bool m_bValue;
    };

    class o_qt_export BoolCheckBoxEditor : public VariableWidgetEditor
    {
    public:
        BoolCheckBoxEditor();
        virtual void setValue(const void* a_pSrc) const 
        {
            ((BoolCheckImage*)m_pWidget)->setValue(*((bool*)a_pSrc));
        }
        virtual void getValue(void* a_pDest) const 
        {
            *((bool*)a_pDest) = ((BoolCheckImage*)m_pWidget)->getValue();
        }
    };

} // qt 
} // phantom 

#endif // phantom_qt_EnumComboBox_h__
