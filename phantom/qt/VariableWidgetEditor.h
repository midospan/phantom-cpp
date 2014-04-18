#ifndef o_qt_VariableWidgetEditor_h__
#define o_qt_VariableWidgetEditor_h__


/* ****************** Includes ******************* */
#include <QtCore/QObject>
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

protected:
    VariableWidgetEditor(QWidget* a_pWidget, const char* signal, reflection::Type* a_pType);

public:
    virtual void setValue(void const* a_pSrc) const = 0;
    virtual void getValue(void* a_pDest) const = 0;

    virtual void setValues(void const** a_ppMultipleSrc) const;
    virtual void getValues(void** a_ppMultipleDest) const;

    QWidget* getWidget() const { return m_pWidget; }

    VariableNode* getVariable() const { return m_pVariableNode; }
    reflection::Type* getType() const { return m_pType; }

    void setVariable(VariableNode* a_pVariable);

protected:
    virtual void variableChanged(VariableNode* a_pVariable);


signals:
    void valueChanged();

protected slots:
    void slotDestroyed();

protected:
    QWidget*                m_pWidget;
    reflection::Type*       m_pType; 
    VariableNode*       m_pVariableNode;
};

}}

#endif // o_qt_VariableWidgetEditor_h__