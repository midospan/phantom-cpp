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

#ifndef unitest_ControlableEntity_h__
#define unitest_ControlableEntity_h__
// #pragma __PragmaPrintControlableEntity__


/* ****************** Includes ******************* */
#include "GameEntity.h"
/* *********************************************** */
/* The *.classdef.h file must be the last #include */
#include "ControlableEntity.classdef.h"
/* **************** Declarations ***************** */
/* *********************************************** */

o_h_Begin
    
class ControlableEntity : public GameEntity 
{
    Reflection_____________________________________________________________________________________
        o_Attribute(int, m_iPlayer)
    _____________________________________________________________________________________Reflection

    StateMachine___________________________________________________________________________________
        o_Track(ControlAbility, Active)
        o_State(ControlEnabled, ControlAbility)
        o_State(ControlDisabled, ControlAbility)
    ___________________________________________________________________________________StateMachine

public:

    ControlableEntity(void) : m_iPlayer(0) {}
    o_destructor ~ControlableEntity(void) {}
    
    o_Enter(ControlEnabled) {  }
    o_Update(ControlEnabled) { }
    o_Leave(ControlEnabled) { }

    o_Enter(ControlDisabled) {}
    o_Update(ControlDisabled) { }
    o_Leave(ControlDisabled) {}

protected:
    int     m_iPlayer;

};

o_h_End


#else // unitest_ControlableEntity_h__
#include "ControlableEntity.classdef.h"
#endif
