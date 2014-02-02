#ifndef o_qt_VariableAction_h__
#define o_qt_VariableAction_h__

/* ****************** Includes ******************* */
#include <QtGui/QAction>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, qt), VariableAction);
o_declareN(class, (phantom, qt), ResetAction);
o_declareN(class, (phantom, qt), EraseContainerIteratorAction);
o_declareN(class, (phantom, qt), ContainerMoveDownAction);
o_declareN(class, (phantom, qt), ContainerMoveUpAction);
/* *********************************************** */

namespace phantom { namespace qt {

class VariableWidget;
class VariableEditor;
class CollectionElementVariable;
class BufferedVariable;

class o_qt_export VariableAction : public QAction
{
    Q_OBJECT

public:
    VariableAction(const QIcon& a_Icon, const QString& a_Name, BufferedVariable* a_pVariable, VariableWidget* a_pVariableWidget);
    ~VariableAction();
    VariableEditor* getVariableEditor() const;
    BufferedVariable* getVariable() const { return m_pVariable; }

protected slots:
    void slotActionDone();

protected:
    virtual void actionDone() = 0;
    virtual void variableChanged() 
    {

    }

    void valueChanged();
    void valueAboutToBeChanged();

protected:
    BufferedVariable*       m_pVariable;
    VariableWidget* m_pVariableWidget;

};

class o_qt_export ResetAction : public VariableAction
{
public:
    ResetAction(BufferedVariable* a_pVariable, VariableWidget* a_pEditor);

protected:
    virtual void actionDone();
};


class o_qt_export ContainerMoveUpAction : public VariableAction
{
public:
    ContainerMoveUpAction(BufferedVariable* a_pVariable, VariableWidget* a_pVariableWidget);

    virtual void actionDone();

protected:
};

class o_qt_export ContainerMoveDownAction : public VariableAction
{
public:
    ContainerMoveDownAction(BufferedVariable* a_pVariable, VariableWidget* a_pVariableWidget);

    virtual void actionDone();

protected:
};

class o_qt_export EraseContainerIteratorAction : public VariableAction
{
public:
    EraseContainerIteratorAction(BufferedVariable* a_pVariable, VariableWidget* a_pVariableWidget);

    void actionDone();

};

}}

#endif // o_qt_VariableAction_h__
