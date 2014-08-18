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
#include <phantom/reflection/StaticVariableAccess.h>
#include <phantom/reflection/StaticVariableAccess.hxx>
/* *********************************************** */
o_registerN((phantom, reflection), StaticVariableAccess);
o_namespace_begin(phantom, reflection) 

StaticVariableAccess::StaticVariableAccess(StaticVariable* a_pStaticVariable, Expression* a_pChildExpression /*= nullptr*/)
    : Expression(a_pStaticVariable->getValueType()->referenceType(), a_pStaticVariable->getQualifiedDecoratedName())
    , m_pStaticVariable(a_pStaticVariable)
{
    addReferencedElement(a_pStaticVariable);
    if(a_pChildExpression)
        addElement(a_pChildExpression);
}

void StaticVariableAccess::getValue( void* a_pDest ) const
{
    *((void**)a_pDest) = m_pStaticVariable->getAddress();
}

StaticVariableAccess* StaticVariableAccess::clone() const
{
    return o_new(StaticVariableAccess)(m_pStaticVariable, getElementCount() ? getElement(0)->asExpression()->clone() : nullptr);
}

o_namespace_end(phantom, reflection)
