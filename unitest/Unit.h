/* TODO LICENCE HERE */

#ifndef unitest_Unit_h__
#define unitest_Unit_h__
// #pragma __PragmaPrintUnit__


/* ****************** Includes ******************* */
#include "GameEntity.h"
#include "Ability.h"
#include "phantom/composition.h"
#include "phantom/math/math.h"
/* **************** Declarations ***************** */
o_declareN(class, (sc2), RallyPoint)
o_declareN(class, (sc2), Ability)
/* *********************************************** */

o_namespace_begin(sc2)

class Unit : public GameEntity
{
public:
    typedef phantom::composition<Ability> Abilities;
public:
    Unit(void);

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

    void setPosition(const phantom::math::vector2<float>& a_Position)
    {
        m_Position = a_Position;
    }

    const phantom::math::vector2<float>& getPosition() const { return m_Position; }
    
protected:
    Abilities m_Abilities;
    phantom::math::vector2<float> m_Position;
    int       m_iLifePoints;
    int       m_iInitialLifePoints;
    bool      m_bPatrolWay;

};

o_namespace_end(sc2)

#if o__int__reflection_template_use_level == 3
#include "Unit.hxx"
#else 
    o_declareN(class, (sc2), Unit);
#endif

#endif

