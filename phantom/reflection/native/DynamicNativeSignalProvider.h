#pragma once 


o_namespace_begin(phantom, reflection, native)

template<typename t_Ty, typename t_PropertyValueType>
class DynamicNativePropertySignalProvider
{
    typedef typename proxy_of<t_Ty>::type proxy_type;
public:
    static Signal* CreateSignal(const char* a_strName, const char* a_strPropertyValueTypeName, TemplateSpecialization* a_pTemplateSpecialization, LanguageElement* a_pScope, signal_t (t_Ty::*signal_pointer)(t_PropertyValueType) const, connection::slot::list (t_Ty::*signal_slot_list_pointer))
    {
        return o_dynamic_proxy_new(phantom::reflection::Signal, phantom::reflection::Signal::metaType, TNativeSignal<t_Ty, signal_t(t_PropertyValueType)>)( a_strName
            , phantom::reflection::Signature::Create(
            (string("phantom::signal_t(") + a_strPropertyValueTypeName + ")").c_str()
            , a_pTemplateSpecialization
            , a_pScope
            )
            , signal_pointer
            , signal_slot_list_pointer
            , o_protected);
    }
    static Signal* CreateSignal(const char* a_strName, const char* a_strPropertyValueTypeName, TemplateSpecialization* a_pTemplateSpecialization, LanguageElement* a_pScope, signal_t (t_Ty::*signal_pointer)() const, connection::slot::list (t_Ty::*signal_slot_list_pointer))
    {
        return o_dynamic_proxy_new(phantom::reflection::Signal, phantom::reflection::Signal::metaType, TNativeSignal<t_Ty, signal_t()>)( a_strName
            , phantom::reflection::Signature::Create(
            "phantom::signal_t()"
            , a_pTemplateSpecialization
            , a_pScope
            )
            , signal_pointer
            , signal_slot_list_pointer
            , o_protected);
    }
    static Signal* CreateSignal(const char* a_strName, const char* a_strPropertyValueTypeName, TemplateSpecialization* a_pTemplateSpecialization, LanguageElement* a_pScope, int (proxy_type::*a_iNoSignal), int (proxy_type::*a_iNoSlotList))
    {
        return nullptr;
    }
};

o_namespace_end(phantom, reflection, native)