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

#ifndef o_phantom_reflection_TBinaryBooleanExpression_h__
#define o_phantom_reflection_TBinaryBooleanExpression_h__



/* ****************** Includes ******************* */
#include <phantom/reflection/BinaryOperationExpression.h>
/* **************** Declarations ***************** */
o_declareNT(class, (phantom, reflection), (typename), (t_Ty), TBinaryBooleanExpression);
/* *********************************************** */

o_namespace_begin(phantom, reflection)


template<typename t_Ty>
class  TBinaryBooleanExpression : public BinaryOperationExpression
{
    o_static_assert(boost::is_fundamental<t_Ty>::value OR boost::is_pointer<t_Ty>::value);
    typedef o_NESTED_TYPE boost::promote<t_Ty>::type promoted_type;
public:
    TBinaryBooleanExpression( const string& a_strOperator, Expression* a_pLeftExpression, Expression* a_pRightExpression )
        : BinaryOperationExpression(typeOf<bool>()
        , typeOf<t_Ty>()
        , typeOf<t_Ty>()
        , a_strOperator
        , a_pLeftExpression
        , a_pRightExpression)
    {
        o_assert(m_pLeftExpression->getValueType()->removeReference()->removeConst()->getTypeId() <= typeOf<t_Ty>()->getTypeId());
        o_assert(m_pRightExpression->getValueType()->removeReference()->removeConst()->getTypeId() <= typeOf<t_Ty>()->getTypeId());
        o_assert(m_pConvertedLeftExpression->getValueType()->removeReference() == typeOf<t_Ty>());
        o_assert(m_pConvertedRightExpression->getValueType()->removeReference() == typeOf<t_Ty>());
    }

    virtual void    internalEval(void* a_pDest) const 
    {
        bool* _where = (bool*)a_pDest;
        promoted_type _op0;
        promoted_type _op1;
        if(m_strOperator.size() == 2)
        {
            o_assert(m_strOperator[1] == '=');
            switch(m_strOperator[0])
            {
            case '<':
                m_pConvertedLeftExpression->load(&_op0);
                m_pConvertedRightExpression->load(&_op1);
                *_where = _op0 <= _op1;
                break;
            case '>':
                m_pConvertedLeftExpression->load(&_op0);
                m_pConvertedRightExpression->load(&_op1);
                *_where = _op0 >= _op1;
                break;
            case '=':
                m_pConvertedLeftExpression->load(&_op0);
                m_pConvertedRightExpression->load(&_op1);
                *_where = _op0 == _op1;
                break;
            case '!':
                m_pConvertedLeftExpression->load(&_op0);
                m_pConvertedRightExpression->load(&_op1);
                *_where = _op0 != _op1;
                break;
            }
        }
        else 
        {
            o_assert(m_strOperator.size() == 1);
            switch(m_strOperator[0])
            {
            case '<':
                m_pConvertedLeftExpression->load(&_op0);
                m_pConvertedRightExpression->load(&_op1);
                *_where = _op0 < _op1;
                break;
            case '>':
                m_pConvertedLeftExpression->load(&_op0);
                m_pConvertedRightExpression->load(&_op1);
                *_where = _op0 > _op1;
                break;

            }
        }
    }

    virtual TBinaryBooleanExpression<t_Ty>*     clone() const 
    {
        return o_new(TBinaryBooleanExpression<t_Ty>)(m_strOperator, m_pLeftExpression, m_pRightExpression);
    }

};

o_namespace_end(phantom, reflection)



#endif
