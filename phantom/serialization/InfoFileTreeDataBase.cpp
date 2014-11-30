/*
    This file is part of PHANTOM
         P reprocessed 
         H igh-level 
         A llocator 
         N ested state-machines and 
         T emplate 
         O riented 
         M eta-programming

    For the latest infos and sources, see http://code.google.com/p/phantom-cpp

    Copyright (C) 2008-2011 by Vivien MILLET

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
    THE SOFTWARE
*/

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