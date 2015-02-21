/* TODO LICENCE HERE */

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#if o__bool__use_custom_stl_partioned_allocator OR o__bool__use_custom_stl_contiguous_allocator
#include <boost/property_tree_custom/json_parser.hpp>
#else 
#include <boost/property_tree/json_parser.hpp>
#endif
#include "phantom/serialization/JsonFileTreeNode.h"
#include <phantom/serialization/JsonFileTreeDataBase.h>
#include <phantom/serialization/JsonFileTreeDataBase.hxx>
/* *********************************************** */
o_registerN((phantom, serialization), JsonFileTreeDataBase);

o_namespace_begin(phantom, serialization)


Node* JsonFileTreeDataBase::createNode( uint a_Guid, Node* a_pParentNode ) const
{
  return o_new(JsonFileTreeNode)(
    const_cast<JsonFileTreeDataBase*>(this)
    , a_Guid
    , phantom::as<JsonFileTreeNode*>(a_pParentNode));
}

void JsonFileTreeDataBase::destroyNode( Node* a_pNode ) const
{
    o_delete(JsonFileTreeNode) a_pNode; 
}

void JsonFileTreeDataBase::write( const string& a_Path, const property_tree& a_Tree ) const
{
    property_tree_namespace::write_json(a_Path, a_Tree, std::locale(), true);
}

void JsonFileTreeDataBase::read( const string& a_Path, property_tree& a_Tree ) const
{
    property_tree_namespace::read_json(a_Path, a_Tree);
}

o_namespace_end(phantom, serialization)