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

#ifndef o_phantom_reflection_TBinaryIntegralExpression_h__
#define o_phantom_reflection_TBinaryIntegralExpression_h__



/* ****************** Includes ******************* */
#include <phantom/reflection/BinaryOperationExpression.h>
/* **************** Declarations ***************** */
o_declareNT(class, (phantom, reflection), (typename), (t_Ty), TBinaryIntegralExpression);
/* *********************************************** */

o_namespace_begin(phantom, reflection)


template<typename t_Ty>
class  TBinaryIntegralExpression : public BinaryOperationExpression
{
    o_static_assert(boost::is_integral<t_Ty>::value);
public:
    TBinaryIntegralExpression( const string& a_strOperator, Expression* a_pLeftExpression, Expression* a_pRightExpression )
        : BinaryOperationExpression(typeOf<t_Ty>()
        , a_strOperator
        , a_pLeftExpression
        , a_pRightExpression)
    {
        o_assert(m_pConvertedLeftExpression->getValueType()->removeReference() == typeOf<t_Ty>());
        o_assert(m_pConvertedRightExpression->getValueType()->removeReference() == typeOf<t_Ty>());
    }

    virtual void    internalEval(void* a_pDest) const 
    {
        t_Ty* _where = (t_Ty*)a_pDest;
        t_Ty _intermediate;
        switch(m_strOperator[0])
        {
        case '%':
            m_pConvertedLeftExpression->load(_where);
            m_pConvertedRightExpression->load(&_intermediate);
#pragma warning(disable:4800)
#pragma warning(disable:4804)
            *_where %= _intermediate;
#pragma warning(default:4804)
#pragma warning(default:4800)
            break;
        }
    }

    virtual TBinaryIntegralExpression<t_Ty>*     clone() const 
    {
        return o_new(TBinaryIntegralExpression<t_Ty>)(m_strOperator, m_pLeftExpression, m_pRightExpression);
    }

};

o_namespace_end(phantom, reflection)



#endif
