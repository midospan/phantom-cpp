#pragma once

o_classN((phantom, qt), MessageDisplay, o_no_copy)
{
    o_reflection
    {
        o_slot(void, addNodeItem, (Message*));
        o_slot(void, removeNodeItem, (Message*));
        o_slot(void, listenedMessageChanged, ());
    };
};
o_exposeN((phantom, qt), MessageDisplay);
