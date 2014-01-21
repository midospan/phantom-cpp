/* ******************* Includes ****************** */
#include <phantom/phantom.h>
#include "ModuleLoader.h"
#include "phantom/util/Message.h"
#include <windows.h>
#include <TlHelp32.h>
/* ** The Class Header must be the last #include * */
/* *********************************************** */
o_registerN((phantom), ModuleLoader);

o_namespace_begin(phantom)
    
ModuleLoader::ModuleLoader(void) 
    : m_OperationCounter(0)
{
}

ModuleLoader::~ModuleLoader( void )
{

}

o_initialize_cpp(ModuleLoader)
{
    o_connect(phantom::typeOf<Module>(), kindCreated(void*), this, moduleInstanciated(void*));
    o_connect(phantom::typeOf<Module>(), kindDestroyed(void*), this, moduleDestroyed(void*));
}

o_terminate_cpp(ModuleLoader)
{
    o_disconnect(phantom::typeOf<Module>(), kindCreated(void*), this, moduleInstanciated(void*));
    o_disconnect(phantom::typeOf<Module>(), kindDestroyed(void*), this, moduleDestroyed(void*));
}

bool ModuleLoader::loadLibrary( const string& a_strPath, phantom::Message* a_pMessage /*= nullptr*/ )
{
    m_OperationCounter++;

    o_emit libraryAboutToBeLoaded(a_strPath);

    Module* pModule = phantom::moduleByFileName(a_strPath);
    string moduleName = a_strPath.substr(a_strPath.find_last_of("/\\")+1);
    Message* pMessageLoadFailed = nullptr;

    bool result = true;
    if(LoadLibrary(a_strPath.c_str()))
    {
        if(a_pMessage) a_pMessage->success("Module loaded : %s", moduleName.c_str());
        o_warning(m_CurrentlyLoadedModules.size(), "No module found in the loaded library");
        m_CurrentlyLoadedModules.clear();
    }
    else
    {
        result = false;
        DWORD dw = GetLastError(); 
        if(a_pMessage)
        {
            if(pMessageLoadFailed == nullptr) pMessageLoadFailed = a_pMessage->error("Cannot load module : %s", moduleName.c_str());
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
            pMessageLoadFailed->error("System DLL loading failed : %s", clampedMessage.c_str());

            LocalFree(lpMsgBuf);
#endif
        }
        m_CurrentlyLoadedModules.clear();
    }
    updateReferenceCounts(a_strPath, true);
    if(result)
    {
        o_emit libraryLoaded(a_strPath);
    }
    else 
    {
        o_emit libraryLoadFailed(a_strPath);
    }
    m_OperationCounter--;
    return result;
}

bool ModuleLoader::unloadLibrary( const string& a_strPath, phantom::Message* a_pMessage /*= nullptr*/ )
{
    m_OperationCounter++;

    o_emit libraryAboutToBeUnloaded(a_strPath);
    
    if(NOT(libraryCanBeUnloaded(a_strPath, a_pMessage)))
    {
        o_emit libraryUnloadFailed(a_strPath);
        m_OperationCounter--;
        return false;
    }

    bool result = true;

    Module* pModule = phantom::moduleByFileName(a_strPath);
    string moduleName = a_strPath.substr(a_strPath.find_last_of("/\\")+1);
    o_assert(pModule);
    o_assert(std::find(m_LoadedModules.begin(), m_LoadedModules.end(), pModule) != m_LoadedModules.end(), "This module was not loaded via ModuleLoader");
    Message* pMessageUnloadFailed = nullptr;

    if(FreeLibrary((HMODULE)pModule->getPlatformHandle()))
    {
        if(a_pMessage) a_pMessage->success("Module unloaded : %s", moduleName.c_str());
    }
    else
    {
        result = false;
        DWORD dw = GetLastError(); 
        if(a_pMessage)
        {
            if(pMessageUnloadFailed == nullptr) pMessageUnloadFailed = a_pMessage->error("Cannot unload module : %s", moduleName.c_str());
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

            pMessageUnloadFailed->error("System DLL unloading failed : %s", clampedMessage.c_str());

            LocalFree(lpMsgBuf);
#endif
        }
    }
    updateReferenceCounts(a_strPath, false);
    if(result)
    {
        m_LibraryModules.erase(a_strPath);
        o_emit libraryUnloaded(a_strPath);
    }
    else 
    {
        o_emit libraryUnloadFailed(a_strPath);
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
}

void ModuleLoader::moduleDestroyed( void* a_pModule )
{
    o_assert(m_OperationCounter, "DLL loader must be responsible for loading phantom modules, don't use platform specific function to load them such as LoadLibrary/FreeLibrary, use ModuleLoader::loadLibrary/unloadlibrary");
    phantom::Module* pModule = phantom::as<phantom::Module*>(a_pModule);
    o_emit moduleUnloaded(pModule, m_LoadedModuleCounts[pModule], 0);
    m_LoadedModuleCounts.erase(pModule);
    m_LoadedModules.erase(std::find(m_LoadedModules.begin(), m_LoadedModules.end(), pModule));// Remove dependencies reference of this module
}

void ModuleLoader::updateReferenceCounts(const string& a_strLibPath, bool a_bLoading)
{
    HANDLE snapshotHandle = CreateToolhelp32Snapshot(
        TH32CS_SNAPMODULE,
        GetCurrentProcessId()
        );
    MODULEENTRY32 entry;
    BOOL result = Module32First(snapshotHandle, &entry);
    size_t matchingModuleCount = 0;
    if(result)
    {
        do 
        {
            for(auto it = m_LoadedModules.begin(); it != m_LoadedModules.end(); ++it) 
            {
                Module* pModule = *it;
                if(entry.hModule == (HMODULE)(*it)->getPlatformHandle())
                {
                    size_t oldCount = m_LoadedModuleCounts[pModule];
                    m_LoadedModuleCounts[pModule] = entry.ProccntUsage;
                    if(a_bLoading)
                    {
                        o_assert(oldCount <= entry.ProccntUsage, "A dynamic library loading shoudn't decrement any reference counter");
                        if((int)oldCount < entry.ProccntUsage)
                        {
                            m_LibraryModules[a_strLibPath][pModule] += ((size_t)entry.ProccntUsage)-oldCount;
                            o_emit moduleLoaded(pModule, oldCount, entry.ProccntUsage);
                        }
                    }
                    else 
                    {
                        o_assert(oldCount >= entry.ProccntUsage, "A dynamic library unloading shoudn't increment any reference counter");
                        if(oldCount > entry.ProccntUsage)
                        {
                            o_emit moduleUnloaded(*it, oldCount, entry.ProccntUsage);
                        }
                    }
                    m_LoadedModuleCounts[*it] = entry.ProccntUsage;
                    matchingModuleCount++;
                    break;
                }
            }
        }
        while(Module32Next(snapshotHandle, &entry));
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
    o_assert(isLibraryLoaded(a_strPath));
    return m_LibraryModules.find(a_strPath)->second.begin();
}

map<Module*, size_t>::const_iterator ModuleLoader::endLoadedLibraryModules( const string& a_strPath ) const
{
    o_assert(isLibraryLoaded(a_strPath));
    return m_LibraryModules.find(a_strPath)->second.end();
}

bool ModuleLoader::libraryCanBeUnloaded( const string& a_strPath, phantom::Message* a_pMessage ) const
{
    Message* pMessageUnloadFailed = nullptr;
    bool canUnload = true;
    for(auto it = beginLoadedLibraryModules(a_strPath); it != endLoadedLibraryModules(a_strPath); ++it)
    {
        Module* pModule = it->first;
        if(getModuleLoadCount(pModule) == it->second AND NOT(pModule->canBeUnloaded())) 
        {
            canUnload = false;
            if(a_pMessage)
            {
                string moduleName = pModule->getFileName().substr(pModule->getFileName().find_last_of("/\\")+1);
                for(auto it = pModule->beginLanguageElements(); it != pModule->endLanguageElements(); ++it)
                {
                    reflection::Class* pClass = (*it)->asClass();
                    if(pClass)
                    {
                        if(pClass->getInstanceCount() != 0)
                        {
                            if(a_pMessage)
                            {
                                if(pMessageUnloadFailed == nullptr) 
                                    pMessageUnloadFailed = a_pMessage->error("Cannot unload module : %s", moduleName.c_str());
                                pMessageUnloadFailed->error("Class still used : %s", pClass->getQualifiedDecoratedName().c_str());
                            }
                        }
                    }
                }
            }
            else return false;
        }
    }
    return canUnload;
}

size_t ModuleLoader::getLibraryModuleLoadCount( const string& a_strPath, Module* a_pModule ) const
{
    auto foundLib = m_LibraryModules.find(a_strPath);
    if(foundLib == m_LibraryModules.end()) return 0;
    auto foundModule = foundLib->second.find(a_pModule);
    if(foundModule == foundLib->second.end()) return 0;
    return foundModule->second;
}

o_namespace_end(phantom)
