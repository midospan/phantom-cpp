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

#ifndef o_phantom_reflection_TShiftExpression_h__
#define o_phantom_reflection_TShiftExpression_h__



/* ****************** Includes ******************* */
#include <phantom/reflection/BinaryOperationExpression.h>
/* **************** Declarations ***************** */
o_declareNT(class, (phantom, reflection), (typename), (t_Ty), TShiftExpression);
/* *********************************************** */

o_namespace_begin(phantom, reflection)


template<typename t_Ty>
class  TShiftExpression : public BinaryOperationExpression
{
    o_static_assert(boost::is_integral<t_Ty>::value);
public:
    TShiftExpression( const string& a_strOperator, Expression* a_pLHSExpression, Expression* a_pRHSExpression )
        : BinaryOperationExpression(typeOf<t_Ty>(), typeOf<int>()
        , a_strOperator
        , a_pLHSExpression
        , a_pRHSExpression)
    {
        o_assert(m_pRHSConvertedExpression->getValueType() == typeOf<int>());
    }

    virtual void    getValue(void* a_pDest) const 
    {
        t_Ty* _where = (t_Ty*)a_pDest;
        int _intermediate;
        switch(m_strOperator[0])
        {
#pragma warning(disable:4804)
#pragma warning(disable:4800)
        case '<':
            m_pLHSConvertedExpression->load(_where);
            m_pRHSConvertedExpression->load(&_intermediate);
            *_where <<= _intermediate;
            break;
        case '>':
            m_pLHSConvertedExpression->load(_where);
            m_pRHSConvertedExpression->load(&_intermediate);
            *_where >>= _intermediate;
            break;
#pragma warning(default:4804)
#pragma warning(default:4800)
        }
    }

    virtual TShiftExpression<t_Ty>*     clone() const 
    {
        return o_new(TShiftExpression<t_Ty>)(m_strOperator, m_pLHSExpression, m_pRHSExpression);
    }

};

o_namespace_end(phantom, reflection)



#endif
