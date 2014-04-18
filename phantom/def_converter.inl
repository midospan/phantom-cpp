

template<typename t_Ty>
struct default_converter_enum 
{
    // By default converter just copy
    static void convert(reflection::Type* a_pDestType, void* a_pDestValue, const t_Ty* a_pSrcValue)
    {
        if(a_pDestType == typeOf<t_Ty>()) 
        {
            copier<t_Ty>::copy((t_Ty*)a_pDestValue, a_pSrcValue); 
            return;
        }
        else 
        {
            switch(a_pDestType->getTypeId())
            {
                case reflection::e_char: *((char*)a_pDestValue) = (char)*a_pSrcValue; return;
                case reflection::e_unsigned_char: *((uchar*)a_pDestValue) = (uchar)*a_pSrcValue; return;
                case reflection::e_signed_char: *((schar*)a_pDestValue) = (schar)*a_pSrcValue; return;
                case reflection::e_short: *((short*)a_pDestValue) = (short)*a_pSrcValue; return;
                case reflection::e_unsigned_short: *((ushort*)a_pDestValue) = (ushort)*a_pSrcValue; return;
                case reflection::e_int: *((int*)a_pDestValue) = (int)*a_pSrcValue; return;
                case reflection::e_unsigned_int: *((uint*)a_pDestValue) = (uint)*a_pSrcValue; return;
                case reflection::e_long: *((long*)a_pDestValue) = (long)*a_pSrcValue; return;
                case reflection::e_unsigned_long: *((ulong*)a_pDestValue) = (ulong)*a_pSrcValue; return;
                case reflection::e_long_long: *((longlong*)a_pDestValue) = (longlong)*a_pSrcValue; return;
                case reflection::e_unsigned_long_long: *((ulonglong*)a_pDestValue) = (ulonglong)*a_pSrcValue; return;
                case reflection::e_float: *((float*)a_pDestValue) = (float)*a_pSrcValue; return;
                case reflection::e_double: *((double*)a_pDestValue) = (double)*a_pSrcValue; return;
                case reflection::e_long_double: *((longdouble*)a_pDestValue) = (longdouble)*a_pSrcValue; return;
#pragma warning(disable:4800)
                case reflection::e_bool: *((bool*)a_pDestValue) = (bool)*a_pSrcValue; return;
#pragma warning(default:4800)
                default:
                    break;
            }
        }
        o_exception(exception::reflection_runtime_exception, "Cannot convert types");
    }
    static bool isConvertibleTo(reflection::Type* a_pType)
    {
        return ((a_pType->getTypeId() >= reflection::e_char) AND (a_pType->getTypeId() <= reflection::e_enum));
    }
    static bool isImplicitlyConvertibleTo(reflection::Type* a_pType)
    {
        return a_pType == typeOf<t_Ty>() OR ((a_pType->getTypeId() >= reflection::e_char) AND (a_pType->getTypeId() <= reflection::e_wchar_t));
    }
};

template<typename t_Ty, bool is_enum>
struct default_converter_helper : public default_converter_enum<t_Ty>
{
};

template<typename t_Ty>
struct default_converter_helper<t_Ty, false>
{
    // By default converter just copy
    static void convert(reflection::Type* a_pDestType, void* a_pDestValue, const t_Ty* a_pSrcValue)
    {
        reflection::ReferenceType* pRefType = a_pDestType->asReferenceType();
        if(pRefType)
        {
            pRefType->getReferencedType()->copy(a_pDestValue, a_pSrcValue); // for references, copy address to dest
        }
        // By default just copy
        else copier<t_Ty>::copy((t_Ty*)a_pDestValue, a_pSrcValue);

    }
    static bool isConvertibleTo(reflection::Type* a_pDestType)
    {
        if(a_pDestType->removeConst() == reflection::Types::get<t_Ty>()->removeConst()) return !has_copy_disabled<t_Ty>::value;
        reflection::ReferenceType* pRefType = a_pDestType->asReferenceType();
        if(pRefType AND pRefType->getReferencedType()->asReferenceType()) return false;
        return pRefType AND isConvertibleTo(pRefType->getReferencedType()) AND !has_copy_disabled<t_Ty>::value;
    }
    static bool isImplicitlyConvertibleTo(reflection::Type* a_pDestType)
    {
        if(a_pDestType->removeConst() == reflection::Types::get<t_Ty>()->removeConst()) return !has_copy_disabled<t_Ty>::value;
        reflection::ReferenceType* pRefType = a_pDestType->asReferenceType();
        if(pRefType AND pRefType->getReferencedType()->asReferenceType()) return false;
        return pRefType AND isImplicitlyConvertibleTo(pRefType->getReferencedType()) AND !has_copy_disabled<t_Ty>::value;
    }
};

template<typename t_Ty>
struct default_converter : public default_converter_helper<t_Ty, boost::is_enum<t_Ty>::value>
{

};