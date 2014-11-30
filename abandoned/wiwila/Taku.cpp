/* ******************* Includes ****************** */
#include "wakhan.h"
#include "Taku.h"
#include "Taku.hxx"
/* *********************************************** */
o_registerN((wakhan), Taku)

o_namespace_begin(wakhan)

Taku::Taku( void )
    : m_pSpirit(nullptr)
    , m_fLove(0)
{

}

Taku::~Taku( void )
{

}

o_enter(Taku::Alive) 
{
    m_pSpirit = WakhanThanka::GreatMystery()->incarnateSpirit();
}

o_update(Taku::Alive) 
{

}

o_leave(Taku::Alive) 
{
    o_disconnect(m_pSpirit, loveReceived(float), this, heal(float));
    WakhanThanka::GreatMystery()->recoverSpirit(m_pSpirit);
    m_pSpirit = nullptr;
}

o_enter(Taku::Cerebration) {}

o_update(Taku::Cerebration) {}

o_leave(Taku::Cerebration) {}

o_enter(Taku::Mindfulness) { o_connect(m_pSpirit, loveReceived(float), this, heal(float)); }

o_update(Taku::Mindfulness) {}

o_leave(Taku::Mindfulness) { o_disconnect(m_pSpirit, loveReceived(float), this, heal(float)); }

o_enter(Taku::Mindfulness) {}

o_update(Taku::Dead) {}

o_leave(Taku::Dead) {}

void Taku::meditate()
{
    o_statemachine_post(Meditate);
}

void Taku::thinkTooMuch()
{
    o_statemachine_post(ThinkTooMuch);
}

o_namespace_end(wakhan)