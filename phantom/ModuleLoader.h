

#ifndef o_ModuleLoader_h__
#define o_ModuleLoader_h__
// #pragma message("Including "__FILE__)

/* ****************** Includes ******************* */
#include <phantom/phantom.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom), ModuleLoader);
/* *********************************************** */
o_namespace_begin(phantom)

class Message;

class o_export ModuleLoader
{
public:
    ModuleLoader(void);
    ~ModuleLoader(void);

    o_initialize();
    o_terminate();

    bool loadLibrary(const string& a_strPath, Message* a_pMessage = nullptr);
    bool unloadLibrary(const string& a_strPath, Message* a_pMessage = nullptr);

    vector<Module*>::const_iterator beginLoadedModules() const { return m_LoadedModules.begin(); }
    vector<Module*>::const_iterator endLoadedModules() const { return m_LoadedModules.end(); }

    size_t                          getModuleLoadCount(Module* a_pModule) const;

    size_t                          getLibraryModuleLoadCount(const string& a_strPath, Module* a_pModule) const;

    bool                            isLibraryLoaded(const string& a_strPath) const { return m_LibraryModules.find(a_strPath) != m_LibraryModules.end(); }

    map<Module*, size_t>::const_iterator beginLoadedLibraryModules(const string& a_strPath) const;
    map<Module*, size_t>::const_iterator endLoadedLibraryModules(const string& a_strPath) const;

    map<string, map<Module*, size_t>>::const_iterator beginLoadedLibraries() const { return m_LibraryModules.begin(); }
    map<string, map<Module*, size_t>>::const_iterator endLoadedLibraries() const { return m_LibraryModules.end(); }

    bool                            libraryCanBeUnloaded(const string& a_strPath, phantom::Message* a_pMessage = nullptr) const;

protected:
    void moduleInstanciated(void* a_pModule);
    void moduleDestroyed(void* a_pModule);
    void updateReferenceCounts(const string& a_strLibPath, bool a_bLoading);
            
protected:
    o_signal_data(libraryAboutToBeLoaded, const string&);
    o_signal_data(libraryLoaded, const string&);
    o_signal_data(libraryLoadFailed, const string&);
    o_signal_data(libraryAboutToBeUnloaded, const string&);
    o_signal_data(libraryUnloaded, const string&);
    o_signal_data(libraryUnloadFailed, const string&);
    o_signal_data(moduleLoaded, Module*, size_t, size_t);
    o_signal_data(moduleUnloaded, Module*, size_t, size_t);

protected:
    vector<Module*> m_LoadedModules;
    map<Module*, size_t> m_LoadedModuleCounts;
    map<string, map<Module*, size_t>> m_LibraryModules;
    vector<Module*> m_CurrentlyLoadedModules;
    size_t m_OperationCounter;
};

o_namespace_end(phantom)

#endif // o_ModuleLoaded_h__