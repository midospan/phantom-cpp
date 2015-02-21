#pragma once 


o_namespace_begin(phantom, reflection, native)

template<typename t_Ty, typename t_PropertyValueType>
class DynamicNativePropertySignalProvider
{
public:
    static Signal* CreateSignal(const char* a_strName, const char* a_strPropertyValueTypeName, signal_t (t_Ty::*signal_pointer)(t_PropertyValueType), connection::slot::list (t_Ty::*signal_slot_list_pointer))
    {
        return o_dynamic_proxy_new(TNativeSignal<t_Ty, signal_t(t_PropertyValueType)>)( a_strName
            , string("phantom::signal_t(") + a_strPropertyValueTypeName + ")"
            , signal_pointer
            , signal_slot_list_pointer
            , o_protected_access);
    }
    static Signal* CreateSignal(const char* a_strName, const char* a_strPropertyValueTypeName, signal_t (t_Ty::*signal_pointer)(), connection::slot::list (t_Ty::*signal_slot_list_pointer))
    {
        return o_dynamic_proxy_new(TNativeSignal<t_Ty, signal_t()>)( a_strName
            , "phantom::signal_t()"
            , signal_pointer
            , signal_slot_list_pointer
            , o_protected_access);
    }
    template<typename t_ProtectedHelper>
    static Signal* CreateSignal(const char* a_strName, const char* a_strPropertyValueTypeName, int (t_ProtectedHelper::*a_iNoSignal), int (t_ProtectedHelper::*a_iNoSlotList))
    {
        return nullptr;
    }
};

o_namespace_end(phantom, reflection, native)