/* TODO LICENCE HERE */

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include <phantom/reflection/Structure.h>
#include <phantom/reflection/Structure.hxx>
/* *********************************************** */
o_registerN((phantom, reflection), Structure);

o_namespace_begin(phantom, reflection) 

o_define_meta_type(Structure);

Structure::Structure()
    : ClassType( e_structure, new extra_data )
{

}

Structure::Structure( const string& a_strName, modifiers_t a_Modifiers /*= 0*/ ) 
    : ClassType( e_structure, new extra_data, a_strName, a_Modifiers)
{

}

Structure::Structure( const string& a_strName, ushort a_uiSize, ushort a_uiAlignment, modifiers_t a_Modifiers /*= 0*/ ) 
    : ClassType(e_structure, a_strName, a_uiSize, a_uiAlignment, a_Modifiers)
{

}

o_namespace_end(phantom, reflection)

