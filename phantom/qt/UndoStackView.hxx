#pragma once

o_classN((phantom, qt), UndoStackView, o_no_copy)
{
	o_reflection
    {
        o_slot(void, undoCommandAdded, (UndoCommand*), o_protected);
        o_slot(void, undoCommandAboutToBeRemoved, (UndoCommand*), o_protected);
	};
};