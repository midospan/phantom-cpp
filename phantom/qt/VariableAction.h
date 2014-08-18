#ifndef o_qt_VariableAction_h__
#define o_qt_VariableAction_h__

/* ****************** Includes ******************* */
#include <QtGui/QAction>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, qt), VariableAction);
/* *********************************************** */

namespace phantom { namespace qt {

class VariableEditor;
class CollectionElementVariable;
class VariableNode;

enum EVariableActionLayout
{
    e_VariableActionLayout_Button,
    e_VariableActionLayout_Menu,
};

class o_qt_export VariableAction : public QAction
{
    friend class VariableNode;

public:
    VariableAction(const QIcon& a_Icon, const QString& a_Name, EVariableActionLayout a_Layout, VariableNode* a_pVariableNode, VariableEditor* a_pVariableEditor);
    ~VariableAction();

    VariableNode*   getVariableNode() const { return m_pVariableNode; }
    VariableEditor* getVariableEditor() const;

protected:
    virtual void doNow();

    o_signal_data(actionAboutToBeDone);
    o_signal_data(actionDone);

public slots:
    void slotTriggered();

protected:
    VariableNode*           m_pVariableNode;
    EVariableActionLayout   m_Layout;
};
/*

class o_qt_export ResetAction : public VariableAction
{
public:
    ResetAction();

protected:
    virtual void actionDone();
};
*/

}}

#endif // o_qt_VariableAction_h__
