#pragma once

o_classN((phantom, qt), UndoStack)
{
	o_reflection
	{
        o_slot(void, undo, ());
        o_slot(void, redo, ());
        o_signal(undoCommandAdded, (UndoCommand*), o_protected);
        o_signal(undoCommandAboutToBeRemoved, (UndoCommand*), o_protected);
        o_signal(stackIndexChanged, (int), o_protected);
	};
};