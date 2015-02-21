#pragma once

o_classN((phantom, qt), UndoStackView, o_no_copy)
(
o_protected:
    o_slot(void, commandAdded, (UndoCommand*));
    o_slot(void, commandAboutToBeRemoved, (UndoCommand*));
);