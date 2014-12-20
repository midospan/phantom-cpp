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

#ifndef o_phantom_reflection_StaticVariable_h__
#define o_phantom_reflection_StaticVariable_h__



/* ****************** Includes ******************* */

/* **************** Declarations ***************** */

/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export StaticVariable : public LanguageElement
{
    o_language_element;

    o_declare_meta_type(StaticVariable);

public:
    StaticVariable();
    StaticVariable(Type* a_pValueType, const string& a_strName, modifiers_t a_Modifiers = 0);
    StaticVariable(Type* a_pValueType, const string& a_strName, Range* a_pRange = nullptr, modifiers_t a_Modifiers = 0);

protected:
    StaticVariable(void* a_pAddress, Range* a_pRange = nullptr, modifiers_t a_Modifiers = 0);
    StaticVariable(void* a_pAddress, Type* a_pValueType, Range* a_pRange = nullptr, modifiers_t a_Modifiers = 0);
    StaticVariable(void* a_pAddress, Type* a_pValueType, const string& a_strName, Range* a_pRange = nullptr, modifiers_t a_Modifiers = 0);

public:
    o_destructor ~StaticVariable(void);
    
    virtual StaticVariable* asStaticVariable() const  { return (StaticVariable*)this; }

    void*           getAddress() const { return m_pAddress; }
    Type*           getValueType() const { return m_pValueType; }
    Range*          getRange() const { return m_pRange; }
    void            setRange(Range* a_pRange);

    void            setValue(void const* a_pSrc) const 
    {
        m_pValueType->copy(m_pAddress, a_pSrc);
    }

    void            getValue(void* a_pDest) const 
    {
        m_pValueType->copy(a_pDest, m_pAddress);
    }

protected:
    void            setAddress(void* a_pAddress) { m_pAddress = a_pAddress; }

protected:
    virtual void    referencedElementRemoved(LanguageElement* a_pElement);
    void            setValueTypeName(string str);
    string          getValueTypeName() const;
    virtual void    finalize();

protected:
    Type*       m_pValueType;
    Range*      m_pRange;
    void*       m_pAddress;
    string*     m_pValueTypeName;
};

o_namespace_end(phantom, reflection)



#endif
