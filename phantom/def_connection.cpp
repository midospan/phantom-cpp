/*
    This file is part of PHANTOM
         P reprocessed
         H igh-level
         A llocator
         N ested state-machines and
         T emplate
         O riented
         M eta-programming

    For the latest infos and sources, see http://code.google.com/p/phantom-cpp

    Copyright (C) 2008-2011 by Vivien MILLET

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
    THE SOFTWARE
*/
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
