/* TODO LICENCE HERE */

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include <phantom/reflection/PrimitiveType.h>
#include <phantom/reflection/PrimitiveType.hxx>
#include <phantom/string.hxx>
/* *********************************************** */
o_registerN((phantom, reflection), PrimitiveType);

o_namespace_begin(phantom, reflection) 

o_define_meta_type(PrimitiveType);

PrimitiveType::PrimitiveType(ETypeId a_eTypeId) 
: Type(a_eTypeId, "", 0, 0, 0)
{

}

PrimitiveType::PrimitiveType(ETypeId a_eTypeId, const string& a_strName, ushort a_uiSize, ushort a_uiAlignment, modifiers_t a_Modifiers /*= 0*/ ) 
    : Type(a_eTypeId, a_strName, a_uiSize, a_uiAlignment, a_Modifiers)
{

}

o_namespace_end(phantom, reflection)
