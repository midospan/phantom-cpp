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

#ifndef o_phantom_reflection_TBinaryBitExpression_h__
#define o_phantom_reflection_TBinaryBitExpression_h__

/* ****************** Includes ******************* */
#include <phantom/reflection/BinaryOperationExpression.h>
/* **************** Declarations ***************** */
o_declareNT(class, (phantom, reflection), (typename), (t_Ty), TBinaryBitExpression);
/* *********************************************** */

o_namespace_begin(phantom, reflection)

inline Type* TBinaryBitExpression_ExpressionValueType(Expression* a_pLeftExpression, Expression* a_pRightExpression)
{
    return (a_pLeftExpression->getValueType()->getTypeId() > a_pRightExpression->getValueType()->getTypeId()) 
        ? a_pLeftExpression->getValueType()->promote() 
        : a_pRightExpression->getValueType()->promote();
}

template<typename t_Ty>
class TBinaryBitExpression : public BinaryOperationExpression
{
    o_static_assert(boost::is_integral<t_Ty>::value OR boost::is_pointer<t_Ty>::value);
    typedef o_NESTED_TYPE boost::promote<t_Ty>::type promoted_type;
public:
    TBinaryBitExpression( const string& a_strOperator, Expression* a_pLeftExpression, Expression* a_pRightExpression )
        : BinaryOperationExpression(TBinaryBitExpression_ExpressionValueType(a_pLeftExpression, a_pRightExpression)
        , a_strOperator
        , a_pLeftExpression
        , a_pRightExpression)
    {
        o_assert(m_pLeftExpression->getValueType()->removeReference() == typeOf<promoted_type>());
        o_assert(m_pRightExpression->getValueType()->removeReference() == typeOf<promoted_type>());
    }

    virtual void    internalEval(void* a_pDest) const 
    {
        promoted_type* _where = (promoted_type*)a_pDest;
        promoted_type _intermediate;
        switch(m_strOperator[0])
        {
        case '&':
            m_pConvertedLeftExpression->load(_where);
            m_pConvertedRightExpression->load(&_intermediate);
            *_where &= _intermediate;
            break;
        case '|':
            m_pConvertedLeftExpression->load(_where);
            m_pConvertedRightExpression->load(&_intermediate);
            *_where |= _intermediate;
            break;
        case '^':
            m_pConvertedLeftExpression->load(_where);
            m_pConvertedRightExpression->load(&_intermediate);
            *_where ^= _intermediate;
            break;
        }
    }

    virtual TBinaryBitExpression<t_Ty>*     clone() const 
    {
        return o_new(TBinaryBitExpression<t_Ty>)(m_strOperator, m_pLeftExpression, m_pRightExpression);
    }

};

o_namespace_end(phantom, reflection)



#endif
