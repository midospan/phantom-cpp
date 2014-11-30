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

#include "phantom/ModuleLoader.h"
#include "phantom/ModuleLoader.hxx"
#include "phantom/reflection/CPlusPlus.h"
#include "phantom/reflection/CPlusPlus.hxx"
#include "phantom/reflection/Interpreter.h"
#include "phantom/reflection/Interpreter.hxx"
#include "phantom/reflection/Interpreter.hxx"
#include "phantom/Message.h"
#if o__bool__use_custom_stl_partioned_allocator OR o__bool__use_custom_stl_contiguous_allocator
#include <boost/property_tree_custom/info_parser.hpp>
#else
#include <boost/property_tree/info_parser.hpp>
#endif

o_registerN((phantom, memory), malloc_free_allocator_for_boost)
o_registerNT((phantom, memory), (typename, typename), (T, UserAllocator), malloc_free_allocator)

o_declareN(class, (phantom), Module)
o_declareN(class, (phantom, reflection), SourceFile)
o_declareN(class, (phantom, reflection), Signature)

o_functionN((phantom), phantom::reflection::Namespace*, rootNamespace, ());
o_functionN((phantom), phantom::reflection::Type*, typeByName, (const phantom::string&, phantom::reflection::LanguageElement*));
o_functionN((phantom), phantom::reflection::Expression*, expressionByName, (const phantom::string&, phantom::reflection::LanguageElement*));

int blabla;

o_variable(int, blabla, o_no_range);

namespace bb { float bibi; }

o_variableN((bb), float, bibi, o_no_range);

o_typedefN((phantom), modifiers_t);

o_namespace_begin(phantom)


typedef boost::pool<phantom::memory::malloc_free_allocator_for_boost> dynamic_pool_type ;
typedef phantom::map<size_t, dynamic_pool_type*>                        dynamic_pool_type_map;

typedef phantom::unordered_map<void const*, phantom::list<rtti_data>>		rtti_data_map;
typedef phantom::unordered_map<string, size_t>						element_map;
typedef phantom::vector<phantom::reflection::LanguageElement*>		element_container;
typedef phantom::vector<string>										meta_data_container;


enum
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
}                                               g_eState;

phantom::Phantom*                               g_instance = nullptr;
uint                                            g_uiSetupStep;

phantom::reflection::Type*                      g_type_of_string = nullptr;


phantom::vector<reflection::LanguageElement*>*  g_elements = nullptr;
phantom::vector<phantom::Module*>*              g_auto_loaded_modules;
phantom::message_report_func                    g_assert_func = default_assert;
phantom::message_report_func                    g_warning_func = default_warning;
phantom::message_report_func                    g_error_func = default_error;
phantom::log_func                               g_log_func = default_log;
phantom::map<string, Message*>                  g_Messages;
phantom::reflection::Namespace*                 g_root_namespace;
phantom::reflection::CPlusPlus*                 g_cplusplus;
phantom::reflection::Interpreter*               g_interpreter;
void*                                           g_typeOf_cycling_address_workaround_ptr;
phantom::rtti_data_map*                         g_rtti_data_map = nullptr;
phantom::Module*		                        g_module = nullptr;
phantom::ModuleLoader*		                    g_module_loader = nullptr;
phantom::serialization::DataBase*		        g_current_data_base = nullptr;
phantom::map<phantom::string, phantom::Module*> g_modules;
phantom::dynamic_pool_type_map                  g_DynamicPoolAllocators;
phantom::vector<phantom::reflection::Constant*> g_Constants;
phantom::vector<phantom::string>*               g_meta_data_names;
phantom::map<string, reflection::SourceFile*>   g_source_files;



struct PIMPL
{
    static bool internalAreConnected( const rtti_data& a_Sender, reflection::Signal* a_pSignal, const rtti_data& a_Receiver, reflection::InstanceMemberFunction* a_pMemberFunction )
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

    static connection::slot const* internalConnect( const rtti_data& a_Sender, reflection::Signal* a_pSignal, const rtti_data& a_Receiver, reflection::InstanceMemberFunction* a_pMemberFunction )
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

    static connection::slot const* internalDisconnect( const rtti_data& a_Sender, reflection::Signal* a_pSignal, const rtti_data& a_Receiver, reflection::InstanceMemberFunction* a_pMemberFunction )
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
{
    g_instance = nullptr;

    memory::Statistics::m_Allocations = new std::map<void*, memory::Statistics::allocation_info>;
    memory::Statistics::m_AllocationCount = 0 ;
    memory::Statistics::m_TotalAllocationCount = 0 ;
    memory::Statistics::m_AllocatedByteCount = 0 ;
    memory::Statistics::m_TotalAllocatedByteCount = 0 ;
    memory::Statistics::m_Locked = false;

    g_module_loader = o_allocate(ModuleLoader);
    new (g_module_loader) ModuleLoader;

    g_auto_loaded_modules = new vector<Module*>;

    g_rtti_data_map = o_allocate(rtti_data_map);
    new (g_rtti_data_map) rtti_data_map;

    g_meta_data_names = o_allocate(vector<string>);
    new (g_meta_data_names) vector<string>;

    g_elements = o_allocate(vector<reflection::LanguageElement*>);
    new (g_elements) vector<reflection::LanguageElement*>;

    connection::slot_pool::m_allocation_controller_map= o_allocate(connection::slot_pool::allocation_controller_map);
    new (connection::slot_pool::m_allocation_controller_map) connection::slot_pool::allocation_controller_map;

    g_eState = eState_NotInstalled;
    g_typeOf_cycling_address_workaround_ptr = &g_typeOf_cycling_address_workaround_ptr;

    g_cplusplus = o_static_new_alloc_and_construct_part(reflection::CPlusPlus);
    //o_static_new_install_and_initialize_part(g_cplusplus);

    g_interpreter = o_static_new_alloc_and_construct_part(reflection::Interpreter);

    g_root_namespace = o_static_new_alloc_and_construct_part(reflection::Namespace)(o_CS(o_root_namespace_name));
    o_static_new_install_and_initialize_part(g_root_namespace);

    // Reserve space for registration steps infos
    size_t i = 0;
    for(;i<32;++i)
    {
        m_DeferredSetupInfos.push_back(dynamic_initializer_module_installation_func_vector());
    }

    o_namespace(std);
    o_namespace(phantom);
    o_namespace(phantom::reflection);
    o_namespace(phantom::connection);
    o_namespace(phantom::state);

    reflection::initializeSystem();
}

dynamic_initializer_handle::~dynamic_initializer_handle()
{
    delete g_auto_loaded_modules;
    g_module_loader->~ModuleLoader();
    o_deallocate(g_module_loader, ModuleLoader) ;
    o_delete(reflection::CPlusPlus) g_cplusplus;

    typedef vector<string> vector_string;
    g_meta_data_names->~vector_string();
    o_deallocate(g_meta_data_names, vector<string>);

    connection::slot_pool::m_allocation_controller_map= o_allocate(connection::slot_pool::allocation_controller_map);
    new (connection::slot_pool::m_allocation_controller_map) connection::slot_pool::allocation_controller_map;
}

phantom::reflection::Type* typeByName( const string& a_strName, phantom::reflection::LanguageElement* a_pRootScope )
{
    const string & rootScopeName = a_pRootScope->getQualifiedDecoratedName();
    phantom::reflection::Type* pType = dynamic_initializer()->registeredTypeByName(rootScopeName.empty() ? a_strName : rootScopeName+"::"+a_strName);
    if(pType) return pType;
    reflection::LanguageElement* pElement = elementByName(a_strName, a_pRootScope);
    return pElement ? pElement->asType() : nullptr;
}

phantom::reflection::Type* typeByNameCascade( const string& a_strName, phantom::reflection::LanguageElement* a_pScope )
{
    reflection::LanguageElement* pElement = elementByNameCascade(a_strName, static_cast<phantom::reflection::Namespace*>(a_pScope));
    return pElement ? pElement->asType() : nullptr;
}

phantom::reflection::Expression* expressionByName( const string& a_strName, phantom::reflection::LanguageElement* a_pScope )
{
    return g_cplusplus->expressionByName(a_strName, a_pScope);
}

phantom::reflection::LanguageElement* elementByName( const string& a_strName, phantom::reflection::LanguageElement* a_pScope )
{
    return g_cplusplus->elementByName(a_strName, a_pScope);
}

phantom::reflection::Function* functionByName( const string& a_strName, phantom::reflection::Namespace* a_pScope )
{
    reflection::LanguageElement* pElement = g_cplusplus->elementByName(a_strName, a_pScope);
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

phantom::reflection::LanguageElement* elementByNameCascade( const string& a_strName, phantom::reflection::Namespace* a_pNamespace )
{
	phantom::reflection::LanguageElement* pElement = elementByName(a_strName, reinterpret_cast<phantom::reflection::LanguageElement*>(a_pNamespace));
	if(pElement != NULL)
	{
		return pElement;
	}

	uint uiNamespaceCount = a_pNamespace->getNamespaceCount();
	for (uint i = 0; i < uiNamespaceCount; i++)
	{
		pElement = elementByNameCascade(a_strName, a_pNamespace->getNamespace(i));
		if (pElement != NULL)
		{
			return pElement;
		}
	}

	return NULL;
}

phantom::reflection::Type*                    typeByGuid(uint guid)
{
    return rootNamespace()->getTypeByGuidCascade(guid);
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
    rootNamespace()->addType(a_pType);
}

void dynamic_initializer_handle::registerType( const string& a_strQualifiedDecoratedName, const string& a_strScope, phantom::reflection::Type* a_pType )
{
    o_assert(registeredTypeByName(a_strQualifiedDecoratedName) == nullptr, "type already registered, shouldn't happen, test is in type_of to avoid that");
    m_RegisteredTypes[a_strQualifiedDecoratedName] = a_pType;
    phantom::reflection::LanguageElement* pScope = elementByName(a_strScope);

    // Needed while boost::spirit used (TODO replace boost::spirit...), 
    // because it initialized too late for elementByName to work on C++ dynamic initialization

    if(pScope == nullptr)
    {
        list<string> words;
        split( words, a_strScope, boost::is_any_of(":. "), boost::token_compress_on ); // SplitVec == { "hello abc","ABC","aBc goodbye" }
        words.erase( std::remove_if( words.begin(), words.end(), 
            boost::bind( &string::empty, _1 ) ), words.end() );

        reflection::Namespace* pNamespace = rootNamespace();
        reflection::Type* pNestingType = nullptr;

        while(words.size() AND (pNamespace OR pNestingType))
        {
            const string& word = words.front();
            if(pNestingType)
            {
                size_t i = 0;
                size_t count = pNestingType->getNestedTypeCount();
                for(;i<count; ++i)
                {
                    if(pNestingType->getNestedType(i)->getDecoratedName() == word)
                    {
                        pNestingType = pNestingType->getNestedType(i);
                        break;
                    }
                }
                if(i == count)
                {
                    break;
                }
            }
            else 
            {
                pNestingType = pNamespace->getType(word);
                if(pNestingType == nullptr) pNamespace = pNamespace->getNamespace(word);
            }
            words.pop_front();
        }
        pScope = pNestingType ? (reflection::LanguageElement*)pNestingType : (reflection::LanguageElement*)pNamespace;
    }
    if(pScope == nullptr)
    {
        o_exception(exception::reflection_runtime_exception, "Type scope has not been registered => check your type's nesting class")
    }
    if(pScope->asNamespace())
    {
        pScope->asNamespace()->addType(a_pType);
    }
    else
    {
        o_assert(pScope->asType());
        pScope->asType()->addNestedType(a_pType);
    }
}

phantom::reflection::Namespace* dynamic_initializer_handle::parseNamespace( const string& a_strNamespace ) const
{
    return rootNamespace()->findOrCreateNamespaceCascade(a_strNamespace);
}

void dynamic_initializer_handle::registerTemplate( reflection::Template* a_pTemplate )
{
    m_DeferredTemplates.push_back(a_pTemplate);
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
                if((isAutoRegistrationLocked() || (moduleLoader()->getLoadedModuleCount() == 0)) && m_iCurrentInstallationStep < i )
                {
                    m_DeferredSetupInfos[i].push_back(dynamic_initializer_module_installation_func(a_pType, setupFunc));
                }
                else
                {
                    setupFunc(a_pType, i);
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
    return rootNamespace()->findOrCreateNamespaceCascade(a_pNamespaceNameAsStringList);
}


void dynamic_initializer_handle::installReflection(const string& a_strName, const string& a_strFileName, size_t a_PlatformHandle)
{
    o_assert(phantom::moduleByName(a_strName) == nullptr, "module with same name already registered");

    boost::filesystem::path p (a_strFileName.c_str());
    Module* pModule = o_new(Module)(a_strName, p.generic_string().c_str(), a_PlatformHandle);
    g_modules[a_strName] = pModule;
    phantom::pushModule(pModule);
    for(auto it = m_DeferredTemplates.begin(); it != m_DeferredTemplates.end(); ++it)
    {
        pModule->addLanguageElement(*it);
    }
    m_DeferredTemplates.clear();
    for(auto it = m_DeferredElements.begin(); it != m_DeferredElements.end(); ++it)
    {
        (*it)->registerElement();
        delete *it;
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

    if(a_strName.empty())
    {
        g_eState = eState_Installed;
    }
    if(g_instance == nullptr) // Phantom not initialized yet by user
    {
        g_auto_loaded_modules->push_back(pModule); // Module needs auto loading
    }
//     boost::filesystem::path p(pModule->getFileName().c_str());
//     string metaDataFile(string(p.parent_path().generic_string().c_str())+"/"+p.stem().generic_string().c_str()+".cfg");
//     if(boost::filesystem::exists(metaDataFile.c_str()))
//     {
//         loadMetaData(metaDataFile, pModule);
//     }
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
    o_delete(Module) found->second;
    g_modules.erase(found);
}

phantom::reflection::Class* classByName( const string& a_strQualifiedName, phantom::reflection::LanguageElement* a_pRootScope  )
{
    reflection::LanguageElement* pElement = phantom::elementByName(a_strQualifiedName, a_pRootScope);
    return pElement ? pElement->asClass() : nullptr;
}

phantom::reflection::PrimitiveType* primitiveTypeByName( const string& a_strName )
{
    reflection::LanguageElement* pElement = phantom::elementByName(a_strName, rootNamespace());
    if(pElement) return pElement->asPrimitiveType();
    return NULL;
}

void default_assert( const character* expression, const character* message, const char* file, uint line )
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
    std::cout
        <<console::fg_red<<"ASSERT("<<shortenFile<<"|"<<line<<")"<<std::endl
        <<console::fg_red<<"["<<std::endl
        <<'\t'<<console::fg_blue<< expression
        <<console::fg_white<<" is false" <<std::endl
        <<'\t'<<message<<std::endl
        <<console::fg_red<<"]"<<std::endl;

    o_debug_execution_break();
    exit(1);
}

void default_warning( const character* expression, const character* message, const char* file, uint line )
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
    std::cout
        <<console::fg_yellow<<"WARNING("<<shortenFile<<"|"<<line<<")"<<std::endl
        <<console::fg_yellow<<"["<<std::endl
        <<'\t'<<console::fg_blue<< expression
        <<console::fg_white<<" is false" <<std::endl
        <<'\t'<<message<<std::endl
        <<console::fg_yellow<<"]"<<std::endl;

}

void default_error( const character* expression, const character* message, const char* file, uint line )
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
    std::cout
        <<console::fg_red<<"ERROR("<<shortenFile<<"|"<<line<<")"<<std::endl
        <<console::fg_red<<"["<<std::endl
        <<'\t'<<console::fg_blue<< expression
        <<console::fg_white<<" is false" <<std::endl
        <<'\t'<<message<<std::endl
        <<console::fg_red<<"]"<<std::endl;
    assert(false);
    exit(1);
}

void default_log(int level, const char* file, uint line, const char* format, va_list arglist )
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

    std::cout
        <<console::fg_green<<"LOG("<<console::fg_white<<shortenFile<<console::fg_green<<"|"<<console::fg_white<<line<<console::fg_green<<") "<<console::fg_gray;

    char buffer[512];
    buffer[511] = '\0';
    int r = vsnprintf(buffer, 511, format, arglist);
    std::cout<<buffer<<std::endl<<console::fg_gray;
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

bool areConnected( const rtti_data& a_Sender, reflection::Signal* a_pSignal, const rtti_data& a_Receiver, reflection::InstanceMemberFunction* a_pMemberFunction )
{
    return PIMPL::internalAreConnected(a_Sender, a_pSignal, a_Receiver, a_pMemberFunction);
}

boolean canConnect( reflection::Signal* a_pSignal, reflection::InstanceMemberFunction* a_pSlot )
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
            reflection::ReferenceType* pRefType = pSlotParamType->asReferenceType();
            if(pRefType AND pRefType->getReferencedType()->asConstType() AND pSignalParamType->asReferenceType() == nullptr)
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
    reflection::InstanceMemberFunction* pInstanceMemberFunction = a_Receiver.object_class->getInstanceMemberFunctionCascade(a_pMemberFunction);
    if(pInstanceMemberFunction == NULL)
    {
        o_warning(false, (string(file)+ " " + lexical_cast<string>(line)+ " : unknown slot : " + a_Receiver.object_class->getQualifiedDecoratedName()+"::"+a_pMemberFunction).c_str());
        return nullptr;
    }
    if(pInstanceMemberFunction->asSlot() == nullptr)
    {
        o_warning(false, (string(file)+ " " + lexical_cast<string>(line)+ " : connecting to a member_function which is not a slot").c_str());
    }
    if(NOT(canConnect(pSignal, pInstanceMemberFunction)))
    {
        o_warning(false, "connection impossible due to signature incompatibility");
        return nullptr;
    }
    return PIMPL::internalConnect(a_Sender, pSignal, a_Receiver, pInstanceMemberFunction);
}

connection::slot const* connect( const rtti_data& a_Sender, phantom::reflection::Signal* a_pSignal, const rtti_data& a_Receiver, phantom::reflection::InstanceMemberFunction* a_pMemberFunction, const char* file /*= __FILE__*/, long line /*= __LINE__*/ )
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
    reflection::InstanceMemberFunction* pInstanceMemberFunction = a_Receiver.object_class->getInstanceMemberFunctionCascade(a_pMemberFunction);
    if(pInstanceMemberFunction == NULL)
    {
        return nullptr;
    }
    if(pInstanceMemberFunction->asSlot() == nullptr)
    {
        o_warning(false, (string(file)+ " " + lexical_cast<string>(line)+ " : connecting to a member_function which is not a slot").c_str());
    }
    if(NOT(canConnect(pSignal, pInstanceMemberFunction)))
    {
        return nullptr;
    }
    return PIMPL::internalConnect(a_Sender, pSignal, a_Receiver, pInstanceMemberFunction);
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
        return false;
    }

    // RECEPTION
    if(a_Receiver.isNull())
    {
        o_exception(exception::reflection_runtime_exception, "the address passed as signal receiver doesn't point to a phantom object");
    }
    reflection::InstanceMemberFunction* pInstanceMemberFunction = a_Receiver.object_class->getInstanceMemberFunctionCascade(a_pMemberFunction);
    if(pInstanceMemberFunction == NULL)
    {
        o_warning(false, (string("unknown slot : ")+a_pSignal).c_str());
        return nullptr;
    }
    if(NOT(canConnect(pSignal, pInstanceMemberFunction)))
    {
        o_warning(false, "connection impossible due to signature incompatibility");
        return nullptr;
    }
    return PIMPL::internalDisconnect(a_Sender, pSignal, a_Receiver, pInstanceMemberFunction);
}

connection::slot const* disconnect( const rtti_data& a_Sender, phantom::reflection::Signal* a_pSignal, const rtti_data& a_Receiver, phantom::reflection::InstanceMemberFunction* a_pMemberFunction, const char* file /*= __FILE__*/, long line /*= __LINE__*/ )
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
    reflection::InstanceMemberFunction* pInstanceMemberFunction = a_Receiver.object_class->getInstanceMemberFunctionCascade(a_pMemberFunction);
    if(pInstanceMemberFunction == NULL)
    {
        return nullptr;
    }
    if(NOT(canConnect(pSignal, pInstanceMemberFunction)))
    {
        return nullptr;
    }
    return PIMPL::internalDisconnect(a_Sender, pSignal, a_Receiver, pInstanceMemberFunction);
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
    reflection::InstanceMemberFunction* pInstanceMemberFunction = a_Receiver.object_class->getInstanceMemberFunctionCascade(a_pMemberFunction);
    if(pInstanceMemberFunction == NULL)
    {
        return false;
    }
    return areConnected(a_Sender, pSignal, a_Receiver, pInstanceMemberFunction);
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

phantom::reflection::SourceFile* sourceFile( const string& absoluteName )
{
    boost::filesystem::path p(absoluteName.c_str());
    boost::filesystem::path ap = boost::filesystem::absolute(p);
    string key = ap.generic_string().c_str();
    auto found = g_source_files.find(key);
    if(found != g_source_files.end()) return found->second;
    return (g_source_files[key] = o_new(phantom::reflection::SourceFile)(key));
}

void discardSourceFile( phantom::reflection::SourceFile* a_pSourceFile )
{
    auto found = g_source_files.find(a_pSourceFile->getAbsoluteName());
    o_assert(found != g_source_files.end());
    g_source_files.erase(found);
    o_delete(phantom::reflection::SourceFile) a_pSourceFile;
}

o_export void        assertion BOOST_PREVENT_MACRO_SUBSTITUTION ( const character* e, const character* m , const char* f , uint l)
{
    (*g_assert_func)(e,m,f,l);
}

o_export void        warning BOOST_PREVENT_MACRO_SUBSTITUTION (const character* e, const character* m, const char* f, uint l)
{
    (*g_warning_func)(e,m,f,l);
}

o_export void        error BOOST_PREVENT_MACRO_SUBSTITUTION (const character* e, const character* m, const char* f, uint l)
{
    (*g_error_func)(e,m,f,l);
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
    o_assert(pElement);
    o_assert(index != eInvalidMetaDataIndex, "Meta data not declared, pass the metadata name list as third argument of the Phantom constructor");
    pElement->setMetaDataValue(index, value);
}

o_export  void setMetaDataValue( const string& elementName, const string& metaDataName, const string& value )
{
    setMetaDataValue(elementName, metaDataIndex(metaDataName), value);
}

o_export  const string& metaDataValue( const string& elementName, size_t index )
{
    reflection::LanguageElement* pElement = elementByName(elementName);
    o_assert(pElement);
    o_assert(index != eInvalidMetaDataIndex, "Meta data not declared, pass the metadata name list as third argument of the Phantom constructor");
    return pElement->getMetaDataValue(index);
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

o_export void                                          installReflection(const string& a_strName, const string& a_strFileName, size_t a_PlatformHandle)
{
    dynamic_initializer()->setActive(true);
    dynamic_initializer()->installReflection(a_strName, a_strFileName, a_PlatformHandle);
    dynamic_initializer()->setActive(false);
}
o_export void                                          uninstallReflection(const string& a_strName)
{
    dynamic_initializer()->setActive(true);
    dynamic_initializer()->uninstallReflection(a_strName);
    dynamic_initializer()->setActive(false);
}

o_export void pushModule( Module* a_pModule )
{
    if(g_module)
    {
        a_pModule->setParentModule(g_module);
    }
    g_module = a_pModule;
}

o_export Module* popModule()
{
    o_assert(g_module);
    Module* pModule = g_module;
    g_module = g_module->getParentModule();
    return pModule;
}

o_export Module*                           currentModule()
{
    return g_module;
}


o_export ModuleLoader*                                 moduleLoader()
{
    return g_module_loader;
}

o_export Module*                           moduleByName(const string& a_strName)
{
    auto found = g_modules.find(a_strName);
    if(found == g_modules.end()) return nullptr;
    return found->second;
}

o_export Module*                           moduleByFilePath(const string& a_strFilePath)
{

    for(auto it = g_modules.begin(); it != g_modules.end(); ++it)
    {
        Module* pModule = it->second;
        if(boost::filesystem::equivalent(boost::filesystem::absolute(a_strFilePath.c_str()), boost::filesystem::absolute(pModule->getFilePath().c_str())))
            return pModule;
    }
    return nullptr;
}

o_export Module*                           moduleByFileName(const string& a_strFileName)
{
    for(auto it = g_modules.begin(); it != g_modules.end(); ++it)
    {
        Module* pModule = it->second;
        if(a_strFileName == pModule->getFileName())
            return pModule;
    }
    return nullptr;
}

o_export map<string, Module*>::const_iterator          beginModules()
{
    return g_modules.begin();
}

o_export map<string, Module*>::const_iterator          endModules()
{
    return g_modules.end();
}

detail::dynamic_initializer_template_registrer::dynamic_initializer_template_registrer( const string& a_strNamespace, const string& a_strName )
{
    dynamic_initializer()->setActive(true);

    // Ensure the creation of the meta type
    reflection::Namespace* pNamespace = rootNamespace()->findOrCreateNamespaceCascade(a_strNamespace);
    /// If you get an error : 'apply' : is not a member of 'phantom::detail::module_installer'
    /// It's probably because you didn't declare a reflection scope (internal or external) for the given t_Ty class
    reflection::Template* pTemplate = pNamespace->findOrCreateTemplate(a_strName);
    dynamic_initializer()->registerTemplate(pTemplate);
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

o_export void setCurrentDataBase( serialization::DataBase* a_pDataBase )
{
    g_current_data_base = a_pDataBase;
}

o_export serialization::DataBase* getCurrentDataBase()
{
    return g_current_data_base;
}

o_export phantom::reflection::Language* cplusplus()
{
    return g_cplusplus;
}

o_export phantom::reflection::Interpreter* interpreter()
{
    return g_interpreter;
}

o_export Module* instanceModuleOf( void const* a_pInstance )
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

o_export  phantom::reflection::Namespace* rootNamespace()
{
    return g_root_namespace;
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

Phantom::Phantom( int argc, char* argv[], int metadatasize, char* metadata[] )
{
    o_assert(g_instance == NULL, "Only one instance allowed and initialized once, the best is to use your main function scope and RAII");
    g_instance = this;

    //o_assert(m_eState == eState_NotInstalled, "Phantom has already been installed and can only be installed once per application");
    typeByName("phantom::reflection::Namespace")->install(g_root_namespace);
    typeByName("phantom::reflection::CPlusPlus")->install(g_cplusplus);
    typeByName("phantom::reflection::Interpreter")->install(g_interpreter);

    typeOf<ModuleLoader>()->install(g_module_loader);
    typeOf<ModuleLoader>()->initialize(g_module_loader);

    moduleLoader()->m_OperationCounter++;
    for(auto it = g_auto_loaded_modules->begin(); it != g_auto_loaded_modules->end(); ++it)
    {
        moduleLoader()->moduleInstanciated(*it);
    }
    moduleLoader()->m_OperationCounter--;

#if o_OPERATING_SYSTEM != o_OPERATING_SYSTEM_WINDOWS
    setState(eState_DynamicInitializerDone_StartingInitialization);

    // We initialize and give reflection to objects created before Phantom
    // was setup (for instance, Native meta-types objects)
    dynamic_initializer()->installReflection();

    setState(eState_Installed);
#endif

    g_type_of_string = typeByName("phantom::string");

    int i = 0;
    for(;i<metadatasize;++i)
    {
        g_meta_data_names->push_back(metadata[i]);
    }

    moduleLoader()->loadMain(argv[0]);
}

Phantom::~Phantom()
{
    moduleLoader()->unloadMain();

    moduleLoader()->m_OperationCounter++;
    for(auto it = g_auto_loaded_modules->rbegin(); it != g_auto_loaded_modules->rend(); ++it)
    {
        moduleLoader()->moduleDeleted(*it);
    }
    moduleLoader()->m_OperationCounter--;

    typeOf<ModuleLoader>()->terminate(g_module_loader);
    typeOf<ModuleLoader>()->uninstall(g_module_loader);

    // delete SourceFiles
    for(auto it = g_source_files.begin(); it != g_source_files.end(); ++it)
    {
        o_dynamic_delete it->second;
    }
    g_source_files.clear();

    rootNamespace()->teardownMetaDataCascade(g_meta_data_names->size());
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



o_namespace_end(phantom)

o_module("phantom")
