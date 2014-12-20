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

#ifndef o_def_converter_h__
#define o_def_converter_h__

o_namespace_begin(phantom)


template<typename t_Ty, bool>
struct default_converter_helper;

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
                case reflection::e_uchar: *((uchar*)a_pDestValue) = (uchar)*a_pSrcValue; return;
                case reflection::e_schar: *((schar*)a_pDestValue) = (schar)*a_pSrcValue; return;
                case reflection::e_short: *((short*)a_pDestValue) = (short)*a_pSrcValue; return;
                case reflection::e_ushort: *((ushort*)a_pDestValue) = (ushort)*a_pSrcValue; return;
                case reflection::e_int: *((int*)a_pDestValue) = (int)*a_pSrcValue; return;
                case reflection::e_uint: *((uint*)a_pDestValue) = (uint)*a_pSrcValue; return;
                case reflection::e_long: *((long*)a_pDestValue) = (long)*a_pSrcValue; return;
                case reflection::e_ulong: *((ulong*)a_pDestValue) = (ulong)*a_pSrcValue; return;
                case reflection::e_longlong: *((longlong*)a_pDestValue) = (longlong)*a_pSrcValue; return;
                case reflection::e_ulonglong: *((ulonglong*)a_pDestValue) = (ulonglong)*a_pSrcValue; return;
                case reflection::e_float: *((float*)a_pDestValue) = (float)*a_pSrcValue; return;
                case reflection::e_double: *((double*)a_pDestValue) = (double)*a_pSrcValue; return;
                case reflection::e_longdouble: *((longdouble*)a_pDestValue) = (longdouble)*a_pSrcValue; return;
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

template<>
struct default_converter<std::nullptr_t>
{
    // By default converter just copy
    static void convert(reflection::Type* a_pType, reflection::Type* a_pDestType, void* a_pDestValue, const std::nullptr_t* a_pSrcValue)
    {
        *((void**)a_pDestValue) = nullptr;
    }
    static bool isConvertibleTo(reflection::Type* a_pType, reflection::Type* a_pDestType)
    {
        return a_pDestType->asDataPointerType() != nullptr;
    }
    static bool isImplicitlyConvertibleTo(reflection::Type* a_pType, reflection::Type* a_pDestType)
    {
        return a_pDestType->asDataPointerType() != nullptr;
    }
};

template<typename t_Ty>
struct default_converter_class_type
{
    static bool isImplicitlyConvertibleTo(reflection::ClassType* a_pType, reflection::Type* a_pDestType)
    {
        return a_pType->ClassType::isImplicitlyConvertibleTo(a_pDestType);
    }
    static bool isConvertibleTo(reflection::ClassType* a_pType, reflection::Type* a_pDestType)
    {
        return a_pType->ClassType::isConvertibleTo(a_pDestType);
    }
    static void convert(reflection::ClassType* a_pClassType, reflection::Type* a_pDestType, void* a_pDestValue, const t_Ty* a_pSrcValue)
    {
        a_pClassType->ClassType::convertValueTo(a_pDestType, a_pDestValue, a_pSrcValue);
    }
};


////////////////////////////////////////////////////////////////////////////////////////////////////
/// \struct converter
///
/// \brief  converter.
/// 		Provides conversion of type instances
///
////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename t_Ty>
struct converter : public default_converter<t_Ty>
{
};

o_namespace_end(phantom)

#endif // o_def_converter_h__
