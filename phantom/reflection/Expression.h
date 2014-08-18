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

#ifndef o_phantom_reflection_Expression_h__
#define o_phantom_reflection_Expression_h__



/* ****************** Includes ******************* */
#include "phantom/reflection/Evaluable.h"
/* **************** Declarations ***************** */
o_declareN(class, (phantom, reflection), Expression);
/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export Expression : public Evaluable
{
public:
    Expression(Type* a_pValueType, bitfield a_Modifiers = 0);
    Expression(Type* a_pValueType, const string& a_strName, bitfield a_Modifiers = 0);
     
    virtual void            eval() const {}

    Type*                   getValueType() const { return m_pValueType; }

    virtual void            getValue(void* a_pDest) const = 0;

    virtual void            setValue(void const* a_pSrc) const;

    void                    load(void* a_pDest) const;

    void                    store(void const* a_pSrc) const;

    variant                 get() const;

    void                    set(const variant& v);

    virtual Expression*     asExpression() const { return (Expression*)this; }

    virtual bool            isAddressable() const { return m_pValueType->asReferenceType() != nullptr; }

    virtual bool            isDereferenceable() const;

    virtual bool            isAssignable() const { return isAddressable() && NOT(isConstExpression()); }

    virtual bool            hasValueStorage() const { return false; }

    virtual void*           getValueStorageAddress() const { return nullptr; }

    bool                    hasEffectiveAddress() const { return m_pValueType->asReferenceType() != nullptr OR hasValueStorage(); }

    void*                   loadEffectiveAddress() const;

    virtual void            flush() const {}

    bool                    isConstExpression() const;

    Expression*             solveUnaryOperator(const string& a_strOp, bitfield a_Modifiers = 0) const
    {
        vector<Expression*> elements;
        return solveOperator(a_strOp, elements, a_Modifiers); 
    }

    Expression*             solveBinaryOperator(const string& a_strOp, Expression* a_pExpression, bitfield a_Modifiers = 0) const 
    {
        vector<Expression*> elements;
        elements.push_back(a_pExpression);
        return solveOperator(a_strOp, elements, a_Modifiers); 
    }

    virtual Expression*     solveOperator(const string& a_strOp, const vector<Expression*>& a_Expressions, bitfield a_Modifiers = 0) const;

    virtual LanguageElement*solveElement(
                                const string& a_strName
                                , const vector<TemplateElement*>*
                                , const vector<LanguageElement*>*
                                , bitfield a_Modifiers = 0) const;

    Expression*             implicitCast(Type* a_pTargetType) const;

    Expression*             cast(Type* a_pTargetType) const;

    virtual Expression*     reference() const;

    virtual Expression*     dereference() const;

    virtual Expression*     address() const ;  

    virtual Expression*     clone() const = 0;

    virtual LanguageElement*getHatchedElement() const { return nullptr; }

protected:
    virtual void            ancestorChanged(LanguageElement* a_pLanguageElement) 
    {
        if(m_pBlock == nullptr)
        {
            m_pBlock = a_pLanguageElement->asBlock();
        }
    }
    Type* storageType(Type* a_pType) const;

protected:
    Type*                   m_pValueType;
    Block*                  m_pBlock;
};

o_namespace_end(phantom, reflection)



#endif
