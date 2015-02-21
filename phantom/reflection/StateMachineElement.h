/* TODO LICENCE HERE */

#ifndef state_StateMachineElement_h__
#define state_StateMachineElement_h__



/* ****************** Includes ******************* */
#include <phantom/reflection/NamedElement.h>

/* **************** Declarations ***************** */
/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export StateMachineElement : public NamedElement
{
    friend class StateMachine;

public:

public:

    StateMachineElement() {}
    StateMachineElement(const string& a_strName 
        , modifiers_t bf = 0)
        : NamedElement(a_strName, bf)
    {

    }

    StateMachine*    getOwnerStateMachine() const { return (StateMachine*)m_pOwner; }

    virtual StateMachineElement*        asStateMachineElement() const { return (StateMachineElement*)this; }

protected:
    virtual void    setOwnerStateMachine(StateMachine* a_pStateMachine);

};

o_namespace_end(phantom, reflection)



#endif
