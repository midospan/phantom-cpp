/* ******************* Includes ****************** */
#include <phantom/phantom.h>
#include "ModuleLoader.h"
#include "ModuleLoader.hxx"
#include "phantom/Message.h"
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#if o_PLATFORM == o_PLATFORM_WINDOWS_PC
#include <windows.h>
#include <TlHelp32.h>
#endif
/* ** The Class Header must be the last #include * */
/* *********************************************** */
o_registerN((phantom), ModuleLoader);

o_namespace_begin(phantom)

map<Module*, size_t> sg_EmptyLibraryLoadedModules;

string ModuleLoader_normalizePathString(const string& a_strPath)
{
    boost::filesystem::path p (a_strPath.c_str());
    return p.generic_string().c_str();
}

string ModuleLoader_makeWindowsPathString(const string& a_strPath)
{
    string result = a_strPath;
    for(size_t i = 0; i<result.size(); ++i)
    {
        if(result[i] == '/') result[i] = '\\';
    }
    return result;
}

ModuleLoader::ModuleLoader(void)
    : m_OperationCounter(0)
    , m_pDataBase(nullptr)
{
}

ModuleLoader::~ModuleLoader( void )
{

}

o_initialize_cpp(ModuleLoader)
{
    o_connect(o_type_of(Module), kindCreated(void*), this, moduleInstanciated(void*));
    o_connect(o_type_of(Module), kindDestroyed(void*), this, moduleDeleted(void*));
}

o_terminate_cpp(ModuleLoader)
{
    o_disconnect(o_type_of(Module), kindCreated(void*), this, moduleInstanciated(void*));
    o_disconnect(o_type_of(Module), kindDestroyed(void*), this, moduleDeleted(void*));
}

bool ModuleLoader::loadLibrary( const string& a_strPath, phantom::Message* a_pMessage /*= nullptr*/ )
{
    string strPath = ModuleLoader_normalizePathString(a_strPath);
    m_OperationCounter++;

    o_emit libraryAboutToBeLoaded(strPath);

    Module* pModule = phantom::moduleByFilePath(strPath);
    string moduleName = strPath.substr(strPath.find_last_of("/\\")+1);
    Message* pMessageLoadFailed = nullptr;

    bool result = true;
    if(LoadLibrary(strPath.c_str()))
    {
        if(a_pMessage) a_pMessage->success(moduleName.c_str(), "Module loaded : %s", moduleName.c_str());
        o_warning(m_CurrentlyLoadedModules.size(), "No module found in the loaded library");
        m_CurrentlyLoadedModules.clear();
    }
    else
    {
        result = false;
        DWORD dw = GetLastError();
        if(a_pMessage)
        {
            if(pMessageLoadFailed == nullptr) pMessageLoadFailed = a_pMessage->error(moduleName.c_str(), "Cannot load module : %s", moduleName.c_str());
#if o_OPERATING_SYSTEM == o_OPERATING_SYSTEM_WINDOWS
            LPVOID lpMsgBuf;

            FormatMessage(
                FORMAT_MESSAGE_ALLOCATE_BUFFER |
                FORMAT_MESSAGE_FROM_SYSTEM |
                FORMAT_MESSAGE_IGNORE_INSERTS,
                NULL,
                dw,
                MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                (LPTSTR) &lpMsgBuf,
                0, NULL );

            string clampedMessage = (char*)lpMsgBuf;
            clampedMessage = clampedMessage.substr(0, clampedMessage.find_first_of("\r\n"));
            pMessageLoadFailed->error(variant(), "System DLL loading failed : %s", clampedMessage.c_str());

            LocalFree(lpMsgBuf);
#endif
        }
        m_CurrentlyLoadedModules.clear();
    }
    updateReferenceCounts(strPath, true);
    if(result)
    {
        o_emit libraryLoaded(strPath);
    }
    else
    {
        o_emit libraryLoadFailed(strPath);
    }
    m_OperationCounter--;
    return result;
}

bool ModuleLoader::unloadLibrary( const string& a_strPath, phantom::Message* a_pMessage /*= nullptr*/ )
{
    string strPath = ModuleLoader_normalizePathString(a_strPath);
    m_OperationCounter++;

    o_emit libraryAboutToBeUnloaded(strPath);

    if(NOT(libraryCanBeUnloaded(strPath, a_pMessage)))
    {
        o_emit libraryUnloadFailed(strPath);
        m_OperationCounter--;
        return false;
    }

    bool result = true;

    Module* pModule = phantom::moduleByFilePath(strPath);
    string moduleName = strPath.substr(strPath.find_last_of("/\\")+1);
    o_assert(pModule);
    o_assert(std::find(m_LoadedModules.begin(), m_LoadedModules.end(), pModule) != m_LoadedModules.end(), "This module was not loaded via ModuleLoader");
    Message* pMessageUnloadFailed = nullptr;

    if(FreeLibrary((HMODULE)pModule->getPlatformHandle()))
    {
        if(a_pMessage) a_pMessage->success(moduleName.c_str(), "Module unloaded : %s", moduleName.c_str());
    }
    else
    {
        result = false;
        DWORD dw = GetLastError();
        if(a_pMessage)
        {
            if(pMessageUnloadFailed == nullptr) pMessageUnloadFailed = a_pMessage->error(moduleName.c_str(), "Cannot unload module : %s", moduleName.c_str());
#if o_OPERATING_SYSTEM == o_OPERATING_SYSTEM_WINDOWS
            LPVOID lpMsgBuf;

            FormatMessage(
                FORMAT_MESSAGE_ALLOCATE_BUFFER |
                FORMAT_MESSAGE_FROM_SYSTEM |
                FORMAT_MESSAGE_IGNORE_INSERTS,
                NULL,
                dw,
                MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                (LPTSTR) &lpMsgBuf,
                0, NULL );

            string clampedMessage = (char*)lpMsgBuf;
            clampedMessage = clampedMessage.substr(0, clampedMessage.find_first_of("\r\n"));

            pMessageUnloadFailed->error(moduleName.c_str(), "System DLL unloading failed : %s", clampedMessage.c_str());

            LocalFree(lpMsgBuf);
#endif
        }
    }
    updateReferenceCounts(strPath, false);
    if(result)
    {
        m_LibraryModules.erase(strPath);
        o_emit libraryUnloaded(strPath);
    }
    else
    {
        o_emit libraryUnloadFailed(strPath);
    }
    m_OperationCounter--;
    return result;
}

void ModuleLoader::moduleInstanciated( void* a_pModule )
{
    o_assert(m_OperationCounter, "DLL loader must be responsible for loading phantom modules, don't use platform specific function to load them such as LoadLibrary/FreeLibrary, use ModuleLoader::loadLibrary/unloadlibrary");
    phantom::Module* pModule = phantom::as<phantom::Module*>(a_pModule);
    m_CurrentlyLoadedModules.push_back(pModule);
    m_LoadedModuleCounts[pModule] = 0;
    m_LoadedModules.push_back(pModule);
    o_connect(a_pModule, elementAdded(reflection::LanguageElement*), this, elementAdded(reflection::LanguageElement*));
    o_connect(a_pModule, elementAboutToBeRemoved(reflection::LanguageElement*), this, elementAboutToBeRemoved(reflection::LanguageElement*));
    o_connect(a_pModule, elementsAboutToBeReplaced(const vector<reflection::LanguageElement*>&), this, elementsAboutToBeReplaced(const vector<reflection::LanguageElement*>&));
    o_connect(a_pModule, elementsReplaced(const vector<reflection::LanguageElement*>&, const vector<reflection::LanguageElement*>&), this, elementsReplaced(const vector<reflection::LanguageElement*>&, const vector<reflection::LanguageElement*>&));
    o_emit moduleCreated(pModule);
}

void ModuleLoader::moduleDeleted( void* a_pModule )
{
    o_disconnect(a_pModule, elementAdded(reflection::LanguageElement*), this, elementAdded(reflection::LanguageElement*));
    o_disconnect(a_pModule, elementAboutToBeRemoved(reflection::LanguageElement*), this, elementAboutToBeRemoved(reflection::LanguageElement*));
    o_disconnect(a_pModule, elementsAboutToBeReplaced(const vector<reflection::LanguageElement*>&), this, elementsAboutToBeReplaced(const vector<reflection::LanguageElement*>&));
    o_disconnect(a_pModule, elementsReplaced(const vector<reflection::LanguageElement*>&, const vector<reflection::LanguageElement*>&), this, elementsReplaced(const vector<reflection::LanguageElement*>&, const vector<reflection::LanguageElement*>&));
    o_assert(m_OperationCounter, "DLL loader must be responsible for loading phantom modules, don't use platform specific function to load them such as LoadLibrary/FreeLibrary, use ModuleLoader::loadLibrary/unloadlibrary");
    phantom::Module* pModule = phantom::as<phantom::Module*>(a_pModule);
    o_emit moduleUnloaded(pModule, m_LoadedModuleCounts[pModule], 0);
    m_LoadedModuleCounts.erase(pModule);
    m_LoadedModules.erase(std::find(m_LoadedModules.begin(), m_LoadedModules.end(), pModule));// Remove dependencies reference of this module
    o_emit moduleDestroyed(pModule);
}

void ModuleLoader::updateReferenceCounts(const string& a_strLibPath, bool a_bLoading)
{
    HANDLE snapshotHandle = CreateToolhelp32Snapshot(
        TH32CS_SNAPMODULE,
        GetCurrentProcessId()
        );
    MODULEENTRY32 wentry;
    BOOL result = Module32First(snapshotHandle, &wentry);
    size_t matchingModuleCount = 0;
    if(result == FALSE)
    {
        o_exception(exception::base_exception, "Module32First failed, it happens when some code is written befire CreateToolhelp32Snapshot, don's ask me why...")
    }
    struct quick_entry
    {
        DWORD ProccntUsage;
        HMODULE hModule;
    };

    vector<quick_entry> entries;
    do
    {
        quick_entry entry;
        entry.ProccntUsage = wentry.ProccntUsage;
        entry.hModule = wentry.hModule;
        entries.push_back(entry);
    }
    while(Module32Next(snapshotHandle, &wentry));

    string strLibPath = ModuleLoader_normalizePathString(a_strLibPath);

    for(auto it = m_LoadedModules.begin(); it != m_LoadedModules.end(); ++it)
    {
        Module* pModule = *it;
        for(auto it = entries.begin(); it != entries.end(); ++it)
        {
            quick_entry& entry = *it;
            if(entry.hModule == (HMODULE)pModule->getPlatformHandle())
            {
                size_t oldCount = m_LoadedModuleCounts[pModule];
                m_LoadedModuleCounts[pModule] = entry.ProccntUsage;
                if(entry.ProccntUsage != 0x0000ffff)
                {
                    if(a_bLoading)
                    {
                        o_assert(oldCount <= entry.ProccntUsage, "A dynamic library loading shoudn't decrement any reference counter");
                        if((int)oldCount < entry.ProccntUsage)
                        {
                            m_LibraryModules[strLibPath][pModule] += ((size_t)entry.ProccntUsage)-oldCount;
                            o_emit moduleLoaded(pModule, oldCount, entry.ProccntUsage);
                        }
                    }
                    else
                    {
                        o_assert(oldCount >= entry.ProccntUsage, "A dynamic library unloading shoudn't increment any reference counter");
                        if(oldCount > entry.ProccntUsage)
                        {
                            o_emit moduleUnloaded(pModule, oldCount, entry.ProccntUsage);
                        }
                    }
                }
                m_LoadedModuleCounts[pModule] = entry.ProccntUsage != 0x0000ffff ? entry.ProccntUsage : 1;
                matchingModuleCount++;
                break;
            }
        }
    }
    o_assert(matchingModuleCount == m_LoadedModules.size(), "A loaded module has not been found in the loaded dlls");
    o_verify(CloseHandle(snapshotHandle), "CloseHandle(snapshotHandle)");
}

size_t ModuleLoader::getModuleLoadCount( Module* a_pModule ) const
{
    auto found = m_LoadedModuleCounts.find(a_pModule);
    if(found == m_LoadedModuleCounts.end()) return 0;
    return found->second;
}

map<Module*, size_t>::const_iterator ModuleLoader::beginLoadedLibraryModules( const string& a_strPath ) const
{
    auto abs = boost::filesystem::absolute(a_strPath.c_str());
    for(auto it = m_LibraryModules.begin(); it != m_LibraryModules.end(); ++it)
    {
        if(boost::filesystem::equivalent(boost::filesystem::absolute(it->first.c_str()), abs))
            return it->second.begin();
    }
    return sg_EmptyLibraryLoadedModules.begin();
}

map<Module*, size_t>::const_iterator ModuleLoader::endLoadedLibraryModules( const string& a_strPath ) const
{
    auto abs = boost::filesystem::absolute(a_strPath.c_str());
    for(auto it = m_LibraryModules.begin(); it != m_LibraryModules.end(); ++it)
    {
        if(boost::filesystem::equivalent(boost::filesystem::absolute(it->first.c_str()), abs))
            return it->second.end();
    }
    return sg_EmptyLibraryLoadedModules.end();
}

bool Module_derivedClassHasDifferentModule(const string& moduleName, Module* a_pModule, const phantom::vector<Module*>& a_ModulesAboutToBeUnloaded, reflection::Class* a_pClass, Message*& a_pMessageUnloadFailed, Message* a_pMessage)
{
    bool bResult = false;
    for(size_t i = 0; i<a_pClass->getDerivedClassCount();++i)
    {
        reflection::Class* pDerivedClass = a_pClass->getDerivedClass(i);
        if(std::find(a_ModulesAboutToBeUnloaded.begin(), a_ModulesAboutToBeUnloaded.end(), pDerivedClass->getModule()) == a_ModulesAboutToBeUnloaded.end())
        {
            // We don't find the derived class module in the currently unloaded ones
            if(a_pMessage)
            {
                string derivedClassModuleName = pDerivedClass->getModule()->getFileName().substr(pDerivedClass->getModule()->getFileName().find_last_of("/\\")+1) ;
                bResult = true;
                if(a_pMessageUnloadFailed == nullptr)
                    a_pMessageUnloadFailed = a_pMessage->error(moduleName.c_str(), "Cannot unload module : %s", moduleName.c_str());
                a_pMessageUnloadFailed->error(variant(), "Derived class '%s' of '%s' belongs to another loaded module '%s'", pDerivedClass->getQualifiedDecoratedName().c_str(), a_pClass->getQualifiedDecoratedName().c_str(), derivedClassModuleName.c_str());
            }
            else return true;
        }
        bool result = Module_derivedClassHasDifferentModule(moduleName, a_pModule, a_ModulesAboutToBeUnloaded, pDerivedClass, a_pMessageUnloadFailed, a_pMessage);
        if(a_pMessage)
        {
            bResult = result;
        }
        else if(result) return true;
    }

    return bResult;
}

bool ModuleLoader::libraryCanBeUnloaded( const string& a_strPath, Message* a_pMessage, vector<reflection::LanguageElement*>* a_pBlockingElements /*= nullptr*/ ) const
{
    string strPath = ModuleLoader_normalizePathString(a_strPath);
    string moduleName = strPath.substr(strPath.find_last_of("/\\")+1);
    Message* pMessageUnloadFailed = nullptr;
    bool canUnload = true;
    vector<Module*> modulesAboutToBeUnloaded;

    for(auto it = beginLoadedLibraryModules(strPath); it != endLoadedLibraryModules(strPath); ++it)
    {
        Module* pModule = it->first;
        if(getModuleLoadCount(pModule) == it->second)
        {
            modulesAboutToBeUnloaded.push_back(pModule);
        }
    }
    for(auto it = modulesAboutToBeUnloaded.begin(); it != modulesAboutToBeUnloaded.end(); ++it)
    {
        Module* pModule = *it;
        for(auto it = pModule->beginLanguageElements(); it != pModule->endLanguageElements(); ++it)
        {
            reflection::Class* pClass = (*it)->asClass();
            if(pClass)
            {
                if(pClass->getInstanceCount())
                {
                    if(a_pBlockingElements)
                    {
                        a_pBlockingElements->push_back(pClass);
                    }
                    canUnload = false;
                    if(a_pMessage)
                    {
                        if(pMessageUnloadFailed == nullptr)
                            pMessageUnloadFailed = a_pMessage->error(moduleName.c_str(), "Cannot unload module : %s", moduleName.c_str());
                        pMessageUnloadFailed->error(variant(), "Class '%s' still have %d instances", pClass->getQualifiedDecoratedName().c_str(), pClass->getInstanceCount());
                    } else return false;
                }
                if(Module_derivedClassHasDifferentModule(moduleName, pModule, modulesAboutToBeUnloaded, pClass, pMessageUnloadFailed, a_pMessage))
                {
                    if(a_pBlockingElements)
                    {
                        a_pBlockingElements->push_back(pClass);
                    }
                    if(a_pMessage)
                        canUnload = false;
                    else return false;
                }
            }
        }
    }
    return canUnload;
}

size_t ModuleLoader::getLibraryModuleLoadCount( const string& a_strPath, Module* a_pModule ) const
{
    string strPath = ModuleLoader_normalizePathString(a_strPath);
    auto foundLib = m_LibraryModules.find(strPath);
    if(foundLib == m_LibraryModules.end()) return 0;
    auto foundModule = foundLib->second.find(a_pModule);
    if(foundModule == foundLib->second.end()) return 0;
    return foundModule->second;
}

void ModuleLoader::loadMain( const string& a_strFileName, Message* a_pMessage )
{
    m_OperationCounter++;
    phantom::installReflection("main", a_strFileName, (size_t)GetModuleHandle(0));
    m_OperationCounter--;
}

void ModuleLoader::unloadMain( Message* a_pMessage /*= nullptr*/ )
{
    m_OperationCounter++;
    phantom::uninstallReflection("main");
    m_OperationCounter--;
}

bool ModuleLoader::isLibraryLoaded( const string& a_strPath ) const
{
    auto abs = boost::filesystem::absolute(a_strPath.c_str());
    for(auto it = m_LibraryModules.begin(); it != m_LibraryModules.end(); ++it)
    {
        if(boost::filesystem::equivalent(boost::filesystem::absolute(it->first.c_str()), abs))
            return true;
    }
    return false;
}

bool ModuleLoader::isModuleLoaded( const string& a_strFileName ) const
{
    for(auto it = m_LoadedModules.begin(); it != m_LoadedModules.end(); ++it)
    {
        if((*it)->getFileName() == a_strFileName) return true;
    }
    return false;
}

void ModuleLoader::setDataBase( serialization::DataBase* a_pDataBase )
{
    if(m_pDataBase == a_pDataBase) return;
    if(m_pDataBase)
    {
        o_disconnect(this, moduleLoaded(Module*, size_t, size_t), m_pDataBase, moduleLoaded(Module*, size_t, size_t));
        o_disconnect(this, moduleUnloaded(Module*, size_t, size_t), m_pDataBase, moduleUnloaded(Module*, size_t, size_t));
    }
    m_pDataBase = a_pDataBase;
    if(m_pDataBase)
    {
        o_connect(this, moduleLoaded(Module*, size_t, size_t), m_pDataBase, moduleLoaded(Module*, size_t, size_t));
        o_connect(this, moduleUnloaded(Module*, size_t, size_t), m_pDataBase, moduleUnloaded(Module*, size_t, size_t));
    }
}

auto_dll_loader::auto_dll_loader()
{
    phantom::moduleLoader()->m_OperationCounter++;
}

auto_dll_loader::~auto_dll_loader()
{
    phantom::moduleLoader()->m_OperationCounter--;
}


o_namespace_end(phantom)
