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

#ifndef o_phantom_reflection_native_TNativeConstructor_h__
#define o_phantom_reflection_native_TNativeConstructor_h__



/* ****************** Includes ******************* */
#include "Constructor.h"
/* *********************************************** */

o_h_begin

/* ************* t_Ty Declarations ************** */

/* *********************************************** */
template<typename _Signature>
class TNativeConstructor;


template<typename t_Ty>
class TNativeConstructor<t_Ty()> : public Constructor
{
public:
    typedef TNativeConstructor<t_Ty()>    self_type;
    TNativeConstructor(){}
    TNativeConstructor(const string& a_strName, Signature* a_pSignature, bitfield a_Modifiers = 0)
        : Constructor(a_strName, a_pSignature, a_Modifiers)
    {

    }
    virtual boolean      isNative() const { return true; }

    virtual void            deleteNow() { allocator<TNativeConstructor<t_Ty()>::instance::deallocate(this); }

    virtual void            construct(void* a_pAddress, argument::list* a_pParams)
    {
        new (a_pAddress) t_Ty();
    }
    virtual void            construct(void* a_pAddress, void** a_pParams)
    {
        new (a_pAddress) t_Ty();
    }
    virtual void            destroy(void* a_pAddress)
    {
        static_cast<t_Ty*>(a_pAddress)->~t_Ty();
    }
    virtual void            construct(void* a_pAddress, argument::list* a_pParams, size_t a_uiCount)
    {
        while(a_uiCount--)
        {    
            new (static_cast<t_Ty*>(a_pAddress)++) t_Ty();
        }
    }
    virtual void            construct(void* a_pAddress, void** a_pParams, size_t a_uiCount)
    {
        while(a_uiCount--)
        {    
            new (static_cast<t_Ty*>(a_pAddress)++) t_Ty();
        }
    }
    virtual void            destroy(void* a_pAddress, size_t a_uiCount)
    {
        while(a_uiCount--)
        {
            (static_cast<t_Ty*>(a_pAddress)++)->~t_Ty();
        }
    }

};

template<typename t_Ty, typename t_Param0>
class TNativeConstructor<t_Ty(t_Param0)> : public Constructor
{
public:
    typedef TNativeConstructor<t_Ty(t_Param0)> self_type;

    TNativeConstructor(){}
    TNativeConstructor(const string& a_strName, Signature* a_pSignature, bitfield a_Modifiers = 0)
        : Constructor(a_strName, a_pSignature, a_Modifiers)
    {
    }
    virtual boolean         isNative() const { return true; }
    virtual void            deleteNow() { allocator<TNativeConstructor<t_Ty(t_Param0)>::instance::deallocate(this); }
    
    virtual void            construct(void* a_pAddress, argument::list* a_pParams)
    {
        new (a_pAddress) t_Ty(static_cast<argument::list_1<t_Param0>*>(a_pParams)->p0);
    }
    virtual void            construct(void* a_pAddress, void** a_pParams)
    {
        new (a_pAddress) t_Ty(*static_cast<t_Param0*>(a_pParams[0]));
    }
    virtual void            destroy(void* a_pObject)
    {
        static_cast<t_Ty*>(a_pObject)->~t_Ty();
    }
    virtual void            construct(void* a_pAddress, argument::list* a_pParams, size_t a_uiCount)
    {
        while(a_uiCount--)
        {    
            new (static_cast<t_Ty*>(a_pAddress)++) t_Ty(static_cast<argument::list_1<t_Param0>*>(a_pParams)->p0);
        }
    }
    virtual void            construct(void* a_pAddress, void** a_pParams, size_t a_uiCount)
    {
        while(a_uiCount--)
        {    
            new (static_cast<t_Ty*>(a_pAddress)++) t_Ty(*static_cast<t_Param0*>(a_pParams[0]));
        }
    }
    virtual void            destroy(void* a_pAddress, size_t a_uiCount)
    {
        while(a_uiCount--)
        {
            (static_cast<t_Ty*>(a_pAddress)++)->~t_Ty();
        }
    }
};


template<typename t_Ty, typename t_Param0, typename t_Param1>
class TNativeConstructor<t_Ty(t_Param0,t_Param1)> : public Constructor
{
public:
    typedef TNativeConstructor<t_Ty(t_Param0,t_Param1)> self_type;

    TNativeConstructor(){}
    TNativeConstructor(const string& a_strName, Signature* a_pSignature, bitfield a_Modifiers = 0)
        : Constructor(a_strName, a_pSignature, a_Modifiers)
    {
    }
    virtual boolean      isNative() const { return true; }
    virtual void            deleteNow() { allocator<TNativeConstructor<t_Ty(t_Param0,t_Param1)>::instance::deallocate(this); }

    virtual void            construct(void* a_pAddress, argument::list* a_pParams)
    {
        new (a_pAddress) t_Ty(static_cast<argument::list_2<t_Param0,t_Param1>*>(a_pParams)->p0
                                , static_cast<argument::list_2<t_Param0,t_Param1>*>(a_pParams)->p1);
    }
    virtual void            construct(void* a_pAddress, void** a_pParams)
    {
        new (a_pAddress) t_Ty(*static_cast<t_Param0*>(a_pParams[0])
                                , *static_cast<t_Param1*>(a_pParams[1]));
    }
    virtual void            destroy(void* a_pObject)
    {
        static_cast<t_Ty*>(a_pObject)->~t_Ty();
    }
    virtual void            construct(void* a_pAddress, argument::list* a_pParams, size_t a_uiCount)
    {
        while(a_uiCount--)
        {    
            new (static_cast<t_Ty*>(a_pAddress)++) t_Ty(
                    static_cast<argument::list_2<t_Param0,t_Param1>*>(a_pParams)->p0
                    , static_cast<argument::list_2<t_Param0,t_Param1>*>(a_pParams)->p1
            );
        }
    }
    virtual void            construct(void* a_pAddress, void** a_pParams, size_t a_uiCount)
    {
        while(a_uiCount--)
        {    
            new (static_cast<t_Ty*>(a_pAddress)++) t_Ty(*static_cast<t_Param0*>(a_pParams[0])
                                                            , *static_cast<t_Param1*>(a_pParams[1]));
        }
    }
    virtual void            destroy(void* a_pAddress, size_t a_uiCount)
    {
        while(a_uiCount--)
        {
            (static_cast<t_Ty*>(a_pAddress)++)->~t_Ty();
        }
    }
};

o_h_end

#endif // TConstructor_h__