/* TODO LICENCE HERE */

/* ******************* Includes ****************** */
#include "phantom/phantom.h"


#if o__int__reflection_template_use_level != 3
#   include "def_phantom_deferred_reflection.inl"
#endif

#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>
#include <stdarg.h>
#if o_OPERATING_SYSTEM == o_OPERATING_SYSTEM_WINDOWS
#include <windows.h>
#endif
/* *********************************************** */

#if o__int__reflection_template_use_level != 3
#   include "phantom/phantom.hxx"
#endif

#include "phantom/reflection/Package.h"
#include "phantom/reflection/Package.hxx"
#include "phantom/reflection/Source.h"
#include "phantom/reflection/Source.hxx"
#include "phantom/reflection/Module.h"
#include "phantom/reflection/Module.hxx"
#include "phantom/reflection/Application.h"
#include "phantom/reflection/CPlusPlus.h"
#include "phantom/reflection/Shaman.h"
#include "phantom/reflection/Interpreter.h"
#include "phantom/Message.h"
#if o__bool__use_custom_stl_partioned_allocator OR o__bool__use_custom_stl_contiguous_allocator
#include <boost/property_tree_custom/info_parser.hpp>
#else
#include <boost/property_tree/info_parser.hpp>
#endif

o_registerN((phantom, memory), malloc_free_allocator_for_boost)
o_registerNT((phantom, memory), (typename, typename), (T, UserAllocator), malloc_free_allocator)

o_declareN(class, (phantom), reflection::Module)
o_declareN(class, (phantom, reflection), Source)
o_declareN(class, (phantom, reflection), Signature)

o_functionN((phantom), phantom::reflection::Namespace*, globalNamespace, ());
o_functionN((phantom), phantom::reflection::Type*, typeByName, (const phantom::string&, phantom::reflection::LanguageElement*, phantom::modifiers_t));
o_functionN((phantom), phantom::reflection::Expression*, expressionByName, (const phantom::string&, phantom::reflection::LanguageElement*, phantom::modifiers_t));

o_typedefN((phantom), modifiers_t);

o_namespace_begin(phantom)

o_forceinline bool dynamic_initializer_handle::dynamic_initializer_module_installation_func::operator<( const dynamic_initializer_module_installation_func& other ) const
{
    reflection::Class* pThisClass = type->asClass();
    reflection::Class* pOtherClass = other.type->asClass();

    if(pThisClass)
    {
        if(pOtherClass)
        {
            if(pThisClass->isKindOf(pOtherClass)) return false;
            if(pOtherClass->isKindOf(pThisClass)) return true;
            
            size_t i = 0;
            size_t thisLevel = 0;
            size_t otherLevel = 0;
            size_t baseCount = std::max(pThisClass->getBaseClassCount(), pOtherClass->getBaseClassCount());
            while(i<baseCount AND (thisLevel = pThisClass->getInheritanceLevel(i)) == (otherLevel = pOtherClass->getInheritanceLevel(i)))
                ++i;
            return thisLevel == otherLevel 
                ? pThisClass < pOtherClass 
                : thisLevel < otherLevel;
        }
        else 
        {
            return false;
        }
    }
    else if(pOtherClass)
    {
        return true;
    }
    return type < other.type;
}

typedef boost::pool<phantom::memory::malloc_free_allocator_for_boost> dynamic_pool_type ;
typedef phantom::map<size_t, dynamic_pool_type*>                        dynamic_pool_type_map;

typedef phantom::unordered_map<void const*, phantom::list<rtti_data> >		rtti_data_map;
typedef phantom::unordered_map<string, size_t>						element_map;
typedef phantom::vector<phantom::reflection::LanguageElement*>		element_container;
typedef phantom::vector<string>										meta_data_container;


static enum
{
    eState_NotInstalled,
    eState_DynamicInitializerDone_StartingInitialization,
    eState_Reflection_InheritanceSetup,
    eState_Reflection_ContentSetup,
    eState_Reflection_StateChartSetup,
    eState_Reflection_DeferredSetup,
    eState_Installed,
    eState_Uninstalling,
    eState_Uninstalled
}                                                       g_eState;

static phantom::Phantom*                                g_instance;
static uint                                             g_uiSetupStep;
static phantom::reflection::Type*                       g_type_of_string;
static std::stack<reflection::NamedElement*>*           g_pScopes;
static std::stack<reflection::AnonymousSection*>*       g_pAnonymousSections;
static std::stack<reflection::MemberAnonymousSection*>* g_pMemberAnonymousSections;
static std::stack<modifiers_t>*                         g_pModifiers;
static phantom::vector<reflection::LanguageElement*>*   g_elements;
static phantom::vector<phantom::reflection::Module*>*               g_auto_loaded_modules;
static phantom::message_report_func                     g_assert_func;
static phantom::message_report_func                     g_warning_func;
static phantom::message_report_func                     g_error_func;
static phantom::log_func                                g_log_func;
static phantom::map<string, Message*>                   g_Messages;
static phantom::reflection::Namespace*                  g_pGlobalNamespace;
static map<string, reflection::Package*>*               g_pPackages;
static phantom::reflection::CPlusPlus*                  g_cplusplus;
static phantom::reflection::Shaman*                     g_shaman;
static phantom::reflection::Interpreter*                g_interpreter;
static void*                                            g_typeOf_cycling_address_workaround_ptr;
static phantom::rtti_data_map*                          g_rtti_data_map;
static phantom::reflection::Module*		                g_module;
static phantom::reflection::Application*		        g_application;
static phantom::map<phantom::string, phantom::reflection::Module*>  g_modules;
static phantom::dynamic_pool_type_map                   g_DynamicPoolAllocators;
static phantom::vector<phantom::reflection::Constant*>  g_Constants;
static phantom::vector<phantom::string>*                g_meta_data_names;
static phantom::map<string, reflection::Source*>    g_source_files;



struct PIMPL
{
    static bool internalAreConnected( const rtti_data& a_Sender, reflection::Signal* a_pSignal, const rtti_data& a_Receiver, reflection::MemberFunction* a_pMemberFunction )
    {
        connection::slot::list* pSlotList = a_pSignal->getSlotList(a_Sender.cast(static_cast<reflection::Class*>(a_pSignal->getOwner())));
        connection::slot* pSlot = pSlotList->m_head;
        while(pSlot)
        {
            if(pSlot->m_subroutine == a_pMemberFunction
                AND pSlot->m_receiver == a_Receiver.cast(static_cast<reflection::Class*>(a_pMemberFunction->getOwner())))
            {
                return true;
            }
            pSlot = pSlot->m_next;
        }
        return false;
    }

    static connection::slot const* internalConnect( const rtti_data& a_Sender, reflection::Signal* a_pSignal, const rtti_data& a_Receiver, reflection::MemberFunction* a_pMemberFunction )
    {
        connection::slot::list* pSlotList = a_pSignal->getSlotList(a_Sender.cast(static_cast<reflection::Class*>(a_pSignal->getOwner())));
        connection::slot* pFirstSlot = pSlotList->m_head;
        connection::slot* pLastSlot = pSlotList->m_queue;

        // Ask a new slot to the allocator
        connection::slot* pSlot = a_Receiver.connection_slot_allocator->take();

        // Give the slot list pointer to the slot so that it will be able to detach itself on deconnection/destruction
        pSlot->m_list_pointer = pSlotList;

        // The best place to affect to the slot list its signal is here (we don't want to store it in each node,
        // neither want to add an extra install process in the class to do so. As the signal is only used for emission information saving
        // its only necessary on emission, which implies a connection, which implies this function where we are would have beend called.
        o_assert(pSlotList->m_signal == nullptr OR pSlotList->m_signal == a_pSignal);
        pSlotList->m_signal = a_pSignal;
        pSlot->m_subroutine = a_pMemberFunction;
        pSlot->m_receiver = a_Receiver.cast(static_cast<reflection::Class*>(a_pMemberFunction->getOwner()));
#ifdef _DEBUG
        {
            while(pFirstSlot)
            {
                o_assert(!pFirstSlot->equals(pSlot));
                pFirstSlot = pFirstSlot->next();
            }
            pFirstSlot = pSlotList->head();
        }
#endif // _DEBUG
        if(pSlotList->m_head == NULL)
        {
            pSlotList->m_head = pSlot;
        }
        else
        {
            pLastSlot->m_next = pSlot;
        }
        pSlot->m_prev = pLastSlot;
        pSlotList->m_queue = pSlot;
        return pSlot;
    }

    static connection::slot const* internalDisconnect( const rtti_data& a_Sender, reflection::Signal* a_pSignal, const rtti_data& a_Receiver, reflection::MemberFunction* a_pMemberFunction )
    {
        connection::slot::list* pSlotList = a_pSignal->getSlotList(a_Sender.cast(static_cast<reflection::Class*>(a_pSignal->getOwner())));
        connection::slot* pSlot = pSlotList->m_head;
        while(pSlot)
        {
            if(pSlot->m_subroutine == a_pMemberFunction
                AND pSlot->m_receiver == a_Receiver.cast(static_cast<reflection::Class*>(a_pMemberFunction->getOwner())))
            {
                // Found -> Release the connection

                a_Receiver.connection_slot_allocator->release(pSlot);
                return pSlot;
            }
            pSlot = pSlot->m_next;
        }
        o_assert(false, "cannot find the connection");
        return nullptr;
    }
};

void    dynamic_delete_function_helper::operator>>(void* instance)
{
    if(!instance)
    {
        o_warning(false, "dynamic delete applied to null pointer");
        return;
    }
    const phantom::rtti_data& oi = phantom::rttiDataOf(instance, (size_t)0);
    o_assert_not(oi.isNull());
/*#if o__bool__enable_allocation_statistics
    o_warning(false, "dynamic deletion not yet supported by allocation statistics");
#endif*/
    oi.deleteNow(o_memory_stat_insert_parameters_use);
}

dynamic_initializer_handle::dynamic_initializer_handle()
    : m_bActive(false)
    , m_bAutoRegistrationLocked(false)
    , m_iCurrentInstallationStep(-1)
    , m_file(0)
{
    g_instance = nullptr;

    g_assert_func = default_assert;
    g_warning_func = default_warning;
    g_error_func = default_error;
    g_log_func = default_log;

    g_type_of_string = nullptr;
    g_module = nullptr;
    g_pPackages = nullptr;

    g_pScopes = new std::stack<reflection::NamedElement*>;
    g_pAnonymousSections = new std::stack<reflection::AnonymousSection*>;
    g_pAnonymousSections->push(nullptr);
    g_pMemberAnonymousSections = new std::stack<reflection::MemberAnonymousSection*>;
    g_pMemberAnonymousSections->push(nullptr);
    g_pModifiers = new std::stack<modifiers_t>;
    g_pModifiers->push(0);
    memory::Statistics::m_Allocations = new std::map<void*, memory::Statistics::allocation_info>;
    memory::Statistics::m_AllocationCount = 0 ;
    memory::Statistics::m_TotalAllocationCount = 0 ;
    memory::Statistics::m_AllocatedByteCount = 0 ;
    memory::Statistics::m_TotalAllocatedByteCount = 0 ;
    memory::Statistics::m_Locked = false;

    g_elements = o_allocate(vector<reflection::LanguageElement*>);
    new (g_elements) vector<reflection::LanguageElement*>;

    g_pGlobalNamespace = o_static_new_alloc_and_construct_part(reflection::Namespace)(o_CS(o_root_namespace_name));

    g_application = o_allocate(reflection::Application);
    new (g_application) reflection::Application;

    g_auto_loaded_modules = new vector<reflection::Module*>;

    g_rtti_data_map = o_allocate(rtti_data_map);
    new (g_rtti_data_map) rtti_data_map;

    g_meta_data_names = o_allocate(vector<string>);
    new (g_meta_data_names) vector<string>;

    connection::slot_pool::m_allocation_controller_map= o_allocate(connection::slot_pool::allocation_controller_map);
    new (connection::slot_pool::m_allocation_controller_map) connection::slot_pool::allocation_controller_map;

    g_eState = eState_NotInstalled;
    g_typeOf_cycling_address_workaround_ptr = &g_typeOf_cycling_address_workaround_ptr;

    g_cplusplus = o_static_new_alloc_and_construct_part(reflection::CPlusPlus);
    g_shaman = o_static_new_alloc_and_construct_part(reflection::Shaman);

    g_application->setDefaultLanguage(g_cplusplus);
    //o_static_new_install_and_initialize_part(g_cplusplus);

    g_interpreter = o_static_new_alloc_and_construct_part(reflection::Interpreter);

    g_pScopes->push(g_pGlobalNamespace);
    reflection::Namespace* phantom_namespace = o_static_new_alloc_and_construct_part(reflection::Namespace)("phantom");
    g_pGlobalNamespace->addNamespace(phantom_namespace);
    reflection::Namespace* reflection_namespace = o_static_new_alloc_and_construct_part(reflection::Namespace)("reflection");
    phantom_namespace->addNamespace(reflection_namespace);

    // Reserve space for registration steps infos
    size_t i = 0;
    for(;i<32;++i)
    {
        m_DeferredSetupInfos.push_back(dynamic_initializer_module_installation_func_vector());
    }

    reflection::initializeSystem();

    o_static_new_install_and_initialize_part(g_pGlobalNamespace);
    o_static_new_install_and_initialize_part(phantom_namespace);
    o_static_new_install_and_initialize_part(reflection_namespace);

    g_application->installFundamentalBuiltInOperators(true);
}

dynamic_initializer_handle::~dynamic_initializer_handle()
{
    g_application->installFundamentalBuiltInOperators(false);
    delete g_pAnonymousSections;
    delete g_pMemberAnonymousSections;
    delete g_pScopes;
    delete g_pModifiers;
    delete g_auto_loaded_modules;
    g_application->~Application();
    o_deallocate(g_application, reflection::Application) ;
    o_delete(reflection::CPlusPlus) g_cplusplus;
    o_delete(reflection::Shaman) g_shaman;

    typedef vector<string> vector_string;
#ifdef WIN32
    g_meta_data_names->~vector_string();
#endif //WIN32
    o_deallocate(g_meta_data_names, vector<string>);

    connection::slot_pool::m_allocation_controller_map= o_allocate(connection::slot_pool::allocation_controller_map);
    new (connection::slot_pool::m_allocation_controller_map) connection::slot_pool::allocation_controller_map;
}

phantom::reflection::Type* typeByName( const string& a_strName, phantom::reflection::LanguageElement* a_pRootScope, modifiers_t a_Modifiers )
{
    const string & rootScopeName = a_pRootScope->getQualifiedDecoratedName();
    phantom::reflection::Type* pType = ((a_Modifiers & o_native) == o_native) ? dynamic_initializer()->registeredTypeByName(rootScopeName.empty() ? a_strName : rootScopeName+"::"+a_strName) : nullptr;
    if(pType) return pType;
    reflection::LanguageElement* pElement = elementByName(a_strName, a_pRootScope, a_Modifiers);
    return pElement ? pElement->asType() : nullptr;
}

phantom::reflection::Type* typeByNameCascade( const string& a_strName, phantom::reflection::LanguageElement* a_pScope, modifiers_t a_Modifiers )
{
    reflection::LanguageElement* pElement = elementByNameCascade(a_strName, static_cast<phantom::reflection::Namespace*>(a_pScope), a_Modifiers);
    return pElement ? pElement->asType() : nullptr;
}

phantom::reflection::Expression* expressionByName( const string& a_strName, phantom::reflection::LanguageElement* a_pScope, modifiers_t a_Modifiers )
{
    return application()->getDefaultLanguage()->expressionByName(a_strName, a_pScope, a_Modifiers);
}

phantom::reflection::LanguageElement* elementByName( const string& a_strName, phantom::reflection::LanguageElement* a_pScope, modifiers_t a_Modifiers )
{
    return application()->getDefaultLanguage()->elementByName(a_strName, a_pScope, a_Modifiers);
}

phantom::reflection::Function* functionByName( const string& a_strName, phantom::reflection::Namespace* a_pScope, modifiers_t a_Modifiers )
{
    reflection::LanguageElement* pElement = application()->getDefaultLanguage()->elementByName(a_strName, a_pScope, a_Modifiers);
    return pElement ? pElement->asFunction() : nullptr;
}

void elementsByClass(reflection::Class* a_pClass, vector<reflection::LanguageElement*>& out, phantom::reflection::LanguageElement* a_pScope )
{
    if(a_pClass == nullptr OR classOf(a_pScope)->isKindOf(a_pClass))
    {
        out.push_back(a_pScope);
    }
    a_pScope->getElementsCascade(out, a_pClass);
}

phantom::reflection::LanguageElement* elementByNameCascade( const string& a_strName, phantom::reflection::Namespace* a_pNamespace, modifiers_t a_Modifiers )
{
	phantom::reflection::LanguageElement* pElement = elementByName(a_strName, reinterpret_cast<phantom::reflection::LanguageElement*>(a_pNamespace), a_Modifiers);
	if(pElement != NULL)
	{
		return pElement;
	}

	uint uiNamespaceCount = a_pNamespace->getNamespaceCount();
	for (uint i = 0; i < uiNamespaceCount; i++)
	{
		pElement = elementByNameCascade(a_strName, a_pNamespace->getNamespace(i), a_Modifiers);
		if (pElement != NULL)
		{
			return pElement;
		}
	}

	return NULL;
}

phantom::reflection::Type*                    typeByGuid(uint guid)
{
    o_assert_no_implementation();
    return nullptr;
    //return globalNamespace()->getTypeByGuidCascade(guid);
}

phantom::reflection::LanguageElement*         elementByGuid(uint guid)
{
    o_assert(false, "not implemented");
    return NULL;
}

void dynamic_initializer_handle::registerType( const string& a_strQualifiedDecoratedName, phantom::reflection::Type* a_pType )
{
    o_assert(registeredTypeByName(a_strQualifiedDecoratedName) == nullptr, "type already registered, shouldn't happen, test is in type_of to avoid that");
    m_RegisteredTypes[a_strQualifiedDecoratedName] = a_pType;
    globalNamespace()->addType(a_pType);
}

void dynamic_initializer_handle::registerType( const string& a_strQualifiedDecoratedName, const string& a_strScope, phantom::reflection::Type* a_pType )
{
    bool isTemplateInstance = a_pType->testModifiers(o_template);
    o_assert(registeredTypeByName(a_strQualifiedDecoratedName) == nullptr, "type already registered in same module, shouldn't happen, test is in type_of to avoid that");
    m_RegisteredTypes[a_strQualifiedDecoratedName] = a_pType;
    if(!isTemplateInstance)
    {
        phantom::reflection::LanguageElement* pNamingScope = a_strScope.empty() ? globalNamespace() : elementByName(a_strScope);
        if(pNamingScope == nullptr)
        {
            o_exception(exception::reflection_runtime_exception, "scope has not been registered => check your type's nesting class")
        }
        o_assert(pNamingScope->asScope());

   
        /// Only add type if it's not a template instance
        pNamingScope->asScope()->addType(a_pType);
    }
    else 
    {
        int i=0;
        ++i;
    }
//     else 
//     {
//         pNamingScope->asScope()->templateInstance()
//     }
}

phantom::reflection::Namespace* dynamic_initializer_handle::parseNamespace( const string& a_strNamespace ) const
{
    return globalNamespace()->findOrCreateNamespaceCascade(a_strNamespace);
}

void dynamic_initializer_handle::registerTemplate( reflection::Template* a_pTemplate, const char* a_strFile )
{
    m_DeferredTemplates.push_back(std::pair<reflection::Template*, const char*>(a_pTemplate, a_strFile));
}

void dynamic_initializer_handle::registerNamespace( reflection::Namespace* a_pNamespace, const char* a_strFile )
{
    m_DeferredNamespaces.push_back(std::pair<reflection::Namespace*, const char*>(a_pNamespace, a_strFile));
}

void dynamic_initializer_handle::registerModule( phantom::reflection::Type* a_pType, module_installation_func setupFunc, uint a_uiSetupStepMask )
{
    o_assert(isActive());

    if(setupFunc == NULL)
        return;

    int i = 0;
    for(;i<32;++i)
    {
        if(o_mask_test(a_uiSetupStepMask, (0x1<<i)))
        {
            bool alreadyRegistered = false;
            for(auto it = m_DeferredSetupInfos[i].begin(); it != m_DeferredSetupInfos[i].end(); ++it)
            {
                if(it->setupFunc == setupFunc || it->type == a_pType)
                {
                    alreadyRegistered = true;
                    break;
                }
            }
            if(NOT(alreadyRegistered))
            {
                if((isAutoRegistrationLocked() || (application()->getLoadedModuleCount() == 0)) && m_iCurrentInstallationStep < i )
                {
                    m_DeferredSetupInfos[i].push_back(dynamic_initializer_module_installation_func(a_pType, setupFunc, m_file));
                }
                else
                {
                    dynamic_initializer_module_installation_func(a_pType, setupFunc, m_file).exec(i);
                }
            }
        }
    }
}

phantom::reflection::Namespace*            namespaceByName( const string& a_strNamespaceName, reflection::Namespace* a_pScopeNamespace )
{
    reflection::LanguageElement* pElement = elementByName(a_strNamespaceName, a_pScopeNamespace);
    reflection::Namespace* pNamespace = pElement ? pElement->asNamespace() : nullptr;
    if(pNamespace == nullptr)
    {
        pNamespace = a_pScopeNamespace->findOrCreateNamespaceCascade(a_strNamespaceName);
    }
    return pNamespace;
}

phantom::reflection::Namespace*            namespaceByList( list<string>* a_pNamespaceNameAsStringList )
{
    o_warning(false, "deprecated function namespaceByList used");
    return globalNamespace()->findOrCreateNamespaceCascade(a_pNamespaceNameAsStringList);
}


void dynamic_initializer_handle::installReflection(const string& a_strQualifiedName, const string& a_strDynamicLibraryFileName, size_t a_PlatformHandle, const char* a_strDeclarationFile)
{
    o_assert(phantom::moduleByName(a_strQualifiedName) == nullptr, "module with same qualified name already registered");

    /// (1) split module qualified name (ex : 'phantom.reflection.jit' gives 'phantom', 'reflection' and 'jit')
    vector<string> packageWords;
    boost::split( packageWords, a_strQualifiedName, boost::is_any_of("."), boost::token_compress_on ); // SplitVec == { "hello abc","ABC","aBc goodbye" }
    packageWords.erase( std::remove_if( packageWords.begin(), packageWords.end(), 
        boost::bind( &string::empty, _1 ) ), packageWords.end() );
    
    /// (2) split module declaration file path (ex : 'd:/phantom/phantom/phantom.h' gives 'd:', 'phantom', 'phantom', 'phantom.h'
    vector<string> pathWords;
    boost::split( pathWords, a_strDeclarationFile, boost::is_any_of("/\\"), boost::token_compress_on ); // SplitVec == { "hello abc","ABC","aBc goodbye" }
    pathWords.erase( std::remove_if( pathWords.begin(), pathWords.end(), 
        boost::bind( &string::empty, _1 ) ), pathWords.end() );
    pathWords.pop_back(); // remove file name

    /// (3) Compare the two split word list starting from the end to ensure path contains qualified name and then deduce the module source path
    /// ex1 : d:/phantom/phantom/phantom.cpp holds o_module("phantom") and is in a directory 'phantom' => OK => source path = d:/phantom
    /// ex2 : d:/phantom/phantom/reflection/jit/jit.cpp holds o_module("phantom.reflection.jit") and is in a directory 'phantom/reflection/jit' => OK => source path = d:/phantom
    // 
    o_error(pathWords.size(), "module declaration cpp file cannot be at HD root directory");

    size_t packageCount = packageWords.size();
    size_t pathCount = pathWords.size();

    string pathName;
    for(size_t i = 0; i<pathCount; ++i)
    {
        if(!i)
            pathName+='/';
        pathName+=pathWords[i];
    }

    o_error(pathCount>=packageCount, "module qualified name %s does not match module root package path name %s extracted from o_module() declaration file %s", a_strQualifiedName.c_str(), pathName.c_str(), a_strDeclarationFile);
    
    while(packageCount--)
    {
        o_error(packageWords[packageCount] == pathWords[--pathCount], "module qualified name %s does not match module root package path name %s extracted from o_module() declaration file %s", a_strQualifiedName.c_str(), pathName.c_str(), a_strDeclarationFile);
    }

    pathWords.resize(pathWords.size() - packageWords.size());
    string sourcePath;
    for(size_t i = 0; i<pathWords.size(); ++i)
    {
        if(i OR pathWords[i].find_first_of(":") == string::npos) // on windows c:, d:, must not have a starting '/', but on unix system we must
            sourcePath+='/';
        sourcePath+=pathWords[i];
    }
    
    boost::filesystem::path p (a_strDynamicLibraryFileName.c_str());
    reflection::Module* pModule = new (phantom::allocator<reflection::Module>::allocate(o_memory_stat_insert_arguments)) reflection::Module(a_strQualifiedName, sourcePath, p.generic_string().c_str(), a_PlatformHandle);
    typeOf<reflection::Module>()->install(pModule, 0);
    pModule->PHANTOM_CODEGEN_initialize(); /// use manual initialization because module is instanciated before its meta type is complete
    o_assert(!rttiDataOf(pModule, typeOf<reflection::Module>()).isNull());
    g_modules[a_strQualifiedName] = pModule;
    phantom::pushModule(pModule);
    for(auto it = m_DeferredNamespaces.begin(); it != m_DeferredNamespaces.end(); ++it)
    {
        package(pModule, it->first->asPath('.')); // create packages
        nativeSource(it->second)->addReferencedElement(it->first); // add reference to the namespace in source
    }
    m_DeferredNamespaces.clear();
    for(auto it = m_DeferredTemplates.begin(); it != m_DeferredTemplates.end(); ++it)
    {
        o_assert(it->second);
        nativeSource(pModule, it->second)->addTemplate(it->first);
    }
    m_DeferredTemplates.clear();
    for(auto it = m_DeferredElements.begin(); it != m_DeferredElements.end(); ++it)
    {
        (*it)->registerElement();
    }
    m_DeferredElements.clear();
    o_assert(m_iCurrentInstallationStep == -1);
    m_iCurrentInstallationStep = 0;
    for(;m_iCurrentInstallationStep<32;++m_iCurrentInstallationStep)
    {
        dynamic_initializer_module_installation_func_vector& infos = m_DeferredSetupInfos[m_iCurrentInstallationStep];
        std::sort(infos.begin(), infos.end());
        size_t j = 0;
        for(;j<infos.size(); ++j)
        {
            infos[j].exec(m_iCurrentInstallationStep);
        }
        infos.clear();
    }

    for(auto it = pModule->beginPackages(); it != pModule->endPackages(); ++it)
    {
        reflection::Package* pPackage = *it;
        o_static_new_install_and_initialize_part(pPackage);
        for(auto it = pPackage->beginSources(); it != pPackage->endSources(); ++it)
        {
            reflection::Source* pSource = *it;
            o_static_new_install_and_initialize_part(pSource);
        }
    }

    if(a_strQualifiedName.empty())
    {
        g_eState = eState_Installed;
    }
    if(g_instance == nullptr) // Phantom not initialized yet by user
    {
        g_auto_loaded_modules->push_back(pModule); // reflection::Module needs auto loading
    }
//     boost::filesystem::path p(pModule->getFileName().c_str());
//     string metaDataFile(string(p.parent_path().generic_string().c_str())+"/"+p.stem().generic_string().c_str()+".cfg");
//     if(boost::filesystem::exists(metaDataFile.c_str()))
//     {
//         loadMetaData(metaDataFile, pModule);
//     }
//     
// o_debug_only(pModule->dumpElementListCascade(std::cout));
    phantom::popModule();
    m_RegisteredTypes.clear();
    pModule->checkCompleteness();
    m_iCurrentInstallationStep = -1;
}

void dynamic_initializer_handle::uninstallReflection(const string& a_strName)
{
    if(a_strName.empty())
    {
        g_eState = eState_Uninstalled;
    }
    o_assert(a_strName != "" OR g_modules.size() == 1);
    auto found = g_modules.find(a_strName);
    o_assert(found != g_modules.end());
    o_emit application()->moduleAboutToBeDestroyed(found->second);
    o_delete(reflection::Module) found->second;
    g_modules.erase(found);
}

phantom::reflection::Class* classByName( const string& a_strQualifiedName, phantom::reflection::LanguageElement* a_pRootScope, modifiers_t a_Modifiers  )
{
    reflection::LanguageElement* pElement = phantom::elementByName(a_strQualifiedName, a_pRootScope, a_Modifiers);
    return pElement ? pElement->asClass() : nullptr;
}

phantom::reflection::PrimitiveType* primitiveTypeByName( const string& a_strName )
{
    reflection::LanguageElement* pElement = phantom::elementByName(a_strName, globalNamespace());
    if(pElement) return pElement->asPrimitiveType();
    return nullptr;
}

void default_assert( const char* expression, const char* file, uint line, const char* format, va_list args )
{
    string shortenFile = file;
    std::size_t pos = shortenFile.find_last_of('/');
    if(pos == std::string::npos)
    {
        pos = shortenFile.find_last_of('\\');
        if(pos != std::string::npos)
        {
            shortenFile = shortenFile.substr(pos+1);
        }
    }
    char message[512];
    message[511] = '\0';
    int r = vsnprintf(message, 511, format, args);

    std::cout<<console::push
        <<console::fg_red<<"ASSERT("<<shortenFile<<"|"<<line<<")"
        <<console::fg_red<<"["
        <<console::fg_red<< message
        <<console::fg_white<<" is false" <<std::endl
        <<'\t'<<message<<std::endl
        <<console::fg_red<<"]"<<console::pop<<std::endl;

    o_debug_execution_break();
    exit(1);
}

void default_warning( const char* expression, const char* file, uint line, const char* format, va_list args )
{
    string shortenFile = file;
    std::size_t pos = shortenFile.find_last_of('/');
    if(pos == std::string::npos)
    {
        pos = shortenFile.find_last_of('\\');
        if(pos != std::string::npos)
        {
            shortenFile = shortenFile.substr(pos+1);
        }
    }
    char message[512];
    message[511] = '\0';
    int r = vsnprintf(message, 511, format, args);

    std::cout<<console::push
        <<console::fg_yellow<<"WARNING("<<shortenFile<<"|"<<line<<")"<<std::endl
        <<console::fg_yellow<<"["<<std::endl
        <<'\t'<<console::fg_blue<< expression
        <<console::fg_white<<" is false" <<std::endl
        <<'\t'<<message<<std::endl
        <<console::fg_yellow<<"]"<<console::pop<<std::endl;

}

void default_error( const char* expression, const char* file, uint line, const char* format, va_list args )
{
    string shortenFile = file;
    std::size_t pos = shortenFile.find_last_of('/');
    if(pos == std::string::npos)
    {
        pos = shortenFile.find_last_of('\\');
        if(pos != std::string::npos)
        {
            shortenFile = shortenFile.substr(pos+1);
        }
    }
    char message[512];
    message[511] = '\0';
    int r = vsnprintf(message, 511, format, args);

    std::cout<<console::push
        <<console::fg_red<<"ERROR("<<shortenFile<<"|"<<line<<")"<<std::endl
        <<console::fg_red<<"["<<std::endl
        <<'\t'<<console::fg_blue<< expression
        <<console::fg_white<<" is false" <<std::endl
        <<'\t'<<message<<std::endl
        <<console::fg_red<<"]"<<console::pop<<std::endl;
    assert(false);
    exit(1);
}

void default_log(int level, const char* file, uint line, const char* format, va_list args )
{
    string shortenFile = file;
    std::size_t pos = shortenFile.find_last_of('/');
    if(pos == std::string::npos)
    {
        pos = shortenFile.find_last_of('\\');
        if(pos != std::string::npos)
        {
            shortenFile = shortenFile.substr(pos+1);
        }
    }

    std::cout<<console::push
        <<console::fg_green<<"LOG("<<console::fg_white<<shortenFile<<console::fg_green<<"|"<<console::fg_white<<line<<console::fg_green<<") "<<console::fg_gray;

    char buffer[512];
    buffer[511] = '\0';
    int r = vsnprintf(buffer, 511, format, args);
    std::cout<<buffer<<console::pop<<std::endl;
}

Message* topMessage(const string& a_strCategory)
{
    auto found = g_Messages.find(a_strCategory);
    if(found == g_Messages.end())
    {
        g_Messages[a_strCategory] = o_new(Message);
    }
    return g_Messages[a_strCategory];
}

void clearMessages(const string& a_strCategory)
{
    auto found = g_Messages.find(a_strCategory);
    if(found != g_Messages.end())
    {
        o_delete(Message) g_Messages[a_strCategory]->getRootMessage();
        g_Messages.erase(found);
    }
}

Message* _message(EMessageType a_eType, const phantom::variant& a_Data, char* a_Format, va_list args )
{
    Message* pMessage = o_new(Message)(a_eType);
    pMessage->setData(a_Data);
    size_t size = strlen(a_Format)+512;
    char* buffer = (char*)o_malloc(size);
    buffer[size-1] = '\0';
    int r = vsnprintf(buffer, size, a_Format, args);
    pMessage->setText(buffer);
    o_free(buffer);
    return pMessage;
}

void message(const string& a_strCategory, EMessageType a_eType, const phantom::variant& a_Data, char* a_Format, va_list args )
{
    topMessage(a_strCategory)->addChild(_message(a_eType, a_Data, a_Format, args ));
}

void message(const string& a_strCategory, EMessageType a_eType, const phantom::variant& a_Data, char* a_Format, ... )
{
    va_list args;
    va_start(args, a_Format);
    message(a_strCategory, a_eType, a_Data, a_Format, args );
    va_end(args);
}

void pushMessage(const string& a_strCategory, EMessageType a_eType, const phantom::variant& a_Data, char* a_Format, va_list args)
{
    Message* pTopMessage = topMessage(a_strCategory);
    Message* pNewTopMessage = _message(a_eType, a_Data, a_Format, args );
    pTopMessage->addChild(pNewTopMessage);
    pTopMessage = pNewTopMessage;
}

void pushMessage(const string& a_strCategory, EMessageType a_eType, const phantom::variant& a_Data, char* a_Format, ...)
{
    va_list args;
    va_start(args, a_Format);
    pushMessage(a_strCategory, a_eType, a_Data, a_Format, args );
    va_end(args);
}

void popMessage(const string& a_strCategory)
{
    Message* pTopMessage = topMessage(a_strCategory);
    pTopMessage = pTopMessage->getParent();
    o_assert(pTopMessage);
}

bool areConnected( const rtti_data& a_Sender, reflection::Signal* a_pSignal, const rtti_data& a_Receiver, reflection::MemberFunction* a_pMemberFunction )
{
    return PIMPL::internalAreConnected(a_Sender, a_pSignal, a_Receiver, a_pMemberFunction);
}

boolean canConnect( reflection::Signal* a_pSignal, reflection::MemberFunction* a_pSlot )
{
    reflection::Signature* pSlotSignature = a_pSlot->getSignature();
    reflection::Signature* pSignalSignature = a_pSignal->getSignature();
    if(pSlotSignature->getParameterCount() > pSignalSignature->getParameterCount())
    {
        return false;
    }
    else
    {
        uint i = 0;
        uint count = pSlotSignature->getParameterCount();
        for(;i<count;++i)
        {
            reflection::Type* pSlotParamType = pSlotSignature->getParameterType(i);
            reflection::Type* pSignalParamType = pSignalSignature->getParameterType(i);
            reflection::LValueReferenceType* pRefType = pSlotParamType->asLValueReferenceType();
            if(pRefType AND pRefType->getReferencedType()->asConstType() AND pSignalParamType->asLValueReferenceType() == nullptr)
            {
                pSlotParamType = pSlotParamType->removeReference()->removeConst();
            }
            if(pSignalParamType != pSlotParamType)
            {
                uint slotPointerLevel = pSlotParamType->getDataPointerLevel();
                uint signalPointerLevel = pSignalParamType->getDataPointerLevel();
                if( slotPointerLevel > 0 AND signalPointerLevel > 0 )
                {
                    // Both types are pointers and slot type is void* (accepts every kind of pointer)
                    if(pSlotParamType == typeOf<void*>())
                        return true;

                    // Both are pointer types of the same reference level
                    if(slotPointerLevel == signalPointerLevel)
                    {
                        reflection::DataPointerType* pSlotParamPointerType = pSlotParamType->asDataPointerType();
                        reflection::DataPointerType* pSignalParamPointerType = pSignalParamType->asDataPointerType();
                        while(pSlotParamPointerType->getDataPointerLevel() > 1)
                        {
                            pSignalParamPointerType = pSignalParamPointerType->removePointer()->asDataPointerType();
                            pSlotParamPointerType = pSlotParamPointerType->removePointer()->asDataPointerType();
                        }
                        reflection::Class* pSlotParamClass = pSlotParamPointerType->getPointedType()->asClass();
                        reflection::Class* pSignalParamClass = pSignalParamPointerType->getPointedType()->asClass();

                        // Pointer cast between pointers don't imply an offset (will still be compatible on lazy copy)
                        if( pSlotParamClass
                            AND pSignalParamClass
                            AND (
                            pSlotParamClass->getBaseClassOffsetCascade(pSignalParamClass) == 0
                            OR pSignalParamClass->getBaseClassOffsetCascade(pSlotParamClass) == 0)
                            )
                        {
                            return true;
                        }
                    }
                }
                return false;
            }
        }
    }
    return true;
}

connection::slot const* connect( const rtti_data& a_Sender, const character* a_pSignal, const rtti_data& a_Receiver, const character* a_pMemberFunction, const char* file /*= __FILE__*/, long line /*= __LINE__*/ )
{
    // EMISSION
    if(a_Sender.isNull())
    {
        o_exception(exception::reflection_runtime_exception, "the address passed as signal sender doesn't point to a phantom object");
    }
    reflection::Signal* pSignal = a_Sender.object_class->getSignalCascade(a_pSignal);
    if(pSignal == NULL)
    {
        o_warning(false, (string(file)+ " " + lexical_cast<string>(line)+ " : unknown signal : " + a_Sender.object_class->getQualifiedDecoratedName()+"::"+a_pSignal).c_str());
        return nullptr;
    }

    // RECEPTION
    if(a_Receiver.isNull())
    {
        o_exception(exception::reflection_runtime_exception, "the address passed as signal receiver doesn't point to a phantom object");
    }
    reflection::MemberFunction* pMemberFunction = a_Receiver.object_class->getMemberFunctionCascade(a_pMemberFunction);
    if(pMemberFunction == NULL)
    {
        o_warning(false, (string(file)+ " " + lexical_cast<string>(line)+ " : unknown slot : " + a_Receiver.object_class->getQualifiedDecoratedName()+"::"+a_pMemberFunction).c_str());
        return nullptr;
    }
    if(pMemberFunction->asSlot() == nullptr)
    {
        o_warning(false, (string(file)+ " " + lexical_cast<string>(line)+ " : connecting to a member_function which is not a slot").c_str());
    }
    if(NOT(canConnect(pSignal, pMemberFunction)))
    {
        o_warning(false, "connection impossible due to signature incompatibility");
        return nullptr;
    }
    return PIMPL::internalConnect(a_Sender, pSignal, a_Receiver, pMemberFunction);
}

connection::slot const* connect( const rtti_data& a_Sender, phantom::reflection::Signal* a_pSignal, const rtti_data& a_Receiver, phantom::reflection::MemberFunction* a_pMemberFunction, const char* file /*= __FILE__*/, long line /*= __LINE__*/ )
{
    o_assert(a_pSignal != NULL AND a_pMemberFunction != NULL);
    // EMISSION
    if(a_Sender.isNull())
    {
        o_exception(exception::reflection_runtime_exception, "the address passed as signal sender doesn't point to a phantom object");
    }
    if(NOT(a_Sender.object_class->isKindOf(static_cast<reflection::Class*>(a_pSignal->getOwner()))))
    {
        o_exception(exception::reflection_runtime_exception, "the signal doesn't belong to the sender's class");
    }
    // RECEPTION
    if(a_Receiver.isNull())
    {
        o_exception(exception::reflection_runtime_exception, "the address passed as signal receiver doesn't point to a phantom object");
    }
    if(NOT(a_Receiver.object_class->isKindOf(static_cast<reflection::Class*>(a_pMemberFunction->getOwner()))))
    {
        o_exception(exception::reflection_runtime_exception, "the slot doesn't belong to the receiver's class");
    }
    if(a_pMemberFunction->asSlot() == nullptr)
    {
        o_warning(false, "connecting to a member_function which is not a slot");
    }
    if(NOT(canConnect(a_pSignal, a_pMemberFunction)))
    {
        o_warning(false, "connection impossible due to signature incompatibility");
        return nullptr;
    }
    return PIMPL::internalConnect(a_Sender, a_pSignal, a_Receiver, a_pMemberFunction);
}


connection::slot const* tryConnect( const rtti_data& a_Sender, const character* a_pSignal, const rtti_data& a_Receiver, const character* a_pMemberFunction, const char* file /*= __FILE__*/, long line /*= __LINE__*/ )
{
    // EMISSION
    if(a_Sender.isNull())
    {
        o_exception(exception::reflection_runtime_exception, "the address passed as signal sender doesn't point to a phantom object");
    }
    reflection::Signal* pSignal = a_Sender.object_class->getSignalCascade(a_pSignal);
    if(pSignal == NULL)
    {
        return nullptr;
    }

    // RECEPTION
    if(a_Receiver.isNull())
    {
        o_exception(exception::reflection_runtime_exception, "the address passed as signal receiver doesn't point to a phantom object");
    }
    reflection::MemberFunction* pMemberFunction = a_Receiver.object_class->getMemberFunctionCascade(a_pMemberFunction);
    if(pMemberFunction == NULL)
    {
        return nullptr;
    }
    if(pMemberFunction->asSlot() == nullptr)
    {
        o_warning(false, (string(file)+ " " + lexical_cast<string>(line)+ " : connecting to a member_function which is not a slot").c_str());
    }
    if(NOT(canConnect(pSignal, pMemberFunction)))
    {
        return nullptr;
    }
    return PIMPL::internalConnect(a_Sender, pSignal, a_Receiver, pMemberFunction);
}

connection::slot const* disconnect( const rtti_data& a_Sender, const character* a_pSignal, const rtti_data& a_Receiver, const character* a_pMemberFunction, const char* file /*= __FILE__*/, long line /*= __LINE__*/ )
{
    // EMISSION
    if(a_Sender.isNull())
    {
        o_exception(exception::reflection_runtime_exception, "the address passed as signal sender doesn't point to a phantom object");
    }
    reflection::Signal* pSignal = a_Sender.object_class->getSignalCascade(a_pSignal);
    if(pSignal == NULL)
    {
        o_warning(false, (string("unknown signal : ")+a_pSignal).c_str());
        return nullptr;
    }

    // RECEPTION
    if(a_Receiver.isNull())
    {
        o_exception(exception::reflection_runtime_exception, "the address passed as signal receiver doesn't point to a phantom object");
    }
    reflection::MemberFunction* pMemberFunction = a_Receiver.object_class->getMemberFunctionCascade(a_pMemberFunction);
    if(pMemberFunction == NULL)
    {
        o_warning(false, (string("unknown slot : ")+a_pSignal).c_str());
        return nullptr;
    }
    if(NOT(canConnect(pSignal, pMemberFunction)))
    {
        o_warning(false, "connection impossible due to signature incompatibility");
        return nullptr;
    }
    return PIMPL::internalDisconnect(a_Sender, pSignal, a_Receiver, pMemberFunction);
}

connection::slot const* disconnect( const rtti_data& a_Sender, phantom::reflection::Signal* a_pSignal, const rtti_data& a_Receiver, phantom::reflection::MemberFunction* a_pMemberFunction, const char* file /*= __FILE__*/, long line /*= __LINE__*/ )
{
    o_assert(a_pSignal != NULL AND a_pMemberFunction != NULL);
    // EMISSION
    if(a_Sender.isNull())
    {
        o_exception(exception::reflection_runtime_exception, "the address passed as signal sender doesn't point to a phantom object");
    }
    // RECEPTION
    if(a_Receiver.isNull())
    {
        o_exception(exception::reflection_runtime_exception, "the address passed as signal receiver doesn't point to a phantom object");
    }
    if(NOT(canConnect(a_pSignal, a_pMemberFunction)))
    {
        o_warning(false, "connection impossible due to signature incompatibility");
        return nullptr;
    }
    return PIMPL::internalDisconnect(a_Sender, a_pSignal, a_Receiver, a_pMemberFunction);
}

connection::slot const* tryDisconnect( const rtti_data& a_Sender, const character* a_pSignal, const rtti_data& a_Receiver, const character* a_pMemberFunction, const char* file /*= __FILE__*/, long line /*= __LINE__*/ )
{
    // EMISSION
    if(a_Sender.isNull())
    {
        o_exception(exception::reflection_runtime_exception, "the address passed as signal sender doesn't point to a phantom object");
    }
    reflection::Signal* pSignal = a_Sender.object_class->getSignalCascade(a_pSignal);
    if(pSignal == NULL)
    {
        return nullptr;
    }

    // RECEPTION
    if(a_Receiver.isNull())
    {
        o_exception(exception::reflection_runtime_exception, "the address passed as signal receiver doesn't point to a phantom object");
    }
    reflection::MemberFunction* pMemberFunction = a_Receiver.object_class->getMemberFunctionCascade(a_pMemberFunction);
    if(pMemberFunction == NULL)
    {
        return nullptr;
    }
    if(NOT(canConnect(pSignal, pMemberFunction)))
    {
        return nullptr;
    }
    return PIMPL::internalDisconnect(a_Sender, pSignal, a_Receiver, pMemberFunction);
}

bool areConnected( const rtti_data& a_Sender, const character* a_pSignal, const rtti_data& a_Receiver, const character* a_pMemberFunction )
{
    if(a_Sender.isNull() || a_Receiver.isNull())
    {
        return false;
    }

    // EMISSION
    reflection::Signal* pSignal = a_Sender.object_class->getSignalCascade(a_pSignal);
    if(pSignal == NULL)
    {
        return false;
    }

    // RECEPTION
    reflection::MemberFunction* pMemberFunction = a_Receiver.object_class->getMemberFunctionCascade(a_pMemberFunction);
    if(pMemberFunction == NULL)
    {
        return false;
    }
    return areConnected(a_Sender, pSignal, a_Receiver, pMemberFunction);
}

dynamic_initializer_handle* dynamic_initializer()
{
    static dynamic_initializer_handle*    s_Singleton = NULL;
    if(s_Singleton == NULL)
    {
        s_Singleton = (dynamic_initializer_handle*)malloc(sizeof(dynamic_initializer_handle));
        new (s_Singleton) dynamic_initializer_handle;
    }
    return s_Singleton;
}

o_export void        assertion BOOST_PREVENT_MACRO_SUBSTITUTION ( const char* e, const char* file, uint line, const char* format, ...)
{
    va_list args;
    va_start(args, format);
    (*g_assert_func)(e, file,line,format,args);
    va_end(args);
}

o_export void        warning BOOST_PREVENT_MACRO_SUBSTITUTION (const char* e, const char* file, uint line, const char* format, ...)
{
    va_list args;
    va_start(args, format);
    (*g_warning_func)(e, file,line,format,args);
    va_end(args);
}

o_export void        error BOOST_PREVENT_MACRO_SUBSTITUTION (const char* e, const char* file, uint line, const char* format, ...)
{
    va_list args;
    va_start(args, format);
    (*g_error_func)(e,file,line,format,args);
    va_end(args);
}

o_export void        log BOOST_PREVENT_MACRO_SUBSTITUTION (int level, const char* file, uint line, const char* format, ...)
{
    va_list args;
    va_start(args, format);
    (*g_log_func)(level,file,line,format,args);
    va_end(args);
}

o_export void dynamicDelete( void* in o_memory_stat_append_parameters)
{
    const phantom::rtti_data&  oi = rttiDataOf(in);
    o_assert_not(oi.isNull());
    oi.deleteNow(o_memory_stat_insert_parameters_use);
}

boolean is( reflection::Class* a_pTestedClass, void* in )
{
    if(in == NULL) return true;
    reflection::Class* pClass = phantom::classOf(in);
    return pClass ? pClass->isKindOf(a_pTestedClass) : false;
}

o_export void setMetaDataValue( const string& elementName, size_t index, const string& value )
{
    reflection::LanguageElement* pElement = elementByName(elementName);
    o_assert(pElement AND pElement->asNamedElement());
    o_assert(index != eInvalidMetaDataIndex, "Meta data not declared, pass the metadata name list as third argument of the Phantom constructor");
    pElement->asNamedElement()->setMetaDataValue(index, value);
}

o_export  void setMetaDataValue( const string& elementName, const string& metaDataName, const string& value )
{
    setMetaDataValue(elementName, metaDataIndex(metaDataName), value);
}

o_export  const string& metaDataValue( const string& elementName, size_t index )
{
    reflection::LanguageElement* pElement = elementByName(elementName);
    o_assert(pElement AND pElement->asNamedElement());
    o_assert(index != eInvalidMetaDataIndex, "Meta data not declared, pass the metadata name list as third argument of the Phantom constructor");
    return pElement->asNamedElement()->getMetaDataValue(index);
}

o_export  const string& metaDataValue( const string& elementName, const string& metaDataName )
{
    return metaDataValue(elementName, metaDataIndex(metaDataName));
}

/*

#define x_define_primitive_type_singleton_member_function(_type_) \
    _type_##_Type* _type_##_Type::Instance() \
    { \
        static _type_##_Type* s_Instance = NULL;\
        if(s_Instance == NULL)\
        {\
            s_Instance = o_new_alloc_and_construct_part(_type_##_Type);\
            o_new_install_and_initialize_part(s_Instance);\
        }\
        return s_Instance; \
    }

o_static_assert(has_virtual_destructor_cascade<phantom::reflection::PrimitiveType>::value);

x_define_primitive_type_singleton_member_function(signal_t);
x_define_primitive_type_singleton_member_function(char);
x_define_primitive_type_singleton_member_function(uchar);
x_define_primitive_type_singleton_member_function(schar);
#if o_HAS_BUILT_IN_WCHAR_T
x_define_primitive_type_singleton_member_function(wchar_t);
#endif
x_define_primitive_type_singleton_member_function(short);
x_define_primitive_type_singleton_member_function(ushort);
x_define_primitive_type_singleton_member_function(int);

o_static_assert(boost::is_class<int_Type>::value);

x_define_primitive_type_singleton_member_function(uint);
x_define_primitive_type_singleton_member_function(long);
x_define_primitive_type_singleton_member_function(ulong);
x_define_primitive_type_singleton_member_function(longlong);
x_define_primitive_type_singleton_member_function(ulonglong);
x_define_primitive_type_singleton_member_function(float);
x_define_primitive_type_singleton_member_function(double);
x_define_primitive_type_singleton_member_function(longdouble);
x_define_primitive_type_singleton_member_function(bool);
x_define_primitive_type_singleton_member_function(void);

#undef x_define_primitive_type_singleton_member_function*/


void object::destroy()
{
    o_dynamic_delete m_address;
}

string encodeQualifiedDecoratedNameToIdentifierName( const string& a_strTypeName )
{
    string encoded = a_strTypeName;
    boost::replace_all(encoded, "<", "&lt;");
    boost::replace_all(encoded, ">", "&gt;");
    return encoded;
}

string decodeQualifiedDecoratedNameFromIdentifierName( const string& a_strTypeName )
{

    string decoded = a_strTypeName;
    boost::replace_all(decoded, "&lt;", "<");
    boost::replace_all(decoded, "&gt;", ">");
    return decoded;
}

o_export size_t currentThreadId()
{
    size_t threadId = 0;
#if o_OPERATING_SYSTEM == o_OPERATING_SYSTEM_WINDOWS
    threadId = GetCurrentThreadId();
#endif
    return threadId;
}

o_export void yieldCurrentThread()
{
#if o_OPERATING_SYSTEM == o_OPERATING_SYSTEM_WINDOWS
    Yield();
#endif
}

o_export void                                          installReflection(const string& a_strName, const string& a_strFileName, size_t a_PlatformHandle, const char* a_strFile)
{
    dynamic_initializer()->setActive(true);
    dynamic_initializer()->installReflection(a_strName, a_strFileName, a_PlatformHandle, a_strFile);
    dynamic_initializer()->setActive(false);
}
o_export void                                          uninstallReflection(const string& a_strName)
{
    dynamic_initializer()->setActive(true);
    dynamic_initializer()->uninstallReflection(a_strName);
    dynamic_initializer()->setActive(false);
}

o_export void pushModule( reflection::Module* a_pModule )
{
    o_assert(g_module == nullptr);
    g_module = a_pModule;
}

o_export reflection::Module* popModule()
{
    o_assert(g_module);
    reflection::Module* pModule = g_module;
    g_module = nullptr;
    return pModule;
}

o_export reflection::Module*                           currentModule()
{
    return g_module;
}


o_export reflection::Application*                                 application()
{
    return g_application;
}

o_export reflection::Module*                           moduleByName(const string& a_strName)
{
    auto found = g_modules.find(a_strName);
    if(found == g_modules.end()) return nullptr;
    return found->second;
}

o_export reflection::Module*                           moduleByFilePath(const string& a_strFilePath)
{

    for(auto it = g_modules.begin(); it != g_modules.end(); ++it)
    {
        reflection::Module* pModule = it->second;
        if(boost::filesystem::equivalent(boost::filesystem::absolute(a_strFilePath.c_str()), boost::filesystem::absolute(pModule->getFilePath().c_str())))
            return pModule;
    }
    return nullptr;
}

o_export reflection::Module*                           moduleByFileName(const string& a_strFileName)
{
    for(auto it = g_modules.begin(); it != g_modules.end(); ++it)
    {
        reflection::Module* pModule = it->second;
        if(a_strFileName == pModule->getFileName())
            return pModule;
    }
    return nullptr;
}

o_export map<string, reflection::Module*>::const_iterator          beginModules()
{
    return g_modules.begin();
}

o_export map<string, reflection::Module*>::const_iterator          endModules()
{
    return g_modules.end();
}

detail::dynamic_initializer_template_registrer::dynamic_initializer_template_registrer( const string& a_strNamespace, const string& a_strTemplateTypes, const string& a_strTemplateParams, const string& a_strName, const char* a_strFile )
{
    dynamic_initializer()->setActive(true);

    // Ensure the creation of the meta type
    reflection::Namespace* pNamespace = globalNamespace()->findOrCreateNamespaceCascade(a_strNamespace);
    reflection::Template* pTemplate = o_new(reflection::Template)(a_strTemplateTypes, a_strTemplateParams, a_strName, o_native);
    pNamespace->addTemplate(pTemplate);
    dynamic_initializer()->registerTemplate(pTemplate, a_strFile);
    dynamic_initializer()->setActive(false);
}

o_export phantom::reflection::Type* backupType( reflection::Type* a_pType )
{
    // TODO : make thread safe, at least ensure an assert if concurrency in debug mode
    static vector<phantom::reflection::Type*> backupedTypes;
    o_assert(a_pType);
    if(a_pType != (reflection::Type*)0xffffffff)
    {
        backupedTypes.push_back(a_pType);
    }
    else
    {
        o_assert(backupedTypes.size());
        a_pType = backupedTypes.back();
        backupedTypes.pop_back();
    }
    return a_pType;
}

o_export void* dynamicPoolAllocate( size_t s o_memory_stat_append_parameters )
{
    o_assert(s);
#if o__bool__enable_allocation_statistics
    phantom::memory::Statistics::RegisterBytes(s o_memory_stat_append_parameters_use);
#endif
    phantom::dynamic_pool_type_map::iterator it = g_DynamicPoolAllocators.find(s);
    if(it != g_DynamicPoolAllocators.end())
    {
        return it->second->ordered_malloc();
    }
    phantom::dynamic_pool_type*    new_pool = o_allocate(phantom::dynamic_pool_type);
    new (new_pool) phantom::dynamic_pool_type(s);
    g_DynamicPoolAllocators[s] = new_pool;
    return new_pool->ordered_malloc();
}

o_export void* dynamicPoolAllocate( size_t s, size_t count o_memory_stat_append_parameters )
{
    o_assert(s);
    o_assert(count);
#if o__bool__enable_allocation_statistics
    phantom::memory::Statistics::RegisterBytesN(s, count o_memory_stat_append_parameters_use);
#endif
    phantom::dynamic_pool_type_map::iterator it = g_DynamicPoolAllocators.find(s);
    if(it != g_DynamicPoolAllocators.end())
    {
        return it->second->ordered_malloc(count);
    }
    phantom::dynamic_pool_type*    new_pool = o_allocate(phantom::dynamic_pool_type);
    new (new_pool) phantom::dynamic_pool_type(s);
    g_DynamicPoolAllocators[s] = new_pool;
    return new_pool->ordered_malloc(count);
}

o_export void dynamicPoolDeallocate( size_t s, void* a_pAddress o_memory_stat_append_parameters )
{
    o_assert(s);
#if o__bool__enable_allocation_statistics
    phantom::memory::Statistics::UnregisterBytes(s o_memory_stat_append_parameters_use);
#endif
    phantom::dynamic_pool_type_map::iterator it = g_DynamicPoolAllocators.find(s);
    if(it != g_DynamicPoolAllocators.end())
    {
        return it->second->ordered_free(a_pAddress);
    }
    phantom::dynamic_pool_type*    new_pool = o_allocate(phantom::dynamic_pool_type);
    new (new_pool) phantom::dynamic_pool_type(s);
    g_DynamicPoolAllocators[s] = new_pool;
    new_pool->ordered_free(a_pAddress);
}

o_export void dynamicPoolDeallocate( size_t s, void* a_pAddress, size_t count o_memory_stat_append_parameters )
{
    o_assert(s);
    o_assert(count);
#if o__bool__enable_allocation_statistics
    phantom::memory::Statistics::UnregisterBytesN(s, count o_memory_stat_append_parameters_use);
#endif
    phantom::dynamic_pool_type_map::iterator it = g_DynamicPoolAllocators.find(s);
    if(it != g_DynamicPoolAllocators.end())
    {
        return it->second->ordered_free(a_pAddress, count);
    }
    phantom::dynamic_pool_type*    new_pool = o_allocate(phantom::dynamic_pool_type);
    new (new_pool) phantom::dynamic_pool_type(s);
    g_DynamicPoolAllocators[s] = new_pool;
    new_pool->ordered_free(a_pAddress, count);
}

o_export phantom::reflection::CPlusPlus* cplusplus()
{
    return g_cplusplus;
}

o_export phantom::reflection::Shaman* shaman()
{
    return g_shaman;
}

o_export phantom::reflection::Interpreter* interpreter()
{
    return g_interpreter;
}

o_export reflection::Module* instanceModuleOf( void const* a_pInstance )
{
    reflection::Class* pClass = classOf(a_pInstance);
    if(pClass) return pClass->getModule();
    else return nullptr;
}

o_export string conversionOperatorNameNormalizer( const string& a_strName, reflection::LanguageElement* a_pScope )
{
    if(a_strName.compare(0, 9, "operator ") == 0)
    {
        reflection::Type* pType = phantom::typeByName(a_strName.substr(9), a_pScope);
        if(pType)
        return "operator "+pType->getQualifiedDecoratedName();
    }
    return a_strName;
}

/// Placed here to avoid having to recompile CPlusPlus.cpp on each test change
string reflection::CPlusPlus::compilationTest()
{
    // return "((@(2854893509)).fragmentShader)=(&(@(2854884344)))";
    return "((args)[0])=((void*)&(a_0))";
}

o_export void setAssertFunc( message_report_func a_func )
{
    g_assert_func = a_func;
}

o_export void setErrorFunc( message_report_func a_func )
{
    g_error_func = a_func;
}

o_export void setLogFunc( log_func a_func )
{
    g_log_func = a_func;
}

o_export void setWarningFunc( message_report_func a_func )
{
    g_warning_func = a_func;
}

o_export void* baseOf( void const* a_pThis, size_t a_uiLevel /*= 0*/ )
{
    phantom::rtti_data_map::const_iterator found = phantom::g_rtti_data_map->find(a_pThis);
    if(found != phantom::g_rtti_data_map->end())
    {
        auto it = found->second.begin();
        std::advance(it, a_uiLevel);
        return it->base;
    }
    return const_cast<void*>(a_pThis);
}

o_export  phantom::reflection::Class* classOf( void const* a_pThis, size_t a_uiLevel )
{
    phantom::rtti_data_map::const_iterator found = phantom::g_rtti_data_map->find(a_pThis);
    if(found != phantom::g_rtti_data_map->end())
    {
        auto it = found->second.begin();
        std::advance(it, a_uiLevel);
        return it->object_class;
    }
    return nullptr;
}

o_export  phantom::reflection::Class* classAt( void const* a_pThis, size_t a_uiLevel )
{
    phantom::rtti_data_map::const_iterator found = phantom::g_rtti_data_map->find(a_pThis);
    if(found != phantom::g_rtti_data_map->end())
    {
        auto it = found->second.begin();
        std::advance(it, a_uiLevel);
        return it->layout_class;
    }
    return nullptr;
}

o_export  const phantom::rtti_data& rttiDataOf( void const* a_pThis, size_t a_uiLevel )
{
    static phantom::rtti_data null_info(0,0,0,0,0,0,0);
    phantom::rtti_data_map::const_iterator found = phantom::g_rtti_data_map->find(a_pThis);
    if(found != phantom::g_rtti_data_map->end()
        AND a_uiLevel < found->second.size())
    {
        auto it = found->second.begin();
        std::advance(it, a_uiLevel);
        return *it;
    }
    return null_info;
}

o_export  const phantom::rtti_data& rttiDataOf( void const* a_pThis, reflection::Class* a_pLayoutClass )
{
    static phantom::rtti_data null_info(0,0,0,0,0,0,0);
    phantom::rtti_data_map::const_iterator found = phantom::g_rtti_data_map->find(a_pThis);
    if(found != phantom::g_rtti_data_map->end())
    {
        auto& levels = found->second;
        if(a_pLayoutClass)
        {
            for(auto it = levels.begin(); it != levels.end(); ++it)
            {
                if(it->layout_class == a_pLayoutClass) return *it;
            }
            for(auto it = levels.begin(); it != levels.end(); ++it)
            {
                if(it->object_class->isKindOf(a_pLayoutClass)) return *it;
            }
        }
        return levels.front();
    }
    return null_info;
}

o_export void rttiLayoutOf( void const* a_pThis, vector<void*>& out, size_t a_uiLevel )
{
    static phantom::rtti_data null_info(0,0,0,0,0,0,0);
    phantom::rtti_data_map::const_iterator found = phantom::g_rtti_data_map->find(a_pThis);
    if(found != phantom::g_rtti_data_map->end())
    {
        auto base_it = found->second.begin();
        std::advance(base_it, a_uiLevel);
        void* base_address = base_it->base;
        auto it = phantom::g_rtti_data_map->begin();
        auto end = phantom::g_rtti_data_map->end();
        for(;it!=end;++it)
        {
            base_it = found->second.begin();
            std::advance(base_it, a_uiLevel);
            if(base_it->base == base_address)
            {
                out.push_back((void*)it->first);
            }
        }
    }
}

o_export  const rtti_data* addRttiData( void const* a_pThis, const rtti_data& a_RttiData )
{
    o_assert(a_pThis == a_RttiData.layout);
    auto& levels = (*g_rtti_data_map)[a_pThis];
    size_t level = a_RttiData.level();
    o_assert(level >= levels.size());
    levels.resize(level+1);
    return &(levels.back() = a_RttiData);
}

o_export  void replaceRttiData( void const* a_pThis, const rtti_data& a_RttiData )
{
    phantom::rtti_data_map::iterator found = phantom::g_rtti_data_map->find(a_pThis);
    o_assert(found != phantom::g_rtti_data_map->end());
    auto& levels = found->second;
    size_t level = a_RttiData.level();
    o_assert(level < levels.size());
    auto it = levels.begin();
    std::advance(it, level);
    *it = a_RttiData;
}

o_export  void removeRttiData( void const* a_pThis, size_t a_uiLevel )
{
    phantom::rtti_data_map::iterator found = phantom::g_rtti_data_map->find(a_pThis);
    o_assert((found != phantom::g_rtti_data_map->end()
        && (found->second.size()-1) == a_uiLevel), "remove order must be reversed of add order (LIFO/Stack)");
    found->second.pop_back();
    while(!found->second.empty() && found->second.back().isNull())
        found->second.pop_back();

    if(found->second.empty())
    {
        phantom::g_rtti_data_map->erase(found);
    }
}

o_export  size_t metaDataIndex( const string& elementName )
{
    const vector<string>& metaData = *phantom::g_meta_data_names;
    size_t i = 0;
    size_t count = metaData.size();
    for(;i<count;++i)
    {
        if(metaData[i] == elementName) return i;
    }
    return eInvalidMetaDataIndex;
}

o_export  phantom::reflection::Namespace* globalNamespace()
{
    return g_pGlobalNamespace;
}

o_export phantom::reflection::Package* package(reflection::Module* a_pModule, const string& a_strName)
{
    if(g_pPackages == nullptr) g_pPackages = new map<string, reflection::Package*>; 
    auto found = g_pPackages->find(a_strName);
    if(found == g_pPackages->end())
    {
        if(a_pModule)
        {
            reflection::Package* pPackage = o_static_new_alloc_and_construct_part(reflection::Package)(a_pModule, a_strName);
            return (*g_pPackages)[a_strName] = pPackage;
        }
        return nullptr;
    }
    else if(a_pModule AND a_pModule != found->second->getModule())
    {
        o_error(false, "package '%s' already defined in module '%s'", a_strName.c_str(), found->second->getModule()->getName().c_str());
    }
    return found->second;
}

o_export void sourceQualifiedNames( const string& a_strFilePath, vector<string>& words, reflection::Module* a_pModule )
{
    o_assert(a_strFilePath.size());

    vector<string> moduleSourcePathWords;
    boost::split( moduleSourcePathWords, a_pModule->getSourcePath(), boost::is_any_of("\\/"), boost::token_compress_on ); // SplitVec == { "hello abc","ABC","aBc goodbye" }
    moduleSourcePathWords.erase( std::remove_if( moduleSourcePathWords.begin(), moduleSourcePathWords.end(), 
        boost::bind( &string::empty, _1 ) ), moduleSourcePathWords.end() );

    boost::split( words, a_strFilePath, boost::is_any_of("\\/"), boost::token_compress_on ); // SplitVec == { "hello abc","ABC","aBc goodbye" }
    words.erase( std::remove_if( words.begin(), words.end(), 
        boost::bind( &string::empty, _1 ) ), words.end() );
    words.back() = words.back().substr(0, words.back().find_first_of(".")); // remove file name

    if(moduleSourcePathWords.size() > words.size())
    {
        o_exception(exception::reflection_runtime_exception, "source cannot be found in module source path sub directories");
    }

    size_t c = 0;
    for(size_t i = 0; i<words.size(); ++i)
    {
        if(i<moduleSourcePathWords.size())
        {
            if(moduleSourcePathWords[i] != words[i])
            {
                o_exception(exception::reflection_runtime_exception, "source cannot be found in module source path sub directories");
            }
        }
        else 
        {
            words[c++] = words[i];
        }
    }
    words.resize(words.size()-moduleSourcePathWords.size());
}

phantom::reflection::Source* nativeSource( reflection::Module* a_pModule, const string& a_strFilePath )
{
    o_error(a_pModule, "no module provided");
    vector<string> words;
#if 0//o_COMPILER == o_COMPILER_VISUAL_STUDIO && (o_COMPILER_VERSION <= o_COMPILER_VISUAL_STUDIO_MAJOR_VERSION_2010)
    boost::filesystem::path p(a_strFilePath);
    string fileName = p.filename().generic_string();
    for(auto it = fileName.begin(); it != fileName.end(); ++it)
        *it = tolower(*it);
    boost::filesystem::directory_iterator dirit(p.parent_path());
    boost::filesystem::directory_iterator dirend;
    for(;dirit!=dirend; ++dirit)
    {
        string dfileName = dirit->path().filename().generic_string();
        for(auto it = dfileName.begin(); it != dfileName.end(); ++it)
            *it = tolower(*it);
        if(dfileName == fileName)
        {
            sourceQualifiedNames(dirit->path().generic_string(), words, a_pModule);
            break;
        }
    }
#else
    sourceQualifiedNames(a_strFilePath, words, a_pModule);
#endif
    string packageName;
    auto end = words.end();
    end--;
    for(auto it = words.begin(); it != end; ++it)
    {
        if(it != words.begin())
            packageName+='.';
        packageName+=*it;
    }
    o_assert(packageName.size());
    reflection::Package* pPackage = package(a_pModule, packageName);
    const string& sourceName = words.back().substr(0, words.back().find_last_of("."));
    reflection::Source* pSource = pPackage->getSource(sourceName);
    if(pSource == nullptr)
    {
        return o_static_new_alloc_and_construct_part(reflection::Source)(pPackage, cplusplus(), sourceName, o_native|o_finalized);
    }
    return pSource;
}

void discardSourceFile( phantom::reflection::Source* a_pSourceFile )
{
    auto found = g_source_files.find(a_pSourceFile->getQualifiedName());
    o_assert(found != g_source_files.end());
    g_source_files.erase(found);
    o_delete(phantom::reflection::Source) a_pSourceFile;
}

o_export  reflection::Type* stringType()
{
    return g_type_of_string;
}

o_export  size_t metaDataCount()
{
    return phantom::g_meta_data_names->size();
}

o_export  const string& metaDataName( size_t index )
{
    return (*phantom::g_meta_data_names)[index];
}

void reflection::LanguageElement::Register(phantom::reflection::LanguageElement* pElement)
{
    g_elements->push_back(pElement);
}

void reflection::LanguageElement::Unregister(phantom::reflection::LanguageElement* pElement)
{
    g_elements->erase(std::find(g_elements->begin(), g_elements->end(), pElement));
}

Phantom::Phantom( const char* a_strMainModuleName, const char* a_strFile, int argc, char* argv[], int metadatasize, char* metadata[] )
{
    o_assert(g_instance == NULL, "Only one instance allowed and initialized once, the best is to use your main function scope and RAII");
    g_instance = this;

    //o_assert(m_eState == eState_NotInstalled, "Phantom has already been installed and can only be installed once per application");
    typeByName("phantom::reflection::Namespace", globalNamespace(), o_native)->install(g_pGlobalNamespace);
    typeByName("phantom::reflection::CPlusPlus", globalNamespace(), o_native)->install(g_cplusplus);
    typeByName("phantom::reflection::Shaman", globalNamespace(), o_native)->install(g_shaman); /// the funny thing in this line is that typeByName uses shaman...
    typeByName("phantom::reflection::Interpreter", globalNamespace(), o_native)->install(g_interpreter);

    typeOf<reflection::Application>()->install(g_application);
    typeOf<reflection::Application>()->initialize(g_application);

    application()->m_OperationCounter++;
    for(auto it = g_auto_loaded_modules->begin(); it != g_auto_loaded_modules->end(); ++it)
    {
        application()->moduleInstanciated(*it);
    }
    application()->m_OperationCounter--;

#if o_OPERATING_SYSTEM != o_OPERATING_SYSTEM_WINDOWS
    /* TODO LINUX
    setState(eState_DynamicInitializerDone_StartingInitialization);

    // We initialize and give reflection to objects created before Phantom
    // was setup (for instance, Native meta-types objects)
    dynamic_initializer()->installReflection();

    setState(eState_Installed);*/
#endif

    g_type_of_string = typeByName("phantom::string", globalNamespace(), o_native);

    int i = 0;
    for(;i<metadatasize;++i)
    {
        g_meta_data_names->push_back(metadata[i]);
    }

    application()->loadMain(a_strMainModuleName, argv[0], a_strFile);
}

Phantom::~Phantom()
{
    application()->unloadMain();

    application()->m_OperationCounter++;
    for(auto it = g_auto_loaded_modules->rbegin(); it != g_auto_loaded_modules->rend(); ++it)
    {
        application()->moduleDeleted(*it);
    }
    application()->m_OperationCounter--;

    typeOf<reflection::Application>()->terminate(g_application);
    typeOf<reflection::Application>()->uninstall(g_application);

    // delete SourceFiles
    for(auto it = g_source_files.begin(); it != g_source_files.end(); ++it)
    {
        o_dynamic_delete it->second;
    }
    g_source_files.clear();

    globalNamespace()->teardownMetaDataCascade(g_meta_data_names->size());
    // Deleting all the registered singletons
    /*{
        singleton_container::reverse_iterator it = m_singleton_container->rbegin();
        singleton_container::reverse_iterator end = m_singleton_container->rend();
        for(;it != end; ++it)
        {
            o_dynamic_delete (*it);
        }
    }*/

/*end_of_cleaning:
    o_warning(g_rtti_data_map->empty(), "not every phantom managed object has been released");
    g_rtti_data_map->~rtti_data_map();
    o_deallocate(g_rtti_data_map, Phantom::rtti_data_map);
    m_singleton_container->~singleton_container();
    o_deallocate(m_singleton_container, Phantom::singleton_container);
    setState(eState_Uninstalled);*/
}

o_export void release()
{
#if o__bool__enable_allocation_statistics
    phantom::memory::Statistics::Trace(std::cout);
#if o_COMPILER == o_COMPILER_VISUAL_STUDIO AND DEBUG
    system("pause");
#endif
#endif
    o_warning(g_rtti_data_map->empty(), "not every phantom managed object has been released");
    g_rtti_data_map->~rtti_data_map();
    o_deallocate(g_rtti_data_map, rtti_data_map);
    g_elements->~vector<reflection::LanguageElement*>();
    o_deallocate(g_elements, vector<reflection::LanguageElement*>);
//     dynamic_initializer()->~dynamic_initializer_handle();
//     auto di = dynamic_initializer();
//     o_deallocate(di, dynamic_initializer_handle);
}

o_export void reflection::detail::cpp_typeid_name_to_phantom_qualifiedDecoratedName( string& a_typeid_name )
{
    // TODO optimize
    if(a_typeid_name.find("class ") == 0)
        a_typeid_name = a_typeid_name.substr(6);
    else if(a_typeid_name.find("enum ") == 0)
        a_typeid_name = a_typeid_name.substr(5);
    else if(a_typeid_name.find("struct ") == 0)
        a_typeid_name = a_typeid_name.substr(7);
    else if(a_typeid_name.find("union ") == 0)
        a_typeid_name = a_typeid_name.substr(6);

    boost::replace_all(a_typeid_name, "<class ", "<");
    boost::replace_all(a_typeid_name, "<enum ", "<");
    boost::replace_all(a_typeid_name, "<struct ", "<");
    boost::replace_all(a_typeid_name, "<union ", "<");
    boost::replace_all(a_typeid_name, ",class ", ",");
    boost::replace_all(a_typeid_name, ",enum ", ",");
    boost::replace_all(a_typeid_name, ",struct ", ",");
    boost::replace_all(a_typeid_name, ",union ", ",");
}

o_export void reflection::detail::qualifiedDecoratedName_to_type_infos( string& qualifiedDecoratedName, reflection::type_infos& a_type_infos )
{
    size_t lt_pos = qualifiedDecoratedName.find_first_of('<');
    if(lt_pos != string::npos)
    {
        // a template, need to extract decoration
        a_type_infos.decoration = qualifiedDecoratedName.substr(lt_pos); // read decoration
        qualifiedDecoratedName = qualifiedDecoratedName.substr(0, lt_pos); // remove decoration
    }
    size_t scope_separator_pos = qualifiedDecoratedName.find_last_of(':');
    if(scope_separator_pos != string::npos)
    {
        a_type_infos.scope = qualifiedDecoratedName.substr(0, scope_separator_pos-1); // -1 is for the other ':' preceding the one we found last
        a_type_infos.name = qualifiedDecoratedName.substr(scope_separator_pos+1);
    }
    else 
    {
        a_type_infos.name = qualifiedDecoratedName;
    }
}

dynamic_initializer_handle::deferred_registrer_base::deferred_registrer_base(const char* a_srtFile, byte a_Priority)
    : file(a_srtFile)
    , priority(a_Priority)
{
    if(phantom::reflection::native::currentClassType() == nullptr)
        dynamic_initializer()->deferRegistration(this);
}

void dynamic_initializer_handle::dynamic_initializer_module_installation_func::exec( uint step )
{
    if(type->getQualifiedDecoratedName() == "std::allocator< char >")
    {
        int i=0;
        ++i;
    }
    if((step > o_global_value_SetupStepBit_TemplateSignature) AND file AND type->getOwner() == nullptr) 
    {
        reflection::ClassType* pClassType = type->asClassType();
        if(pClassType AND pClassType->getTemplateSpecialization())
        {
            nativeSource(file)->addTemplateSpecialization(pClassType->getTemplateSpecialization());
        }
        else nativeSource(file)->addType(type);
    }
    (*setupFunc)(type, step);
}

namespace reflection { namespace native {

#if o_COMPILER == o_COMPILER_VISUAL_STUDIO

o_export void** extract_vtable_pointer_from_asm(void* codeAddress)
{
#if 0
    //size_t thunkOffset = *(size_t*)((byte*)codeAddress+1);
    byte* realPtr = extract_asm_jmp_address_at((byte*)codeAddress);
    if(realPtr == nullptr) 
    {
        realPtr = (byte*)codeAddress;
    }
    else 
    {
        int i = 0;
        ++i;
    }
    byte* ctorCallInstruction = realPtr+0x47;//7;
    //byte* ctorFuncForwardAddress = extract_asm_jmp_address_at(ctorCallInstruction);
    byte* ctorFuncAddress = extract_asm_jmp_address_at(ctorCallInstruction);
    o_assert(ctorFuncAddress);
//     ctorCallInstruction = ctorFuncAddress+0xA;
//     ctorFuncAddress = extract_asm_jmp_address_at(ctorCallInstruction);
//     o_assert(ctorFuncAddress);
    o_assert(*(ctorFuncAddress+0x12) == (byte)0xC7);
    o_assert(*(ctorFuncAddress+0x13) == (byte)0x00);
    byte* vtableValueAddress = ctorFuncAddress+0x14;
    return *(void***)vtableValueAddress;
#else
    return nullptr;
#endif
}

#endif

o_export void pushScope( NamedElement* a_pScope )
{
    o_assert(a_pScope);
    g_pScopes->push(a_pScope);
}

o_export void popScope()
{
    g_pScopes->pop();
}

o_export ClassType* currentClassType()
{
    return currentScope()->asLanguageElement()->asClassType();
}

o_export Class* currentClass()
{
    return currentScope()->asLanguageElement()->asClass();
}

o_export NamedElement* currentScope()
{
    return g_pScopes->top();
}

o_export void pushAnonymousSection( AnonymousSection* a_pAnonymousSection )
{
    o_assert(a_pAnonymousSection);
    g_pAnonymousSections->push(a_pAnonymousSection);
}

o_export void popAnonymousSection()
{
    g_pAnonymousSections->pop();
}

o_export AnonymousSection* currentAnonymousSection()
{
    return g_pAnonymousSections->top();
}

o_export void pushMemberAnonymousSection( MemberAnonymousSection* a_pMemberAnonymousSection )
{
    o_assert(a_pMemberAnonymousSection);
    g_pMemberAnonymousSections->push(a_pMemberAnonymousSection);
}

o_export void popMemberAnonymousSection()
{
    g_pMemberAnonymousSections->pop();
}

o_export MemberAnonymousSection* currentMemberAnonymousSection()
{
    return g_pMemberAnonymousSections->top();
}

o_export void pushModifiers( modifiers_t a_Modifiers )
{
    return g_pModifiers->push(a_Modifiers);
}

o_export modifiers_t& currentModifiers()
{
    return g_pModifiers->top();
}

o_export void popModifiers()
{
    return g_pModifiers->pop();
}

}}

o_export phantom::reflection::PackageFolder* rootPackageFolder()
{
    o_assert_no_implementation();
    return nullptr;
}

o_namespace_end(phantom)

#ifdef WIN32
o_module("phantom")
#endif //WIN32
