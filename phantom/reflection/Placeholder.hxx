#pragma once

#include "Constant.hxx"
#include "Type.hxx"
#include "Class.hxx"
#include "DataMember.hxx"
#include "ArrayType.hxx"
#include "Template.hxx"
#include "Expression.hxx"

o_classN((phantom, reflection),  Placeholder, o_deferred) ();

o_classNB((phantom, reflection), PlaceholderType, (Type, Placeholder), o_deferred) ();

o_classNB((phantom, reflection), PlaceholderClassType, (ClassType, Placeholder), o_deferred) ();

o_classNB((phantom, reflection), PlaceholderClass, (Class, Placeholder), o_deferred) ();

o_classNB((phantom, reflection), PlaceholderConstant, (Constant, Placeholder), o_deferred) ();

o_classNB((phantom, reflection), PlaceholderTemplate, (Template, Placeholder), o_deferred) ();



o_classNB((phantom, reflection), TemplateDependantTemplateInstance, (Type), o_deferred) ();

o_classNB((phantom, reflection), TemplateDependantArrayType, (ArrayType), o_deferred) ();

o_classNB((phantom, reflection), TemplateDependantType, (Type), o_deferred) ();

o_classNB((phantom, reflection), TemplateDependantElement, (NamedElement), o_deferred) ();

o_classNB((phantom, reflection), TemplateDependantExpression, (Expression), o_deferred) ();

o_classNB((phantom, reflection), TemplateDependantDotExpression, (Expression), o_deferred) ();






