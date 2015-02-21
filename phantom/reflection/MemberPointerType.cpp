/* TODO LICENCE HERE */

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include <phantom/reflection/MemberPointerType.h>
#include <phantom/reflection/MemberPointerType.hxx>
/* *********************************************** */
o_registerN((phantom, reflection), MemberPointerType);

o_namespace_begin(phantom, reflection) 

o_define_meta_type(MemberPointerType);

MemberPointerType::MemberPointerType( ClassType* a_pObjectType, ushort a_uiSize, ushort a_uiAlignment, modifiers_t a_Modifiers /*= 0*/ ) : PrimitiveType(e_member_pointer, "", a_uiSize, a_uiAlignment, a_Modifiers)
{
}

o_destructor MemberPointerType::~MemberPointerType( void )
{
}


o_namespace_end(phantom, reflection)