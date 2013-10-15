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

#ifndef util_Interpolator_h__
#define util_Interpolator_h__
// #pragma message("Including "__FILE__)


/* ****************** Includes ******************* */
#include <phantom/util/AbstractInterpolator.h>
/* *********************************************** */
/* The *.classdef.h file must be the last #include */
#include "Interpolator.classdef.h"
/* **************** Declarations ***************** */

/* *********************************************** */


o_h_begin


class o_export Interpolator : public AbstractInterpolator
{
public:
    Reflection_____________________________________________________________________________________
    _____________________________________________________________________________________Reflection
public:

    Interpolator(void)     : m_pStart(NULL), m_pEnd(NULL), m_uiMode(0), m_pInterpolatedType(NULL)            {}
    o_destructor ~Interpolator(void)     {}


    virtual reflection::Type* getInterpolatedType() const { return m_pInterpolatedType; }
    void                    setInterpolatedType(reflection::Type* type) { m_pInterpolatedType = type; }
    
    virtual void            setStartValueAddress(void* a_pAddress) { m_pStart = a_pAddress; }
    virtual void*            getStartValueAddress() const { return m_pStart; }

    virtual void*            getEndValueAddress() const    { return m_pEnd; }
    virtual void            setEndValueAddress(void* a_pAddress) { m_pEnd = a_pAddress; }

    virtual uint            getMode() const            { return m_uiMode; }
    void                    setMode(uint m)            { m_uiMode = m; }

protected:
    reflection::Type*                m_pInterpolatedType;
    uint                m_uiMode;
    void*                m_pStart;
    void*                m_pEnd;
    
};

o_h_end


#else // util_Interpolator_h__
#include "Interpolator.classdef.h"
#endif
