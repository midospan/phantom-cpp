#pragma once

o_namespace_begin(phantom, reflection, native)

template <int t_counter, typename t_ReturnType>
class TNativeSignatureProvider0
{
public:
    static Signature*    CreateSignature()
    {
        /// Check first by static resolving
        Signature* pSignature = Signature::Create();
        phantom::reflection::Type* pReturnType = phantom::reflection::detail::type_of_counter<t_ReturnType, t_counter>::object();
        o_assert(pReturnType);
        pSignature->setReturnType(pReturnType);
        return pSignature;
    }
};

template <int t_counter, typename t_ReturnType
    , typename t_Param0>
class TNativeSignatureProvider1
{
public:
    static Signature*    CreateSignature()
    {
        /// Resolve first by static type resolving.
        /// If one fails, resolve via signature parsing (probably a pointer on an uncomplete class).
        Signature* pSignature = Signature::Create();
        Type* pReturnType = phantom::reflection::detail::type_of_counter<t_ReturnType, t_counter>::object();
        o_assert(pReturnType) ;
        Type* pParam0 = phantom::reflection::detail::type_of_counter<t_Param0, t_counter>::object();
        o_assert(pParam0); 
        pSignature->setReturnType(pReturnType);
        pSignature->addParameterType(pParam0);
        return pSignature;
    }
};


template <int t_counter, typename t_ReturnType
    , typename t_Param0
    , typename t_Param1>
class TNativeSignatureProvider2
{
public:
    static Signature*    CreateSignature()
    {
        /// Resolve first by static type resolving.
        /// If one fails, resolve via signature parsing (probably a pointer on an uncomplete class).
        Signature* pSignature = Signature::Create();
        Type* pReturnType = phantom::reflection::detail::type_of_counter<t_ReturnType, t_counter>::object();
        o_assert(pReturnType) ;
        Type* pParam0 = phantom::reflection::detail::type_of_counter<t_Param0, t_counter>::object();
        o_assert(pParam0); 
        Type* pParam1 = phantom::reflection::detail::type_of_counter<t_Param1, t_counter>::object();
        o_assert(pParam1); 
        pSignature->setReturnType(pReturnType);
        pSignature->addParameterType(pParam0);
        pSignature->addParameterType(pParam1);
        return pSignature;
    }
};

template <int t_counter, typename t_ReturnType
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2>
class TNativeSignatureProvider3
{
public:
    static Signature*    CreateSignature()
    {
        /// Resolve first by static type resolving.
        /// If one fails, resolve via signature parsing (probably due to the presence of a pointer on an uncomplete class).
        Signature* pSignature = Signature::Create();
        Type* pReturnType = phantom::reflection::detail::type_of_counter<t_ReturnType, t_counter>::object();
        o_assert(pReturnType) ;
        Type* pParam0 = phantom::reflection::detail::type_of_counter<t_Param0, t_counter>::object();
        o_assert(pParam0); 
        Type* pParam1 = phantom::reflection::detail::type_of_counter<t_Param1, t_counter>::object();
        o_assert(pParam1); 
        Type* pParam2 = phantom::reflection::detail::type_of_counter<t_Param2, t_counter>::object();
        o_assert(pParam2); 
        pSignature->setReturnType(pReturnType);
        pSignature->addParameterType(pParam0);
        pSignature->addParameterType(pParam1);
        pSignature->addParameterType(pParam2);
        return pSignature;
    }
};

template <int t_counter, typename t_ReturnType
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3>
class TNativeSignatureProvider4
{
public:
    static Signature*    CreateSignature()
    {
        /// Resolve first by static type resolving.
        /// If one fails, resolve via signature parsing (probably due to the presence of a pointer on an uncomplete class).
        Signature* pSignature = Signature::Create();
        Type* pReturnType = phantom::reflection::detail::type_of_counter<t_ReturnType, t_counter>::object();
        o_assert(pReturnType) ;
        Type* pParam0 = phantom::reflection::detail::type_of_counter<t_Param0, t_counter>::object();
        o_assert(pParam0); 
        Type* pParam1 = phantom::reflection::detail::type_of_counter<t_Param1, t_counter>::object();
        o_assert(pParam1); 
        Type* pParam2 = phantom::reflection::detail::type_of_counter<t_Param2, t_counter>::object();
        o_assert(pParam2); 
        Type* pParam3 = phantom::reflection::detail::type_of_counter<t_Param3, t_counter>::object();
        o_assert(pParam3); 
        pSignature->setReturnType(pReturnType);
        pSignature->addParameterType(pParam0);
        pSignature->addParameterType(pParam1);
        pSignature->addParameterType(pParam2);
        pSignature->addParameterType(pParam3);
        return pSignature;
    }
};

template <int t_counter, typename t_ReturnType
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3
    , typename t_Param4>
class TNativeSignatureProvider5
{
public:
    static Signature*    CreateSignature()
    {
        /// Resolve first by static type resolving.
        /// If one fails, resolve via signature parsing (probably due to the presence of a pointer on an uncomplete class).
        Signature* pSignature = Signature::Create();
        Type* pReturnType = phantom::reflection::detail::type_of_counter<t_ReturnType, t_counter>::object();
        o_assert(pReturnType) ;
        Type* pParam0 = phantom::reflection::detail::type_of_counter<t_Param0, t_counter>::object();
        o_assert(pParam0); 
        Type* pParam1 = phantom::reflection::detail::type_of_counter<t_Param1, t_counter>::object();
        o_assert(pParam1); 
        Type* pParam2 = phantom::reflection::detail::type_of_counter<t_Param2, t_counter>::object();
        o_assert(pParam2); 
        Type* pParam3 = phantom::reflection::detail::type_of_counter<t_Param3, t_counter>::object();
        o_assert(pParam3); 
        Type* pParam4 = phantom::reflection::detail::type_of_counter<t_Param4, t_counter>::object();
        o_assert(pParam4); 
        pSignature->setReturnType(pReturnType);
        pSignature->addParameterType(pParam0);
        pSignature->addParameterType(pParam1);
        pSignature->addParameterType(pParam2);
        pSignature->addParameterType(pParam3);
        pSignature->addParameterType(pParam4);
        return pSignature;
    }
};

#ifdef o_NO_FUNCTION_STYLE_TEMPLATE_SIGNATURE

template <int t_counter, typename t_ReturnType
    , typename t_Param0 = void
    , typename t_Param1 = void
    , typename t_Param2 = void
    , typename t_Param3 = void
    , typename t_Param4 = void>
class TNativeSignatureProvider 
    : public TNativeSignatureProvider5<t_counter, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4>
{
};

template <int t_counter, typename t_ReturnType>
class TNativeSignatureProvider<t_ReturnType,t_Param0, t_Param1, t_Param2, t_Param3, void> 
    : public TNativeSignatureProvider4<t_counter, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3>
{
};
template <int t_counter, typename t_ReturnType
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2>
class TNativeSignatureProvider<t_ReturnType,t_Param0, t_Param1, t_Param2, void, void> 
    : public TNativeSignatureProvider3<t_counter, t_ReturnType, t_Param0, t_Param1, t_Param2>
{
};

template <int t_counter, typename t_ReturnType
    , typename t_Param0
    , typename t_Param1>
class TNativeSignatureProvider<t_ReturnType,t_Param0, t_Param1, void, void, void> 
    : public TNativeSignatureProvider2<t_counter, t_ReturnType, t_Param0, t_Param1>
{
};

template <int t_counter, typename t_ReturnType
    , typename t_Param0>
class TNativeSignatureProvider<t_ReturnType,t_Param0, void, void, void, void> 
    : public TNativeSignatureProvider1<t_counter, t_ReturnType, t_Param0>
{
};


template <int t_counter, typename t_ReturnType>
class TNativeSignatureProvider<t_ReturnType,void, void, void, void, void> : public TNativeSignatureProvider0<t_counter, t_ReturnType>
{
};

#else

template <int t_counter, typename Signature>
class TNativeSignatureProvider;


template <int t_counter, typename t_ReturnType>
class TNativeSignatureProvider<t_counter, t_ReturnType()> : public TNativeSignatureProvider0<t_counter, t_ReturnType>
{

};

template <int t_counter, typename t_ReturnType, typename t_Param0>
class TNativeSignatureProvider<t_counter, t_ReturnType(t_Param0)> : public TNativeSignatureProvider1<t_counter, t_ReturnType, t_Param0>
{

};

template <int t_counter, typename t_ReturnType, typename t_Param0, typename t_Param1>
class TNativeSignatureProvider<t_counter, t_ReturnType(t_Param0, t_Param1)> : public TNativeSignatureProvider2<t_counter, t_ReturnType, t_Param0, t_Param1>
{

};

template <int t_counter, typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2>
class TNativeSignatureProvider<t_counter, t_ReturnType(t_Param0, t_Param1, t_Param2)> : public TNativeSignatureProvider3<t_counter, t_ReturnType, t_Param0, t_Param1, t_Param2>
{

};

template <int t_counter, typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3>
class TNativeSignatureProvider<t_counter, t_ReturnType(t_Param0, t_Param1, t_Param2, t_Param3)> 
    : public TNativeSignatureProvider4<t_counter, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3>
{

};

#endif

o_namespace_end(phantom, reflection, native)
