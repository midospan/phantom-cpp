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
#include <phantom/reflection/ConstantExpression.h>
#include <phantom/reflection/DataExpression.h>
#include <phantom/reflection/ConstantExpression.hxx>
/* *********************************************** */
o_registerN((phantom, reflection), ConstantExpression);
o_namespace_begin(phantom, reflection) 

ConstantExpression::ConstantExpression(Constant* a_pConstant, Expression* a_pChildExpression /*= nullptr*/, bool a_bOwnsConstant /*= false*/)
    : Expression(a_pConstant->getValueType(), a_pConstant->getQualifiedDecoratedName(), 0)
    , m_pConstant(a_pConstant)
{
    //addReferencedElement(m_pConstant); // TODO : add o_native to Constant instead
    if(a_pChildExpression)
        addElement(a_pChildExpression);
//     if(a_bOwnsConstant) // TODO : fix the native constant thing to avoid this leak
//         addElement(m_pConstant);
}

void ConstantExpression::setValue( void const* a_pSrc ) const
{
    o_exception(exception::reflection_runtime_exception, "Constant cannot be assigned");
}

void ConstantExpression::getValue( void* a_pDest ) const
{
    m_pConstant->getValue(a_pDest);
}

LanguageElement* ConstantExpression::hatch()
{
    Constant* pConstant = m_pConstant;
    if(pConstant->getOwner() == this)
    {
        removeElement(pConstant);
    }
    phantom::deleteElement(this);
    return pConstant;
}

ConstantExpression* ConstantExpression::clone() const
{
    // TODO : add clone function to Constant
    return o_new(ConstantExpression)(m_pConstant, (getElementCount() == 2) ? getElement(0)->asExpression()->clone() : nullptr, false);
}

o_namespace_end(phantom, reflection)
