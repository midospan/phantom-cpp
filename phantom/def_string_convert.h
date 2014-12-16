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

#ifndef o_def_string_convert_h__
#define o_def_string_convert_h__

o_namespace_begin(phantom)


namespace reflection
{
    namespace detail
    {
        template<typename t_Ty> struct meta_type_id_of;
    }
}

enum string_converter_id
{
    string_converter_default,
    string_converter_array,
    string_converter_enum,
    string_converter_class,
    string_converter_classtype,
};

template<typename t_Ty, int t_MetaTypeId>
struct string_converter_helper // string_converter_default
{
    static void to(const reflection::Type* a_pType, string& a_strOut, const t_Ty* a_pSrc)
    {
        a_strOut += phantom::lexical_cast<string>(*a_pSrc);
    }
    static void toLiteral(const reflection::Type* a_pType, string& a_strOut, const t_Ty* a_pSrc)
    {
        a_strOut += phantom::lexical_cast<string>(*a_pSrc);
    }
    static void from(const reflection::Type* a_pType, const string& input, t_Ty* a_pDest)
    {
        *a_pDest = phantom::lexical_cast<t_Ty>(input);
    }
};

template<typename t_Ty>
struct string_converter_helper<t_Ty, string_converter_classtype>
{
    static void to(const reflection::ClassType* a_pClass, string& a_strOut, const t_Ty* a_pSrc)
    {
        a_pClass->reflection::ClassType::valueToString(a_strOut, a_pSrc);
    }
    static void toLiteral(const reflection::ClassType* a_pClass, string& a_strOut, const t_Ty* a_pSrc)
    {
        a_pClass->reflection::ClassType::valueToString(a_strOut, a_pSrc);
    }
    static void from(const reflection::ClassType* a_pClass, const string& a_strIn, t_Ty* a_pDest)
    {
        a_pClass->reflection::ClassType::valueFromString(a_strIn, a_pDest);
    }
};

template<typename t_Ty>
struct string_converter_helper<t_Ty, string_converter_class>
{
    static void to(const reflection::Class* a_pClass, string& a_strOut, const t_Ty* a_pSrc)
    {
        a_pClass->reflection::Class::valueToString(a_strOut, a_pSrc);
    }
    static void toLiteral(const reflection::Class* a_pClass, string& a_strOut, const t_Ty* a_pSrc)
    {
        a_pClass->reflection::Class::valueToString(a_strOut, a_pSrc);
    }
    static void from(const reflection::Class* a_pClass, const string& a_strIn, t_Ty* a_pDest)
    {
        a_pClass->reflection::Class::valueFromString(a_strIn, a_pDest);
    }
};

template<typename t_Ty>
struct string_converter_helper<t_Ty, string_converter_enum>
{
    static void toLiteral(const reflection::Enum* a_pEnum, string& a_strOut, const t_Ty* a_pSrc)
    {
        a_pEnum->reflection::Enum::valueToLiteral(a_strOut, a_pSrc);
    }
    static void to(const reflection::Enum* a_pEnum, string& a_strOut, const t_Ty* a_pSrc)
    {
        a_pEnum->reflection::Enum::valueToString(a_strOut, a_pSrc);
    }
    static void from(const reflection::Enum* a_pEnum, const string& a_strIn, t_Ty* a_pDest)
    {
        a_pEnum->reflection::Enum::valueFromString(a_strIn, a_pDest);
    }
};

template<typename t_Ty>
struct string_converter_helper<t_Ty, string_converter_array>
{
    static void toLiteral(const reflection::ArrayType* a_pArrayType, string& a_strOut, const t_Ty* a_pSrc)
    {
        a_pArrayType->reflection::ArrayType::valueToLiteral(a_strOut, a_pSrc);
    }
    static void to(const reflection::ArrayType* a_pArrayType, string& a_strOut, const t_Ty* a_pSrc)
    {
        a_pArrayType->reflection::ArrayType::valueToString(a_strOut, a_pSrc);
    }
    static void from(const reflection::ArrayType* a_pArrayType, const string& a_strIn, t_Ty* a_pDest)
    {
        a_pArrayType->reflection::ArrayType::valueFromString(a_strIn, a_pDest);
    }
};

template<typename t_Ty>
struct string_converter : public string_converter_helper<t_Ty,
    boost::is_array<t_Ty>::value
    ? string_converter_array
    : boost::is_enum<t_Ty>::value
    ? string_converter_enum
    : (boost::is_void<t_Ty>::value)
    ? string_converter_default
    : phantom::is_data_pointer<t_Ty>::value
    ? string_converter_default
    : boost::is_pointer<t_Ty>::value
    ? string_converter_default
    : ::boost::is_floating_point<t_Ty>::value
    ? string_converter_default
    : ::phantom::is_nullptr_t<t_Ty>::value
    ? string_converter_default
    : ::boost::is_integral<t_Ty>::value
    ? string_converter_default
    : ::boost::is_member_function_pointer<t_Ty>::value
    ? string_converter_default
    : ::boost::is_member_object_pointer<t_Ty>::value
    ? string_converter_default
    : boost::is_union<t_Ty>::value
    ? string_converter_classtype
    : boost::is_class<t_Ty>::value
    ? is_structure<t_Ty>::value
    ? string_converter_classtype
    : string_converter_class
    : string_converter_default>
{

};

template<>
struct string_converter<void>
{
    static void to(const reflection::Type* a_pType, string& a_strOut, const void* a_pSrc)
    {
    }
    static void toLiteral(const reflection::Type* a_pType, string& a_strOut, const void* a_pSrc)
    {
    }
    static void from(const reflection::Type* a_pType, const string& a_strIn, void* a_pDest)
    {
    }
};

template<>
struct string_converter<std::nullptr_t>
{
    static void toLiteral(const reflection::Type* a_pType, string& a_strOut, const std::nullptr_t* a_pSrc)
    {
        if(*a_pSrc != nullptr)
        {
            o_exception(exception::reflection_runtime_exception, "parsing nullptr value failed");
        }
        a_strOut = "nullptr";
    }
    static void to(const reflection::Type* a_pType, string& a_strOut, const std::nullptr_t* a_pSrc)
    {
        if(*a_pSrc != nullptr)
        {
            o_exception(exception::reflection_runtime_exception, "parsing nullptr value failed");
        }
        a_strOut = "nullptr";
    }
    static void from(const reflection::Type* a_pType, const string& a_strIn, std::nullptr_t* a_pDest)
    {
        if(a_strIn != "nullptr")
        {
            o_exception(exception::reflection_runtime_exception, "parsing nullptr value failed");
        }
        *a_pDest = nullptr;
    }
};

template<>
struct string_converter<char>
{
    static void toLiteral(const reflection::Type* a_pType, string& a_strOut, const char* a_pSrc)
    {
        a_strOut += "'";
        switch(*a_pSrc)
        {
        case '\'':  a_strOut += "\\'"; break;
        case '\\': a_strOut += "\\\\"; break;
        case '\n': a_strOut += "\\n" ; break;
        case '\r': a_strOut += "\\r" ; break;
        case '\t': a_strOut += "\\t" ; break;
        case '\0': a_strOut += "\\0" ; break;
        default:
            a_strOut += *a_pSrc;
        }
        a_strOut += "'";
    }
    static void to(const reflection::Type* a_pType, string& a_strOut, const char* a_pSrc)
    {
        a_strOut += *a_pSrc;
    }
    static void from(const reflection::Type* a_pType, const string& a_strIn, char* a_pDest)
    {
        *a_pDest = a_strIn[0];
    }
};

template<>
struct string_converter<bool>
{
    static void toLiteral(const reflection::Type* a_pType, string& a_strOut, const bool* a_pSrc)
    {
        a_strOut += *a_pSrc ? "true" : "false";
    }
    static void to(const reflection::Type* a_pType, string& a_strOut, const bool* a_pSrc)
    {
        a_strOut += *a_pSrc ? "true" : "false";
    }
    static void from(const reflection::Type* a_pType, const string& a_strIn, bool* a_pDest)
    {
        if(a_strIn == "true")
        {
            *a_pDest = true;
        }
        else
        {
            *a_pDest = false;
        }
    }
};

template<>
struct string_converter<wchar_t>
{
    static void toLiteral(const reflection::Type* a_pType, string& a_strOut, const wchar_t* a_pSrc)
    {
        a_strOut += *((const char*)a_pSrc);
        a_strOut += *(((const char*)a_pSrc)+1);
    }
    static void to(const reflection::Type* a_pType, string& a_strOut, const wchar_t* a_pSrc)
    {
        a_strOut += *((const char*)a_pSrc);
        a_strOut += *(((const char*)a_pSrc)+1);
    }
    static void from(const reflection::Type* a_pType, const string& a_strIn, wchar_t* a_pDest)
    {
        *((char*)a_pDest) = a_strIn[0];
        *(((char*)a_pDest)+1) = a_strIn[1];
    }
};

template<>
struct string_converter<signal_t>
{
    static void toLiteral(const reflection::Type* a_pType, string& a_strOut, const signal_t* a_pSrc)
    {
    }
    static void to(const reflection::Type* a_pType, string& a_strOut, const signal_t* a_pSrc)
    {
    }
    static void from(const reflection::Type* a_pType, const string& a_strIn, signal_t* a_pDest)
    {
    }
};

template<typename t_Alloc>
struct string_converter<std::basic_string<char, std::char_traits<char>, t_Alloc> >
{
    typedef std::basic_string<char, std::char_traits<char>, t_Alloc> self_type;

    static void toLiteral(const reflection::Type* a_pType, string& a_strOut, const self_type* a_pSrc)
    {
        a_strOut += "\"";
        for(auto it = a_pSrc->begin(); it != a_pSrc->end(); ++it)
        {
            switch(*it)
            {
            case '"':  a_strOut += "\\\""; break;
            case '\\': a_strOut += "\\\\"; break;
            case '\n': a_strOut += "\\n" ; break;
            case '\r': a_strOut += "\\r" ; break;
            case '\t': a_strOut += "\\t" ; break;
            case '\0': a_strOut += "\\0" ; break;
            default:
                a_strOut += *it;
            }
        }
        a_strOut += "\"";
    }
    static void to(const reflection::Type* a_pType, string& a_strOut, const self_type* a_pSrc)
    {
        a_strOut.insert(a_strOut.end(), a_pSrc->begin(), a_pSrc->end());
    }
    static void from(const reflection::Type* a_pType, const string& a_strIn, self_type* a_pDest)
    {
        a_pDest->insert(a_pDest->end(), a_strIn.begin(), a_strIn.end());
    }
};

o_namespace_end(phantom)

#endif // o_def_string_convert_h__
