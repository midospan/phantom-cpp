
namespace detail
{


    template<typename t_Ty, bool t_has_reflection>
    struct reflection_installer_helper
    {

    };

    template<typename t_Ty>
    struct reflection_installer_helper<t_Ty, true>
        : public proxy_of<t_Ty>::type::enclosed_reflection
    {
        reflection_installer_helper() 
        { 
            auto pType = typeOf<t_Ty>(); 
            o_assert(phantom::currentModule(), "no module pushed for the current registered type") ;
            o_assert(pType->getModule() == nullptr);
            phantom::currentModule()->addLanguageElement(pType);
        } // ensure type is registered even if no members is added
    };

    template<typename t_Ty>
    struct reflection_installer : public reflection_installer_helper<t_Ty, has_enclosed_reflection<t_Ty>::value>
    {

    };

    template<typename t_Ty, bool t_has_statechart>
    struct statechart_installer_helper
    {

    };

    template<typename t_Ty>
    struct statechart_installer_helper<t_Ty, true>
        : public proxy_of<t_Ty>::type::o_NESTED_TEMPLATE enclosed_statechart<t_Ty>
    {
        statechart_installer_helper()
        {
            classOf<t_Ty>()->setStateMachine(phantom::state::native::TNativeStateMachine<t_Ty>::Instance());
        }
    };

    template<typename t_Ty>
    struct statechart_installer : public statechart_installer_helper<t_Ty, has_statechart<t_Ty>::value>
    {

    };

    template<typename t_Ty, int t_counter, bool t_has_reflection, bool t_has_statechart>
    struct module_installer_helper
    {
    };

    template<typename t_Ty, int t_counter>
    struct module_installer_helper<t_Ty, t_counter, true, true>
    {
        static void apply(phantom::reflection::Type* a_pType, uint step)
        {
            reflection::Class* saved_class = reflection::Types::currentInstalledClass;
            reflection::TemplateSpecialization* saved_template_specialization = reflection::Types::currentInstalledTemplateSpecialization;
            reflection::Types::currentInstalledClass = a_pType->asClass();
            reflection::Types::currentInstalledTemplateSpecialization = reflection::Types::currentInstalledClass ? reflection::Types::currentInstalledClass->getTemplateSpecialization() : nullptr;
            switch(step)
            {
            case o_global_value_SetupStepIndex_TemplateSignature:
                {
                    reflection::template_specialization_adder<t_Ty, t_counter>::apply(reflection::Types::currentInstalledClass);
                }
                break;

            case o_global_value_SetupStepIndex_Inheritance:
                {
                    reflection::super_classes_adder<t_Ty, t_counter>::apply(reflection::Types::currentInstalledClass);
                }
                break;
            case o_global_value_SetupStepIndex_Reflection:
                {
                    reflection_installer<t_Ty> m_reflection_module_installer;
                    (void)m_reflection_module_installer;
                }
                break;
            case o_global_value_SetupStepIndex_StateChart:
                {
                    statechart_installer<t_Ty> m_statechart_module_installer;
                    (void)m_statechart_module_installer;
                }
                break;
            }
            reflection::Types::currentInstalledClass = saved_class;
            reflection::Types::currentInstalledTemplateSpecialization = saved_template_specialization;
        }
    };

    template<typename t_Ty, int t_counter>
    struct module_installer_helper<t_Ty, t_counter, false, true>
    {
        static void apply(phantom::reflection::Type* a_pType, uint step)
        {
            reflection::Class* saved_class = reflection::Types::currentInstalledClass;
            reflection::TemplateSpecialization* saved_template_specialization = reflection::Types::currentInstalledTemplateSpecialization;
            reflection::Types::currentInstalledClass = a_pType->asClass();
            reflection::Types::currentInstalledTemplateSpecialization = reflection::Types::currentInstalledClass ? reflection::Types::currentInstalledClass->getTemplateSpecialization() : nullptr;
            switch(step)
            {
            case o_global_value_SetupStepIndex_TemplateSignature:
                {
                    reflection::template_specialization_adder<t_Ty, t_counter>::apply(reflection::Types::currentInstalledClass);
                }
                break;

            case o_global_value_SetupStepIndex_Inheritance:
                {
                    reflection::super_classes_adder<t_Ty, t_counter>::apply(reflection::Types::currentInstalledClass);
                }
                break;
            case o_global_value_SetupStepIndex_StateChart:
                {
                    statechart_installer<t_Ty> m_statechart_module_installer;
                    (void)m_statechart_module_installer;
                }
                break;
            }
            reflection::Types::currentInstalledClass = saved_class;
            reflection::Types::currentInstalledTemplateSpecialization = saved_template_specialization;
        }
    };

    template<typename t_Ty, int t_counter>
    struct module_installer_helper<t_Ty, t_counter, true, false>
    {
        static void apply(phantom::reflection::Type* a_pType, uint step)
        {
            reflection::Class* saved_class = reflection::Types::currentInstalledClass;
            reflection::TemplateSpecialization* saved_template_specialization = reflection::Types::currentInstalledTemplateSpecialization;
            reflection::Types::currentInstalledClass = a_pType->asClass();
            reflection::Types::currentInstalledTemplateSpecialization = reflection::Types::currentInstalledClass ? reflection::Types::currentInstalledClass->getTemplateSpecialization() : nullptr;
            switch(step)
            {
            case o_global_value_SetupStepIndex_TemplateSignature:
                {
                    reflection::template_specialization_adder<t_Ty, t_counter>::apply(reflection::Types::currentInstalledClass);
                }
                break;

            case o_global_value_SetupStepIndex_Inheritance:
                {
                    reflection::super_classes_adder<t_Ty, t_counter>::apply(reflection::Types::currentInstalledClass);
                }
                break;
            case o_global_value_SetupStepIndex_Reflection:
                {
                    reflection_installer<t_Ty> m_reflection_module_installer;
                    (void)m_reflection_module_installer;
                }
                break;
            }
            reflection::Types::currentInstalledClass = saved_class;
            reflection::Types::currentInstalledTemplateSpecialization = saved_template_specialization;
        }
    };

    template<typename t_Ty, int t_counter>
    struct module_installer
        : public module_installer_helper<t_Ty, t_counter, has_reflection<t_Ty>::value, has_statechart<t_Ty>::value>
    {
    };

    template<typename t_Ty, int t_counter, bool is_deferred>
    struct dynamic_initializer_module_installer_registrer_helper
    {
        dynamic_initializer_module_installer_registrer_helper()
        {
            Phantom::dynamic_initializer()->setActive(true);
            // Ensure the creation of the meta type
            Phantom::dynamic_initializer()->setAutoRegistrationLocked(true);
            //o_assert(phantom::typeByName(type_name_of<t_Ty>::qualifiedDecoratedName()) == nullptr, "Type with same qualified decorated name already registered");
            
            auto pType = phantom::reflection::detail::type_of_counter<t_Ty, t_counter>::object();
            o_assert(pType, "Type reflection not defined with 'o_classX' or 'o_enumX' in this compilation unit");
            o_assert(pType->getModule() == nullptr, "Type already registered in another module");

            Phantom::dynamic_initializer()->setAutoRegistrationLocked(false);
            /// If you get an error : 'apply' : is not a member of 'phantom::detail::module_installer'
            /// It's probably because you didn't declare a reflection scope (internal or external) for the given t_Ty class
            Phantom::dynamic_initializer()->setActive(false);
        }
    };

    template<typename t_Ty, int t_counter>
    struct dynamic_initializer_module_installer_registrer_helper<t_Ty, t_counter, true> 
    {
        dynamic_initializer_module_installer_registrer_helper()
        {
            Phantom::dynamic_initializer()->setActive(true);
            // Ensure the creation of the meta type
            Phantom::dynamic_initializer()->setAutoRegistrationLocked(true);
            auto pType = phantom::reflection::detail::type_of_counter<t_Ty, t_counter>::object();
            o_assert(pType, "Type reflection not declared in this registration compilation unit");
            o_assert(pType->getModule() == nullptr, "Type already registered in another module");
            Phantom::dynamic_initializer()->registerModule(pType, &phantom::detail::module_installer<t_Ty, t_counter>::apply, setup_steps_mask_of<t_Ty>::value);
            Phantom::dynamic_initializer()->setAutoRegistrationLocked(false);
            /// If you get an error : 'apply' : is not a member of 'phantom::detail::module_installer'
            /// It's probably because you didn't declare a reflection scope (internal or external) for the given t_Ty class
            Phantom::dynamic_initializer()->setActive(false);
        }
    };

    template<typename t_Ty, int t_counter>
    struct dynamic_initializer_module_installer_registrer 
        : public dynamic_initializer_module_installer_registrer_helper<t_Ty, t_counter, (phantom::meta_specifiers<t_Ty>::value & o_deferred) == o_deferred>
    {
    };

    template<typename t_Ty>
    struct scope_registrer
    {
        scope_registrer() 
        { 
            type_of<t_Ty>::object(); 
        }
    };

    template<typename t_Ty, int t_counter, bool is_deferred>
    struct module_installer_registrer_helper
    {
        module_installer_registrer_helper(phantom::reflection::Type* a_pType)
        {
            Phantom::dynamic_initializer()->registerModule(a_pType, &phantom::detail::module_installer<t_Ty, t_counter>::apply, setup_steps_mask_of<t_Ty>::value);
        }
    };

    template<typename t_Ty, int t_counter>
    struct module_installer_registrer_helper<t_Ty, t_counter, true> 
    {
        module_installer_registrer_helper(phantom::reflection::Type* a_pType)
        {
        }
    };

    template<typename t_Ty, int t_counter>
    struct module_installer_registrer 
        : public module_installer_registrer_helper<t_Ty, t_counter, (phantom::meta_specifiers<t_Ty>::value & o_deferred) == o_deferred>
    {
        module_installer_registrer(phantom::reflection::Type* a_pType) : module_installer_registrer_helper(a_pType) {}
    };

    struct o_export dynamic_initializer_template_registrer
    {
        dynamic_initializer_template_registrer(const string& a_strNamespace, const string& a_strName);
    };

}