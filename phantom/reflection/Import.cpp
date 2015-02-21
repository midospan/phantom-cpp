/* TODO LICENCE HERE */

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include "Import.h"
#include "Import.hxx"
/* *********************************************** */
o_registerN((phantom, reflection), Import);

o_namespace_begin(phantom, reflection) 
    
Import::Import( Source* a_pSource, const string& a_strSymbolName, modifiers_t a_Modifiers )
    : NamedElement(a_strSymbolName, a_Modifiers)
    , m_pImportedSource(a_pSource)
{
    addReferencedElement(a_pSource);
}

o_namespace_end(phantom, reflection)
