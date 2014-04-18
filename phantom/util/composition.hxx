#pragma once

#include "phantom/std/vector.hxx"
#include "phantom/reflection/native/TCompositionClass.h"
#include "phantom/reflection/native/TCompositionClass.hxx"

o_namespace_begin(phantom, reflection)

template<typename t_Component>
struct base_meta_class_type_of<phantom::composition<t_Component>>
{
    typedef native::TCompositionClass<phantom::composition<t_Component>> type;
};

o_namespace_end(phantom, reflection)

o_classNT((phantom), (typename), (t_Component), composition)
{
	o_reflection
    {
        o_typedef(sequence_type);

        o_signal(aboutToBeInserted, (size_t, t_Component*));
        o_signal(inserted, (size_t, t_Component*));
        o_signal(aboutToBeRemoved, (size_t, t_Component*));
        o_signal(removed, (size_t, t_Component*));
        o_signal(aboutToBeReplaced, (size_t, t_Component*, t_Component*));
        o_signal(replaced, (size_t, t_Component*, t_Component*));
        o_signal(aboutToBeSwapped, (t_Component*, t_Component*));
        o_signal(swapped, (t_Component*, t_Component*));
        o_signal(aboutToBeMoved, (t_Component*, size_t, size_t));
        o_signal(moved, (t_Component*, size_t, size_t));

        o_slot(void, add, (t_Component*), o_public);
        o_slot(void, insert, (size_t, t_Component*), o_public);
        o_slot(void, remove, (t_Component*), o_public);
        o_slot(t_Component*, remove, (size_t), o_public);
        o_member_function(bool, has, (t_Component*), o_public);
        o_member_function(t_Component*, get, (size_t), o_public);
        o_slot(void, set, (size_t, t_Component*), o_public);
        o_slot(void, swap, (t_Component*, t_Component*), o_public);
        o_slot(void, move, (t_Component*, size_t), o_public);
        o_member_function(size_t, indexOf, (t_Component*), o_public);
        o_member_function(size_t, count, (), o_public);

        o_data_member(vector<t_Component*>, m_Components, o_no_range, o_protected|o_component);
	};
};
