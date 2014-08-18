
o_namespace_begin(phantom)


template<>
struct variant_type_helper<void*>
{
    static reflection::Type* type() 
    { 
        return (reflection::Type*)typeOf<void*>();
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

inline variant::variant(const variant& a_Other) 
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

inline void variant::setType(reflection::Type* a_pType)
{
    o_assert(isNull());
    o_assert(a_pType->isCopyable());
    byte* pBuffer = (a_pType->getSize() > e_StaticBufferSize) 
        ? (m_Buffer.dynamicBuffer = (byte*)o_malloc(a_pType->getSize())) 
        : m_Buffer.staticBuffer;
    m_pType = a_pType;
    m_pType->safeConstruct(pBuffer);
}

inline bool variant::operator==(const variant& other) const 
{
    return (m_pType == other.m_pType) AND m_pType->areValueEqual(_buffer(), other._buffer());
}

inline bool variant::operator!=(const variant& other) const 
{
    return !operator==(other);
}

inline variant& variant::operator=(const variant& a_Other) 
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

inline variant& variant::operator=(variant&& a_Other) 
{
    if(m_pType)
    {
        _release();
    }
    if(a_Other.isValid())
    {
        if(a_Other.size() > e_StaticBufferSize) 
        {
            m_Buffer.dynamicBuffer = a_Other.m_Buffer.dynamicBuffer;
            a_Other.m_Buffer.dynamicBuffer = nullptr;
        }
        else
        {
            memcpy(m_Buffer.staticBuffer, a_Other.m_Buffer.staticBuffer, e_StaticBufferSize);
        }
        m_pType = a_Other.m_pType;
        a_Other.m_pType = nullptr;
    }
    else m_pType = nullptr;
    return *this;
}

inline size_t variant::size() const 
{
    return m_pType ? m_pType->getSize() : 0; 
}

inline bool variant::as(reflection::Type* a_pType, void* a_pDest) const
{
    if(a_pType == nullptr OR m_pType == nullptr OR !m_pType->isImplicitlyConvertibleTo(a_pType))
    {
        return false;
    }
    m_pType->convertValueTo(a_pType, a_pDest, _buffer());
    return true;
}

inline variant variant::as(reflection::Type* a_pType) const
{
    if(a_pType == nullptr OR m_pType == nullptr OR !m_pType->isImplicitlyConvertibleTo(a_pType))
    {
        return phantom::variant();
    }
    variant result;
    byte* pBuffer = (a_pType->getSize() > e_StaticBufferSize) 
        ? (result.m_Buffer.dynamicBuffer = (byte*)o_malloc(a_pType->getSize())) 
        : result.m_Buffer.staticBuffer;
    result.m_pType = a_pType;
    m_pType->convertValueTo(a_pType, pBuffer, _buffer());
    return result;
}

inline void variant::_release()
{
    if(size() > e_StaticBufferSize)
    {
        m_pType->terminate(m_Buffer.dynamicBuffer);
        m_pType->destroy(m_Buffer.dynamicBuffer);
        o_free(m_Buffer.dynamicBuffer);
    }
    else 
    {
        m_pType->terminate(m_Buffer.staticBuffer);
        m_pType->destroy(m_Buffer.staticBuffer);
    }
}          

o_namespace_end(phantom)