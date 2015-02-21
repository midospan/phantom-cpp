/* TODO LICENCE HERE */

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



template<typename T> struct vector2
{
    T& operator[](size_t i) { return a[i]; }
    const T& operator[](size_t i) const { return a[i]; }
    union { 
        T a[2]; 
        struct { 
            T x;
            T y;
        };
    };
};
class Luigi;

o_structureT((typename), (T), vector2)
{
    o_member_function(T&, operator[], (size_t), o_noconst);
    o_member_function(const T&, operator[], (size_t), o_const);
    o_anonymous_union(
        o_data_member(T[2], a);
        o_anonymous_struct(
            o_data_member(T, x, (T(-100), T(0), T(100)));
            o_data_member(T, y, (T(-100), T(0), T(100)));
        );
    );
};

o_class(Mario)
(
o_public:
    o_typedef(vector2f)
    o_friend(Luigi)
    o_constructor((int))
    o_member_function(void, jump, ())
    o_slot(void, get1up, ())
    o_property(vector2f, Position, setPosition, getPosition);

o_protected:
    o_signal(crouched, ())

o_private:
    o_data_member(int, m_LifePoints)
);

class Mario
{
public:
    typedef vector2<float> vector2f;
    friend class Luigi;
    Mario(int);
    void jump();
    void get1up();
    vector2f getPosition() const;
    void setPosition(vector2f);

protected:
    o_signal_data(crouched);

private:
    int m_LifePoints;
};

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