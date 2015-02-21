/* TODO LICENCE HERE */

#ifndef o_phantom_reflection_TRange_h__
#define o_phantom_reflection_TRange_h__
// #pragma message("Including "__FILE__)


/* ****************** Includes ******************* */
#include <phantom/reflection/Range.h>
/* *********************************************** */
/* **************** Declarations ***************** */
/* *********************************************** */

o_namespace_begin(phantom, reflection, native)

struct null_range {};

template<typename t_Ty>
class TRange : public Range
{
public:
    typedef TRange<t_Ty> self_type;

public:
    TRange(t_Ty a_Min, t_Ty a_Default, t_Ty a_Max)
        : Range(typeOf<t_Ty>())
        , m_Min(a_Min)
        , m_Default(a_Default)
        , m_Max(a_Max)
    {

    }
    virtual Range* clone() const
    {
        return o_dynamic_proxy_new(self_type)(m_Min, m_Default, m_Max);
    }

    virtual void getMin(void* a_pDest) const
    {
        *((t_Ty*)a_pDest) = m_Min;
    }

    virtual void getMax(void* a_pDest) const
    {
        *((t_Ty*)a_pDest) = m_Max;
    }

    virtual void getDefault(void* a_pDest) const
    {
        *((t_Ty*)a_pDest) = m_Default;
    }

    virtual void setMin(const void* a_pSrc)
    {
        m_Min = *((const t_Ty*)a_pSrc);
    }

    virtual void setMax(const void* a_pSrc)
    {
        m_Max = *((const t_Ty*)a_pSrc);
    }

    virtual void setDefault(const void* a_pSrc)
    {
        m_Default = *((const t_Ty*)a_pSrc);
    }

protected:
    t_Ty m_Min;
    t_Ty m_Max;
    t_Ty m_Default;
};

template<typename t_Ty>
class TRange<const t_Ty&> : public TRange<t_Ty>
{
    TRange(const t_Ty& a_Min, const t_Ty& a_Default, const t_Ty& a_Max) : TRange<t_Ty>(a_Min, a_Default, a_Max) {}
};


template<typename t_Ty>
inline Range* CreateRange(t_Ty a_Default)
{
    o_static_assert(!(boost::is_same<t_Ty, null_range>::value));
    return o_dynamic_proxy_new(TRange<t_Ty>)(std::numeric_limits<t_Ty>::min(), a_Default, std::numeric_limits<t_Ty>::max());
}

template<>
inline Range* CreateRange<null_range>(null_range )
{
    return nullptr;
}

template<typename t_Ty>
inline TRange<t_Ty>* CreateRange(t_Ty a_Min, t_Ty a_Default, t_Ty a_Max)
{
    typedef o_NESTED_TYPE boost::remove_cv<o_NESTED_TYPE boost::remove_reference<t_Ty>::type>::type type;
    o_static_assert(boost::has_less<type>::value && boost::has_equal_to<type>::value);
    return o_dynamic_proxy_new(TRange<t_Ty>)(a_Min, a_Default, a_Max);
}

template<typename t_Ty>
TRange<t_Ty>* CreateRange(t_Ty a_Min, t_Ty a_Max)
{
    return o_dynamic_proxy_new(TRange<t_Ty>)(a_Min, t_Ty(), a_Max);
}

o_namespace_end(phantom, reflection, native)

#endif
