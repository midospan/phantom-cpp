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
#include <boost/property_tree_custom/xml_parser.hpp>
#else 
#include <boost/property_tree/xml_parser.hpp>
#endif
#include "phantom/serialization/XmlFileTreeNode.h"
#include <phantom/serialization/XmlFileTreeDataBase.h>
#include <phantom/serialization/XmlFileTreeDataBase.hxx>
#include <boost/algorithm/string.hpp>
/* *********************************************** */
o_registerN((phantom, serialization), XmlFileTreeDataBase);

o_namespace_begin(phantom, serialization)



    string tag_encodeQualifiedDecoratedNameToIdentifierName( const string& a_strTypeName )
{
    string encoded = a_strTypeName;
    boost::replace_all(encoded, "<", "&lt;");
    boost::replace_all(encoded, ">", "&gt;");
    boost::replace_all(encoded, " ", "&#032;");
    return encoded;
}

string tag_decodeQualifiedDecoratedNameFromIdentifierName( const string& a_strTypeName )
{
    string decoded = a_strTypeName;
    boost::replace_all(decoded, "&lt;", "<");
    boost::replace_all(decoded, "&gt;", ">");
    boost::replace_all(decoded, "&#032;"  , " ");
    return decoded;
}

property_tree encodeSpecialXmlCharacters(const property_tree& tree)
{
    property_tree encoded_tree;
    for(property_tree::const_iterator it = tree.begin(); it != tree.end(); ++it)
    {
        encoded_tree.add_child(tag_encodeQualifiedDecoratedNameToIdentifierName(it->first), encodeSpecialXmlCharacters(it->second));
    }
    encoded_tree.put_value(encodeQualifiedDecoratedNameToIdentifierName(tree.get_value<string>()));
    return encoded_tree;
}

property_tree decodeSpecialXmlCharacters(const property_tree& tree)
{
    property_tree decoded_tree;
    for(property_tree::const_iterator it = tree.begin(); it != tree.end(); ++it)
    {
        decoded_tree.add_child(tag_decodeQualifiedDecoratedNameFromIdentifierName(it->first), decodeSpecialXmlCharacters(it->second));
    }
    decoded_tree.put_value(decodeQualifiedDecoratedNameFromIdentifierName(tree.get_value<string>()));
    return decoded_tree;
}

Node* XmlFileTreeDataBase::createNode( uint a_Guid, Node* a_pParentNode ) const
{
  return o_new(XmlFileTreeNode)(
    const_cast<XmlFileTreeDataBase*>(this)
    , a_Guid
    , phantom::as<XmlFileTreeNode*>(a_pParentNode));
}

void XmlFileTreeDataBase::destroyNode( Node* a_pNode ) const
{
    o_delete(XmlFileTreeNode) a_pNode; 
}

void XmlFileTreeDataBase::write( const string& a_Path, const property_tree& a_Tree ) const
{
#if o__bool__use_custom_stl_partioned_allocator OR o__bool__use_custom_stl_contiguous_allocator
    property_tree_namespace::write_xml(a_Path, encodeSpecialXmlCharacters(a_Tree), std::locale(), property_tree_namespace::xml_parser::xml_writer_settings<string>(' ', 1));
#else
    property_tree_namespace::write_xml(a_Path, encodeSpecialXmlCharacters(a_Tree), std::locale(), property_tree_namespace::xml_parser::xml_writer_settings<char>(' ', 1));
#endif
}

void XmlFileTreeDataBase::read( const string& a_Path, property_tree& a_Tree ) const
{
    property_tree encoded;
    property_tree_namespace::read_xml(a_Path, encoded);
    a_Tree = decodeSpecialXmlCharacters(encoded);
}

o_namespace_end(phantom, serialization)