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

#ifndef o_phantom_reflection_SourceFile_h__
#define o_phantom_reflection_SourceFile_h__




/* ****************** Includes ******************* */


/* **************** Declarations ***************** */

/* *********************************************** */
namespace phantom { class Phantom; }

o_namespace_begin(phantom, reflection)

class o_export SourceFile
{
    friend class phantom::Phantom;
    friend class LanguageElement;

    
protected:
    SourceFile(const string& a_strAbsoluteName);

public:
    const string& getAbsoluteName() const { return m_strAbsoluteName; }

    void clearCodeLocations();

    void getElements(const CodePosition& a_Position, vector<reflection::LanguageElement*>& out);
    void getElementReferences(const CodePosition& a_Position, vector<reflection::LanguageElement*>& out);
    void getElementDeclarations(const CodePosition& a_Position, vector<reflection::LanguageElement*>& out);

    void getElements(const CodeLocation& a_Location, vector<reflection::LanguageElement*>& out);
    void getElementReferences(const CodeLocation& a_Location, vector<reflection::LanguageElement*>& out);
    void getElementDeclarations(const CodeLocation& a_Location, vector<reflection::LanguageElement*>& out);

protected:
    void addElement(const CodeLocation& a_Location, LanguageElement* a_pLanguageElement);
    void removeElement(const CodeLocation& a_Location, LanguageElement* a_pLanguageElement);

    void addElementReference(const CodeLocation& a_Location, LanguageElement* a_pLanguageElement);
    void removeElementReference(const CodeLocation& a_Location, LanguageElement* a_pLanguageElement);

    void addElementDeclaration(const CodeLocation& a_Location, LanguageElement* a_pLanguageElement);
    void removeElementDeclaration(const CodeLocation& a_Location, LanguageElement* a_pLanguageElement);

protected:
    vector<std::pair<CodeLocation, LanguageElement*>>   m_LanguageElements;
    vector<std::pair<CodeLocation, LanguageElement*>>   m_LanguageElementReferences;
    vector<std::pair<CodeLocation, LanguageElement*>>   m_LanguageElementDeclarations;
    string                                              m_strAbsoluteName;
};

o_namespace_end(phantom, reflection)


#endif
