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

#ifndef o_phantom_reflection_native_TNativeCollection_h__
#define o_phantom_reflection_native_TNativeCollection_h__



/* ****************** Includes ******************* */

/* **************** Declarations ***************** */

/* *********************************************** */
using namespace fastdelegate;

o_namespace_begin(phantom, reflection, native)

template<typename t_Ty, typename t_ContentType>
class TNativeCollection : public Collection
{
    typedef o_NESTED_TYPE boost::remove_reference<t_ContentType>::type      t_ContentTypeNoRef;
    typedef o_NESTED_TYPE boost::remove_const<t_ContentTypeNoRef>::type     t_ContentTypeNoConstNoRef;
    
public:
    typedef TNativeCollection<t_Ty, t_ContentType> self_type;
    typedef void (t_Ty::*adder)(t_ContentType);
    typedef void (t_Ty::*mover)(t_ContentType, size_t);
    typedef void (t_Ty::*remover)(t_ContentType);
    typedef void (t_Ty::*setter)(size_t, t_ContentType);
    typedef t_ContentType (t_Ty::*getter)(size_t) const;
    typedef size_t (t_Ty::*size_getter)() const;
public:
    TNativeCollection(const string& a_strName
        , Type* a_pElementType
        , adder a_adder
        , remover a_remover
        , mover a_mover
        , setter a_setter
        , getter a_getter
        , size_getter a_size_getter
        , bitfield a_uiModifiers = 0)
     : Collection(a_strName, a_pElementType, a_uiModifiers)
     , m_adder(a_adder)
     , m_remover(a_remover)
     , m_mover(a_mover)
     , m_setter(a_setter)
     , m_getter(a_getter)
     , m_size_getter(a_size_getter)
    {

    }
    virtual boolean      isNative() const { return true; }

    virtual void        addElement( void* a_pObject, void const* src ) const
    {
        (reinterpret_cast<t_Ty*>(a_pObject)->*m_adder)(*((t_ContentTypeNoConstNoRef*)src));
    }
    virtual void        removeElement( void* a_pObject, void const* src ) const
    {
        (reinterpret_cast<t_Ty*>(a_pObject)->*m_remover)(*((t_ContentTypeNoConstNoRef*)src));
    }
    virtual void        moveElement( void* a_pObject, void const* src, size_t a_uiIndex ) const
    {
        (reinterpret_cast<t_Ty*>(a_pObject)->*m_mover)(*((t_ContentTypeNoConstNoRef*)src), a_uiIndex);
    }
    virtual void        setElement(void* a_pObject, size_t a_uiIndex, void const* src) const
    {
        (reinterpret_cast<t_Ty*>(a_pObject)->*m_setter)(a_uiIndex, *((t_ContentTypeNoConstNoRef*)src) );
    }

    virtual void        deleteNow()
    {
        o_delete(self_type) this;
    }

    virtual void        getElement(void const* a_pObject, size_t a_uiIndex, void* dest) const 
    {
        *((t_ContentTypeNoConstNoRef*)dest) = (reinterpret_cast<t_Ty const*>(a_pObject)->*m_getter)(a_uiIndex);
    }

    virtual size_t      getSize(void const* a_pObject) const 
    {
        return (reinterpret_cast<t_Ty const*>(a_pObject)->*m_size_getter)();
    }

protected:
    adder       m_adder;
    remover     m_remover;
    mover       m_mover;
    setter      m_setter;
    getter      m_getter;
    size_getter m_size_getter;
};

/*template<typename t_Ty, typename t_ContentType>
class TNativeCollection<t_Ty, t_ContentType const>
    : public TNativeCollection<t_Ty,t_ContentType>
{
public:
    typedef TNativeCollection<t_Ty, t_ContentType const> self_type;
    typedef t_ContentType const (t_Ty::*member_field_pointer);

public:
    TNativeCollection(const string& a_strName, Type* a_pContentType
        , member_field_pointer a_member_field_pointer, bitfield a_uiModifiers = 0)
        : TNativeCollection<t_Ty,t_ContentType>(a_strName, a_pContentType

        // We manage const-type attributes like no-const-type attributes : we break the const qualifier to be able to force write with "setValue"
        , const_cast<typename TNativeCollection<t_Ty,t_ContentType>::member_field_pointer>(a_member_field_pointer)
        , a_uiModifiers)
    {}

};*/

o_namespace_end(phantom, reflection, native)

o_traits_specialize_all_super_traitNTTS(
(phantom,reflection,native)
, (typename, typename)
, (t_Ty, t_ContentType)
, TNativeCollection
, (Collection)
)

#endif // TNativeCollection_h__
