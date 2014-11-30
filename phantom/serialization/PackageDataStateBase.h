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

#ifndef serialization_PackageDataStateBase_h__
#define serialization_PackageDataStateBase_h__


/* ****************** Includes ******************* */
#include "phantom/serialization/DataStateBase.h"
/* **************** Declarations ***************** */
o_declareN(class, (phantom, serialization), PackageDataStateBase);
namespace boost { namespace filesystem { class path; } }
/* *********************************************** */


o_namespace_begin(phantom, serialization)

class PackageDataBase;
class o_export PackageDataStateBase : public DataStateBase
{
public:

    PackageDataStateBase(PackageDataBase* a_pDataBase, const string& a_strUrl, uint a_uiSerializationFlag);
    o_destructor ~PackageDataStateBase();

    virtual bool	hasStateSaved(Node* a_pNode, uint a_uiStateId) const;


protected:

    virtual void	loadState(Node* a_pNode, const vector<data>& a_Data, uint a_uiStateId) = 0;
    virtual void	saveState(Node* a_pNode, const vector<data>& a_Data, uint a_uiStateId) = 0;
};

o_namespace_end(phantom, serialization)

#endif //serialization_PackageDataStateBase_h__