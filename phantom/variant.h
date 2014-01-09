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

template<>
struct variant_type_helper<void*>
{
    static reflection::Type* type() 
    { 
        return typeOf<void*>();
    }
};

template<typename t_Ty>
struct variant_ctor_helper
{
    static reflection::Type* apply(byte* a_pBuffer,  t_Ty const& a_In)
    {
        reflection::Type* pType = typeOf<t_Ty>();
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
            return pType ? pType : typeOf<variant_generic_class*>(); // no reflection, store it just as void*
        }
        else 
        {
            memcpy(a_pBuffer, &rttiData.base, sizeof(t_Ty*));
            return rttiData.object_class->pointerType();
        }
    }
};

template<>
struct variant_ctor_helper<void*>
{
    static reflection::Type* apply(byte* a_pBuffer, void* const& a_In)
    {
        rtti_data rttiData = rttiDataOf(a_In);
        if(rttiData.isNull())
        {
            memcpy(a_pBuffer, &a_In, sizeof(void*));
            return typeOf<void*>(); // no reflection, store it just as void*
        }
        else 
        {
            memcpy(a_pBuffer, &rttiData.base, sizeof(void*));
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
    variant()
        : m_pType(nullptr)
    {

    }
    template<typename t_Ty>
    variant(const t_Ty& a_In) 
    {
        byte* pBuffer = (sizeof(t_Ty) > e_StaticBufferSize) 
            ? (m_Buffer.dynamicBuffer = (byte*)o_malloc(sizeof(t_Ty))) 
            : m_Buffer.staticBuffer;
        m_pType = variant_ctor_helper<t_Ty>::apply(pBuffer, a_In);
    }
    variant(const char* a_Str) 
    {
        new (m_Buffer.dynamicBuffer = (byte*)o_malloc(sizeof(string))) string(a_Str);
        m_pType = typeOf<string>();
    }
    variant(const variant& a_Other) 
        : m_pType(nullptr)
    {
        if(a_Other.isValid())
        {
            byte* pBuffer = (a_Other.size() > e_StaticBufferSize) 
                ? (m_Buffer.dynamicBuffer = (byte*)o_malloc(a_Other.size())) 
                : m_Buffer.staticBuffer;
            m_pType = a_Other.m_pType;
            m_pType->safeConstruct(pBuffer);
            m_pType->copy(pBuffer, a_Other._buffer());
        }
    }
    ~variant(void) 
    {
        if(m_pType)
            _release();
    }

    bool operator==(const variant& other) const 
    {
        return (m_pType == other.m_pType) AND m_pType->areValueEqual(_buffer(), other._buffer());
    }

    bool operator!=(const variant& other) const 
    {
        return !operator==(other);
    }

    variant& operator=(const variant& a_Other) 
    {
        if(m_pType)
        {
            _release();
        }
        if(a_Other.isValid())
        {
            byte* pBuffer = (a_Other.size() > e_StaticBufferSize) 
                ? (m_Buffer.dynamicBuffer = (byte*)o_malloc(a_Other.size())) 
                : m_Buffer.staticBuffer;
            m_pType = a_Other.m_pType;
            m_pType->safeConstruct(pBuffer);
            m_pType->copy(pBuffer, a_Other._buffer());
        }
        else m_pType = nullptr;
        return *this;
    }

    variant& operator=(const char* a_Str) 
    {
        if(m_pType)
        {
            _release();
        }
        new (m_Buffer.dynamicBuffer = (byte*)o_malloc(sizeof(string))) string(a_Str);
        m_pType = typeOf<string>();
        return *this;
    }

    template<typename t_Ty>
    variant& operator=(const t_Ty& a_In) 
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

    inline size_t size() const {return m_pType ? m_pType->getSize() : 0; }
    reflection::Type* type() const { return m_pType; }

    inline bool isValid() const { return m_pType != nullptr; }
    inline bool isNull() const { return m_pType == nullptr; }

    inline bool as(reflection::Type* a_pType, void* a_pDest) const
    {
        if(a_pType == nullptr OR m_pType == nullptr OR !m_pType->isImplicitlyConvertibleTo(a_pType))
        {
            return false;
        }
        m_pType->convertValueTo(a_pType, a_pDest, _buffer());
        return true;
    }

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
    inline void _release()
    {
        if(size() > e_StaticBufferSize)
        {
            m_pType->destroy(m_Buffer.dynamicBuffer);
            o_free(m_Buffer.dynamicBuffer);
        }
        else 
        {
            m_pType->destroy(m_Buffer.staticBuffer);
        }
    }

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
o_exposeN((phantom), variant);

#endif
