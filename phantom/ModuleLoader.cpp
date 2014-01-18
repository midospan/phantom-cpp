/* ******************* Includes ****************** */
#include <phantom/phantom.h>
#include "ModuleLoader.h"
#include "phantom/util/Message.h"
#include <windows.h>
/* ** The Class Header must be the last #include * */
/* *********************************************** */
o_registerN((phantom), ModuleLoader);

o_namespace_begin(phantom)
    
ModuleLoader::ModuleLoader(void) 
: m_pCurrentlyUnloadedModule(nullptr)
{
}

ModuleLoader::~ModuleLoader( void )
{

}

bool ModuleLoader::loadModule( const string& a_strPath, phantom::Message* a_pMessage /*= nullptr*/ )
{
    Module* pModule = phantom::moduleByFileName(a_strPath);
    o_assert(pModule == nullptr);
    string moduleName = a_strPath.substr(a_strPath.find_last_of("/\\")+1);
    Message* pMessageLoadFailed = nullptr;
    o_emit moduleAboutToBeLoaded(a_strPath);
    o_connect(phantom::typeOf<phantom::Module>(), kindCreated(void*), this, moduleInstanciated(void*));
    if(LoadLibrary(a_strPath.c_str()))
    {
        if(a_pMessage) a_pMessage->success("Module loaded : %s", moduleName.c_str());
        o_assert(m_CurrentlyLoadedModules.size());
        pModule = m_CurrentlyLoadedModules.back();
        m_LoadedModules.push_back(pModule);
        m_CurrentlyLoadedModules.pop_back();
        m_ModuleDependencies[pModule].insert(m_ModuleDependencies[pModule].end(), m_CurrentlyLoadedModules.begin(), m_CurrentlyLoadedModules.end());
        m_CurrentlyLoadedModules.clear();
        o_disconnect(phantom::typeOf<phantom::Module>(), kindCreated(void*), this, moduleInstanciated(void*));
        o_emit moduleLoaded(a_strPath);
        return true;
    }
    else
    {
        if(a_pMessage)
        {
            if(pMessageLoadFailed == nullptr) pMessageLoadFailed = a_pMessage->error("Cannot load module : %s", moduleName.c_str());
#if o_OPERATING_SYSTEM == o_OPERATING_SYSTEM_WINDOWS
            LPVOID lpMsgBuf;
            DWORD dw = GetLastError(); 

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
        o_disconnect(phantom::typeOf<phantom::Module>(), kindCreated(void*), this, moduleInstanciated(void*));
        o_emit moduleLoadFailed(a_strPath);
        return false;
    }
    return false;
}

bool ModuleLoader::unloadModule( const string& a_strPath, phantom::Message* a_pMessage /*= nullptr*/ )
{
    o_emit moduleAboutToBeUnloaded(a_strPath);

    Module* pModule = phantom::moduleByFileName(a_strPath);
    string moduleName = a_strPath.substr(a_strPath.find_last_of("/\\")+1);
    o_assert(pModule);
    o_assert(std::find(m_LoadedModules.begin(), m_LoadedModules.end(), pModule) != m_LoadedModules.end(), "This module was not loaded via ModuleLoader");
    Message* pMessageUnloadFailed = nullptr;
    bool canUnload = true;
    for(auto it = m_ModuleDependencies[pModule].begin(); it != m_ModuleDependencies[pModule].end(); ++it)
    {
        if(NOT((*it)->canBeUnloaded()))
        {
            canUnload = false;
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
    }
    
    if(!canUnload)
    {
        o_emit moduleUnloadFailed(a_strPath);
        return false;
    }

    o_connect(phantom::typeOf<Module>(), kindDestroyed(void*), this, moduleDestroyed(void*));

    if(FreeLibrary((HMODULE)pModule->getPlatformHandle()))
    {
        if(a_pMessage) a_pMessage->success("Module unloaded : %s", moduleName.c_str());

        m_LoadedModules.erase(std::find(m_LoadedModules.begin(), m_LoadedModules.end(), m_pCurrentlyUnloadedModule));
        m_ModuleDependencies.erase(m_pCurrentlyUnloadedModule);
        m_pCurrentlyUnloadedModule = nullptr;
        o_disconnect(phantom::typeOf<Module>(), kindDestroyed(void*), this, moduleDestroyed(void*));

        o_emit moduleUnloaded(a_strPath);
        return true;
    }
    else
    {
        if(a_pMessage)
        {
            if(pMessageUnloadFailed == nullptr) pMessageUnloadFailed = a_pMessage->error("Cannot unload module : %s", moduleName.c_str());
#if o_OPERATING_SYSTEM == o_OPERATING_SYSTEM_WINDOWS
            LPVOID lpMsgBuf;
            DWORD dw = GetLastError(); 

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
        m_pCurrentlyUnloadedModule = nullptr;
        o_disconnect(phantom::typeOf<phantom::Module>(), kindDestroyed(void*), this, moduleDestroyed(void*));
        o_emit moduleUnloadFailed(a_strPath);
        return false;
    }
}

void ModuleLoader::moduleInstanciated( void* a_pModule )
{
    phantom::Module* pModule = phantom::as<phantom::Module*>(a_pModule);
    m_CurrentlyLoadedModules.push_back(pModule);
}

void ModuleLoader::moduleDestroyed( void* a_pModule )
{
    phantom::Module* pModule = phantom::as<phantom::Module*>(a_pModule);
    if(m_pCurrentlyUnloadedModule == nullptr)
    {
        m_pCurrentlyUnloadedModule = pModule;
    }
    // Debug check (check that an unloaded module which is only a dependency is not a deliberately loaded module (shouldn't happen because DLL load counters should match our internal module storage)
#if defined(_DEBUG)
    else 
    {
        o_assert(std::find(m_LoadedModules.begin(), m_LoadedModules.end(), pModule) == m_LoadedModules.end());// Remove dependencies reference of this module
        /*for(auto it = m_ModuleDependencies.begin(); it != m_ModuleDependencies.end(); ++it)
        {
            o_assert(pModule != it->first);
            auto& vec = it->second;
            for(auto it = vec.begin(); it != vec.end(); ++it)
            {
                o_assert(*it != pModule)
            }
        }*/
    }
#endif
}

bool ModuleLoader::hasLoadedModule( const string& a_strPath ) const
{
    Module* pModule = phantom::moduleByFileName(a_strPath);
    if(pModule == nullptr) return false;
    return hasLoadedModule(pModule);
}

bool ModuleLoader::hasLoadedModule( Module* a_pModule ) const
{
    return std::find(m_LoadedModules.begin(), m_LoadedModules.end(), a_pModule) != m_LoadedModules.end();
}

o_namespace_end(phantom)
