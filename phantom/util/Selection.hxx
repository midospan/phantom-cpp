#pragma once

#include "phantom/std/vector.h"

o_classN((phantom), Selection, o_no_copy)
(
        o_signal(selectionChanged, ());
        o_slot(void, select, (const phantom::vector<phantom::data>&));
        o_slot(void, deselect, (const phantom::vector<phantom::data>&));
        o_slot(void, deselectAll, ());
);
