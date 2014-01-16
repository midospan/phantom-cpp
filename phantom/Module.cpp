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
#include "Module.h"
/* *********************************************** */
o_cpp_begin 

ReflectionCPP__________________________________________________________________________________
__________________________________________________________________________________ReflectionCPP

struct ModuleLanguageElementSorter
{
    bool operator()(const reflection::LanguageElement* l0, const reflection::LanguageElement* l1) const 
    {
        reflection::Type* pType0 = l0->asType();
        reflection::Type* pType1 = l1->asType();
        if(pType0 && ((pType0 != nullptr) == (pType1 != nullptr))) // both type
        {
            if(pType0->isKindOf(pType1))
                return true;
            else if(pType1->isKindOf(pType0))
                return false; 
            return pType0->getBuildOrder() > pType1->getBuildOrder();
        }
        else if(pType0)
        {
            return false;
        }
        else if(pType1)
        {
            return true;
        }
        else return l0 < l1;
    }
};

Module::Module( const string& a_strName, const string& a_strFileName, size_t a_PlatformHandle ) 
    : m_strName(a_strName)
    , m_pParentModule(nullptr)
    , m_PlatformHandle(a_PlatformHandle)
    , m_strFileName(a_strFileName)
{

}

Module::~Module() 
{
    vector<reflection::Class*> remaining_classes;
    auto languageElements = m_LanguageElements;
    std::sort(m_LanguageElements.begin(), m_LanguageElements.end(), ModuleLanguageElementSorter());
    while(!m_LanguageElements.empty())
    {
        auto it = m_LanguageElements.begin();
        auto end = m_LanguageElements.end();
        for(;it!=end;++it)
        {
            if((*it)->canBeDestroyed()) 
                break;
        }
        if(it != end)
        {
            reflection::LanguageElement* pElement = *it;
            pElement->terminate();
            o_dynamic_delete pElement;
        }
        else
        {
            
#if defined(_DEBUG)
            std::cout<<console::bg_gray<<console::fg_red;
            std::cout<<"Phantom release process : some class instances haven't been destroyed"<<std::endl;

            std::cout<<console::bg_black;

            auto it = m_LanguageElements.begin();
            auto end = m_LanguageElements.end();
            for(;it!=end;++it)
            {
                std::cout<<console::fg_red<<"----------------------------------------------------------------------------"<<std::endl;
                std::cout<<console::fg_gray<<(*it)->getQualifiedDecoratedName()<<" : ";
                if((*it)->asClass())
                {
                    std::cout<<console::fg_red<<"this "<<(*it)->asClass()->getInstanceCount()<<" ";
                    std::cout<<console::fg_blue<<"all "<<(*it)->asClass()->getKindCount()<<std::endl;
                }
            }
            std::cout<<console::fg_gray;
            o_assert(false);
/*
#   if o_OPERATING_SYSTEM == o_OPERATING_SYSTEM_WINDOWS 
                system("pause");
#   endif*/
#endif
            return;
        }
    }
}

void Module::addLanguageElement(reflection::LanguageElement* a_pLanguageElement) 
{
    o_assert(a_pLanguageElement->m_pModule == nullptr);
    o_assert(std::find(m_LanguageElements.begin(), m_LanguageElements.end(), a_pLanguageElement) == m_LanguageElements.end());
    m_LanguageElements.push_back(a_pLanguageElement);
    a_pLanguageElement->setModule(this);
}

void Module::removeLanguageElement(reflection::LanguageElement* a_pLanguageElement) 
{
    o_assert(a_pLanguageElement->m_pModule == this);
    m_LanguageElements.erase(std::find(m_LanguageElements.begin(), m_LanguageElements.end(), a_pLanguageElement));
    a_pLanguageElement->setModule(nullptr);
}

void Module::setParentModule( Module* a_pModule )
{
    o_assert(m_pParentModule == nullptr);
    m_pParentModule = a_pModule;
}

bool Module::hasLanguageElement( reflection::LanguageElement* a_pLanguageElement ) const
{
    return std::find(m_LanguageElements.begin(), m_LanguageElements.end(), a_pLanguageElement) != m_LanguageElements.end();
}

void Module::checkCompleteness()
{
    for(auto it = m_LanguageElements.begin(); it != m_LanguageElements.end(); ++it)
    {
        (*it)->checkCompleteness();
    }
}

bool Module::canBeUnloaded() const
{
    for(auto it = m_LanguageElements.begin(); it != m_LanguageElements.end(); ++it)
    {
        if(NOT((*it)->canBeDestroyed())) return false;
    }
    return true;
}

o_cpp_end
