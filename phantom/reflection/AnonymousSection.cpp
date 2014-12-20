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
#include <phantom/reflection/AnonymousSection.h>
#include <phantom/reflection/AnonymousSection.hxx>
/* *********************************************** */
o_registerN((phantom, reflection), AnonymousSection);

o_namespace_begin(phantom, reflection)

o_define_meta_type(AnonymousSection) = o_type_of(AnonymousSection);

AnonymousSection::AnonymousSection( modifiers_t modifiers /*= 0*/ )
    : LanguageElement("", modifiers)
{

}

void AnonymousSection::addInstanceDataMember( InstanceDataMember* a_pDataMember )
{
    if(a_pDataMember == nullptr)
    {
        o_exception(exception::base_exception, "null data member");
    }
    addReferencedElement(a_pDataMember);
    m_Elements.push_back(a_pDataMember);
    o_assert(a_pDataMember->m_pAnonymousSection == nullptr);
    a_pDataMember->m_pAnonymousSection = this;
}

void AnonymousSection::addAnonymousSection( AnonymousSection* a_pAnonymousSection )
{
    addElement(a_pAnonymousSection);
    m_Elements.push_back(a_pAnonymousSection);
}

void AnonymousSection::referencedElementRemoved( LanguageElement* a_pElement )
{
    auto found = std::find(m_Elements.begin(), m_Elements.end(), a_pElement);
    if(found != m_Elements.end())
    {
        m_Elements.erase(found);
        o_assert(a_pElement->asInstanceDataMember());
        static_cast<InstanceDataMember*>(a_pElement)->m_pAnonymousSection = nullptr;
    }
}

o_namespace_end(phantom, reflection)
