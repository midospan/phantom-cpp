#pragma once

o_classN((phantom, qt), UndoStack)
{
	o_reflection
	{
        o_slot(void, undo, (), o_public);
        o_slot(void, redo, (), o_public);
        o_signal(commandAdded, (UndoCommand*), o_protected);
        o_signal(commandAboutToBeRemoved, (UndoCommand*), o_protected);
        o_signal(stackIndexChanged, (int), o_protected);
        o_slot(void, slotCommandUndone, (), o_protected);
        o_slot(void, slotCommandRedone, (), o_protected);
        o_signal(commandRedone, (UndoCommand*), o_protected);
        o_signal(commandUndone, (UndoCommand*), o_protected);
	};
};