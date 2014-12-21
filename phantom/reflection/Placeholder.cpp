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
#include <phantom/reflection/Placeholder.h>
#include <phantom/reflection/Placeholder.hxx>
/* *********************************************** */
o_registerN((phantom, reflection), Placeholder);

o_namespace_begin(phantom, reflection) 

o_define_meta_type(Placeholder);
o_define_meta_type(PlaceholderType);
o_define_meta_type(PlaceholderClass);
o_define_meta_type(PlaceholderSubroutine);
o_define_meta_type(PlaceholderConstant);
o_define_meta_type(PlaceholderInstanceDataMember);

Constant* PlaceholderConstant::clone() const
{
    return o_new(PlaceholderConstant)(m_pType, m_strName, m_pTemplateParameterDependencies->front(), m_Modifiers);
}

o_namespace_end(phantom, reflection)

