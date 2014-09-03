
template<typename t_Ty>
struct default_converter_class_type;

template<typename t_Ty>
struct default_converter_integral 
{
    // By default converter just copy
    static void convert(reflection::Type* a_pType, reflection::Type* a_pDestType, void* a_pDestValue, const t_Ty* a_pSrcValue)
    {
        if(a_pDestType == a_pType) 
        {
            a_pType->copy((t_Ty*)a_pDestValue, a_pSrcValue); 
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
                case reflection::e_pointer: *((void**)a_pDestValue) = (void*)*a_pSrcValue; return;
                default:
                    break;
            }
        }
        return default_converter_helper<t_Ty, false>::convert(a_pType, a_pDestType, a_pDestValue, a_pSrcValue);
    }
    static bool isConvertibleTo(reflection::Type* a_pType, reflection::Type* a_pDestType)
    {
        reflection::ReferenceType* pRefDestType = a_pDestType->asReferenceType();
        if(pRefDestType AND pRefDestType->getReferencedType()->asConstType())
            return isConvertibleTo(a_pType, a_pDestType->removeReference()->removeConst());
        return ((a_pDestType->getTypeId() >= reflection::e_char) AND (a_pDestType->getTypeId() <= reflection::e_enum)) OR a_pDestType->getTypeId() == reflection::e_pointer;
    }
    static bool isImplicitlyConvertibleTo(reflection::Type* a_pType, reflection::Type* a_pDestType)
    {
        reflection::ReferenceType* pRefDestType = a_pDestType->asReferenceType();
        if(pRefDestType AND pRefDestType->getReferencedType()->asConstType())
            return isImplicitlyConvertibleTo(a_pType, a_pDestType->removeReference()->removeConst());
        return a_pDestType == a_pType 
            OR ((a_pDestType->getTypeId() >= reflection::e_char) AND (a_pDestType->getTypeId() <= reflection::e_wchar_t))
            
            ;
    }
};

template<typename t_Ty, bool is_enum>
struct default_converter_helper : public default_converter_integral<t_Ty>
{
};

template<typename t_Ty, bool is_class>
struct default_converter_class_type_helper : public default_converter_class_type<t_Ty>
{
};

template<typename t_Ty>
struct default_converter_helper<t_Ty, false> : default_converter_class_type_helper<t_Ty, boost::is_class<t_Ty>::value>
{

};

template<typename t_Ty>
struct default_converter_class_type_helper<t_Ty, false>
{
    // By default converter just copy
    static void convert(reflection::Type* a_pType, reflection::Type* a_pDestType, void* a_pDestValue, const t_Ty* a_pSrcValue)
    {
        reflection::ReferenceType* pRefType = a_pDestType->asReferenceType();
        if(pRefType)
        {
            pRefType->getReferencedType()->copy(a_pDestValue, a_pSrcValue); // for references, copy address to dest
        }
        // By default just copy
        else a_pType->copy((t_Ty*)a_pDestValue, a_pSrcValue);

    }
    static bool isConvertibleTo(reflection::Type* a_pType, reflection::Type* a_pDestType)
    {
        if(a_pDestType->removeConst() == a_pType->removeConst()) return !a_pType->hasCopyDisabled();
        reflection::ReferenceType* pRefDestType = a_pDestType->asReferenceType();
        if(pRefDestType AND pRefDestType->getReferencedType()->asConstType())
            return isConvertibleTo(a_pType, a_pDestType->removeReference()->removeConst());
        return false;
    }
    static bool isImplicitlyConvertibleTo(reflection::Type* a_pType, reflection::Type* a_pDestType)
    {
        if(a_pDestType->removeConst() == a_pType->removeConst()) return a_pType->isCopyConstructible();
        reflection::ReferenceType* pRefDestType = a_pDestType->asReferenceType();
        if(pRefDestType AND pRefDestType->getReferencedType()->asConstType())
            return isImplicitlyConvertibleTo(a_pType, a_pDestType->removeReference()->removeConst());
        return false;
    }
};

template<typename t_Ty>
struct default_converter : public default_converter_helper<t_Ty, boost::is_integral<t_Ty>::value OR boost::is_enum<t_Ty>::value>
{

};
