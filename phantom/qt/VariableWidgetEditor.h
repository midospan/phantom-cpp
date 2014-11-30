#ifndef o_qt_VariableWidgetEditor_h__
#define o_qt_VariableWidgetEditor_h__


/* ****************** Includes ******************* */
#include <QtCore/QObject>
#include <QtCore/QTimer>
/* **************** Declarations ***************** */
class QWidget;
class QtProperty;
o_declareN(class, (phantom, qt), VariableWidgetEditor);
/* *********************************************** */

namespace phantom { namespace qt {

class VariableAction;
class VariableEditor;
class VariableNode;

class o_qt_export VariableWidgetEditor : public QObject
{
    Q_OBJECT

    friend class VariableEditor;

protected:
    VariableWidgetEditor(QWidget* a_pWidget, const char* signal, reflection::Type* a_pValueType);
    VariableWidgetEditor( QWidget* a_pWidget, const char* valueChangedSignal, const char* canceledSignal, reflection::Type* a_pValueType);
public:
    virtual void setValue(void const* a_pSrc) const = 0;
    virtual void getValue(void* a_pDest) const = 0;

    QWidget* getWidget() const { return m_pWidget; }

    reflection::Type* getValueType() const { return m_pValueType; }

signals:
    void valueChanged();
    void canceled();

protected slots:
    void slotDestroyed();
    virtual void opened() {}

protected:
    QWidget*                m_pWidget;
    reflection::Type*       m_pValueType; 
    QTimer                  m_OpenTimer;

private:
    VariableNode*           m_pVariableNode;
};

}}

#endif // o_qt_VariableWidgetEditor_h__