#ifndef o_qt_AggregationVariableNodeDelegate_h__
#define o_qt_AggregationVariableNodeDelegate_h__

/* ****************** Includes ******************* */
#include <phantom/qt/VariableNodeDelegate.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, qt), AggregationVariableNodeDelegate);
/* *********************************************** */

namespace phantom { namespace qt {
    
class UndoCommand;
class Action;

class o_qt_export AggregationVariableNodeDelegate : public VariableNodeDelegate
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

#endif // o_qt_AggregationVariableNodeDelegate_h__
