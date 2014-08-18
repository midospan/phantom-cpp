#pragma once

o_classN((phantom, qt), UndoCommand)
{
	o_reflection
	{
        o_signal(childCommandAdded, (UndoCommand*));
        o_signal(childCommandAboutToBeRemoved, (UndoCommand*));
        o_signal(redone, (), o_protected);
        o_signal(undone, (), o_protected);
	};
};