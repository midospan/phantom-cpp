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

#ifndef o_phantom_reflection_BinaryOperationExpression_h__
#define o_phantom_reflection_BinaryOperationExpression_h__



/* ****************** Includes ******************* */
#include <phantom/reflection/Expression.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, reflection), BinaryOperationExpression);
/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export BinaryOperationExpression : public Expression
{
public:
    BinaryOperationExpression( Type* a_pType, const string& a_strOperator, Expression* a_pLHSExpression, Expression* a_pRHSExpression );
    BinaryOperationExpression( Type* a_pLHSType, Type* a_pRHSType, const string& a_strOperator, Expression* a_pLHSExpression, Expression* a_pRHSExpression );
    BinaryOperationExpression( Type* a_pValueType, Type* a_pLHSType, Type* a_pRHSType, const string& a_strOperator, Expression* a_pLHSExpression, Expression* a_pRHSExpression );
    ~BinaryOperationExpression();

    virtual void    getValue(void* a_pDest) const = 0;

    virtual void    flush() const { m_pLHSExpression->flush(); m_pRHSExpression->flush(); }

    virtual bool    hasValueStorage() const { return false; }

    Expression*     getLHSExpression() const { return m_pLHSExpression; }
    Expression*     getRHSExpression() const { return m_pRHSExpression; }

    Expression*     getLHSConvertedExpression() const { return m_pLHSConvertedExpression; }
    Expression*     getRHSConvertedExpression() const { return m_pRHSConvertedExpression; }

protected:
    string          m_strOperator;
    Expression*     m_pLHSExpression;
    Expression*     m_pRHSExpression;
    Expression*     m_pLHSConvertedExpression;
    Expression*     m_pRHSConvertedExpression;

};

o_namespace_end(phantom, reflection)



#endif
