#pragma once

o_classN((phantom, qt), VariableModel, o_no_copy)
{
    o_reflection
    {
        o_slot(void, dataAboutToBeUnloaded, (const phantom::data&, phantom::serialization::Node*));
        o_slot(void, dataReloaded, (const phantom::data&,phantom::serialization::Node*));
        o_slot(void, dataAboutToBeRemoved, (const phantom::data&,phantom::serialization::Node*));
        o_signal(rootNodeAdded, (VariableNode*));
        o_signal(rootNodeAboutToBeRemoved, (VariableNode*));
        o_signal(variableNodeExpressionsAboutToBeAssigned, (VariableNode*), o_protected);
        o_signal(variableNodeExpressionsAssigned, (VariableNode*), o_protected);
        o_signal(variableNodeAboutToBeAccessed, (VariableNode*), o_protected);
        o_signal(variableNodeAccessed, (VariableNode*), o_protected);
        o_signal(changed, (), o_protected);
        o_slot(void, reset, (), o_public);
        o_slot(void, registerVariableNode, (VariableNode*), o_protected);
        o_slot(void, unregisterVariableNode, (VariableNode*), o_protected);
    };
};
