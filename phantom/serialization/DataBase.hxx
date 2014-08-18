#pragma once

o_classN((phantom, serialization), DataBase, o_deferred|o_abstract) 
{
    o_reflection 
    {
        o_signal(dataAdded, (const phantom::data&, Node*));
        o_signal(dataAboutToBeRemoved, (const phantom::data&, Node*));
        o_signal(dataAboutToBeAborted, (const phantom::data&, Node*));
        o_signal(dataMoved, (const phantom::data&, Node*, Node*));
        o_signal(dataAttributeValueChanged, (const phantom::data&, size_t, const string&));
        o_signal(dataReplaced, (const phantom::data&, const phantom::data&));
        o_signal(dataErased, (uint));
        o_signal(dataRestored, (uint));

        o_signal(subDataOwnershipLost, (const phantom::data&));

        o_signal(nodeAdded, (Node*, Node*));
        o_signal(nodeAboutToBeRemoved, (Node*, Node*));
        o_signal(nodeMoved, (Node*, Node*, Node*));
        o_signal(nodeAttributeValueChanged, (Node*, size_t, const string&)); 

        o_member_function(uint, getGuid, ( const phantom::data&), o_public);
        o_member_function(const phantom::data&, getData, (uint), o_public);
    }; 
};
o_exposeN((phantom, serialization), DataBase);
