#ifndef phantom_util_TVisitor_h__
#define phantom_util_TVisitor_h__


/* ****************** Includes ******************* */
#include "phantom/phantom.h"

/* **************** Declarations ***************** */

/* *********************************************** */

o_namespace_begin(phantom)

template<typename t_Ty>
class TVisitor
{
public:
    virtual void apply(t_Ty* a_pVisited) = 0;
};

o_namespace_end(phantom)


#endif
