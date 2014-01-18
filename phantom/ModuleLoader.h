

#ifndef o_ModuleLoader_h__
#define o_ModuleLoader_h__
// #pragma message("Including "__FILE__)


/* ****************** Includes ******************* */
#include <phantom/phantom.h>
/* **************** Declarations ***************** */
/* *********************************************** */
o_namespace_begin(phantom)

class Message;

class o_export ModuleLoader
{
public:
    ModuleLoader(void);
    ~ModuleLoader(void);

    bool loadModule(const string& a_strPath, Message* a_pMessage = nullptr);
    bool unloadModule(const string& a_strPath, Message* a_pMessage = nullptr);
    bool hasLoadedModule(const string& a_strPath) const;
    bool hasLoadedModule( Module* a_pModule ) const;

    vector<Module*>::const_iterator beginLoadedModules() const { return m_LoadedModules.begin(); }
    vector<Module*>::const_iterator endLoadedModules() const { return m_LoadedModules.end(); }

protected:
    void moduleInstanciated(void* a_pModule);
    void moduleDestroyed(void* a_pModule);
            
protected:
    o_signal_data(moduleAboutToBeLoaded, const string&);
    o_signal_data(moduleLoaded, const string&);
    o_signal_data(moduleLoadFailed, const string&);
    o_signal_data(moduleAboutToBeUnloaded, const string&);
    o_signal_data(moduleUnloaded, const string&);
    o_signal_data(moduleUnloadFailed, const string&);
       
protected:
    vector<Module*> m_LoadedModules;
    map<Module*, vector<Module*>> m_ModuleDependencies;
    Module* m_pCurrentlyUnloadedModule;
    vector<Module*> m_CurrentlyLoadedModules;
};

o_namespace_end(phantom)

o_classN((phantom), ModuleLoader)
{
    o_reflection
    {
        o_slot(void, moduleInstanciated, (void*));
        o_slot(void, moduleDestroyed, (void*));
        o_signal(moduleAboutToBeLoaded, (const string&));
        o_signal(moduleLoaded, (const string&));
        o_signal(moduleAboutToBeUnloaded, (const string&));
        o_signal(moduleUnloaded, (const string&));
        o_signal(moduleLoadFailed, (const string&));
        o_signal(moduleUnloadFailed, (const string&));
    };
};
o_exposeN((phantom), ModuleLoader);

#endif // o_ModuleLoaded_h__