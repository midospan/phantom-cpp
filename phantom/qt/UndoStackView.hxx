#pragma once

o_classN((phantom, qt), UndoStackView, o_no_copy)
{
	o_reflection
    {
        o_slot(void, commandAdded, (UndoCommand*), o_protected);
        o_slot(void, commandAboutToBeRemoved, (UndoCommand*), o_protected);
	};
};