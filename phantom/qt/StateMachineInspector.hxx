#pragma once

o_classN((phantom, qt), StateMachineInspector, o_no_copy)
{
    o_reflection
    {
        o_slot(void, dataAboutToBeUnloaded, (const phantom::data&, phantom::serialization::Node*));
        o_slot(void, dataReloaded, (const phantom::data&,phantom::serialization::Node*));
    };
};
