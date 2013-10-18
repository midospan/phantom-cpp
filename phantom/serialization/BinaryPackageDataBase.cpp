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
#include "phantom/serialization/BinaryPackageNode.h"
#include <phantom/serialization/BinaryPackageDataBase.h>
/* *********************************************** */
o_registerN((phantom, serialization), BinaryPackageDataBase);

o_namespace_begin(phantom, serialization)

BinaryPackageDataBase::BinaryPackageDataBase(const string& a_strUrl, uint a_uiSerializationFlag)
: PackageDataBase(a_strUrl, a_uiSerializationFlag)
{

}

o_destructor BinaryPackageDataBase::~BinaryPackageDataBase()
{

}

string BinaryPackageDataBase::dataFileExtension(void* a_pData) const 
{
	return "bin"; 
}

Node* BinaryPackageDataBase::createNode(uint a_uiGuid, Node* a_pParentNode) const
{
  return NULL;
  /*o_new(BinaryPackageNode)(
    const_cast<BinaryPackageDataBase*>(this)
    , a_uiGuid
    , phantom::as<BinaryPackageNode*>(a_pParentNode));*/
}

void BinaryPackageDataBase::destroyNode(Node* a_pNode) const
{
    o_delete(BinaryPackageNode) a_pNode; 
}

o_namespace_end(phantom, serialization)