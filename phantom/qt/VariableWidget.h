#ifndef o_qt_VariableWidget_h__
#define o_qt_VariableWidget_h__


/* ****************** Includes ******************* */
#include <QtGui/QLabel>
#include <QtGui/QToolButton>
#include <QtGui/QPushButton>
#include <QtGui/QHBoxLayout>
/* **************** Declarations ***************** */
class QWidget;
class QtProperty;
/* *********************************************** */

namespace phantom { namespace qt {

class VariableAction;
class VariableEditor;
class VariableWidgetEditor;

class o_qt_export VariableWidget : public QWidget
{
    Q_OBJECT

public:
    VariableWidget(VariableWidgetEditor* a_pVariableWidgetEditor, VariableEditor* a_pVariableEditor);
    ~VariableWidget();

    VariableWidgetEditor* getVariableWidgetEditor() const { return m_pVariableWidgetEditor; }

    reflection::Variable* getVariable() const { return m_pVariable; }

    void setVariable(reflection::Variable* a_pVariable);

    void addVariableAction(VariableAction* a_pAction);

    VariableEditor* getVariableEditor() const { return m_pVariableEditor; }

    void setVariableEditor(VariableEditor* a_pVariableEditor)
    {
        m_pVariableEditor = a_pVariableEditor;
    }

protected:
    void rebuildLayout();

signals:
    void valueChanged();

protected:
    reflection::Variable*   m_pVariable;
    VariableEditor*         m_pVariableEditor;
    VariableWidgetEditor*   m_pVariableWidgetEditor;
    QVector<VariableAction*>m_Actions;
};

}}

#endif // o_qt_VariableWidget_h__