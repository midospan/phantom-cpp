#pragma once

o_classN((phantom, qt), Action, o_no_copy)
{
    o_reflection
    {
        o_signal(aboutToBeDone, (), o_protected);
        o_signal(done, (), o_protected);
    };
};
o_exposeN((phantom, qt), Action);

