#ifndef o_variant_h__
#define o_variant_h__


/* ****************** Includes ******************* */
#include "phantom/phantom.h"
/* **************** Declarations ***************** */

/* *********************************************** */

o_namespace_begin(phantom)

class variant_generic_class
{

};


o_namespace_end(phantom)


o_classN((phantom), variant_generic_class)
{
    o_reflection {};
};
o_exposeN((phantom), variant_generic_class);

o_namespace_begin(phantom)

template<typename t_Ty>
struct variant_type_helper
{
    static reflection::Type* type() 
    { 
        reflection::Type* pType = typeOf<t_Ty>();
        o_warning(pType != nullptr, "variant type cannot be deduced without reflection");
        return pType ; // no reflection, store it just as void*
    }
};

template<typename t_Ty>
struct variant_type_helper<t_Ty*>
{
    static reflection::Type* type() 
    { 
        reflection::Type* pType = typeOf<t_Ty*>();
        //o_warning(pType != nullptr, "variant pointer type cannot be deduced without reflection, store it as void*");
        return pType ? pType : typeOf<variant_generic_class*>(); // no reflection, store it just as void*
    }
};

template<typename t_Ty>
struct variant_ctor_helper
{
    static reflection::Type* apply(byte* a_pBuffer,  t_Ty const& a_In)
    {
        reflection::Type* pType = typeOf<t_Ty>();
        o_assert(pType->isCopyable());
        pType->safeConstruct(a_pBuffer);
        pType->copy(a_pBuffer, &a_In);
        return pType;
    }
};

template<typename t_Ty>
struct variant_ctor_helper<t_Ty*>
{
    static reflection::Type* apply(byte* a_pBuffer, t_Ty* const& a_In)
    {
        rtti_data rttiData = rttiDataOf(a_In);
        if(rttiData.isNull())
        {
            memcpy(a_pBuffer, &a_In, sizeof(t_Ty*));
            reflection::Type* pType = typeOf<t_Ty*>();
            o_assert(pType == nullptr OR pType->isCopyable());
            return pType ? pType : typeOf<variant_generic_class*>(); // no reflection, store it just as void*
        }
        else 
        {
            memcpy(a_pBuffer, &rttiData.base, sizeof(t_Ty*));
            return rttiData.object_class->pointerType();
        }
    }
};

class o_export variant
{
    enum {
        e_StaticBufferSize = 8,
    };

public:
    static const variant null;
    inline variant()
        : m_pType(nullptr)
    {

    }
    template<typename t_Ty>
    inline variant(const t_Ty& a_In) 
    {
        byte* pBuffer = (sizeof(t_Ty) > e_StaticBufferSize) 
            ? (m_Buffer.dynamicBuffer = (byte*)o_malloc(sizeof(t_Ty))) 
            : m_Buffer.staticBuffer;
        m_pType = variant_ctor_helper<t_Ty>::apply(pBuffer, a_In);
    }
    inline variant(const char* a_Str) 
    {
        new (m_Buffer.dynamicBuffer = (byte*)o_malloc(sizeof(string))) string(a_Str);
        m_pType = phantom::reflection::Types::get<string>();
    }
    inline variant(const variant& a_Other);
    ~variant(void) 
    {
        if(m_pType)
            _release();
    }

    inline void setType(reflection::Type* a_pType);

    inline bool operator==(const variant& other) const ;

    inline bool operator!=(const variant& other) const ;

    inline variant& operator=(const variant& a_Other) ;

    inline variant& operator=(variant&& a_Other);

    inline variant& operator=(const char* a_Str) ;

    template<typename t_Ty>
    inline variant& operator=(const t_Ty& a_In) 
    {
        if(m_pType)
        {
            _release();
        }
        byte* pBuffer = (sizeof(t_Ty) > e_StaticBufferSize) 
            ? (m_Buffer.dynamicBuffer = (byte*)o_malloc(sizeof(t_Ty))) 
            : m_Buffer.staticBuffer;
        m_pType = variant_ctor_helper<t_Ty>::apply(pBuffer, a_In);
        return *this;
    }

    inline size_t size() const ;

    inline reflection::Type* type() const { return m_pType; }

    inline const byte* buffer() const { return _buffer(); }

    inline byte* buffer() { return _buffer(); }

    inline bool isValid() const { return m_pType != nullptr; }

    inline bool isNull() const { return m_pType == nullptr; }

    inline bool as(reflection::Type* a_pType, void* a_pDest) const;

    inline phantom::variant as(reflection::Type* a_pType) const;

    template<typename t_Ty>
    inline bool as(t_Ty* a_pDest) const
    {
        return as(variant_type_helper<t_Ty>::type(), a_pDest);
    }

    template<typename t_Ty>
    inline t_Ty as(bool* a_pOK = nullptr) const
    {
        byte temp[sizeof(t_Ty)];
        o_static_assert_msg(!boost::is_class<t_Ty>::value, 
            "template return type is a class, it must be a fundamental type"
            ", use 'as(t_Ty* a_pDest)' instead for class to have proper copy to pointed memory");
        variant_type_helper<t_Ty>::type()->safeConstruct(&temp);
        if(a_pOK)
        {
            *a_pOK = as(variant_type_helper<t_Ty>::type(), &temp);
        }
        else 
        {
            as(variant_type_helper<t_Ty>::type(), &temp);
        }
        return *((t_Ty*)&temp);
    }

protected:
    inline byte* _buffer() const
    {
        return (size() > e_StaticBufferSize) 
            ? m_Buffer.dynamicBuffer 
            : (byte*)m_Buffer.staticBuffer;
    }
    inline void _release();

protected:
    reflection::Type* m_pType;

    union Union
    {	// storage for small buffer or pointer to larger one
        byte    staticBuffer[e_StaticBufferSize];
        byte *  dynamicBuffer;
    } m_Buffer;             
};

o_namespace_end(phantom)



o_classN((phantom), variant)
{
    o_reflection {};
};

#endif
