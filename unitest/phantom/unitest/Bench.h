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
o_declare(class, phantom, sc2, Ability);
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

o_classNS((sc2), Bench, (Marine))
{
    o_reflection 
    {

        o_property(float,          value0, setValue0, getValue0, o_no_signal, o_public);
        o_property(int,            value1, setValue1, getValue1, o_no_signal, o_public);
        o_property(unsigned int,   value2, setValue2, getValue2, o_no_signal, o_public);
        o_property(unsigned long,  value3, setValue3, getValue3, o_no_signal, o_public);
        o_property(bool,           value4, setValue4, getValue4, o_no_signal, o_public);
        o_property(char,           value5, setValue5, getValue5, o_no_signal, o_public);
        o_property(short,          value6, setValue6, getValue6, o_no_signal, o_public);
        o_property(long,           value7, setValue7, getValue7, o_no_signal, o_public);
        o_property(long long,      value8, setValue8, getValue8, o_no_signal, o_public);
        o_property(double,         value9, setValue9, getValue9, o_no_signal, o_public);
    };
    o_statechart
    {
        o_track(BenchTrack0, StimPackDisabled)
        o_state(BenchState0, BenchTrack0)
        o_track(BenchTrack1, BenchState0)
        o_state(BenchState1, BenchTrack1)
        o_track(BenchTrack2, BenchState1)
        o_state(BenchState2, BenchTrack2)
        o_track(BenchTrack3, BenchState2)
        o_state(BenchState3, BenchTrack3)
        o_track(BenchTrack4, BenchState3)
        o_state(BenchState4, BenchTrack4)
        o_track(BenchTrack5, BenchState4)
        o_state(BenchState5, BenchTrack5)
        o_track(BenchTrack6, BenchState5)
        o_state(BenchState6, BenchTrack6)
        o_track(BenchTrack7, BenchState6)
        o_state(BenchState7, BenchTrack7)
        o_track(BenchTrack8, BenchState7)
        o_state(BenchState8, BenchTrack8)
        o_track(BenchTrack9, BenchState8)
        o_state(BenchState9, BenchTrack9)
    };
};
o_exposeN((sc2), Bench);

o_static_assert(phantom::has_initializer_member_function_initialize<sc2::Bench>::value);
o_static_assert(!phantom::has_initializer_member_function_initialize_declared<sc2::Bench>::value);

#endif
