#pragma once

#include "Class.hxx"
#include "Expression.hxx"

o_classNB((phantom, reflection), CompositionClass, (Class))
(
);

o_classNCB((phantom, reflection), (CompositionClass), GetSetExpression, (Expression))
(
);

o_classNCB((phantom, reflection), (CompositionClass), InsertRemoveExpression, (Expression))
(
);