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

#ifndef o_phantom_reflection_AnonymousSection_h__
#define o_phantom_reflection_AnonymousSection_h__

/* ****************** Includes ******************* */

/* **************** Declarations ***************** */

/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export AnonymousSection : public LanguageElement
{
    o_declare_meta_type(AnonymousSection);

public:
    AnonymousSection(modifiers_t modifiers = 0);

    virtual AnonymousSection* asAnonymousSection() const { return (AnonymousSection*)this; }

    void addInstanceDataMember( InstanceDataMember* a_pDataMember );

    void addAnonymousSection( AnonymousSection* a_pAnonymousSection );

    LanguageElement* getElement(size_t a_uiIndex) const { return m_Elements[a_uiIndex]; }

    size_t getElementCount() const { return m_Elements.size(); }

    vector<LanguageElement*>::const_iterator beginElements() const { return m_Elements.begin(); }

    vector<LanguageElement*>::const_iterator endElements() const { return m_Elements.end(); }

    AnonymousSection* getOwnerSection() const { return m_pOwner ? m_pOwner->asAnonymousSection() : nullptr; }

    AnonymousSection* getRootSection() const { return getOwnerSection() ? getOwnerSection()->getRootSection() : (AnonymousSection*)this; }

protected:
    void referencedElementRemoved(LanguageElement* a_pElement);

protected:
    vector<LanguageElement*> m_Elements;

};

o_namespace_end(phantom, reflection)



#endif
