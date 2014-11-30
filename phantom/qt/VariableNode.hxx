#pragma once

o_classN((phantom, qt), VariableNode)
{
    o_reflection 
    {
        o_signal(nameChanged, (const string&), o_protected);
        o_signal(valueChanged, (), o_protected);
        o_signal(childNodeAdded, (VariableNode*), o_protected);
        o_signal(childNodeAboutToBeRemoved, (VariableNode*), o_protected);
    };
};
