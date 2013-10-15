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
#include <phantom/reflection/SourceFile.h>
/* *********************************************** */
o_cpp_begin 

ReflectionCPP__________________________________________________________________________________
__________________________________________________________________________________ReflectionCPP

SourceFile::SourceFile(const string& a_strAbsoluteName) 
: m_strAbsoluteName(a_strAbsoluteName) 
{

}

void SourceFile::clearCodeLocations()
{
    while(m_LanguageElements.size())
    {
        auto it = m_LanguageElements.begin();
        it->second->removeCodeLocation(it->first);
    }
    while(m_LanguageElementReferences.size())
    {
        auto it = m_LanguageElements.begin();
        it->second->removeReferenceCodeLocation(it->first);
    }
    while(m_LanguageElementDeclarations.size())
    {
        auto it = m_LanguageElements.begin();
        it->second->removeDeclarationCodeLocation(it->first);
    }
}

void SourceFile::getElements(const CodePosition& a_Position, vector<reflection::LanguageElement*>& out)
{
    for(auto it = m_LanguageElements.begin(); it != m_LanguageElements.end(); ++it)
    {
        if(it->first.containsCodePosition(a_Position))
        {
            out.push_back(it->second);
        }
    }
}
void SourceFile::getElementReferences(const CodePosition& a_Position, vector<reflection::LanguageElement*>& out)
{
    for(auto it = m_LanguageElementReferences.begin(); it != m_LanguageElementReferences.end(); ++it)
    {
        if(it->first.containsCodePosition(a_Position))
        {
            out.push_back(it->second);
        }
    }
}
void SourceFile::getElementDeclarations(const CodePosition& a_Position, vector<reflection::LanguageElement*>& out)
{
    for(auto it = m_LanguageElementDeclarations.begin(); it != m_LanguageElementDeclarations.end(); ++it)
    {
        if(it->first.containsCodePosition(a_Position))
        {
            out.push_back(it->second);
        }
    }
}
void SourceFile::getElements(const CodeLocation& a_Location, vector<reflection::LanguageElement*>& out)
{
    for(auto it = m_LanguageElements.begin(); it != m_LanguageElements.end(); ++it)
    {
        if(it->first == a_Location)
        {
            out.push_back(it->second);
        }
    }
}

void SourceFile::getElementReferences(const CodeLocation& a_Location, vector<reflection::LanguageElement*>& out)
{
    for(auto it = m_LanguageElementReferences.begin(); it != m_LanguageElementReferences.end(); ++it)
    {
        if(it->first == a_Location)
        {
            out.push_back(it->second);
        }
    }
}

void SourceFile::getElementDeclarations(const CodeLocation& a_Location, vector<reflection::LanguageElement*>& out)
{
    for(auto it = m_LanguageElementDeclarations.begin(); it != m_LanguageElementDeclarations.end(); ++it)
    {
        if(it->first == a_Location)
        {
            out.push_back(it->second);
        }
    }
}

void SourceFile::addElement( const CodeLocation& a_Location, LanguageElement* a_pLanguageElement )
{
    //o_assert(findLanguageElement(a_Location) == nullptr);
    o_assert(a_Location.getSourceFile() == this);
    m_LanguageElements.push_back(std::pair<CodeLocation, LanguageElement*>(a_Location, a_pLanguageElement));
}

void SourceFile::removeElement( const CodeLocation& a_Location, LanguageElement* a_pLanguageElement )
{
    //o_assert(findLanguageElement(a_Location) != nullptr);
    m_LanguageElements.erase(std::find(m_LanguageElements.begin(), m_LanguageElements.end(), std::pair<CodeLocation, LanguageElement*>(a_Location, a_pLanguageElement)));
}

void SourceFile::addElementReference( const CodeLocation& a_Location, LanguageElement* a_pLanguageElement )
{
    //o_assert(findLanguageElementReference(a_Location) == nullptr);
    o_assert(a_Location.getSourceFile() == this);
    m_LanguageElementReferences.push_back(std::pair<CodeLocation, LanguageElement*>(a_Location, a_pLanguageElement));
}

void SourceFile::removeElementReference( const CodeLocation& a_Location, LanguageElement* a_pLanguageElement )
{
    //o_assert(findLanguageElementReference(a_Location) != nullptr);
    m_LanguageElementReferences.erase(std::find(m_LanguageElementReferences.begin(), m_LanguageElementReferences.end(), std::pair<CodeLocation, LanguageElement*>(a_Location, a_pLanguageElement)));
}

void SourceFile::addElementDeclaration( const CodeLocation& a_Location, LanguageElement* a_pLanguageElement )
{
    //o_assert(findLanguageElementDeclaration(a_Location) == nullptr);
    o_assert(a_Location.getSourceFile() == this);
    m_LanguageElementDeclarations.push_back(std::pair<CodeLocation, LanguageElement*>(a_Location, a_pLanguageElement));
}

void SourceFile::removeElementDeclaration( const CodeLocation& a_Location, LanguageElement* a_pLanguageElement )
{
    //o_assert(findLanguageElementDeclaration(a_Location) != nullptr);
    m_LanguageElementDeclarations.erase(std::find(m_LanguageElementDeclarations.begin(), m_LanguageElementDeclarations.end(), std::pair<CodeLocation, LanguageElement*>(a_Location, a_pLanguageElement)));
}

o_cpp_end
