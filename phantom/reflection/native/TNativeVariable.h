/* TODO LICENCE HERE */

#ifndef o_phantom_reflection_native_TNativeVariable_h__
#define o_phantom_reflection_native_TNativeVariable_h__



/* ****************** Includes ******************* */

/* **************** Declarations ***************** */

/* *********************************************** */
using namespace fastdelegate;

o_namespace_begin(phantom, reflection, native)

template<typename t_Ty>
class TNativeVariable : public Variable
{
public:
    typedef TNativeVariable<t_Ty> self_type;
    
public:
    TNativeVariable(Type* a_pContentType, const string& a_strName, t_Ty* a_pPointer, Range* a_pRange, modifiers_t a_uiModifiers = 0)
        : Variable(a_pPointer, a_pContentType, a_strName, a_pRange, a_uiModifiers|o_native)
    {}
    
    virtual void        getValue( void* dest ) const
    {
        *static_cast<t_Ty*>(dest) = *static_cast<t_Ty*>(m_pAddress);
    }
    virtual void        setValue( void const* src ) const
    {
        *static_cast<t_Ty*>(m_pAddress) = *static_cast<t_Ty const*>(src);
    }

};

o_namespace_end(phantom, reflection, native)

#endif // TNativeVariable_h__