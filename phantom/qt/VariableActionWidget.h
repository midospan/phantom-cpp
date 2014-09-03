#ifndef o_qt_VariableActionWidget_h__
#define o_qt_VariableActionWidget_h__


/* ****************** Includes ******************* */
#include <QtCore/QObject>
/* **************** Declarations ***************** */
class QWidget;
class QtProperty;
o_declareN(class, (phantom, qt), VariableActionWidget);
/* *********************************************** */

namespace phantom { namespace qt {

class VariableAction;
class VariableEditor;
class VariableNode;

class o_qt_export VariableActionWidget : public QObject
{
    Q_OBJECT

protected:
    VariableActionWidget(QWidget* a_pWidget, const char* a_pReeditSignal);

    QWidget* getWidget() const { return m_pWidget; }

    VariableNode* getVariableNode() const { return m_pVariableNode; }

    void setVariableNode(VariableNode* a_pVariableNode);

protected:
    virtual void variableNodeChanged(VariableNode* a_pVariable);

signals:
    void reeditRequested();

protected slots:
    void slotDestroyed();

protected:
    QWidget*                m_pWidget;
    VariableNode*           m_pVariableNode;
};

}}

#endif // o_qt_VariableActionWidget_h__