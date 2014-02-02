#pragma once

#include "phantom/reflection/Variable.hxx"
#include "phantom/qt/VariableManager.hxx"

o_classNS((phantom, qt, jit), GenericVariable, (phantom::reflection::Variable))
{
    o_reflection
    {

    };
};
o_exposeN((phantom, qt, jit), GenericVariable);

o_classNS((phantom, qt, jit), OptimizedAwayVariable, (phantom::reflection::Variable))
{
    o_reflection
    {

    };
};
o_exposeN((phantom, qt, jit), OptimizedAwayVariable);

o_classNS((phantom, qt, jit), ReferencedVariable, (phantom::reflection::Variable))
{
    o_reflection
    {

    };
};
o_exposeN((phantom, qt, jit), ReferencedVariable);

o_classNS((phantom, qt, jit), DereferencedVariable, (phantom::reflection::Variable))
{
    o_reflection
    {

    };
};
o_exposeN((phantom, qt, jit), DereferencedVariable);

o_classNS((phantom, qt, jit), ValueMemberVariable, (phantom::reflection::Variable))
{
    o_reflection
    {

    };
};
o_exposeN((phantom, qt, jit), ValueMemberVariable);

o_classNS((phantom, qt, jit), LocalVariableManager, (VariableManager), o_no_copy)
{
	o_reflection
	{
		
	};
};
o_exposeN((phantom, qt, jit), LocalVariableManager);
