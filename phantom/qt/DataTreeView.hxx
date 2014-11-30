#pragma once

#include "Action.hxx"

o_classN((phantom, qt), DataTreeView, o_no_copy)
{
    o_reflection 
    {
        o_slot(void, dataAdded, (const phantom::data&,phantom::serialization::Node*));
        o_slot(void, dataAboutToBeUnloaded, (const phantom::data&, phantom::serialization::Node*));
        o_slot(void, dataReloaded, (const phantom::data&,phantom::serialization::Node*));
        o_slot(void, dataAboutToBeRemoved, (const phantom::data&,phantom::serialization::Node*));
        o_slot(void, nodeAdded, (phantom::serialization::Node* ,phantom::serialization::Node*));
        o_slot(void, nodeAboutToBeRemoved, (phantom::serialization::Node* ,phantom::serialization::Node*));
        o_slot(void, nodeLoaded, ());
        o_slot(void, nodeAboutToBeUnloaded, ());
        o_slot(void, dataAttributeValueChanged, ( const phantom::data& , size_t , const string& ));
        o_slot(void, nodeAttributeValueChanged, ( phantom::serialization::Node* , size_t , const string& ));
    };
};


o_classNB((phantom, qt), AddDataAction, (Action), o_no_copy)
{
    o_reflection
    {

    };
};


o_classNB((phantom, qt), RemoveDataAction, (Action), o_no_copy)
{
    o_reflection
    {

    };
};


o_classNB((phantom, qt), AddNodeAction, (Action), o_no_copy)
{
    o_reflection
    {

    };
};


o_classNB((phantom, qt), LoadNodeAction, (Action), o_no_copy)
{
    o_reflection
    {

    };
};


o_classNB((phantom, qt), UnloadNodeAction, (Action), o_no_copy)
{
    o_reflection
    {

    };
};
