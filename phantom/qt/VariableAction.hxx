#pragma once

#include "VariableAction.hxx"

o_classN((phantom, qt), VariableAction, o_no_copy)
{
    o_reflection
    {

    };
};
o_exposeN((phantom, qt), VariableAction);

o_classNS((phantom, qt), EraseContainerIteratorAction, (VariableAction), o_no_copy)
{
    o_reflection
    {

    };
};
o_exposeN((phantom, qt), EraseContainerIteratorAction);

o_classNS((phantom, qt), ResetAction, (VariableAction), o_no_copy)
{
    o_reflection
    {

    };
};
o_exposeN((phantom, qt), ResetAction);

o_classNS((phantom, qt), ContainerMoveDownAction, (VariableAction), o_no_copy)
{
    o_reflection
    {

    };
};
o_exposeN((phantom, qt), ContainerMoveDownAction);

o_classNS((phantom, qt), ContainerMoveUpAction, (VariableAction), o_no_copy)
{
    o_reflection
    {

    };
};
o_exposeN((phantom, qt), ContainerMoveUpAction);