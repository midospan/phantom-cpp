/* TODO LICENCE HERE */

#ifndef o_unitest_plugin_Plugin_h__
#define o_unitest_plugin_Plugin_h__

/* ****************** Includes ******************* */
#include "phantom/phantom.h"
/* **************** Declarations ***************** */
o_declareN(class, (unitest, module), Plugin);
/* *********************************************** */

o_namespace_begin(unitest, module)

class Plugin 
{
public:
    Plugin(void)  {  }
    o_destructor ~Plugin(void) {}
};

o_namespace_end(unitest, module)

o_classN((unitest, module), Plugin)
(
);


#endif
