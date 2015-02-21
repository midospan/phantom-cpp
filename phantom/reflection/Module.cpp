/* TODO LICENCE HERE */

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include "Module.h"
#include "Module.hxx"
#include "Application.h"
#include "Package.h"
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/split.hpp>
/* *********************************************** */
o_registerN((phantom, reflection), Module);

o_namespace_begin(phantom, reflection)

o_invalid_def(Module, "<unknown-module>", "");

struct ModuleLanguageElementSorter
{
    bool operator()(const LanguageElement* l0, const LanguageElement* l1) const
    {
        Type* pType0 = l0->asType();
        Type* pType1 = l1->asType();
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

Module::Module( const string& a_strName, const string& a_strSourcePath )
    : NamedElement(a_strName, (a_strName == "<unknown-module>") ? o_invalid : o_always_valid)
    , m_PlatformHandle(0)
    , m_strSourcePath(a_strSourcePath)
{
}

Module::Module( const string& a_strName, const string& a_strSourcePath, const string& a_strFilePath, size_t a_PlatformHandle )
    : NamedElement(a_strName, o_always_valid|o_native)
    , m_PlatformHandle(a_PlatformHandle)
    , m_strFilePath(a_strFilePath)
    , m_strSourcePath(a_strSourcePath)
{
    o_assert(a_PlatformHandle != 0);
    o_assert(a_strFilePath.size());
}

o_initialize_cpp(Module)
{
    application()->addModule(this);
}

o_terminate_cpp(Module)
{
    for(auto it = m_PersistentElements.begin(); it != m_PersistentElements.end(); ++it)
    {
        (*it)->moduleAboutToBeDestroyed();
    }
}

Module::~Module()
{
}

bool Module::canBeUnloaded() const
{
    for(auto it = m_Packages.begin(); it != m_Packages.end(); ++it)
    {
        if(NOT((*it)->canBeUnloaded())) return false;
    }
    for(auto it = m_PersistentElements.begin(); it != m_PersistentElements.end(); ++it)
    {
        if((*it)->isSingle()) return false; /// If any persistent element still have a single reference to an element of this module, we cannot unload
    }
    return true;
}

void Module::addPackage( Package* a_pPackage )
{
    o_assert(a_pPackage->getModule() == nullptr);
    m_Packages.push_back(a_pPackage);
    addElement(a_pPackage);
}

void Module::removePackage( Package* a_pPackage )
{
    removeElement(a_pPackage);
}

// o_terminate_cpp(Module)
// {
//     vector<Class*> remaining_classes;
//     auto languageElements = m_LanguageElements;
//     std::sort(m_LanguageElements.begin(), m_LanguageElements.end(), ModuleLanguageElementSorter());
// 
//     while(!m_LanguageElements.empty())
//     {
//         auto it = m_LanguageElements.begin();
//         auto end = m_LanguageElements.end();
//         for(;it!=end;++it)
//         {
//             if((*it)->canBeDestroyed())
//                 break;
//         }
//         if(it != end)
//         {
//             LanguageElement* pElement = *it;
//             o_emit elementAboutToBeRemoved(pElement);
//             o_dynamic_delete pElement;
//         }
//         else
//         {
// 
// #if defined(_DEBUG)
//             std::cout<<console::bg_gray<<console::fg_red;
//             o_warning(false, "Module unloading process : some elements can't be destroyed due to remaining instances, see the list of all instances remaining below...");
// 
//             std::cout<<console::bg_black;
// 
//             auto it = m_LanguageElements.begin();
//             auto end = m_LanguageElements.end();
//             for(;it!=end;++it)
//             {
//                 std::cout<<console::fg_red<<"----------------------------------------------------------------------------"<<std::endl;
//                 std::cout<<console::fg_gray<<(*it)->getQualifiedDecoratedName()<<" : ";
//                 if((*it)->asClass())
//                 {
//                     std::cout<<console::fg_red<<"this "<<(*it)->asClass()->getInstanceCount()<<" ";
//                     std::cout<<console::fg_blue<<"all "<<(*it)->asClass()->getKindCount()<<std::endl;
//                 }
//             }
//             std::cout<<console::fg_gray;
// 
// #   if o_OPERATING_SYSTEM == o_OPERATING_SYSTEM_WINDOWS
//             system("pause");
// #   endif
// #endif
//             return;
//         }
//     }
// }
/*

bool Module_derivedClassHasDifferentModule(Module* a_pModule, Class* a_pClass)
{
    if(a_pClass->getModule() != a_pModule) return true;
    for(size_t i = 0; i<a_pClass->getDerivedClassCount();++i)
    {
        if(Module_derivedClassHasDifferentModule(a_pModule, a_pClass->getDerivedClass(i)))
            return true;
    }

    return false;
}

bool Module::canBeUnloaded() const
{
    for(auto it = m_LanguageElements.begin(); it != m_LanguageElements.end(); ++it)
    {
        Class* pClass = (*it)->asClass();
        if(pClass->getKindCount()) return false;
        if(Module_derivedClassHasDifferentModule((Module*)this, pClass)) return false;
    }
    return true;
}*/

phantom::signal_t Module::packageAdded(LanguageElement* a_0)
{
    if(PHANTOM_CODEGEN_m_slot_list_of_packageAdded.unblocked())
    {
        phantom::connection::slot* pSlot = PHANTOM_CODEGEN_m_slot_list_of_packageAdded.head();
        while(pSlot)
        {
            phantom::connection::pair::push(this, pSlot);
            void* args[] = { (void*)(&a_0) };
            pSlot->subroutine()->call( pSlot->receiver(), args );
            pSlot = pSlot->next();
            phantom::connection::pair::pop();
        }
    }
    return phantom::signal_t();
}

phantom::signal_t Module::packageAboutToBeRemoved(LanguageElement* a_0)
{
    if(PHANTOM_CODEGEN_m_slot_list_of_packageAboutToBeRemoved.unblocked())
    {
        phantom::connection::slot* pSlot = PHANTOM_CODEGEN_m_slot_list_of_packageAboutToBeRemoved.head();
        while(pSlot)
        {
            phantom::connection::pair::push(this, pSlot);
            void* args[] = { (void*)(&a_0) };
            pSlot->subroutine()->call( pSlot->receiver(), args );
            pSlot = pSlot->next();
            phantom::connection::pair::pop();
        }
    }
    return phantom::signal_t();
}

phantom::signal_t Module::elementAdded(LanguageElement* a_0)
{
    if(PHANTOM_CODEGEN_m_slot_list_of_elementAdded.unblocked())
    {
        phantom::connection::slot* pSlot = PHANTOM_CODEGEN_m_slot_list_of_elementAdded.head();
        while(pSlot)
        {
            phantom::connection::pair::push(this, pSlot);
            void* args[] = { (void*)(&a_0) };
            pSlot->subroutine()->call( pSlot->receiver(), args );
            pSlot = pSlot->next();
            phantom::connection::pair::pop();
        }
    }
    return phantom::signal_t();
}

phantom::signal_t Module::elementAboutToBeRemoved(LanguageElement* a_0)
{
    if(PHANTOM_CODEGEN_m_slot_list_of_elementAboutToBeRemoved.unblocked())
    {
        phantom::connection::slot* pSlot = PHANTOM_CODEGEN_m_slot_list_of_elementAboutToBeRemoved.head();
        while(pSlot)
        {
            phantom::connection::pair::push(this, pSlot);
            void* args[] = { (void*)(&a_0) };
            pSlot->subroutine()->call( pSlot->receiver(), args );
            pSlot = pSlot->next();
            phantom::connection::pair::pop();
        }
    }
    return phantom::signal_t();
}

string Module::getFileName() const
{
    return m_strFilePath.substr(m_strFilePath.find_last_of("\\/")+1);
}

void Module::elementRemoved( LanguageElement* a_pLanguageElement )
{
    if(a_pLanguageElement->asPackage())
    {
        o_emit packageAboutToBeRemoved(static_cast<Package*>(a_pLanguageElement));
        o_disconnect(static_cast<Package*>(a_pLanguageElement), elementAdded(LanguageElement*), this, elementAdded(LanguageElement*));
        o_disconnect(static_cast<Package*>(a_pLanguageElement), elementAboutToBeRemoved(LanguageElement*), this, elementAboutToBeRemoved(LanguageElement*));
        m_Packages.erase(std::find(m_Packages.begin(), m_Packages.end(), static_cast<Package*>(a_pLanguageElement)));
    }
}

byte* Module::getMemoryStart() const
{
    if(!isNative()) return 0;
#if o_OPERATING_SYSTEM == o_OPERATING_SYSTEM_WINDOWS
    return (byte*)m_PlatformHandle;
#else 
#   error missing phantom::reflection::Module::getMemoryStart() for your compiler (gets your OS shared library PIC start)
#endif
}

o_namespace_end(phantom, reflection)
