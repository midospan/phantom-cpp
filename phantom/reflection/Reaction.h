/* TODO LICENCE HERE */

#ifndef state_Reaction_h__
#define state_Reaction_h__



/* ****************** Includes ******************* */


/* **************** Declarations ***************** */

/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export Reaction : public StateMachineElement
{
    friend class State;

public:
    Reaction() {}
    Reaction(const string& a_strName, modifiers_t bf = 0) : StateMachineElement(a_strName, bf) {}
    ~Reaction() {}

    virtual void react(void* a_pObject, Event* a_pTriggerEvent) = 0;

protected:
};

o_namespace_end(phantom, reflection)



#endif
