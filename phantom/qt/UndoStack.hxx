#pragma once

o_classN((phantom, qt), UndoStack)
(
o_public:
    o_slot(void, undo, ());
    o_slot(void, redo, ());

o_protected:
    o_slot(void, slotCommandUndone, ());
    o_slot(void, slotCommandRedone, ());
    o_signal(commandAdded, (UndoCommand*));
    o_signal(commandAboutToBeRemoved, (UndoCommand*));
    o_signal(stackIndexChanged, (int));
    o_signal(commandRedone, (UndoCommand*));
    o_signal(commandUndone, (UndoCommand*));
);