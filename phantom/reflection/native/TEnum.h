/* TODO LICENCE HERE */

#ifndef o_phantom_reflection_native_TEnum_h__
#define o_phantom_reflection_native_TEnum_h__



/* ****************** Includes ******************* */
/* **************** Declarations ***************** */
/* *********************************************** */
o_namespace_begin(phantom, reflection, native)

template<typename t_Ty>
class TEnum : public Enum
{
public:
    static char underlyingTypeDeducer(char);
    static schar underlyingTypeDeducer(schar);
    static uchar underlyingTypeDeducer(uchar);
    static short underlyingTypeDeducer(short);
    static ushort underlyingTypeDeducer(ushort);
    static int underlyingTypeDeducer(int);
    static uint underlyingTypeDeducer(uint);
    static long underlyingTypeDeducer(long);
    static ulong underlyingTypeDeducer(ulong);
    static longlong underlyingTypeDeducer(longlong);
    static ulonglong underlyingTypeDeducer(ulonglong);

    TEnum(const string& a_strName, ushort a_uiSize, ushort a_uiAlignment, modifiers_t a_Modifiers = 0)
        : Enum(typeOf<decltype(underlyingTypeDeducer((t_Ty)0))>(), a_strName, a_uiSize, a_uiAlignment, a_Modifiers)
    {

    }
};


o_namespace_end(phantom, reflection, native)

#endif // reflection_native_TEnum_h__