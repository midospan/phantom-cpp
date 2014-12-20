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

#ifndef o_phantom_reflection_TEqualityExpression_h__
#define o_phantom_reflection_TEqualityExpression_h__



/* ****************** Includes ******************* */
#include <phantom/reflection/BinaryOperationExpression.h>
/* **************** Declarations ***************** */
o_declareNT(class, (phantom, reflection), (typename), (t_Ty), TEqualityExpression);
/* *********************************************** */

o_namespace_begin(phantom, reflection)


template<typename t_Ty>
class  TEqualityExpression : public BinaryOperationExpression
{
    o_static_assert(boost::is_fundamental<t_Ty>::value);
    typedef o_NESTED_TYPE boost::promote<t_Ty>::type promoted_type;
public:
    TEqualityExpression( const string& a_strOperator, Expression* a_pLeftExpression, Expression* a_pRightExpression )
        : BinaryOperationExpression(
        typeOf<bool>()
        , typeOf<promoted_type>()
        , typeOf<promoted_type>()
        , a_strOperator
        , a_pLeftExpression
        , a_pRightExpression)
    {
        o_assert(a_strOperator == "==" OR a_strOperator == "!=");
        o_assert(m_pConvertedLeftExpression->getValueType()->removeReference() == typeOf<promoted_type>());
        o_assert(m_pConvertedRightExpression->getValueType()->removeReference() == typeOf<promoted_type>());
    }

    virtual void    internalEval(void* a_pDest) const 
    {
        promoted_type l;
        promoted_type r;
        m_pConvertedLeftExpression->load(&l);
        m_pConvertedRightExpression->load(&r);
        switch(m_strOperator[0])
        {
        case '!':
            *((bool*)a_pDest) = (l != r);
            break;
        case '=':
            *((bool*)a_pDest) = (l == r);
            break;
        }
    }

    virtual TEqualityExpression<t_Ty>*     clone() const 
    {
        return o_new(TEqualityExpression<t_Ty>)(m_strOperator, m_pLeftExpression, m_pRightExpression);
    }
};

o_namespace_end(phantom, reflection)



#endif
