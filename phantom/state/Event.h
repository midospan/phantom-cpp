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

#ifndef state_Event_h__
#define state_Event_h__



/* ****************** Includes ******************* */

/* *********************************************** */
/* The *.classdef.h file must be the last #include */
#include "Event.classdef.h"
/* **************** Declarations ***************** */

/* *********************************************** */

o_h_begin


class o_export Event : public StateMachineElement
{
    o_friend(class, phantom, state, StateMachine)

    Reflection_____________________________________________________________________________________
    _____________________________________________________________________________________Reflection
public:
    Event(const string& a_strName, uint id, bitfield a_bfModifiers = bitfield());
    ~Event() {}

    uint getId() const  { return m_uiId; }
    
protected:
    uint    m_uiId;
};
/*

#pragma message(o_PP_QUOTE_L3(o_h_end))

}} 
namespace phantom 
{ 
  template<> 
  struct meta_specifiers<phantom::state::Event > 
  { 
    const static int value = phantom::state::Event ::meta_specifiers; 
  }; 
} 
namespace phantom 
{ 
  template<> 
  struct object_dynamic_cast<phantom::state::Event > 
  { 
    __forceinline static void* apply(reflection::Class* a_pClass, phantom::state::Event * a_pBase) 
    { 
      return phantom::state::Event ::PHANTOM_CODEGEN_static_member_function_DynamicCast(a_pClass, a_pBase); 
    } 
  }; 
} 
namespace phantom 
{ 
  template<> 
  class super_class_index_of< phantom::state::Event , phantom::state::Event ::super_class_0 > 
  { 
    const static int code = 0; 
  }; 
} 
namespace phantom { 
  template<> 
  class extension<phantom::state::Event > 
  { 
    typedef phantom::state::Event type; 
  public: typedef ::boost::fast_pool_allocator<type, phantom::memory::malloc_free_allocator_for_boost> allocator; 
          typedef phantom::constructor_helper<type, default_constructor> constructor; 
          typedef phantom::installer_helper<type, default_installer> installer; 
          typedef phantom::initializer_helper<type, no_initializer> initializer; 
  }; 
}*/


o_h_end


#else // state_Event_h__
#include "Event.classdef.h"
#endif
