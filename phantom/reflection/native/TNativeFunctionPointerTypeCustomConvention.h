#define o_convention_id o_PP_CAT(e_, o_convention_base)
#define o_convention_keyword o_PP_CAT(__, o_convention_base)

template<typename Signature>
class TNativeFunctionPointerType;

template<typename t_ReturnType>
class TNativeFunctionPointerType<t_ReturnType (o_convention_keyword *)()>
    : public TNativeFunctionPointerType0<o_convention_id, t_ReturnType>
{
public:
    typedef TNativeFunctionPointerType<t_ReturnType (o_convention_keyword *)()>    self_type;
    typedef typename native_function_pointer_type<o_convention_id, t_ReturnType (o_convention_keyword *)()>::type function_pointer_t;

    TNativeFunctionPointerType()
        : TNativeFunctionPointerType0<o_convention_id, t_ReturnType>(TNativeSignatureProvider<t_ReturnType()>::CreateSignature(), a_Modifiers|o_native)
    {

    }
};

template<typename t_ReturnType, typename t_Param0>
class TNativeFunctionPointerType<t_ReturnType (o_convention_keyword *)(t_Param0)> 
    : public TNativeFunctionPointerType1<o_convention_id, t_ReturnType, t_Param0>
{
public:
    typedef TNativeFunctionPointerType<t_ReturnType (o_convention_keyword *)(t_Param0)>    self_type;
    typedef typename native_function_pointer_type<o_convention_id, t_ReturnType (o_convention_keyword *)(t_Param0)>::type function_pointer_t;

    TNativeFunctionPointerType()
        :TNativeFunctionPointerType1<o_convention_id, t_ReturnType,t_Param0>(TNativeSignatureProvider<t_ReturnType(t_Param0)>::CreateSignature(), a_Modifiers|o_native)
    {

    }
};

template<typename t_ReturnType, typename t_Param0, typename t_Param1>
class TNativeFunctionPointerType<t_ReturnType (o_convention_keyword *)(t_Param0,t_Param1)> 
    : public TNativeFunctionPointerType2<o_convention_id, t_ReturnType, t_Param0, t_Param1>
{
public:
    typedef TNativeFunctionPointerType<t_ReturnType (o_convention_keyword *)(t_Param0, t_Param1)>    self_type;
    typedef typename native_function_pointer_type<o_convention_id, t_ReturnType (o_convention_keyword *)(t_Param0, t_Param1)>::type function_pointer_t;

    TNativeFunctionPointerType()
        :TNativeFunctionPointerType2<o_convention_id, t_ReturnType,t_Param0,t_Param1>(TNativeSignatureProvider<t_ReturnType(t_Param0,t_Param1)>::CreateSignature(), a_Modifiers|o_native)
    {

    }

};

template<
    typename t_ReturnType
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2>
class TNativeFunctionPointerType<t_ReturnType (o_convention_keyword *)(t_Param0,t_Param1,t_Param2)> 
    : public TNativeFunctionPointerType3<o_convention_id, t_ReturnType, t_Param0, t_Param1, t_Param2>
{
public:
    typedef TNativeFunctionPointerType<t_ReturnType (o_convention_keyword *)(t_Param0, t_Param1, t_Param2)>    self_type;
    typedef typename native_function_pointer_type<o_convention_id, t_ReturnType (o_convention_keyword *)(t_Param0, t_Param1,t_Param2)>::type function_pointer_t;

    TNativeFunctionPointerType()
        :TNativeFunctionPointerType3<o_convention_id, t_ReturnType, t_Param0, t_Param1, t_Param2>(TNativeSignatureProvider<t_ReturnType(t_Param0,t_Param1,t_Param2)>::CreateSignature(), a_Modifiers|o_native)
    {

    }

};


template<
    typename t_ReturnType
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3>
class TNativeFunctionPointerType<t_ReturnType (o_convention_keyword *)(t_Param0,t_Param1,t_Param2,t_Param3)> 
    : public TNativeFunctionPointerType4<o_convention_id, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3>
{
public:
    typedef TNativeFunctionPointerType<t_ReturnType (o_convention_keyword *)(t_Param0, t_Param1, t_Param2,t_Param3)>    self_type;
    typedef typename native_function_pointer_type<o_convention_id, t_ReturnType (o_convention_keyword *)(t_Param0, t_Param1,t_Param2,t_Param3)>::type function_pointer_t;

    TNativeFunctionPointerType()
        :TNativeFunctionPointerType4<o_convention_id, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3>(TNativeSignatureProvider<t_ReturnType(t_Param0, t_Param1, t_Param2, t_Param3)>::CreateSignature(), a_Modifiers|o_native)
    {

    }

};

template<
    typename t_ReturnType
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3
    , typename t_Param4>
class TNativeFunctionPointerType<t_ReturnType (o_convention_keyword *)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4)> 
    : public TNativeFunctionPointerType5<o_convention_id, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3,t_Param4>
{
public:
    typedef TNativeFunctionPointerType<t_ReturnType (o_convention_keyword *)(t_Param0, t_Param1, t_Param2,t_Param3,t_Param4)>    self_type;
    typedef typename native_function_pointer_type<o_convention_id, t_ReturnType (o_convention_keyword *)(t_Param0, t_Param1,t_Param2,t_Param3,t_Param4)>::type function_pointer_t;

    TNativeFunctionPointerType()
        :TNativeFunctionPointerType5<o_convention_id, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3,t_Param4>(TNativeSignatureProvider<t_ReturnType(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4)>::CreateSignature(), a_Modifiers|o_native)
    {

    }

};

template<
    typename t_ReturnType
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3
    , typename t_Param4
    , typename t_Param5>
class TNativeFunctionPointerType<t_ReturnType (o_convention_keyword *)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5)> 
    : public TNativeFunctionPointerType6<o_convention_id, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3,t_Param4,t_Param5>
{
public:
    typedef TNativeFunctionPointerType<t_ReturnType (o_convention_keyword *)(t_Param0, t_Param1, t_Param2,t_Param3,t_Param4,t_Param5)>    self_type;
    typedef typename native_function_pointer_type<o_convention_id, t_ReturnType (o_convention_keyword *)(t_Param0, t_Param1,t_Param2,t_Param3,t_Param4,t_Param5)>::type function_pointer_t;

    TNativeFunctionPointerType()
        :TNativeFunctionPointerType6<o_convention_id, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3,t_Param4,t_Param5>(TNativeSignatureProvider<t_ReturnType(t_Param0, t_Param1,t_Param2,t_Param3,t_Param4,t_Param5)>::CreateSignature(), a_Modifiers|o_native)
    {

    }

};

template<
    typename t_ReturnType
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3
    , typename t_Param4
    , typename t_Param5
    , typename t_Param6>
class TNativeFunctionPointerType<t_ReturnType (o_convention_keyword *)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6)> 
    : public TNativeFunctionPointerType7<o_convention_id, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3,t_Param4,t_Param5,t_Param6>
{
public:
    typedef TNativeFunctionPointerType<t_ReturnType (o_convention_keyword *)(t_Param0, t_Param1, t_Param2,t_Param3,t_Param4,t_Param5,t_Param6)>    self_type;
    typedef typename native_function_pointer_type<o_convention_id, t_ReturnType (o_convention_keyword *)(t_Param0, t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6)>::type function_pointer_t;

    TNativeFunctionPointerType()
        :TNativeFunctionPointerType7<o_convention_id, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3,t_Param4,t_Param5,t_Param6>(TNativeSignatureProvider<t_ReturnType(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6)>::CreateSignature(), a_Modifiers|o_native)
    {

    }

};


template<
    typename t_ReturnType
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3
    , typename t_Param4
    , typename t_Param5
    , typename t_Param6
    , typename t_Param7>
class TNativeFunctionPointerType<t_ReturnType (o_convention_keyword *)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7)> 
    : public TNativeFunctionPointerType8<o_convention_id, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>
{
public:
    typedef TNativeFunctionPointerType<t_ReturnType (o_convention_keyword *)(t_Param0, t_Param1, t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7)>    self_type;
    typedef typename native_function_pointer_type<o_convention_id, t_ReturnType (o_convention_keyword *)(t_Param0, t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7)>::type function_pointer_t;

    TNativeFunctionPointerType()
        :TNativeFunctionPointerType8<o_convention_id, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>(TNativeSignatureProvider<t_ReturnType(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7)>::CreateSignature(), a_Modifiers|o_native)
    {

    }
};

#endif // TNativeFunctionPointerType_h__
