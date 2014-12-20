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
#include <phantom/reflection/MemberFunctionPointerType.h>
#include <phantom/reflection/MemberFunctionPointerType.hxx>
#include <phantom/reflection/Expression.h>
#include <phantom/reflection/AssignmentExpression.h>
#include <phantom/reflection/ConstantExpression.h>
#include <phantom/reflection/BinaryLogicalExpression.h>
#include <phantom/reflection/PointerArithmeticExpression.h>
#include <phantom/reflection/TBinaryBooleanExpression.h>
/* *********************************************** */
o_registerN((phantom, reflection), MemberFunctionPointerType);

o_namespace_begin(phantom, reflection) 

o_define_meta_type(MemberFunctionPointerType);

MemberFunctionPointerType::MemberFunctionPointerType( Type* a_pObjectType, Signature* a_pSignature, size_t a_Size, size_t a_Alignment, modifiers_t a_Modifiers ) 
: MemberPointerType(a_pObjectType
            , a_Size
            , a_Alignment
            , a_Modifiers)    
            , m_pSignature(a_pSignature)
            , m_pObjectType(a_pObjectType)
{
    addReferencedElement(m_pObjectType);
    addElement(m_pSignature);
}

MemberFunctionPointerType::~MemberFunctionPointerType()
{

}

boolean MemberFunctionPointerType::isConvertibleTo( Type* a_pType ) const
{
    o_assert(a_pType);
    return a_pType->removeConst() == this;
}

boolean MemberFunctionPointerType::isImplicitlyConvertibleTo( Type* a_pType ) const
{
    o_assert(a_pType);
    return a_pType->removeConst() == this;
}

void MemberFunctionPointerType::convertValueTo( Type* a_pDestType, void* a_pDestValue, void const* a_pSrcValue ) const
{
    Type::convertValueTo(a_pDestType, a_pDestValue, a_pSrcValue);
}

void MemberFunctionPointerType::referencedElementRemoved( LanguageElement* a_pElement )
{
    Type::referencedElementRemoved(a_pElement);
    if(m_pObjectType == a_pElement)
    {
        m_pObjectType = nullptr;
    }
}

void MemberFunctionPointerType::valueToLiteral( string& a_str, const void* src ) const
{
    o_exception(exception::base_exception, "valueToLiteral not defined for member function pointer types");
}

void MemberFunctionPointerType::valueToString( string& a_str, const void* src ) const
{
    o_exception(exception::base_exception, "valueToString not defined for member function pointer types");
}

void MemberFunctionPointerType::valueFromString( const string& a_str, void* dest ) const
{
    o_exception(exception::base_exception, "valueFromString not defined for member function pointer types");
}

void MemberFunctionPointerType::copy( void* a_pDest, void const* a_pSrc ) const
{
    memcpy(a_pDest, a_pSrc, m_uiSize);
}

o_namespace_end(phantom, reflection)