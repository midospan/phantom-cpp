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
/* ** The Class Header must be the last #include * */
#include <phantom/reflection/VirtualMemberFunctionTable.h>
/* *********************************************** */
o_cpp_begin 

ReflectionCPP__________________________________________________________________________________
__________________________________________________________________________________ReflectionCPP


VirtualMemberFunctionTable::VirtualMemberFunctionTable( Class* a_pBaseClass, member_function_list* a_MemberFunctionList ) 
: m_pBaseClass(a_pBaseClass)
, m_ppMemberFunctions(NULL)
{
    m_uiSize = a_MemberFunctionList->size();
    if(m_uiSize > 0)
    {
        m_ppMemberFunctions = o_allocate_n(m_uiSize, InstanceMemberFunction*);
        member_function_list::const_iterator it = a_MemberFunctionList->begin();
        for(uint i = 0; i<m_uiSize; ++i)
        {
            o_assert(it != a_MemberFunctionList->end());
            m_ppMemberFunctions[i] = *it;
            it++;
        }
    }
}

uint VirtualMemberFunctionTable::getIndexOf( InstanceMemberFunction* a_pMemberFunction )
{
    uint i = 0;
    for(;i<m_uiSize; ++i )
    {
        if(m_ppMemberFunctions[i] == a_pMemberFunction) return i;
    }
    return i;
}

o_destructor VirtualMemberFunctionTable::~VirtualMemberFunctionTable( void )
{
    o_deallocate_n(m_ppMemberFunctions, m_uiSize, InstanceMemberFunction*);
}

o_cpp_end