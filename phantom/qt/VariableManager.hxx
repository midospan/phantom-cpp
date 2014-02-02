#pragma once

#include <phantom/reflection/Variable.hxx>

o_classN((phantom, qt), VariableManager, o_no_copy)
{
    o_reflection
    {

    };
};
o_exposeN((phantom, qt), VariableManager);

o_classNS((phantom, qt), CollectionElementVariable, (reflection::Variable))
{
    o_reflection {};
};
o_exposeN((phantom, qt), CollectionElementVariable);

o_classNS((phantom, qt), ArrayElementVariable, (reflection::Variable))
{
    o_reflection {};
};
o_exposeN((phantom, qt), ArrayElementVariable);

o_classNS((phantom, qt), CollectionInsertVariable, (reflection::Variable))
{
    o_reflection {};
};
o_exposeN((phantom, qt), CollectionInsertVariable);

o_classNS((phantom, qt), ContainerInsertVariable, (reflection::Variable))
{
    o_reflection {};
};
o_exposeN((phantom, qt), ContainerInsertVariable);

o_classNS((phantom, qt), SequentialContainerItemInsertVariable, (ContainerInsertVariable))
{
    o_reflection {};
};
o_exposeN((phantom, qt), SequentialContainerItemInsertVariable);

o_classNS((phantom, qt), MapInsertPairVariable, (ContainerInsertVariable))
{
    o_reflection {};
};
o_exposeN((phantom, qt), MapInsertPairVariable);

o_classNS((phantom, qt), SetInsertPairVariable, (ContainerInsertVariable))
{
    o_reflection {};
};
o_exposeN((phantom, qt), SetInsertPairVariable);

o_classNS((phantom, qt), BufferedVariable, (reflection::Variable))
{
    o_reflection {};
};
o_exposeN((phantom, qt), BufferedVariable);

o_classNS((phantom, qt), DataBaseAttributeVariable, (reflection::Variable))
{
    o_reflection {};
};
o_exposeN((phantom, qt), DataBaseAttributeVariable);