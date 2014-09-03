#ifndef o_qt_CompositionVariableNodeDelegate_h__
#define o_qt_CompositionVariableNodeDelegate_h__

/* ****************** Includes ******************* */
#include <phantom/qt/VariableNodeDelegate.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, qt), CompositionVariableNodeDelegate);
/* *********************************************** */

namespace phantom { namespace qt {
    
class UndoCommand;
class Action;

class o_qt_export CompositionVariableNodeDelegate : public VariableNodeDelegate
{
    Q_OBJECT

public:
    virtual Menu* createMenu() const;
    virtual QWidget* createActionWidget() const;

protected:
    void createActions(vector<Action*>& out) const;
    Menu* createAddMenu() const;

protected slots:
    void popupAddRequested();

};


}}

#endif // o_qt_CompositionVariableNodeDelegate_h__
