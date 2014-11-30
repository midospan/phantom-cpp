#ifndef o_qt_ComponentVariableNodeDelegate_h__
#define o_qt_ComponentVariableNodeDelegate_h__

/* ****************** Includes ******************* */
#include <phantom/qt/VariableNodeDelegate.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, qt), ComponentVariableNodeDelegate);
/* *********************************************** */

namespace phantom { namespace qt {
    
class UndoCommand;
class Action;

class o_qt_export ComponentVariableNodeDelegate : public VariableNodeDelegate
{
    Q_OBJECT

public:
    virtual VariableWidgetEditor* createEditor() const;
    virtual UndoCommand* createValueSetUndoCommand( const void* a_pValue ) const;
    virtual string valueText() const;
};


}}

#endif // o_qt_ComponentVariableNodeDelegate_h__
