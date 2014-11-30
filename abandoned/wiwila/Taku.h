#ifndef unitest_Wiwila_h__
#define unitest_Wiwila_h__

/* ****************** Includes ******************* */
#include "wakhan"
/* **************** Declarations ***************** */
o_declareN(class, (wakhan), Taku);
o_fwd(class, wakhan, Nagi);
o_fwd(class, wakhan, WakhanThanka);
/* *********************************************** */

o_namespace_begin(wakhan)

class Taku 
{
    o_statemachine;

public:
    Taku(void);
    ~Taku(void);

    o_initialize();
    o_terminate();
    o_restore(filter, pass);

    o_enter(Alive);
    o_update(Alive);
    o_leave(Alive);

    o_enter(Mindfulness);
    o_update(Mindfulness);
    o_leave(Mindfulness);

    o_enter(Cerebration);
    o_update(Cerebration);
    o_leave(Cerebration);
  
    o_enter(Dead);
    o_update(Dead);
    o_leave(Dead);

    void meditate();
    void thinkTooMuch();

    Nagi* getSpirit() const { return m_pSpirit; }

protected:
    void setSpirit(Nagi* a_pNagi) 
    {
        if(m_pSpirit == a_pNagi) return;
        m_pSpirit = a_pNagi;
        o_emit spiritChanged(a_pNagi);
    }
    void heal(float a_fLove) {}

protected:
    Nagi* m_pSpirit;
    float m_fLove;
};

o_namespace_end(wakhan)

#endif
