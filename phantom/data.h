/* TODO LICENCE HERE */

#ifndef o_data_h__
#define o_data_h__

/* ****************** Includes ******************* */

/* **************** Declarations ***************** */
o_declareN(class, (phantom), data)
/* *********************************************** */
o_namespace_begin(phantom)
/**
 * \brief data stores a memory address with the reflection Type associated
 */
class data
{
public:
    data() : m_address(0), m_type(0) {}
    data(void* a_pAddress, reflection::Type* a_pType)
        : m_address(a_pAddress)
        , m_type(a_pType)
    {

    }
    inline bool isNull() const { return m_address == NULL; }
    template<typename t_Ty>
    inline data(t_Ty* const a_address);

    template<typename t_Ty>
    inline data const& operator=(t_Ty* const a_address);

    template<typename t_Ty>
    inline t_Ty* as() const;

    phantom::data       cast(reflection::Type* a_pTargetType) const;
    void*               address() const { return m_address; }
    reflection::Type*   type() const { return m_type; }
    boolean             operator==(const phantom::data& a_Other) const
    {
        return a_Other.m_address == m_address AND a_Other.m_type == m_type;
    }
    boolean             operator!=(const phantom::data& a_Other) const
    {
        return a_Other.m_address != m_address OR a_Other.m_type != m_type;
    }
    boolean             operator<(const phantom::data& a_Other) const
    {
        return m_address == a_Other.m_address ? m_type < a_Other.m_type : m_address < a_Other.m_address;
    }
    inline void        destroy() ;

protected:
    void*              m_address;
    reflection::Type*  m_type;
};

o_namespace_end(phantom)

#endif // o_data_h__