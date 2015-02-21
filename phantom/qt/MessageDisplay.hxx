#pragma once

o_classN((phantom, qt), MessageDisplay, o_no_copy)
(
o_public:
    o_slot(void, addNodeItem, (Message*));
    o_slot(void, removeNodeItem, (Message*));

o_protected:
    o_slot(void, listenedMessageChanged, ());
);

