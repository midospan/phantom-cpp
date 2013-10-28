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
#include <phantom/reflection/detail/element_finder_spirit.h>
#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>
/* ** The Class Header must be the last #include * */
#include "phantom.h"
/* *********************************************** */
o_registerN((phantom), data);
o_registerN((phantom), object);
o_registerN((phantom), bitfield);

o_begin_phantom_namespace() 

#define element_finder_default element_finder_spirit

connection::pair connection::pair::stack[connection::pair::eMaxStackSize];
int32 connection::pair::stack_pointer = -1;

size_t                connection::emission_guard::counter = 0;
size_t                connection::emission_guard::object_destroyed_count = 0;
connection::slot_pool::allocation_controller_map* connection::slot_pool::m_allocation_controller_map = 0;

phantom::Phantom::EState                        Phantom::m_eState;
phantom::Phantom::message_report_func           Phantom::m_assert_func = default_assert;
phantom::Phantom::message_report_func           Phantom::m_warning_func = default_warning;
phantom::Phantom::message_report_func           Phantom::m_error_func = default_error;
phantom::Phantom::log_func                      Phantom::m_log_func = default_log;
phantom::uint                                   Phantom::m_uiSetupStep;
phantom::reflection::Namespace*                 Phantom::m_pRootNamespace;
void*                                           Phantom::m_typeOf_cycling_address_workaround_ptr;
phantom::Phantom::rtti_data_map*                Phantom::m_rtti_data_map = NULL;
phantom::Phantom::element_container*		Phantom::m_elements = NULL;
phantom::Phantom::singleton_container*          Phantom::m_singleton_container = NULL;
phantom::Phantom*                               Phantom::m_instance = NULL;
phantom::Phantom::dynamic_pool_type_map         Phantom::m_DynamicPoolAllocators;

map<string, reflection::SourceFile*>            phantom::Phantom::m_SourceFiles;

Phantom::Phantom( int argc, char* argv[], int metadatasize, char* metadata[] )
{
    o_assert(m_instance == NULL, "Only one instance allowed and initialized once, the best is to use your main function scope and RAII");
    m_instance = this;

    o_assert(m_eState == eState_NotInstalled, "Phantom has already been installed and can only be installed once per application");

    setState(eState_DynamicInitializerDone_StartingInitialization);

    // We initialize and give reflection to objects created before Phantom
    // was setup (for instance, Native meta-types objects)
    dynamic_initializer()->installReflection();

    int i = 0;
    for(;i<metadatasize;++i)
    {
        m_meta_data_names.push_back(metadata[i]);
    }

    setState(eState_Installed);
}


Phantom::~Phantom()
{
    setState(eState_Uninstalling);

    // delete SourceFiles
    for(auto it = m_SourceFiles.begin(); it != m_SourceFiles.end(); ++it)
    {
        o_dynamic_delete it->second;
    }
    m_SourceFiles.clear();

    rootNamespace()->teardownMetaDataCascade(m_meta_data_names.size());
    // Deleting all the registered singletons
    {
        singleton_container::reverse_iterator it = m_singleton_container->rbegin();
        singleton_container::reverse_iterator end = m_singleton_container->rend();
        for(;it != end; ++it)
        {
            o_dynamic_delete (*it);
        }
    }
    vector<reflection::Type*> types_to_destroy;
    m_pRootNamespace->release(types_to_destroy);
    o_dynamic_delete_clean(m_pRootNamespace);
    std::sort(types_to_destroy.begin(), types_to_destroy.end(), type_sorter_by_build_order());


    vector<reflection::Class*> remaining_classes;

    vector<reflection::Type*>::iterator it = types_to_destroy.begin();
    vector<reflection::Type*>::iterator end = types_to_destroy.end();
    for(;it!=end;++it)
    {
        reflection::Type* pType = *it;
        if(pType == NULL) continue;
        if(pType->isClass())
        {
            reflection::Class* pClass = static_cast<reflection::Class*>(pType);
            pClass->destroyContent();
            if(pClass->getKindCount() OR pClass->getDerivedClassCount()) 
            {
                remaining_classes.push_back(pClass);
            }
            else
            {
                o_dynamic_delete_clean(pClass);
            }
        }
        else
        {
            o_dynamic_delete_clean(pType);
        }
    }

    while(!remaining_classes.empty())
    {
        vector<reflection::Class*>::iterator it = remaining_classes.begin();
        vector<reflection::Class*>::iterator end = remaining_classes.end();
        for(;it!=end;++it)
        {
            if((*it)->getKindCount() OR (*it)->getDerivedClassCount()) continue;
            break;
        }
        if(it != end)
        {
            o_dynamic_delete_clean((*it));
            remaining_classes.erase(it);
        }
        else
        {
            if(remaining_classes.size() == 1 AND remaining_classes[0] == classOf<reflection::Class>() )
            {
                o_dynamic_delete_clean(remaining_classes[0]);
                remaining_classes.clear();
            }
            else
            {
                std::cout<<console::bg_gray<<console::fg_red;
                std::cout<<"Phantom release process : some class instances haven't been destroyed"<<std::endl;

                std::cout<<console::bg_black;
                vector<reflection::Class*>::iterator it = remaining_classes.begin();
                vector<reflection::Class*>::iterator end = remaining_classes.end();
                for(;it!=end;++it)
                {
                    std::cout<<console::fg_red<<"----------------------------------------------------------------------------"<<std::endl;
                    std::cout<<console::fg_gray<<(*it)->getQualifiedDecoratedName()<<" : ";
                    std::cout<<console::fg_red<<"this "<<(*it)->getInstanceCount()<<" ";
                    std::cout<<console::fg_blue<<"all "<<(*it)->getKindCount()<<std::endl;

                }
                std::cout<<console::fg_gray;
#if o_OPERATING_SYSTEM == o_OPERATING_SYSTEM_WINDOWS AND DEBUG
                system("pause");
#endif
                goto end_of_cleaning;
            }
        }
    }
end_of_cleaning:
    o_warning(m_rtti_data_map->empty(), "not every phantom managed object has been released");
    m_rtti_data_map->~rtti_data_map();
    o_deallocate(m_rtti_data_map, Phantom::rtti_data_map);
	m_elements->~element_container();
	o_deallocate(m_elements, Phantom::element_container);
    m_singleton_container->~singleton_container();
    o_deallocate(m_singleton_container, Phantom::singleton_container);
    setState(eState_Uninstalled);
#if o__bool__enable_allocation_statistics
    phantom::memory::Statistics::Trace(std::cout);
#if o_COMPILER == o_COMPILER_VISUAL_STUDIO AND DEBUG
    system("pause");
#endif
#endif
}


void    extension::detail::dynamic_delete_helper::operator>>(void* instance)
{
    const phantom::rtti_data& oi = phantom::rttiDataOf(instance);
    o_assert_not(oi.isNull());
/*#if o__bool__enable_allocation_statistics
    o_warning(false, "dynamic deletion not yet supported by allocation statistics");
#endif*/
    oi.deleteNow(o_memory_stat_insert_parameters_use);
}

detail::dynamic_initializer_handle::dynamic_initializer_handle()
{
    Phantom::m_rtti_data_map = o_allocate(Phantom::rtti_data_map);
    new (Phantom::m_rtti_data_map) Phantom::rtti_data_map; 

	Phantom::m_elements = o_allocate(Phantom::element_container);
	new (Phantom::m_elements) Phantom::element_container; 

    Phantom::m_singleton_container = o_allocate(Phantom::singleton_container);
    new (Phantom::m_singleton_container) Phantom::singleton_container; 

    
    connection::slot_pool::m_allocation_controller_map= o_allocate(connection::slot_pool::allocation_controller_map);
    new (connection::slot_pool::m_allocation_controller_map) connection::slot_pool::allocation_controller_map; 

    Phantom::m_eState = Phantom::eState_NotInstalled;
    Phantom::m_uiSetupStep = 0;
    Phantom::m_typeOf_cycling_address_workaround_ptr = &Phantom::m_typeOf_cycling_address_workaround_ptr;
    Phantom::m_pRootNamespace = o_new_alloc_and_construct_part(reflection::Namespace)(o_CS(o_root_namespace_name));
    o_new_install_and_initialize_part(Phantom::m_pRootNamespace);
        
    uint i = 0;
    for(;i<32;++i)
    {
        m_DeferredSetupInfos.push_back(dynamic_initializer_module_installation_func_vector());
    }

    reflection::initializeSystem();

}



void Phantom::setState(EState s) 
{
    o_assert( s != eState_NotInstalled );
    m_eState = s;
}

void Phantom::updateLanguageElementGuid()
{
	static uint s_uitransientGuid = 0;

	Phantom::element_container::iterator it = m_elements->begin();
	Phantom::element_container::iterator end = m_elements->end();
	for (; it != end; it++)
	{
		s_uitransientGuid++;
		(*it)->setGuid(s_uitransientGuid);
	}
}

Phantom::element_map Phantom::getElementMap()
{
	Phantom::element_map element_map;
	Phantom::element_container::iterator it = m_elements->begin();
	Phantom::element_container::iterator end = m_elements->end();
	for (; it != end; it++)
	{
		element_map[(*it)->getQualifiedDecoratedName()] = (*it)->getGuid();
	}

	return element_map;
}

void Phantom::setElementMap(element_map a_element_map)
{
	uint uiGuid;
	Phantom::element_container::iterator it = m_elements->begin();
	Phantom::element_container::iterator end = m_elements->end();
	for (; it != end; it++)
	{
		uiGuid = a_element_map[(*it)->getQualifiedDecoratedName()];
		(*it)->setGuid(uiGuid);
	}
}

void Phantom::registerLanguageElement(phantom::reflection::LanguageElement* pElement)
{
	m_elements->push_back(pElement);
}

void Phantom::unregisterLanguageElement(phantom::reflection::LanguageElement* pElement)
{
	m_elements->erase(std::find(m_elements->begin(), m_elements->end(), pElement));
}

phantom::reflection::Type* typeByName( const string& a_strName, phantom::reflection::LanguageElement* a_pRootScope ) 
{
    return as<phantom::reflection::Type*>(elementByName(a_strName, a_pRootScope));
}

phantom::reflection::Type* typeByNameCascade( const string& a_strName, phantom::reflection::LanguageElement* a_pRootScope ) 
{
	return as<phantom::reflection::Type*>(elementByNameCascade(a_strName, reinterpret_cast<phantom::reflection::Namespace*>(a_pRootScope)));
}

phantom::reflection::LanguageElement* elementByName( const string& a_strName, phantom::reflection::LanguageElement* a_pRootElement )
{
  return phantom::reflection::detail::element_finder_default::find(a_strName, a_pRootElement);
}

void elementsByClass(reflection::Class* a_pClass, vector<reflection::LanguageElement*>& out, phantom::reflection::LanguageElement* a_pRootElement )
{
    if(a_pClass == nullptr OR classOf(a_pRootElement)->isKindOf(a_pClass))
    {
        out.push_back(a_pRootElement);
    }
    a_pRootElement->getElementsCascade(out, a_pClass);
}

phantom::reflection::LanguageElement* elementByNameCascade( const string& a_strName, phantom::reflection::Namespace* a_pNamespace )
{
	phantom::reflection::LanguageElement* pElement = elementByName(a_strName, reinterpret_cast<phantom::reflection::LanguageElement*>(a_pNamespace));
	if (pElement != NULL)
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

void detail::dynamic_initializer_handle::registerType( phantom::reflection::Type* a_pType )
{
    rootNamespace()->addType(a_pType);
}

void detail::dynamic_initializer_handle::registerType( const string& a_strNamespace, const string& a_strClassScope, phantom::reflection::Type* a_pType )
{
    phantom::reflection::Namespace* pNamespace = parseNamespace(a_strNamespace);
    o_assert(pNamespace != NULL);    
    if(a_strClassScope.empty())
    {
        pNamespace->addType(a_pType);
    }
    else
    {
        phantom::reflection::Type* pType = phantom::typeByName(a_strClassScope, pNamespace);
        o_assert(pType != NULL);
        pType->addNestedType(a_pType);
    }
}

phantom::reflection::Namespace* detail::dynamic_initializer_handle::parseNamespace( const string& a_strNamespace ) const
{
    return rootNamespace()->findOrCreateNamespaceCascade(a_strNamespace);
}

/*
void detail::dynamic_initializer_handle::registerType( phantom::reflection::Class* a_pType, module_installation_func setupFunc, uint a_uiSetupStepMask, const string& a_strNamespace )
{
    phantom::reflection::Namespace* pNamespace = parseNamespace(a_strNamespace);
    o_assert(pNamespace != NULL);    
    registerType(a_pType, setupFunc, a_uiSetupStepMask, pNamespace);
}*/

void detail::dynamic_initializer_handle::registerModule( module_installation_func setupFunc, uint a_uiSetupStepMask )
{
    if(setupFunc == NULL) 
        return;

    uint i = 0;
    for(;i<32;++i)
    {
        if(o_mask_test(a_uiSetupStepMask, (0x1<<i)))
        {
            if(Phantom::getSetupStep() > i)
            {
                (*setupFunc)(i);
            }
            else
            {
                m_DeferredSetupInfos[i].push_back(dynamic_initializer_module_installation_func(setupFunc));
            }
        }
    }
}

phantom::reflection::Namespace*            namespaceByName( const string& a_strNamespaceName )
{
    return as<phantom::reflection::Namespace*>(elementByName(a_strNamespaceName, rootNamespace()));
}

phantom::reflection::Namespace*            namespaceByList( list<string>* a_pNamespaceNameAsStringList )
{
    o_warning(false, "deprecated function "__FUNCTION__" used");
    return rootNamespace()->findOrCreateNamespaceCascade(a_pNamespaceNameAsStringList);
}

void detail::dynamic_initializer_handle::installReflection()
{
    Phantom::setState(Phantom::eState_Reflection_DeferredSetup);
    o_foreach(Object* pObject, m_DeferredReflectionSetupObjects)
    {
        pObject->getClass()->install(pObject);
    }
    m_DeferredReflectionSetupObjects.clear();
    if(Phantom::m_uiSetupStep > 0)
    {
        throw exception::reflection_runtime_exception("Only one instance of Phantom can be installed");
    }
    for(;Phantom::m_uiSetupStep<32;++Phantom::m_uiSetupStep)
    {
        dynamic_initializer_module_installation_func_vector& infos = m_DeferredSetupInfos[Phantom::m_uiSetupStep]; 
        if(infos.empty())
        {
            int i = 2;
        }
        uint j = 0;
        for(;j<infos.size(); ++j)
        {
            infos[j].exec(Phantom::m_uiSetupStep);
        }
    }
}

phantom::reflection::Class* classByName( const string& a_strQualifiedName, phantom::reflection::LanguageElement* a_pRootScope  ) 
{
    reflection::LanguageElement* pElement = phantom::elementByName(a_strQualifiedName, a_pRootScope);
    if(pElement) return pElement->asClass();
    return NULL;
}

phantom::reflection::PrimitiveType* primitiveTypeByName( const string& a_strName ) 
{
    reflection::LanguageElement* pElement = phantom::elementByName(a_strName, rootNamespace());
    if(pElement) return pElement->asPrimitiveType();
    return NULL;
}

phantom::reflection::DataPointerType* pointerTypeOf( phantom::reflection::Type* a_pType )
{
    return a_pType
                ? static_cast<phantom::reflection::DataPointerType*>(a_pType->getNamespace()->pointerTypeOf(a_pType))
                : NULL;
}

phantom::reflection::ReferenceType* referenceTypeOf( phantom::reflection::Type* a_pType )
{
    return a_pType
                ? static_cast<phantom::reflection::ReferenceType*>(
                        a_pType->getNamespace()->referenceTypeOf(a_pType)
                  )
                : NULL;
}
    
phantom::reflection::ArrayType* arrayTypeOf( phantom::reflection::Type* a_pType, size_t a_uiCount )
{
    return a_pType
        ? static_cast<phantom::reflection::ArrayType*>(
        a_pType->getNamespace()->arrayTypeOf(a_pType,a_uiCount)
        )
        : NULL;
}

phantom::reflection::Type* constTypeOf( phantom::reflection::Type* a_pType )
{
    return a_pType
                ? static_cast<phantom::reflection::Type*>(
                        a_pType->getNamespace()->constTypeOf(a_pType)
                  )
                : NULL;
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
    int r = vsprintf_s(buffer, 511, format, arglist);
    std::cout<<buffer<<std::endl<<console::fg_gray;
}

connection::slot const* Phantom::internalConnect( const rtti_data& a_Sender, reflection::Signal* a_pSignal, const rtti_data& a_Receiver, reflection::InstanceMemberFunction* a_pMemberFunction )
{
    connection::slot::list* pSlotList = a_pSignal->getSlotList(a_Sender.cast(static_cast<reflection::Class*>(a_pSignal->getOwner())));
    connection::slot* pFirstSlot = pSlotList->m_head;
    connection::slot* pLastSlot = pSlotList->m_queue;
    connection::slot* pSlot = a_Receiver.connection_slot_allocator->take();
    pSlot->m_list_pointer = pSlotList;
    pSlot->m_subroutine = a_pMemberFunction;
    pSlot->m_receiver = a_Receiver.cast(static_cast<reflection::Class*>(a_pMemberFunction->getOwner()));
#ifdef _DEBUG
    {
        while(pFirstSlot)
        {
            o_assert(!pFirstSlot->equals(pSlot));
            pFirstSlot = pFirstSlot->m_next;
        }
        pFirstSlot = pSlotList->m_head;
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
    a_pSignal->m_uiConnectionCount++;
    return pSlot;
}

connection::slot const* connect( void* a_pSender, const character* a_pSignal, void* a_pReceiver, const character* a_pMemberFunction )
{
    // EMISSION
    const rtti_data& pSenderInfo = phantom::rttiDataOf(a_pSender);
    if(pSenderInfo.isNull())
    {
        o_exception(exception::reflection_runtime_exception, "the address passed as signal sender doesn't point to a phantom object");
    }
    reflection::Signal* pSignal = pSenderInfo.object_class->getSignalCascade(a_pSignal);
    if(pSignal == NULL) 
    {
        o_warning(false, (string("unknown signal : ")+a_pSignal).c_str());
        return nullptr;
    }

    // RECEPTION
    const rtti_data& pReceiverInfo = phantom::rttiDataOf(a_pReceiver);
    if(pReceiverInfo.isNull())
    {
        o_exception(exception::reflection_runtime_exception, "the address passed as signal receiver doesn't point to a phantom object");
    }
    reflection::InstanceMemberFunction* pInstanceMemberFunction = pReceiverInfo.object_class->getInstanceMemberFunctionCascade(a_pMemberFunction);
    if(pInstanceMemberFunction == NULL) 
    {
        o_warning(false, (string("unknown slot : ")+a_pMemberFunction).c_str());
        return nullptr;
    }
    if(NOT(pInstanceMemberFunction->isSlot()))
    {
        o_warning(false, "connecting to a member_function which is not a slot");
    }
    if(NOT(canConnect(pSignal, pInstanceMemberFunction)))
    {
        o_warning(false, "connection impossible due to signature incompatibility");
        return nullptr;
    }
    return phantom::Phantom::internalConnect(pSenderInfo, pSignal, pReceiverInfo, pInstanceMemberFunction);
}

connection::slot const* connect( void* a_pSender, phantom::reflection::Signal* a_pSignal, void* a_pReceiver, phantom::reflection::InstanceMemberFunction* a_pMemberFunction )
{
    o_assert(a_pSignal != NULL AND a_pMemberFunction != NULL);
    // EMISSION
    const rtti_data& pSenderInfo = phantom::rttiDataOf(a_pSender);
    if(pSenderInfo.isNull())
    {
        o_exception(exception::reflection_runtime_exception, "the address passed as signal sender doesn't point to a phantom object");
    }
    if(NOT(pSenderInfo.object_class->isKindOf(static_cast<reflection::Class*>(a_pSignal->getOwner()))))
    {
        o_exception(exception::reflection_runtime_exception, "the signal doesn't belong to the sender's class");
    }
    // RECEPTION
    const rtti_data& pReceiverInfo = phantom::rttiDataOf(a_pReceiver);
    if(pReceiverInfo.isNull())
    {
        o_exception(exception::reflection_runtime_exception, "the address passed as signal receiver doesn't point to a phantom object");
    }
    if(NOT(pReceiverInfo.object_class->isKindOf(static_cast<reflection::Class*>(a_pMemberFunction->getOwner()))))
    {
        o_exception(exception::reflection_runtime_exception, "the slot doesn't belong to the receiver's class");
    }
    if(NOT(a_pMemberFunction->isSlot()))
    {
        o_warning(false, "connecting to a member_function which is not a slot");
    }
    if(NOT(canConnect(a_pSignal, a_pMemberFunction)))
    {
        o_warning(false, "connection impossible due to signature incompatibility");
        return nullptr;
    }
    return phantom::Phantom::internalConnect(pSenderInfo, a_pSignal, pReceiverInfo, a_pMemberFunction);
}


connection::slot const* tryConnect( void* a_pSender, const character* a_pSignal, void* a_pReceiver, const character* a_pMemberFunction )
{
    // EMISSION
    const rtti_data& pSenderInfo = phantom::rttiDataOf(a_pSender);
    if(pSenderInfo.isNull())
    {
        o_exception(exception::reflection_runtime_exception, "the address passed as signal sender doesn't point to a phantom object");
    }
    reflection::Signal* pSignal = pSenderInfo.object_class->getSignalCascade(a_pSignal);
    if(pSignal == NULL) 
    {
        return nullptr;
    }

    // RECEPTION
    const rtti_data& pReceiverInfo = phantom::rttiDataOf(a_pReceiver);
    if(pReceiverInfo.isNull())
    {
        o_exception(exception::reflection_runtime_exception, "the address passed as signal receiver doesn't point to a phantom object");
    }
    reflection::InstanceMemberFunction* pInstanceMemberFunction = pReceiverInfo.object_class->getInstanceMemberFunctionCascade(a_pMemberFunction);
    if(pInstanceMemberFunction == NULL) 
    {
        return nullptr;
    }
    if(NOT(pInstanceMemberFunction->isSlot()))
    {
        o_warning(false, "connecting to a member_function which is not a slot");
    }
    if(NOT(canConnect(pSignal, pInstanceMemberFunction)))
    {
        return nullptr;
    }
    return phantom::Phantom::internalConnect(pSenderInfo, pSignal, pReceiverInfo, pInstanceMemberFunction);
}


connection::slot const* Phantom::internalDisconnect( const rtti_data& a_Sender, reflection::Signal* a_pSignal, const rtti_data& a_Receiver, reflection::InstanceMemberFunction* a_pMemberFunction )
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

detail::dynamic_initializer_handle* Phantom::dynamic_initializer()
{
    static detail::dynamic_initializer_handle*    s_Singleton = NULL;
    if(s_Singleton == NULL)
    {
        s_Singleton = o_allocate(detail::dynamic_initializer_handle);
        new (s_Singleton) detail::dynamic_initializer_handle;
    }
    return s_Singleton;
}

phantom::reflection::SourceFile* Phantom::sourceFile( const string& absoluteName )
{
    boost::filesystem::path p(absoluteName.c_str());
    boost::filesystem::path ap = boost::filesystem::absolute(p);
    string key = ap.generic_string().c_str();
    auto found = m_SourceFiles.find(key);
    if(found != m_SourceFiles.end()) return found->second;
    return (m_SourceFiles[key] = o_new(phantom::reflection::SourceFile)(key));
}

void Phantom::discardSourceFile( phantom::reflection::SourceFile* a_pSourceFile )
{
    auto found = m_SourceFiles.find(a_pSourceFile->getAbsoluteName());
    o_assert(found != m_SourceFiles.end());
    m_SourceFiles.erase(found);
    o_delete(phantom::reflection::SourceFile) a_pSourceFile;
}
/*

void Phantom::completeElement( const string& a_Prefix, const reflection::CodePosition& a_Position, vector<reflection::LanguageElement*>& a_Elements )
{
    reflection::LanguageElement* pElementAtCodePosition = a_Position.sourceFile->findLanguageElement(a_Position);
    if(pElementAtCodePosition == nullptr)
        pElementAtCodePosition = rootNamespace();

    string normalizedPrefix = a_Prefix;
    boost::replace_all(normalizedPrefix, ".", "::");


    reflection::LanguageElement* pElement;
    vector<reflection::LanguageElement*> subElements;
    size_t pos = normalizedPrefix.rfind("::");
    if(pos == string::npos)
    {
        pElement = pElementAtCodePosition;
        o_assert(pElement);
        while(pElement)
        {
            pElement->getElements(subElements);
            pElement = pElement->getOwner();
        }
    }
    else 
    {
        
        pElement = elementByName(normalizedPrefix.substr(0, pos), pElementAtCodePosition);
        normalizedPrefix = normalizedPrefix.substr(pos+2);
        if(pElement == nullptr)
        {
            return;
        }
        pElement->getElements(subElements);
    }
    for(auto it = subElements.begin(); it != subElements.end(); ++it)
    {
        if((*it)->getName().find(normalizedPrefix) == 0)
            a_Elements.push_back(*it);
    }
}*/

connection::slot const* disconnect( void* a_pSender, const character* a_pSignal, void* a_pReceiver, const character* a_pMemberFunction )
{
    // EMISSION
    const rtti_data& pSenderInfo = phantom::rttiDataOf(a_pSender);
    if(pSenderInfo.isNull())
    {
        o_exception(exception::reflection_runtime_exception, "the address passed as signal sender doesn't point to a phantom object");
    }
    reflection::Signal* pSignal = pSenderInfo.object_class->getSignalCascade(a_pSignal);
    if(pSignal == NULL) 
    {
        o_warning(false, (string("unknown signal : ")+a_pSignal).c_str());
        return false;
    }

    // RECEPTION
    const rtti_data& pReceiverInfo = phantom::rttiDataOf(a_pReceiver);
    if(pReceiverInfo.isNull())
    {
        o_exception(exception::reflection_runtime_exception, "the address passed as signal receiver doesn't point to a phantom object");
    }
    reflection::InstanceMemberFunction* pInstanceMemberFunction = pReceiverInfo.object_class->getInstanceMemberFunctionCascade(a_pMemberFunction);
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
    return phantom::Phantom::internalDisconnect(pSenderInfo, pSignal, pReceiverInfo, pInstanceMemberFunction);
}

connection::slot const* disconnect( void* a_pSender, phantom::reflection::Signal* a_pSignal, void* a_pReceiver, phantom::reflection::InstanceMemberFunction* a_pMemberFunction )
{
    o_assert(a_pSignal != NULL AND a_pMemberFunction != NULL);
    // EMISSION
    const rtti_data& pSenderInfo = phantom::rttiDataOf(a_pSender);
    if(pSenderInfo.isNull())
    {
        o_exception(exception::reflection_runtime_exception, "the address passed as signal sender doesn't point to a phantom object");
    }
    // RECEPTION
    const rtti_data& pReceiverInfo = phantom::rttiDataOf(a_pReceiver);
    if(pReceiverInfo.isNull())
    {
        o_exception(exception::reflection_runtime_exception, "the address passed as signal receiver doesn't point to a phantom object");
    }
    if(NOT(canConnect(a_pSignal, a_pMemberFunction)))
    {
        o_warning(false, "connection impossible due to signature incompatibility");
        return nullptr;
    }
    return phantom::Phantom::internalDisconnect(pSenderInfo, a_pSignal, pReceiverInfo, a_pMemberFunction);
}


connection::slot const* tryDisconnect( void* a_pSender, const character* a_pSignal, void* a_pReceiver, const character* a_pMemberFunction )
{
    // EMISSION
    const rtti_data& pSenderInfo = phantom::rttiDataOf(a_pSender);
    if(pSenderInfo.isNull())
    {
        o_exception(exception::reflection_runtime_exception, "the address passed as signal sender doesn't point to a phantom object");
    }
    reflection::Signal* pSignal = pSenderInfo.object_class->getSignalCascade(a_pSignal);
    if(pSignal == NULL) 
    {
        return nullptr;
    }

    // RECEPTION
    const rtti_data& pReceiverInfo = phantom::rttiDataOf(a_pReceiver);
    if(pReceiverInfo.isNull())
    {
        o_exception(exception::reflection_runtime_exception, "the address passed as signal receiver doesn't point to a phantom object");
    }
    reflection::InstanceMemberFunction* pInstanceMemberFunction = pReceiverInfo.object_class->getInstanceMemberFunctionCascade(a_pMemberFunction);
    if(pInstanceMemberFunction == NULL) 
    {
        return nullptr;
    }
    if(NOT(canConnect(pSignal, pInstanceMemberFunction)))
    {
        return nullptr;
    }
    return phantom::Phantom::internalDisconnect(pSenderInfo, pSignal, pReceiverInfo, pInstanceMemberFunction);
}

bool Phantom::type_sorter_by_build_order::operator()( reflection::Type* one, reflection::Type* another )
{
    if(one->isKindOf(another))
        return true;
    else if(another->isKindOf(one))
        return false; 
    return one->getBuildOrder() > another->getBuildOrder();
}

boolean canConnect( reflection::Signal* a_pSignal, reflection::InstanceMemberFunction* a_pMemberFunction )
{
    reflection::Signature* pMemberFunctionSignature = a_pMemberFunction->getSignature();
    reflection::Signature* pSignalSignature = a_pSignal->getSignature();
    if(pMemberFunctionSignature->getParameterCount() > pSignalSignature->getParameterCount())
    {
        return false;
    }
    else
    {
        uint i = 0;
        uint count = pMemberFunctionSignature->getParameterCount();
        for(;i<count;++i)
        {
            reflection::Type* pMemberFunctionParamType = pMemberFunctionSignature->getParameterType(i);
            reflection::Type* pSignalParamType = pSignalSignature->getParameterType(i);
            if(NOT(pSignalParamType->hasTrivialCastTo(pMemberFunctionParamType)))
            {
                return false;
            }
        }
    }
    return true;
}

o_export void        assertion BOOST_PREVENT_MACRO_SUBSTITUTION ( const character* e, const character* m , const char* f , uint l)
{
    (*Phantom::m_assert_func)(e,m,f,l);
}
o_export void        warning BOOST_PREVENT_MACRO_SUBSTITUTION (const character* e, const character* m, const char* f, uint l)
{
    (*Phantom::m_warning_func)(e,m,f,l);
}
o_export void        error BOOST_PREVENT_MACRO_SUBSTITUTION (const character* e, const character* m, const char* f, uint l)
{
    (*Phantom::m_error_func)(e,m,f,l);
}
o_export void        log BOOST_PREVENT_MACRO_SUBSTITUTION (int level, const char* file, uint line, const char* format, ...)
{
    va_list args;
    va_start(args, format);
    (*Phantom::m_log_func)(level,file,line,format,args);
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
    o_assert(index != 0xffffffff, "Meta data not declared, pass the metadata name list as third argument of the Phantom constructor");
    pElement->setMetaDataValue(index, value);
}

o_export  const string& metaDataValue( const string& elementName, size_t index )
{
    reflection::LanguageElement* pElement = elementByName(elementName);
    o_assert(pElement);
    o_assert(index != 0xffffffff, "Meta data not declared, pass the metadata name list as third argument of the Phantom constructor");
    return pElement->getMetaDataValue(index);
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
#if o_BUILT_IN_WCHAR_T
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
    boost::replace_all(encoded, "_", "__");
    boost::replace_all(encoded, "<", "_L");
    boost::replace_all(encoded, ">", "_R");
    boost::replace_all(encoded, ",", "_C");
    boost::replace_all(encoded,"::", "_D");
    boost::replace_all(encoded, " ", "_S");
    return encoded;
}

string decodeQualifiedDecoratedNameFromIdentifierName( const string& a_strTypeName )
{
    string decoded;
    auto it = a_strTypeName.begin();
    auto end = a_strTypeName.end();
    for(;it!=end;++it)
    {
        if((*it) == '_')
        {
            ++it;
            switch(*it)
            {
            case 'L':
                decoded += '<';
                break;
            case 'R':
                decoded += '>';
                break;
            case 'S':
                decoded += ' ';
                break;
            case '_':
                decoded += '_';
                break;
            case 'C':
                decoded += ',';
                break;
            case 'D':
                decoded += "::";
                break;
            default:
                o_assert(false, "unknown encoding special character");
            }
        }
        else
        {
            decoded += *it;
        }
    }
    return decoded;
}

o_end_phantom_namespace()
