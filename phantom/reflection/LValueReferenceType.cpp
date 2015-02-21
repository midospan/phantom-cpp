/* TODO LICENCE HERE */

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include <phantom/reflection/LValueReferenceType.h>
#include <phantom/reflection/LValueReferenceType.hxx>
#include <phantom/reflection/Expression.h>
/* *********************************************** */
o_registerN((phantom, reflection), LValueReferenceType);

o_namespace_begin(phantom, reflection) 

o_define_meta_type(LValueReferenceType);

LValueReferenceType::LValueReferenceType( Type* a_pReferencedType ) 
    : ReferenceType(a_pReferencedType, "&")    
{
}

bool LValueReferenceType::partialAccepts( Type* a_pType, size_t& a_Score, map<Placeholder*, LanguageElement*>& a_DeducedConstants ) const
{
    if(a_pType->asLValueReferenceType())
    {
        a_Score += 10;
        return m_pReferencedType ? m_pReferencedType->partialAccepts(a_pType->removeReference(), a_Score, a_DeducedConstants) : false;
    }
    return false;
}

o_namespace_end(phantom, reflection)