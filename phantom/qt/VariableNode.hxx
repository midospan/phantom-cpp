#pragma once

o_classN((phantom, qt), VariableNode)
(
o_protected:
    o_signal(nameChanged, (const string&));
    o_signal(valueChanged, ());
    o_signal(childNodeAdded, (VariableNode*));
    o_signal(childNodeAboutToBeRemoved, (VariableNode*));
);
