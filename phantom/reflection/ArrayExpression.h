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

#ifndef o_phantom_reflection_ArrayExpression_h__
#define o_phantom_reflection_ArrayExpression_h__



/* ****************** Includes ******************* */
#include <phantom/reflection/Expression.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, reflection), ArrayExpression);
/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export ArrayExpression : public Expression
{
    o_language_element;

public:
    ArrayExpression(Expression* a_pLeftExpression, Expression* a_pIndexExpression);
    ArrayExpression(ArrayType* a_pArrayType, Expression* a_pLeftExpression, Expression* a_pIndexExpression);
    ArrayExpression(ConstType* a_pConstArrayType, Expression* a_pLeftExpression, Expression* a_pIndexExpression);

    virtual ArrayExpression*    asArrayExpression() const { return (ArrayExpression*)this; }

    virtual void                internalEval(void* a_pDest) const 
    {
        size_t index;
        m_pIndexExpression->internalEval(&index);
        *((void**)a_pDest) = m_pArrayType->getElementAddress(m_pLeftExpression->loadEffectiveAddress(), index);
    }

    Expression*                 getLeftExpression() const { return m_pLeftExpression; }

    Expression*                 getIndexExpression() const { return m_pIndexExpression; }

    virtual bool                isPersistent() const;

    virtual void                flush() const;

    virtual ArrayExpression*    clone() const;

    ArrayType*                  getArrayType() const { return m_pArrayType; }

protected:
    void referencedElementRemoved( LanguageElement* a_pElement );

protected:
    ArrayType*      m_pArrayType;
    Expression*     m_pLeftExpression;
    Expression*     m_pIndexExpression;

};

o_namespace_end(phantom, reflection)



#endif
