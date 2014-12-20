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
#include <phantom/reflection/FunctionPointerType.h>
#include <phantom/reflection/FunctionPointerType.hxx>
/* *********************************************** */
o_registerN((phantom, reflection), FunctionPointerType);

o_namespace_begin(phantom, reflection) 

o_define_meta_type(FunctionPointerType);

FunctionPointerType::FunctionPointerType( Signature* a_pSignature, modifiers_t a_Modifiers ) 
: PointerType(""
            , sizeof(void(*)())
            , boost::alignment_of<void(*)()>::value
            , a_Modifiers)    
            , m_pSignature(a_pSignature)
{
    addElement(m_pSignature);
}

FunctionPointerType::~FunctionPointerType()
{

}

boolean FunctionPointerType::isConvertibleTo( Type* a_pType ) const
{
    o_assert(a_pType);
    return a_pType->removeConst() == this OR a_pType == typeOf<void*>();
}

boolean FunctionPointerType::isImplicitlyConvertibleTo( Type* a_pType ) const
{
    o_assert(a_pType);
    return a_pType->removeConst() == this;
}

void FunctionPointerType::convertValueTo( Type* a_pDestType, void* a_pDestValue, void const* a_pSrcValue ) const
{
    Type::convertValueTo(a_pDestType, a_pDestValue, a_pSrcValue);
}

void FunctionPointerType::referencedElementRemoved( LanguageElement* a_pElement )
{
    Type::referencedElementRemoved(a_pElement);
}

void FunctionPointerType::valueToLiteral( string& a_str, const void* src ) const
{
    o_exception(exception::base_exception, "valueToLiteral not defined for member function pointer types");
}

void FunctionPointerType::valueToString( string& a_str, const void* src ) const
{
    o_exception(exception::base_exception, "valueToString not defined for member function pointer types");
}

void FunctionPointerType::valueFromString( const string& a_str, void* dest ) const
{
    o_exception(exception::base_exception, "valueFromString not defined for member function pointer types");
}

void FunctionPointerType::copy( void* a_pDest, void const* a_pSrc ) const
{
    memcpy(a_pDest, a_pSrc, m_uiSize);
}

o_namespace_end(phantom, reflection)