/* TODO LICENCE HERE */

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include <phantom/reflection/WStringLiteralExpression.h>
#include <phantom/reflection/DataExpression.h>
#include <phantom/reflection/WStringLiteralExpression.hxx>
/* *********************************************** */
o_registerN((phantom, reflection), WStringLiteralExpression);

o_namespace_begin(phantom, reflection) 


WStringLiteralExpression::WStringLiteralExpression(const string& literal, const wstring& a_Value)
    : Expression(typeOf<const wchar_t*>())
    , m_Value((const wchar_t*)malloc((a_Value.size()+1)*sizeof(wchar_t)))
    , m_literal(literal)
{
    memcpy((void*)m_Value, a_Value.c_str(), (a_Value.size()+1)*sizeof(wchar_t));
}

void WStringLiteralExpression::internalEval( void* a_pDest ) const
{
    *((const wchar_t**)a_pDest) = m_Value;
}

WStringLiteralExpression* WStringLiteralExpression::clone() const
{
    return o_new(WStringLiteralExpression)(m_literal, m_Value);
}

o_namespace_end(phantom, reflection)
