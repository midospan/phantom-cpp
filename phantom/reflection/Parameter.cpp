/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include "Parameter.h"
#include "Parameter.hxx"
#include "Expression.h"
#include "Block.h"
#include <phantom/std/vector.hxx>
/* *********************************************** */
o_registerN((phantom, reflection), Parameter);
o_registerNTI((phantom), vector, (phantom::reflection::Parameter*));

o_namespace_begin(phantom, reflection) 

o_define_meta_type(Parameter);

Parameter::Parameter()
{

}

Parameter::Parameter( Type* a_pValueType, const string& a_strName, Expression* a_pInitializer, modifiers_t a_Modifiers /*= 0*/ ) 
    : LocalVariable(a_pValueType, a_strName, a_pInitializer, a_Modifiers)
{
}

Parameter* Parameter::clone() const
{
    return o_new(Parameter)(m_pValueType, m_strName, m_pInitializationExpression, m_Modifiers);
}

o_namespace_end(phantom, reflection)