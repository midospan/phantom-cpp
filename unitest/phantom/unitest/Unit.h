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

#ifndef unitest_Unit_h__
#define unitest_Unit_h__
// #pragma __PragmaPrintUnit__


/* ****************** Includes ******************* */
#include "GameEntity.h"
#include "Ability.h"
#include "phantom/util/TComposition.h"
/* **************** Declarations ***************** */
o_declareN(class, (sc2), RallyPoint)
o_declareN(class, (sc2), Ability)
/* *********************************************** */

o_namespace_begin(sc2)

class Unit : public GameEntity
{

public:
    Unit(void) 
        : m_bPatrolWay(false)
        , m_iLifePoints(-1)
        , m_iInitialLifePoints(-1)
    {

    }

    o_destructor ~Unit(void) {}

    o_enter(Alive) {  }
    o_update(Alive) { }
    o_leave(Alive) {  }

    o_enter(Dead) {  }
    o_update(Dead) { }
    o_leave(Dead) {  }

    o_enter(Move) {  }
    o_update(Move) { }
    o_leave(Move) {  }

    o_enter(Hit) {  }
    o_update(Hit) { }
    o_leave(Hit) {  }

    o_enter(CoolDown) {  }
    o_update(CoolDown) { }
    o_leave(CoolDown) {  }

    o_enter(Pacific) {  }
    o_update(Pacific) { }
    o_leave(Pacific) {  }

    o_enter(Idle) { }
    o_update(Idle) { }
    o_leave(Idle) {  }

    o_enter(Patrol) { }
    o_update(Patrol) { }
    o_leave(Patrol) {  }

    o_enter(Visible) { }
    o_update(Visible) { }
    o_leave(Visible) {  }

    o_enter(Invisible) { }
    o_update(Invisible) { }
    o_leave(Invisible) {  }

    o_enter(ControlOff) {  }
    o_update(ControlOff) { }
    o_leave(ControlOff) {  }

    o_enter(ControlOn) { showControlMarkers(); }
    o_update(ControlOn) { }
    o_leave(ControlOn) { hideControlMarkers(); }

    void showControlMarkers() { /*code to show control markers such as rounding selection circle ...*/ }
    void hideControlMarkers() { /*code to hide control markers*/ }

    void removeAbility(Ability* a_pAbility) 
    {
        o_assert(containsAbility(a_pAbility));
        o_emit abilityRemoved(a_pAbility);
        a_pAbility->m_pUnit = nullptr;
        m_Abilities.erase(std::find(m_Abilities.begin(), m_Abilities.end(), a_pAbility));
    }

    void addAbility(Ability* a_pAbility)
    {
        o_assert(NOT(containsAbility(a_pAbility)));
        a_pAbility->m_pUnit = this;
        m_Abilities.push_back(a_pAbility);
        o_emit abilityAdded(a_pAbility);
    }

    virtual void        setAbility(size_t a_uiIndex, Ability* a_pAbility)
    {
        if(m_Abilities[a_uiIndex] == a_pAbility) return;
        if(m_Abilities[a_uiIndex] != nullptr)
        {
            if(a_pAbility == nullptr) 
            {
                removeAbility(m_Abilities[a_uiIndex]);
                return;
            }
            o_emit abilityRemoved(m_Abilities[a_uiIndex]);
            m_Abilities[a_uiIndex]->m_pUnit = nullptr;
            m_Abilities[a_uiIndex] = a_pAbility;
            a_pAbility->m_pUnit = this; 
            o_emit abilityAdded(a_pAbility);
        }
    }

    bool containsAbility(Ability* a_pAbility) const 
    {
        return std::find(m_Abilities.begin(), m_Abilities.end(), a_pAbility) != m_Abilities.end();
    }

    void moveAbility(Ability* a_pAbility, size_t a_uiNewIndex)
    {
        phantom::container::move_unique(m_Abilities, a_pAbility, a_uiNewIndex);
    }

    Ability* getAbility(size_t a_uiIndex) const { return m_Abilities[a_uiIndex]; }

    size_t getAbilityCount() const { return m_Abilities.size(); }

protected:
    o_signal_data(abilityAdded, Ability*);
    o_signal_data(abilityRemoved, Ability*);

protected:
    phantom::vector<Ability*>           m_Abilities;
    int                                 m_iLifePoints;
    int                                 m_iInitialLifePoints;
    bool                                m_bPatrolWay;

};

o_namespace_end(sc2)

#if o__int__reflection_template_use_level == 3
#include "Unit.hxx"
#else 
    o_declareN(class, (sc2), Unit);
#endif

#endif

