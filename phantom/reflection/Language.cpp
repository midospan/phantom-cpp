/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include "Language.h"
#include "Language.hxx"
/* *********************************************** */
o_registerN((phantom, reflection), Language);

o_namespace_begin(phantom, reflection)

Type* Language::typeByName( const string& a_strName, LanguageElement* a_pScope /*= phantom::rootNamespace()*/ ) const
{
    LanguageElement* pElement = elementByName(a_strName, a_pScope);
    return pElement ? pElement->asType() : nullptr;
}

o_namespace_end(phantom, reflection)