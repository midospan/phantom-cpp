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
#include "StateOrderingComparator.h"
/* *********************************************** */
o_registerN((phantom, state), StateOrderingComparator);

o_namespace_begin(phantom, state)

int StateOrderingComparator::compare( void* a_pS0, void* a_pS1 ) const
{
    State*    pState0 = phantom::as<State*>(a_pS0);
    State*    pState1 = phantom::as<State*>(a_pS1);
    
    o_assert(pState0);
    o_assert(pState1);

    reflection::Class* pOC0 = pState0->getOwnerStateMachine()->getOwnerClass();
    reflection::Class* pOC1 = pState1->getOwnerStateMachine()->getOwnerClass();
    if(pOC0 == pOC1)
    {
        if(pState1->getOrderingFactor() == pState0->getOrderingFactor()) return 0;
        if(pState1->getOrderingFactor() > pState0->getOrderingFactor()) return 1;
        return -1;
    }
    else
    {
        if(pOC1->isKindOf(pOC0)) return 1;
        o_assert(pOC0->isKindOf(pOC1)); // Compared state must be from same class hierarchy
        return -1;
    }
    return 0;
}

StateOrderingComparator* StateOrderingComparator::Instance()
{
    static StateOrderingComparator* s_Instance = NULL;
    if(s_Instance == NULL) 
    {
        s_Instance = o_new(StateOrderingComparator);
        phantom::registerSingleton(s_Instance);
    }
    return s_Instance;
}

o_namespace_end(phantom, state)