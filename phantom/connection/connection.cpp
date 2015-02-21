/* TODO LICENCE HERE */
#include <phantom/phantom.h>

o_classN((phantom, connection), slot)
(
o_public:
    o_member_function(void*, receiver, ());
    o_member_function(reflection::Subroutine*, subroutine, ());
    o_member_function(slot*, prev, ());
    o_member_function(slot*, next, ());
    o_member_function(boolean, equals, (slot*));
);
o_registerN((phantom, connection), slot)

o_classN((phantom, connection), pair)
(
    o_member_function(void, push, (void const*, slot*));
    o_member_function(void, pop, ());
);
o_registerN((phantom, connection), pair)

o_classNC((phantom, connection), (slot), list)
(
o_public:
    o_member_function(bool, unblocked, ());
    o_member_function(slot*, head, ());
    o_member_function(slot*, queue, ());
);
o_registerNC((phantom, connection), (slot), list)

o_function(int, strcmp, (const char*, const char*));
o_functionN((phantom, connection), void*, sender, ());

o_namespace_begin(phantom, connection)

pair pair::stack[pair::eMaxStackSize];
int32 pair::stack_pointer = -1;

size_t                emission_guard::counter = 0;
size_t                emission_guard::object_destroyed_count = 0;
slot_pool::allocation_controller_map* slot_pool::m_allocation_controller_map = 0;

reflection::Class* const slot::list::metaType = typeOf<slot::list>();

o_namespace_end(phantom, connection)
