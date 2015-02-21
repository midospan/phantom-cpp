#ifndef o_reflection_native_TFundamentals_h__
#define o_reflection_native_TFundamentals_h__

#include <phantom/phantom.h>

o_namespace_begin(phantom, reflection, native)

    template<typename t_Ty>
class TFundamentalType : public TPrimitiveType<t_Ty>
{
    o_type;

public:
    TFundamentalType(const string& a_strName, ushort a_uiSize, ushort a_uiAlignment, modifiers_t a_Modifiers = 0)
        : TPrimitiveType<t_Ty>(a_strName, a_uiSize, a_uiAlignment, a_Modifiers) {}

    virtual PrimitiveType* asFundamentalType() const { return (PrimitiveType*)this; }

};

template<typename t_Ty>
class TArithmeticType : public TFundamentalType<t_Ty>
{
    o_type;

public:
    TArithmeticType(const string& a_strName, ushort a_uiSize, ushort a_uiAlignment, modifiers_t a_Modifiers = 0)
        : TFundamentalType<t_Ty>(a_strName, a_uiSize, a_uiAlignment, a_Modifiers) {}

    virtual PrimitiveType* asArithmeticType() const { return (PrimitiveType*)this; }

};

template<typename t_Ty>
class TFloatingPointType : public TArithmeticType<t_Ty>
{
    o_type;

public:
    TFloatingPointType(const string& a_strName, ushort a_uiSize, ushort a_uiAlignment, modifiers_t a_Modifiers = 0)
        : TArithmeticType<t_Ty>(a_strName, a_uiSize, a_uiAlignment, a_Modifiers) {}

    virtual PrimitiveType* asFloatingPointType() const { return (PrimitiveType*)this; }
};

template<typename t_Ty>
class TIntegralType : public TArithmeticType<t_Ty>
{
    o_type;

public:
    TIntegralType(const string& a_strName, ushort a_uiSize, ushort a_uiAlignment, modifiers_t a_Modifiers = 0)
        : TArithmeticType<t_Ty>(a_strName, a_uiSize, a_uiAlignment, a_Modifiers) 
    {

    }

    virtual PrimitiveType* asIntegralType() const { return (PrimitiveType*)this; }

};
o_namespace_end(phantom, reflection, native)

#endif // o_reflection_native_TFundamentals_h__