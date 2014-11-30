#ifndef unitest_Wiwila_h__
#define unitest_Wiwila_h__

/* ****************** Includes ******************* */
#include "Taku"
#include "phantom/aggregation.h"
#include "phantom/component.h"
/* **************** Declarations ***************** */
o_declareN(class, (wakhan), Wiwila);
o_fwd(class, wakhan, Takula);
o_fwd(class, wakhan, Chan);
o_fwd(class, wakhan, Mni);
/* *********************************************** */

o_namespace_begin(wakhan)

class Wiwila : public Taku
{
public:
    Wiwila(void);
    ~Wiwila(void);

    o_initialize();
    o_terminate();
    o_restore(filter, pass);

    o_enter(Dried);
    o_update(Dried);
    o_leave(Dried);
  
    o_enter(Flows);
    o_update(Flows);
    o_leave(Flows);

protected:
    phantom::aggregation<Taku>    m_Entities;
    phantom::component<Mni>       m_Water;
};

o_namespace_end(wakhan)

#endif
