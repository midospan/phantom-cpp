#pragma once

#include "Class.hxx"
#include "Expression.hxx"

o_classNB((phantom, reflection), AggregationClass, (Class))
(
);

o_classNCB((phantom, reflection), (AggregationClass), GetSetExpression, (Expression))
(
);

o_classNCB((phantom, reflection), (AggregationClass), InsertRemoveExpression, (Expression))
(
);