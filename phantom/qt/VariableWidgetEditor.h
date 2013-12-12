#ifndef o_qt_VariableWidgetEditor_h__
#define o_qt_VariableWidgetEditor_h__


/* ****************** Includes ******************* */
#include <QtCore/QObject>
/* **************** Declarations ***************** */
class QWidget;
class QtProperty;
/* *********************************************** */

namespace phantom { namespace qt {

class VariableAction;
class VariableEditor;
class BufferedVariable;

class o_qt_export VariableWidgetEditor : public QObject
{
    Q_OBJECT

protected:
    VariableWidgetEditor(QWidget* a_pWidget, const char* signal, reflection::Type* a_pType);

public:
    virtual void setValue(const void* a_pSrc) const = 0;
    virtual void getValue(void* a_pDest) const = 0;

    QWidget* getWidget() const { return m_pWidget; }

    BufferedVariable* getVariable() const { return m_pVariable; }
    reflection::Type* getType() const { return m_pType; }

    void setVariable(BufferedVariable* a_pVariable);

protected:
    virtual void variableChanged(BufferedVariable* a_pVariable);


signals:
    void valueChanged();

protected slots:
    void slotDestroyed();

protected:
    QWidget*                m_pWidget;
    reflection::Type*       m_pType; 
    BufferedVariable*       m_pVariable;
};

}}

o_classN((phantom, qt), VariableWidgetEditor, o_no_copy)
{
    o_reflection
    {
    };
};
o_exposeN((phantom, qt), VariableWidgetEditor);

#endif // o_qt_VariableWidgetEditor_h__