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

/* *********************************************** */

o_namespace_begin(phantom, reflection, native)

/* ************* t_Ty Declarations ************** */

/* *********************************************** */
template<typename _Signature>
class TNativeConstructor;

template<typename t_Ty>
class TNativeConstructor<t_Ty()> : public Constructor
{
public:
    typedef TNativeConstructor<t_Ty()>    self_type;
    TNativeConstructor(const string& a_strName, Signature* a_pSignature, bitfield a_Modifiers = 0)
        : Constructor(a_strName, a_pSignature, a_Modifiers|o_native)
    {

    }
    virtual boolean      isNative() const { return true; }

    virtual void            deleteNow() 
    { 
        o_proxy_delete(phantom::reflection::Constructor, self_type) this;
    }
    virtual void            call(void* a_pAddress, void** a_pParams) const
    {
        new (a_pAddress) t_Ty();
    }

};

template<typename t_Ty, typename t_Param0>
class TNativeConstructor<t_Ty(t_Param0)> : public Constructor
{
public:
    typedef TNativeConstructor<t_Ty(t_Param0)> self_type;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;

    TNativeConstructor(const string& a_strName, Signature* a_pSignature, bitfield a_Modifiers = 0)
        : Constructor(a_strName, a_pSignature, a_Modifiers|o_native)
    {
    }
    virtual boolean         isNative() const { return true; }
    virtual void            deleteNow() 
    { 
        o_proxy_delete(phantom::reflection::Constructor, self_type) this;
    }
    virtual void            call(void* a_pAddress, void** a_pParams) const
    {
        new (a_pAddress) t_Ty(*static_cast<t_Param0*>(a_pParams[0]));
    }
};


template<typename t_Ty, typename t_Param0, typename t_Param1>
class TNativeConstructor<t_Ty(t_Param0,t_Param1)> : public Constructor
{
public:
    typedef TNativeConstructor<t_Ty(t_Param0,t_Param1)> self_type;

    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;

    TNativeConstructor(const string& a_strName, Signature* a_pSignature, bitfield a_Modifiers = 0)
        : Constructor(a_strName, a_pSignature, a_Modifiers|o_native)
    {
    }
    virtual boolean         isNative() const { return true; }

    virtual void            deleteNow() 
    { 
        o_proxy_delete(phantom::reflection::Constructor, self_type) this;
    }

    virtual void            call(void* a_pAddress, void** a_pParams) const
    {
        new (a_pAddress) t_Ty(*static_cast<t_Param0_noref*>(a_pParams[0])
                                , *static_cast<t_Param1_noref*>(a_pParams[1]));
    }
};


template<typename t_Ty, typename t_Param0, typename t_Param1, typename t_Param2>
class TNativeConstructor<t_Ty(t_Param0,t_Param1,t_Param2)> : public Constructor
{
public:
    typedef TNativeConstructor<t_Ty(t_Param0,t_Param1,t_Param2)> self_type;

    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;

    TNativeConstructor(const string& a_strName, Signature* a_pSignature, bitfield a_Modifiers = 0)
        : Constructor(a_strName, a_pSignature, a_Modifiers|o_native)
    {
    }
    virtual boolean      isNative() const { return true; }
    virtual void            deleteNow() 
    { 
        o_proxy_delete(phantom::reflection::Constructor, self_type) this;
    }

    virtual void            call(void* a_pAddress, void** a_pParams) const
    {
        new (a_pAddress) t_Ty(*static_cast<t_Param0_noref*>(a_pParams[0])
                            , *static_cast<t_Param1_noref*>(a_pParams[1])
                            , *static_cast<t_Param2_noref*>(a_pParams[2])
            );
    }
};

template<typename t_Ty
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3
>
class TNativeConstructor<t_Ty(t_Param0,t_Param1,t_Param2,t_Param3)> : public Constructor
{
public:
    typedef TNativeConstructor<t_Ty(t_Param0,t_Param1,t_Param2,t_Param3)> self_type;

    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param3>::type t_Param3_noref;


    TNativeConstructor(const string& a_strName, Signature* a_pSignature, bitfield a_Modifiers = 0)
        : Constructor(a_strName, a_pSignature, a_Modifiers|o_native)
    {
    }
    virtual boolean      isNative() const { return true; }
    virtual void            deleteNow() 
    { 
        o_proxy_delete(phantom::reflection::Constructor, self_type) this;
    }

    virtual void            call(void* a_pAddress, void** a_pParams) const
    {
        new (a_pAddress) t_Ty(*static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3])
            );
    }
};

template<typename t_Ty
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3
    , typename t_Param4
>
class TNativeConstructor<t_Ty(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4)> : public Constructor
{
public:
    typedef TNativeConstructor<t_Ty(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4)> self_type;

    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param3>::type t_Param3_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param4>::type t_Param4_noref;


    TNativeConstructor(const string& a_strName, Signature* a_pSignature, bitfield a_Modifiers = 0)
        : Constructor(a_strName, a_pSignature, a_Modifiers|o_native)
    {
    }
    virtual boolean      isNative() const { return true; }
    virtual void            deleteNow() 
    { 
        o_proxy_delete(phantom::reflection::Constructor, self_type) this;
    }

    virtual void            call(void* a_pAddress, void** a_pParams) const
    {
        new (a_pAddress) t_Ty(*static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3])
            , *static_cast<t_Param4_noref*>(a_pParams[4])
            );
    }
};

template<typename t_Ty
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3
    , typename t_Param4
    , typename t_Param5
>
class TNativeConstructor<t_Ty(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5)> : public Constructor
{
public:
    typedef TNativeConstructor<t_Ty(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5)> self_type;

    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param3>::type t_Param3_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param4>::type t_Param4_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param5>::type t_Param5_noref;


    TNativeConstructor(const string& a_strName, Signature* a_pSignature, bitfield a_Modifiers = 0)
        : Constructor(a_strName, a_pSignature, a_Modifiers|o_native)
    {
    }
    virtual boolean      isNative() const { return true; }
    virtual void            deleteNow() 
    { 
        o_proxy_delete(phantom::reflection::Constructor, self_type) this;
    }

    virtual void            call(void* a_pAddress, void** a_pParams) const
    {
        new (a_pAddress) t_Ty(*static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3])
            , *static_cast<t_Param4_noref*>(a_pParams[4])
            , *static_cast<t_Param5_noref*>(a_pParams[5])
            );
    }
};

template<typename t_Ty
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3
    , typename t_Param4
    , typename t_Param5
    , typename t_Param6
>
class TNativeConstructor<t_Ty(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6)> : public Constructor
{
public:
    typedef TNativeConstructor<t_Ty(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6)> self_type;

    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param3>::type t_Param3_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param4>::type t_Param4_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param5>::type t_Param5_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param6>::type t_Param6_noref;


    TNativeConstructor(const string& a_strName, Signature* a_pSignature, bitfield a_Modifiers = 0)
        : Constructor(a_strName, a_pSignature, a_Modifiers|o_native)
    {
    }
    virtual boolean      isNative() const { return true; }
    virtual void            deleteNow() 
    { 
        o_proxy_delete(phantom::reflection::Constructor, self_type) this;
    }

    virtual void            call(void* a_pAddress, void** a_pParams) const
    {
        new (a_pAddress) t_Ty(*static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3])
            , *static_cast<t_Param4_noref*>(a_pParams[4])
            , *static_cast<t_Param5_noref*>(a_pParams[5])
            , *static_cast<t_Param6_noref*>(a_pParams[6])
            );
    }
};

template<typename t_Ty
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3
    , typename t_Param4
    , typename t_Param5
    , typename t_Param6
    , typename t_Param7
>
class TNativeConstructor<t_Ty(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7)> : public Constructor
{
public:
    typedef TNativeConstructor<t_Ty(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7)> self_type;

    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param3>::type t_Param3_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param4>::type t_Param4_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param5>::type t_Param5_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param6>::type t_Param6_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param7>::type t_Param7_noref;


    TNativeConstructor(const string& a_strName, Signature* a_pSignature, bitfield a_Modifiers = 0)
        : Constructor(a_strName, a_pSignature, a_Modifiers|o_native)
    {
    }
    virtual boolean      isNative() const { return true; }
    virtual void            deleteNow() 
    { 
        o_proxy_delete(phantom::reflection::Constructor, self_type) this;
    }

    virtual void            call(void* a_pAddress, void** a_pParams) const
    {
        new (a_pAddress) t_Ty(*static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3])
            , *static_cast<t_Param4_noref*>(a_pParams[4])
            , *static_cast<t_Param5_noref*>(a_pParams[5])
            , *static_cast<t_Param6_noref*>(a_pParams[6])
            , *static_cast<t_Param7_noref*>(a_pParams[7])
            );
    }
};

template<typename t_Ty
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3
    , typename t_Param4
    , typename t_Param5
    , typename t_Param6
    , typename t_Param7
    , typename t_Param8
>
class TNativeConstructor<t_Ty(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7,t_Param8)> : public Constructor
{
public:
    typedef TNativeConstructor<t_Ty(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7,t_Param8)> self_type;

    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param3>::type t_Param3_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param4>::type t_Param4_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param5>::type t_Param5_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param6>::type t_Param6_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param7>::type t_Param7_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param8>::type t_Param8_noref;


    TNativeConstructor(const string& a_strName, Signature* a_pSignature, bitfield a_Modifiers = 0)
        : Constructor(a_strName, a_pSignature, a_Modifiers|o_native)
    {
    }
    virtual boolean      isNative() const { return true; }
    virtual void            deleteNow() 
    { 
        o_proxy_delete(phantom::reflection::Constructor, self_type) this;
    }

    virtual void            call(void* a_pAddress, void** a_pParams) const
    {
        new (a_pAddress) t_Ty(*static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3])
            , *static_cast<t_Param4_noref*>(a_pParams[4])
            , *static_cast<t_Param5_noref*>(a_pParams[5])
            , *static_cast<t_Param6_noref*>(a_pParams[6])
            , *static_cast<t_Param7_noref*>(a_pParams[7])
            , *static_cast<t_Param8_noref*>(a_pParams[8])
            );
    }
};

template<typename t_Ty
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3
    , typename t_Param4
    , typename t_Param5
    , typename t_Param6
    , typename t_Param7
    , typename t_Param8
    , typename t_Param9
>
class TNativeConstructor<t_Ty(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7,t_Param8,t_Param9)> : public Constructor
{
public:
    typedef TNativeConstructor<t_Ty(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7,t_Param8,t_Param9)> self_type;

    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param3>::type t_Param3_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param4>::type t_Param4_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param5>::type t_Param5_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param6>::type t_Param6_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param7>::type t_Param7_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param8>::type t_Param8_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param9>::type t_Param9_noref;


    TNativeConstructor(const string& a_strName, Signature* a_pSignature, bitfield a_Modifiers = 0)
        : Constructor(a_strName, a_pSignature, a_Modifiers|o_native)
    {
    }
    virtual boolean      isNative() const { return true; }
    virtual void            deleteNow() 
    { 
        o_proxy_delete(phantom::reflection::Constructor, self_type) this;
    }

    virtual void            call(void* a_pAddress, void** a_pParams) const
    {
        new (a_pAddress) t_Ty(*static_cast<t_Param0_noref*>(a_pParams[0])
                            , *static_cast<t_Param1_noref*>(a_pParams[1])
                            , *static_cast<t_Param2_noref*>(a_pParams[2])
                            , *static_cast<t_Param3_noref*>(a_pParams[3])
                            , *static_cast<t_Param4_noref*>(a_pParams[4])
                            , *static_cast<t_Param5_noref*>(a_pParams[5])
                            , *static_cast<t_Param6_noref*>(a_pParams[6])
                            , *static_cast<t_Param7_noref*>(a_pParams[7])
                            , *static_cast<t_Param8_noref*>(a_pParams[8])
                            , *static_cast<t_Param9_noref*>(a_pParams[9])
            );
    }
};

o_namespace_end(phantom, reflection, native)

#endif // TConstructor_h__