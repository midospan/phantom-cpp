
o_namespace_begin(phantom, detail)

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
//         o_assert(phantom::currentModule(), "no module pushed for the current registered type") ;
//         o_assert(pType->getModule() == nullptr);
//         phantom::currentModule()->addElement(pType);
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
    : public proxy_of<t_Ty>::type::enclosed_reflection::o_NESTED_TEMPLATE enclosed_statechart<t_Ty>
{
    statechart_installer_helper()
    {
        typeOf<t_Ty>()->setStateMachine(phantom::reflection::native::TNativeStateMachine<t_Ty>::Instance());
    }
};

template<typename t_Ty>
struct statechart_installer : public statechart_installer_helper<t_Ty, has_statechart<t_Ty>::value>
{

};

template<typename t_Ty, bool t_has_reflection, bool t_has_statechart>
struct module_installer_helper
{
};

template<typename t_Ty>
struct module_installer_helper<t_Ty, true, true>
{
    static void apply(phantom::reflection::Type* a_pType, uint step)
    {
        reflection::native::pushScope(a_pType);
        reflection::native::pushModifiers((!is_structure<t_Ty>::value) * o_private_access);
        switch(step)
        {
        case o_global_value_SetupStepIndex_TemplateSignature:
            {
                reflection::template_specialization_adder<t_Ty>::apply(a_pType->asClassType());
            }
            break;

        case o_global_value_SetupStepIndex_VTable:
            {
                reflection::vtable_adder<t_Ty>::apply(a_pType->asClass());
            }
            break;

        case o_global_value_SetupStepIndex_Inheritance:
            {
                reflection::base_classes_adder<t_Ty>::apply(a_pType->asClass());
            }
            break;
        case o_global_value_SetupStepIndex_Reflection:
            {
                reflection_installer<t_Ty> m_reflection_module_installer;
                (void)m_reflection_module_installer;
                a_pType->setFinalized();
            }
            break;
        case o_global_value_SetupStepIndex_StateChart:
            {
                statechart_installer<t_Ty> m_statechart_module_installer;
                (void)m_statechart_module_installer;
            }
            break;
        }
        reflection::native::popScope();
        reflection::native::popModifiers();
    }
};

template<typename t_Ty>
struct module_installer_helper<t_Ty, false, true>
{
    static void apply(phantom::reflection::Type* a_pType, uint step)
    {
        reflection::native::pushScope(a_pType);
        reflection::native::pushModifiers((!is_structure<t_Ty>::value) * o_private_access);
        switch(step)
        {
        case o_global_value_SetupStepIndex_TemplateSignature:
            {
                reflection::template_specialization_adder<t_Ty>::apply(a_pType->asClassType());
            }
            break;

        case o_global_value_SetupStepIndex_VTable:
            {
                reflection::vtable_adder<t_Ty>::apply(a_pType->asClass());
            }
            break;

        case o_global_value_SetupStepIndex_Inheritance:
            {
                reflection::base_classes_adder<t_Ty>::apply(a_pType->asClass());
            }
            break;
        case o_global_value_SetupStepIndex_StateChart:
            {
                statechart_installer<t_Ty> m_statechart_module_installer;
                (void)m_statechart_module_installer;
            }
            break;
        }
        reflection::native::popScope();
        reflection::native::popModifiers();
    }
};

template<typename t_Ty>
struct module_installer_helper<t_Ty, true, false>
{
    static void apply(phantom::reflection::Type* a_pType, uint step)
    {
        reflection::native::pushScope(a_pType);
        reflection::native::pushModifiers((!is_structure<t_Ty>::value) * o_private_access);
        switch(step)
        {
        case o_global_value_SetupStepIndex_TemplateSignature:
            {
                reflection::template_specialization_adder<t_Ty>::apply(a_pType->asClassType());
            }
            break;

        case o_global_value_SetupStepIndex_VTable:
            {
                reflection::vtable_adder<t_Ty>::apply(a_pType->asClass());
            }
            break;

        case o_global_value_SetupStepIndex_Inheritance:
            {
                reflection::base_classes_adder<t_Ty>::apply(a_pType->asClass());
            }
            break;
        case o_global_value_SetupStepIndex_Reflection:
            {
                reflection_installer<t_Ty> m_reflection_module_installer;
                (void)m_reflection_module_installer;
                a_pType->setFinalized();
            }
            break;
        }
        reflection::native::popScope();
        reflection::native::popModifiers();
    }
};

template<typename t_Ty>
struct module_installer
    : public module_installer_helper<t_Ty, has_reflection<t_Ty>::value, has_statechart<t_Ty>::value>
{
};

template<typename t_Ty, bool is_deferred>
struct dynamic_initializer_module_installer_registrer_helper
{
    dynamic_initializer_module_installer_registrer_helper(const char* a_strFile)
    {
        dynamic_initializer()->setActive(true);
        // Ensure the creation of the meta type
        dynamic_initializer()->setAutoRegistrationLocked(true);
        //o_assert(phantom::typeByName(type_name_of<t_Ty>::qualifiedDecoratedName()) == nullptr, "Type with same qualified decorated name already registered");

        dynamic_initializer()->pushFile(a_strFile);
        auto pType = phantom::reflection::type_of<t_Ty>::object();
        dynamic_initializer()->popFile(a_strFile);
        o_assert(pType, "Type reflection not defined with 'o_classX' or 'o_enumX' in this compilation unit");
        o_assert(pType->getModule() == nullptr, "Type already registered in another module");

        dynamic_initializer()->setAutoRegistrationLocked(false);
        /// If you get an error : 'apply' : is not a member of 'phantom::detail::module_installer'
        /// It's probably because you didn't declare a reflection scope (internal or external) for the given t_Ty class
        dynamic_initializer()->setActive(false);
    }
};

template<typename t_Ty>
struct dynamic_initializer_module_installer_registrer_helper<t_Ty, true>
{
    dynamic_initializer_module_installer_registrer_helper(const char* a_strFile)
    {
        dynamic_initializer()->setActive(true);
        // Ensure the creation of the meta type
        dynamic_initializer()->setAutoRegistrationLocked(true);
        auto pType = phantom::reflection::type_of<t_Ty>::object();
        o_assert(pType, "Type reflection not declared in this registration compilation unit");
        o_assert(pType->getModule() == nullptr, "Type already registered in another module");
        dynamic_initializer()->pushFile(a_strFile);
        dynamic_initializer()->registerModule(pType, &phantom::detail::module_installer<t_Ty>::apply, setup_steps_mask_of<t_Ty>::value);
        dynamic_initializer()->popFile(a_strFile);
        dynamic_initializer()->setAutoRegistrationLocked(false);
        /// If you get an error : 'apply' : is not a member of 'phantom::detail::module_installer'
        /// It's probably because you didn't declare a reflection scope (internal or external) for the given t_Ty class
        dynamic_initializer()->setActive(false);
    }
};

template<typename t_Ty>
struct dynamic_initializer_module_installer_registrer
    : public dynamic_initializer_module_installer_registrer_helper<t_Ty, (phantom::meta_specifiers<t_Ty>::value & o_deferred) == o_deferred>
{
    dynamic_initializer_module_installer_registrer(const char* a_strFile)
        : dynamic_initializer_module_installer_registrer_helper<t_Ty, (phantom::meta_specifiers<t_Ty>::value & o_deferred) == o_deferred>(a_strFile) {}
};

template<typename t_Ty, bool is_deferred>
struct module_installer_registrer_helper
{
    module_installer_registrer_helper(phantom::reflection::Type* a_pType)
    {
        dynamic_initializer()->registerModule(a_pType, &phantom::detail::module_installer<t_Ty>::apply, setup_steps_mask_of<t_Ty>::value);
    }
};

template<typename t_Ty>
struct module_installer_registrer_helper<t_Ty, true>
{
    module_installer_registrer_helper(phantom::reflection::Type* a_pType)
    {
    }
};

template<typename t_Ty>
struct module_installer_registrer
    : public module_installer_registrer_helper<t_Ty, (phantom::meta_specifiers<t_Ty>::value & o_deferred) == o_deferred>
{
    module_installer_registrer(phantom::reflection::Type* a_pType) : module_installer_registrer_helper<t_Ty, (phantom::meta_specifiers<t_Ty>::value & o_deferred) == o_deferred>(a_pType) {}
};

struct o_export dynamic_initializer_template_registrer
{
    dynamic_initializer_template_registrer(const string& a_strNamespace, const string& a_strTemplateTypes, const string& a_strTemplateParams, const string& a_strName, const char* a_strFile);
};

o_namespace_end(phantom, detail)
