#pragma once

#include "Constant.hxx"
#include "Type.hxx"
#include "Class.hxx"
#include "InstanceDataMember.hxx"
#include "Subroutine.hxx"

o_classN((phantom, reflection), Placeholder, o_deferred) (
);

o_classNB((phantom, reflection), PlaceholderType, (Type, Placeholder), o_deferred) ();

o_classNB((phantom, reflection), PlaceholderClass, (Class, Placeholder), o_deferred) ();

o_classNB((phantom, reflection), PlaceholderSubroutine, (Subroutine, Placeholder), o_deferred) ();

o_classNB((phantom, reflection), PlaceholderConstant, (Constant, Placeholder), o_deferred) ();

o_classNB((phantom, reflection), PlaceholderInstanceDataMember, (InstanceDataMember, Placeholder), o_deferred) ();





