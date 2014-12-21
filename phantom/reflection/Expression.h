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
    o_language_element;

public:
    Expression(Type* a_pValueType, modifiers_t a_Modifiers = 0);

    using Evaluable::eval;

    void                    eval(void* a_pDest) const 
    {
        if(isInvalid())
        {
            o_exception(exception::reflection_runtime_exception, "Invalid expression cannot be evaluated");
        }
        internalEval(a_pDest);
    }

    virtual void            internalEval() const { /*by default evaluating an expression do nothing, must be reimplemented to have significant role*/ }
    virtual void            internalEval(void* a_pDest) const = 0;

    Type*                   getValueType() const { return m_pValueType; }

    void                    load(void* a_pDest) const;

    void                    store(void const* a_pSrc) const;

    void                    storeWithSignalsBlocked(void const* a_pSrc) const;

    variant                 get() const;

    void                    set(const variant& v);

    virtual Expression*     asExpression() const { return (Expression*)this; }

    virtual bool            isAddressable() const { return m_pValueType->asReferenceType() != nullptr; }

    virtual bool            isDereferenceable() const;

    virtual bool            isAssignable() const { return isAddressable() && NOT(isConstExpression()); }

    virtual bool            isPersistent() const;

    virtual bool            hasValueStorage() const { return false; }

    bool                    hasValueStorageCascade() const;

    virtual void*           getValueStorageAddress() const { return nullptr; }

    bool                    hasEffectiveAddress() const { return (m_pValueType AND m_pValueType->asReferenceType() != nullptr) OR hasValueStorage(); }

    void*                   loadEffectiveAddress() const;

    virtual void            flush() const {}

    bool                    isConstExpression() const;

    Expression*             precompilePreUnaryOperator(Precompiler* a_pPrecompiler, const string& a_strOp, modifiers_t a_Modifiers = 0) 
    {
        vector<Expression*> elements;
        return precompileOperator(a_pPrecompiler, a_strOp, elements, a_Modifiers); 
    }

    Expression*             precompilePostUnaryOperator(Precompiler* a_pPrecompiler, const string& a_strOp, modifiers_t a_Modifiers = 0) 
    {
        vector<Expression*> elements;
        elements.push_back(nullptr);
        return precompileOperator(a_pPrecompiler, a_strOp, elements, a_Modifiers); 
    }

    Expression*             precompileBinaryOperator(Precompiler* a_pPrecompiler, const string& a_strOp, Expression* a_pExpression, modifiers_t a_Modifiers = 0) 
    {
        vector<Expression*> elements;
        elements.push_back(a_pExpression);
        return precompileOperator(a_pPrecompiler, a_strOp, elements, a_Modifiers); 
    }

    Expression*             implicitCast(Type* a_pTargetType) const;

    Expression*             cast(Type* a_pTargetType) const;

    virtual Expression*     reference() const;

    virtual Expression*     dereference() const;

    virtual Expression*     address() const ;  

    virtual Expression*     clone() const = 0;

    void                    setSignalBlocked(bool a_bSignalsBlocked);

    void                    setSignalBlockedCascade(bool a_bSignalsBlocked);

    bool                    areSignalsBlocked() const { return m_bSignalsBlocked; }

    void                    detach();

    /// Dynamic Conversion helpers (useful if rtti not enabled for expressions)

    virtual ConditionalExpression*      asConditionalExpression() const { return nullptr; }
    virtual ConstantExpression*         asConstantExpression() const { return nullptr; }
    virtual CallExpression*             asCallExpression() const { return nullptr; }
    virtual CastExpression*             asCastExpression() const { return nullptr; }
    virtual ReferenceExpression*        asReferenceExpression() const { return nullptr; }
    virtual AddressExpression*          asAddressExpression() const { return nullptr; }
    virtual BinaryLogicalExpression*    asBinaryLogicalExpression() const { return nullptr; }
    virtual UnaryLogicalExpression*     asUnaryLogicalExpression() const { return nullptr; }
    virtual BinaryOperationExpression*  asBinaryOperationExpression() const { return nullptr; }
    virtual PreUnaryOperationExpression*asPreUnaryOperationExpression() const { return nullptr; }
    virtual PostUnaryOperationExpression*asPostUnaryOperationExpression() const { return nullptr; }
    virtual ArrayExpression*            asArrayExpression() const { return nullptr; }
    virtual LocalVariableExpression*    asLocalVariableExpression() const { return nullptr; }
    virtual InstanceDataMemberExpression* asInstanceDataMemberExpression() const { return nullptr; }
    virtual PropertyExpression*         asPropertyExpression() const { return nullptr; }
    virtual PointerArithmeticExpression*asPointerArithmeticExpression() const { return nullptr; }
    virtual StaticVariableExpression*   asStaticVariableExpression() const { return nullptr; }
    virtual StringLiteralExpression*    asStringLiteralExpression() const { return nullptr; }
    virtual WStringLiteralExpression*   asWStringLiteralExpression() const { return nullptr; }
    virtual AssignmentExpression*       asAssignmentExpression() const { return nullptr; }
    virtual ConstructorCallExpression*  asConstructorCallExpression() const { return nullptr; }
    virtual DataExpression*             asDataExpression() const { return nullptr; }
    virtual DereferenceExpression*      asDereferenceExpression() const { return nullptr; }
    virtual PlacementConstructionExpression* asPlacementConstructionExpression() const { return nullptr; }
    virtual MemberFunctionPointerCallExpression* asMemberFunctionPointerCallExpression() const { return nullptr; }

protected:

    virtual void referencedElementRemoved(LanguageElement* a_pElement);

    virtual void elementRemoved(LanguageElement* a_pElement);

    Type* storageType(Type* a_pType) const;

    void addSubExpression(Expression*& a_prExpression);

    void removeSubExpression(Expression* a_pExpression);

protected:
    void setValue( void const* a_pSrc ) const;

protected:
    Type*                   m_pValueType;
    vector<Expression*>*    m_pSubExpressions;
    bool                    m_bSignalsBlocked;
};

o_namespace_end(phantom, reflection)



#endif
