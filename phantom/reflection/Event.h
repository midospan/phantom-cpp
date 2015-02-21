/* TODO LICENCE HERE */

#ifndef state_Event_h__
#define state_Event_h__



/* ****************** Includes ******************* */


/* **************** Declarations ***************** */

/* *********************************************** */

o_namespace_begin(phantom, reflection)


class o_export Event : public StateMachineElement
{
    friend class StateMachine;

public:
    Event(const string& a_strName, uint id, modifiers_t a_Modifiers = 0);
    ~Event() {}

    virtual Event* asEvent() const { return (Event*)this; }

    uint getId() const  { return m_uiId; }
    
protected:
    uint    m_uiId;
};
o_namespace_end(phantom, reflection)



#endif
