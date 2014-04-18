#ifndef o_phantom_qt_UndoCommand_h__
#define o_phantom_qt_UndoCommand_h__


/* ****************** Includes ******************* */
#include <phantom/qt/qt.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, qt), UndoCommand);
/* *********************************************** */

o_namespace_begin(phantom, qt)

class o_qt_export UndoCommand
{
public:
	UndoCommand(void) {}
	~UndoCommand(void) {}
	
    virtual void undo() = 0;
    virtual void redo() = 0;

protected:

};

o_namespace_end(phantom, qt)

#endif // o_phantom_qt_UndoCommand_h__
