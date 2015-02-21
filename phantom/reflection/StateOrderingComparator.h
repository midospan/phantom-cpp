/* TODO LICENCE HERE */

#ifndef StateMachineNodeOrderingComparator_h__
#define StateMachineNodeOrderingComparator_h__

/* ****************** Includes ******************* */
#include <phantom/util/Comparator.h>
/* **************** Declarations ***************** */
/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export StateOrderingComparator : public Comparator
{
public:
    StateOrderingComparator(void)             {}

public:
    o_destructor ~StateOrderingComparator(void)     {}
    static StateOrderingComparator* Instance();

    virtual int            compare(void* a_pS0, void* a_pS1) const;
protected:
    
};

o_namespace_end(phantom, reflection)

#endif