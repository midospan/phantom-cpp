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

#ifndef o_sc2_Bench_h__
#define o_sc2_Bench_h__

/* ****************** Includes ******************* */
#include "Marine.h"
/* **************** Declarations ***************** */
o_declareN(class, (phantom, sc2), Ability);
/* *********************************************** */


o_namespace_begin(sc2)

class Bench : public Marine
{
public:
    Bench(void)  { }
    o_destructor ~Bench(void) {}

    o_enter(BenchState0) {} o_update(BenchState0) {} o_leave(BenchState0) {}
    o_enter(BenchState1) {} o_update(BenchState1) {} o_leave(BenchState1) {}
    o_enter(BenchState2) {} o_update(BenchState2) {} o_leave(BenchState2) {}
    o_enter(BenchState3) {} o_update(BenchState3) {} o_leave(BenchState3) {}
    o_enter(BenchState4) {} o_update(BenchState4) {} o_leave(BenchState4) {}
    o_enter(BenchState5) {} o_update(BenchState5) {} o_leave(BenchState5) {}
    o_enter(BenchState6) {} o_update(BenchState6) {} o_leave(BenchState6) {}
    o_enter(BenchState7) {} o_update(BenchState7) {} o_leave(BenchState7) {}
    o_enter(BenchState8) {} o_update(BenchState8) {} o_leave(BenchState8) {}
    o_enter(BenchState9) {} o_update(BenchState9) {} o_leave(BenchState9) {}

    void setValue0(float value) {} float getValue0() const {return 0;}
    void setValue1(int value) {} int getValue1() const {return 0;}
    void setValue2(unsigned int value) {} unsigned int getValue2() const {return 0;}
    void setValue3(unsigned long value) {} unsigned long getValue3() const {return 0;}
    void setValue4(bool value) {} bool getValue4() const {return 0;}
    void setValue5(char value) {} char getValue5() const {return 0;}
    void setValue6(short value) {} short getValue6() const {return 0;}
    void setValue7(long value) {} long getValue7() const {return 0;}
    void setValue8(long long value) {} long long getValue8() const {return 0;}
    void setValue9(double value) {} double getValue9() const {return 0;}

};

o_namespace_end(sc2)

#endif
