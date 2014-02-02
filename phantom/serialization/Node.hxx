#pragma once

o_classN((phantom, serialization), Node)
{
    o_reflection 
    {
        o_signal(loaded, ());
        o_signal(aboutToBeUnloaded, ());
    };
};
o_exposeN((phantom, serialization), Node);
