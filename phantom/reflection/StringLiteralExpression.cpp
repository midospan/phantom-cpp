/* TODO LICENCE HERE */

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include <phantom/reflection/StringLiteralExpression.h>
#include <phantom/reflection/DataExpression.h>
#include <phantom/reflection/StringLiteralExpression.hxx>
/* *********************************************** */
o_registerN((phantom, reflection), StringLiteralExpression);

o_namespace_begin(phantom, reflection) 


StringLiteralExpression::StringLiteralExpression(const string& literal, const string& a_Value)
    : Expression(typeOf<const char*>())
    , m_Value((const char*)malloc(a_Value.size()+1))
    , m_literal(literal)
{
    memcpy((void*)m_Value, a_Value.c_str(), a_Value.size()+1);
}

void StringLiteralExpression::internalEval( void* a_pDest ) const
{
    *((const char**)a_pDest) = m_Value;
}

StringLiteralExpression* StringLiteralExpression::clone() const
{
    return o_new(StringLiteralExpression)(m_literal, m_Value);
}

o_namespace_end(phantom, reflection)
