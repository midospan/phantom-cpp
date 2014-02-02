#pragma once

o_classN((phantom, qt), CallStackView, o_no_copy)
{
	o_reflection
	{
        o_slot(void, activate, ());
        o_slot(void, deactivate, ());
	};
};
o_exposeN((phantom, qt), CallStackView);
