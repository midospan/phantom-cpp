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

#ifndef o_sc2_Marine_h__
#define o_sc2_Marine_h__

/* ****************** Includes ******************* */
#include "Unit.h"
/* **************** Declarations ***************** */
o_declareN(class, (phantom, sc2), Ability);
o_declareN(class, (sc2), Marine);
/* *********************************************** */


o_namespace_begin(sc2)

class Marine : public Unit
{
    friend class Ability;
    using Unit::m_iLifePoints;

public:
    Marine(void)  { m_iInitialLifePoints = 50; }
    o_destructor ~Marine(void) {}

    o_enter(Idle) 
    {

    }

    o_enter(Pooled) 
    {

    }

    o_enter(StimPackDisabled) {  }
    o_update(StimPackDisabled) { }
    o_leave(StimPackDisabled) {  }

    o_enter(StimPackEnabled) { if(m_iLifePoints > 10) m_iLifePoints -= 10; }
    o_update(StimPackEnabled) { }
    o_leave(StimPackEnabled) {  }



};

o_namespace_end(sc2)

#if 0

#include <phantom/phantom.h>
#include <phantom/composition.h>

class Lumi
{
public:
    Lumi() : m_LifePoints(100) {}

    void decreaseLifePoints(int count) 
    { 
        m_LifePoints -= count; 
        if(m_LifePoints == 0) 
        { 
            m_LifePoints = 0; 
        }
    }

protected:
    int m_LifePoints;
    phantom::composition<Ability> m_Abilities;
};



class Lumi
{
public:
    Lumi() : m_LifePoints(100) {}

    void decreaseLifePoints(int count) 
    { 
        m_LifePoints -= count; 
        if(m_LifePoints == 0) 
        { 
            m_LifePoints = 0; 
        }
    }

protected:
    int m_LifePoints;
    phantom::composition<Ability> m_Abilities;
};




#include <phantom/phantom.h>
#include <phantom/composition.h>
#include "Ability.h"

class Lumi                                  
{                                           
public:                                     
    Lumi(int a_fLifePoints);    
    void jump();

protected:                                  
    std::vector<Ability*> m_Abilities;      
    int m_LifePoints;                       
};                                          

o_class(Lumi)
(
o_public:
    o_constructor((int));
    o_member_function(void, jump, ());

o_protected:
    o_data_member(std::vector<Ability*>, m_Abilities);
    o_data_member(int, m_LifePoints);
);

#undef Idle

class Alive;
class Dead;
class Moving;
class Appearance;
class Motion;
class Idle {};
class Walk {};
class Jump;
class Power{};
class Disabled {;};
class Magnetism {};
class Drowning {};
class Run {};
class Tanuki {};
class Fire {};
class Frog {};
class Transformation {};
class Small {};
class Big {};
class Enabled {};
class Invincibility {};
class Vulnerable {};
class Invincible {};
class Racoon {};
class Boot {};
class Crouch {};
class Mario { int m_LifeCount; int m_CoinCount; int crouched; void get1up(); };










o_class(Mario)
(
o_public:
    o_constructor((int))
    o_member_function(void, jump, ())
    o_member_function(void, fire, ())
    o_slot(void, get1up, ())

o_protected:
    o_signal(crouched, ());
    o_data_member(int, m_LifeCount)
    o_data_member(int, m_CoinCount)

    o_statechart
    (
        o_state(Dead, Root)
        o_state(Alive, Root)
            o_track(Motion, Alive)
                o_state(Idle, Motion)
                o_state(Walk, Motion)
                o_state(Run, Motion)
                o_state(Jump, Motion)
                o_state(Crouch, Motion)
            o_track(Size, Alive)
                o_state(Small, Size)
                o_state(Big, Size)
                    o_track(Transformation, Big)
                        o_state(Normal, Transformation)
                        o_state(Fire, Transformation)
                        o_state(Racoon, Transformation)
                        o_state(Tanuki, Transformation)
                        o_state(Frog, Transformation)
                        o_state(Boot, Transformation)
            o_track(Invincibility, Alive)
                o_state(Vulnerable, Invincibility)
                o_state(Invincible, Invincibility)
    )
);

#endif
#endif