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
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/fstream.hpp>
#include <phantom/serialization/FileTreeNode.h>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/fstream.hpp>
#include <phantom/serialization/FileTreeDataStateBase.h>
#include <phantom/serialization/FileTreeDataStateBase.hxx>
/* *********************************************** */
o_registerN((phantom, serialization), FileTreeDataStateBase);

o_namespace_begin(phantom, serialization)

FileTreeDataStateBase::FileTreeDataStateBase( const string& a_Url, uint a_uiSerializationFlag ) 
    : DataStateBase(a_Url, a_uiSerializationFlag)
{
}

bool FileTreeDataStateBase::hasStateSaved( Node* a_pNode, uint a_uiStateId ) const
{
    const string & path = statePath(a_pNode, a_uiStateId);
    boost::filesystem::path p((path).c_str());
    return boost::filesystem::exists(p);
}

string FileTreeDataStateBase::statePath( Node* a_pNode, uint a_uiStateId ) const
{
    Node* pParent = a_pNode->getParentNode();
    string path = pParent
        ? statePath(pParent, a_uiStateId) 
        : getUrl() + "/[" + phantom::lexical_cast<string>(reinterpret_cast<void*>(a_uiStateId)) + "]";
    path += "/[";
    path += phantom::lexical_cast<string>(reinterpret_cast<void*>(a_pNode->getGuid()));
    path += "]";
    return path;
}

string FileTreeDataStateBase::dataPath( const phantom::data& a_Data, uint a_uiGuid, Node* a_pNode, uint a_uiStateId ) const
{
    string path = statePath(a_pNode, a_uiStateId);
    path += "/[";
    path += phantom::lexical_cast<string>(reinterpret_cast<void*>(a_uiGuid));
    path += "]";
    return path;
}




o_namespace_end(phantom, serialization)
