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

#ifndef o_sc2_Marine_h__
#define o_sc2_Marine_h__

/* ****************** Includes ******************* */
#include "Unit.h"
/* **************** Declarations ***************** */
o_declareN(class, (phantom, sc2), Ability);
/* *********************************************** */


o_namespace_begin(sc2)

class Marine : public Unit
{
public:
    Marine(void)  { m_iInitialLifePoints = 50; }
    o_destructor ~Marine(void) {}

    o_enter(Idle) 
    {

    }

    o_enter(Pooled) 
    {

    }

    o_enter(StimPackDisabled) {  }
    o_update(StimPackDisabled) { }
    o_leave(StimPackDisabled) {  }

    o_enter(StimPackEnabled) { if(m_iLifePoints > 10) m_iLifePoints -= 10; }
    o_update(StimPackEnabled) { }
    o_leave(StimPackEnabled) {  }



};

o_namespace_end(sc2)

#if o__int__reflection_template_use_level == 3
#include "Marine.hxx"
#else 
    o_declareN(class, (sc2), Marine);
#endif

#endif
