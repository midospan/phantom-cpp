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

o_declareN(class, (phantom), variant);

o_declareN((phantom), variant_generic_class);

o_namespace_begin(phantom)

template<typename t_Ty>
struct variant_type_helper
{
    inline static reflection::Type* type();
};

template<typename t_Ty>
struct variant_type_helper<t_Ty*>
{
    inline static reflection::Type* type();
};

template<typename t_Ty>
struct variant_ctor_helper
{
    inline static reflection::Type* apply(byte* a_pBuffer,  t_Ty const& a_In);
};

template<typename t_Ty>
struct variant_ctor_helper<t_Ty*>
{
    inline static reflection::Type* apply(byte* a_pBuffer, t_Ty* const& a_In);    
};

class o_export variant
{
    enum {
        e_StaticBufferSize = 8,
    };

public:
    static const variant null;
    inline variant() : m_pType(nullptr) {}

    template<typename t_Ty>
    inline variant(const t_Ty& a_In) ;

    inline variant(const char* a_Str) ;

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
    inline variant& operator=(const t_Ty& a_In) ;

    inline size_t size() const ;

    inline reflection::Type* type() const { return m_pType; }

    inline const byte* buffer() const { return _buffer(); }

    inline byte* buffer() { return _buffer(); }

    inline bool isValid() const { return m_pType != nullptr; }

    inline bool isNull() const { return m_pType == nullptr; }

    inline bool as(reflection::Type* a_pType, void* a_pDest) const;

    inline phantom::variant as(reflection::Type* a_pType) const;

    template<typename t_Ty>
    inline bool as(t_Ty* a_pDest) const;

    template<typename t_Ty>
    inline t_Ty as(bool* a_pOK = nullptr) const;

    inline void toLiteral(string& out) const;

    inline void toString(string& out) const;

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

typedef std::pair<variant, variant> variant_pair;

o_namespace_end(phantom)

#endif
