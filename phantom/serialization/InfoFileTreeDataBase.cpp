/* TODO LICENCE HERE */

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#if o__bool__use_custom_stl_partioned_allocator OR o__bool__use_custom_stl_contiguous_allocator
#include <boost/property_tree_custom/info_parser.hpp>
#else 
#include <boost/property_tree/info_parser.hpp>
#endif
#include "phantom/serialization/InfoFileTreeNode.h"
#include <phantom/serialization/InfoFileTreeDataBase.h>
#include <phantom/serialization/InfoFileTreeDataBase.hxx>
/* *********************************************** */
o_registerN((phantom, serialization), InfoFileTreeDataBase);

o_namespace_begin(phantom, serialization)


Node* InfoFileTreeDataBase::createNode( uint a_Guid, Node* a_pParentNode ) const
{
  return o_new(InfoFileTreeNode)(
    const_cast<InfoFileTreeDataBase*>(this)
    , a_Guid
    , phantom::as<InfoFileTreeNode*>(a_pParentNode));
}

void InfoFileTreeDataBase::destroyNode( Node* a_pNode ) const
{
    o_delete(InfoFileTreeNode) a_pNode; 
}

void InfoFileTreeDataBase::write( const string& a_Path, const property_tree& a_Tree ) const
{
    property_tree_namespace::write_info(a_Path.c_str(), a_Tree, std::locale(), property_tree_namespace::info_parser::info_writer_settings<char>(' ', 4));
}

void InfoFileTreeDataBase::read( const string& a_Path, property_tree& a_Tree ) const
{
    property_tree_namespace::read_info(a_Path.c_str(), a_Tree);
}

o_namespace_end(phantom, serialization)