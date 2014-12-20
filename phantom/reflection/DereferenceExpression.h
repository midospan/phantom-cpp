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

#ifndef o_phantom_reflection_DereferenceExpression_h__
#define o_phantom_reflection_DereferenceExpression_h__



/* ****************** Includes ******************* */
#include "phantom/reflection/Expression.h"
/* **************** Declarations ***************** */
o_declareN(class, (phantom, reflection), DereferenceExpression);
/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export DereferenceExpression : public Expression
{
    o_language_element;

public:
    DereferenceExpression(Expression* a_pDereferenceableExpression);

    virtual DereferenceExpression*  asDereferenceExpression() const { return (DereferenceExpression*)this; }

    virtual void                    internalEval(void* a_pDest) const;

    virtual void flush() const;

    virtual Expression*     reference() const
    {
        return const_cast<DereferenceExpression*>(this);
    }

    virtual Expression*     address() const
    {
        Expression* pExp = m_pDereferencedExpression;
        const_cast<DereferenceExpression*>(this)->removeElement(pExp);
        o_dynamic_delete const_cast<DereferenceExpression*>(this);
        return pExp;
    }

    Expression* getDereferencedExpression() const { return m_pDereferencedExpression; }

    virtual Expression*     clone() const;

protected:
    Expression* m_pDereferencedExpression;
};

o_namespace_end(phantom, reflection)



#endif
