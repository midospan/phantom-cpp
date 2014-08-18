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

#ifndef o_phantom_reflection_TAssignmentExpression_h__
#define o_phantom_reflection_TAssignmentExpression_h__



/* ****************** Includes ******************* */
#include <phantom/reflection/Expression.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, reflection), (typename), (t_Ty), TAssignmentExpression);
/* *********************************************** */

o_namespace_begin(phantom, reflection)

template<typename t_Ty>
class o_export TAssignmentExpression : public AssignmentExpression
{
    o_static_assert(boost::is_fundamental<t_Ty>::value);

public:
    TAssignmentExpression( const string& a_strOperator, Expression* a_pLHSExpression, Expression* a_pRHSExpression )
        : AssignmentExpression(a_strOperator, a_pLHSExpression, a_pRHSExpression)
    {
        o_assert(m_pLHSExpression->getValueType() == typeOf<t_Ty&>());
        o_assert(m_pRHSExpression->getValueType() == typeOf<t_Ty>());
    }

    virtual void    getValue(void* a_pDest) const 
    {
        t_Ty* _where = 0;
        m_pLHSExpression->getValue(&_where); // get reference address
        t_Ty _intermediate;
        switch(m_strOperator[0])
        {
        case '=':
            m_pRHSExpression->load(_where);
            break;
        case '+':
            m_pRHSExpression->load(&_intermediate);
            *_where += _intermediate;
            break;
        case '-':
            m_pRHSExpression->load(&_intermediate);
            *_where -= _intermediate;
            break;
        case '*':
            m_pRHSExpression->load(&_intermediate);
            *_where *= _intermediate;
            break;
        case '/':
            m_pRHSExpression->load(&_intermediate);
            *_where /= _intermediate;
            break;
        case '&':
            m_pRHSExpression->load(&_intermediate);
            *_where &= _intermediate;
            break;
        case '|':
            m_pRHSExpression->load(&_intermediate);
            *_where |= _intermediate;
            break;
        case '^':
            m_pRHSExpression->load(&_intermediate);
            *_where ^= _intermediate;
            break;
        case '>':
            m_pRHSExpression->load(&_intermediate);
            *_where >>= _intermediate;
            break;
        case '<':
            m_pRHSExpression->load(&_intermediate);
            *_where <<= _intermediate;
            break;
        }

        *(t_Ty**)a_pDest = _where;
    }

    virtual void    setValue(const void* a_pDest) const 
    {
        m_pLHSExpression->setValue(a_pDest);
    }

protected:
    string          m_strOperator;
    Expression*     m_pLHSExpression;
    Expression*     m_pRHSExpression;

};

o_namespace_end(phantom, reflection)



#endif
