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
/* ** The Class Header must be the last #include * */
#include <phantom/serialization/Bundle.h>
/* *********************************************** */
o_cpp_begin

ReflectionCPP__________________________________________________________________________________
__________________________________________________________________________________ReflectionCPP

void Bundle::add( void* a_pInstance )
{
#ifndef NDEBUG
    reflection::Class* pClass = classOf(a_pInstance);
    if(m_pContentType->isClass())
    {
        o_assert( pClass AND pClass->isKindOf(static_cast<reflection::Class*>(m_pContentType)),     
            "a_pInstance class doesn't match the bundle content class");  
    }
    else
    {
        o_assert( pClass == NULL, "address added matches a polymorphic instance whereas the bundle content type is a non-polymorphic type");      
    }
#endif
    m_Content.push_back(chunk(a_pInstance, 1, 0));
}

void Bundle::add( void* a_pChunkAddress, size_t a_uiCount, size_t a_uiChunkSectionSize )
{
#ifndef NDEBUG
    o_assert(a_uiChunkSectionSize >= m_pContentType->getSize());
    byte* pChunk = (byte*)a_pChunkAddress;
    for(uint i = 0; i<a_uiCount; ++i)
    {
        reflection::Class* pClass = classOf(pChunk);
        if(m_pContentType->isClass())
        {
            o_assert( pClass AND pClass->isKindOf(static_cast<reflection::Class*>(m_pContentType)),     
                "a_pInstance class doesn't match the bundle content class");  
        }
        else
        {
            o_assert( pClass == NULL, "address added matches a polymorphic instance whereas the bundle content type is a non-polymorphic type");      
        }
        pChunk += a_uiChunkSectionSize;
    }
    o_assert(a_uiCount < std::numeric_limits<ushort>::max());
    o_assert(a_uiChunkSectionSize < std::numeric_limits<ushort>::max());
#endif
    m_Content.push_back(chunk(a_pChunkAddress, a_uiCount, a_uiChunkSectionSize));
}

void Bundle::remove( void* a_pInstance )
{
#ifndef NDEBUG
    reflection::Class* pClass = classOf(a_pInstance);
    if(m_pContentType->isClass())
    {
        o_assert( pClass AND pClass->isKindOf(static_cast<reflection::Class*>(m_pContentType)),     
            "a_pInstance class doesn't match the bundle content class");  
    }
    else
    {
        o_assert( pClass == NULL, "address added matches a polymorphic instance whereas the bundle content type is a non-polymorphic type");      
    }
#endif
    vector<chunk>::iterator  it = m_Content.begin();
    vector<chunk>::iterator  end = m_Content.end();
    for(;it != end; ++it)
    {
        if(it->address == a_pInstance)
            break;
    }
    o_assert(it != end);
    m_Content.erase(it);
}

void Bundle::remove( void* a_pChunkAddress, size_t a_uiCount, size_t a_uiChunkSectionSize )
{
#ifndef NDEBUG
    o_assert(a_uiChunkSectionSize >= m_pContentType->getSize());
    byte* pChunk = (byte*)a_pChunkAddress;
    for(uint i = 0; i<a_uiCount; ++i)
    {
        reflection::Class* pClass = classOf(pChunk);
        if(m_pContentType->isClass())
        {
            o_assert( pClass AND pClass->isKindOf(static_cast<reflection::Class*>(m_pContentType)),     
                "a_pInstance class doesn't match the bundle content class");  
        }
        else
        {
            o_assert( pClass == NULL, "address added matches a polymorphic instance whereas the bundle content type is a non-polymorphic type");      
        }
        pChunk += a_uiChunkSectionSize;
    }
    o_assert(a_uiCount < std::numeric_limits<ushort>::max());
    o_assert(a_uiChunkSectionSize < std::numeric_limits<ushort>::max());
#endif
    vector<chunk>::iterator  it = m_Content.begin();
    vector<chunk>::iterator  end = m_Content.end();
    for(;it != end; ++it)
    {
        if(it->address == a_pChunkAddress)
            break;
    }
    o_assert(it != end);
    m_Content.erase(it);
}

o_cpp_end

