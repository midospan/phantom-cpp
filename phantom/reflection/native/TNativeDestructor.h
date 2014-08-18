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

#ifndef o_phantom_reflection_native_TNativeDestructor_h__
#define o_phantom_reflection_native_TNativeDestructor_h__



/* ****************** Includes ******************* */
/* **************** Declarations ***************** */

/* *********************************************** */
o_namespace_begin(phantom, reflection, native)

template<typename t_Ty>
class TNativeDestructor : public InstanceMemberFunction
{
    typedef TNativeDestructor<t_Ty> self_type;

public:
    void closure_wrapper() { reinterpret_cast<t_Ty*>(this)->~t_Ty(); }
    TNativeDestructor(const string& a_strName)
        : InstanceMemberFunction(a_strName, o_new(Signature)(typeOf<void>()), (has_virtual_destructor_cascade<t_Ty>::value ? o_virtual : 0) | o_native | o_public)
    {
        if(this->isVirtual()) this->setVirtualTableIndex(phantom::virtualDestructorIndex<t_Ty>());
    }

    virtual void            deleteNow() { o_dynamic_proxy_delete(phantom::reflection::InstanceMemberFunction, phantom::reflection::InstanceMemberFunction::metaType, self_type) this; }

    virtual void*           getClosure() const { return generic_member_func_ptr(&self_type::closure_wrapper); }

    DelegateMemento         getDelegateMemento(void* a_pObject) const
    {
        return DelegateMemento();
    }

    virtual void call(void* a_pObject, void** a_pParams) const
    {
        static_cast<t_Ty*>(a_pObject)->~t_Ty();
    }

    virtual void call(void* a_pObject, void** a_pParams, void* a_pReturnAddress) const
    {
        static_cast<t_Ty*>(a_pObject)->~t_Ty();
    }

    virtual void call(void** a_pParams) const
    {
        static_cast<t_Ty*>(a_pParams[0])->~t_Ty();
    }

    virtual void call(void** a_pParams, void* a_pReturnAddress) const
    {
        static_cast<t_Ty*>(a_pParams[0])->~t_Ty();
    }

    virtual void* getAddress(void* a_pObject, void** a_pParams) const
    {
        return nullptr;
    }

    virtual bool        isAddressable() const { return false; }

};


o_namespace_end(phantom, reflection, native)

#endif // TNativeDestructor_h__
