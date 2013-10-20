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
#include <phantom/Object.h>
/* *********************************************** */

o_cpp_begin


ReflectionCPP__________________________________________________________________________________
    o_member_function(void, destroy, ());
    o_signal(destroyed, ());
__________________________________________________________________________________ReflectionCPP

Object::~Object()
{
}

void Object::destroy()
{
    Object* me = this;
    o_dynamic_delete_clean(me);
}

reflection::Class* Object::getClass() const
{
    return phantom::classOf(this);
}

void Object::deleteNow()
{
    getClass()->deleteInstance(this);
}

phantom::signal_t Object::destroyed( void ) const
{
    connection::slot* pSlot = PHANTOM_CODEGEN_m_slot_list_of_destroyed.head();
    while(pSlot)
    {
        connection::pair::push(const_cast<Object*>(this), pSlot);
        pSlot->subroutine()->call(pSlot->receiver(), o_no_arg );
        pSlot = pSlot->next();
        connection::pair::pop();
    }
    return signal_t();
}

o_cpp_end
