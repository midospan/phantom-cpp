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

#ifndef o_phantom_reflection_InstanceDataMemberAccess_h__
#define o_phantom_reflection_InstanceDataMemberAccess_h__



/* ****************** Includes ******************* */
#include <phantom/reflection/Expression.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, reflection), InstanceDataMemberAccess);
/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export InstanceDataMemberAccess : public Expression
{
public:
    InstanceDataMemberAccess(Expression* a_pLeftExpression, InstanceDataMember* a_pInstanceDataMember);

    virtual Type*               getValueType() const 
    {
        return m_pInstanceDataMember->getValueType();
    }

    virtual void                getValue(void* dest) const;

    virtual void                setValue(void const* src) const;

    Expression*                 getLeftExpression() const { return m_pLeftExpression; }

    InstanceDataMember*         getInstanceDataMember() const { return m_pInstanceDataMember; }

    virtual void                flush() const { m_pLeftExpression->flush(); }

    virtual LanguageElement*    getHatchedElement() const;

    virtual bool                isPersistent() const;

    virtual InstanceDataMemberAccess* clone() const;

protected:
    void referencedElementRemoved( LanguageElement* a_pElement );

protected:
    Expression*             m_pLeftExpression;
    InstanceDataMember*     m_pInstanceDataMember;

};

o_namespace_end(phantom, reflection)



#endif
