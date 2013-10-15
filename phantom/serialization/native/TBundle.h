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

#ifndef o_serialization_native_TBundle_h__
#define o_serialization_native_TBundle_h__
// #pragma message("Including "__FILE__)


/* ****************** Includes ******************* */

/* **************** Declarations ***************** */

/* *********************************************** */

o_namespace_begin(phantom, serialization, native)
    
template<typename t_Ty>
class TBundleBase : public Bundle
{
public:
    TBundleBase(BundleNode* a_pNode) : Bundle(a_pNode, typeOf<t_Ty>()) {}
        
    
protected:
    size_t              m_sSize;
};

template<typename t_Ty, int t_super_class_count> 
class TCascadeBundle;

template<typename t_Ty>
class TBundle : public TCascadeBundle<t_Ty, super_class_count_of<t_Ty>::value>
{
public:
    TBundle(BundleNode* node) 
        : TCascadeBundle<t_Ty, super_class_count_of<t_Ty>::value>(node) 
    {

    }
};

template<typename t_Ty>
class TCascadeBundle<t_Ty, 0> // 0 => root class
    : public TBundleBase<t_Ty> 
{
public:
    TCascadeBundle<t_Ty, 0>(BundleNode* a_pNode) : TBundleBase<t_Ty>(a_pNode) {}

    virtual void add(void* a_pInstance)
    {
        addCascade(static_cast<t_Ty*>(a_pInstance));
    }
    virtual void add(void* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize)
    {
        addCascade(static_cast<t_Ty*>(a_pInstance), a_uiCount, a_uiChunkSectionSize);
    }

    void addCascade(t_Ty* a_pInstance) 
    {
        Bundle::add(a_pInstance);
    }
    void addCascade(t_Ty* a_pChunkAddress, size_t a_uiCount, size_t a_uiChunkSectionSize) 
    {
        Bundle::add(a_pChunkAddress, a_uiCount, a_uiChunkSectionSize);
    }

};

template<typename t_Ty>
class TCascadeBundle<t_Ty, 1> : public TBundleBase<t_Ty>
{
public:
    typedef o_traits_t_Ty_super_class(0) bundled_super_class_0;
    TCascadeBundle<t_Ty, 1>(BundleNode* a_pNode)
        : TBundleBase<t_Ty>(a_pNode)
        , m_pSuperBundle0(a_pNode->bundle<bundled_super_class_0>()) {

    }
    virtual void add(void* a_pInstance)
    {
        addCascade(static_cast<t_Ty*>(a_pInstance));
    }
    virtual void add(void* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize)
    {
        addCascade(static_cast<t_Ty*>(a_pInstance), a_uiCount, a_uiChunkSectionSize);
    }

    void addCascade(t_Ty* a_pObject)
    {
        Bundle::add(a_pObject);
        m_pSuperBundle0->addCascade(a_pObject);
    }
    void addCascade(t_Ty* a_pChunkAddress, size_t a_uiCount, size_t a_uiChunkSectionSize) 
    {
        Bundle::add(a_pChunkAddress, a_uiCount, a_uiChunkSectionSize);
        m_pSuperBundle0->addCascade(a_pChunkAddress, a_uiCount, a_uiChunkSectionSize);
    }

protected:
    TBundle<bundled_super_class_0>*    m_pSuperBundle0;
};

template<typename t_Ty>
class TCascadeBundle<t_Ty, 2> : public TBundleBase<t_Ty>
{
public:
    typedef o_traits_t_Ty_super_class(0) bundled_super_class_0;
    typedef o_traits_t_Ty_super_class(1) bundled_super_class_1;

    TCascadeBundle<t_Ty, 2>(BundleNode* a_pNode)
        : TBundleBase<t_Ty>(a_pNode)
        , m_pSuperBundle0(a_pNode->bundle<bundled_super_class_0>())
        , m_pSuperBundle1(a_pNode->bundle<bundled_super_class_1>())
    {
        
    }
    virtual void add(void* a_pInstance)
    {
        addCascade(static_cast<t_Ty*>(a_pInstance));
    }
    virtual void add(void* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize)
    {
        addCascade(static_cast<t_Ty*>(a_pInstance), a_uiCount, a_uiChunkSectionSize);
    }
    void addCascade(t_Ty* a_pObject)
    {
        Bundle::add(a_pObject);
        m_pSuperBundle0->addCascade(a_pObject);
        m_pSuperBundle1->addCascade(a_pObject);
    }
    void addCascade(t_Ty* a_pChunkAddress, size_t a_uiCount, size_t a_uiChunkSectionSize) 
    {
        Bundle::add(a_pChunkAddress, a_uiCount, a_uiChunkSectionSize);
        m_pSuperBundle0->addCascade(a_pChunkAddress, a_uiCount, a_uiChunkSectionSize);
        m_pSuperBundle1->addCascade(a_pChunkAddress, a_uiCount, a_uiChunkSectionSize);
    }

protected:
    TBundle<bundled_super_class_0>*    m_pSuperBundle0;
    TBundle<bundled_super_class_1>*    m_pSuperBundle1;
};

template<typename t_Ty>
class TCascadeBundle<t_Ty, 3> : public TBundleBase<t_Ty>
{
public:
    typedef o_traits_t_Ty_super_class(0) bundled_super_class_0;
    typedef o_traits_t_Ty_super_class(1) bundled_super_class_1;
    typedef o_traits_t_Ty_super_class(2) bundled_super_class_2;

    TCascadeBundle<t_Ty, 3>(BundleNode* a_pNode)
        : TBundleBase<t_Ty>(a_pNode)
        , m_pSuperBundle0(a_pNode->bundle<bundled_super_class_0>())
        , m_pSuperBundle1(a_pNode->bundle<bundled_super_class_1>())
        , m_pSuperBundle2(a_pNode->bundle<bundled_super_class_2>())
    {

    }
    virtual void add(void* a_pInstance)
    {
        addCascade(static_cast<t_Ty*>(a_pInstance));
    }
    virtual void add(void* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize)
    {
        addCascade(static_cast<t_Ty*>(a_pInstance), a_uiCount, a_uiChunkSectionSize);
    }
    void addCascade(t_Ty* a_pObject)
    {
        Bundle::add(a_pObject);
        m_pSuperBundle0->addCascade(a_pObject);
        m_pSuperBundle1->addCascade(a_pObject);
        m_pSuperBundle2->addCascade(a_pObject);
    }
    void addCascade(t_Ty* a_pChunkAddress, size_t a_uiCount, size_t a_uiChunkSectionSize) 
    {
        Bundle::add(a_pChunkAddress, a_uiCount, a_uiChunkSectionSize);
        m_pSuperBundle0->addCascade(a_pChunkAddress, a_uiCount, a_uiChunkSectionSize);
        m_pSuperBundle1->addCascade(a_pChunkAddress, a_uiCount, a_uiChunkSectionSize);
        m_pSuperBundle2->addCascade(a_pChunkAddress, a_uiCount, a_uiChunkSectionSize);
    }

protected:
    TBundle<bundled_super_class_0>*    m_pSuperBundle0;
    TBundle<bundled_super_class_1>*    m_pSuperBundle1;
    TBundle<bundled_super_class_2>*    m_pSuperBundle2;
};

template<typename t_Ty>
class TCascadeBundle<t_Ty, 4> : public TBundleBase<t_Ty>
{
public:
    typedef o_traits_t_Ty_super_class(0) bundled_super_class_0;
    typedef o_traits_t_Ty_super_class(1) bundled_super_class_1;
    typedef o_traits_t_Ty_super_class(2) bundled_super_class_2;
    typedef o_traits_t_Ty_super_class(3) bundled_super_class_3;

    TCascadeBundle<t_Ty, 4>(BundleNode* a_pNode)
        : TBundleBase<t_Ty>(a_pNode)
        , m_pSuperBundle0(a_pNode->bundle<bundled_super_class_0>())
        , m_pSuperBundle1(a_pNode->bundle<bundled_super_class_1>())
        , m_pSuperBundle2(a_pNode->bundle<bundled_super_class_2>())
        , m_pSuperBundle3(a_pNode->bundle<bundled_super_class_3>())
    {

    }
    virtual void add(void* a_pInstance)
    {
        addCascade(static_cast<t_Ty*>(a_pInstance));
    }
    virtual void add(void* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize)
    {
        addCascade(static_cast<t_Ty*>(a_pInstance), a_uiCount, a_uiChunkSectionSize);
    }
    void addCascade(t_Ty* a_pObject)
    {
        Bundle::add(a_pObject);
        m_pSuperBundle0->addCascade(a_pObject);
        m_pSuperBundle1->addCascade(a_pObject);
        m_pSuperBundle2->addCascade(a_pObject);
        m_pSuperBundle3->addCascade(a_pObject);
    }
    void addCascade(t_Ty* a_pChunkAddress, size_t a_uiCount, size_t a_uiChunkSectionSize) 
    {
        Bundle::add(a_pChunkAddress, a_uiCount, a_uiChunkSectionSize);
        m_pSuperBundle0->addCascade(a_pChunkAddress, a_uiCount, a_uiChunkSectionSize);
        m_pSuperBundle1->addCascade(a_pChunkAddress, a_uiCount, a_uiChunkSectionSize);
        m_pSuperBundle2->addCascade(a_pChunkAddress, a_uiCount, a_uiChunkSectionSize);
        m_pSuperBundle3->addCascade(a_pChunkAddress, a_uiCount, a_uiChunkSectionSize);
    }

protected:
    TBundle<bundled_super_class_0>*    m_pSuperBundle0;
    TBundle<bundled_super_class_1>*    m_pSuperBundle1;
    TBundle<bundled_super_class_2>*    m_pSuperBundle2;
    TBundle<bundled_super_class_3>*    m_pSuperBundle3;
};

template<typename t_Ty>
class TCascadeBundle<t_Ty, 5> : public TBundleBase<t_Ty>
{
public:
    typedef o_traits_t_Ty_super_class(0) bundled_super_class_0;
    typedef o_traits_t_Ty_super_class(1) bundled_super_class_1;
    typedef o_traits_t_Ty_super_class(2) bundled_super_class_2;
    typedef o_traits_t_Ty_super_class(3) bundled_super_class_3;
    typedef o_traits_t_Ty_super_class(4) bundled_super_class_4;

    TCascadeBundle<t_Ty, 5>(BundleNode* a_pNode)
        : TBundleBase<t_Ty>(a_pNode)
        , m_pSuperBundle0(a_pNode->bundle<bundled_super_class_0>())
        , m_pSuperBundle1(a_pNode->bundle<bundled_super_class_1>())
        , m_pSuperBundle2(a_pNode->bundle<bundled_super_class_2>())
        , m_pSuperBundle3(a_pNode->bundle<bundled_super_class_3>())
        , m_pSuperBundle4(a_pNode->bundle<bundled_super_class_4>())
    {

    }
    virtual void add(void* a_pInstance)
    {
        addCascade(static_cast<t_Ty*>(a_pInstance));
    }
    virtual void add(void* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize)
    {
        addCascade(static_cast<t_Ty*>(a_pInstance), a_uiCount, a_uiChunkSectionSize);
    }
    void addCascade(t_Ty* a_pObject)
    {
        Bundle::add(a_pObject);
        m_pSuperBundle0->addCascade(a_pObject);
        m_pSuperBundle1->addCascade(a_pObject);
        m_pSuperBundle2->addCascade(a_pObject);
        m_pSuperBundle3->addCascade(a_pObject);
        m_pSuperBundle4->addCascade(a_pObject);
    }
    void addCascade(t_Ty* a_pChunkAddress, size_t a_uiCount, size_t a_uiChunkSectionSize) 
    {
        Bundle::add(a_pChunkAddress, a_uiCount, a_uiChunkSectionSize);
        m_pSuperBundle0->addCascade(a_pChunkAddress, a_uiCount, a_uiChunkSectionSize);
        m_pSuperBundle1->addCascade(a_pChunkAddress, a_uiCount, a_uiChunkSectionSize);
        m_pSuperBundle2->addCascade(a_pChunkAddress, a_uiCount, a_uiChunkSectionSize);
        m_pSuperBundle3->addCascade(a_pChunkAddress, a_uiCount, a_uiChunkSectionSize);
        m_pSuperBundle4->addCascade(a_pChunkAddress, a_uiCount, a_uiChunkSectionSize);
    }

protected:
    TBundle<bundled_super_class_0>*    m_pSuperBundle0;
    TBundle<bundled_super_class_1>*    m_pSuperBundle1;
    TBundle<bundled_super_class_2>*    m_pSuperBundle2;
    TBundle<bundled_super_class_3>*    m_pSuperBundle3;
    TBundle<bundled_super_class_4>*    m_pSuperBundle4;
};


o_namespace_end(phantom, serialization, native)

o_traits_specialize_all_super_traitNTTS(
    (phantom,serialization,native)
    ,(typename)
    ,(t_Ty)
    ,TBundleBase
    ,(Bundle)
)

o_traits_specialize_all_super_traitNTTS(
    (phantom,serialization,native)
    ,(typename,int)
    ,(t_Ty,t_id)
    ,TCascadeBundle
    ,(TBundleBase<t_Ty>)
)

o_traits_specialize_all_super_traitNTTS(
    (phantom,serialization,native)
    ,(typename)
    ,(t_Ty)
    ,TBundle
    ,(TCascadeBundle<t_Ty, super_class_count_of<t_Ty>::value>)
)

#endif // o_serialization_native_TBundle_h__

