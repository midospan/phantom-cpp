#pragma once

o_classN((phantom, qt), VariableEditor, o_no_copy)
(
o_protected:
    o_slot(void, reedit, ());
    o_slot(void, refresh, ());
    o_slot(void, variableChildNodeAdded, (VariableNode*));
    o_slot(void, variableChildNodeAboutToBeRemoved, (VariableNode*));
    o_slot(void, variableNodeExpressionsAssigned, (VariableNode*));
    o_slot(void, variableNodeExpressionsAboutToBeAssigned, (VariableNode*));
);
