#pragma once

o_classN((phantom), Message)
{
    o_reflection
    {
        o_signal(opened, ());
        o_signal(messageOpened, (Message*));
        o_signal(childAdded, (Message*));
        o_signal(childRemoved, (Message*));
    };
};
o_exposeN((phantom), Message);