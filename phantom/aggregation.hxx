#pragma once

#include "phantom/std/vector.hxx"
#include "phantom/reflection/native/TAggregationClass.h"
#include "phantom/reflection/native/TAggregationClass.hxx"

o_namespace_begin(phantom, reflection)

template<typename t_Aggregate>
struct base_meta_class_type_of<phantom::aggregation<t_Aggregate>>
{
    typedef native::TAggregationClass<phantom::aggregation<t_Aggregate>> type;
};

o_namespace_end(phantom, reflection)


namespace phantom { template<typename t_Aggregate> struct has_has_something<aggregation_replacer<t_Aggregate>> : public detail::false_ {}; }
namespace phantom { template<typename t_Aggregate> struct has_has_something<aggregation_inserter<t_Aggregate>> : public detail::false_ {}; }

o_classNT((phantom), (typename), (t_Aggregate), aggregation_replacer)
(
o_public:
    o_member_function(t_Aggregate*, operator t_Aggregate*, ());
);

o_classNT((phantom), (typename), (t_Aggregate), aggregation_inserter)
(
);
o_classNT((phantom), (typename), (t_Aggregate), aggregation, o_placement_extension)
(
    o_static_assert((boost::is_same<typename phantom::reflection::base_meta_class_type_of<phantom::aggregation<t_Aggregate>>::type
                                , phantom::reflection::native::TAggregationClass<phantom::aggregation<t_Aggregate>>>::value));

o_public:
    o_nested_typedef(sequence_type);
    o_nested_typedef(replacer);
    o_nested_typedef(inserter);

o_protected:
    o_signal(aboutToBeInserted, (size_t, t_Aggregate*));
    o_signal(inserted, (size_t, t_Aggregate*));
    o_signal(aboutToBeRemoved, (size_t, t_Aggregate*));
    o_signal(removed, (size_t, t_Aggregate*));
    o_signal(aboutToBeReplaced, (size_t, t_Aggregate*, t_Aggregate*));
    o_signal(replaced, (size_t, t_Aggregate*, t_Aggregate*));
    o_signal(aboutToBeSwapped, (size_t, size_t, t_Aggregate*, t_Aggregate*));
    o_signal(swapped, (size_t, size_t, t_Aggregate*, t_Aggregate*));
    o_signal(aboutToBeMoved, (size_t, size_t, t_Aggregate*));
    o_signal(moved, (size_t, size_t, t_Aggregate*));
    o_data_member(vector<t_Aggregate*>, m_Aggregates, o_no_range, o_protected_access);

o_public:
    o_member_function(replacer, operator[], (size_t));
    o_member_function(inserter, operator(), (size_t));
    o_slot(void, add, (t_Aggregate*));
    o_slot(void, insert, (size_t, t_Aggregate*));
    o_slot(void, removeAll, (t_Aggregate*));
    o_slot(t_Aggregate*, remove, (size_t));
    o_member_function(size_t, countOf, (t_Aggregate*));
    o_member_function(t_Aggregate*, get, (size_t));
    o_slot(void, set, (size_t, t_Aggregate*));
    o_slot(void, swap, (size_t, size_t));
    o_slot(void, move, (size_t, size_t));
    o_member_function(size_t, count, ());
);