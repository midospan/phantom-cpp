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

#ifndef util_PolymorphicArray_h__
#define util_PolymorphicArray_h__



/* ****************** Includes ******************* */
#include <phantom/util/Array.h>
/* *********************************************** */
/* The *.classdef.h file must be the last #include */
#include "PolymorphicArray.classdef.h"
/* **************** Declarations ***************** */
o_declare(class, phantom, reflection, PolymorphicArrayClass)
/* *********************************************** */
o_h_begin

class o_export PolymorphicArray : public Array
{
public:
    typedef PolymorphicArray        self_type;
    typedef reflection::PolymorphicArrayClass    meta_type;
    typedef phantom::vector<void*> internal_vector_type;

    o_friend(class, phantom, Phantom)
    enum 
    {
        eNativeFlag_ArrayAutoDestroyContent = 0x00000008,
    };

    enum
    {
        NullIndex = 0xffffffff,
    };

    PolymorphicArray( void ) ;
    PolymorphicArray( reflection::Class* a_pPolymorphicType );
    PolymorphicArray( reflection::Class* a_pPolymorphicType, size_t a_EnsuredCapacity );
    o_destructor ~PolymorphicArray(void);

    void    initialize();

    static reflection::PolymorphicArrayClass* Reflect();

    virtual reflection::Class*  getClass(void) const
    {
        o_check_phantom_setup_step(o_global_value_SetupStepIndex_Inheritance);
        return ____type_reflection; 
    }

    void    setAutoDestroyContent(boolean a_bValue);
    boolean    isAutoDestroyContent() const;

    boolean    accepts(void* a_pObject) const 
    {
        o_check_phantom_installed();
        return acceptsType(phantom::classOf(a_pObject)); 
        
    }
    boolean    acceptsType(reflection::Class* a_pType) const
    {
        return a_pType->isConvertibleTo(getContentType());
    }

    boolean    isEmpty() const { return m_Content.empty(); }

    virtual boolean    isArray() const { return true; }

    boolean    equals(Object* a_pObject) const;

    reflection::Class* getContentType() const;

    o_forceinline void    destroyContent();    
    o_forceinline void    destroyContentCascade();
    o_forceinline void    clear() { m_Content.clear(); }

    o_forceinline void replace(void* a_pOld, void* a_pNew)
    {
        std::replace(m_Content.begin(),m_Content.end(),phantom::baseOf(a_pOld),phantom::baseOf(a_pNew));
    }

    o_forceinline size_t    getIndex( const void* a_pObject )
    {
        size_t i = 0;
        for(;i<getLength();++i)
            if(m_Content[i] == a_pObject) return i;
        return NullIndex;
    }

    o_forceinline void     reserve(size_t a_uiLength) { m_Content.reserve(a_uiLength); }

    o_forceinline boolean     removeFirst(void* a_pObject)
    {
        internal_vector_type::iterator found = std::find(m_Content.begin(), m_Content.end(), a_pObject);
        if(m_Content.end() == found) return false;
        m_Content.erase(found);
        return true;
    }

    o_forceinline boolean     safeRemoveFirst(void* a_pObject) { return removeFirst(phantom::baseOf(a_pObject)); }
    o_forceinline void removeAll( void* a_pObject ) { while(removeFirst(a_pObject)); }

    template<typename t_Ty>
    void    popFront()
    {
        t_Ty* pFront = phantom::polymorphic_cast<t_Ty>(m_Content.front());
        m_Content.erase(m_Content.begin());
        return pFront;
    }

    template<typename t_Ty>
    t_Ty*    popBack()
    {
        t_Ty* pBack = phantom::polymorphic_cast<t_Ty>(m_Content.back());
        m_Content.pop_back();
        return pBack;
    }

    void    addFront(void* a_pObject)
    {
        m_Content.insert(m_Content.begin(), a_pObject);
    }

    void    addBack(void* a_pObject)
    {
        o_assert(accepts(a_pObject));
        m_Content.push_back(baseOf(a_pObject));
    }

    template<typename t_Ty>
    t_Ty*    get(size_t i) const
    {
        o_check_phantom_installed();
        o_assert(i<getLength());
        o_assert(getContentType()->isKindOf(classOf<t_Ty>()));
        return phantom::as<t_Ty*>(m_Content[i]);
    }

    void*        getObject(size_t i) const { return m_Content[i]; }

    o_forceinline void        append(void* a_pValue) { addBack(a_pValue); }

    void        insert( size_t index, void* a_pValue ) { m_Content.insert(m_Content.begin()+index, baseOf(a_pValue)); }

    o_forceinline size_t        getLength() const { return m_Content.size(); }

    virtual size_t        getSize() const { return m_Content.size(); }

    virtual void    getValue(size_t i, void* a_pDest) const 
    {
        *static_cast<void**>(a_pDest) = m_Content[i];
    }
    virtual void    setValue(size_t i, void* a_pSrc) 
    {
        m_Content[i] = *static_cast<void**>(a_pSrc);
    }

    boolean        contains(void* a_pObject) const 
    {
        void* base = phantom::baseOf(a_pObject);
        o_foreach(void* pO, m_Content)
        {
            if(pO == base) return true;
        }
        return false;
    }
    
    o_forceinline void        sort(util::Comparator* a_pComparator)
    {
        std::sort(m_Content.begin(),m_Content.end(),util::Comparator::std_adapter(a_pComparator));
    }
    o_forceinline void        sortReversed(util::Comparator* a_pComparator)
    {
        std::sort(m_Content.begin(),m_Content.end(),util::Comparator::std_reversed_adapter(a_pComparator));
    }

    size_t        copyTo(PolymorphicArray* a_pDest) const;

    void        trim() {m_Content.resize(m_Content.size());}

    void        set(size_t i, void* a_pValue) { o_assert(accepts(a_pValue)); m_Content[i] = phantom::baseOf(a_pValue); }

protected:
    void        initializeLength(size_t a_uiLength);

protected:
    reflection::PolymorphicArrayClass*    ____type_reflection;
    internal_vector_type            m_Content;

};

o_namespace_end(phantom, util)


#else // util_PolymorphicArray_h__
#include "PolymorphicArray.classdef.h"
#endif
