#ifndef o_phantom_qt_UndoCommandContainer_h__
#define o_phantom_qt_UndoCommandContainer_h__


/* ****************** Includes ******************* */
#include <phantom/qt/qt.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, qt), UndoCommandContainer);
o_fwd(class, phantom, qt, UndoStack);
o_fwd(class, phantom, qt, UndoGroup);
/* *********************************************** */

o_namespace_begin(phantom, qt)

class o_qt_export UndoCommandContainer
{
public:
	UndoCommandContainer(void) {}
	~UndoCommandContainer(void) {}

    virtual UndoStack* asStack() const { return nullptr; }
    virtual UndoGroup* asGroup() const { return nullptr; }

    virtual void pushCommand(UndoCommand* command) = 0;
    virtual void popCommand(UndoCommand* command) = 0;

public:
    virtual UndoStack*	getUndoStack() const = 0;

protected:
    o_signal(undoCommandAboutToBeRemoved, UndoCommand*);
    o_signal(undoCommandAdded, UndoCommand*);
};

o_namespace_end(phantom, qt)

#endif // o_phantom_qt_UndoCommandContainer_h__
