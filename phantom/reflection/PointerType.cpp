/* TODO LICENCE HERE */

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include <phantom/reflection/PointerType.h>
#include <phantom/reflection/PointerType.hxx>
/* *********************************************** */
o_registerN((phantom, reflection), PointerType);

o_namespace_begin(phantom, reflection) 

o_define_meta_type(PointerType);

void PointerType::less( void** a_pArgs, void* a_pOutput )
{
    *(bool*)a_pOutput = *(byte**)a_pArgs[0] < *(byte**)a_pArgs[1];
}

void PointerType::greater( void** a_pArgs, void* a_pOutput )
{
    *(bool*)a_pOutput = *(byte**)a_pArgs[0] > *(byte**)a_pArgs[1];
}

void PointerType::lessEqual( void** a_pArgs, void* a_pOutput )
{
    *(bool*)a_pOutput = *(byte**)a_pArgs[0] <= *(byte**)a_pArgs[1];
}

void PointerType::greaterEqual( void** a_pArgs, void* a_pOutput )
{
    *(bool*)a_pOutput = *(byte**)a_pArgs[0] >= *(byte**)a_pArgs[1];
}

void PointerType::equal( void** a_pArgs, void* a_pOutput )
{
    *(bool*)a_pOutput = *(byte**)a_pArgs[0] == *(byte**)a_pArgs[1];
}

void PointerType::notEqual( void** a_pArgs, void* a_pOutput )
{
    *(bool*)a_pOutput = *(byte**)a_pArgs[0] != *(byte**)a_pArgs[1];
}

void PointerType::assignment( void** a_pArgs, void* a_pOutput )
{
    *(byte**)a_pArgs[0] = *(byte**)a_pArgs[1];
    *(byte***)a_pOutput = (byte**)a_pArgs[0];
}

o_namespace_end(phantom, reflection)