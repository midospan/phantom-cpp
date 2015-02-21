/* TODO LICENCE HERE */

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include <phantom/reflection/Function.h>
#include <phantom/reflection/Function.hxx>
#include <phantom/reflection/CallExpression.h>
/* *********************************************** */
o_registerN((phantom, reflection), Function);


int   __stdcall o_function_test_stdcall(int) { return 0; }
int     __cdecl o_function_test_cdecl(int) { return 0; }
int  __fastcall o_function_test_fastcall(int) { return 0; }

o_function(int, o_function_test_stdcall, (int));
o_function(int, o_function_test_cdecl, (int));
o_function(int, o_function_test_fastcall, (int));

o_namespace_begin(phantom, reflection) 

Class* const Function::metaType = o_type_of(phantom::reflection::Function);

Function::Function(modifiers_t a_Modifiers /*= 0*/)
    : Subroutine(e_defaultcall, a_Modifiers)
{
    if(a_Modifiers&(o_const|o_virtual|o_abstract))
    {
        setInvalid();
    }
}

Function::Function( const string& a_strName, EABI a_eABI, modifiers_t a_Modifiers /*= 0*/ ) 
    : Subroutine(a_strName, a_eABI, a_Modifiers)
{
    if(a_Modifiers&(o_const|o_virtual|o_abstract))
    {
        setInvalid();
    }
}

Function::Function( const string& a_strName, Signature* a_pSignature, EABI a_eABI, modifiers_t a_Modifiers /*= 0*/ ) 
    : Subroutine(a_strName, a_pSignature, a_eABI, a_Modifiers)
{
    if(a_Modifiers&(o_const|o_virtual|o_abstract))
    {
        setInvalid();
    }
}

Function::Function( const string& a_strName, Signature* a_pSignature, modifiers_t a_Modifiers /*= 0*/ )
    : Subroutine(a_strName, a_pSignature, e_defaultcall, a_Modifiers)
{
    if(a_Modifiers&(o_const|o_virtual|o_abstract))
    {
        setInvalid();
    }
}

Function::Function( LanguageElement* a_pScope, const string& a_strName, const string& a_strSignature, EABI a_eABI, modifiers_t a_Modifiers /*= 0*/ )
    : Subroutine(a_pScope, a_strName, a_strSignature, a_eABI, a_Modifiers)
{
    if(a_Modifiers&(o_const|o_virtual|o_abstract))
    {
        setInvalid();
    }
}

o_namespace_end(phantom, reflection)
