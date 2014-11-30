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

#ifndef o_phantom_reflection_CallExpression_h__
#define o_phantom_reflection_CallExpression_h__



/* ****************** Includes ******************* */
#include <phantom/reflection/Expression.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, reflection), CallExpression);
/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export CallExpression : public Expression
{
public:
    CallExpression(Subroutine* a_pFunction, const vector<Expression*>& a_Arguments, Type* a_pConstructedType = nullptr);
    CallExpression(Subroutine* a_pFunction, Expression* a_pArgument, Type* a_pConstructedType = nullptr);

    o_initialize();
    o_terminate(); 

    virtual void  getValue(void* a_pDest) const ;

    virtual void  setValue(void const* a_pSrc) const;

    virtual void* getValueStorageAddress() const ;

    virtual bool hasValueStorage() const { return m_pReturnStorage != nullptr; }

    virtual void flush() const;

    virtual void eval() const;

    void call() const { eval(); }

    void call(void* a_pReturnAddress) const { getValue(a_pReturnAddress); }

    vector<Expression*>::const_iterator beginArguments() const { return m_Arguments.begin(); }
    vector<Expression*>::const_iterator endArguments() const { return m_Arguments.end(); }

    vector<Expression*>::const_reverse_iterator rbeginArguments() const { return m_Arguments.rbegin(); }
    vector<Expression*>::const_reverse_iterator rendArguments() const { return m_Arguments.rend(); }

    virtual variant         compile(Compiler* a_pCompiler);

    virtual LanguageElement*hatch();

    virtual Expression*     clone() const;

    virtual LanguageElement*getHatchedElement() const { return m_pSubroutine; }

    virtual bool            isPersistent() const;

protected:
    static string evaluateName(Subroutine* a_pSubroutine, const vector<Expression*>& a_Arguments);
    static string evaluateName( Subroutine* a_pSubroutine, Expression* a_pArgument );

protected:
    virtual void ancestorChanged(LanguageElement* a_pLanguageElement);
    virtual void elementRemoved( LanguageElement* a_pElement );
    virtual void referencedElementRemoved( LanguageElement* a_pElement );

protected:
    Subroutine*         m_pSubroutine;
    vector<Expression*> m_Arguments;
    vector<Expression*> m_ConvertedArguments;
    vector<void*>       m_TempValues;
    void*               m_pReturnStorage;
    Type**              m_pConvertedArgumentTypes;
};

o_namespace_end(phantom, reflection)



#endif
