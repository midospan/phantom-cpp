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

#ifndef unitest_GameEntity_h__
#define unitest_GameEntity_h__

/* ****************** Includes ******************* */
#include "phantom/phantom.h"
/* **************** Declarations ***************** */
/* *********************************************** */

o_namespace_begin(sc2)

class GameEntity 
{
    o_statemachine;

public:
    GameEntity(void) {}
    o_destructor ~GameEntity(void) {}

    o_initialize() 
    {
        o_statemachine_initialize();
    }
    o_terminate() 
    {
        o_statemachine_terminate();
    }

    o_restore(filter, pass) 
    {
        o_statemachine_initialize();
        return phantom::restore_complete;
    }


    o_enter(Pooled) { }
    o_update(Pooled) { }
    o_leave(Pooled) {  }
  
    o_enter(Spawned) { }
    o_update(Spawned) { }
    o_leave(Spawned) { }

};

o_namespace_end(sc2)

o_classN((sc2), GameEntity)
{
    o_reflection 
    {

    };
    o_statechart
    {
        o_state(Pooled, Root)
        o_state(Spawned, Root)
        o_event(Spawn)
        o_transition(Pooled, Spawn, Spawned)
    };
};
o_exposeN((sc2), GameEntity);


o_static_assert(phantom::has_initializer_member_function_initialize_declared<sc2::GameEntity>::value);
o_static_assert(phantom::has_statechart<sc2::GameEntity>::value);
o_static_assert(phantom::has_root_statechart<sc2::GameEntity>::value);
o_static_assert(phantom::track_count_of<sc2::GameEntity>::value == 1);
o_static_assert(phantom::track_count_cascade_of<sc2::GameEntity>::value == 1);

#endif
