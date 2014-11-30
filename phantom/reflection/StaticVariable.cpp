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

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include <phantom/reflection/StaticVariable.h>
#include <phantom/reflection/StaticVariable.hxx>
/* *********************************************** */
o_registerN((phantom, reflection), StaticVariable);
o_namespace_begin(phantom, reflection)

o_define_meta_type(StaticVariable) = o_type_of(StaticVariable);

StaticVariable::StaticVariable()
    : LanguageElement()
    , m_pRange(nullptr)
    , m_pValueType(nullptr)
    , m_pAddress(nullptr)
{

}

StaticVariable::StaticVariable(void* a_pAddress, Range* a_pRange, modifiers_t a_Modifiers /*= 0*/)
    : LanguageElement(phantom::lexical_cast<string>(a_pAddress), a_Modifiers)
    , m_pRange(a_pRange)
    , m_pValueType(classOf(a_pAddress))
    , m_pAddress(a_pAddress)
{
    o_assert(testModifiers(o_native));
    if(m_pValueType)
    {
        addReferencedElement(m_pValueType);
    }
    else
    {
        o_exception(exception::reflection_runtime_exception, "No rtti at given static variable address");
    }
}

StaticVariable::StaticVariable(void* a_pAddress, Type* a_pValueType, Range* a_pRange, modifiers_t a_Modifiers /*= 0*/)
    : LanguageElement(phantom::lexical_cast<string>(a_pAddress), a_Modifiers)
    , m_pRange(a_pRange)
    , m_pValueType(a_pValueType)
    , m_pAddress(a_pAddress)
    , m_pValueTypeName(nullptr)
{
    o_assert(testModifiers(o_native));
    o_assert(m_pValueType);
    addReferencedElement(m_pValueType);
}

StaticVariable::StaticVariable( void* a_pAddress, Type* a_pValueType, const string& a_strName, Range* a_pRange, modifiers_t a_Modifiers /*= 0*/ )
    : LanguageElement(a_strName, a_Modifiers)
    , m_pRange(a_pRange)
    , m_pValueType(a_pValueType)
    , m_pAddress(a_pAddress)
    , m_pValueTypeName(nullptr)
{
    o_assert(isNative());
    o_assert(m_pValueType);
    addReferencedElement(m_pValueType);
}

StaticVariable::StaticVariable( Type* a_pValueType, const string& a_strName, modifiers_t a_Modifiers /*= 0*/ )
    : LanguageElement(a_strName, a_Modifiers)
    , m_pRange(nullptr)
    , m_pValueType(a_pValueType)
    , m_pAddress(a_pValueType ? a_pValueType->newInstance() : nullptr)
    , m_pValueTypeName(nullptr)
{
    o_assert(!isNative());
    if(m_pValueType)
    {
        addReferencedElement(m_pValueType);
    }
}

StaticVariable::StaticVariable( Type* a_pValueType, const string& a_strName, Range* a_pRange /*= nullptr*/, modifiers_t a_Modifiers /*= 0*/ )
    : LanguageElement(a_strName, a_Modifiers)
    , m_pRange(a_pRange)
    , m_pValueType(a_pValueType)
    , m_pAddress(a_pValueType ? a_pValueType->newInstance() : nullptr)
    , m_pValueTypeName(nullptr)
{
    o_assert(!isNative());
    if(m_pValueType)
    {
        addReferencedElement(m_pValueType);
    }
}

StaticVariable::~StaticVariable( void )
{
    if(!isNative() AND m_pValueType)
    {
        m_pValueType->deleteInstance(m_pAddress);
    }
}

void StaticVariable::referencedElementRemoved( LanguageElement* a_pElement )
{
    LanguageElement::referencedElementRemoved(a_pElement);
    if(m_pValueType == a_pElement)
        m_pValueType = nullptr;
}

void StaticVariable::setRange( Range* a_pRange )
{
    if(testModifiers(o_native))
    {
        o_exception(exception::base_exception, "Native elements cannot be modified");
    }
    m_pRange = a_pRange;
    if(m_pRange)
    {
        addElement(m_pRange);
    }
}

void StaticVariable::setValueTypeName( string str )
{
    if(str.size())
    {
        m_pValueTypeName = new string(str);
    }
}

string StaticVariable::getValueTypeName() const
{
    return m_pValueType ? m_pValueType->getQualifiedDecoratedName() : "";
}

void StaticVariable::finalize()
{
    if(m_pValueTypeName)
    {
        o_assert(m_pValueType == nullptr);
        m_pValueType = phantom::typeByName(*m_pValueTypeName);
        if(m_pValueType)
        {
            addReferencedElement(m_pValueType);
            m_pAddress = m_pValueType->newInstance();
        }
        delete m_pValueTypeName;
        m_pValueTypeName = nullptr;
    }
}

o_namespace_end(phantom, reflection)
