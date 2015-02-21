#ifndef BuiltInOperators_h__
#define BuiltInOperators_h__

#include <phantom/reflection/native/TFundamentals.h>

o_namespace_begin(phantom, reflection)

/// disable unsafe integral operations (we generate code for them because of template genericity, but we will never go through them, so it doesn't matter)
#if o_COMPILER == o_COMPILER_VISUAL_STUDIO
#pragma warning(disable:4800)
#pragma warning(disable:4804)
#pragma warning(disable:4805)
#pragma warning(disable:4018)
#pragma warning(disable:4244)
#pragma warning(disable:4146)
#endif

#define operandT0 (*(T0*)a_pArgs[0])

#define operandT1 (*(T1*)a_pArgs[1])

#define resultR (*(R*)a_pOutput)

#define resultRref (*(R**)a_pOutput)

#define resultRrefCast(c) (R*)(c)

#define resultLR o_NESTED_TYPE builtin_operation_delegate_LR<T0, T1>::type

template<typename T0, typename T1 = void, typename R = T0>
struct builtin_operation_delegate_Plus { static void apply(void** a_pArgs, void* a_pOutput) { resultR = operandT0; } };
template<typename T0, typename T1 = void, typename R = T0>
struct builtin_operation_delegate_Minus { static void apply(void** a_pArgs, void* a_pOutput) { resultR = -operandT0; } };
template<typename T0, typename T1 = void, typename R = T0>
struct builtin_operation_delegate_PreDecrement { static void apply(void** a_pArgs, void* a_pOutput) { resultRref = resultRrefCast(&--operandT0); } };
template<typename T1, typename R>
struct builtin_operation_delegate_PreDecrement<bool, T1, R> { static void apply(void** a_pArgs, void* a_pOutput) { o_exception_no_implementation(); } };
template<typename T0, typename T1 = void, typename R = T0>
struct builtin_operation_delegate_PreIncrement { static void apply(void** a_pArgs, void* a_pOutput) { resultRref = resultRrefCast(&++operandT0); } };
template<typename T0, typename T1 = void, typename R = T0>
struct builtin_operation_delegate_Not { static void apply(void** a_pArgs, void* a_pOutput) { resultR = !operandT0; } };
template<typename T0, typename T1 = void, typename R = T0>
struct builtin_operation_delegate_Complement { static void apply(void** a_pArgs, void* a_pOutput) { resultR = ~operandT0; } };

template<typename T0, typename T1 = void, typename R = T0>
struct builtin_operation_delegate_PostDecrement { static void apply(void** a_pArgs, void* a_pOutput) { resultR = operandT0--; } };
template< typename T1, typename R>
struct builtin_operation_delegate_PostDecrement<bool, T1, R> { static void apply(void** a_pArgs, void* a_pOutput) { o_exception_no_implementation(); } };
template<typename T0, typename T1 = void, typename R = T0>
struct builtin_operation_delegate_PostIncrement { static void apply(void** a_pArgs, void* a_pOutput) { resultR = operandT0++; } };



template<typename T0, typename T1> 
struct builtin_operation_delegate_LR : public boost::mpl::if_c<((native::primitive_type_id_helper<T0>::value) > (native::primitive_type_id_helper<T1>::value)), T0, T1>
{
};  

template<typename T0, typename T1, typename R = resultLR>
struct builtin_operation_delegate_Add { static void apply(void** a_pArgs, void* a_pOutput) { resultR = *(T0*)a_pArgs[0] + operandT1; } };

template<typename T0, typename T1, typename R = resultLR>
struct builtin_operation_delegate_Subtract { static void apply(void** a_pArgs, void* a_pOutput) { resultR = operandT0 - operandT1; } };

template<typename T0, typename T1, typename R = resultLR>
struct builtin_operation_delegate_Multiply { static void apply(void** a_pArgs, void* a_pOutput) { resultR = operandT0 * operandT1; } };

template<typename T0, typename T1, typename R = resultLR>
struct builtin_operation_delegate_Divide { static void apply(void** a_pArgs, void* a_pOutput) { resultR = operandT0 / operandT1; } };

template<typename T0, typename T1, typename R = bool>
struct builtin_operation_delegate_Equal { static void apply(void** a_pArgs, void* a_pOutput) { resultR = operandT0 == operandT1; } };

template<typename T0, typename T1, typename R = bool>
struct builtin_operation_delegate_NotEqual { static void apply(void** a_pArgs, void* a_pOutput) { resultR = operandT0 != operandT1; } };

template<typename T0, typename T1, typename R = bool>
struct builtin_operation_delegate_Greater { static void apply(void** a_pArgs, void* a_pOutput) { resultR = operandT0 > operandT1; } };

template<typename T0, typename T1, typename R = bool>
struct builtin_operation_delegate_Less { static void apply(void** a_pArgs, void* a_pOutput) { resultR = operandT0 < operandT1; } };

template<typename T0, typename T1, typename R = bool>
struct builtin_operation_delegate_GreaterEqual { static void apply(void** a_pArgs, void* a_pOutput) { resultR = operandT0 >= operandT1; } };

template<typename T0, typename T1, typename R = bool>
struct builtin_operation_delegate_LessEqual { static void apply(void** a_pArgs, void* a_pOutput) { resultR = operandT0 <= operandT1; } };

template<typename T0, typename T1, typename R = bool>
struct builtin_operation_delegate_LogicalAnd { static void apply(void** a_pArgs, void* a_pOutput) { resultR = operandT0 && operandT1; } };

template<typename T0, typename T1, typename R = bool>
struct builtin_operation_delegate_LogicalOr { static void apply(void** a_pArgs, void* a_pOutput) { resultR = operandT0 || operandT1; } };

template<typename T0, typename T1, typename R = resultLR>
struct builtin_operation_delegate_XOr { static void apply(void** a_pArgs, void* a_pOutput) { resultR = operandT0 ^ operandT1; } };

template<typename T0, typename T1, typename R = resultLR>
struct builtin_operation_delegate_BitAnd { static void apply(void** a_pArgs, void* a_pOutput) { resultR = operandT0 & operandT1; } };

template<typename T0, typename T1, typename R = resultLR>
struct builtin_operation_delegate_BitOr { static void apply(void** a_pArgs, void* a_pOutput) { resultR = operandT0 | operandT1; } };

template<typename T0, typename T1, typename R = resultLR>
struct builtin_operation_delegate_Modulo { static void apply(void** a_pArgs, void* a_pOutput) { resultR = operandT0 % operandT1; } };

template<typename T0, typename T1, typename R = T0>
struct builtin_operation_delegate_ShiftLeft { static void apply(void** a_pArgs, void* a_pOutput) { resultR = operandT0 << operandT1; } };

template<typename T0, typename T1, typename R = T0>
struct builtin_operation_delegate_ShiftRight { static void apply(void** a_pArgs, void* a_pOutput) { resultR = operandT0 >> operandT1; } };

template<typename T0, typename T1, typename R = T0>
struct builtin_operation_delegate_Assignment { static void apply(void** a_pArgs, void* a_pOutput) { resultRref = resultRrefCast(&(operandT0 = operandT1)); } };

template<typename T0, typename T1, typename R = T0>
struct builtin_operation_delegate_AssignmentAdd { static void apply(void** a_pArgs, void* a_pOutput) { resultRref = resultRrefCast(&(operandT0 += operandT1)); } };

template<typename T0, typename T1, typename R = T0>
struct builtin_operation_delegate_AssignmentSubtract { static void apply(void** a_pArgs, void* a_pOutput) { resultRref = resultRrefCast(&(operandT0 -= operandT1)); } };

template<typename T0, typename T1, typename R = T0>
struct builtin_operation_delegate_AssignmentMultiply { static void apply(void** a_pArgs, void* a_pOutput) { resultRref = resultRrefCast(&(operandT0 *= operandT1)); } };

template<typename T0, typename T1, typename R = T0>
struct builtin_operation_delegate_AssignmentDivide { static void apply(void** a_pArgs, void* a_pOutput) { resultRref = resultRrefCast(&(operandT0 /= operandT1)); } };

template<typename T0, typename T1, typename R = T0>
struct builtin_operation_delegate_AssignmentBitAnd { static void apply(void** a_pArgs, void* a_pOutput) { resultRref = resultRrefCast(&(operandT0 &= operandT1)); } };

template<typename T0, typename T1, typename R = T0>
struct builtin_operation_delegate_AssignmentBitOr { static void apply(void** a_pArgs, void* a_pOutput) { resultRref = resultRrefCast(&(operandT0 |= operandT1)); } };

template<typename T0, typename T1, typename R = T0>
struct builtin_operation_delegate_AssignmentModulo { static void apply(void** a_pArgs, void* a_pOutput) { resultRref = resultRrefCast(&(operandT0 %= operandT1)); } };

template<typename T0, typename T1, typename R = T0>
struct builtin_operation_delegate_AssignmentShiftLeft { static void apply(void** a_pArgs, void* a_pOutput) { resultRref = resultRrefCast(&(operandT0 <<= operandT1)); } };

template<typename T0, typename T1, typename R = T0>
struct builtin_operation_delegate_AssignmentShiftRight { static void apply(void** a_pArgs, void* a_pOutput) { resultRref = resultRrefCast(&(operandT0 >>= operandT1)); } };

template<typename T0, typename T1, typename R = T0>
struct builtin_operation_delegate_AssignmentXOr { static void apply(void** a_pArgs, void* a_pOutput) { resultRref = resultRrefCast(&(operandT0 ^= operandT1)); } };

#undef operandT0 // (*(T0*)a_pArgs[0])

#undef operandT1 // (*(T1*)a_pArgs[1])

#undef resultR // (*(R*)a_pOutput)

#undef resultRref // (*(R**)a_pOutput)

#define builtin_operation_delegate_selector_input_type_id (*(ETypeId*) a_Data.in[1])
#define builtin_operation_delegate_selector_input_op_id (*(EOperator*) a_Data.in[0])
#define builtin_operation_delegate_selector_result (*(operation_delegate_t*) a_Data.out[0])

#define builtin_operation_delegate_selector_type_case(t, op)\
    case e_##t : builtin_operation_delegate_selector_result = operation_delegate_t(&builtin_operation_delegate_##op<t_Ty, t>::apply); return

#define builtin_operation_delegate_selector_op_integral_no_bool_cases(op)  \
    builtin_operation_delegate_selector_type_case(char, op);      \
    builtin_operation_delegate_selector_type_case(schar, op);     \
    builtin_operation_delegate_selector_type_case(uchar, op);     \
    builtin_operation_delegate_selector_type_case(short, op);     \
    builtin_operation_delegate_selector_type_case(ushort, op);    \
    builtin_operation_delegate_selector_type_case(int, op);       \
    builtin_operation_delegate_selector_type_case(uint, op);      \
    builtin_operation_delegate_selector_type_case(long, op);      \
    builtin_operation_delegate_selector_type_case(ulong, op);     \
    builtin_operation_delegate_selector_type_case(longlong, op);  \
    builtin_operation_delegate_selector_type_case(ulonglong, op); \
    o_if_wchar_t(builtin_operation_delegate_selector_type_case(wchar_t, op);)\
    o_if_char16_t(builtin_operation_delegate_selector_type_case(char16_t, op);)\
    o_if_char32_t(builtin_operation_delegate_selector_type_case(char32_t, op);)\


#define builtin_operation_delegate_selector_op_integral_cases(op)  \
    builtin_operation_delegate_selector_type_case(bool, op);      \
    builtin_operation_delegate_selector_op_integral_no_bool_cases(op);\

#define builtin_operation_delegate_selector_op_floating_cases(op)  \
    builtin_operation_delegate_selector_type_case(float, op);     \
    builtin_operation_delegate_selector_type_case(double, op);    \
    builtin_operation_delegate_selector_type_case(longdouble, op);\

#define builtin_operation_delegate_selector_op_integral(op)\
    case e_Operator_##op: { switch(builtin_operation_delegate_selector_input_type_id) { builtin_operation_delegate_selector_op_integral_cases(op) } } return;

#define builtin_operation_delegate_selector_op_unary(op)\
    case e_Operator_##op: builtin_operation_delegate_selector_result = operation_delegate_t(&builtin_operation_delegate_##op<t_Ty>::apply); return;

#define builtin_operation_delegate_selector_op_unary_no_bool(op)\
    case e_Operator_##op: if(typeOf<bool>() != a_pInput->removeQualifiers()) builtin_operation_delegate_selector_result = operation_delegate_t(&builtin_operation_delegate_##op<t_Ty>::apply); return;

#define builtin_operation_delegate_selector_op_arithmetic(op)\
    case e_Operator_##op: { switch(builtin_operation_delegate_selector_input_type_id) { \
    builtin_operation_delegate_selector_op_integral_cases(op) builtin_operation_delegate_selector_op_floating_cases(op) } } return;

#define builtin_operation_delegate_selector_op_arithmetic_no_bool(op)\
    case e_Operator_##op: { switch(builtin_operation_delegate_selector_input_type_id) { \
    builtin_operation_delegate_selector_op_integral_no_bool_cases(op) builtin_operation_delegate_selector_op_floating_cases(op) } } return;


struct builtin_operation_delegate_selector : public LanguageElementVisitor
{
    operation_delegate_t delegate(EOperator a_eOperator, Type* T)
    {
        visitor_data data;
        const void* in[1] = {&a_eOperator};
        operation_delegate_t result;
        void* out[1] = {&result};
        data.in = in;
        data.out = out;
        T->visit(this, data);
        o_assert(!result.empty());
        return result;
    }

    operation_delegate_t delegate(EOperator a_eOperator, Type* L, Type* R)
    {
        visitor_data data;
        ETypeId RtypeId = R->getTypeId();
        const void* in[2] = {&a_eOperator, &RtypeId};
        operation_delegate_t result = 0;
        void* out[1] = {&result};
        data.in = in;
        data.out = out;
        L->visit(this, data);
        o_assert(!result.empty());
        return result;
    }

    template<typename t_Ty>
    void visitIntegral(native::TIntegralType<t_Ty>* a_pInput, visitor_data a_Data) 
    { 
        visitArithmetic(a_pInput, a_Data);
        if(builtin_operation_delegate_selector_result == 0) /// not found in 'visitArithmetic'
        {
            switch(builtin_operation_delegate_selector_input_op_id)
            {
                builtin_operation_delegate_selector_op_unary(Complement);
                builtin_operation_delegate_selector_op_integral(Modulo);
                builtin_operation_delegate_selector_op_integral(BitAnd);
                builtin_operation_delegate_selector_op_integral(XOr);
                builtin_operation_delegate_selector_op_integral(BitOr);
                builtin_operation_delegate_selector_op_integral(ShiftLeft);
                builtin_operation_delegate_selector_op_integral(ShiftRight);
                builtin_operation_delegate_selector_op_integral(AssignmentModulo);
                builtin_operation_delegate_selector_op_integral(AssignmentShiftLeft);
                builtin_operation_delegate_selector_op_integral(AssignmentShiftRight);
                builtin_operation_delegate_selector_op_integral(AssignmentBitAnd);
                builtin_operation_delegate_selector_op_integral(AssignmentXOr);
                builtin_operation_delegate_selector_op_integral(AssignmentBitOr);
            }
        }
    }
    template<typename t_Ty>
    void visitArithmetic(native::TArithmeticType<t_Ty>* a_pInput, visitor_data a_Data) 
    { 
        switch(builtin_operation_delegate_selector_input_op_id)
        {
            builtin_operation_delegate_selector_op_unary(Plus);
            builtin_operation_delegate_selector_op_unary(Minus);
            builtin_operation_delegate_selector_op_arithmetic(Multiply);
            builtin_operation_delegate_selector_op_arithmetic(Divide);
            builtin_operation_delegate_selector_op_arithmetic(Add);
            builtin_operation_delegate_selector_op_arithmetic(Subtract);
            builtin_operation_delegate_selector_op_arithmetic(Less);
            builtin_operation_delegate_selector_op_arithmetic(Greater);
            builtin_operation_delegate_selector_op_arithmetic(LessEqual);
            builtin_operation_delegate_selector_op_arithmetic(GreaterEqual);
            builtin_operation_delegate_selector_op_arithmetic(Equal);
            builtin_operation_delegate_selector_op_arithmetic(NotEqual);
            builtin_operation_delegate_selector_op_unary(PreIncrement);
            builtin_operation_delegate_selector_op_unary(PostIncrement);
            builtin_operation_delegate_selector_op_unary_no_bool(PreDecrement);
            builtin_operation_delegate_selector_op_unary_no_bool(PostDecrement);
            builtin_operation_delegate_selector_op_arithmetic(Assignment);
            builtin_operation_delegate_selector_op_arithmetic(AssignmentAdd);
            builtin_operation_delegate_selector_op_arithmetic(AssignmentSubtract);
            builtin_operation_delegate_selector_op_arithmetic(AssignmentMultiply);
            builtin_operation_delegate_selector_op_arithmetic(AssignmentDivide);
        }
    }
    template<typename t_Ty>
    void visitFloatingPoint(native::TFloatingPointType<t_Ty>* a_pInput, visitor_data a_Data) 
    { 
        visitArithmetic(a_pInput, a_Data);
    }

    virtual void visit(native::TIntegralType<bool>* a_pInput, visitor_data a_Data) { visitIntegral(a_pInput, a_Data); }
    virtual void visit(native::TIntegralType<char>* a_pInput, visitor_data a_Data) { visitIntegral(a_pInput, a_Data); }
    virtual void visit(native::TIntegralType<uchar>* a_pInput, visitor_data a_Data) { visitIntegral(a_pInput, a_Data); }
    virtual void visit(native::TIntegralType<schar>* a_pInput, visitor_data a_Data) { visitIntegral(a_pInput, a_Data); }
    virtual void visit(native::TIntegralType<short>* a_pInput, visitor_data a_Data) { visitIntegral(a_pInput, a_Data); }
    virtual void visit(native::TIntegralType<ushort>* a_pInput, visitor_data a_Data) { visitIntegral(a_pInput, a_Data); }
    virtual void visit(native::TIntegralType<int>* a_pInput, visitor_data a_Data) { visitIntegral(a_pInput, a_Data); }
    virtual void visit(native::TIntegralType<uint>* a_pInput, visitor_data a_Data) { visitIntegral(a_pInput, a_Data); }
    virtual void visit(native::TIntegralType<long>* a_pInput, visitor_data a_Data) { visitIntegral(a_pInput, a_Data); }
    virtual void visit(native::TIntegralType<ulong>* a_pInput, visitor_data a_Data) { visitIntegral(a_pInput, a_Data); }
    virtual void visit(native::TIntegralType<longlong>* a_pInput, visitor_data a_Data) { visitIntegral(a_pInput, a_Data); }
    virtual void visit(native::TIntegralType<ulonglong>* a_pInput, visitor_data a_Data) { visitIntegral(a_pInput, a_Data); }
    virtual void visit(native::TFloatingPointType<float>* a_pInput, visitor_data a_Data) { visitFloatingPoint(a_pInput, a_Data); }
    virtual void visit(native::TFloatingPointType<double>* a_pInput, visitor_data a_Data) { visitFloatingPoint(a_pInput, a_Data); }
    virtual void visit(native::TFloatingPointType<longdouble>* a_pInput, visitor_data a_Data) { visitFloatingPoint(a_pInput, a_Data); }

    o_if_wchar_t(virtual void visit(native::TIntegralType<wchar_t>* a_pInput, visitor_data a_Data) { visitIntegral(a_pInput, a_Data); });
    o_if_char16_t(virtual void visit(native::TIntegralType<char16_t>* a_pInput, visitor_data a_Data) { visitIntegral(a_pInput, a_Data); });
    o_if_char32_t(virtual void visit(native::TIntegralType<char32_t>* a_pInput, visitor_data a_Data) { visitIntegral(a_pInput, a_Data); });
};

o_namespace_end(phantom, reflection)
#endif // BuiltInOperators_h__
