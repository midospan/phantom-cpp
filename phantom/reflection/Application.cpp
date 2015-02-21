/* ******************* Includes ****************** */
#include <phantom/phantom.h>
#include "Application.h"
#include "Application.hxx"
#include "BuiltInOperator.h"
#include "phantom/Message.h"
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#if o_PLATFORM == o_PLATFORM_WINDOWS_PC
#include <windows.h>
#include <TlHelp32.h>
#endif
#include <phantom/reflection/native/TFundamentals.h>
#include "BuiltInOperators.h"
/* *********************************************** */

o_registerN((phantom, reflection), Application);

o_namespace_begin(phantom, reflection)

map<Module*, size_t> sg_EmptyLibraryLoadedModules;

string Application_normalizePathString(const string& a_strPath)
{
    boost::filesystem::path p (a_strPath.c_str());
    return p.generic_string().c_str();
}

string Application_makeWindowsPathString(const string& a_strPath)
{
    string result = a_strPath;
    for(size_t i = 0; i<result.size(); ++i)
    {
        if(result[i] == '/') result[i] = '\\';
    }
    return result;
}

Application::Application(void)
    : NamedElement("", o_always_valid|o_native)
    , m_OperationCounter(0)
    , m_pDataBase(nullptr)
    , m_pMainModule(nullptr)
    , m_pDefaultLanguage(shaman()) /// default language is shaman, yeah !! ...hum
{
    addElement(globalNamespace());
    for(int i = 0; i<e_Operator_Count; ++i)
    {
        m_BuiltInOperators[i] = new BuiltInOperator((EOperator)i);
    }
}

Application::~Application( void )
{
    for(int i = 0; i<e_Operator_Count; ++i)
    {
        delete m_BuiltInOperators[i];
    }
}

o_initialize_cpp(Application)
{
    o_connect(o_type_of(Module), kindCreated(void*), this, moduleInstanciated(void*));
    o_connect(o_type_of(Module), kindDestroyed(void*), this, moduleDeleted(void*));
}

o_terminate_cpp(Application)
{
    o_disconnect(o_type_of(Module), kindCreated(void*), this, moduleInstanciated(void*));
    o_disconnect(o_type_of(Module), kindDestroyed(void*), this, moduleDeleted(void*));
}

bool Application::loadLibrary( const string& a_strPath, phantom::Message* a_pMessage /*= nullptr*/ )
{
    string strPath = Application_normalizePathString(a_strPath);
    m_OperationCounter++;

    o_emit libraryAboutToBeLoaded(strPath);

    Module* pModule = phantom::moduleByFilePath(strPath);
    string moduleName = strPath.substr(strPath.find_last_of("/\\")+1);
    Message* pMessageLoadFailed = nullptr;

    bool result = true;
    if(LoadLibrary(strPath.c_str()))
    {
        if(a_pMessage) a_pMessage->success(moduleName.c_str(), "Module loaded : %s", moduleName.c_str());
        o_warning(m_CurrentlyLoadingModules.size(), "No module found in the loaded library");
        m_CurrentlyLoadingModules.clear();
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
        m_CurrentlyLoadingModules.clear();
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

bool Application::unloadLibrary( const string& a_strPath, phantom::Message* a_pMessage /*= nullptr*/ )
{
    string strPath = Application_normalizePathString(a_strPath);
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
    o_assert(std::find(m_LoadedNativeModules.begin(), m_LoadedNativeModules.end(), pModule) != m_LoadedNativeModules.end(), "This module was not loaded via Application");
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

void Application::moduleInstanciated( void* a_pModule )
{
    o_assert(m_OperationCounter, "DLL loader must be responsible for loading phantom modules, don't use platform specific function to load them such as LoadLibrary/FreeLibrary, use Application::loadLibrary/unloadlibrary");
    Module* pModule = phantom::as<Module*>(a_pModule);
    m_LoadedModuleCounts[pModule] = 0;
    m_LoadedModules.push_back(pModule);
    if(pModule->isNative())
    {
        m_CurrentlyLoadingModules.push_back(pModule);
        m_LoadedNativeModules.push_back(pModule);
    }
    o_connect(a_pModule, elementAdded(LanguageElement*), this, elementAdded(LanguageElement*));
    o_connect(a_pModule, elementAboutToBeRemoved(LanguageElement*), this, elementAboutToBeRemoved(LanguageElement*));
    o_emit moduleCreated(pModule);
}

void Application::moduleDeleted( void* a_pModule )
{
    o_disconnect(a_pModule, elementAdded(LanguageElement*), this, elementAdded(LanguageElement*));
    o_disconnect(a_pModule, elementAboutToBeRemoved(LanguageElement*), this, elementAboutToBeRemoved(LanguageElement*));
    o_assert(m_OperationCounter, "DLL loader must be responsible for loading phantom modules, don't use platform specific function to load them such as LoadLibrary/FreeLibrary, use Application::loadLibrary/unloadlibrary");
    Module* pModule = phantom::as<Module*>(a_pModule);
    o_emit moduleUnloaded(pModule, m_LoadedModuleCounts[pModule], 0);
    m_LoadedModuleCounts.erase(pModule);
    if(pModule->isNative())
    {
        m_LoadedNativeModules.erase(std::find(m_LoadedNativeModules.begin(), m_LoadedNativeModules.end(), pModule));// Remove dependencies reference of this module
    }
    m_LoadedModules.erase(std::find(m_LoadedModules.begin(), m_LoadedModules.end(), pModule));// Remove dependencies reference of this module
    o_emit moduleDestroyed(pModule);
}

void Application::updateReferenceCounts(const string& a_strLibPath, bool a_bLoading)
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

    string strLibPath = Application_normalizePathString(a_strLibPath);

    for(auto it = m_LoadedNativeModules.begin(); it != m_LoadedNativeModules.end(); ++it)
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
    o_assert(matchingModuleCount == m_LoadedNativeModules.size(), "A loaded module has not been found in the loaded dlls");
    o_verify(CloseHandle(snapshotHandle), "CloseHandle(snapshotHandle)");
}

size_t Application::getModuleLoadCount( Module* a_pModule ) const
{
    auto found = m_LoadedModuleCounts.find(a_pModule);
    if(found == m_LoadedModuleCounts.end()) return 0;
    return found->second;
}

map<Module*, size_t>::const_iterator Application::beginLoadedLibraryModules( const string& a_strPath ) const
{
    auto abs = boost::filesystem::absolute(a_strPath.c_str());
    for(auto it = m_LibraryModules.begin(); it != m_LibraryModules.end(); ++it)
    {
        if(boost::filesystem::equivalent(boost::filesystem::absolute(it->first.c_str()), abs))
            return it->second.begin();
    }
    return sg_EmptyLibraryLoadedModules.begin();
}

map<Module*, size_t>::const_iterator Application::endLoadedLibraryModules( const string& a_strPath ) const
{
    auto abs = boost::filesystem::absolute(a_strPath.c_str());
    for(auto it = m_LibraryModules.begin(); it != m_LibraryModules.end(); ++it)
    {
        if(boost::filesystem::equivalent(boost::filesystem::absolute(it->first.c_str()), abs))
            return it->second.end();
    }
    return sg_EmptyLibraryLoadedModules.end();
}

bool Module_derivedClassHasDifferentModule(const string& moduleName, Module* a_pModule, const phantom::vector<Module*>& a_ModulesAboutToBeUnloaded, Class* a_pClass, Message*& a_pMessageUnloadFailed, Message* a_pMessage)
{
    bool bResult = false;
    for(size_t i = 0; i<a_pClass->getDerivedClassCount();++i)
    {
        Class* pDerivedClass = a_pClass->getDerivedClass(i);
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

bool Application::libraryCanBeUnloaded( const string& a_strPath, Message* a_pMessage, vector<LanguageElement*>* a_pBlockingElements /*= nullptr*/ ) const
{
    string strPath = Application_normalizePathString(a_strPath);
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
        vector<LanguageElement*> moduleElements;
        pModule->fetchElementsCascade(moduleElements);
        for(auto it = moduleElements.begin(); it != moduleElements.end(); ++it)
        {
            Class* pClass = (*it)->asClass();
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

size_t Application::getLibraryModuleLoadCount( const string& a_strPath, Module* a_pModule ) const
{
    string strPath = Application_normalizePathString(a_strPath);
    auto foundLib = m_LibraryModules.find(strPath);
    if(foundLib == m_LibraryModules.end()) return 0;
    auto foundModule = foundLib->second.find(a_pModule);
    if(foundModule == foundLib->second.end()) return 0;
    return foundModule->second;
}

void Application::loadMain( const string& a_strModuleName, const string& a_strFileName, const char* a_strSourceFile, Message* a_pMessage )
{
    m_OperationCounter++;
    phantom::installReflection(a_strModuleName, a_strFileName, (size_t)GetModuleHandle(0), a_strSourceFile);
    m_pMainModule = m_LoadedModules.back();
    m_OperationCounter--;
}

void Application::unloadMain( Message* a_pMessage /*= nullptr*/ )
{
    m_OperationCounter++;
    phantom::uninstallReflection(m_pMainModule->getName());
    m_pMainModule = nullptr;
    m_OperationCounter--;
}

bool Application::isLibraryLoaded( const string& a_strPath ) const
{
    auto abs = boost::filesystem::absolute(a_strPath.c_str());
    for(auto it = m_LibraryModules.begin(); it != m_LibraryModules.end(); ++it)
    {
        if(boost::filesystem::equivalent(boost::filesystem::absolute(it->first.c_str()), abs))
            return true;
    }
    return false;
}

bool Application::isNativeModuleLoaded( const string& a_strFileName ) const
{
    for(auto it = m_LoadedNativeModules.begin(); it != m_LoadedNativeModules.end(); ++it)
    {
        if((*it)->getFileName() == a_strFileName) return true;
    }
    return false;
}

bool Application::isNativeModuleLoaded( Module* a_pModule ) const
{
    for(auto it = m_LoadedNativeModules.begin(); it != m_LoadedNativeModules.end(); ++it)
    {
        if((*it) == a_pModule) return true;
    }
    return false;
}

void Application::setDataBase( serialization::DataBase* a_pDataBase )
{
    if(m_pDataBase == a_pDataBase) return;
    if(m_pDataBase)
    {
        o_disconnect(this, moduleLoaded(Module*, size_t, size_t), m_pDataBase, moduleLoaded(reflection::Module*, size_t, size_t));
        o_disconnect(this, moduleUnloaded(Module*, size_t, size_t), m_pDataBase, moduleUnloaded(reflection::Module*, size_t, size_t));
    }
    m_pDataBase = a_pDataBase;
    if(m_pDataBase)
    {
        o_connect(this, moduleLoaded(Module*, size_t, size_t), m_pDataBase, moduleLoaded(reflection::Module*, size_t, size_t));
        o_connect(this, moduleUnloaded(Module*, size_t, size_t), m_pDataBase, moduleUnloaded(reflection::Module*, size_t, size_t));
    }
}

void Application::addModule( Module* a_pModule )
{
    m_LoadedModules.push_back(a_pModule);
    addElement(a_pModule);
    size_t oldLoadCount = m_LoadedModuleCounts[a_pModule];
    o_emit moduleLoaded(a_pModule, oldLoadCount, ++m_LoadedModuleCounts[a_pModule]);
}

void Application::removeModule( Module* a_pModule )
{
    if(a_pModule->isNative())
    {
        o_exception(exception::base_exception, "cannot manually add and load a native module, use library loading to do so");
    }
    removeElement(a_pModule);
}

void Application::elementRemoved(LanguageElement* a_pElement)
{
    if(a_pElement->asModule())
    {
        Module* pModule = static_cast<Module*>(a_pElement);
        if(!pModule->isNative())
        {
            size_t oldLoadCount = m_LoadedModuleCounts[pModule];
            o_assert(oldLoadCount > 0);
            size_t newLoadCount = 0;
            if(oldLoadCount == 1)
                m_LoadedModuleCounts.erase(pModule);
            else 
                newLoadCount = --m_LoadedModuleCounts[pModule];
            o_emit moduleUnloaded(pModule, oldLoadCount, newLoadCount);
        }
    }
    else if(a_pElement->asType())
    {
        m_BuiltInTypes.erase(std::find(m_BuiltInTypes.begin(), m_BuiltInTypes.end(), static_cast<Type*>(a_pElement)));
    }
    else if(a_pElement->asNamespace())
    {
        o_assert(globalNamespace() == a_pElement);
    }
}

void Application::beginReplaceElement( LanguageElement* a_pOldLanguageElement )
{
    vector<LanguageElement*> oldElements;
    oldElements.push_back(a_pOldLanguageElement);
    beginReplaceElements(oldElements);
}

void Application::beginReplaceElements( const vector<LanguageElement*>& a_OldLanguageElements )
{
    o_error(m_ReplacementOldElements.empty(), "A replacement is already in progress, call endReplaceElements to finish the current replacement");
    m_ReplacementOldElements = a_OldLanguageElements;
    o_assert(m_ReplacementOldElements.size(), "No elements passed as arguments");
    for(size_t i = 0; i<m_ReplacementOldElements.size(); ++i)
    {
        o_error(m_ReplacementOldElements[i]->getOwner(), "Old elements must have their owner before being replaced");
    }
    o_emit elementsAboutToBeReplaced(m_ReplacementOldElements);
}

void Application::endReplaceElements(const vector<LanguageElement*>& a_NewLanguageElements)
{
    o_error(NOT(m_ReplacementOldElements.empty()) AND NOT(a_NewLanguageElements.empty())
        , "A replacement is already in progress, call endReplaceElements to finish the current replacement");
    for(size_t i = 0; i<m_ReplacementOldElements.size(); ++i)
    {
        LanguageElement* pOldElement = m_ReplacementOldElements[i];
        if(classOf(a_NewLanguageElements[i]) != classOf(pOldElement))
        {
            o_exception(exception::base_exception, "Old type and new type doesn't have the same class");
        }
        pOldElement->getSource()->getOwner()->replaceElement(pOldElement, a_NewLanguageElements[i]);
        o_error(a_NewLanguageElements[i]->getOwner(), "New elements must have their owner after being replaced");
    }
    o_emit elementsReplaced(m_ReplacementOldElements, a_NewLanguageElements);
    m_ReplacementOldElements.clear();
}

void Application::endReplaceElement( LanguageElement* a_pNewLanguageElement )
{
    vector<LanguageElement*> newElements;
    newElements.push_back(a_pNewLanguageElement);
    endReplaceElements(newElements);
}

Module* Application::main() const
{
    return m_pMainModule;
}

void Application::addBuiltInType( Type* a_pType )
{
    o_assert(getBuiltInType(a_pType->getDecoratedName()) == nullptr);
    m_BuiltInTypes.push_back(a_pType);
    addElement(a_pType);
}

void Application::removeBuiltInType( Type* a_pType )
{
    removeElement(a_pType);
}

Type* Application::getBuiltInType( const string& a_strDecoratedName ) const
{
    for(auto it = m_BuiltInTypes.begin(); it != m_BuiltInTypes.end(); ++it)
    {
        if((*it)->getDecoratedName() == a_strDecoratedName) return *it;
    }
    return nullptr;
}

#define BREAK_INSTRUCTION_SIZE 1
#define CALL_INSTRUCTION_SIZE 5

Module* Application::nativeModuleFromStackContext( byte* ebp, uint stackLevel, byte* epc /*= 0*/ )
{
    o_assert(epc OR stackLevel > 0);
    while(stackLevel--)
    {
        // down the stack
        byte* up_epc = *((byte**)(ebp+sizeof(void*))) - CALL_INSTRUCTION_SIZE;
        byte* up_ebp = *((byte**)ebp);
        epc = up_epc;
        ebp = up_ebp;
    }
    return nativeModuleFromProgramCounter(epc);
}

Module* Application::nativeModuleFromProgramCounter( byte* epc )
{
    Module* pBestMatch = nullptr;
    ptrdiff_t distanceFromModuleStart = PTRDIFF_MAX;
    for(auto it = m_LoadedNativeModules.begin(); it != m_LoadedNativeModules.end(); ++it)
    {
        byte* pMemoryStart = (*it)->getMemoryStart();
        if(pMemoryStart AND (epc > pMemoryStart)) // current instruction pointer is after current module start => current module is candidate
        {
            if((epc-pMemoryStart) < distanceFromModuleStart)
            {
                // distance from memory start if less than current best module => current module become best candidate
                pBestMatch = *it;
                distanceFromModuleStart = (epc-pMemoryStart);
            }
        }
    }
    return pBestMatch;
}

auto_dll_loader::auto_dll_loader()
{
    phantom::application()->m_OperationCounter++;
}

auto_dll_loader::~auto_dll_loader()
{
    phantom::application()->m_OperationCounter--;
}

void Application::installFundamentalBuiltInOperators(bool a_bAdd)
{
    builtin_operation_delegate_selector selector;
    
    Type* pBoolType = typeOf<bool>();
    Type* pIntType = typeOf<int>();

    /// standard 13.6.2 : promoted integral and arithmetic types
    /// ------------------------
    vector<Type*> promotedArithmeticTypes;
    vector<Type*> promotedIntegralTypes;
    vector<Type*> arithmeticTypes;
    for(auto it = m_BuiltInTypes.begin(); it != m_BuiltInTypes.end(); ++it)
    {
        Type* pType = *it;
        if(pType->asArithmeticType())
        {
            arithmeticTypes.push_back(pType);
        }
        if(pType->isPromotedIntegralType())
        {
            promotedIntegralTypes.push_back(pType);
            promotedArithmeticTypes.push_back(pType);
        }
        else if(pType->asFloatingPointType())
        {
            promotedArithmeticTypes.push_back(pType);
        }
    }

    for(auto it = arithmeticTypes.begin(); it != arithmeticTypes.end(); ++it)
    {
        /// standard 13.6.3
        /// ------------------------
        /// VQ T & operator++(VQ T &);
        /// T operator++(VQ T &, int);
        Type* T = *it;
        Type* Tr = T->lvalueReferenceType();
        Type* VTr = T->volatileType()->lvalueReferenceType();
        m_BuiltInOperators[e_Operator_PreIncrement]->editOverload(a_bAdd, Tr, Tr, selector.delegate(e_Operator_PreIncrement, T));
        m_BuiltInOperators[e_Operator_PostIncrement]->editOverload(a_bAdd, Tr, Tr, pIntType, selector.delegate(e_Operator_PostIncrement, T));
        m_BuiltInOperators[e_Operator_PreIncrement]->editOverload(a_bAdd, VTr, VTr, selector.delegate(e_Operator_PreIncrement, T));
        m_BuiltInOperators[e_Operator_PostIncrement]->editOverload(a_bAdd, VTr, VTr, pIntType, selector.delegate(e_Operator_PostIncrement, T));

        if(*it != pBoolType)
        {
            /// standard 13.6.4
            /// ------------------------
            /// VQ T & operator--(VQ T &);
            /// T operator--(VQ T &, int);
            m_BuiltInOperators[e_Operator_PreDecrement]->editOverload(a_bAdd, Tr, Tr, selector.delegate(e_Operator_PreDecrement, T));
            m_BuiltInOperators[e_Operator_PostDecrement]->editOverload(a_bAdd, Tr, Tr, pIntType, selector.delegate(e_Operator_PostDecrement, T));
            m_BuiltInOperators[e_Operator_PreDecrement]->editOverload(a_bAdd, VTr, VTr, selector.delegate(e_Operator_PreDecrement, T));
            m_BuiltInOperators[e_Operator_PostDecrement]->editOverload(a_bAdd, VTr, VTr, pIntType, selector.delegate(e_Operator_PostDecrement, T));
        }

        Type* L = *it;
        Type* Lr = T->lvalueReferenceType();
        Type* VLr = T->volatileType()->lvalueReferenceType();

        for(auto it = promotedArithmeticTypes.begin(); it != promotedArithmeticTypes.end(); ++it)
        {
            Type* R = *it;
            /// standard 13.6.18
            /// ------------------------
            /// VQ L & operator=(VQ L &, R );
            /// VQ L & operator*=(VQ L &, R );
            /// VQ L & operator/=(VQ L &, R );
            /// VQ L & operator+=(VQ L &, R );
            /// VQ L & operator-=(VQ L &, R );

            m_BuiltInOperators[e_Operator_Assignment]->editOverload(a_bAdd, Lr, Lr, R, selector.delegate(e_Operator_Assignment, L, R));
            m_BuiltInOperators[e_Operator_Assignment]->editOverload(a_bAdd, VLr, VLr, R, selector.delegate(e_Operator_Assignment, L, R));
            m_BuiltInOperators[e_Operator_AssignmentMultiply]->editOverload(a_bAdd, Lr, Lr, R, selector.delegate(e_Operator_AssignmentMultiply, L, R));
            m_BuiltInOperators[e_Operator_AssignmentMultiply]->editOverload(a_bAdd, VLr, VLr, R, selector.delegate(e_Operator_AssignmentMultiply, L, R));
            m_BuiltInOperators[e_Operator_AssignmentDivide]->editOverload(a_bAdd, Lr, Lr, R, selector.delegate(e_Operator_AssignmentDivide, L, R));
            m_BuiltInOperators[e_Operator_AssignmentDivide]->editOverload(a_bAdd, VLr, VLr, R, selector.delegate(e_Operator_AssignmentDivide, L, R));
            m_BuiltInOperators[e_Operator_AssignmentAdd]->editOverload(a_bAdd, Lr, Lr, R, selector.delegate(e_Operator_AssignmentAdd, L, R));
            m_BuiltInOperators[e_Operator_AssignmentAdd]->editOverload(a_bAdd, VLr, VLr, R, selector.delegate(e_Operator_AssignmentAdd, L, R));
            m_BuiltInOperators[e_Operator_AssignmentSubtract]->editOverload(a_bAdd, Lr, Lr, R, selector.delegate(e_Operator_AssignmentSubtract, L, R));
            m_BuiltInOperators[e_Operator_AssignmentSubtract]->editOverload(a_bAdd, VLr, VLr, R, selector.delegate(e_Operator_AssignmentSubtract, L, R));

        }
    }

    for(auto it = promotedArithmeticTypes.begin(); it != promotedArithmeticTypes.end(); ++it)
    {
        Type* L = *it;

        /// standard 13.6.9
        /// ------------------------
        /// T operator+(T );
        /// T operator-(T );
        m_BuiltInOperators[e_Operator_Plus]->editOverload(a_bAdd, L, L, selector.delegate(e_Operator_Plus, L));
        m_BuiltInOperators[e_Operator_Minus]->editOverload(a_bAdd, L, L, selector.delegate(e_Operator_Minus, L));

        bool Lfloating = L->asFloatingPointType() != 0;
        for(auto it = promotedArithmeticTypes.begin(); it != promotedArithmeticTypes.end(); ++it)
        {
            Type* R = *it;

            /// standard 13.6.12 (L and R are promoted arithmetic types)
            /// ------------------------
            /// LR operator*(L , R );
            /// LR operator/(L , R );
            /// LR operator+(L , R );
            /// LR operator-(L , R );
            /// bool operator<(L , R );
            /// bool operator>(L , R );
            /// bool operator<=(L , R );
            /// bool operator>=(L , R );
            /// bool operator==(L , R );
            /// bool operator!=(L , R );

            bool Rfloating = L->asFloatingPointType() != 0;
            Type* LR = (L->getTypeId() > R->getTypeId()) ? L : R; /// unary arithmetic conversion (standard 5.x)
            m_BuiltInOperators[e_Operator_Multiply]->editOverload(a_bAdd, LR, L, R, selector.delegate(e_Operator_Multiply, L, R));
            m_BuiltInOperators[e_Operator_Divide]->editOverload(a_bAdd, LR, L, R, selector.delegate(e_Operator_Divide, L, R));
            m_BuiltInOperators[e_Operator_Add]->editOverload(a_bAdd, LR, L, R, selector.delegate(e_Operator_Add, L, R));
            m_BuiltInOperators[e_Operator_Subtract]->editOverload(a_bAdd, LR, L, R, selector.delegate(e_Operator_Subtract, L, R));
            m_BuiltInOperators[e_Operator_Less]->editOverload(a_bAdd, pBoolType, R, selector.delegate(e_Operator_Less, L, R));
            m_BuiltInOperators[e_Operator_Greater]->editOverload(a_bAdd, pBoolType, L, R, selector.delegate(e_Operator_Greater, L, R));
            m_BuiltInOperators[e_Operator_LessEqual]->editOverload(a_bAdd, pBoolType, L, R, selector.delegate(e_Operator_LessEqual, L, R));
            m_BuiltInOperators[e_Operator_GreaterEqual]->editOverload(a_bAdd, pBoolType, L, R, selector.delegate(e_Operator_GreaterEqual, L, R));
            m_BuiltInOperators[e_Operator_Equal]->editOverload(a_bAdd, pBoolType, L, R, selector.delegate(e_Operator_Equal, L, R));
            m_BuiltInOperators[e_Operator_NotEqual]->editOverload(a_bAdd, pBoolType, L, R, selector.delegate(e_Operator_NotEqual, L, R));
        }
    }

    for(auto it = promotedIntegralTypes.begin(); it != promotedIntegralTypes.end(); ++it)
    {
        Type* L = *it;

        /// standard 13.6.10
        /// ------------------------
        /// T operator~(T );
        m_BuiltInOperators[e_Operator_Complement]->editOverload(a_bAdd, L, L, selector.delegate(e_Operator_Complement, L));

        for(auto it = promotedIntegralTypes.begin(); it != promotedIntegralTypes.end(); ++it)
        {
            Type* R = *it;

            Type* Lr = L->lvalueReferenceType();
            Type* VLr = L->volatileType()->lvalueReferenceType();

            Type* LR = (L->getTypeId() > R->getTypeId()) ? L : R; /// unary arithmetic conversion (standard 5.x)

            /// standard 13.6.17
            /// ------------------------
            /// LR operator%(L , R );
            /// LR operator&(L , R );
            /// LR operator^(L , R );
            /// LR operator|(L , R );
            /// L operator<<(L , R );
            /// L operator>>(L , R );

            m_BuiltInOperators[e_Operator_Modulo]->editOverload(a_bAdd, LR, L, R, selector.delegate(e_Operator_Modulo, L, R));
            m_BuiltInOperators[e_Operator_BitAnd]->editOverload(a_bAdd, LR, L, R, selector.delegate(e_Operator_BitAnd, L, R));
            m_BuiltInOperators[e_Operator_XOr]->editOverload(a_bAdd, LR, L, R, selector.delegate(e_Operator_XOr, L, R));
            m_BuiltInOperators[e_Operator_BitOr]->editOverload(a_bAdd, LR, L, R, selector.delegate(e_Operator_BitOr, L, R));
            m_BuiltInOperators[e_Operator_ShiftLeft]->editOverload(a_bAdd, L, L, R, selector.delegate(e_Operator_ShiftLeft, L, R));
            m_BuiltInOperators[e_Operator_ShiftRight]->editOverload(a_bAdd, L, L, R, selector.delegate(e_Operator_ShiftRight, L, R));


            /// standard 13.6.22
            /// ------------------------
            /// VQ L & operator%=(VQ L &, R );
            /// VQ L & operator<<=(VQ L &, R );
            /// VQ L & operator>>=(VQ L &, R );
            /// VQ L & operator&=(VQ L &, R );
            /// VQ L & operator^=(VQ L &, R );
            /// VQ L & operator|=(VQ L &, R );
            m_BuiltInOperators[e_Operator_AssignmentModulo]->editOverload(a_bAdd, Lr, Lr, R, selector.delegate(e_Operator_AssignmentModulo, L, R));
            m_BuiltInOperators[e_Operator_AssignmentShiftLeft]->editOverload(a_bAdd, Lr, Lr, R, selector.delegate(e_Operator_AssignmentShiftLeft, L, R));
            m_BuiltInOperators[e_Operator_AssignmentShiftRight]->editOverload(a_bAdd, Lr, Lr, R, selector.delegate(e_Operator_AssignmentShiftRight, L, R));
            m_BuiltInOperators[e_Operator_AssignmentBitAnd]->editOverload(a_bAdd, Lr, Lr, R, selector.delegate(e_Operator_AssignmentBitAnd, L, R));
            m_BuiltInOperators[e_Operator_AssignmentXOr]->editOverload(a_bAdd, Lr, Lr, R, selector.delegate(e_Operator_AssignmentXOr, L, R));
            m_BuiltInOperators[e_Operator_AssignmentBitOr]->editOverload(a_bAdd, Lr, Lr, R, selector.delegate(e_Operator_AssignmentBitOr, L, R));

            m_BuiltInOperators[e_Operator_AssignmentModulo]->editOverload(a_bAdd, VLr, VLr, R, selector.delegate(e_Operator_AssignmentModulo, L, R));
            m_BuiltInOperators[e_Operator_AssignmentShiftLeft]->editOverload(a_bAdd, VLr, VLr, R, selector.delegate(e_Operator_AssignmentShiftLeft, L, R));
            m_BuiltInOperators[e_Operator_AssignmentShiftRight]->editOverload(a_bAdd, VLr, VLr, R, selector.delegate(e_Operator_AssignmentShiftRight, L, R));
            m_BuiltInOperators[e_Operator_AssignmentBitAnd]->editOverload(a_bAdd, VLr, VLr, R, selector.delegate(e_Operator_AssignmentBitAnd, L, R));
            m_BuiltInOperators[e_Operator_AssignmentXOr]->editOverload(a_bAdd, VLr, VLr, R, selector.delegate(e_Operator_AssignmentXOr, L, R));
            m_BuiltInOperators[e_Operator_AssignmentBitOr]->editOverload(a_bAdd, VLr, VLr, R, selector.delegate(e_Operator_AssignmentBitOr, L, R));
        }
    }

    /// standard 13.6.16 (for std::nullptr_t)
    /// ------------------------
    /// bool operator==(T , T );
    /// bool operator!=(T , T );
    m_BuiltInOperators[e_Operator_Equal]->editOverload(a_bAdd, pBoolType, typeOf<std::nullptr_t>(), typeOf<std::nullptr_t>(), &builtin_operation_delegate_Equal<std::nullptr_t, std::nullptr_t>::apply);
    m_BuiltInOperators[e_Operator_NotEqual]->editOverload(a_bAdd, pBoolType, typeOf<std::nullptr_t>(), typeOf<std::nullptr_t>(), &builtin_operation_delegate_NotEqual<std::nullptr_t, std::nullptr_t>::apply);

    /// standard 13.6.23
    /// ------------------------
    /// bool operator!(bool);
    /// bool operator&&(bool, bool);
    /// bool operator||(bool, bool);

    m_BuiltInOperators[e_Operator_Not]->editOverload(a_bAdd, pBoolType, pBoolType, &builtin_operation_delegate_Not<bool>::apply);
    m_BuiltInOperators[e_Operator_LogicalAnd]->editOverload(a_bAdd, pBoolType, pBoolType, pBoolType, &builtin_operation_delegate_LogicalAnd<bool ,bool>::apply);
    m_BuiltInOperators[e_Operator_LogicalOr]->editOverload(a_bAdd, pBoolType, pBoolType, pBoolType, &builtin_operation_delegate_LogicalOr<bool ,bool>::apply);
}

BuiltInOperator* Application::getBuiltInBinaryOperator( const string& a_strName ) const
{
    static map<string, EOperator> s_OperatorNames;
    if(s_OperatorNames.empty())
    {
        s_OperatorNames["+"  ] = e_Operator_Add                     ;
        s_OperatorNames["-"  ] = e_Operator_Subtract                ;
        s_OperatorNames["*"  ] = e_Operator_Multiply                ;
        s_OperatorNames["/"  ] = e_Operator_Divide                  ;
        s_OperatorNames["->*"] = e_Operator_ArrowStar               ;
        s_OperatorNames["==" ] = e_Operator_Equal                   ;
        s_OperatorNames["!=" ] = e_Operator_NotEqual                ;
        s_OperatorNames[">"  ] = e_Operator_Greater                 ;
        s_OperatorNames["<"  ] = e_Operator_Less                    ;
        s_OperatorNames[">=" ] = e_Operator_GreaterEqual            ;
        s_OperatorNames["<=" ] = e_Operator_LessEqual               ;
        s_OperatorNames["&&" ] = e_Operator_LogicalAnd              ;
        s_OperatorNames["||" ] = e_Operator_LogicalOr               ;
        s_OperatorNames["^"  ] = e_Operator_XOr                     ;
        s_OperatorNames["&"  ] = e_Operator_BitAnd                  ;
        s_OperatorNames["|"  ] = e_Operator_BitOr                   ;
        s_OperatorNames["%"  ] = e_Operator_Modulo                  ;
        s_OperatorNames["<<" ] = e_Operator_ShiftLeft               ;
        s_OperatorNames[">>" ] = e_Operator_ShiftRight              ;
        s_OperatorNames["="  ] = e_Operator_Assignment              ;
        s_OperatorNames["+=" ] = e_Operator_AssignmentAdd           ;
        s_OperatorNames["-=" ] = e_Operator_AssignmentSubtract      ;
        s_OperatorNames["*=" ] = e_Operator_AssignmentMultiply      ;
        s_OperatorNames["/=" ] = e_Operator_AssignmentDivide        ;
        s_OperatorNames["&=" ] = e_Operator_AssignmentBitAnd        ;
        s_OperatorNames["|=" ] = e_Operator_AssignmentBitOr         ;
        s_OperatorNames["%=" ] = e_Operator_AssignmentModulo        ;
        s_OperatorNames["<<="] = e_Operator_AssignmentShiftLeft     ;
        s_OperatorNames[">>="] = e_Operator_AssignmentShiftRight    ;
        s_OperatorNames["^=" ] = e_Operator_AssignmentXOr           ;
    }
    auto found = s_OperatorNames.find(a_strName);
    if(found == s_OperatorNames.end()) return nullptr;
    return m_BuiltInOperators[found->second];
}

BuiltInOperator* Application::getBuiltInPreUnaryOperator( const string& a_strName ) const
{
    static map<string, EOperator> s_OperatorNames;
    if(s_OperatorNames.empty())
    {
        s_OperatorNames["+"  ] = e_Operator_Plus        ;
        s_OperatorNames["-"  ] = e_Operator_Minus       ;
        s_OperatorNames["++" ] = e_Operator_PreIncrement;
        s_OperatorNames["--" ] = e_Operator_PreDecrement;
        s_OperatorNames["~"  ] = e_Operator_Complement  ;
        s_OperatorNames["!"  ] = e_Operator_Not         ;
        s_OperatorNames["&"  ] = e_Operator_Address     ;
        s_OperatorNames["*"  ] = e_Operator_Dereference ;
    }
    auto found = s_OperatorNames.find(a_strName);
    if(found == s_OperatorNames.end()) return nullptr;
    return m_BuiltInOperators[found->second];
}

BuiltInOperator* Application::getBuiltInPostUnaryOperator( const string& a_strName ) const
{
    static map<string, EOperator> s_OperatorNames;
    if(s_OperatorNames.empty())
    {
        s_OperatorNames["++" ] = e_Operator_PostIncrement;
        s_OperatorNames["--" ] = e_Operator_PostDecrement;
        s_OperatorNames["->" ] = e_Operator_Arrow;
    }
    auto found = s_OperatorNames.find(a_strName);
    if(found == s_OperatorNames.end()) return nullptr;
    return m_BuiltInOperators[found->second];
}

LanguageElement* Application::invalid( LanguageElement* a_pElement )
{
    addElement(a_pElement);
    return a_pElement;
}

o_namespace_end(phantom, reflection)
