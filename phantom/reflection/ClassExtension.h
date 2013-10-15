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

#ifndef o_phantom_reflection_ClassExtension_h__
#define o_phantom_reflection_ClassExtension_h__



/* ****************** Includes ******************* */
#include <phantom/reflection/LanguageElement.h>
/* *********************************************** */
/* The *.classdef.h file must be the last #include */
#include "ClassExtension.classdef.h"
/* ************* Class Declarations ************** */

/* *********************************************** */

o_h_begin

class o_export ClassExtension : public LanguageElement
{
public:
    Reflection_____________________________________________________________________________________
    _____________________________________________________________________________________Reflection
public:
    
    ClassExtension();

    o_initialize();

    virtual boolean        isExtension() const { return true; }

    Class*        getOwnerClass() const { return static_cast<Class*>(m_pOwner); }

};

o_h_end


#else // o_phantom_reflection_ClassExtension_h__
#include "ClassExtension.classdef.h"
#endif
