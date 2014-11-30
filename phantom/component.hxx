#pragma once

#include "phantom/std/vector.hxx"
#include "phantom/reflection/native/TComponentClass.h"
#include "phantom/reflection/native/TComponentClass.hxx"

o_namespace_begin(phantom, reflection)

template<typename t_Component>
struct base_meta_class_type_of<phantom::component<t_Component>>
{
    typedef native::TComponentClass<phantom::component<t_Component>> type;
};

o_namespace_end(phantom, reflection)

o_classNT((phantom), (typename), (t_Component), component, o_placement_extension)
(
        o_nested_typedef(self_type);
        o_nested_typedef(pointed_type);

        o_signal(aboutToBeChanged, (t_Component*, t_Component*));
        o_signal(changed, (t_Component*, t_Component*));

        o_member_function(self_type&, operator=, (t_Component*), o_public_access|o_noconst);
        o_member_function(t_Component&, operator*, (), o_public_access);
        o_member_function(t_Component*, operator->, (), o_public_access);
        o_member_function(t_Component*, operator t_Component*, (), o_public_access);
        o_data_member(t_Component*, m_pPointer, o_no_range, o_protected_access);
);
