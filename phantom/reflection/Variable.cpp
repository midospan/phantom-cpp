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
#include <phantom/reflection/Variable.h>
#include <phantom/reflection/Variable.hxx>
/* *********************************************** */
o_registerN((phantom, reflection), Variable);

o_namespace_begin(phantom, reflection) 

Variable::Variable() : m_pRange(nullptr)
{

}

Variable::Variable( const string& a_strName, bitfield a_Modifiers /*= 0*/ ) 
    : Constant(a_strName, a_Modifiers)
    , m_pRange(nullptr)
{

}

Variable::Variable( const string& a_strName, Range* a_pRange, bitfield a_Modifiers /*= 0*/ ) 
    : Constant(a_strName, a_Modifiers)
    , m_pRange(a_pRange)
{
    if(m_pRange)
    {
        addElement(m_pRange);
    }
}

phantom::signal_t Variable::valueChanged() const
{
    phantom::connection::slot* pSlot = PHANTOM_CODEGEN_m_slot_list_of_valueChanged.head();
    while(pSlot)
    {
        phantom::connection::pair::push(this, pSlot);
        pSlot->subroutine()->call( pSlot->receiver(), nullptr );
        pSlot = pSlot->next();
        phantom::connection::pair::pop();
    }
    return phantom::signal_t();
}

o_namespace_end(phantom, reflection)
