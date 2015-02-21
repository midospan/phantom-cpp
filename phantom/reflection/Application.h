

#ifndef o_Application_h__
#define o_Application_h__

/* ****************** Includes ******************* */
#include <phantom/phantom.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, reflection), Application);
o_fwd(class, phantom, Message);
/* *********************************************** */
o_namespace_begin(phantom, reflection)

#define o_main(name, ...) \
    phantom::reflection::auto_dll_loader PHANTOM_RESERVED_auto_dll_loader; \
    phantom::Phantom PHANTOM_CODEGEN_main(name,__FILE__,##__VA_ARGS__);


struct o_export auto_dll_loader
{
    auto_dll_loader();
    ~auto_dll_loader();
};

class o_export Application : public NamedElement
{
    o_language_element

    friend struct auto_dll_loader;
    friend class Phantom;
    friend class Namespace;
    friend class Package;
    friend class Module;
    friend class phantom::dynamic_initializer_handle;
    template<typename> friend class native::TIntegralType;
    template<typename> friend class native::TArithmeticType;
    template<typename> friend class native::TFundamentalType;
    friend class MemberPointerType;
    friend class ReferenceType;
    friend class DataPointerType;
    friend class Enum;

public:
    Application(void);
    ~Application(void);

    o_initialize();
    o_terminate();

    bool                            loadLibrary(const string& a_strPath, Message* a_pMessage = nullptr);
    bool                            unloadLibrary(const string& a_strPath, Message* a_pMessage = nullptr);

    void                            loadMain(const string& a_strModuleName, const string& a_strFileName, const char* a_strSourceFile, Message* a_pMessage = nullptr);
    void                            unloadMain(Message* a_pMessage = nullptr);

    Module*                         main() const;

    vector<Module*>::const_iterator beginLoadedModules() const { return m_LoadedModules.begin(); }
    vector<Module*>::const_iterator endLoadedModules() const { return m_LoadedModules.end(); }

    size_t                          getLoadedModuleCount() const { return m_LoadedModules.size(); }

    size_t                          getLoadedNativeModuleCount() const { return m_LoadedNativeModules.size(); }

    size_t                          getModuleLoadCount(Module* a_pModule) const;

    size_t                          getLibraryModuleLoadCount(const string& a_strPath, Module* a_pModule) const;

    bool                            isLibraryLoaded(const string& a_strPath) const;

    bool                            isNativeModuleLoaded(const string& a_strFileName) const;

    bool                            isNativeModuleLoaded(Module* a_pModule) const;

    map<Module*, size_t>::const_iterator beginLoadedLibraryModules(const string& a_strPath) const;
    map<Module*, size_t>::const_iterator endLoadedLibraryModules(const string& a_strPath) const;

    map<string, map<Module*, size_t>>::const_iterator beginLoadedLibraries() const { return m_LibraryModules.begin(); }
    map<string, map<Module*, size_t>>::const_iterator endLoadedLibraries() const { return m_LibraryModules.end(); }

    bool                            libraryCanBeUnloaded(const string& a_strPath, phantom::Message* a_pMessage = nullptr, vector<LanguageElement*>* a_pBlockingElements = nullptr) const;

    void                            setDataBase(serialization::DataBase* a_pDataBase);
    serialization::DataBase*        getDataBase() const { return m_pDataBase; }

    void                            beginReplaceElements( const vector<LanguageElement*>& a_OldLanguageElements);
    void                            endReplaceElements( const vector<LanguageElement*>& a_NewLanguageElements );

    void                            beginReplaceElement( LanguageElement* a_pOldLanguageElement );
    void                            endReplaceElement( LanguageElement* a_pOldLanguageElement );

    void                            addBuiltInType( Type* a_pType );
    void                            removeBuiltInType( Type* a_pType );

    Type*                           getBuiltInType(const string& a_strName) const;

    Module*                         nativeModuleFromStackContext( byte* ebp, uint stackLevel = 1, byte* eip = 0 );

    Module*                         nativeModuleFromProgramCounter( byte* pc );

    inline Language*                getDefaultLanguage() const { return m_pDefaultLanguage; }
    inline void                     setDefaultLanguage(Language* val) { m_pDefaultLanguage = val; }

    BuiltInOperator*                getBuiltInBinaryOperator(const string& a_strName) const;
    BuiltInOperator*                getBuiltInPreUnaryOperator(const string& a_strName) const;
    BuiltInOperator*                getBuiltInPostUnaryOperator(const string& a_strName) const;
    BuiltInOperator*                getBuiltInOperator(EOperator a_eOperator) const {return m_BuiltInOperators[a_eOperator]; }

    LanguageElement*                invalid(LanguageElement* a_pElement);

protected:
    void addModule(Module* a_pModule);
    void removeModule(Module* a_pModule);
    void moduleInstanciated(void* a_pModule);
    void moduleDeleted(void* a_pModule);
    void updateReferenceCounts(const string& a_strLibPath, bool a_bLoading);
    void elementRemoved(LanguageElement* a_pElement);

    void installFundamentalBuiltInOperators(bool a_bAdd);

protected:
    o_signal_data(libraryAboutToBeLoaded, const string&);
    o_signal_data(libraryLoaded, const string&);
    o_signal_data(libraryLoadFailed, const string&);
    o_signal_data(libraryAboutToBeUnloaded, const string&);
    o_signal_data(libraryUnloaded, const string&);
    o_signal_data(libraryUnloadFailed, const string&);
    o_signal_data(moduleCreated, Module*);
    o_signal_data(moduleDestroyed, Module*);
    o_signal_data(moduleLoaded, Module*, size_t, size_t);
    o_signal_data(moduleAboutToBeDestroyed, Module*);
    o_signal_data(moduleUnloaded, Module*, size_t, size_t);
    o_signal_data(elementAdded, LanguageElement*);
    o_signal_data(elementAboutToBeRemoved, LanguageElement*);
    o_signal_data(elementsAboutToBeReplaced, const vector<LanguageElement*>&);
    o_signal_data(elementsReplaced, const vector<LanguageElement*>&, const vector<LanguageElement*>&);

protected:
    vector<Module*> m_LoadedNativeModules;
    vector<Module*> m_LoadedModules;
    Module*         m_pMainModule;
    Language*       m_pDefaultLanguage;
    map<Module*, size_t> m_LoadedModuleCounts;
    map<string, map<Module*, size_t>> m_LibraryModules;
    vector<Module*> m_CurrentlyLoadingModules;
    size_t m_OperationCounter;
    serialization::DataBase* m_pDataBase;
    vector<LanguageElement*> m_ReplacementOldElements;
    BuiltInOperator*m_BuiltInOperators[e_Operator_Count];
    vector<Type*>   m_BuiltInTypes;
};

o_namespace_end(phantom, reflection)

#endif // o_ModuleLoaded_h__