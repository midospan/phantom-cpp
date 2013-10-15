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

#ifndef util_Comparator_h__
#define util_Comparator_h__
// #pragma message("Including "__FILE__)



/* ****************** Includes ******************* */

/* *********************************************** */
/* The *.classdef.h file must be the last #include */
#include "Comparator.classdef.h"
/* **************** Declarations ***************** */

/* *********************************************** */


o_h_begin


class o_export Comparator : public Object
{
public:
    Reflection_____________________________________________________________________________________
    _____________________________________________________________________________________Reflection
public:

    struct std_adapter
    {
        std_adapter(Comparator* a_pComparator)
            : m_pComparator(a_pComparator){}
        
        inline bool        operator()(void* one, void* another) const
        {
            return m_pComparator->compare(one, another) > 0;
        }
        Comparator* m_pComparator;
    };
    struct std_reversed_adapter
    {
        std_reversed_adapter(Comparator* a_pComparator)
            : m_pComparator(a_pComparator) {}

        inline bool        operator()(void* one, void* another)  const
        {
            return m_pComparator->compare(another, one) > 0;
        }
        Comparator* m_pComparator;
    };
    virtual int32        compare(void*,void*) const = 0;

protected:
    
};

o_h_end


#else // util_Comparator_h__
#include "Comparator.classdef.h"
#endif
