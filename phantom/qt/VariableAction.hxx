#pragma once

#include "VariableAction.hxx"

o_classN((phantom, qt), VariableAction, o_no_copy)
{
    o_reflection
    {
        o_signal(actionAboutToBeDone, (), o_protected);
        o_signal(actionDone, (), o_protected);
    };
};
o_exposeN((phantom, qt), VariableAction);/*

o_classNS((phantom, qt), ResetAction, (VariableAction), o_no_copy)
{
    o_reflection
    {

    };
};
o_exposeN((phantom, qt), ResetAction);*/
