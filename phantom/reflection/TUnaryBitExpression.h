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

#ifndef o_phantom_reflection_TUnaryBitExpression_h__
#define o_phantom_reflection_TUnaryBitExpression_h__

/* ****************** Includes ******************* */
#include <phantom/reflection/PreUnaryOperationExpression.h>
/* **************** Declarations ***************** */
o_declareNT(class, (phantom, reflection), (typename), (t_Ty), TUnaryBitExpression);
/* *********************************************** */

o_namespace_begin(phantom, reflection)

template<typename t_Ty>
class TUnaryBitExpression : public PreUnaryOperationExpression
{
public:
    TUnaryBitExpression( const string& a_strOperator, Expression* a_pExpression )
        : PreUnaryOperationExpression(
        typeOf<t_Ty>()
        , a_strOperator
        , a_pExpression)
    {
    }

    virtual void    getValue(void* a_pDest) const 
    {
        t_Ty* _where = (t_Ty*)a_pDest;
        switch(m_strOperator[0])
        {
        case '~':
            m_pExpression->load(_where);
#pragma warning(disable:4800)
#pragma warning(disable:4804)
            *_where = (t_Ty)~(*_where);
#pragma warning(default:4804)
#pragma warning(default:4800)
            break;
        }
    }

    virtual TUnaryBitExpression<t_Ty>*     clone() const 
    {
        return o_new(TUnaryBitExpression<t_Ty>)(m_strOperator, m_pExpression);
    }
};

o_namespace_end(phantom, reflection)



#endif