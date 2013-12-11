#ifndef o_qt_VariableAction_h__
#define o_qt_VariableAction_h__

/* ****************** Includes ******************* */
#include <QtGui/QAction>
/* **************** Declarations ***************** */

namespace phantom { namespace qt {

class VariableWidget;
class VariableEditor;
class CollectionElementVariable;

class o_qt_export VariableAction : public QAction
{
    Q_OBJECT

public:
    VariableAction(const QIcon& a_Icon, const QString& a_Name, reflection::Variable* a_pVariable, VariableWidget* a_pVariableWidget);
    ~VariableAction();
    VariableEditor* getVariableEditor() const;
    reflection::Variable*       getVariable() const { return m_pVariable; }

protected slots:
    void slotActionDone();

signals:
    void done();

protected:
    virtual void actionDone() = 0;
    virtual void variableChanged() 
    {

    }

    void valueChanged();
    void valueAboutToBeChanged();

protected:
    reflection::Variable*       m_pVariable;
    VariableWidget* m_pVariableWidget;

};

class o_qt_export ResetAction : public VariableAction
{
public:
    ResetAction(reflection::Variable* a_pVariable, VariableWidget* a_pEditor);

protected:
    virtual void actionDone();
};


class o_qt_export ContainerMoveUpAction : public VariableAction
{
public:
    ContainerMoveUpAction(CollectionElementVariable* a_pVariable, VariableWidget* a_pVariableWidget);

    virtual void actionDone();

protected:
};

class o_qt_export ContainerMoveDownAction : public VariableAction
{
public:
    ContainerMoveDownAction(CollectionElementVariable* a_pVariable, VariableWidget* a_pVariableWidget);

    virtual void actionDone();

protected:
};

class o_qt_export EraseContainerIteratorAction : public VariableAction
{
public:
    EraseContainerIteratorAction(phantom::reflection::IteratorVariable* a_pVariable, VariableWidget* a_pVariableWidget);

    void actionDone();

};

}}


o_classN((phantom, qt), VariableAction, o_no_copy)
{
    o_reflection
    {

    };
};
o_exposeN((phantom, qt), VariableAction);




o_classNS((phantom, qt), EraseContainerIteratorAction, (VariableAction), o_no_copy)
{
    o_reflection
    {

    };
};
o_exposeN((phantom, qt), EraseContainerIteratorAction);

o_classNS((phantom, qt), ResetAction, (VariableAction), o_no_copy)
{
    o_reflection
    {

    };
};
o_exposeN((phantom, qt), ResetAction);

o_classNS((phantom, qt), ContainerMoveDownAction, (VariableAction), o_no_copy)
{
    o_reflection
    {

    };
};
o_exposeN((phantom, qt), ContainerMoveDownAction);

o_classNS((phantom, qt), ContainerMoveUpAction, (VariableAction), o_no_copy)
{
    o_reflection
    {

    };
};
o_exposeN((phantom, qt), ContainerMoveUpAction);




#endif // o_qt_VariableAction_h__
