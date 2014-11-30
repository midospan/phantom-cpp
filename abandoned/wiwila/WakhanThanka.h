#ifndef unitest_WakhanThanka_h__
#define unitest_WakhanThanka_h__

/* ****************** Includes ******************* */
#include "Taku"
#include "phantom/composition.h"
/* **************** Declarations ***************** */
o_declareN(class, (wakhan), WakhanThanka);
o_fwd(class, wakhan, Taku);
/* *********************************************** */

o_namespace_begin(wakhan)

class WakhanThanka
{
public:
    ~WakhanThanka(void);

    Nagi*   embodySpirit() 
    { 
        Nagi* pSpirit = o_new(Nagi); 
        m_Spirits.add(pSpirit); 
        o_connect(this, loveSpread(float), pSpirit, receiveLove(float));
        return pSpirit; 
    }

    void    disembodySpirit(Nagi* a_pSpirit) 
    { 
        o_disconnect(this, loveSpread(float), a_pSpirit, receiveLove(float));
        m_Spirits.remove(a_pSpirit); 
    }

    static WakhanThanka* GreatMystery();

    void exist() { o_emit loveSpread(1.618f); } // ;)

protected:
    WakhanThanka(void);

protected:
    o_signal_data(loveSpread, float);

protected:
    phantom::composition<Nagi> m_Spirits;
};

o_namespace_end(wakhan)

#endif
