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
#include <phantom/reflection/DataExpression.h>
#include <phantom/reflection/DataExpression.hxx>
/* *********************************************** */
o_registerN((phantom, reflection), DataExpression);

o_namespace_begin(phantom, reflection) 

DataExpression::DataExpression(serialization::DataBase* a_pDataBase, Expression* a_pGuidExpression)
    : Expression(a_pDataBase->getData(a_pGuidExpression->get().as<uint>()).type()->referenceType()
                , "@("+a_pGuidExpression->getName()+")")
                , m_pGuidExpression((a_pGuidExpression AND a_pGuidExpression->getOwner()) ? a_pGuidExpression->clone() : a_pGuidExpression)
    , m_pDataBase(a_pDataBase)
{
    if(m_pGuidExpression)
    {
        o_assert(m_pGuidExpression->getValueType()->isImplicitlyConvertibleTo(typeOf<uint>()));
        m_pConvertedGuidExpression = m_pGuidExpression->implicitCast(typeOf<uint>());
        addSubExpression(m_pConvertedGuidExpression);
    }
}

void DataExpression::getValue( void* a_pDest ) const
{
    uint value = 0;
    m_pConvertedGuidExpression->load(&value);
    *((void**)a_pDest) = m_pDataBase->getData(value).address(); 
}

DataExpression* DataExpression::clone() const
{
    return o_new(DataExpression)(m_pDataBase, m_pGuidExpression);
}

o_namespace_end(phantom, reflection)
