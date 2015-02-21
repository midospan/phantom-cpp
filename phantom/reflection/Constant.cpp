/* TODO LICENCE HERE */

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include "Constant.h"
#include "Constant.hxx"
#include "ConstantExpression.h"
/* *********************************************** */
o_registerN((phantom, reflection), Constant);

o_namespace_begin(phantom, reflection) 

Class* const Constant::metaType = o_type_of(phantom::reflection::Constant);

Expression* Constant::toExpression() const
{
    return o_new(ConstantExpression)(const_cast<Constant*>(this));
}

o_namespace_end(phantom, reflection)

