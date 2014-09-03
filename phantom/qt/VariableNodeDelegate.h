#ifndef o_qt_VariableNodeDelegate_h__
#define o_qt_VariableNodeDelegate_h__

/* ****************** Includes ******************* */
#include <phantom/qt/qt.h>
#include <QWidget>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, qt), VariableNodeDelegate);
/* *********************************************** */

namespace phantom { namespace qt {
    
class UndoCommand;
class VariableNode;
class VariableWidgetEditor;
class VariableActionWidget;
class Menu;

class o_qt_export VariableNodeDelegate : public QObject
{
    friend class VariableNode;

    Q_OBJECT

public:
    VariableNodeDelegate() : m_pVariableNode(nullptr) {}

    virtual UndoCommand*            createValueSetUndoCommand(const void* a_pValue) const;
    virtual Menu*                   createMenu() const { return nullptr; }
    virtual VariableWidgetEditor*   createEditor() const;
    virtual string                  valueText() const;
    virtual QIcon                   valueIcon() const;
    virtual QWidget*                createActionWidget() const { return nullptr; }

protected slots:
    void invalidateNode();

protected:
    VariableNode* m_pVariableNode;
};


}}

#endif // o_qt_VariableNodeDelegate_h__
