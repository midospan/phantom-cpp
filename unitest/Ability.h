/* TODO LICENCE HERE */

#ifndef o_sc2_Ability_h__
#define o_sc2_Ability_h__

/* ****************** Includes ******************* */
/* **************** Declarations ***************** */
o_declareN(class, (sc2), Unit);
/* *********************************************** */

o_namespace_begin(sc2)

class Ability
{
    friend class Unit;
public:
    Ability(void)  { }
    o_destructor ~Ability(void) {}

    Unit* getUnit() const { return m_pUnit; }

protected:
    void setUnit(Unit* a_pUnit)
    {
        m_pUnit = a_pUnit;
    }

protected:
    Unit* m_pUnit;
};

o_namespace_end(sc2)

#endif
