#pragma once

o_classN((phantom, qt), VariableEditor, o_no_copy)
{
    o_reflection
    {
        o_slot(void, reedit, (), o_protected);
        o_slot(void, refresh, (), o_protected);
        o_slot(void, variableChildNodeAdded, (VariableNode*), o_protected);
        o_slot(void, variableChildNodeAboutToBeRemoved, (VariableNode*), o_protected);
        o_slot(void, variableNodeExpressionsAssigned, (VariableNode*), o_protected);
        o_slot(void, variableNodeExpressionsAboutToBeAssigned, (VariableNode*), o_protected);
    };
};
