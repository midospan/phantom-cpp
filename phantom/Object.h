/* TODO LICENCE HERE */

#ifndef o_object_h__
#define o_object_h__

/* ****************** Includes ******************* */

/* **************** Declarations ***************** */
o_declareN(class, (phantom), object)
/* *********************************************** */
o_namespace_begin(phantom)

/**
  * \brief object stores a memory address with the reflection ClassType associated
  */
class object
{
public:
    object() : m_address(0), m_class_type(0) {}
    object(void* a_pAddress, reflection::ClassType* a_pClassType)
        : m_address(a_pAddress)
        , m_class_type(a_pClassType)
    {

    }
    template<typename t_Ty>
    inline object(t_Ty* const a_address);

    template<typename t_Ty>
    inline object& operator=(t_Ty* const a_address);

    template<typename t_Ty>
    inline t_Ty* as  ();

    boolean isNull() const { return m_address == nullptr; }
    void destroy();

    operator data  ()
    {
        return data(m_address,(reflection::Type*)m_class_type);
    }

    boolean             operator==(const phantom::object& a_Other) const
    {
        return a_Other.m_address == m_address AND a_Other.m_class_type == m_class_type;
    }

    boolean             operator!=(const phantom::object& a_Other) const
    {
        return a_Other.m_address != m_address OR a_Other.m_class_type != m_class_type;
    }

    void*                   address() const { return m_address; }
    reflection::ClassType*  classType() const { return m_class_type; }

protected:
    void*                   m_address;
    reflection::ClassType*  m_class_type;
};


o_namespace_end(phantom)

#endif // o_object_h__