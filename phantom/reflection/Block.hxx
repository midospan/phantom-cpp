#pragma once

#include "Statement.hxx"

o_classNB((phantom, reflection), Block, (Statement))
(
    o_property(vector<LocalVariable*>, localVariable, setLocalVariables, getLocalVariables, o_no_signal, o_no_range, o_protected_access);
    o_property(vector<Statement*>, statements, setStatements, getStatements, o_no_signal, o_no_range, o_protected_access);
    o_property(vector<Statement*>, raiiDestructionStatements, setRAIIDestructionStatements, getRAIIDestructionStatements, o_no_signal, o_no_range, o_protected_access);
);
