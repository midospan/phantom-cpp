#pragma once

o_classN((phantom, qt), UndoCommand)
{
	o_reflection
	{
        o_slot(void, undo, ());
        o_slot(void, redo, ());
	};
};