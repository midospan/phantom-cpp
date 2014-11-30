#ifndef unitest_Makha_h__
#define unitest_Makha_h__

/* ****************** Includes ******************* */
#include "Taku"
#include "phantom/composition.h"
/* **************** Declarations ***************** */
o_declareN(class, (wakhan), Makha);
o_fwd(class, wakhan, Taku);
/* *********************************************** */

o_namespace_begin(wakhan)

class Makha
{
public:
    Makha(void);
    ~Makha(void);

    o_initialize();
    o_terminate();
    o_restore(filter, pass);

    Taku* getEntity(size_t a_uiIndex) const { return m_Entities.get(a_uiIndex); }
    void addEntity(Taku* a_pEntity) { m_Entities.add(a_pEntity); }
    void removeEntity(Taku* a_pEntity) { m_Entities.remove(a_pEntity); }

protected:
    phantom::composition<Taku> m_Entities;
};

o_namespace_end(wakhan)

#endif
