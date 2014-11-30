#pragma once 


o_namespace_begin(phantom, reflection, native)

template<typename t_Ty, typename t_PropertyValueType>
class TNativePropertySignalProvider
{
    typedef typename proxy_of<t_Ty>::type proxy_type;
public:
    static Signal* CreateSignal(const char* a_strName, const char* a_strPropertyValueTypeName, signal_t (t_Ty::*signal_pointer)(t_PropertyValueType) const, connection::slot::list (t_Ty::*signal_slot_list_pointer))
    {
        return o_dynamic_proxy_new(TNativeSignal<t_Ty, signal_t(t_PropertyValueType)>)( a_strName
            , TNativeSignatureProvider<phantom::signal_t(t_PropertyValueType) >::CreateSignature()
            , signal_pointer
            , signal_slot_list_pointer
            , o_protected_access);
    }
    static Signal* CreateSignal(const char* a_strName, const char* a_strPropertyValueTypeName, signal_t (t_Ty::*signal_pointer)() const, connection::slot::list (t_Ty::*signal_slot_list_pointer))
    {
        return o_dynamic_proxy_new(TNativeSignal<t_Ty, signal_t()>)( a_strName
            , TNativeSignatureProvider<phantom::signal_t() >::CreateSignature()
            , signal_pointer
            , signal_slot_list_pointer
            , o_protected_access);
    }
    static Signal* CreateSignal(const char* a_strPropertyValueTypeName, const char* a_strName, int (proxy_type::*a_iNoSignal), int (proxy_type::*a_iNoSlotList))
    {
        return nullptr;
    }
};


o_namespace_end(phantom, reflection, native)