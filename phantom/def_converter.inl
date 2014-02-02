

template<typename t_Ty>
struct default_converter 
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