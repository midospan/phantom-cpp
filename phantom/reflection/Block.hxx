#pragma once

#include "Statement.hxx"
#include "Scope.hxx"

o_classNB((phantom, reflection), Block, (Statement, Scope))
(
o_protected:
    o_property(vector<LocalVariable*>, localVariable, setLocalVariables, getLocalVariables);
    o_property(vector<Statement*>, statements, setStatements, getStatements);
    o_property(vector<Statement*>, raiiDestructionStatements, setRAIIDestructionStatements, getRAIIDestructionStatements);
);
