#ifndef phantom_util_TVisitor_h__
#define phantom_util_TVisitor_h__


/* ****************** Includes ******************* */
#include "phantom/phantom.h"
/* *********************************************** */
/* The *.classdef.h file must be the last #include */
#include "TVisitor.classdef.h"
/* **************** Declarations ***************** */

/* *********************************************** */

o_h_begin

template<typename t_Ty>
class TVisitor
{
public:
    virtual void apply(t_Ty* a_pVisited) = 0;
};

o_h_end

#else
#include "TVisitor.classdef.h"
#endif
