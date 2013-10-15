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

#ifndef o_phantom_Object_h__
#define o_phantom_Object_h__

/* ****************** Includes ******************* */
//#include <phantom/PolymorphicBase.h>
/* *********************************************** */
/* The *.classdef.h file must be the last #include */
#include "Object.classdef.h"
/* **************** Declarations ***************** */

/* *********************************************** */



o_h_begin

namespace state
{
    namespace native
    {
        template <typename > class root_statechart;
    }
}

class o_export Object
{
    reflection_________________________________________
    _________________________________________reflection

public:
    Object()
    {
    }
    o_destructor virtual ~Object();

    void                            destroy();

    virtual void                    deleteNow();

    phantom::reflection::Class*     getClass() const;
    virtual boolean                 equals(Object* a_pObject) const { return a_pObject == this; }

    virtual string                  toString() const { return string(); }

    virtual boolean                 isArray() const { return false; }

    signal_t destroyed(void) const;

protected:

private:    // slot allocator
    mutable phantom::connection::slot::list    PHANTOM_CODEGEN_m_slot_list_of_output;
    mutable phantom::connection::slot::list    PHANTOM_CODEGEN_m_slot_list_of_destroyed;

};

o_h_end

    o_static_assert(phantom::detail::has_enclosed_reflection<phantom::Object>::value);

#else // o_phantom_Object_h__
#include "Object.classdef.h"
#endif
