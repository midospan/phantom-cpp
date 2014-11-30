#ifndef unitest_Wiwila_h__
#define unitest_Wiwila_h__

/* ****************** Includes ******************* */
#include "wakhan"
/* **************** Declarations ***************** */
o_declareN(class, (wakhan), Nagi);
o_fwd(class, wakhan, Nagi);
o_fwd(class, wakhan, WakhanThanka);
/* *********************************************** */

o_namespace_begin(wakhan)

class Nagi 
{
    o_statemachine;

public:
    Nagi(void);
    ~Nagi(void);

    o_initialize();
    o_terminate();
    o_restore(filter, pass);
    
protected:
    o_signal_data(loveReceived, float);

};

o_namespace_end(wakhan)

#endif
