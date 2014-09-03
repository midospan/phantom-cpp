#ifndef o_qt_CompositionComponentVariableNodeDelegate_h__
#define o_qt_CompositionComponentVariableNodeDelegate_h__

/* ****************** Includes ******************* */
#include <phantom/qt/VariableNodeDelegate.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, qt), CompositionComponentVariableNodeDelegate);
/* *********************************************** */

namespace phantom { namespace qt {
    
class UndoCommand;
class Action;

class o_qt_export CompositionComponentVariableNodeDelegate : public VariableNodeDelegate
{
    Q_OBJECT

public:
    CompositionComponentVariableNodeDelegate(size_t a_uiIndex, size_t a_uiCount) 
        : m_uiIndex(a_uiIndex)
        , m_uiCount(a_uiCount)
    {

    }
    virtual Menu* createMenu() const;
    virtual QWidget* createActionWidget() const;

protected:
    void createActions(vector<Action*>& out) const;
    Menu* createAddMenu() const;

protected slots:
    void slotRemove();
    void slotMoveUp();
    void slotMoveDown();

protected:
    size_t m_uiIndex;
    size_t m_uiCount;
};


}}

#endif // o_qt_CompositionComponentVariableNodeDelegate_h__
