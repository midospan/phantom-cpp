/* TODO LICENCE HERE */

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include <phantom/reflection/Constructor.h>
#include <phantom/reflection/Constructor.hxx>
#include <phantom/vector.hxx>
/* *********************************************** */
o_registerN((phantom, reflection), Constructor);
o_registerNTI((phantom), vector, (phantom::reflection::Constructor*));

o_namespace_begin(phantom, reflection) 

Class* const Constructor::metaType = o_type_of(Constructor);

Constructor::Constructor()
{

}

Constructor::Constructor( const string& a_strName, Signature* a_pSignature , modifiers_t a_Modifiers) 
    : MemberFunction(a_strName, a_pSignature, a_Modifiers)
{

}

Constructor::Constructor( ClassType* a_pClassType, const string& a_strName, const string& a_strSignature, modifiers_t a_Modifiers) 
    : MemberFunction(a_pClassType, a_strName, a_strSignature, a_Modifiers)
{

}

o_namespace_end(phantom, reflection)