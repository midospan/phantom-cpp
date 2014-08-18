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
#include <phantom/reflection/StringLiteralExpression.h>
#include <phantom/reflection/DataExpression.h>
#include <phantom/reflection/StringLiteralExpression.hxx>
/* *********************************************** */
o_registerN((phantom, reflection), StringLiteralExpression);

o_namespace_begin(phantom, reflection) 

string StringLiteralExpression::Literalize(const string& a_Value)
{
    string literalized = "\"";
    for(auto it = a_Value.begin(); it != a_Value.end(); ++it)
    {
        switch(*it)
        {
        case '"':  literalized += "\\\""; break;
        case '\\': literalized += "\\\\"; break;
        case '\n': literalized += "\\n" ; break;
        case '\r': literalized += "\\r" ; break;
        case '\t': literalized += "\\t" ; break;
        case '\0': literalized += "\\0" ; break;
        default:
            literalized += *it;
        }
    }
    return literalized + "\"";
}

StringLiteralExpression::StringLiteralExpression(const string& a_Value)
    : Expression(typeOf<const char*>(), Literalize(a_Value))
    , m_Value((const char*)malloc(a_Value.size()+1))
{
    memcpy((void*)m_Value, a_Value.c_str(), a_Value.size()+1);
}

void StringLiteralExpression::setValue( void const* a_pSrc ) const
{
    o_exception(exception::reflection_runtime_exception, "Constant cannot be assigned");
}

void StringLiteralExpression::getValue( void* a_pDest ) const
{
    *((const char**)a_pDest) = m_Value;
}

StringLiteralExpression* StringLiteralExpression::clone() const
{
    return o_new(StringLiteralExpression)(m_Value);
}

o_namespace_end(phantom, reflection)
