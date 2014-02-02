#pragma once

#include "Action.hxx"

o_classN((phantom, qt), DataTreeView, o_no_copy)
{
    o_reflection 
    {
        o_slot(void, dataAdded, (const phantom::data&,phantom::serialization::Node*));
        o_slot(void, dataReplaced, (const phantom::data&,const phantom::data&));
        o_slot(void, dataAboutToBeRemoved, (const phantom::data&,phantom::serialization::Node*));
        o_slot(void, nodeAdded, (phantom::serialization::Node* ,phantom::serialization::Node*));
        o_slot(void, nodeAboutToBeRemoved, (phantom::serialization::Node* ,phantom::serialization::Node*));
        o_slot(void, nodeLoaded, ());
        o_slot(void, nodeAboutToBeUnloaded, ());
        o_slot(void, dataAttributeValueChanged, ( const phantom::data& , size_t , const string& ));
        o_slot(void, nodeAttributeValueChanged, ( phantom::serialization::Node* , size_t , const string& ));
    };
};
o_exposeN((phantom, qt), DataTreeView);

o_classNS((phantom, qt), AddDataAction, (Action), o_no_copy)
{
    o_reflection
    {

    };
};
o_exposeN((phantom, qt), AddDataAction);

o_classNS((phantom, qt), AddNodeAction, (Action), o_no_copy)
{
    o_reflection
    {

    };
};
o_exposeN((phantom, qt), AddNodeAction);

o_classNS((phantom, qt), LoadNodeAction, (Action), o_no_copy)
{
    o_reflection
    {

    };
};
o_exposeN((phantom, qt), LoadNodeAction);

o_classNS((phantom, qt), UnloadNodeAction, (Action), o_no_copy)
{
    o_reflection
    {

    };
};
o_exposeN((phantom, qt), UnloadNodeAction);